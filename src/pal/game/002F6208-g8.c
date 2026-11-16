#include "include_asm.h"
#include "names.h"
typedef float f32_F2144bf3d;
typedef int s32_F2144bf3d;
typedef struct {
    char  pad0[0x100];
    f32_F2144bf3d   f100;                  
    f32_F2144bf3d   f104;                  
    f32_F2144bf3d   f108;                  
    f32_F2144bf3d   f10C;                  
    char  pad1[0x1A0 - 0x110];
    s32_F2144bf3d   i1A0;                  
} Resident138180_F2144bf3d;
extern char g_pad_state[];
extern s32_F2144bf3d g_level_idle_frame_counts[];
extern s32_F2144bf3d g_idle_frame_counter __attribute__((sda));
extern s32_F2144bf3d g_frame_counter;
extern s32_F2144bf3d g_current_map_index;
extern s32_F2144bf3d g_game_l06_frame_counter;
extern s32_F2144bf3d g_idle_counter_check;
extern s32_F2144bf3d g_idle_frame_marker;
extern s32_F2144bf3d g_idle_counter_reset;

/* Counts how many frames in a row the controller has had no input, and counts every frame played.
   While the pause is shorter than 750 frames (PAL: 50 Hz) it also adds the frame to the current slot's total. */
void game_update_idle_frame_counters_pal(void)
{
    Resident138180_F2144bf3d *pad = (Resident138180_F2144bf3d *)g_pad_state;

    if (pad->i1A0 != 0) goto mismatch;
    if (pad->f108 != 0.0f) goto mismatch;
    if (pad->f10C != 0.0f) goto mismatch;
    if (pad->f100 != 0.0f) goto mismatch;
    if (pad->f104 == 0.0f) goto match;
mismatch:
    g_idle_frame_counter = 0;
    goto gated;
match:
    g_idle_frame_counter = g_idle_frame_counter + 1;
gated:
    g_game_l06_frame_counter = g_game_l06_frame_counter + 1;
    g_frame_counter = g_frame_counter + 1;

    if (g_idle_counter_check != 0) {
        if (g_idle_frame_counter < 750) {
            g_level_idle_frame_counts[g_current_map_index] = g_level_idle_frame_counts[g_current_map_index] + 1;
        }
    }

    if (g_idle_frame_marker != g_frame_counter - 1) {
        g_idle_counter_reset = -1;
    }
}

#include "common.h"
extern char g_loader_movie[];
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
extern CutsceneTalk g_dialogue_talk_state MACRO_ADDR;
extern CutsceneResources g_loader_memory;
extern float g_cutscene_camera_scale, g_cutscene_camera_blend, g_mode_fade_scale, g_screen_fade;
extern int g_current_map_index, g_current_game_mode, g_screen_flash_alpha, g_cutscene_active_flag, g_cutscene_letterbox_progress;
extern int g_packet_buffer_size[] __attribute__((sda));
extern char *g_moby_pool_end;
extern int g_request_flag_table[];
extern char g_cutscene_scratch_d[] MACRO_ADDR, g_cutscene_scratch_a[] MACRO_ADDR, g_cutscene_scratch_b[] MACRO_ADDR, g_cutscene_scratch_c[] MACRO_ADDR;
extern char g_cutscene_scratch_state[], g_cutscene_buffer[];
extern void req_mark_queued_in_flag_table(void *);
extern int cutscene_map_id_to_index(int);
extern void music_Pause(int);
extern s16 snd_pump_music_and_disc_read_pal(int);
extern void mem_clear(void *, int, int);
extern void subtitle_clear_state(void);
extern unsigned int stub_empty_9_pal(int, int);
extern void stub_empty_4(void);
extern int load_chunk_part_from_disc_pal(int);
extern void load_relocate_world_object_parts(void);
extern void gfx_empty_stub(void);
extern s32 UpdateSoundVoices_pal(void);
extern int sceGsSyncV(int);
extern int snd_resume_music_stream(void);

/* Starts cutscene n: marks it seen, clears the cutscene state and buffers, sets
   up the resource bases and hero, then waits for the dialog stream and three
   frames. */
void cutscene_start_pal(int cutscene_id)
{
    int index, i, buffer_size;
    char *entry_ptr, *moby_ptr;

    if ((unsigned)cutscene_id < 0xB1)
        *(g_request_flag_table + ((unsigned)cutscene_id >> 2)) |= 1 << (cutscene_id & 31);
    req_mark_queued_in_flag_table(g_loader_movie);
    index = cutscene_map_id_to_index(cutscene_id);
    if (index < 0)
        return;
    music_Pause(0);
    snd_pump_music_and_disc_read_pal(0);
    mem_clear(&g_scene_playback_state, 0, 0x1D0);
    mem_clear(g_cutscene_scratch_d, 0, 0x40);
    mem_clear(g_cutscene_scratch_a, 0, 0x40);
    mem_clear(g_cutscene_scratch_state, 0, 0x40);
    mem_clear(g_cutscene_scratch_state + 0x40, 0, 0x40);
    mem_clear(g_cutscene_scratch_b, 0, 0x40);
    mem_clear(g_cutscene_scratch_c, 0, 0x40);
    entry_ptr = g_cutscene_buffer;
    for (i = 0; i < 7; i++) {
        char *entry = entry_ptr;
        entry_ptr += 0x40;
        mem_clear(entry, 0, 0x40);
    }
    g_cutscene_camera_scale = 1.0f;
    g_scene_playback_state.id = index;
    g_cutscene_camera_blend = 0;
    g_scene_playback_state.unk34 = 0;
    g_scene_playback_state.unk3C = 0;
    if (g_current_map_index == 20)
        buffer_size = g_packet_buffer_size[0] - 0x60000;
    else
        buffer_size = g_packet_buffer_size[0] - 0x40000;
    g_packet_buffer_size[0] = buffer_size;
    g_scene_playback_state.base6C = g_loader_memory.baseC + buffer_size;
    g_scene_playback_state.base70 = g_loader_memory.base10 + buffer_size;
    subtitle_clear_state();
    g_screen_fade = 1.0f;
    g_current_game_mode = 2;
    g_screen_flash_alpha = 0;
    g_mode_fade_scale = 0;
    if (g_hero_state.active) {
        stub_empty_9_pal(0x61, 2);
        g_hero_state.flag = 1;
        stub_empty_4();
    }
    if (g_dialogue_talk_state.moby)
        *(unsigned short *)(g_dialogue_talk_state.moby + 0x34) |= 1;
    if (g_pause_menu_state.moby)
        *(unsigned short *)(g_pause_menu_state.moby + 0x34) |= 1;
    g_cutscene_active_flag = 1;
    g_cutscene_letterbox_progress = 52;
    if (g_music_state.active) {
        snd_pump_music_and_disc_read_pal(1);
        load_chunk_part_from_disc_pal(0);
    } else
        load_chunk_part_from_disc_pal(0);
    if (g_music_state.active)
        snd_pump_music_and_disc_read_pal(1);
    load_relocate_world_object_parts();
    gfx_empty_stub();
    for (moby_ptr = g_moby_pool_end; (unsigned char)moby_ptr[0x20] != 255; moby_ptr += 0x100) {
        if (!((unsigned char)moby_ptr[0x20] & 0x80) && *(short *)(moby_ptr + 0xAA) == 0xCB)
            *(unsigned short *)(moby_ptr + 0x34) |= 0x80;
    }
    g_music_state.id = g_scene_playback_state.id;
    g_music_state.flag = 0;
    while (g_music_state.state != 3 || g_music_state.timer >= 6000) {
        UpdateSoundVoices_pal();
        sceGsSyncV(0);
    }
    {
        int ticks = 0;
        CutsceneState *state = &g_scene_playback_state;

        state->wait = -3;
        snd_resume_music_stream();
        load_chunk_part_from_disc_pal(1);
        for (; state->wait < ticks; ticks--)
            sceGsSyncV(0);
    }
}

typedef struct { char pad[0xB0]; float fov; } CutsceneCamVars;
extern CutsceneCamVars g_view_params;
extern void (*g_cutscene_end_callback)(int);
extern int g_cutscene_end_callback_arg, g_requested_game_mode;
extern int g_movie_state_flags[];
extern void gfx_select_packet_buffer_setup(void);
extern void FadeToBlack(int);
extern void cam_set_transition_frames(float);
extern void game_reset_frame_counters(void);
extern void UpdateViewContext(void);
extern void moby_mark_spawned(void *);
extern void stub_empty_10(int);
extern float coll_probe_ground_height_below(void *, int, float);
extern float math_fabs(float);
extern void stub_empty_5_pal(void);
extern void stub_empty_15(void *, void *, int, int);
extern void cutscene_run_dialogue_node(void *, void *, int);
extern void music_set_active_track_value(int);
extern void hero_destroy_equipment_pieces(void);

/* Ends the cutscene: restores the frame rate, camera field of view and the
   cutscene mobys, drops the hero and camera back to the ground, clears the
   talk and menu mobys and runs the pending end callback. */
void cutscene_end_pal(void)
{
    char *moby_ptr;
    CutsceneHero *hero;
    CutsceneState *scene;
    float hero_ground, scene_ground;
    int i;

    if ((unsigned short)(g_music_state.state - 6) >= 2)
        g_music_state.state = 5;
    gfx_select_packet_buffer_setup();
    FadeToBlack(6);
    g_cutscene_active_flag = 0;
    g_cutscene_letterbox_progress = 0;
    g_screen_flash_alpha = 0;
    g_mode_fade_scale = 0;
    cam_set_transition_frames(5.0f);
    game_reset_frame_counters();
    g_view_params.fov = 0.62f;
    UpdateViewContext();
    for (i = 0; i < g_scene_playback_state.count; i++) {
        CutsceneMoby *scene_moby = g_scene_playback_state.mobys[i];
        if (scene_moby) {
            scene_moby->parts->n--;
            scene_moby->parts->slots[scene_moby->parts->n] = 0;
            moby_mark_spawned(scene_moby);
        }
    }
    for (moby_ptr = g_moby_pool_end; (unsigned char)moby_ptr[0x20] != 255; moby_ptr += 0x100) {
        if (!((unsigned char)moby_ptr[0x20] & 0x80) && *(short *)(moby_ptr + 0xAA) == 0xCB)
            *(unsigned short *)(moby_ptr + 0x34) &= 0xFF7F;
    }
    hero = &g_hero_state;
    if (hero->active) {
        stub_empty_10(1);
        hero_ground = coll_probe_ground_height_below(hero->pos, 0, 0.5f);
        if (2.0f < hero_ground) {
            if (math_fabs(hero->pos[2] - hero_ground) < 4.5f)
                hero->pos[2] = hero_ground;
        }
        g_hero_state.flag = 0;
        stub_empty_5_pal();
        scene = &g_scene_playback_state;
        if (scene->restore) {
            scene_ground = coll_probe_ground_height_below(scene->pos, 0, 0.5f);
            if (2.0f < scene_ground && math_fabs(scene->pos[2] - scene_ground) < 2.0f)
                scene->pos[2] = scene_ground;
            stub_empty_15(g_scene_playback_state.pos, g_scene_playback_state.rot, 0, 1);
        }
    }
    if (g_dialogue_talk_state.moby)
        *(unsigned short *)(g_dialogue_talk_state.moby + 0x34) &= 0xFFFE;
    if (g_pause_menu_state.moby) {
        *(unsigned short *)(g_pause_menu_state.moby + 0x34) &= 0xFFFE;
        g_pause_menu_state.moby = 0;
    }
    if (g_dialogue_talk_state.moby) {
        char *moby = g_dialogue_talk_state.moby;
        void *data = g_dialogue_talk_state.data;
        g_dialogue_talk_state.moby = 0;
        g_dialogue_talk_state.data = 0;
        cutscene_run_dialogue_node(moby, data, 1);
    }
    music_set_active_track_value(25);
    if (g_cutscene_end_callback && !g_movie_state_flags[0] && g_requested_game_mode != 2 && g_requested_game_mode != 1) {
        g_cutscene_end_callback(g_cutscene_end_callback_arg);
        g_cutscene_end_callback = 0;
        g_cutscene_end_callback_arg = 0;
    }
    hero_destroy_equipment_pieces();
}
