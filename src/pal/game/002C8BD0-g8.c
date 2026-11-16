#include "include_asm.h"
#include "names.h"

extern int FastDecTimer(short *);
extern void FastVecAdd(char *, char *, char *);
extern void part_kill(void *);
extern unsigned char *g_part_tex_falling_drift_table[];
extern float g_falling_spin_param __attribute__((sda));

/* Falling drift particle: moves by its velocity plus a shared vector, spins, and is freed when
   it passes its height limit. */
void part_update_falling_drift_pal(char *self)
{
    char *state = self + 32;
    char *pos;

    if (FastDecTimer((short *)(self + 10)))
        *(float *)(state + 8) -= *(float *)(state + 24);
    pos = self + 16;
    FastVecAdd(pos, pos, state);
    FastVecAdd(pos, pos, *(char **)(state + 28));
    self[8] = (unsigned char)self[8] + *(unsigned char *)(state + 20);
    if ((unsigned char)self[2] == g_part_tex_falling_drift_table[0][0])
        *(float *)(self + 12) += g_falling_spin_param * 4200.0005f;
    if (*(float *)(self + 24) < *(float *)(state + 16))
        part_kill(self);
}
