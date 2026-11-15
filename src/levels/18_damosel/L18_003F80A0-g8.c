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
extern void moby_transform_joint_point(s32 arg0, s32 arg1, void *arg2);
extern void transform_vector(void *arg0, void *arg1, void *arg2);
extern void FastVecAdd(void *arg0, void *arg1, void *arg2);
extern void gfx_l00_draw_billboard_quad(void *arg0, s32 arg1, float arg2, float arg3);

/* Spawns a spark effect at the first bone point of the object, using the first set of effect values. */
void part_spawn_spark_first_bone(u8 *moby) {
    u8 buf[0x50];
    u8 *bone_pos = buf + 0x10;
    moby_transform_joint_point(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C0), 1, bone_pos);
    transform_vector(buf, &D_L18_001B15C0, bone_pos);
    FastVecAdd(buf, buf, buf + 0x40);
    gfx_l00_draw_billboard_quad(buf, D_L18_001B15B0, D_L18_001B15B8, D_L18_001B15B4);
}
/* Spawns a spark effect at the first bone point of the object, using the second set of effect values. */
void part_spawn_spark_first_bone_alt(u8 *moby) {
    u8 buf[0x50];
    u8 *bone_pos = buf + 0x10;
    moby_transform_joint_point(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C0), 1, bone_pos);
    transform_vector(buf, &D_L18_001B15E0, bone_pos);
    FastVecAdd(buf, buf, buf + 0x40);
    gfx_l00_draw_billboard_quad(buf, D_L18_001B15D0, D_L18_001B15D8, D_L18_001B15D4);
}
/* Spawns a spark effect at the chosen point of the second bone, using a third set of effect values. */
void part_spawn_spark_second_bone(u8 *moby, s32 bone_index) {
    u8 buf[0x50];
    u8 *bone_pos = buf + 0x10;
    moby_transform_joint_point(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C4), bone_index, bone_pos);
    transform_vector(buf, &D_L18_001B1620, bone_pos);
    FastVecAdd(buf, buf, buf + 0x40);
    gfx_l00_draw_billboard_quad(buf, D_L18_001B1614, D_L18_001B161C, D_L18_001B1618);
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
void gfx_draw_beams_both_tables(u8 *moby)
{
    u8 *moby_copy = moby;

    gfx_draw_beam_from_offset(moby, D_L18_001B1480);
    gfx_draw_beam_from_offset(moby_copy, D_L18_001B1490);
}

/* Draws a glowing beam from a point on the object, but only when it is long enough to see. */
void gfx_draw_beam_from_bone_point(u8 *moby, s32 bone_index) {
    u8 buf[0x70];
    float distance;
    u8 *bone_pos = buf + 0x10;

    moby_transform_joint_point(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C4), bone_index, bone_pos);
    func_00308DE0(buf, D_L18_001B1600, bone_pos);
    func_003088F0(buf, buf, buf + 0x40);
    func_00308920(buf + 0x50, D_001C97C0, buf);
    func_00308BD8(buf + 0x50, buf + 0x50, 1.0f);
    qcopy(buf + 0x60, bone_pos);
    distance = func_003089E0(buf + 0x50, buf + 0x60);
    if (D_L18_001B1610 < distance) {
        func_00340828(buf, func_00337AD8(D_L18_001B15F0 & 0xFFFFFF,
                                         D_L18_001B15F0, distance * distance),
                      D_L18_001B15F8, D_L18_001B15F4);
    }
}


/* Draws a glowing beam from the object towards a given offset, but only when it is long enough to see. */
void gfx_draw_beam_from_offset(u8 *moby, void *local_offset) {
    u8 buf[0x30];
    u8 *dir;
    u8 *base_pos = moby + 0xC0;
    float distance;
    matrix_mul_vec3(buf, local_offset, base_pos);
    func_003088F0(buf, moby + 0x10, buf);
    dir = buf + 0x10;
    func_00308920(dir, D_001C97C0, buf);
    func_00308BD8(dir, dir, 1.0f);
    func_00308BD8(buf + 0x20, base_pos, -1.0f);
    distance = func_003089E0(dir, buf + 0x20);
    if (D_L18_001B152C < distance) {
        func_00340828(buf, func_00337AD8(D_L18_001B1528 & 0xFFFFFF,
                                         D_L18_001B1528, distance * distance),
                      D_L18_001B1524, D_L18_001B1520);
    }
}
