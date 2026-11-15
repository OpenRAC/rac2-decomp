#include "include_asm.h"

#include "common.h"
extern void *part_find_owned_effect_slot(void *a0, s32 a1, s32 a2);
extern s32 math_random_int_below(s32 a0);
extern s32 snd_play_from_class_bank(s32 a0, s32 a1, char *a2, s32 a3);
extern void func_PAL_002AD288(u8 *a0, void *a1, s32 a2, f32 f12, f32 f13);
extern s32 PlayMobySound(s32 a0, s32 a1, char *a2);
extern void func_PAL_002B15D8(char *a0, s32 a1, f32 *a2, u8 a3, f32 f12, f32 f13, f32 f14,
                        f32 f15);
extern void moby_mark_spawned(char *a0);
extern int math_random_int_below(int);
extern u8 *g_hero_moby;
extern s32 D_L22_001B2128 __attribute__((sda));
extern u8 D_L22_001A7A78 __attribute__((sda));
extern s32 D_L22_001A903C __attribute__((sda));
extern s32 D_L22_0018B6A8 __attribute__((sda));
extern s32 func_2F36F0(s32);
extern void vec_scale_to_length(void *, void *, f32);
extern f32 func_2F4AD0(f32, f32);
extern void text_show_message_with_sound(s32, s32, s32);
extern u8 *D_L22_001AF314[] __attribute__((sda));
extern f32 D_L22_001B2A98 __attribute__((sda));
extern u8 *g_hero_moby;
extern void moby_mark_spawned(char *a0);

void func_PAL_L22_003FE960(s32 arg, s32 unused1, s32 unused2)
{
    char *a0 = (char *)arg;
    char *s1 = part_find_owned_effect_slot(a0, -1, 0);
    char buf[0x10];

    if (s1 == 0)
        return;
    snd_play_from_class_bank(math_random_int_below(3) + 0xC, 0, a0, 0xE0B);
    func_PAL_002AD288((u8 *)a0, a0 + 0x10, -1, 2.0f, 13.0f);
    PlayMobySound(0, 0, a0);
    vec_scale_to_length(buf, s1 + 0x10, 0.3f);
    func_PAL_002B15D8(a0, 3, (f32 *)buf, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(a0);
}
