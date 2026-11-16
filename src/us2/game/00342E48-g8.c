#include "include_asm.h"
#include "names.h"

extern void object_set_first_float4(void *, float, float, float, float);
extern int func_US2_00348E68(void *);
extern int *object_get_fourth_field(void *);
extern float g_small_list_row_spacing __attribute__((sda));
extern float g_small_list_text_x_offset __attribute__((sda));
extern int g_menu_input_flags[];
extern int list_menu_get_selection(void *);
extern int *object_get_fourth_field(void *);
extern void gfx_draw_screen_element_stored(void *);
extern void func_US2_00348E70(void *);
extern int math_ping_pong_blend_values(int, int, int, int, int);

void small_list_menu_draw_rows_us2(char *self)
{
    int count = func_US2_00348E68(self + 0x10);
    int i;
    int *slot;

    if (g_menu_input_flags[0] & 0x5000)
        math_ping_pong_blend_values(0, 0, 1, 0, 1);
    for (i = 0; i < count; i++) {
        float step = (float)i;
        object_set_first_float4(self + 0xEC, (*(float **)self)[0] + g_small_list_text_x_offset,
                      (*(float **)self)[1] + g_small_list_row_spacing * step, 0.0f, 0.0f);
        object_set_first_float4(self + 0x138, (*(float **)self)[0] + g_small_list_text_x_offset,
                      (*(float **)self)[1] + g_small_list_row_spacing * step, 0.0f, 0.0f);
        slot = object_get_fourth_field(self + 0x138);
        *slot = list_menu_get_selection(self) == i ? math_ping_pong_blend_values(0x20FFFEED, 0x70FFFEED, 0x14, 0, 0) : 0x55F0C070;
        gfx_draw_screen_element_stored(self + 0xEC);
        gfx_draw_screen_element_stored(self + 0x138);
    }
    func_US2_00348E70(self + 0x10);
}
