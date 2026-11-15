#include "include_asm.h"
#include "names.h"

extern void func_0027BD70(void);

extern unsigned int D_L00_001B18D4;

/* Sets a draw setting to a fixed value and renders the frame. */
void func_L00_002E6348(void) {
 D_L00_001B18D4 = 0x100FF;
 RenderFrame();
}

extern void func_00284F40(int);

extern void func_0027DDC0(int, int, int, int);

/* Clears the screen to black, sets a draw setting and renders the frame. */
void func_L00_002E6400(void) {
 AppendDrawListBufferTag(0);
 SetClearColorPacket(0, 0, 0, 0x80);
 D_L00_001B18D4 = 0xF0;
 RenderFrame();
}

extern int D_L00_001B19A8;

/* Turns a draw flag on. */
void func_L00_002E9098(void) {
    D_L00_001B19A8 = 1;
}

/* Turns a draw flag off. */
void func_L00_002E90A8(void) {
    D_L00_001B19A8 = 0;
}

/* ---- 0x002E73E0: a counter bump around three measured callees. ---- */

extern int D_L00_001B18D8;
extern int D_001A72DC;
extern int D_001A7344;

extern void ref_L00_002E73E0_00(int);
extern int ref_L00_002E73E0_01(void);
extern void ref_L00_002E73E0_02(void *, int, int);

extern int func_001261F0(int);

/* Starts a draw pass, bumps a frame counter and draws the given item. */
void func_L00_002E73E0(void *item) {
    ref_L00_002E73E0_00(1);
    GetGsCurrentField(0);
    D_L00_001B18D8 = D_L00_001B18D8 + 1;
    ref_L00_002E73E0_01();
    ref_L00_002E73E0_02(item, D_001A72DC, gScreenHeight << 11);
}
