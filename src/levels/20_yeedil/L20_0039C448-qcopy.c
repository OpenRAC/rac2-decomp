#include "common.h"

/* The grouped quadword copy: the R5900 lq/sq pair with both addresses in registers,
   and the copy as the scheduling barrier the retail's inline-asm macro was. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_00282CC0(char *, char *, char *);

extern void func_002A8C00(char *, int, int, void *, float);

extern int func_002761F8(void *, void *, int, int, void *);

extern int func_00282948(void *);

extern void func_002E5DA0(int, int, void *, int);

extern void func_L00_002E6EF8(void *, int);

extern void func_L20_0039C5D0(char *);

extern void func_L20_0039C8C8(char *, int, int);

extern void func_L20_0039CC10(void);

extern void func_0029F338(int);

extern char D_L20_001C0420[];

void func_L20_0039C448(char *arg0) {
    char *s0 = arg0 + 0x10;
    char *s3 = *(char **)(arg0 + 0x68);
    char *s1;
    char buf[0x30];

    *(TI128 *)s3 = *(TI128 *)s0;
    s1 = s3 + 0x10;
    FastVecAdd(s0, s0, s1);
    make_hit_descriptor(buf, (int)arg0, 0x10001, s1, *(float *)(s3 + 0x2C));
    if (CollLine(s3, s0, 0, *(int *)(arg0 + 0xB8), buf) != 0
        || func_00282948(s3 + 0x20) != 0) {
        func_L20_0039C8C8(D_L20_001C0420, 0x14, 1);
        func_002E5DA0(2, 0, arg0, 0x12EF);
        func_0029F338((int)arg0);
    } else {
        EmitJitteredParticleTrail(arg0);
        func_L00_002E6EF8(func_L20_0039CC10, (int)arg0);
    }
}

void func_L20_0043D470(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    *(f32 *)(*(char **)(state + 0x84) + 0x0) = 8.0f;
    *(f32 *)(*(char **)(state + 0x84) + 0x4) = 2.5f;
    *(u8 *)(*(char **)(state + 0x84) + 0x18) = 1;
    *(u16 *)(*(char **)(state + 0x84) + 0x1A) = 0;
    *(u8 *)(*(char **)(state + 0x84) + 0x1E) = 1;
    *(u8 *)(*(char **)(state + 0x84) + 0x1F) = 0;
    *(TI128 *)(*(char **)(state + 0x84) + 0x20) = *(TI128 *)(state + 0x60);
}
