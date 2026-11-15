#include "common.h"

typedef int GornQuad __attribute__((mode(TI)));

static __inline__ void GornCopyQuad(void *dst, void *src) {
    *(GornQuad *)dst = *(GornQuad *)src;
}

extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern char *func_0029EFD0(int);
extern void func_00282D60(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AB6D8(void *, void *);

/* Spawns a class 0x1211 part at the record that the object's table links to from slot idx, unless
   the link byte is the empty value 0xFF. The byte is read twice: `value` going on to hold the class
   keeps cse from sharing the first read, and the second becomes a register copy after reload. */
void func_L15_004360D8(char *self, int idx) {
    char *p = *(char **)(self + 0x24);
    int count = *(short *)(p + 0x2E);

    if (count != 0) {
        int none = 0xFF;
        char *entry = p + (count << 4);
        int value = ((u8 *)entry)[idx + 1];

        if (value != none) {
            char *row;
            char *basis = self + 0xC0;
            char *pos = self + 0x10;
            char *obj;
            char *st;
            char *a;
            char *b;
            char m[0x40] __attribute__((aligned(16)));

            value = 0x1211;
            row = entry + (((u8 *)entry)[idx + 1] << 4);
            obj = CreateMoby(value);
            st = *(char **)(obj + 0x68);
            a = st + 0x420;
            b = st + 0x410;
            scale_vector(a, row, *(float *)(self + 0x2C) * 0.0009765599970705807f);
            matrix_mul_vec3(a, a, basis);
            FastVecAdd(a, a, pos);
            obj[0x30] = none;
            *(u16 *)(obj + 0x32) = 0x1FF;
            *(float *)(obj + 0x2C) = *(float *)(self + 0x2C);
            *(u16 *)(obj + 0x34) |= 0x100;
            FastVecSub(b, a, pos);
            vec_scale_to_length(b, b, 0.26666668f);
            GornCopyQuad(obj + 0xC0, basis);
            GornCopyQuad(obj + 0xD0, self + 0xD0);
            GornCopyQuad(obj + 0xE0, self + 0xE0);
            GornCopyQuad(m, basis);
            GornCopyQuad(m + 0x10, self + 0xD0);
            GornCopyQuad(m + 0x20, self + 0xE0);
            func_002AB6D8(m, st + 0x400);
            obj[0x20] = 7;
            *(u16 *)(obj + 0x7C) = (1 << idx) | 0x8000;
            GornCopyQuad(obj + 0x10, pos);
            *(int *)(obj + 0x98) = 0;
        }
    }
}
