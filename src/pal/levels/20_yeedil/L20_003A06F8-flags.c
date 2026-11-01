#include "include_asm.h"

#include "common.h"
extern int func_00283CF0(float);
extern float func_002A78D8(float, float);
extern float func_00283B98(float, float);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void *func_PAL_002735D0(void *, int, int, int, void *, void *, void *, float, float, int);
extern void func_002E5E58(int, int, int);
extern void func_0029F338(void *);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_PAL_003120C0(unsigned char *);
extern char D_L20_001B9E80[];

void func_PAL_L20_003A07C8(char *self) {
    char *state = *(char **)(self + 0x68);
    float buf[4];
    int i;
    unsigned int threshold;
    int bit;
    float angle, speed;
    char *effect;
    char *global;
    void (*callback)(unsigned char *);

    if (*(char **)(state + 0x254) == 0) return;
    {
        float health = *(float *)(state + 0x20);
        float maximum = (float)*(short *)(state + 0x24);
        float fraction;
        fraction = health / maximum;
        threshold = func_00283CF0(fraction * 255.0f) & 0xFF;
        global = D_L20_001B9E80;
        callback = func_PAL_003120C0;
        for (i = 0; i < 10; i++) {
            if ((unsigned int)(i - 4) < 2) continue;
            if (i == 7) continue;
            bit = 1 << i;
            if ((*(unsigned short *)(*(char **)(state + 0x254) + 0x7C) & bit) == 0) continue;
            if (threshold >= *(unsigned char *)(state + i + 0x270)) continue;
            angle = func_00283B98(func_002A78D8(90.0f, 120.0f) * 0.017453294f, *(float *)(global + 0x158));
            speed = func_002A7878(2.0f, 4.0f) * 0.020000001f;
            buf[0] = func_00283180(angle) * speed;
            buf[1] = func_00283198(angle) * speed;
            buf[2] = 0.0f;
            buf[2] = func_002A7878(5.0f, 8.0f) * 0.020000001f;
            effect = func_PAL_002735D0(*(char **)(state + 0x254), 1,
                *(short *)(*(char **)(state + 0x254) + 0xAA), i,
                *(char **)(state + 0x254) + 0x10, *(char **)(state + 0x254) + 0xF0,
                buf, 90.0f, 15.0f, 255);
            if (effect) *(void (**)(unsigned char *))(effect + 0x64) = callback;
            *(unsigned short *)(*(char **)(state + 0x254) + 0x7C) &= ~bit;
            func_002E5E58(7, 0, 0);
        }
    }
    if (*(float *)(state + 0x20) <= 0.0f) {
        char **p = (char **)(state + 0x258);
        int j;
        for (j = 1; j >= 0; j--, p++) {
            if (*p != 0) {
                func_0029F338(*p);
                *p = 0;
            }
        }
        if (*(char **)(state + 0x254) != 0) {
            func_0029F338(*(char **)(state + 0x254));
            *(char **)(state + 0x254) = 0;
            qcopy(buf, self + 0x10);
            buf[2] += 1.0f;
            func_PAL_L00_003FB330(buf, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, 0.5f, 20.0f, 1, 0, 0, 0);
        }
    }
}
