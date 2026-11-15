#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { Quad v[3]; } __attribute__((aligned(16))) Axes4045E0;

extern char D_L04_001B9680[];
extern Quad D_L04_001BFAF0;
/* const: retail loads the three rows past the flag stores before them. */
extern const Axes4045E0 D_001B0630;

extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_00277258(void *, int, void *, float);
extern void func_L04_00402C88(u8 *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern void func_L04_00403530(u8 *, u8 *);
extern void func_L04_004027B0(u8 *, u8 *);
extern void func_L04_00400EE0(u8 *, u8 *);
extern void func_L04_004044B8(u8 *, u8 *);
extern void func_L04_00404100(u8 *, u8 *);
extern s32 func_L04_00400AB0(void *, void *, s32);
extern float func_00283CE0(int);
extern void func_002C96F8(float, float, void *, void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern float func_00282DB0(void *, void *);
extern void func_L04_00410518(u8 *, u8 *, void *, void *, void *, void *);

/* Update of the path follower: state 0 lands it, scales its three axes and draws six random
   phases; state 2 runs its behaviours while the leader is not waiting; state 3 walks to the
   nearest path node and, after 300 frames, leaves for the leader once it is 5 units away and
   out of sight; state 4 drops both targets. The leader's own state can hold it entirely. */
/* Updates the enemy hoverbike that follows a race path behind its leader. */
void func_L04_004045E0(u8 *bike)
{
    u8 *vars = *(u8 **)(bike + 0x68);
    u8 *leader;
    u8 *leaderVars;
    u8 *pos;
    u8 *dst;
    u8 *src;
    f32 *phases;
    union {
        Axes4045E0 axes;
        f32 d[4];
    } u;
    f32 scale;
    f32 targetDistance;
    int nearestPoint;
    int i;
    Quad axisRow0, axisRow1, axisRow2;
    int j;
    f32 *phasePtr;

    *(f32 *)(bike + 0x2C) = *(f32 *)(*(u8 **)(bike + 0x24) + 0x24) * 0.25f;
    bike[0x30] = 0xFF;
    *(s16 *)(bike + 0x32) = 0x7F;
    if (bike[0x31] != 0 && fast_vec_dist(bike + 0x10, D_L04_001B9680) < 9.0f) {
        UpdateMobyGroundCheck(bike);
        bike[0x6F] = 8;
    }
    if (*(u8 **)(vars + 0x164) != 0) {
        if ((*(u8 **)(vars + 0x164))[0x20] == 1 || (*(u8 **)(vars + 0x164))[0x20] == 4 || (*(u8 **)(vars + 0x164))[0x20] == 0)
            return;
        if ((*(u8 **)(vars + 0x164))[0x20] == 2 && (u8)((*(u8 **)(vars + 0x164))[0xBC] - 5) < 2)
            (*(s32 *)(vars + 0x1B8))++;
    }
    switch (bike[0x20]) {
    case 0:
        if (TestPointAgainstCollision(bike + 0x10, 4, bike, *(f32 *)(vars + 0x90)))
            *(Quad *)(bike + 0x10) = D_L04_001BFAF0;
        *(Quad *)(vars + 0xB0) = *(Quad *)(bike + 0x10);
        *(Quad *)(vars + 0xC0) = *(Quad *)(bike + 0xF0);
        dst = vars + 0x200;
        phases = (f32 *)(vars + 0x184);
        ComputeRacerRouteLengths(bike);
        bike[0x20] = 1;
        *(s32 *)(vars + 0x30) = 0;
        axisRow0 = D_001B0630.v[0];
        axisRow1 = D_001B0630.v[1];
        axisRow2 = D_001B0630.v[2];
        *(u16 *)(bike + 0x34) |= 0x41;
        bike[0x62] = 1;
        u.axes.v[0] = axisRow0;
        u.axes.v[1] = axisRow1;
        u.axes.v[2] = axisRow2;
        scale = *(f32 *)(bike + 0x2C) / *(f32 *)(*(u8 **)(bike + 0x24) + 0x24);
        src = (u8 *)&u.axes;
        for (i = 2; i >= 0; i--) {
            FastVecScale(dst, src, scale);
            src += 0x10;
            dst += 0x10;
        }
        phasePtr = phases;
        for (j = 5; j >= 0; j--)
            *phasePtr++ = RandomFloatRange(0.0f, 1.0f);
        return;
    case 1:
        break;
    case 2:
        if (*(u8 **)(vars + 0x164) != 0 && (*(u8 **)(vars + 0x164))[0x20] == 2 && (*(u8 **)(vars + 0x164))[0xBC] == 0)
            return;
        UpdateRouteFollowerPace(bike, vars);
        UpdateRacerBoostPadContact(bike, vars);
        UpdateRacingHoverbikeMovement(bike, vars);
        UpdateRacerCheckpointProgress(bike, vars);
        UpdateRacerBikeLean(bike, vars);
        return;
    case 3:
        if (*(u16 *)(bike + 0x96) == 0) {
            nearestPoint = FindNearestRoutePointIndex(bike, *(u8 **)(vars + 0x110), 1);
            *(Quad *)(bike + 0x10) = *(Quad *)(*(u8 **)(vars + 0x110) + nearestPoint * 16 + 0x10);
            targetDistance = IntToFloat(nearestPoint) * *(f32 *)(*(u8 **)(vars + 0x110) + 0x1C) +
                (*(s32 *)(vars + 0x244) != 0 ? 15.0f : 5.0f);
            *(f32 *)(vars + 0xA8) = targetDistance;
            SampleKeyTrack(targetDistance, *(f32 *)(*(u8 **)(vars + 0x110) + 0x1C), *(u8 **)(vars + 0x110),
                          vars + 0x114, vars + 0x118, vars + 0xF0);
        }
        if (*(u16 *)(bike + 0x96) >= 300 && (leader = *(u8 **)(vars + 0x164)) != 0) {
            pos = bike + 0x10;
            leaderVars = *(u8 **)(leader + 0x68);
            FastVecSub(u.d, pos, leader + 0x10);
            if (FastMathHelperA(pos, 60.0f) == -1 && FastVecDot(u.d, u.d) > 25.0f) {
                *(s32 *)(bike + 0x98) = *(s32 *)(*(u8 **)(bike + 0x24) + 0x10);
                *(u16 *)(bike + 0x34) = (*(u16 *)(bike + 0x34) & 0xFFBE) | 0x1400;
                if (*(u8 **)(vars + 0x8C) != 0)
                    *(u16 *)(*(u8 **)(vars + 0x8C) + 0x34) &= 0xFFBE;
                FindNearestRoutePoint(bike, leaderVars, vars + 0x120, vars + 0x124, vars + 0x11C, *(void **)(vars + 0x160));
                bike[0x20] = 2;
            }
        }
        (*(u16 *)(bike + 0x96))++;
        break;
    case 4:
        *(s32 *)(bike + 0x48) = 0;
        if (*(u8 **)(vars + 0x8C) != 0)
            *(s32 *)(*(u8 **)(vars + 0x8C) + 0x48) = 0;
        bike[0x20] = 1;
        break;
    }
}
