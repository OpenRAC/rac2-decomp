/* 30 October 2026 retained reconstruction, not a match.
 * Profile: -O2 -G0 -ffunction-sections. USA v1.01: 440/444 bytes, 0/1.
 * Corrected the matrix extent to64 bytes: func_002AB6D8 copies four rows then replaces
 * its last row before angle calculations. Corrected scale to retail bits0x3A7FFFD5 and
 * used reviewed qcopy. Frame now0x90 as in retail; link cursor allocation and
 * initialization stores still differ. Byte-sized link and index-first addition tie.
 * Older source and trial history remain in Git and the private workspace.
 */
#include "common.h"
extern char *func_0029EFD0(int);
extern void func_00282D60(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AB6D8(char *, char *);

void func_L15_004360D8(char *self, int idx)
{
    char *p = *(char **)(self + 0x24);
    int count = *(short *)(p + 0x2E);

    if (count != 0) {
        char *entry = p + (count << 4);
        u8 link = *(u8 *)(idx + entry + 1);

        if (link != 0xFF) {
            char *basis = self + 0xC0;
            char *pos = self + 0x10;
            char *obj;
            char *st;
            char *a;
            char *b;
            /* The angle helper reads all four rows, then replaces its last row. */
            char m[0x40] __attribute__((aligned(16)));

            p = entry + (link << 4);
            obj = func_0029EFD0(0x1211);
            st = *(char **)(obj + 0x68);
            a = st + 0x420;
            b = st + 0x410;
            func_00282D60(a, p, *(float *)(self + 0x2C) * 0.0009765599970705807f);
            func_00283098(a, a, basis);
            func_00282CC0(a, a, pos);
            *(u8 *)(obj + 0x30) = 0xFF;
            *(u16 *)(obj + 0x32) = 0x1FF;
            *(u16 *)(obj + 0x34) |= 0x100;
            *(float *)(obj + 0x2C) = *(float *)(self + 0x2C);
            func_00282CF0(b, a, pos);
            func_00282F20(b, b, 0.26666668f);
            qcopy(obj + 0xC0, basis);
            qcopy(obj + 0xD0, (self + 0xD0));
            qcopy(obj + 0xE0, (self + 0xE0));
            qcopy(m, basis);
            qcopy(m + 0x10, (self + 0xD0));
            qcopy(m + 0x20, (self + 0xE0));
            func_002AB6D8(m, st + 0x400);
            *(u8 *)(obj + 0x20) = 7;
            *(u16 *)(obj + 0x7C) = (1 << idx) | 0x8000;
            qcopy(obj + 0x10, pos);
            *(int *)(obj + 0x98) = 0;
        }
    }
}
