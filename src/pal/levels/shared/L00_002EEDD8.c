#include "include_asm.h"

typedef struct {
    char pad_00[0x10];
    unsigned short f10;
    unsigned short f12;
    char pad_14[4];
    float f18;
    char pad_1c[4];
} Entry_r002ED808;
extern Entry_r002ED808 D_L00_001BECC0[];
extern float ref_L00_002ED808_00(float, float);
extern void ref_L00_002ED808_01(void *, int, int);

/* Steps the sixteen slots: eases the angle down by five degrees a tick and drops a slot
   when its countdown reaches zero. 0.087266475f is 0x3DB2B8C4 as retail materialises it. */
void func_PAL_L00_002EEDD8(void) {
    Entry_r002ED808 *e = D_L00_001BECC0;
    int i = 15;

    do {
        if ((short)e->f10 > 0) {
            e->f18 = ref_L00_002ED808_00(e->f18, 0.10471977f);
            if ((short)e->f10 >= 13)
                e->f12 += 5;
            else
                e->f12 -= 5;
            e->f10--;
            if ((short)e->f10 <= 0)
                ref_L00_002ED808_01(e, 0, 0x20);
        }
        i--;
        e++;
    } while (i >= 0);
}

