#include "include_asm.h"

#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef struct {
    char p0[0x760]; float facing[4];
    char p00[0x488]; char *aimTarget;
    char p1[0x634]; unsigned int buttons;
    char p2[0xC]; int inputTicks;
    char p3[0x20C]; char *overrideTarget;
    char p4[0xE3C]; char *hero; int mode;
    char p5[0x24]; u8 blocked;
    char p6[0x22F]; short viewMode;
    char p7[0x46]; int inputTimer;
} PlayerStatePrefix;
extern PlayerStatePrefix g_hero_state;
extern u8 g_charged_beam_weapon_index[];
extern unsigned int g_pad_state[];
typedef struct { int mode; char pad[0x18]; float time; } Ctrl0F30;
extern Ctrl0F30 g_charged_beam_state __attribute__((sda));
extern int g_charged_beam_init_flag __attribute__((sda));
extern float g_charge_increment __attribute__((sda));
extern float g_charge_decrement __attribute__((sda));
extern float g_charge_minimum __attribute__((sda));
extern float g_charge_next_step __attribute__((sda));
extern float g_charge_limit __attribute__((sda));
extern int g_charged_beam_phase __attribute__((sda));
extern char *g_charged_beam_effect_moby __attribute__((sda));
extern int g_charged_beam_timer __attribute__((sda));
typedef struct {
    float angle0[3], speed0[3], scale0[3];
    float angle1[3], speed1[3], scale1[3];
    float padding[2];
    VectorBits output0, output1;
    char tail[16];
} BeamOscillator;
extern BeamOscillator g_beam_oscillator_table[4];
typedef struct { char prefix[0x54]; float rate; char tail[0x88]; } WeaponEntry;
extern WeaponEntry g_weapon_l00_table[];
extern int math_fast_float_d(void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern void AttachManipulator(u8 *, u32, u8 *);
extern int AcquireEntitySlot(void *, int, void *);
extern char *level_get_slot_body(int, int);
extern float math_random_signed_float_range(float, float), math_random_float_range(float, float);
extern void vec_clear_128(VectorBits *);
extern s32 hero_l00_set_move_state_pal(int, int);
extern int get_ammo(int);
extern void hud_add_moby_marker(void *, unsigned int, int, int, int, int, float, float, float);
extern int vec_fast_helper_b(void *);
extern int effect_is_count_two(void);
extern int weapon_spend_ammo(int, int);
extern int PlayMobySound(int, int, char *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_compute_object_to_target(char *, char *, char *, float);
extern void *effect_spawn_moby_pal(char *, char *, char *, char *);
extern void weapon_draw_beam_network_pal(void *);
extern void ref_L00_003A0F30_00(void (*)(void *), void *);
extern float FastAddRotations(float, float), math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float);

/* Initialize the beam oscillators and update the weapon's charge cycle. */
void charged_l00_beam_weapon_update_pal(char *moby)
{
    float velocity[4], origin[4], query[4];
    char *state = *(char **)(moby + 0x68);
    int ready = 1;
    if (g_hero_state.mode == 29) {
        if (math_fast_float_d(&g_hero_state.inputTimer) == 0)
            ready = 0;
    }
    else
        g_hero_state.inputTimer = 33;
    if (g_hero_state.overrideTarget)
        g_hero_state.aimTarget = (char *)g_hero_state.overrideTarget;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0: {
        int i, handle;
        *(float *)state = 0.3666666746f;
        *(unsigned char *)(moby + 0x20) = 1;
        g_charged_beam_state.time = -1.0f;
        g_charged_beam_phase = 0;
        g_charged_beam_init_flag = 0;
        if (*(unsigned char *)(moby + 0x43) || (*(unsigned char *)(moby + 0x60) & 2))
            anim_start_blended_pal(moby, 1, 0, 0);
        *(int *)(state + 0xC) = 0;
        *(int *)(state + 0x10) = 0;
        AttachManipulator((u8 *)moby, 0, (u8 *)state + 0x20);
        handle = AcquireEntitySlot(moby, 0, query);
        *(int *)(state + 4) = handle;
        *(char **)(state + 8) = level_get_slot_body(*(short *)(moby + 0xAA), handle);
        for (i = 0; i < 4; i++) {
            BeamOscillator *entry = &g_beam_oscillator_table[i];
            entry->angle0[0] = 0.0f; entry->angle0[1] = 0.0f; entry->angle0[2] = 0.0f;
            entry->speed0[0] = math_random_signed_float_range(0.05f, 0.3f);
            entry->speed0[1] = math_random_signed_float_range(0.05f, 0.3f);
            entry->speed0[2] = math_random_signed_float_range(0.05f, 0.3f);
            entry->scale0[0] = math_random_float_range(0.25f, 0.75f);
            entry->scale0[1] = math_random_float_range(0.25f, 0.75f);
            entry->scale0[2] = math_random_float_range(0.25f, 0.75f);
            entry->angle1[0] = 0.0f; entry->angle1[1] = 0.0f; entry->angle1[2] = 0.0f;
            entry->speed1[0] = math_random_signed_float_range(0.05f, 0.3f);
            entry->speed1[1] = math_random_signed_float_range(0.05f, 0.3f);
            entry->speed1[2] = math_random_signed_float_range(0.05f, 0.3f);
            entry->scale1[0] = math_random_float_range(0.25f, 0.75f);
            entry->scale1[1] = math_random_float_range(0.25f, 0.75f);
            entry->scale1[2] = math_random_float_range(0.25f, 0.75f);
            vec_clear_128(&g_beam_oscillator_table[i].output0);
            vec_clear_128(&g_beam_oscillator_table[i].output1);
        }
        return;
    }
    case 1: {
    g_charged_beam_state.time = -1.0f;
    if (g_charged_beam_init_flag == 0) {
        *(int *)(state + 0xC) = 0;
        g_charged_beam_init_flag = 1;
    }
    if (g_hero_state.mode == 1)
        hero_l00_set_move_state_pal(29, 1);
    if (g_hero_state.mode == 29) {
        unsigned int color;
        if (*(float *)state != 0.0f && get_ammo(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        hud_add_moby_marker(moby, color, 0, 0x26, -1, 4, 1.0f, 0.0f, 90.0f);
    }
    if (vec_fast_helper_b(state) && ready && !g_hero_state.blocked && (g_pad_state[0x68] & g_hero_state.buttons) &&
        !effect_is_count_two() && g_hero_state.inputTicks > 18) {
        if (weapon_spend_ammo(-1, 1)) {
            g_charged_beam_state.mode = 1;
            PlayMobySound(2, 0, moby);
            {
                float cooldown;
                switch (g_charged_beam_phase) {
                case 0: {
                    WeaponEntry *weapon;
                    int index;
                    g_charged_beam_phase = 1;
                    *(float *)(state + 0xC) = g_charge_minimum;
                    weapon = &g_weapon_l00_table[g_charged_beam_weapon_index[0]];
                    cooldown = 1.0f / weapon->rate;
                    break;
                }
                case 2: {
                    WeaponEntry *weapon;
                    int index;
                    g_charged_beam_phase = 1;
                    weapon = &g_weapon_l00_table[g_charged_beam_weapon_index[0]];
                    cooldown = 1.0f / weapon->rate;
                    break;
                }
                default:
                    goto update_charge;
                }
                *(float *)state = cooldown;
            }
        } else if ((g_pad_state[0x69] & g_hero_state.buttons) || g_charged_beam_state.mode == 1) {
            PlayMobySound(6, 0, moby);
            g_charged_beam_state.mode = 0;
        }
    }
update_charge:
    switch (g_charged_beam_phase) {
    case 0: {
        float charge = *(float *)(state + 0xC);
        float minimum = g_charge_minimum;
        if (charge < minimum) {
            float next = charge + g_charge_next_step;
            *(float *)(state + 0xC) = next;
            if (next > minimum)
                *(float *)(state + 0xC) = minimum;
        }
        break;
    }
    case 1: {
        float charge = *(float *)(state + 0xC) + g_charge_increment;
        float limit = g_charge_limit;
        *(float *)(state + 0xC) = charge;
        if (charge > limit) {
            float speed;
            moby_transform_joint_to_world(moby, 0, (char *)origin);
            speed = 0.40000004f;
            if (g_hero_state.viewMode == 1) {
                speed = -speed;
                vec_scale_to_length(velocity, moby + 0xD0, speed);
            } else
                vec_scale_to_length(velocity, g_hero_state.facing, speed);
            if (g_hero_state.aimTarget)
                vec_compute_object_to_target(g_hero_state.aimTarget, (char *)origin, (char *)velocity, 0.40000004f);
            g_charged_beam_effect_moby = effect_spawn_moby_pal(moby, (char *)*(int *)(state + 4), (char *)origin, (char *)velocity);
            if (g_charged_beam_effect_moby)
                *(char **)(g_charged_beam_effect_moby + 0xB8) = moby;
            g_charged_beam_timer = 42;
            g_charged_beam_phase = 2;
        }
        break;
    }
    case 2: {
        float charge = *(float *)(state + 0xC) - g_charge_decrement;
        float minimum = g_charge_minimum;
        *(float *)(state + 0xC) = charge;
        if (charge <= minimum) {
            *(float *)(state + 0xC) = minimum;
            g_charged_beam_phase = 0;
        }
    }
    }
    if (*(unsigned char *)(moby + 0x31))
        ref_L00_003A0F30_00(weapon_draw_beam_network_pal, moby);
    *(float *)(state + 0x10) = FastAddRotations(*(float *)(state + 0x10), *(float *)(state + 0xC) * 0.37699118f);
    *(float *)(state + 0x30) = math_fast_sin_or_cos_b(*(float *)(state + 0x10) * 0.5f);
    *(float *)(state + 0x3C) = math_fast_sin_or_cos_a(*(float *)(state + 0x10) * 0.5f);
    }
    }
}
