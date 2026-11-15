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
extern void tutorial_probe_points_update(void);
extern void moby_update_visible_objects(void);
extern void snd_run_callbacks(void);
extern void hero_l00_update_frame_2(void);
extern float ApproachValue(float *, float, float);
extern int snd_resume_music_stream(void);
extern int req_launch_queued(void *);

extern void load_relocate_world_object_parts(void);
extern int cutscene_apply_camera_key(void);
extern void update_moby_animation_state(unsigned char *);
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void func_002A0F48(unsigned char *);
extern void gfx_register_overlay_draw_callback(void (*)(void *), void *);
extern void render_environment_mapped_object(void *);
extern void moby_update_ground_check(void *);
extern void level_setup_glow_effects(void *, int);
extern void update_moby_pulsing_glow_effects(void *);
extern void tutorial_scene_objects_update(void);
extern void UpdateLightingEnvironment(void);
extern void gfx_compute_light_direction(void);

extern int D_L00_001BCAC0[];
extern void snd_pump_music_and_disc_read(int);
extern void game_reset_frame_counters(void);
extern void part_update_all(void);
extern int load_queue_level_data_chunk(int);
extern void UpdateSoundVoices(void);
extern void game_update_idle_frame_counters(void);

typedef struct {
    char prefix[0x34];
    int time, frame, chunk;
    short end_time, pad42, count, pad46, fade_time;
    char pad4a[14];
    int done;
    char pad5c[0x130];
    unsigned char *actors[0];
} SequenceState;

/* Plays one frame of a cutscene: moves the actors along their paths, fades in, and ends it on time or when the player skips. */
void cutscene_update_frame(void) {
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
    tutorial_probe_points_update();
    moby_update_visible_objects();
    snd_run_callbacks();
    hero_l00_update_frame_2();
    part_update_all();
    { int t; ++((SequenceState *)D_L00_001BCAC0)->frame; t = ++((SequenceState *)D_L00_001BCAC0)->time; if (t < 18) {
        ApproachValue(&D_L00_001B18E0, 0.0f, 0.16666667f);
        if (D_L00_001B18E0 > 1.0f) D_L00_001B18E0 = 1.0f;
    }
    }
    if (((SequenceState *)D_L00_001BCAC0)->fade_time <= ((SequenceState *)D_L00_001BCAC0)->time) snd_resume_music_stream();
    ended = ((SequenceState *)D_L00_001BCAC0)->time >= ((SequenceState *)D_L00_001BCAC0)->end_time;
    abort = 0;
    if (((SequenceState *)D_L00_001BCAC0)->time > 17 && D_L00_001B18E0 == 0.0f) {
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
                if (D_001A63AC) snd_pump_music_and_disc_read(1);
                load_relocate_world_object_parts();
                load_queue_level_data_chunk(((SequenceState *)D_L00_001BCAC0)->chunk + 1);
            }
            complete = cutscene_apply_camera_key();
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
                if (*(short *)(object + 0xAA) == 0xD54 /* moby class 3412 */) gfx_register_overlay_draw_callback(render_environment_mapped_object, object);
                if (object[0x6F]) moby_update_ground_check(object);
                id = *(short *)(object + 0xAA);
                if (id == 0 || id == 0xF6B /* moby class 3947 */) level_setup_glow_effects(object, 0);
                id = *(short *)(object + 0xAA);
                if (id == 10 || id == 0x1159 /* moby class 4441 */ || id == 0x57 /* Clank */ || id == 0xD6B /* moby class 3435 */) update_moby_pulsing_glow_effects(object);
            }
        }
    }
    tutorial_scene_objects_update();
    UpdateSoundVoices();
    UpdateLightingEnvironment();
    gfx_compute_light_direction();
    game_update_idle_frame_counters();
}
