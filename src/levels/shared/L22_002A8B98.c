#include "include_asm.h"
#include "names.h"

extern char g_hero_state[];

extern int g_current_map_index;

extern int g_hero_aim_speed_start;

extern unsigned char g_item_slot_to_record[];

extern char g_weapon_l22_table[];

extern char g_pickup_entry_table[];

extern void hero_clear_queued_anim(void);

extern int hero_l22_set_move_state(int mode, int flag);

extern void trail_reset_slots(void);

extern int hero_slot_item_id(int index);

/* Loads the level's tuning constants and starts the two subsystems. */
/* func_L22_002A8B98 is defined in L22_002A8B98-init.c. */


extern void hero_build_relative_point(void *, int, float, float, float);
extern float ApproachValue(float *, float, float);
extern int g_pad_pressed_flags;
extern int PadPressedWithin(int, int, int);
extern int player_slot_has_object(void *);
extern void release_moby_animation_slot(void *, void *);
extern void *allocate_moby_animation_slot(void *, int);
extern void initialize_moby_animation_blend(void *, void *, int, int, int, int);
extern void AdvanceAndDecodeAnimationFrames(void *, void *);
extern int math_fast_float_d(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_add_transformed_point(void *, void *, float, float, float);
/* the two calls whose targets differ between levels 22 and 23 */
extern void ref_L22_002AA678_00(void *, void *, int);
extern void ref_L22_002AA678_01(void *, void *, int, int, int);

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
void hero_update_effect_slot(void) {
    float v[4];
    int available;
    int i;

    if (HERO->unk1E0)
        return;
    if (HERO->unk2294 == 1 && PadPressedWithin(16, 7, 0) && !player_slot_has_object(HERO->unk2290) &&
        HERO->counts->unkC) {
        hero_build_relative_point(v, 1, 2.0f, -2.1f, 8.7f);
        ref_L22_002AA678_00(HERO->unk2290, v, 1);
        HERO->counts->unkC--;
    }
    available = 1;
    if (!HERO->counts->unk8 || player_slot_has_object(HERO->unk2290))
        available = 0;
    if ((unsigned)(HERO->unk2294 - 0x5D) <= 1)
        available = 0;
    if (HERO->active) {
        if (!HERO->counts->unk8) {
            if (HERO->effect) {
                if (HERO->effect->flags & 2)
                    HERO->fading = 1;
                if (HERO->fading) {
                    if (HERO->effect->fade == 0) {
                        release_moby_animation_slot(HERO->unk2290, &HERO->effect);
                        HERO->active = 0;
                        return;
                    }
                    ApproachValue(&HERO->effect->fade, 0, 0.07f);
                }
            } else
                HERO->active = 0;
        }
    }
    if (HERO->active) {
        if (!(g_pad_pressed_flags & 0x20) || !available) {
            if (HERO->effect) {
                if (HERO->effect->flags & 2)
                    HERO->fading = 1;
                if (HERO->fading) {
                    if (HERO->effect->fade == 0) {
                        release_moby_animation_slot(HERO->unk2290, &HERO->effect);
                        HERO->active = 0;
                        return;
                    }
                    ApproachValue(&HERO->effect->fade, 0, 0.07f);
                }
            } else
                HERO->active = 0;
        } else if (HERO->counts->unk8)
            HERO->fading = 0;
    }
    if (!HERO->active && available && PadPressedWithin(32, 8, 0)) {
        Effect_002AA678 *p = allocate_moby_animation_slot(HERO->unk2290, 2);
        HERO->fading = 0;
        HERO->effect = p;
        if (p) {
            HERO->active = 1;
            initialize_moby_animation_blend(HERO->unk2290, p, 13, 0, 9, 1);
        }
    }
    if (!HERO->active || !HERO->effect || HERO->fading)
        return;
    ApproachValue(&HERO->effect->fade, 1, 0.13f);
    HERO->effect->unk28 = 2;
    AdvanceAndDecodeAnimationFrames(HERO->unk2290, HERO->effect);
    math_fast_float_d(&HERO->timer);
    if (HERO->effect->state == 4 && !HERO->timer) {
        HERO->timer = 5;
        for (i = 0; i < 2; i++) {
            moby_transform_joint_to_world(HERO->unk2290, i + 3, v);
            vec_add_transformed_point(HERO->unk2290, v, 1.4f, 0, 0);
            if (HERO->counts->unk8) {
                ref_L22_002AA678_01(HERO->unk2290, v, 0, 0, HERO->counts->unk0 != 0);
                HERO->counts->unk8--;
            }
        }
    }
}

#undef HERO

extern int g_pad_pressed_flags;

extern void cancel_hero_item_animation(void);

extern void UpdateHeroSlotCallbacks(void);

extern void level_release_slot_list(void *p);

extern void hero_set_objects_flag_bit(void);

extern void hero_clear_tracked_slots(void);

extern void attachment_reset_all(void);

extern int hud_set_slot_contents(int a0, int a1, void *a2, void *a3, void *a4, int a5, int a6);

extern int level_run_slot_callback(int a0);

extern void hero_l22_update_speed_targets(void);

extern void func_002A677C(int a0);

/* the three routines the tuning table points at; their places differ per level */
extern void ref_L22_002B70F8_00(void);

extern void ref_L22_002B70F8_01(void);

extern void ref_L22_002B70F8_02(void);

typedef unsigned char u8;

typedef unsigned short u16;

typedef float f32;

/* Restarts the run: resets the racer's state block, plays the two subsystem
   start-ups, then arms the racer for the mode the caller asked for.
   The state block is reached through three block-scoped copies of its address,
   so each stretch of the body re-materialises the base instead of keeping it
   live across the calls; the three table entries are the routines the tuning
   table points at, whose places differ from level to level. */
void hero_restart_in_mode(int mode, int entryId, void *mobyArg) {
    char *hero = g_hero_state;

    cancel_hero_item_animation();
    hero[0x22B6] = 1;
    UpdateHeroSlotCallbacks();
    *(int *)(hero + 0x2290) = *(int *)(hero + 0xC18);
    level_release_slot_list(hero + 0x18E0);
    level_release_slot_list(hero + 0x1A30);
    *(int *)(*(int *)(hero + 0x2290) + 0x9C) = -1;
    if (mode != 4 || *(u8 *)(hero + 0x22B4) != mode)
        hero_set_objects_flag_bit();
    hero_clear_tracked_slots();
    attachment_reset_all();
    {
        char *heroAfter = g_hero_state;

        *(u8 *)(heroAfter + 0x22B4) = (u8)mode;
        *(int *)(heroAfter + 0xC14) = (int)mobyArg;
        *(int *)(heroAfter + 0x2290) = (int)mobyArg;
    }
    if ((mode & 0xFF) == 1) {
        if (g_pad_pressed_flags & 0x10) {
            hud_set_slot_contents(0x23, 0, &ref_L22_002B70F8_00, &ref_L22_002B70F8_01,
                          &ref_L22_002B70F8_02, 0, 0);
            level_run_slot_callback(3);
        }
    }
    hero_l22_update_speed_targets();
    {
        char *heroInit = g_hero_state;

        *(f32 *)(heroInit + 0x250) = *(f32 *)(heroInit + 0x258);
        *(f32 *)(heroInit + 0x254) = *(f32 *)(heroInit + 0x25C);
        *(u16 *)(*(int *)(heroInit + 0x2290) + 0x34) |= 6;
        *(f32 *)(heroInit + 0xC20) = 1.0f;
        *(f32 *)(heroInit + 0xC24) = 1.0f;
        hero_clear_queued_anim();
        func_002A677C(*(int *)(heroInit + 0x2290));
        *(u16 *)(heroInit + 0x24F2) = (u16)entryId;
        switch (mode) {
        case 1:
            *(u16 *)(heroInit + 0x24D4) = *(u16 *)(heroInit + 0x24CC);
            *(int *)(heroInit + 0x24CC) = *(int *)(heroInit + 0x24D0);
            if (*(int *)(heroInit + 0x24D0) >= 5)
                *(int *)(heroInit + 0x24CC) = 4;
            break;
        case 2:
            *(int *)(heroInit + 0x1874) = 0x4B0;
            break;
        }
    }
    hero_l22_set_move_state(entryId, 2);
}


extern float vec_distance_xy(void *, void *);
extern float ApproachValue(float *, float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

/* Sets the hero's movement speed targets for the current mode and eases the current speeds toward them. */
void hero_l22_update_speed_targets(void) {
    char *g = g_hero_state;
    switch (*(u8 *)(g + 0x22B4)) {
    case 0:
        *(float *)(g + 0x258) = 0.8f;
        *(float *)(g + 0x25C) = 0.7f;
        *(float *)(g + 0x260) = 0.45f;
        break;
    case 1:
        *(float *)(g + 0x258) = 0.59999996f;
        *(float *)(g + 0x25C) = 0.45000002f;
        *(float *)(g + 0x260) = 0.3f;
        break;
    case 2:
        *(float *)(g + 0x258) = 5.25f;
        *(float *)(g + 0x25C) = 4.45f;
        *(float *)(g + 0x260) = 3.75f;
        break;
    }
    {
        char *g = g_hero_state;
        if (*(int *)(g + 0x229C) == 4) {
            if (*(short *)(g + 0x4AC) < *(int *)(g + 0x1B8) && !*(u8 *)(g + 0x49E))
                *(float *)(g + 0x25C) = *(float *)(g + 0x4B8);
        } else if (*(int *)(g + 0x2294) == 6) {
            *(float *)(g + 0x25C) = 0.5f;
        } else if (*(int *)(g + 0x2294) == 4) {
            *(float *)(g + 0x258) = 0.35000002f;
        } else if ((unsigned)(*(int *)(g + 0x229C) - 17) < 2) {
            *(float *)(g + 0x258) = 0;
            *(float *)(g + 0x25C) = 0;
        } else if (*(u8 *)(g + 0x1492) && *(int *)(g + 0x340)) {
            *(float *)(g + 0x258) = 0.8f;
            *(float *)(g + 0x25C) = 0.9f;
        } else {
            char *g = g_hero_state;
            if (*(int *)(g + 0x2294) == 0x7C)
                *(float *)(g + 0x260) = 0.8f;
        }
    }
    {
        char *g = g_hero_state;
        if (*(u8 *)(g + 0x287) && *(int *)(g + 0x22A4) != 18 && *(int *)(g + 0x22B0) != 18 &&
            (*(u8 *)(g + 0x22B4) != 0 || !(*(float *)(g + 0x254) < 0.53f)) &&
            *(int *)(g + 0x229C) != 17 && !*(u8 *)(g + 0x1494) &&
            !(vec_distance_xy(g + 0x240, g + 0x80) > *(float *)(g + 0x264) * 0.5f))
            return;
    }
    {
        float *speeds = (float *)(g_hero_state + 0x250);
        char *g = (char *)speeds - 0x250;
        ApproachValue(speeds, *(float *)(g + 0x258), 0.02f);
        ApproachValue(speeds + 1, *(float *)(g + 0x25C), 0.02f);
        math_spring_float_to_goal(speeds + 5, speeds + 6, *(float *)(g + 0x260), 0.02f, 0.3f, 0.06666667f);
    }
}



extern unsigned char g_screen_mode_flag;

extern int hero_l22_set_move_state(int a0, int a1);

/* plays one of three resident messages, picked by the type byte; the second argument
   is 1 or 2 depending on the caller's flag */
void text_play_mode_message(int slow) {
    unsigned char type = g_screen_mode_flag;
    int mode = 1;

    if (slow != 0)
        mode = 2;
    switch (type) {
    case 0:
        hero_l22_set_move_state(0, mode);
        break;
    case 1:
        hero_l22_set_move_state(0x3F, mode);
        break;
    case 2:
        hero_l22_set_move_state(0x56, mode);
        break;
    }
}
