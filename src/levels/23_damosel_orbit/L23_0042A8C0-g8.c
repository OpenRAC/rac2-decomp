#include "names.h"
/* func_L23_0042A8C0 is a unit of its own for its mixed $gp and macro addresses. The non-clobbering
   transfers write only its private stack rows and the ring's edge table, so the ring index stays
   live across them. D_L23_001B1B98 has two names because retail keeps both of its stores, which
   flow would merge through one name. */

#include "common.h"

typedef struct Edge_0042A8C0 {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
} Edge_0042A8C0;

extern u8 *g_mothership_boss_moby MACRO_ADDR;

extern float g_mothership_scale_factor MACRO_ADDR;

extern float g_star_quad_scale MACRO_ADDR;

extern s32 g_charged_l23_blast_timer MACRO_ADDR;

extern s32 g_effect_link_count MACRO_ADDR;

extern s32 g_trail_effect_cursors[] MACRO_ADDR;

extern s32 g_effect_link_table[];

extern Edge_0042A8C0 g_trail_edge_table[];

extern float g_star_quad_vertices[][4];

extern float g_trail_ribbon_endpoints[][4];

extern float g_trail_speed_scale __attribute__((sda));

extern s16 g_effect_sound_handle_b __attribute__((sda));

extern s32 g_trail_spawn_index __attribute__((sda));

extern s32 D_L23_001B1B98_2 __asm__("D_L23_001B1B98") __attribute__((sda));

extern float g_trail_size_a __attribute__((sda));

extern float g_trail_size_b __attribute__((sda));

extern float g_trail_size_c __attribute__((sda));

extern float g_trail_matrix_param __attribute__((sda));

extern float g_trail_effect_arg_a __attribute__((sda));

extern s32 g_trail_effect_arg_c __attribute__((sda));

extern s32 g_trail_effect_arg_d __attribute__((sda));

extern s32 g_trail_effect_arg_b __attribute__((sda));

extern u8 g_trail_effect_byte_a __attribute__((sda));

extern u8 g_trail_effect_byte_b __attribute__((sda));

extern s16 g_trail_effect_short_a __attribute__((sda));

extern s16 g_trail_effect_short_b __attribute__((sda));

extern void gfx_free_point_light(s32);

extern void FastVecScale(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern float math_random_float_range(float, float);

extern s32 part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);

extern s32 mothership_is_blast_cooling_down(void);

extern void func_L03_002EFB60(void *, void *, float);

extern void euler_rotation_basis(void *, void *);

extern void multiply_matrix3x3(void *, void *, void *);

extern void transform_vector(void *, void *, void *);

extern void *ribbon_trail_create(void *, u8 *, void *, u8, u8, s16, s16, float, float, float, float, s32, s32, s32,
                               s32, s32);

/* Refreshes the sound handle, builds a rotation from the state's matrix rows and the roll angle, picks the next slot of the 15-entry ring, rewrites the slot's
   two edge vectors from the edge table and starts the effect object with them. */
void hero_spawn_trail_effect(u8 *moby) {
    u8 *vars;
    float m[16] __attribute__((aligned(16)));
    float v60[4] __attribute__((aligned(16)));
    float v70[4] __attribute__((aligned(16)));
    float m80[12] __attribute__((aligned(16)));
    float vB0[4] __attribute__((aligned(16)));
    float vC0[4] __attribute__((aligned(16)));
    float f20;
    float f21;
    float f22;
    float r1;
    float r2;
    float r3;
    s32 flag;
    float *rot;
    s32 e;
    u8 *hero;

    if (g_mothership_boss_moby != 0) {
        g_star_quad_scale = g_mothership_scale_factor * g_trail_speed_scale;
        if (g_effect_sound_handle_b != -1) {
            gfx_free_point_light(g_effect_sound_handle_b);
        }
        FastVecScale(v60, g_mothership_boss_moby + 0xE0, 5.0f);
        FastVecAdd(v60, v60, g_mothership_boss_moby + 0x10);
        r1 = math_random_float_range(0.0f, 1.3f) + 1.3f;
        r2 = math_random_float_range(0.0f, 1.3f) + 1.3f;
        r3 = math_random_float_range(0.0f, 1.35f) + 1.6f;
        g_effect_sound_handle_b = part_l00_alloc_effect_slot_2(v60, 10.0f, 0.0f, r1, r2, r3);
        if (mothership_is_blast_cooling_down() == 0) {
            flag = 0;
            f21 = g_trail_size_a - g_trail_size_a * 0.5f;
            f20 = g_trail_size_b - g_trail_size_b * 0.5f;
            f22 = g_trail_size_c * 0.5f;
        } else {
            flag = 1;
            f21 = g_trail_size_a;
            f22 = g_trail_size_c * 1.6f;
            f20 = g_trail_size_b;
        }
        vars = *(u8 **)(moby + 0x68);
        hero = g_mothership_boss_moby;
        qcopy_nc(m, hero + 0xC0);
        qcopy_nc(m + 4, hero + 0xD0);
        qcopy_nc(m + 8, hero + 0xE0);
        qzero_nc(m + 12);
        func_L03_002EFB60(m, m, g_trail_matrix_param);
        qcopy(m + 12, g_mothership_boss_moby + 0x10);
        m[15] = 1.0f;
        rot = m;
        qzero_nc(v70);
        v70[2] = *(float *)vars;
        euler_rotation_basis(m80, v70);
        multiply_matrix3x3(rot, rot, m80);
        g_trail_spawn_index = g_trail_spawn_index + 1;
        D_L23_001B1B98_2 = g_trail_spawn_index % 15;
        if (g_charged_l23_blast_timer < 0) {
            if (g_charged_l23_blast_timer >= -0x45) {
                g_trail_effect_cursors[D_L23_001B1B98_2] = g_trail_effect_cursors[D_L23_001B1B98_2] + 1;
            }
        }
        g_trail_effect_cursors[D_L23_001B1B98_2] = g_trail_effect_cursors[D_L23_001B1B98_2] % g_effect_link_count;
        e = g_effect_link_table[g_trail_effect_cursors[D_L23_001B1B98_2]];
        transform_vector(vB0, g_star_quad_vertices[g_trail_edge_table[e].a], m);
        transform_vector(vC0, g_star_quad_vertices[g_trail_edge_table[e].b], m);
        qcopy_nc(g_trail_ribbon_endpoints[D_L23_001B1B98_2 * 2], vB0);
        qcopy_nc(g_trail_ribbon_endpoints[D_L23_001B1B98_2 * 2 + 1], vC0);
        ribbon_trail_create(g_trail_ribbon_endpoints[D_L23_001B1B98_2 * 2], moby, g_trail_ribbon_endpoints[D_L23_001B1B98_2 * 2 + 1],
                          g_trail_effect_byte_a, g_trail_effect_byte_b, g_trail_effect_short_a, g_trail_effect_short_b, f21, f20, f22,
                          g_trail_effect_arg_a, g_trail_effect_arg_b, g_trail_effect_arg_c, flag, g_trail_effect_arg_d, 0);
    }
}
