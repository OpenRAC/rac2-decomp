#include "common.h"

extern void func_00282CC0(char *, char *, char *);
extern float func_00283CE0(int);
extern int func_00283D38(int, int, float);
extern int D_L13_001B1624 __attribute__((sda));
extern int D_L13_001B1628 __attribute__((sda));
extern int D_L13_001B1650 __attribute__((sda));
extern int D_L13_001B1654 __attribute__((sda));
extern int D_L13_001B1658 __attribute__((sda));
void func_L13_0041AB30(char *obj)
{
    char *s = *(char **)(obj + 0x68);
    int j;
    char *q;
    if (*(short *)(s + 0x12)) {
        (*(short *)(s + 0x12))--;
        {
            int i;
            for (i = 0; i < 23; i++)
                func_00282CC0(s + 0x60 + i * 16, s + 0x60 + i * 16, s + 0x260 + i * 16);
        }
        {
            int i = 0;
            do {
                int next = i + 1;
                char *p;
                q = (char *)(i * 16 + (int)s);
                j = 2;
                p = q;
                do {
                    q += 0x460;
                } while (0);
                for (; j >= 0; j--) {
                    char *b = p + 0x560 + (2 - j) * 64;
                    char *a = q + (2 - j) * 64;
                    func_00282CC0(a, a, b);
                }
                i = next;
            } while (i < 4.0f);
        }
        {
            int i;
            for (i = 0; i < 4; i++) {
                unsigned char *idx = (unsigned char *)s + 0x18;
                q = (char *)(idx[i] * 16 + (int)s) + 0x20;
                qcopy(s + 0x420 + i * 16, q);
            }
        }
    }
    if (*(short *)(s + 0x12) > D_L13_001B1624) {
        float a = func_00283CE0(*(short *)(s + 0x12) - D_L13_001B1624);
        float b = func_00283CE0(*(int *)(s + 0x620) - D_L13_001B1624);
        *(int *)(s + 0x14) = func_00283D38(D_L13_001B1654, D_L13_001B1650, a / b);
    } else if (*(short *)(s + 0x12) > D_L13_001B1628) {
        float a = func_00283CE0(*(short *)(s + 0x12) - D_L13_001B1628);
        float b = func_00283CE0(D_L13_001B1624 - D_L13_001B1628);
        *(int *)(s + 0x14) = func_00283D38(D_L13_001B1658, D_L13_001B1654, a / b);
    } else *(int *)(s + 0x14) = 0;
}
