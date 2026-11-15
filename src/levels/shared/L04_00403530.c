#include "common.h"

/* Own unit: the branch to the padding nop after the 15.0f constant needs -frac2-hazard-labels. */

#define INT_AT(p, o) (*(int *)((p) + (o)))
#define SHORT_AT(p, o) (*(short *)((p) + (o)))
#define FLOAT_AT(p, o) (*(float *)((p) + (o)))
#define PTR_AT(p, o) (*(unsigned char **)((p) + (o)))

typedef unsigned int PathQuad __attribute__((mode(TI)));

extern int D_001A7B90 MACRO_ADDR;
extern int D_L04_001A8FE4 __attribute__((sda));

extern void func_L04_00402D90(void *);
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
void func_L04_00403530(unsigned char *moby, unsigned char *vars)
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

    UpdateRacerRouteChoice(moby);

    if (speed < 0.0f
        || (speed >= 22.15f && INT_AT(vars, 0x160) >= 2
            && FLOAT_AT(vars, 0x11C) / FLOAT_AT(vars, 0x1B4) > 0.66f))
        speed = 22.15f;
    if (speed > 28.15f)
        speed = 28.15f;
    if (speed < 13.29f)
        speed = 13.29f;
    FLOAT_AT(vars, 0x134) = speed * 0.016666668f - IntToFloat(vars[0xA2] - 1) * 0.011666667f;

    if (PTR_AT(vars, 0x164) && !vars[0xA5] && GetCollHitMaterial() != 5) {
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
            FLOAT_AT(vars, 0x134) += (delta - 12.0f) * 0.0016666668234393f;
        if (PTR_AT(vars, 0x164)[0xBC] == 5 && !INT_AT(peerVars, 0x724) && delta > 1.0f && delta < 10.0f) {
            PTR_AT(peerVars, 0x734) = moby;
            INT_AT(peerVars, 0x720) = 1;
        }
        if (INT_AT(vars, 0x168) && vars[0xA2] != 1 && func_00282C48(delta) < 10.0f
            && INT_AT(vars, 0x160) >= D_L04_001A8FE4) {
            int closest;

            FLOAT_AT(vars, 0x134) += (delta * 0.016666668f) + (delta * 0.016666668f);
            if (FLOAT_AT(vars, 0x11C) > FLOAT_AT(peerVars, 0x310) && !INT_AT(vars, 0x180)
                && !SHORT_AT(vars, 0x17E) && PTR_AT(vars, 0x8C)) {
                float lead = FLOAT_AT(vars, 0x11C) - FLOAT_AT(peerVars, 0x310);

                if (lead < 10.0f && lead > 2.0f && !func_002A77E0(1)) {
                    unsigned char *target = PTR_AT(vars, 0x164);
                    float angle = fast_subtract_rotations(FLOAT_AT(moby, 0xF8),
                                                func_00283248(FLOAT_AT(target, 0x10) - FLOAT_AT(moby, 0x10),
                                                              FLOAT_AT(target, 0x14) - FLOAT_AT(moby, 0x14)));

                    if (angle > 0.0f)
                        func_002A7470(PTR_AT(vars, 0x8C), 8, 0, 12);
                    else
                        func_002A7470(PTR_AT(vars, 0x8C), 7, 0, 12);
                    INT_AT(vars, 0x180) = func_002A7820(120, 180);
                } else if (FLOAT_AT(vars, 0x11C) - FLOAT_AT(peerVars, 0x310) > -5.0f && !func_002A77E0(3)) {
                    unsigned char *target = PTR_AT(vars, 0x164);
                    float angle = fast_subtract_rotations(FLOAT_AT(moby, 0xF8),
                                                func_00283248(FLOAT_AT(target, 0x10) - FLOAT_AT(moby, 0x10),
                                                              FLOAT_AT(target, 0x14) - FLOAT_AT(moby, 0x14)));

                    if (angle > 0.0f)
                        func_002A7470(PTR_AT(vars, 0x8C), 5, 0, 12);
                    else
                        func_002A7470(PTR_AT(vars, 0x8C), 6, 0, 12);
                    INT_AT(vars, 0x180) = func_002A7820(120, 300);
                } else
                    INT_AT(vars, 0x180) = 60;
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
                nextDist = fast_vec_dist(PTR_AT(vars, 0x110) + 16 + next * 16, PTR_AT(vars, 0x164) + 16);
                prevDist = fast_vec_dist(PTR_AT(vars, 0x110) + 16 + prev * 16, PTR_AT(vars, 0x164) + 16);
                neighbor = prev;
                if (nextDist < prevDist)
                    neighbor = next;
                FLOAT_AT(vars, 0x16C) = func_L04_00365300(PTR_AT(vars, 0x110) + 16 + closest * 16,
                                                          PTR_AT(vars, 0x110) + 16 + neighbor * 16,
                                                          PTR_AT(vars, 0x164) + 16);
                FastVecSub(tmp, PTR_AT(vars, 0x110) + 16 + next * 16, PTR_AT(vars, 0x110) + 16 + closest * 16);
                *(PathQuad *)toNext = *(PathQuad *)tmp;
                FastVecSub(tmp, PTR_AT(vars, 0x164) + 16, PTR_AT(vars, 0x110) + 16 + closest * 16);
                *(PathQuad *)toPeer = *(PathQuad *)tmp;
                FastVecCross(cross, toNext, toPeer);
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
        if (FLOAT_AT(vars, 0x134) > 0.4691667f)
            FLOAT_AT(vars, 0x134) = 0.4691667f;
        if (FLOAT_AT(vars, 0x134) < 0.14766668f)
            FLOAT_AT(vars, 0x134) = 0.14766668f;
    }

    oldIndex = INT_AT(vars, 0x114);
    distance = vec_distance_xy(vars + 0xF0, moby + 0x10);
    if ((INT_AT(vars, 0x244) && distance < 15.0f) || (!INT_AT(vars, 0x244) && distance < 5.0f)) {
        FLOAT_AT(vars, 0xA8) += (INT_AT(vars, 0x244) ? 15.0f : 5.0f) - distance;
        if (FLOAT_AT(PTR_AT(vars, 0x110), 0x1C) * IntToFloat(INT_AT(PTR_AT(vars, 0x110), 0)) < FLOAT_AT(vars, 0xA8))
            FLOAT_AT(vars, 0xA8) -= FLOAT_AT(PTR_AT(vars, 0x110), 0x1C) * IntToFloat(INT_AT(PTR_AT(vars, 0x110), 0));
        func_002C96F8(FLOAT_AT(vars, 0xA8), FLOAT_AT(PTR_AT(vars, 0x110), 0x1C), PTR_AT(vars, 0x110),
                      vars + 0x114, vars + 0x118, vars + 0xF0);
    } else {
        func_002C96F8(FLOAT_AT(vars, 0xA8), FLOAT_AT(PTR_AT(vars, 0x110), 0x1C), PTR_AT(vars, 0x110),
                      vars + 0x114, vars + 0x118, vars + 0xF0);
    }
    {
        float f = FastDiffRots(FLOAT_AT(moby, 0xF8),
                                func_00283248(FLOAT_AT(vars, 0xF0) - FLOAT_AT(moby, 0x10),
                                              FLOAT_AT(vars, 0xF4) - FLOAT_AT(moby, 0x14)));

        if (f > 1.047197699546814f) {
            i = FindNearestRoutePointIndex(moby, PTR_AT(vars, 0x110), 0);
            {
                float along = IntToFloat(i) * FLOAT_AT(PTR_AT(vars, 0x110), 0x1C);

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
            INT_AT(vars, 0x174) = FloatToInt(func_002A7878(3.0f, 6.0f) * 60.0f);
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
            INT_AT(vars, 0x174) = FloatToInt(func_002A7878(3.0f, 6.0f) * 60.0f);
        }
    }
    distance = FLOAT_AT(vars, 0x170) + FLOAT_AT(vars, 0x16C);
    toNext[0] = func_00283180(FastAddRotations(FLOAT_AT(moby, 0xF8), 1.5707964897155762f)) * distance;
    toNext[1] = func_00283198(FastAddRotations(FLOAT_AT(moby, 0xF8), 1.5707964897155762f)) * distance;
    toNext[2] = 0.0f;
    add_vectors(toPeer, vars + 0xF0, toNext);
}
