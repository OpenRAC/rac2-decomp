#include "include_asm.h"
#include "common.h"

/* func_L18_003FB620 is in L18_003FB620-particles.c (-G32 settings record). */

extern int D_L18_001B15C0 __attribute__((sda));
extern int D_L18_001B15B0 __attribute__((sda));
extern float D_L18_001B15B8 __attribute__((sda));
extern float D_L18_001B15B4 __attribute__((sda));

extern int D_L18_001B15E0 __attribute__((sda));
extern int D_L18_001B15D0 __attribute__((sda));
extern float D_L18_001B15D8 __attribute__((sda));
extern float D_L18_001B15D4 __attribute__((sda));

extern int D_L18_001B1620 __attribute__((sda));
extern int D_L18_001B1614 __attribute__((sda));
extern float D_L18_001B161C __attribute__((sda));
extern float D_L18_001B1618 __attribute__((sda));
extern void func_0029FC20(s32 arg0, s32 arg1, void *arg2);
extern void func_002830C0(void *arg0, void *arg1, void *arg2);
extern void func_00282CC0(void *arg0, void *arg1, void *arg2);
extern void func_L00_00325AE8(void *arg0, s32 arg1, float arg2, float arg3);

/* Spawns a spark effect at the first bone point of the object, using the first set of effect values. */
void func_L18_00432FB8(u8 *moby) {
    u8 buf[0x50];
    u8 *bonePos = buf + 0x10;
    TransformMobyJointPoint(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C0), 1, bonePos);
    transform_vector(buf, &D_L18_001B15C0, bonePos);
    FastVecAdd(buf, buf, buf + 0x40);
    DrawBillboardQuad_L00(buf, D_L18_001B15B0, D_L18_001B15B8, D_L18_001B15B4);
}
/* Spawns a spark effect at the first bone point of the object, using the second set of effect values. */
void func_L18_00433020(u8 *moby) {
    u8 buf[0x50];
    u8 *bonePos = buf + 0x10;
    TransformMobyJointPoint(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C0), 1, bonePos);
    transform_vector(buf, &D_L18_001B15E0, bonePos);
    FastVecAdd(buf, buf, buf + 0x40);
    DrawBillboardQuad_L00(buf, D_L18_001B15D0, D_L18_001B15D8, D_L18_001B15D4);
}
/* Spawns a spark effect at the chosen point of the second bone, using a third set of effect values. */
void func_L18_00433168(u8 *moby, s32 boneIndex) {
    u8 buf[0x50];
    u8 *bonePos = buf + 0x10;
    TransformMobyJointPoint(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C4), boneIndex, bonePos);
    transform_vector(buf, &D_L18_001B1620, bonePos);
    FastVecAdd(buf, buf, buf + 0x40);
    DrawBillboardQuad_L00(buf, D_L18_001B1614, D_L18_001B161C, D_L18_001B1618);
}

typedef int TI128 __attribute__((mode(TI)));

extern void func_00308DE0(void *arg0, void *arg1, void *arg2);
extern void func_003088F0(void *arg0, void *arg1, void *arg2);
extern void func_00308920(void *arg0, void *arg1, void *arg2);
extern void func_00308BD8(void *arg0, void *arg1, float arg2);
extern float func_003089E0(void *arg0, void *arg1);
extern s32 func_00337AD8(s32 arg0, s32 arg1, float arg2);
extern void func_00340828(void *arg0, s32 arg1, float arg2, float arg3);
extern int D_L18_001B15F0 __attribute__((sda));
extern float D_L18_001B15F4 __attribute__((sda));
extern float D_L18_001B15F8 __attribute__((sda));
extern u8 D_L18_001B1600[1] __attribute__((sda));
extern float D_L18_001B1610 __attribute__((sda));
extern u8 D_001C97C0[];
extern float D_L18_001B1520 __attribute__((sda));
extern float D_L18_001B1524 __attribute__((sda));
extern int D_L18_001B1528 __attribute__((sda));
extern float D_L18_001B152C __attribute__((sda));

extern char D_L18_001B1480[1] __attribute__((sda));
extern char D_L18_001B1490[] __attribute__((sda));

/* Runs the effect twice: once against the shared table at 0x1B1480 and once
   against the level's own copy at 0x1B1490. */
void func_L18_0042FAA8(u8 *moby)
{
    u8 *mobyCopy = moby;

    DrawBeamFromOffset(moby, D_L18_001B1480);
    DrawBeamFromOffset(mobyCopy, D_L18_001B1490);
}

/* Draws a glowing beam from a point on the object, but only when it is long enough to see. */
void func_L18_00433088(u8 *moby, s32 boneIndex) {
    u8 buf[0x70];
    float distance;
    u8 *bonePos = buf + 0x10;

    TransformMobyJointPoint(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C4), boneIndex, bonePos);
    func_00308DE0(buf, D_L18_001B1600, bonePos);
    func_003088F0(buf, buf, buf + 0x40);
    func_00308920(buf + 0x50, D_001C97C0, buf);
    func_00308BD8(buf + 0x50, buf + 0x50, 1.0f);
    qcopy(buf + 0x60, bonePos);
    distance = func_003089E0(buf + 0x50, buf + 0x60);
    if (D_L18_001B1610 < distance) {
        func_00340828(buf, func_00337AD8(D_L18_001B15F0 & 0xFFFFFF,
                                         D_L18_001B15F0, distance * distance),
                      D_L18_001B15F8, D_L18_001B15F4);
    }
}


/* Draws a glowing beam from the object towards a given offset, but only when it is long enough to see. */
void func_L18_0042FAE0(u8 *moby, void *localOffset) {
    u8 buf[0x30];
    u8 *dir;
    u8 *basePos = moby + 0xC0;
    float distance;
    matrix_mul_vec3(buf, localOffset, basePos);
    func_003088F0(buf, moby + 0x10, buf);
    dir = buf + 0x10;
    func_00308920(dir, D_001C97C0, buf);
    func_00308BD8(dir, dir, 1.0f);
    func_00308BD8(buf + 0x20, basePos, -1.0f);
    distance = func_003089E0(dir, buf + 0x20);
    if (D_L18_001B152C < distance) {
        func_00340828(buf, func_00337AD8(D_L18_001B1528 & 0xFFFFFF,
                                         D_L18_001B1528, distance * distance),
                      D_L18_001B1524, D_L18_001B1520);
    }
}
