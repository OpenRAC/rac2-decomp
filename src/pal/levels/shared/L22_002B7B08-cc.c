#include "names.h"
/* func_PAL_L22_002B7B08, the PAL copy of func_L22_002B7C70: the same C, where lit 0.024f becomes 0.0288f. */

extern char g_hero_state[];

extern int hero_l22_set_action(int mode, int flag);

/* Loads the level's tuning constants and starts the two subsystems. */
/* func_L22_002A8B98 is defined in L22_002A8B98-init.c. */

extern float ApproachValue(float *, float, float);
extern int g_pad_pressed_flags;
/* the two calls whose targets differ between levels 22 and 23 */
typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
} Counts_002AA678;

typedef struct {
    char pad0[5];
    unsigned char flags;
    char pad6[2];
    float fade;
    char padC[0x21 - 0xC];
    unsigned char state;
    char pad22[0x28 - 0x22];
    float unk28;
} Effect_002AA678;

typedef struct {
    char pad0[0x1E0];
    short unk1E0;
    char pad1E2[0x1870 - 0x1E2];
    Effect_002AA678 *effect; /* 0x1870 */
    char pad1874[0x187C - 0x1874];
    int active;              /* 0x187C */
    int fading;              /* 0x1880 */
    int timer;               /* 0x1884 */
    Counts_002AA678 *counts; /* 0x1888 */
    char pad188C[0x2290 - 0x188C];
    void *unk2290;
    int unk2294;
} Hero_002AA678;

/* Every access names the resident block through a struct cast, so the address's
   %hi stays in one saved register and each stretch of the body re-materialises
   its own %lo base. */
#define HERO ((Hero_002AA678 *)D_00189E20)

/* Per-frame update of the hero's effect slot (0x1870): spends the counted charges
   on the two level-specific actions, fades the effect out (releasing it at zero)
   or in, and creates it when it is allowed and absent. */
#undef HERO

extern int g_pad_pressed_flags;

/* Sets the hero's speed targets for its current mode and state, then eases the current speeds toward them (PAL: 50 Hz rates). */
extern void hero_l22_update_speed_targets_pal(void);

/* the three routines the tuning table points at; their places differ per level */
typedef unsigned char u8;

typedef unsigned short u16;

typedef float f32;

/* Restarts the run: resets the racer's state block, plays the two subsystem
   start-ups, then arms the racer for the mode the caller asked for.
   The state block is reached through three block-scoped copies of its address,
   so each stretch of the body re-materialises the base instead of keeping it
   live across the calls; the three table entries are the routines the tuning
   table points at, whose places differ from level to level. */
extern float vec_distance_xy(void *, void *);
extern float ApproachValue(float *, float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

void hero_l22_update_speed_targets_pal(void) {
    char *hero = g_hero_state;
    switch (*(u8 *)(hero + 0x22B4)) {
    case 0:
        *(float *)(hero + 0x258) = 0.8f;
        *(float *)(hero + 0x25C) = 0.7f;
        *(float *)(hero + 0x260) = 0.45f;
        break;
    case 1:
        *(float *)(hero + 0x258) = 0.59999996f;
        *(float *)(hero + 0x25C) = 0.45000002f;
        *(float *)(hero + 0x260) = 0.3f;
        break;
    case 2:
        *(float *)(hero + 0x258) = 5.25f;
        *(float *)(hero + 0x25C) = 4.45f;
        *(float *)(hero + 0x260) = 3.75f;
        break;
    }
    {
        char *hero = g_hero_state;
        if (*(int *)(hero + 0x229C) == 4) {
            if (*(short *)(hero + 0x4AC) < *(int *)(hero + 0x1B8) && !*(u8 *)(hero + 0x49E))
                *(float *)(hero + 0x25C) = *(float *)(hero + 0x4B8);
        } else if (*(int *)(hero + 0x2294) == 6) {
            *(float *)(hero + 0x25C) = 0.5f;
        } else if (*(int *)(hero + 0x2294) == 4) {
            *(float *)(hero + 0x258) = 0.35000002f;
        } else if ((unsigned)(*(int *)(hero + 0x229C) - 17) < 2) {
            *(float *)(hero + 0x258) = 0;
            *(float *)(hero + 0x25C) = 0;
        } else if (*(u8 *)(hero + 0x1492) && *(int *)(hero + 0x340)) {
            *(float *)(hero + 0x258) = 0.8f;
            *(float *)(hero + 0x25C) = 0.9f;
        } else {
            char *hero = g_hero_state;
            if (*(int *)(hero + 0x2294) == 0x7C)
                *(float *)(hero + 0x260) = 0.8f;
        }
    }
    {
        char *hero = g_hero_state;
        if (*(u8 *)(hero + 0x287) && *(int *)(hero + 0x22A4) != 18 && *(int *)(hero + 0x22B0) != 18 &&
            (*(u8 *)(hero + 0x22B4) != 0 || !(*(float *)(hero + 0x254) < 0.53f)) &&
            *(int *)(hero + 0x229C) != 17 && !*(u8 *)(hero + 0x1494) &&
            !(vec_distance_xy(hero + 0x240, hero + 0x80) > *(float *)(hero + 0x264) * 0.5f))
            return;
    }
    {
        float *speed_targets = (float *)(g_hero_state + 0x250);
        char *hero = (char *)speed_targets - 0x250;
        ApproachValue(speed_targets, *(float *)(hero + 0x258), 0.024f);
        ApproachValue(speed_targets + 1, *(float *)(hero + 0x25C), 0.024f);
        math_spring_float_to_goal(speed_targets + 5, speed_targets + 6, *(float *)(hero + 0x260), 0.028800001f, 0.43200004f, 0.080000006f);
    }
}

extern int hero_l22_set_action(int a0, int a1);

/* plays one of three resident messages, picked by the type byte; the second argument
   is 1 or 2 depending on the caller's flag */
