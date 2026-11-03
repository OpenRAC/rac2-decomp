#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
extern void func_L06_003F3690(char *, char *);
extern int func_00282978(void *);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void func_L04_003429F8(void *, void *, void *, int, void *, int, float);
extern int func_L06_003F3760(void *, void *);
extern char *D_L06_001FE500[];
extern char *D_L06_001B290C __attribute__((sda));
extern int D_L06_001B2348 __attribute__((sda));
extern Vector D_00189EA0;
extern Vector D_L06_001B9840;
extern char D_L06_001A8F20[] MACRO_ADDR;
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282FB8(void *, void *, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_L02_0031E9E8(void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern float func_002A89A8(void *, int, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_002ACB48(float *, float);
extern float func_L00_0031CDD0(void *, void *, int, float, float);
extern char *func_L06_003F3EF0(void *, void *, void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float,
                         int, float, int, int, int, int, int);
extern void func_002E5DA0(int, int, void *, int);
extern void *func_L02_0032B468(void *, int, void *, void *, int, int, float, void *, void *, void *);
extern void func_0029F338(void *);
extern int func_002A8600(void *, int, int, int);
extern void func_002A93B0(void *);

/* regions[] holds indices into the 0x80-byte region table at D_L06_001B290C,
 * -1 for an empty slot. */
typedef struct {
    char pad[0x90];
    int regions[4];
    char *children[20];
} SpawnerSlots;

/* Select a spawn point, launch a child and retire the spawner when destroyed. */
void func_L06_003F3800(char *moby)
{
    Vector point, delta, origin, step;
    char *region;
    void *anchor;
    int hasAnchor;
    char *path_points;
    int path_count;
    char *path;
    char *target;
    int slot;
    int first;
    char *state = *(char **)(moby + 0x68);

    func_L06_003F3690(moby, state);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0: {
        char *child;
        if (D_L06_001B2348) {
            child = 0;
            while (!func_002A8600(&child, *(int *)(state + 0x84), 0, 0))
                func_0029F338(child);
            *(unsigned char *)(moby + 0x20) = 1;
        }
        break;
    }
    case 1: {
        func_L06_003F3690(moby, state);
        if (!func_00282978(state + 0x7E))
            break;
        if (!func_002A77E0(7)) {
            anchor = 0;
            hasAnchor = 0;
            path_points = 0;
            path_count = 0;
            if (*(int *)(state + 0x74) != -1) {
                anchor = state + 0x74;
                hasAnchor = 1;
            }
            if (*(int *)(state + 0x78) != -1) {
                path = D_L06_001FE500[*(int *)(state + 0x78)];
                path_points = path + 0x10;
                path_count = *(int *)path;
            }
            func_L04_003429F8(moby, state + 0xF0, anchor, hasAnchor,
                             path_points, path_count,
                             *(float *)(state + 0x70));
        } else {
            target = *(char **)(state + 0x130);
            if (target && *(unsigned char *)(target + 0x20) != 0xFE &&
                *(unsigned char *)(target + 0x20) != 0xFD) {
                qcopy((state + 0xF0), (target + 0x10));
            } else {
                *(int *)(state + 0x130) = 0;
                *(int *)(state + 0x134) = 2;
            }
        }
        if (*(int *)(state + 0x134) == 2)
            break;
        slot = func_L06_003F3760(moby, state);
        if (*(unsigned char *)(state + 0x81) >= *(unsigned char *)(state + 0x80) || slot == -1)
            break;
        region = 0;
        if (*(unsigned char *)(state + 0x82)) {
            int i;
            float nearest = 100000.0f;
            for (i = 0; i < 4; i++) {
                int index = ((int *)(state + 0x90))[i];
                if (index != -1) {
                    char *candidate = D_L06_001B290C + index * 0x80;
                    float current = func_00282E48(D_00189EA0, candidate + 0x30);
                    if (current < nearest) {
                        region = candidate;
                        nearest = current;
                    }
                }
            }
            if (!region) {
                func_00282CF0(point, state + 0xF0, moby + 0x10);
                func_00282D30(point, point, 0.5f);
                if (*(float *)(state + 0x70) > 3.0f)
                    func_00282FB8(point, point, 3.0f);
                if (func_00282DF0(point) < 3.0f)
                    func_00282F20(point, point, 3.0f);
                func_00282CC0(point, point, moby + 0x10);
            } else {
                qcopy(point, region + 0x30);
            }
        } else {
            int i;
            first = func_002A7820(0, 3);
            /* regions[k] is read twice (cse merges the loads): that keeps the
             * search at 30 insns at expand time, so jump1 does not copy the
             * loop's exit test in front of the loop. */
            for (i = 0; i < 4; i++) {
                int k = (i + first) % 4;
                if (((SpawnerSlots *)state)->regions[k] != -1) {
                    region = D_L06_001B290C + ((SpawnerSlots *)state)->regions[k] * 0x80;
                    break;
                }
            }
            if (!region) {
                float radius = *(float *)(state + 0x70);
                if (radius < 3.0f)
                    radius = 3.0f;
                func_L02_0031E9E8(point, radius);
                func_00282CC0(point, point, moby + 0x10);
            } else {
                qcopy(point, region + 0x30);
            }
        }
        if (region) {
            func_00282D30(delta, region, func_002A7878(-1.0f, 1.0f));
            func_00282CC0(point, point, delta);
            func_00282D30(delta, region + 0x10, func_002A7878(-1.0f, 1.0f));
            func_00282CC0(point, point, delta);
        }
        {
            float height = func_002A89A8(point, 0, 0.5f);
            if (height != 0.0f)
                point[2] = height;
        }
        func_00282CF0(delta, point, moby + 0x10);
        {
            float distance = func_00282DF0(delta) * 0.01000000071f;
            func_00282F20(delta, delta, distance);
            func_0029FCC0(moby, 0, origin);
            func_00282F20(step, delta, 0.05f);
            func_002ACB48(step, 0.025f);
            func_00282CC0(origin, origin, step);
            delta[2] = func_L00_0031CDD0(origin, point, 0, distance, -0.002722222358f);
        }
        ((SpawnerSlots *)state)->children[slot] = func_L06_003F3EF0(moby, origin, delta,
                                           *(unsigned char *)(state + 0x83), (unsigned char)slot);
        func_002E5CF8(0, 0, moby);
        *(short *)(state + 0x7E) = *(short *)(state + 0x7C);
        (*(unsigned char *)(state + 0x81))++;
        break;
    }
    case 2:
        func_002ABBB8(moby, state + 0x60, 0, 0.0f, 0.0f, 30, 8, 20, 8.0f, 4.0f, 18.0f, 1.0f, 1, 15.0f, 1, 1, -1, 0,
                      0x810001);
        func_002E5DA0(1, 0, moby, 0x75D);
        func_L02_0032B468(moby, 0x6C5, moby + 0x10, moby + 0xF0, 0, 0, 0.0f,
                          D_L06_001A8F20, D_L06_001A8F20, D_L06_001A8F20);
        func_L02_0032B468(moby, 0x6C6, moby + 0x10, moby + 0xF0, 0, 0, 0.0f,
                          D_L06_001A8F20, D_L06_001A8F20, D_L06_001A8F20);
        func_L02_0032B468(moby, 0x6C7, moby + 0x10, moby + 0xF0, 0, 0, 0.0f,
                          D_L06_001A8F20, D_L06_001A8F20, D_L06_001A8F20);
        func_0029F338(moby);
        return;
    }
    if (*(unsigned char *)(moby + 0x31) && func_00282E48(moby + 0x10, D_L06_001B9840) < 24.0f) {
        func_002A93B0(moby);
        *(unsigned char *)(moby + 0x6F) = 0x16;
    }
}
