#include "include_asm.h"

typedef unsigned char u8;
extern void func_002A7750(unsigned char *, int, int);
extern float func_002A7878(float, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L26_003DF7E8(void);
extern int D_L26_001A8FF0;
extern float D_L26_001B0660 __attribute__((sda));
typedef struct { float f[2]; float g[2]; } Counters;

void func_PAL_L26_003E3AB8(char *a0) {
    char *s3 = a0;
    char *s4 = *(char **)(s3 + 0x68);
    int i;
    int j;

    switch (*(u8 *)(s3 + 0x20)) {
    case 0:
        *(u8 *)(s3 + 0x30) = 0xFF;
        func_002A7750((unsigned char *)s3, 1, -1);
        *(int *)s4 = 0;
        *(float *)(s4 + 4) = 0.5f;
        break;
    case 1:
        if (D_L26_001A8FF0 != 0) {
            for (i = 0; i < 2; i = j) {
                float v;

                j = i + 1;
                v = ((Counters *)s4)->f[i] + D_L26_001B0660 * 0.020000001f;
                ((Counters *)s4)->f[i] = v;
                if (1.0f < v) {
                    v = v - 1.0f;
                    ((Counters *)s4)->f[i] = v;
                    v = ((Counters *)s4)->g[j & 1] + func_002A7878(0.333f, 0.666f);
                    ((Counters *)s4)->g[i] = v;
                    if (1.0f < v) {
                        v = v - 1.0f;
                        ((Counters *)s4)->g[i] = v;
                    }
                }
            }
            func_L00_002E6CF0((void *)func_L26_003DF7E8, s3);
        }
        break;
    }
}
