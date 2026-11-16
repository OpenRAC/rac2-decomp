#include "common.h"
extern int g_hero_l03_mode, g_current_map_index, g_frame_counter;
extern int g_pad_held_flags __attribute__((nosda));
extern u8 g_subtitle_history[], g_sound_state[];
extern u16 g_infiltrator_ball_id[];
extern u8 *g_scene_switch_moby MACRO_ADDR;
extern float g_gadget_approach_value;
extern int g_puzzle_triggered_flag;
extern int g_path_puzzle_step_count __attribute__((sda)), g_path_puzzle_timer_max __attribute__((sda));
extern u16 g_path_puzzle_duration __attribute__((sda));
extern u16 g_path_puzzle_limit __attribute__((sda));
extern float g_path_puzzle_drain_rate __attribute__((sda));
extern void moby_set_state(u8 *, int, int);
extern float ApproachValue(float *, float, float);
extern void snd_stop_voice(int);
extern void InitializePathPuzzle(u8 *), ComputePathPuzzleTurn(u8 *),UpdateChoicePath(u8 *),path_puzzle_animate_turn(u8 *),path_puzzle_choose_next_node(u8 *),path_puzzle_update_glow_color(u8 *),moby_set_flag_on(u8 *);
extern int path_puzzle_select_node_from_stick(u8 *);
extern int subtitle_request_voice_line(int,int);
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
    short current, next, f54, f56;
    float f58;
    short last, length, maximumLength, cursor, depth, pending, timer, active;
    u8 pad6C[0x10];
    int sound;
} PathRecord;

/* Updates the Infiltrator Ball (moby class 2856): runs the timed path puzzle through its states. */
void UpdateTimedPathPuzzle(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    PathRecord *path = (PathRecord *)vars;
    int i, sound_handle;
    float ratio;
    u8 *timeRecord;

    if (g_hero_l03_mode != 7) {
        if (moby[0x20])
            moby_set_state(moby, 0, -1);
        return;
    }
    ApproachValue(&g_gadget_approach_value, 0.0f, 0.16666667f);
    g_puzzle_triggered_flag = 1;
    switch (moby[0x20]) {
    case 0:
        for (i = 0; i < 52; i++)
            snd_stop_voice(i);
        InitializePathPuzzle(moby);
        *(u16 *)(moby + 0x34) |= 0x100;
        ComputePathPuzzleTurn(moby);
        moby_set_state(moby, g_current_map_index == 11 ? 1 : 3, -1);
        break;
    case 1:
        timeRecord = g_subtitle_history;
        if ((u32)(g_frame_counter - *(u32 *)(timeRecord + 0x73C)) > 1080 ||
            !*(u32 *)(timeRecord + 0x73C))
            subtitle_request_voice_line(0xA43, 0x9A);
        else if (*(u32 *)(timeRecord + 0x73C) < (u32)g_frame_counter)
            *(u32 *)(timeRecord + 0x73C) = g_frame_counter;
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
        path_puzzle_animate_turn(moby);
        if (!path->f56)
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
                sound_handle = PlayMobySound(1, 0, moby);
                if (sound_handle != -1) {
                    ratio = IntToFloat(path->length);
                    ratio /= IntToFloat(g_path_puzzle_step_count);
                    snd_set_voice_pitch_bend(sound_handle, FloatToInt(ratio * 1024.0f) + 1024);
                }
            }
        }
        if (path->length > path->maximumLength) {
            path->maximumLength = *(u16 *)(vars + 0x5E);
            path->timer += g_path_puzzle_limit;
            if (path->timer > g_path_puzzle_timer_max)
                path->timer = g_path_puzzle_timer_max;
        }
        if (path->length == g_path_puzzle_step_count) {
            PlayMobySound(5, 0, moby);
            moby_set_state(moby, 5, -1);
        } else {
            moby_set_state(moby, 2, -1);
        }
        break;
    case 4:
        if (path->f56) {
            if (path->last != path->current) {
                *(u16 *)(vars + 0x52) = *(u16 *)(vars + 0x5C);
                UpdateChoicePath(moby);
                PlayMobySound(2, 0, moby);
            } else {
                path->active = 0;
                path->maximumLength = 0;
                path->timer = g_path_puzzle_duration;
                moby_set_state(moby, 2, -1);
            }
        } else {
            path_puzzle_animate_turn(moby);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby))
            *(u16 *)(moby + 0x96) = 120;
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
    path_puzzle_update_glow_color(moby);
    *(float *)(vars + 0x58) -= g_path_puzzle_drain_rate * 0.016666667f;
    if (*(float *)(vars + 0x58) < -1.0f)
        *(float *)(vars + 0x58) += 1.0f;
    gfx_add_draw_callback_first(DrawPathPuzzleHud, moby);
}
