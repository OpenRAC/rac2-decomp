#include "names.h"
/* Carried from rac1-decomp (src/game/pause.c, reset_active_camera_position_and_basis,
   func_00219C08): the same instructions; rac2's camera block is larger, so the matrix sits
   at +0x370 instead of +0x350. Puts the active camera at (256, 256, 64) with an identity
   basis. */

#include "common.h"

typedef struct {
    f32 f[4];
} CameraRow;

typedef struct {
    u8 pad0[0x140];
    f32 pos[3];               /* 0x140 */
    u8 pad14C[0x370 - 0x14C];
    CameraRow matrix[3];      /* 0x370 */
} CameraBlock;

extern CameraBlock g_active_camera;
extern s32 g_sway_vector;
extern s32 g_camera_reset_word;

void cam_reset_active_position(void) {
    g_active_camera.pos[0] = 256.0f;
    g_active_camera.pos[2] = 64.0f;
    g_active_camera.pos[1] = 256.0f;
    qzero_nc(&g_active_camera.matrix[0].f[0]);
    qzero_nc(&g_sway_vector);
    qzero_nc(&g_camera_reset_word);
    g_active_camera.matrix[0].f[0] = 1.0f;
    g_active_camera.matrix[1].f[1] = 1.0f;
    g_active_camera.matrix[2].f[2] = 1.0f;
    g_active_camera.matrix[2].f[3] = 1.0f;
}
