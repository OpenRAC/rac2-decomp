#include "common.h"

#define RAC2_T_OBJ_F7B2F1854

typedef struct {
    unsigned char pad[0x1FB0];
    float limit_x;
    float limit_y;
} Glob_199E20;

typedef struct {
    unsigned char pad[0x50];
    float f50;
    float f54;
} Obj_32FDD0;

typedef int TI128 __attribute__((mode(TI)));

typedef struct Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout {
    unsigned char unknown_00[8];
    float first_0;
    float second_0;
    float first_1;
    float second_1;
    float first_2;
    float second_2;
    float first_3;
    float second_3;
} Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout;

typedef struct Obj_F7b2f1854 {
    int *f0;
    int *f4;
    int *f8;
    int *f12;
    int *f16;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
} Obj_F7b2f1854;

typedef struct {
    char reserved[0x30];
    void *table;
} Constructor_3361A8;

extern Glob_199E20 g_hero_state;

extern float g_stick_length __attribute__((sda));

extern float g_hero_position[];

extern void F7242f0a4_FUN_00282D30(char *out, void *source, float value);

extern int F7242f0a4_FUN_00334730(char *buffer, int mode);

extern f32 math_random_signed_float_range(f32 low, f32 high);
extern f32 g_default_effect_vector[] __attribute__((sda));

typedef union { TI128 quad; float v[4]; } EffectVector;

extern unsigned char *g_particle_texture_table[];                     /* the texture table */
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_below(int);
extern unsigned char *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);

typedef struct {
    TI128 position;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
} State_332440;

/* The EE assigns the integer and FP banks independently: this is func_002FED90(obj, src, x, y, z)
   with its FP arguments set up first, as retail does. */
extern int part_alloc_effect_slot(void *obj, f32 x, f32 y, f32 z, void *src);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void cam_compute_view_direction(void *, void *, int);
extern char *CreateMoby(int);

extern void F7242f0a4_FUN_00334710(int value, char *buffer);

extern void F7242f0a4_FUN_00282CC0(char *first, char *second, char *third);

extern float F7242f0a4_FUN_00282DB0(void *owner, char *buffer);

extern int F7242f0a4_D_001B53A0[];

extern s32 FastTweenColor(s32, s32, f32);

extern int *object_get_fourth_field(unsigned char *field);

extern void pool_free_cell(int a, int b);

extern int *F7b2f1854_FUN_00336E40(int n);

extern int *F7b2f1854_FUN_00336DA8(int size, int *p);

extern void F7b2f1854_FUN_00335E68(Obj_F7b2f1854 *o, int v);

extern void F36efd143_FUN_00335FC8(char *a);

extern void *F36efd143_FUN_00336E40(char *a);

extern void *F36efd143_FUN_00336DA8(int size, void *b);

extern void F081de6c9_FUN_00335FC8(char *s, int a1, char *a2);

extern void *F081de6c9_FUN_00336E40(int x);

extern int *F081de6c9_FUN_00336DA8(int n, int x);

extern int g_moby_slot_ids[] __attribute__((sda));

extern char g_str_moby_release_debug[];

extern void STUB_printf(void *);

extern unsigned short *g_moby_group_lists[];

extern char *g_moby_pool_start __attribute__((sda));

extern void part_draw_spinning_billboard_pair(void *, void *, int, float);

extern char g_active_camera[];

extern void moby_clear_visible_flags(void);

extern void euler_to_matrix(void *, void *);

extern void copy_matrix3x4(void *, void *);

extern void vec_scale_to_length(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern void moby_clear_visible_flags(void);

extern char g_object_free_type_table[] __attribute__((sda));

extern void ui_nop_a(void *);

extern void assert_fail_abort(char *, int, char *);

extern char g_str_assert_file[];

extern char g_str_assert_expr[];

extern char g_object_type_table[] __attribute__((sda));

extern void object_reset_type_and_free(void *, int);

extern int g_hud_mode __attribute__((sda));

extern char g_object_base_table[] __attribute__((sda));

extern char g_object_base_table[] __attribute__((sda));

extern void ui_nop_a(void *);

extern void *object_init_base(void *);

extern char g_object_derived_table_a[] __attribute__((sda));

extern void *table_find_by_id(int, int);

extern char g_object_derived_table_b[] __attribute__((sda));

extern char g_object_derived_table_c[] __attribute__((sda));

/* Measured partial layouts; original type and game roles are unknown. */

/* func_0034CA68: owner ABI/declaration review retained. */

#ifndef RAC2_T_OBJ_F7B2F1854
#endif

/* func_0032EB28 uses small data in 0032EB28-update-g8.c. */



/* func_0032F598 is defined in 0032EB28-turret-g8.c. */


/* func_0032FEA8 uses small data in 0032EB28-g8.c. */


/* func_0032FFD8 is defined in its own sibling unit. */

/* func_00330150 is defined in 0032EB28-probe-g8.c. */

/* func_003304D8 is defined in 0032EB28-ground-g8.c. */


/* func_00330BC0 uses small data in 0032EB28-g8.c. */

/* func_00330CA0 is in 0032EB28-damage-g8.c. */


/* func_00330E48 is in 0032EB28-g8.c. */

/* func_00330EC0 is in 0032EB28-ring-g8.c. */

/* func_00331238 is in 0032EB28-spark.c. */


/* Sprays a burst of small flashing sparks around a point, pushed along a direction. */
void part_spawn_spark_burst_2(TI128 *a0, void *dir)
{
    EffectVector base;
    float vel[4];
    float pos[3];
    float size = 84000.0f;
    int i;
    int rnd;
    unsigned char *p;

    qcopy(&base, a0);
    FastVecScale(vel, dir, 0.5f);
    FastVecAdd(&base, &base, vel);
    i = 8;
    do {
        i--;
        pos[0] = base.v[0] + math_random_signed_float_range(0.0f, 0.1f);
        pos[1] = base.v[1] + math_random_signed_float_range(0.0f, 0.1f);
        pos[2] = base.v[2] + math_random_signed_float_range(0.0f, 0.1f);
        rnd = math_random_int_below(0xFF);
        p = part_spawn_gravity_fade(pos, g_default_effect_vector, 10, 0x407FFF, rnd, 0x7F, 0, size, size, 0.0f, 1);
        if (p != 0)
            p[2] = g_particle_texture_table[92][5];
        p = part_spawn_gravity_fade(pos, g_default_effect_vector, 10, 0x406080, rnd, 0x7F, 0, size, size, 0.0f, 1);
        if (p != 0)
            p[2] = g_particle_texture_table[53][0];
    } while (i >= 0);
}

extern s32 FloatToInt(f32 value);
extern u8 *part_spawn_burst(f32 *pos, f32 *sym, s32 a2, s32 a3, u32 color, s32 alpha, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern u8 *g_part_tex_flash_puffs_table;
/* Spawns a couple of puffs and one bright flash near a position. */
void part_spawn_flash_puffs(f32 *pos, f32 scale)
{
    f32 v[3];
    f32 size = scale * 6300.0f;
    u8 *effect;
    s32 i;
    for (i = 1; i >= 0; i--) {
    v[0] = pos[0] + math_random_signed_float_range(0.0f, 0.04f);
    v[1] = pos[1] + math_random_signed_float_range(0.0f, 0.04f);
    v[2] = pos[2] + math_random_signed_float_range(0.0f, 0.04f);
    part_spawn_burst(v, g_default_effect_vector, 15, 0x5F, 0x7F7F7F, FloatToInt(math_random_signed_float_range(1.0f, 3.0f)), size, 500.0f, 1.0f, 0.0f, 0.0f);
    }
    effect = part_spawn_burst(v, g_default_effect_vector, 15, 0x7F, 0x407FFF, FloatToInt(math_random_signed_float_range(1.0f, -1.0f)), size * 0.8f, 500.0f, 1.0f, 0.0f, 0.0f);
    if (effect != 0) {
        effect[2] = g_part_tex_flash_puffs_table[5];
    }
}

/* func_00331718 uses small data in 0032EB28-g8.c. */



/* Removes an id from the list of 16 slots, or reports a problem if it is not there. */
void moby_release_slot_by_id(int slot_id) {
    int i;

    for (i = 0; i < 16; i++) {
        if (g_moby_slot_ids[i] == slot_id) {
            g_moby_slot_ids[i] = 0;
            return;
        }
    }
    STUB_printf(g_str_moby_release_debug);
}

/* Creates a new game object at a position and sets up its direction and starting values. */
char *moby_spawn_directed(void *a0, void *a1, void *a2)
{
    TI128 localA;
    TI128 localB;
    char *object;
    State_332440 *state;
    int result;

    cam_compute_view_direction(a1, &localA, 1);
    object = CreateMoby(0xEAA /* moby class 3754 */);
    if (object != 0) {
        state = *(State_332440 **)(object + 0x68);
        state->f10 = 0x50;
        *(unsigned char *)(object + 0x30) = 0xFF;
        *(short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x20) = 0;
        qcopy(object + 0x10, a1);
        qcopy(state, a2);
        state->f18 = 0;
        state->f14 = 0;
        vec_scale_to_length(&localB, a2, 1.0f);
        qcopy(object + 0xC0, &localB);
        FastVecCross(object + 0xD0, object + 0xC0, &localA);
        vec_scale_to_length(object + 0xD0, object + 0xD0, 1.0f);
        FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
        *(float *)(object + 0xCC) = *(float *)(object + 0xDC) = *(float *)(object + 0xEC) = 0.0f;
        result = part_alloc_effect_slot(object, 1.0f, 1.0f, 1.0f, 0);
        state->f1C = result;
        state->f20 = (int)a0;
    }
    return object;
}




/* func_003334B0 is in 0032EB28-trigger-g8.c. */

/* func_00333AF8 is in 0032EB28-beam.c. */


/* Sets one byte of private data on every object in a list. */
void moby_set_entry_list_flag_byte(int index, int value)
{
    unsigned short *list = g_moby_group_lists[index];
    if (list != 0) {
        unsigned short *entry = list;
        int key;
        do {
            char *object = (char *)(((*entry & 0x7FFF) << 8) + (unsigned int)g_moby_pool_start);
            *(unsigned char *)(*(char **)(object + 0x68) + 0x15) = value;
            key = *(short *)entry++;
        } while (key >= 0);
    }
}

/* Calls a helper on an object when it is in state 2 or 3 and has its extra data set. */
void moby_update_attached_effect_by_state(char *object)
{
    char *data = *(char **)(object + 0x68);
    unsigned int mode = *(unsigned char *)(object + 0x20);
    if (mode - 2 < 2 && *(int *)(data + 0x40) != 0)
        part_draw_spinning_billboard_pair(data + 0x10, data + 0x20, 0, 1.0f);
}


/* The table func_00334100 walks: 0x30-byte entries with the searched id at +0x18.
   Its address differs from level to level, so the symbol carries no address. */
typedef struct {
    unsigned char pad_34100[0x18];
    int id_34100;
    unsigned char pad2_34100[0x14];
} Entry_34100;

extern Entry_34100 ref_L00_00334100_00[30];

/* Finds the table entry with a given id, or returns -1 if none matches. */
s32 moby_find_entry_index_by_id(s32 id)
{
    s32 i;
    s32 found;

    found = -1;
    for (i = 0; i < 30; i++) {
        if (ref_L00_00334100_00[i].id_34100 == id) {
            found = i;
            break;
        }
    }
    return found;
}


/* func_00334710 is matched in 00334710-rc2.c. */




typedef int L_34730TI __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; short h[0x1300]; int i[0x980]; float f[0x980]; } L_34730Hero;
extern L_34730TI hero_copy_vector_to_out(int, L_34730TI *);
extern int CollLine(void *, void *, int, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern char g_camera_follow_state[];
extern float g_coll_hit_position[];

/* Works out the camera spot to use, checking whether something blocks the view. */
int cam_resolve_position(float *out, int flag)
{
    float base[4] __attribute__((aligned(16)));
    float near[4] __attribute__((aligned(16)));
    float far[4] __attribute__((aligned(16)));
    float ofs[4] __attribute__((aligned(16)));
    L_34730Hero *hero = (L_34730Hero *)&g_hero_state;
    float f;
    char *cam = g_camera_follow_state;

    if (hero->h[0x34C / 2] == 0) {
        hero_copy_vector_to_out(((int *)cam)[-4], (L_34730TI *)out);
        return 1;
    }
    hero_copy_vector_to_out(((int *)cam)[-4], (L_34730TI *)base);
    f = hero->f[0x31C / 4];
    if (f >= 30.0f || flag == 0) {
        FastVecScale(ofs, cam + 0x30, 0.2f);
        FastVecAdd(near, base, ofs);
        FastVecScale(ofs, cam + 0x30, -30.0f);
        FastVecAdd(far, base, ofs);
        if (CollLine(near, far, 0x12, (void *)hero->i[0x2290 / 4], 0) != 0) {
            qcopy(out, g_coll_hit_position);
            return 0;
        }
        qcopy(out, base);
        return -1;
    }
    FastVecScale(near, cam + 0x30, -f);
    FastVecAdd(out, base, near);
    return 1;
}



/* Computes a camera offset and stores it in the owner. */
void cam_compute_offset(void *owner, int flag, float value)
{
    char buffer[32];
    int *root = F7242f0a4_D_001B53A0;

    F7242f0a4_FUN_00282D30(buffer, root + 8, value);
    if (flag)
        F7242f0a4_FUN_00334730(buffer + 16, 1);
    else
        F7242f0a4_FUN_00334710(root[-4], buffer + 16);
    F7242f0a4_FUN_00282CC0(buffer, buffer, buffer + 16);
    F7242f0a4_FUN_00282D30(owner, root + 12, F7242f0a4_FUN_00282DB0(root + 12, buffer));
}


typedef int TI __attribute__((mode(TI)));
extern void *D_0026E810[7];
extern TI hero_copy_vector_to_out(int, TI *);
extern void FastVecAdd(void *, void *, void *);

/* Adds an offset vector to a point, choosing the offset by mode. */
int cam_add_offset_by_mode(char *self, void *src, void *dst, int mode)
{
    static void *arms[7] = {&&transformed, &&direct, &&zero, &&zero, &&zero, &&zero, &&zero};
    TI local;
    int ret = 1;
    char *vector = *(char **)(self + 0x70) + 0x60;
    if ((unsigned int)(mode - 1) >= 7) goto direct;
    goto *D_0026E810[mode - 1];
zero:
    FastVecAdd(dst, src, vector);
    ret = 0;
    goto done;
transformed:
    hero_copy_vector_to_out((int)self, &local);
    FastVecAdd(dst, src, &local);
    goto done;
direct:
    FastVecAdd(dst, src, vector);
done:
    return ret;
}

/* func_00335370 is defined in 00335370-copy.c. */

/* func_003353C8 uses the quadword-copy profile in 0032EB28-qcopy.c. */



/* Moves camera 5 to a new position/rotation; mode 3 starts a transition back from the
   previous pose, modes 2 and 3 store the transition duration. */
/* func_00335438 is defined in its own sibling unit. */

/* Sets up the camera for the chosen mode (reset, hold or follow). */
void cam_set_mode_state(int mode)
{
    struct { float scaled[4]; float negative[4]; float matrix[16]; } work;
    char *state = g_active_camera;
    char *camera = *(char **)(state + 0x190);
    moby_clear_visible_flags();
    if (mode == 0) {
        char *position = camera + 0x30;
        euler_to_matrix(work.matrix, g_hero_position + 4);
        copy_matrix3x4(camera, work.matrix);
        vec_scale_to_length(work.negative, work.matrix, -1.0f);
        vec_scale_to_length(work.scaled, work.matrix + 8, 1.2f);
        FastVecAdd(position, g_hero_position, work.scaled);
        FastVecAdd(position, position, work.negative);
        *(short *)(*(char **)(state + 0x190) + 0x8A) = 1;
    } else if (mode == 2) {
        state[0x293] = 0;
        *(short *)(camera + 0x7E) = 2;
        *(float *)(state + 0x2B4) = 0.018f;
        *(float *)(state + 0x2A8) = 0.018f;
    } else if (mode == 1) {
        *(short *)(camera + 0x7E) = 3;
    } else if (mode == 4) {
        state[0x293] = 0;
        *(short *)(camera + 0x7E) = 5;
        *(float *)(state + 0x2B4) = 0.018f;
        *(float *)(state + 0x2A8) = 0.018f;
    }
}

/* Calls the camera helper with no extra work. */
void cam_call_helper(void) {
    moby_clear_visible_flags();
}


/* Resets an object and frees it when the flag asks for it. */
void object_reset_type_and_free(void *object, int flags) {
    *(void **)((char *)object + 4) = g_object_free_type_table;
    if (flags & 1)
        ui_nop_a(object);
}

/* Fills four numbers from a blend factor and its opposite. */
void math_fill_blend_weights(void *unused, char *out, float factor) {
    if (out == 0)
        assert_fail_abort(g_str_assert_file, 61, g_str_assert_expr);
    *(float *)(out + 0x0) = factor;
    *(float *)(out + 0x4) = factor * 0.5f;
    *(float *)(out + 0x8) = 1.0f - factor;
    *(float *)(out + 0xC) = (1.0f - factor) * 0.5f;
}


/* func_00335960 is defined in its own sibling unit. */

/* Sets the type pointer of an object and returns it. */
void *object_init_type_pointer(void *object) {
    *(void **)object = g_object_type_table;
    return object;
}

/* Resets an object type pointer and frees it when the flag asks for it. */
void object_destroy_with_type(void *object, int flags) {
    *(void **)object = g_object_type_table;
    if (flags & 1)
        ui_nop_a(object);
}

/* Interpolate four scalar float components from separate input arrays using (1.0f - factor) * first + factor * second, writing each component to the destination. */
void math_lerp_float4(float factor, void *context,
                                   float *destination,
                                   const float *first, const float *second)
{
    float complement = 1.0f - factor;
    destination[0] = complement * first[0] + factor * second[0];
    destination[1] = complement * first[1] + factor * second[1];
    destination[2] = complement * first[2] + factor * second[2];
    destination[3] = complement * first[3] + factor * second[3];
}

/* calls one four-argument helper four times, left[i] and right[i] with the float scale, storing each result into dst[i]; the first pointer parameter is unused. */
void math_blend_four(s32 *unused, s32 *dst, s32 *left, s32 *right, f32 scale) {
    dst[0] = FastTweenColor(left[0], right[0], scale);
    dst[1] = FastTweenColor(left[1], right[1], scale);
    dst[2] = FastTweenColor(left[2], right[2], scale);
    dst[3] = FastTweenColor(left[3], right[3], scale);
}



/* Interpolate four scalar float components from interleaved endpoint pairs at source offsets 0x08 through 0x24 using (1.0f - factor) * first + factor * second, writing each component to the destination. */
void math_lerp_interleaved_float4(float factor,
                                     const Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout *source,
                                     float *destination)
{
    float complement = 1.0f - factor;
    destination[0] = complement * source->first_0 + factor * source->second_0;
    destination[1] = complement * source->first_1 + factor * source->second_1;
    destination[2] = complement * source->first_2 + factor * source->second_2;
    destination[3] = complement * source->first_3 + factor * source->second_3;
}


/* Passes the call on to the base cleanup. */
void object_destroy_wrapper(void *object, int flags) {
    object_reset_type_and_free(object, flags);
}

/* func_00335DC0 uses small data in 0032EB28-g8.c. */

/* Returns a stored number. */
int object_get_stored_counter(void) {
    return g_hud_mode;
}

/* Measured target: byte-identical across all 27 levels. */
float *object_get_first_field(u8 *a0) { return *(s32 *)(a0 + 0x0); }

/* Measured target: byte-identical across all 27 levels. */
float *object_get_second_field(u8 *a0) { return *(s32 *)(a0 + 0x4); }

/* Measured target: byte-identical across all 27 levels. */
int *object_get_fourth_field(u8 *a0) { return *(s32 *)(a0 + 0xc); }

/* Stores four numbers in the first array of an object. */
void object_set_first_float4(u8 *a0,f32 f0,f32 f1,f32 f2,f32 f3) {
 (*(f32 **)a0)[0]=f0;(*(f32 **)a0)[1]=f1;
 (*(f32 **)a0)[2]=f2;(*(f32 **)a0)[3]=f3;
}


/* Turns a stored on/off value to 1 or 0. */
void object_set_flag_value(u8 *object, s32 enable) {
 f32 *value=*(f32 **)(object+0x10);
 *value=(enable!=0)?1.0f:0.0f;
}

/* Tells whether the stored value is above zero. */
s32 object_is_flag_positive(u8 *object) {
 return 0.0f<**(f32 **)(object+0x10);
}

/* Compares the second argument with the word at offset 4 of the object; when they differ, and when the word at offset 44 is non-zero while the word at offset 24 is zero, it calls a two-argument helper with those two words, marks offset 24 with 1, and finally writes the second argument into offset 4. */
void object_change_first_value(char *object, int new_value)
{
    if (new_value != *(int *)(object + 4)) {
        if (*(int *)(object + 44) != 0 && *(int *)(object + 24) == 0) {
            pool_free_cell(*(int *)(object + 44), *(int *)(object + 4));
            *(int *)(object + 24) = 1;
        }
        *(int *)(object + 4) = new_value;
    }
}


/* Changes a value and releases the old one if needed. */
void object_change_second_value(char *object, int value) {
    if (value != *(int *)(object + 0x10)) {
        if (*(int *)(object + 0x2C) != 0 && *(int *)(object + 0x24) == 0) {
            pool_free_cell(*(int *)(object + 0x2C), *(int *)(object + 0x10));
            *(int *)(object + 0x24) = 1;
        }
        *(int *)(object + 0x10) = value;
    }
}

/* Stores four numbers in the second array of an object. */
void object_set_second_float4(u8 *a0,f32 f0,f32 f1,f32 f2,f32 f3) {
 (*(f32 **)(a0+4))[0]=f0;(*(f32 **)(a0+4))[1]=f1;
 (*(f32 **)(a0+4))[2]=f2;(*(f32 **)(a0+4))[3]=f3;
}

/* Sets the type pointer of an object and returns it. */
void *object_init_base(void *object) {
    *(void **)((char *)object + 0x30) = g_object_base_table;
    return object;
}

/* Sets up an object by allocating five small arrays of zeros. */
void object_alloc_float4_arrays(Obj_F7b2f1854 *o, int a1, int count)
{
    int *p;
    int n;

    o->f44 = count;
    if (count != 0) {
        p = F7b2f1854_FUN_00336DA8(16, F7b2f1854_FUN_00336E40(count));
        n = o->f44;
        o->f0 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = F7b2f1854_FUN_00336DA8(16, F7b2f1854_FUN_00336E40(n));
        n = o->f44;
        o->f8 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = F7b2f1854_FUN_00336DA8(16, F7b2f1854_FUN_00336E40(n));
        n = o->f44;
        o->f4 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = F7b2f1854_FUN_00336DA8(16, F7b2f1854_FUN_00336E40(n));
        n = o->f44;
        o->f12 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = F7b2f1854_FUN_00336DA8(16, F7b2f1854_FUN_00336E40(n));
        o->f16 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;
    }
    o->f40 = a1;
    o->f32 = 0;
    o->f20 = 0;
    o->f28 = 0;
    o->f24 = 0;
    o->f36 = 0;
    F7b2f1854_FUN_00335E68(o, 1);
}


/* Cleans up an object and frees its arrays. */
void object_destroy_array(char *object, int flags)
{
    *(char **)(object + 0x30) = g_object_base_table;
    if (*(int *)(object + 0x2C)) {
        if (*(int *)(object + 0x14) == 0)
            pool_free_cell(*(int *)(object + 0x2C), *(int *)object);
        if (*(int *)(object + 0x1C) == 0)
            pool_free_cell(*(int *)(object + 0x2C), *(int *)(object + 8));
        if (*(int *)(object + 0x18) == 0)
            pool_free_cell(*(int *)(object + 0x2C), *(int *)(object + 4));
        if (*(int *)(object + 0x20) == 0)
            pool_free_cell(*(int *)(object + 0x2C), *(int *)(object + 12));
    }
    if (flags & 1)
        ui_nop_a(object);
}

/* Builds an object and sets its table pointer. */
Constructor_3361A8 *object_construct_derived_a(Constructor_3361A8 *object) {
    object_init_base(object);
    object->table = g_object_derived_table_a;
    return object;
}

/* Sets up an object with two more arrays and default values. */
void object_init_derived_arrays(char *obj)
{
    int *p;
    int x;
    F36efd143_FUN_00335FC8(obj);
    if (*(int *)(obj + 44) != 0) {
        p = (int *)F36efd143_FUN_00336DA8(16, F36efd143_FUN_00336E40(*(int *)(obj + 44)));
        *(int *)(obj + 52) = (int)p;
        x = *(int *)(obj + 44);
        p[1] = 0; p[2] = 0; p[3] = 0; p[0] = 0;
        p = (int *)F36efd143_FUN_00336DA8(16, F36efd143_FUN_00336E40(x));
        *(int *)(obj + 56) = (int)p;
        {
            float *f = (float *)*(int *)(obj + 4);
            p[1] = 0;
            p[2] = 0;
            p[3] = 0;
            p[0] = 0;
            f[0] = 1.0f;
            *(float *)(*(int *)(obj + 4) + 4) = 1.0f;
            *(float *)(*(int *)(obj + 4) + 8) = 1.0f;
        }
    }
    *(int *)(obj + 68) = 0;
    *(int *)(obj + 72) = 0;
}



/* Measured target: byte-identical across all 27 levels. */
float *object_get_field_a(u8 *a0) { return *(s32 *)(a0 + 0x38); }

/* Stores the result of a helper call in the object. */
void object_set_helper_result(char *object, int first, int second) {
    *(int *)(object + 0x40) = table_find_by_id(first, second);
}

/* Writes a number to the object value. */
void object_set_value_float(u8 *object, f32 value) { f32 *target = *(f32 **)(object + 0x38); *target = value; }

/* Builds an object and sets its table pointer. */
Constructor_3361A8 *object_construct_derived_b(Constructor_3361A8 *object) {
    object_init_base(object);
    object->table = g_object_derived_table_b;
    return object;
}

/* Sets up an object and fills in its starting values. */
void object_init_derived_b(char *object, int a1, int a2, int a3, int a4) {
    object_alloc_float4_arrays((Obj_F7b2f1854 *)object, a3, a4);
    *(int *)(object + 0x3C) = a1;
    *(int *)(object + 0x34) = a2;
    *(int *)(object + 0x40) = 100;
    *(int *)(object + 0x44) = 0x80000000;
}


/* lot12 -- measured bodies with sizes recorded in the catalogue. */
/* Stores two numbers in the first slots of the array. */
void object_set_first_pair(u8 *object, s32 first, s32 second) {
    *(s32 *)*(u8 **)(object + 0xc) = first;
    *(s32 *)(*(u8 **)(object + 0xc) + 0x4) = second;
}

/* Stores two numbers in the third and fourth slots of the array. */
void object_set_second_pair(u8 *object, s32 first, s32 second) {
    *(s32 *)(*(u8 **)(object + 0xc) + 0x8) = first;
    *(s32 *)(*(u8 **)(object + 0xc) + 0xc) = second;
}

/* Sets the top byte of the first two numbers in the array. */
void object_set_first_pair_top_bytes(u8 *a0, s32 a1, s32 a2) {
    u8 *o = a0;
    *(u32 *)*(u8 **)(o + 0xC) = (*(u32 *)*(u8 **)(o + 0xC) & 0x00FFFFFF) | (u32)(a1 << 24);
    *((u32 *)*(u8 **)(o + 0xC) + 1) = (*((u32 *)*(u8 **)(o + 0xC) + 1) & 0x00FFFFFF) | (u32)(a2 << 24);
}

/* Sets the top byte of the third and fourth numbers in the array. */
void object_set_second_pair_top_bytes(u8 *a0, s32 a1, s32 a2) {
    u8 *o = a0;
    *((u32 *)*(u8 **)(o + 0xC) + 2) = (*((u32 *)*(u8 **)(o + 0xC) + 2) & 0x00FFFFFF) | (u32)(a1 << 24);
    *((u32 *)*(u8 **)(o + 0xC) + 3) = (*((u32 *)*(u8 **)(o + 0xC) + 3) & 0x00FFFFFF) | (u32)(a2 << 24);
}

/* func_00336548 is defined in 0032EB28-math-g8.c. */

/* Builds an object and sets its table pointer. */
Constructor_3361A8 *object_construct_derived_c(Constructor_3361A8 *object) {
    object_init_base(object);
    object->table = g_object_derived_table_c;
    return object;
}


/* Sets up an object and fills in its default sizes. */
void object_init_derived_c(char *s1, int a1, char *a2)
{
    F081de6c9_FUN_00335FC8(s1, a1, a2);
    if (a2 != 0) {
        int *v = F081de6c9_FUN_00336DA8(16, F081de6c9_FUN_00336E40(*(int *)(s1 + 44)));

        *(int **)(s1 + 52) = v;
        v[1] = 0;
        v[2] = 0;
        v[3] = 0;
        v[0] = 0;
    }
    ((int *)*(int **)(s1 + 52))[0] = 0;
    ((int *)*(int **)(s1 + 52))[1] = 0;
    *(float *)(*(char **)s1 + 0) = 100.0f;
    *(float *)(*(char **)s1 + 4) = 100.0f;
    *(float *)(*((char **)s1 + 1) + 0) = 64.0f;
    *(float *)(*((char **)s1 + 1) + 4) = 64.0f;
    *(int *)(s1 + 56) = 0;
}

/* Measured target: byte-identical across all 27 levels. */
void *object_get_field_b(u8 *a0) { return *(s32 *)(a0 + 0x34); }
