#include "include_asm.h"
#include "names.h"

/* This unit is built with -G8: every body here reaches a global through $gp. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int TI128 __attribute__((mode(TI)));

extern float g_path_movement_seconds __attribute__((sda));

extern float g_vanish_sweep_radius __attribute__((sda));

extern float g_pop_touch_radius __attribute__((sda));

extern float g_yeedil_projectile_radius __attribute__((sda));

extern float g_turret_bob_amplitude __attribute__((sda));

extern float g_turret_bob_phase __attribute__((sda));

extern float g_turret_bob_amount __attribute__((sda));

extern float g_turret_small_turn_step __attribute__((sda));

extern float g_turret_turn_step __attribute__((sda));

extern int g_frame_l20_counter __attribute__((sda));

extern void moby_set_state(char *, int, int);

extern void FastVecSub(void *, void *, void *);

extern void vec_scale_to_length(void *dst, void *src, float x);

extern float vec_length_xy(void *vec);

extern void vec_fast_normalize_helper(char *a, char *b);

extern int path_push_point_away(char *a, char *b, char *c, float f);

extern char *part_spawn_blast_effect_moby(char *, char *, void *, float);

/* func_002A8C28 returns a value here: retail keeps $v0 live after the call,
   and only a non-void prototype gives the flag word $v1 instead of $v0. */
extern int coll_sweep_from_object(char *, char *, int, int, float, float, float, int, int);

extern float FastAddRotations(float, float);

extern float math_fast_sin_or_cos_b(float);

extern void part_queue_ground_shadow(char *, float);

extern float mat_fast_helper_a(float, float);

extern float math_approach_target_with_direction_mode(char *a, char *b, int c, float d, float e, float f,
                            float g);

extern float ApproachValue(float *, float, float);

extern void *CreateMoby(int);

extern void moby_init_child_from_parent(u8 *, u8 *);

extern float math_random_angle(void);

extern void euler_rotation_basis(void *, void *);

extern float math_random_float_range(float a, float b);

extern int coll_process_hit(float f, char *a, int b, char *c, int d);

extern void moby_local_to_world_point(char *arg0, char *arg1);

extern char g_camera_l20_position[] __attribute__((nosda));

/* Turns the turret to face its target and eases its yaw and pitch toward the aimed angles. */
void turret_turn_toward_target(char *moby) {
    char *state = *(char **)(moby + 0x68);
    char *angles = moby + 0xF8;
    float deltaX = *(float *)(state + 0x140) - *(float *)(moby + 0x10);
    float deltaY = *(float *)(state + 0x144) - *(float *)(moby + 0x14);
    float smallStep = g_turret_small_turn_step * 4.84813745e-06f;
    float turnStep = g_turret_turn_step * 0.000290888245f;
    float heading;

    heading = mat_fast_helper_a(deltaX, deltaY);
    math_approach_target_with_direction_mode(angles, state + 0x1A4, 0, heading, smallStep, smallStep, turnStep);
    turnStep = turnStep * 4.0f;
    ApproachValue(moby + 0x0F0, *(float *)(state + 0x1A8), turnStep);
    *(float *)(state + 0x1A8) = 0.0f;
    ApproachValue(moby + 0x0F4, *(float *)(state + 0x1AC), turnStep);
    *(float *)(state + 0x1AC) = 0.0f;
}

/* Makes the object vanish with an impact effect and puts it back into its resting state. */
void moby_vanish_with_effect(char *moby) {
    TI128 offset;

    FastVecSub(&offset, g_camera_l20_position, moby + 0x10);
    vec_scale_to_length(&offset, &offset, 1.0f);
    part_spawn_blast_effect_moby(moby, moby + 0x10, &offset, *(float *)(moby + 0x18) - 0.5f);
    coll_sweep_from_object(moby, moby + 0x10, 0x10000, 0, 6.0f, g_vanish_sweep_radius, 2.0f,
                  1, 0);
    *(int *)(moby + 0x98) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
    moby_set_state(moby, 1, -1);
}

/* func_L20_0044A838 is defined in L20_0044A838-g8.c. */

/* func_L20_00449BB0 is defined in L20_00449BB0-g8.c. */

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

/* The moby fields func_L20_00449FD0 sets.  Written as casts of byte offsets, these four
   accesses let the scheduler put the $gp scale load after the pVars load; as struct
   members they give retail's order.  The float/int/float parameter order follows the
   0x14/0x18/0x1C fields it fills (a0-a3 and $f12/$f13 are assigned as before). */
typedef struct {
    u8 pad00[0x20];
    u8 state;        /* 0x20 */
    u8 pad21[3];
    char *pClass;    /* 0x24 */
    u8 pad28[4];
    float scale;     /* 0x2C */
    u8 pad30[4];
    u16 flags;       /* 0x34 */
    u8 pad36[0x68 - 0x36];
    char *pVars;     /* 0x68 */
} Moby449FD0;

/* Creates a new projectile (moby class 4846) at a position, with a direction, speed and lifetime, and returns it. */
char *yeedil_projectile_spawn(char *template, char *position, char *direction, float speed, int lifetime,
                        float extraValue) {
    char *projectile;
    char *state;

    projectile = CreateMoby(0x12EE /* moby class 4846 */);
    if (projectile != 0) {
        moby_init_child_from_parent((u8 *)projectile, (u8 *)template);
        qcopy(projectile + 0x10, position);
        *(float *)(projectile + 0xF0) = math_random_angle();
        *(float *)(projectile + 0xF4) = math_random_angle();
        euler_rotation_basis(projectile + 0xC0, projectile + 0xF0);
        ((Moby449FD0 *)projectile)->state = 1;
        ((Moby449FD0 *)projectile)->flags |= 0x100;
        ((Moby449FD0 *)projectile)->scale =
            *(float *)(((Moby449FD0 *)projectile)->pClass + 0x24) * g_yeedil_projectile_radius;
        state = ((Moby449FD0 *)projectile)->pVars;
        qcopy(state, direction);
        *(float *)(state + 0x14) = speed * 0.016666668f;
        *(int *)(state + 0x18) = lifetime;
        *(float *)(state + 0x1C) = extraValue;
        *(int *)(state + 0x20) = 0x3C;
        *(float *)(state + 0x10) = math_random_float_range(10.0f, 20.0f) * 0.00027777778f;
    }
    return projectile;
}

/* func_L20_0044B100 is defined in L20_0044B100-g8.c. */

/* func_L20_0044A658 is defined in L20_0044A658-g8.c. */

/* func_L20_0044A8F0 is defined in L20_0044A8F0-g8.c. */

/* func_L20_00449338 is defined in L20_00449338-g8.c. */
