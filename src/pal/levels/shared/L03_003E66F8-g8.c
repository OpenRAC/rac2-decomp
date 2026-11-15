#include "names.h"
/* func_PAL_L03_003E66F8, the PAL copy of func_L03_003E21B0: the same C, where the four timers are
   words scaled to 50 Hz, the rates become 0.2f and 0.02f, and the limits 900 and 100. */

#include "common.h"
extern int D_L03_001A8F00, g_current_map_index, D_001A7390;
extern int D_00138324 __attribute__((nosda));
extern u8 g_subtitle_history[], g_sound_state[];
extern u16 D_0018D090[];
extern u8 *D_L03_001AC040 MACRO_ADDR;
extern float D_001B2464;
extern int D_L03_001B2768;
extern int D_L03_001B0B50 __attribute__((sda)), D_L03_001B0B58 __attribute__((sda));
extern int D_L03_001B0B5C __attribute__((sda));
extern int D_L03_001B0B60 __attribute__((sda));
extern float D_L03_001B0B74 __attribute__((sda));
extern void moby_set_state(u8 *, int, int);
extern float ApproachValue(float *, float, float);
extern void snd_stop_voice(int);
extern void func_PAL_L03_003E6CA8(u8 *), ComputePathPuzzleTurn(u8 *),UpdateChoicePath(u8 *),func_PAL_L03_003E7C78(u8 *),path_puzzle_choose_next_node(u8 *),func_PAL_L03_003E8B88(u8 *),moby_set_flag_on(u8 *);
extern int path_puzzle_select_node_from_stick(u8 *);
extern int func_PAL_00289730(int,int);
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

void func_PAL_L03_003E66F8(u8 *p) {
    u8 *q = *(u8 **)(p + 0x68);
    PathRecord *path = (PathRecord *)q;
    int i, h;
    float f;
    u8 *timeRecord;

    if (D_L03_001A8F00 != 7) {
        if (p[0x20])
            moby_set_state(p, 0, -1);
        return;
    }
    ApproachValue(&D_001B2464, 0.0f, 0.20000002f);
    D_L03_001B2768 = 1;
    switch (p[0x20]) {
    case 0:
        for (i = 0; i < 52; i++)
            snd_stop_voice(i);
        func_PAL_L03_003E6CA8(p);
        *(u16 *)(p + 0x34) |= 0x100;
        ComputePathPuzzleTurn(p);
        moby_set_state(p, g_current_map_index == 11 ? 1 : 3, -1);
        break;
    case 1:
        timeRecord = g_subtitle_history;
        if ((u32)(((s32)(D_001A7390) * 5 + 2) / 6 - *(u32 *)(timeRecord + 0x73C)) > 900 ||
            !*(u32 *)(timeRecord + 0x73C))
            func_PAL_00289730(0xA43, 0x9A);
        else if (*(u32 *)(timeRecord + 0x73C) < (u32)(((s32)(D_001A7390) * 5 + 2) / 6))
            *(u32 *)(timeRecord + 0x73C) = ((s32)(D_001A7390) * 5 + 2) / 6;
        moby_set_state(p, 3, -1);
        break;
    case 2:
        if (!path->timer) {
            moby_set_state(p, 4, -1);
            break;
        }
        if (path_puzzle_select_node_from_stick(p)) {
            path->active = 1;
            UpdateChoicePath(p);
            PlayMobySound(4, 0, p);
            moby_set_state(p, 3, -1);
        }
        break;
    case 3:
        func_PAL_L03_003E7C78(p);
        if (!path->f56)
            break;
        if (path->pending != -1) {
            *(u16 *)(q + 0x52) = *(u16 *)(q + 0x66);
            path->pending = -1;
        } else {
            path_puzzle_choose_next_node(p);
        }
        /* 255 terminates the available-neighbor list. */
        {
            int choice = path->choices[0];
            choice ^= 255;
            if (choice == 0) {
                PlayMobySound(0, 0, p);
            } else {
                h = PlayMobySound(1, 0, p);
                if (h != -1) {
                    f = IntToFloat(path->length);
                    f /= IntToFloat(D_L03_001B0B50);
                    snd_set_voice_pitch_bend(h, FloatToInt(f * 1024.0f) + 1024);
                }
            }
        }
        if (path->length > path->maximumLength) {
            path->maximumLength = *(u16 *)(q + 0x5E);
            path->timer += ((s32)(D_L03_001B0B60) * 5 + 2) / 6;
            if (path->timer > ((s32)(D_L03_001B0B58) * 5 + 2) / 6)
                path->timer = ((s32)(D_L03_001B0B58) * 5 + 2) / 6;
        }
        if (path->length == D_L03_001B0B50) {
            PlayMobySound(5, 0, p);
            moby_set_state(p, 5, -1);
        } else {
            moby_set_state(p, 2, -1);
        }
        break;
    case 4:
        if (path->f56) {
            if (path->last != path->current) {
                *(u16 *)(q + 0x52) = *(u16 *)(q + 0x5C);
                UpdateChoicePath(p);
                PlayMobySound(2, 0, p);
            } else {
                path->timer = ((s32)(D_L03_001B0B5C) * 5 + 2) / 6;
                path->active = 0;
                path->maximumLength = 0;
                moby_set_state(p, 2, -1);
            }
        } else {
            func_PAL_L03_003E7C78(p);
        }
        break;
    case 5:
        if (flag_set_first_pending(p))
            *(u16 *)(p + 0x96) = 100;
        if (!*(u16 *)(p + 0x96)) {
            D_0018D090[0] = 65535;
            moby_set_flag_on(D_L03_001AC040);
            goto exit;
        } else {
            --*(u16 *)(p + 0x96);
        }
        break;
    }
    if (D_00138324 & 16) {
        if (p[0x20] == 5)
            moby_set_flag_on(D_L03_001AC040);
    exit:
        request_end_slot(0, 0);
        moby_mark_spawned(p);
        return;
    }
    if (p[0x20] != 5 && path->active)
        FastDecTimer(&path->timer);
    if (path->active && path->timer) {
        u8 *r = g_sound_state + *(int *)(q + 0x7C) * 112;
        if (*(u8 **)(r + 0x88) != p || !r[0x74])
            *(int *)(q + 0x7C) = PlayMobySound(3, 4, p);
    } else {
        int handle = *(int *)(q + 0x7C);
        if (handle != -1) {
            int offset = handle * 112;
            u8 *r = g_sound_state + offset;
            if (*(u8 **)(r + 0x88) == p && r[0x74])
                snd_stop_voice(handle);
        }
        *(int *)(q + 0x7C) = -1;
    }
    func_PAL_L03_003E8B88(p);
    *(float *)(q + 0x58) -= D_L03_001B0B74 * 0.020000001f;
    if (*(float *)(q + 0x58) < -1.0f)
        *(float *)(q + 0x58) += 1.0f;
    gfx_add_draw_callback_first(DrawPathPuzzleHud, p);
}
