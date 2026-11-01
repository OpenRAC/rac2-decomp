#include "include_asm.h"


typedef int s32;
extern void func_L00_004287E8(void);
extern void func_L00_00428CE0(s32);

/* prepares the shared object then hands it to the shared starter */
void func_PAL_L23_00445458(s32 arg0) {
    func_L00_004287E8();
    func_L00_00428CE0(arg0);
}

