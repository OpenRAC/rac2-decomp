#include "include_asm.h"

typedef struct { short field[12]; } TextLayout;
extern char D_L00_0022F7C0[];
extern float D_L00_001B25E0 __attribute__((sda));
extern int D_001A79FC __attribute__((sda));
extern void func_002FC620(int, int, int, int);
extern void *func_00115484(void *, int, unsigned int);
extern unsigned char *func_00288FB8(int);
extern void func_00280200(TextLayout *, unsigned long long, unsigned char *, int);

void func_US2_L00_0037A2C8(void) {
    TextLayout copy;
    TextLayout layout;
    char *model;
    int index;
    float scale;
    func_002FC620(192, 488, 59, 195);
    model = D_L00_0022F7C0;
    if (*(int *)(model + 0x84) == 0) return;
    index = *(int *)(model + 0x80);
    func_00115484(&layout, 0, 24);
    scale = D_L00_001B25E0;
    layout.field[2] = 32;
    layout.field[3] = 386;
    layout.field[4] = 209;
    layout.field[0] = (short)(scale * 63.0f + 0.5f);
    layout.field[1] = (short)(scale * 231.0f + 0.5f);
    layout.field[5] = (short)(scale * 204.0f + 0.5f);
    layout.field[6] = 346;
    layout.field[7] = (short)(scale * 160.0f + 0.5f);
    layout.field[8] = 16;
    layout.field[9] = 3;
    copy = layout;
    if (D_001A79FC >= *(int *)(model + 0x144 + index * 28)) {
        copy.field[9] = 1;
        copy.field[5] = (short)((float)(copy.field[0] + 40) * scale + 0.5f);
        func_00280200(&copy, 0x80F0F0F0ULL, func_00288FB8(0x31B5), -1);
    } else {
        copy.field[9] = 1;
        copy.field[5] = (short)((float)(copy.field[0] + 60) * scale + 0.5f);
        func_00280200(&copy, 0x80F0F0F0ULL, func_00288FB8(0x31B4), -1);
    }
}
