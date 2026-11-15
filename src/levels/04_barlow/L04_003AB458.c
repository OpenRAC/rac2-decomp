#include "include_asm.h"
#include "names.h"

typedef unsigned short u16;

extern void FastDecTimer(void *);
extern void set_moby_color(void *, int, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void gfx_update_color_fade(void *, void *);
extern void gfx_add_draw_callback_first(void *);
extern void render_water_grids(void *, int);
extern char D_L04_002AF6C0[];

extern void moby_transform_joint_to_world(void *, int, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern void gfx_draw_tether_beam_red(void *, void *);
extern void gfx_draw_tether_beam_white(void *, void *);

typedef struct L04_003E5318_BUF {
    float f[6];
    int z;
} L04_003E5318_BUF;

/* func_L04_003E5298 is defined in L02_003CE9A8-g8.c. */

typedef unsigned int TI2338 __attribute__((mode(TI)));
typedef struct {
    char pad[0x280];
    TI2338 position;
    char pad290[0x60];
    int slots[4];
    char pad300[6];
    unsigned char current;
} Private2338;
typedef struct {
    char pad[0x30];
    TI2338 position;
    char pad40[0x40];
} Record2338;
extern void memset(void *, int, int);
extern void math_trap_always(void);
extern int math_random_int_range(int, int);
extern char *D_L04_001B25CC __attribute__((sda));

/* Draws the beam effect from the linked object's attachment point. */
void object_draw_linked_beam(char *mobyArg)
{
    char *moby = mobyArg;
    char *vars = *(char **)(moby + 0x68);
    char *linked = *(char **)(vars + 0x2AC);
    L04_003E5318_BUF start;

    if (linked != 0) {
        char *linkedVars = *(char **)(linked + 0x68);

        moby_transform_joint_to_world(*(char **)(linkedVars + 0x288), 0, &start);
        start.f[4] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * 0.1f;
        start.f[5] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * 0.1f;
        start.z = 0;
        FastVecAdd(&start, &start, start.f + 4);
        start.f[2] = start.f[2] - 0.05f;
        gfx_draw_tether_beam_red(moby, &start);
        gfx_draw_tether_beam_white(moby, &start);
    }
}

/* Does the per-frame upkeep of the object and counts up its age, stopping at the maximum. */
void object_update_age_timer(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    u16 age;

    gfx_update_color_fade(moby, vars + 0x50);
    FastDecTimer(vars + 0x2A0);
    FastDecTimer(vars + 0x2A2);
    age = *(u16 *)(moby + 0x96);
    if (age <= 0xFFFE) {
        *(u16 *)(moby + 0x96) = age + 1;
    }
}

/* Releases the linked object and clears the link to it. */
void object_release_linked(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    if (*(char **)(vars + 0x2AC) != 0) {
        anim_start_blended(*(char **)(vars + 0x2AC), 9, 0, 3);
        *(int *)(*(char **)(*(char **)(vars + 0x2AC) + 0x68) + 0x27C) = 0;
        *(char **)(vars + 0x2AC) = 0;
    }
}

/* Runs the shared level routine on the standard list with a count of 10. */
void group_run_shared_routine(void)
{
    render_water_grids(D_L04_002AF6C0, 10);
}

typedef unsigned char u8;
typedef int s32;
typedef float f32;
extern u8 g_sound_state[];
extern char g_hero_position[];
extern s32 func_00342228(void *, s32);
extern s32 func_00382FF0(s32, s32, void *);
extern s32 func_0033D168(s32, s32);
extern void func_00382AF8(s32);
extern void func_003317E8(void *);
extern f32 func_0030EFA8(void *, void *);

/* Keeps a sound playing for the object while the player is close, and stops it when the player moves away or the object ends. */
void proximity_loop_sound_update(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (func_00342228(g_hero_position, *(s32 *)vars) != 0) {
        u8 *sound = g_sound_state + *(s32 *)(vars + 8) * 0x70;
        if (*(u8 **)(sound + 0x88) != moby || *(u8 *)(sound + 0x74) == 0) {
            *(s32 *)(vars + 8) = func_00382FF0(0x17, 4, moby);
        }
    }
    if (func_0033D168(*(s32 *)(vars + 4), -1) < 7) {
        s32 soundId = *(s32 *)(vars + 8);
        if (soundId != -1) {
            u8 *sound = g_sound_state + soundId * 0x70;
            if (*(u8 **)(sound + 0x88) == moby && *(u8 *)(sound + 0x74) != 0)
                func_00382AF8(soundId);
        }
        *(s32 *)(vars + 8) = -1;
        func_003317E8(moby);
    } else {
        u8 *sound = g_sound_state + *(s32 *)(vars + 8) * 0x70;
        if (*(u8 **)(sound + 0x88) == moby && *(u8 *)(sound + 0x74) != 0) {
            if (func_0030EFA8(moby + 0x10, g_hero_position) > 50.0f) {
                s32 soundId = *(s32 *)(vars + 8);
                if (soundId != -1) {
                    u8 *sound = g_sound_state + soundId * 0x70;
                    if (*(u8 **)(sound + 0x88) == moby && *(u8 *)(sound + 0x74) != 0)
                        func_00382AF8(soundId);
                }
                *(s32 *)(vars + 8) = -1;
            }
        }
    }
}



/* Switches the object, and its linked object if it has one, to new states. */
void object_set_linked_states(char *moby, int stateA, int stateB, int arg3, int arg4)
{
    char *vars = *(char **)(moby + 0x68);

    if (*(char **)(vars + 0x2AC) != 0) {
        anim_start_blended(moby, stateA, arg3, arg4);
        anim_start_blended(*(char **)(vars + 0x2AC), stateB, arg3, arg4);
    } else if (*(unsigned char *)(moby + 0x43) != stateA) {
        anim_start_blended(moby, stateA, arg3, arg4);
    }
}

/* Picks a random other slot that is in use and moves the object to that slot's position. */
void SelectRandomOtherLiveSlot(char *moby)
{
    Private2338 *vars = *(Private2338 **)(moby + 0x68);
    int values[3];
    int slotIndex;
    int count = 0;
    int *slotPtr = vars->slots;
    int none = -1;

    memset(values, 0, 12);
    slotIndex = 0;
    for (;;) {
        if (slotIndex != vars->current) {
            if (*(int *)slotPtr != none) {
                count++;
                if (count < 4)
                    values[count - 1] = slotIndex;
                else
                    math_trap_always();
            }
        }
        slotIndex++;
        if (slotIndex >= 4)
            break;
        slotPtr++;
    }
    if (count != 0) {
        int pick = math_random_int_range(0, count - 1);
        vars->current = (unsigned char)values[pick];
        vars->position = ((Record2338 *)D_L04_001B25CC)[vars->slots[vars->current]].position;
    }
}

/* func_L04_003E4C00 is defined in L04_003E4C00.c. */

/* func_L04_003E5B10 is defined in L04_003E5B10.c. */

/* func_L04_003E7E68 is defined in L04_003E7E68-g32.c. */

/* func_L04_003E8010 is defined in L04_003E8010.c. */

/* func_L04_003EB8D8 is defined in L04_003EB8D8.c. */

/* func_L04_003EC140 is defined in L04_003EC140-g8.c. */

/* func_L04_003ED3D8 is defined in L04_003ED3D8.c. */

/* func_L04_003ED740 is defined in L04_003ED740.c. */





/* Defined in L04_00412AF8.c. */

/* func_L04_00422318 is defined in L04_00422318-g8.c. */
