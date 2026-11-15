#include "include_asm.h"
#include "names.h"

extern void object_set_first_float4(void *, float, float, float, float);
extern int func_US2_00348E68(void *);
extern int *object_get_fourth_field(void *);
extern float D_001AE130 __attribute__((sda));
extern float D_001AE134 __attribute__((sda));
extern int D_00138344[];
extern int list_menu_get_selection(void *);
extern int *object_get_fourth_field(void *);
extern void gfx_draw_screen_element_stored(void *);
extern void func_US2_00348E70(void *);
extern int math_ping_pong_blend_values(int, int, int, int, int);

void func_US2_00342E48(char *self)
{
    int count = func_US2_00348E68(self + 0x10);
    int i;
    int *slot;

    if (D_00138344[0] & 0x5000)
        math_ping_pong_blend_values(0, 0, 1, 0, 1);
    for (i = 0; i < count; i++) {
        float step = (float)i;
        object_set_first_float4(self + 0xEC, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        object_set_first_float4(self + 0x138, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        slot = object_get_fourth_field(self + 0x138);
        *slot = list_menu_get_selection(self) == i ? math_ping_pong_blend_values(0x20FFFEED, 0x70FFFEED, 0x14, 0, 0) : 0x55F0C070;
        gfx_draw_screen_element_stored(self + 0xEC);
        gfx_draw_screen_element_stored(self + 0x138);
    }
    func_US2_00348E70(self + 0x10);
}
