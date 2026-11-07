#include "include_asm.h"

/* func_PAL_003426B8, the PAL copy of func_00340638: the same C, where the fields at
   0xA18 and 0x870 move to 0xA78 and 0x880. */
typedef struct { unsigned int lo; unsigned int hi; } Word2_340498;
extern const Word2_340498 D_001AE090;
extern const Word2_340498 D_001AE098;
extern const Word2_340498 D_001AE0A0;
extern const Word2_340498 D_001AE0A8;
extern const Word2_340498 D_001AE0B0;
extern char D_00259CE0[];
extern char *D_001A8CFC __attribute__((sda));
extern void func_00336390(void *, void *, int);
extern void func_00337210(int *);

static __inline__ void initDescriptor_340498(int *f) { f[20] = 0; f[21] = 1; }

void func_PAL_003426B8(char *o)
{
    Word2_340498 q0 = D_001AE098;
    Word2_340498 q1 = D_001AE0A0;
    Word2_340498 q2 = D_001AE098;
    Word2_340498 q3 = D_001AE0A8;
    Word2_340498 q4 = D_001AE090;
    Word2_340498 q5 = D_001AE0B0;
    int f[23];
    char *child;
    initDescriptor_340498(f);
    f[19] = *(int *)(o + 0x820);
    f[21] = *(int *)(o + 0x81C) == 1;
    f[16] = (int)(o + 0xA78);
    f[3] = *(int *)(o + 0x814);
    f[4] = *(int *)(o + 0x818);
    child = o + 0x17C;
    f[9] = (int)&q4;
    f[14] = 1;
    f[13] = 0;
    f[1] = 3;
    f[2] = 2;
    f[0] = (int)D_00259CE0;
    f[17] = (int)(o + 0x880);
    func_00336390(child, D_001A8CFC + 0x8710, 0x5D);
    f[10] = (int)child;
    f[12] = (int)(o + 0x214);
    f[15] = (int)(o + 0x7D0);
    f[8] = (int)&q3;
    f[7] = (int)&q2;
    f[11] = 0;
    f[18] = *(int *)(o + 0x80C);
    f[6] = (int)&q1;
    f[5] = (int)&q0;
    f[20] = (int)&q5;
    f[22] = 0;
    func_00337210(f);
}
