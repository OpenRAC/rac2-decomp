#include "include_asm.h"
#include "common.h"
typedef struct { char pad00[0x20]; short active; short slot; } Sel52C00;

extern Sel52C00 g_hero_moby_default;

extern float ref_L00_00360ED0_00 MACRO_ADDR;
extern int ref_L00_00360ED0_01 MACRO_ADDR;
extern int ref_L00_00360ED0_02 __attribute__((sda));

typedef struct { char pad00[0x0C]; int range_start; int range_end; } World2E71B8;

typedef struct {
    char pad00[0x34];
    int frame;
    char pad38[0x34];
    int start_window;
    int destination_window;
} State2E71B8;

extern World2E71B8 ref_L00_00360ED0_03;
extern State2E71B8 ref_L00_00360ED0_04;

extern void gfx_select_packet_buffer_setup(void);
extern void level_transition_scene_start(int);

/* Starts a scene: resets the fade, sets up its memory block and marks the scene as running. */
void scene_init_playback_state(void)
{
    int base;

    ref_L00_00360ED0_00 = 1.0f;
    g_hero_moby_default.active = 0;
    g_hero_moby_default.slot = -1;
    gfx_select_packet_buffer_setup();

    base = ref_L00_00360ED0_01 - 0x60000;
    ref_L00_00360ED0_04.start_window = ref_L00_00360ED0_03.range_start + base;
    ref_L00_00360ED0_04.destination_window = ref_L00_00360ED0_03.range_end + base;
    ref_L00_00360ED0_02 = base;
    level_transition_scene_start(3);
    ref_L00_00360ED0_04.frame = 1;
}
