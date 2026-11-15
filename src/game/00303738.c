#include "common.h"
typedef struct { float x,y,z,w; } V4_F213135aa;
typedef struct { float position, height, reserved08[2], noise, reserved14[3]; } SurfaceSample;
typedef struct { V4_F213135aa position[4]; u32 color[4]; float uv[4][2]; } SurfacePacketView;
extern V4_F213135aa ref_00303738_00[];
extern SurfaceSample ref_00303738_01[];
#define SURFACE_NOISE(column, row) (ref_00303738_01[((row) % 8) * 8 + (column) % 8].noise)

/* Fill one vertex, color and a pair of perturbed repeating surface coordinates. */
/* Fills in one corner of a surface square with its position, colour and wobbling texture coordinates. */
void func_00303738(char *object, SurfacePacketView *packet, int column, int row, int vertex)
{
    char *state = *(char **)(object + 0x68);
    int cell = row * 8 + column;
    int k = *(int *)(state + 0x40) * 64 + cell;
    V4_F213135aa *destination = &packet->position[vertex];
    float u, v, sum, sum2;
    u32 shade, colour;
    destination->x = ((V4_F213135aa *)(k * sizeof(V4_F213135aa) + (unsigned int)ref_00303738_00))->x;
    destination->y = ref_00303738_00[k].y;
    destination->z = ref_00303738_00[k].z;
    destination->w = 1.0f;
    if (~*(u32 *)(state + 0x4c) & 0x40) {
        shade = (int)(ref_00303738_01[cell].height * 48.0f + 80.0f);
        colour = (shade << 8) | 0x80000000U;
        packet->color[vertex] = ((shade << 16) | colour) | 0x80;
    }
    if (~*(u32 *)(state + 0x4c) & 0x20) {
        u = (float)column * *(float *)(state + 0x28);
        packet->uv[vertex][0] = u;
        sum = SURFACE_NOISE(column, row) + SURFACE_NOISE(column + 1, row)
            + SURFACE_NOISE(column - 1, row) + SURFACE_NOISE(column, row + 1)
            + SURFACE_NOISE(column, row - 1);
        packet->uv[vertex][0] = u + *(float *)(state + 0x2c) * sum;
        v = (float)row * *(float *)(state + 0x28);
        packet->uv[vertex][1] = v;
        sum2 = SURFACE_NOISE(column + 4, row + 4) + SURFACE_NOISE(column + 5, row + 4)
            + SURFACE_NOISE(column + 3, row + 4) + SURFACE_NOISE(column + 4, row + 5)
            + SURFACE_NOISE(column + 4, row + 3);
        packet->uv[vertex][1] = v + *(float *)(state + 0x2c) * sum2;
    }
}

