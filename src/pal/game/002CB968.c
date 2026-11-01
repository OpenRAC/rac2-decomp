#include "include_asm.h"


#include "common.h"
extern char D_001F2840[];
extern short D_001A63AC;
extern int D_001C51D0;
extern int D_00239BA0[];
extern unsigned char D_00139568[];
extern int func_002B4B70(int, int);
extern int func_002B49E0(int, int, int, int, void *);
extern void func_PAL_002B8898(int);
extern void func_00294420(int);
typedef struct {
    char pad00[0x1C];
    int mode;
    char pad20[0x04];
    volatile int count;
    char pad28[0x08];
    int field30;
    char pad34[0x0C];
    int field40;
    char pad44[0xB0];
    int fieldF4;
} GameState_1F2840;

void func_PAL_002CBC18(void)
{
    int n = ((GameState_1F2840 *)D_001F2840)->count;

    if (n != 0)
        ((GameState_1F2840 *)D_001F2840)->count = n - 1;
    if (((GameState_1F2840 *)D_001F2840)->count != 0)
        return;
    if (D_001A63AC != 0)
        return;
    if (((GameState_1F2840 *)D_001F2840)->mode == 2) {
        func_002B4B70(0, D_001C51D0);
    } else if (((GameState_1F2840 *)D_001F2840)->mode == 3) {
        func_002B49E0(1, 1, 0, ((GameState_1F2840 *)D_001F2840)->fieldF4, 0);
    } else if (((GameState_1F2840 *)D_001F2840)->mode == 4) {
        func_002B49E0(1, 1, 0, ((GameState_1F2840 *)D_001F2840)->fieldF4, 0);
    } else if (((GameState_1F2840 *)D_001F2840)->mode == 6) {
        func_002B49E0(1, 1, 0, ((GameState_1F2840 *)D_001F2840)->fieldF4, 0);
    } else if (((GameState_1F2840 *)D_001F2840)->mode == 5) {
        func_002B49E0(2, 1, ((GameState_1F2840 *)D_001F2840)->fieldF4, 0, 0);
    } else {
        func_002B4B70(0, 0);
    }
    if (((GameState_1F2840 *)D_001F2840)->field40 != 0 &&
        ((GameState_1F2840 *)D_001F2840)->field30 != ((GameState_1F2840 *)D_001F2840)->field40) {
        int id;
        int *rec;
        func_PAL_002B8898(1);
        id = ((GameState_1F2840 *)D_001F2840)->field40;
        rec = (int *)((char *)D_00239BA0 + D_00139568[id] * 0xE0);
        func_00294420(rec[5]);
        func_PAL_002B8898(1);
    }
    func_PAL_002B8898(1);
}


INCLUDE_ASM("asm/pal/game", func_PAL_002CBD80);
