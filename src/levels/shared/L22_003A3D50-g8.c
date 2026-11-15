#include "common.h"
typedef int Quad0792 __attribute__((mode(TI)));
extern char *D_L22_0023B530[3][60] __attribute__((section(".data")));
extern int D_L22_001B2AB8[] MACRO_ADDR;
extern int D_L22_001B2AC4[] MACRO_ADDR;
extern char *D_L22_001B2AB4[] MACRO_ADDR;
typedef struct Globals_3D50 {
    char pad[0x1874];
    int mode;
    char gap[0xA18];
    char *player;
} Globals_3D50;
extern Globals_3D50 D_00189E20;
extern float D_L22_001AF380 __attribute__((sda));
extern float D_L22_001AF308 __attribute__((sda));
extern Quad0792 D_L22_001C00E0 __attribute__((section(".data")));
extern float func_L22_003A65E0(void *);
extern int func_L22_003A42E8(void *, void *, int, int);
extern void func_002A7750(void *, int, int);
extern float func_00282E48(void *, void *);
extern void func_00282948(void *);
extern int func_002A77E0(int);
extern void func_L22_003A3550(void *, int, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L22_003A2988(void *, float);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_L22_003A3B50(void *, int);

void func_L22_003A3D50(char *obj) {
    struct { Quad0792 point, high; } v;
    char *st = *(char **)(obj + 0x68);
    int i, n;
    int *counts = D_L22_001B2AB8;
    int offset;
    i = 0;
    offset = 0;
    do {
        int *count = counts;
        char **slot = (char **)((char *)D_L22_0023B530 + offset);
        for (n = 49; n >= 0; n--, slot++) {
            if (*slot) {
                if (D_00189E20.mode > 0 &&
                    *(unsigned char *)(D_00189E20.player + 0x43) != 6 &&
                    func_L22_003A65E0(*slot) < D_L22_001AF380) {
                    if (func_L22_003A42E8(obj, *slot, i, 1)) {
                        if (!*(unsigned char *)(*slot + 0x20)) {
                            func_002A7750(*slot, 16, 0);
                            *(unsigned char *)(*slot + 0x23) = 127;
                        }
                        (*count)--;
                        *slot = 0;
                        D_L22_001B2AC4[0]--;
                    } else {
                        float ratio = func_L22_003A65E0(*slot) / D_L22_001AF380;
                        if (ratio > 1.0f) ratio = 1.0f;
                        else if (ratio < 0.1f) ratio = 0.1f;
                        *(unsigned char *)(*slot + 0x23) = (int)(ratio * 127.0f);
                        continue;
                    }
                } else {
                    if (!(*(float *)(st + 0x20) > 0.0f) || (unsigned char)obj[0x43] == 4 || (unsigned char)obj[0x43] == 8)
                        continue;
                    if (!(fast_vec_dist(*slot + 0x10, obj + 0x10) < D_L22_001AF380) || !func_L22_003A42E8(obj, *slot, i, 0))
                        continue;
                    if (!*(unsigned char *)(*slot + 0x20)) func_002A7750(*slot, 17, 0);
                    (*count)--;
                    *slot = 0;
                    D_L22_001B2AC4[0]--;
                }
            }
        }
        counts++;
        offset += 240;
        i++;
    } while (i < 3);
    for (i = 1; i >= 0; i--) {
        func_00282948(D_L22_001B2AB4[0] + 4);
        func_00282948(D_L22_001B2AB4[0]);
    }
    if (func_002A77E0(30) == 0 && D_L22_001B2AC4[0] < 12) {
        int group;
        Quad0792 *high;
        func_L22_003A3550(&v.point, 1, 0.0f);
        high = &v.high;
        group = 0;
        while (group < 3) {
            int next_group = group + 1;
            char **slot = D_L22_0023B530[group];
            int remaining;
            for (remaining = 49; remaining >= 0; remaining--, slot++) {
                if (*slot && fast_vec_dist(*slot + 0x10, &v.point) < 4.0f) {
                    char *axis = *slot + 0xC0 + func_002A77E0(2) * 16;
                    float scale;
                    if (func_002A77E0(2)) scale = D_L22_001AF308;
                    else scale = -D_L22_001AF308;
                    FastVecScale(high, axis, scale);
                    FastVecAdd(&v.point, &v.point, high);
                    func_L22_003A2988(&v.point, 0.0f);
                }
            }
            group = next_group;
        }
        qcopy(high, &v.point);
        func_L22_003A2988(high, 3.0f);
        if (CollLine(high, &v.point, 0x12, 0, 0)) qcopy(&v.point, &D_L22_001C00E0);
        SpawnRandomKindAt(&v.point, 0);
    }
}
