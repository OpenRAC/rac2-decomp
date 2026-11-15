#include "include_asm.h"

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

/* Clears the 0x600-byte table at ref_L00_002EA630_00 and resets its counter. */
void func_00280630(void) {
    func_00282A60(ref_L00_002EA630_00, 0, 0x600);
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
            total += func_00283CE0(*(s8 *)(table + c * 4 + 3)) * scale;
            if (i == length) break;
        } while (*p != 0);
    }
    return func_00283CF0(total);
}

extern s32 D_001A7BB8;
extern s32 D_001A7B90;
extern s32 func_00124418(void);
extern s32 func_001257D0(s32,s32,s32,s32);

/* Resets the display mode: calls the video setup and picks the output settings from the mode flags D_001A7B90 and D_001A7BB8. */
void func_00284000(void) {
    func_00124418();
    if (D_001A7B90 != 0) D_001A7BB8 = 0;
    if (D_001A7BB8 != 0) func_001257D0(0,0,0x50,1);
    else func_001257D0(0,1,D_001A7B90 != 0 ? 3 : 2,0);
}
