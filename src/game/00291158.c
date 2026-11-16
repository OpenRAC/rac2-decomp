#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    float x;
    float y;
    float z;
} Vec3_00291158;

/* the two ten-entry tables: the source heights and the scaled copy the pointer is aimed at */
extern Vec3_00291158 g_sky_shell_heights_2[];

extern Vec3_00291158 g_sky_shell_scaled_heights[];

extern Vec3_00291158 *g_sky_shell_heights __attribute__((sda));

/* the mode word: 2 turns the reference axis from +x to -y */
extern s32 g_current_game_mode MACRO_ADDR;

/* the axis the reference is measured against */
extern float g_camera_basis_vectors[];

/* the record whose count drives the per-entry pass, and the overflow entry's block */
extern char *g_sky_shell_definition MACRO_ADDR;

extern float g_view_matrix[] MACRO_ADDR;

extern float FastVecDot(void *, void *);

extern void set_identity_matrix(void *);

extern void cam_update_view_rotation(s32);

extern void gfx_process_view_entry(s32);

/* scales the ten heights by the negated projection of the reference axis, then runs the
   per-entry pass (entries past the tenth only get the overflow block) */
void gfx_update_sky_shell_heights(void) {
    union {
        TI128 q;
        float f[4];
    } axis;
    float scale;
    s32 j;
    s32 i;

    axis.q = 0;
    axis.f[0] = 1.0f;
    g_sky_shell_heights = g_sky_shell_scaled_heights;
    if (g_current_game_mode == 2) {
        axis.f[0] = 0.0f;
        axis.f[1] = -1.0f;
    }
    scale = -FastVecDot(g_camera_basis_vectors, &axis);
    for (j = 0; j < 10; j++) {
        g_sky_shell_scaled_heights[j].z = g_sky_shell_heights_2[j].z * scale;
    }
    for (i = 0; i < *(short *)(g_sky_shell_definition + 6); i++) {
        if (i >= 10) {
            set_identity_matrix(g_view_matrix);
        } else {
            cam_update_view_rotation(i);
        }
        gfx_process_view_entry(i);
    }
}
