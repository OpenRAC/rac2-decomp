/* func_L04_00402D90: near miss, 1948/1952 bytes, 0 of 2 places (USA v1.01, 1 November 2026).

   Profile: its own unit, `-O2 -G0 -ffunction-sections`.

   A racer's route choice in Barlow and Joba. Calls, constants, stores and the branch layout
   agree with retail, including the absolute link symbol compared with 40 (4 in level 04, 11
   in Joba, as ref_L04_00400AB0_00 in L04_003C8380-path-g8.c). Things that mattered: the three
   repeated sequences as macros with plain braces (a `do { } while (0)` puts loop notes, and a
   `.p2align 3` nop, after them); the join taking the route as an argument and its distance in a
   new variable; `fresh = 0` before the second random call; the inner if in the first branch
   loop written with the assignment first.
   What differs: retail keeps self in $s7, the rival record in $s2 and `fresh` in $s3 (here $s4,
   $s3, $s2; declaration and assignment orders do not move them), and on the !fresh path it
   reloads +0x54 before the end-of-branch test (4 bytes). */

#include "common.h"

extern u8 *D_L04_001FE340[];
extern struct { s32 pad; s32 flags; u8 rest[56]; } D_L04_002C63C0[];
extern int D_L04_001B090C MACRO_ADDR;
extern u8 *D_L04_001B24DC MACRO_ADDR;
extern int D_001A79F0 MACRO_ADDR;
extern char ref_L04_00402D90_00[];     /* an absolute symbol: 4 in level 04 */
extern int func_002829A8(u8 *);
extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern int func_002ACBC8(void *, int);
extern void func_002C96F8(float, float, void *, void *, void *, void *);
extern int func_L04_00400AB0(void *, void *, int);

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
#define NEXT_SWAY() (I(s, 0x174) = func_00283CF0(func_002A7878(3.0f, 6.0f) * 60.0f))
#define WOBBLE() { SWAY(); NEXT_SWAY(); }

/* A racer's route choice in Barlow and Joba: takes the shortcuts at the scripted points,
   turns onto a nearby branch route at random, and rejoins its main route at the end of a
   branch. */
void func_L04_00402D90(u8 *self)
{
    float delta[4];
    u8 *s;
    int k;
    u8 *p;
    int fresh;

    s = P(self, 0x68);
    fresh = 1;
    p = P(P(s, 0x164), 0x68);

    if (I(s, 0x54) == -1) {
        return;
    }
    if (D_001A79F0 == 11) {
        if (P(s, 0x110) == D_L04_001FE340[I(s, 0x54)] && I(s, 0x124) >= 0xBA && I(s, 0x124) < 0xCD
            && I(s, 0x1AC) >= 5) {
            START_ROUTE(0x7C, 4.0f);
        }
        if (I(s, 0x240) == 0 && I(s, 0x120) == -1 && I(s, 0x124) >= 0x2C && I(s, 0x124) < 0x33) {
            u8 *rival = P(D_L04_001B24DC + (I(p, 0x1A4) << 8), 0x68);

            if (I(rival, 0x14) == 0) {
                if (func_002A7878(0.0f, 1.0f) < 0.9f - (float)(10 - I(s, 0x1A8)) * 0.03f) {
                    u8 *route = D_L04_001FE340[I(s, 0x5C)];

                    P(s, 0x110) = route;
                    JOIN_ROUTE(route);
                    SWAY();
                    fresh = 0;
                    NEXT_SWAY();
                    I(s, 0x240) = 1;
                    s[0xA1] = 180;
                } else {
                    fresh = 0;
                }
            } else {
                if (func_002A7878(0.0f, 1.0f) < 0.9f) {
                    I(s, 0x240) = 1;
                    s[0xA1] = 180;
                }
                fresh = 0;
            }
        }
    }
    if ((int)ref_L04_00402D90_00 == 40 || D_001A79F0 == 4) {
        if (P(s, 0x110) == D_L04_001FE340[I(s, 0x54)] && I(s, 0x124) >= 0x1AA && I(s, 0x124) < 0x1B3
            && I(s, 0x1AC) >= 2 && func_002ACBC8(self + 0x10, I(p, 0x1A0)) != 0) {
            START_ROUTE(0x7C, 2.0f);
        }
        if (P(s, 0x110) == D_L04_001FE340[I(s, 0x6C)] && I(s, 0x124) >= 0xAB && I(s, 0x124) < 0xAF
            && I(s, 0x1AC) >= 4) {
            u8 *route = D_L04_001FE340[I(s, 0x54)];

            P(s, 0x110) = route;
            JOIN_ROUTE(route);
        }
    }
    if (func_002829A8(s + 0xA1) != 0 && I(s, 0x240) == 0 && P(s, 0x110) == D_L04_001FE340[I(s, 0x54)]) {
        if (fresh) {
            for (k = 0; k < 5; k++) {
                int id = ((int *)(s + 0x58))[k];

                if (id != -1) {
                    u8 *branch = D_L04_001FE340[id];

                    func_00282CF0(delta, branch + 0x10, s + 0xF0);
                    if (func_L00_002EE290(delta) < 25.0f) {
                        if (func_002A77E0(2) != 0) {
                            s[0xA1] = 120;
                        } else {
                            P(s, 0x110) = branch;
                        }
                    }
                }
            }
            if (D_L04_002C63C0[D_L04_001B090C].flags & 4) {
                for (k = 0; k < 4; k++) {
                    int id = ((int *)(s + 0x6C))[k];

                    if (id != -1) {
                        u8 *branch = D_L04_001FE340[id];

                        func_00282CF0(delta, branch + 0x10, s + 0xF0);
                        if (func_L00_002EE290(delta) < 25.0f) {
                            if (func_002A77E0(2) != 0) {
                                s[0xA1] = 120;
                            } else {
                                P(s, 0x110) = branch;
                            }
                        }
                    }
                }
            }
            if (P(s, 0x110) != D_L04_001FE340[I(s, 0x54)]) {
                JOIN_ROUTE(P(s, 0x110));
                WOBBLE();
            }
        }
    } else if (P(s, 0x110) != D_L04_001FE340[I(s, 0x54)] && I(s, 0x114) == I(P(s, 0x110), 0) - 1) {
        u8 *route = D_L04_001FE340[I(s, 0x54)];

        P(s, 0x110) = route;
        JOIN_ROUTE(route);
        WOBBLE();
    }
    if (s[0xA1] == 0) {
        I(s, 0x240) = 0;
    }
}
