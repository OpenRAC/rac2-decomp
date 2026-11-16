#include "include_asm.h"

#include "common.h"
typedef struct { u8 header[0x40]; unsigned int colour[4]; float uv[8]; unsigned long tag, tex0, tex1, alpha; } DoorPacket;
extern DoorPacket g_effect_quad_packets_a, g_effect_quad_packets_b, g_effect_quad_packets_c;
extern u8 *g_moby_pointer_table[];
extern int g_frame_l08_counter MACRO_ADDR;
extern int g_flare_last_frame __attribute__((sda));
extern int g_flare_quad_count __attribute__((sda));
extern int g_flare_l08_texture_id __attribute__((sda));
extern int g_flare_tex_bits_a __attribute__((sda));
extern int g_flare_tex_bits_b __attribute__((sda));
extern int g_flare_tex_bits_c __attribute__((sda));
extern int g_flare_tex_bits_d __attribute__((sda));
extern int g_flare_tex_bits_e __attribute__((sda));
extern int g_flare_first_colour __attribute__((sda));
extern int g_flare_tex_bits_f __attribute__((sda));
extern int g_flare_tex_bits_g __attribute__((sda));
extern int g_flare_tex_bits_h __attribute__((sda));
extern int g_flare_tex_bits_i __attribute__((sda));
extern int g_flare_tex_bits_j __attribute__((sda));
extern int g_flare_second_colour __attribute__((sda));
extern int g_flare_tex_bits_k __attribute__((sda));
extern int g_flare_tex_bits_l __attribute__((sda));
extern int g_flare_tex_bits_m __attribute__((sda));
extern int g_flare_tex_bits_n __attribute__((sda));
extern int g_flare_tex_bits_o __attribute__((sda));
extern int g_flare_third_colour __attribute__((sda));
extern float g_flare_uv_speed __attribute__((sda));
extern float g_flare_wave_speed __attribute__((sda));
extern float g_flare_wave_amplitude __attribute__((sda));
extern float g_flare_z_offset __attribute__((sda));
extern u8 *g_flare_last_moby __attribute__((sda));
extern u8 g_moby_group_flags[], g_hero_state[];
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
        if (g_frame_l08_counter != g_flare_last_frame) {
            mem_clear(g_moby_pointer_table, 0, 128);
            g_flare_quad_count = 0;
        }
        data->rate *= 0.0003490659f;
        data->phase = 0;
        texture = GetEffectTextureDescriptor(g_flare_l08_texture_id);
        alpha = (unsigned long)((long)((unsigned long)(
                    (long)((unsigned long)g_flare_tex_bits_a |
                           ((unsigned long)g_flare_tex_bits_b << 2)) |
                    (long)((unsigned long)g_flare_tex_bits_c << 4)) |
                    ((unsigned long)g_flare_tex_bits_d << 6)) |
                    (long)((unsigned long)g_flare_tex_bits_e << 32));
        g_effect_quad_packets_a.alpha = alpha;
        g_effect_quad_packets_a.colour[0] = g_effect_quad_packets_a.colour[1] = g_effect_quad_packets_a.colour[2] = g_effect_quad_packets_a.colour[3] = g_flare_first_colour;
        g_effect_quad_packets_a.tex0 = texture;
        g_effect_quad_packets_a.tag = 0;
        g_effect_quad_packets_a.tex1 = 0xff9000000260UL;
        texture = GetEffectTextureDescriptor(72);
        second = &g_effect_quad_packets_b;
        third = &g_effect_quad_packets_c;
        /* As in RAC1, each of these packets gets its ALPHA word last. */
        second->colour[0] = second->colour[1] = second->colour[2] = second->colour[3] = g_flare_second_colour;
        second->tex0 = texture;
        second->tex1 = 0xff9000000260UL;
        second->tag = 0;
        alpha = (unsigned long)((long)((unsigned long)(
                    (long)((unsigned long)g_flare_tex_bits_f |
                           ((unsigned long)g_flare_tex_bits_g << 2)) |
                    (long)((unsigned long)g_flare_tex_bits_h << 4)) |
                    ((unsigned long)g_flare_tex_bits_i << 6)) |
                    (long)((unsigned long)g_flare_tex_bits_j << 32));
        second->alpha = alpha;
        third->colour[0] = third->colour[1] = third->colour[2] = third->colour[3] = g_flare_third_colour;
        third->tex0 = texture;
        third->tex1 = 0xff9000000260UL;
        third->tag = 0;
        alpha = (unsigned long)((long)((unsigned long)(
                    (long)((unsigned long)g_flare_tex_bits_k |
                           ((unsigned long)g_flare_tex_bits_l << 2)) |
                    (long)((unsigned long)g_flare_tex_bits_m << 4)) |
                    ((unsigned long)g_flare_tex_bits_n << 6)) |
                    (long)((unsigned long)g_flare_tex_bits_o << 32));
        third->alpha = alpha;
        ((DoorObject *)object)->drawMode = 0;
        ((DoorObject *)object)->flags |= 1;
        if (g_moby_group_flags[object[0xb0] + g_current_map_index * 16] & 0x80) {
            data->phase = 3.1415927410125732f;
            object[0x95] = 3;
        } else {
            object[0x95] = 1;
        }
        break;
    case 1:
        if ((g_moby_group_flags[object[0xb0] + g_current_map_index * 16] & 0x80) || flag_is_third_pending_set(object)) {
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
    if (g_frame_l08_counter != g_flare_last_frame) {
        phase = math_fast_sin_or_cos_b(math_wrap_angle_to_pi(IntToFloat(g_frame_l08_counter) * g_flare_wave_speed));
        g_flare_z_offset = g_flare_wave_amplitude * phase;
        uv = fast_fmod(IntToFloat(g_frame_l08_counter) * g_flare_uv_speed, 1.0f);
        corner = uv + 2.0f;
        g_effect_quad_packets_a.uv[0] = uv;
        g_effect_quad_packets_a.uv[4] = uv;
        g_effect_quad_packets_a.uv[2] = corner;
        g_effect_quad_packets_a.uv[6] = corner;
        g_effect_quad_packets_a.uv[1] = uv;
        g_effect_quad_packets_a.uv[5] = corner;
        g_effect_quad_packets_a.uv[3] = uv;
        g_effect_quad_packets_a.uv[7] = corner;
        g_flare_last_frame = g_frame_l08_counter;
        g_moby_pointer_table[0] = 0;
        g_flare_quad_count = 0;
    }
    qcopy(position, object + 0x10);
    position[3] = (*(float *)(object + 0x2c) * 11.319999694824219f) / *(float *)(*(u8 **)(object + 0x24) + 0x24);
    if (math_fast_helper_a(position, (float)*(short *)(object + 0x32)) != -1) {
        gfx_add_draw_callback_first(DrawLayeredDoorQuads, object);
        g_flare_last_moby = object;
        g_moby_pointer_table[g_flare_quad_count++] = object;
        g_moby_pointer_table[g_flare_quad_count] = 0;
    }
}
