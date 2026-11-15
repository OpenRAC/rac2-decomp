#include "common.h"
extern void matrix_mul_vec3(float *, float *, float *);
extern void func_338398(char *, char *, float, int, int);
extern void func_32E480(char *, char *, int, float, float, float, int, int, int);
/* A path stores its point count in a 16-byte header, followed by vectors. */
struct RotorPath {
    int count;
    char pad04[12];
    float points[0][4];
};

/* The rotor's state (the object's field 0x68): a 13-point chain, the ten records it drives
   and the path it follows. Only the fields these functions use are named. */
struct RotorState {
    /* 0x000 */ char pad00[0x35];
    /* 0x035 */ u8 f35;
    /* 0x036 */ char pad36[0x1A];
    /* 0x050 */ float aim[4];
    /* 0x060 */ int f60;
    /* 0x064 */ char pad64[0x9C];
    /* 0x100 */ float points[13][4];
    /* 0x1D0 */ float oldPoints[13][4];
    /* 0x2A0 */ char pad2A0[0x10];
    /* 0x2B0 */ int choices[4][4];
    /* 0x2F0 */ char pad2F0[0x30];
    /* 0x320 */ int pathIndex;
    /* 0x324 */ struct RotorPath *path;
    /* 0x328 */ char pad328[8];
    /* 0x330 */ int records[10];
    /* 0x358 */ int linked;
    /* 0x35C */ char pad35C[0xC];
    /* 0x368 */ int projectileClass;
    /* 0x36C */ char pad36C[4];
    /* 0x370 */ s16 pathPoint;
    /* 0x372 */ char pad372[2];
    /* 0x374 */ s16 projectileIndex;
    /* 0x376 */ s16 projectileDelay;
    /* 0x378 */ s16 ropeCount;
    /* 0x37A */ u16 toggle;
    /* 0x37C */ char pad37C[4];
    /* 0x380 */ u8 disabled[10];
};

/* A basis vector whose fourth word is cleared as an integer. */
struct RotorAxis {
    float x, y, z;
    int w;
};

/* A rotor moby, and each 256-byte record of the level's table has the same layout. */
struct RotorObject {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ float pos[4];
    /* 0x20 */ u8 mode;
    /* 0x21 */ char pad21[0x13];
    /* 0x34 */ u16 flags;
    /* 0x36 */ char pad36[0x32];
    /* 0x68 */ struct RotorState *state;
    /* 0x6C */ char pad6C[0x4C];
    /* 0xB8 */ int fB8;
    /* 0xBC */ char padBC[4];
    /* 0xC0 */ struct RotorAxis basis[3];
};

extern struct RotorPath *D_L11_001FF580[];
extern char g_sound_state[];
extern void func_3739C0(int);
extern int PlayMobySound(int, int, char *);
extern float IntToFloat(int);
extern float math_lerp_float(float, float, float);
extern f32 ApproachValue(float *, float, float);
extern float FastVecDot(void *, void *);
extern float fast_vec_dist(void *, void *);

extern int g_moby_l11_table __attribute__((sda));

extern void func_32C700();

/* func_L11_00432628 is defined in L11_00432628-dust.c. */

/* func_L11_00434580 lives in L11_00434580-g-g8.c. */

/* func_L11_00434580 is defined in L11_00432628-g8.c. */

extern char *CreateMoby(int);

/* Spawns a class 0xD1B moby: its position is the first vector of its own state, which then
   takes the vectors at a (at +0x00) and b (at +0x20) and the float f (at +0x3C). */
char *SpawnStateVectorMoby(char *obj, void *first_vector, void *second_vector, float value)
{
    typedef int Quadword __attribute__((mode(TI)));
    Quadword vectors[2];
    Quadword *saved = &vectors[1];
    char *moby;
    char *vars;

    vectors[0] = *(Quadword *)first_vector;
    *saved = *(Quadword *)second_vector;
    moby = CreateMoby(0xD1B /* moby class 3355 */);
    if (moby != 0) {
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(unsigned short *)(moby + 0x32) = 0xFF;
        *(unsigned char *)(moby + 0x31) = 1;
        *(unsigned char *)(moby + 0x20) = 0;
        vars = *(char **)(moby + 0x68);
        *(unsigned long long *)(moby + 0x38) = *(unsigned long long *)(obj + 0x38);
        qcopy(moby + 0x10, vars);
        *(Quadword *)vars = vectors[0];
        qcopy(vars + 0x20, saved);
        *(float *)(vars + 0x3C) = value;
        *(int *)(vars + 0x38) = 0;
        *(int *)(vars + 0x34) = 0;
    }
    return moby;
}


typedef int TI128 __attribute__((mode(TI)));

extern void joba_draw_beam_first_stage(char *p, void *q);

extern void joba_draw_beam_second_stage(char *p, void *q);

/* Hands two reads of the state's quadword to the two measured stage helpers. */
/* Each frame, runs the two follow-up effect steps for a thrown projectile. */
void projectile_run_trail_steps(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    TI128 v = *(TI128 *)state;

    joba_draw_beam_first_stage(moby, &v);
    v = *(TI128 *)state;
    joba_draw_beam_second_stage(moby, &v);
}

extern char D_L11_001BA8C0[];
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int FloatToInt(float);
/* Throws out a burst of puffy particles from a point, each flying off at a random angle and speed. */
void part_l11_spawn_impact_burst(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    FastVecSub(direction, (float *)D_L11_001BA8C0, pos);
    vec_scale_to_length((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (!sign) sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        vec_scale_to_length((char *)velocity, (char *)velocity, math_random_float_range(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = math_random_float_range(1.0f, 5.0f) * 0.0166666675f;
        FastVecAdd((char *)origin, (char *)pos, (char *)offset);
        pos[0] += math_random_signed_float_range(0, 0.15f);
        pos[1] += math_random_signed_float_range(0, 0.15f);
        pos[2] += math_random_signed_float_range(0, 0.15f);
        particle = part_spawn_ground_effect(origin, 60, size * 0.1f, size, 0x8020FF20, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = part_spawn_ground_effect(origin, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}


extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float vec_distance_xy(void *, void *);
extern char g_hero_position[];

/* Stops the object's sound if its slot still belongs to it, then forgets the slot. */
static inline void stop_owned_sound(char *state, char *moby)
{
    int slot = *(int *)(state + 0x14);

    if (slot != -1) {
        char *e = g_sound_state + slot * 0x70;

        if (*(char **)(e + 0x88) == moby && *(unsigned char *)(e + 0x74))
            func_3739C0(slot);
    }
    *(int *)(state + 0x14) = -1;
}

/* Five-stage mover driven by the parent's state byte: when the parent reaches 2 it starts its
   sound and moves out along its +0xE0 direction over half a turn (pi/120 a frame); when the
   parent leaves 2 it does the same back, only while D_00189EA0 is more than 6 away, and at a
   full turn returns to its saved position and waits again. */
/* Slides a part out and back along its own direction when the parent object changes state, with a sound while it moves. */
void sliding_part_update(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    char *parent = (char *)(g_moby_l11_table + (*(int *)(state + 8) << 8));
    float offset[4];

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x20) = 1;
        *(float *)(state + 0xC) = 3.1415927f;
        *(float *)(state + 0x10) = 0;
        qcopy(state + 0x20, moby + 0x10);
        *(unsigned short *)(moby + 0x34) |= 0x800;
    case 1:
        if (*(unsigned char *)(parent + 0x20) == 2) {
            char *e = g_sound_state + *(int *)(state + 0x14) * 0x70;

            if (*(char **)(e + 0x88) != moby || !*(unsigned char *)(e + 0x74))
                *(int *)(state + 0x14) = PlayMobySound(0, 4, moby);
            *(unsigned char *)(moby + 0x20) = 2;
            *(float *)(state + 0xC) = 3.1415927f;
            *(float *)(state + 0x10) = 0;
        } else {
            stop_owned_sound(state, moby);
        }
        break;
    case 2:
        *(float *)(state + 0x10) += 0.026179943f;
        *(float *)(state + 0xC) = FastAddRotations(*(float *)(state + 0xC), 0.026179943f);
        if (*(float *)(state + 0x10) >= 3.1415927f) {
            stop_owned_sound(state, moby);
            *(unsigned char *)(moby + 0x20) = 3;
        } else {
            vec_scale_to_length((char *)offset, moby + 0xE0, (math_fast_sin_or_cos_a(*(float *)(state + 0xC)) + 1.0f) * 5.0f);
            FastVecAdd(moby + 0x10, (char *)offset, state + 0x20);
        }
        break;
    case 3:
        if (*(unsigned char *)(parent + 0x20) != 2) {
            char *e = g_sound_state + *(int *)(state + 0x14) * 0x70;

            if (*(char **)(e + 0x88) != moby || !*(unsigned char *)(e + 0x74))
                *(int *)(state + 0x14) = PlayMobySound(0, 4, moby);
            *(unsigned char *)(moby + 0x20) = 4;
        } else {
            stop_owned_sound(state, moby);
        }
        break;
    case 4:
        if (vec_distance_xy(moby + 0x10, g_hero_position) > 6.0f) {
            *(float *)(state + 0x10) += 0.026179943f;
            *(float *)(state + 0xC) = FastAddRotations(*(float *)(state + 0xC), 0.026179943f);
            if (*(float *)(state + 0x10) >= 6.2831855f) {
                stop_owned_sound(state, moby);
                *(unsigned char *)(moby + 0x20) = 1;
                *(float *)(state + 0xC) = 3.1415927f;
                *(float *)(state + 0x10) = 0;
                qcopy(moby + 0x10, state + 0x20);
            } else {
                vec_scale_to_length((char *)offset, moby + 0xE0, (math_fast_sin_or_cos_a(*(float *)(state + 0xC)) + 1.0f) * 5.0f);
                FastVecAdd(moby + 0x10, (char *)offset, state + 0x20);
            }
        }
        break;
    }
}

/* func_L11_00435600 is defined in L11_00435600-g8.c. */

/* func_L11_00436350 is defined in L11_00436350-g8.c. */

/* Counts how many frames the object has lived and draws its glow effects. */
void enemy_count_frames_draw_glow(char *obj)
{
    float tmp[3];
    TI128 tmp2[2];
    char *state;
    float second_value, first_value;

    tmp2[1] = 0;
    state = *(char **)(obj + 0x68);
    first_value = *(float *)(state + 0x100);
    second_value = *(float *)(state + 0x104);
    *(float *)((char *)&tmp2[1] + 8) = second_value + first_value;
    tmp2[0] = tmp2[1];
    matrix_mul_vec3((float *)&tmp2[0], (float *)&tmp2[0], (float *)((char *)obj + 0xC0));
    FastVecAdd((char *)tmp, (char *)obj + 0x10, (char *)&tmp2[0]);
    if (*(unsigned short *)(obj + 0x96) <= 0xFFFE)
        *(unsigned short *)(obj + 0x96) = *(unsigned short *)(obj + 0x96) + 1;
    func_338398(obj, state + 0x290, 2.5f, 1, 1);
    func_32E480(obj, obj + 0x10, 0x4000000, 1.0f, 1.0f, 1.0f, 0, 1, 0);
}


/* Re-arms the measured stage guard, then clears it. */
extern int func_002B3BA8_6850(char *, int, float, float, int, int);

/* Same body as func_L02_003F16F0, with this function's own callees. */
/* Keeps the enemy locked onto its target while it is awake, and drops the lock when it is not. */
void enemy_update_target_lock(char *moby) {
    char *state = *(char **)(moby + 0x68);

    if (*(unsigned char *)(moby + 0x20) < 4) {
        *(int *)(state + 0x270) = 0;
        goto done;
    }

    if (*(short *)(state + 0x282) == 1) {
        *(short *)(state + 0x280) =
            func_002B3BA8_6850(moby, *(int *)(state + 0x27C), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x270) = *(int *)(state + 0x200);
    } else {
        if (arena_consume_waiting_fighter(*(int *)(moby + 0xB8), *(short *)(moby + 0xAA)) == 0)
            goto done;
        *(short *)(state + 0x282) = 1;
        *(short *)(state + 0x280) =
            func_002B3BA8_6850(moby, *(int *)(state + 0x27C), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x270) = *(int *)(state + 0x200);
    }
    return;

done:
    *(short *)(state + 0x282) = 0;
}

extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern void func_002A05A8(char *);
extern void set_moby_color(char *, int, int, int);
extern int moby_spawn_linked(char *, int, float, float);

/* Sets up an enemy when it appears: clears its lock, picks its look (active or resting) and starts its animation. */
void enemy_init_state(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);
    unsigned short flags;
    char *definition;
    int cache;

    *(short *)(state + 0x282) = 0;
    *(short *)(state + 0x88) = 0;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x286) = active;
    moby_set_controller_speed_limits(object, 0.004444444552063942f, 0.13333334028720856f,
                  0.006981317885220051f, 0.20943954586982727f);
    flags = *(unsigned short *)(object + 0x34);
    definition = *(char **)(object + 0x24);
    cache = *(int *)(definition + 0x10);
    *(unsigned short *)(object + 0x34) = (flags | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = cache;
    *(unsigned char *)(object + 0x7F) = 0;
    if (*(short *)(state + 0x286) != 0) {
        moby_set_state(object, 7, 3);
        *(unsigned short *)(object + 0x34) |= 0x100;
        anim_start_blended(object, 1, 0, 0);
        func_002A05A8(object);
        moby_spawn_linked(object, 0, 2.0f, 2.0f);
    } else {
        moby_set_state(object, 3, 0);
        *(unsigned char *)(object + 0x31) = 1;
        *(unsigned short *)(object + 0x34) &= 0xFEFE;
    }
    *(unsigned char *)(state + 0x2E) = 1;
    *(short *)(state + 0x284) = mode;
    *(unsigned char *)(state + 0x6A) = 0;
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        set_moby_color(object, *(unsigned char *)(state + 0x54),
                      *(unsigned char *)(state + 0x55), *(unsigned char *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
}

extern void arena_add_waiting_fighter(unsigned char *object, int class_id);

extern char *SpawnExplosion(char *, int, int, int, int, int, int, int, float, float, int, int, int, int);

extern int snd_play_from_class_bank(int, int, void *, int);

extern void anim_start_blended(void *, int, int, int);

extern void func_002A05A8(char *);

extern void moby_set_state(void *, int, int);

/* Retires the measured stage-46 record: clears the guard, drops the effect and re-tags the object. */
/* Puts the enemy back to rest: drops its target, plays a small puff and sound if it was visible, and resets its flags. */
void enemy_reset_to_idle(char *obj)
{
    char *state = *(char **)(obj + 0x68);

    if (*(short *)(state + 0x282) == 1) {
        arena_add_waiting_fighter(*(unsigned char **)(obj + 0xB8), 0xD37 /* moby class 3383 */);
        *(int *)(state + 0x270) = 0;
    } else {
        *(int *)(state + 0x270) = 0;
    }
    *(short *)(state + 0x282) = 0;
    if (*(unsigned char *)(obj + 0x31)) {
        SpawnExplosion(obj + 0x10, 0, 0, 0x1E, 5, 0, 0x32, 1, 0.3f, 0.0f, 0, 0, 0, 0);
        snd_play_from_class_bank(0, 0, obj, 0xDF7);
    }
    anim_start_blended(obj, 0, 0, 3);
    func_002A05A8(obj);
    moby_set_state(obj, 1, 0);
    *(unsigned char *)(obj + 0x31) = 0;
    *(int *)(obj + 0x98) = 0;
    *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) & 0xEFFF) | 0x47;
}

/* func_L11_00436B78 is defined in L11_00436B78-flags.c. */


/* func_L11_00436F80 is defined in L11_00436F80.c. */

/* func_L11_004375B8 is defined in L11_004375B8.c. */

extern unsigned char D_L11_00438880[];

extern void func_802F8AD0(void *a0, void *a1);
extern void func_80338398(void *a0, void *a1, int a2, int a3, float f12);
extern void rotor_tick_timers(char *p);
extern void IntegrateVerletChain(void *obj);
extern void chain_creature_solve_length(char *p);
extern void chain_creature_update_segments(void *obj);
extern void chain_creature_update_linked(void *obj);

/* Runs the ten rotors' update, one frame each, and restarts the entry timer. */
/* Runs one frame of the chain creature body: moves the chain points and updates every body segment. */
void chain_creature_update_body(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int i;

    func_802F8AD0((void *)D_L11_00438880, moby);

    for (i = 12; i >= 0; i--)
        ;

    if (*(unsigned char *)(moby + 0x20) >= 2) {
        rotor_tick_timers(moby);
        IntegrateVerletChain(moby);
        chain_creature_solve_length(moby);
        chain_creature_update_segments(moby);
        chain_creature_update_linked(moby);
    }
    if (*(unsigned short *)(moby + 0x96) <= 0xFFFE) {
        (*(unsigned short *)(moby + 0x96))++;
    }
    func_80338398(moby, vars + 0x80, 1, 1, 2.5f);
}

/* Walks the ten measured indices, clearing each record selected through 0x330. */
/* Switches all ten body segments to a given animation unless they already play it. */
void chain_creature_set_segments_anim(char *moby, int animation, int mode, int blend)
{
    int i;

    for (i = 0; i < 10; i++) {
        int offset = i * 4;
        int index = *(int *)(*(char **)(moby + 0x68) + offset + 0x330);
        char *record = (char *)(g_moby_l11_table + (index << 8));

        if (*(unsigned char *)(record + 0x43) != animation)
            func_32C700(record, animation, mode, blend);
    }
}

/* Invalidates the measured slot at 0x43 of the 256-byte record indexed by 0x358. */
/* Switches the linked end segment to a given animation unless it already plays it. */
void chain_creature_set_linked_anim(char *moby, int animation, int mode, int blend)
{
    int record = (*(int *)(*(char **)(moby + 0x68) + 0x358) << 8) + g_moby_l11_table;

    if (*(unsigned char *)(record + 0x43) != animation)
        anim_start_blended((char *)record, animation, mode, blend);
}

extern void vec_clear_128(void *);
extern void FastVecScale(void *, void *, float);

/* A 16-byte aligned vector, copied as one quadword. */
typedef union Quad {
    TI128 q;
    float f[4];
} Quad;

/* Advances the thirteen chain points one Verlet step: each moves by its damped displacement
   from its old position plus a small downward pull, and the old position takes the point's
   previous value. The damping blends 0.97 to 0.98 with the count at 0x378. */
void IntegrateVerletChain(void *object)
{
    struct RotorObject *obj = object;
    struct RotorState *state = obj->state;
    float (*pos)[4];
    float (*old)[4];
    Quad saved;
    Quad delta;
    Quad gravity;
    float t;
    float damping;
    int i;

    vec_clear_128(&gravity);
    pos = state->points;
    old = state->oldPoints;
    gravity.f[2] = -1.0f / 720.0f;

    t = IntToFloat(state->ropeCount);
    damping = math_lerp_float(0.97f, 0.98f, (t -= 2.0f) / IntToFloat(8));

    for (i = 12; i >= 0; i--, pos++, old++) {
        qcopy(&saved, pos);
        FastVecSub(delta.f, *pos, *old);
        FastVecScale(&delta, &delta, damping);
        FastVecAdd(pos, pos, &delta);
        FastVecAdd(pos, pos, &gravity);
        qcopy(old, &saved);
    }
}

/* func_L11_00437FD0 lives in L11_00437FD0.c. */

extern void euler_rotation_basis(char *, char *);

/* Lays the thirteen chain points out from the object's position: the step starts as the
   reversed first basis axis, each segment takes its length from the twelve floats at 0x2F0,
   and each old point takes the new point's value. */
void LayOutVerletChain(void *object)
{
    struct RotorObject *obj = object;
    struct RotorState *state = obj->state;
    float (*pos)[4];
    float (*old)[4];
    float (*next)[4];
    float (*nextOld)[4];
    Quad step;
    int i;

    euler_rotation_basis((char *)obj->basis, (char *)obj + 0xF0);
    qcopy(state->points[0], obj->pos);
    qcopy(state->oldPoints[0], obj->pos);
    FastVecScale(&step, obj->basis, -1.0f);
    pos = state->points;
    old = state->oldPoints;
    for (i = 0; i < 12; i++) {
        vec_scale_to_length(&step, &step, ((float *)state->pad2F0)[i]);
        next = pos + 1;
        FastVecAdd(next, pos, &step);
        nextOld = old + 1;
        qcopy(nextOld, next);
        pos = next;
        old = nextOld;
    }
}

extern void FastVecCross(void *a, void *b, void *c);

extern void mat_get_euler_angles(char *a, char *b);

extern f32 math_approach_target_with_direction_mode(char *a, char *b, int c, float d, float e, float f, float g);

/* Builds the measured three-axis basis of the object and hands it to the three slots. */
/* Turns the object smoothly so it faces a given direction. */
void chain_creature_turn_to_face(char *obj, char *direction, float rate1, float rate2, float rate3)
{
    char *state = *(char **)(obj + 0x68);
    float m[4][4];
    float out[4];

    vec_scale_to_length((char *)m[0], direction, 1.0f);
    vec_clear_128((TI128 *)m[2]);
    m[2][2] = 1.0f;
    FastVecCross((char *)m[1], (char *)m[0], (char *)m[2]);
    vec_scale_to_length((char *)m[1], (char *)m[1], 1.0f);
    FastVecCross((char *)m[2], (char *)m[1], (char *)m[0]);
    vec_scale_to_length((char *)m[2], (char *)m[2], 1.0f);
    mat_get_euler_angles((char *)m[0], (char *)out);
    math_approach_target_with_direction_mode(obj + 0xF0, state + 0x2A0, 0, out[0], rate1, rate2, rate3);
    math_approach_target_with_direction_mode(obj + 0xF4, state + 0x2A4, 0, out[1], rate1, rate2, rate3);
    math_approach_target_with_direction_mode(obj + 0xF8, state + 0x2A8, 0, out[2], rate1, rate2, rate3);
}

/* Record `index` of the level's 256-byte record table. */
#define ROTOR_RECORD(index) ((struct RotorObject *)(D_L11_001B359C + ((index) << 8)))
/* The record the object's state lists at `i`, and the one it links to. */
#define LISTED_RECORD(obj, i) ROTOR_RECORD((obj)->state->records[i])
#define LINKED_RECORD(obj) ROTOR_RECORD((obj)->state->linked)
/* The same records for stores, with the addition ordered as retail orders it there. */
#define STORED_RECORD(index) \
    ((struct RotorObject *)(((index) << 8) + D_L11_001B359C))
#define LISTED_STORE(obj, i) STORED_RECORD((obj)->state->records[i])
#define LINKED_STORE(obj) STORED_RECORD((obj)->state->linked)

/* Updates the positions and orthonormal bases of the ten enabled records. */
void chain_creature_update_segments(void *object)
{
    struct RotorObject *obj = object;
    struct RotorState *state = obj->state;
    int i;

    for (i = 0; i < 10; i++) {
        if (state->disabled[i])
            continue;

        qcopy_nc(LISTED_STORE(obj, i)->pos, state->points[i + 1]);
        FastVecSub(&LISTED_RECORD(obj, i)->basis[0], state->points[i], state->points[i + 1]);
        LISTED_STORE(obj, i)->basis[0].w = 0;
        vec_scale_to_length(&LISTED_RECORD(obj, i)->basis[0], &LISTED_RECORD(obj, i)->basis[0], 1.0f);
        vec_clear_128(&LISTED_RECORD(obj, i)->basis[2]);
        LISTED_STORE(obj, i)->basis[2].z = 1.0f;
        FastVecCross(&LISTED_RECORD(obj, i)->basis[1], &LISTED_RECORD(obj, i)->basis[0],
                      &LISTED_RECORD(obj, i)->basis[2]);
        LISTED_STORE(obj, i)->basis[1].w = 0;
        vec_scale_to_length(&LISTED_RECORD(obj, i)->basis[1], &LISTED_RECORD(obj, i)->basis[1], 1.0f);
        FastVecCross(&LISTED_RECORD(obj, i)->basis[2], &LISTED_RECORD(obj, i)->basis[1],
                      &LISTED_RECORD(obj, i)->basis[0]);
        LISTED_STORE(obj, i)->basis[2].w = 0;
        vec_scale_to_length(&LISTED_RECORD(obj, i)->basis[2], &LISTED_RECORD(obj, i)->basis[2], 1.0f);
        LISTED_STORE(obj, i)->flags |= 0x100;
    }
}

/* Updates the single record selected by the state index at 0x358. */
void chain_creature_update_linked(void *object)
{
    struct RotorObject *obj = object;
    struct RotorState *state = obj->state;

    qcopy_nc(LINKED_STORE(obj)->pos, state->points[11]);
    FastVecSub(&LINKED_RECORD(obj)->basis[0], state->points[10], state->points[11]);
    LINKED_STORE(obj)->basis[0].w = 0;
    vec_scale_to_length(&LINKED_RECORD(obj)->basis[0], &LINKED_RECORD(obj)->basis[0], 1.0f);
    vec_clear_128(&LINKED_RECORD(obj)->basis[2]);
    LINKED_STORE(obj)->basis[2].z = 1.0f;
    FastVecCross(&LINKED_RECORD(obj)->basis[1], &LINKED_RECORD(obj)->basis[0],
                  &LINKED_RECORD(obj)->basis[2]);
    LINKED_STORE(obj)->basis[1].w = 0;
    vec_scale_to_length(&LINKED_RECORD(obj)->basis[1], &LINKED_RECORD(obj)->basis[1], 1.0f);
    FastVecCross(&LINKED_RECORD(obj)->basis[2], &LINKED_RECORD(obj)->basis[1],
                  &LINKED_RECORD(obj)->basis[0]);
    LINKED_STORE(obj)->basis[2].w = 0;
    vec_scale_to_length(&LINKED_RECORD(obj)->basis[2], &LINKED_RECORD(obj)->basis[2], 1.0f);
    LINKED_STORE(obj)->flags |= 0x100;
}

/* func_L11_00438880 lives in L11_00438880-g-g8.c. */

/* Clears the two 16-bit flags at 0x374/0x376 of the object held at 0x68. */
void chain_creature_reset_projectile_seq(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    *(short *)(vars + 0x374) = 0;
    *(short *)(vars + 0x376) = 0;
}

extern int FastDecTimer(short *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void moby_transform_joint_point(void *, int, void *);
extern char *moby_find_active_in_group(int);
extern void joba_shot_init(char *, void *, int, int, void *, void *, int, float, float);
extern void vec_random_direction(float *, float, float);

/* Emits a projectile from the next enabled record, with a fifteen-frame delay. */
void chain_creature_fire_projectile(struct RotorObject *obj)
{
    float pos[4];
    float matrix[4][4];
    float offset[4];
    float velocity[4];
    float jitter[4];
    float toTarget[4];
    struct RotorState *state = obj->state;
    char *projectile;

    if (state->projectileIndex == -1)
        return;

    while (state->disabled[state->projectileIndex])
        ++state->projectileIndex;
    if (state->projectileIndex >= 10) {
        state->projectileIndex = -1;
        return;
    }
    if (!FastDecTimer(&state->projectileDelay))
        return;

    moby_transform_joint_to_world(LISTED_RECORD(obj, state->projectileIndex), 0, pos);
    moby_transform_joint_point(LISTED_RECORD(obj, state->projectileIndex), 0, matrix);
    vec_scale_to_length(offset, matrix[2], -0.3f);
    FastVecAdd(pos, pos, offset);

    vec_random_direction(jitter, 0.0166666675f, 0.0500000045f);
    jitter[2] = -0.0833333358f;
    qcopy_nc(velocity, jitter);
    FastVecSub(toTarget, state->aim, pos);
    vec_scale_to_length(toTarget, toTarget, 0.333333343f);
    FastVecAdd(velocity, velocity, toTarget);

    projectile = moby_find_active_in_group(state->projectileClass);
    if (projectile)
        joba_shot_init(projectile, LISTED_RECORD(obj, state->projectileIndex), obj->fB8,
                          state->f60, pos, velocity, 120, 0.00277777785f, state->f35);
    ++state->projectileIndex;
    state->projectileDelay = 15;
}

/* Chooses the state-dependent path, then finds its nearest point. */
void chain_creature_choose_path(struct RotorObject *obj)
{
    struct RotorState *state = obj->state;
    struct RotorPath *path;
    float best;
    float d;
    int pick;
    int i;
    int toggled;

    toggled = state->toggle ^ 1;
    state->toggle = toggled;
    switch (obj->mode) {
    case 2:
        state->path = D_L11_001FF580[state->pathIndex];
        break;
    case 3:
        if (toggled != 0)
            path = D_L11_001FF580[state->choices[0][math_random_int_below(4)]];
        else
            path = D_L11_001FF580[state->choices[1][math_random_int_below(4)]];
        state->path = path;
        break;
    case 4:
        if (toggled != 0)
            path = D_L11_001FF580[state->choices[2][math_random_int_below(4)]];
        else
            path = D_L11_001FF580[state->choices[3][math_random_int_below(4)]];
        state->path = path;
        break;
    }
    pick = 0;
    best = vec_distance_xy(obj->pos, state->path->points[0]);
    for (i = 0; i < state->path->count - 1; i++) {
        d = vec_distance_xy(obj->pos, state->path->points[i]);
        if (d < best) {
            best = d;
            pick = i;
        }
    }
    state->pathPoint = pick;
}

/* Follows the current path, steers toward its next point and releases the sound at the end. */
int chain_creature_follow_path(char *object)
{
    char *state = *(char **)(object + 0x68);
    float target[4], direction[4], aim[4], old[4];
    float speed, duration;

    if (!*(int *)(state + 0x324)) {
        if (*(int *)(state + 0x38C) != -1) {
            char *entry = g_sound_state + *(int *)(state + 0x38C) * 0x70;
            if (*(char **)(entry + 0x88) == object && *(unsigned char *)(entry + 0x74))
                func_3739C0(*(int *)(state + 0x38C));
        }
        *(int *)(state + 0x38C) = -1;
        return 1;
    }
    {
        char *entry = g_sound_state + *(int *)(state + 0x38C) * 0x70;
        if (*(char **)(entry + 0x88) != object || !*(unsigned char *)(entry + 0x74))
            *(int *)(state + 0x38C) = PlayMobySound(0, 4, object);
    }
    qcopy(target, *(char **)(state + 0x324) + *(short *)(state + 0x370) * 16 + 16);
    speed = IntToFloat(*(short *)(state + 0x378));
    duration = IntToFloat(8);
    speed = math_lerp_float(15.0f, 20.0f, (speed - 2.0f) / duration);
    ApproachValue((float *)(state + 0x32C), speed * (1.0f / 60.0f), 1.0f / 180.0f);
    FastVecSub(direction, target, (float *)(object + 0x10));
    vec_scale_to_length((char *)direction, (char *)direction, *(float *)(state + 0x32C));
    FastVecAdd(object + 0x10, object + 0x10, (char *)direction);
    FastVecSub(old, (float *)(state + 0x50), (float *)(object + 0x10));
    vec_scale_to_length((char *)old, (char *)old, 1.0f);
    vec_scale_to_length((char *)direction, (char *)direction, 1.0f);
    if (FastVecDot(direction, old) > 0.707f) {
        qcopy(aim, old);
        chain_creature_turn_to_face(object, (char *)aim, 0.006981317885220051f,
                         0.006981317885220051f, 0.41887909173965454f);
    } else {
        qcopy(aim, direction);
        chain_creature_turn_to_face(object, (char *)aim, 0.006981317885220051f,
                         0.006981317885220051f, 0.41887909173965454f);
    }
    if (fast_vec_dist(object + 0x10, target) < 4.0f)
        (*(short *)(state + 0x370))++;
    if (*(short *)(state + 0x370) < **(int **)(state + 0x324) - 1)
        return 0;
    *(int *)(state + 0x324) = 0;
    if (*(int *)(state + 0x38C) != -1) {
        char *entry = g_sound_state + *(int *)(state + 0x38C) * 0x70;
        if (*(char **)(entry + 0x88) == object && *(unsigned char *)(entry + 0x74))
            func_3739C0(*(int *)(state + 0x38C));
    }
    *(int *)(state + 0x38C) = -1;
    return 1;
}

/* func_L11_004393D8 is defined in L11_00432628-g8.c (it reaches D_L11_001B12C4
   through $gp). */

/* func_L11_004395C8: attempt kept in drafts (112 bytes, expected 116). */
/* func_L11_004395C8 is defined in L11_00432628-g8.c (this unit has no $gp access for it). */

/* func_L11_00439640 is defined in L11_00432628-burst-g8.c. */

/* func_L11_00439950 is defined in L11_00432628-reset-g64.c. */

extern int func_373978(char *obj, int a);

extern void func_3739C0(int a);

extern struct RotorPath *D_L11_001FF580[];
extern char g_sound_state[];

#define REC_L11_359C(o, t) ((*(int *)(*(char **)((o) + 0x68) + 0x358) << 8) + (int)(t))

/* Releases the object's measured slot and clears the six flags of its record. */
void chain_creature_clear_sound_flags(char *obj)
{
    char *state;
    char *records;

    moby_set_state(obj, 1, 0);
    state = *(char **)(obj + 0x68);
    *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) & 0xEFFF) | 0x47;
    *(unsigned char *)(obj + 0x31) = 0;
    *(int *)(obj + 0x98) = 0;
    if (func_373978(obj, *(int *)(state + 0x38C)) != 0) {
        if (*(int *)(state + 0x38C) != -1) {
            char *entry = g_sound_state + *(int *)(state + 0x38C) * 0x70;

            if (*(char **)(entry + 0x88) == obj && *(unsigned char *)(entry + 0x74) != 0)
                func_3739C0(*(int *)(state + 0x38C));
        }
        *(int *)(state + 0x38C) = -1;
    }
    records = (char *)g_moby_l11_table;
    *(unsigned short *)(REC_L11_359C(obj, records) + 0x34) |= 0x2;
    *(unsigned short *)(REC_L11_359C(obj, records) + 0x34) |= 0x4;
    *(unsigned short *)(REC_L11_359C(obj, records) + 0x34) |= 0x40;
    *(unsigned short *)(REC_L11_359C(obj, records) + 0x34) &= 0xEFFF;
    *(unsigned short *)(REC_L11_359C(obj, records) + 0x34) |= 0x1;
    *(unsigned char *)(REC_L11_359C(obj, records) + 0x31) = 0;
    *(int *)(REC_L11_359C(obj, (char *)g_moby_l11_table) + 0x98) = 0;
}


/* Picks the measured 3/4 code from the counter at 0x364 of the object at 0x68. */
/* Returns the next movement state: 3 when the object has a parent holding it, otherwise 4. */
int chain_creature_pick_move_state(char *moby)
{
        if (*(int *)(*(char **)(moby + 0x68) + 0x364))
        return 3;
    return 4;
}

/* func_L11_00439DD0 is defined in L11_00439DD0-g8.c. */

extern int FloatToInt(float);
extern void drone_kill_with_effects(char *);
extern int moby_apply_damage_to_object(char *, char *, int);
extern int weapon_select_aim_target(char *, int, int, int, float, float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(char *);
extern char D_L11_001BA8C0[];

/* Sets up the flying drone on its first frame, then each frame handles hits and checks whether the hero is very close. */
void drone_setup_and_hits(char *object) {
    char *state = *(char **)(object + 0x68);

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(state + 0x48) = FloatToInt(15.0f);
        *(unsigned char *)(state + 0x4A) = FloatToInt(12.0f);
        *(float *)(state + 0x1A0) = 1.0f;
        *(unsigned char *)(state + 0x180) = 6;
        *(int *)(state + 0x1B8) = 2;
        *(float *)(state + 0x1AC) = 0.15f;
        *(float *)(state + 0x80) = 1.0f;
        *(float *)(state + 0x84) = 0.4f;
        *(float *)(state + 0x88) = 0.3f;
        *(float *)(state + 0x8C) = 0.3f;
        *(float *)(state + 0x90) = 1.5707964897155762f;
        *(float *)(state + 0xB0) = 0.523598849773407f;
        *(float *)(state + 0xB4) = 2.0f;
        *(float *)(state + 0xAC) = 0.0027777778450399637f;
        *(int *)(state + 0x1A4) = 0;
        moby_set_controller_speed_limits(object, 0.2777777910232544f, 0.3333333432674408f,
                      0.0017453294713050127f, 0.05235988646745682f);
        if (*(short *)(state + 0x24) == 0) {
            *(short *)(state + 0x24) = 10;
            *(float *)(state + 0x20) = 10;
        }
        if (*(unsigned char *)(object + 0x43) != 1)
            anim_start_blended(object, 1, 0, 0);
        moby_set_state(object, 1, -1);
        drone_kill_with_effects(object);
    }
    if (*(unsigned char *)(object + 0x20) >= 4)
        moby_apply_damage_to_object(object, state + 0x170, 0);
    if (*(unsigned char *)(object + 0x20) >= 3 &&
        *(unsigned char *)(state + 0x2E) == 2)
        drone_kill_with_effects(object);
    *(int *)(state + 0x2D8) = weapon_select_aim_target(object, *(int *)(state + 0x2E8),
                                         0, 0, 255.0f, 255.0f);
    if (*(unsigned char *)(object + 0x31) != 0) {
        if (fast_vec_dist(object + 0x10, D_L11_001BA8C0) < 48.0f) {
            moby_update_ground_check(object);
            *(unsigned char *)(object + 0x6F) = 45;
        }
    }
}

extern void func_32E480(char *p, char *q, int a, float b, float c, float d, int e, int f, int g);

/* Bumps the 16-bit counter at 0x96 while it is under the measured ceiling, then re-arms. */
void drone_count_frames_draw_glow(char *moby)
{
    unsigned short count = *(unsigned short *)(moby + 0x96);

    if (count <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) = count + 1;
    func_32E480(moby, moby + 0x10, 0x4000000, 1.2f, 1.0f, 1.0f, 0, 1, 0);
}

/* func_L11_0043A680 is defined in L11_0043A680-g8.c. */

/* True when the byte at 0x20 is above the measured small-id range. */
int drone_is_state_at_least_four(char *moby)
{
    return *(unsigned char *)(moby + 0x20) >= 4;
}


extern void vec_random_direction(float *out, float a, float b);
extern float math_random_float_range(float a, float b);
extern void part_spawn_masked_debris(char *self, int mask, float *arg2, unsigned char arg3,
                           float f0, float f1, float f2, float f3);
extern int PlayMobySound(int index, int a1, char *a2);
extern void moby_detach_manipulator(char *list, char *node);

/* Spawns the object's jitter effect while its flag byte is set, then retires the state. */
void drone_kill_with_effects(char *obj)
{
    char *state;
    unsigned short flags;
    float v[3];

    if (*(unsigned char *)(obj + 0x20) == 0)
        return;

    if (*(unsigned char *)(obj + 0x31) != 0) {
        float s = 1.0f / 6.0f;

        vec_random_direction(v, s, 1.0f / 3.0f);
        v[2] = math_random_float_range(1.0f / 12.0f, s);
        part_spawn_masked_debris(obj, 3, v, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(1, 0, obj);
        SpawnExplosion(obj + 0x10, 1, 0x19, 0xA, 0xA, 5, 0, 1, 1.0f, 20.0f, 0, 0, 0, 0);
        snd_play_from_class_bank(0, 0, obj, 0xDF7);
    }

    moby_set_state(obj, 1, 0);
    anim_start_blended(obj, 0, 0, 3);
    func_002A05A8(obj);

    state = *(char **)(obj + 0x68);
    flags = *(unsigned short *)(obj + 0x34);
    *(unsigned char *)(obj + 0x31) = 0;
    *(int *)(obj + 0x98) = 0;
    *(unsigned short *)(obj + 0x34) = (flags & 0xEFFF) | 0x47;

    if (*(unsigned char *)(state + 0x221))
        moby_detach_manipulator(obj, state + 0x220);
    if (*(unsigned char *)(state + 0x261))
        moby_detach_manipulator(obj, state + 0x260);
}

extern float mat_fast_helper_a(float, float);
extern float math_fast_sin_or_cos_b(float);

/* Places out at src plus dist along the heading from src to out's old position, the heading
   and the distance each jittered at random; z comes from src. */
void PlacePointWithPolarJitterFlat(float *out, TI128 *src, float distance, float angle_jitter, float dist_jitter) {
    TI128 vec = *src;
    TI128 *p = &vec;
    float *v = (float *)&vec;
    float angle;

    angle = mat_fast_helper_a(out[0] - v[0], out[1] - v[1]);
    angle_jitter *= 0.017453294f;
    angle += math_random_float_range(-angle_jitter, angle_jitter);
    distance += math_random_float_range(-dist_jitter, dist_jitter);
    qcopy(out, p);
    out[0] += distance * math_fast_sin_or_cos_a(angle);
    out[1] += distance * math_fast_sin_or_cos_b(angle);
    out[2] = v[2];
}

/* Maps the measured selector onto its small index. */
/* func_L11_0043E090 is defined in L11_0043E090.c. */

/* Maps the measured selector onto its large index. */
/* func_L11_0043E108 is defined in L11_0043E108.c. */
