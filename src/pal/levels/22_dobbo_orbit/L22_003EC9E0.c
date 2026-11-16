#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern s32 g_trigger_event_list_head __attribute__((sda));
extern u8 g_unused_level_byte __attribute__((sda));
extern s32 g_trigger_event_flag __attribute__((sda));
extern s32 g_unused_l22_level_word __attribute__((sda));
extern s32 func_2F36F0(s32);
extern void text_show_message_at_moby(s32, s32, s32);

void text_show_message_clear_flag_pal(s32 a0) {
    s32 x = *(u32 *)(a0 + 0x68);

    text_show_message_at_moby(a0, x, x);
    *(u8 *)(a0 + 0x30) = 0xFF;
}

