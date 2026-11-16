#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_F32_FD368ADD8
#define RAC2_T_F32_FD368ADD8
typedef float f32_Fd368add8;
#endif

extern f32_Fd368add8 g_tab_menu_first_x __attribute__((sda));

extern f32_Fd368add8 g_tab_menu_third_x __attribute__((sda));

extern f32_Fd368add8 g_tab_menu_second_x __attribute__((sda));

extern f32_Fd368add8 g_tab_menu_fourth_x __attribute__((sda));

extern f32_Fd368add8 g_tab_menu_fifth_x __attribute__((sda));

extern f32_Fd368add8 g_tab_menu_first_y;

extern f32_Fd368add8 g_tab_menu_third_y;

extern f32_Fd368add8 g_tab_menu_second_y;

extern f32_Fd368add8 g_tab_menu_fourth_y;

extern f32_Fd368add8 g_tab_menu_fifth_y;

extern void func_00335E38_1(void *a0, f32_Fd368add8 a1, f32_Fd368add8 a2, f32_Fd368add8 a3, f32_Fd368add8 a4);

extern void *func_00335E20_1(void *a0);

extern int math_ping_pong_blend_values(int a0, int a1, int a2, int a3, int a4);

extern void tab_menu_update_list(void *a0, int a1);

extern void tab_menu_position_cursor(void *a0);

/* This call target is not the unrelated function at Aranos 0x004370F8. */
extern void ref_L00_003418C0_00(void *a0);

/* Updates the tabbed menu each frame: places its parts, sets the cursor color and returns the selected entry. */
int tab_menu_update(char *self, int arg1)
{
    f32_Fd368add8 *v;

    v = *(f32_Fd368add8 **)(self + 536);
    func_00335E38_1(self, g_tab_menu_first_x + v[0], g_tab_menu_first_y + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 536);
    func_00335E38_1(self + 152, g_tab_menu_third_x + v[0], g_tab_menu_third_y + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 536);
    func_00335E38_1(self + 76, g_tab_menu_second_x + v[0], g_tab_menu_second_y + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 536);
    func_00335E38_1(self + 228, g_tab_menu_fourth_x + v[0], g_tab_menu_fourth_y + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 536);
    func_00335E38_1(self + 464, g_tab_menu_fifth_x + v[0], g_tab_menu_fifth_y + v[1], 0.0f, 0.0f);

    *(int *)func_00335E20_1(self + 304) = math_ping_pong_blend_values(0x60442D00, 0x70FFFEED, 20, 0, 0);
    tab_menu_update_list(self, arg1);
    tab_menu_position_cursor(self);
    ref_L00_003418C0_00(self);
    return *(int *)(self + (*(int *)(self + 764) << 2) + 440);
}

extern void gfx_draw_screen_element_stored(void *);

/* Draws one part of the tabbed menu. */
void tab_menu_draw_part(char *object) {
    gfx_draw_screen_element_stored(object + 0x130);
}
