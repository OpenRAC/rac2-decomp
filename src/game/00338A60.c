#include "include_asm.h"
#include "names.h"

extern void text_panel_update_fade(char *a0);

extern void func_L00_0042E388_1(char *a0);

extern void func_L00_0042E138_1(char *a0);

extern void func_L00_0042BAD0_10(void *p);

extern void func_L00_0042C290_10(void *p);

extern void func_00336320_1(char *a);

extern void func_00336A78_1(char *a);

/* Returns early when a float field reached through a two-level pointer chain is exactly zero; otherwise dispatches on an integer state (0 or 2 selects one of two callees) and then always calls a third callee with the same object pointer. */
/* Updates a text panel each frame according to its mode, unless it is hidden. */
void text_panel_update_mode(char *panel)
{
    if (*(float *)(*(int *)(panel + 4)) == 0.0f)
        return;

    switch (*(int *)(panel + 456))
    {
    case 0:
        text_panel_update_fade(panel);
        break;
    case 2:
        func_L00_0042E388_1(panel);
        break;
    }

    func_L00_0042E138_1(panel);
}


/* Does nothing. */
void ui_nop_d(char *object)
{
}

/* func_00338F58 is matched in 00338F58.c. */

/* Initialises eight sub-objects at byte offsets 8, 84, 160, 236 (step 76) and 312, 384, 456, 528 (step 72) of the argument with two different helpers and returns the argument. */
/* Sets up the eight text parts of the mission screen and returns the screen. */
void *mission_screen_init_parts(char *screen)
{
    func_L00_0042BAD0_10(screen + 8);
    func_L00_0042BAD0_10(screen + 84);
    func_L00_0042BAD0_10(screen + 160);
    func_L00_0042BAD0_10(screen + 236);
    func_L00_0042C290_10(screen + 312);
    func_L00_0042C290_10(screen + 384);
    func_L00_0042C290_10(screen + 456);
    func_L00_0042C290_10(screen + 528);
    return screen;
}


/* func_00339078 is defined in 00339078-g16.c. */

typedef struct { float x, y; } Float2_00339320;

typedef struct {
    char pad[0x1C8];
    unsigned short count;
    unsigned short unused;
    unsigned int maximum;
    unsigned int levels;
} Statistics_00339320;

extern void object_set_first_float4(void *, float, float, float, float);
/* The retail callee hands a value back in v0; the declaration says so because v0
   then stays the call's return register and is not handed to the tail's reloads. */
extern int text_format_location_name(void *, int);

/* The three position pairs live in the program's own data, so they have no address
   of their own: each program reads them from its own bytes. */
extern Float2_00339320 ref_L00_0042EC50_00;
extern Float2_00339320 ref_L00_0042EC50_01;
extern Float2_00339320 ref_L00_0042EC50_02;

extern int g_game_time __attribute__((sda));
extern int D_001C51D0;
extern unsigned int D_001A7390 __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern Statistics_00339320 g_progress_statistics;

/* Places the seven sub-objects of the argument at their world positions, hands the
   current level to the one at +0x258, and updates the statistics block: the visit
   count once the game time has reached 11, the highest level number seen and the
   bit of the level that was reached. */
int mission_screen_place_parts(char *screen)
{
    Float2_00339320 z0 = {0.0f, 0.0f};
    Float2_00339320 z1 = {0.0f, 0.0f};
    Float2_00339320 z2 = {0.0f, 0.0f};
    Float2_00339320 z3 = {0.0f, 0.0f};
    Float2_00339320 g0 = ref_L00_0042EC50_00;
    Float2_00339320 g1 = ref_L00_0042EC50_01;
    Float2_00339320 g2 = ref_L00_0042EC50_02;

    object_set_first_float4(screen + 8, z0.x + (*(float **)(screen + 4))[0], z0.y + (*(float **)(screen + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(screen + 0x54, z3.x + (*(float **)(screen + 4))[0], z3.y + (*(float **)(screen + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(screen + 0xA0, z1.x + (*(float **)(screen + 4))[0], z1.y + (*(float **)(screen + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(screen + 0xEC, z2.x + (*(float **)(screen + 4))[0], z2.y + (*(float **)(screen + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(screen + 0x138, g0.x + (*(float **)(screen + 4))[0], g0.y + (*(float **)(screen + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(screen + 0x180, g1.x + (*(float **)(screen + 4))[0], g1.y + (*(float **)(screen + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(screen + 0x1C8, g2.x + (*(float **)(screen + 4))[0], g2.y + (*(float **)(screen + 4))[1], 0.0f, 0.0f);
    text_format_location_name(screen + 0x258, D_001C51D0);
    if (g_game_time >= 11) {
        if (g_progress_statistics.count < 0xffff) g_progress_statistics.count++;
    }
    if (D_001A7390 > g_progress_statistics.maximum) g_progress_statistics.maximum = D_001A7390;
    g_progress_statistics.levels = (g_progress_statistics.levels | (1u << g_current_map_index)) | 0x80000000u;
    return 0;
}

/* early-returns when a 32-bit field is zero, otherwise calls one helper four times and another three times with fixed byte offsets off the argument pointer. */
/* Draws the seven text parts of the mission screen, if it is visible. */
void mission_screen_draw_parts(char *screen)
{
    if (*(int *)(screen + 664) == 0)
        return;
    func_00336320_1(screen + 8);
    func_00336320_1(screen + 84);
    func_00336320_1(screen + 160);
    func_00336320_1(screen + 236);
    func_00336A78_1(screen + 312);
    func_00336A78_1(screen + 384);
    func_00336A78_1(screen + 456);
}

/* Shuts down the mission screen's parts and returns the screen. */
char *mission_screen_shutdown(char *screen)
{
    extern void prompt_bar_destroy(void *);
    extern void *object_construct_derived_a(void *);
    prompt_bar_destroy(screen + 8);
    object_construct_derived_a(screen + 0x2A8);
    return screen;
}
