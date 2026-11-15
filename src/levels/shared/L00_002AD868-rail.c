/* func_L00_002AD868 in its own unit (-O2 -G0 -ffunction-sections): the counterpart of
 * RAC1's nearest_rail_point (src/overlays/shared/hero_animation_slots.c, GPL-3.0),
 * with RAC2's obstruction probe and ninth argument. The rail table and its count are
 * incomplete sda arrays: absolute `lui; lw` macro loads, and the one load reorg puts in
 * a delay slot becomes the $gp form, as in retail. */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char D_00189E20[];
typedef struct { Vector sphere; int *path; int mode; int pad[2]; } RailEntry;
extern RailEntry *D_L00_001B16C0[] __attribute__((sda));
extern int D_L00_001B16C4[] __attribute__((sda));
extern float func_00282E48(const void *, const void *);
extern float func_00282E80(const void *, const void *);
extern float func_00282C48(float);
extern int func_002761F8(Vector *, Vector *, unsigned int, void *, void *);
extern int func_L00_00341FA8(void *, Vector *, Vector *, int *, float *, int, float, float, float);

#define RAILS (D_L00_001B16C0[0])

/* Find an eligible nearby path and return its projection and owner metadata. */
int func_L00_002AD868(Vector *source, void **pathOut, Vector *destination,
                      int *segmentOut, float *offsetOut, int *modeOut,
                      void *excludePath, void *requiredPath, int ignoreObstruction) {
    Vector origin;
    Vector upper, lower;
    int index, segment, clear;
    float offset, radius, height, distance, vertical;
    Vector *p = &origin;
    unsigned char *hero;
    origin.q = source->q;
    for (index = 0; index < D_L00_001B16C4[0]; ++index) {
        if (excludePath && RAILS[index].path == excludePath) continue;
        if (requiredPath && RAILS[index].path != requiredPath) continue;
        if (*RAILS[index].path == 0) continue;
        distance = fast_vec_dist(&RAILS[index], p);
        if (RAILS[index].sphere.f[3] < distance) continue;
        if (!find_nearest_path_point(RAILS[index].path, p, destination,
                              &segment, &offset, RAILS[index].mode, 12.0f, 10.0f, 0.0f)) continue;
        hero = gHeroState;
        radius = 0.9f;
        height = 1.5f;
        if (*(unsigned int *)(hero + 0x229C) < 2) radius = 0.3f;
        if (*(short *)(hero + 0x1F6)) { radius += 0.5f; height = 10.0f; }
        clear = 1;
        if (!ignoreObstruction) {
            qcopy(&upper, destination);
            qcopy(&lower, destination);
            upper.f[2] += 0.25f;
            lower.f[2] -= 1.0f;
            if (!CollLine(&upper, &lower, 2, 0, 0)) clear = 0;
        }
        distance = vec_distance_xy(p, destination);
        vertical = FloatAbs(p->f[2] - destination->f[2]);
        if (distance < radius && vertical < height && clear) {
            *pathOut = RAILS[index].path;
            *segmentOut = segment;
            *offsetOut = offset;
            *modeOut = RAILS[index].mode;
            return 1;
        }
    }
    return 0;
}
