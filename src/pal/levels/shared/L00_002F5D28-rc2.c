#include "include_asm.h"

#include "common.h"
struct Obj27 {
    s32 f0;
    s8 pad4[0x34];
    s16 f38;
    s16 pad3A;
    s32 f3C;
};
extern struct Obj27 ref_L00_002F46C8_00;
extern void ref_L00_002F46C8_01(void *arg0);

void func_PAL_L00_002F5D28(void) {
    struct Obj27 *p  = &ref_L00_002F46C8_00;

    if (p->f38 == 0) {
        p->f38 = 1;
        p->f3C = 0x32;
        ref_L00_002F46C8_01(p);
        if (ref_L00_002F46C8_00.f0 == 0) {
            ref_L00_002F46C8_00.f0 = 8;
        }
    }
}
