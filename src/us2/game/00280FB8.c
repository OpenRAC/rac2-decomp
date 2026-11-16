#include "include_asm.h"
#include "names.h"

extern void gfx_append_draw_list_header(void);
extern void gfx_init_view_context_us2(void);

/* func_US2_00280FB8, the v2.00 copy of func_L00_002EA600: the same C with one call fewer. */
void gfx_refresh_engine_and_view_us2(void) {
    gfx_append_draw_list_header();
    gfx_init_view_context_us2();
}
