#include "common.h"

/* This body reads a small-data word through $gp. */

typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));

extern s32 D_001A79F0;
extern s32 ref_L04_00400D48_01 __attribute__((sda));
extern char ref_L04_00400D48_00[];
extern u8 *D_L04_001FE340[];
extern struct { s32 pad; s32 flags; u8 rest[56]; } D_L04_002C63C0[];
extern s32 ref_L04_00400D48_02(u8 *a0, u8 *a1, s32 a2);
extern f32 func_00283CE0(s32 value);
extern void L04_UpdatePath(float, float, u8 *, u8 *, u8 *, u8 *) __asm__("func_002C96F8");

void func_L04_00400D48(u8 *a0, u8 *a1, s32 a2)
{
    u8 *s1 = *(u8 **)(*(u8 **)(a1 + 0x164) + 0x68);
    s32 a3 = -1;
    f32 f;
    f32 t;
    f32 h;
    u8 *o;

    if ((s32)ref_L04_00400D48_00 == 0x28 || D_001A79F0 == 4) {
        if (*(s32 *)(s1 + 0x314) == -1) {
            *(u8 **)(a1 + 0x110) = D_L04_001FE340[*(s32 *)(a1 + 0x54)];
        } else if (D_L04_002C63C0[ref_L04_00400D48_01].flags & 4) {
            *(u8 **)(a1 + 0x110) = D_L04_001FE340[*(s32 *)(a1 + 0x6C)];
            if (*(s32 *)(a1 + 0x120) == 1 && *(s32 *)(a1 + 0x124) >= 3) {
                a3 = 0x82;
            }
        }
    }
    if (a3 == -1) {
        a3 = ref_L04_00400D48_02(a0, *(u8 **)(a1 + 0x110), 1);
    }
    if (a2 != 0) {
        *(Q16_B0e5d8f83 *)(a0 + 0x10) = *(Q16_B0e5d8f83 *)(*(u8 **)(a1 + 0x110) + a3 * 16 + 0x10);
    }
    t = IntToFloat(a3);
    t = t * *(f32 *)(*(u8 **)(a1 + 0x110) + 0x1C);
    if (*(s32 *)(a1 + 0x244) != 0) {
        f = t + 15.0f;
    } else {
        f = t + 5.0f;
    }
    *(f32 *)(a1 + 0xA8) = f;
    o = *(u8 **)(a1 + 0x110);
    h = *(f32 *)(o + 0x1C);
    L04_UpdatePath(f, h, o, a1 + 0x114, a1 + 0x118, a1 + 0xF0);
    *(s32 *)(a1 + 0x1C0) = 0;
    *(f32 *)(s1 + 0x63C) = 1.0f;
    *(s32 *)(s1 + 0x4C4) = 0;
}

/* A route of D_L04_001FE340: a point count, then the points. */
typedef struct {
    int count;                  /* 0x00 */
    u8 pad04[0x10 - 0x04];
    float points[1][4];         /* 0x10: count points */
} Route;

/* The moby, as far as func_L04_00400AB0 reads it. */
typedef struct {
    u8 pad00[0x10];
    float position[4];          /* 0x10 */
    u8 pad20[0x68 - 0x20];
    void *vars;                 /* 0x68 */
    u8 pad6C[0xAA - 0x6C];
    s16 oClass;                 /* 0xAA */
} Moby;

/* A racer's instance data: route indices in D_L04_001FE340, -1 when unused (a group of
   six, then one of four). */
typedef struct {
    u8 pad00[0x54];
    int routes[10];             /* 0x54 */
} RacerVars;

/* The same indices in the instance data of class 0xBBC. */
typedef struct {
    u8 pad000[0x6E0];
    int routes[10];             /* 0x6E0 */
} RacerVarsBBC;

extern void func_00282CF0(void *out, void *a, void *b);
extern float func_L00_002EE290(void *v);
extern char ref_L04_00400AB0_00[];     /* an absolute symbol: 4 in level 04 */

/* Returns the index of the point of path nearest to the moby: a coarse pass over every
   fifth point, then a pass over the ten points around the best one, wrapping at the ends.
   With clamp set, in Barlow (level 4) and Joba (level 11), an index inside certain
   stretches of the moby's routes is moved to the end of the stretch. */
int func_L04_00400AB0(Moby *moby, Route *path, int clamp)
{
    int best = 0;
    int i;
    int index;
    int count;
    int offset;
    float nearest = 99999.0f;
    float distance;
    float delta[4];

    for (i = 0; i < path->count; i += 5) {
        FastVecSub(delta, moby->position, path->points[i]);
        distance = func_L00_002EE290(delta);
        if (distance < nearest) {
            nearest = distance;
            best = i;
        }
    }

    count = path->count;
    for (offset = -5; offset < 5; offset++) {
        index = best + offset;
        if (index < 0)
            index += count;
        else if (index >= count)
            index -= count;
        FastVecSub(delta, moby->position, path->points[index]);
        distance = func_L00_002EE290(delta);
        if (distance < nearest) {
            best = index;
            nearest = distance;
        }
    }

    if (clamp) {
        if ((int)ref_L04_00400AB0_00 == 40 || D_001A79F0 == 4) {
            Route *route6;

            if (moby->oClass == 0xBBC) {
                RacerVarsBBC *vars = moby->vars;
                route6 = (Route *)D_L04_001FE340[vars->routes[6]];
            } else {
                RacerVars *vars = moby->vars;
                route6 = (Route *)D_L04_001FE340[vars->routes[6]];
            }
            if (path == route6 && best >= 105 && best < 124)
                best = 124;
        } else if (D_001A79F0 == 11) {
            Route *route0;
            Route *route7;
            Route *route2;

            if (moby->oClass == 0xBBC) {
                RacerVarsBBC *vars = moby->vars;
                route7 = (Route *)D_L04_001FE340[vars->routes[7]];
                route0 = (Route *)D_L04_001FE340[vars->routes[0]];
                route2 = (Route *)D_L04_001FE340[vars->routes[2]];
            } else {
                RacerVars *vars = moby->vars;
                route7 = (Route *)D_L04_001FE340[vars->routes[7]];
                route0 = (Route *)D_L04_001FE340[vars->routes[0]];
                route2 = (Route *)D_L04_001FE340[vars->routes[2]];
            }
            if (path == route7) {
                if (best >= 12 && best < 22)
                    best = 22;
                else if (best >= 59 && best < 71)
                    best = 71;
            } else if (path == route0) {
                if (best >= 183 && best < 203)
                    best = 203;
                else if (best >= 55 && best < 62)
                    best = 62;
            } else if (path == route2) {
                if (best >= 4 && best < 9)
                    best = 9;
            }
        }
    }
    return best;
}
