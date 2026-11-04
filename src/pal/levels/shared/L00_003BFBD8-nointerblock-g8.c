/* func_PAL_L00_003BFBD8, the PAL copy of func_L00_003BBF48: the same C with the callee is PAL's
   func_PAL_L00_003BFEB8. */
#include "include_asm.h"
#include "common.h"

extern char D_L00_0023DDA0[] __attribute__((nosda));

extern void func_PAL_L00_003BFEB8(char *a0, char *a1);

extern int func_002A7820(int a, int b);

extern float func_002A7940(void);

extern void func_00281EB8(char *a, int b, unsigned int c, int d, float e, float f, float g);

/* Walks the level's table of records and draws the two sprites of the record the owner
   holds, when that record is still free. The record's own field is the owner, the one
   after it says whether it is free. Without interblock scheduling the two skips stay likely
   branches. Each sprite's colour is its own local: one shared variable dies twice, becomes a
   global pseudo, and the shifted alpha no longer ties to its saved register. */
void func_PAL_L00_003BFBD8(char *a0)
{
    unsigned int firstRGB = 0x103080;
    unsigned int secondRGB = 0xFFFFFF;
    char *base = D_L00_0023DDA0;
    char *p = base + 0x30;
    char *q = base;
    int i;
    int color;
    int color2;
    float f;

    for (i = 29; i >= 0; p += 0xA0, i--, q += 0xA0) {
        if (*(int *)(p + 0x5C) == (int)a0) {
            func_PAL_L00_003BFEB8(a0, q);
            if (*(int *)(p + 0x64) == 0) {
                color = func_002A7820(0x50, 0x60);
                color = (int)(color << 24) | firstRGB;
                f = func_002A7940();
                func_00281EB8(p, 0x31, color, 1, 0.5f, 0.15f, f);
                color2 = func_002A7820(0x50, 0x60);
                color2 = (int)(color2 << 24) | secondRGB;
                f = func_002A7940();
                func_00281EB8(p, 0x31, color2, 1, 0.3f, 0.151f, f);
            }
        }
    }
}
