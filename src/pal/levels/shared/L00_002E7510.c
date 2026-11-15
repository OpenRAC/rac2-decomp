#include "include_asm.h"
#include "names.h"

typedef long s64;
extern void menu_draw_pause_panels(s64);

/* calls the measured callee with zero */
void func_PAL_L00_002E7610(void) {
 menu_draw_pause_panels(0);
}

