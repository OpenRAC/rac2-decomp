#include "common.h"

extern u8 *g_moby_list_start __attribute__((sda));

/* The subtitle history (src/game/00289178.c): per record, its play count, the time it was last
   played and the levels it was played in (bit 31: played at all). */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;

extern void moby_set_state(void *, int, int);
extern int subtitle_request_voice_line_pal(int, int);

extern u8 g_hero_position[];
extern SubtitleHistory g_subtitle_history[];
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u32 g_frame_counter;
extern int g_current_map_index[] __attribute__((sda));
extern int g_game_mode NOT_SDA;
extern int IsPointInCuboid(void *, int);
extern int math_fast_float_d(void *);

/* func_PAL_L12_003EF838, the PAL copy of func_L12_003EB470: the same C, where func_00288E18
   becomes func_PAL_00289730, the 0x438 and 0x2A30 frame counts become 0x384 and 0x2328, and
   D_001A7390 is scaled to 50 Hz wherever it is read. Plays subtitle lines, each gated on its
   record in the subtitle history (the record index is the second argument of the call). */
void todano_subtitle_triggers_update_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 255;
        *(int *)(vars + 0x10) = -1;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, *(int *)vars) && *(int *)(g_hero_position + 0x540)
            && !g_subtitle_history[121].count)
            subtitle_request_voice_line_pal(0xA22, 121);
        if (IsPointInCuboid(g_hero_position, *(int *)(vars + 4)) && !g_item_owned_flags[0x33]) {
            if (g_subtitle_history[92].count) {
                if (((s32)g_frame_counter * 5 + 2) / 6 - g_subtitle_history[92].time > 0x384
                    || g_subtitle_history[92].time == 0)
                    subtitle_request_voice_line_pal(0xA05, 92);
                else if (g_subtitle_history[92].time < ((s32)g_frame_counter * 5 + 2) / 6)
                    g_subtitle_history[92].time = ((s32)g_frame_counter * 5 + 2) / 6;
            } else {
                if (g_subtitle_history[92].count < 65535)
                    g_subtitle_history[92].count++;
                if (g_subtitle_history[92].time < ((s32)g_frame_counter * 5 + 2) / 6)
                    g_subtitle_history[92].time = ((s32)g_frame_counter * 5 + 2) / 6;
                g_subtitle_history[92].levels = (g_subtitle_history[92].levels | (1u << g_current_map_index[0])) | 0x80000000u;
            }
        }
        if (IsPointInCuboid(g_hero_position, *(int *)(vars + 8))) {
            u8 *guide_moby = g_moby_list_start + (*(int *)(vars + 0xC) << 8);

            if (guide_moby && *(s16 *)(guide_moby + 0xAA) == 0xFB8 && guide_moby[0x20] != 254 && guide_moby[0x20] != 253) {
                if (*(int *)(vars + 0x10) < 0)
                    *(int *)(vars + 0x10) = 0x2328;
                else if (!*(int *)(vars + 0x10)) {
                    u32 seen = g_subtitle_history[93].levels & (1 << g_current_map_index[0]);

                    if (!seen)
                        subtitle_request_voice_line_pal(0xA06, 93);
                }
            }
        }
        if (g_item_owned_flags[7] && g_game_mode != 0x6F) {
            u32 seen = g_subtitle_history[127].levels & (1 << g_current_map_index[0]);

            if (!seen)
                subtitle_request_voice_line_pal(0xA28, 127);
        }
        if (*(int *)(vars + 0x10) >= 0)
            math_fast_float_d(vars + 0x10);
        break;
    }
}
