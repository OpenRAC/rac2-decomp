#include "include_asm.h"
#include "names.h"


typedef int s32;
extern void cam_swingshot_update(void);
extern void cam_aim_at_hero(s32);

/* prepares the shared object then hands it to the shared starter */
void func_PAL_L23_00445458(s32 arg0) {
    cam_swingshot_update();
    cam_aim_at_hero(arg0);
}

