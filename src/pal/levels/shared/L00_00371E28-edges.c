#include "include_asm.h"

#include "common.h"
typedef struct { char prefix[0x3C]; int abort; } SequencePlayback;
extern SequencePlayback D_L00_001BEFC0;
extern float D_L00_001B18E0 __attribute__((sda));
extern int D_001A7A00[] __attribute__((sda));
extern int D_001A7478 __attribute__((sda)), g_current_map_index __attribute__((sda)), g_is_pal_video __attribute__((sda));
typedef struct { char prefix[0x1A0]; union { unsigned long long all; struct { unsigned int low, high; } word; } buttons; } SequenceInput;
extern SequenceInput g_pad_state;
extern short D_001A63AC;
extern void req_flush_queue(void *);
extern int request_end_slot(int, int);
extern void func_PAL_L00_002FE328(void);
extern void moby_update_visible_objects(void);
extern void snd_run_callbacks(void);
extern void func_PAL_L00_002A6CB8(void);
extern float ApproachValue(float *, float, float);
extern int snd_resume_music_stream(void);
extern int req_launch_queued(void *);
extern void load_relocate_world_object_parts(void);
extern int func_PAL_002F6A48(void);
extern void update_moby_animation_state(unsigned char *);
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void func_002A0F48(unsigned char *);
extern void gfx_register_overlay_draw_callback(void (*)(void *), void *);
extern void func_PAL_002EDA88(void *);
extern void moby_update_ground_check(void *);
extern void func_PAL_L00_002D5380(void *, int);
extern void func_PAL_L00_002A6FE0(void *);
extern void func_PAL_L00_002FE768(void);
extern void UpdateLightingEnvironment(void);
extern void gfx_compute_light_direction(void);
extern int D_L00_001BCAC0[];
extern s16 func_PAL_002B8898(int);
extern void game_reset_frame_counters(void);
extern void part_update_all(void);
extern int func_PAL_L00_003062B0(int);
extern s32 func_PAL_002E5898(void);
extern void func_PAL_002F6208(void);
typedef struct {
    char prefix[0x34];
    int time, frame, chunk;
    short end_time, pad42, count, pad46, fade_time;
    char pad4a[14];
    int done;
    char pad5c[0x130];
    unsigned char *actors[0];
} SequenceState;

void func_PAL_L00_00372EA8(void) {
    float first[4];
    float second[4];
    int ended;
    unsigned char *object;
    char *path;
    int abort;
    int threshold;
    int complete;
    int i;
    short id;
    if (((SequenceState *)D_L00_001BCAC0)->done) return;
    if (((SequenceState *)D_L00_001BCAC0)->end_time == 0) {
        req_flush_queue(&D_L00_001BEFC0);
        ((SequenceState *)D_L00_001BCAC0)->done = 1;
        request_end_slot(0, 0);
        return;
    }
    game_reset_frame_counters();
    func_PAL_L00_002FE328();
    moby_update_visible_objects();
    snd_run_callbacks();
    func_PAL_L00_002A6CB8();
    part_update_all();
    { int t; ++((SequenceState *)D_L00_001BCAC0)->frame; t = ++((SequenceState *)D_L00_001BCAC0)->time; if (t < 15) {
        ApproachValue(&D_L00_001B18E0, 0.0f, 0.20000002f);
        if (D_L00_001B18E0 > 1.0f) D_L00_001B18E0 = 1.0f;
    }
    }
    if (((SequenceState *)D_L00_001BCAC0)->fade_time <= ((SequenceState *)D_L00_001BCAC0)->time) snd_resume_music_stream();
    ended = ((SequenceState *)D_L00_001BCAC0)->time >= ((SequenceState *)D_L00_001BCAC0)->end_time;
    abort = 0;
    if (((SequenceState *)D_L00_001BCAC0)->time > 14 && D_L00_001B18E0 == 0.0f) {
        if (!(((D_001A7A00[2] & 0xFFFF0000) == 0) && D_001A7478 == 0 && g_current_map_index > 0) && (g_pad_state.buttons.word.high & 0x800)) abort = 1;
        else { unsigned long long v = (g_pad_state.buttons.all & 0x8000000000FULL) ^ 0x8000000000FULL; abort = 1; if (v) abort = 0; }
    }
    if (abort) {
        D_L00_001BEFC0.abort = 1;
        req_flush_queue(&D_L00_001BEFC0);
        ((SequenceState *)D_L00_001BCAC0)->done = 1;
        request_end_slot(0, 0);
    } else {
        if (ended) {
            ((SequenceState *)D_L00_001BCAC0)->done = 1;
            if (!req_launch_queued(&D_L00_001BEFC0)) request_end_slot(0, 0);
        } else {
            threshold = g_is_pal_video ? 80 : 96;
            if (((SequenceState *)D_L00_001BCAC0)->frame >= threshold) {
                ++((SequenceState *)D_L00_001BCAC0)->chunk;
                if (D_001A63AC) func_PAL_002B8898(1);
                load_relocate_world_object_parts();
                func_PAL_L00_003062B0(((SequenceState *)D_L00_001BCAC0)->chunk + 1);
            }
            complete = func_PAL_002F6A48();
            for (i = 0; i < ((SequenceState *)D_L00_001BCAC0)->count; i++) {
                object = ((SequenceState *)D_L00_001BCAC0)->actors[i];
                { int frame = ((SequenceState *)D_L00_001BCAC0)->frame >> 1;
                object[0x41] = frame + 1;
                object[0x40] = frame; }
                update_moby_animation_state(object);
                *(float *)(object + 0x44) = IntToFloat(((SequenceState *)D_L00_001BCAC0)->frame & 1) * 0.5f;
                if (complete && (((SequenceState *)D_L00_001BCAC0)->frame & 1)) *(float *)(object + 0x44) = 1.0f;
                path = *(char **)(object + 0x68);
                FastVecScale(first, path + object[0x40] * 16, 1.0f - *(float *)(object + 0x44));
                FastVecScale(second, path + object[0x41] * 16, *(float *)(object + 0x44));
                FastVecAdd(object + 0x10, first, second);
                object[0x61] = 0xFF;
                func_002A0F48(object);
                if (*(short *)(object + 0xAA) == 0xD54) gfx_register_overlay_draw_callback(func_PAL_002EDA88, object);
                if (object[0x6F]) moby_update_ground_check(object);
                id = *(short *)(object + 0xAA);
                if (id == 0 || id == 0xF6B) func_PAL_L00_002D5380(object, 0);
                id = *(short *)(object + 0xAA);
                if (id == 10 || id == 0x1159 || id == 0x57 || id == 0xD6B) func_PAL_L00_002A6FE0(object);
            }
        }
    }
    func_PAL_L00_002FE768();
    func_PAL_002E5898();
    UpdateLightingEnvironment();
    gfx_compute_light_direction();
    func_PAL_002F6208();
}
