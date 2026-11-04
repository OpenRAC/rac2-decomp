/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 1176/1176 bytes, 0/27 placements; first difference 0x4c.
 * Profile: -O2 -G8 -ffunction-sections.
 * Current source reproduces 1176 bytes in all three releases. The old 832-byte index measurement
 * is superseded. Only the two PRE spill slots remain swapped; the exact probe with 27 unused
 * locals remains rejected.
 * Earlier measurements below are historical where superseded by this note.
 */
/* Tier: Claude Opus 5.5 (xhigh), task v1715, 31 October 2026.
 * Unit: new sibling src/levels/shared/L00_0041ABB8-beam-g8.c, default -G8 profile
 * (-O2 -G8 -ffunction-sections); the name alone gives the flags, no cflags line.
 * Best: 1176/1176 bytes, 0/27 USA v1.01 places, 6 non-relocation words differ.
 * All declarations it needs are below. US2 and PAL were not checked for this draft.
 *
 * Only difference left: two spill slots are swapped. Retail keeps index+1 at 0x6C($sp)
 * and the shifted alpha at 0x74($sp); this draft has them the other way round.
 * Slots follow ascending pseudo number, and these pseudos are gcse PRE reaching regs,
 * numbered in expression hash-bucket order (table size N = 115 here, n_insns/2|1).
 * Hashes: (plus index 1) = index mod N, (plus fp 32) = 32, (ashift alpha 24) =
 * (alpha + 35) mod N. Here that is 88, 32, 10; retail needs index+1 < &matrix[2] < alpha<<24,
 * so index must be >= N and alpha >= N - 2: about 27 more pseudos before those decls.
 *
 * EXACT-BYTES FORM, NOT LANDED: adding this line immediately before
 * "int index, part, alpha;" gives 27 of 27 USA v1.01 places:
 *     int u0, u1, ..., u26;
 * (27 unused locals). Their only effect is on pseudo numbering, the same kind of
 * compiler steering as the forms WORKER2.md holds back for a maintainer ruling, so it
 * is reported as FAILED. That form also gives 27 of 27 on us2 and on pal.
 * Real named locals declared before index would be the clean version, if enough exist.
 *
 * What recovered the rest, each from retail evidence:
 * - plain slot->packet[part] / source[part] / phase[part] / scroll[part] / point[part]
 *   indexing, with no pointer variables or cursors. Cursors or a top-of-loop packet
 *   variable change the reduced-giv set and the order of the increments.
 * - (alpha << 24) written at each use: PRE then gives retail's s0 plus a stack copy.
 * - the two colour stores adjacent in source (sum life 2): loop's threshold test then
 *   keeps the add inside the loop. With header[0] between them (life 3) it is hoisted.
 * - full UV sets per arm in field order; cross-jumping merges the tails.
 * Tried, no help: a side = &matrix[1] local (1168 bytes), a matrix pointer local
 * (1200 bytes), different base spellings per arm (1180 bytes).
 */
#include "common.h"

typedef int Quad128 __attribute__((mode(TI)));

/* A 0x90-byte packet: four corners, then their colours, UVs and the GS header. */
typedef struct {
    Quad128 vertex[4];            /* 0x00 */
    unsigned int color[4];        /* 0x40 */
    float uv[4][2];               /* 0x50 */
    long header[4];               /* 0x70 */
} BeamPacket;

/* One 0x530-byte effect slot (see func_L00_0041B840). */
typedef struct {
    Quad128 first, second;        /* 0x00 */
    Quad128 point[2];             /* 0x20 */
    char pad40[0x20];
    BeamPacket source[2];         /* 0x60 */
    char pad180[0x120];
    BeamPacket packet[2];         /* 0x2A0 */
    char pad3C0[0x120];
    int phase[2];                 /* 0x4E0 */
    char pad4E8[0x18];
    float scroll[2];              /* 0x500 */
    char pad508[8];
    float scale;                  /* 0x510 */
    int inUse;                    /* 0x514 */
    int fading;                   /* 0x518 */
    char pad51C[0x14];
} EffectSlot;

extern char *D_L00_001B1450 __attribute__((sda));
extern char D_L00_001B8DC0[];
extern int func_00283CF0(float);
extern void func_L00_0041C160(void *, Quad128 *, EffectSlot *, int, float);
extern long long func_0027C878(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

void func_L00_0041BCC8(void *unused)
{
    Quad128 matrix[4], eye, normal;
    EffectSlot *slot;
    int index, part, alpha;

    for (index = 0; index < 10; index++) {
        slot = (EffectSlot *)(index * 0x530 + (int)D_L00_001B1450);
        if (slot->inUse != 1)
            continue;
        if (slot->fading == 1) {
            float scale = slot->scale * 64.0f;
            alpha = func_00283CF0(scale + scale);
        } else {
            alpha = 64;
        }
        func_L00_0041C160(unused, slot->point, slot, (alpha << 24) | 0x103080, 0.35f);
        func_L00_0041C160(unused, slot->point, slot, (alpha << 24) | 0xFFFFFF, 0.075f);
        for (part = 0; part < 2; part++) {
            slot->packet[part].header[1] = func_0027C878(23);
            slot->packet[part].header[2] = 0xFF9000000260LL;
            slot->packet[part].header[0] = 0;
            slot->packet[part].color[2] = (alpha << 24) + 0x103080;
            slot->packet[part].color[0] = (alpha << 24) + 0x103080;
            slot->packet[part].color[3] = 0x103080;
            slot->packet[part].color[1] = 0x103080;
            slot->packet[part].header[3] = ((long)(part % 2 + 1) << 2) | 0x8000000040UL;
            if (slot->phase[part] != 0) {
                slot->packet[part].uv[0][0] = slot->scroll[part];
                slot->packet[part].uv[0][1] = 0.0f;
                slot->packet[part].uv[1][0] = slot->scroll[part] + 1.0f;
                slot->packet[part].uv[1][1] = 0.0f;
                slot->packet[part].uv[2][0] = slot->scroll[part];
                slot->packet[part].uv[2][1] = 1.0f;
                slot->packet[part].uv[3][0] = slot->scroll[part] + 1.0f;
                slot->packet[part].uv[3][1] = 1.0f;
            } else {
                slot->packet[part].uv[0][0] = slot->scroll[part];
                slot->packet[part].uv[0][1] = 1.0f;
                slot->packet[part].uv[1][0] = slot->scroll[part] + 1.0f;
                slot->packet[part].uv[1][1] = 1.0f;
                slot->packet[part].uv[2][0] = slot->scroll[part];
                slot->packet[part].uv[2][1] = 0.0f;
                slot->packet[part].uv[3][0] = slot->scroll[part] + 1.0f;
                slot->packet[part].uv[3][1] = 0.0f;
            }
            func_00282CF0(&eye, D_L00_001B8DC0, &slot->point[part]);
            func_002AFFD8(&slot->point[part], &normal, 1);
            func_00282F20(&matrix[0], &eye, 1.0f);
            func_00282DD8(&matrix[1], &matrix[0], &normal);
            func_00282F20(&matrix[1], &matrix[1], 1.0f);
            func_00282DD8(&matrix[2], &matrix[1], &matrix[0]);
            ((float *)&matrix[3])[0] = ((float *)&slot->point[part])[0];
            ((float *)&matrix[3])[1] = ((float *)&slot->point[part])[1];
            ((float *)&matrix[3])[2] = ((float *)&slot->point[part])[2];
            ((float *)&matrix[3])[3] = 1.0f;
            if (slot->fading == 1) {
                func_00282D30(&slot->packet[part].vertex[0], &slot->source[part].vertex[0], 0.5f);
                func_00282D30(&slot->packet[part].vertex[1], &slot->source[part].vertex[1], 0.5f);
                func_00282D30(&slot->packet[part].vertex[2], &slot->source[part].vertex[2], 0.5f);
                func_00282D30(&slot->packet[part].vertex[3], &slot->source[part].vertex[3], 0.5f);
            } else {
                func_00282D30(&slot->packet[part].vertex[0], &slot->source[part].vertex[0], slot->scale);
                func_00282D30(&slot->packet[part].vertex[1], &slot->source[part].vertex[1], slot->scale);
                func_00282D30(&slot->packet[part].vertex[2], &slot->source[part].vertex[2], slot->scale);
                func_00282D30(&slot->packet[part].vertex[3], &slot->source[part].vertex[3], slot->scale);
            }
            func_00280B90(&slot->packet[part], matrix, 0);
        }
    }
}
