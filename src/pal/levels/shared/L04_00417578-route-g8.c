#include "include_asm.h"

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

extern s32 D_001A79F0;
extern Route *D_L04_001FE340[];
/* Object table, 0x100 bytes per object. */
extern u8 *ref_L04_00412EC0_00 __attribute__((sda));
extern s32 ref_L04_00412EC0_01 __attribute__((sda));
extern s32 ref_L04_00412EC0_02 __attribute__((sda));
extern RouteFlags D_L04_002C63C0[];

/* The EE ABI assigns the float and integer argument banks independently. */
extern void func_002C96F8(f32, f32, void *, void *, void *, void *);
extern s32 func_L04_00400AB0(void *, void *, s32);
extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);
extern f32 func_002A7878(f32, f32);
extern s32 func_002ACBC8(void *, s32);
extern s32 func_002A77E0(s32);
extern s32 func_00282948(void *);
extern void func_00282CF0(void *, void *, void *);
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

    if (D_001A79F0 == 11) {
        if (state->route == D_L04_001FE340[state->homeRoute] && state->animFrame >= 186 &&
            state->animFrame < 205 && state->f70C >= 5) {
            state->route = D_L04_001FE340[state->f708];
            state->pathPoint = 0;
            state->pathOffset = 0;
            state->routeSpeed = 4.0f;
            func_002C96F8(4.0f, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
            state->pathTimer = -1000;
        }
        if (!state->switching && state->f314 == -1 && state->animFrame >= 44 && state->animFrame < 51) {
            if (((RouteObject *)(ref_L04_00412EC0_00 + (state->objectIndex << 8)))->state->f14 == 0) {
                state->route = D_L04_001FE340[state->links[1]];
                amount = func_00283CE0(func_L04_00400AB0(object, state->route, 0)) * state->route->f1C;
                state->routeSpeed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
                func_002C96F8(state->routeSpeed, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
                state->pathOffset += func_002A7878(-0.25f, 0.25f);
                if (state->pathOffset > 1.5f)
                    state->pathOffset = 1.5f;
                if (state->pathOffset < -1.5f)
                    state->pathOffset = -1.5f;
                state->pathTimer = func_00283CF0((func_002A7878(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
                state->switching = 1;
                state->switchTimer = 150;
            } else {
                state->switching = 1;
                state->switchTimer = 150;
            }
            allowed = 0;
        }
    }

    if (D_001A79F0 == 4) {
        if (state->route == D_L04_001FE340[state->homeRoute] && state->animFrame >= 426 &&
            state->animFrame < 432 && state->f70C >= 6 && func_002ACBC8(object->pos, state->f1A0)) {
            state->route = D_L04_001FE340[state->f708];
            state->pathPoint = 0;
            state->pathOffset = 0;
            state->routeSpeed = 2.0f;
            func_002C96F8(2.0f, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
            state->pathTimer = -1000;
        }
        if (state->route == D_L04_001FE340[state->altLinks[0]] && state->animFrame >= 171 &&
            state->animFrame < 175 && state->f70C >= 4) {
            state->route = D_L04_001FE340[state->homeRoute];
            amount = func_00283CE0(func_L04_00400AB0(object, state->route, 0)) * state->route->f1C;
            state->routeSpeed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
            func_002C96F8(state->routeSpeed, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
        }
    }

    if (func_00282948(&state->switchTimer) && !state->switching && allowed &&
        state->route == D_L04_001FE340[state->homeRoute]) {
        for (i = 0; i < 5; i++) {
            if (state->links[i] != -1) {
                route = D_L04_001FE340[state->links[i]];
                func_00282CF0(delta, route->point0, state->pos);
                if (func_L00_002EE290(delta) < 25.0f) {
                    if (func_002A77E0(2) == 0)
                        state->route = route;
                    else
                        state->switchTimer = 100;
                }
            }
        }
        if (D_L04_002C63C0[ref_L04_00412EC0_02].flags & 4) {
            for (i = 0; i < 4; i++) {
                if (state->altLinks[i] != -1) {
                    Route *altRoute = D_L04_001FE340[state->altLinks[i]];
                    func_00282CF0(delta, altRoute->point0, state->pos);
                    if (func_L00_002EE290(delta) < 25.0f) {
                        if (func_002A77E0(2) == 0)
                            state->route = altRoute;
                        else
                            state->switchTimer = 100;
                    }
                }
            }
        }
        if (state->route != D_L04_001FE340[state->homeRoute]) {
            amount = func_00283CE0(func_L04_00400AB0(object, state->route, 0)) * state->route->f1C;
            state->routeSpeed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
            func_002C96F8(state->routeSpeed, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
            state->pathOffset += func_002A7878(-0.25f, 0.25f);
            if (state->pathOffset > 1.5f)
                state->pathOffset = 1.5f;
            if (state->pathOffset < -1.5f)
                state->pathOffset = -1.5f;
            state->pathTimer = func_00283CF0((func_002A7878(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
        }
    } else if (state->route != D_L04_001FE340[state->homeRoute] && state->pathPoint == state->route->count - 1) {
        state->route = D_L04_001FE340[state->homeRoute];
        amount = func_00283CE0(func_L04_00400AB0(object, state->route, 0)) * state->route->f1C;
        state->routeSpeed = amount + (ref_L04_00412EC0_01 ? 20.0f : 5.0f);
        func_002C96F8(state->routeSpeed, state->route->f1C, state->route, &state->pathPoint, &state->f6D4, state->pos);
        state->pathOffset += func_002A7878(-0.25f, 0.25f);
        if (state->pathOffset > 1.5f)
            state->pathOffset = 1.5f;
        if (state->pathOffset < -1.5f)
            state->pathOffset = -1.5f;
        state->pathTimer = func_00283CF0((func_002A7878(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
    }

    if (state->switchTimer <= 0)
        state->switching = 0;
}
