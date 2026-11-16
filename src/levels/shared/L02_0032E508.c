#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern char *g_route_polygons[];
extern void mem_fast_helper_b(void *, int);
extern int g_route_node_count __attribute__((sda));
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern int path_find_touching_polygon_corners(int, int, int *, int *);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);

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
   loop inside a one-pass group (docs/build/compiler-notes.md:54): retail keeps its constant and
   address unhoisted and its loop-start alignment nop, which a for loop does not give.
   The neighbour reset indexes the node array as flat bytes, which gives retail's
   address grouping. */
int path_build_route_nodes(void *unused, int start, L02RegionLink *regions, int capacity) {
    unsigned char visited[256];
    struct {
        TI128 center;
        int edgeA, edgeB, connectionA, connectionB;
    } scratch;
    int count = 0, depth = 1, changed, i, j;
    char *polygon;
    float distance;
    unsigned char *vis;
    mem_fast_helper_b(visited, 256);
    visited[start] = depth;
    vis = visited;
    for (;;) {
        changed = 0;
        for (i = 0; i < g_route_node_count; ++i) {
            if (vis[i] == depth && count < capacity) {
                regions[count++].index = i;
                for (j = 0; j < g_route_node_count; ++j) {
                    if (i != j && vis[j] == 0) {
                        char *candidate = g_route_polygons[j];
                        if (*(int *)candidate <= 64 && !(0.2f < fast_vec_dist(candidate + 0x10, candidate + (*(int *)candidate << 4)))) {
                            if (path_find_touching_polygon_corners(i, j, &scratch.edgeA, &scratch.edgeB)) {
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
                if (path_find_touching_polygon_corners(regions[nodeA].index, regions[nodeB].index, &scratch.connectionA, &scratch.connectionB)) {
                    *(int *)(g_route_polygons[regions[nodeA].index] + (scratch.connectionA << 4) + 0x1C) = 0;
                    *(int *)(g_route_polygons[regions[nodeB].index] + (scratch.connectionB << 4) + 0x1C) = 0;
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
            polygon = g_route_polygons[regions[node].index];
            vec_clear_128(&scratch.center);
            {
                int sumVertex;
                for (sumVertex = 0; sumVertex < *(int *)polygon; ++sumVertex)
                    FastVecAdd(&scratch.center, &scratch.center, polygon + (sumVertex << 4) + 0x10);
            }
            FastVecScale(&scratch.center, &scratch.center, 1.0f / (float)*(int *)polygon);
            ((float *)&scratch.center)[3] = 0.0f;
            {
                int radiusVertex;
                for (radiusVertex = 0; radiusVertex < *(int *)polygon; ++radiusVertex) {
                    distance = vec_distance_xy(&scratch.center, polygon + (radiusVertex << 4) + 0x10);
                    if (((float *)&scratch.center)[3] < distance) ((float *)&scratch.center)[3] = distance;
                }
            }
            qcopy(&regions[node].center, &scratch.center);
        }
    }
    return count;
}
