#include "common.h"

extern u8 g_hero_state[];
extern u8 g_hero_position[];
extern u8 g_progress_statistics[];
extern u8 D_001395B8[];
extern u32 D_001A7390[] __attribute__((sda));
extern u8 D_001A7A60[] __attribute__((sda));
extern s32 D_001A903C[] __attribute__((sda));
extern s32 D_0018CC18;
extern s32 IsPointInCuboid(void *a0, s32 a1);
extern void snd_play_from_global_bank(s32 a0, s32 a1, s32 a2);
extern void value_set_entry_by_index(s32 a0, s32 a1);
extern void subtitle_request_voice_line(s32 a0, s32 a1);

/* Watches the player entering two trigger boxes and, on the second, unlocks a story event with a sound. Also plays a one-time hint when the player enters the main box. */
void trigger_hint_update(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    s16 phase;
    u8 *hero;
    u8 *timers;
    u8 *counters;

    if (moby[0x20] == 0) {
        moby[0x30] = 0xFF;
        *(s16 *)(vars + 0xC) = 0;
        moby[0x20] = 1;
    }
    if (moby[0x20] != 1)
        return;
    phase = *(s16 *)(vars + 0xE);
    switch (phase) {
    case 0:
        if (IsPointInCuboid(g_hero_position, *(s32 *)(vars + 4)) != 0 && *(s32 *)(g_hero_position + 0x221C) == 0xF)
            *(s16 *)(vars + 0xE) = 1;
        break;
    case 1:
        hero = g_hero_state;
        if (*(s32 *)(hero + 0x2294) == 0x3E) {
            *(s16 *)(vars + 0xE) = 0;
        } else if (IsPointInCuboid(hero + 0x80, *(s32 *)(vars + 8)) != 0 && D_001A7A60[4] == 0) {
            D_001A7A60[4] = 1;
            snd_play_from_global_bank(1, 0, 0);
            value_set_entry_by_index(0x1233, -1);
            D_001A903C[0] = 1;
        }
        break;
    }
    if (IsPointInCuboid(g_hero_position, *(s32 *)vars) == 0)
        return;
    timers = g_progress_statistics;
    if (*(u16 *)(timers + 0x1BC) != 0 && !(D_001A7390[0] - *(u32 *)(timers + 0x1C0) > 0x69780))
        return;
    counters = D_001395B8;
    if (counters[0x7E] < 2 && *(s16 *)(vars + 0xC) == 0) {
        if (D_0018CC18 >= 0)
            subtitle_request_voice_line(0x9E3, 0x3A);
        counters[0x7E] = counters[0x7E] + 1;
        *(s16 *)(vars + 0xC) = 1;
    }
}
