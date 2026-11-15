#include "common.h"
extern char *func_379CA0(char *);
extern int func_001163B0(void);
extern int func_L05_0037BBB8(char *);
extern int func_L05_0037BB90(char *);
extern unsigned short *D_L05_001FB220[];
extern char *D_L05_001B251C MACRO_ADDR;
extern signed char D_L05_002BA2B8[];
extern float func_00283CE0(int);
void func_L05_0037BF48(char *obj)
{
    unsigned short *p;
    char *child, *parent;
    int off, choice, ordinal, i, count, row;

    short t;
    if (D_L05_001FB220[*(unsigned char *)(obj + 0x21)] == 0) return;
    parent = func_379CA0(obj);
    ordinal = 1;
    choice = func_001163B0() % 2;
    p = D_L05_001FB220[*(unsigned char *)(obj + 0x21)];
    do {
        off = (*p & 0x7fff) << 8;
        child = func_379CA0(D_L05_001B251C + off);
        if (func_L05_0037BBB8(D_L05_001B251C + off) &&
            !func_L05_0037BB90(D_L05_001B251C + off) &&
            *(int *)(child + 0x1c) == *(int *)(parent + 0x1c)) {
            float left = -10.5f, right = 10.5f;
            *(int *)(child + 0x20) = ordinal++;
            count = -1;
            for (i = 0; i < 25; i++) {
                if (D_L05_002BA2B8[i + choice * 25 + (*(int *)(parent + 0x18) - 3) * 50]) {
                    if (++count == *(int *)(child + 0x20)) {
                        *(int *)(child + 8) = 0;
                        row = i / 5;
                        *(float *)child = IntToFloat(row) * left;
                        *(float *)(child + 4) = IntToFloat(i - (i / 5) * 5 - 2) * right;
                        break;
                    }
                }
            }
        }
        t = *(short *)p;
        p++;
        if (t < 0) break;
        if (ordinal == *(int *)(parent + 0x18)) break;
    } while (t >= 0);
}
