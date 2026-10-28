/* 28 October 2026: retained712/772 bytes, frame0xF0 versus0x110.
 * Five checks: direct rows644, coordinate streams696, separate plane
 * bases708, explicit next-row/index lifetimes712. -fforce-addr ties.
 * Retail spills seven caller temporaries as full quadwords; this draft
 * keeps the input point in a saved register and spills fewer loop bases.
 * The full4x16-byte quad is initialized from the input before XY fields
 * are replaced; Z/W remain initialized for every later query. All qcopy
 * transfers are aligned16-byte copies, no nc. Both real callees return
 * int; 2A8A50 takes a const float point, const4-float vertices and count.
 * Default -O2 -G0 -ffunction-sections; no local/strict match.
 * Reopen with original coordinate-view/caller-lifetime evidence.
 * RAC1 water/ripple and surface-height families were inspected at8bbc6b38;
 * no byte-equivalent donor was identified for this owner-based grid test. */
#include "common.h"

typedef struct { float x, y, z, w; } MmiPoint;
typedef struct {
    char reserved00[4];
    float height;
    char reserved08[0x2C];
    float halfHeight;
    char reserved38[8];
    int gridBlock, volume;
    char reserved48[8];
    float x[4], y[4], heightOffset;
} SurfaceGridPrefix;

extern int func_002ACBC8(void *, int);
extern int func_002A8A50(const float *, const MmiPoint *, int);
extern float D_00222AE0[];

/* Find the seven-by-seven grid cell whose surface slab contains the point. */
int func_00303E20(void *owner, float *point, int *column, int *row)
{
    MmiPoint quad[4] __attribute__((aligned(16)));
    SurfaceGridPrefix *state = *(SurfaceGridPrefix **)((char *)owner + 0x68);
    float center;
    int i, x, y;
    int block;
    float *xBase, *yBase, *zBase;
    if (state->volume == -1 || !func_002ACBC8(point, state->volume)) return 0;
    center = state->height + state->heightOffset;
    if (center + state->halfHeight < point[2]) return 0;
    if (point[2] < center - state->halfHeight - 1.2f) return 0;
    for (i = 0; i < 4; i++) {
        qcopy(&quad[i], point);
        quad[i].x = state->x[i];
        quad[i].y = state->y[i];
    }
    if (func_002A8A50(point, quad, 4)) return 0;
    block = state->gridBlock * 64;
    xBase = D_00222AE0;
    yBase = D_00222AE0 + 1;
    zBase = D_00222AE0 + 2;
    for (y = 0; y < 7;) {
        int nextRow = y + 1;
        int rowOffset = y * 8;
        float *nextX = xBase + (block + nextRow * 8) * 4;
        float *nextX1 = nextX + 4;
        float *nextY = yBase + (block + nextRow * 8) * 4;
        float *nextY1 = nextY + 4;
        float *nextZ = zBase + (block + nextRow * 8) * 4;
        float *nextZ1 = nextZ + 4;
        for (x = 0; x < 7; x++, nextX += 4, nextX1 += 4,
                nextY += 4, nextY1 += 4, nextZ += 4, nextZ1 += 4) {
            int firstIndex = block + rowOffset + x;
            int first = firstIndex * 16;
            int second = (firstIndex + 1) * 16;
            float height;
            quad[0].x = *(float *)((char *)xBase + first);
            quad[1].x = *(float *)((char *)xBase + second);
            quad[2].x = *nextX1;
            quad[3].x = *nextX;
            quad[0].y = *(float *)((char *)yBase + first);
            quad[1].y = *(float *)((char *)yBase + second);
            quad[2].y = *nextY1;
            quad[3].y = *nextY;
            if (func_002A8A50(point, quad, 4)) continue;
            height = (*(float *)((char *)zBase + first) +
                *(float *)((char *)zBase + second) + *nextZ1 + *nextZ) * 0.25f;
            if (point[2] <= height && height - 1.2f <= point[2]) {
                if (column) *column = x;
                if (row) *row = y;
                return 1;
            }
        }
        y = nextRow;
    }
    return 0;
}
