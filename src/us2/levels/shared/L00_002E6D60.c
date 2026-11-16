#include "include_asm.h"
#include "names.h"

typedef long s64;
extern void menu_draw_pause_panels(s64);

/* calls the measured callee with zero */
void gfx_call_engine_routine_zero_us2(void) {
 menu_draw_pause_panels(0);
}

