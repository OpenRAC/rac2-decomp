#include "common.h"

/* Four position vectors, colours and UV pairs, followed by GS register words. */
typedef struct {
    float p[4][4];
    u32 color[4];
    float uv[8];
    u64 tag, tex0, tex1, alpha;
} QuadPacket;

typedef struct {
    u8 pad[0x140];
    float position[4];
} DoorCamera;

extern QuadPacket g_effect_quad_packets_c[], g_effect_quad_packets_a[], g_effect_quad_packets_b[];
extern float g_flare_z_offset __attribute__((sda));
extern float g_flare_time_scale __attribute__((sda));
extern float g_flare_y_scale __attribute__((sda));
extern float g_flare_x_scale __attribute__((sda));
extern float g_flare_quad_size __attribute__((sda));
extern u8 *g_flare_last_moby __attribute__((sda));
extern int g_flare_quad_count __attribute__((sda));
extern int g_frame_l08_counter;
extern DoorCamera g_hero_l08_extra_state;
extern float g_normalize_length_vec[4][4] MACRO_ADDR;
extern float g_hero_position_vec[4] NOT_SDA;
extern u8 *g_moby_pointer_table[];

extern u64 GetEffectTextureDescriptor(int);
extern float IntToFloat(int);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern void gfx_world_to_screen_unit(void *, float *, float *);
extern void draw_world_quad(void *, int, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Draws the tiled door overlay and the collected doors' layered quads.
 * Keep the diameter live before testing the camera side. The first two passes
 * retain their source position pointer between that test and sign selection.
 */
void DrawLayeredDoorQuads(u8 *moby)
{
    float v[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float radius = *(float *)(moby + 0x2C) * 8.0f / *(float *)(*(u8 **)(moby + 0x24) + 0x24);
    float diameter = radius + radius;
    float z = *(float *)(moby + 0x18) + g_flare_z_offset;
    u8 *state = *(u8 **)(moby + 0x68);
    float sign;
    int i, j;
    {
        int below = *(float *)(moby + 0x18) < g_hero_l08_extra_state.position[2];
        sign = below ? -1.0f : 1.0f;
    }

    if (state[0x23]) {
        float x, y, y2, f;
        float row = -radius, col;
        g_effect_quad_packets_c[0].p[0][2] = g_effect_quad_packets_c[0].p[1][2] = g_effect_quad_packets_c[0].p[2][2] =
            g_effect_quad_packets_c[0].p[3][2] = z + sign * 0.1f;
        g_effect_quad_packets_c[0].tex0 = GetEffectTextureDescriptor(-1);
        g_effect_quad_packets_c[0].color[0] = g_effect_quad_packets_c[0].color[1] = g_effect_quad_packets_c[0].color[2] =
            g_effect_quad_packets_c[0].color[3] = *(u32 *)(state + 0x20);
        f = IntToFloat(g_frame_l08_counter) * g_flare_time_scale;
        f = math_wrap_angle_to_pi(f);
        f = math_fast_sin_or_cos_b(f);
        y = *(float *)(moby + 0x14) - radius + f * g_flare_y_scale;
        g_effect_quad_packets_c[0].p[0][1] = y;
        g_effect_quad_packets_c[0].p[1][1] = y;
        y2 = y + g_flare_quad_size;
        g_effect_quad_packets_c[0].p[3][1] = y2;
        g_effect_quad_packets_c[0].p[2][1] = y2;
        x = *(float *)(moby + 0x10) - radius + f * g_flare_x_scale;
        g_effect_quad_packets_c[0].p[2][0] = g_effect_quad_packets_c[0].p[0][0] = x;
        g_effect_quad_packets_c[0].p[1][0] = g_effect_quad_packets_c[0].p[3][0] = x + g_flare_quad_size;
        gfx_world_to_screen_unit(g_effect_quad_packets_c[0].p[0], g_effect_quad_packets_c[0].uv + 2, g_effect_quad_packets_c[0].uv + 3);
        gfx_world_to_screen_unit(g_effect_quad_packets_c[0].p[2], g_effect_quad_packets_c[0].uv + 6, g_effect_quad_packets_c[0].uv + 7);
        while (row < radius) {
            col = -radius;
            while (col < radius) {
                g_effect_quad_packets_c[0].uv[0] = g_effect_quad_packets_c[0].uv[2];
                g_effect_quad_packets_c[0].uv[1] = g_effect_quad_packets_c[0].uv[3];
                g_effect_quad_packets_c[0].uv[4] = g_effect_quad_packets_c[0].uv[6];
                g_effect_quad_packets_c[0].uv[5] = g_effect_quad_packets_c[0].uv[7];
                gfx_world_to_screen_unit(g_effect_quad_packets_c[0].p[1], g_effect_quad_packets_c[0].uv + 2, g_effect_quad_packets_c[0].uv + 3);
                gfx_world_to_screen_unit(g_effect_quad_packets_c[0].p[3], g_effect_quad_packets_c[0].uv + 6, g_effect_quad_packets_c[0].uv + 7);
                draw_world_quad(g_effect_quad_packets_c, 0, 1);
                qcopy(g_effect_quad_packets_c[0].p[0], g_effect_quad_packets_c[0].p[1]);
                qcopy(g_effect_quad_packets_c[0].p[2], g_effect_quad_packets_c[0].p[3]);
                g_effect_quad_packets_c[0].p[2][0] = g_effect_quad_packets_c[0].p[0][0] = g_effect_quad_packets_c[0].p[1][0];
                g_effect_quad_packets_c[0].p[1][0] = g_effect_quad_packets_c[0].p[3][0] = g_effect_quad_packets_c[0].p[3][0] +
                    g_flare_quad_size;
                col += g_flare_quad_size;
            }
            g_effect_quad_packets_c[0].p[1][1] = g_effect_quad_packets_c[0].p[0][1] = g_effect_quad_packets_c[0].p[2][1];
            g_effect_quad_packets_c[0].p[2][1] = g_effect_quad_packets_c[0].p[3][1] = g_effect_quad_packets_c[0].p[3][1] +
                g_flare_quad_size;
            g_effect_quad_packets_c[0].p[2][0] = g_effect_quad_packets_c[0].p[0][0] = g_effect_quad_packets_c[0].p[0][0] - diameter;
            g_effect_quad_packets_c[0].p[1][0] = g_effect_quad_packets_c[0].p[3][0] = g_effect_quad_packets_c[0].p[3][0] - diameter;
            gfx_world_to_screen_unit(g_effect_quad_packets_c[0].p[0], g_effect_quad_packets_c[0].uv + 2, g_effect_quad_packets_c[0].uv + 3);
            gfx_world_to_screen_unit(g_effect_quad_packets_c[0].p[2], g_effect_quad_packets_c[0].uv + 6, g_effect_quad_packets_c[0].uv + 7);
            row += g_flare_quad_size;
        }
    }
    if (moby != g_flare_last_moby)
        return;
    for (i = 0; i < g_flare_quad_count; i++) {
        u8 *position;
        moby = g_moby_pointer_table[i];
        radius = *(float *)(moby + 0x2C) * 8.0f / *(float *)(*(u8 **)(moby + 0x24) + 0x24);
        z = *(float *)(moby + 0x18) + g_flare_z_offset;
        state = *(u8 **)(moby + 0x68);
        {
            int below = *(float *)(moby + 0x18) < g_hero_l08_extra_state.position[2];
            position = moby + 0x10;
            sign = below ? -1.0f : 1.0f;
        }
        qcopy(g_effect_quad_packets_a[0].p[0], position);
        g_effect_quad_packets_a[0].p[0][2] = z + sign * 0.06f;
        qcopy(g_effect_quad_packets_a[0].p[1], g_effect_quad_packets_a[0].p[0]);
        qcopy(g_effect_quad_packets_a[0].p[2], g_effect_quad_packets_a[0].p[0]);
        qcopy(g_effect_quad_packets_a[0].p[3], g_effect_quad_packets_a[0].p[0]);
        g_effect_quad_packets_a[0].color[0] = g_effect_quad_packets_a[0].color[1] = g_effect_quad_packets_a[0].color[2] =
            g_effect_quad_packets_a[0].color[3] = *(u32 *)(state + 0x14);
        g_effect_quad_packets_a[0].p[2][0] = g_effect_quad_packets_a[0].p[0][0] = g_effect_quad_packets_a[0].p[0][0] - radius;
        g_effect_quad_packets_a[0].p[3][0] = g_effect_quad_packets_a[0].p[1][0] = g_effect_quad_packets_a[0].p[1][0] + radius;
        g_effect_quad_packets_a[0].p[1][1] = g_effect_quad_packets_a[0].p[0][1] = g_effect_quad_packets_a[0].p[0][1] - radius;
        g_effect_quad_packets_a[0].p[3][1] = g_effect_quad_packets_a[0].p[2][1] = g_effect_quad_packets_a[0].p[2][1] + radius;
        g_effect_quad_packets_a[0].tex0 = GetEffectTextureDescriptor(*(int *)(state + 0x10) + 0x3F);
        draw_world_quad(g_effect_quad_packets_a, 0, 1);
    }
    for (i = 0; i < g_flare_quad_count; i++) {
        u8 *position;
        moby = g_moby_pointer_table[i];
        radius = *(float *)(moby + 0x2C) * 8.0f / *(float *)(*(u8 **)(moby + 0x24) + 0x24);
        z = *(float *)(moby + 0x18) + g_flare_z_offset;
        state = *(u8 **)(moby + 0x68);
        {
            int below = *(float *)(moby + 0x18) < g_hero_l08_extra_state.position[2];
            position = moby + 0x10;
            sign = below ? -1.0f : 1.0f;
        }
        qcopy(g_effect_quad_packets_a[0].p[0], position);
        g_effect_quad_packets_a[0].p[0][2] = z + sign * 0.04f;
        qcopy(g_effect_quad_packets_a[0].p[1], g_effect_quad_packets_a[0].p[0]);
        qcopy(g_effect_quad_packets_a[0].p[2], g_effect_quad_packets_a[0].p[0]);
        qcopy(g_effect_quad_packets_a[0].p[3], g_effect_quad_packets_a[0].p[0]);
        g_effect_quad_packets_a[0].p[2][0] = g_effect_quad_packets_a[0].p[0][0] = g_effect_quad_packets_a[0].p[0][0] + radius;
        g_effect_quad_packets_a[0].p[3][0] = g_effect_quad_packets_a[0].p[1][0] = g_effect_quad_packets_a[0].p[1][0] - radius;
        g_effect_quad_packets_a[0].p[1][1] = g_effect_quad_packets_a[0].p[0][1] = g_effect_quad_packets_a[0].p[0][1] - radius;
        g_effect_quad_packets_a[0].p[3][1] = g_effect_quad_packets_a[0].p[2][1] = g_effect_quad_packets_a[0].p[2][1] + radius;
        g_effect_quad_packets_a[0].color[0] = g_effect_quad_packets_a[0].color[1] = g_effect_quad_packets_a[0].color[2] =
            g_effect_quad_packets_a[0].color[3] = *(u32 *)(state + 0x14);
        draw_world_quad(g_effect_quad_packets_a, 0, 1);
    }
    for (i = 0; i < g_flare_quad_count; i++) {
        moby = g_moby_pointer_table[i];
        radius = *(float *)(moby + 0x2C) * 8.0f / *(float *)(*(u8 **)(moby + 0x24) + 0x24);
        z = *(float *)(moby + 0x18) + g_flare_z_offset;
        state = *(u8 **)(moby + 0x68);
        qcopy(g_effect_quad_packets_a[0].p[0], (moby + 0x10));
        g_effect_quad_packets_a[0].p[0][2] = z;
        qcopy(g_effect_quad_packets_a[0].p[1], g_effect_quad_packets_a[0].p[0]);
        qcopy(g_effect_quad_packets_a[0].p[2], g_effect_quad_packets_a[0].p[0]);
        qcopy(g_effect_quad_packets_a[0].p[3], g_effect_quad_packets_a[0].p[0]);
        g_effect_quad_packets_a[0].p[2][0] = g_effect_quad_packets_a[0].p[0][0] = g_effect_quad_packets_a[0].p[0][0] + radius;
        g_effect_quad_packets_a[0].p[3][0] = g_effect_quad_packets_a[0].p[1][0] = g_effect_quad_packets_a[0].p[1][0] - radius;
        g_effect_quad_packets_a[0].p[1][1] = g_effect_quad_packets_a[0].p[0][1] = g_effect_quad_packets_a[0].p[0][1] + radius;
        g_effect_quad_packets_a[0].p[3][1] = g_effect_quad_packets_a[0].p[2][1] = g_effect_quad_packets_a[0].p[2][1] - radius;
        g_effect_quad_packets_a[0].color[0] = g_effect_quad_packets_a[0].color[1] = g_effect_quad_packets_a[0].color[2] =
            g_effect_quad_packets_a[0].color[3] = *(u32 *)(state + 0x14);
        draw_world_quad(g_effect_quad_packets_a, 0, 1);
    }
    if (*(int *)(state + 0x18) == -1)
        return;
    for (i = 0; i < g_flare_quad_count; i++) {
        moby = g_moby_pointer_table[i];
        radius = *(float *)(moby + 0x2C) * 8.0f / *(float *)(*(u8 **)(moby + 0x24) + 0x24);
        z = *(float *)(moby + 0x18) + g_flare_z_offset;
        qcopy(g_effect_quad_packets_b[0].p[0], (moby + 0x10));
        g_effect_quad_packets_b[0].p[0][2] = z;
        qcopy(g_effect_quad_packets_b[0].p[1], g_effect_quad_packets_b[0].p[0]);
        qcopy(g_effect_quad_packets_b[0].p[2], g_effect_quad_packets_b[0].p[0]);
        qcopy(g_effect_quad_packets_b[0].p[3], g_effect_quad_packets_b[0].p[0]);
        g_effect_quad_packets_b[0].p[2][0] = g_effect_quad_packets_b[0].p[0][0] = g_effect_quad_packets_b[0].p[0][0] - radius;
        g_effect_quad_packets_b[0].p[3][0] = g_effect_quad_packets_b[0].p[1][0] = g_effect_quad_packets_b[0].p[1][0] + radius;
        g_effect_quad_packets_b[0].p[1][1] = g_effect_quad_packets_b[0].p[0][1] = g_effect_quad_packets_b[0].p[0][1] - radius;
        g_effect_quad_packets_b[0].p[3][1] = g_effect_quad_packets_b[0].p[2][1] = g_effect_quad_packets_b[0].p[2][1] + radius;
        g_effect_quad_packets_b[0].tex0 = GetEffectTextureDescriptor(*(int *)(state + 0x18) + 0x3F);
        g_effect_quad_packets_b[0].color[0] = g_effect_quad_packets_b[0].color[1] = g_effect_quad_packets_b[0].color[2] =
            g_effect_quad_packets_b[0].color[3] = *(u32 *)(state + 0x1C);
        for (j = 0; j < 4; j++) {
            FastVecSub(delta, g_effect_quad_packets_b[0].p[j], g_hero_position_vec);
            vec_fast_normalize(v, delta, g_normalize_length_vec);
            vec_scale_to_length(v, v, 1.0f);
            g_effect_quad_packets_b[0].uv[j * 2] = v[0];
            g_effect_quad_packets_b[0].uv[j * 2 + 1] = v[1];
        }
        draw_world_quad(g_effect_quad_packets_b, 0, 1);
    }
}
