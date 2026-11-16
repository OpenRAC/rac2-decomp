#include "include_asm.h"

#include "common.h"
extern void func_3F7CD8(s32);
extern void func_3F7EF8(s32);
extern void func_3F80A0(s32);
extern void func_3F8A98(s32);
extern void func_3F8C08(s32);
extern s32 func_001163B0(void);
extern s32 FloatToInt(float);
extern u8 *g_orbiting_effect_type_table;

/* Per-frame update of a small flying robot enemy: sets it up on the first frame, then runs its movement, attack and hit checks. (PAL version) */
void robot_l18_update_pal(s32 moby)
{
    u8 mode = *(u8 *)(moby + 0x20);

    if (mode == 0) {
        func_3F7CD8(moby);
        return;
    }
    if (mode == 1)
        return;
    func_3F7EF8(moby);
    func_3F80A0(moby);
    func_3F8A98(moby);
    func_3F8C08(moby);
}

extern u16 g_two_step_trigger_flag;
extern u8 g_map_overlay_flag[] __attribute__((sda));
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern u8 g_hero_position[];
extern u8 g_hero_state[];
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int path_build_route_nodes(u8 *, int, u8 *, int);
extern void protopet_reset_to_start_anim(u8 *);
extern void moby_set_state(u8 *, int, int);

/* Sets up the robot enemy: its speeds, turning and bounce values, a random spin direction and its starting behaviour. (PAL version) */
void robot_init_pal(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    float rate, spin;

    state[0x70] = 9;
    *(int *)(state + 0xA8) = 4;
    *(float *)(state + 0x90) = 0.8f;
    *(float *)(state + 0x94) = 0.9f;
    *(float *)(state + 0x9C) = 0.4f;
    if (*(short *)(state + 0x24) == 0) {
        *(short *)(state + 0x24) = 16;
        *(float *)(state + 0x20) = 16;
    }
    state[0x28] = 3;
    *(float *)(state + 0x144) = 0.25f;
    *(float *)(state + 0x110) = 0.8f;
    *(float *)(state + 0x13C) = 0.008f;
    *(float *)(state + 0x114) = 0.5f;
    *(float *)(state + 0x118) = 0.5f;
    *(float *)(state + 0x11C) = 2.0f;
    *(float *)(state + 0x120) = 1.5707964897155762f;
    moby_set_controller_speed_limits(object, 0.0048f, 0.120000005f,
                  0.005026549f, 0.25132746f);
    *(u8 **)(state + 0x158) = state + 0x680;
    *(u8 **)(state + 0x15C) = state + 0x600;
    rate = math_random_float_range(5.0f, 20.0f);
    if (math_random_int_below(2) != 0)
        spin = rate * -0.01745329424738884f;
    else
        spin = rate * 0.01745329424738884f;
    *(float *)(state + 0x720) = spin;
    *(int *)(state + 0x14C) = *(int *)(state + 0x718);
    if (*(int *)(state + 0x71C) != -1)
        *(int *)(state + 0x730) = path_build_route_nodes(object,
            *(int *)(state + 0x71C), state + 0x200, 0x20);
    *(short *)(state + 0x76C) = math_random_int_below(2);
    *(float *)(state + 0x72C) = math_random_float_range(5.0f, 7.0f);
    *(u16 *)(object + 0x7C) |= 1 << math_random_int_below(6);
    switch (*(short *)(state + 0x764)) {
    case 1:
        protopet_reset_to_start_anim(object);
        break;
    case 2:
        moby_set_state(object, 2, 1);
        break;
    }
}


typedef int u128 __attribute__((mode(TI)));
extern char *part_find_owned_effect_slot(char *, int, int);
extern int moby_apply_damage_to_object_pal(char *, char *, int);
extern void SetDeathBits_pal(char *, int, int);
extern void moby_mark_spawned(char *);
extern void FastVecAdd(void *, void *, void *);
extern int coll_sweep_from_object(char *, void *, float, float, float, int, int, int, int);
extern void gfx_add_draw_callback_third(void *, char *);
extern char g_robot_draw_callback[];

/* Handles hits on the robot enemy: damages or ignores the thing it touched, destroys it if it falls too low, and draws its shadow. (PAL version) */
void robot_handle_hits_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *hit = part_find_owned_effect_slot(moby, 0x10000, 1);
    int old_state;
    float position[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    float zero[4] __attribute__((aligned(16)));
    if (hit && *(char **)(hit + 0x20)) {
        int class_id = *(short *)(*(char **)(hit + 0x20) + 0xAA);
        if (class_id == MOBY_CLASS_PROTOPET) {
            if (*(unsigned char *)(moby + 0x31)) *(float *)(hit + 0x2C) = 4.0f;
            else *(float *)(hit + 0x2C) = 0;
        } else if (class_id == MOBY_CLASS_EXTERMIBOT_LEGS || class_id == 0xF9E) *(float *)(hit + 0x2C) = 0;
    }
    old_state = *(unsigned char *)(moby + 0x94);
    moby_apply_damage_to_object_pal(moby, vars + 0x60, 0);
    if (*(unsigned char *)(moby + 0x20) == 9 &&
        (*(unsigned char *)(moby + 0x94) == 9 || *(unsigned char *)(moby + 0x94) == 4 || *(unsigned char *)(moby + 0x94) == 3))
        *(unsigned char *)(moby + 0x94) = old_state;
    if (*(float *)(moby + 0x18) < 90.0f) {
        SetDeathBits_pal(moby, 0, 3);
        moby_mark_spawned(moby);
        return;
    }
    *(u128 *)zero = 0;
    zero[2] = *(float *)(vars + 0x114) + *(float *)(vars + 0x110);
    *(u128 *)temp = *(u128 *)zero;
    FastVecAdd(position, moby + 0x10, temp);
    coll_sweep_from_object(moby, position, *(float *)(vars + 0x110) + 0.2f, 10.0f, 1.0f, 0x4000000, 0, 1, 0);
    if (*(unsigned char *)(moby + 0x20) >= 2) gfx_add_draw_callback_third(g_robot_draw_callback, moby);
}
