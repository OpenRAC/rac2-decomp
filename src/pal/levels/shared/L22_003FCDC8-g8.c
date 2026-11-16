#include "include_asm.h"

#include "common.h"
extern f32 g_flyer_ramp_start __attribute__((sda));
extern f32 g_flyer_ramp_end __attribute__((sda));
extern f32 g_flyer_l22_speed __attribute__((sda));
extern f32 g_flyer_offset_x __attribute__((sda));
extern f32 g_flyer_offset_y __attribute__((sda));
extern f32 g_flyer_offset_z __attribute__((sda));
extern f32 g_flyer_scale __attribute__((sda));
extern u8 g_tether_origin[];
extern void matrix_mul_vec3(f32 *, f32 *, u8 *);
extern void FastVecAdd(u8 *, u8 *, u8 *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 vec_distance_xy(u8 *, u8 *);
extern f32 FastAddRotations(f32, f32);
extern void moby_mark_spawned(void *);

/* Runs the object's speed ramp, then either tears it down (no controller slot, or a
 * slot of kind 0xFE/0xFD) or points it along the level's direction vector and stores
 * the turn it must make plus the angle it turns at. */
void ramping_flyer_update_pal(u8 *a0) {
    u8 *obj = a0;
    u8 *ctl = *(u8 **)(obj + 0x68);
    u8 *sub = *(u8 **)(obj + 0x24);
    u8 *p;
    u8 *dst;
    u8 *buf;
    f32 v[8];
    f32 t;
    f32 x, y, z, angle, scale, control_speed;

    *(f32 *)(obj + 0x2C) = *(f32 *)(sub + 0x24)
        * (g_flyer_ramp_start + (g_flyer_ramp_end - g_flyer_ramp_start) * *(f32 *)(ctl + 0x18));
    p = *(u8 **)(ctl + 0x10);
    if (p == 0 || *(u8 *)(p + 0x20) == 0xFE || *(u8 *)(p + 0x20) == 0xFD) {
        moby_mark_spawned(obj);
        return;
    }
    dst = obj + 0x10;
    control_speed = g_flyer_l22_speed;
    x = g_flyer_offset_x;
    y = g_flyer_offset_y;
    z = g_flyer_offset_z;
    *(f32 *)(ctl + 0xC) = control_speed;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    matrix_mul_vec3(v, v, g_tether_origin + 0x230);
    buf = (u8 *)(v + 4);
    FastVecAdd(buf, (u8 *)v, g_tether_origin);
    qcopy(dst, buf);
    *(f32 *)(obj + 0xF8) = mat_fast_helper_a(*(f32 *)(ctl + 0x0) - *(f32 *)(obj + 0x10),
                                         *(f32 *)(ctl + 0x4) - *(f32 *)(obj + 0x14));
    t = vec_distance_xy(dst, ctl);
    angle = -mat_fast_helper_a(t, *(f32 *)(ctl + 0x8) - *(f32 *)(obj + 0x18));
    scale = g_flyer_scale;
    *(f32 *)(obj + 0xF4) = angle;
    *(f32 *)(obj + 0xF0) = FastAddRotations(*(f32 *)(obj + 0xF0), scale * 0.0003490659f);
}
