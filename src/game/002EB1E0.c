#include "common.h"

/* func_002EB1E0 (cutscene_update_scripted_actors), split from 002E7018.c: this unit needs
   -frac2-gcse-unsplit-edges for the skip test's branch layout. */

typedef struct {
    char pad0[0x10];
    float pos[4];                   /* 0x10 */
    char pad20[0x20];
    unsigned char key;              /* 0x40 */
    unsigned char next_key;         /* 0x41 */
    char pad42[2];
    float blend;                    /* 0x44 */
    char pad48[0x19];
    unsigned char alpha;            /* 0x61 */
    char pad62;
    unsigned char flags;            /* 0x63 */
    char pad64[4];
    char *keys;                     /* 0x68: 16-byte key positions */
    char pad6C[0x3E];
    short type;                     /* 0xAA */
} SceneActor;

typedef struct {
    char pad0[0x30];
    int selected;                   /* 0x30 */
    int frame;                      /* 0x34 */
    int tick;                       /* 0x38: two ticks per key */
    int chunk;                      /* 0x3C */
    short end;                      /* 0x40 */
    short pad42;
    short count;                    /* 0x44 */
    short pad46;
    short wait;                     /* 0x48 */
    char pad4A[0x0E];
    int done;                       /* 0x58 */
    char pad5C[0x10];
    int start;                      /* 0x6C */
    int destination;                /* 0x70 */
    char pad74[0x118];
    SceneActor *actors[17];         /* 0x18C */
} Scene2EB1E0;

typedef struct {
    char pad0[0x2290];
    SceneActor *focus;              /* 0x2290 */
} Game2EB1E0;

typedef struct {
    char pad0[0x1A0];
    union {
        unsigned long long held;
        unsigned int words[2];
    } buttons;                      /* 0x1A0 */
} Input2EB1E0;

/* Player state: the word at 0x08 holds both flags, so their test reads it once. */
typedef struct {
    unsigned char pad0[0x0A];
    unsigned char x0A;
    unsigned char x0B;
    unsigned char pad0C[0x08];
    int x14;
} Global001A7A00;

extern Scene2EB1E0 g_scene_playback_state;
extern Game2EB1E0 D_00189E20_9;
extern char g_pad_state[];
#define INPUT ((Input2EB1E0 *)D_00138180)
extern char D_001A63A8_3[];
extern SceneActor *D_001B2148;
extern Global001A7A00 D_001A7A00 MACRO_ADDR;
extern int D_001A7478 MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern int g_is_pal_video MACRO_ADDR;
extern int g_requested_game_mode MACRO_ADDR;
extern float g_screen_fade MACRO_ADDR;

extern void game_reset_frame_counters(void);
extern void scene_update_backdrop_quads(void);
extern int snd_resume_music_stream(void);
extern s16 snd_pump_music_and_disc_read(int);
extern void moby_spawn_model_parts(void);
extern int scene_load_chunk_data(int);
extern int cutscene_apply_camera_key(void);
extern void update_moby_animation_state(void *);
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void UpdateEquipmentPieces(void *);
extern void render_environment_mapped_object(void);
extern void gfx_register_overlay_draw_callback(void *, void *);
extern void func_002A0F48(void *);
extern void stub_empty_16(void *, int);
extern s32 UpdateSoundVoices(void);
extern void UpdateLightingEnvironment(void);
extern void game_update_idle_frame_counters(void);

/* Advances the scripted scene one frame: fades in, lets the player skip once the fade is
   done, pages in the next chunk every 80 or 96 ticks and poses each actor between its two
   current keys. Returns 1 when the player skipped. */
int cutscene_update_scripted_actors(void)
{
    SceneActor *actor;
    float first[4], last[4];
    float fade;
    int skip, done, camera, i;

    if (g_scene_playback_state.done)
        return 0;
    if (g_scene_playback_state.frame + 1 >= g_scene_playback_state.end) {
        g_requested_game_mode = 0;
        g_scene_playback_state.done = 1;
        return 0;
    }
    game_reset_frame_counters();
    scene_update_backdrop_quads();
    fade = g_screen_fade - 0.34f;
    g_scene_playback_state.tick++;
    g_scene_playback_state.frame++;
    g_screen_fade = fade;
    if (fade < 0.0f)
        g_screen_fade = 0.0f;
    if (g_scene_playback_state.frame >= g_scene_playback_state.wait)
        snd_resume_music_stream();

    skip = 0;
    done = g_scene_playback_state.frame >= g_scene_playback_state.end;
    if (g_scene_playback_state.frame >= 18 && g_screen_fade == 0.0f) {
        if ((D_001A7A00.x0A || D_001A7A00.x0B || D_001A7478 || g_current_map_index <= 0)
            && (INPUT->buttons.words[1] & 0x800))
            skip = 1;
        else if ((INPUT->buttons.held & 0x8000000000FULL) == 0x8000000000FULL)
            skip = 1;
    }

    if (skip || done) {
        g_scene_playback_state.done = 1;
        g_requested_game_mode = 0;
    } else {
        int ticks = g_is_pal_video ? 80 : 96;
        if (g_scene_playback_state.tick >= ticks) {
            g_scene_playback_state.chunk++;
            if (*(short *)(D_001A63A8_3 + 4))
                snd_pump_music_and_disc_read(1);
            moby_spawn_model_parts();
            scene_load_chunk_data(g_scene_playback_state.chunk + 1);
        }
        camera = cutscene_apply_camera_key();
        for (i = 0; i < g_scene_playback_state.count; i++) {
            char *keys;
            int key, type;

            actor = g_scene_playback_state.actors[i];
            key = g_scene_playback_state.tick >> 1;
            actor->next_key = key + 1;
            actor->key = key;
            update_moby_animation_state(actor);
            actor->blend = IntToFloat(g_scene_playback_state.tick & 1) * 0.5f;
            if (camera && (g_scene_playback_state.tick & 1))
                actor->blend = 1.0f;
            keys = actor->keys;
            FastVecScale(first, keys + actor->key * 16, 1.0f - actor->blend);
            FastVecScale(last, keys + actor->next_key * 16, actor->blend);
            FastVecAdd(actor->pos, first, last);
            type = actor->type;
            if (type == 0xD54 /* moby class 3412 */) {
                actor->flags = 8;
                UpdateEquipmentPieces(actor);
                if (!D_001B2148 || D_001B2148->type == type)
                    gfx_register_overlay_draw_callback(render_environment_mapped_object, actor);
            }
            actor->alpha = 255;
            func_002A0F48(actor);
            if (actor->type == 0) {
                D_00189E20_9.focus = actor;
                stub_empty_16(actor, 1);
            }
        }
    }
    UpdateSoundVoices();
    UpdateLightingEnvironment();
    game_update_idle_frame_counters();
    return skip;
}
