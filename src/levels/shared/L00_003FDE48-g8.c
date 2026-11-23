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
extern int g_tetrabomb_fire_held __attribute__((sda));
extern char g_tetrabomb_gun_origin_offset[] __attribute__((sda));
extern u16 g_tetrabomb_gun_delay_first __attribute__((sda));
extern u16 g_tetrabomb_gun_delay_next __attribute__((sda));
extern u16 g_tetrabomb_gun_repeat __attribute__((sda));
extern int g_spread_shot_count __attribute__((sda));
typedef struct { char pad00[0x54]; float rate; char pad58[0xE0 - 0x58]; } AimEntry;
extern AimEntry g_weapon_l00_table[];
extern void moby_init_private_data(char *);
extern s32 hero_l00_set_action(int a0, int a1);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern int FastDecTimer(s16 *);
extern int math_fast_float_d(int *);
extern int vec_fast_helper_b(float *);
extern void cancel_hero_item_animation(void);
extern void start_equipped_item_animation(void);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int get_ammo(int);
extern int weapon_spend_ammo(int, int);
/* The caller deliberately supplies a sixth GPR word (4) in the call slot;
 * retail overwrites it before consumption. Original return/unused-formal
 * intent remains unqualified, but the observed call prefix is preserved. */
extern void hud_add_moby_marker(float, float, float, void *, u32, void *, int, int, int);
extern int PlayMobySound(int, int, char *);
extern void weapon_compute_spread_shot_velocity(char *, void *, int, void *);
extern void part_spawn_linked_effect_with_sparks(char *, void *, void *, int);
extern void moby_compute_offset_point(char *, char *);
extern char *moby_get_private_value_0(u8 *);
extern void CalculateAimedLaunchVelocity(float, float, float, float, void *, void *, void *, void *);
extern int coll_trace_projectile_to_impact(float, void *, void *, void *, void *, void *, int *, int *);
extern void part_spawn_muzzle_spark_burst(void *, void *, void *);
extern int bouncer_spawn_debris(int, int, int);
struct Rac2Native_5f824a0e369ccf7b_src_record;
extern struct Rac2Native_5f824a0e369ccf7b_src_record g_bouncer_sound_record;
extern int actuator_play_waves(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern void actuator_end_looping_waves(int);
extern void ref_L00_003FDE48_00(void *, void *);
extern void moby_draw_attached_effect(void *);

/* Coordinate the multi-object interaction and its repeat/cooldown timers. */

/* Per-frame update of the Bouncer weapon (also used by the Heavy Bouncer): aims, fires and runs the reload timer. */
void bouncer_update(unsigned char *object) {
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
        g_bouncer_timer = 20;
    }
    if (g_hero_state.level == 1) hero_l00_set_action(29, 1);
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
    else g_hero_state.cooldown = 40;
    CalculateAimedLaunchVelocity(1.6f, 10.0f, 0.25f, 0.004055555909872055f, aim, origin, target, 0);
    *(int *)(state + 0x24) = coll_trace_projectile_to_impact(0.004055555909872055f, origin, aim, state, state + 0x10, object, 0, 0);
    was_running = *(float *)(state + 0x20) > 0.0f;
    vec_fast_helper_b((float *)(state + 0x20));
    if (was_running && *(float *)(state + 0x20) <= 0.0f && get_ammo(-1)) PlayMobySound(3, 0, object);
    if (*(int *)(state + 0x2C) != 0 && math_fast_float_d((int *)(state + 0x2C))) cancel_hero_item_animation();
    if ((g_pad_state.pressed & g_hero_state.buttons) && !get_ammo(-1)) {
        PlayMobySound(1, 0, object);
        g_bouncer_timer = 20;
    }
    if (g_game_l00_mode == 0 && *(float *)(state + 0x20) == 0.0f && g_hero_state.busy == 0 &&
        (u8)object[0x42] <= 1 && (g_pad_state.held & g_hero_state.buttons) && g_hero_state.resource >= 23 && allowed) {
        if (get_ammo(-1)) {
            PlayMobySound(0, 0, object);
            weapon_spend_ammo(-1, 1);
            part_spawn_muzzle_spark_burst(object, origin, aim);
            anim_start_blended_with_flags(object, 2, 0, 2, 0);
            bouncer_spawn_debris((int)object, (int)origin, (int)aim);
            start_equipped_item_animation();
            *(int *)(state + 0x2C) = 16;
            *(int *)(state + 0x28) = actuator_play_waves(&g_bouncer_sound_record);
        }
        if (!(g_pad_state.held & g_hero_state.buttons) || !get_ammo(-1) || g_hero_state.f22B8 == 0) {
            handle = *(int *)(state + 0x28);
            if (handle >= 0) {
                actuator_end_looping_waves(handle);
                *(int *)(state + 0x28) = -1;
            }
        }
        entry = g_weapon_l00_table + g_bouncer_weapon_index[0];
        *(float *)(state + 0x20) = 1.0f / entry->rate;
    }
    ref_L00_003FDE48_00(moby_draw_attached_effect, object);
}
