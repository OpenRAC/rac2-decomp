#include "common.h"
extern unsigned int g_request_flag_table[];
extern char g_cutscene_state[], g_cutscene_scratch_d[] MACRO_ADDR, g_cutscene_scratch_a[] MACRO_ADDR, g_cutscene_scratch_state[], g_cutscene_scratch_b[] MACRO_ADDR, g_cutscene_scratch_c[] MACRO_ADDR;
extern int g_current_game_mode MACRO_ADDR, g_cutscene_active_flag MACRO_ADDR, g_cutscene_letterbox_progress MACRO_ADDR;
extern float g_screen_fade MACRO_ADDR, g_cutscene_camera_scale MACRO_ADDR, g_cutscene_camera_blend MACRO_ADDR;
extern int g_screen_flash_alpha __attribute__((sda));
extern int cutscene_map_id_to_index(int);
extern void mem_clear(void *, int, int);
extern void FadeToBlack(int), moby_spawn_model_parts(void), level_select_data_bank(void);
extern s32 UpdateSoundVoices(void);
extern short snd_pump_music_and_disc_read(int);
extern int snd_resume_music_stream(void);
typedef struct { char pad[0x30]; int selected, frame, tick, chunk; short end, h42, count, h46, wait; char pad4a[0x2]; int p4c; char pad50[8]; int done; char pad5c[0x10]; int start, dest; char pad74[0x118]; char *objects[17]; } Scene;
extern Scene g_scene_playback_state;
typedef struct { char pad[0x6C]; int arena; } Archive;
extern Archive g_loader_memory;
typedef struct { char pad0[4]; short mode; char pad6[0x1e]; int destination, count; char pad2c[0x40]; short progress; char pad6e[4]; short state; } Transition;
extern Transition D_001A63A8_3;
extern int scene_load_chunk_data(int), sceGsSyncV(int);
/* Scene start for `id`: sets its bit in D_00139768, maps it to an index
   (func_002EF010, nothing if negative), clears the scene buffers, places the
   start and destination windows 0x80000 and 0x100000 below the arena, resets
   the fade and control words, waits until the transition reaches state 3
   below progress 6000, then sets the wait word to -3, calls func_002B6D28
   and func_002EB158(1) and waits a frame per step while it stays below the
   count.

   The stores after the clears are written in the order that gives the
   scheduler retail's register-pressure ties (a store whose register dies
   is issued first, then the rest in source order). The do { } while (0)
   around the two calls leaves loop notes in the block, which the
   scheduler treats as a barrier: the scene address is then computed
   ahead of the -3, as in retail (compare func_00124818). */
/* Starts a scripted scene: clears its buffers, loads the first data and waits for the stream to be ready. */
void cutscene_start_scripted(unsigned int id) {
 int index, count, dest, start;


 if (id < 0xB1) *(unsigned int *)((id >> 2) * 4 + (int)g_request_flag_table) |= 1 << (id & 31);
 index = cutscene_map_id_to_index(id);
 if (index < 0) return;
 mem_clear(g_cutscene_state,0,0x230);
 mem_clear(&g_scene_playback_state,0,0x1D0);
 mem_clear(g_cutscene_scratch_d,0,0x40);
 mem_clear(g_cutscene_scratch_a,0,0x40);
 mem_clear(g_cutscene_scratch_state,0,0x40);
 mem_clear(g_cutscene_scratch_state+0x40,0,0x40);
 mem_clear(g_cutscene_scratch_b,0,0x40);
 mem_clear(g_cutscene_scratch_c,0,0x40);
 start=g_loader_memory.arena - 0x80000;
 dest=g_loader_memory.arena - 0x100000;
 g_cutscene_camera_scale=1.0f;
 g_cutscene_camera_blend=0.0f;
 g_scene_playback_state.frame=0;
 g_scene_playback_state.chunk=0;
 g_scene_playback_state.selected=index;
 g_scene_playback_state.start=start;
 g_scene_playback_state.dest=dest;
 g_screen_fade=1.0f;
 g_current_game_mode=2;
 g_cutscene_active_flag=1;
 g_cutscene_letterbox_progress=0x34;
 g_screen_flash_alpha=0;
 if(D_001A63A8_3.mode) {
  FadeToBlack(6); snd_pump_music_and_disc_read(1); scene_load_chunk_data(0);
 } else { scene_load_chunk_data(0); FadeToBlack(6); }
 if(D_001A63A8_3.mode) snd_pump_music_and_disc_read(1);
 moby_spawn_model_parts(); level_select_data_bank();
 D_001A63A8_3.count=0;
 D_001A63A8_3.destination=g_scene_playback_state.selected+4000;
 while(!(D_001A63A8_3.state==3 && D_001A63A8_3.progress<6000)) { UpdateSoundVoices(); sceGsSyncV(0); }
 g_scene_playback_state.wait=-3;
 count=0;
 do { snd_resume_music_stream(); scene_load_chunk_data(1); } while (0);
 while(g_scene_playback_state.wait<count) { sceGsSyncV(0); count--; }
}
