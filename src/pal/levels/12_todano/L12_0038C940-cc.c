#include "names.h"
/* func_PAL_L12_0038C940, the PAL copy of func_L12_00389BC0: the same C, where wrap state[5] (({e}) * 8.0f). */
#include "common.h"

typedef struct { float rows[4][4]; } TodanoMatrix;
extern TodanoMatrix g_water_wave_matrix __attribute__((sda));
/* The initialization uses GP addressing; updates use absolute field addresses. */
extern TodanoMatrix matrixGP SDATA(D_L12_001AEE40);
extern unsigned char g_hero_position[];
extern int g_water_wave_state_id __attribute__((sda));
extern int g_frame_l12_counter[] __attribute__((sda));
extern float g_water_wave_position[4] __attribute__((aligned(16), sda));
extern float g_water_wave_speed_min SDATA(D_L12_001AEF4C);
extern float g_water_wave_speed_max SDATA(D_L12_001AEF50);
extern void gfx_draw_water_wave_strips(void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern float vec_distance_xy(void *, void *);

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern Collision g_collision_l12_result;
extern Material g_item_l12_material_table[];
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_b(float);
/* func_L12_002CF7B0 is in the sibling file L12_002CF7B0-decider.c (its own profile). */

/* func_L12_002FFF88 is in the sibling file L12_002CF7B0-g8.c: it reads a
   small-data global through $gp. */

/* func_L12_00300410 is in the sibling file L12_00300410-g8.c. */

/* func_L12_0035A838 is defined in L12_0035A838-g8.c (it reads its list through $gp). */

/* func_L12_00388038 is in the sibling file L12_002CF7B0-g8.c: its body
   reads a small-data global through $gp. */

/* func_L12_00388090 is defined in L12_00388090-flags-g8.c. */

/* func_L12_00389988 is defined in L12_00389988-g64.c. */

/* Updates the Todano water surface: sets up the wave offsets, then animates the wave matrix and draws it when the hero is near. */
void water_wave_update_pal(unsigned char *moby)
{
    float *wave_state = *(float **)(moby + 0x68);
    float wave_a, wave_b, wave_c, wave_d;
    int row_count, state_id = moby[0x20];
    float *vec;
    switch (state_id) {
    case 0:
        wave_state[0] = 0.0f;
        wave_state[1] = 0.25f;
        wave_state[2] = 0.5f;
        wave_state[3] = 0.75f;
        wave_state[8] = 1.0f;
        wave_state[9] = 1.25f;
        wave_state[10] = 1.5f;
        wave_state[11] = 1.75f;
        moby[0x20] = 1;
        moby[0x30] = 255;
        if (matrixGP.rows[0][0] > 1000.0f) {
            vec = matrixGP.rows[0];
            row_count = 3;
            do {
                float x = vec[0] * 0.01f;
                float y = vec[1] * 0.01f;
                float z = vec[2] * 0.01f;
                vec[0] = x;
                vec[1] = y;
                vec[2] = z;
                vec += 4;
            } while (--row_count >= 0);
        }
        break;
    case 1:
        gfx_add_draw_callback_first(gfx_draw_water_wave_strips, moby);
        g_water_wave_state_id = state_id;
        qcopy(g_water_wave_position, g_hero_position);
        *(short *)(g_hero_position + 0x17E) = 5;
        g_water_wave_position[3] = 48.0f;
        g_water_wave_position[2] = math_fast_sin_or_cos_b((float)(g_frame_l12_counter[0] % 360) * 0.01744444482028484344482421875f - 3.14f) * 0.25f + 59.5f;
        wave_state[4] += ((wave_state[5]) * 1.2f);
        if (wave_state[4] >= 8.0f) wave_state[4] -= 8.0f;
        wave_a = math_fast_sin_or_cos_b(wave_state[0] * 3.141590118408203125f) * 0.01f;
        wave_b = math_fast_sin_or_cos_b(wave_state[1] * 3.141590118408203125f) * 0.025f;
        wave_c = math_fast_sin_or_cos_b(wave_state[2] * 3.141590118408203125f) * 0.01f;
        wave_d = math_fast_sin_or_cos_b(wave_state[3] * 3.141590118408203125f) * 0.025f;
        g_water_wave_matrix.rows[0][2] += wave_a;
        g_water_wave_matrix.rows[1][2] += wave_b;
        g_water_wave_matrix.rows[2][2] += wave_c;
        g_water_wave_matrix.rows[3][2] += wave_d;
        wave_state[0] += 0.01f;
        wave_state[1] += 0.01f;
        wave_state[2] += 0.01f;
        wave_state[3] += 0.01f;
        if (wave_state[0] > 2.0f) wave_state[0] = 0.0f;
        if (wave_state[1] > 2.0f) wave_state[1] = 0.0f;
        if (wave_state[2] > 2.0f) wave_state[2] = 0.0f;
        if (wave_state[3] > 2.0f) wave_state[3] = 0.0f;
        wave_state[5] = math_random_float_range(g_water_wave_speed_min, g_water_wave_speed_max);
        break;
    case 2:
        if (vec_distance_xy(moby + 0x10, g_hero_position) < 64.0f)
            gfx_add_draw_callback_third(gfx_draw_water_wave_strips, moby);
        break;
    }
}

/* func_L12_00389F80 uses small data in L12_002CF7B0-g8.c. */

