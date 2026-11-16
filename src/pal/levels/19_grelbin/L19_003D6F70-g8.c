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
extern void func_PAL_L03_003E6CA8(void *);
extern void ComputePathPuzzleTurn(void *);
extern void UpdateChoicePath(void *);
extern void path_puzzle_animate_turn_pal(void *);
extern void path_puzzle_choose_next_node(void *);
extern void path_puzzle_update_glow_color_pal(void *);
extern int path_puzzle_select_node_from_stick(void *);
extern int func_PAL_00289730(int, int);

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

void func_PAL_L19_003D6F70(char *m)
{
    GrelbinState *p;
    int i, sound, kind;

    p = *(GrelbinState **)(m + 0x68);
    if (g_hero_l19_mode[0] != 7) {
        if (*(unsigned char *)(m + 0x20))
            moby_set_state(m, 0, -1);
        return;
    }
    ApproachValue(g_infiltrator_ball_value, 0.0f, 0.20000002f);
    g_infiltrator_state_flags[0] = 1;
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        for (i = 0; i < 52; i++)
            snd_stop_voice(i);
        func_PAL_L03_003E6CA8(m);
        *(unsigned short *)(m + 0x34) |= 0x100;
        ComputePathPuzzleTurn(m);
        moby_set_state(m, g_current_map_index[0] == 11 ? 1 : 3, -1);
        break;
    case 1:
        if (((s32)g_frame_counter[0] * 5 + 2) / 6 - g_subtitle_history.time > 900 || !g_subtitle_history.time)
            func_PAL_00289730(0xA43, 0x9A);
        else if (g_subtitle_history.time < ((s32)g_frame_counter[0] * 5 + 2) / 6)
            g_subtitle_history.time = ((s32)g_frame_counter[0] * 5 + 2) / 6;
        moby_set_state(m, 3, -1);
        break;
    case 2:
        if (!p->field68) {
            moby_set_state(m, 4, -1);
            break;
        }
        if (path_puzzle_select_node_from_stick(m)) {
            p->field6a = 1;
            UpdateChoicePath(m);
            PlayMobySound(4, 0, m);
            moby_set_state(m, 3, -1);
        }
        break;
    case 3:
        path_puzzle_animate_turn_pal(m);
        if (p->field56) {
            if (p->field66 != -1) {
                p->field52 = (unsigned short)p->field66;
                p->field66 = -1;
            } else {
                path_puzzle_choose_next_node(m);
            }
            kind = p->kind;
            kind ^= 255;
            if (kind == 0) {
                PlayMobySound(0, 0, m);
            } else {
                sound = PlayMobySound(1, 0, m);
                if (sound != -1)
                    snd_set_voice_pitch_bend(sound, FloatToInt(
                        IntToFloat(p->field5e) / IntToFloat(g_ball_progress_max)
                        * 1024.0f) + 1024);
            }
            if (p->field5e > p->field60) {
                p->field60 = (unsigned short)p->field5e;
                p->field68 = (unsigned short)p->field68 + ((s32)g_ball_counter_step * 5 + 2) / 6;
                if (p->field68 > ((s32)g_ball_counter_max * 5 + 2) / 6)
                    p->field68 = ((s32)g_ball_counter_max * 5 + 2) / 6;
            }
            if (p->field5e == g_ball_progress_max) {
                PlayMobySound(5, 0, m);
                moby_set_state(m, 5, -1);
            } else {
                moby_set_state(m, 2, -1);
            }
        }
        break;
    case 4:
        if (p->field56) {
            if (p->field5c != p->field50) {
                p->field52 = (unsigned short)p->field5c;
                UpdateChoicePath(m);
                PlayMobySound(2, 0, m);
            } else {
                p->field68 = ((s32)g_ball_counter_reset * 5 + 2) / 6;
                p->field6a = 0;
                p->field60 = 0;
                moby_set_state(m, 2, -1);
            }
        } else {
            path_puzzle_animate_turn_pal(m);
        }
        break;
    case 5:
        if (flag_set_first_pending(m))
            *(unsigned short *)(m + 0x96) = 100;
        if (!*(unsigned short *)(m + 0x96)) {
            g_infiltrator_ball_id = 65535;
            moby_set_flag_on(g_infiltrator_ball_mobys[0]);
            goto destroy;
        }
        (*(unsigned short *)(m + 0x96))--;
        break;
    }
    if (g_pad_held_flags & 16) {
        if (*(unsigned char *)(m + 0x20) == 5)
            moby_set_flag_on(g_infiltrator_ball_mobys[0]);
    destroy:
        request_end_slot(0, 0);
        moby_mark_spawned(m);
        return;
    }
    if (*(unsigned char *)(m + 0x20) != 5 && p->field6a)
        FastDecTimer(&p->field68);
    if (p->field6a && p->field68) {
        char *s = g_sound_state + p->sound * 0x70;
        if (*(char **)(s + 0x88) != m || !*(unsigned char *)(s + 0x74))
            p->sound = PlayMobySound(3, 4, m);
    } else {
        if (p->sound != -1) {
            char *s = g_sound_state + p->sound * 0x70;
            if (*(char **)(s + 0x88) == m && *(unsigned char *)(s + 0x74))
                snd_stop_voice(p->sound);
        }
        p->sound = -1;
    }
    path_puzzle_update_glow_color_pal(m);
    p->field58 -= g_ball_decay_rate * 0.020000001f;
    if (p->field58 < -1.0f)
        p->field58 += 1.0f;
    gfx_add_draw_callback_first(DrawPathPuzzleHud_pal, m);
}
