#include "include_asm.h"

#include "common.h"
extern char *func_002ED688(char *);
extern int func_001163B0(void);
extern float func_002A7878(float, float);
extern void func_00282CC0(void *, void *, void *), func_00283098(void *, void *, void *);
extern int func_002EE6A8(char *);
extern void func_PAL_002EE5C0(char *), func_PAL_002EF630(char *), func_002EE238(char *), func_002EE610(char *), func_002EE000(char *);
extern void func_002EE920(char *, void *), func_002EE678(char *, int);
extern int func_002EEB00(char *), func_002ED948(char *);
extern void func_002ED9C0(char *), func_PAL_002EF708(char *), func_PAL_002EF800(char *);
extern float func_00283198(float), func_00283180(float), func_00283B98(float, float);
extern void func_00282F20(void *, void *, float), func_00282DD8(void *, void *, void *);
extern int func_00283DB8(void *, float), func_002A7820(int, int);
extern char *D_L05_001B9710;
typedef unsigned int U128_C160 __attribute__((mode(TI)));

/* Update the movement state and target position of this object. */
void func_PAL_002EE914(char *obj)
{
    float v[4], v1[4], v2[4], v3[4], v4[4];
    U128_C160 axes[2];
    float v7[4], v8[4], v9[4], probe[4], tmp[4];
    char *s = func_002ED688(obj);
    char *player, *p;
    float direction;
    if (!s) return;
    axes[0] = 0;
    axes[1] = 0;
    ((float *)&axes[0])[2] = 1.0f;
    ((float *)&axes[1])[0] = 1.0f;
    qcopy(s + 0xB0, obj + 0x10);
    if (func_002EE6A8(obj) != 8) func_00282CC0(obj + 0x10, s + 0x90, obj + 0x10);
    func_PAL_002EE5C0(obj);
    func_PAL_002EF630(obj);
    func_002EE238(obj);
    func_002EE610(obj);
    func_002EE000(obj);
    player = D_L05_001B9710;
    switch (func_002EE6A8(obj)) {
    case 7:
        func_00282F20(v, *(char **)(s + 0x120) + 0xC0, -50.0f);
        func_00282CC0(v, *(char **)(s + 0x120) + 0x10, v);
        func_002EE920(obj, v);
        if (func_002EEB00(obj)) {
            func_002EE678(obj, 8);
            *(int *)(s + 0x130) = 750;
            direction = (func_001163B0() & 1) ? -1.0f : 1.0f;
            *(float *)(s + 0x140) = direction;
            *(float *)(s + 0x134) = direction < 0.0f ? 1.5707964f : -1.5707964f;
            *(float *)(s + 0x144) = func_002A7878(5.0f, 15.0f);
        }
        break;
    case 8: {
            float *basis;
            v[2] = 0;
            v[0] = func_00283198(*(float *)(s + 0x134)) * *(float *)(s + 0x144);
            v[1] = -func_00283180(*(float *)(s + 0x134)) * *(float *)(s + 0x144);
            v[3] = 0;
            *(float *)(s + 0x134) = func_00283B98(*(float *)(s + 0x134), *(float *)(s + 0x140) * 0.015707966f);
            qcopy(v9, player + 0x20);
            basis = v7;
            func_00282DD8(v8, &axes[1], v9);
            func_00282F20(v8, v8, 1.0f);
            func_00282DD8(basis, v9, v8);
            func_00283098(v, v, basis);
            func_00282CC0(obj + 0x10, *(char **)(s + 0x120) + 0x10, v);
            func_002EE920(obj, v);
            if (func_002ED948(obj))func_002EE678(obj, 9);
            if (func_002EEB00(obj)) {
                qcopy(probe, obj + 0x10);
                probe[3] = 5;
                if (func_00283DB8(probe, 256.0f) == -1) {
                    func_002ED9C0(obj);
                    func_002EE678(obj, 1);
                }
            }
            break;
        }
    case 9:
        qcopy(probe, obj + 0x10);
        probe[3] = 5;
        if (func_00283DB8(probe, 256.0f) == -1) {
            func_002ED9C0(obj);
            func_002EE678(obj, 1);
        }
        break;
    case 4:
        if (!*(char **)(s + 0x120)) {
            func_002ED9C0(obj);
            func_002EE678(obj, 1);
            break;
        }
        func_00282F20(v, *(char **)(s + 0x120) + 0xC0, 25.0f);
        if (*(int *)(s + 0xFC)) {
            func_00283098(tmp, s + 0x70, *(char **)(s + 0x120) + 0xC0);
            func_00282CC0(v, tmp, v);
        }
        func_00282CC0(v, *(char **)(s + 0x120) + 0x10, v);
        func_002EE920(obj, v);
        if (func_002EEB00(obj)) {
            func_002EE678(obj, 5);
            *(int *)(s + 0x130) = ((s32)(func_002A7820(300, 600)) * 5 + 2) / 6;
        }
        break;
    case 5:
        if (!*(char **)(s + 0x120)) {
            func_002ED9C0(obj);
            func_002EE678(obj, 1);
            break;
        }
        func_00282F20(v, *(char **)(s + 0x120) + 0xC0, 5.0f);
        if (*(int *)(s + 0xFC)) {
            func_00283098(tmp, s + 0x70, *(char **)(s + 0x120) + 0xC0);
            func_00282CC0(v, tmp, v);
        }
        func_00282CC0(v, *(char **)(s + 0x120) + 0x10, v);
        func_002EE920(obj, v);
        if (func_002EEB00(obj)) {
            func_002ED9C0(obj);
            func_002EE678(obj, 1);
        }
        break;
    case 6:
        if (!*(char **)(s + 0x120)) {
            func_002ED9C0(obj);
            func_002EE678(obj, 1);
            break;
        }
        func_00282F20(v, *(char **)(s + 0x120) + 0xC0, 10.0f);
        func_00282F20(v1, *(char **)(s + 0x120) + 0xE0, 0.05f);
        if (*(int *)(s + 0xFC)) {
            func_00283098(tmp, s + 0x70, *(char **)(s + 0x120) + 0xC0);
            func_00282CC0(v, tmp, v);
        }
        func_00282CC0(v, v1, v);
        func_00282CC0(v, *(char **)(s + 0x120) + 0x10, v);
        func_002EE920(obj, v);
        if (func_002EEB00(obj)) {
            func_002ED9C0(obj);
            func_002EE678(obj, 1);
        }
        break;
    case 3:
        p = *(char **)(s + 0x10);
        qcopy(v2, p + 0xC0);
        func_00282DD8(v3, v2, &axes[0]);
        func_00282F20(v3, v3, 1.0f);
        func_00282DD8(v4, v3, v2);
        func_00283098(v, s, v2);
        func_00282CC0(v, p + 0x10, v);
        func_002EE920(obj, v);
        break;
    case 1: if (func_002EEB00(obj))func_PAL_002EF708(obj);
        break;
    case 13: if (func_002EEB00(obj))func_PAL_002EF800(obj);
        break;
    }
}
