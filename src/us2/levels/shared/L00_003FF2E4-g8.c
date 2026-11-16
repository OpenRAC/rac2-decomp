/* func_US2_L00_003FF2E4, the USA v2.00 copy of func_L00_003FDE48: the same C, where the repeat
   timer moves from vars + 0x20 to a global, and a new bouncer clears that timer only when it
   lies outside the current entry's period, instead of always clearing it. */
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
extern u8 g_bouncer_weapon_index[];
extern int g_game_l00_mode;
extern int g_bouncer_timer;
typedef struct { char pad00[0x54]; float rate; char pad58[0xE0 - 0x58]; } AimEntry;
extern AimEntry g_weapon_l00_table[];
extern s32 hero_l00_change_action_us2(int a0, int a1);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern int math_fast_float_d(int *);
extern int vec_fast_helper_b(float *);
extern void cancel_hero_item_animation(void);
extern void start_equipped_item_animation(void);
extern int get_ammo(int);
extern int weapon_spend_ammo(int, int);
extern int PlayMobySound(int, int, char *);
extern void moby_compute_offset_point(char *, char *);
extern char *moby_get_private_value_0(u8 *);
extern void CalculateAimedLaunchVelocity(float, float, float, float, void *, void *, void *, void *);
extern int coll_trace_projectile_to_impact(float, void *, void *, void *, void *, void *, int *, int *);
extern void part_spawn_muzzle_spark_burst(void *, void *, void *);
extern int bouncer_spawn_debris(int, int, int);
struct Rac2Native_5f824a0e369ccf7b_src_record;
extern struct Rac2Native_5f824a0e369ccf7b_src_record g_bouncer_sound_record;
extern int slot_copy_records_to_free(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern void slot_reset_active(int);
extern void ref_L00_003FDE48_00(void *, void *);
extern void moby_draw_attached_effect(void *);

/* Coordinate the multi-bouncer interaction and its repeat/cooldown timers. */

extern float g_timer_remaining __attribute__((sda));
typedef struct {
    float f00[4];
    float f10[4];
    char pad20[4];
    int f24;
    int handle;
    int repeat;
} AimState;

/* Updates the Bouncer: aims the launch, fires debris while the button is held and runs the repeat and cooldown timers (US2 copy of bouncer_update). */
void bouncer_update_us2(unsigned char *bouncer) {
    float origin[4];
    float aim[4];
    AimEntry *limit_entry;
    AimEntry *entry;
    AimState *vars = *(AimState **)(bouncer + 0x68);
    char *target;
    s32 target_data;
    int allowed;
    int was_running;
    int handle;
    float period;

    if (bouncer[0x20] == 0) {
        bouncer[0x20] = 1;
        limit_entry = g_weapon_l00_table + g_bouncer_weapon_index[0];
        period = 1.0f / limit_entry->rate;
        if (period < g_timer_remaining || g_timer_remaining < 0.0f) g_timer_remaining = 0.0f;
        vars->repeat = 0;
        vars->handle = -1;
        g_bouncer_timer = 20;
    }
    if (g_hero_state.level == 1) hero_l00_change_action_us2(29, 1);
    if (bouncer[0x42] == bouncer[0x43] && (bouncer[0x60] & 2)) anim_start_blended_with_flags(bouncer, 1, 0, 2, 0);
    moby_compute_offset_point(bouncer, (char *)origin);
    target = 0;
    if (g_hero_state.target != 0 && (u8)g_hero_state.target[0x20] != 0xFE && (u8)g_hero_state.target[0x20] != 0xFD) {
        target_data = moby_get_private_value_0((u8 *)g_hero_state.target);
        if (target_data != 0 && *(float *)target_data > 0.0f) target = g_hero_state.target;
    }
    allowed = 1;
    if (g_hero_state.level == 29) {
        if (!math_fast_float_d(&g_hero_state.cooldown)) allowed = 0;
    }
    else g_hero_state.cooldown = 40;
    CalculateAimedLaunchVelocity(1.6f, 10.0f, 0.25f, 0.004055555909872055f, aim, origin, target, 0);
    vars->f24 = coll_trace_projectile_to_impact(0.004055555909872055f, origin, aim, vars, vars->f10, bouncer, 0, 0);
    was_running = g_timer_remaining > 0.0f;
    vec_fast_helper_b(&g_timer_remaining);
    if (was_running && g_timer_remaining <= 0.0f && get_ammo(-1)) PlayMobySound(3, 0, bouncer);
    if (vars->repeat != 0 && math_fast_float_d(&vars->repeat)) cancel_hero_item_animation();
    if ((g_pad_state.pressed & g_hero_state.buttons) && !get_ammo(-1)) {
        PlayMobySound(1, 0, bouncer);
        g_bouncer_timer = 20;
    }
    if (g_game_l00_mode == 0 && g_timer_remaining == 0.0f && g_hero_state.busy == 0 &&
        (u8)bouncer[0x42] <= 1 && (g_pad_state.held & g_hero_state.buttons) && g_hero_state.resource >= 23 && allowed) {
        if (get_ammo(-1)) {
            PlayMobySound(0, 0, bouncer);
            weapon_spend_ammo(-1, 1);
            part_spawn_muzzle_spark_burst(bouncer, origin, aim);
            anim_start_blended_with_flags(bouncer, 2, 0, 2, 0);
            bouncer_spawn_debris((int)bouncer, (int)origin, (int)aim);
            start_equipped_item_animation();
            vars->repeat = 16;
            vars->handle = slot_copy_records_to_free(&g_bouncer_sound_record);
        }
        if (!(g_pad_state.held & g_hero_state.buttons) || !get_ammo(-1) || g_hero_state.f22B8 == 0) {
            handle = vars->handle;
            if (handle >= 0) {
                slot_reset_active(handle);
                vars->handle = -1;
            }
        }
        entry = g_weapon_l00_table + g_bouncer_weapon_index[0];
        g_timer_remaining = 1.0f / entry->rate;
    }
    ref_L00_003FDE48_00(moby_draw_attached_effect, bouncer);
}
