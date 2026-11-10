#include "include_asm.h"

/* func_L02_003EAE10 is a unit of its own: it reads $gp data (hence -G8) and needs the opt-in
   clear profile (-frac2-zero-ti-barrier, docs/build/compiler-notes.md): with it, the load of the
   state's +0x3C float follows the 16-byte clear at once, as retail has it. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int TI128 __attribute__((mode(TI)));

extern u16 *D_L02_001FC060[];
extern u8 *D_L02_001B359C_1[] __attribute__((sda));
extern int D_L02_001B35B8 __attribute__((sda));

extern void func_002833F0(float *, float *);
extern void func_00283698(float *, float *);
extern void func_00282CF0(float *, float *, float *);
extern void func_00283098(float *, float *, float *);
extern float func_00282C48(float);

int func_L02_003EAE10(char *self) {
    char *state = *(char **)(self + 0x68);
    float a[4];
    float b[12];
    float c[16];
    float d[4];
    float f[4];
    float limit;
    u16 *p;
    u8 *e;

    if (*(u8 *)(self + 0x21) == 0xFF)
        return 1;
    *(TI128 *)a = 0;
    a[2] = *(float *)(state + 0x3C);
    func_002833F0(b, a);
    func_00283698(c, b);
    func_00282CF0(d, (float *)(state + 0x30), (float *)(self + 0x10));
    func_00283098(d, d, c);
    limit = func_00282C48(d[1]);
    for (p = D_L02_001FC060[*(u8 *)(self + 0x21)];
         *(u8 *)(self + 0x21) != 0xFF && *(u8 *)(self + 0x21) <= D_L02_001B35B8 && p != 0 &&
         ((p != 0 && (s16)p[-1] >= 0) || p == D_L02_001FC060[*(u8 *)(self + 0x21)]);
         p++) {
        e = D_L02_001B359C_1[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e != (u8 *)self && *(short *)(e + 0xAA) == 0xAB0 && e[0x20] == 3) {
            func_00282CF0(f, (float *)(*(char **)(e + 0x68) + 0x30), (float *)(e + 0x10));
            func_00283098(f, f, c);
            if (limit < func_00282C48(f[1]))
                return 0;
        }
    }
    return 1;
}
