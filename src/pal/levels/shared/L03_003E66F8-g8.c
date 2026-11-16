#include "names.h"
/* func_PAL_L03_003E66F8, the PAL copy of func_L03_003E21B0: the same C, where the four timers are
   words scaled to 50 Hz, the rates become 0.2f and 0.02f, and the limits 900 and 100. */

#include "common.h"
extern int g_hero_l03_mode, g_current_map_index, g_frame_counter;
extern int g_pad_held_flags __attribute__((nosda));
extern u8 g_subtitle_history[], g_sound_state[];
extern u16 g_infiltrator_ball_id[];
extern u8 *g_scene_switch_moby MACRO_ADDR;
extern float g_gadget_approach_value;
extern int g_puzzle_triggered_flag;
extern int g_path_puzzle_step_count __attribute__((sda)), g_path_puzzle_timer_max __attribute__((sda));
extern int g_path_puzzle_duration __attribute__((sda));
extern int g_path_puzzle_limit __attribute__((sda));
extern float g_path_puzzle_drain_rate __attribute__((sda));
extern void moby_set_state(u8 *, int, int);
extern float ApproachValue(float *, float, float);
extern void snd_stop_voice(int);
extern void path_puzzle_init_pal(u8 *), ComputePathPuzzleTurn(u8 *),UpdateChoicePath(u8 *),path_puzzle_animate_turn_pal(u8 *),path_puzzle_choose_next_node(u8 *),path_puzzle_update_glow_color_pal(u8 *),moby_set_flag_on(u8 *);
extern int path_puzzle_select_node_from_stick(u8 *);
extern int subtitle_request_voice_line_pal(int,int);
extern int PlayMobySound(int,int,u8 *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int snd_set_voice_pitch_bend(int,int);
extern int flag_set_first_pending(u8 *);
extern int request_end_slot(int,int),FastDecTimer(short *);
extern void moby_mark_spawned(u8 *);
extern void DrawPathPuzzleHud(u8 *);
extern void gfx_add_draw_callback_first(void (*)(u8 *),u8 *);

/* The signed halfword members preserve the record/global alias information
 * needed by the timer increment and clamp. */
typedef struct {
    u8 pad00[0x40];
    u8 choices[0x10];
    short current, next, unk_54, unk_56;
    float unk_58;
    short last, length, max_length, cursor, depth, pending, timer, active;
    u8 pad6C[0x10];
    int sound;
} PathRecord;

void path_puzzle_update_timed_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    PathRecord *path = (PathRecord *)vars;
    int i, voice;
    float ratio;
    u8 *time_record;

    if (g_hero_l03_mode != 7) {
        if (moby[0x20])
            moby_set_state(moby, 0, -1);
        return;
    }
    ApproachValue(&g_gadget_approach_value, 0.0f, 0.20000002f);
    g_puzzle_triggered_flag = 1;
    switch (moby[0x20]) {
    case 0:
        for (i = 0; i < 52; i++)
            snd_stop_voice(i);
        path_puzzle_init_pal(moby);
        *(u16 *)(moby + 0x34) |= 0x100;
        ComputePathPuzzleTurn(moby);
        moby_set_state(moby, g_current_map_index == 11 ? 1 : 3, -1);
        break;
    case 1:
        time_record = g_subtitle_history;
        if ((u32)(((s32)(g_frame_counter) * 5 + 2) / 6 - *(u32 *)(time_record + 0x73C)) > 900 ||
            !*(u32 *)(time_record + 0x73C))
            subtitle_request_voice_line_pal(0xA43, 0x9A);
        else if (*(u32 *)(time_record + 0x73C) < (u32)(((s32)(g_frame_counter) * 5 + 2) / 6))
            *(u32 *)(time_record + 0x73C) = ((s32)(g_frame_counter) * 5 + 2) / 6;
        moby_set_state(moby, 3, -1);
        break;
    case 2:
        if (!path->timer) {
            moby_set_state(moby, 4, -1);
            break;
        }
        if (path_puzzle_select_node_from_stick(moby)) {
            path->active = 1;
            UpdateChoicePath(moby);
            PlayMobySound(4, 0, moby);
            moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        path_puzzle_animate_turn_pal(moby);
        if (!path->unk_56)
            break;
        if (path->pending != -1) {
            *(u16 *)(vars + 0x52) = *(u16 *)(vars + 0x66);
            path->pending = -1;
        } else {
            path_puzzle_choose_next_node(moby);
        }
        /* 255 terminates the available-neighbor list. */
        {
            int choice = path->choices[0];
            choice ^= 255;
            if (choice == 0) {
                PlayMobySound(0, 0, moby);
            } else {
                voice = PlayMobySound(1, 0, moby);
                if (voice != -1) {
                    ratio = IntToFloat(path->length);
                    ratio /= IntToFloat(g_path_puzzle_step_count);
                    snd_set_voice_pitch_bend(voice, FloatToInt(ratio * 1024.0f) + 1024);
                }
            }
        }
        if (path->length > path->max_length) {
            path->max_length = *(u16 *)(vars + 0x5E);
            path->timer += ((s32)(g_path_puzzle_limit) * 5 + 2) / 6;
            if (path->timer > ((s32)(g_path_puzzle_timer_max) * 5 + 2) / 6)
                path->timer = ((s32)(g_path_puzzle_timer_max) * 5 + 2) / 6;
        }
        if (path->length == g_path_puzzle_step_count) {
            PlayMobySound(5, 0, moby);
            moby_set_state(moby, 5, -1);
        } else {
            moby_set_state(moby, 2, -1);
        }
        break;
    case 4:
        if (path->unk_56) {
            if (path->last != path->current) {
                *(u16 *)(vars + 0x52) = *(u16 *)(vars + 0x5C);
                UpdateChoicePath(moby);
                PlayMobySound(2, 0, moby);
            } else {
                path->timer = ((s32)(g_path_puzzle_duration) * 5 + 2) / 6;
                path->active = 0;
                path->max_length = 0;
                moby_set_state(moby, 2, -1);
            }
        } else {
            path_puzzle_animate_turn_pal(moby);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby))
            *(u16 *)(moby + 0x96) = 100;
        if (!*(u16 *)(moby + 0x96)) {
            g_infiltrator_ball_id[0] = 65535;
            moby_set_flag_on(g_scene_switch_moby);
            goto exit;
        } else {
            --*(u16 *)(moby + 0x96);
        }
        break;
    }
    if (g_pad_held_flags & 16) {
        if (moby[0x20] == 5)
            moby_set_flag_on(g_scene_switch_moby);
    exit:
        request_end_slot(0, 0);
        moby_mark_spawned(moby);
        return;
    }
    if (moby[0x20] != 5 && path->active)
        FastDecTimer(&path->timer);
    if (path->active && path->timer) {
        u8 *sound_slot = g_sound_state + *(int *)(vars + 0x7C) * 112;
        if (*(u8 **)(sound_slot + 0x88) != moby || !sound_slot[0x74])
            *(int *)(vars + 0x7C) = PlayMobySound(3, 4, moby);
    } else {
        int handle = *(int *)(vars + 0x7C);
        if (handle != -1) {
            int offset = handle * 112;
            u8 *sound_slot = g_sound_state + offset;
            if (*(u8 **)(sound_slot + 0x88) == moby && sound_slot[0x74])
                snd_stop_voice(handle);
        }
        *(int *)(vars + 0x7C) = -1;
    }
    path_puzzle_update_glow_color_pal(moby);
    *(float *)(vars + 0x58) -= g_path_puzzle_drain_rate * 0.020000001f;
    if (*(float *)(vars + 0x58) < -1.0f)
        *(float *)(vars + 0x58) += 1.0f;
    gfx_add_draw_callback_first(DrawPathPuzzleHud, moby);
}
