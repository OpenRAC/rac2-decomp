#include "names.h"
/* func_L00_0039F300 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections). */
#include "include_asm.h"
#include "names.h"

/* Functions of L00_0038F178.c whose float constants the retail build reached through $gp. */

extern void math_apply_axis_rotation_to_quat(char *a, char *b, char *c, float value);

extern void vec_scale_to_length(char *a, char *b, float value);

extern char D_L00_0023A670[];

extern char D_L00_0023A6F0[];

extern float D_L00_001AF448 __attribute__((sda));

extern float D_L00_001AF470 __attribute__((sda));

/* Fills eight 0x10-byte records: two helpers per record, the second one a quarter scale. */

void part_init_effect_vector_table(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        math_apply_axis_rotation_to_quat(D_L00_0023A670 + i * 0x10, D_L00_0023A670 + i * 0x10, D_L00_0023A6F0 + i * 0x10, D_L00_001AF448);
        vec_scale_to_length(D_L00_0023A670 + i * 0x10, D_L00_0023A670 + i * 0x10, D_L00_001AF470);
    }
}
