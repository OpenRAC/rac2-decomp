#include "names.h"
/* func_PAL_L04_00407168, the PAL copy of func_L04_00402D90: the same C, where the sway timer of 60 frames
   per unit becomes (x * 300 + 2) / 6 and the branch cooldowns 180 and 120 become 150 and 100.
   In a unit of its own: it needs -frac2-gcse-unsplit-edges (config/cflags.txt), so gcse leaves the
   reload of the main route index at the label of the rejoin test. */

#include "common.h"

extern u8 *g_route_path_table[];
extern struct { s32 pad; s32 flags; u8 rest[56]; } g_race_challenge_table[];
extern int g_current_race_index MACRO_ADDR;
extern u8 *g_moby_l04_pool MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern char ref_L04_00402D90_00[];     /* an absolute symbol: 4 in level 04 */
extern int vec_fast_helper_a(u8 *);
extern void FastVecSub(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern int IsPointInCuboid(void *, int);
extern void anim_sample_key_track(float, float, void *, void *, void *, void *);
extern int FindNearestRoutePointIndex(void *, void *, int);

#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define P(p, o) (*(u8 **)((p) + (o)))

/* Starts the route at index slot from its first point at the given speed. */
#define START_ROUTE(slot, speed)                                                            \
    {                                                                                      \
        u8 *route_ = D_L04_001FE340[I(s, slot)];                                            \
                                                                                            \
        I(s, 0x114) = 0;                                                                    \
        P(s, 0x110) = route_;                                                               \
        F(s, 0x16C) = 0.0f;                                                                 \
        F(s, 0xA8) = speed;                                                                 \
        func_002C96F8(speed, F(route_, 0x1C), route_, s + 0x114, s + 0x118, s + 0xF0);      \
        I(s, 0x174) = -1000;                                                                \
    }

/* Joins the current route at the point nearest the object, a little ahead of it. */
#define JOIN_ROUTE(route)                                                                   \
    {                                                                                      \
        float base_ = func_00283CE0(func_L04_00400AB0(self, route, 0)) * F(P(s, 0x110), 0x1C); \
        float ahead_;                                                                       \
                                                                                            \
        if (I(s, 0x244) != 0) {                                                             \
            ahead_ = base_ + 15.0f;                                                         \
        } else {                                                                            \
            ahead_ = base_ + 5.0f;                                                          \
        }                                                                                   \
        F(s, 0xA8) = ahead_;                                                                \
        func_002C96F8(ahead_, F(P(s, 0x110), 0x1C), P(s, 0x110), s + 0x114, s + 0x118,    \
                      s + 0xF0);                                                            \
    }

/* Picks a new sideways wobble and the time until the next one. */
#define SWAY()                                                                              \
    {                                                                                      \
        F(s, 0x16C) += func_002A7878(-0.25f, 0.25f);                                        \
        if (F(s, 0x16C) > 1.5f) {                                                           \
            F(s, 0x16C) = 1.5f;                                                             \
        }                                                                                   \
        if (F(s, 0x16C) < -1.5f) {                                                          \
            F(s, 0x16C) = -1.5f;                                                            \
        }                                                                                   \
    }
#define NEXT_SWAY() (I(s, 0x174) = func_00283CF0((func_002A7878(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f))
#define WOBBLE() { SWAY(); NEXT_SWAY(); }

/* A racer's route choice in Barlow and Joba: takes the shortcuts at the scripted points,
   turns onto a nearby branch route at random, and rejoins its main route at the end of a
   branch. */
void func_PAL_L04_00407168(u8 *self)
{
    float delta[4];
    u8 *s;
    u8 *p;
    int i; /* 1 while a branch route may still be picked this frame, then the branch index */

    s = P(self, 0x68);
    i = 1;
    p = P(P(s, 0x164), 0x68);

    if (I(s, 0x54) == -1) {
        return;
    }
    if (g_current_map_index == 11) {
        if (P(s, 0x110) == g_route_path_table[I(s, 0x54)] && I(s, 0x124) >= 0xBA && I(s, 0x124) < 0xCD
            && I(s, 0x1AC) >= 5) {
            START_ROUTE(0x7C, 4.0f);
        }
        if (I(s, 0x240) == 0 && I(s, 0x120) == -1 && I(s, 0x124) >= 0x2C && I(s, 0x124) < 0x33) {
            u8 *rival = P(g_moby_l04_pool + (I(p, 0x1A4) << 8), 0x68);

            if (I(rival, 0x14) == 0) {
                if (math_random_float_range(0.0f, 1.0f) < 0.9f - (float)(10 - I(s, 0x1A8)) * 0.03f) {
                    u8 *route = g_route_path_table[I(s, 0x5C)];

                    P(s, 0x110) = route;
                    JOIN_ROUTE(route);
                    SWAY();
                    i = 0;
                    NEXT_SWAY();
                    I(s, 0x240) = 1;
                    s[0xA1] = 150;
                } else {
                    i = 0;
                }
            } else {
                if (math_random_float_range(0.0f, 1.0f) < 0.9f) {
                    I(s, 0x240) = 1;
                    s[0xA1] = 150;
                }
                i = 0;
            }
        }
    }
    if ((int)ref_L04_00402D90_00 == 40 || g_current_map_index == 4) {
        if (P(s, 0x110) == g_route_path_table[I(s, 0x54)] && I(s, 0x124) >= 0x1AA && I(s, 0x124) < 0x1B3
            && I(s, 0x1AC) >= 2 && IsPointInCuboid(self + 0x10, I(p, 0x1A0)) != 0) {
            START_ROUTE(0x7C, 2.0f);
        }
        if (P(s, 0x110) == g_route_path_table[I(s, 0x6C)] && I(s, 0x124) >= 0xAB && I(s, 0x124) < 0xAF
            && I(s, 0x1AC) >= 4) {
            u8 *route = g_route_path_table[I(s, 0x54)];

            P(s, 0x110) = route;
            JOIN_ROUTE(route);
        }
    }
    if (vec_fast_helper_a(s + 0xA1) != 0 && I(s, 0x240) == 0 && P(s, 0x110) == g_route_path_table[I(s, 0x54)]
        && i) {
        for (i = 0; i < 5; i++) {
            int id = ((int *)(s + 0x58))[i];

            if (id != -1) {
                u8 *branch = g_route_path_table[id];

                FastVecSub(delta, branch + 0x10, s + 0xF0);
                if (func_L00_002EE290(delta) < 25.0f) {
                    if (math_random_int_below(2) == 0) {
                        P(s, 0x110) = branch;
                    } else {
                        s[0xA1] = 100;
                    }
                }
            }
        }
        if (g_race_challenge_table[g_current_race_index].flags & 4) {
            for (i = 0; i < 4; i++) {
                int id = ((int *)(s + 0x6C))[i];

                if (id != -1) {
                    u8 *branch = g_route_path_table[id];

                    FastVecSub(delta, branch + 0x10, s + 0xF0);
                    if (func_L00_002EE290(delta) < 25.0f) {
                        if (math_random_int_below(2) == 0) {
                            P(s, 0x110) = branch;
                        } else {
                            s[0xA1] = 100;
                        }
                    }
                }
            }
        }
        if (P(s, 0x110) != g_route_path_table[I(s, 0x54)]) {
            JOIN_ROUTE(P(s, 0x110));
            WOBBLE();
        }
    } else if (P(s, 0x110) != g_route_path_table[I(s, 0x54)] && I(s, 0x114) == I(P(s, 0x110), 0) - 1) {
        u8 *route = g_route_path_table[I(s, 0x54)];

        P(s, 0x110) = route;
        JOIN_ROUTE(route);
        WOBBLE();
    }
    if (s[0xA1] == 0) {
        I(s, 0x240) = 0;
    }
}
