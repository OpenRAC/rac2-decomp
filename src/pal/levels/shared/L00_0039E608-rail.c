#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { float heading, pitch; int unused; float speed; } RailAngles;
extern char *g_launch_path_table[];
typedef struct { int paths[20]; float velocity[4]; float speed, radius; int initialized, pad6C, count; } RailState;
typedef struct {
    char pad00[0x80]; float point[4]; char pad90[0x70]; float velocity[4];
    char pad110[0xA8]; int advanceState; char pad1BC[0x44]; short timer;
    char pad202[0x93E]; RailAngles angles; char padB50[0x174C]; int state;
} RailHero;
extern RailHero g_hero_state;
extern float fast_vec_dist(void *, void *);
extern int find_nearest_path_point(void *, void *, void *, int *, float *, int, float, float, float);
extern int Spline_AdvanceByDistance(void *, void *, int *, float *, int, float);
extern void FastVecSub(void *, void *, void *);
extern float vec_length_xy(void *), mat_fast_helper_a(float, float), ApproachValue(float *, float, float), FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float), FastVecScale(void *, void *, float);
/* Precomputes path segment lengths and steers the hero along the nearest active path. */
typedef struct { float f[4]; } PV; typedef struct { char h[16]; PV p[1]; } PC;
void func_PAL_L00_003A1688(char *actor) {
    RailState *state = *(RailState **)(actor + 0x68);
    float previous[4], point[4], delta[4], step[4];
    int segment, bestSegment;
    float t, bestT;
    char *curve, *bestCurve;
    int i, j, path;
    float distance, bestDistance, advance, length;
    if (!state || state->paths[0] == -1 || state->count == 0) return;
    if (state->initialized == 0) {
        state->initialized = 1;
        for (path = 0; path < state->count; path++) {
            char *initCurve = g_launch_path_table[state->paths[path]];
            j = 0;
            if (j < *(int *)initCurve - 1) {
                float *lengths = (float *)(initCurve + 0x1C);
                char *next = initCurve + 0x20;
                char *current = initCurve + 0x10;
                do {
                    *lengths = fast_vec_dist(current, next);
                    j++;
                    next += 16;
                    lengths += 4;
                    current += 16;
                } while (j < *(int *)initCurve - 1);
            }
            ((PC *)initCurve)->p[j].f[3] = fast_vec_dist(initCurve + (j * 16 + 0x10), initCurve + 0x10);
        }
        *(u8 *)(actor + 0x30) = 0xFF;
    }
    if (g_hero_state.state != 16) return;
    bestCurve = 0;
    bestDistance = 9999.0f;
    for (i = 0; i < state->count; i++) {
        curve = g_launch_path_table[state->paths[i]];
        find_nearest_path_point(curve, g_hero_state.point, point, &segment, &t, 0, 999.0f, 5.0f, 0.0f);
        distance = fast_vec_dist(g_hero_state.point, point);
        if (distance < bestDistance) {
            bestCurve = curve;
            qcopy(previous, point);
            bestDistance = distance;
            bestSegment = segment;
            bestT = t;
        }
    }
    if (!bestCurve) return;
    advance = 3.7f - (float)g_hero_state.advanceState * 0.02f;
    if (advance < 0.7f) advance = 0.7f;
    {
        int result = Spline_AdvanceByDistance(bestCurve, point, &bestSegment, &bestT, 0, advance);
        if (state->radius < bestDistance) return;
        if (!result) {
            FastVecSub(step, point, previous);
            FastVecSub(delta, point, g_hero_state.point);
            g_hero_state.angles.pitch = mat_fast_helper_a(vec_length_xy(step), step[2]);
            g_hero_state.angles.heading = mat_fast_helper_a(delta[0], delta[1]);
            delta[2] = 0;
            ApproachValue(&g_hero_state.angles.speed, state->speed, 0.0052000005f);
            length = FastVecLength(delta);
            if (length > 0.001f) vec_scale_to_length(g_hero_state.velocity, delta, g_hero_state.angles.speed);
            g_hero_state.velocity[3] = 0;
            qcopy(state->velocity, g_hero_state.velocity);
            if (g_hero_state.timer < 25) g_hero_state.timer = 25;
        } else {
            FastVecScale(state->velocity, state->velocity, 0.98800004f);
            qcopy(g_hero_state.velocity, state->velocity);
            g_hero_state.velocity[3] = 0;
        }
    }
}
