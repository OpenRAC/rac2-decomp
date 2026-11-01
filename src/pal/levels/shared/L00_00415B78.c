#include "include_asm.h"

#include "common.h"
extern void func_PAL_L00_00416638(void *);
extern void ref_L00_00410D20_00(void (*)(void *), void *);
extern void func_PAL_L00_004169B0(void *);
extern void func_002A0488(void *, int, int, int);
extern int func_00283D38(int, int, float);
extern float func_00283180(float);
extern void func_L00_004110D8(void *);
extern void func_00282C88(void *);
extern void func_L00_004118A8(void *, void *, void *, void *, void *, int, int, int, void *, float);
extern int func_002A7820(int, int);
extern void func_002AF000(void *, float, float, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern int func_00277F48(void *, int, void *, int, float);
extern int func_002829D8(void *);
extern int func_00282948(void *);
extern float func_00283B98(float, float);
typedef struct {
    char data[0x18];
    char *target;
    char end[0x14];
} ParticleEffectSlot;
extern char D_00189E20[];
extern ParticleEffectSlot ref_L00_00410D20_01[];
extern char *ref_L00_00410D20_02[];

void func_PAL_L00_00415B78(char *m) {
    float a[4], b[4];
    int i;

    qcopy_nc(m + 0x10, D_00189E20);
    for (i = 0; i < 30; i++) {
        char *s;
        char *other;
        int dead;

        if (!ref_L00_00410D20_01[i].target)
            continue;
        s = (char *)&ref_L00_00410D20_01[i];
        *(float *)(s + 0xC) = func_00283B98(*(float *)(s + 0xC), 0.25132746f);
        dead = 0;
        if (*(signed char *)(*(char **)(s + 0x18) + 0x20) < 0)
            dead = 1;
        if (!*(int *)(*(char **)(s + 0x18) + 0x98))
            dead = 1;
        if (func_00282948(s))
            dead = 1;
        if (func_002829D8(s + 0x1C)) {
            int count, j;
            char *target = *(char **)(s + 0x18);

            *(float *)(s + 0x1C) = *(float *)(s + 0x14);
            count = func_00277F48(target + 0x10, 0, target, 0, 8.0f);
            for (j = 0; j < count; j++) {
                other = ref_L00_00410D20_02[j];
                if ((*(unsigned short *)(other + 0x34) & 0x1000) && other &&
                    *(unsigned char *)(other + 0x20) != 254 && *(unsigned char *)(other + 0x20) != 253 &&
                    *(short *)(*(char **)(other + 0x24) + 0x46) == 5)
                    goto collide;
            }
        }
    random_particles:
        if (func_001163B0() % 11 == 0) {
            int j, count;

            {
                float scale = func_002A7878(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(s + 0x18) + 0xC) * scale;
                float y = func_002A7940();
                float z = func_002A7940();

                func_002AF000(a, x, y, z);
            }
            {
                float scale = func_002A7878(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(s + 0x18) + 0xC) * scale;
                float y = func_002A7940();
                float z = func_002A7940();

                func_002AF000(b, x, y, z);
            }
            j = func_002A7820(5, 15);
            count = func_002A7820(15, 30);
            func_L00_004118A8(m, *(char **)(s + 0x18), *(char **)(s + 0x18), a, b, 0, j, count, s, 0.0f);
        }
        if (dead) {
            func_L00_004110D8(s);
            *(char **)(s + 0x18) = 0;
            continue;
        }
        goto timer;
    collide:
        func_00282C88(a);
        func_L00_004118A8(m, *(char **)(s + 0x18), other, a, a, 1, 10, 30, s, *(float *)(s + 0x10));
        func_L00_004118A8(m, *(char **)(s + 0x18), other, a, a, 0, 10, 30, s, 0.0f);
        goto random_particles;
    timer:
        if (*(int *)(s + 0x24) == 0) {
            int c = func_00283D38(*(int *)(s + 4), *(int *)(s + 8),
                                  (func_00283180(*(float *)(s + 0xC)) + 1.0f) * 0.5f);

            func_002A0488(*(char **)(s + 0x18), c & 255, (c >> 8) & 255, (c >> 16) & 255);
        } else
            --*(int *)(s + 0x24);
    }
    func_PAL_L00_004169B0(m);
    ref_L00_00410D20_00(func_PAL_L00_00416638, m);
}

