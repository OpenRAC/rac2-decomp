#include "common.h"

typedef struct { u8 pad00[0x86]; s16 state; } Moby_271E88;
typedef struct {
    u8 pad000[0x140];
    f32 pos[4];
    u8 pad150[0x190 - 0x150];
    Moby_271E88 *moby;
    u8 pad194[0x400 - 0x194];
    s32 grounded;
} Cam_271E88;

extern Cam_271E88 g_active_camera;
extern s32 g_current_game_mode __attribute__((sda));
extern f32 D_001BAFA0[4];
extern s32 CollLine(void *, void *, s32, void *, s32);
extern int GetCollHitMaterial(void);
extern float coll_get_ground_height_at_position(float *, void *);

/* Probe down from the camera target for up to six hits; grounded when a floor is within reach. */
void cam_update_grounded(void)
{
    f32 top[4] __attribute__((aligned(16)));
    f32 bottom[4] __attribute__((aligned(16)));
    int i;

    if (g_active_camera.moby->state == 6 || g_current_game_mode != 0) {
        g_active_camera.grounded = 0;
        return;
    }
    qcopy(top, g_active_camera.pos);
    qcopy(bottom, g_active_camera.pos);
    top[2] += 0.75f;
    bottom[2] -= 0.75f;
    for (i = 0; i < 6 && CollLine(top, bottom, 0x12, 0, 0); i++) {
        if (GetCollHitMaterial() == 0) {
            f32 floorHeight = coll_get_ground_height_at_position(D_001BAFA0, 0) + 0.04f;
            if (g_active_camera.pos[2] < floorHeight) {
                g_active_camera.grounded = 1;
            } else {
                g_active_camera.grounded = 0;
            }
            return;
        }
        qcopy(top, D_001BAFA0);
        top[2] -= 0.01f;
    }
}
