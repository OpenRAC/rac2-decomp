#include "names.h"
/* Carried from rac3-decomp (src/levels/shared/L01_0047DBB0.c, func_L01_0047DCB8): the
   same instructions with rac2's offsets. Uploads D_001A7344 * 1536 bytes from the source
   at +0x20 of D_001F2840 to GS memory in 16 KB blocks (to the top of the 0x3FB000 area when
   the mode at +0xD0 is 2 or more, else at D_001A72D4), counts the call in D_001B1598 and
   clears the mode. */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    u8 pad0[0x20];
    s32 src;
    u8 pad24[0xD0 - 0x24];
    s32 mode;
} UploadRequest;

extern UploadRequest g_pause_menu_state;
extern s32 g_frame_counter_3 MACRO_ADDR;
extern s32 g_screen_height MACRO_ADDR;
extern s32 g_vram_frame_base __attribute__((sda));
extern void gfx_wait_for_dma_status_bits(s32);
extern int sceGsSyncV(s32);
extern s32 func_00126470(void *, s16, s32, s32, s32, s32, s32, s32);
extern void FlushCache(s32);
extern s32 func_00126730(void *, s32);
extern int gfx_wait_paths_idle(s32, s32);

void menu_upload_pause_background_to_gs(void) {
    TI128 buf[7];
    s32 size;
    s32 dst;
    s32 src;

    gfx_wait_for_dma_status_bits(1);
    sceGsSyncV(0);
    g_frame_counter_3++;
    size = g_screen_height * 1536;
    src = g_pause_menu_state.src;
    dst = g_vram_frame_base;
    if (g_pause_menu_state.mode >= 2) {
        dst = 0x3FB000 - size;
    }
    for (; size >= 0; size -= 16384) {
        func_00126470(buf, dst >> 8, 1, 0, 0, 0, 64, 64);
        dst += 16384;
        FlushCache(0);
        func_00126730(buf, src);
        src += 16384;
        gfx_wait_paths_idle(0, 0);
    }
    g_pause_menu_state.mode = 0;
}
