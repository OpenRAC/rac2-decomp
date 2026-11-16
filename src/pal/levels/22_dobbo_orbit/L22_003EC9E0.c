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

/* Shows the message effect for this object and clears one of its flags. */
void text_show_message_clear_flag_pal(s32 moby) {
    s32 vars_ptr = *(u32 *)(moby + 0x68);

    text_show_message_at_moby(moby, vars_ptr, vars_ptr);
    *(u8 *)(moby + 0x30) = 0xFF;
}

