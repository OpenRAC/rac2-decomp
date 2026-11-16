#include "include_asm.h"

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
void hero_spawn_trail_effect_pal(u8 *moby) {
    u8 *vars;
    float matrix[16] __attribute__((aligned(16)));
    float light_pos[4] __attribute__((aligned(16)));
    float roll_vec[4] __attribute__((aligned(16)));
    float roll_matrix[12] __attribute__((aligned(16)));
    float edge_a[4] __attribute__((aligned(16)));
    float edge_b[4] __attribute__((aligned(16)));
    float size_b;
    float size_a;
    float size_c;
    float color_r;
    float color_g;
    float color_b;
    s32 flag;
    float *matrix_ptr;
    s32 edge_index;
    u8 *boss;

    if (g_mothership_boss_moby != 0) {
        g_star_quad_scale = g_mothership_scale_factor * g_trail_speed_scale;
        if (g_effect_sound_handle_b != -1) {
            gfx_free_point_light(g_effect_sound_handle_b);
        }
        FastVecScale(light_pos, g_mothership_boss_moby + 0xE0, 5.0f);
        FastVecAdd(light_pos, light_pos, g_mothership_boss_moby + 0x10);
        color_r = math_random_float_range(0.0f, 1.3f) + 1.3f;
        color_g = math_random_float_range(0.0f, 1.3f) + 1.3f;
        color_b = math_random_float_range(0.0f, 1.35f) + 1.6f;
        g_effect_sound_handle_b = part_l00_alloc_effect_slot_2(light_pos, 10.0f, 0.0f, color_r, color_g, color_b);
        if (mothership_is_blast_cooling_down() == 0) {
            flag = 0;
            size_a = g_trail_size_a - g_trail_size_a * 0.5f;
            size_b = g_trail_size_b - g_trail_size_b * 0.5f;
            size_c = g_trail_size_c * 0.5f;
        } else {
            flag = 1;
            size_a = g_trail_size_a;
            size_c = g_trail_size_c * 1.6f;
            size_b = g_trail_size_b;
        }
        vars = *(u8 **)(moby + 0x68);
        boss = g_mothership_boss_moby;
        qcopy_nc(matrix, boss + 0xC0);
        qcopy_nc(matrix + 4, boss + 0xD0);
        qcopy_nc(matrix + 8, boss + 0xE0);
        qzero_nc(matrix + 12);
        func_L03_002EFB60(matrix, matrix, g_trail_matrix_param);
        qcopy(matrix + 12, g_mothership_boss_moby + 0x10);
        matrix[15] = 1.0f;
        matrix_ptr = matrix;
        qzero_nc(roll_vec);
        roll_vec[2] = *(float *)vars;
        euler_rotation_basis(roll_matrix, roll_vec);
        multiply_matrix3x3(matrix_ptr, matrix_ptr, roll_matrix);
        g_trail_spawn_index = g_trail_spawn_index + 1;
        D_L23_001B1B98_2 = g_trail_spawn_index % 15;
        if (g_charged_l23_blast_timer < 0) {
            if (g_charged_l23_blast_timer >= -0x39) {
                g_trail_effect_cursors[D_L23_001B1B98_2] = g_trail_effect_cursors[D_L23_001B1B98_2] + 1;
            }
        }
        g_trail_effect_cursors[D_L23_001B1B98_2] = g_trail_effect_cursors[D_L23_001B1B98_2] % g_effect_link_count;
        edge_index = g_effect_link_table[g_trail_effect_cursors[D_L23_001B1B98_2]];
        transform_vector(edge_a, g_star_quad_vertices[g_trail_edge_table[edge_index].a], matrix);
        transform_vector(edge_b, g_star_quad_vertices[g_trail_edge_table[edge_index].b], matrix);
        qcopy_nc(g_trail_ribbon_endpoints[D_L23_001B1B98_2 * 2], edge_a);
        qcopy_nc(g_trail_ribbon_endpoints[D_L23_001B1B98_2 * 2 + 1], edge_b);
        ribbon_trail_create(g_trail_ribbon_endpoints[D_L23_001B1B98_2 * 2], moby, g_trail_ribbon_endpoints[D_L23_001B1B98_2 * 2 + 1],
                          g_trail_effect_byte_a, g_trail_effect_byte_b, g_trail_effect_short_a, g_trail_effect_short_b, size_a, size_b, size_c,
                          g_trail_effect_arg_a, g_trail_effect_arg_b, g_trail_effect_arg_c, flag, g_trail_effect_arg_d, 0);
    }
}
