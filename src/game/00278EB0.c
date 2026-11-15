#include "include_asm.h"
#include "names.h"
/* func_00278EB0 (204 bytes, boot + 27 levels): fills the D_001B7F80 block. The 0x60000
 * reset of D_001B22B0 is written before the coordinate stores; its constant then dies at the
 * second coordinate's addition, which gives retail's order of the two additions. */
extern void gfx_wait_for_dma_status_bits(unsigned long);
extern int sceGsSyncV(int);
extern void gfx_reset_packet_buffer(void);
extern void snd_clear_all_voices(void);
extern int D_001BAEC0[8];
typedef struct { int x, y, z, pad0C, f10, f14, f18; char pad1C[0x26 - 0x1C]; short f26; } CamState;
extern CamState D_001B7F80;
extern int D_001B1598 __attribute__((sda));
extern int D_001B22B0 __attribute__((sda));
extern int D_001A8BC0 __attribute__((sda));
extern float g_screen_fade __attribute__((sda));
extern int D_001A72D4 __attribute__((sda));

/* Sets up the camera and screen state for a new scene and resets the clock values it uses. */
void cam_init_scene_state(void)
{
    CamState *state;
    int x, y, z;
    gfx_wait_for_dma_status_bits(1UL);
    sceGsSyncV(0);
    D_001B1598++;
    y = D_001BAEC0[4];
    x = D_001BAEC0[3];
    z = D_001B22B0;
    state = &D_001B7F80;
    state->f14 = z - 0x60000;
    D_001B22B0 = 0x60000;
    state->x = x + 0x60000;
    state->y = y + 0x60000;
    state->z = state->x + 0xD0800;
    D_001A8BC0 = 0x2000;
    gfx_reset_packet_buffer();
    snd_clear_all_voices();
    state->f18 = D_001A72D4;
    state->f26 = 0;
    g_screen_fade = 1.0f;
}
