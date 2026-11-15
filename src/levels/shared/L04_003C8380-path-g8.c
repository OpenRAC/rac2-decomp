#include "common.h"

/* This body reads a small-data word through $gp. */

typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));

extern s32 g_current_map_index;
extern s32 ref_L04_00400D48_01 __attribute__((sda));
extern char ref_L04_00400D48_00[];
extern u8 *g_route_path_table[];
extern struct { s32 pad; s32 flags; u8 rest[56]; } g_race_challenge_table[];
extern s32 ref_L04_00400D48_02(u8 *a0, u8 *a1, s32 a2);
extern f32 IntToFloat(s32 value);
extern void L04_UpdatePath(float, float, u8 *, u8 *, u8 *, u8 *) __asm__("func_002C96F8");

/* Picks a route and the nearest point on it for a racing hoverbike, then points its steering at that spot. */
void hoverbike_select_route_point(u8 *racer, u8 *bike, s32 snapToPoint)
{
    u8 *riderVars = *(u8 **)(*(u8 **)(bike + 0x164) + 0x68);
    s32 pointIndex = -1;
    f32 targetDist;
    f32 pointDist;
    f32 routeLength;
    u8 *route;

    if ((s32)ref_L04_00400D48_00 == 0x28 || g_current_map_index == 4) {
        if (*(s32 *)(riderVars + 0x314) == -1) {
            *(u8 **)(bike + 0x110) = g_route_path_table[*(s32 *)(bike + 0x54)];
        } else if (g_race_challenge_table[ref_L04_00400D48_01].flags & 4) {
            *(u8 **)(bike + 0x110) = g_route_path_table[*(s32 *)(bike + 0x6C)];
            if (*(s32 *)(bike + 0x120) == 1 && *(s32 *)(bike + 0x124) >= 3) {
                pointIndex = 0x82;
            }
        }
    }
    if (pointIndex == -1) {
        pointIndex = ref_L04_00400D48_02(racer, *(u8 **)(bike + 0x110), 1);
    }
    if (snapToPoint != 0) {
        *(Q16_B0e5d8f83 *)(racer + 0x10) = *(Q16_B0e5d8f83 *)(*(u8 **)(bike + 0x110) + pointIndex * 16 + 0x10);
    }
    pointDist = IntToFloat(pointIndex);
    pointDist = pointDist * *(f32 *)(*(u8 **)(bike + 0x110) + 0x1C);
    if (*(s32 *)(bike + 0x244) != 0) {
        targetDist = pointDist + 15.0f;
    } else {
        targetDist = pointDist + 5.0f;
    }
    *(f32 *)(bike + 0xA8) = targetDist;
    route = *(u8 **)(bike + 0x110);
    routeLength = *(f32 *)(route + 0x1C);
    L04_UpdatePath(targetDist, routeLength, route, bike + 0x114, bike + 0x118, bike + 0xF0);
    *(s32 *)(bike + 0x1C0) = 0;
    *(f32 *)(riderVars + 0x63C) = 1.0f;
    *(s32 *)(riderVars + 0x4C4) = 0;
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

extern void FastVecSub(void *out, void *a, void *b);
extern float func_L00_002EE290(void *v);
extern char ref_L04_00400AB0_00[];     /* an absolute symbol: 4 in level 04 */

/* Returns the index of the point of path nearest to the moby: a coarse pass over every
   fifth point, then a pass over the ten points around the best one, wrapping at the ends.
   With clamp set, in Barlow (level 4) and Joba (level 11), an index inside certain
   stretches of the moby's routes is moved to the end of the stretch. */
int FindNearestRoutePointIndex(Moby *moby, Route *path, int clamp)
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
        if ((int)ref_L04_00400AB0_00 == 40 || g_current_map_index == 4) {
            Route *route6;

            if (moby->oClass == 0xBBC /* moby class 3004 */) {
                RacerVarsBBC *vars = moby->vars;
                route6 = (Route *)g_route_path_table[vars->routes[6]];
            } else {
                RacerVars *vars = moby->vars;
                route6 = (Route *)g_route_path_table[vars->routes[6]];
            }
            if (path == route6 && best >= 105 && best < 124)
                best = 124;
        } else if (g_current_map_index == 11) {
            Route *route0;
            Route *route7;
            Route *route2;

            if (moby->oClass == 0xBBC /* moby class 3004 */) {
                RacerVarsBBC *vars = moby->vars;
                route7 = (Route *)g_route_path_table[vars->routes[7]];
                route0 = (Route *)g_route_path_table[vars->routes[0]];
                route2 = (Route *)g_route_path_table[vars->routes[2]];
            } else {
                RacerVars *vars = moby->vars;
                route7 = (Route *)g_route_path_table[vars->routes[7]];
                route0 = (Route *)g_route_path_table[vars->routes[0]];
                route2 = (Route *)g_route_path_table[vars->routes[2]];
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
