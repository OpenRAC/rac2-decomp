#include "include_asm.h"

extern char D_L00_0022F7C0[];
extern int D_001A79F8;
extern float D_L00_001B25E0[] __attribute__((sda));
extern int D_001AD778 __attribute__((sda));
extern int D_001AD780 __attribute__((sda));
extern int D_001AD77C;
extern unsigned char *func_00288FB8(int);
extern void func_0027FB40(int, int, unsigned long long, unsigned char *, int);

void func_PAL_L00_0037AFB0(void)
{
    char *model = D_L00_0022F7C0;

    if (*(int *)(model + 0x84) != 0) {
        int index = *(int *)(model + 0x80);

        if (D_001A79F8 >= *(int *)(D_L00_0022F7C0 + index * 16 + 0x148)) {
            func_0027FB40(D_001AD778, (int)((float)D_001AD77C * D_L00_001B25E0[0] + 0.5f),
                              0x80F0F0F0ULL, func_00288FB8(0x113B), -1);
            func_0027FB40(D_001AD778 + D_001AD780, (int)((float)D_001AD77C * D_L00_001B25E0[0] + 0.5f),
                              0x80F0F0F0ULL, func_00288FB8(0x1138), -1);
        } else {
            func_0027FB40(D_001AD778 + D_001AD780, (int)((float)D_001AD77C * D_L00_001B25E0[0] + 0.5f),
                              0x80F0F0F0ULL, func_00288FB8(0x1124), -1);
        }
    } else {
        func_0027FB40(D_001AD778, (int)((float)D_001AD77C * D_L00_001B25E0[0] + 0.5f),
                          0x80F0F0F0ULL, func_00288FB8(0x1125), -1);
        func_0027FB40(D_001AD778 + D_001AD780, (int)((float)D_001AD77C * D_L00_001B25E0[0] + 0.5f),
                          0x80F0F0F0ULL, func_00288FB8(0xB60), -1);
    }
}
