#include "names.h"
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
extern float IntToFloat(int);
extern unsigned int FastTweenColor(int, int, float);
extern u64 GetEffectTextureDescriptor(int);
extern void mat_from_rotation(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
extern int g_trail_texture_id __attribute__((sda));
extern int g_trail_flags_a __attribute__((sda));
extern int g_trail_flags_b __attribute__((sda));
typedef struct { float u, v; } UiTexCoord;
extern UiTexCoord g_trail_uv_table[] __attribute__((sda));
extern UiTexCoord D_001A89E0_gp[] SDATA(D_001A89E0);

/* Draws a fading ribbon trail behind a moving object by joining its past positions. */
void part_draw_trail_ribbon(UiVector *vertices, int vertex_count, UiVector *positions,
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
    increment = 1.0f / IntToFloat(steps - 1);
    t = increment * blend;
    color = FastTweenColor(first_color, last_color, increment);
    m = matrix;
    tp = &matrix[3];
    for (i = 0; i < (vertex_count >> 1); i++) {
        packets[i].texture = GetEffectTextureDescriptor(g_trail_texture_id);
        packets[i].state = 0xFF9000000260UL;
        packets[i].primitive = 5;
        packets[i].flags = ((long)g_trail_flags_a << 2) | ((long)g_trail_flags_b << 6) | 0x8000000000UL;
        packets[i].colors[0] = color;
        packets[i].colors[1] = color;
        for (j = 0; j < 4; j++) {
            packets[i].uv[j][0] = D_001A89E0_gp[j].u;
            packets[i].uv[j][1] = g_trail_uv_table[j].v;
        }
    }
    cur = phase;
    mat_from_rotation(&rotations[cur], m);
    tp->bits = positions[cur].bits;
    matrix[3].f[3] = 1.0f;
    for (k = 0; k < vertex_count; k++)
        transform_vector(&packets[k >> 1].vertices[k & 1], vertices + k, m);
    for (step = 1; step < steps; step = next) {
        unsigned int next_color;
        cur = (cur + steps - 1) % steps;
        mat_from_rotation(&rotations[cur], m);
        tp->bits = positions[cur].bits;
        matrix[3].f[3] = 1.0f;
        next_color = FastTweenColor(first_color, last_color, t);
        t += increment;
        if (t > 1.0f)
            t = 1.0f;
        next = step + 1;
        for (v = 0; v < vertex_count; v++) {
            transform_vector(&packets[v >> 1].vertices[ring + (v & 1)], vertices + v, m);
            packets[v >> 1].colors[ring + (v & 1)] = next_color;
        }
        ring = (ring + 2) % 4;
        for (n = 0; n < (vertex_count >> 1); n++)
            draw_world_quad(&packets[n], 0, 1);
    }
}
