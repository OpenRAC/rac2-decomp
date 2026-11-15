#include "include_asm.h"
#include "common.h"

extern s32 FastDecTimer(s16 *timer);
extern s32 subtitle_request_voice_line(s32 key, s32 selection);
extern s32 IsPointInCuboid(void *point, s32 index);
extern s32 snd_play_from_global_bank(s32 index, s32 value, void *object);
extern void value_set_entry_by_index(s32 first, s32 second);

extern u16 D_0018CF40;
extern u8 D_001A7AFD[] __attribute__((sda));
extern u8 D_001A7A60[] MACRO_ADDR;
extern u8 g_hero_position[];
extern u8 g_hero_state[];
extern u32 D_L18_001A903C[] __attribute__((sda));

typedef int u128 __attribute__((mode(TI)));

extern char *part_find_owned_effect_slot(char *, int, int);
extern int moby_apply_damage_to_object(char *, char *, int);
extern void SetDeathBits(char *, int, int);
extern void moby_mark_spawned(char *);
extern void FastVecAdd(void *, void *, void *);
extern int coll_sweep_from_object(char *, void *, float, float, float, int, int, int, int);
extern void gfx_add_draw_callback_third(void *, char *);
extern char D_L18_003F9018[];

extern void func_3F7CD8(s32);
extern void func_3F7EF8(s32);
extern void func_3F80A0(s32);
extern void func_3F8A98(s32);
extern void func_3F8C08(s32);

extern float func_309900(float, float);
extern float func_308EE8(float);
extern float func_308F00(float);
extern float func_3099E8(float, float);
extern float func_308860(float);
extern void func_34B1D0(s32);

extern char *part_alloc(s32);
extern s32 func_001163B0(void);
extern s32 FloatToInt(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern u8 *D_L18_001FF4D4;

/* func_L18_002E68B0 is in the sibling file L18_002E68B0-decider.c (its own profile). */

/* func_L18_003170F8 is in the sibling file L18_002E68B0-movables.c (its own profile). */


/* Fills the record with the requested fields and derived coordinates. */
/* Creates a short-lived effect that circles a point, at a set distance and angle from it. */
char *part_create_orbiting_effect(char *center, float radius, float angle, float angle_step, float scale_a, float scale_b, s16 frame_step,
                         char *owner, s32 type_index, char *flag)
{
    char *record = part_alloc(0x65);
    char *orbit = record + 0x20;

    if (record != 0) {
        *(u8 *)(record + 3) = (flag != 0) ? 0x48 : 0x44;
        *(u8 *)(record + 1) = 0;
        *(u8 *)(record + 2) = D_L18_001FF4D4[type_index];
        *(u8 *)(record + 8) = func_001163B0();
        *(u8 *)(record + 9) = FloatToInt(1.0f) + 0x40;
        *(u32 *)(record + 4) = owner;
        *(float *)(record + 0xC) = scale_a * 210000.0f;
        *(u32 *)(orbit + 0) = center;
        *(float *)(orbit + 4) = radius;
        *(float *)(orbit + 8) = angle;
        *(float *)(orbit + 0xC) = angle_step;
        *(u16 *)(orbit + 0x14) = frame_step;
        *(float *)(orbit + 0x10) = scale_b * 210000.0f;
        *(float *)(record + 0x10) = *(float *)(*(char **)(orbit + 0)) +
                                *(float *)(orbit + 4) * math_fast_sin_or_cos_a(angle);
        *(float *)(record + 0x18) = *(float *)(*(char **)(orbit + 0) + 8) +
                                *(float *)(orbit + 4) * math_fast_sin_or_cos_b(*(float *)(orbit + 8));
        *(float *)(record + 0x14) = *(float *)(*(char **)(orbit + 0) + 4);
    }
    return record;
}

/* Turns the circling effect a little each frame, moves it, and removes it when it has turned far enough. */
void part_update_orbiting_effect(char *effect)
{
    char *record = effect;
    char *orbit = record + 0x20;
    float angle_diff;

    *(u8 *)(record + 8) = *(u8 *)(record + 8) + *(u8 *)(orbit + 0x14);
    *(float *)(orbit + 8) = func_309900(*(float *)(orbit + 8), *(float *)(orbit + 0xC));
    *(float *)(record + 0xC) = *(float *)(record + 0xC) + *(float *)(orbit + 0x10);
    *(float *)(record + 0x10) = *(float *)(*(char **)(record + 0x20)) +
                            *(float *)(orbit + 4) * func_308EE8(*(float *)(orbit + 8));
    *(float *)(record + 0x18) = *(float *)(*(char **)(record + 0x20) + 8) +
                            *(float *)(orbit + 4) * func_308F00(*(float *)(orbit + 8));
    angle_diff = func_3099E8(*(float *)(orbit + 8), *(float *)(*(char **)(record + 0x20) + 0x10));
    if (angle_diff < func_308860(*(float *)(orbit + 0xC) + *(float *)(orbit + 0xC)))
        func_34B1D0(record);
}

/* Watches the hero in two steps, first for one action and then for another, and then triggers an event with a sound. */
void two_step_hero_trigger_update(u8 *moby) {
    u8 *vars;
    u32 step;
    u8 state_byte;

    vars = *(u8 **)(moby + 0x68);
    if (moby[0x20] == 0) {
        moby[0x30] = 0xFF;
        *(u16 *)(vars + 0xE) = 0x28;
        *(u16 *)(vars + 0xC) = 0;
        moby[0x20] = 1;
    }
    if (D_0018CF40 != 0)
        goto after;
    if (D_001A7AFD[0] != 0) {
        if (FastDecTimer((s16 *)(vars + 0xE)) != 0)
            subtitle_request_voice_line(0xA27, 0x7E);
    }
after:
    state_byte = moby[0x20];
    if (state_byte != 1)
        goto end;
    step = *(u32 *)(vars + 0x8);
    switch (step) {
    case 0: {
        u8 *hero = g_hero_position;
        if (IsPointInCuboid(hero, *(u32 *)(vars + 0)) != 0) {
            if (*(u32 *)(hero + 0x221C) == 15)
                *(u32 *)(vars + 8) = state_byte;
        }
        break;
    }
    case 1: {
        u8 *hero = g_hero_state;
        if (*(u32 *)(hero + 0x2294) == 0x3E) {
            *(u32 *)(vars + 8) = 0;
        } else if (IsPointInCuboid(hero + 0x80, *(u32 *)(vars + 4)) != 0) {
            if (D_001A7A60[7] == 0) {
                D_001A7A60[7] = step;
                snd_play_from_global_bank(1, 0, 0);
                value_set_entry_by_index(0x1233, -1);
                D_L18_001A903C[0] = step;
            }
        }
        break;
    }
    }
end:
    return;
}


/* Per-frame update of a small flying robot enemy: sets it up on the first frame, then runs its movement, attack and hit checks. */
void robot_l18_update(s32 moby)
{
    u8 state_byte = *(u8 *)(moby + 0x20);

    if (state_byte == 0) {
        func_3F7CD8(moby);
        return;
    }
    if (state_byte == 1)
        return;
    func_3F7EF8(moby);
    func_3F80A0(moby);
    func_3F8A98(moby);
    func_3F8C08(moby);
}

extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int path_build_route_nodes(u8 *, int, u8 *, int);
extern void protopet_reset_to_start_anim(u8 *);
extern void moby_set_state(u8 *, int, int);

/* Sets up the robot enemy: its speeds, turning and bounce values, a random spin direction and its starting behaviour. */
void robot_init(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    float turn_degrees, turn_speed;

    vars[0x70] = 9;
    *(int *)(vars + 0xA8) = 4;
    *(float *)(vars + 0x90) = 0.8f;
    *(float *)(vars + 0x94) = 0.9f;
    *(float *)(vars + 0x9C) = 0.4f;
    if (*(short *)(vars + 0x24) == 0) {
        *(short *)(vars + 0x24) = 16;
        *(float *)(vars + 0x20) = 16;
    }
    vars[0x28] = 3;
    *(float *)(vars + 0x144) = 0.25f;
    *(float *)(vars + 0x110) = 0.8f;
    *(float *)(vars + 0x13C) = 0.0055555556900799274f;
    *(float *)(vars + 0x114) = 0.5f;
    *(float *)(vars + 0x118) = 0.5f;
    *(float *)(vars + 0x11C) = 2.0f;
    *(float *)(vars + 0x120) = 1.5707964897155762f;
    moby_set_controller_speed_limits(object, 0.0033333334140479565f, 0.10000000894069672f,
                  0.0034906589426100254f, 0.20943954586982727f);
    *(u8 **)(vars + 0x158) = vars + 0x680;
    *(u8 **)(vars + 0x15C) = vars + 0x600;
    turn_degrees = math_random_float_range(5.0f, 20.0f);
    if (math_random_int_below(2) != 0)
        turn_speed = turn_degrees * -0.01745329424738884f;
    else
        turn_speed = turn_degrees * 0.01745329424738884f;
    *(float *)(vars + 0x720) = turn_speed;
    *(int *)(vars + 0x14C) = *(int *)(vars + 0x718);
    if (*(int *)(vars + 0x71C) != -1)
        *(int *)(vars + 0x730) = path_build_route_nodes(object,
            *(int *)(vars + 0x71C), vars + 0x200, 0x20);
    *(short *)(vars + 0x76C) = math_random_int_below(2);
    *(float *)(vars + 0x72C) = math_random_float_range(5.0f, 7.0f);
    *(u16 *)(object + 0x7C) |= 1 << math_random_int_below(6);
    switch (*(short *)(vars + 0x764)) {
    case 1:
        protopet_reset_to_start_anim(object);
        break;
    case 2:
        moby_set_state(object, 2, 1);
        break;
    }
}

/* Handles hits on the robot enemy: damages or ignores the thing it touched, destroys it if it falls too low, and draws its shadow. */
void robot_handle_hits(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *hit_info = part_find_owned_effect_slot(moby, 0x10000, 1);
    int old_anim;
    float world_pos[4] __attribute__((aligned(16)));
    float offset_temp[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    if (hit_info && *(char **)(hit_info + 0x20)) {
        int hit_class = *(short *)(*(char **)(hit_info + 0x20) + 0xAA);
        if (hit_class == MOBY_CLASS_PROTOPET) {
            if (*(unsigned char *)(moby + 0x31)) *(float *)(hit_info + 0x2C) = 4.0f;
            else *(float *)(hit_info + 0x2C) = 0;
        } else if (hit_class == MOBY_CLASS_EXTERMIBOT_LEGS || hit_class == 0xF9E /* moby class 3998 */) *(float *)(hit_info + 0x2C) = 0;
    }
    old_anim = *(unsigned char *)(moby + 0x94);
    moby_apply_damage_to_object(moby, vars + 0x60, 0);
    if (*(unsigned char *)(moby + 0x20) == 9 &&
        (*(unsigned char *)(moby + 0x94) == 9 || *(unsigned char *)(moby + 0x94) == 4 || *(unsigned char *)(moby + 0x94) == 3))
        *(unsigned char *)(moby + 0x94) = old_anim;
    if (*(float *)(moby + 0x18) < 90.0f) {
        SetDeathBits(moby, 0, 3);
        moby_mark_spawned(moby);
        return;
    }
    *(u128 *)offset = 0;
    offset[2] = *(float *)(vars + 0x114) + *(float *)(vars + 0x110);
    *(u128 *)offset_temp = *(u128 *)offset;
    FastVecAdd(world_pos, moby + 0x10, offset_temp);
    coll_sweep_from_object(moby, world_pos, *(float *)(vars + 0x110) + 0.2f, 10.0f, 1.0f, 0x4000000, 0, 1, 0);
    if (*(unsigned char *)(moby + 0x20) >= 2) gfx_add_draw_callback_third(D_L18_003F9018, moby);
}
