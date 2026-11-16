#include "include_asm.h"
#include "common.h"

/* func_L18_003FB620 is in L18_003FB620-particles.c (-G32 settings record). */

extern int g_spark_local_offset __attribute__((sda));
extern int g_spark_l18_quad_color __attribute__((sda));
extern float g_spark_quad_width __attribute__((sda));
extern float g_spark_quad_height __attribute__((sda));

extern int g_spark_alt_local_offset __attribute__((sda));
extern int g_spark_alt_quad_color __attribute__((sda));
extern float g_spark_alt_quad_width __attribute__((sda));
extern float g_spark_alt_quad_height __attribute__((sda));

extern int g_spark_second_local_offset __attribute__((sda));
extern int g_spark_second_quad_color __attribute__((sda));
extern float g_spark_second_quad_width __attribute__((sda));
extern float g_spark_second_quad_height __attribute__((sda));
extern void moby_transform_joint_point(s32 arg0, s32 arg1, void *arg2);
extern void transform_vector(void *arg0, void *arg1, void *arg2);
extern void FastVecAdd(void *arg0, void *arg1, void *arg2);
extern void gfx_l00_draw_billboard_quad(void *arg0, s32 arg1, float arg2, float arg3);

/* Spawns a spark effect at the first bone point of the object, using the first set of effect values. */
void part_spawn_spark_first_bone(u8 *moby) {
    u8 buf[0x50];
    u8 *bone_pos = buf + 0x10;
    moby_transform_joint_point(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C0), 1, bone_pos);
    transform_vector(buf, &g_spark_local_offset, bone_pos);
    FastVecAdd(buf, buf, buf + 0x40);
    gfx_l00_draw_billboard_quad(buf, g_spark_l18_quad_color, g_spark_quad_width, g_spark_quad_height);
}
/* Spawns a spark effect at the first bone point of the object, using the second set of effect values. */
void part_spawn_spark_first_bone_alt(u8 *moby) {
    u8 buf[0x50];
    u8 *bone_pos = buf + 0x10;
    moby_transform_joint_point(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C0), 1, bone_pos);
    transform_vector(buf, &g_spark_alt_local_offset, bone_pos);
    FastVecAdd(buf, buf, buf + 0x40);
    gfx_l00_draw_billboard_quad(buf, g_spark_alt_quad_color, g_spark_alt_quad_width, g_spark_alt_quad_height);
}
/* Spawns a spark effect at the chosen point of the second bone, using a third set of effect values. */
void part_spawn_spark_second_bone(u8 *moby, s32 bone_index) {
    u8 buf[0x50];
    u8 *bone_pos = buf + 0x10;
    moby_transform_joint_point(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C4), bone_index, bone_pos);
    transform_vector(buf, &g_spark_second_local_offset, bone_pos);
    FastVecAdd(buf, buf, buf + 0x40);
    gfx_l00_draw_billboard_quad(buf, g_spark_second_quad_color, g_spark_second_quad_width, g_spark_second_quad_height);
}

typedef int TI128 __attribute__((mode(TI)));

extern void func_00308DE0(void *arg0, void *arg1, void *arg2);
extern void func_003088F0(void *arg0, void *arg1, void *arg2);
extern void func_00308920(void *arg0, void *arg1, void *arg2);
extern void func_00308BD8(void *arg0, void *arg1, float arg2);
extern float func_003089E0(void *arg0, void *arg1);
extern s32 func_00337AD8(s32 arg0, s32 arg1, float arg2);
extern void func_00340828(void *arg0, s32 arg1, float arg2, float arg3);
extern int g_beam_l18_color_2 __attribute__((sda));
extern float g_beam_l18_width_end __attribute__((sda));
extern float g_beam_l18_width_start __attribute__((sda));
extern u8 g_beam_local_offset[1] __attribute__((sda));
extern float g_beam_l18_max_distance_2 __attribute__((sda));
extern u8 g_beam_target_vec[];
extern float g_beam_width_param __attribute__((sda));
extern float g_beam_length_param __attribute__((sda));
extern int g_beam_l18_color __attribute__((sda));
extern float g_beam_l18_max_distance __attribute__((sda));

extern char g_leader_exhaust_offset_left[1] __attribute__((sda));
extern char g_leader_exhaust_offset_right[] __attribute__((sda));

/* Runs the effect twice: once against the shared table at 0x1B1480 and once
   against the level's own copy at 0x1B1490. */
void gfx_draw_beams_both_tables(u8 *moby)
{
    u8 *moby_copy = moby;

    gfx_draw_beam_from_offset(moby, g_leader_exhaust_offset_left);
    gfx_draw_beam_from_offset(moby_copy, g_leader_exhaust_offset_right);
}

/* Draws a glowing beam from a point on the object, but only when it is long enough to see. */
void gfx_draw_beam_from_bone_point(u8 *moby, s32 bone_index) {
    u8 buf[0x70];
    float distance;
    u8 *bone_pos = buf + 0x10;

    moby_transform_joint_point(*(s32 *)(*(u8 **)(moby + 0x68) + 0x7C4), bone_index, bone_pos);
    func_00308DE0(buf, g_beam_local_offset, bone_pos);
    func_003088F0(buf, buf, buf + 0x40);
    func_00308920(buf + 0x50, g_beam_target_vec, buf);
    func_00308BD8(buf + 0x50, buf + 0x50, 1.0f);
    qcopy(buf + 0x60, bone_pos);
    distance = func_003089E0(buf + 0x50, buf + 0x60);
    if (g_beam_l18_max_distance_2 < distance) {
        func_00340828(buf, func_00337AD8(g_beam_l18_color_2 & 0xFFFFFF,
                                         g_beam_l18_color_2, distance * distance),
                      g_beam_l18_width_start, g_beam_l18_width_end);
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
    func_00308920(dir, g_beam_target_vec, buf);
    func_00308BD8(dir, dir, 1.0f);
    func_00308BD8(buf + 0x20, base_pos, -1.0f);
    distance = func_003089E0(dir, buf + 0x20);
    if (g_beam_l18_max_distance < distance) {
        func_00340828(buf, func_00337AD8(g_beam_l18_color & 0xFFFFFF,
                                         g_beam_l18_color, distance * distance),
                      g_beam_length_param, g_beam_width_param);
    }
}
