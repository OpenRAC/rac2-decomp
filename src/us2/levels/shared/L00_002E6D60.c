#include "include_asm.h"
#include "names.h"

typedef long s64;
extern void menu_draw_pause_panels(s64);

/* calls the measured callee with zero */
void func_US2_L00_002E6E60(void) {
 menu_draw_pause_panels(0);
}

