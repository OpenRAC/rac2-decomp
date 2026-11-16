#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    float v[4][4];           
    s32 c[4];                
    float uv[4][2];          
    u64 w[4];                
} Quad;
typedef struct { s16 a; s16 b; } Pair;
typedef struct { float angle; s32 fix; } Vars;
extern u8 *g_mothership_boss_moby MACRO_ADDR;
extern s32 g_spinning_quad_turn_speed MACRO_ADDR;
extern float g_mothership_scale_factor MACRO_ADDR;
extern s32 g_spinning_quad_period MACRO_ADDR;
extern float g_spinning_quad_alpha_scale MACRO_ADDR;
extern s32 g_spinning_quad_alpha_base MACRO_ADDR;
extern float g_spinning_quad_scale MACRO_ADDR;
extern s32 g_quad_alpha_a __attribute__((sda));
extern s32 g_quad_alpha_b __attribute__((sda));
extern s32 g_quad_alpha_c __attribute__((sda));
extern s32 g_quad_alpha_d __attribute__((sda));
extern s32 g_quad_effect_texture __attribute__((sda));
extern s32 g_quad_l23_color __attribute__((sda));
extern float g_quad_l23_depth __attribute__((sda));
extern float g_spinning_quad_vertices[][4];
extern float g_spinning_quad_uvs[][2];
extern Pair g_spinning_quad_corner_pairs[][4];
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern u64 GetEffectTextureDescriptor(s32);
extern void VU1_addGSregister(u16, u64);
extern void func_L22_002F3B38(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void FastVecScale(float, void *, void *);
extern void draw_world_quad(void *, void *, s32);

/* Updates the spin state at +0x68 and draws the 40 spinning quads of the table around the mothership boss (PAL). */
void gfx_draw_spinning_quad_table_pal(u8 *moby) {
    Quad quad;
    float matrix[12];
    float center[4];
    float offset[4];
    float temp_vec[4];
    float spin_matrix[12];
    u64 alpha;
    float wave;
    s32 alpha_value;
    s32 alpha_base;
    Vars *payload;
    s32 period;
    s32 i;
    s32 j;
    s32 uv;

    if (g_mothership_boss_moby != 0) {
        payload = *(Vars **)(moby + 0x68);
        g_spinning_quad_scale = g_mothership_scale_factor * 1.1f;
        payload->angle = FastAddRotations(payload->angle, (float)g_spinning_quad_turn_speed * 0.0003490659f);
        period = g_spinning_quad_period;
        wave = math_fast_sin_or_cos_b((float)(s32)(*(u16 *)(moby + 0x96) % period) * (1.0f / (float)period) * 3.1415927f);
        alpha_value = g_spinning_quad_alpha_base;
        alpha_base = alpha_value;
        alpha_value = (s32)(wave * g_spinning_quad_alpha_scale) + alpha_base;
        payload->fix = alpha_value;
        alpha = (u64)g_quad_alpha_a | ((u64)g_quad_alpha_b << 2);
        alpha |= (u64)g_quad_alpha_c << 4;
        alpha |= (u64)g_quad_alpha_d << 6;
        quad.w[3] = alpha | ((u64)payload->fix << 32);
        quad.w[1] = GetEffectTextureDescriptor(g_quad_effect_texture);
        quad.w[2] = 0xFF9000000260ULL;
        quad.w[0] = 0;
        VU1_addGSregister(0x47, 0x53001);
        qcopy(matrix, moby + 0xC0);
        qcopy(matrix + 4, moby + 0xD0);
        qcopy(matrix + 8, moby + 0xE0);
        qcopy_nc(matrix, g_mothership_boss_moby + 0xC0);
        qcopy_nc(matrix + 4, g_mothership_boss_moby + 0xD0);
        qcopy_nc(matrix + 8, g_mothership_boss_moby + 0xE0);
        qcopy_nc(center, g_mothership_boss_moby + 0x10);
        *(TI128 *)temp_vec = 0;
        temp_vec[3] = 1.0f;
        temp_vec[2] = g_quad_l23_depth;
        *(TI128 *)offset = *(TI128 *)temp_vec;
        func_L22_002F3B38(offset, offset, g_mothership_boss_moby + 0xE0);
        FastVecAdd(center, g_mothership_boss_moby + 0x10, offset);
        qzero_nc(temp_vec);
        temp_vec[2] = payload->angle;
        euler_rotation_basis(spin_matrix, temp_vec);
        multiply_matrix3x3(matrix, matrix, spin_matrix);
        center[3] = 1.0f;
        quad.c[3] = g_quad_l23_color;
        quad.c[2] = g_quad_l23_color;
        quad.c[1] = g_quad_l23_color;
        quad.c[0] = g_quad_l23_color;
        for (i = 0; i < 40; i++) {
            for (j = 0; j < 4; j++) {
                uv = g_spinning_quad_corner_pairs[i][j].b;
                FastVecScale(g_spinning_quad_scale, &quad.v[j], g_spinning_quad_vertices[g_spinning_quad_corner_pairs[i][j].a]);
                quad.uv[j][0] = g_spinning_quad_uvs[uv][0];
                quad.uv[j][1] = g_spinning_quad_uvs[uv][1];
            }
            draw_world_quad(&quad, matrix, 0);
        }
    }
}
