#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
/* The cutscene record: the group of L19_0042A860.c (entity count at 0x44,
 * entity list at 0x18C) with its state and frame counter at 0x30. */
typedef struct {
    u8 pad0[0x30];
    s32 state;
    s32 frame;
    u8 pad38[0x44 - 0x38];
    s16 count;
    u8 pad46[0x18C - 0x46];
    char *items[1]; /* bounded by count */
} L19Cutscene;
extern L19Cutscene D_L19_001BD740;
typedef struct { u8 prefix[0x160]; float strength; u8 unknown164[4]; int ticks, mode; } CameraShakeView;
extern CameraShakeView D_L19_001B9900;
/* Separate scalars: only a plain symbol operand is one instruction to cc1, so
 * only these reach the delay slots where retail has their $gp forms. */
extern int g_current_map_index MACRO_ADDR;
extern char *D_L19_001B2814 MACRO_ADDR;
extern Vec D_L19_001B2820 MACRO_ADDR;
extern float D_L19_001B2830 MACRO_ADDR;
extern float D_L19_001B2834 MACRO_ADDR;
extern float D_L19_001B2838 MACRO_ADDR;
extern float D_L19_001B283C MACRO_ADDR;
extern float D_L19_001B2840 MACRO_ADDR;
extern int D_L19_001B2844 MACRO_ADDR;
extern u8 D_L19_001A8F20[] MACRO_ADDR;
extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(void *);
extern void math_store_angle_update_result(char *, float *, int, int, float);
extern int FastTweenColor(float, int, int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern u8 *part_spawn_fading_drift(void *, void *, int, int, int, int, int, float, float, float, int);
extern u8 *part_spawn_size_changing(void *, void *, int, int, int, int, int, float, float, float, int);
extern void part_spawn_growing_puff(void *, void *, int, int, float, int);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(char *, char *, char *);

/* func_US2_L19_002FABB0, the USA v2.00 copy of func_L19_002FA1A8: the same C,
 * with the actor 4000 effect left out in level 51. */
void func_US2_L19_002FABB0(void)
{
    Vec position, direction, axis;
    char *actor;
    int i;
    anim_start_startup_animations();
    for (i = 0; i < D_L19_001BD740.count; i++) {
        actor = D_L19_001BD740.items[i];
        if (actor && *(short *)(actor + 0xaa) == 0xe29)
            *(unsigned short *)(actor + 0x34) |= 0x800;
        /* Retail makes this test without a null check: it also reads an
         * empty slot. */
        if (*(short *)(actor + 0xaa) == 0xd54)
            UpdateEquipmentPieces(actor);
        if (actor) {
            /* Held in a local: its longer life makes the first loop pass hoist
             * it, ahead of the items pointer. The level's 51 waits for the
             * second pass and lands after that pointer, as in retail. */
            int id = 4000;
            if (*(short *)(actor + 0xaa) == id && g_current_map_index != 51 && *(char **)(actor + 0x68))
                math_store_angle_update_result(actor, (float *)(*(char **)(actor + 0x68) + 0xc), 0x80aaaad2, 0x80396464, 0.061086535f);
        }
    }
    if (g_current_map_index == 19) {
        if (D_L19_001BD740.state == 4) {
            int frame = D_L19_001BD740.frame;
            if (frame == 1) {
                D_L19_001B2814 = D_L19_001BD740.items[3];
                D_L19_001B2830 = 3.5f;
                D_L19_001B2834 = 11.0f;
                D_L19_001B2838 = 10.7f;
                D_L19_001B283C = 0.0f;
                D_L19_001B2840 = 0.0f;
                D_L19_001B2844 = frame;
            }
            D_L19_001B2820.q = *(Quad *)(D_L19_001B2814 + 0x10);
            if (frame == 750) {
                D_L19_001B9900.strength = 1.0f;
                D_L19_001B9900.ticks = 15;
                D_L19_001B9900.mode = 0;
            }
            if (D_L19_001BD740.frame >= 750 && D_L19_001BD740.frame <= 770) {
                D_L19_001B2840 += D_L19_001B2838;
                if (D_L19_001B2840 >= 1.0f) {
                    do {
                        int color;
                        float angle;
                        direction.q = 0;
                        direction.f[0] = 0.72f;
                        direction.f[1] = -0.72f;
                        direction.f[3] = 1.0f;
                        color = ((u32)math_random_int_range(96, 128) << 16) | 0x1e00;
                        position.f[0] = 0.0f;
                        position.f[1] = D_L19_001B2830 * math_random_float_range(0.9f, 1.1f);
                        position.f[2] = 0.0f;
                        position.f[3] = 1.0f;
                        angle = math_random_float_range(0.0f, 6.2831855f);
                        math_apply_axis_rotation_to_quat(&position, &position, &direction, angle);
                        FastVecAdd((char *)&position, (char *)&position, (char *)&D_L19_001B2820);
                        vec_scale_to_length(&direction, &direction, math_random_float_range(1.5f, 2.5f));
                        FastVecAdd((char *)&position, (char *)&position, (char *)&direction);
                        FastVecAdd((char *)&position, (char *)&position, (char *)&direction);
                        D_L19_001B2840 -= 1.0f;
                        {
                            int life = math_random_int_range(4, 8);
                            float speed = math_random_float_range(0.6f, 0.8f) * 210000.0f;
                            part_spawn_fading_drift(&position, D_L19_001A8F20, 24, color, life, 128, 32, speed, 21000.0f, 0.0f, 0);
                        }
                        {
                            int life = math_random_int_range(4, 8);
                            float speed = math_random_float_range(0.6f, 0.8f) * 210000.0f;
                            int style = math_random_int_range(1, 7);
                            part_spawn_fading_drift(&position, D_L19_001A8F20, 24, color, life, 128, 32, speed, 21000.0f, 0.0f, style);
                        }
                    } while (D_L19_001B2840 >= 1.0f);
                }
            }
            if (D_L19_001BD740.frame >= 761 && D_L19_001BD740.frame <= 839) {
                D_L19_001B283C += D_L19_001B2834;
                if (D_L19_001B283C >= 1.0f) {
                    do {
                        int color, life, style;
                        float speed, other, angle;
                        color = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x803c14, 0x400000);
                        position.f[0] = 0.0f;
                        position.f[1] = 0.0f;
                        position.f[2] = D_L19_001B2830 * -0.8f;
                        position.f[3] = 1.0f;
                        direction.f[0] = 1.0f;
                        direction.f[1] = 0.0f;
                        direction.f[2] = 0.0f;
                        direction.f[3] = 1.0f;
                        /* Retail never writes axis.f[0] before this rotation. */
                        axis.f[1] = 0.0f;
                        axis.f[2] = 1.0f;
                        axis.f[3] = 1.0f;
                        math_apply_axis_rotation_to_quat(&direction, &direction, &axis, math_random_float_range(0.0f, 6.2831855f));
                        angle = math_random_float_range(0.0f, 1.5707964f);
                        math_apply_axis_rotation_to_quat(&position, &position, &direction, angle);
                        FastVecAdd((char *)&position, (char *)&position, (char *)&D_L19_001B2820);
                        life = math_random_int_range(22, 55);
                        style = math_random_int_range(0, 10);
                        speed = math_random_float_range(0.5f, 1.0f) * 21000.0f;
                        other = math_random_float_range(0.7f, 1.0f) * 21000.0f;
                        part_spawn_size_changing(&position, D_L19_001A8F20, life, color, style, 128, 0, speed, other, 0.0033333334f, 3);
                        D_L19_001B283C -= 1.0f;
                    } while (D_L19_001B283C >= 1.0f);
                }
            }
        }
        if (g_current_map_index == 19 && D_L19_001BD740.state == 5 && D_L19_001BD740.frame == 1375) {
            char *burstActor = D_L19_001BD740.items[4];
            int n;
            for (n = 0; n < 47; n++) {
                int color, style, life, red, gray, high;
                float speed, angle, pitch, radius;
                radius = math_random_float_range(0.0f, 0.37f);
                angle = math_random_angle();
                pitch = math_random_angle();
                vec_build_spherical_offset(direction.f, radius, angle, pitch);
                FastVecAdd((char *)&direction, (char *)&direction, burstActor + 0x10);
                radius = math_random_float_range(0.006166667f, 0.023333333f);
                angle = math_random_angle();
                pitch = math_random_angle();
                vec_build_spherical_offset(position.f, radius, angle, pitch);
                red = math_random_int_range(47, 87);
                gray = math_random_int_range(100, 220);
                speed = math_random_float_range(70000.0f, 150000.0f);
                /* Built in two steps: as one expression cc1 regroups the four
                 * terms and shares an OR with style, unlike retail. */
                high = (red << 24) | (gray << 16) | (gray << 8);
                color = high | gray;
                style = (gray << 16) | (gray << 8) | gray;
                life = math_random_int_range(13, 42);
                part_spawn_growing_puff(&direction, &position, color, style, speed, life);
            }
        }
    }
}
