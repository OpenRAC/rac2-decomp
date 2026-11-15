#include "include_asm.h"
#include "names.h"

/* func_PAL_L04_00417578, the PAL copy of func_L04_00412EC0: the same C, where the switch timers scale
 * from 180 and 120 to 150 and 100, and the route timer becomes (x * 300 + 2) / 6 in float. The second loop's
 * route is its own block-scoped local: one local across both loops outranks state in global allocation. */

typedef int s32;
typedef unsigned char u8;
typedef float f32;

typedef struct {
    s32 count;
    s32 pad04[3];
    f32 point0[3];
    f32 f1C;
} Route;

typedef struct {
    u8 pad000[0x14];
    s32 f14;
    u8 pad018[0x1A0 - 0x18];
    s32 f1A0;
    s32 objectIndex;
    u8 pad1A8[0x314 - 0x1A8];
    s32 f314;
    s32 animFrame;
    u8 pad31C[0x654 - 0x31C];
    s32 pathPoint;
    f32 pathOffset;
    s32 pathTimer;
    u8 pad660[0x6A0 - 0x660];
    f32 pos[4];
    u8 pad6B0[0x6D0 - 0x6B0];
    Route *route;
    s32 f6D4;
    f32 routeSpeed;
    u8 pad6DC[0x6E0 - 0x6DC];
    s32 homeRoute;
    s32 links[5];
    s32 altLinks[4];
    s32 f708;
    s32 f70C;
    s32 switchTimer;
    u8 pad714[4];
    s32 switching;
} RouteState;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 pad20[0x68 - 0x20];
    RouteState *state;
} RouteObject;

typedef struct {
    s32 value;
    s32 flags;
    u8 pad[0x38];
} RouteFlags;

extern s32 g_current_map_index;
extern Route *g_route_path_table[];
/* Object table, 0x100 bytes per object. */
extern u8 *ref_L04_00412EC0_00 __attribute__((sda));
extern s32 ref_L04_00412EC0_01 __attribute__((sda));
extern s32 ref_L04_00412EC0_02 __attribute__((sda));
extern RouteFlags g_race_challenge_table[];

/* The EE ABI assigns the float and integer argument banks independently. */
extern void anim_sample_key_track(f32, f32, void *, void *, void *, void *);
extern s32 FindNearestRoutePointIndex(void *, void *, s32);
extern f32 IntToFloat(s32);
extern s32 FloatToInt(f32);
extern f32 math_random_float_range(f32, f32);
extern s32 IsPointInCuboid(void *, s32);
extern s32 math_random_int_below(s32);
extern s32 math_fast_float_d(void *);
extern void FastVecSub(void *, void *, void *);
extern f32 func_L00_002EE290(void *);

/* Selects linked routes near the object and returns completed routes to the main route. */
void func_PAL_L04_00417578(RouteObject *object)
{
    f32 delta[4] __attribute__((aligned(16)));
    RouteState *state = object->state;
    Route *route;
    s32 allowed = 1, i;
    f32 amount;

    if (state->homeRoute == -1)
        return;

    if (g_current_map_index == 11) {
        if (state->route == g_route_path_table[state->homeRoute] && state->animFrame >= 186 &&
            state->animFrame < 205 && state->f70C >= 5) {
            state->route = g_route_path_table[state->f708];
            state->pathPoint = 0;
            state->pathOffset = 0;
            state->routeSpeed = 4.0f;
            anim_sample_key_track(4.0f, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
            state->pathTimer = -1000;
        }
        if (!state->switching && state->f314 == -1 && state->animFrame >= 44 && state->animFrame < 51) {
            if (((RouteObject *)(ref_L04_00412EC0_00 + (state->objectIndex << 8)))->state->f14 == 0) {
                state->route = g_route_path_table[state->links[1]];
                amount = IntToFloat(FindNearestRoutePointIndex(object, state->route, 0)) * state->route->f1C;
                state->routeSpeed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
                anim_sample_key_track(state->routeSpeed, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
                state->pathOffset += math_random_float_range(-0.25f, 0.25f);
                if (state->pathOffset > 1.5f)
                    state->pathOffset = 1.5f;
                if (state->pathOffset < -1.5f)
                    state->pathOffset = -1.5f;
                state->pathTimer = FloatToInt((math_random_float_range(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
                state->switching = 1;
                state->switchTimer = 150;
            } else {
                state->switching = 1;
                state->switchTimer = 150;
            }
            allowed = 0;
        }
    }

    if (g_current_map_index == 4) {
        if (state->route == g_route_path_table[state->homeRoute] && state->animFrame >= 426 &&
            state->animFrame < 432 && state->f70C >= 6 && IsPointInCuboid(object->pos, state->f1A0)) {
            state->route = g_route_path_table[state->f708];
            state->pathPoint = 0;
            state->pathOffset = 0;
            state->routeSpeed = 2.0f;
            anim_sample_key_track(2.0f, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
            state->pathTimer = -1000;
        }
        if (state->route == g_route_path_table[state->altLinks[0]] && state->animFrame >= 171 &&
            state->animFrame < 175 && state->f70C >= 4) {
            state->route = g_route_path_table[state->homeRoute];
            amount = IntToFloat(FindNearestRoutePointIndex(object, state->route, 0)) * state->route->f1C;
            state->routeSpeed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
            anim_sample_key_track(state->routeSpeed, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
        }
    }

    if (math_fast_float_d(&state->switchTimer) && !state->switching && allowed &&
        state->route == g_route_path_table[state->homeRoute]) {
        for (i = 0; i < 5; i++) {
            if (state->links[i] != -1) {
                route = g_route_path_table[state->links[i]];
                FastVecSub(delta, route->point0, state->pos);
                if (func_L00_002EE290(delta) < 25.0f) {
                    if (math_random_int_below(2) == 0)
                        state->route = route;
                    else
                        state->switchTimer = 100;
                }
            }
        }
        if (g_race_challenge_table[ref_L04_00412EC0_02].flags & 4) {
            for (i = 0; i < 4; i++) {
                if (state->altLinks[i] != -1) {
                    Route *altRoute = g_route_path_table[state->altLinks[i]];
                    FastVecSub(delta, altRoute->point0, state->pos);
                    if (func_L00_002EE290(delta) < 25.0f) {
                        if (math_random_int_below(2) == 0)
                            state->route = altRoute;
                        else
                            state->switchTimer = 100;
                    }
                }
            }
        }
        if (state->route != g_route_path_table[state->homeRoute]) {
            amount = IntToFloat(FindNearestRoutePointIndex(object, state->route, 0)) * state->route->f1C;
            state->routeSpeed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
            anim_sample_key_track(state->routeSpeed, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
            state->pathOffset += math_random_float_range(-0.25f, 0.25f);
            if (state->pathOffset > 1.5f)
                state->pathOffset = 1.5f;
            if (state->pathOffset < -1.5f)
                state->pathOffset = -1.5f;
            state->pathTimer = FloatToInt((math_random_float_range(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
        }
    } else if (state->route != g_route_path_table[state->homeRoute] && state->pathPoint == state->route->count - 1) {
        state->route = g_route_path_table[state->homeRoute];
        amount = IntToFloat(FindNearestRoutePointIndex(object, state->route, 0)) * state->route->f1C;
        state->routeSpeed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
        anim_sample_key_track(state->routeSpeed, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
        state->pathOffset += math_random_float_range(-0.25f, 0.25f);
        if (state->pathOffset > 1.5f)
            state->pathOffset = 1.5f;
        if (state->pathOffset < -1.5f)
            state->pathOffset = -1.5f;
        state->pathTimer = FloatToInt((math_random_float_range(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
    }

    if (state->switchTimer <= 0)
        state->switching = 0;
}
