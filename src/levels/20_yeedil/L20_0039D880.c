#include "common.h"

/* func_L20_0039D880 sheds damage effects as health falls below each threshold (compare
   func_002B3380). Its unit is built with -g: retail has the two nops -g leaves before the
   div.s. The final copy uses qcopy (the retail materialises both transfer addresses). */

extern int func_00283CF0(float);
extern float func_002A78D8(float, float);
extern float func_00283B98(float, float);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void *func_00273730(void *, int, int, int, void *, void *, void *, float, float, int);
extern void func_002E5E58(int, int, int);
extern void func_0029F338(void *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_00310C88(unsigned char *);
extern char D_L20_001B9E80[];

void func_L20_0039D880(char *self) {
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
        threshold = FloatToInt(fraction * 255.0f) & 0xFF;
        global = D_L20_001B9E80;
        callback = func_00310C88;
        for (i = 0; i < 10; i++) {
            if ((unsigned int)(i - 4) < 2) continue;
            if (i == 7) continue;
            bit = 1 << i;
            if ((*(unsigned short *)(*(char **)(state + 0x254) + 0x7C) & bit) == 0) continue;
            if (threshold >= *(unsigned char *)(state + i + 0x270)) continue;
            angle = FastAddRotations(func_002A78D8(90.0f, 120.0f) * 0.017453294f, *(float *)(global + 0x158));
            speed = func_002A7878(2.0f, 4.0f) * 0.016666668f;
            buf[0] = func_00283180(angle) * speed;
            buf[1] = func_00283198(angle) * speed;
            buf[2] = 0.0f;
            buf[2] = func_002A7878(5.0f, 8.0f) * 0.016666668f;
            effect = func_00273730(*(char **)(state + 0x254), 1,
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
            SpawnExplosion(buf, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, 0.5f, 20.0f, 1, 0, 0, 0);
        }
    }
}
