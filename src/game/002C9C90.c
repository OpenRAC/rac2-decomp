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

extern CameraBlock D_001B5200;
extern s32 D_001B5580;
extern s32 D_001B5590;

void func_002C9C90(void) {
    gActiveCamera.pos[0] = 256.0f;
    gActiveCamera.pos[2] = 64.0f;
    gActiveCamera.pos[1] = 256.0f;
    qzero_nc(&gActiveCamera.matrix[0].f[0]);
    qzero_nc(&D_001B5580);
    qzero_nc(&D_001B5590);
    gActiveCamera.matrix[0].f[0] = 1.0f;
    gActiveCamera.matrix[1].f[1] = 1.0f;
    gActiveCamera.matrix[2].f[2] = 1.0f;
    gActiveCamera.matrix[2].f[3] = 1.0f;
}
