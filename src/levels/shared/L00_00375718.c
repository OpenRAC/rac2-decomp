#include "common.h"
typedef union { u8 b[0x800]; s32 i[0x200]; u8 *ptr[0x200]; } HudModel;
extern char D_L00_0022F7C0[];
extern float D_L00_001B25E0;
extern int D_001A7B90 MACRO_ADDR;
extern int D_L00_001AD690 __attribute__((sda));
extern int D_L00_001AD698[6] __attribute__((sda));
extern void func_002FC620(int, int, int, int);
extern unsigned int func_001157AC(const char *);
extern int func_002A77E0(int);
extern int func_00288FB8(int);
extern void func_002F88D8(void *);
extern void func_002F97A0(float, float, unsigned long long, unsigned char *, int, float);

/* Draws the scrolling help text, advancing its scroll and starting a random voice line at the end. */
void func_L00_00375718(void) {
    int baseline;
    float magnification;
    int choice;
    int y;
    if (((HudModel *)D_L00_0022F7C0)->i[0x50 / 4] == 2) {
        baseline = 20;
        magnification = 1.0f;
        func_002FC620(75, 355, (int)(D_L00_001B25E0 * 19.0f + 0.5f), (int)(D_L00_001B25E0 * 36.0f + 0.5f));
    } else {
        baseline = 60;
        magnification = 1.5f;
        func_002FC620(80, 432, (int)(D_L00_001B25E0 * 56.0f + 0.5f), (int)(D_L00_001B25E0 * 100.0f + 0.5f));
    }
    if ((int)func_001157AC((char *)((HudModel *)D_L00_0022F7C0)->ptr[0x3C / 4]) - ((HudModel *)D_L00_0022F7C0)->i[0x64 / 4] / 20 > 0)
        ((HudModel *)D_L00_0022F7C0)->i[0x64 / 4] = ((HudModel *)D_L00_0022F7C0)->i[0x64 / 4] + 2;
    else if (((HudModel *)D_L00_0022F7C0)->i[0x744 / 4] == 0 && (unsigned int)(((HudModel *)D_L00_0022F7C0)->i[0x50 / 4] - 1) > 1) {
        choice = func_002A77E0(12);
        if (choice >= 6) func_002F88D8((void *)GetLocalizedString(D_L00_001AD690));
        else func_002F88D8((void *)GetLocalizedString(D_L00_001AD698[choice]));
    }
    y = (int)((float)baseline * D_L00_001B25E0 + 0.5f);
    draw_large_text_edge_faded((float)-((HudModel *)D_L00_0022F7C0)->i[0x64 / 4], (float)(D_001A7B90 ? y - 4 : y), 0xF0C070ULL, ((HudModel *)D_L00_0022F7C0)->ptr[0x3C / 4], -1, magnification);
}
