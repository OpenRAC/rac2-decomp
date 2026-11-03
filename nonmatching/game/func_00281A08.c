/* Claude Opus 5.5, task v2193; NOT MATCHING.
   Own unit, flags: -O2 -G8 -ffunction-sections -g -frac2-qcopy -frac2-qcopy-barrier
   check.py: 0 of 7 places; 980/980 bytes, frame 0xA00 matches. Only 10 rows
   differ, all spill-slot offsets of four gcse PRE registers: ours trans 0x964,
   matrix 0x968, half 0x96C, step+1 0x970; retail step+1 0x964, matrix 0x968,
   trans 0x96C, half 0x970. Bucket model (raw step+1 = 14030+step regno,
   half = 14044+85, matrix 16334, trans 16382; T = 93 now): matrix before trans
   needs T 85 or 97, and then step/half bases near pseudo 130/110, so retail
   probably differs in structure (half or step+1 not a pass-1 PRE register).
   colors[0] before colors[1] keeps sched1's dead-base preference off the
   other stores (retail store order). -G8 + SDATA view gives GP .u loads and
   the incomplete sda array keeps .v absolute; declarations below.
*/

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
    int ring, i, j, k, n, v, step, cur;
    float increment, t;
    unsigned int color;

    if (steps < 2)
        return;
    ring = 2;
    increment = 1.0f / func_00283CE0(steps - 1);
    t = increment * blend;
    color = func_00283D38(first_color, last_color, increment);
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
    func_002839D0(&rotations[cur], matrix);
    matrix[3].bits = positions[cur].bits;
    matrix[3].f[3] = 1.0f;
    for (k = 0; k < vertex_count; k++)
        func_002830C0(&packets[k >> 1].vertices[k & 1], vertices + k, matrix);
    for (step = 1; step < steps; step++) {
        unsigned int next_color;
        cur = (cur + steps - 1) % steps;
        func_002839D0(&rotations[cur], matrix);
        matrix[3].bits = positions[cur].bits;
        matrix[3].f[3] = 1.0f;
        next_color = func_00283D38(first_color, last_color, t);
        t += increment;
        if (t > 1.0f)
            t = 1.0f;
        for (v = 0; v < vertex_count; v++) {
            func_002830C0(&packets[v >> 1].vertices[ring + (v & 1)], vertices + v, matrix);
            packets[v >> 1].colors[ring + (v & 1)] = next_color;
        }
        ring = (ring + 2) % 4;
        for (n = 0; n < (vertex_count >> 1); n++)
            func_00280B90(&packets[n], 0, 1);
    }
}
