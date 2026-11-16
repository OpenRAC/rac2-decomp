#include "include_asm.h"
#include "common.h"

/* Own unit: -G8 for the small-data scale factors, -fno-sched-spec for the loop. */

extern char g_vehicle_probe_vectors[];
extern char g_gravity_direction[] __attribute__((section(".sdata")));
extern float g_vehicle_probe_radius __attribute__((sda));
extern float g_vehicle_probe_lift __attribute__((sda));
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Builds the eight-vector table D_0022AFA0 from the object's two axis rows
   (+0xC0, +0xD0): entries 4-7 are row0, -row0, -row1, row1, entries 0-3 the
   four sums of a signed row0 and a signed row1. Every entry is then scaled,
   moved to the object's position (+0x10) and offset by D_001B27B0. The axis
   rows are written through `table` before the loop and the entries through
   `out` inside it; the two pointers must stay separate. */
void BuildEightDirectionOffsets(char *object)
{
    char vectors[4][16] __attribute__((aligned(16)));
    char temp[16] __attribute__((aligned(16)));
    char sum[16] __attribute__((aligned(16)));
    char *table = g_vehicle_probe_vectors;
    char *out;
    char *pos;
    int i;

    qcopy(vectors[0], object + 0xC0);
    qcopy(vectors[3], object + 0xD0);
    FastVecScale(vectors[1], vectors[0], -1.0f);
    FastVecScale(vectors[2], vectors[3], -1.0f);
    qcopy(table + 0x40, vectors[0]);
    qcopy(table + 0x50, vectors[1]);
    qcopy(table + 0x60, vectors[2]);
    qcopy(table + 0x70, vectors[3]);
    pos = object + 0x10;
    out = table;
    for (i = 0; i < 8; i++) {
        if (i < 4)
            FastVecAdd(out, vectors[i >> 1], vectors[2 + (i & 1)]);
        vec_scale_to_length(out, out, g_vehicle_probe_radius);
        FastVecAdd(out, out, pos);
        vec_scale_to_length(temp, g_gravity_direction, -g_vehicle_probe_lift);
        FastVecAdd(out, out, temp);
        out += 16;
        FastVecAdd(sum, temp, pos);
    }
}
