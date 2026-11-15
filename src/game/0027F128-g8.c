#include "include_asm.h"
#include "names.h"

/* -G8 siblings for src/game/0027F128.c: these need the small-data addressing
   mode (absolute lui forms and gp-relative loads). */

typedef float f32;
typedef int s32;
typedef signed char s8;
typedef unsigned char u8;

extern void func_00282A60(void *, int, int);
extern char ref_L00_002EA630_00[];
extern int ref_L00_002EA630_01;
extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);

/* Clears a data buffer and resets a related counter. */
void func_00280630(void) {
    ClearMemory(ref_L00_002EA630_00, 0, 0x600);
    ref_L00_002EA630_01 = 0;
}

/* Sum the scaled per-character widths. */
int func_0027F1D8(u8 *text, int length, u8 *table, float scale) {
    int i = 0;
    f32 total = 0.0f;
    u8 *p;
    u8 c;

    if (length != 0 && text[0] != 0) {
        p = text;
        do {
            c = *p;
            i++;
            p++;
            total += IntToFloat(*(s8 *)(table + c * 4 + 3)) * scale;
            if (i == length) break;
        } while (*p != 0);
    }
    return FloatToInt(total);
}

extern s32 D_001A7BB8;
extern s32 D_001A7B90;
extern s32 func_00124418(void);
extern s32 func_001257D0(s32,s32,s32,s32);

/* Updates the display mode when the screen type changes. */
void func_00284000(void) {
    func_00124418();
    if (gIsPalVideo != 0) gWidescreenFlag = 0;
    if (gWidescreenFlag != 0) ResetGsGraph(0,0,0x50,1);
    else ResetGsGraph(0,1,gIsPalVideo != 0 ? 3 : 2,0);
}
