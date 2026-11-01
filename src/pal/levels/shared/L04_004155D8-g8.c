#include "include_asm.h"

typedef unsigned char u8;
typedef short s16;
extern u8 *D_L04_001B24DC;
extern u8 *D_L04_001FE340[];
extern int D_L04_001A8FE4[] __attribute__((sda));
extern int D_L04_001A8FE8[] __attribute__((sda));
extern float func_002A7878(float, float);
extern int func_00283CF0(float);

/* Collects the racers, sorts their recorded times, and records each rank and
   the next racer in the ordered list. */
void func_PAL_L04_004155D8(u8 *object) {
    u8 *list[24], **out;
    u8 *state = *(u8 **)(object + 0x68), *obj, *p, *route;
    int *slot = (int *)(state + 0x1E4);
    int i, j, n = 1, a, b, k;
    float length, distance;

    out = list + 1;
    *(u8 **)(state + 0x39C) = object;
    list[0] = object;
    for (k = 19; k >= 0; k--, slot++) {
        if (*slot != -1) {
            obj = D_L04_001B24DC + (*slot << 8);
            p = *(u8 **)(obj + 0x68);
            *out++ = obj;
            n++;
            if (*(int *)(p + 0x1A0) == 0) {
                route = D_L04_001FE340[*(int *)(state + 0x1A8)];
                length = (float)*(int *)route * *(float *)(route + 0x1C);
                distance = length - *(float *)(p + 0x11C) +
                           length * (float)(D_L04_001A8FE4[0] - *(int *)(p + 0x160));
                if (distance <= 0.0f) {
                    distance = func_002A7878(10.0f, 20.0f);
                }
                *(int *)(p + 0x1A0) = func_00283CF0(distance * 2.4999998f);
                if (*(int *)(p + 0x1A0) < 5) {
                    *(int *)(p + 0x1A0) = 5;
                }
                *(int *)(p + 0x1A0) += D_L04_001A8FE8[0];
            }
        }
    }
    {
        int i;
        for (i = 0; i < n - 1; i++) {
            for (j = 0; j < n - i - 1; j++) {
                a = 0;
                b = 0;
                {
                    u8 *obj = list[j];
                    if (*(s16 *)(obj + 0xAA) == 0xBBC) {
                        a = D_L04_001A8FE8[0];
                    } else if (*(s16 *)(obj + 0xAA) == 0xB2D) {
                        a = *(int *)(*(u8 **)(obj + 0x68) + 0x1A0);
                    }
                }
                {
                    u8 *obj = list[j + 1];
                    if (*(s16 *)(obj + 0xAA) == 0xBBC) {
                        b = D_L04_001A8FE8[0];
                    } else if (*(s16 *)(obj + 0xAA) == 0xB2D) {
                        b = *(int *)(*(u8 **)(obj + 0x68) + 0x1A0);
                    }
                }
                if (b < a) {
                    u8 *obj = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = obj;
                }
            }
        }
    }
    *(u8 **)(state + 0x39C) = list[0];
    for (i = 0; i < n; i++) {
        u8 *obj, *p;
        obj = list[i];
        if (*(s16 *)(obj + 0xAA) == 0xBBC) {
            *(int *)(state + 0x320) = i + 1;
            if (i == n - 1) {
                *(u8 **)(state + 0x3A0) = 0;
            } else {
                *(u8 **)(state + 0x3A0) = list[i + 1];
            }
        } else if (*(s16 *)(obj + 0xAA) == 0xB2D) {
            p = *(u8 **)(obj + 0x68);
            p[0xA2] = i + 1;
            if (i == n - 1) {
                *(u8 **)(p + 0x1A4) = 0;
            } else {
                *(u8 **)(p + 0x1A4) = list[i + 1];
            }
        }
    }
}
