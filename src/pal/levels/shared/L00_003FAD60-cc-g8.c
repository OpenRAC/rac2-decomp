#include "names.h"
/* func_PAL_L00_003FAD60, the PAL copy of func_L00_003F6900: the same C, where scale func_002A7820(D_L00_001B09C4, D_L00_001B09C8). */
typedef int EffectWord128 __attribute__((mode(TI)));
typedef union { EffectWord128 word; float xyzw[4]; } EffectVector;
typedef struct {
    EffectVector position;
    short lifetime, active;
    float inverseLifetime, phase, angularSpeed;
    float u0, v0, u1, v1;
    int reserved;
    float angle, scale;
    int tail;
} EffectRecord64;
extern char *level_get_slot_body(int, int);
extern char *level_get_slot_header(int, int);
extern int math_random_int_range(int, int);
extern float IntToFloat(int);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern int g_vaporizer_spark_lifetime_min __attribute__((sda));
extern int g_vaporizer_spark_lifetime_max __attribute__((sda));
extern float g_vaporizer_spark_spin_min __attribute__((sda));
extern float g_vaporizer_spark_spin_max __attribute__((sda));
extern float g_vaporizer_spark_u_min __attribute__((sda));
extern float g_vaporizer_spark_u_max __attribute__((sda));
extern float g_vaporizer_spark_v_min __attribute__((sda));
extern float g_vaporizer_spark_v_max __attribute__((sda));
extern float g_vaporizer_spark_angle_min __attribute__((sda));
extern float g_vaporizer_spark_angle_max __attribute__((sda));
extern float g_vaporizer_spark_scale_min __attribute__((sda));
extern float g_vaporizer_spark_scale_max __attribute__((sda));

void func_PAL_L00_003FAD60(char *object, EffectVector *position) {
    char *state = *(char **)(object + 0x68);
    char *base = level_get_slot_body(0xC04, *(short *)(state + 0x1A));
    EffectRecord64 *record;
    int i;
    base += *(int *)(level_get_slot_header(0xC04, *(short *)(state + 0x1A)) + 4);
    record = (EffectRecord64 *)base;
    for (i = 0; i < 120; i++, record++) {
        if (record->active == 0) {
            record->active = 1;
            record->position.word = position->word;
            record->lifetime = (((int)(math_random_int_range(g_vaporizer_spark_lifetime_min, g_vaporizer_spark_lifetime_max)) * 5 + 2) / 6);
            record->inverseLifetime = 1.0f / IntToFloat(record->lifetime);
            record->phase = math_random_angle();
            record->angularSpeed = math_random_signed_float_range(g_vaporizer_spark_spin_min, g_vaporizer_spark_spin_max) * 0.017453294f;
            record->u0 = math_random_float_range(g_vaporizer_spark_u_min, g_vaporizer_spark_u_max);
            record->v0 = math_random_float_range(g_vaporizer_spark_v_min, g_vaporizer_spark_v_max);
            record->u1 = math_random_float_range(g_vaporizer_spark_u_min, g_vaporizer_spark_u_max);
            record->v1 = math_random_float_range(g_vaporizer_spark_v_min, g_vaporizer_spark_v_max);
            record->reserved = 0;
            record->angle = math_random_float_range(g_vaporizer_spark_angle_min, g_vaporizer_spark_angle_max) * 0.017453294f;
            record->scale = math_random_float_range(g_vaporizer_spark_scale_min, g_vaporizer_spark_scale_max);
            break;
        }
    }
}
