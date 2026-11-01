#include "include_asm.h"

typedef int s32;
typedef float f32;
extern s32 func_00277F48(f32, s32, s32, s32, s32);
extern void func_00282F20(void *, void *, float);
extern void func_PAL_0032F0B8(int, int, int);
extern int D_0018C0B0;
extern unsigned char D_00139568[];
extern unsigned char D_L00_00262570[];
extern unsigned int D_L00_001C3280[];
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    float pos[4];
    unsigned int obj;
    unsigned int magic;
    unsigned char kind;
    unsigned char kind2;
    unsigned short id;
    float len;
    unsigned int count;
} Trail_3A9798;
typedef struct {
    unsigned char pad0[4];
    unsigned char flag;
} Entry262570;

void func_PAL_L00_003ACF38(char *a0, char *a1, char *a2)
{
    Trail_3A9798 s;
    int count;
    int i;
    unsigned int *p;

    s.magic = 0x810000;
    s.len = *(float *)(a1 + 0x18);
    s.count = 1;
    s.obj = (unsigned int)a0;
    *(TI128 *)s.pos = *(TI128 *)a1;
    func_00282F20(&s, &s, 1.0f);
    s.pos[3] = 5627.9248046875f;
    s.kind = 3;
    s.kind2 = 2;
    s.id = *(unsigned short *)(a0 + 0xAA);
    count = func_00277F48(6.0f, (int)a2, 1, D_0018C0B0, (int)&s);
    if (((Entry262570 *)(D_L00_00262570 + D_00139568[0x19] * 224))->flag != 0) {
        p = D_L00_001C3280;
        for (i = 0; i < count; i++)
            func_PAL_0032F0B8(D_L00_001C3280[i], 0x46, *(int *)(a0 + 0xB8));
    } else {
        p = D_L00_001C3280;
        for (i = 0; i < count; i++)
            func_PAL_0032F0B8(D_L00_001C3280[i], 0x19, *(int *)(a0 + 0xB8));
    }
}
