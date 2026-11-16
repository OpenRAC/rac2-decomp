#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } RopeVector;
extern RopeVector g_rope_strand_points[][16];

typedef struct {
    unsigned char pad_0[0x28];
    int groups[4];
    int count;
    int flags;
    unsigned char pad_40[0x44];
    float cycle;
    float cycleRate;
    unsigned char pad_8C[0x4];
    float jitterScale;
    float phaseA;
    float rate;
    unsigned char pad_9C[0x4];
    float amplitude;
    float swayScale;
    float phaseB;
    unsigned char pad_AC[0x28];
    float radius;
    unsigned char pad_D8[0x4];
    int pool;
    float center[4];
} RopeState;

extern float (*g_path_l03_entry_table[])[4];
extern RopeVector g_random_vector_table[];
extern float g_hero_position[];
extern float FastAddRotations(float, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float mat_fast_helper_a(float, float);


/* Updates the four rope strands: it copies or builds their points, then adds wobble and sway for drawing. */
void rope_update_strand_points(u8 *object)
{
    RopeVector toward, relative, blended, tangent, radial, jitter;
    RopeState *state = *(RopeState **)(object + 0x68);
    int row, column;
    float segmentLength, vertical, phase, angle, magnitude;

    state->phaseA = FastAddRotations(state->phaseA, state->rate);
    state->phaseB = FastAddRotations(state->phaseB, state->rate);
    state->cycle += state->cycleRate;
    if (state->cycle > 1.0f)
        state->cycle -= 1.0f;
    for (row = 0; row < 4; row++) {
        if ((state->flags & 1) && state->groups[row] >= 0) {
            RopeVector *source = (RopeVector *)g_path_l03_entry_table[state->groups[row]];
            int limit = state->count;
            for (column = 0; column < limit; column++)
                qcopy_nc(&g_rope_strand_points[state->pool + row][column], &source[column + 1]);
            if (state->flags & 8) {
                float distance, strength;
                FastVecSub(&toward, g_hero_position, state->center);
                distance = FastVecLength(&toward);
                vec_scale_to_length(&toward, &toward, 1.1f);
                if (!(distance > state->radius + 1.1f)) {
                    strength = 1.0f - (distance - 1.1f) / state->radius;
                    for (column = 0; column < state->count; column++) {
                        float length, amount;
                        qcopy(&relative, &g_rope_strand_points[state->pool + row][column]);
                        FastVecSub(&relative, &relative, state->center);
                        length = FastVecLength(&relative);
                        if (length > 1.1f)
                            length = 1.1f;
                        length *= 0.9090909f;
                        amount = strength * (1.0f - length);
                        FastVecScale(&blended, &toward, amount);
                        FastVecScale(&relative, &relative, 1.0f - amount);
                        FastVecAdd(&blended, &blended, &relative);
                        FastVecAdd(&g_rope_strand_points[state->pool + row][column], &blended, state->center);
                    }
                }
            }
        } else {
            tangent.quad = 0;
            tangent.f[3] = 1.0f;
            switch (row) {
            case 0:
                tangent.f[2] += 1.1f;
                break;
            case 1:
                tangent.f[2] -= 0.6395348906517029f;
                tangent.f[1] -= 0.6395348906517029f;
                tangent.f[0] -= 0.6395348906517029f;
                break;
            case 2:
                tangent.f[2] -= 0.6395348906517029f;
                tangent.f[1] -= 0.6395348906517029f;
                tangent.f[0] += 0.6395348906517029f;
                break;
            default:
                tangent.f[2] -= 0.6395348906517029f;
                tangent.f[1] += 0.785714328289032f;
                break;
            }
            for (column = 0; column < state->count; column++) {
                vec_scale_to_length(&radial, &tangent, (float)column / ((float)state->count - 0.5f));
                qcopy_nc(&g_rope_strand_points[state->pool + row][column], &radial);
                FastVecAdd(&g_rope_strand_points[state->pool + row][column], &g_rope_strand_points[state->pool + row][column], state->center);
            }
        }
    }
    FastVecSub(&tangent, &(*(RopeVector *)((unsigned int)g_rope_strand_points + ((state->pool) * 256 + (1) * 16))),
                             &(*(RopeVector *)((unsigned int)g_rope_strand_points + ((state->pool) * 256 + (0) * 16))));
    segmentLength = FastVecLength(&tangent);
    for (column = 0; column < state->count; column++) {
        vertical = 0.0f;
        phase = 0.0f;
        if (!(state->flags & 0x40))
            FastVecScale(&jitter, &g_random_vector_table[column], state->jitterScale * segmentLength);
        if (!(state->flags & 0x80)) {
            float firstPhase = math_wrap_angle_to_pi(state->phaseA + (float)column * -1.780236005783081f);
            float first = state->amplitude * math_fast_sin_or_cos_b(firstPhase);
            phase = math_wrap_angle_to_pi(state->phaseB + (float)column * -1.5184365510940552f);
            vertical = segmentLength * (first * math_fast_sin_or_cos_b(phase));
        }
        if (!(state->flags & 0x100)) {
            angle = FastAddRotations(mat_fast_helper_a(tangent.f[0], tangent.f[1]), 1.5707964897155762f);
            magnitude = segmentLength * state->swayScale * math_fast_sin_or_cos_a(phase);
            radial.f[0] = math_fast_sin_or_cos_a(angle) * magnitude;
            radial.f[1] = math_fast_sin_or_cos_b(angle) * magnitude;
            radial.f[2] = 0.0f;
        }
        for (row = 0; row < 4; row++) {
            qcopy_nc(&g_rope_strand_points[state->pool + row + 4][column], &g_rope_strand_points[state->pool + row][column]);
            if (column != 0 && column != state->count - 1) {
                if (!(state->flags & 0x40)) {
                    FastVecAdd(&g_rope_strand_points[state->pool + row + 4][column], &g_rope_strand_points[state->pool + row + 4][column], &jitter);
                    FastVecAdd(&g_rope_strand_points[state->pool + row][column], &g_rope_strand_points[state->pool + row][column], &jitter);
                }
                if (!(state->flags & 0x80))
                    g_rope_strand_points[state->pool + row + 4][column].f[2] += vertical;
                if (!(state->flags & 0x100))
                    FastVecAdd(&g_rope_strand_points[state->pool + row + 4][column], &g_rope_strand_points[state->pool + row + 4][column], &radial);
            }
        }
    }
}
