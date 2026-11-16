#include "common.h"
extern unsigned char *CreateMoby(int type);
extern int FloatToInt(float value);
extern void vec_scale_to_length(void *out, void *in, float scale);
extern void FastVecCross(void *out, void *a, void *b);
extern float g_projectile_speed_normal __attribute__((sda));
extern float g_projectile_speed_alt __attribute__((sda));
extern float g_projectile_range_normal __attribute__((sda));
extern float g_projectile_range_alt __attribute__((sda));
extern float g_projectile_scale_a __attribute__((sda));
extern float g_projectile_scale_b __attribute__((sda));

/* Creates a shot at a position flying in a direction with a speed and lifetime based on its
   kind. */
unsigned char *func_L05_003D0960(void *position, void *direction, int value, char *owner, int kind)
{
    unsigned char *object;
    char *state;
    float speed;
    float duration;
    float distance;
    float scale;
    if (kind)
        object = CreateMoby(0x1161);
    else
        object = CreateMoby(0x974);
    if (object != 0) {
        state = *(char **)(object + 0x68);
        object[0x30] = 255;
        *(unsigned short *)(object + 0x32) = 511;
        object[0x31] = 1;
        object[0x20] = 1;
        speed = (kind ? g_projectile_speed_alt : g_projectile_speed_normal) * 0.01666666753590107f;
        *(int *)(state + 0x24) = kind;
        duration = (kind ? g_projectile_range_alt : g_projectile_range_normal) / speed;
        *(int *)(state + 0x18) = FloatToInt(duration);
        *(float *)(state + 0x1C) = 1.0f / duration;
        *(int *)(state + 0x10) = value;
        *(char **)(state + 0x20) = owner;
        *(int *)(state + 0x14) = 0;
        if (kind)
            *(float *)(object + 0x2C) *= g_projectile_scale_b;
        else
            *(float *)(object + 0x2C) *= g_projectile_scale_a;
        *(unsigned short *)(object + 0x34) |= 0x100;
        qcopy(object + 0x10, position);
        vec_scale_to_length(state, direction, speed);
        vec_scale_to_length(object + 0xC0, state, 1.0f);
        FastVecCross(object + 0xD0, object + 0xC0, owner + 0xE0);
        vec_scale_to_length(object + 0xD0, object + 0xD0, 1.0f);
        FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
    }
    return object;
}
