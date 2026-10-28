/* func_L00_00378C18 - 452 bytes.  Worker attempt, 27 October 2026 (draft below).

   Same size as retail (452) now, 40 masked diff lines of scheduling/register
   choice. Sibling of func_L00_00378E90 (same TextLayout code).
   Diffs: retail beqz delay slot holds a1=0 (memset arg) before a0=&layout;
   retail loads D_001A79F8 via lui just before the slt (mine early); retail
   keeps 314 (0x13A) in a2 right after the memset call and converts that
   register for field[1] (mtc1 a2) -> needs int top=314 style local assigned
   after the call (tried; regs differ: t5/s1).
   Callees guessed as func_L00_002F4668 / func_L00_002EA200 (boot-vs-level
   names unverified at other levels). */

/* insert before func_L00_00378E90 in src/levels/shared/L00_00378E90.c (-O2 -G0), remove INCLUDE_ASM from L00_00358D98.c. Level 00 only compiled. */
extern int D_001A79F8;
extern float D_L00_001B25E0;
extern unsigned char *func_L00_002F4668(int);
extern void func_L00_002EA200(TextLayout *, unsigned long long, unsigned char *, int);

void func_L00_00378C18(void) {
    int top;
    TextLayout copy;
    TextLayout layout;
    char *model;
    int index;
    float scale;
    model = D_L00_0022F7C0;
    if (*(int *)(model + 0x84) == 0) return;
    func_00115484(&layout, 0, 24);
    top = 314;
    scale = D_L00_001B25E0;
    layout.field[2] = top;
    layout.field[3] = 486;
    layout.field[4] = 400;
    layout.field[6] = 164;
    layout.field[8] = 16;
    layout.field[9] = 3;
    layout.field[0] = (short)(scale * 120.0f + 0.5f);
    layout.field[1] = (short)(scale * (float)top + 0.5f);
    layout.field[5] = (short)(scale * 217.0f + 0.5f);
    layout.field[7] = (short)(scale * 186.0f + 0.5f);
    index = *(int *)(model + 0x80);
    copy = layout;
    if (D_001A79F8 >= *(int *)(model + 0x144 + index * 12)) {
        copy.field[9] = 1;
        copy.field[5] = (short)((float)(copy.field[0] + 40) * scale + 0.5f);
        func_L00_002EA200(&copy, 0x80F0F0F0ULL, func_L00_002F4668(0x1129), -1);
    } else {
        func_L00_002EA200(&copy, 0x80F0F0F0ULL, func_L00_002F4668(0x1128), -1);
    }
}
