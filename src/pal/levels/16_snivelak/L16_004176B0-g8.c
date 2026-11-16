#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
extern s32 g_snivelak_attach_rotation __attribute__((sda));
extern s32 g_snivelak_attach_offset __attribute__((sda));
extern s32 g_snivelak_voice_cue_count __attribute__((sda));
extern char g_hero_l16_moby[] __attribute__((nosda));
extern s32 FloatToInt(float);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 FastDecTimer(void *);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);
extern char g_snivelak_voice_cues[] __attribute__((nosda));
extern char g_str_snivelak_voice_debug_a[] __attribute__((nosda));
extern char g_str_snivelak_voice_debug_b[] __attribute__((nosda));
extern void STUB_printf(void *);
extern s32 snd_resume_music_stream(void);
extern int math_fast_float_d(void *);
extern void snd_play_unplayed_voice_line(void *, s32, s32);
extern s32 math_random_int_range(s32, s32);

/* Raises the level's one-shot flag while the counter is low, then hands the sub-object
   its tail record. */
void snivelak_play_voice_cues_pal(u8 *moby)
{
    u8 *state;
    u8 *hero;
    u8 *cues;

    state = *(u8 **)(moby + 0x68);
    hero = g_hero_l16_moby;
    if (*(s32 *)(hero + 0x2294) == 0x39) {
        if (*(s32 *)(hero + 0x1B8) == 0) {
            STUB_printf(g_str_snivelak_voice_debug_a);
            snd_play_unplayed_voice_line(moby, 0x1C, 0x20);
            g_snivelak_voice_cue_count++;
        }
    }
    cues = g_snivelak_voice_cues;
    if (*(s16 *)(cues + 0x72) == 3 && *(s16 *)(cues + 0x6C) < 0x1770) {
        STUB_printf(g_str_snivelak_voice_debug_b);
        snd_resume_music_stream();
    }
    math_fast_float_d(state + 0x350);
}
