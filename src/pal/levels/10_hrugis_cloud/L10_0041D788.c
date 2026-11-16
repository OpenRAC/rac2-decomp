#include "include_asm.h"
#include "names.h"


typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;
extern u32 *func_0037BA88(u8 *arg0);
extern s32 func_003351C0(s32 mode);
extern s32 func_003737B8(s32 a, s32 b, u8 *c, s32 d);
extern void func_0037BD88(u8 *arg0, u32 flags, s32 a, s32 b, s32 c, s32 d, s32 e,
                          f32 f0, f32 f1, f32 f2, f32 f3);
extern f32 func_00335320(void);
extern u8 *func_0037B670(u8 *arg0);
extern s32 func_003062A0(u8 *a0);
extern s32 func_0037D390(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_00335200(s32 a0, s32 a1);
extern f32 func_00309138(f32 f12);
extern f32 func_00309120(f32 f12);
extern void hrugis_start_timed_effect(u8 *arg0);
extern s32 moby_process_collision_hit(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 snd_play_from_class_bank(s32 index, s32 value, u8 *object, s32 kind);
extern s32 func_0037D6E0(u8 *a0);
extern u8 *g_unused_pointer_table[];
extern u8 *g_moby_pool_base;
extern u8 g_group_state_buffer[];
extern u8 g_effect_l10_record_table[];
extern u8 g_mission_state[];
extern u8 g_sound_state[];
extern s32 g_unused_sda_word_a __attribute__((sda));
extern s32 g_unused_sda_word_b __attribute__((sda));

/* arms one timed effect slot and records it in the state word, skipping out while the
   object is inactive */
void hrugis_start_timed_effect_pal(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *motion = (u8 *)func_0037BA88(moby);
    if (motion == 0) return;
    if (*(s32 *)(motion + 0x120) == 0) return;
    if (*(s32 *)(state + 0x268) != 0) return;
    func_0037BD88(moby, 0x60000080, 1, 0, 0, -1, 0, 0.8f, 2.0f, 1.0f, 1.3f);
    if (func_003351C0(3) != 0) {
        func_003737B8(1, 0, moby, 0xF8E);
    }
    *(s32 *)(state + 0x268) = 0x19;
}

