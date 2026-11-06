/* func_PAL_L04_00407940, the PAL copy of func_L04_00403530: the same C for 50 Hz, with the per-frame speeds scaled by 6/5 and the frame counts by 5/6. */
#include "common.h"

/* Own unit: the branch to the padding nop after the 15.0f constant needs -frac2-hazard-labels. */

#define INT_AT(p, o) (*(int *)((p) + (o)))
#define SHORT_AT(p, o) (*(short *)((p) + (o)))
#define FLOAT_AT(p, o) (*(float *)((p) + (o)))
#define PTR_AT(p, o) (*(unsigned char **)((p) + (o)))

typedef unsigned int PathQuad __attribute__((mode(TI)));

extern int D_001A7B90 MACRO_ADDR;
extern int D_L04_001A8FE4 __attribute__((sda));

extern void func_PAL_L04_00407168(void *);
extern float func_00283CE0(int);
extern int func_00278E78(void);
extern float func_00282C48(float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern void func_002A7470(void *, int, int, int);
extern int func_L02_00348420(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_L04_00365300(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282E80(void *, void *);
extern void func_002C96F8(float, float, void *, void *, void *, void *);
extern float func_00283C80(float, float);
extern int func_L04_00400AB0(void *, void *, int);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CD8(void *, void *, void *);

/* Paces a route follower: derives its speed from the time left and from a peer at +0x164,
   steers its lateral offset (+0x16C) and advances its point on the route at +0x110. */
void func_PAL_L04_00407940(unsigned char *moby, unsigned char *vars)
{
    float toNext[4], toPeer[4], cross[4], tmp[4];
    unsigned char *peerVars;
    float speed, distance;
    int i, neighbor, next, oldIndex;

    if (INT_AT(vars, 0x180))
        INT_AT(vars, 0x180)--;
    if (SHORT_AT(vars, 0x17E))
        SHORT_AT(vars, 0x17E)--;
    {
        float extra = FLOAT_AT(vars, 0x2D0);

        if (D_001A7B90)
            speed = (FLOAT_AT(vars, 0x1B4) - FLOAT_AT(vars, 0x11C))
                    / ((FLOAT_AT(vars, 0x1B0) + extra) - (float)INT_AT(vars, 0x1B8) * 0.02f);
        else
            speed = (FLOAT_AT(vars, 0x1B4) - FLOAT_AT(vars, 0x11C))
                    / ((FLOAT_AT(vars, 0x1B0) + extra) - (float)INT_AT(vars, 0x1B8) * 0.016666668f);
    }
    FLOAT_AT(vars, 0x2D4) = speed;
    if (speed < 6.645f)
        FLOAT_AT(vars, 0x2D4) = 6.645f;
    if (INT_AT(vars, 0x1C0) > 0)
        return;

    func_PAL_L04_00407168(moby);

    if (speed < 0.0f
        || (speed >= 22.15f && INT_AT(vars, 0x160) >= 2
            && FLOAT_AT(vars, 0x11C) / FLOAT_AT(vars, 0x1B4) > 0.66f))
        speed = 22.15f;
    if (speed > 28.15f)
        speed = 28.15f;
    if (speed < 13.29f)
        speed = 13.29f;
    FLOAT_AT(vars, 0x134) = speed * 0.020000001f - func_00283CE0(vars[0xA2] - 1) * 0.014f;

    if (PTR_AT(vars, 0x164) && !vars[0xA5] && func_00278E78() != 5) {
        float delta;
        unsigned char *peer = PTR_AT(vars, 0x164);

        peerVars = PTR_AT(peer, 0x68);
        delta = FLOAT_AT(peerVars, 0x310) - FLOAT_AT(vars, 0x11C);
        /* Re-reading the peer's state here lets jump threading skip the identical test below. */
        if (FLOAT_AT(vars, 0x11C) + 12.0f < FLOAT_AT(peerVars, 0x310)
            && FLOAT_AT(vars, 0x11C) > FLOAT_AT(peerVars, 0x310) - 150.0f
            && D_L04_001A8FE4 >= INT_AT(vars, 0x160)
            && PTR_AT(peerVars, 0x730) != moby
            && PTR_AT(vars, 0x164)[0xBC] == 5)
            FLOAT_AT(vars, 0x134) += (delta - 12.0f) * 0.002f;
        if (PTR_AT(vars, 0x164)[0xBC] == 5 && !INT_AT(peerVars, 0x724) && delta > 1.0f && delta < 10.0f) {
            PTR_AT(peerVars, 0x734) = moby;
            INT_AT(peerVars, 0x720) = 1;
        }
        if (INT_AT(vars, 0x168) && vars[0xA2] != 1 && func_00282C48(delta) < 10.0f
            && INT_AT(vars, 0x160) >= D_L04_001A8FE4) {
            int closest;

            FLOAT_AT(vars, 0x134) += (delta * 0.020000001f) + (delta * 0.020000001f);
            if (FLOAT_AT(vars, 0x11C) > FLOAT_AT(peerVars, 0x310) && !INT_AT(vars, 0x180)
                && !SHORT_AT(vars, 0x17E) && PTR_AT(vars, 0x8C)) {
                float lead = FLOAT_AT(vars, 0x11C) - FLOAT_AT(peerVars, 0x310);

                if (lead < 10.0f && lead > 2.0f && !func_002A77E0(1)) {
                    unsigned char *target = PTR_AT(vars, 0x164);
                    float angle = func_00283BE0(FLOAT_AT(moby, 0xF8),
                                                func_00283248(FLOAT_AT(target, 0x10) - FLOAT_AT(moby, 0x10),
                                                              FLOAT_AT(target, 0x14) - FLOAT_AT(moby, 0x14)));

                    if (angle > 0.0f)
                        func_002A7470(PTR_AT(vars, 0x8C), 8, 0, 10);
                    else
                        func_002A7470(PTR_AT(vars, 0x8C), 7, 0, 10);
                    INT_AT(vars, 0x180) = (func_002A7820(120, 180) * 5 + 2) / 6;
                } else if (FLOAT_AT(vars, 0x11C) - FLOAT_AT(peerVars, 0x310) > -5.0f && !func_002A77E0(3)) {
                    unsigned char *target = PTR_AT(vars, 0x164);
                    float angle = func_00283BE0(FLOAT_AT(moby, 0xF8),
                                                func_00283248(FLOAT_AT(target, 0x10) - FLOAT_AT(moby, 0x10),
                                                              FLOAT_AT(target, 0x14) - FLOAT_AT(moby, 0x14)));

                    if (angle > 0.0f)
                        func_002A7470(PTR_AT(vars, 0x8C), 5, 0, 10);
                    else
                        func_002A7470(PTR_AT(vars, 0x8C), 6, 0, 10);
                    INT_AT(vars, 0x180) = (func_002A7820(120, 300) * 5 + 2) / 6;
                } else
                    INT_AT(vars, 0x180) = 50;
            }
            *(PathQuad *)toNext = *(PathQuad *)(PTR_AT(vars, 0x164) + 0x10);
            closest = func_L02_00348420(toNext, PTR_AT(vars, 0x110));
            if (closest == 0 || closest == INT_AT(PTR_AT(vars, 0x110), 0) - 1)
                FLOAT_AT(vars, 0x16C) = 0;
            else {
                float nextDist, prevDist;
                int prev;

                next = closest + 1;
                prev = closest - 1;
                nextDist = func_00282E48(PTR_AT(vars, 0x110) + 16 + next * 16, PTR_AT(vars, 0x164) + 16);
                prevDist = func_00282E48(PTR_AT(vars, 0x110) + 16 + prev * 16, PTR_AT(vars, 0x164) + 16);
                neighbor = prev;
                if (nextDist < prevDist)
                    neighbor = next;
                FLOAT_AT(vars, 0x16C) = func_L04_00365300(PTR_AT(vars, 0x110) + 16 + closest * 16,
                                                          PTR_AT(vars, 0x110) + 16 + neighbor * 16,
                                                          PTR_AT(vars, 0x164) + 16);
                func_00282CF0(tmp, PTR_AT(vars, 0x110) + 16 + next * 16, PTR_AT(vars, 0x110) + 16 + closest * 16);
                *(PathQuad *)toNext = *(PathQuad *)tmp;
                func_00282CF0(tmp, PTR_AT(vars, 0x164) + 16, PTR_AT(vars, 0x110) + 16 + closest * 16);
                *(PathQuad *)toPeer = *(PathQuad *)tmp;
                func_00282DD8(cross, toNext, toPeer);
                if (cross[2] > 0.0f)
                    FLOAT_AT(vars, 0x16C) = -FLOAT_AT(vars, 0x16C);
                if (FLOAT_AT(vars, 0x16C) > 1.5f)
                    FLOAT_AT(vars, 0x16C) = 1.5f;
                if (FLOAT_AT(vars, 0x16C) < -1.5f)
                    FLOAT_AT(vars, 0x16C) = -1.5f;
            }
            INT_AT(vars, 0x174) = -1000;
        } else if ((float)INT_AT(vars, 0x174) < 0.0f)
            FLOAT_AT(vars, 0x16C) = 0.0f;
        if (FLOAT_AT(vars, 0x134) > 0.563f)
            FLOAT_AT(vars, 0x134) = 0.563f;
        if (FLOAT_AT(vars, 0x134) < 0.1772f)
            FLOAT_AT(vars, 0x134) = 0.1772f;
    }

    oldIndex = INT_AT(vars, 0x114);
    distance = func_00282E80(vars + 0xF0, moby + 0x10);
    if ((INT_AT(vars, 0x244) && distance < 15.0f) || (!INT_AT(vars, 0x244) && distance < 5.0f)) {
        FLOAT_AT(vars, 0xA8) += (INT_AT(vars, 0x244) ? 15.0f : 5.0f) - distance;
        if (FLOAT_AT(PTR_AT(vars, 0x110), 0x1C) * func_00283CE0(INT_AT(PTR_AT(vars, 0x110), 0)) < FLOAT_AT(vars, 0xA8))
            FLOAT_AT(vars, 0xA8) -= FLOAT_AT(PTR_AT(vars, 0x110), 0x1C) * func_00283CE0(INT_AT(PTR_AT(vars, 0x110), 0));
        func_002C96F8(FLOAT_AT(vars, 0xA8), FLOAT_AT(PTR_AT(vars, 0x110), 0x1C), PTR_AT(vars, 0x110),
                      vars + 0x114, vars + 0x118, vars + 0xF0);
    } else {
        func_002C96F8(FLOAT_AT(vars, 0xA8), FLOAT_AT(PTR_AT(vars, 0x110), 0x1C), PTR_AT(vars, 0x110),
                      vars + 0x114, vars + 0x118, vars + 0xF0);
    }
    {
        float f = func_00283C80(FLOAT_AT(moby, 0xF8),
                                func_00283248(FLOAT_AT(vars, 0xF0) - FLOAT_AT(moby, 0x10),
                                              FLOAT_AT(vars, 0xF4) - FLOAT_AT(moby, 0x14)));

        if (f > 1.047197699546814f) {
            i = func_L04_00400AB0(moby, PTR_AT(vars, 0x110), 0);
            {
                float along = func_00283CE0(i) * FLOAT_AT(PTR_AT(vars, 0x110), 0x1C);

                f = along + (INT_AT(vars, 0x244) ? 15.0f : 5.0f);
            }
            FLOAT_AT(vars, 0xA8) = f;
            func_002C96F8(f, FLOAT_AT(PTR_AT(vars, 0x110), 0x1C), PTR_AT(vars, 0x110),
                          vars + 0x114, vars + 0x118, vars + 0xF0);
        }
    }
    for (i = oldIndex; i <= INT_AT(vars, 0x114); i++) {
        unsigned char *point = PTR_AT(vars, 0x110) + i * 16;
        float f = FLOAT_AT(point, 0x1C);

        if (f >= 1000.0f) {
            FLOAT_AT(vars, 0x16C) += func_002A7878(-0.25f, 0.25f);
            if (FLOAT_AT(vars, 0x16C) > 1.5f)
                FLOAT_AT(vars, 0x16C) = 1.5f;
            if (FLOAT_AT(vars, 0x16C) < -1.5f)
                FLOAT_AT(vars, 0x16C) = -1.5f;
            INT_AT(vars, 0x174) = func_00283CF0((func_002A7878(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
        } else if (f <= -1000.0f) {
            FLOAT_AT(vars, 0x16C) = 0.0f;
            INT_AT(vars, 0x174) = -1000;
        }
    }
    if (INT_AT(vars, 0x174) > 0) {
        INT_AT(vars, 0x174)--;
        if (INT_AT(vars, 0x174) == -1) {
            FLOAT_AT(vars, 0x16C) += func_002A7878(-0.25f, 0.25f);
            if (FLOAT_AT(vars, 0x16C) > 1.5f)
                FLOAT_AT(vars, 0x16C) = 1.5f;
            if (FLOAT_AT(vars, 0x16C) < -1.5f)
                FLOAT_AT(vars, 0x16C) = -1.5f;
            INT_AT(vars, 0x174) = func_00283CF0((func_002A7878(3.0f, 6.0f) * 300.0f + 2.0f) * 0.16666667f);
        }
    }
    distance = FLOAT_AT(vars, 0x170) + FLOAT_AT(vars, 0x16C);
    toNext[0] = func_00283180(func_00283B98(FLOAT_AT(moby, 0xF8), 1.5707964897155762f)) * distance;
    toNext[1] = func_00283198(func_00283B98(FLOAT_AT(moby, 0xF8), 1.5707964897155762f)) * distance;
    toNext[2] = 0.0f;
    func_00282CD8(toPeer, vars + 0xF0, toNext);
}
