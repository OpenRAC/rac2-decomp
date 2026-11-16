#include "include_asm.h"
#include "names.h"

extern char g_hero_state[];
extern void hero_clear_queued_anim(void);
extern int hero_l22_set_action(int mode, int flag);
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
extern void ref_L22_002B70F8_00(void);
extern void ref_L22_002B70F8_01(void);
extern void ref_L22_002B70F8_02(void);
typedef unsigned char u8;
typedef unsigned short u16;
typedef float f32;
extern int hero_l22_set_action(int a0, int a1);

/* func_PAL_L22_002AA488, the PAL copy of func_L22_002AA678: the same C, where the fade rates
   0.07f and 0.13f become 0.08400001f and 0.156f, the timer 5 becomes 4, and the three call
   arguments 7, 8 and 9 become 6, 7 and 7. func_00282948 is declared int, as at its other call
   sites: the ignored result keeps $v0 from the base load after the call. */
extern void hero_build_relative_point(void *, int, float, float, float);
extern f32 ApproachValue(float *, float, float);
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

/* Per-frame update of the hero's effect slot (0x1870): spends the counted charges
   on the two level-specific actions, fades the effect out (releasing it at zero)
   or in, and creates it when it is allowed and absent. */
void hero_update_effect_slot_pal(void) {
    float v[4];
    int available;
    int i;

    if (((Hero_002AA678 *)g_hero_state)->unk1E0)
        return;
    if (((Hero_002AA678 *)g_hero_state)->unk2294 == 1 && PadPressedWithin(16, 6, 0) && !player_slot_has_object(((Hero_002AA678 *)g_hero_state)->unk2290) &&
        ((Hero_002AA678 *)g_hero_state)->counts->unkC) {
        hero_build_relative_point(v, 1, 2.0f, -2.1f, 8.7f);
        ref_L22_002AA678_00(((Hero_002AA678 *)g_hero_state)->unk2290, v, 1);
        ((Hero_002AA678 *)g_hero_state)->counts->unkC--;
    }
    available = 1;
    if (!((Hero_002AA678 *)g_hero_state)->counts->unk8 || player_slot_has_object(((Hero_002AA678 *)g_hero_state)->unk2290))
        available = 0;
    if ((unsigned)(((Hero_002AA678 *)g_hero_state)->unk2294 - 0x5D) <= 1)
        available = 0;
    if (((Hero_002AA678 *)g_hero_state)->active) {
        if (!((Hero_002AA678 *)g_hero_state)->counts->unk8) {
            if (((Hero_002AA678 *)g_hero_state)->effect) {
                if (((Hero_002AA678 *)g_hero_state)->effect->flags & 2)
                    ((Hero_002AA678 *)g_hero_state)->fading = 1;
                if (((Hero_002AA678 *)g_hero_state)->fading) {
                    if (((Hero_002AA678 *)g_hero_state)->effect->fade == 0) {
                        release_moby_animation_slot(((Hero_002AA678 *)g_hero_state)->unk2290, &((Hero_002AA678 *)g_hero_state)->effect);
                        ((Hero_002AA678 *)g_hero_state)->active = 0;
                        return;
                    }
                    ApproachValue(&((Hero_002AA678 *)g_hero_state)->effect->fade, 0, 0.08400001f);
                }
            } else
                ((Hero_002AA678 *)g_hero_state)->active = 0;
        }
    }
    if (((Hero_002AA678 *)g_hero_state)->active) {
        if (!(g_pad_pressed_flags & 0x20) || !available) {
            if (((Hero_002AA678 *)g_hero_state)->effect) {
                if (((Hero_002AA678 *)g_hero_state)->effect->flags & 2)
                    ((Hero_002AA678 *)g_hero_state)->fading = 1;
                if (((Hero_002AA678 *)g_hero_state)->fading) {
                    if (((Hero_002AA678 *)g_hero_state)->effect->fade == 0) {
                        release_moby_animation_slot(((Hero_002AA678 *)g_hero_state)->unk2290, &((Hero_002AA678 *)g_hero_state)->effect);
                        ((Hero_002AA678 *)g_hero_state)->active = 0;
                        return;
                    }
                    ApproachValue(&((Hero_002AA678 *)g_hero_state)->effect->fade, 0, 0.08400001f);
                }
            } else
                ((Hero_002AA678 *)g_hero_state)->active = 0;
        } else if (((Hero_002AA678 *)g_hero_state)->counts->unk8)
            ((Hero_002AA678 *)g_hero_state)->fading = 0;
    }
    if (!((Hero_002AA678 *)g_hero_state)->active && available && PadPressedWithin(32, 7, 0)) {
        Effect_002AA678 *p = allocate_moby_animation_slot(((Hero_002AA678 *)g_hero_state)->unk2290, 2);
        ((Hero_002AA678 *)g_hero_state)->fading = 0;
        ((Hero_002AA678 *)g_hero_state)->effect = p;
        if (p) {
            ((Hero_002AA678 *)g_hero_state)->active = 1;
            initialize_moby_animation_blend(((Hero_002AA678 *)g_hero_state)->unk2290, p, 13, 0, 7, 1);
        }
    }
    if (!((Hero_002AA678 *)g_hero_state)->active || !((Hero_002AA678 *)g_hero_state)->effect || ((Hero_002AA678 *)g_hero_state)->fading)
        return;
    ApproachValue(&((Hero_002AA678 *)g_hero_state)->effect->fade, 1, 0.156f);
    ((Hero_002AA678 *)g_hero_state)->effect->unk28 = 2;
    AdvanceAndDecodeAnimationFrames(((Hero_002AA678 *)g_hero_state)->unk2290, ((Hero_002AA678 *)g_hero_state)->effect);
    math_fast_float_d(&((Hero_002AA678 *)g_hero_state)->timer);
    if (((Hero_002AA678 *)g_hero_state)->effect->state == 4 && !((Hero_002AA678 *)g_hero_state)->timer) {
        ((Hero_002AA678 *)g_hero_state)->timer = 4;
        for (i = 0; i < 2; i++) {
            moby_transform_joint_to_world(((Hero_002AA678 *)g_hero_state)->unk2290, i + 3, v);
            vec_add_transformed_point(((Hero_002AA678 *)g_hero_state)->unk2290, v, 1.4f, 0, 0);
            if (((Hero_002AA678 *)g_hero_state)->counts->unk8) {
                ref_L22_002AA678_01(((Hero_002AA678 *)g_hero_state)->unk2290, v, 0, 0, ((Hero_002AA678 *)g_hero_state)->counts->unk0 != 0);
                ((Hero_002AA678 *)g_hero_state)->counts->unk8--;
            }
        }
    }
}


/* Restarts the run: resets the racer's state block, plays the two subsystem
   start-ups, then arms the racer for the mode the caller asked for.
   The state block is reached through three block-scoped copies of its address,
   so each stretch of the body re-materialises the base instead of keeping it
   live across the calls; the three table entries are the routines the tuning
   table points at, whose places differ from level to level. */
void hero_restart_in_mode_pal(int a0, int a1, void *a2) {
    char *s0 = g_hero_state;

    cancel_hero_item_animation();
    s0[0x22B6] = 1;
    UpdateHeroSlotCallbacks();
    *(int *)(s0 + 0x2290) = *(int *)(s0 + 0xC18);
    level_release_slot_list(s0 + 0x18E0);
    level_release_slot_list(s0 + 0x1A30);
    *(int *)(*(int *)(s0 + 0x2290) + 0x9C) = -1;
    if (a0 != 4 || *(u8 *)(s0 + 0x22B4) != a0)
        hero_set_objects_flag_bit();
    hero_clear_tracked_slots();
    attachment_reset_all();
    {
        char *s1 = g_hero_state;

        *(u8 *)(s1 + 0x22B4) = (u8)a0;
        *(int *)(s1 + 0xC14) = (int)a2;
        *(int *)(s1 + 0x2290) = (int)a2;
    }
    if ((a0 & 0xFF) == 1) {
        if (g_pad_pressed_flags & 0x10) {
            hud_set_slot_contents(0x23, 0, &ref_L22_002B70F8_00, &ref_L22_002B70F8_01,
                          &ref_L22_002B70F8_02, 0, 0);
            level_run_slot_callback(3);
        }
    }
    hero_l22_update_speed_targets();
    {
        char *s2 = g_hero_state;

        *(f32 *)(s2 + 0x250) = *(f32 *)(s2 + 0x258);
        *(f32 *)(s2 + 0x254) = *(f32 *)(s2 + 0x25C);
        *(u16 *)(*(int *)(s2 + 0x2290) + 0x34) |= 6;
        *(f32 *)(s2 + 0xC20) = 1.0f;
        *(f32 *)(s2 + 0xC24) = 1.0f;
        hero_clear_queued_anim();
        func_002A677C(*(int *)(s2 + 0x2290));
        *(u16 *)(s2 + 0x24F2) = (u16)a1;
        switch (a0) {
        case 1:
            *(u16 *)(s2 + 0x24D4) = *(u16 *)(s2 + 0x24CC);
            *(int *)(s2 + 0x24CC) = *(int *)(s2 + 0x24D0);
            if (*(int *)(s2 + 0x24D0) >= 5)
                *(int *)(s2 + 0x24CC) = 4;
            break;
        case 2:
            *(int *)(s2 + 0x1874) = 0x4B0;
            break;
        }
    }
    hero_l22_set_action(a1, 2);
}

