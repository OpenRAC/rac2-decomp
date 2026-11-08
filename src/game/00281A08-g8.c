/* func_00281A08: trail ribbon draw. Own unit: -G8 for the GP loads of D_001A89D0..D8 and
   the u column, -g for the nop pair in front of div.s.

   The step + 1 copy, the matrix pointer and the translation pointer are plain locals
   (next, m, tp): reload gives their spill slots in declaration order, ahead of the gcse
   PRE register for vertex_count >> 1. As PRE expressions they took slots in hash-bucket
   order instead and swapped two of them. */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 bits; float f[4]; } UiVector;
typedef struct { UiVector vertices[4]; unsigned int colors[4]; float uv[4][2];
                 u64 primitive, texture, state, flags; } UiDrawPacket;
extern float func_00283CE0(int);
extern unsigned int func_00283D38(int, int, float);
extern u64 func_0027C878(int);
extern void func_002839D0(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);
extern int D_001A89D0 __attribute__((sda));
extern int D_001A89D4 __attribute__((sda));
extern int D_001A89D8 __attribute__((sda));
typedef struct { float u, v; } UiTexCoord;
extern UiTexCoord D_001A89E0[] __attribute__((sda));
extern UiTexCoord D_001A89E0_gp[] SDATA(D_001A89E0);

void func_00281A08(UiVector *vertices, int vertex_count, UiVector *positions,
                   UiVector *rotations, int phase, int steps,
                   int first_color, int last_color, float blend)
{
    UiDrawPacket packets[16];
    UiVector matrix[4];
    int ring, step, next;
    UiVector *m, *tp;
    int i, j, k, n, v, cur;
    float increment, t;
    unsigned int color;

    if (steps < 2)
        return;
    ring = 2;
    increment = 1.0f / func_00283CE0(steps - 1);
    t = increment * blend;
    color = func_00283D38(first_color, last_color, increment);
    m = matrix;
    tp = &matrix[3];
    for (i = 0; i < (vertex_count >> 1); i++) {
        packets[i].texture = func_0027C878(D_001A89D0);
        packets[i].state = 0xFF9000000260UL;
        packets[i].primitive = 5;
        packets[i].flags = ((long)D_001A89D4 << 2) | ((long)D_001A89D8 << 6) | 0x8000000000UL;
        packets[i].colors[0] = color;
        packets[i].colors[1] = color;
        for (j = 0; j < 4; j++) {
            packets[i].uv[j][0] = D_001A89E0_gp[j].u;
            packets[i].uv[j][1] = D_001A89E0[j].v;
        }
    }
    cur = phase;
    func_002839D0(&rotations[cur], m);
    tp->bits = positions[cur].bits;
    matrix[3].f[3] = 1.0f;
    for (k = 0; k < vertex_count; k++)
        func_002830C0(&packets[k >> 1].vertices[k & 1], vertices + k, m);
    for (step = 1; step < steps; step = next) {
        unsigned int next_color;
        cur = (cur + steps - 1) % steps;
        func_002839D0(&rotations[cur], m);
        tp->bits = positions[cur].bits;
        matrix[3].f[3] = 1.0f;
        next_color = func_00283D38(first_color, last_color, t);
        t += increment;
        if (t > 1.0f)
            t = 1.0f;
        next = step + 1;
        for (v = 0; v < vertex_count; v++) {
            func_002830C0(&packets[v >> 1].vertices[ring + (v & 1)], vertices + v, m);
            packets[v >> 1].colors[ring + (v & 1)] = next_color;
        }
        ring = (ring + 2) % 4;
        for (n = 0; n < (vertex_count >> 1); n++)
            func_00280B90(&packets[n], 0, 1);
    }
}
