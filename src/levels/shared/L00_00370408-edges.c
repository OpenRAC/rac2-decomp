#include "common.h"

typedef struct { char prefix[0x3C]; int abort; } SequencePlayback;
extern SequencePlayback g_request_l00_queue;
extern float g_hero_scalar_transition_value __attribute__((sda));
extern int g_player_stats[] __attribute__((sda));
extern int g_loader_state_word __attribute__((sda)), g_current_map_index __attribute__((sda)), g_is_pal_video __attribute__((sda));
typedef struct { char prefix[0x1A0]; union { unsigned long long all; struct { unsigned int low, high; } word; } buttons; } SequenceInput;
extern SequenceInput g_pad_state;
extern short g_sequence_active_flag;
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

extern int g_tutorial_probe_context[];
extern s16 snd_pump_music_and_disc_read(int);
extern void game_reset_frame_counters(void);
extern void part_update_all(void);
extern int load_queue_level_data_chunk(int);
extern s32 UpdateSoundVoices(void);
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
    if (((SequenceState *)g_tutorial_probe_context)->done) return;
    if (((SequenceState *)g_tutorial_probe_context)->end_time == 0) {
        req_flush_queue(&g_request_l00_queue);
        ((SequenceState *)g_tutorial_probe_context)->done = 1;
        request_end_slot(0, 0);
        return;
    }
    game_reset_frame_counters();
    tutorial_probe_points_update();
    moby_update_visible_objects();
    snd_run_callbacks();
    hero_l00_update_frame_2();
    part_update_all();
    { int t; ++((SequenceState *)g_tutorial_probe_context)->frame; t = ++((SequenceState *)g_tutorial_probe_context)->time; if (t < 18) {
        ApproachValue(&g_hero_scalar_transition_value, 0.0f, 0.16666667f);
        if (g_hero_scalar_transition_value > 1.0f) g_hero_scalar_transition_value = 1.0f;
    }
    }
    if (((SequenceState *)g_tutorial_probe_context)->fade_time <= ((SequenceState *)g_tutorial_probe_context)->time) snd_resume_music_stream();
    ended = ((SequenceState *)g_tutorial_probe_context)->time >= ((SequenceState *)g_tutorial_probe_context)->end_time;
    abort = 0;
    if (((SequenceState *)g_tutorial_probe_context)->time > 17 && g_hero_scalar_transition_value == 0.0f) {
        if (!(((g_player_stats[2] & 0xFFFF0000) == 0) && g_loader_state_word == 0 && g_current_map_index > 0) && (g_pad_state.buttons.word.high & 0x800)) abort = 1;
        else { unsigned long long v = (g_pad_state.buttons.all & 0x8000000000FULL) ^ 0x8000000000FULL; abort = 1; if (v) abort = 0; }
    }
    if (abort) {
        g_request_l00_queue.abort = 1;
        req_flush_queue(&g_request_l00_queue);
        ((SequenceState *)g_tutorial_probe_context)->done = 1;
        request_end_slot(0, 0);
    } else {
        if (ended) {
            ((SequenceState *)g_tutorial_probe_context)->done = 1;
            if (!req_launch_queued(&g_request_l00_queue)) request_end_slot(0, 0);
        } else {
            threshold = g_is_pal_video ? 80 : 96;
            if (((SequenceState *)g_tutorial_probe_context)->frame >= threshold) {
                ++((SequenceState *)g_tutorial_probe_context)->chunk;
                if (g_sequence_active_flag) snd_pump_music_and_disc_read(1);
                load_relocate_world_object_parts();
                load_queue_level_data_chunk(((SequenceState *)g_tutorial_probe_context)->chunk + 1);
            }
            complete = cutscene_apply_camera_key();
            for (i = 0; i < ((SequenceState *)g_tutorial_probe_context)->count; i++) {
                object = ((SequenceState *)g_tutorial_probe_context)->actors[i];
                { int frame = ((SequenceState *)g_tutorial_probe_context)->frame >> 1;
                object[0x41] = frame + 1;
                object[0x40] = frame; }
                update_moby_animation_state(object);
                *(float *)(object + 0x44) = IntToFloat(((SequenceState *)g_tutorial_probe_context)->frame & 1) * 0.5f;
                if (complete && (((SequenceState *)g_tutorial_probe_context)->frame & 1)) *(float *)(object + 0x44) = 1.0f;
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
                if (id == 10 || id == 0x1159 /* moby class 4441 */ || id == MOBY_CLASS_CLANK || id == 0xD6B /* moby class 3435 */) update_moby_pulsing_glow_effects(object);
            }
        }
    }
    tutorial_scene_objects_update();
    UpdateSoundVoices();
    UpdateLightingEnvironment();
    gfx_compute_light_direction();
    game_update_idle_frame_counters();
}
