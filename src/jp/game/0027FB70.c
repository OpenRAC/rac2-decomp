#include "common.h"

INCLUDE_ASM("asm/jp/game", func_JP_0027FB70);

void func_JP_00280280(void) {
    extern void gfx_append_draw_list_buffer_tag(int);
    extern void func_JP_0027FB70(void);
    extern int D_001B1594 __attribute__((sda));
    gfx_append_draw_list_buffer_tag(0);
    D_001B1594 = 0x7F;
    func_JP_0027FB70();
}

extern unsigned int menu_get_second_value(void);
extern void gfx_append_draw_list_buffer_tag(int);
extern int D_001B1594 __attribute__((sda));
extern void func_JP_0027FB70(void);
extern void func_JP_002D0198(int);
extern void func_JP_00289E68(void);

void func_JP_002802A8(void)
{
    if (menu_get_second_value() == 1) {
        gfx_append_draw_list_buffer_tag(0);
        D_001B1594 = 0x100FF;
        func_JP_0027FB70();
    } else if (!menu_get_second_value()) {
        func_JP_002D0198(1);
    }
    func_JP_00289E68();
}

void func_JP_00280320(void)
{
    func_JP_002D0198(0);
}
