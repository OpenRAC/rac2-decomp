/* 6 November 2026, round 9: 972/972, 0/1, 11 real rows (18 before, counting stack-offset
 * rows that the earlier "11" ignored). Writing phase inside the band loop
 * (`float *phase = (float *)(state + 0x60)`) lets gcse hoist it into a late pseudo, so
 * reload gives stride/band/phase retail's 0x160/0x164/0x168 slots; `off = band * 4`
 * gives retail's addu operand order. Left: colour $a0/primitive $v1 (retail $v1/$a0) and
 * the packet store order. Putting colour before primitive (needed for $v1) moves mode,
 * primitive and band registers (19-33 rows). Hill-climbs over declarations and setup
 * order (~450 runs, chained or split colour stores) and band types tie or worsen. */
/* 6 November 2026, lead: hill-climb over the packet setup order (60 runs) cuts real instruction differences from 20 to 11; the band loop registers now match. Left: colour constant in $a0 (retail $v1), primitive in $v1 (retail $a0), band/phase stack slots 0x160 vs 0x168 and their store order. Split colour stores, a grey local, declaration orders and -freduce-all-givs/-fno-rerun-loop-opt/-fexpensive-optimizations tie at 11. Source below is the 11-row form. */
/* 6 November 2026, round 3: unchanged, 972/972, 0/1, 22 rows. Slot order here is
 * phase 0x160, stride 0x164, band 0x168; retail is stride, band, phase. Writing phase[band]
 * inline from state (four forms, no phase local) gives 61 rows. A hill-climb over the
 * declaration order (60 orders) stays at 22. Original best C retained.
 */
/* 6 November 2026: 972/972, 0/1 USA, 22 rows (was first diff +0x7C). `state = ...; flip = 0.0f;`
 * (flip set after the state load) fixes the lhu/andi/mtc1 order. This source order gives retail's
 * colour register ($v1) and its whole packet store order. Left: mode $a0/primitive $a1/band $a0
 * (retail $a1/$a0/$a1), and the phase spill slot 0x160 (retail 0x168, above stride 0x160 and
 * band 0x164). Local-alloc needs colour > primitive > mode. A hill-climb over the setup order
 * (about 500 orders) only trades this for colour/primitive $a0/$v1 (16 rows). Declaring band
 * before phase, and phase inside the loop (folds 0x60 into lwc1), do not move the slot.
 * Colour chain/split/local forms all tie.
 */
/* Retained reconstruction, updated 2 November 2026; not a linked match.
 * Profile: -O2 -G0 -ffunction-sections.
 * Current US check: 972/972 bytes, 0/1 placements, first difference +0x7C.
 * The faithful assignment of the complete aligned 192-byte StripGeometry now
 * emits retail's full lq/lq/sq/sq/addiu/bne/addiu copy loop without padding.
 * This supersedes the earlier block-copy refusal: the maintained compiler's
 * block_move_quad support is the independently verified changed input.
 * The 0x200 frame and prologue/copy through +0x78 agree. Remaining differences
 * include flag-mask/float-zero scheduling, mode/primitive register allocation,
 * phase spill at 0x160 rather than 0x168 and band/texture-loop address lifetimes.
 * A real flag snapshot and primitive-before-mode assignment still gave 972
 * bytes and 0/1, changed packet allocation without improving it, and were
 * reverted. Two bounded checks; US2/PAL not rerun for this nonmatching body.
 * Reopen on independent packet-field and phase/loop lifetime evidence.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { float point[3][4][4]; } StripGeometry __attribute__((aligned(16)));
typedef struct {
    float corner[4][4];
    unsigned int color[4];
    float tex0[4];
    float tex1[4];
    unsigned long long primitive, texture, mode, flags;
} StripPacket __attribute__((aligned(16)));
extern StripGeometry D_L02_002A52F0;
extern int D_L02_002A53B0[3][9];
extern int D_L02_001B0A00[];
extern unsigned long long func_0027C878(int);
extern int func_00283CF0(float);
extern void func_00282D08(void *, void *, void *, float);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void func_00280B90(void *, void *, int);

void func_L02_003E7B58(char *actor) {
    StripGeometry geometry;
    StripPacket packet;
    char *state;
    float flip;
    float sample[4] __attribute__((aligned(16)));
    int band, piece;
    geometry = D_L02_002A52F0;
    state = *(char **)(actor + 0x68);
    flip = 0.0f;
    if (*(unsigned short *)(actor + 0x34) & 0x8000) flip = 1.0f;
    packet.tex0[0] = flip;
    packet.tex0[1] = 0.0f;
    packet.tex0[2] = 1.0f - flip;
    packet.tex0[3] = 0.0f;
    packet.tex1[1] = 1.0f;
    packet.mode = 0xFF9000000260ULL;
    packet.primitive = 5;
    packet.tex1[2] = 1.0f - flip;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = 0x7F7F7F7F;
    packet.tex1[0] = flip;
    packet.flags = 0x8000000000ULL;
    packet.tex1[3] = 1.0f;
    for (band = 0; band < 3; band++) {
        int off = band * 4;
        float *phase = (float *)(state + 0x60);
        float scroll = *(float *)((char *)phase + off) + 0.15f;
        for (piece = 0; piece < 3; piece++) {
            float first = ((float)func_00283CF0(scroll) - scroll) * 0.43094158f;
            int tile;
            float last;
            float texFirst;
            float texLast;
            first += (float)piece * 0.43094158f;
            tile = func_00283CF0((scroll + (float)piece - 1.0f) + 9.0f) % 9;
            last = first + 0.43094158f;
            packet.texture = func_0027C878(D_L02_001B0A00[D_L02_002A53B0[band][tile]]);
            texFirst = 0.0f;
            texLast = 1.0f;
            if (last < 0.1f || first > 0.9f) continue;
            if (first < 0.1f) {
                texFirst = (0.1f - first) * 2.3205001f;
                first = 0.1f;
            } else if (last > 0.9f) {
                texLast = (0.9f - last) * 2.3205001f + texLast;
                last = 0.9f;
            }
            packet.tex0[1] = packet.tex0[3] = texFirst;
            packet.tex1[1] = packet.tex1[3] = texLast;
            func_00282D08(sample, geometry.point[band][0], geometry.point[band][2], first);
            func_L01_0031A278(actor, packet.corner[0], sample[0], sample[1], sample[2]);
            func_00282D08(sample, geometry.point[band][1], geometry.point[band][3], first);
            func_L01_0031A278(actor, packet.corner[1], sample[0], sample[1], sample[2]);
            func_00282D08(sample, geometry.point[band][0], geometry.point[band][2], last);
            func_L01_0031A278(actor, packet.corner[2], sample[0], sample[1], sample[2]);
            func_00282D08(sample, geometry.point[band][1], geometry.point[band][3], last);
            func_L01_0031A278(actor, packet.corner[3], sample[0], sample[1], sample[2]);
            func_00280B90(&packet, 0, 0);
        }
    }
}
