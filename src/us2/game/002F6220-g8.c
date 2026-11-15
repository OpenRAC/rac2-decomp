#include "include_asm.h"

#include "common.h"
extern char D_001BAD40[];
typedef struct { char pad[0xC]; unsigned char n; char padD[0x3B]; int slots[1]; } CutsceneParts;
typedef struct { char pad[0x24]; CutsceneParts *parts; } CutsceneMoby;
typedef struct {
    char pad0[0x10];
    float pos[4];              
    float rot[4];              
    int id;                    
    int unk34;                 
    int index;                 
    int unk3C;                 
    char pad40[4];
    short count;               
    short restore;             
    short wait;                
    char pad4A[0x22];
    int base6C;                
    int base70;                
    char pad74[0x118];
    CutsceneMoby *mobys[1];    
} CutsceneState;
typedef struct {
    char pad0[4];
    short active;              
    char pad6[0x1E];
    int id;                    
    int flag;                  
    char pad2C[0x40];
    short timer;               
    char pad6E[4];
    short state;               
} CutsceneHelp;
typedef struct {
    char pad0[0x80];
    float pos[4];              
    char pad90[0x2200];
    int active;                
    char pad2294[0x21];
    char flag;                 
} CutsceneHero;
typedef struct { char pad[0xFC]; char *moby; } CutsceneMenu;
typedef struct { int unk0; char *moby; void *data; } CutsceneTalk;
typedef struct { char pad[0xC]; int baseC, base10; } CutsceneResources;
extern CutsceneState g_scene_playback_state;
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
extern void req_mark_queued_in_flag_table(void *);
extern int cutscene_map_id_to_index(int);
extern void music_Pause(int);
extern s16 snd_pump_music_and_disc_read(int);
extern void mem_clear(void *, int, int);
extern void subtitle_clear_state(void);
extern unsigned int func_US2_0026F750(int, int);
extern void stub_empty_4(void);
extern int load_chunk_part_from_disc(int);
extern void load_relocate_world_object_parts(void);
extern void gfx_empty_stub(void);
extern s32 UpdateSoundVoices(void);
extern int sceGsSyncV(int);
extern int snd_resume_music_stream(void);

/* Starts cutscene n: marks it seen, clears the cutscene state and buffers, sets
   up the resource bases and hero, then waits for the dialog stream and three
   frames. */
void func_US2_002F6220(int n)
{
    int index, i, v;
    char *p, *o;

    if ((unsigned)n < 0xB1)
        *(D_00139768 + ((unsigned)n >> 2)) |= 1 << (n & 31);
    req_mark_queued_in_flag_table(D_001BAD40);
    index = cutscene_map_id_to_index(n);
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
    p = D_0021F080;
    for (i = 0; i < 7; i++) {
        char *entry = p;
        p += 0x40;
        mem_clear(entry, 0, 0x40);
    }
    D_001A8C74 = 1.0f;
    g_scene_playback_state.id = index;
    D_001A8C78 = 0;
    g_scene_playback_state.unk34 = 0;
    g_scene_playback_state.unk3C = 0;
    if (g_current_map_index == 20)
        v = D_001B22B0[0] - 0x60000;
    else
        v = D_001B22B0[0] - 0x40000;
    D_001B22B0[0] = v;
    g_scene_playback_state.base6C = D_001BAEC0.baseC + v;
    g_scene_playback_state.base70 = D_001BAEC0.base10 + v;
    subtitle_clear_state();
    g_screen_fade = 1.0f;
    g_current_game_mode = 2;
    D_001B15A4 = 0;
    D_001A8C7C = 0;
    if (g_hero_state.active) {
        func_US2_0026F750(0x61, 2);
        g_hero_state.flag = 1;
        stub_empty_4();
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
    for (o = D_001B1B60; (unsigned char)o[0x20] != 255; o += 0x100) {
        if (!((unsigned char)o[0x20] & 0x80) && *(short *)(o + 0xAA) == 0xCB)
            *(unsigned short *)(o + 0x34) |= 0x80;
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

typedef struct { char pad[0xB0]; float fov; } CutsceneCamVars;
extern CutsceneCamVars D_001B9040;
extern void (*D_001A8C80)(int);
extern int D_001A8C84, g_requested_game_mode;
extern int D_001BAD78[];
extern void gfx_select_packet_buffer_setup(void);
extern void FadeToBlack(int);
extern void cam_set_transition_frames(float);
extern void game_reset_frame_counters(void);
extern void UpdateViewContext(void);
extern void moby_mark_spawned(void *);
extern void stub_empty_10(int);
extern float coll_probe_ground_height_below(void *, int, float);
extern float math_fabs(float);
extern void func_US2_0026F730(void);
extern void stub_empty_15(void *, void *, int, int);
extern void cutscene_run_dialogue_node(void *, void *, int);
extern void music_set_active_track_value(int);
extern void hero_destroy_equipment_pieces(void);

/* Ends the cutscene: restores the frame rate, camera field of view and the
   cutscene mobys, drops the hero and camera back to the ground, clears the
   talk and menu mobys and runs the pending end callback. */
void func_US2_002F6600(void)
{
    char *o;
    CutsceneHero *p;
    CutsceneState *b;
    float g, f;
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
    for (o = D_001B1B60; (unsigned char)o[0x20] != 255; o += 0x100) {
        if (!((unsigned char)o[0x20] & 0x80) && *(short *)(o + 0xAA) == 0xCB)
            *(unsigned short *)(o + 0x34) &= 0xFF7F;
    }
    p = &g_hero_state;
    if (p->active) {
        stub_empty_10(1);
        g = coll_probe_ground_height_below(p->pos, 0, 0.5f);
        if (2.0f < g) {
            if (math_fabs(p->pos[2] - g) < 4.5f)
                p->pos[2] = g;
        }
        g_hero_state.flag = 0;
        func_US2_0026F730();
        b = &g_scene_playback_state;
        if (b->restore) {
            f = coll_probe_ground_height_below(b->pos, 0, 0.5f);
            if (2.0f < f && math_fabs(b->pos[2] - f) < 2.0f)
                b->pos[2] = f;
            stub_empty_15(g_scene_playback_state.pos, g_scene_playback_state.rot, 0, 1);
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
