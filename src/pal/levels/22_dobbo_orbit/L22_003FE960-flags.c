#include "include_asm.h"

#include "common.h"
extern void *part_find_owned_effect_slot(void *a0, s32 a1, s32 a2);
extern s32 math_random_int_below(s32 a0);
extern s32 snd_play_from_class_bank(s32 a0, s32 a1, char *a2, s32 a3);
extern void part_spawn_explosion_with_sparks_pal(u8 *a0, void *a1, s32 a2, f32 f12, f32 f13);
extern s32 PlayMobySound(s32 a0, s32 a1, char *a2);
extern void part_spawn_masked_debris_pal(char *a0, s32 a1, f32 *a2, u8 a3, f32 f12, f32 f13, f32 f14,
                        f32 f15);
extern void moby_mark_spawned(char *a0);
extern int math_random_int_below(int);
extern u8 *g_hero_moby;
extern s32 g_trigger_event_list_head __attribute__((sda));
extern u8 g_unused_level_byte __attribute__((sda));
extern s32 g_trigger_event_flag __attribute__((sda));
extern s32 g_unused_l22_level_word __attribute__((sda));
extern s32 func_2F36F0(s32);
extern void vec_scale_to_length(void *, void *, f32);
extern f32 func_2F4AD0(f32, f32);
extern void text_show_message_with_sound(s32, s32, s32);
extern u8 *g_space_ship_owner_moby[] __attribute__((sda));
extern f32 g_space_ship_param_y __attribute__((sda));
extern u8 *g_hero_moby;
extern void moby_mark_spawned(char *a0);

/* Shows a text message with a sound at the object and starts its effect. Does nothing if the object has no target. */
void text_show_message_with_sound_pal(s32 moby_addr, s32 unused1, s32 unused2)
{
    char *moby = (char *)moby_addr;
    char *target = part_find_owned_effect_slot(moby, -1, 0);
    char buf[0x10];

    if (target == 0)
        return;
    snd_play_from_class_bank(math_random_int_below(3) + 0xC, 0, moby, 0xE0B);
    part_spawn_explosion_with_sparks_pal((u8 *)moby, moby + 0x10, -1, 2.0f, 13.0f);
    PlayMobySound(0, 0, moby);
    vec_scale_to_length(buf, target + 0x10, 0.3f);
    part_spawn_masked_debris_pal(moby, 3, (f32 *)buf, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(moby);
}
