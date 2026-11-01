#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_00282CC0(char *, char *, char *);
extern void func_002A8C00(char *, int, int, void *, float);
extern int func_002761F8(void *, void *, int, int, void *);
extern int func_00282948(void *);
extern void func_002E5DA0(int, int, void *, int);
extern void func_L00_002E6EF8(void *, int);
extern void func_PAL_L20_0039F518(char *);
extern void func_PAL_L20_0039F810(char *, int, int);
extern void func_L20_0039CC10(void);
extern void func_0029F338(int);
extern char D_L20_001C0420[];

void func_PAL_L20_0039F390(char *arg0) {
    char *s0 = arg0 + 0x10;
    char *s3 = *(char **)(arg0 + 0x68);
    char *s1;
    char buf[0x30];

    *(TI128 *)s3 = *(TI128 *)s0;
    s1 = s3 + 0x10;
    func_00282CC0(s0, s0, s1);
    func_002A8C00(buf, (int)arg0, 0x10001, s1, *(float *)(s3 + 0x2C));
    if (func_002761F8(s3, s0, 0, *(int *)(arg0 + 0xB8), buf) != 0
        || func_00282948(s3 + 0x20) != 0) {
        func_PAL_L20_0039F810(D_L20_001C0420, 0x14, 1);
        func_002E5DA0(2, 0, arg0, 0x12EF);
        func_0029F338((int)arg0);
    } else {
        func_PAL_L20_0039F518(arg0);
        func_L00_002E6EF8(func_L20_0039CC10, (int)arg0);
    }
}

extern char *func_0029EFD0(int);

/* Spawns an object of type 0x12F2 and fills its position and its sub-record vector. */
char *func_PAL_L20_0039F488(char *arg0, char *arg1, char *arg2, float f12) {
    char *v;
    char *o = func_0029EFD0(0x12F2);

    if (o != 0) {
        *(int *)(o + 0xB8) = (int)arg0;
        *(TI128 *)(o + 0x10) = *(TI128 *)arg1;
        v = *(char **)(o + 0x68);
        *(unsigned char *)(o + 0x30) = 0xFF;
        *(TI128 *)(v + 0x10) = *(TI128 *)arg2;
        *(float *)(v + 0x2C) = f12;
        *(int *)(v + 0x20) = 0xFA;
    }
    return o;
}
