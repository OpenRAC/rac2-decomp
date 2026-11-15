#include "common.h"

extern char D_001BAD40[];
extern int D_001A7478 __attribute__((sda));
extern short D_00152C28[];
extern int D_0013955C[];
extern s32 req_push_queue(char *, int);
extern s32 req_launch_queued(char *);
extern void game_set_stored_value_pair(void (*)(void), int);
extern void menu_flag_current_entry(void);

/* Loads a data file into the shared buffer and sets up a callback and two flags for the next screen. */
void load_data_and_setup_callback(void)
{
    char *buffer = D_001BAD40;
    D_001A7478 = 1;
    req_push_queue(buffer, 21);
    req_launch_queued(buffer);
    game_set_stored_value_pair(menu_flag_current_entry, 0);
    D_00152C28[0] = 1;
    D_0013955C[0] = 0;
}

/* Cutscene state: cleared whole when a cutscene starts. */
typedef struct { char pad[0xC]; unsigned char n; char padD[0x3B]; int slots[1]; } CutsceneParts;
typedef struct { char pad[0x24]; CutsceneParts *parts; } CutsceneMoby;
typedef struct {
    char pad0[0x10];
    float pos[4];             /* 0x10 */
    float rot[4];             /* 0x20 */
    int id;                   /* 0x30 */
    int unk34;                /* 0x34 */
    int index;                /* 0x38 */
    int unk3C;                /* 0x3C */
    char pad40[4];
    short count;              /* 0x44 */
    short restore;            /* 0x46 */
    short wait;               /* 0x48 */
    char pad4A[0x22];
    int base6C;               /* 0x6C */
    int base70;               /* 0x70 */
    char pad74[0x118];
    CutsceneMoby *mobys[1];   /* 0x18C */
} CutsceneState;
typedef struct { char pad[0xB0]; float fov; } CutsceneCamVars;
typedef struct {
    char pad0[4];
    short active;             /* 0x04 */
    char pad6[0x1E];
    int id;                   /* 0x24 */
    int flag;                 /* 0x28 */
    char pad2C[0x40];
    short timer;              /* 0x6C */
    char pad6E[4];
    short state;              /* 0x72 */
} CutsceneHelp;
typedef struct {
    char pad0[0x80];
    float pos[4];             /* 0x80 */
    char pad90[0x2200];
    int active;               /* 0x2290 */
    char pad2294[0x21];
    char flag;                /* 0x22B5 */
} CutsceneHero;
typedef struct { char pad[0xFC]; char *moby; } CutsceneMenu;
/* Retail never puts the moby or data load in a delay slot: both are read at an
   offset from an earlier small-data name, taken here as the word before them. */
typedef struct { int unk0; char *moby; void *data; } CutsceneTalk;
typedef struct { char pad[0xC]; int baseC, base10; } CutsceneResources;

extern CutsceneState g_scene_playback_state;
extern CutsceneCamVars D_001B9040;
extern CutsceneHelp g_music_state;
extern CutsceneHero g_hero_state;
extern CutsceneMenu g_pause_menu_state;
extern CutsceneTalk D_001B178C MACRO_ADDR;
extern CutsceneResources D_001BAEC0;
extern float D_001A8C74, D_001A8C78, D_001A8C7C, g_screen_fade;
extern int g_current_map_index, g_current_game_mode, D_001B15A4, D_001B15A8, D_001B15AC;
extern int D_001B22B0[] __attribute__((sda));
extern char *D_001B1B60;
extern int D_00139768[];
extern char D_001B1450[] MACRO_ADDR, D_001B1390[] MACRO_ADDR, D_001B13D0[] MACRO_ADDR, D_001B1410[] MACRO_ADDR;
extern char D_001B2980[], D_0021F080[];
extern void (*D_001A8C80)(int);
extern int D_001A8C84, g_requested_game_mode;
extern int D_001BAD78[];
extern void req_mark_queued_in_flag_table(void *);
extern int cutscene_map_id_to_index(int);
extern void music_Pause(int);
extern s16 snd_pump_music_and_disc_read(int);
extern void mem_clear(void *, int, int);
extern void subtitle_clear_state(void);
extern unsigned int stub_empty_8(int, int);
extern void stub_empty_3(void);
extern int load_chunk_part_from_disc(int);
extern void load_relocate_world_object_parts(void);
extern void gfx_empty_stub(void);
extern s32 UpdateSoundVoices(void);
extern int sceGsSyncV(int);
extern int snd_resume_music_stream(void);
extern void gfx_select_packet_buffer_setup(void);
extern void FadeToBlack(int);
extern void cam_set_transition_frames(float);
extern void game_reset_frame_counters(void);
extern void UpdateViewContext(void);
extern void moby_mark_spawned(void *);
extern void stub_empty_9(int);
extern float coll_probe_ground_height_below(void *, int, float);
extern float math_fabs(float);
extern void stub_empty_4(void);
extern void stub_empty_14(void *, void *, int, int);
extern void cutscene_run_dialogue_node(void *, void *, int);
extern void music_set_active_track_value(int);
extern void hero_destroy_equipment_pieces(void);

/* Starts cutscene n: marks it seen, clears the cutscene state and buffers, sets
   up the resource bases and hero, then waits for the dialog stream and three
   frames. */
/* Starts a cutscene by its number. */
void cutscene_start(int cutscene_id)
{
    int index, i, mem_top;
    char *buffer_ptr, *moby;

    if ((unsigned)cutscene_id < 0xB1)
        *(D_00139768 + ((unsigned)cutscene_id >> 2)) |= 1 << (cutscene_id & 31);
    req_mark_queued_in_flag_table(D_001BAD40);
    index = cutscene_map_id_to_index(cutscene_id);
    if (index < 0)
        return;
    music_Pause(0);
    snd_pump_music_and_disc_read(0);
    mem_clear(&g_scene_playback_state, 0, 0x1D0);
    mem_clear(D_001B1450, 0, 0x40);
    mem_clear(D_001B1390, 0, 0x40);
    mem_clear(D_001B2980, 0, 0x40);
    mem_clear(D_001B2980 + 0x40, 0, 0x40);
    mem_clear(D_001B13D0, 0, 0x40);
    mem_clear(D_001B1410, 0, 0x40);
    buffer_ptr = D_0021F080;
    for (i = 0; i < 7; i++) {
        char *entry = buffer_ptr;
        buffer_ptr += 0x40;
        mem_clear(entry, 0, 0x40);
    }
    D_001A8C74 = 1.0f;
    g_scene_playback_state.id = index;
    D_001A8C78 = 0;
    g_scene_playback_state.unk34 = 0;
    g_scene_playback_state.unk3C = 0;
    if (g_current_map_index == 20)
        mem_top = D_001B22B0[0] - 0x60000;
    else
        mem_top = D_001B22B0[0] - 0x40000;
    D_001B22B0[0] = mem_top;
    g_scene_playback_state.base6C = D_001BAEC0.baseC + mem_top;
    g_scene_playback_state.base70 = D_001BAEC0.base10 + mem_top;
    subtitle_clear_state();
    g_screen_fade = 1.0f;
    g_current_game_mode = 2;
    D_001B15A4 = 0;
    D_001A8C7C = 0;
    if (g_hero_state.active) {
        stub_empty_8(0x61, 2);
        g_hero_state.flag = 1;
        stub_empty_3();
    }
    if (D_001B178C.moby)
        *(unsigned short *)(D_001B178C.moby + 0x34) |= 1;
    if (g_pause_menu_state.moby)
        *(unsigned short *)(g_pause_menu_state.moby + 0x34) |= 1;
    D_001B15A8 = 1;
    D_001B15AC = 52;
    if (g_music_state.active) {
        snd_pump_music_and_disc_read(1);
        load_chunk_part_from_disc(0);
    } else
        load_chunk_part_from_disc(0);
    if (g_music_state.active)
        snd_pump_music_and_disc_read(1);
    load_relocate_world_object_parts();
    gfx_empty_stub();
    for (moby = D_001B1B60; (unsigned char)moby[0x20] != 255; moby += 0x100) {
        if (!((unsigned char)moby[0x20] & 0x80) && *(short *)(moby + 0xAA) == MOBY_CLASS_DECOY)
            *(unsigned short *)(moby + 0x34) |= 0x80;
    }
    g_music_state.id = g_scene_playback_state.id;
    g_music_state.flag = 0;
    while (g_music_state.state != 3 || g_music_state.timer >= 6000) {
        UpdateSoundVoices();
        sceGsSyncV(0);
    }
    {
        int ticks = 0;
        CutsceneState *state = &g_scene_playback_state;

        state->wait = -3;
        snd_resume_music_stream();
        load_chunk_part_from_disc(1);
        for (; state->wait < ticks; ticks--)
            sceGsSyncV(0);
    }
}

/* Ends the cutscene: restores the frame rate, camera field of view and the
   cutscene mobys, drops the hero and camera back to the ground, clears the
   talk and menu mobys and runs the pending end callback. */
void cutscene_end(void)
{
    char *moby;
    CutsceneHero *hero;
    CutsceneState *cutscene;
    float hero_ground_z, cutscene_ground_z;
    int i;

    if ((unsigned short)(g_music_state.state - 6) >= 2)
        g_music_state.state = 5;
    gfx_select_packet_buffer_setup();
    FadeToBlack(6);
    D_001B15A8 = 0;
    D_001B15AC = 0;
    D_001B15A4 = 0;
    D_001A8C7C = 0;
    cam_set_transition_frames(6.0f);
    game_reset_frame_counters();
    D_001B9040.fov = 0.62f;
    UpdateViewContext();
    for (i = 0; i < g_scene_playback_state.count; i++) {
        CutsceneMoby *m = g_scene_playback_state.mobys[i];
        if (m) {
            m->parts->n--;
            m->parts->slots[m->parts->n] = 0;
            moby_mark_spawned(m);
        }
    }
    for (moby = D_001B1B60; (unsigned char)moby[0x20] != 255; moby += 0x100) {
        if (!((unsigned char)moby[0x20] & 0x80) && *(short *)(moby + 0xAA) == MOBY_CLASS_DECOY)
            *(unsigned short *)(moby + 0x34) &= 0xFF7F;
    }
    hero = &g_hero_state;
    if (hero->active) {
        stub_empty_9(1);
        hero_ground_z = coll_probe_ground_height_below(hero->pos, 0, 0.5f);
        if (2.0f < hero_ground_z) {
            if (math_fabs(hero->pos[2] - hero_ground_z) < 4.5f)
                hero->pos[2] = hero_ground_z;
        }
        g_hero_state.flag = 0;
        stub_empty_4();
        cutscene = &g_scene_playback_state;
        if (cutscene->restore) {
            cutscene_ground_z = coll_probe_ground_height_below(cutscene->pos, 0, 0.5f);
            if (2.0f < cutscene_ground_z && math_fabs(cutscene->pos[2] - cutscene_ground_z) < 2.0f)
                cutscene->pos[2] = cutscene_ground_z;
            stub_empty_14(g_scene_playback_state.pos, g_scene_playback_state.rot, 0, 1);
        }
    }
    if (D_001B178C.moby)
        *(unsigned short *)(D_001B178C.moby + 0x34) &= 0xFFFE;
    if (g_pause_menu_state.moby) {
        *(unsigned short *)(g_pause_menu_state.moby + 0x34) &= 0xFFFE;
        g_pause_menu_state.moby = 0;
    }
    if (D_001B178C.moby) {
        char *moby = D_001B178C.moby;
        void *data = D_001B178C.data;
        D_001B178C.moby = 0;
        D_001B178C.data = 0;
        cutscene_run_dialogue_node(moby, data, 1);
    }
    music_set_active_track_value(30);
    if (D_001A8C80 && !D_001BAD78[0] && g_requested_game_mode != 2 && g_requested_game_mode != 1) {
        D_001A8C80(D_001A8C84);
        D_001A8C80 = 0;
        D_001A8C84 = 0;
    }
    hero_destroy_equipment_pieces();
}
