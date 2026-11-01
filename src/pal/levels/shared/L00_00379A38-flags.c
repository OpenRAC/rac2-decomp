#include "include_asm.h"

extern int D_L00_0022F7C0[];
extern float D_L00_001B25E0 __attribute__((sda));
extern int D_001A79F8 __attribute__((sda));
extern int func_00288FB8(int id);
extern void func_0027F5B8(int sprite, int x, unsigned long color, int id, int y);
extern void func_0027FA10(int sprite, int x, unsigned long color, int id, int y);
typedef struct {
    int first;
    int second;
    int third;
} L00_003781B0_Cell;
#define L00_003781B0_X ((int)(D_L00_001B25E0 * 312.0f + 0.5f))

void func_PAL_L00_0037ADD8(void)
{
    if (D_L00_0022F7C0[0x84 / 4] != 0) {
        L00_003781B0_Cell *cell = (L00_003781B0_Cell *)((char *)D_L00_0022F7C0 + 0x144);
        if (D_001A79F8 >= cell[D_L00_0022F7C0[0x80 / 4]].first) {
            func_0027F5B8(0x28, L00_003781B0_X, 0x80F0F0F0UL, func_00288FB8(0x113B), -1);
            func_0027FA10(0x118, L00_003781B0_X, 0x80F0F0F0UL, func_00288FB8(0x1138), -1);
        } else {
            func_0027FA10(0x118, L00_003781B0_X, 0x80F0F0F0UL, func_00288FB8(0x1124), -1);
        }
    } else {
        L00_003781B0_Cell *cell = (L00_003781B0_Cell *)((char *)D_L00_0022F7C0 + 0x144);
        if (cell[D_L00_0022F7C0[0x80 / 4]].first > 0)
            func_0027F5B8(0x28, L00_003781B0_X, 0x80F0F0F0UL, func_00288FB8(0x1125), -1);
        func_0027FA10(0x118, L00_003781B0_X, 0x80F0F0F0UL, func_00288FB8(0xB60), -1);
    }
}
