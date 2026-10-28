/* func_00273978 - 504 bytes.  Worker attempt, 27 October 2026 (draft below).

   Goes at the end of src/game/0026EA00-qcopy.c (already has common.h include
   and the other externs; draft declares its own). Marker removed from
   0026EA00.c.
   Size matches (504); ONLY difference is register naming: retail state ptr =
   $s1, derived (state+0x20) = $s0; mine reversed (38 masked lines, all
   s0<->s1). Declaration order has no effect. Signature: (char *obj, int mode,
   int idx, void *src0, void *src1, unsigned char flag, float scale). Switch
   order in layout: case 2, case 0/3, case 1. */

extern int func_0029F840(void *, void *, int, int);
extern void func_0029F6A0(void *, int, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFDD8(void *, void *, void *, int);

void func_00273978(char *obj, int mode, int idx, void *src0, void *src1, unsigned char flag, float scale) {
    float buf[4] __attribute__((aligned(16)));
    float k;
    char *s1;
    char *s0;

    *(int *)(obj + 0x98) = 0;
    *(unsigned short *)(obj + 0x34) |= 0x100;
    s1 = *(char **)(obj + 0x68);
    qcopy(s1, src0);
    qcopy(s1 + 0x10, src1);
    *(float *)(s1 + 0x38) = 0.45f;
    *(float *)(s1 + 0x3C) = 0.033333333f;
    *(float *)(s1 + 0x40) = 0.5f;
    *(float *)(s1 + 0x44) = 0.01308997f;
    *(float *)(s1 + 0x48) = scale * (1.0f / 3600.0f);
    *(float *)(s1 + 0x4C) = 0.0017453294f;
    *(short *)(s1 + 0x34) = 180;
    *(unsigned char *)(s1 + 0x5E) = flag;
    *(unsigned char *)(s1 + 0x5D) = mode;
    *(unsigned char *)(s1 + 0x58) = 0;
    *(unsigned char *)(s1 + 0x5C) = 0;
    *(int *)(s1 + 0x30) = 0;
    switch (mode) {
    case 2:
        *(short *)(s1 + 0x36) = idx;
        *(unsigned short *)(obj + 0x7C) = (1 << idx) | 0x8000;
        s0 = s1 + 0x20;
        *(unsigned char *)(s1 + 0x58) = func_0029F840(obj, s0, *(int *)(s1 + 0x30), idx);
        func_00282CF0(s0, s0, obj + 0x10);
        func_002AFDD8(obj, s0, s0, 0);
        break;
    case 0:
    case 3:
        k = 1.0f / 1024.0f;
        s0 = s1 + 0x20;
        func_00282D30(s0, obj, k);
        *(float *)(s1 + 0x2C) = *(float *)(obj + 0xC) * k;
        func_00282CF0(s0, s0, obj + 0x10);
        func_002AFDD8(obj, s0, s0, 0);
        break;
    case 1:
        *(short *)(s1 + 0x36) = idx;
        *(unsigned short *)(obj + 0x7C) = (1 << idx) | 0x8000;
        func_0029F6A0(obj, idx, buf);
        s0 = s1 + 0x20;
        func_00282CF0(s0, buf, obj + 0x10);
        func_002AFDD8(obj, s0, s0, 0);
        break;
    }
}
