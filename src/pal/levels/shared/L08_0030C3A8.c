#include "include_asm.h"

#include "common.h"
extern void LoadPackSingleTexture();
extern void gfx_send_gs_register_packet();
extern void load_copy_header_relocate_pointers();
extern u8 D_L08_001DB5E7;
extern s32 D_L08_001DAC40[];
extern s32 D_L08_001BFEF4;
extern u8 *D_L08_001B29DC __attribute__((sda));
extern u8 *D_L08_001B29E0 __attribute__((sda));
extern u8 *D_L08_001B29DC __attribute__((sda));
extern u8 *g_hero_moby;

void func_PAL_L08_0030C3A8(s32 x) {
    LoadPackSingleTexture(x);
    gfx_send_gs_register_packet(x);
    load_copy_header_relocate_pointers(D_L08_001DAC40[D_L08_001DB5E7], D_L08_001BFEF4);
}

