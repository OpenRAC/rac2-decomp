/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, task v0862, 29 October 2026.
 * USA v1.01: 1176/1164 bytes, 0/8 placements; default -O2 -G0
 * -ffunction-sections. Reproduced in a separate unit and the original unit.
 * Separate polygon/loop variables per algorithm phase recover the 0x190
 * frame and the traversal's saved registers. A grouped center/edge scratch
 * record recovers center at stack +0x100 and edge outputs at +0x110..0x11C.
 * The SDA count declaration recovers the mixed absolute/GP count accesses.
 * Still different: visited-base spill, count-increment scheduling, descending
 * neighbor initialization, adjacency-slot loop peeling and constant lifetime,
 * final vector address materialization, and vertex-loop allocation/order.
 * An explicit visited pointer recovers the +0x12C spill but induces an extra
 * adjacency spill and a 0x1A0 frame. Earlier slot initialization, while-search
 * wording, shared outer indices, qcopy/qcopy_nc, -frac2-qcopy and -fno-gcse
 * did not improve this retained draft. Next useful evidence: original slot
 * search/control-flow shape that avoids hoisting 255 across adjacency calls.
 */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern void func_00282A88(void *, int);
extern int D_L02_001B36A4 __attribute__((sda));
extern char *D_L02_001FF1C0[];
extern float func_00282E48(void *, void *);
extern float func_00282E80(const void *, const void *);
extern int func_L02_00349BD8(int, int, int *, int *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);

typedef struct L02RegionLink {
    int index;
    unsigned char neighbors[4];
    unsigned char edges[4];
    int unused;
    TI128 center;
} L02RegionLink;

extern void func_00282C88(void *);

int func_L02_0032E508(void *unused, int start, L02RegionLink *regions, int capacity) {
    unsigned char visited[256];
    struct {
        TI128 center;
        int edgeA, edgeB, connectionA, connectionB;
    } scratch;
    int count = 0, depth = 1, changed, i, j;
    char *polygon;
    float distance;
    func_00282A88(visited, 256);
    visited[start] = depth;
    for (;;) {
        changed = 0;
        for (i = 0; i < D_L02_001B36A4; ++i) {
            if (visited[i] == depth && count < capacity) {
                regions[count++].index = i;
                for (j = 0; j < D_L02_001B36A4; ++j) {
                    if (i != j && visited[j] == 0) {
                        char *candidate = D_L02_001FF1C0[j];
                        if (*(int *)candidate <= 64 && !(0.2f < func_00282E48(candidate + 0x10, candidate + (*(int *)candidate << 4)))) {
                            if (func_L02_00349BD8(i, j, &scratch.edgeA, &scratch.edgeB)) {
                                visited[j] = depth + 1;
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
        ++depth;
        if (!changed || depth >= 32)
            break;
    }
    {
        int node, slot;
    for (node = 0; node < count; ++node)
        for (slot = 3; slot >= 0; --slot) regions[node].neighbors[slot] = 0xFF;
    }
    {
        int nodeA, nodeB;
    for (nodeA = 0; nodeA < count; ++nodeA) {
        for (nodeB = nodeA + 1; nodeB < count; ++nodeB) {
            if (func_L02_00349BD8(regions[nodeA].index, regions[nodeB].index, &scratch.connectionA, &scratch.connectionB)) {
                *(int *)(D_L02_001FF1C0[regions[nodeA].index] + (scratch.connectionA << 4) + 0x1C) = 0;
                *(int *)(D_L02_001FF1C0[regions[nodeB].index] + (scratch.connectionB << 4) + 0x1C) = 0;
                {
                    int slotA;
                for (slotA = 0; slotA < 4; ++slotA) {
                    if (regions[nodeA].neighbors[slotA] == 0xFF) {
                        regions[nodeA].neighbors[slotA] = nodeB;
                        regions[nodeA].edges[slotA] = scratch.connectionA;
                        break;
                    }
                }
                }
                {
                    int slotB;
                for (slotB = 0; slotB < 4; ++slotB) {
                    if (regions[nodeB].neighbors[slotB] == 0xFF) {
                        regions[nodeB].neighbors[slotB] = nodeA;
                        regions[nodeB].edges[slotB] = scratch.connectionB;
                        break;
                    }
                }                }
            }
        }
    }
    }
    {
        int node;
    for (node = 0; node < count; ++node) {
        polygon = D_L02_001FF1C0[regions[node].index];
        func_00282C88(&scratch.center);
        {
            int sumVertex;
        for (sumVertex = 0; sumVertex < *(int *)polygon; ++sumVertex)
            func_00282CC0(&scratch.center, &scratch.center, polygon + (sumVertex << 4) + 0x10);
        }
        func_00282D30(&scratch.center, &scratch.center, 1.0f / (float)*(int *)polygon);
        ((float *)&scratch.center)[3] = 0.0f;
        {
            int radiusVertex;
        for (radiusVertex = 0; radiusVertex < *(int *)polygon; ++radiusVertex) {
            distance = func_00282E80(&scratch.center, polygon + (radiusVertex << 4) + 0x10);
            if (((float *)&scratch.center)[3] < distance) ((float *)&scratch.center)[3] = distance;
        }
        }
        regions[node].center = scratch.center;
    }
    }
    return count;
}
