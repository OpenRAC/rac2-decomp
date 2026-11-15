#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    char position[16];
    char pad10[0x25C];
    char *attached;
    char pad270[0x2024];
    int state;
} PlayerState;
extern PlayerState g_hero_state;
typedef struct {
    u8 header[0x464];
    u8 entries[0];
} TriggerTable;
extern TriggerTable D_L03_0021EA30;
extern u8 D_0019B4A8[];
extern char D_L03_001A8F20[] __attribute__((sda));
extern float D_L03_001B0460 __attribute__((sda));
extern float D_L03_001B0464 __attribute__((sda));
extern float D_L03_001B0468 __attribute__((sda));
extern char D_L03_001B0470[] SDATA(D_L03_001B0470);
extern int g_current_map_index MACRO_ADDR;
extern int g_frame_l03_counter;
extern char *part_find_owned_effect_slot(char *, int, int);
extern void moby_set_state(char *, int, int);
extern void func_PAL_002B1588(int, int);
extern int PlayMobySound(int, int, char *);
extern void vec_copy_helper_a(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void vec_set_direction_with_complement(void *, void *, float);
extern void func_PAL_00273818(char *, int, int, void *, void *, u8, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void mat_get_euler_angles(void *, void *);
extern void func_PAL_002B15D8(char *, int, void *, u8, float, float, float, float);
extern void vec_random_direction(void *, float, float);
extern void func_PAL_L03_003D4480(char *);
extern int math_random_int_below(int), func_PAL_00273A10(char *);
extern char *func_PAL_002735D0(char *, int, int, int, void *, void *, void *, u8, float, float);
extern float math_fast_sin_or_cos_b(float), FastVecDot(void *, void *), FastVecLength(void *);
extern float math_random_signed_float_range(float, float), math_random_float_range(float, float), math_random_angle(void);

/* Initializes the triggered motion, sheds debris while moving, and emits the
 * final twenty-object burst when the collision magnitude reaches its threshold. */
void func_PAL_L03_003D3220(char *obj)
{
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float temporary[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    char *vars = *(char **)(obj + 0x68);
    char *collision = part_find_owned_effect_slot(obj, 0x10000, 0);
    int i, dialogue;
    float value;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (!collision && !(g_hero_state.state == 0x10 && g_hero_state.attached == obj))
            break;
        dialogue = *(int *)(vars + 0x84);
        if (dialogue >= 0) {
            u16 id = *(u16 *)(obj + 0xB2);
            if (!D_L03_0021EA30.entries[(s16)id]) {
                int count = D_0019B4A8[((s16)id >> 1) + (g_current_map_index << 10)];
                if (!((id & 1) ? ((count >> 4) & 7) : (count & 7)))
                    func_PAL_002B1588(dialogue + 0xE77, 0x96);
            }
        }
        if (*(u16 *)(obj + 0xB2) & 1) {
            u8 *cell = D_0019B4A8 +
                (((short)*(u16 *)(obj + 0xB2) >> 1) + (g_current_map_index << 10));
            if (((*cell >> 4) & 7) != 7)
                *cell += 16;
        } else {
            u8 *cell = D_0019B4A8 +
                (((short)*(u16 *)(obj + 0xB2) >> 1) + (g_current_map_index << 10));
            if ((*cell & 7) != 7)
                ++*cell;
        }
        PlayMobySound(0, 0, obj);
        vec_copy_helper_a(velocity);
        if (collision)
            vec_fast_normalize_helper(target, collision + 0x10, D_L03_001B0460 * 0.020000001f);
        else
            vec_fast_normalize_helper(target, g_hero_state.position, D_L03_001B0460 * 0.020000001f);
        target[2] = D_L03_001B0464 * 0.020000001f;
        FastVecCross(position, velocity, target);
        value = math_fast_sin_or_cos_b(D_L03_001B0468 * 0.0003490659f);
        vec_set_direction_with_complement(position, position, value * 0.5f);
        func_PAL_00273818(obj, 0, -1, target, position, 255, 15.0f);
        *(int *)(obj + 0x98) = *(int *)(*(char **)(obj + 0x24) + 0x10);
        moby_set_state(obj, 2, -1);
        break;
    case 2:
        vec_copy_helper_a(target);
        value = FastVecDot(obj + 0xE0, target);
        if ((g_frame_l03_counter & 3) == (((int)obj >> 8) & 3) && value < 0.9f && value > 0.1f) {
            int kind;
            char *child;

            i = math_random_int_below(4);
            matrix_mul_vec3(position, D_L03_001B0470 + (i << 4), obj + 0xC0);
            FastVecAdd(position, position, obj + 0x10);
            kind = 0x9D7;
            if (math_random_int_below(2))
                kind = 0x9D4;
            *(Quad *)temporary = 0;
            temporary[0] = math_random_signed_float_range(0, 2);
            temporary[1] = math_random_signed_float_range(0, 2);
            temporary[2] = math_random_float_range(4, 8);
            *(Quad *)velocity = *(Quad *)temporary;
            value = FastVecLength(velocity);
            vec_scale_to_length(velocity, velocity, value * 0.020000001f);
            matrix_mul_vec3(velocity, velocity, obj + 0xC0);
            *(Quad *)angles = 0;
            angles[0] = math_random_angle();
            angles[1] = math_random_angle();
            angles[2] = math_random_angle();
            *(Quad *)temporary = *(Quad *)angles;
            child = func_PAL_002735D0(obj, 0, kind, -1, position, temporary, velocity, 255,
                math_random_signed_float_range(45, 180) * 0.0003490659f, 20.0f);
            if (child) {
                *(void (**)(char *))(child + 0x64) = func_PAL_L03_003D4480;
                PlayMobySound(1, 0, obj);
            }
        }
        if (func_PAL_00273A10(obj))
            moby_set_state(obj, 3, -1);
        break;
    case 3:
        break;
    case 4:
        return;
    }
    if (collision && *(float *)(collision + 0x2C) >= 3.0f) {
        moby_set_state(obj, 4, -1);
        *(int *)(obj + 0x98) = 0;
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & ~0x1000;
        mat_get_euler_angles(obj + 0xC0, obj + 0xF0);
        func_PAL_002B15D8(obj, 0x1FF, D_L03_001A8F20, 255, 3.0f, 5.0f, 5.0f, 10.0f);
        *(Quad *)target = 0;
        target[2] = 0.5f;
        matrix_mul_vec3(target, target, obj + 0xC0);
        FastVecAdd(target, target, obj + 0x10);
        for (i = 0x13; i >= 0; --i) {
            int kind;
            char *child;

            vec_random_direction(position, 0, 0.5f);
            FastVecAdd(position, position, target);
            *(Quad *)temporary = 0;
            temporary[0] = math_random_signed_float_range(0, 2);
            temporary[1] = math_random_signed_float_range(0, 2);
            temporary[2] = math_random_float_range(5, 12);
            *(Quad *)velocity = *(Quad *)temporary;
            value = FastVecLength(velocity);
            vec_scale_to_length(velocity, velocity, value * 0.020000001f);
            kind = 0x9D7;
            if (math_random_int_below(2))
                kind = 0x9D4;
            *(Quad *)angles = 0;
            angles[0] = math_random_angle();
            angles[1] = math_random_angle();
            angles[2] = math_random_angle();
            *(Quad *)temporary = *(Quad *)angles;
            child = func_PAL_002735D0(obj, 0, kind, -1, position, temporary, velocity, 255,
                math_random_signed_float_range(45, 180) * 0.0003490659f, 20.0f);
            if (child)
                *(void (**)(char *))(child + 0x64) = func_PAL_L03_003D4480;
        }
    }
}
