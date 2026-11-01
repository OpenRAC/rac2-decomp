/* opus-1 (Claude Opus 5.5, xhigh), task v1948, USA v1.01: 2588/2444 bytes, 0/1 places.
 * Unit: its own file, e.g. src/levels/12_todano/L12_004149B8-field.c, flags
 *   -O2 -G0 -ffunction-sections -mno-split-addresses -g
 * (-mno-split-addresses: retail's adjacent lui/lw pairs for D_L12_001B2F8C are gas
 * macro expansion; -g: the nop pair before div.s.) All declarations are below.
 *
 * BLOCKER (compiler): the six packet copies (`rotated = packet;`, `side = packet;`)
 * are compiler block moves in retail, but 16-byte ones: block_move_loop's shape
 * (final_src = src + 0x80, unaligned loop label, bne src/final_src, leftover copy
 * through final_src) with lq/lq/sq/sq and reload scratch registers (a1/a2+t1, a2/a3+v0,
 * t0/t1+a2, a0/a1+t0, ...). This compiler's movstrsi only uses ld/sd (8-byte units):
 * each copy is 6 words longer here (that is the 144-byte excess), but its scratch
 * registers are the same as retail's (ld a1..t0 / lq a1,a2; trailer t1). The same
 * 16-byte block move is in func_002DE990 (0x2DEB20: addiu v1,v0,0xE0; lq;lq;sq;sq).
 * A C quadword loop cannot stand in: a do/while gets an aligned label (+nop), and its
 * data temporaries go through local-alloc (v0/v1), shifting the whole allocation; a
 * goto loop gives 2436/2444 bytes with different registers. Do not retry those.
 *
 * Stack layout is exact (frame 0x330): packet 0x00, matrix 0x90, rotation 0xD0,
 * angle 0x110, offset 0x120; corner 0x130; loop 1 copy 0x140; loop 2 copies
 * 0x130/0x1D0; loop 3 copies 0x130/0x1C0. Plain blocks never share stack slots in
 * this compiler; GNU statement expressions free their locals as temp slots, which
 * are then combined and split, which gives exactly retail's offsets. NEEDS A RULING:
 * the `({ ... });` blocks have only this lifetime/allocation effect (cf. the
 * do/while(0) ban); they model scope ends that the original likely got from macros.
 *
 * With the struct copies set aside, only these differ (everything else, including
 * every other GPR/FPR and all spill slots but two, matches):
 *  - 0x41C2FC..0x41C360: the 0.5 constant takes $f2 (retail $f1), because pseudos
 *    for -(width*0.5f) carry an $f1 preference here; and the loop-2 preheader copies
 *    come out as mov.s f25 (0.5) before mov.s f27 (-w/2), retail the reverse.
 *  - spill slots 0x26C/0x270 (sp+0x20 / sp+0x200 addresses) are swapped. They are
 *    gcse PRE reaching registers numbered by hash % buckets; raw hash of
 *    (plus at C) is 14030+C. This source has 241 buckets; only 233 or 237 give
 *    retail's order, i.e. retail's source has ~5-11 fewer insns before gcse.
 *    Initializers cannot help (they add insns). With the four x-store loops and the
 *    two bottom-z loops written descending (for (i = 3; i >= 0; i--)) it is 237 and
 *    the spill slots match, but then the bottom-z copy mov.s f0,f28 follows
 *    `li v1,1` (retail precedes it: the counter is created by loop reversal, so those
 *    loops are ascending in the source, as here).
 * Measured: ascending store loops `for (i = 0; i < N; i++) x.point[i]...` are reversed
 * by loop.c into retail's descending stores; per-loop counters are needed (one shared
 * `i` lands in $s0 everywhere); `angle` stores precede the height/width loads; the
 * top-z chain stores point[3] first; holding D_L12_001B1D4C in a local hoists it.
 *
 * closer D, 1 November 2026: on branch compiler/block-move-quad the six copies are retail's lq/sq
 * loops and this draft reaches 2444/2444 bytes with 13 words left, the FPR and spill-slot items.
 */
#include "common.h"

typedef int BF88Quad __attribute__((mode(TI)));
typedef union { BF88Quad q; float f[4]; } __attribute__((aligned(16))) BF88Vector;
typedef struct {
    BF88Vector point[4];
    u32 color[4];
    float uv[4][2];
    u64 reserved, texture, setup, state;
} __attribute__((aligned(16))) BF88Packet;
extern u8 *D_L12_001B2F8C;
extern float D_L12_001B1D20[8] SDATA(D_L12_001B1D20);
extern float D_L12_001B1D24[];
extern float D_L12_001B1D40 SDATA(D_L12_001B1D40);
extern float D_L12_001B1D44 SDATA(D_L12_001B1D44);
extern float D_L12_001B1D80 SDATA(D_L12_001B1D80);
extern float D_L12_001B1D84 SDATA(D_L12_001B1D84);
extern s32 D_L12_001B1D14 SDATA(D_L12_001B1D14);
extern s32 D_L12_001B1D18 SDATA(D_L12_001B1D18);
extern s32 D_L12_001B1D1C SDATA(D_L12_001B1D1C);
extern s32 D_L12_001B1D4C SDATA(D_L12_001B1D4C);
extern s32 D_L12_001B1D50 SDATA(D_L12_001B1D50);
extern s32 D_L12_001B1D54 SDATA(D_L12_001B1D54);
extern void func_00283410(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern u64 func_0027C878(int);
extern u32 func_00283D38(u32, u32, float);

void func_L12_0041BF88(u8 *self)
{
    BF88Packet packet;
    BF88Vector matrix[4], rotation[4], angle, offset;
    u8 *p = *(u8 **)(self + 0x68);
    float width, height;
    float h, y, phase, nextPhase, step, halfHeight;
    int i, j, k, n;

    angle.q = 0;
    angle.f[1] = 1.5707964897155762f;
    height = *(float *)(p + 0x44);
    width = *(float *)(p + 0x40);
    func_00283410(rotation, &angle);
    ({
        BF88Vector corner;
        corner.q = 0;
        corner.f[1] = width * 0.5f;
        corner.f[2] = D_L12_001B1D40;
        corner.f[3] = 1.0f;
        offset.q = corner.q;
    });
    func_00283410(matrix, D_L12_001B2F8C + *(int *)p * 128 + 0x70);
    qcopy(&matrix[3], D_L12_001B2F8C + *(int *)p * 128 + 0x30);
    matrix[3].f[2] -= height * 0.5f + 0.5f;
    matrix[3].f[3] = 1.0f;
    {
        u32 color = D_L12_001B1D4C;
        for (n = 0; n < 4; n++) {
            packet.color[n] = color;
            packet.uv[n][0] = D_L12_001B1D20[n * 2];
            packet.uv[n][1] = D_L12_001B1D24[n * 2];
            qcopy(&packet.point[n], &offset);
            if (n < 2) packet.point[n].f[1] = -packet.point[n].f[1];
            if (n & 1) packet.point[n].f[2] = -packet.point[n].f[2];
            packet.point[n].f[2] += 0.25f;
        }
    }
    packet.texture = func_0027C878(D_L12_001B1D14);
    packet.setup = 0xFF9000000260ULL;
    packet.state = ((u64)D_L12_001B1D18 << 2) | ((u64)D_L12_001B1D1C << 6) | 0x8000000000ULL;
    packet.reserved = 0;
    for (h = 0.0f; h <= height - 0.1f; h += 0.5f) {
        for (j = 0; j < 4; j++) {
            if (j >= 2) {
                if (h <= 2.5f) packet.point[j].f[1] = *(float *)(p + 0x34);
                else if (h <= 4.5f) packet.point[j].f[1] = *(float *)(p + 0x38);
                else packet.point[j].f[1] = width;
            }
            packet.point[j].f[2] += 0.5f;
        }
        ({
            BF88Packet rotated;
            rotated = packet;
            for (i = 0; i < 4; i++)
                func_002830C0(&rotated.point[i], &packet.point[i], matrix);
            func_00280B90(&rotated, 0, 1);
        });
    }
    for (k = 0; k < 4; k++) {
        float thickness = D_L12_001B1D44;
        packet.point[k].f[2] -= height;
        if (packet.point[k].f[2] <= 0.0f) thickness = -thickness;
        packet.point[k].f[2] = thickness;
    }
    y = *(float *)(p + 0x34);
    phase = *(float *)(p + 4);
    step = 0.5f / width;
    halfHeight = height * 0.5f;
    for (; y > -(width * 0.5f); y -= 0.5f) {
        nextPhase = phase + step;
        { int j; for (j = 0; j < 4; j++) {
            packet.point[j].f[1] = y;
            if (j & 1) packet.point[j].f[1] = y + 0.5f;
        } }
        { int i; for (i = 0; i < 2; i++) packet.point[i].f[2] = -halfHeight; }
        packet.point[2].f[2] = packet.point[3].f[2] = halfHeight + halfHeight;
        { int i; for (i = 0; i < 4; i++) packet.point[i].f[0] = D_L12_001B1D80; }
        ({
            BF88Packet rotated, side;
            rotated = packet;
            { int i; for (i = 0; i < 4; i++) rotated.point[i].f[0] = D_L12_001B1D80; }
            func_00280B90(&rotated, matrix, 1);
            { int i; for (i = 0; i < 4; i++) rotated.point[i].f[0] = -D_L12_001B1D80; }
            func_00280B90(&rotated, matrix, 1);
            side = packet;
            qcopy(&side.point[0], &packet.point[0]);
            qcopy(&side.point[1], &rotated.point[0]);
            qcopy(&side.point[2], &packet.point[2]);
            qcopy(&side.point[3], &rotated.point[2]);
            func_00280B90(&side, matrix, 1);
            qcopy(&side.point[0], &packet.point[1]);
            qcopy(&side.point[1], &rotated.point[1]);
            qcopy(&side.point[2], &packet.point[3]);
            qcopy(&side.point[3], &rotated.point[3]);
            func_00280B90(&side, matrix, 1);
        });
        { int i; for (i = 0; i < 4; i++)
            packet.color[i] = func_00283D38(D_L12_001B1D50, D_L12_001B1D54, phase); }
        phase = nextPhase;
        if (nextPhase > 0.0f) phase = nextPhase - 1.0f;
    }
    for (y = *(float *)(p + 0x38); y > *(float *)(p + 0x34); y -= 0.5f) {
        nextPhase = phase + step;
        { int j; for (j = 0; j < 4; j++) {
            packet.point[j].f[1] = y;
            if (j & 1) packet.point[j].f[1] = y + 0.5f;
        } }
        { int i; for (i = 0; i < 2; i++) packet.point[i].f[2] = D_L12_001B1D84; }
        packet.point[2].f[2] = packet.point[3].f[2] = halfHeight + halfHeight;
        { int i; for (i = 0; i < 4; i++) packet.point[i].f[0] = D_L12_001B1D80; }
        ({
            BF88Packet rotated, side;
            rotated = packet;
            { int i; for (i = 0; i < 4; i++) rotated.point[i].f[0] = D_L12_001B1D80; }
            func_00280B90(&rotated, matrix, 1);
            rotated = packet;
            func_00280B90(&rotated, matrix, 1);
            { int i; for (i = 0; i < 4; i++) rotated.point[i].f[0] = -D_L12_001B1D80; }
            func_00280B90(&rotated, matrix, 1);
            side = packet;
            qcopy(&side.point[0], &packet.point[0]);
            qcopy(&side.point[1], &rotated.point[0]);
            qcopy(&side.point[2], &packet.point[2]);
            qcopy(&side.point[3], &rotated.point[2]);
            func_00280B90(&side, matrix, 1);
            qcopy(&side.point[0], &packet.point[1]);
            qcopy(&side.point[1], &rotated.point[1]);
            qcopy(&side.point[2], &packet.point[3]);
            qcopy(&side.point[3], &rotated.point[3]);
            func_00280B90(&side, matrix, 1);
        });
        { int i; for (i = 0; i < 4; i++)
            packet.color[i] = func_00283D38(D_L12_001B1D50, D_L12_001B1D54, phase); }
        phase = nextPhase;
        if (nextPhase > 0.0f) phase = nextPhase - 1.0f;
    }
}
