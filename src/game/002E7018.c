#include "common.h"

extern char D_00189E20_9[];

extern char D_001A63A8_3[];

extern short D_00152C2A;

extern void func_002B72E8_1();

extern void UpdateSoundVoices();

extern void subtitle_clear_state();

extern void level_transition_scene_start();


typedef struct {
 u8 prefix[0x30];s32 state;u8 gap0[0x1c];u8 *current;u8 gap1[0x138];s32 bank[2];
} NativeContext;

extern NativeContext D_L24_001BC3C0;

extern u8 D_L24_0028AAC0[];

/* One-shot init: raises an int flag, forces a state word outside {6,7} to 5, runs three calls, then clears a 16-bit global. */
/* Resets the scene state when a scene starts. */
void scene_reset_state_on_start(void)
{
    char *gameData = D_00189E20_9;
    char *transitionData;
    unsigned short stateValue;

    if (*(int *)(gameData + 9420) <= 0) {
        *(int *)(gameData + 9420) = 1;
    }
    func_002B72E8_1(0);

    transitionData = D_001A63A8_3;
    stateValue = *(unsigned short *)(transitionData + 114);
    if ((unsigned short)(stateValue - 6) >= 2) {
        *(unsigned short *)(transitionData + 114) = 5;
    }
    UpdateSoundVoices();
    subtitle_clear_state();
    level_transition_scene_start(0);
    D_00152C2A = 0;
}

#define MACRO_ADDR __attribute__((section(".sdata")))

typedef struct { char pad[0x20]; short active; short slot; } Menu2E7090;
typedef struct { char pad[0xC]; int start; int end; } Range2E7090;
typedef struct { char pad[0x30]; int selected; int base; int page; int row; char pad40[0x6C - 0x40]; int start; int destination; } List2E7090;

extern float g_screen_fade MACRO_ADDR;
extern int D_001B15A4 MACRO_ADDR;
extern Menu2E7090 g_hero_moby_default;
extern int D_001B22B0 MACRO_ADDR;
extern Range2E7090 D_001BAEC0;
extern List2E7090 g_scene_playback_state;
extern int g_current_map_index MACRO_ADDR;
extern int g_is_pal_video MACRO_ADDR;
extern int D_001B1680 MACRO_ADDR;
extern void gfx_select_packet_buffer_setup(void);
extern void load_select_segment_update_world(int);
extern int MemcardSave(int, int);

/* Opens the list: rebases its range on the loaded block and, for the current program, lays
   out the first page (80 or 96 rows a page). */
/* Starts the scene list: sets up its memory block and loads the first page of data. */
void scene_init_list(int level)
{
    Menu2E7090 *menu = &g_hero_moby_default;
    short none = -1;
    int base;

    g_screen_fade = 1.0f;
    D_001B15A4 = 0;
    menu->active = 0;
    menu->slot = none;
    gfx_select_packet_buffer_setup();
    base = D_001B22B0 - 0x60000;
    g_scene_playback_state.start = D_001BAEC0.start + base;
    g_scene_playback_state.destination = D_001BAEC0.end + base;
    D_001B22B0 = base;
    if (g_current_map_index == level) {
        level_transition_scene_start(3);
        level = g_is_pal_video ? 0x50 : 0x60;
        g_scene_playback_state.base = 0;
        g_scene_playback_state.row = g_scene_playback_state.base / level;
        load_select_segment_update_world(g_scene_playback_state.row);
        g_scene_playback_state.page = g_scene_playback_state.base % level;
    } else {
        MemcardSave(0, level);
        D_001B1680 = level;
        menu->active = 1;
        menu->slot = none;
    }
}


/* func_002E7248 is matched in its own unit, 002E7248-qcopy.c. */


/* func_002E7570 is in 002E7018-qcopy.c (grouped lq/sq copies). */

/* func_002E76C0 is in 002E76C0-g8.c. */

extern unsigned int g_equipment_bits __attribute__((sda));
extern void ship_spawn_engine_flame(void *, int, int);

/* Draws the ship engine flames, three of them or just one depending on a game setting. */
void ship_draw_engine_flames(void *object)
{
    int count = ((g_equipment_bits >> 4) & 1) ? 3 : 1;
    int index;
    for (index = 0; index < count; index++)
        ship_spawn_engine_flame(object, index, 0);
}


/* func_002E7BC8 is in 002E7BC8-g8.c. */


/* func_002E8190 is matched in 002E7018-g8.c (-G8 small data). */

extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void DrawTexturedQuad(int, char *, int, int, int, int, int, int, unsigned long long, unsigned long long);
extern char *g_screen_height __attribute__((sda));
extern unsigned long long D_001B2168 __attribute__((sda));

/* Draws a fading overlay strip across the screen with the given see-through amount. */
void gfx_draw_fade_strip(int alpha)
{
    unsigned long long color;
    unsigned long long packet;
    char *dst;

    VU1_addGSregister(0x47, 0x31801ULL);
    VU1_addGSregister(0x42, 0x8000000044ULL);
    color = (alpha << 24) | 0x00808080;
    packet = D_001B2168;
    dst = g_screen_height;
    DrawTexturedQuad(0x20, dst - 0x58, 0x100, 0x20, 0, 0, 0x100, 0x20, color, packet);
    VU1_addGSregister(0x47, 0x5360BULL);
}


/* func_002E8368 is matched in 002E7018-transition-g8.c. */

/* func_002E8BA8 is matched in 002E8BA8-g8.c. */



/* func_002E9268 is in 002E9268.c. */

extern short D_00152C20;
extern int D_001B1594 __attribute__((sda));
extern void gfx_render_frame_all_layers(void);
extern void RenderFrame(void);
extern void transition_render_scene(void);

/* Draws the background of the transition screen for the current transition type. */
void transition_draw_background(void)
{
    switch (D_00152C20) {
    case 0:
    case 3:
        gfx_render_frame_all_layers();
        break;
    case 1:
        D_001B1594 = 127;
        RenderFrame();
        break;
    case 2:
        transition_render_scene();
        break;
    }
}


extern void func_001325E8(void *, void (*)(int, long), long long);
extern void FlushCache(int);
extern int sceGsSyncV(int);
extern int snd_Pump(void);
extern void snd_store_result(int, long);

/* Starts a background load and waits until it reports back. */
void load_run_async_and_wait(void *arg, int *status) {
    *status = -1;
    func_001325E8(arg, snd_store_result, (unsigned long long)(unsigned int)status);
    {
        int sentinel = -1;
        do {
            FlushCache(0);
            sceGsSyncV(0);
            snd_Pump();
        } while (*status == sentinel);
    }
}

/* func_002EAB18 is in 002E7018-load.c (its views of D_00152C00 and D_001BAEC0 differ from this file's). */


/* D_001B8840 is declared above func_002E7090 (List2E7090). */
extern char g_copy_setup_data[];
extern int load_start_disc_read(int, int, int);
extern void snd_pump_music_and_disc_read(int);

/* Loads the data for one chunk of the current scene. */
int scene_load_chunk_data(int index)
{
    char *table = g_copy_setup_data;
    int row = g_scene_playback_state.selected * 0x14C;
    int destination = g_scene_playback_state.destination;
    int base = (int)(table + 0x3EA8);
    int first = *(int *)((index << 2) + row + base);
    int count = *(int *)(((index + 1) << 2) + row + base) - first;
    if (count > 0) {
        load_start_disc_read(destination, first + *(int *)(table + 0x3E24), count);
        snd_pump_music_and_disc_read(0);
    }
    return 1;
}

/* func_002EB1E0 is matched in its own unit, 002EB1E0.c (-frac2-gcse-unsplit-edges). */


/* func_002EB7E8 is in 002EB7E8-g8.c (-G8 small data). */

/* func_002EBAA8 is in 002EBAA8-g8.c (-G8 small data). */


/* func_002EBC70 is in 002EBC70-g8.c (-G8 small data). */

/* func_002EBDF0 is matched in 002EBDF0-g8.c. */

/* func_002EC1C0 is matched in 002E7018-g8.c (-G8 small data). */

/* func_002EC408 is in 002EC408-g8.c (-G8 small data). */

/* func_002ECB70 is matched in 002ECB70-g8.c (-G8 small data, -fno-gcse). */


/* selects the level data bank when the resident context is in state 9 */
void level_select_data_bank(void) {
 s32 index=-1;
 if(D_L24_001BC3C0.state==9) index=1;
 if(index!=-1) {
  D_L24_001BC3C0.current=D_L24_0028AAC0;
  *(s32 *)(D_L24_0028AAC0+0x68)=D_L24_001BC3C0.bank[index];
 }
}

