#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0000[0xBF8];
    char *f0BF8;
    char pad0BFC[0x1230 - 0xBFC];
    u32 buttons;
    char pad1234[0xC];
    int resource;
    char pad1244[0x1450 - 0x1244];
    char *target;
    char pad1454[0x2294 - 0x1454];
    int level;
    char pad2298[0x22B8 - 0x2298];
    u8 f22B8;
    char pad22B9[3];
    u8 busy;
    char pad22BD[0x2534 - 0x22BD];
    int cooldown;
} AimHero;
extern AimHero g_hero_state;
typedef struct { char pad000[0x1A0]; u32 held; u32 pressed; } AimPad;
extern AimPad g_pad_state;
extern u8 g_hoverbomb_weapon_index;
extern u8 g_bouncer_weapon_index[];
extern int g_game_l00_mode;
extern int g_bouncer_timer;
typedef struct { char pad00[0x54]; float rate; char pad58[0xE0 - 0x58]; } AimEntry;
extern AimEntry g_weapon_l00_table[];
extern s32 func_PAL_L00_002C4480(int a0, int a1);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern int math_fast_float_d(int *);
extern int vec_fast_helper_b(float *);
extern void cancel_hero_item_animation_pal(void);
extern void func_PAL_L00_002AF458(void);
extern int get_ammo(int);
extern int weapon_spend_ammo(int, int);
extern int PlayMobySound(int, int, char *);
extern void moby_compute_offset_point(char *, char *);
extern char *moby_get_private_value_0(u8 *);
extern void CalculateAimedLaunchVelocity(float, float, float, float, void *, void *, void *, void *);
extern int coll_trace_projectile_to_impact_pal(float, void *, void *, void *, void *, void *, int *, int *);
extern void part_spawn_muzzle_spark_burst_pal(void *, void *, void *);
extern int bouncer_spawn_debris(int, int, int);
struct Rac2Native_5f824a0e369ccf7b_src_record;
extern struct Rac2Native_5f824a0e369ccf7b_src_record g_bouncer_sound_record;
extern int slot_copy_records_to_free(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern void slot_reset_active(int);
extern void ref_L00_003FDE48_00(void *, void *);
extern void moby_draw_attached_effect_pal(void *);

/* Coordinate the multi-object interaction and its repeat/cooldown timers. */

void func_PAL_L00_004026C4(unsigned char *object) {
    float origin[4];
    float aim[4];
    AimEntry *entry;
    char *state = *(char **)(object + 0x68);
    char *target;
    s32 target_data;
    int allowed;
    int was_running;
    int handle;

    if (object[0x20] == 0) {
        object[0x20] = 1;
        *(int *)(state + 0x28) = -1;
        *(float *)(state + 0x20) = 0.0f;
        *(int *)(state + 0x2C) = 0;
        g_bouncer_timer = 17;
    }
    if (g_hero_state.level == 1) func_PAL_L00_002C4480(29, 1);
    if (object[0x42] == object[0x43] && (object[0x60] & 2)) anim_start_blended_with_flags(object, 1, 0, 2, 0);
    moby_compute_offset_point(object, (char *)origin);
    target = 0;
    if (g_hero_state.target != 0 && (u8)g_hero_state.target[0x20] != 0xFE && (u8)g_hero_state.target[0x20] != 0xFD) {
        target_data = moby_get_private_value_0((u8 *)g_hero_state.target);
        if (target_data != 0 && *(float *)target_data > 0.0f) target = g_hero_state.target;
    }
    allowed = 1;
    if (g_hero_state.level == 29) {
        if (!math_fast_float_d(&g_hero_state.cooldown)) allowed = 0;
    }
    else g_hero_state.cooldown = 33;
    CalculateAimedLaunchVelocity(1.6f, 10.0f, 0.3f, 0.00584f, aim, origin, target, 0);
    *(int *)(state + 0x24) = coll_trace_projectile_to_impact_pal(0.00584f, origin, aim, state, state + 0x10, object, 0, 0);
    was_running = *(float *)(state + 0x20) > 0.0f;
    vec_fast_helper_b((float *)(state + 0x20));
    if (was_running && *(float *)(state + 0x20) <= 0.0f && get_ammo(-1)) PlayMobySound(3, 0, object);
    if (*(int *)(state + 0x2C) != 0 && math_fast_float_d((int *)(state + 0x2C))) cancel_hero_item_animation_pal();
    if ((g_pad_state.pressed & g_hero_state.buttons) && !get_ammo(-1)) {
        PlayMobySound(1, 0, object);
        g_bouncer_timer = 17;
    }
    if (g_game_l00_mode == 0 && *(float *)(state + 0x20) == 0.0f && g_hero_state.busy == 0 &&
        (u8)object[0x42] <= 1 && (g_pad_state.held & g_hero_state.buttons) && g_hero_state.resource >= 19 && allowed) {
        if (get_ammo(-1)) {
            PlayMobySound(0, 0, object);
            weapon_spend_ammo(-1, 1);
            part_spawn_muzzle_spark_burst_pal(object, origin, aim);
            anim_start_blended_with_flags(object, 2, 0, 2, 0);
            bouncer_spawn_debris((int)object, (int)origin, (int)aim);
            func_PAL_L00_002AF458();
            *(int *)(state + 0x2C) = 13;
            *(int *)(state + 0x28) = slot_copy_records_to_free(&g_bouncer_sound_record);
        }
        if (!(g_pad_state.held & g_hero_state.buttons) || !get_ammo(-1) || g_hero_state.f22B8 == 0) {
            handle = *(int *)(state + 0x28);
            if (handle >= 0) {
                slot_reset_active(handle);
                *(int *)(state + 0x28) = -1;
            }
        }
        entry = g_weapon_l00_table + g_bouncer_weapon_index[0];
        *(float *)(state + 0x20) = 1.0f / entry->rate;
    }
    ref_L00_003FDE48_00(moby_draw_attached_effect_pal, object);
}
