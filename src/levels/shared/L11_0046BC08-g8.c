#include "common.h"

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vector;

/* One bolt's row of the level's vertex table (640 bytes). */
typedef struct { Vector core[20]; Vector wave[20]; } BoltBuffer;

/* The bolt's state record (object + 0x68). */
typedef struct {
    Vector start;   /* 0x00 */
    Vector end;     /* 0x10 */
    char pad20[12];
    int count;      /* 0x2C */
    int pad30;
    int path;       /* 0x34 */
    int row;        /* 0x38 */
} BoltState;

extern int D_L11_001B25A0 __attribute__((sda));
extern int D_L11_001B25A4 __attribute__((sda));
extern float D_L11_001B25A8 __attribute__((sda));
extern float D_L11_001B25C0 __attribute__((sda));
extern float D_L11_001B25C8 __attribute__((sda));
extern float D_L11_001B25DC __attribute__((sda));
extern BoltBuffer D_L11_00264760[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

/* When the bolt's reset flag is set: lays the row's core points on the straight line
 * from start towards end, one step apart, and clears the jitter and wave phases. */
void func_L11_0046BC08(char *object)
{
    Vector delta, step;
    BoltState *state = *(BoltState **)(object + 0x68);
    Vector *prev;
    int i;

    if (D_L11_001B25A4) {
        D_L11_001B25A4 = 0;
        func_00282CF0(&delta, &state->end, &state->start);
        func_00282F20(&step, &delta, D_L11_001B25A8 / (float)D_L11_001B25A0);
        qcopy_nc(&D_L11_00264760[state->row].core[0], &state->start);
        for (i = 1; i < D_L11_001B25A0; i++) {
            /* Previous point: the row's points from index -1. */
            prev = &D_L11_00264760[state->row].core[-1];
            func_00282CC0(&D_L11_00264760[state->row].core[i], &prev[i], &step);
        }
        D_L11_001B25C0 = 0.0f;
        D_L11_001B25C8 = 0.0f;
        D_L11_001B25DC = 0.0f;
    }
}
