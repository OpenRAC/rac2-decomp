#include "include_asm.h"
#include "names.h"

/* func_PAL_00280EC8, the PAL copy of func_L00_002EA600: the same C without the last call. */
extern void gfx_append_draw_list_header(void);
extern void func_PAL_0027B810(void);

void func_PAL_00280EC8(void) {
    gfx_append_draw_list_header();
    func_PAL_0027B810();
}

