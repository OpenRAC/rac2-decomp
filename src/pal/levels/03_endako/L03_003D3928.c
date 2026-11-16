#include "include_asm.h"


#include "common.h"
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void func_32C010();
extern void func_32C328(char *a0, char *a1, s32 a2);
extern s32  func_32AB10(char *a0);
extern s32  func_360A80(s32 a0, s32 a1, char *a2);
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern u8  *g_moby_record_base;
extern u8   g_clank_scene_done_flag;
extern u8   g_remote_view_done_flag;
extern u8   g_barlow_hint_inside_flag;
extern u8   g_unused_byte_c;
extern u8   g_unused_byte_a;
extern u8   g_unused_byte_d;
extern u8   g_unused_byte_b;
extern u8   g_unused_byte_e;

void attached_effect_update_pal(char *a0)
{
    char *moby = *(char **)(a0 + 0x68);

    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(s32 *)(moby + 0x5C) |= 1;
        func_32C010(a0, moby + 0x60, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        func_32C328(a0, moby + 0x60, 0);
        break;
    }
}

