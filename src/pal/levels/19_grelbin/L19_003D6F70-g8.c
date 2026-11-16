#include "names.h"
/* func_PAL_L19_003D6F70, the PAL copy of func_L19_003D2E38: the same C at 50 Hz, with the callees'
   PAL names, the frame counts and tuning values scaled by 5/6 and the per-frame steps by 6/5. */
#include "common.h"

/* Incomplete SDA arrays preserve the measured absolute accesses in this G8 unit. */
extern int g_hero_l19_mode[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern unsigned int g_frame_counter[] __attribute__((sda));
typedef struct {
    char pad[0x73C];
    unsigned int time;
} GrelbinTimestamp;
extern GrelbinTimestamp g_subtitle_history;
extern char g_sound_state[];
extern int g_pad_held_flags NOT_SDA;
extern unsigned short g_infiltrator_ball_id NOT_SDA;
extern char g_infiltrator_ball_value[] __attribute__((sda));
extern int g_infiltrator_state_flags[] __attribute__((sda));
extern void *g_infiltrator_ball_mobys[] __attribute__((sda));
extern int g_ball_progress_max __attribute__((sda));
extern int g_ball_counter_max __attribute__((sda));
extern int g_ball_counter_reset __attribute__((sda));
extern int g_ball_counter_step __attribute__((sda));
extern float g_ball_decay_rate __attribute__((sda));

extern void moby_set_state(char *, int, int);
extern f32 ApproachValue(void *, float, float);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern s32 snd_set_voice_pitch_bend(int, int);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastDecTimer(void *);
extern void moby_mark_spawned(void *);
extern int flag_set_first_pending(void *);
extern int request_end_slot(int, int);
extern void gfx_add_draw_callback_first(void *, void *);
extern void DrawPathPuzzleHud_pal(void);
extern void moby_set_flag_on(void *);
extern void path_puzzle_init_pal(void *);
extern void ComputePathPuzzleTurn(void *);
extern void UpdateChoicePath(void *);
extern void path_puzzle_animate_turn_pal(void *);
extern void path_puzzle_choose_next_node(void *);
extern void path_puzzle_update_glow_color_pal(void *);
extern int path_puzzle_select_node_from_stick(void *);
extern int subtitle_request_voice_line_pal(int, int);

typedef struct {
    char pad[0x40];
    unsigned char kind;
    char gap[0xF];
    short field50, field52, field54, field56;
    float field58;
    short field5c, field5e, field60, field62, field64, field66, field68, field6a;
    char tail[0x10];
    int sound;
} GrelbinState;

void infiltrator_ball_update_pal(char *moby)
{
    GrelbinState *puzzle;
    int i, sound, kind;

    puzzle = *(GrelbinState **)(moby + 0x68);
    if (g_hero_l19_mode[0] != 7) {
        if (*(unsigned char *)(moby + 0x20))
            moby_set_state(moby, 0, -1);
        return;
    }
    ApproachValue(g_infiltrator_ball_value, 0.0f, 0.20000002f);
    g_infiltrator_state_flags[0] = 1;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        for (i = 0; i < 52; i++)
            snd_stop_voice(i);
        path_puzzle_init_pal(moby);
        *(unsigned short *)(moby + 0x34) |= 0x100;
        ComputePathPuzzleTurn(moby);
        moby_set_state(moby, g_current_map_index[0] == 11 ? 1 : 3, -1);
        break;
    case 1:
        if (((s32)g_frame_counter[0] * 5 + 2) / 6 - g_subtitle_history.time > 900 || !g_subtitle_history.time)
            subtitle_request_voice_line_pal(0xA43, 0x9A);
        else if (g_subtitle_history.time < ((s32)g_frame_counter[0] * 5 + 2) / 6)
            g_subtitle_history.time = ((s32)g_frame_counter[0] * 5 + 2) / 6;
        moby_set_state(moby, 3, -1);
        break;
    case 2:
        if (!puzzle->field68) {
            moby_set_state(moby, 4, -1);
            break;
        }
        if (path_puzzle_select_node_from_stick(moby)) {
            puzzle->field6a = 1;
            UpdateChoicePath(moby);
            PlayMobySound(4, 0, moby);
            moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        path_puzzle_animate_turn_pal(moby);
        if (puzzle->field56) {
            if (puzzle->field66 != -1) {
                puzzle->field52 = (unsigned short)puzzle->field66;
                puzzle->field66 = -1;
            } else {
                path_puzzle_choose_next_node(moby);
            }
            kind = puzzle->kind;
            kind ^= 255;
            if (kind == 0) {
                PlayMobySound(0, 0, moby);
            } else {
                sound = PlayMobySound(1, 0, moby);
                if (sound != -1)
                    snd_set_voice_pitch_bend(sound, FloatToInt(
                        IntToFloat(puzzle->field5e) / IntToFloat(g_ball_progress_max)
                        * 1024.0f) + 1024);
            }
            if (puzzle->field5e > puzzle->field60) {
                puzzle->field60 = (unsigned short)puzzle->field5e;
                puzzle->field68 = (unsigned short)puzzle->field68 + ((s32)g_ball_counter_step * 5 + 2) / 6;
                if (puzzle->field68 > ((s32)g_ball_counter_max * 5 + 2) / 6)
                    puzzle->field68 = ((s32)g_ball_counter_max * 5 + 2) / 6;
            }
            if (puzzle->field5e == g_ball_progress_max) {
                PlayMobySound(5, 0, moby);
                moby_set_state(moby, 5, -1);
            } else {
                moby_set_state(moby, 2, -1);
            }
        }
        break;
    case 4:
        if (puzzle->field56) {
            if (puzzle->field5c != puzzle->field50) {
                puzzle->field52 = (unsigned short)puzzle->field5c;
                UpdateChoicePath(moby);
                PlayMobySound(2, 0, moby);
            } else {
                puzzle->field68 = ((s32)g_ball_counter_reset * 5 + 2) / 6;
                puzzle->field6a = 0;
                puzzle->field60 = 0;
                moby_set_state(moby, 2, -1);
            }
        } else {
            path_puzzle_animate_turn_pal(moby);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby))
            *(unsigned short *)(moby + 0x96) = 100;
        if (!*(unsigned short *)(moby + 0x96)) {
            g_infiltrator_ball_id = 65535;
            moby_set_flag_on(g_infiltrator_ball_mobys[0]);
            goto destroy;
        }
        (*(unsigned short *)(moby + 0x96))--;
        break;
    }
    if (g_pad_held_flags & 16) {
        if (*(unsigned char *)(moby + 0x20) == 5)
            moby_set_flag_on(g_infiltrator_ball_mobys[0]);
    destroy:
        request_end_slot(0, 0);
        moby_mark_spawned(moby);
        return;
    }
    if (*(unsigned char *)(moby + 0x20) != 5 && puzzle->field6a)
        FastDecTimer(&puzzle->field68);
    if (puzzle->field6a && puzzle->field68) {
        char *s = g_sound_state + puzzle->sound * 0x70;
        if (*(char **)(s + 0x88) != moby || !*(unsigned char *)(s + 0x74))
            puzzle->sound = PlayMobySound(3, 4, moby);
    } else {
        if (puzzle->sound != -1) {
            char *s = g_sound_state + puzzle->sound * 0x70;
            if (*(char **)(s + 0x88) == moby && *(unsigned char *)(s + 0x74))
                snd_stop_voice(puzzle->sound);
        }
        puzzle->sound = -1;
    }
    path_puzzle_update_glow_color_pal(moby);
    puzzle->field58 -= g_ball_decay_rate * 0.020000001f;
    if (puzzle->field58 < -1.0f)
        puzzle->field58 += 1.0f;
    gfx_add_draw_callback_first(DrawPathPuzzleHud_pal, moby);
}
