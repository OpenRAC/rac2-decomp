#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern char *D_L02_001FF1C0[];
extern void func_00282A88(void *, int);
extern int D_L02_001B36A4 __attribute__((sda));
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern int func_L02_00349BD8(int, int, int *, int *);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);

/* One route node, as struct RouteNode in L02_002B5F50.c: polygon index, four neighbour
   slots (0xFF = free), the portal edge of each, and the polygon's centre and radius. */
typedef struct L02RegionLink {
    int index;
    unsigned char neighbors[4];
    unsigned char edges[4];
    int unused;
    TI128 center;
} L02RegionLink;

/* Builds the route nodes reachable from polygon START: a breadth-first walk over the
   polygons (up to 32 layers, CAPACITY nodes), then the links between the found nodes,
   then each node's centre and radius. Returns the node count.
   -g, as retail's two-nop floor before div.s shows. The first slot search is a label
   loop inside a one-pass group (docs/COMPILER-NOTES.md:54): retail keeps its constant and
   address unhoisted and its loop-start alignment nop, which a for loop does not give.
   The neighbour reset indexes the node array as flat bytes, which gives retail's
   address grouping. */
int func_L02_0032E508(void *unused, int start, L02RegionLink *regions, int capacity) {
    unsigned char visited[256];
    struct {
        TI128 center;
        int edgeA, edgeB, connectionA, connectionB;
    } scratch;
    int count = 0, depth = 1, changed, i, j;
    char *polygon;
    float distance;
    unsigned char *vis;
    func_00282A88(visited, 256);
    visited[start] = depth;
    vis = visited;
    for (;;) {
        changed = 0;
        for (i = 0; i < D_L02_001B36A4; ++i) {
            if (vis[i] == depth && count < capacity) {
                regions[count++].index = i;
                for (j = 0; j < D_L02_001B36A4; ++j) {
                    if (i != j && vis[j] == 0) {
                        char *candidate = D_L02_001FF1C0[j];
                        if (*(int *)candidate <= 64 && !(0.2f < func_00282E48(candidate + 0x10, candidate + (*(int *)candidate << 4)))) {
                            if (func_L02_00349BD8(i, j, &scratch.edgeA, &scratch.edgeB)) {
                                vis[j] = depth + 1;
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
        {
            int none = 0xFF;
            /* Flat byte index over the region array (same bytes as regions[node].neighbors[slot]);
             * gives retail's address order. Allowed by owner ruling, 8 November 2026. */
            for (slot = 0; slot < 4; slot++) regions->neighbors[node * sizeof(L02RegionLink) + slot] = none;
        }
    }
    {
        int nodeA, nodeB;
        for (nodeA = 0; nodeA < count; ++nodeA) {
            for (nodeB = nodeA + 1; nodeB < count; ++nodeB) {
                if (func_L02_00349BD8(regions[nodeA].index, regions[nodeB].index, &scratch.connectionA, &scratch.connectionB)) {
                    *(int *)(D_L02_001FF1C0[regions[nodeA].index] + (scratch.connectionA << 4) + 0x1C) = 0;
                    *(int *)(D_L02_001FF1C0[regions[nodeB].index] + (scratch.connectionB << 4) + 0x1C) = 0;
                    {
                        int slotA = 0;
                        do {
                            goto testA;
                        nextA:
                            slotA++;
                        testA:
                            if (slotA < 4) {
                                if (regions[nodeA].neighbors[slotA] != 0xFF)
                                    goto nextA;
                                regions[nodeA].neighbors[slotA] = nodeB;
                                regions[nodeA].edges[slotA] = scratch.connectionA;
                            }
                        } while (0);
                    }
                    {
                        int slotB = 0;
                        unsigned char edge = scratch.connectionB;
                        int none = 0xFF;
                        for (; slotB < 4; ++slotB) {
                            if (regions[nodeB].neighbors[slotB] == none) {
                                regions[nodeB].neighbors[slotB] = nodeA;
                                regions[nodeB].edges[slotB] = edge;
                                break;
                            }
                        }
                    }
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
            qcopy(&regions[node].center, &scratch.center);
        }
    }
    return count;
}
