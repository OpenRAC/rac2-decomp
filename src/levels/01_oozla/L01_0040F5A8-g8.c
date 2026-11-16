#include "common.h"

typedef union { int q __attribute__((mode(TI))); float f[4]; } DebrisVector;

extern s32 g_oozla_intro_timer SDATA(D_L01_001AEC38);
extern s32 D_L01_001AEC38_1 __asm__("D_L01_001AEC38");
extern s32 g_breakable_count SDATA(D_L01_001B3468);
extern s32 D_L01_001B3468_1 __asm__("D_L01_001B3468");
extern float g_breakable_alpha_check_a __attribute__((sda));
extern float g_breakable_alpha_check_b __attribute__((sda));
extern s32 g_breakable_active_limit NOT_SDA;
extern float g_breakable_piece_params_a[] SDATA(D_L01_001B1600);
extern float g_breakable_piece_params_b[] SDATA(D_L01_001B15F8);
extern float g_breakable_piece_params_c[] SDATA(D_L01_001B15F0);
extern float g_breakable_effect_offset_x __attribute__((sda));
extern float g_breakable_effect_offset_y NOT_SDA;
extern float g_breakable_effect_offset_z NOT_SDA;
extern char g_zero_l01_vector[] NOT_SDA;

extern s32 math_fast_float_d(char *);
extern void moby_mark_spawned(char *);
extern void moby_set_state(char *, s32, s32);
extern void *part_find_owned_effect_slot(char *, s32, s32);
extern float math_random_float_range(float, float);
extern void *cam_moby_create(char *, s32, s32, s32, char *, char *, void *, s32, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void part_spawn_masked_debris(char *, s32, char *, s32, float, float, float, float);
extern s32 flag_set_first_pending(char *);
extern int PlayMobySound(s32, s32, char *);
extern void vec_local_offset_to_world(char *, void *, float, float, float);
extern void part_spawn_scaled_bolts(char *, s32, float);
extern void part_explode_object_into_pieces(char *, void *, void *, void *, s32, s32, s32, s32, s32, u8, void *);
extern void part_l01_spawn_spark_burst(float, float, float, void *, void *, s32, u32, s32);

typedef struct { char pad0[0x31]; u8 active; u16 pad32; u16 flags; char pad36[0x62]; int target; } RetiringObject;
/* Update for a breakable object that throws debris with a sound when hit, then retires after a timer. */
void breakable_l01_debris_update_2(char *obj)
{
    DebrisVector velocity, jitter, position;
    char *vars = *(char **)(obj + 0x68);

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        g_oozla_intro_timer = D_L01_001AEC38_1 + 1;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(obj, 0x04010000, 0) != 0 && *(s32 *)vars == 0) {
            g_oozla_intro_timer = D_L01_001AEC38_1 - 1;
            moby_set_state(obj, 2, -1);
        }
        *(u8 *)(obj + 0xA8) = 0xFF;
        break;
    case 2:
        if (*(u8 *)(obj + 0x31) != 0 && g_breakable_alpha_check_a < 0.9f && g_breakable_alpha_check_b < 0.9f
            && g_breakable_count < g_breakable_active_limit) {
            part_explode_object_into_pieces(obj, g_breakable_piece_params_a, g_breakable_piece_params_b, g_breakable_piece_params_c,
                65535, 0, 0, 6, 65535, 255, 0);
            jitter.q = 0;
            jitter.f[0] = math_random_float_range(-1.0f, 1.0f) * 0.016666668f;
            jitter.f[1] = math_random_float_range(-1.0f, 1.0f) * 0.016666668f;
            jitter.f[2] = 0.083333336f;
            velocity.q = jitter.q;
            cam_moby_create(obj, 2, *(s16 *)(obj + 0xaa), 0, obj + 0x10, obj + 0xf0,
                &velocity, 255, math_random_float_range(180.0f, 360.0f), 15.0f);
            jitter.q = 0;
            jitter.f[1] = -0.015000000596046448f;
            vec_local_offset_to_world(obj, &position, g_breakable_effect_offset_x, g_breakable_effect_offset_y, g_breakable_effect_offset_z);
            matrix_mul_vec3(&jitter, &jitter, obj + 0xc0);
            part_l01_spawn_spark_burst(0.0066666672937572f, 1.0f, 1.0299999713897705f, &position, &jitter, 10, 0x80808080, 0);
            moby_set_state(obj, 3, -1);
        } else {
            part_spawn_masked_debris(obj, 17, g_zero_l01_vector, 255, 1.0f, 3.0f, 2.0f, 5.0f);
            part_spawn_scaled_bolts(obj, 1, 0.0f);
            PlayMobySound(0, 0, obj);
        }
        moby_set_state(obj, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(obj) != 0) {
            RetiringObject *retiring = (RetiringObject *)obj;
            unsigned int flags = retiring->flags;
            int count;
            retiring->active = 0;
            retiring->target = 0;
            count = D_L01_001B3468_1;
            retiring->flags = flags | 1;
            *(int *)(vars + 8) = 0x78;
            D_L01_001B3468_1 = count + 1;
        }
        if (math_fast_float_d(vars + 8) != 0) {
            g_breakable_count = g_breakable_count - 1;
            moby_mark_spawned(obj);
        }
        break;
    }
}
