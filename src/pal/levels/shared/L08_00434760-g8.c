#include "include_asm.h"

#include "common.h"
typedef struct { u8 header[0x40]; unsigned int colour[4]; float uv[8]; unsigned long tag, tex0, tex1, alpha; } DoorPacket;
extern DoorPacket D_L08_00264F20, D_L08_00264FB0, D_L08_00265040;
extern u8 *D_L08_002B2540[];
extern int D_L08_001B2508 MACRO_ADDR;
extern int D_L08_001B1EC0 __attribute__((sda));
extern int D_L08_001B1ECC __attribute__((sda));
extern int D_L08_001B1EBC __attribute__((sda));
extern int D_L08_001B1E58 __attribute__((sda));
extern int D_L08_001B1E5C __attribute__((sda));
extern int D_L08_001B1E60 __attribute__((sda));
extern int D_L08_001B1E64 __attribute__((sda));
extern int D_L08_001B1E68 __attribute__((sda));
extern int D_L08_001B1E6C __attribute__((sda));
extern int D_L08_001B1E70 __attribute__((sda));
extern int D_L08_001B1E74 __attribute__((sda));
extern int D_L08_001B1E78 __attribute__((sda));
extern int D_L08_001B1E7C __attribute__((sda));
extern int D_L08_001B1E80 __attribute__((sda));
extern int D_L08_001B1E84 __attribute__((sda));
extern int D_L08_001B1E88 __attribute__((sda));
extern int D_L08_001B1E8C __attribute__((sda));
extern int D_L08_001B1E90 __attribute__((sda));
extern int D_L08_001B1E94 __attribute__((sda));
extern int D_L08_001B1E98 __attribute__((sda));
extern int D_L08_001B1E9C __attribute__((sda));
extern float D_L08_001B1EA0 __attribute__((sda));
extern float D_L08_001B1EA4 __attribute__((sda));
extern float D_L08_001B1EA8 __attribute__((sda));
extern float D_L08_001B1EC4 __attribute__((sda));
extern u8 *D_L08_001B1EC8 __attribute__((sda));
extern u8 D_0019B2E8[], g_hero_state[];
extern int g_current_map_index;
extern void mem_clear(void *destination, int value, int size);
extern unsigned long GetEffectTextureDescriptor(int texture);
extern int flag_is_third_pending_set(u8 *object);
extern int snd_start_in_slot(int index, int value, int object);
extern float fast_subtract_rotations(float angle, float bound);
extern float math_fast_sin_or_cos_a(float angle);
extern float FastAddRotations(float angle, float velocity);
extern float IntToFloat(int value);
extern float math_wrap_angle_to_pi(float angle);
extern float math_fast_sin_or_cos_b(float angle);
extern float fast_fmod(float value, float divisor);
extern int math_fast_helper_a(void *position, float radius);
extern void DrawLayeredDoorQuads(void *object);
extern void gfx_add_draw_callback_first(void (*callback)(void *), void *object);
typedef struct { float upper, lower, phase, rate; } DoorState;
typedef struct {
    u8 pad0[0x31];
    u8 drawMode;
    short radius;
    u16 flags;
    u8 pad36[0x7a];
    u8 id;
} DoorObject;

void func_PAL_L08_00434760(u8 *object)
{
    DoorState *data = *(DoorState **)(object + 0x68);
    float rate;
    float half;
    float phase;
    float uv;
    float corner;
    unsigned long texture;
    /* Preserve each 64-bit packing stage when combining the signed selectors
       into the unsigned GS register word. */
    unsigned long alpha;
    DoorPacket *second, *third;
    float position[4] __attribute__((aligned(16)));
    if (data == 0)
        return;
    switch (object[0x95]) {
    case 0:
        if (D_L08_001B2508 != D_L08_001B1EC0) {
            mem_clear(D_L08_002B2540, 0, 128);
            D_L08_001B1ECC = 0;
        }
        data->rate *= 0.0003490659f;
        data->phase = 0;
        texture = GetEffectTextureDescriptor(D_L08_001B1EBC);
        alpha = (unsigned long)((long)((unsigned long)(
                    (long)((unsigned long)D_L08_001B1E58 |
                           ((unsigned long)D_L08_001B1E5C << 2)) |
                    (long)((unsigned long)D_L08_001B1E60 << 4)) |
                    ((unsigned long)D_L08_001B1E64 << 6)) |
                    (long)((unsigned long)D_L08_001B1E68 << 32));
        D_L08_00264F20.alpha = alpha;
        D_L08_00264F20.colour[0] = D_L08_00264F20.colour[1] = D_L08_00264F20.colour[2] = D_L08_00264F20.colour[3] = D_L08_001B1E6C;
        D_L08_00264F20.tex0 = texture;
        D_L08_00264F20.tag = 0;
        D_L08_00264F20.tex1 = 0xff9000000260UL;
        texture = GetEffectTextureDescriptor(72);
        second = &D_L08_00264FB0;
        third = &D_L08_00265040;
        /* As in RAC1, each of these packets gets its ALPHA word last. */
        second->colour[0] = second->colour[1] = second->colour[2] = second->colour[3] = D_L08_001B1E84;
        second->tex0 = texture;
        second->tex1 = 0xff9000000260UL;
        second->tag = 0;
        alpha = (unsigned long)((long)((unsigned long)(
                    (long)((unsigned long)D_L08_001B1E70 |
                           ((unsigned long)D_L08_001B1E74 << 2)) |
                    (long)((unsigned long)D_L08_001B1E78 << 4)) |
                    ((unsigned long)D_L08_001B1E7C << 6)) |
                    (long)((unsigned long)D_L08_001B1E80 << 32));
        second->alpha = alpha;
        third->colour[0] = third->colour[1] = third->colour[2] = third->colour[3] = D_L08_001B1E9C;
        third->tex0 = texture;
        third->tex1 = 0xff9000000260UL;
        third->tag = 0;
        alpha = (unsigned long)((long)((unsigned long)(
                    (long)((unsigned long)D_L08_001B1E88 |
                           ((unsigned long)D_L08_001B1E8C << 2)) |
                    (long)((unsigned long)D_L08_001B1E90 << 4)) |
                    ((unsigned long)D_L08_001B1E94 << 6)) |
                    (long)((unsigned long)D_L08_001B1E98 << 32));
        third->alpha = alpha;
        ((DoorObject *)object)->drawMode = 0;
        ((DoorObject *)object)->flags |= 1;
        if (D_0019B2E8[object[0xb0] + g_current_map_index * 16] & 0x80) {
            data->phase = 3.1415927410125732f;
            object[0x95] = 3;
        } else {
            object[0x95] = 1;
        }
        break;
    case 1:
        if ((D_0019B2E8[object[0xb0] + g_current_map_index * 16] & 0x80) || flag_is_third_pending_set(object)) {
            if (g_current_map_index == 19)
                snd_start_in_slot(18, 0, (int)object);
            object[0x95] = 2;
        }
        break;
    case 2:
        phase = data->phase;
        if (phase >= 3.1415927410125732f || phase < -3.0f) {
            data->phase = 3.1415927410125732f;
            object[0x95] = 3;
        }
        break;
    }
    rate = data->rate;
    if (object[0x95] != 2 || data->phase >= 3.1415927410125732f || data->phase < -3.0f)
        data->rate = 0;
    half = (data->upper - data->lower) * 0.5f;
    phase = math_fast_sin_or_cos_a(fast_subtract_rotations(data->phase, 3.1415927410125732f));
    *(float *)(object + 0x18) = data->lower + (phase * half + half);
    if (g_hero_state[0x22b4] == 4 ||
        (*(int *)(g_hero_state + 0x229c) != 20 && *(int *)(g_hero_state + 0x229c) != 25 &&
         *(int *)(g_hero_state + 0x2294) != 0x39 && *(int *)(g_hero_state + 0x2294) != 0x78 &&
         *(int *)(g_hero_state + 0x2294) != 0x79))
        data->phase = FastAddRotations(data->phase, data->rate);
    data->rate = rate;
    if (D_L08_001B2508 != D_L08_001B1EC0) {
        phase = math_fast_sin_or_cos_b(math_wrap_angle_to_pi(IntToFloat(D_L08_001B2508) * D_L08_001B1EA4));
        D_L08_001B1EC4 = D_L08_001B1EA8 * phase;
        uv = fast_fmod(IntToFloat(D_L08_001B2508) * D_L08_001B1EA0, 1.0f);
        corner = uv + 2.0f;
        D_L08_00264F20.uv[0] = uv;
        D_L08_00264F20.uv[4] = uv;
        D_L08_00264F20.uv[2] = corner;
        D_L08_00264F20.uv[6] = corner;
        D_L08_00264F20.uv[1] = uv;
        D_L08_00264F20.uv[5] = corner;
        D_L08_00264F20.uv[3] = uv;
        D_L08_00264F20.uv[7] = corner;
        D_L08_001B1EC0 = D_L08_001B2508;
        D_L08_002B2540[0] = 0;
        D_L08_001B1ECC = 0;
    }
    qcopy(position, object + 0x10);
    position[3] = (*(float *)(object + 0x2c) * 11.319999694824219f) / *(float *)(*(u8 **)(object + 0x24) + 0x24);
    if (math_fast_helper_a(position, (float)*(short *)(object + 0x32)) != -1) {
        gfx_add_draw_callback_first(DrawLayeredDoorQuads, object);
        D_L08_001B1EC8 = object;
        D_L08_002B2540[D_L08_001B1ECC++] = object;
        D_L08_002B2540[D_L08_001B1ECC] = 0;
    }
}
