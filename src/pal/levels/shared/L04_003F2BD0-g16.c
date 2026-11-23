#include "common.h"
typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char g_hero_state[];
extern unsigned char g_pad_state[];

extern u8 g_hoverbomb_weapon_index[];
extern int g_game_l00_mode;
extern int g_hoverbomb_fire_held;
extern float g_hoverbomb_gun_offset[4] __attribute__((sda));
extern int g_hoverbomb_fire_delay __attribute__((sda));
extern int g_hoverbomb_fire_repeat __attribute__((sda));
extern void moby_init_vars_once(char *);
extern void moby_fire_shot(char *, void *);
typedef struct { char pad00[0x54]; float rate; char pad58[0xE0 - 0x58]; } AimEntry;
extern AimEntry g_weapon_l00_table[];
extern s32 hero_l00_set_action(int, int);
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
extern void moby_compute_offset_point(char *, char *);
extern char *moby_get_private_value_0(u8 *);
extern void CalculateAimedLaunchVelocity(float, float, float, float, void *, void *, void *, void *);
extern int coll_trace_projectile_to_impact(float, void *, void *, void *, void *, void *, int *, int *);
extern void part_spawn_muzzle_spark_burst(void *, void *, void *);
extern int bouncer_spawn_debris(int, int, int);
struct Rac2Native_5f824a0e369ccf7b_src_record;
extern struct Rac2Native_5f824a0e369ccf7b_src_record g_bouncer_sound_record;
extern int actuator_play_waves(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern void actuator_end_looping_waves(void);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void moby_draw_attached_effect(void *);

/* func_PAL_L04_003F2BD0, the PAL copy of func_L00_003C3418: the same C, where 10, 40 and 23 frames
 * become 8, 33 and 19, and the two int timers are scaled to 50 Hz as they are stored.
 * Coordinate the multi-object interaction and its repeat/cooldown timers. */

typedef struct { char *target; int pad04; float timer; s16 delay; s16 repeat; } BeamState;

void hoverbomb_l04_gun_update_pal(unsigned char *object) {
    float origin[4];
    AimEntry *entry;
    BeamState *state = *(BeamState **)(object + 0x68);
    char *member;
    u32 color;
    int allowed;
    int phase;

    moby_init_vars_once(object);
    if (((Hero *)g_hero_state)->i[2213] == 1) hero_l00_set_action(29, 1);
    if (((Hero *)g_hero_state)->ptr[1300] != 0) ((Hero *)g_hero_state)->ptr[766] = ((Hero *)g_hero_state)->ptr[1300];
    if (object[0x42] == object[0x43] && (object[0x60] & 2))
        anim_start_blended_with_flags(object, 1, 0, 8, 0);
    if (state->repeat != 0 && FastDecTimer(&state->repeat)) cancel_hero_item_animation();
    matrix_mul_vec3(origin, g_hoverbomb_gun_offset, object + 0xC0);
    FastVecAdd(origin, origin, object + 0x10);
    vec_fast_helper_b(&state->timer);
    allowed = 1;
    if (((Hero *)g_hero_state)->i[2213] == 29) {
        if (!math_fast_float_d(&((Hero *)g_hero_state)->i[2381])) allowed = 0;
        else {
            if (state->timer > 0.0f || !get_ammo(-1) || object[0x20] != 1)
                color = 0x600000FF;
            else color = 0x600FFF0F;
            hud_add_moby_marker(1.0f, 0.0f, 90.0f, object, color, 0, 31, -1, 4);
        }
    } else ((Hero *)g_hero_state)->i[2381] = 33;
    phase = (u8)object[0x20];
    if (phase == 1) {
        if (g_game_l00_mode != 0 || state->timer != 0.0f || ((Hero *)g_hero_state)->b[8892] != 0 ||
            (u8)object[0x42] > 1 || !(((Hero *)g_pad_state)->u[104] & ((Hero *)g_hero_state)->u[1164]) || ((Hero *)g_hero_state)->i[1168] < 19 || !allowed) return;
        if (get_ammo(-1)) {
            weapon_spend_ammo(-1, 1);
            g_hoverbomb_fire_held = phase;
            anim_start_blended_with_flags(object, 2, 4, 2, 0);
            PlayMobySound(0, 0, object);
            start_equipped_item_animation();
            object[0x20] = 2;
            state->delay = ((s32)(g_hoverbomb_fire_delay) * 5 + 2) / 6;
            state->repeat = ((s32)(g_hoverbomb_fire_repeat) * 5 + 2) / 6;
        } else if ((((Hero *)g_pad_state)->u[105] & ((Hero *)g_hero_state)->u[1164]) || g_hoverbomb_fire_held == 1) {
            PlayMobySound(1, 0, object);
            g_hoverbomb_fire_held = 0;
        }
        entry = g_weapon_l00_table + g_hoverbomb_weapon_index[0];
        state->timer = 1.0f / entry->rate;
    } else if (phase == 2) {
        if (!FastDecTimer(&state->delay)) return;
        moby_fire_shot(object, origin);
        object[0x20] = 3;
    } else {
        member = state->target;
        if ((member == 0 || *(s16 *)(member + 0xAA) != 0x5D8 || (u8)member[0x20] == 0xFE ||
             (u8)member[0x20] == 0xFD) && !(((Hero *)g_pad_state)->u[104] & ((Hero *)g_hero_state)->u[1164])) {
            state->target = 0;
            object[0x20] = 1;
        }
    }
}
