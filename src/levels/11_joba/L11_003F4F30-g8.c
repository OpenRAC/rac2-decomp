#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_transform_joint_point(u8 *arg0, s32 arg1, u8 *arg2);

extern void transform_vector(void *arg0, void *arg1, void *arg2);

extern void FastVecAdd(void *arg0, void *arg1, void *arg2);

extern void gfx_l00_draw_billboard_quad(void *arg0, s32 arg1, f32 arg2, f32 arg3);

extern s32 g_l11_billboard_quad_texture __attribute__((sda));

extern f32 g_l11_billboard_quad_heights[4] SDATA(D_L11_001B0678);

extern f32 g_l11_billboard_quad_widths[4] SDATA(D_L11_001B0688);

extern TI128 g_l11_billboard_corner_vectors[4] SDATA(D_L11_001B06A0);

/* Poses the object's four frames from the level's four pose vectors and the level's four
   angle pairs. */
void UpdateJobaFourFramePoses(u8 *moby) {
    u8 buf[0x50];
    u8 *pose = buf + 0x10;
    s32 i;

    for (i = 0; i < 4; i++) {
        moby_transform_joint_point(moby, i + 8, pose);
        transform_vector(buf, (void *)&((TI128 *)g_l11_billboard_corner_vectors)[i], pose);
        FastVecAdd(buf, buf, buf + 0x40);
        gfx_l00_draw_billboard_quad(buf, g_l11_billboard_quad_texture, g_l11_billboard_quad_widths[i], g_l11_billboard_quad_heights[i]);
    }
}

