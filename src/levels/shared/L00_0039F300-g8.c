#include "names.h"
/* func_L00_0039F300 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections). */
#include "include_asm.h"
#include "names.h"

/* Functions of L00_0038F178.c whose float constants the retail build reached through $gp. */

extern void math_apply_axis_rotation_to_quat(char *a, char *b, char *c, float value);

extern void vec_scale_to_length(char *a, char *b, float value);

extern char g_nanotech_ball_axes[];

extern char g_nanotech_ball_basis_vectors[];

extern float g_effect_vector_rotation_angle __attribute__((sda));

extern float g_effect_vector_length __attribute__((sda));

/* Fills eight 0x10-byte records: two helpers per record, the second one a quarter scale. */

void part_init_effect_vector_table(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        math_apply_axis_rotation_to_quat(g_nanotech_ball_axes + i * 0x10, g_nanotech_ball_axes + i * 0x10, g_nanotech_ball_basis_vectors + i * 0x10, g_effect_vector_rotation_angle);
        vec_scale_to_length(g_nanotech_ball_axes + i * 0x10, g_nanotech_ball_axes + i * 0x10, g_effect_vector_length);
    }
}
