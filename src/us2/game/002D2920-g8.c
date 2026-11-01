#include "include_asm.h"

#include "common.h"
extern char *D_001A8CFC;
extern int D_001A7340;
extern int D_001ABA54 __attribute__((sda));
extern int D_001ABA3C __attribute__((sda));
extern int D_001ABA40[] SDATA(D_001ABA40);
extern int D_001ABD28[] MACRO_ADDR;
extern float D_001B23A8;
extern void func_0027C540(long);
extern void func_0027C660(void);
extern int func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_0027FAA8(int, int, unsigned long, char *, int);
extern void func_0028FC48(int, int, int, int, unsigned long, int);

int func_US2_002D2920(void)
{
    int i, y = 125;
    int *keys = D_001ABD28;
    int *enabled = D_001ABA40;
    float z;

    func_0027C540(0);
    z = 0.775f;
    func_00300A00((char *)func_00336D50(D_001A8CFC + 0x8710, 0x8B), 0x60442D00,
                 (float)(D_001A7340 / 2), (float)D_001ABA54, 1.0f, D_001B23A8, z);
    func_00300A00((char *)func_00336D50(D_001A8CFC + 0x8710, 0x8C), 0x55F0C070,
                 (float)(D_001A7340 / 2), (float)D_001ABA54, 1.0f, D_001B23A8, z);
    func_00300A00((char *)func_00336D50(D_001A8CFC + 0x8710, 0x8D), 0x55F0C070,
                 (float)(D_001A7340 / 2), (float)D_001ABA54, 1.0f, D_001B23A8, z);
    func_0027FAA8(D_001A7340 / 2, 65, 0x80F0F0F0UL, func_00288FB8(0x30A2), -1);
    func_0027FAA8(D_001A7340 / 2, 321, 0x80F0F0F0UL, func_00288FB8(0x2C0B), -1);
    func_0027FAA8(D_001A7340 / 2, 346, 0x80F0F0F0UL, func_00288FB8(0x2BE5), -1);
    func_0028FC48(312, 128, 449, 130, 0x55F0C070, 0);
    func_0028FC48(312, 265, 451, 267, 0x55F0C070, 0);
    func_0028FC48(312, 128, 314, 265, 0x55F0C070, 0);
    func_0028FC48(449, 128, 451, 265, 0x55F0C070, 0);
    for (i = 0; i < 5; i++, y += 31, keys++, enabled++) {
        unsigned long color = i == D_001ABA3C ? 0x7000FFFFUL : 0x80F0F0F0UL;
        int key = *enabled ? *keys : 0x2C56;
        func_0027FAA8(165, y, color, func_00288FB8(key), -1);
    }
    func_0027C660();
    return 0;
}
