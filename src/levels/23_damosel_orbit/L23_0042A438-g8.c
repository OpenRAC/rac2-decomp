#include "common.h"

/* func_L23_0042A438 is a unit of its own: it reads its globals through $gp (-G8) and needs the
 * qcopy/qzero macros (see config/cflags.txt). */

typedef int TI16 __attribute__((mode(TI)));

/* the state object word, read through an absolute access */
extern u8 *D_L23_001B1484_2;

extern float g_mothership_scale_factor;

extern s32 g_spinning_quad_period;

extern float g_star_quad_scale __attribute__((sda));

extern float g_trail_ribbon_phase;

extern s16 g_effect_sound_handle_a __attribute__((sda));

extern s32 g_alpha_blend_a __attribute__((sda));

extern s32 g_alpha_blend_b __attribute__((sda));

extern s32 g_alpha_blend_c __attribute__((sda));

extern s32 g_alpha_blend_d __attribute__((sda));

extern s32 g_trail_color_start __attribute__((sda));

extern s32 g_trail_color_end __attribute__((sda));

extern float g_trail_l23_uv_scroll __attribute__((sda));

extern float g_trail_uv_scroll_speed __attribute__((sda));

extern float g_trail_matrix_param __attribute__((sda));

extern float g_trail_length_scale __attribute__((sda));

extern s32 g_trail_effect_texture __attribute__((sda));

extern float g_trail_alpha_scale __attribute__((sda));

extern float g_trail_alpha_factor __attribute__((sda));

extern float g_trail_time_offset __attribute__((sda));

extern s32 g_trail_initial_alpha __attribute__((sda));

extern float g_trail_width_a __attribute__((sda));

extern float g_trail_width_b __attribute__((sda));

extern float g_trail_width_c __attribute__((sda));

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
} L23Spin3;

/* the object this update runs on */
typedef struct {
    u8 pad0[0x68];
    L23Spin3 *vars;
} L23Obj;

extern s32 g_effect_link_active_flags[];

extern TI16 g_trail_ribbon_vertices[];

extern TI16 g_trail_ribbon_dirs[];

extern TI16 g_camera_l23_position[];

extern void gfx_free_point_light(s32);

extern void FastVecScale(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern void FastVecSub(void *, void *, void *);

extern void FastVecCross(void *, void *, void *);

extern void vec_scale_to_length(void *, void *, float);

extern float FastVecLength(void *);

extern float math_random_float_range(float, float);

extern s32 part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);

extern long long GetEffectTextureDescriptor(s32);

extern void VU1_addGSregister(u32, u64);

extern void func_L03_002EFB60(void *, void *, float);

extern void euler_rotation_basis(void *, void *);

extern void multiply_matrix3x3(void *, void *, void *);

extern void transform_vector(void *, void *, void *);

extern void matrix_mul_vec3(void *, void *, void *);

extern void draw_world_quad(void *, void *, s32);

/* releases the held handle, spawns a new one from jittered values, updates the globals, then
   draws one quad for every live entry of the 72-entry table, tilted by the spin state */
void hero_draw_trail_ribbons(u8 *moby) {
    L23Spin3 *vars;
    L23Quad pkt;
    struct { TI16 rows[4]; } matrix;
    TI16 *mp;
    float *basis;
    TI16 w[1];
    TI16 axis[1];
    TI16 rot[3];
    TI16 v120[1];
    TI16 v130[1];
    TI16 v140[1];
    TI16 v150[1];
    TI16 v160[1];
    float fa;
    float fb;
    float fc;
    float f;
    float t;
    float alphaScale;
    float scaledLength;
    float ribbonWidth;
    s32 i;
    u8 *hero;
    s64 reg;
    s64 tex;

    if (D_L23_001B1484_2 != 0) {
        if (g_effect_sound_handle_a != -1) {
            gfx_free_point_light(g_effect_sound_handle_a);
        }
        FastVecScale(w, D_L23_001B1484_2 + 0xE0, 10.0f);
        FastVecAdd(w, w, D_L23_001B1484_2 + 0x10);
        f = math_random_float_range(0.0f, g_trail_width_a);
        fa = g_trail_width_a + f;
        f = math_random_float_range(0.0f, g_trail_width_b);
        fb = g_trail_width_b + f;
        f = math_random_float_range(0.0f, g_trail_width_c * 0.5f);
        fc = g_trail_width_c + f;
        g_effect_sound_handle_a = part_l00_alloc_effect_slot_2(w, 20.0f, 0.0f, fa, fb, fc);
        g_trail_l23_uv_scroll = g_trail_l23_uv_scroll - g_trail_uv_scroll_speed;
        g_star_quad_scale = g_mothership_scale_factor * 0.94f;
        vars = ((L23Obj *)moby)->vars;
        if (g_trail_l23_uv_scroll <= -6.0f) {
            g_trail_l23_uv_scroll = g_trail_l23_uv_scroll + 6.0f;
        }
        i = *(u16 *)(moby + 0x96) % (g_spinning_quad_period >> 2);
        vars->alpha = g_trail_initial_alpha;
        reg = g_alpha_blend_a | ((s64)g_alpha_blend_b << 2);
        reg |= (s64)g_alpha_blend_c << 4;
        reg |= (s64)g_alpha_blend_d << 6;
        reg |= (s64)vars->alpha << 32;
        pkt.tail[3] = reg;
        g_trail_alpha_scale = (float)vars->alpha * g_trail_alpha_factor;
        tex = GetEffectTextureDescriptor(g_trail_effect_texture);
        pkt.tail[2] = 0xFF9000000260LL;
        pkt.tail[1] = tex;
        pkt.tail[0] = 0;
        VU1_addGSregister(0x47, 0x53001);
        hero = D_L23_001B1484_2;
        qcopy_nc(&matrix.rows[0], hero + 0xC0);
        qcopy_nc(&matrix.rows[1], hero + 0xD0);
        qcopy_nc(&matrix.rows[2], hero + 0xE0);
        qzero_nc(&matrix.rows[3]);
        mp = matrix.rows;
        func_L03_002EFB60(mp, mp, g_trail_matrix_param);
        qcopy(&matrix.rows[3], D_L23_001B1484_2 + 0x10);
        ((float *)&matrix.rows[3])[3] = 1.0f;
        basis = (float *)mp;
        qzero_nc(axis);
        ((float *)axis)[2] = vars->turn;
        euler_rotation_basis(rot, axis);
        multiply_matrix3x3(basis, basis, rot);
        pkt.col[0] = pkt.col[1] = g_trail_color_start;
        pkt.col[2] = pkt.col[3] = g_trail_color_end;
        for (i = 0; i < 0x48; i++) {
            if (g_effect_link_active_flags[i] != 0) {
                alphaScale = g_trail_alpha_scale;
                transform_vector(v120, &g_trail_ribbon_vertices[i], &matrix);
                matrix_mul_vec3(v140, &g_trail_ribbon_dirs[i], mp);
                FastVecSub(v150, v120, g_camera_l23_position);
                FastVecCross(v160, v140, v150);
                vec_scale_to_length(v160, v160, alphaScale);
                f = FastVecLength(v150);
                scaledLength = f * g_trail_length_scale;
                t = g_trail_ribbon_phase;
                ribbonWidth = scaledLength * t;
                g_trail_ribbon_phase = t + g_trail_time_offset;
                if (g_trail_ribbon_phase > 1.0f) {
                    g_trail_ribbon_phase = 1.0f;
                }
                FastVecScale(v130, v140, ribbonWidth);
                FastVecAdd(v130, v130, v120);
                FastVecAdd(&pkt.pos[0], v120, v160);
                FastVecSub(&pkt.pos[1], v120, v160);
                FastVecAdd(&pkt.pos[2], v130, v160);
                FastVecSub(&pkt.pos[3], v130, v160);
                pkt.uv[0][1] = 0.0f;
                pkt.uv[1][1] = 1.0f;
                pkt.uv[2][1] = 0.0f;
                pkt.uv[3][1] = 1.0f;
                pkt.uv[2][0] = pkt.uv[3][0] = g_trail_l23_uv_scroll + 1.0f;
                pkt.uv[0][0] = pkt.uv[1][0] = g_trail_l23_uv_scroll;
                draw_world_quad(&pkt, 0, 0);
            }
        }
    }
}
