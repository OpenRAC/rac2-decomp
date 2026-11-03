/* Claude Opus 5.5 xhigh tier (opus-1), v2195: 928/928 bytes, 0/28 USA places (74 of 232 rows differ).
 * Profile: its own unit (e.g. src/game/00327038-quads-g8.c) built with -O2 -G8 -ffunction-sections -g;
 * -g matters, because the line notes count towards haifa's region size limit.
 * What works: struct-member reads of D_00189E20.pos give retail's s2 = &pos and the -0xE0 rebase; the
 * static inline ClampUnit pushes the inner loop's sched1 region past MAX_RGN_INSNS (100 luids), so the
 * loop-bottom increments are not hoisted by interblock motion; state + tag[1] + tag[2] first and the
 * alpha OR chain (FIX last) after them reproduce the whole prologue schedule.
 * Remaining: (1) gcse PRE inserts face+1 at the end of the outer loop head (PRE/HOIST bb 1) and turns
 * face++ into a copy, so face is s5 plus an fp copy (retail: one fp, addiu fp,fp,1 in the jal slot);
 * (2) the hoisted u/v starts (spilled to 0xF4/0xF8) get s2/s1, retail s1/s2 (declaration order has no
 * effect); (3) matrix[3] temps f2/f3/f4 vs retail f4/f2/f3; (4) a0 vs v1 for the D_0026B210 and
 * D_00235D00 address temporaries. Needs extern ints with __attribute__((sda)) in the -G8 unit.
 */
#include "include_asm.h"

typedef struct {
    float x;
    float y;
    float z;
    float w;
} RenderVec __attribute__((aligned(16)));

typedef struct {
    RenderVec vertex[4];
    unsigned int color[4];
    float uv[8];
    long long tag[4];
    RenderVec matrix[4];
} RenderPacket;

typedef struct {
    char pad_000[0xE0];
    RenderVec pos;
} HeroPosBlock;

extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_00282DD8(void *, const void *, const void *);
extern void func_00282D30(void *, const void *, float);
extern void func_002830C0(void *, const void *, const void *);
extern void func_0027C768(void *, float *, float *);
extern float func_00283180(float);
extern float func_00283B98(float, float);
extern void func_00280B90(void *, void *, int);
extern void func_002FE8D8(void *, void *);

extern RenderVec D_001B5340;
extern HeroPosBlock D_00189E20;
extern long long D_001B2810;
extern int D_001B059C __attribute__((sda));
extern int D_001B05A0 __attribute__((sda));
extern int D_001B05A4 __attribute__((sda));
extern int D_001B05A8 __attribute__((sda));
extern int D_001B05AC __attribute__((sda));
extern unsigned int D_001B05B0 __attribute__((sda));
extern short D_0026B210[][2];
extern RenderVec D_0026AA00[];
extern float D_00235D00[][2];

static inline void ClampUnit(float *value)
{
    if (*value > 1.0f) {
        *value = 1.0f;
    } else if (*value < 0.0f) {
        *value = 0.0f;
    }
}

void func_0032C2E8(char *object)
{
    RenderPacket packet;
    RenderVec up;
    RenderVec difference;
    char *state;
    int face;
    int corner;
    short (*quad)[2];
    float *u;
    float *v;
    float *phase;

    state = *(char **)(object + 0x68);
    packet.tag[1] = D_001B2810;
    packet.tag[2] = 0xFF9000000260LL;
    packet.tag[3] = (long long)D_001B059C;
    packet.tag[3] |= (long long)D_001B05A0 << 2;
    packet.tag[3] |= (long long)D_001B05A4 << 4;
    packet.tag[3] |= (long long)D_001B05A8 << 6;
    packet.tag[3] |= (long long)D_001B05AC << 32;
    packet.tag[0] = 0;

    func_002FE8D8(&D_00189E20.pos, &up);
    func_00282CF0(&difference, &D_001B5340, &D_00189E20.pos);
    func_00282F20(&packet.matrix[0], &difference, 1.0f);
    func_00282DD8(&packet.matrix[1], &packet.matrix[0], &up);
    func_00282F20(&packet.matrix[1], &packet.matrix[1], 1.0f);
    func_00282DD8(&packet.matrix[2], &packet.matrix[1], &packet.matrix[0]);
    func_00282F20(&difference, &difference, 2.0f);
    packet.matrix[3].x = D_00189E20.pos.x + difference.x;
    packet.matrix[3].y = D_00189E20.pos.y + difference.y;
    packet.matrix[3].z = D_00189E20.pos.z + difference.z;
    packet.matrix[3].w = 1.0f;

    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = D_001B05B0;

    for (face = 0; face < 127; face++) {
        quad = &D_0026B210[face * 4];
        u = packet.uv;
        v = packet.uv + 1;
        for (corner = 0; corner < 4; corner++) {
            int index = quad[corner][1];

            func_00282D30(&packet.vertex[corner], &D_0026AA00[quad[corner][0]], *(float *)(state + 0x14) * 4.0f);
            func_002830C0(&packet.vertex[corner], &packet.vertex[corner], packet.matrix);
            func_0027C768(&packet.vertex[corner], &packet.uv[corner * 2], &packet.uv[corner * 2 + 1]);
            *u += func_00283180(D_00235D00[index][0]) * 0.01f;
            *v += func_00283180(D_00235D00[index][1]) * 0.02f;
            ClampUnit(u);
            ClampUnit(v);
            u += 2;
            v += 2;
        }
        func_00280B90(&packet, 0, 0);
    }

    phase = D_00235D00[0];
    for (face = 136; face >= 0; face--) {
        phase[0] = func_00283B98(phase[0], 0.6283186078071594f);
        phase[1] = func_00283B98(phase[1], 0.3141593039035797f);
        phase += 2;
    }
}
