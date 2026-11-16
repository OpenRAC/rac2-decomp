#include "include_asm.h"
#include "names.h"


extern char D_00189E20_9[];
extern char D_001A63A8_3[];
extern short g_scene_reset_flag;
extern void func_002B72E8_1();
extern int UpdateSoundVoices();
extern void subtitle_clear_state();
extern void level_transition_scene_start();

/* One-shot init: raises an int flag, forces a state word outside {6,7} to 5, runs three calls, then clears a 16-bit global. */
void scene_reset_state_on_start_us2(void)
{
    char *p = D_00189E20_9;
    char *q;
    unsigned short v;

    if (*(int *)(p + 9420) <= 0) {
        *(int *)(p + 9420) = 1;
    }
    func_002B72E8_1(0);

    q = D_001A63A8_3;
    v = *(unsigned short *)(q + 114);
    if ((unsigned short)(v - 6) >= 2) {
        *(unsigned short *)(q + 114) = 5;
    }
    UpdateSoundVoices();
    subtitle_clear_state();
    level_transition_scene_start(0);
    g_scene_reset_flag = 0;
}

#include "common.h"
extern void level_transition_scene_start_us2();
#define MACRO_ADDR __attribute__((section(".sdata")))
typedef struct { char pad[0x20]; short active; short slot; } Menu2E7090;
typedef struct { char pad[0xC]; int start; int end; } Range2E7090;
typedef struct { char pad[0x30]; int selected; int base; int page; int row; char pad40[0x6C - 0x40]; int start; int destination; } List2E7090;
extern float g_screen_fade MACRO_ADDR;
extern int g_screen_flash_alpha MACRO_ADDR;
extern Menu2E7090 g_hero_moby_default;
extern int g_packet_buffer_size MACRO_ADDR;
extern Range2E7090 g_loader_memory;
extern List2E7090 g_scene_playback_state;
extern int g_current_map_index MACRO_ADDR;
extern int g_is_pal_video MACRO_ADDR;
extern int g_small_data_value MACRO_ADDR;
extern void gfx_select_packet_buffer_setup(void);
extern void load_select_segment_update_world(int);
extern int MemcardSave(int, int);

/* Opens the list: rebases its range on the loaded block and, for the current program, lays
   out the first page (80 or 96 rows a page). */
void scene_init_list_us2(int level)
{
    Menu2E7090 *menu = &g_hero_moby_default;
    short none = -1;
    int base;

    g_screen_fade = 1.0f;
    g_screen_flash_alpha = 0;
    menu->active = 0;
    menu->slot = none;
    gfx_select_packet_buffer_setup();
    base = g_packet_buffer_size - 0x60000;
    g_scene_playback_state.start = g_loader_memory.start + base;
    g_scene_playback_state.destination = g_loader_memory.end + base;
    g_packet_buffer_size = base;
    if (g_current_map_index == level) {
        level_transition_scene_start_us2(3);
        level = g_is_pal_video ? 0x50 : 0x60;
        g_scene_playback_state.base = 0;
        g_scene_playback_state.row = g_scene_playback_state.base / level;
        load_select_segment_update_world(g_scene_playback_state.row);
        g_scene_playback_state.page = g_scene_playback_state.base % level;
    } else {
        MemcardSave(0, level);
        g_small_data_value = level;
        menu->active = 1;
        menu->slot = none;
    }
}



