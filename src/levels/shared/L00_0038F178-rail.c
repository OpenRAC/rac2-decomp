#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { float heading, pitch; int unused; float speed; } RailAngles;
extern char *D_L00_001FDA80[];
typedef struct { int paths[20]; float velocity[4]; float speed, radius; int initialized, pad6C, count; } RailState;
typedef struct {
    char pad00[0x80]; float point[4]; char pad90[0x70]; float velocity[4];
    char pad110[0xA8]; int advanceState; char pad1BC[0x44]; short timer;
    char pad202[0x93E]; RailAngles angles; char padB50[0x174C]; int state;
} RailHero;
extern RailHero D_00189E20;
extern float func_00282E48(void *, void *);
extern int func_L00_00341FA8(void *, void *, void *, int *, float *, int, float, float, float);
extern int func_L00_00341820(void *, void *, int *, float *, int, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E20(void *), func_00283248(float, float), func_002AA2E8(float *, float, float), func_00282DF0(void *);
extern void func_00282F20(void *, void *, float), func_00282D30(void *, void *, float);
/* Precomputes path segment lengths and steers the hero along the nearest active path. */
typedef struct { float f[4]; } PV; typedef struct { char h[16]; PV p[1]; } PC;
/* Measures the rail paths once, then pulls the hero along the nearest path while the hero is riding it. */
void func_L00_0039E158(char *actor) {
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
            char *initCurve = D_L00_001FDA80[state->paths[path]];
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
    if (gHeroState.state != 16) return;
    bestCurve = 0;
    bestDistance = 9999.0f;
    for (i = 0; i < state->count; i++) {
        curve = D_L00_001FDA80[state->paths[i]];
        find_nearest_path_point(curve, gHeroState.point, point, &segment, &t, 0, 999.0f, 5.0f, 0.0f);
        distance = fast_vec_dist(gHeroState.point, point);
        if (distance < bestDistance) {
            bestCurve = curve;
            qcopy(previous, point);
            bestDistance = distance;
            bestSegment = segment;
            bestT = t;
        }
    }
    if (!bestCurve) return;
    advance = 3.7f - (float)gHeroState.advanceState * 0.02f;
    if (advance < 0.7f) advance = 0.7f;
    {
        int result = Spline_AdvanceByDistance(bestCurve, point, &bestSegment, &bestT, 0, advance);
        if (state->radius < bestDistance) return;
        if (!result) {
            FastVecSub(step, point, previous);
            FastVecSub(delta, point, gHeroState.point);
            gHeroState.angles.pitch = FastMatrixHelperA(vec_length_xy(step), step[2]);
            gHeroState.angles.heading = FastMatrixHelperA(delta[0], delta[1]);
            delta[2] = 0;
            ApproachValue(&gHeroState.angles.speed, state->speed, 0.0036111111f);
            length = FastVecLength(delta);
            if (length > 0.001f) vec_scale_to_length(gHeroState.velocity, delta, gHeroState.angles.speed);
            gHeroState.velocity[3] = 0;
            qcopy(state->velocity, gHeroState.velocity);
            if (gHeroState.timer < 30) gHeroState.timer = 30;
        } else {
            FastVecScale(state->velocity, state->velocity, 0.99f);
            qcopy(gHeroState.velocity, state->velocity);
            gHeroState.velocity[3] = 0;
        }
    }
}
