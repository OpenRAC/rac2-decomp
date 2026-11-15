#include "include_asm.h"
#include "names.h"
extern void RenderFrame(void);
extern unsigned int D_L00_001B18D4;

void func_US2_L00_002E6D60(void) {
 D_L00_001B18D4 = 0x100FF;
 RenderFrame();
}

extern void gfx_append_draw_list_buffer_tag(int);
extern void gfx_set_clear_color_packet(int, int, int, int);

void func_US2_L00_002E6E18(void) {
 gfx_append_draw_list_buffer_tag(0);
 gfx_set_clear_color_packet(0, 0, 0, 0x80);
 D_L00_001B18D4 = 0xF0;
 RenderFrame();
}
