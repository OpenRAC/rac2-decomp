#include "common.h"
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) RegionPoint;
typedef struct { int id; unsigned char links[4]; unsigned char edges[4]; int reserved; RegionPoint sphere; } RegionRecord;
typedef struct { int count; int reserved[3]; RegionPoint points[0]; } RegionGeometry;
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
    float distance;
    func_00282A88(depth, 0x100);
    depth[0] = pass;
    visited = (unsigned int)depth;
    { int i, j;
    do {
        changed = 0;
        for (i = 0; i < capacity && count < capacity && ids[i] != -1; i++) {
            if (*(unsigned char *)(visited + i) == pass) {
                records[count++].id = ids[i];
                for (j = 0; j < capacity; j++) {
                    if (i == j || *(unsigned char *)(visited + j))
                        continue;
                    if (ids[j] == -1)
                        break;
                    if (func_L02_00349BD8(ids[i], ids[j], &sourceEdge, &targetEdge)) {
                        changed = 1;
                        *(unsigned char *)(visited + j) = pass + 1;
                    }
                }
            }
        }
        pass++;
        if (!changed) break;
    } while (pass < 0x20);
    }
    { int i, j;
    for (i = 0; i < count; i++) {
        int none = 255;
        unsigned int base = (unsigned int)records->links;
        unsigned char *link;
        j = 3;
        link = (unsigned char *)(i * sizeof(RegionRecord) + base + j);
        for (; j >= 0; j--)
            *link-- = none;
    }
    }
    { int i, j, k;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            if (func_L02_00349BD8(records[i].id, records[j].id, &edgeA, &edgeB)) {
                ((RegionGeometry *)D_L03_001FE700[records[i].id])->points[edgeA].w = 0;
                ((RegionGeometry *)D_L03_001FE700[records[j].id])->points[edgeB].w = 0;
                /* Entered at its test: loop.c leaves a loop entered from outside alone. */
                k = 0;
                goto find_source_link;
                for (;;) {
                    k++;
                find_source_link:
                    if (k >= 4)
                        break;
                    if (records[i].links[k] == 255) {
                        records[i].links[k] = j;
                        records[i].edges[k] = edgeA;
                        break;
                    }
                }
                { int m = 0;
                int none = 255;
                unsigned char edge = edgeB;
                for (; m < 4; m++) {
                    if (records[j].links[m] == none) {
                        records[j].links[m] = i;
                        records[j].edges[m] = edge;
                        break;
                    }
                }}
            }
        }
    }
    }
    { int i, j, k;
    for (i = 0; i < count; i++) {
        geometry = (RegionGeometry *)D_L03_001FE700[records[i].id];
        func_00282C88(&center);
        for (j = 0; j < geometry->count; j++)
            func_00282CC0(&center, &center, &geometry->points[j]);
        func_00282D30(&center, &center, 1.0f / (float)geometry->count);
        center.w = 0;
        for (k = 0; k < geometry->count; k++) {
            distance = func_00282E80(&center, &geometry->points[k]);
            if (distance > center.w)
                center.w = distance;
        }
        qcopy(&records[i].sphere, &center);
    }
    }
    return count;
}
