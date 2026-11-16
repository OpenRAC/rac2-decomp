#include "include_asm.h"
#include "names.h"

extern int FastDecTimer(short *);
extern void FastVecAdd(char *, char *, char *);
extern void part_kill(void *);
extern unsigned char *g_part_tex_spinning_fall_table[];
extern float g_falling_spin_param __attribute__((sda));

void part_update_spinning_fall_pal(char *self)
{
    char *state = self + 32;
    if (FastDecTimer((short *)(self + 10)))
        *(float *)(state + 8) -= *(float *)(state + 24);
    FastVecAdd(self + 16, self + 16, state);
    self[8] = (unsigned char)self[8] + *(unsigned char *)(state + 20);
    if ((unsigned char)self[2] == g_part_tex_spinning_fall_table[0][0])
        *(float *)(self + 12) += g_falling_spin_param * 4200.0005f;
    if (*(float *)(self + 24) < *(float *)(state + 16))
        part_kill(self);
}
