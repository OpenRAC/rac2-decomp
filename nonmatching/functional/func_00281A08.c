/* functional: high. Same calls, arguments, reads and writes as retail. The 16-byte lq/sq copy of the position is four word copies, and the UV table is one name (D_001A89E0, four u/v pairs) where retail forms the v column's address separately as 0x1A89E4. */

/* Draws a trail ribbon of `steps` segments: builds up to 16 strip packets (0x90 bytes: four vertices, four
 * colours, four UVs from D_001A89E0, primitive 5, texture func_0027C878(D_001A89D0), GS state words), places
 * the first ring of `vertices` (pairs) with the rotation/position history at `phase`, then for each further
 * step walks the history backwards (phase - 1 mod steps), transforms the vertices into the next ring slot,
 * colours them with the first..last colour blend (clamped to 1), and submits every packet
 * (func_00280B90(packet, 0, 1)). */

typedef struct {
    float vertices[4][4];       /* 0x00 */
    unsigned int colors[4];     /* 0x40 */
    float uv[4][2];             /* 0x50 */
    unsigned long primitive;    /* 0x70 */
    unsigned long texture;      /* 0x78 */
    unsigned long state;        /* 0x80 */
    unsigned long flags;        /* 0x88 */
} TrailStripPacket;

extern float func_00283CE0(int);
extern unsigned int func_00283D38(int, int, float);
extern unsigned long func_0027C878(int);
extern void func_002839D0(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);
extern int D_001A89D0 __attribute__((sda));
extern int D_001A89D4 __attribute__((sda));
extern int D_001A89D8 __attribute__((sda));
extern float D_001A89E0[8] __attribute__((sda));

void func_00281A08(float (*vertices)[4], int vertex_count, float (*positions)[4],
                   float (*rotations)[4], int phase, int steps,
                   int first_color, int last_color, float blend)
{
    TrailStripPacket packets[16];
    float matrix[4][4] __attribute__((aligned(16)));
    int ring, i, k, step, pairs;
    float increment;
    unsigned int color;

    if (steps < 2)
        return;
    ring = 2;
    increment = 1.0f / func_00283CE0(steps - 1);
    blend = increment * blend;
    color = func_00283D38(first_color, last_color, increment);
    pairs = vertex_count >> 1;
    for (i = 0; i < pairs; i++) {
        packets[i].texture = func_0027C878(D_001A89D0);
        packets[i].colors[1] = color;
        packets[i].state = 0xFF9000000260UL;
        packets[i].primitive = 5;
        packets[i].flags = ((unsigned long)(long)D_001A89D4 << 2) | ((unsigned long)(long)D_001A89D8 << 6)
                         | 0x8000000000UL;
        packets[i].colors[0] = color;
        for (k = 0; k < 4; k++) {
            packets[i].uv[k][0] = D_001A89E0[k * 2];
            packets[i].uv[k][1] = D_001A89E0[k * 2 + 1];
        }
    }
    func_002839D0(rotations[phase], matrix);
    for (k = 0; k < 4; k++)
        matrix[3][k] = positions[phase][k];
    matrix[3][3] = 1.0f;
    for (i = 0; i < vertex_count; i++)
        func_002830C0(packets[i >> 1].vertices[i & 1], vertices[i], matrix);
    for (step = 1; step < steps; step++) {
        unsigned int next_color;
        phase = (phase + steps - 1) % steps;
        func_002839D0(rotations[phase], matrix);
        for (k = 0; k < 4; k++)
            matrix[3][k] = positions[phase][k];
        matrix[3][3] = 1.0f;
        next_color = func_00283D38(first_color, last_color, blend);
        blend += increment;
        if (1.0f < blend)
            blend = 1.0f;
        for (i = 0; i < vertex_count; i++) {
            int slot = ring + (i & 1);
            func_002830C0(packets[i >> 1].vertices[slot], vertices[i], matrix);
            packets[i >> 1].colors[slot] = next_color;
        }
        ring = (ring + 2) % 4;
        for (i = 0; i < pairs; i++)
            func_00280B90(&packets[i], 0, 1);
    }
}
