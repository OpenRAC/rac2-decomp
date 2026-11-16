#include "include_asm.h"
#include "names.h"

/* func_PAL_00280EC8, the PAL copy of func_L00_002EA600: the same C without the last call. */
extern void gfx_append_draw_list_header(void);
extern void gfx_init_view_context_pal(void);

void gfx_refresh_engine_and_view_pal(void) {
    gfx_append_draw_list_header();
    gfx_init_view_context_pal();
}

