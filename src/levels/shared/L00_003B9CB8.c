#include "common.h"

extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern void euler_rotation_basis(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern float FastVecLength(void *);
extern void mat_build_rotation_toward_vector(void *, void *, void *, int, float);
extern int coll_test_point(void *, int, void *, float);
extern char *D_L00_001BF218;
extern char *g_hero_moby;
extern char D_L00_001BF230[];
typedef struct { float x, y, z; int unused; float position[4]; } EffectLightRecord;
extern EffectLightRecord D_L00_001C6F40[];
extern float FastVecDot(void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern void part_l00_spawn_spark_burst_2(float *, float *, int, int);
extern void PlayMobySound(int, int, void *);
extern void spark_spawn_orbit(char *, char *);


extern float func_802EE7A8_1(float x, float y);

extern float func_802EE2E8_1(char *p, float *v);

extern void func_802EE970_1(float *matrix, float *quat);

extern void func_802EE138_1(float *off, float *v, char *p);

extern void func_802EE3D0_1(float *dst, float *src, float angle);

extern void func_802EAC30_1(char *pkt, float *matrix, int mode);

extern void ref_L00_003C1FC8_00(char *p);
extern long long func_002E67A0_2(int id);
extern float func_0031A888_1(void);
extern void func_002EE178_1(char *dst, char *src, float scale);
/* The vector the aim helpers read, at 0x001B8C80. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L00AimVector;

extern L00AimVector D_L00_001B8C80;



/* The 128-bit unit four of these bodies copy whole. */
typedef int Rac2TI128 __attribute__((mode(TI)));

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_86f665335d9cb905_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_86f665335d9cb905_AnalysisOwner;

extern void target_lock_on_update(Rac2Native_86f665335d9cb905_AnalysisOwner *owner, void *context);

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

extern char D_L00_001BF240[];

extern void func_00282F20_2(void *out, void *in, float scale);

extern void func_00282CC0_6(void *out, void *in1, void *in2);

extern int CollLine(void *a, void *b, int mode, void *self, int flag);

extern void func_00282D30_6(void *out, void *in, float scale);

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;

extern void func_002FDBD8_2(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

extern void func_002A77E0_1(int a);

extern float func_002A7878_2(float a, float b);

extern unsigned int func_002A7820_1(int a, int b);

extern void vec_random_direction(char *p, float a, float b);

extern char *SpawnSpinningSparkParticle(float fa, float fb, float fc, float fd, char *p, int z,
                     char *local, unsigned int v, int one);

extern char D_00189E20_13[];

/* Pass the owner and its pointer at offset 0x68 to the explicitly bound helper; original game role is unknown. */
/* Updates the Hypnomatic moby by passing it and its private data to a helper. */
void hypnomatic_update(Rac2Native_86f665335d9cb905_AnalysisOwner *owner)
{
    target_lock_on_update(owner, owner->context_68);
}

extern void flyer_alert_group(char *);

/* Calls the measured callee with the object it was given. OpenRAC: the decompilation's
   (void) left a0 unset; the console's a0 still held the moby, the host's held anything. */
/* Updates the Heavy Lancer moby by running one helper on it. */
void heavy_lancer_update(char *moby)
{
    flyer_alert_group(moby);
}

/* Implemented in L00_003B9CB8-state-g8.c. */

/* Integrates motion, reflects a collision, updates the light and emits trail slots. */
char *spark_move_projectile(char *moby)
{
    float saved[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float projection[4] __attribute__((aligned(16)));
    float remainder[4] __attribute__((aligned(16)));
    char *ctx = *(char **)(moby + 0x68);
    char *hit = 0;
    char *hitObject;
    EffectLightRecord *light;
    int light_index;
    float dot;
    *(float *)(moby + 0xF0) = FastAddRotations(*(float *)(moby + 0xF0), 0.0523598865f);
    *(float *)(moby + 0xF4) = fast_subtract_rotations(*(float *)(moby + 0xF4), 0.0130899716f);
    *(int *)(moby + 0xFC) = 0;
    euler_rotation_basis(moby + 0xC0, moby + 0xF0);
    qcopy(saved, moby + 0x10);
    FastVecAdd(moby + 0x10, ctx, moby + 0x10);
    part_steer_effect_direction(*(int *)(ctx + 0x50), ctx, 0);
    vec_transform_or_copy(moby + 0x10, moby + 0x10);
    shop_trigger_current_state_effect(ctx, ctx);
    if (FastVecLength(ctx) != 0.0f && FastVecLength(ctx + 0x20) != 0.0f)
        mat_build_rotation_toward_vector(ctx, ctx, ctx + 0x20, 0, 0.075f);
    if (coll_test_point(moby + 0x10, 0, moby, *(float *)(ctx + 0x4C))) {
        hitObject = D_L00_001BF218;
        if (hitObject && hitObject != g_hero_moby && *(short *)(hitObject + 0xAA) != 0x5CA /* Plasma Storm */)
            hit = (*(unsigned short *)(hitObject + 0x34) & 0x1000) ? hitObject : 0;
        qcopy(moby + 0x10, D_L00_001BF230);
        func_002EE178_1((char *)normal, D_L00_001BF230 + 0x10, 0.0009765625f);
        func_802EE3D0_1(normal, normal, 1.0f);
        vec_fast_normalize(ctx, ctx, normal);
        dot = FastVecDot(ctx, normal);
        func_002EE178_1((char *)projection, (char *)normal, dot);
        func_802EE138_1(remainder, (float *)ctx, (char *)projection);
        func_002EE178_1(ctx, (char *)projection, 0.85f);
        FastVecAdd(ctx, remainder, ctx);
        func_002EE178_1(ctx + 0x20, ctx + 0x20, 0.95f);
        part_l00_spawn_spark_burst_2(D_L00_001BF230 - 0x10, normal, 6, 0x72FF);
        part_l00_spawn_spark_burst_2(D_L00_001BF230 - 0x10, normal, 6, 0xFF0000);
        PlayMobySound(1, 0, moby);
    }
    light_index = *(int *)(ctx + 0x5C);
    if (light_index != -1) {
        light = D_L00_001C6F40 + light_index;
        qcopy(light->position, moby + 0x10);
        light->position[3] = 4.0f;
        light->x = 0.25f;
        light->y = 0.14f;
        light->z = 1.0f;
        light->unused = 0;
        dot = func_002A7878_2(-0.1f, 0.1f);
        light->x += dot;
        light->y += dot;
        light->z += dot;
    }
    if (*(float *)(moby + 0x10) < 2.0f || *(float *)(moby + 0x10) > 1021.0f ||
        *(float *)(moby + 0x14) < 2.0f || *(float *)(moby + 0x14) > 1021.0f ||
        *(float *)(moby + 0x18) < 2.0f || *(float *)(moby + 0x18) > 1021.0f) {
        qcopy(moby + 0x10, saved);
        moby[0x20] = 3;
    }
    if (*(int *)(ctx + 0x58) < 8)
        spark_spawn_orbit(moby, (char *)func_002A7820_1(8, 20));
    return hit;
}


extern void VU1_addGSregister(unsigned int reg, unsigned long value);

extern float math_random_angle(void);

extern void gfx_draw_billboard_quad(char *a, int b, unsigned int c, int d, float e, float f,
                          float g);

extern void effect_draw_slot_sprites(char *a0);

extern void spark_process_owned_records(char *a0);

/* Opens the block, lays seven oriented sprites over it from two helper draws and the shared
   colour word, then runs the two slot-table passes and closes the block. */
void spark_draw_projectile(char *moby)
{
    char *ctx;

    ctx = *(char **)(moby + 0x68);
    VU1_addGSregister(0x47, 0x00053001);

    gfx_draw_billboard_quad(moby + 0x10, 0x2C,
                  (func_002A7820_1(0x80, 0xC8) << 24) | 0x72FF, 1,
                  func_002A7878_2(0.38500002f, 0.415f) * *(float *)(ctx + 0x4C),
                  -0.01f, math_random_angle());
    gfx_draw_billboard_quad(moby + 0x10, 0x2D,
                  (func_002A7820_1(4, 0x28) << 24) | 0x00DDB973, 1,
                  *(float *)(ctx + 0x4C) * 1.225f, 0.0f, math_random_angle());
    gfx_draw_billboard_quad(moby + 0x10, 0x29,
                  (func_002A7820_1(4, 0x28) << 24) | 0x00DDB973, 1,
                  *(float *)(ctx + 0x4C) * 0.6f, 0.0f, math_random_angle());
    gfx_draw_billboard_quad(moby + 0x10, 0x2A,
                  (func_002A7820_1(4, 0x2D) << 24) | 0x00DDB973, 1,
                  func_002A7878_2(0.975f, 1.025f) * *(float *)(ctx + 0x4C),
                  0.0f, math_random_angle());
    gfx_draw_billboard_quad(moby + 0x10, 0x2A,
                  (func_002A7820_1(4, 0x2D) << 24) | 0x00DDB973, 1,
                  func_002A7878_2(0.975f, 1.025f) * *(float *)(ctx + 0x4C),
                  0.0f, math_random_angle());
    effect_draw_slot_sprites(moby);
    spark_process_owned_records(moby);
    VU1_addGSregister(0x47, 0x0005360B);
}

extern int D_L00_0023DDA0[];
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void vec_clear_128(void *);
extern char *moby_get_private_value_0(char *);
extern void moby_forward_position_call(char *, void *, int);
extern void FastVecScale(void *, void *, float);

/* Claims the first free one of the thirty 0xA0-byte records at D_L00_0023DDA0 for self:
   counts it in self's data, copies self's position, draws three triples from the ranges
   below, stores count, target and the timer, and starts it at target (offset through
   func_L00_003252A8 when func_002AB1F0 finds target's info). */
void spark_spawn_orbiting_record(char *self, char *target, int count)
{
    char *pool = (char *)D_L00_0023DDA0;
    char *position = self + 0x10;
    char *target_position = target + 0x10;
    char *data = *(char **)(self + 0x68);
    char *p;
    char *info;
    float v[4];
    int i;
    for (i = 0; i < 30; i++) {
        p = pool + i * 0xA0;
        if (*(int *)(p + 0x8C) == 0) {
            float max_angle, min_angle;
            float max_scale, min_scale;
            float max_dist, min_dist;
            *(char **)(p + 0x8C) = self;
            (*(int *)(data + 0x54))++;
            qcopy(p + 0x20, position);
            min_angle = -3.14159274101257324219f;
            max_angle = 3.14159274101257324219f;
            min_scale = 0.001f;
            max_scale = 0.005f;
            min_dist = 3.25f;
            max_dist = 4.75f;
            *(float *)(p + 64) = math_random_float_range(min_angle, max_angle);
            *(float *)(p + 68) = math_random_float_range(min_angle, max_angle);
            *(float *)(p + 72) = math_random_float_range(min_angle, max_angle);
            *(float *)(p + 100) = math_random_float_range(min_angle, max_angle);
            *(float *)(p + 104) = math_random_float_range(min_angle, max_angle);
            *(float *)(p + 108) = math_random_float_range(min_angle, max_angle);
            *(float *)(p + 76) = math_random_signed_float_range(min_scale, max_scale);
            *(float *)(p + 80) = math_random_signed_float_range(min_scale, max_scale);
            *(float *)(p + 84) = math_random_signed_float_range(min_scale, max_scale);
            *(float *)(p + 112) = math_random_signed_float_range(min_scale, max_scale);
            *(float *)(p + 116) = math_random_signed_float_range(min_scale, max_scale);
            *(float *)(p + 120) = math_random_signed_float_range(min_scale, max_scale);
            *(float *)(p + 88) = math_random_float_range(min_dist, max_dist);
            *(float *)(p + 92) = math_random_float_range(min_dist, max_dist);
            *(float *)(p + 96) = math_random_float_range(min_dist, max_dist);
            *(float *)(p + 124) = math_random_float_range(min_dist, max_dist);
            *(float *)(p + 128) = math_random_float_range(min_dist, max_dist);
            *(float *)(p + 132) = math_random_float_range(min_dist, max_dist);
            vec_clear_128(p);
            vec_clear_128(p + 0x10);
            *(int *)(p + 0x94) = count;
            *(int *)(p + 0x98) = count;
            *(char **)(p + 0x90) = target;
            *(int *)(p + 0x9C) = 0;
            *(int *)(p + 0x88) = 20;
            info = moby_get_private_value_0(target);
            if (info) {
                moby_forward_position_call(target, v, 1);
                FastVecScale(v, v, *(float *)(info + 0x10));
                FastVecAdd(p + 0x30, v, target + 0x10);
            } else {
                qcopy(p + 0x30, target_position);
            }
            break;
        }
    }
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
/* Sets a sprite record to its starting values: unit-sized corners and a cleared state. */
void sprite_reset_record(char *record)
{
    *(long long *)(record + 112) = 0LL;
    *(int *)(record + 80) = 0;
    *(int *)(record + 84) = 0;
    *(float *)(record + 88) = 1.0f;
    *(int *)(record + 92) = 0;
    *(int *)(record + 96) = 0;
    *(float *)(record + 100) = 1.0f;
    *(float *)(record + 104) = 1.0f;
    *(float *)(record + 108) = 1.0f;
    *(float *)(record + 8) = -1.0f;
    *(float *)(record + 24) = 1.0f;
    *(float *)(record + 40) = -1.0f;
    *(float *)(record + 56) = 1.0f;
    *(float *)(record + 4) = -1.0f;
    *(float *)(record + 36) = 1.0f;
    *(float *)(record + 52) = 1.0f;
    *(int *)(record + 0) = 0;
    *(int *)(record + 16) = 0;
    *(int *)(record + 32) = 0;
    *(int *)(record + 48) = 0;
    *(float *)(record + 12) = 1.0f;
    *(float *)(record + 28) = 1.0f;
    *(float *)(record + 44) = 1.0f;
    *(long long *)(record + 128) = 280993940374112LL;
    *(float *)(record + 20) = -1.0f;
    *(float *)(record + 60) = 1.0f;
}

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void vec_l00_derive_element_from_neighbours_2(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

/* Implemented in L00_003B9CB8-ribbons.c. */

/* Measured partial layout of one 0xB0-byte record of the table at D_L00_0023F060. */
typedef struct Rac2Native_003BC998_Slot {
    unsigned char prefix_00[0x50];
    float f_50;
    float f_54;
    float f_58;
    float f_5C;
    float f_60;
    float f_64;
    float f_68;
    float f_6C;
    float f_70;
    float f_74;
    float f_78;
    float f_7C;
    float f_80;
    float f_84;
    float f_88;
    float f_8C;
    float f_90;
    float f_94;
    void *w_98;
    void *w_9C;
    void *owner_A0;
    unsigned char tail_A4[0xC];
} Rac2Native_003BC998_Slot;

extern Rac2Native_003BC998_Slot D_L00_0023F060[];

extern float func_002A78D8_1(float low, float high);

extern void func_002AF000_1(float *out, float a, float b, float c);

extern void func_00282C88_1(void *p);

/* Claims the first free record of the sixteen 0xB0-byte records at D_L00_0023F060, keeps the
   owner's pointer in it and fills the drawn values. The base and the output pointer are kept
   in their own variables, and the two owner words are stored in the order 0x9C, 0x98, so that
   cc1 keeps the table base and the output pointer in registers and fills the delay slots the
   way retail does. */
void spark_spawn_orbit(char *moby, char *linkedValue)
{
    Rac2Native_003BC998_Slot *base = D_L00_0023F060;
    Rac2Native_003BC998_Slot *slot;
    float *out;
    char *ctx;
    int i;
    float r1;
    float r2;

    ctx = *(char **)(moby + 0x68);
    for (i = 0; i < 16; i++) {
        slot = base + i;
        if (slot->owner_A0 != 0)
            continue;
        slot->owner_A0 = moby;
        out = (float *)((char *)slot + 0x40);
        (*(int *)(ctx + 0x58))++;
        slot->f_50 = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_54 = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_58 = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_74 = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_78 = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_7C = func_002A7878_2(-3.14159274f, 3.14159274f);
        slot->f_5C = func_002A78D8_1(0.1f, 0.5f);
        slot->f_60 = func_002A78D8_1(0.1f, 0.5f);
        slot->f_64 = func_002A78D8_1(0.1f, 0.5f);
        slot->f_80 = func_002A78D8_1(0.1f, 0.5f);
        slot->f_84 = func_002A78D8_1(0.1f, 0.5f);
        slot->f_88 = func_002A78D8_1(0.1f, 0.5f);
        slot->f_68 = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        slot->f_6C = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        slot->f_70 = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        slot->f_8C = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        slot->f_90 = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        slot->f_94 = func_002A7878_2(3.25f, 4.75f) * 0.25f;
        func_00282C88_1(slot);
        func_00282C88_1((char *)slot + 0x10);
        slot->w_9C = linkedValue;
        slot->w_98 = linkedValue;
        r1 = math_random_angle();
        r2 = math_random_angle();
        func_002AF000_1(out, *(float *)(ctx + 0x4C), r1, r2);
        break;
    }
}


extern void lightning_build_and_draw_ribbon(char *a0, char *a1);

extern char D_0023F060[];

/* Near miss: nonmatching/levels/func_L00_003BCDC0.c - every instruction present but the
   loop test is `sltu` here against retail's `slt`, and the base is derived from the end
   pointer instead of being materialised on its own. */

extern int math_random_int_below(int);
extern int func_001163B0(void);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int FloatToInt(float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);

/* Emits count pairs of sparks at position, moving along direction turned by a random rotation;
   position is jittered a little before each pair. Both arms of the random-bit test are the same
   code: retail keeps the test, so it stays. */
void part_l00_spawn_spark_burst_2(float *position, float *direction, int count, int color)
{
    float velocity[4];
    float previous[4];
    float angles[4];
    char matrix[48];
    float *saved;
    float scale;
    int spin;
    char *particle;
    int i;

    for (i = 0; i < count; i++) {
        scale = math_random_float_range(1.75f, 2.0f);
        spin = math_random_int_below(2);
        if (!spin)
            spin--;
        angles[3] = 0;
        angles[1] = math_random_float_range(-1.57079637f, 1.57079637f);
        angles[0] = math_random_float_range(-1.57079637f, 1.57079637f);
        angles[2] = math_random_float_range(-1.57079637f, 1.57079637f);
        euler_rotation_basis(matrix, angles);
        matrix_mul_vec3(velocity, direction, matrix);

        saved = previous;
        vec_scale_to_length(velocity, velocity, 0.05f);
        velocity[2] += 0.05f;
        qcopy(saved, position);
        position[0] += math_random_signed_float_range(0.0f, 0.15f);
        position[1] += math_random_signed_float_range(0.0f, 0.15f);
        position[2] += math_random_signed_float_range(0.0f, 0.15f);

        if (func_001163B0() & 1) {
            particle = part_spawn_ground_effect(position, 60, scale * 0.1f, scale, color | 0x4F000000, 0,
                                     spin, velocity, 1, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 112;
            particle = part_spawn_ground_effect(position, 60, scale * 0.07f, scale * 0.7f, 0x7FFFFFFF, 1,
                                     -spin, velocity, 1, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 112;
        } else {
            particle = part_spawn_ground_effect(position, 60, scale * 0.1f, scale, color | 0x4F000000, 0,
                                     spin, velocity, 1, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 112;
            particle = part_spawn_ground_effect(position, 60, scale * 0.07f, scale * 0.7f, 0x7FFFFFFF, 1,
                                     -spin, velocity, 1, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 112;
        }
    }
}

/* func_L00_003BD7E0 is in L00_003B9CB8-update.c. */

/* Normalises and combines two temporary vectors from a state block, dispatches on the combined result and conditionally scales the output vector. */
void coll_compute_surface_direction(char *moby, char *outVector, int keepSign)
{
    float a[4];
    float b[4];

    func_00282F20_2(a, moby + 224, 0.1f);
    func_00282F20_2(b, moby + 224, -3.0f);
    func_00282CC0_6(a, a, moby + 16);
    func_00282CC0_6(b, b, moby + 16);

    if (CollLine(a, b, 2, moby, 0))
        func_00282F20_2(outVector, D_L00_001BF240, 1.0f);
    else
        func_00282F20_2(outVector, moby + 224, -1.0f);

    if (keepSign == 0)
        func_00282D30_6(outVector, outVector, -1.0f);
}

/* Read the word at offset 0x 18 through the pointer stored at owner offset 0x 68. */
unsigned int moby_get_vars_state_word(unsigned int moby)
{
    unsigned int vars;
    unsigned int value;

    vars = *(unsigned int *)(moby + 0x68);
    value = *(unsigned int *)(vars + 0x18);
    return value;
}

extern float vec_get_heading_angle(char *a0, float *src, char *third);

/* The four floats are declared before the two other arguments, which sets the order this caller
   evaluates them in (the registers are the same either way). */
extern float math_approach_target_with_direction_mode(void *out, float f12, float f13, float f14, float f15, char *in, int a2);

extern void euler_rotation_basis(void *out, void *in);

extern void multiply_matrix3x3(char *a0, char *a1, void *a2);

extern float math_fabs(float f);

/* Copies the caller's 16-byte block into a stack scratch area, runs the three-argument starter on
   it, then fills the scratch area's upper half from the state block's 0xB4 float and the pair
   helper before folding the starter's result against the state's own reading of that float. One
   `char scratch[0x50]` gives retail's frame. The 16-byte clear is retail's `sq $zero,0($sp)`:
   with the scheduling barrier of zero_ti_store_barrier.py it takes retail's place, and so does
   the prologue's save order. */
float moby_aim_at_target(char *moby, char *state, char *startBlock, char *extra)
{
    char scratch[0x50];
    float angle;

    *(Rac2TI128 *)scratch = *(Rac2TI128 *)startBlock;
    angle = vec_get_heading_angle(moby, (float *)scratch, extra);
    *(int *)(scratch + 0x40) = 0;
    math_approach_target_with_direction_mode(scratch + 0x40, angle, *(float *)(state + 0x14), *(float *)(state + 0x18), 3.14159274f, state + 0xB4, 0);
    *(Rac2TI128 *)scratch = 0;
    *(float *)(scratch + 8) = *(float *)(state + 0xB4);
    euler_rotation_basis(scratch + 0x10, scratch);
    multiply_matrix3x3(moby + 0xC0, moby + 0xC0, scratch + 0x10);
    return math_fabs(angle) - math_fabs(*(float *)(state + 0xB4));
}

/* shared native body of family a04928c6 */
/* Sets a bigger sprite record to its starting values: corners twice the size and a cleared state. */
void sprite_reset_large_record(char *record)
{
    *(long long *)(record + 112) = 0LL;
    *(int *)(record + 80) = 0;
    *(int *)(record + 84) = 0;
    *(float *)(record + 88) = 1.0f;
    *(int *)(record + 92) = 0;
    *(int *)(record + 96) = 0;
    *(float *)(record + 100) = 1.0f;
    *(float *)(record + 104) = 1.0f;
    *(float *)(record + 108) = 1.0f;
    *(float *)(record + 8) = -2.0f;
    *(float *)(record + 24) = 2.0f;
    *(float *)(record + 40) = -2.0f;
    *(float *)(record + 56) = 2.0f;
    *(float *)(record + 4) = -2.0f;
    *(float *)(record + 36) = 2.0f;
    *(int *)(record + 0) = 0;
    *(int *)(record + 16) = 0;
    *(int *)(record + 32) = 0;
    *(int *)(record + 48) = 0;
    *(float *)(record + 12) = 1.0f;
    *(float *)(record + 28) = 1.0f;
    *(float *)(record + 44) = 1.0f;
    *(long long *)(record + 128) = 0x0000FF9000000260LL;
    *(float *)(record + 20) = -2.0f;
    *(float *)(record + 52) = 2.0f;
    *(float *)(record + 60) = 1.0f;
}

/* Draws two glowing flat sprites between a point and the camera, one big and one half as big. */
void gfx_l00_draw_facing_glow_sprite(int unused, char *pos, int color, int first, int second, float scale)
{
    char packet[144];
    float matrix[16];
    float quat[4];
    float off[4];
    long long texture;
    float dx, dy;

    ref_L00_003C1FC8_00(packet);
    *(int *)(packet + 80) = 0;
    *(float *)(packet + 92) = 1.0f;
    *(float *)(packet + 96) = 1.0f;
    *(float *)(packet + 104) = 1.0f;
    *(float *)(packet + 108) = 1.0f;
    *(int *)(packet + 84) = 0;
    *(int *)(packet + 88) = 0;
    *(int *)(packet + 100) = 0;
    texture = func_002E67A0_2(11);
    *(long long *)(packet + 112) = 0;
    *(long long *)(packet + 120) = texture;
    *(long long *)(packet + 128) = 0xFF9000000260LL;
    *(long long *)(packet + 136) = 0x8000000048LL;
    dx = D_L00_001B8C80.x_140 - *(float *)pos;
    dy = D_L00_001B8C80.y_144 - *(float *)(pos + 4);
    *(int *)(packet + 76) = color + first;
    *(int *)(packet + 72) = color + first;
    *(int *)(packet + 68) = color + first;
    *(int *)(packet + 64) = color + first;
    quat[3] = 0;
    quat[2] = func_802EE7A8_1(dx, dy);
    quat[1] = -func_802EE7A8_1(func_802EE2E8_1(pos, &D_L00_001B8C80.x_140),
                              D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = func_0031A888_1();
    func_802EE970_1(matrix, quat);
    func_802EE138_1(off, &D_L00_001B8C80.x_140, pos);
    func_802EE3D0_1(off, off, 0.5f);
    matrix[12] = *(float *)(pos) + off[0];
    matrix[13] = *(float *)(pos + 4) + off[1];
    matrix[14] = *(float *)(pos + 8) + off[2];
    matrix[15] = 1.0f;
    func_002EE178_1(packet, packet, scale);
    func_002EE178_1(packet + 16, packet + 16, scale);
    func_002EE178_1(packet + 32, packet + 32, scale);
    func_002EE178_1(packet + 48, packet + 48, scale);
    func_802EAC30_1(packet, matrix, 0);
    *(int *)(packet + 76) = color + second;
    *(int *)(packet + 72) = color + second;
    *(int *)(packet + 68) = color + second;
    *(int *)(packet + 64) = color + second;
    func_002EE178_1(packet, packet, 0.5f);
    func_002EE178_1(packet + 16, packet + 16, 0.5f);
    func_002EE178_1(packet + 32, packet + 32, 0.5f);
    func_002EE178_1(packet + 48, packet + 48, 0.5f);
    func_802EAC30_1(packet, matrix, 0);
}

extern void SpawnTintedEffects(char *a, char *b, float h, int c, int d, char *e, float i,
                               int f, int g, float j, float k);

/* Twenty rounds of four bound helpers on three 16-byte scratch vectors, the first of which
   starts as the second argument's record; each round ends with the eleven-argument emitter. */
void part_spawn_random_spark_rays(char *effect, char *source, float fa, float fb)
{
    char v0[16];
    char v1[16];
    char v2[16];
    char *pv0 = v0;
    int i;

    *(Rac2TI128 *)pv0 = *(Rac2TI128 *)source;
    i = 0x13;
    do {
        vec_random_direction(v1, fa, fa);
        func_00282F20_2(v2, v1, func_002A7878_2(fb * 0.75f, fb * 1.25f));
        func_00282CC0_6(v1, v1, pv0);
        SpawnTintedEffects(effect, v1, 0.0f, 1, 0, v2, 0.0f, 0x50804040, 0, 2.0f, 5.0f);
        i--;
    } while (i >= 0);
}

/* Two-state gate on the record's byte 0x20 (the same body as func_L09_003C8CD8, which
   the level 09 file already carries). In state 0, as long as the live word the sub-object
   opens with is not -1, the record is stamped 0xFF, the shared eight-argument starter is
   run on the sub-object's track block and the record flips to state 1. In state 1 the
   sub-object's first float is scaled by 2*pi/21600 (a per-frame 1/100 s turn rate) and
   folded into the record's own angle before its track block is stepped again. */
extern void func_323448();
extern void func_323958(unsigned char *, unsigned char *);
extern float func_2EF0F8(float, float);

void tracked_state_update(unsigned char *moby) {
    unsigned char *self = moby;
    unsigned char *vars = *(unsigned char **)(self + 0x68);
    switch (self[0x20]) {
    case 0:
        if (*(long long *)vars == -1) {
            break;
        }
        {
            unsigned char stamp = 0xFF;
            *(unsigned char *)(self + 0x30) = stamp;
        }
        func_323448(self, vars + 0x30, 0x64, *(int *)(vars + 4), *(int *)vars, -1, 7, 0);
        vars[0xC5A] = 1;
        self[0x20] = 1;
        break;
    case 1:
        *(float *)(self + 0xF4) = func_2EF0F8(
            *(float *)(self + 0xF4), *(float *)(vars + 8) * 0.000290888245f);
        func_323958(self, vars + 0x30);
        break;
    }
}


/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
/* Calls a helper for this moby only when its active flag is set. */
void moby_apply_active_effect(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_2(1.0f, context, context->vector_10, 0);
    }
}


/* The 0x68 context block starts with two words and a halfword that this body clears. */
/* On the first frame, clears the moby private data and moves it to state 1. */
void moby_init_vars_once(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(int *)(vars + 0x8) = 0;
        *(short *)(vars + 0xE) = 0;
        *(int *)(vars + 0x0) = 0;
        *(unsigned char *)(moby + 0x20) = 1;
    }
}

/* Runs 20 local iterations; the first two calls each pass integer 2 to the same bound target; on each non-null final result, stores a short at +10, an int at +36, and bytes at +42 and +43. */
/* Spawns twenty small sparks at a position, each with a random speed and grey shade. */
void part_l00_spawn_spark_shower(char *unused, char *position)
{
    char local[16];
    float speed;
    int i;
    unsigned int shade;
    unsigned int shadeHigh;
    unsigned int colorBits;
    char *particle;

    i = 19;
    do {
        func_002A77E0_1(2);
        i = i - 1;
        func_002A77E0_1(2);
        speed = func_002A7878_2(70000.0f, 150000.0f);
        shade = func_002A7820_1(10, 127);
        shadeHigh = (shade << 8) | 0x7f000000U;
        colorBits = (shade << 16) | shadeHigh;
        shade = colorBits | shade;
        vec_random_direction(local, 1.6666668670950457453728e-05f,
                6.6666672937572002410889e-03f);
        particle = SpawnSpinningSparkParticle(0.3f, 1.0f, 1.01f, speed, position, 0, local, shade, 1);
        if (particle != 0) {
            char *extra = particle + 32;

            *(short *)(particle + 10) = 120;
            *(int *)(extra + 4) = 2;
            *(char *)(extra + 10) = 127;
            *(char *)(extra + 11) = *(unsigned char *)(particle + 10);
        }
    } while (i >= 0);
}

/* func_L00_003C48D0 is defined in L00_003C48D0-g8.c. */


/* func_L00_003C5310 is defined in L00_003C5310.c. */

/* func_L00_003C58E8 is in L00_003C58E8-qcopy.c. */

/* Implemented in L00_003C58E8.c. */

/* one float gate followed by five integer gates; every failing gate */
/* Returns 1 if the player can still use the weapon right now, otherwise 0. */
int weapon_can_use_held(float value)
{
    char *hero;

    if (value <= 0.0f)
        goto fail;
    hero = D_00189E20_13;
    if (*(short *)(*(int *)(hero + 8848) + 170) != 0)
        goto fail;
    if (*(unsigned char *)(hero + 8884) != 0)
        goto fail;
    if (*(int *)(hero + 8852) == 49)
        goto fail;
    if (*(int *)(hero + 8860) == 20)
        goto fail;
    if (*(int *)(hero + 9420) > 0)
        goto ok;
fail:
    return 0;
ok:
    return 1;
}
