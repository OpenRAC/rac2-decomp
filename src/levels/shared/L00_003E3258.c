#include "common.h"

typedef int VectorBits __attribute__((mode(TI)));
typedef union { VectorBits bits; float f[4]; } __attribute__((aligned(16))) BeamVector;
typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { float vertices[4][4]; unsigned int colors[4]; float uv[4][2]; u64 registers[4]; } __attribute__((aligned(16))) BeamQuad;
extern void blast_reset_record_large(char *);
extern void FastVecScale(void *, void *, float);
extern float IntToFloat(int);


#define RAC2_T_VEC16_FC936841D

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;

typedef struct {
    void *object;
    int index;
    int unused0;
    float scale;
    int unused1[4];
} Entry_24efc0;

extern char *D_L00_001B2B54 __attribute__((sda));

extern void func_002833F0_1(char *a, char *b);

extern float func_00283198_1(float value);

extern void func_00282D30_3(char *a, char *b, float value);

extern float func_00283B98_3(float value, float scale);

extern int moby_is_in_special_class_range(char *object);

extern float *moby_get_private_value_0(char *object);

extern void func_00282D30_2(char *dst, char *src, float scale);

extern float func_00283B98_2(float, float);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_sin_or_cos_b(float);

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

extern int func_002A7820_2(int, int);

extern float func_002A7878_5(float, float);

extern float func_002A7940_2(void);

extern void gfx_draw_billboard_quad(char *, int, int, int, float, float, float);

extern void ref_L00_003E4948_00(void);

extern int D_L00_001B05DC_2 __attribute__((sda));

extern int D_L00_001B2B50_1 __attribute__((sda));

extern int D_L00_001B05DC_1 __attribute__((sda));

extern int save_is_record_value(short id, int mode);

extern int math_fast_helper_a(Vec16_Fc936841d *v, float scale);

extern void moby_mark_spawned(char *object);

extern void blast_draw_ring_mesh_large(char *object);

extern void blast_draw_ring_mesh_small(char *object);

extern void blast_draw_screen_flash(char *object);

extern void blast_draw_shell_mesh(char *object);

extern void blast_draw_ripple_mesh(char *object);

extern void blast_finish_effect_records(char *object);

extern int math_fast_float_d(void *p);

extern int func_001163B0(void);

extern void AllocateOwnedEffectParticle(char *rec, int a, float b, float c, int d);

extern void part_update_owned_effect(char *rec);

extern void part_spawn_for_owned_pieces(char *object);

extern int FloatToInt(float value);

extern int FastTweenColor(char *object, int index, float scale);

extern void set_moby_color(int handle, int a, int b, int c);

extern Entry_24efc0 g_fading_moby_list[];

#ifndef RAC2_T_VEC16_FC936841D
#endif

extern char D_0018A0E0[];
extern unsigned char *D_L00_001FEA14;
extern char g_camera_l00_position[];
extern char D_L00_001A8F20_1[] __attribute__((sda));
extern void FastVecSub(char *, char *, char *);
extern float mat_fast_helper_a(float, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern int math_random_int_below(int);
extern char *SpawnSpinningSparkParticle(float *, float, float, int, float *, float, float, unsigned, int);
extern char *func_002C16C0_1(float *, float *, int, int, unsigned, int, float, float, float, float, float);
/* Emit twenty paired particles around a position, optionally adding two final flashes. */
/* Bursts of sparks fly out from a point, with two extra flashes if asked. */
void part_l00_spawn_spark_burst_3(float *pos, int unused, int extra)
{
    float toCamera[4], velocity[4], spawnPos[4];
    float cameraAngle, speed, scale, pitch, yaw;
    int id, i, colorSeed;
    char *particle, *extraData;
    FastVecSub((char *)toCamera, g_camera_l00_position, (char *)pos);
    cameraAngle = mat_fast_helper_a(toCamera[0], toCamera[1]);
    for (i = 19; i >= 0; i--) {
        FastVecScale(velocity, D_0018A0E0, -(math_random_float_range(0.2f, 3.0f) * 0.01666666753590107f));
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        speed = math_random_float_range(0.3f, 0.75f) * 210000.0f;
        spawnPos[0] = pos[0] + math_random_signed_float_range(0.0f, 0.2f);
        spawnPos[1] = pos[1] + math_random_signed_float_range(0.0f, 0.2f);
        spawnPos[2] = pos[2] + math_random_signed_float_range(0.0f, 0.2f);
        particle = SpawnSpinningSparkParticle(spawnPos, 0.0f, 1.0f, id, velocity, 1.01f, speed, 0x7F202020, 1);
        if (particle) {
            particle[3] = 68;
            *(short *)(particle + 10) = 90;
            extraData = particle + 32;
            particle[9] = FloatToInt(4.0f) + 64;
            *(float *)(extraData + 28) = IntToFloat(5);
            *(int *)(extraData + 4) = 3;
            extraData[10] = 48;
            extraData[11] = particle[10];
        }
        scale = math_random_float_range(1.0f, 2.0f);
        pitch = math_random_float_range(0.0f, 1.396263599395752f);
        yaw = FastAddRotations(cameraAngle, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(velocity, scale * 0.01666666753590107f, yaw, pitch);
        spawnPos[0] = pos[0] + math_random_signed_float_range(0.0f, 0.1f);
        spawnPos[1] = pos[1] + math_random_signed_float_range(0.0f, 0.1f);
        spawnPos[2] = pos[2] + math_random_signed_float_range(0.0f, 0.1f);
        func_002C16C0_1(spawnPos, velocity, 30, 127, 0x7F7F7F, id,
            math_random_float_range(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    }
    if (extra == 1) {
        char *last;
        speed = 525000.0f;
        colorSeed = math_random_int_below(255);
        last = func_002C16C0_1(pos, (float *)D_L00_001A8F20_1, 5, 127, 0x207080, colorSeed, speed, 0.0f, 1.0f, 0.0f, 1.0f);
        if (last) last[2] = *D_L00_001FEA14;
        last = func_002C16C0_1(pos, (float *)D_L00_001A8F20_1, 5, 127, 0x207080, (colorSeed + 128) & 255, speed, 0.0f, 1.0f, 0.0f, 1.0f);
        if (last) last[2] = *D_L00_001FEA14;
    }
}

extern char g_camera_l00_position[];

extern void FastVecSub(char *dst, char *src, char *arg);

extern float mat_fast_helper_a(float, float);

extern float math_random_float_range(float, float);

extern float math_random_signed_float_range(float, float);

extern float FastAddRotations(float, float);

extern void vec_build_spherical_offset(float *, float, float, float);

extern void part_spawn_burst(float *, float *, int, int, unsigned int, int,
                          float, float, float, float, float);

/* Twenty rounds that spawn a particle at the point: each round draws a step and a random
   magnitude, jitters the point on each axis and hands the result to the spawn helper with
   210000.0f, 500.0f, 1.0f, 0.0f and 1.0f; the original game role is unknown. */
/* Sprays twenty small sparks from a point. */
void part_spawn_small_spark_spray(float *pos)
{
    float toCamera[4];
    float velocity[4];
    float spawnPos[4];
    float cameraAngle;
    float yaw;
    float step;
    float pitch;
    float speed;
    int id;
    int i;

    FastVecSub((char *)toCamera, g_camera_l00_position, (char *)pos);
    cameraAngle = mat_fast_helper_a(toCamera[0], toCamera[1]);

    for (i = 19; i >= 0; i--) {
        step = math_random_float_range(0.25f, 0.5f);
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        math_random_float_range(0.05f, 0.2f);
        speed = 210000.0f;
        pitch = math_random_float_range(0.0f, 1.396263599395752f);
        yaw = FastAddRotations(cameraAngle, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(velocity, step * 0.01666666753590107f, yaw, pitch);
        spawnPos[0] = pos[0] + math_random_signed_float_range(0.0f, 0.075f);
        spawnPos[1] = pos[1] + math_random_signed_float_range(0.0f, 0.075f);
        spawnPos[2] = pos[2] + math_random_signed_float_range(0.0f, 0.075f);
        part_spawn_burst(spawnPos, velocity, 15, 127, 0x007F7F7F, id,
                      math_random_float_range(0.05f, 0.2f) * speed, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}

/* Family 40487154aa250cc8: fixed-field addend writes into one resource record. */
/* Sets the colour scale of an object from three values that slowly settle. */
void moby_update_color_scale(char *object)
{
    char *data;
    float scaleX;
    float scaleY;
    float scaleZ;

    data = *(char **)(object + 104);
    func_002833F0_1(object + 192, object + 240);
    scaleX = func_00283198_1(*(float *)(data + 4)) * 0.15f + 0.35000002f;
    scaleY = func_00283198_1(*(float *)(data + 8)) * 0.15f + 0.35000002f;
    scaleZ = func_00283198_1(*(float *)(data + 12)) * 0.15f + 0.35000002f;
    func_00282D30_3(object + 192, object + 192, scaleX);
    func_00282D30_3(object + 208, object + 208, scaleY);
    func_00282D30_3(object + 224, object + 224, scaleZ);
    *(float *)(data + 4) = func_00283B98_3(*(float *)(data + 4), 0.5f);
    *(float *)(data + 8) = func_00283B98_3(*(float *)(data + 8), 0.5f);
    *(float *)(data + 12) = func_00283B98_3(*(float *)(data + 12), 0.5f);
}

/* calls two guards and returns 1 only when both succeed and the object's float field is not positive */
/* Tells if an object is a living target that can still be hit. */
int coll_is_living_hittable_target(char *object)
{
    float *health;

    if (moby_is_in_special_class_range(object) != 0)
        return 0;
    health = moby_get_private_value_0(object);
    if (health == 0)
        return 0;
    if (0.0f < *health)
        return 0;
    return 1;
}

/* func_L00_003E4508 is defined in L00_003E4508-g8.c. */

/* Calls a helper that does nothing more on its own. */
void blast_call_helper_no_args(void)
{
    ref_L00_003E4948_00();
}

extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern void *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern char D_L00_001FE940[];
extern char D_L00_001A8F20[] __attribute__((sda));
/* Throws out bright particles in a short line from an object's position. */
void part_spawn_line_at_moby(char *moby) {
    float origin[4];
    float backOffset[4];
    float upStep[4];
    float jittered[4];
    char *table;
    int colorSeed;
    char *particle;
    char *vars;
    float size;
    int i;

    vars = *(char **)(moby + 0x68);
    { float *p = (float *)(vars + 0x14);
    origin[0] = p[0];
    origin[1] = p[1];
    origin[2] = p[2]; }
    origin[3] = 0.0f;
    FastVecScale(backOffset, moby + 0xD0, -0.1f);
    FastVecAdd(origin, origin, backOffset);
    FastVecScale(upStep, moby + 0xE0, 0.15f);
    FastVecAdd(origin, origin, upStep);
    FastVecScale(upStep, moby + 0xE0, -0.033333335f);
    table = D_L00_001FE940;
    for (i = 8; i >= 0; i--) {
        jittered[0] = origin[0] + math_random_signed_float_range(0.0f, 0.1f);
        jittered[1] = origin[1] + math_random_signed_float_range(0.0f, 0.1f);
        jittered[2] = origin[2] + math_random_signed_float_range(0.0f, 0.1f);
        colorSeed = math_random_int_below(0xFF);
        size = 42000.0f;
        part_spawn_gravity_fade(jittered, D_L00_001A8F20, 4, 0x808080, colorSeed, 0x7F, 0x7F, size, size, 0.0f, 1);
        size = 273000.0f;
        particle = part_spawn_gravity_fade(origin, D_L00_001A8F20, 4, 0x406080, colorSeed, 0x10, 0x10, size, size, 0.0f, 1);
        if (particle != 0)
            *(unsigned char *)(particle + 2) = *(unsigned char *)(*(unsigned *)(table + 0xD4));
        FastVecAdd(origin, origin, upStep);
    }
}

/* func_L00_003E4B80 is defined in L00_003E4B80-g.c. */


/* func_L00_003E51C0 is defined in L00_003E51C0-g8.c. */

/* Clears a saved object pointer. */
void blast_clear_saved_pointer(void)
{
    D_L00_001B05DC_2 = 0;
}

/* clears two words of the shared state block; the second store reaches through
   $gp because it lands in the return delay slot */
/* Clears the blast data pointer and the saved object pointer. */
void blast_clear_state(void)
{
    D_L00_001B2B50_1 = 0;
    D_L00_001B05DC_1 = 0;
}

extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_fast_divide_helper(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern void ref_L00_003E5340_00(float *, float *, int, int, int);

/* Emits ten particles at POSITION: one thrown towards D_L00_001B8DC0 with a random spread, then
   nine at random upward angles turned by the object's matrix, about a third of them (rand() % 3
   == 0) in mode 1. */
/* Throws out ten sparks from a point, some upward and some toward the camera. */
void part_spawn_blast_sparks(char *object, float *position)
{
    Vector delta, velocity, random;
    float distance;
    int divisor = 3;
    int i = 8;
    int mode;

    FastVecSub((char *)delta, g_camera_l00_position, (char *)position);
    distance = FastVecLength(delta);
    *(VectorBits *)random = 0;
    random[0] = math_random_float_range(-1.0f, 1.0f);
    random[1] = math_random_float_range(-1.0f, 1.0f);
    random[2] = math_random_float_range(-1.0f, 1.0f);
    delta[2] += distance * 0.5f;
    *(VectorBits *)velocity = *(VectorBits *)random;
    vec_scale_to_length(velocity, velocity, distance * 0.0033333336468786f);
    vec_scale_to_length(delta, delta, (distance + distance) * 0.01666666753590107f);
    FastVecAdd(velocity, velocity, delta);
    vec_fast_divide_helper(velocity, velocity, 0.1666666716337204f);
    ref_L00_003E5340_00(position, velocity, math_random_int_range(60, 90), 0, 0);
    for (; i >= 0; i--) {
        float pitch, yaw, speed;

        mode = 0;
        pitch = math_random_float_range(0.2617994248867035f, 1.3089970350265503f);
        yaw = math_random_angle();
        speed = math_random_float_range(8.0f, 12.0f);
        vec_build_spherical_offset(random, speed * 0.01666666753590107f, yaw, pitch);
        random[2] += 0.05000000447034836f;
        if (func_001163B0() % divisor == 0)
            mode = 1;
        matrix_mul_vec3(random, random, object + 0xC0);
        ref_L00_003E5340_00(position, random, math_random_int_range(60, 90), mode, 0);
    }
}

#include "common.h"

/* func_L00_003E5650 is defined in L00_003E5650-qcopy.c. */

/* func_L00_003E5710 is defined in L00_003E3258-g8.c. */

/* func_L00_003E5978 is defined in L00_003E3258-g8.c. */


/* func_L00_003E6030 is defined in L00_003E6030-g8.c. */


/* Walks the shared table of 0x50-byte records and, for the one owned by OBJECT, either
   releases the owner when the record is busy, or (half of the time) runs the effect helper
   twice with a zero amount; the record is then closed. The amount is converted from an int
   so that the compiler keeps it in a saved register across the calls, as the retail code
   does. */
/* Goes through the blast's effect records and keeps the ones owned by this object updating. */
void blast_update_effect_records(char *object)
{
    char *rec;
    int zero = 0;
    float amount = (float)zero;
    int offset = 0;
    int i = 0;

    do {
        i--;
        rec = (char *)(offset + (int)D_L00_001B2B50_1);
        if (*(int *)(rec + 0x30) == (int)object) {
            if (math_fast_float_d(rec + 0x34) != 0) {
                if (*(int *)(rec + 0x38) == 0) {
                    *(int *)(rec + 0x30) = 0;
                }
            } else if ((func_001163B0() & 1) == 0) {
                AllocateOwnedEffectParticle(rec, 0, amount, amount, 0);
                AllocateOwnedEffectParticle(rec, 0, amount, amount, 0);
            }
            part_update_owned_effect(rec);
        }
        offset += 0x50;
    } while (i >= 0);
}
/* Goes through the blast's effect records and tidies up the ones owned by this object. */
void blast_finish_effect_records(char *object)
{
    char *rec;
    int i;
    int offset;

    offset = 0;
    i = 0;
    do {
        i--;
        rec = (char *)(offset + (int)D_L00_001B2B50_1);
        if (*(int *)(rec + 0x30) == (int)object)
            part_spawn_for_owned_pieces(rec);
        offset += 0x50;
    } while (i >= 0);
}

/* func_L00_003E6778 is defined in L00_003E6778.c. */


extern char *D_L00_001B2BB8 __attribute__((sda));
extern void ref_L00_003E6F48_01(char *rec, float f1, int a1, int a2, int a3,
                                float f2, int a4, float f3);

/* Same body as func_L00_003F09A0, with this function's own callees. */
extern char *ref_L00_003E6F48_00 __attribute__((sda));
/* Finds every piece owned by the object and spawns a small effect for it. */
void part_spawn_for_owned_pieces(char *owner)
{
    char *piece;
    int index;

    for (index = 0; index < 320; index++) {
        piece = (char *)(index * 128 + (int)ref_L00_003E6F48_00);
        if (*(int *)(piece + 0x7C) == (int)owner)
            ref_L00_003E6F48_01(piece, *(float *)(piece + 0x48), *(int *)(piece + 0x68),
                                *(int *)(piece + 0x60), 46, *(float *)(piece + 0x34),
                                *(int *)(piece + 0x70), 0.25f);
    }
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
/* Resets a record to its starting values. */
void blast_reset_record(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
/* Makes four vectors bigger or smaller by the same amount. */
void vec_scale_four_b(char *vectors, float scale)
{
    func_00282D30_2(vectors, vectors, scale);
    func_00282D30_2(vectors + 16, vectors + 16, scale);
    func_00282D30_2(vectors + 32, vectors + 32, scale);
    func_00282D30_2(vectors + 48, vectors + 48, scale);
}

/* func_L00_003E70B8 is defined in L00_003E70B8.c. */

/* func_L00_003E7650 is defined in L00_003E7650-qcopy.c. */

/* Does nothing. */
void blast_hook_empty(void)
{
}

/* func_L00_003E7C88 is in L00_003E3258-fade.c */

/* func_L00_003E7E40 lives in L00_003E7E40-trails.c. */

/* Sets the see-through level and colour of one fading object. */
void moby_set_fading_alpha_color(int index, char *object)
{
    int r;
    int high;

    *(char *)((char *)g_fading_moby_list[index].object + 0x23) =
        FloatToInt(g_fading_moby_list[index].scale * 96.0f);
    r = FastTweenColor(object, g_fading_moby_list[index].index,
                      g_fading_moby_list[index].scale);
    high = (r >> 16) & 0xFF;
    set_moby_color((int)g_fading_moby_list[index].object, r & 0xFF, (r >> 8) & 0xFF,
                  high);
}

/* func_L00_003E8180 uses small data in L00_003E8180-g8.c. */

/* func_L00_003E9490 is defined in L00_003E9490-qcopy.c. */

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
/* Works out a smooth point along a curve between two points. */
void math_interpolate_curve_point(float *out, float *b, float *c, float *a, float *d, float t)
{
    float tSquared, tCubed, curveA, curveB, curveC;

    if (t == 0.0f) {
        qcopy(out, b);
        return;
    }
    if (t == 1.0f) {
        qcopy(out, c);
        return;
    }
    tSquared = t * t;
    tCubed = tSquared * t;

    curveA = (d[0] - c[0]) - (a[0] - b[0]);
    curveB = (a[0] - b[0]) - curveA;
    curveC = c[0] - a[0];
    out[0] = curveA * tCubed + curveB * tSquared + curveC * t + b[0];

    curveA = (d[1] - c[1]) - (a[1] - b[1]);
    curveB = (a[1] - b[1]) - curveA;
    curveC = c[1] - a[1];
    out[1] = curveA * tCubed + curveB * tSquared + curveC * t + b[1];

    curveA = (d[2] - c[2]) - (a[2] - b[2]);
    curveB = (a[2] - b[2]) - curveA;
    curveC = c[2] - a[2];
    out[2] = curveA * tCubed + curveB * tSquared + curveC * t + b[2];
    out[3] = 0.0f;
}

/* Shared native body; original game role is unknown. */
/* Moves each entry in a list of wave values forward and works out its new offsets. */
void part_update_wave_offsets(int unused, float *points, int count)
{
    float *cursor;
    int remaining;
    if (count <= 0)
        return;
    cursor = points;
    remaining = count;
    do {
        cursor[0] = func_00283B98_2(cursor[0], cursor[3]);
        cursor[1] = func_00283B98_2(cursor[1], cursor[4]);
        cursor[2] = func_00283B98_2(cursor[2], cursor[5]);
        cursor[9] = func_00283B98_2(cursor[9], cursor[12]);
        cursor[10] = func_00283B98_2(cursor[10], cursor[13]);
        cursor[11] = func_00283B98_2(cursor[11], cursor[14]);
        cursor[20] = math_fast_sin_or_cos_a(cursor[0]) * cursor[6];
        cursor[21] = math_fast_sin_or_cos_b(cursor[1]) * cursor[7];
        cursor[22] = -math_fast_sin_or_cos_b(cursor[2]) * cursor[8];
        cursor[24] = math_fast_sin_or_cos_a(cursor[9]) * cursor[15];
        cursor[25] = math_fast_sin_or_cos_b(cursor[10]) * cursor[16];
        cursor[26] = -math_fast_sin_or_cos_b(cursor[11]) * cursor[17];
        cursor += 32;
    } while (--remaining != 0);
}

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
/* Works out the next point in a list from the two points before it. */
void vec_extend_from_neighbours(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

/* Derives a value from half of one argument, merges a helper's low byte into a packed word, then scales an input float, doubles a second helper's result and dispatches a seven-argument spawn. */
/* Spawns one random effect from a position and colour. */
void part_spawn_random_effect(int p0, int p1, int p2, int p3, float v)
{
    int r;
    float s;
    float t;

    r = func_002A7820_2(p3 >> 1, p3);
    p2 = p2 | (r << 24);
    s = func_002A7878_5(v * 0.75f, v);
    s = s + s;
    t = func_002A7940_2();
    gfx_draw_billboard_quad((char *)p1, 44, p2, 1, s, 0.08f, t);
}

/* Draw a two-layer ribbon along a sequence of sampled beam points. */
/* func_L00_003E9B90 is defined in L00_003E9B90-ribbon.c. */


/* straight-line constant-store body (no calls, no branches, no loads) */
/* Sets a record to its starting values with a larger size. */
void blast_reset_record_large(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 88) = 0;
    *(float *)(p + 96) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(int *)(p + 84) = 0;
    *(float *)(p + 92) = 1.0f;
    *(int *)(p + 100) = 0;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
