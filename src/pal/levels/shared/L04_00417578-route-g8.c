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
    f32 unk_1C;
} Route;

typedef struct {
    u8 pad000[0x14];
    s32 unk_14;
    u8 pad018[0x1A0 - 0x18];
    s32 unk_1A0;
    s32 object_index;
    u8 pad1A8[0x314 - 0x1A8];
    s32 unk_314;
    s32 anim_frame;
    u8 pad31C[0x654 - 0x31C];
    s32 path_point;
    f32 path_offset;
    s32 path_timer;
    u8 pad660[0x6A0 - 0x660];
    f32 pos[4];
    u8 pad6B0[0x6D0 - 0x6B0];
    Route *route;
    s32 unk_6D4;
    f32 route_speed;
    u8 pad6DC[0x6E0 - 0x6DC];
    s32 home_route;
    s32 links[5];
    s32 alt_links[4];
    s32 unk_708;
    s32 unk_70C;
    s32 switch_timer;
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
void update_linked_route_selection_pal(RouteObject *object)
{
    f32 delta[4] __attribute__((aligned(16)));
    RouteState *state = object->state;
    Route *route;
    s32 allowed = 1, i;
    f32 amount;

    if (state->home_route == -1)
        return;

    if (g_current_map_index == 11) {
        if (state->route == g_route_path_table[state->home_route] && state->anim_frame >= 186 &&
            state->anim_frame < 205 && state->unk_70C >= 5) {
            state->route = g_route_path_table[state->unk_708];
            state->path_point = 0;
            state->path_offset = 0;
            state->route_speed = 4.0f;
            anim_sample_key_track(4.0f, state->route->unk_1C, state->route, &state->path_point, &state->unk_6D4, state->pos);
            state->path_timer = -1000;
        }
        if (!state->switching && state->unk_314 == -1 && state->anim_frame >= 44 && state->anim_frame < 51) {
            if (((RouteObject *)(ref_L04_00412EC0_00 + (state->object_index << 8)))->state->unk_14 == 0) {
                state->route = g_route_path_table[state->links[1]];
                amount = IntToFloat(FindNearestRoutePointIndex(object, state->route, 0)) * state->route->unk_1C;
                state->route_speed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
                anim_sample_key_track(state->route_speed, state->route->unk_1C, state->route, &state->path_point, &state->unk_6D4, state->pos);
                state->path_offset += math_random_float_range(-0.25f, 0.25f);
                if (state->path_offset > 1.5f)
                    state->path_offset = 1.5f;
                if (state->path_offset < -1.5f)
                    state->path_offset = -1.5f;
                state->path_timer = FloatToInt((math_random_float_range(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
                state->switching = 1;
                state->switch_timer = 150;
            } else {
                state->switching = 1;
                state->switch_timer = 150;
            }
            allowed = 0;
        }
    }

    if (g_current_map_index == 4) {
        if (state->route == g_route_path_table[state->home_route] && state->anim_frame >= 426 &&
            state->anim_frame < 432 && state->unk_70C >= 6 && IsPointInCuboid(object->pos, state->unk_1A0)) {
            state->route = g_route_path_table[state->unk_708];
            state->path_point = 0;
            state->path_offset = 0;
            state->route_speed = 2.0f;
            anim_sample_key_track(2.0f, state->route->unk_1C, state->route, &state->path_point, &state->unk_6D4, state->pos);
            state->path_timer = -1000;
        }
        if (state->route == g_route_path_table[state->alt_links[0]] && state->anim_frame >= 171 &&
            state->anim_frame < 175 && state->unk_70C >= 4) {
            state->route = g_route_path_table[state->home_route];
            amount = IntToFloat(FindNearestRoutePointIndex(object, state->route, 0)) * state->route->unk_1C;
            state->route_speed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
            anim_sample_key_track(state->route_speed, state->route->unk_1C, state->route, &state->path_point, &state->unk_6D4, state->pos);
        }
    }

    if (math_fast_float_d(&state->switch_timer) && !state->switching && allowed &&
        state->route == g_route_path_table[state->home_route]) {
        for (i = 0; i < 5; i++) {
            if (state->links[i] != -1) {
                route = g_route_path_table[state->links[i]];
                FastVecSub(delta, route->point0, state->pos);
                if (func_L00_002EE290(delta) < 25.0f) {
                    if (math_random_int_below(2) == 0)
                        state->route = route;
                    else
                        state->switch_timer = 100;
                }
            }
        }
        if (g_race_challenge_table[ref_L04_00412EC0_02].flags & 4) {
            for (i = 0; i < 4; i++) {
                if (state->alt_links[i] != -1) {
                    Route *alt_route = g_route_path_table[state->alt_links[i]];
                    FastVecSub(delta, alt_route->point0, state->pos);
                    if (func_L00_002EE290(delta) < 25.0f) {
                        if (math_random_int_below(2) == 0)
                            state->route = alt_route;
                        else
                            state->switch_timer = 100;
                    }
                }
            }
        }
        if (state->route != g_route_path_table[state->home_route]) {
            amount = IntToFloat(FindNearestRoutePointIndex(object, state->route, 0)) * state->route->unk_1C;
            state->route_speed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
            anim_sample_key_track(state->route_speed, state->route->unk_1C, state->route, &state->path_point, &state->unk_6D4, state->pos);
            state->path_offset += math_random_float_range(-0.25f, 0.25f);
            if (state->path_offset > 1.5f)
                state->path_offset = 1.5f;
            if (state->path_offset < -1.5f)
                state->path_offset = -1.5f;
            state->path_timer = FloatToInt((math_random_float_range(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
        }
    } else if (state->route != g_route_path_table[state->home_route] && state->path_point == state->route->count - 1) {
        state->route = g_route_path_table[state->home_route];
        amount = IntToFloat(FindNearestRoutePointIndex(object, state->route, 0)) * state->route->unk_1C;
        state->route_speed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
        anim_sample_key_track(state->route_speed, state->route->unk_1C, state->route, &state->path_point, &state->unk_6D4, state->pos);
        state->path_offset += math_random_float_range(-0.25f, 0.25f);
        if (state->path_offset > 1.5f)
            state->path_offset = 1.5f;
        if (state->path_offset < -1.5f)
            state->path_offset = -1.5f;
        state->path_timer = FloatToInt((math_random_float_range(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
    }

    if (state->switch_timer <= 0)
        state->switching = 0;
}
