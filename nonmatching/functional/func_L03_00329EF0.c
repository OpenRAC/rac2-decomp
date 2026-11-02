/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, 29 October 2026. Upstream pinned GNU game compiler.
 * Best US check: 1200/1200 bytes, 0/2 placements, -O2 -G0 -ffunction-sections -g.
 * Phase-local loop counters, byte-offset visited-array access and qcopy recover
 * much of the flood fill. An explicit first-link scan avoids the initial peel.
 * Remaining: 255 is hoisted into s5 across pair checks, spilling the outer next
 * index at sp+0x120; frame 0x1e0 versus retail 0x1d0, spill slots and allocation.
 * The destination edge byte is captured once; retail also retains it through
 * that scan. Debug labels recover the two nops before the center division.
 * Reopen with evidence for the sentinel and adjacency-counter lifetimes.
 * Other trials: ordinary scoped loops 1208 bytes (default flags), unsigned
 * visited-address form plus ordinary scans 1232; separate next-pass and count-up
 * loop spellings did not fix allocation. No linked build: not an exact match.
 * Declarations below are complete. Preserve source-line layout with -g.
 */
#include "common.h"
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) RegionPoint;
typedef struct { int id; unsigned char links[4]; unsigned char edges[4]; int reserved; RegionPoint sphere; } RegionRecord;
typedef struct { int count; int reserved[3]; RegionPoint points[1]; } RegionGeometry;
extern float (*D_L03_001FE700[])[4];
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282A88(void *, int);
extern int func_L02_00349BD8(int, int, int *, int *);
extern void func_00282D30(void *, void *, float);
extern float func_00282E80(void *, void *);

int func_L03_00329EF0(void *unused, int *ids, RegionRecord *records, int capacity) {
    unsigned char depth[256];
    RegionPoint center;
    unsigned int visited;
    int pass = 1;
    int count = 0;
    int changed, edgeA, edgeB;
    int sourceEdge, targetEdge;
    RegionGeometry *geometry;
    RegionPoint *point;
    float distance;
    func_00282A88(depth, 0x100);
    depth[0] = pass;
    visited = (unsigned int)depth;
    { int i, j;
    do {
        int nextPass;
        changed = 0;
        nextPass = pass + 1;
        for (i = 0; i < capacity && count < capacity && -1 != ids[i]; i++) {
            if (*(unsigned char *)(visited + i) == pass) {
                records[count++].id = ids[i];
                for (j = 0; j < capacity; j++) {
                    if (j == i || *(unsigned char *)(visited + j))
                        continue;
                    if (ids[j] == -1)
                        break;
                    if (func_L02_00349BD8(ids[i], ids[j], &sourceEdge, &targetEdge)) {
                        changed = 1;
                        *(unsigned char *)(visited + j) = nextPass;
                    }
                }
            }
        }
        pass = nextPass;
        if (!changed) break;
    } while (pass < 0x20);
    }
    { int i, j;
    for (i = 0; i < count; i++) {
        unsigned char *link = &records[i].links[3];
        for (j = 3; j >= 0; j--)
            *link-- = 255;
    }
    }
    { int i, j, k;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            if (func_L02_00349BD8(records[i].id, records[j].id, &edgeA, &edgeB)) {
                ((RegionGeometry *)D_L03_001FE700[records[i].id])->points[edgeA].w = 0;
                ((RegionGeometry *)D_L03_001FE700[records[j].id])->points[edgeB].w = 0;
                k = 0;
            find_source_link:
                if (k >= 4) goto source_link_done;
                if (records[i].links[k] != 255) {
                    k++;
                    goto find_source_link;
                }
                records[i].links[k] = j;
                records[i].edges[k] = edgeA;
            source_link_done:
                { unsigned char edge = edgeB;
                for (k = 0; k < 4; k++) {
                    if (records[j].links[k] == 255) {
                        records[j].edges[k] = edge;
                        records[j].links[k] = i;
                        break;
                    }
                }}
            }
        }
    }
    }
    { int i, j;
    for (i = 0; i < count; i++) {
        geometry = (RegionGeometry *)D_L03_001FE700[records[i].id];
        func_00282C88(&center);
        for (j = 0; j < geometry->count; j++)
            func_00282CC0(&center, &center, &geometry->points[j]);
        func_00282D30(&center, &center, 1.0f / (float)geometry->count);
        center.w = 0;
        for (j = 0; j < geometry->count; j++) {
            distance = func_00282E80(&center, &geometry->points[j]);
            if (distance > center.w)
                center.w = distance;
        }
        qcopy(&records[i].sphere, &center);
    }
    }
    return count;
}
