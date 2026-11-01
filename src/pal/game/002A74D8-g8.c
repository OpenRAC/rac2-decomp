#include "include_asm.h"

extern short D_00264630[64][12];
typedef struct {
    unsigned char pad0[0x0A];
    unsigned char enabled;  
    unsigned char pad0B[0x27];
    unsigned char limit;  
    unsigned char count;  
} Global001A7A00;
extern Global001A7A00 D_001A7A00 __attribute__((section(".sdata")));
extern int D_001A9E70;
extern unsigned short D_00188510[][2];
extern void func_0029B698(int);

/* Finds the row of D_00264630 whose first four ids hold the object's id at +0xAA,
   then counts it in column `type` of D_00188510 (capped at 9999). */
void func_PAL_002A74D8(char *p, int type)
{
    int found = -1, i, j;
    int id = *(short *)(p + 0xAA);

    for (i = 0; i < 64; i++) {
        for (j = 0; j < 4; j++) {
            if (id == D_00264630[i][j]) {
                found = i;
                break;
            }
        }
        if (found != -1) goto found_it;
    }
    if (found == -1) return;
found_it:
    if (D_001A7A00.enabled && D_001A9E70 == -1 && D_001A7A00.limit < 20) {
        D_001A7A00.count++;
        if (D_001A7A00.count * 2 >= D_001A7A00.limit) {
            func_0029B698(150);
            D_001A7A00.count = 0;
            D_001A7A00.limit++;
        }
    }
    if (type == 0) {
        if (D_00188510[found][0] < 9999) D_00188510[found][0]++;
    } else if (type == 1) {
        if (D_00188510[found][1] < 9999) D_00188510[found][1]++;
    }
}
