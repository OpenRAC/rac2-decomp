#include "names.h"
/* func_PAL_L14_00418800, the PAL copy of func_L14_004137F8: the same C. */
#include "common.h"
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern char g_sound_state[];
extern void gfx_draw_scrolling_surface_quad(void *);
extern char D_L14_001B9500[];
extern float math_fast_sin_or_cos_b(float);
extern char g_hero_position[];
/* The same entity-base pointer is read both absolutely and through $gp. */
extern char *D_L14_001B259C_direct __asm__("D_L14_001B259C") __attribute__((sda));
extern int IsPointInCuboid(void *, int);
extern void moby_mark_spawned(void *);

typedef int PrisonQword __attribute__((mode(TI)));
typedef struct { PrisonQword v[4]; } PrisonMatrix;
extern PrisonMatrix D_L14_001B1A00;

extern void gfx_draw_rotated_billboard(void *, int, int, int, float, float, float);
extern float math_wrap_angle_full_turn(float);
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
extern int math_fast_float_d(void *);
/* Help-message (subtitle) history: how often each message was shown, when, and in which levels. */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;

typedef struct {
    char pad[4];
    unsigned char level;
    char rest[0xDB];
} PrisonGadget;

extern SubtitleHistory g_subtitle_history[];
extern u8 D_0019B2E8[];
extern PrisonGadget D_L14_002686F0[];
extern int g_current_map_index __attribute__((sda));
/* True once the gadget in slot 10 has been upgraded. */

/* Shows help message MSG unless its history entry IDX says it was shown in the last 18 seconds. */

/* The first time only records history entry IDX as seen in this level; later times show MSG. */

/* Drives the prison's help prompts: links the target moby, plays the hints at the trigger zones
   and records which help messages were already shown. */
/* Read the word at offset 0x 18 through the pointer stored at owner offset 0x 68. */
unsigned int func_PAL_L14_00418800(unsigned int param_1)
{
    unsigned int inner_ptr;
    unsigned int result;

    inner_ptr = *(unsigned int *)(param_1 + 0x68);
    result = *(unsigned int *)(inner_ptr + 0x18);
    return result;
}

/* Normalises and combines two temporary vectors from a state block, dispatches on the combined result and conditionally scales the output vector. */
/* Looks up the graph nodes of first and second and, when they differ, sets (or with clear,
   clears) bit 7 of the link between them in both nodes' four link bytes. The links of node 0
   serve as the base for both scans, and both scans read the two ids from their stack slots. */
/* func_L14_00421BC0 is in L14_003F4F98-f7-g8.c. */

/* func_L14_004221D8 is defined in L14_003F4F98-ribbon-g8.c (it reaches data through $gp and needs -frac2-qcopy). */

/* func_L14_004228C0 is defined in L14_003F4F98-g8.c. */

/* func_L14_004229A0 is defined in L14_003F4F98-ribbon-g8.c. */

/* func_L14_00423000 is defined in L14_00423000-qcopy.c (it needs the quadword-copy profile). */

/* func_L14_00423358 lives in L14_00423358-g8.c (small-data accesses). */

/* The level's own jump table (the label of the data blob at 0x002AA360). */
/* Dispatches on the owner's animation step and plays the matching bone animation. */
extern char D_L14_001B9500[];

/* Restarts the owner's animation: two timed fades, the counter, then the panic state. */
/* func_L14_00423E50 is defined in L14_00423E50-gu.c (it needs -frac2-gcse-unsplit-edges). */

/* The 0x100-byte entity record (PrisonEntity, declared further down), with only the
   fields this function uses. */
extern u8 D_0019B2E8[];
extern char g_hero_position[];
extern int g_current_map_index __attribute__((sda));
extern int IsPointInCuboid(void *, int);
extern int flag_set_first_pending(void *);
 /* the parameter is unused */
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
extern int math_fast_float_d(void *);
extern float math_fast_sin_or_cos_b(float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void snd_queue_level_jingle(char *);

/* func_L14_00426D18 lives in the -g8 sibling file (it reads a count through $gp). */

/* Queues the level jingle for the owner with the volume its state block asks for. */
void snd_queue_level_jingle(char *a0);

/* func_L14_00426F28 is defined in L14_003F4F98-g8.c (it reaches data through $gp). */

/* func_L14_00427250 lives in the -g8 sibling file (it reaches a global through $gp). */

/* func_L14_004281D0 is defined in L14_004281D0-g8.c (it reaches data through $gp and needs the quadword-copy profile). */

/* The same global as D_L14_001B259C, under a second name: this access is
   $gp-relative, that one absolute. */
/* Walks the 0x7FFF-masked id list at table[index] and flags class 0x112B entries. */
/* func_L14_00428A08 lives in the -g8 sibling file (it reads a count through $gp). */

/* func_L14_00428BA0 lives in the -g8 sibling file (it reads two globals through $gp). */

/* func_L14_00428E68 is defined in L14_00428E68-g8.c. */

/* func_L14_004295D0 is defined in L14_004295D0-g8.c (it reaches data through $gp). */

/* Fills the owner's screen slot with the width the display state reports. */
/* func_L14_0042FB10 is defined in L14_0042FB10-effect-g8.c. */

/* Per-object state of the sliding gate (func_L14_0042FDA8). */
/* A 0x100-byte entity record. */
/* Gate logic: opens when the player nears, is hit open by linked objects, and
   hands off to the next object when it slides clear. */
/* func_L14_00430410 is defined in L14_00430410-g8.c. */

float math_wrap_angle_full_turn(float x);

/* Builds a camera-facing quad and rotates its texture coordinates about their center. */
void gfx_draw_rotated_billboard(void *position, int texture, int color, int mode, float scale, float distance, float angle);


/* func_L14_00430B70 is defined in L14_00430B70-visual.c. */

/* func_L14_00430E08 is defined in L14_00430B70-visual.c. */

/* Distinct no-op entries: the first is called directly, the second by the moby table. */
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern char g_sound_state[];
extern void gfx_draw_scrolling_surface_quad(void *);

