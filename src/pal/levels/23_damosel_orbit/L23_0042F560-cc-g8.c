/* func_PAL_L23_0042F560, the PAL copy of func_L23_0042A018: the same C. */
#include "common.h"

/* func_PAL_L23_0042F560 is a unit of its own: it reads its globals through $gp (-G8) and needs
 * -frac2-hazard-labels (see config/cflags.txt). */

typedef int TI16 __attribute__((mode(TI)));

/* the state object word, read through an absolute access */
extern u8 *D_L23_001B1484_2;

extern float g_mothership_scale_factor;

extern float g_spinning_quad_alpha_scale;

extern s32 g_spinning_quad_period;

extern s32 g_spinning_quad_turn_speed;

extern s32 g_spinning_quad_alpha_base;

extern float g_star_quad_scale;

extern s32 g_boss_fight_timer;

extern s32 g_alpha_blend_a __attribute__((sda));

extern s32 g_alpha_blend_b __attribute__((sda));

extern s32 g_alpha_blend_c __attribute__((sda));

extern s32 g_alpha_blend_d __attribute__((sda));

extern s32 g_star_effect_texture __attribute__((sda));

extern s32 g_trail_color_start __attribute__((sda));

extern s32 g_trail_color_end __attribute__((sda));

extern float g_star_spin_speed __attribute__((sda));

extern float g_star_size_min __attribute__((sda));

extern float g_star_size_max __attribute__((sda));

extern float g_star_offset_a __attribute__((sda));

extern float g_star_offset_b __attribute__((sda));

extern float g_star_offset_c __attribute__((sda));

extern float g_star_offset_d __attribute__((sda));

extern float g_star_offset_e __attribute__((sda));

extern float g_star_offset_f __attribute__((sda));

extern float g_star_offset_g __attribute__((sda));

extern float g_star_offset_h __attribute__((sda));

/* the quad record handed to the draw helper */
typedef struct {
    TI16 pos[4];
    u32 col[4];
    float uv[4][2];
    s64 tail[4];
} L23Quad;

/* the spin state at object + 0x68 */
typedef struct {
    float turn;
    s32 alpha;
    float spin;
} L23Spin;

typedef struct {
    s16 a;
    s16 b;
} L23Corner;

extern L23Corner g_star_quad_corners[][4];

extern TI16 g_star_quad_vertices[];

extern float g_star_quad_uvs[][2];

extern float FastAddRotations(float, float);

extern float math_fast_sin_or_cos_b(float);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_float_g(float);

extern float math_random_float_range(float, float);

extern long long GetEffectTextureDescriptor(s32);

extern void VU1_addGSregister(u32, u64);

extern void FastVecScale(void *, void *, float);

extern void euler_rotation_basis(void *, void *);

extern void multiply_matrix3x3(void *, void *, void *);

extern void draw_world_quad(void *, void *, s32);

/* updates the spin state at +0x68 and draws 72 quads of four corners each (corner positions from
   one table, uv from another; the colour and two GS words sit in the packet), the packet's matrix
   being the object's rotation rows turned about the spin angle */
void gfx_draw_spinning_star_quads_pal(u8 *moby) {
    L23Spin *vars;
    L23Quad pkt;
    TI16 matrix[4];
    TI16 axis[1];
    TI16 rot_matrix[3];
    float wave;
    float offset_a;
    float offset_b;
    float offset_c;
    float offset_d;
    s32 i;
    u8 *boss;
    s32 k;
    u32 color;
    s64 alpha_reg;
    s64 texture;
    float *uv_y_start;
    float *uv_x_start;

    if (D_L23_001B1484_2 != 0) {
        vars = *(L23Spin **)(moby + 0x68);
        g_star_quad_scale = g_mothership_scale_factor * 1.1f;
        vars->turn = FastAddRotations(vars->turn, (float)g_spinning_quad_turn_speed * 0.0003490659f);
        wave = math_fast_sin_or_cos_b((float)(*(u16 *)(moby + 0x96) % g_spinning_quad_period) * (1.0f / (float)g_spinning_quad_period) * 3.1415927f);
        vars->alpha = (s32)(wave * g_spinning_quad_alpha_scale);
        vars->alpha += g_spinning_quad_alpha_base;
        alpha_reg = g_alpha_blend_a | ((s64)g_alpha_blend_b << 2);
        alpha_reg |= (s64)g_alpha_blend_c << 4;
        alpha_reg |= (s64)g_alpha_blend_d << 6;
        alpha_reg |= (s64)vars->alpha << 32;
        pkt.tail[3] = alpha_reg;
        texture = GetEffectTextureDescriptor(g_star_effect_texture);
        pkt.tail[2] = 0xFF9000000260LL;
        pkt.tail[1] = texture;
        pkt.tail[0] = 0;
        VU1_addGSregister(0x47, 0x53001);
        boss = D_L23_001B1484_2;
        qcopy_nc(&matrix[0], boss + 0xC0);
        qcopy_nc(&matrix[1], boss + 0xD0);
        qcopy_nc(&matrix[2], boss + 0xE0);
        qcopy(&matrix[3], boss + 0x10);
        ((float *)&matrix[3])[3] = 1.0f;
        qzero_nc(axis);
        ((float *)axis)[2] = vars->turn;
        euler_rotation_basis(rot_matrix, axis);
        multiply_matrix3x3(matrix, matrix, rot_matrix);
        if (g_boss_fight_timer == 0) {
            color = (vars->alpha << 24) + (g_trail_color_start & 0xFFFFFF);
            pkt.col[3] = color;
            pkt.col[2] = color;
            pkt.col[1] = color;
            pkt.col[0] = color;
        } else {
            color = (vars->alpha << 24) + (g_trail_color_end & 0xFFFFFF);
            pkt.col[3] = color;
            pkt.col[2] = color;
            pkt.col[1] = color;
            pkt.col[0] = color;
        }
        for (i = 0, uv_x_start = &pkt.uv[0][0], uv_y_start = &pkt.uv[0][1]; i < 0x48; i++) {
            L23Corner (*corner_table)[4] = g_star_quad_corners;
            L23Corner *corner = corner_table[i];
            float *uv_y = uv_y_start;
            float *uv_x = uv_x_start;
            TI16 *pos = pkt.pos;

            for (k = 3; k >= 0; k--) {
                s32 uv_index = corner->b;

                FastVecScale(pos, &g_star_quad_vertices[corner->a], g_star_quad_scale);
                vars->spin = FastAddRotations(vars->spin, g_star_spin_speed * 0.0003490659f);
                math_fast_float_g(vars->spin);
                if (g_boss_fight_timer == 0) {
                    offset_a = math_fast_sin_or_cos_a(vars->spin) * g_star_offset_a;
                    offset_b = math_fast_sin_or_cos_b(vars->spin) * g_star_offset_b;
                    offset_c = math_fast_sin_or_cos_a(vars->spin) * g_star_offset_c;
                    offset_d = math_fast_sin_or_cos_b(vars->spin) * g_star_offset_d;
                } else {
                    offset_a = math_fast_sin_or_cos_a(vars->spin) * g_star_offset_e;
                    offset_b = math_fast_sin_or_cos_b(vars->spin) * g_star_offset_f;
                    offset_c = math_fast_sin_or_cos_a(vars->spin) * g_star_offset_g;
                    offset_d = math_fast_sin_or_cos_b(vars->spin) * g_star_offset_h;
                }
                wave = math_random_float_range(g_star_size_min, g_star_size_max);
                *uv_x = (g_star_quad_uvs[uv_index][0] * offset_a + offset_b) * wave;
                *uv_y = g_star_quad_uvs[uv_index][1] * offset_c + offset_d;
                pos++;
                corner++;
                uv_x += 2;
                uv_y += 2;
            }
            draw_world_quad(&pkt, matrix, 0);
        }
    }
}
