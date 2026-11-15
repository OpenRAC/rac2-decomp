#include "include_asm.h"
#include "names.h"

extern void gfx_append_draw_list_header(void);
extern void func_US2_0027B988(void);

/* func_US2_00280FB8, the v2.00 copy of func_L00_002EA600: the same C with one call fewer. */
void func_US2_00280FB8(void) {
    gfx_append_draw_list_header();
    func_US2_0027B988();
}
