#include "include_asm.h"

#include "common.h"
extern void func_002B9180(char *);
extern void func_00282CC0(char *, char *, char *);
typedef int TI __attribute__((mode(TI)));
extern float func_002B0520(TI *pos);
extern int D_001A79F0 MACRO_ADDR;
extern float D_001B1DC0[] MACRO_ADDR;

void func_PAL_002BB258(char *p)
{
    float *f = (float *)p;
    float *s = f + 0xC;
    float lim = s[3];
    float tmp[4] __attribute__((aligned(16)));
    TI c1, c2;
    int x, y;
    float h;

    if (D_001A79F0 == 15) {
        if (f[6] < lim) {
            func_002B9180(p);
            return;
        }
    } else if (f[6] < lim || f[4] < 0.0f || f[5] < 0.0f || f[4] > 1024.0f || f[5] > 1024.0f) {
        func_002B9180(p);
        return;
    }
    x = (int)f[8];
    y = (int)f[9];
    func_00282CC0((char *)tmp, (char *)s, (char *)D_001B1DC0);
    func_00282CC0((char *)(f + 8), (char *)(f + 8), (char *)tmp);
    func_00282CC0((char *)(f + 4), (char *)(f + 4), (char *)tmp);
    if (*(short *)(p + 0xA) != 2 && (x != (int)f[8] || y != (int)f[9])) {
        c1 = *(TI *)(f + 8);
        h = func_002B0520(&c1);
        if (h >= D_001B1DC0[4]) {
            c2 = *(TI *)(f + 8);
            lim = func_002B0520(&c2);
        } else {
            lim = D_001B1DC0[4];
        }
        if (f[10] < lim) {
            func_002B9180(p);
            return;
        }
    }
    s[2] -= 0.00392f;
    s[3] = lim + D_001B1DC0[2];
}


extern char *func_002B9030(int size);
extern int ref_002BA8A0_01(float f);
extern unsigned char *ref_002BA8A0_00;

/* Allocates a one-byte record, nudges the source's field 8 up by 0.2, copies the source's
 * first 16 bytes into the record and fills the record's header. */
void func_PAL_002BB458(void *a0, int a1)
{
    char *obj = (char *)func_002B9030(1);
    unsigned char byte;
    int r;

    if (obj == 0)
        return;
    *(float *)((char *)a0 + 8) = *(float *)((char *)a0 + 8) + 0.2f;
    qcopy(obj + 0x10, a0);
    *(int *)(obj + 4) = (a1 << 24) | 0x00907070;
    r = ref_002BA8A0_01(2.0f);
    *(char *)(obj + 9) = (char)(r + 0x40);
    *(char *)(obj + 3) = 0x44;
    *(char *)(obj + 1) = 0;
    byte = *ref_002BA8A0_00;
    *(int *)(obj + 0x20) = a1;
    *(float *)(obj + 0xC) = 63000.00390625f;
    *(unsigned char *)(obj + 8) = 0xA0;
    *(short *)(obj + 0xA) = 0x16;
    *(char *)(obj + 2) = byte;
}


INCLUDE_ASM("asm/pal/game", func_PAL_002BB530);
