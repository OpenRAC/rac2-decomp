#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_002A7750(unsigned char *, int, int);

extern void func_00282D60(TI128 *, char *, float);

extern int func_00283DB8(TI128 *, float);

extern float func_00283248(float, float);

/* The table is indexed in 128-byte records; position starts at offset 0x30. */
typedef struct { char bytes[128]; } EntryECE0;
extern EntryECE0 *D_L07_001B23CC __attribute__((nosda));

void func_L07_003EECE0(char *arg)
{
    TI128 tmp;
    char *s0 = arg;
    char *s1;
    char *definition;
    unsigned short v;
    int r;
    char *entry;
    float f0, f1;

    s1 = *(char **)(arg + 0x68);
    v = *(unsigned short *)(arg + 0x34);
    definition = *(char **)(arg + 0x24);
    *(unsigned short *)(arg + 0x34) = (v & 0xFFBE) | 0x1000;
    *(int *)(arg + 0x98) = *(int *)(definition + 0x10);
    func_002A7750((unsigned char *)arg, 3, -1);
    *(unsigned char *)(arg + 0x30) = 0xFF;
    *(unsigned short *)(arg + 0x32) = 0xFF;

    if (*(int *)(s1 + 0x98) != 0) {
        scale_vector(&tmp, s0, 0.0009765625f);
        r = func_00283DB8(&tmp, 128.0f);
        if (r != -1) {
            qcopy(arg + 0x10, &D_L07_001B23CC[*(int *)(s1 + 0x98)].bytes[0x30]);
        }
    }

    r = *(int *)(s1 + 0x94);
    entry = (char *)(r * 128 + (int)D_L07_001B23CC);
    f1 = *(float *)(arg + 0x10);
    f0 = *(float *)(arg + 0x14);
    *(float *)(s1 + 0xE8) = func_00283248(*(float *)(entry + 0x30) - f1, *(float *)(entry + 0x34) - f0);
    qcopy(s1 + 0xF0, arg + 0x10);
    qcopy(s1 + 0xD0, &D_L07_001B23CC[*(int *)(s1 + 0x94)].bytes[0x30]);
}
