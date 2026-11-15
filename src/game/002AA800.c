#include "include_asm.h"
#include "names.h"

typedef struct { int colors[6]; } Colors1043;
extern Colors1043 ref_L00_002AC728_00, ref_L00_002AC728_01;
extern float ref_L00_002AC728_02[];
extern int math_random_int_below(int);
extern char *part_spawn_firework_spark(void *, void *, int, int, float, int, int, float, int, int);
extern char *part_spawn_shockwave_ring(void *, void *, void *, int, int, int, int, int, float);
extern int PlayMobySound(int, int, void *);
extern char *moby_spawn_template_effect(void *, void *, int, int);

extern float math_shortest_angle_delta (float x, int a1, float y);

extern float func_00283B98_14 (float x, float y);

extern unsigned int func_00283CF0_5(float x);

extern void Fa5914967_FUN_00282F20(float *a, float *b, float c);

extern void func_00282CF0_13(float *, int, int);

extern void func_00283698_4(float *, int);

extern void func_002830C0_7(float *, float *, float *);

typedef int s32;

typedef unsigned char u8;

/* lot14 -- measured bodies with sizes recorded in the catalogue. */
extern u8 g_hero_moby[];

extern float func_00283198_7(float x);

extern void func_00282D30_18(void *a0, int a1, float x);

extern float func_00283180_8(float x);

#ifndef RAC2_T_V4_F876460D6
#define RAC2_T_V4_F876460D6
typedef int V4_F876460d6 __attribute__((mode(TI)));
#endif

extern void func_00282C88_3(char *p);

extern float func_00283248_6(float a, float b);

extern void func_00283410_7(char *dst, char *src);

extern void func_00283788_4(char *a, char *b, char *c);

extern void mat_fast_helper_b(char *dst, char *src);

extern float F500f9762_FUN_00283CE0(int index);

extern int F500f9762_FUN_00283CF0(float value);

extern void F500f9762_FUN_002A04B8(int first, char *a, char *b, char *c);

extern int g_moby_l02_pool __attribute__((sda));

extern float math_random_float_range(float, float);

#ifndef RAC2_T_V4_F904CC63B
#define RAC2_T_V4_F904CC63B
typedef __attribute__((mode(TI))) int V4_F904cc63b;
#endif

extern char *F904cc63b_FUN_002AD0B0(char *p);

extern void F904cc63b_FUN_00283410(V4_F904cc63b *dst, char *src);

extern void F904cc63b_FUN_00282CC0(V4_F904cc63b *dst, V4_F904cc63b *a, char *b);

extern void F904cc63b_FUN_00282CF0(V4_F904cc63b *dst, V4_F904cc63b *a, char *b);

extern void F904cc63b_FUN_00283698(V4_F904cc63b *dst, V4_F904cc63b *src);

extern void F904cc63b_FUN_00283098(V4_F904cc63b *dst, V4_F904cc63b *a, V4_F904cc63b *b);

/* Family 0e7bb6a8908d30dc -- 244 bytes, 28 placements (1 boot + 27 levels). */

extern char *F0e7bb6a8_FUN_002AD0B0(char *a);

extern void F0e7bb6a8_FUN_00283410(char *dst, char *src);

extern void F0e7bb6a8_FUN_00283698(char *dst, char *src);

extern void F0e7bb6a8_FUN_00282CF0(char *dst, char *a, char *b);

extern void F0e7bb6a8_FUN_002830C0(char *a, char *b, char *c);

extern void F0e7bb6a8_FUN_00283788(char *a, char *b, char *c);

extern void F0e7bb6a8_FUN_002AB6D8(char *a, char *b);

extern float func_00283B98_11(float x);

extern float func_00283198_13(float x);

extern float func_00283198_8(float x);

extern float func_00283180_9(float x);

extern float func_00283B98_8(float x, float y);

extern float func_00283180_10(float);

extern float func_00283198_10(float);

extern float Fb5729173_FUN_00282E48(char *a, char *b);

extern float Fb5729173_FUN_00283248(float x, float y);

extern float Fb5729173_FUN_00283C80(float x, float y);

extern float Fb5729173_FUN_00282E80(char *a, char *b);

extern int Fb5729173_FUN_002ABB78(char *a);

extern void F10bf3d29_FUN_00283698(char *a, char *b);

extern void F10bf3d29_FUN_00283098(char *a, char *b, char *c);

/* clamps a float read through a pointer to plus/minus the second float argument, passes it through two helpers and stores the result back */
void StepAngleTowardTarget (float *p, int a1, float fx, float fl)
{
  float v;

  v = math_shortest_angle_delta (fx, a1, p[0]);
  if (fl < v)
    v = fl;
  else if (v < -fl)
    v = -fl;
  v = func_00283B98_14 (p[0], v);
  p[0] = v;
  math_shortest_angle_delta (fx, a1, v);
}

extern void math_update_spring_velocity(float *, float, float, float, float);
extern float math_fabs(float);

float math_approach_with_velocity(float *position, float target, float *velocity,
                   float acceleration, float damping, float limit, int direction)
{
    float distance;
    float residual;
    if (direction == 2) {
        if ((target > 0.0f && *position < 0.0f) ||
            (target < 0.0f && *position > 0.0f)) {
            direction = 1;
            if (target < 0.0f) direction = -1;
        } else direction = 0;
    }
    distance = math_shortest_angle_delta(target, direction, *position);
    math_update_spring_velocity(velocity, distance, acceleration, damping, limit);
    distance = func_00283B98_14(*position, *velocity);
    *position = distance;
    residual = math_shortest_angle_delta(target, direction, distance);
    if (math_fabs(residual) < limit * 0.01f) {
        *position = target;
        *velocity = 0.0f;
        return *velocity;
    }
    return residual;
}


/* func_002AAC80 is in 002AAC80-smoothing.c. */

/* Scales four float arguments by 255, converts each through the same routine, masks each result to a byte and packs the four bytes into one word, low byte first. */
int gfx_pack_color_floats(float r, float g, float b, float a)
{
    unsigned int cr = func_00283CF0_5(r * 255.0f) & 0xff;
    unsigned int cg = func_00283CF0_5(g * 255.0f) & 0xff;
    unsigned int cb = func_00283CF0_5(b * 255.0f) & 0xff;
    unsigned int ca = func_00283CF0_5(a * 255.0f) & 0xff;
    unsigned int packed = cr;

    packed |= cg << 8;
    packed |= cb << 16;
    packed |= ca << 24;
    return packed;
}

void swap_color_channel_words(int *a, int *b, int *c, int mask) {
    int x, y;
    if (mask & 1) { x = *b; y = *a; *a = x; *b = y; }
    if (mask & 2) { x = *c; y = *b; *b = x; *c = y; }
    if (mask & 4) { x = *a; y = *c; *c = x; *a = y; }
}

/* Scales four float arguments by 255, converts each through the same routine, masks each result to a byte and packs the four bytes into one word, low byte first. */


/* Shuffles the red, green and blue parts of a packed color according to a mask and keeps the alpha part. */
int gfx_swap_packed_color_channels(unsigned int color, int mask)
{
    int tmp[3];
    int mid;
    unsigned int alpha;
    int result;

    if (mask == 0)
        return color;

    tmp[0] = color & 0xFF;
    mid = color & 0xFF00;
    tmp[1] = mid >> 8;
    tmp[2] = (color >> 16) & 0xFF;
    alpha = color >> 24;
    swap_color_channel_words(tmp, tmp + 1, tmp + 2, mask);
    result = alpha << 24;
    result |= tmp[2] << 16;
    result |= tmp[1] << 8;
    result |= tmp[0];
    return result;
}

/* Makes each of the three columns of a matrix have length one. */
void mat_normalize_columns(float (*matrix)[4])
{
    int column;
    int i;
    float vec[4];

    for (column = 0; column < 3; column++) {
        vec[3] = 0.0f;
        for (i = 0; i < 3; i++)
            vec[i] = matrix[i][column];
        Fa5914967_FUN_00282F20(vec, vec, 1.0f);
        for (i = 0; i < 3; i++)
            matrix[i][column] = vec[i];
    }
}

/* Initialises a 96-byte stack workspace, calls one routine on its first window with two of the incoming integers, fills the third window from a second routine, combines the three windows with a third routine, and returns one float of the middle window indexed by the fourth integer. */
float mat_get_product_element(int argA, int argB, int argC, int index)
{
	float workspace[24];
	float *middle = workspace + 4;

	func_00282CF0_13(workspace, argC, argA);
	func_00283698_4(workspace + 8, argB);
	func_002830C0_7(middle, workspace, workspace + 8);
	return middle[index];
}

extern void vec_scale_to_length(float *, float *, float);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);

/* Adds to a vector a piece of itself that points along the given axis, scaled by an amount. */
void vec_add_along_axis(float *out, float *vector, float *axis, float amount)
{
    float scaled[4];
    float unit[4];
    float dot;
    vec_scale_to_length(unit, axis, 1.0f);
    dot = FastVecDot(unit, vector);
    FastVecScale(scaled, unit, dot * amount);
    FastVecSub(out, vector, scaled);
}

/* Returns the first value stored in the object's private data, or 0 if it has none. */
char *moby_get_private_value_0(u8 *moby) {
 if(moby==0) return 0;
 if((*(unsigned short *)(moby+0x34)&0x20)!=0) return (*(s32 **)(moby+0x68))[0];
 return 0;
}

/* Returns the fifth value stored in the object's private data, or 0 if it has none. */
char *moby_get_private_value_4(u8 *moby) {
 if(moby==0) return 0;
 if((*(unsigned short *)(moby+0x34)&0x20)!=0) return (*(s32 **)(moby+0x68))[4];
 return 0;
}

extern int coll_scatter_points_in_shapes(void *, int, void *, void *, float);
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern void vec_build_spherical_offset(float *, float, float, float);
extern char *part_spawn_scaling(void *, void *, unsigned int, int, int, int, int, int);

/* Spawns small glowing sparks at several points around an object. */
void part_spawn_sparks_around_moby(void *owner, char *offset, void *filter)
{
    char vectors[320];
    float position[4];
    char *cursor;
    float *point;
    int count;
    int result;
    int first;
    float angle;
    result = coll_scatter_points_in_shapes(owner, 20, vectors, filter, 14.0f);
    if (result == 0)
        return;
    if (result > 0) {
        point = position;
        cursor = vectors;
        count = result;
        do {
            angle = math_random_angle();
            vec_build_spherical_offset(point, 0.030000001192092896f, angle, math_random_angle());
            F904cc63b_FUN_00282CC0((V4_F904cc63b *)point, (V4_F904cc63b *)point, offset);
            position[2] += 0.015000000596046448f;
            first = math_random_int_range(20, 35);
            part_spawn_scaling(cursor, point, 0x7000A0FFu, 255, first, 30, math_random_int_range(40, 60), 1);
            cursor += 16;
        } while (--count != 0);
    }
}


extern void copy_matrix_rotation(void *, void *);
extern void mat_to_quaternion(void *, void *);
extern void copy_matrix3x4(void *, void *);

/* Copies a matrix, changes the copy, and writes the result back. */
void mat_transform_via_copy(void *target, void *matrix) {
    unsigned char copy[0x40];
    copy_matrix_rotation(copy, matrix);
    mat_to_quaternion(target, copy);
    copy_matrix3x4(matrix, copy);
}

/* Copies an 8-byte value from one object into another. */
void hero_copy_field_to_moby(u8 *dest) {
    u8 *source = *(u8 **)g_hero_moby;
    *(long *)(dest + 0x38) = *(long *)(source + 0x38);
}

/* Halves the float argument and calls one helper with it, forwards the second and first arguments plus that helper result to a second helper, and stores a third helper result into the field at offset 12 of the first argument. */
void math_build_axis_angle_quat(void *rotation, int axis, float angle)
{
    float halfAngle = angle * 0.5f;
    float sine = func_00283198_7(halfAngle);

    func_00282D30_18(rotation, axis, sine);
    *(float *)((char *)rotation + 12) = func_00283180_8(halfAngle);
}


/* Copies 64 bytes of a source record onto the stack, normalises the last element of the copy to 1.0, queries three pairwise float angles from the copy after two scratch-matrix builds, and writes the three angles into the caller's output record. */
void mat_get_euler_angles(float *src, float *out)
{
    V4_F876460d6 rotation[4];
    float matrix[16];
    float local[4];
    float angleZ, angleY, angleX;

    *(V4_F876460d6 *)(matrix + 0) = *(V4_F876460d6 *)(src + 0);
    *(V4_F876460d6 *)(matrix + 4) = *(V4_F876460d6 *)(src + 4);
    *(V4_F876460d6 *)(matrix + 8) = *(V4_F876460d6 *)(src + 8);
    *(V4_F876460d6 *)(matrix + 12) = *(V4_F876460d6 *)(src + 12);
    func_00282C88_3((char *)(matrix + 12));
    matrix[15] = 1.0f;
    angleZ = func_00283248_6(matrix[0], matrix[1]);
    local[0] = 0.0f;
    local[1] = 0.0f;
    local[2] = -angleZ;
    func_00283410_7((char *)rotation, (char *)local);
    func_00283788_4((char *)matrix, (char *)rotation, (char *)matrix);
    angleY = func_00283248_6(matrix[0], -matrix[2]);
    local[0] = 0.0f;
    local[2] = 0.0f;
    local[1] = -angleY;
    mat_fast_helper_b((char *)rotation, (char *)local);
    func_00283788_4((char *)matrix, (char *)rotation, (char *)matrix);
    angleX = func_00283248_6(matrix[5], matrix[6]);
    out[2] = angleZ;
    out[1] = angleY;
    out[0] = angleX;
    local[1] = 0.0f;
    local[0] = -angleX;
    local[2] = 0.0f;
}

/* Starts or restarts a color fade timer for a light or glow. */
void gfx_start_color_fade(int first, char *object)
{
    char *fader = object;
    short oldTime = *(short *)(fader + 0);
    unsigned short duration;
    float limit;
    int result;

    if (oldTime != 0 && *(short *)(fader + 2) == 0)
        return;
    duration = *(unsigned short *)(fader + 12);
    *(short *)(fader + 2) = 0;
    *(short *)(fader + 0) = duration;
    if (oldTime != 0) {
        limit = F500f9762_FUN_00283CE0(*(short *)(fader + 14));
        result = F500f9762_FUN_00283CF0((float)*(short *)(fader + 12) * ((float)oldTime / limit));
        *(short *)(fader + 0) = (short)result;
        if ((short)result <= 0)
            *(short *)(fader + 0) = 1;
    } else {
        int red, green, blue;
        F500f9762_FUN_002A04B8(first, (char *)&red, (char *)&green, (char *)&blue);
        *(char *)(fader + 4) = (unsigned char)red;
        *(char *)(fader + 5) = (unsigned char)green;
        *(char *)(fader + 6) = (unsigned char)blue;
    }
}

extern int F500f9762_FUN_00282978(char *a0);

extern void F500f9762_FUN_002A0488(void *a, int b, int c, int d);

/* Updates a color fade each frame and sets the light color on the owner. */
void gfx_update_color_fade(void *owner, u8 *obj)
{
    int red, green, blue;
    float limit, blend;

    if (*(short *)obj == 0)
        return;

    if (F500f9762_FUN_00282978((char *)obj) != 0) {
        if (*(short *)(obj + 2) != 0) {
            F500f9762_FUN_002A0488(owner, obj[4], obj[5], obj[6]);
            return;
        }
        *(short *)(obj + 2) = 1;
        *(short *)obj = *(unsigned short *)(obj + 0xE);
    }

    if (*(short *)(obj + 2) == 0) {
        limit = F500f9762_FUN_00283CE0(*(short *)(obj + 0xC));
        blend = (limit - (float)*(short *)obj) / limit;
        red = obj[7] ? F500f9762_FUN_00283CF0((float)obj[4] + (float)(obj[7] - obj[4]) * blend) : obj[4];
        green = obj[8] ? F500f9762_FUN_00283CF0((float)obj[5] + (float)(obj[8] - obj[5]) * blend) : obj[5];
        blue = obj[9] ? F500f9762_FUN_00283CF0((float)obj[6] + (float)(obj[9] - obj[6]) * blend) : obj[6];
    } else {
        limit = F500f9762_FUN_00283CE0(*(short *)(obj + 0xE));
        blend = (limit - (float)*(short *)obj) / limit;
        red = obj[7] ? F500f9762_FUN_00283CF0((float)obj[7] + (float)(obj[4] - obj[7]) * blend) : obj[4];
        green = obj[8] ? F500f9762_FUN_00283CF0((float)obj[8] + (float)(obj[5] - obj[8]) * blend) : obj[5];
        blue = obj[9] ? F500f9762_FUN_00283CF0((float)obj[9] + (float)(obj[6] - obj[9]) * blend) : obj[6];
    }

    F500f9762_FUN_002A0488(owner, red, green, blue);
}




extern char *g_mobyTableBase __attribute__((sda));
extern char *g_mobyTableEnd __attribute__((sda));

/* Returns true if the pointer is a valid object in the object table and its class is one of a small group of classes. */
int moby_is_in_special_class_range(char *object)
{
    if (object != 0)
        goto check;
fail:
    return 0;
check:
    if ((unsigned int)object < (unsigned int)g_mobyTableBase)
        goto fail;
    if ((unsigned int)g_mobyTableEnd < (unsigned int)object)
        goto fail;
    return (unsigned int)(*(unsigned short *)(object + 0xAA) - 500) < 41;
}

/* Creates an explosion at a position with sparks, flashes, a sound and an optional shockwave. */
void part_spawn_explosion_with_sparks(unsigned char *object, void *position, int sound, float scale, float radius)
{
    float zero[4];
    Colors1043 colorsA, colorsB;
    float speed, energy;
    int i, life;
    int *colorA, *colorB;
    func_00282C88_3((char *)zero);
    for (i=2;i>=0;i--) {
        speed = math_random_float_range(8.0f,10.0f) * 0.01666666753590107f;
        energy = scale * 400000.0f;
        colorsA = ref_L00_002AC728_00;
        colorsB = ref_L00_002AC728_01;
        colorA = &colorsA.colors[math_random_int_below(6)];
        colorB = &colorsB.colors[math_random_int_below(6)];
        life = math_random_int_range(15,20);
        part_spawn_firework_spark(position,zero,*colorA,*colorB,energy,life,math_random_int_range(25,30),speed*scale,0,0);
    }
    if (object) {
        part_spawn_shockwave_ring(object,position,zero,20,127,64,0,48,scale*4.0f);
        part_spawn_shockwave_ring(object,position,zero,29,96,32,0,32,scale*3.0f);
        if (object[0x20] != 0xfe)
            if (object[0x20] != 0xfd)
                if (sound != -1) PlayMobySound(sound,0,object);
    }
    if (radius != 0.0f) {
        if (radius > 0.0f) {
            ref_L00_002AC728_02[9]=radius;
            ref_L00_002AC728_02[10]=radius;
            ref_L00_002AC728_02[8]=radius;
        } else {
            ref_L00_002AC728_02[9]=13.0f;
            ref_L00_002AC728_02[10]=13.0f;
            ref_L00_002AC728_02[8]=13.0f;
        }
        moby_spawn_template_effect(ref_L00_002AC728_02,position,0,0);
    }
}


extern void vec_scale_to_length(float *, float *, float);
extern float FastVecLength(float *);
/* Shortens a vector to the given length if it is longer than that. */
void vec_clamp_length(float *vector, float threshold) { if (threshold < FastVecLength(vector)) vec_scale_to_length(vector, vector, threshold); }


extern int g_moby_l02_pool;

/* The subtraction uses the corresponding global in each program. */
void AddMobyToIndexList(int param_1, short *param_2, short param_3)
{
    int i;

    param_1 = (param_1 - g_moby_l02_pool) << 8 >> 16;
    for (i = 1; i <= param_2[0]; i++) {
        if (param_2[i] == param_1) return;
    }
    if (param_2[0] < param_3) {
        param_2[0] = param_2[0] + 1;
        param_2[param_2[0]] = param_1;
    }
}

/* shared native body of family bef45185f2ede0ad */
void RemoveMobyFromIndexList(int param_1, unsigned short *param_2)
{
    int i;

    for (i = 1; i <= (short)param_2[0]; i++) {
        if (g_moby_l02_pool + ((short)param_2[i] << 8) == param_1) {
            param_2[i] = param_2[(short)param_2[0]];
            param_2[0] = param_2[0] - 1;
            return;
        }
    }
}

/* Adds the result of a two-argument helper, called three times with the same arguments, into each of three consecutive floats of a vector. */
void vec_add_random_offset(float *vector, float scale)
{
    float negative = -scale;

    vector[0] = vector[0] + math_random_float_range(negative, scale);
    vector[1] = vector[1] + math_random_float_range(negative, scale);
    vector[2] = vector[2] + math_random_float_range(negative, scale);
}

extern char *D_001B1C4C __attribute__((sda));
extern void matrix_mul_vec3(char *, char *, char *);

int IsPointInCuboid(void *point, int index)
{
    float local[4];
    float transformed[4];
    char *record;

    if (index != -1) {
        record = D_001B1C4C + (index << 7);
        FastVecSub(local, point, record + 0x30);
        local[3] = 0.0f;
        matrix_mul_vec3((char *)transformed, (char *)local, record + 0x40);
        if (transformed[0] >= -1.0f && transformed[0] <= 1.0f &&
            transformed[1] >= -1.0f && transformed[1] <= 1.0f &&
            transformed[2] >= -1.0f && transformed[2] <= 1.0f)
            return 1;
    }
    return 0;
}


extern char *D_001B1C54 __attribute__((sda));

/* Transforms a point by the record of its index and returns whether the result lies inside the unit sphere. */
int coll_is_point_inside_unit_sphere(void *point, int index)
{
    float local[4];
    float transformed[4];
    char *record;

    if (index < 0) {
        return 0;
    } else {
        record = D_001B1C54 + (index << 7);
        FastVecSub(local, point, record + 0x30);
        local[3] = 0.0f;
        matrix_mul_vec3((char *)transformed, (char *)local, record + 0x40);
        if (FastVecLength(transformed) < 1.0f)
            return 1;
    }
    return 0;
}


typedef struct { int selected, reserved04, reserved08, count; } MatchRange;
extern MatchRange ref_L00_002ACD38_00;
extern float ref_L00_002ACD38_01[][4];
extern int vec_fast_helper_f(void *, void *, void *);
/* Checks whether an object is inside one of the saved zones and whether it is the selected one. */
int moby_is_in_selected_zone(void *object)
{
    int found = 0;
    int i;
    for (i = ref_L00_002ACD38_00.count - 1; i >= 0; i--) {
        if (vec_fast_helper_f(object, ref_L00_002ACD38_01[i], ref_L00_002ACD38_01[i + 2])) {
            found = i + 1;
            break;
        }
    }
    return found == ref_L00_002ACD38_00.selected;
}



extern void vec_scale_to_length(float *dst, float *src, float scale);
extern float square_root(float x);

/* Sets a direction vector and stores a matching value from its length in the fourth slot. */
void vec_set_direction_with_complement(float *out, float *dir, float x) { vec_scale_to_length(out, dir, x); out[3] = square_root(1.0f - x * x); }




/* Returns the third value stored in the object's private data, or 0 if it has none. */
char *moby_get_private_value_2(u8 *moby) {
 if(moby==0) return 0;
 if((*(unsigned short *)(moby+0x34)&0x20)==0) return 0;
 return (*(s32 **)(moby+0x68))[2];
}


/* func_002AD250 is in 002AD250-rc2.c (it needs the grouped 128-bit copy). */

/* Moves a point through an object's attached transform and writes the result. Returns 0 if the object has no transform. */
int moby_transform_point_by_attachment(char *unused, char *object, char *point, char *out)
{
    V4_F904cc63b matA[4];
    V4_F904cc63b work[1];
    V4_F904cc63b matInverse[4];
    V4_F904cc63b matCopy[4];
    char *record;

    record = F904cc63b_FUN_002AD0B0(object);
    if (record == 0)
    {
        *(V4_F904cc63b *)out = 0;
        return 0;
    }
    F904cc63b_FUN_00283410(matA, record);
    F904cc63b_FUN_00282CC0(work, (V4_F904cc63b *)point, record + 16);
    F904cc63b_FUN_00282CF0(work, work, object + 16);
    if (*(int *)(record + 60) & 2)
    {
        F904cc63b_FUN_00283410(matCopy, record + 32);
        F904cc63b_FUN_00283698(matInverse, matCopy);
        F904cc63b_FUN_00283098(work, work, matInverse);
        F904cc63b_FUN_00283098(work, work, (V4_F904cc63b *)(object + 192));
    }
    else
    {
        F904cc63b_FUN_00283098(work, work, matA);
    }
    F904cc63b_FUN_00282CC0(work, work, object + 16);
    F904cc63b_FUN_00282CF0((V4_F904cc63b *)out, work, point);
    return 1;
}


/* Builds rotation angles for a point relative to an object's attached transform. Returns 0 if there is none. */
int moby_get_attachment_rotation_angles(char *unused, char *obj, char *arg2, char *arg3, char *arg4, char *arg5)
{
    char invMatrix[64];
    char localPos[16];
    char tempMatrix[64];
    char *record;

    record = F0e7bb6a8_FUN_002AD0B0(obj);
    if (record == 0)
        return 0;
    if (*(int *)(record + 60) & 0x40) {
        F0e7bb6a8_FUN_00283410(invMatrix, obj + 240);
        F0e7bb6a8_FUN_00283698(invMatrix, invMatrix);
    } else {
        F0e7bb6a8_FUN_00283698(invMatrix, obj + 192);
    }
    F0e7bb6a8_FUN_00282CF0(localPos, arg2, obj + 16);
    F0e7bb6a8_FUN_002830C0(arg4, localPos, invMatrix);
    F0e7bb6a8_FUN_00283410(tempMatrix, arg3);
    F0e7bb6a8_FUN_00283788(tempMatrix, invMatrix, tempMatrix);
    F0e7bb6a8_FUN_002AB6D8(tempMatrix, arg5);
    return 1;
}

/* func_002AD6F0 uses the quadword-copy profile in 002AA800-qcopy.c. */

extern u8 D_001A7BC8[] __attribute__((sda));
extern int D_00139948[];

/* Sets the byte flag of `index` once and, for indices below 0x15 and index 24, appends it to
   the 28-entry list. The sum over the set flags is never read: flow deletes it after the
   loop pass, which leaves retail's empty ascending loop. */
void moby_mark_flag_and_append_to_list(int index)
{
    int i;
    int j;
    int sum;
    int count;

    if (D_001A7BC8[index] != 0)
        return;
    sum = 0;
    for (j = 0; j < 28; j++)
        if (D_001A7BC8[j] != 0)
            sum += j;
    D_001A7BC8[index] = 1;
    if (index >= 0x15 && index != 24)
        return;
    count = 0;
    for (i = 0; i < 28; i++)
        if (D_00139948[i] != 0)
            count++;
    D_00139948[count] = index;
}

/* func_002AD860 is in 002AD860.c. */

typedef struct { u8 before[0x1220]; u8 *owner; u8 gap[0x24]; s32 value; } HeroFields;
extern HeroFields g_hero_state;
extern u8 g_item_slot_to_record[];
typedef struct { u8 before[0x14]; s32 kind; u8 after[0xE0 - 0x18]; } KindRecord;
extern KindRecord g_weapon_table[];

/* Works out which kind slot an object belongs to from its class, or 255 if none matches. */
s32 moby_get_kind_slot(u8 *object) {
    s32 i;

    switch (*(short *)(object + 0xAA)) {
    case 0xA66: /* moby class 2662 */
    case 0xA82: /* moby class 2690 */
        return 0x29;
    case 0xC07: /* Mini Nuke Projectile */
    case 0xCE4: /* moby class 3300 */
    case 0xCE5: /* moby class 3301 */
        return 0x2A;
    case 0x87A: /* moby class 2170 */
        return 0x16;
    case 0xD01: /* moby class 3329 */
        return 0x18;
    case 0xB2E: /* moby class 2862 */
        return 0x1D;
    case 0xE64: /* moby class 3684 */
    case 0xECE: /* moby class 3790 */
        return 0x25;
    case 0x5DA: /* moby class 1498 */
        return 0x1B;
    case 0x9A9: /* moby class 2473 */
    case 0xA9B: /* moby class 2715 */
        return 0x1C;
    case 0xB58: /* Spider Bot */
    case 0xE79: /* Turret Spider Bot */
        return 0x20;
    case 0x79: /* moby class 121 */
        return 0xC;
    case 0xAC: /* Visibomb Missile */
        return 0xE;
    }

    if (object == g_hero_state.owner) {
        return g_hero_state.value;
    }
    if (*(u8 **)(object + 0xB8) != 0 && *(u8 **)(object + 0xB8) == g_hero_state.owner) {
        return g_hero_state.value;
    }
    for (i = 0; i < 0x38; i++) {
        KindRecord *rec = &g_weapon_table[g_item_slot_to_record[i]];
        s32 type = rec->kind;

        if (*(short *)(object + 0xAA) == type) {
            return i;
        }
        if (*(u8 **)(object + 0xB8) != 0 && *(short *)(*(u8 **)(object + 0xB8) + 0xAA) == type) {
            return i;
        }
    }
    return 0xFF;
}


extern int FastVectorToPackedChars(float *);
extern int FloatToInt(float);

/* Scales a direction vector into the 0..255 range around 127 and packs it.
   The unit needs "-g -ffast-math": the two max.s words need the fast-math fold of
   the float ternary, and the two nops in front of the division need the line label
   that -g puts before it (config/cflags.txt). */
/* The packed word is delivered through out, as in RAC1's
   pack_vector_xyz_with_shared_scale. The final pack call leaves its value
   in v0, but the observed callers consume the output word, not that register. */
void vec_pack_direction(float *v, int *out)
{
    float a = math_fabs(v[0]);
    float b = math_fabs(v[1]);
    float c = math_fabs(v[2]);
    float m;
    float scale;
    int n;
    float t[4];
    int r;

    m = (a > b) ? a : b;
    c = (m > c) ? m : c;
    n = FloatToInt(c * 158.73016357421875f);
    n = (n < 256) ? n : 255;
    n = (n > 0) ? n : 1;
    t[3] = (float)n;
    scale = 1.0f / ((float)n * 1.0e-04f);
    t[0] = v[0] * scale + 127.0f;
    t[1] = v[1] * scale + 127.0f;
    t[2] = v[2] * scale + 127.0f;
    r = FastVectorToPackedChars(t);
    *out = r;
    return;
}


/* func_002AE8C0 uses the quadword-copy profile in 002AE8C0-qcopy.c. */


extern float moby_get_anim_value(void *);
extern float math_round_to_decimal_places(int, float);
/* Returns true if a value is at or above the threshold but within one step of it. */
int math_is_value_within_step(char *object, float threshold)
{
    float current = math_round_to_decimal_places(4, moby_get_anim_value(object));
    float difference = current - threshold;
    float step = math_round_to_decimal_places(4, *(float *)(object + 0x48) * *(float *)(object + 0x4C));
    if (threshold <= current)
        return difference < step;
    return 0;
}


/* Sets the light color of an object from a packed color. */
void moby_set_light_color(void *moby, int color) { extern void set_moby_color(void *, unsigned char, unsigned char, unsigned char); int high = color >> 16; int middle = color >> 8; set_moby_color(moby, (unsigned char)color, (unsigned char)middle, (unsigned char)high); }

extern void moby_detach_manipulator(char *list, unsigned char *node);
extern void AttachManipulator(char *a0, char *a1, unsigned char *a2);
extern void mat_build_rotation_from_angles(unsigned char *a0, unsigned char *a1);
extern void vec_clear_128(unsigned char *);
extern float math_approach_with_velocity(float *position, float target, float *velocity,
                           float acceleration, float damping, float limit, int direction);

/* Eases a node's position and scale toward their targets each frame and adds it to the owner's list while it is moving. */
void moby_update_eased_node(char *owner, unsigned char *node, char *list, float acceleration, float damping)
{
    char *current = *(char **)(node + 0x78);
    float scale;

    if (current == 0) {
        *(char **)(node + 0x78) = owner;
    } else if (current != owner) {
        if (node[1] != 0 && (unsigned char)current[0x20] < 0x7F)
            moby_detach_manipulator(current, node);
        node[1] = 0;
        *(char **)(node + 0x78) = owner;
    }
    if (*(float *)(node + 0x60) == 0.0f && *(float *)(node + 0x64) == 0.0f &&
        *(float *)(node + 0x68) == 0.0f && *(float *)(node + 0x70) == 1.0f) {
        if (math_fabs(*(float *)(node + 0x40)) < 0.005f && math_fabs(*(float *)(node + 0x44)) < 0.005f &&
            math_fabs(*(float *)(node + 0x48)) < 0.005f) {
            if (node[1] != 0)
                moby_detach_manipulator(owner, node);
            return;
        }
    }
    math_approach_with_velocity((float *)(node + 0x40), *(float *)(node + 0x60), (float *)(node + 0x50), acceleration, damping, 0.0f, 0);
    math_approach_with_velocity((float *)(node + 0x44), *(float *)(node + 0x64), (float *)(node + 0x54), acceleration, damping, 0.0f, 0);
    math_approach_with_velocity((float *)(node + 0x48), *(float *)(node + 0x68), (float *)(node + 0x58), acceleration, damping, 0.0f, 0);
    if (node[1] == 0)
        AttachManipulator(owner, list, node);
    mat_build_rotation_from_angles(node + 0x10, (char *)(node + 0x40));
    scale = *(float *)(node + 0x70);
    *(float *)(node + 0x20) = scale;
    *(float *)(node + 0x24) = scale;
    *(float *)(node + 0x28) = scale;
    vec_clear_128(node + 0x60);
    *(float *)(node + 0x70) = 1.0f;
}

/* Branches on a float argument: when it is positive it rewrites a float in place with a helper result and sets a field at offset 24 to (helper2 * scale) + offset; otherwise it subtracts a float through a third pointer, rewrites that pointer with (helper2 * scale) and adds it back to the field. */
void math_update_wrapped_angle_offset(float *out, float *angle, float *prevOffset,
                                        float scale, float unused, float offset)
{
    if (offset > 0.0f) {
        float wrapped = func_00283B98_11(*angle);

        *angle = wrapped;
        out[6] = func_00283198_13(wrapped) * scale + offset;
    } else {
        float wrapped = func_00283B98_11(*angle);

        *angle = wrapped;
        out[6] = out[6] - *prevOffset;
        *prevOffset = func_00283198_13(*angle) * scale;
        out[6] = out[6] + *prevOffset;
    }
}

/* Scales two owner words by sampled unit-vector factors derived from two float inputs, then normalises each input in place. */
void moby_scale_owner_words_by_angles(float *out, float *p, float *q,
                                        float k1, float k2, float k3)
{
    out[60] = k1 * func_00283198_8(*p) * func_00283198_8(*q);
    out[61] = k1 * func_00283198_8(*p) * func_00283180_9(*q);
    *p = func_00283B98_8(*p, k2);
    *q = func_00283B98_8(*q, k3);
}


/* Writes three floats built from two one-float helpers and the three incoming floats: f(b)*a*f(c), g(b)*a*f(c) and g(c)*a. */
void vec_build_spherical_offset(float *p, float a, float b, float c)
{
    p[0] = func_00283180_10(b) * a * func_00283180_10(c);
    p[1] = func_00283198_10(b) * a * func_00283180_10(c);
    p[2] = func_00283198_10(c) * a;
}


typedef struct { int items[21]; } Table_002AF0A8;

extern const Table_002AF0A8 D_0026CB30;

extern void value_set_entry_by_index(int, int);

extern int ForceClaimNotice(int, int, int);

/* Plays the entry of the 21-entry table the clamped index picks; entry 3 goes through the
   other player. */
void snd_play_indexed(int index)
{
    Table_002AF0A8 table = D_0026CB30;

    if (index < 0)
        index = 0;
    if (index > 20)
        index = 20;
    if (index == 3)
        value_set_entry_by_index(table.items[3], 0xF0);
    else
        ForceClaimNotice(8, table.items[index], 0xB4);
}

/* func_002AF1D0 is matched in its own unit, src/game/002AF1D0-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* Measures how far a target is from a point and sets a flag if it is too far or too high. Returns the reach. */
float moby_measure_target_reach(char *origin, char *target, int *outOfRange,
                                       float p1, float p2, float p3, float p4)
{
    float minHeight = p4;
    float hi = p3;
    float radius;
    float reach = p2;
    float far;
    float near;
    float tmp;

    *outOfRange = 0;
    far = Fb5729173_FUN_00282E48(origin, target + 16);
    if (reach < far) {
        *outOfRange = 1;
    }

    reach = 0.0f;
    radius = Fb5729173_FUN_00283C80(Fb5729173_FUN_00283248(((float *)(target + 16))[0] - ((float *)origin)[0],
                             ((float *)(target + 16))[1] - ((float *)origin)[1]), p1);
    near = Fb5729173_FUN_00282E80(origin, target + 16);
    tmp = Fb5729173_FUN_00283C80(Fb5729173_FUN_00283248(near, ((float *)(target + 16))[2] - ((float *)origin)[2]), 0.0f);

    if (reach < hi) {
        if (hi < radius) {
            *outOfRange = 1;
        }
    }
    if (0.0f < minHeight) {
        if (minHeight < tmp) {
            *outOfRange = 1;
        }
    }

    reach = far + radius * far;
    if (Fb5729173_FUN_002ABB78(target) != 0) {
        reach = reach + 8.0f;
    }
    return reach;
}

/* func_002AF460 is in 002AA800-nearest.c. */
/* func_002AF580 is matched in its own unit, src/game/002AF580-qcopy.c. */


/* Moves a point by an object's transform and adds it to an output vector. */
void vec_add_transformed_point(float x, float y, float z, char *object, char *out)
{
    float buf[3];
    buf[0] = x;
    buf[1] = y;
    buf[2] = z;
    F10bf3d29_FUN_00283098((char *)buf, (char *)buf, object + 0xC0);
    F904cc63b_FUN_00282CC0((V4_F904cc63b *)out, (V4_F904cc63b *)out, (char *)buf);
}

/* Combines a vector with a transform, using the object's own one if none is given. */
void vec_transform_by_object_or_given(char *object, char *out, char *in, char *transform)
{
    char buf[64];

    if (transform == 0) {
        F10bf3d29_FUN_00283698(buf, object + 192);
        F10bf3d29_FUN_00283098(out, in, buf);
    } else {
        F10bf3d29_FUN_00283098(out, in, transform);
    }
}


extern void vec_fast_normalize_helper(char *, char *, float);
extern void matrix_mul_vec3(char *, char *, char *);

/* Transforms a vector, scales it and moves it into the object's space. */
void vec_transform_and_scale(char *object, char *out, char *in, char *transform, float scale)
{
    vec_transform_by_object_or_given(object, out, in, transform);
    vec_fast_normalize_helper(out, out, scale);
    matrix_mul_vec3(out, out, object + 0xC0);
}

/* Transforms a vector, sets its height and moves it into the object's space. */
void vec_transform_and_set_height(char *object, char *out, char *in, char *transform, float z)
{
    vec_transform_by_object_or_given(object, out, in, transform);
    *(float *)(out + 8) = z;
    matrix_mul_vec3(out, out, object + 0xC0);
}
