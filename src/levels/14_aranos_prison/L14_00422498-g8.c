#include "common.h"

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vector;

/* One bolt's row of the level's vertex table (640 bytes): the jittered points
 * along the path, then the same points displaced by the wave. */
typedef struct { Vector core[20]; Vector wave[20]; } BoltBuffer;

/* An entry of the level's path table: a point count, then the points. */
typedef struct { int count; int pad[3]; Vector points[1]; } Path;

/* The bolt's state record (object + 0x68). */
typedef struct {
    Vector start;   /* 0x00 */
    Vector end;     /* 0x10 */
    char pad20[12];
    int count;      /* 0x2C */
    int pad30;
    int path;       /* 0x34: index into the level's path table */
    int row;        /* 0x38: this bolt's row of the vertex table */
} BoltState;

extern int g_ribbon_l14_segment_count __attribute__((sda));
extern Path *g_effect_path_table[];
extern BoltBuffer g_ribbon_buffers[];
extern float g_lightning_length __attribute__((sda));
extern float g_lightning_random_angle __attribute__((sda));
extern float g_lightning_l14_horizontal_phase __attribute__((sda));
extern float g_lightning_horizontal_spacing __attribute__((sda));
extern float g_lightning_vertical_amp __attribute__((sda));
extern float g_lightning_horizontal_amp __attribute__((sda));
extern float g_lightning_vertical_phase __attribute__((sda));
extern float g_lightning_vertical_speed __attribute__((sda));
extern float g_lightning_vertical_spacing __attribute__((sda));
extern float g_lightning_l14_noise_min __attribute__((sda));
extern float g_lightning_l14_noise_max __attribute__((sda));
extern char g_identity_l14_matrix[] __attribute__((sda));
typedef struct { char pad[0x18]; void *owner; } Controller;
extern Controller g_projectile_l14_collision;
typedef struct { char pad0[0x5B0]; float f5B0; char pad5B4[4]; float f5B8; char pad5BC[0x2290 - 0x5BC]; void *moby; } Hero;
extern Hero g_hero_state;
extern float math_random_angle(void);
extern float FastAddRotations(float, float);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float math_random_signed_float_range(float, float);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float mat_fast_helper_a(float, float);
extern void make_hit_descriptor(void *, void *, int, float, void *);
extern int CollLine(void *, void *, int, void *, void *);

/* Rebuilds a lightning bolt along its path: each point gets a random jitter
 * (core), a copy of it is displaced by a travelling wave (wave), and every
 * second segment spawns a spark effect. */
void part_rebuild_lightning_bolt(char *object)
{
    Vector position;
    Vector direction;
    Vector delta;
    Vector step;
    Vector perpendicular;
    char effect[48] __attribute__((aligned(16)));
    BoltState *state;
    Path *path;
    Vector *wave, *prev;
    float phase, angle, amplitude, horizontalAmplitude, nx, nz, ny, f;
    float scale = g_lightning_length / (float)g_ribbon_l14_segment_count;
    int i;

    state = *(BoltState **)(object + 0x68);
    g_lightning_random_angle = math_random_angle();
    g_lightning_l14_horizontal_phase = math_random_angle();
    g_lightning_vertical_phase = FastAddRotations(g_lightning_vertical_phase, g_lightning_vertical_speed);
    vec_clear_128(&position);
    state->count = g_ribbon_l14_segment_count;
    FastVecSub(&direction, &state->end, &state->start);
    vec_scale_to_length(&direction, &direction, 1.0f);
    FastVecScale(&step, &direction, scale);
    path = g_effect_path_table[state->path];
    qcopy_nc(&g_ribbon_buffers[state->row].core[0], &path->points[0]);
    qcopy_nc(&g_ribbon_buffers[state->row].wave[0], &path->points[0]);
    for (i = 1; i < g_ribbon_l14_segment_count; i++) {
        nz = math_random_signed_float_range(g_lightning_l14_noise_min, g_lightning_l14_noise_max);
        nx = math_random_signed_float_range(g_lightning_l14_noise_min, g_lightning_l14_noise_max);
        ny = math_random_signed_float_range(g_lightning_l14_noise_min, g_lightning_l14_noise_max);
        qcopy_nc(&g_ribbon_buffers[state->row].core[i], &path->points[i]);
        f = (float)i;
        g_ribbon_buffers[state->row].core[i].z += nz;
        g_ribbon_buffers[state->row].core[i].x += nx;
        g_ribbon_buffers[state->row].core[i].y += ny;
        /* Previous point: the row's points from index -1. */
        prev = &g_ribbon_buffers[state->row].core[-1];
        FastVecSub(&delta, &g_ribbon_buffers[state->row].core[i], &prev[i]);
        phase = math_wrap_angle_to_pi(g_lightning_l14_horizontal_phase + f * g_lightning_horizontal_spacing);
        angle = math_wrap_angle_to_pi(g_lightning_vertical_phase + f * g_lightning_vertical_spacing);
        amplitude = g_lightning_vertical_amp * math_fast_sin_or_cos_b(angle);
        /* Column i of the wave points, then this bolt's row. */
        qcopy_nc(&g_ribbon_buffers[0].wave[i] + state->row * 40,
                 &g_ribbon_buffers[state->row].core[i]);
        nz = amplitude * math_fast_sin_or_cos_b(phase) + math_random_signed_float_range(0.0f, 0.1f);
        g_ribbon_buffers[state->row].wave[i].z += nz;
        angle = FastAddRotations(mat_fast_helper_a(delta.x, delta.y), 1.5707964897155762f);
        horizontalAmplitude = g_lightning_horizontal_amp * math_fast_sin_or_cos_a(phase);
        perpendicular.x = math_fast_sin_or_cos_a(angle) * horizontalAmplitude;
        perpendicular.y = math_fast_sin_or_cos_b(angle) * horizontalAmplitude;
        perpendicular.z = 0.0f;
        wave = g_ribbon_buffers[state->row].wave;
        FastVecAdd(&wave[i], &wave[i], &perpendicular);
        if (i > 1 && (i == g_ribbon_l14_segment_count - 1 || !(i & 1))) {
            make_hit_descriptor(effect, object, 1, 0.0f, g_identity_l14_matrix);
            *(unsigned short *)(effect + 26) = *(unsigned short *)(object + 0xaa);
            if (CollLine(&path->points[i - 2], &path->points[i], 17, object, effect)) {
                if (g_projectile_l14_collision.owner == g_hero_state.moby) {
                    g_hero_state.f5B0 = 0.0f;
                    g_hero_state.f5B8 = 0.0f;
                }
            }
        }
    }
}
