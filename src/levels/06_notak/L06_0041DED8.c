#include "include_asm.h"
#include "common.h"

extern short *D_L06_001FB3A0[];
extern char *D_L06_001B281C[] __attribute__((sda));
extern float func_35A780(void);
extern void func_458138(char *);

extern int math_fast_float_d(char *);
extern int math_random_int_below(int);
extern int FloatToInt(float);
extern void gfx_update_color_fade(char *, char *);
extern int math_random_int_range(int, int);
/* EE argument banks preserve position/count/velocity/color/flags and four floats. */
extern char *SpawnSpinningSparkParticle(char *, float, float, float, int, char *, float, unsigned int, int);

extern char D_L06_002AA500[];

extern int func_32D268(char *);
extern void func_366160(char *, char *, float, int, int);
extern int func_36C158();
extern int func_36C1B0(float);
extern void func_3BFBB8(char *, int);

extern char D_L06_00189EA0[];
extern char D_L06_001B13B0[];
extern char D_L06_001B13F0[];
extern char D_L06_001B1330[];
extern char D_L06_001B1370[];
extern char D_L06_001395CE;
extern char D_L06_001395CF;
extern char D_L06_001395D0;

/* The two flags the re-arm sets, at 0x001395B8. */
typedef struct {
    char pad_000[0x13];
    char flag_013;
    char flag_014;
} L06ArmFlags;

extern L06ArmFlags D_L06_001395B8;

extern int func_333898(void);
extern void func_2E3EF0(char *);
extern int func_360F58(char *, int);
extern void func_35A550(char *, int, int);
extern void func_35B810(int, int);
extern int func_35CBA0(char *, int, int);
extern int func_3A0948(int, int, char *);
extern void func_3661E0(char *, int, float);
extern void func_350388(char *);
extern void func_32D650(char *, char *, float);
/* Throws out a set of small debris particles around the object, one for each bit set in the mask. */
extern void part_spawn_debris_mask(char *, int, void *, int, float, float, float, float);
extern void func_32D5F8(char *, char *, char *);
extern void func_365030(char *, char *, char *, int);
extern float func_32DC80(float, float);
extern float func_32D740(char *);
extern void func_32D5C8(char *, char *, char *);
extern int func_32E728(float);
extern void func_352000(char *, int, int, int);
extern void func_32D8A8(char *, char *, float);
extern void moby_fade_out_update();
extern int D_L06_001B375C __attribute__((sda));
extern int D_L06_001B3758 __attribute__((sda));
extern void func_L06_003DDCA8();
extern int func_32D238(char *);
extern int func_35A620(int);
extern void func_35A270(char *, int, int, int);
extern void *D_L06_002E1F00[];
extern char *func_31B0D0(char *, int, int, int, float, float, char *, char *, char *,
                         int);
extern char D_L06_001A8F20[];
/* Pushes the moby away and starts its tumbling fall with a burst of effects. */
extern void object_start_tumble(char *);

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(float *, float *, float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(float *, float *, float);
extern int moby_move_over_ground(char *, char *, char *, int, float, float, float, float);
extern float ApproachValue(float *, float, float);
extern float math_step_value_toward_target(float *, char *, float, float, float, float);
extern f32 math_approach_target_with_direction_mode(char *, float, float, float, float, char *, int);
extern float FastDiffRots(float, float);
extern int ComputeRegionRouteHeading(char *, int, float *, char *, int, char *, char *, float,
                             float);


/* Picks the actor's next walking or idle animation after it reaches a goal or finishes a turn. */
void actor_choose_idle_anim(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    if (*(int *)(vars + 0x5A0) == 1) {
        if (*(int *)(vars + 0x23C) == -1) {
            if (func_32D238(vars + 0x25C)) {
                func_35A550(moby, 7, 2);
                if (*(unsigned char *)(moby + 0x43) != 0x13) {
                    func_35A270(moby, 0x13, 0, 20);
                }
                vars[0x48] = func_32E728(20.0f);
                vars[0x4A] = func_32E728(24.0f);
            }
        } else {
            func_35A550(moby, 8, 2);
            if (*(unsigned char *)(moby + 0x43) != 0x12) {
                func_35A270(moby, 0x12, 0, 20);
            }
            vars[0x48] = func_32E728(20.0f);
            vars[0x4A] = func_32E728(24.0f);
        }
    } else if (*(short *)(vars + 0x492) != 0 && func_32D238(vars + 0x25C)) {
        *(short *)(vars + 0x492) = 0;
        func_35A550(moby, 7, 2);
        if (!func_35A620(2)) {
            if (*(unsigned char *)(moby + 0x43) != 0x11) {
                func_35A270(moby, 0x11, 0, 20);
            }
            vars[0x48] = func_32E728(20.0f);
            vars[0x4A] = func_32E728(24.0f);
        } else {
            if (*(unsigned char *)(moby + 0x43) != 0x13) {
                func_35A270(moby, 0x13, 0, 20);
            }
            vars[0x48] = func_32E728(20.0f);
            vars[0x4A] = func_32E728(24.0f);
        }
    } else if (*(short *)(vars + 0x492) == 0 && func_32D238(vars + 0x25C)) {
        func_35A550(moby, 9, 2);
        if (*(unsigned char *)(moby + 0x43) != 0x12) {
            func_35A270(moby, 0x12, 0, 20);
        }
        vars[0x48] = func_32E728(20.0f);
        vars[0x4A] = func_32E728(24.0f);
    }
}

void object_start_tumble(char *a0)
{
    char *s2 = *(char **)(a0 + 0x68);
    int v;

    func_32D5C8(a0 + 0x10, a0 + 0x10, s2);
    v = func_32E728((float)D_L06_001B375C * 1.5f);
    func_352000(a0, v, func_32E728((float)D_L06_001B375C * 1.25f), D_L06_001B375C);
    if (D_L06_001B3758 != 0) {
        func_32D8A8(s2, s2, 0.11666667461395264f);
        *(float *)(s2 + 0x8) = *(float *)(s2 + 0x8) + 0.18333333730697632f;
        *(unsigned int *)(a0 + 0x64) = (unsigned int)func_L06_003DDCA8;
        *(float *)(a0 + 0x2C) = *(float *)(a0 + 0x2C) * 0.75f;
        func_352000(a0, 0x10, 0x10, 0x10);
    }
}

/* Turns the head toward the hero, within a limited left-right and up-down range. */
void actor_aim_head_at_hero(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float to_hero[3];

    func_32D5F8((char *)to_hero, D_L06_00189EA0, moby + 0x10);
    func_365030(moby, (char *)to_hero, (char *)to_hero, 0);
    *(float *)(vars + 0x2C0) = func_32DC80(to_hero[0], to_hero[1]);
    if (*(float *)(vars + 0x2C0) > 0.78539825f) {
        *(float *)(vars + 0x2C0) = 0.78539825f;
    } else if (*(float *)(vars + 0x2C0) < -0.78539825f) {
        *(float *)(vars + 0x2C0) = -0.78539825f;
    }
    *(float *)(vars + 0x2C8) = -func_32DC80(func_32D740((char *)to_hero), to_hero[2]);
    if (*(float *)(vars + 0x2C8) > 0.52359885f) {
        *(float *)(vars + 0x2C8) = 0.52359885f;
    } else if (*(float *)(vars + 0x2C8) < -0.52359885f) {
        *(float *)(vars + 0x2C8) = -0.52359885f;
    }
}

/* A breakable object: waits to be hit, then bursts into particles and disappears. */
void breakable_l06_object_update(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x800;
        func_35A550((char *)moby, 1, -1);
        break;
    case 1:
        if (func_35CBA0((char *)moby, 0x4010000, 0) != 0) {
            if (*(int *)vars == 0) {
                func_35A550((char *)moby, 2, -1);
            }
        }
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        char offset[16];

        func_32D650(offset, (char *)(moby + 0xD0), -0.033333335f);
        part_spawn_debris_mask((char *)moby, 7, offset, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_3A0948(0, 0, (char *)moby);
        func_3661E0((char *)moby, 1, 0.0f);
        func_350388((char *)moby);
        break;
    }
    }
}

/* Same breakable object behaviour as func_L06_00457AD0, used by another object type. */
void breakable_object_alt_update(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x800;
        func_35A550((char *)moby, 1, -1);
        break;
    case 1:
        if (func_35CBA0((char *)moby, 0x4010000, 0) != 0) {
            if (*(int *)vars == 0) {
                func_35A550((char *)moby, 2, -1);
            }
        }
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        char offset[16];

        func_32D650(offset, (char *)(moby + 0xD0), -0.033333335f);
        part_spawn_debris_mask((char *)moby, 7, offset, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_3A0948(0, 0, (char *)moby);
        func_3661E0((char *)moby, 1, 0.0f);
        func_350388((char *)moby);
        break;
    }
    }
}

/* Switches on the linked object, if this object has one. */
void trigger_linked_object(char *moby)
{
    if (*(unsigned char *)(moby + 0x21) != 0xFF)
        func_35B810(*(unsigned char *)(moby + 0x21), 1);
}

/* func_L06_0041DED8 is defined in L06_0041DED8-update.c. */

extern char D_L06_001B0820[];
extern char D_L06_001B9840[];
extern int path_build_route_nodes(void *, int, void *, int);
extern void STUB_printf(const char *, ...);
extern float math_random_signed_float_range(float, float);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern void actor_alert_group(u8 *);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);
extern void SetDeathBits(void *, int, int);
extern void part_spawn_explosion_with_sparks(void *, void *, int, float, float);
extern void moby_mark_spawned(void *);

/* A Notak enemy's update, the same shape as func_L06_00443A38: spawn-time setup, then the
   distance, target and ground checks. The fields are indexed through typed pointers (in-struct
   MEMs), and the setup's store order is the one that gives retail's schedule and registers.
   qzero_nc's bare volatile asm flushes cse, so the later `m[0x43] != 3` test builds a fresh 3
   rather than keeping the setup's 3 in a saved register across the calls, as retail does. */
#define B(o) (v[o])
#define H(o) (((short *)v)[(o) / 2])
#define I(o) (((int *)v)[(o) / 4])
#define F(o) (((float *)v)[(o) / 4])

void actor_init_and_check_hits(u8 *moby)
{
    u8 *v = *(u8 **)(moby + 0x68);
    int hit_result;

    if (moby[0x20] == 0) {
        I(0x480) = path_build_route_nodes(moby, I(0x230), v + 0x260, 16);
        STUB_printf(D_L06_001B0820, I(0x480));
        qcopy(v + 0x460, moby + 0x10);
        F(0x46C) = *(float *)(moby + 0xF8);
        B(0x70) = 15;
        I(0xA8) = 3;
        B(0x71) = 12;
        F(0x90) = 0.5f;
        B(0x28) = 1;
        B(0xD4) = 0;
        H(0x26) = 0;
        B(0x72) = 16;
        B(0x76) = 14;
        B(0x77) = 15;
        F(0x7C) = 0.20000002f;
        F(0x80) = 0.125f;
        F(0x84) = 0.00555555569f;
        F(0x88) = 0.00972222257f;
        F(0x8C) = 0.00416666688f;
        F(0x94) = 0.5f;
        F(0x9C) = 0.4f;
        B(0xCC) = 7;
        B(0xCD) = 12;
        B(0xCE) = 3;
        B(0xCF) = 5;
        B(0xD2) = 10;
        B(0xD3) = 17;
        F(0x5AC) = (float)B(0x34);
        B(0x29) = 1;
        F(0x30) = 0.75f;
        F(0x47C) = math_random_signed_float_range(10.0f, 25.0f) * 0.0174532942f;
        I(0x478) = 0;
        H(0x24C) = math_random_int_range(0, 0x5F);
        I(0x498) = -1;
        I(0x5A0) = H(0x490);
        qzero_nc(v + 0x5B0);
        moby_set_state(moby, 1, 0);
        if (moby[0x43] != 1)
            anim_start_blended(moby, 1, 0, 0);
        B(0x48) = FloatToInt(20.0f);
        B(0x4A) = FloatToInt(8.0f);
        if (H(0x492) != 0) {
            if (moby[0x43] != 3)
                anim_start_blended(moby, 3, 0, 0);
            B(0x48) = FloatToInt(20.0f);
            B(0x4A) = FloatToInt(24.0f);
        }
    }
    if (moby[0x31] != 0 && fast_vec_dist(moby + 0x10, D_L06_001B9840) < 24.0f) {
        moby_update_ground_check(moby);
        moby[0x6F] = 0x16;
    }
    hit_result = moby_apply_damage_to_object(moby, v + 0x60, 0);
    if (hit_result != 0) {
        if (B(0x37) == 10)
            B(0xD7) = 1;
        if (hit_result == 5) {
            I(0xF0) = 0;
            F(0xF4) = 0.837758183f;
        }
        actor_alert_group(moby);
        moby[0xA8] = 0xFF;
    }
    I(0x228) = weapon_select_aim_target(moby, I(0x220), F(0x240), 10.0f, 0, 0);
    I(0x22C) = weapon_select_aim_target(moby, I(0x224), F(0x244), 10.0f, 0, 0);
    if (*(float *)(moby + 0x18) < 48.0f) {
        SetDeathBits(moby, 0, 3);
        part_spawn_explosion_with_sparks(moby, moby + 0x10, -1, 1.0f, 13.0f);
        moby_mark_spawned(moby);
    }
}

#undef B
#undef H
#undef I
#undef F

/* Turns the actor toward its target and keeps the two angles it stores at +0x470 and
   +0x474 of its state; returns 1 when the actor's state changed. */
int actor_steer_toward_goal(char *moby, char *goal, float default_yaw, float speed_scale, float slow_distance, float turn_rate)
{
    char *vars = *(char **)(moby + 0x68);
    float to_goal[4];
    float step[4];
    float next_pos[4];
    float d = 0.0f;
    float desired_yaw;
    float distance;
    float accel_step;
    int changed = 0;

    FastVecSub(to_goal, (float *)goal, (float *)(moby + 0x10));
    to_goal[2] = 0.0f;
    distance = FastVecLength(to_goal);
    accel_step = speed_scale * 0.0008333333535119891f;
    if (slow_distance < distance) {
        int path_count = *(int *)(vars + 0x480);

        desired_yaw = 0.0f;
        ComputeRegionRouteHeading(moby + 0x10, (int)goal, &desired_yaw, vars + 0x260, path_count, vars + 0x488,
                          vars + 0x48C, turn_rate, 0.5f);
        math_approach_target_with_direction_mode(moby + 0xF8, desired_yaw, 0.0037815470714122057f,
                      0.0037815470714122057f, 0.29670602083206177f, vars + 0x474, 0);
        if (FastDiffRots(*(float *)(moby + 0xF8), desired_yaw) < 1.3089970350265503f) {
            math_step_value_toward_target(&d, vars + 0x470, distance, accel_step, accel_step, speed_scale * 0.01666666753590107f);
        } else {
            *(float *)(vars + 0x470) = 0.0f;
        }
    } else {
        math_approach_target_with_direction_mode(moby + 0xF8, default_yaw, 0.0037815470714122057f,
                      0.0037815470714122057f, 0.29670602083206177f, vars + 0x474, 0);
        ApproachValue((float *)(vars + 0x470), 0.0f, accel_step);
        if (*(float *)(vars + 0x470) == 0.0f) {
            if (FastDiffRots(*(float *)(moby + 0xF8), default_yaw) < 0.0872664749622345f) {
                *(float *)(vars + 0x474) = 0.0f;
                changed = 1;
            }
        }
    }
    vec_scale_to_length(step, (float *)(moby + 0xC0), *(float *)(vars + 0x470));
    FastVecAdd(next_pos, step, (float *)(moby + 0x10));
    if (moby_move_over_ground(moby, moby + 0x10, (char *)next_pos, 0, 0.8999999761581421f, 1.0f, 0.5f,
                     0.7853982448577881f) == 0) {
        *(int *)(vars + 0x5A8) = *(int *)(vars + 0x5A8) + 1;
    }
    /* The counter at +0x5A8 wraps at 0x14, and the actor then reports the change. */
    if (*(int *)(vars + 0x5A8) < 0x14) {
        goto done;
    }
    *(int *)(vars + 0x5A8) = 0;
    changed = 1;
done:
    return changed;
}

/* func_L06_0041F558 is defined in L06_0041F558.c. */

extern char D_L06_001B9840[];
extern int func_35A620(int);
extern float func_35A718(float, float);
extern void func_361300(void *, void *, void *, float);
extern char *func_37A018(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_32E728(float);
extern float func_35A6B8(float, float);

/* Throws a burst of colored particles away from the hero's side of the given position. */
void part_spawn_colored_burst(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    func_32D5F8((char *)direction, (char *)D_L06_001B9840, (char *)pos);
    func_32D8A8((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_35A6B8(0.5f, 2.0f);
        sign = func_35A620(2);
        if (!sign) sign--;
        angle = func_35A6B8(-1.0471977f, 1.0471977f);
        func_361300(velocity, direction, axis, angle);
        func_32D8A8((char *)velocity, (char *)velocity, func_35A6B8(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = func_35A6B8(1.0f, 5.0f) * 0.0166666675f;
        func_32D5C8((char *)origin, (char *)pos, (char *)offset);
        pos[0] += func_35A718(0, 0.15f);
        pos[1] += func_35A718(0, 0.15f);
        pos[2] += func_35A718(0, 0.15f);
        particle = func_37A018(origin, 20, size * 0.1f, size, 0x7F801010, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_32E728(4.0f) + 0x70;
        particle = func_37A018(origin, 20, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_32E728(4.0f) + 0x70;
    }
}



/* func_L06_0041FC58 is matched in its own unit, src/levels/06_notak/L06_0041FC58-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* Counts down the actor's timers and puffs out a few dust particles each frame. */
void actor_tick_timers_spawn_dust(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float velocity[4], position[4];
    int count;
    unsigned char *first, *particle;
    gfx_update_color_fade(moby, vars + 0x50);
    if (moby[0xBC]) {
        moby[0xBC] = 0;
        if (*(int *)(vars + 0x248) < 300)
            *(int *)(vars + 0x248) = math_random_int_range(480, 600);
    }
    if (math_fast_float_d(vars + 0x24C) && *(int *)(vars + 0x204) != 2)
        math_fast_float_d(vars + 0x248);
    math_fast_float_d(vars + 0x240);
    if (*(unsigned short *)(moby + 0x96) < 65534) ++*(unsigned short *)(moby + 0x96);
    if (math_fast_float_d(vars + 0x250)) *(float *)(vars + 0x290) = *(float *)(vars + 0x298);
    velocity[0] = 0;
    velocity[2] = -0.05f;
    velocity[3] = 1;
    velocity[1] = 0;
    count = math_random_int_below(16);
    if (math_random_int_below(2)) count = -count;
    qcopy(position, moby + 0x10);
    position[2] -= 0.2f;
    first = SpawnSpinningSparkParticle((char *)position, .1f, 1, .9f, count, (char *)velocity, 315000, 0xDF204080, 0);
    if (first) {
        unsigned char *state;
        *(short *)(first + 0xA) = 9;
        state = first + 0x20;
        first[9] = FloatToInt(4) + 0x70;
        *(int *)(state + 4) = 2;
        state[0xA] = 0xDF;
        state[0xB] = first[0xA];
    }
    {
        unsigned char *second = SpawnSpinningSparkParticle((char *)position, .1f, 1, .9f, count, (char *)velocity, 315000, 0xDF204080, 0);
        if (second) {
            unsigned char *state = second + 0x20;
            /* Retail reuses the first particle header here. */
            *(short *)(first + 0xA) = 9;
            first[9] = FloatToInt(4) + 0x70;
            *(int *)(state + 4) = 2;
            state[0xA] = 0xDF;
            state[0xB] = first[0xA];
        }
    }
    particle = SpawnSpinningSparkParticle((char *)position, .05f, 1, .97f, 16, (char *)velocity, 157500, 0x8FFFFFFF, 0);
    if (particle) {
        unsigned char *state;
        state = particle + 0x20;
        particle[9] = FloatToInt(4) + 0x70;
        *(short *)(particle + 0xA) = 23;
        particle[8] = math_random_int_below(255);
        *(int *)(state + 4) = 2;
        state[0xA] = 0x8F;
        state[0xB] = first[0xA];
    }
}

/* func_L06_00420080 is defined in L06_00420080.c. */


/* func_L06_00420548 is defined in L06_00420548-g.c. */

/* func_L06_00420740 is defined in L06_00420740.c. */

/* func_L06_00420AE8 is defined in L06_00420AE8-g8.c. */

/* The object runs through five states. The dispatch reads the level's own jump table (five
   words in the level's data at 0x2E1F00); `cases` only keeps the labels alive. */
/* Opens and closes a mechanism in five steps, playing an animation for each step. */
void five_state_mechanism_update(char *moby)
{
    static void *cases[5] = {&&c0, &&c1, &&c2, &&c3, &&c4};
    char *obj = moby;
    char *vars;
    unsigned int step;

    step = *(unsigned char *)(obj + 0x20);
    vars = *(char **)(obj + 0x68);
    if (step < 5)
        goto *D_L06_002E1F00[step];
    goto done;
c0:
    *(unsigned char *)(obj + 0x20) = 1;
    *(int *)vars = 0x5DC;
    goto done;
c1:
    if (*(unsigned char *)(obj + 0xBC) == 0)
        goto done;
    *(unsigned char *)(obj + 0x20) = 2;
    if (*(unsigned char *)(obj + 0x43) != 1)
        func_35A270(obj, 1, 0, 0);
    *(int *)(obj + 0x98) = 0;
    goto done;
c2:
    if ((*(unsigned char *)(obj + 0x60) & 2) == 0)
        goto done;
    *(unsigned char *)(obj + 0x20) = 3;
    if (*(unsigned char *)(obj + 0x43) == 2)
        goto done;
    func_35A270(obj, 2, 0, 0);
    goto done;
c3:
    if (func_32D238(vars) == 0)
        goto done;
    *(unsigned char *)(obj + 0x20) = 4;
    if (*(unsigned char *)(obj + 0x43) == 3)
        goto done;
    func_35A270(obj, 3, 0, 0);
    goto done;
c4:
    if ((*(unsigned char *)(obj + 0x60) & 2) == 0)
        goto done;
    *(unsigned char *)(obj + 0x20) = 1;
    if (*(unsigned char *)(obj + 0x43) == 0)
        goto tail;
    func_35A270(obj, 0, 0, 0);
tail:
    *(int *)(obj + 0x98) = *(int *)(*(int *)(obj + 0x24) + 0x10);
    *(int *)vars = 0x5DC;
    func_35B810(*(unsigned char *)(obj + 0x21), 0);
    goto done;
done:
    return;
}

/* func_L06_00430318 is defined in L06_00430318-g8.c. */


/* func_L06_00443280 is defined in L06_00443280-g8.c. */

/* func_L06_00443A38 is defined in L06_0041DED8-g8.c. */

/* Starts or stops the actor's glow effect. */
int actor_set_glow_effect(char *moby, int unused, int mode)
{
    char *vars = *(char **)(moby + 0x68);
    int result;

    if (mode == 0) {
        result = func_36C158();
    } else {
        result = func_36C1B0(*(float *)(vars + 0x31C));
    }
    return result;
}

/* Counts down the actor's timers, ages it by one frame and updates its effects. */
void actor_tick_timers_effects(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    unsigned int age;

    func_32D268(vars + 0x310);
    func_32D268(vars + 0x312);
    age = *(unsigned short *)(moby + 0x96);
    if (age <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) = age + 1;
    func_366160(moby, vars + 0x260, 2.5f, 0, 1);
}


/* func_L06_00444168 and func_L06_00444300 live in L06_0041DED8-g8.c (func_L06_00444300 reaches
 * its constants through $gp; the pair is the level 6 twin of func_L14_00428A08/func_L14_00428BA0). */

/* The same re-arm, with two probe addresses and two flags. */
/* When the hero reaches the object's trigger, switches on both gate flags and moves the object to its next state. */
void gate_trigger_two_flags_update(char *moby)
{
    int handle;

    if (*(unsigned char *)(moby + 0x20) != 0)
        return;
    handle = *(int *)(*(int *)(moby + 0x68));
    if (handle == -1)
        return;
    if (func_360F58(D_L06_00189EA0, handle) == 0)
        return;
    func_2E3EF0(D_L06_001B1330);
    func_2E3EF0(D_L06_001B1370);
    D_L06_001395B8.flag_013 = 1;
    D_L06_001395B8.flag_014 = 1;
    func_35A550(moby, 1, -1);
}

/* Re-arms the object when the shared probe accepts its live handle. */
/* When the hero reaches the object's trigger, sets the first gate flag and moves the object to its next state. */
void gate_trigger_flag_a_update(char *moby)
{
    int handle;

    if (*(unsigned char *)(moby + 0x20) != 0)
        return;
    handle = *(int *)(*(int *)(moby + 0x68));
    if (handle == -1)
        return;
    if (func_360F58(D_L06_00189EA0, handle) == 0)
        return;
    func_2E3EF0(D_L06_001B13B0);
    D_L06_001395CE = 1;
    func_35A550(moby, 1, -1);
}

/* The same re-arm, with the level's second probe address. */
/* When the hero reaches the object's trigger, sets the second gate flag and moves the object to its next state. */
void gate_trigger_flag_b_update(char *moby)
{
    int handle;

    if (*(unsigned char *)(moby + 0x20) != 0)
        return;
    handle = *(int *)(*(int *)(moby + 0x68));
    if (handle == -1)
        return;
    if (func_360F58(D_L06_00189EA0, handle) == 0)
        return;
    func_2E3EF0(D_L06_001B13F0);
    D_L06_001395CF = 1;
    func_35A550(moby, 1, -1);
}

/* The same re-arm, gated on the shared live-object probe. */
/* When the hero reaches the object's trigger and the level check passes, sets the third gate flag and moves on. */
void gate_trigger_flag_c_update(char *moby)
{
    int handle;

    if (*(unsigned char *)(moby + 0x20) != 0)
        return;
    handle = *(int *)(*(int *)(moby + 0x68));
    if (handle == -1)
        return;
    if (func_360F58(D_L06_00189EA0, handle) == 0)
        return;
    if (func_333898() == 0)
        return;
    D_L06_001395D0 = 1;
    func_35A550(moby, 1, -1);
}

/* func_L06_00455BC0 is in L06_0041DED8-f7-g8.c. */

/* func_L06_00456278 is in L06_00456278.c. */


/* Clears the level's pool of small effect objects. */
void effect_pool_clear(void)
{
    func_3BFBB8(D_L06_002AA500, 0x30);
}

/* func_L06_00456F08 is defined in L06_00456F08.c. */

/* func_L06_00457270 is in L06_00457270.c: its zeroed vector is a por. */

/* func_L06_004573E8 is in L06_004573E8-g8.c. */


/* func_L06_004577B0 lives in L06_0041DED8-g8.c: it reads its first angle through $gp. */



extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern char *cam_moby_create(char *, int, int, int, char *, char *,
                           float *, int, float, float);

void part_spawn_debris_mask(char *object, int mask, void *offset, int color,
                      float speed_min, float speed_max,
                      float vertical_min, float vertical_max)
{
    float velocity[3];
    float angle, speed, life, size;
    char *particle;
    unsigned char shade = color;
    int i;

    for (i = 0; i < 15; i++) {
        if (((mask >> i) ^ 1) & 1)
            continue;
        angle = math_random_angle();
        speed = math_random_float_range(speed_min, speed_max) * (1.0f / 60.0f);
        velocity[0] = math_fast_sin_or_cos_a(angle) * speed;
        velocity[1] = math_fast_sin_or_cos_b(angle) * speed;
        velocity[2] = 0.0f;
        velocity[2] = math_random_float_range(vertical_min, vertical_max) * (1.0f / 60.0f);
        FastVecAdd(velocity, velocity, offset);
        life = math_random_float_range(90.0f, 270.0f);
        size = math_random_float_range(10.0f, 20.0f);
        particle = cam_moby_create(object, 2, *(short *)(object + 0xAA), i,
                                object + 0x10, object + 0xF0, velocity, shade,
                                life, size);
        if (particle)
            *(unsigned short *)(particle + 0x34) |= 0x10;
    }
}

/* When hit, wakes up the actors in its linked groups and then removes itself. */
void wake_actors_trigger_update(unsigned char *moby)
{
    char *vars;
    char *hit_moby;
    short *id_list, *id_cursor;
    char *actor;
    char *actor_vars;
    if (moby[0x20] == 0) {
        *(unsigned short *)(moby + 0x34) |= 0x800;
        moby[0x20] = 1;
    }
    vars = *(char **)(moby + 0x68);
    hit_moby = (char *)func_35CBA0((char *)moby, 0x10000, 0);
    if (hit_moby && *(short *)(*(char **)(hit_moby + 0x20) + 0xAA) != 0xFE5 /* moby class 4069 */) {
        if (*(int *)vars == 255) { func_458138((char *)moby); return; }
        {
            id_list = D_L06_001FB3A0[*(int *)vars];
            if (id_list == 0) { func_458138((char *)moby); return; }
            {
                id_cursor = id_list;
                do {
                    actor = D_L06_001B281C[0] + ((*id_cursor & 0x7FFF) << 8);
                    if (*(signed char *)(actor + 0x20) >= 0 && *(short *)(actor + 0xAA) == 0xBBA /* moby class 3002 */) {
                        actor_vars = *(char **)(actor + 0x68);
                        if (*(float *)(actor_vars + 0x20) > 0.0f) {
                            *(float *)(actor_vars + 0x5A4) = func_35A780();
                            qcopy(actor_vars + 0x5B0, actor_vars + 0x460);
                            *(short *)(actor_vars + 0x24C) = 0x10E;
                            actor[0x20] = 4;
                            func_35A270(actor, 6, 0, 10);
                            *(int *)(actor_vars + 0x5A0) = 0;
                            *(short *)(actor_vars + 0x492) = 0;
                            actor[0x20] = 5;
                            actor[0x95] = 1;
                        }
                    }
                } while (*id_cursor++ >= 0);
            }
        }
        if (*(int *)(vars + 4) == 255) goto destroy;
        id_list = D_L06_001FB3A0[*(int *)(vars + 4)];
        if (id_list == 0) {
 destroy:
            func_458138((char *)moby); return;
        }
        {
            id_cursor = id_list;
            do {
                actor = D_L06_001B281C[0] + ((*id_cursor & 0x7FFF) << 8);
                if (*(signed char *)(actor + 0x20) >= 0 && *(short *)(actor + 0xAA) == 0xBBA /* moby class 3002 */) {
                    actor_vars = *(char **)(actor + 0x68);
                    *(float *)(actor_vars + 0x5A4) = func_35A780();
                    qcopy(actor_vars + 0x5B0, actor_vars + 0x460);
                    *(short *)(actor_vars + 0x24C) = 0x10E;
                    actor[0x20] = 4;
                    func_35A270(actor, 6, 0, 10);
                    actor[0x20] = 5;
                    actor[0x95] = 1;
                }
            } while (*id_cursor++ >= 0);
        }
        func_458138((char *)moby);
    }
    moby[0xA8] = 255;
}
