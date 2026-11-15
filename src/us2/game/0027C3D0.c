#include "include_asm.h"
#include "names.h"


extern void gfx_append_draw_list_buffer_tag(int);
extern int D_001B1594 __attribute__((sda));
extern void RenderFrame(void);

void func_US2_0027CAE0(void) {
    extern void gfx_append_draw_list_buffer_tag(int);
    extern void RenderFrame(void);
    extern int D_001B1594 __attribute__((sda));
    gfx_append_draw_list_buffer_tag(0);
    D_001B1594 = 0x7F;
    RenderFrame();
}

void menu_draw_pause_panels(int);
extern unsigned int menu_get_second_value(void);
extern void menu_draw_pause_panels(int);
extern void menu_draw_message_panel(void);

void func_US2_0027CB08(void)
{
    if (menu_get_second_value() == 1) {
        gfx_append_draw_list_buffer_tag(0);
        D_001B1594 = 0x100FF;
        RenderFrame();
    } else if (menu_get_second_value() == 0) {
        menu_draw_pause_panels(1);
    }
    menu_draw_message_panel();
}

void func_US2_0027CB80(void)
{
  menu_draw_pause_panels(0);
  return;
}

