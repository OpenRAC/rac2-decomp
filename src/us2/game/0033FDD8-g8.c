#include "include_asm.h"
#include "names.h"

extern char D_001ADBC8[];
extern char D_US2_001ADF70[]; /* "%d/%d": sits where v1.01 has "%d" (D_001ADF98), but plain "%d" is elsewhere in v2.00 */
extern int D_001ADF90 __attribute__((sda));
extern char g_map_overlay_state[];
extern const char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern void hud_set_widget_field_a(char *, int);
extern void func_US2_003378A0(char *);
extern int func_US2_002B1C90(int);
extern int func_US2_002B1D18(int);
extern float *object_get_first_field(char *);
extern void object_set_first_float4(char *, float, float, float, float);

/* func_US2_0033FDD8, reduced from func_0033ED88's first row: while the entry at +0x230 is 1 to 20, formats message
 * 0x2C51 and two values derived from it into the buffer at +0x6C0, places the text object at +0x470 and draws it,
 * then draws the object at +0x578. */
void func_US2_0033FDD8(char *self)
{
    float zero = 0.0f;
    char *base = g_map_overlay_state;

    if ((unsigned int)(*(int *)(base + 0x230) - 1) < 20) {
        sprintf(self + 0x6C0, D_001ADBC8, GetLocalizedString(0x2C51));
        hud_set_widget_field_a(self + 0x470, 0);
        func_US2_003378A0(self + 0x470);
        sprintf(self + 0x6C0, D_US2_001ADF70, func_US2_002B1C90(*(int *)(base + 0x230)),
                      func_US2_002B1D18(*(int *)(base + 0x230)));
        object_set_first_float4(self + 0x470, object_get_first_field(self + 0x470)[0] + (float)D_001ADF90,
                      object_get_first_field(self + 0x470)[1], zero, zero);
        hud_set_widget_field_a(self + 0x470, 2);
        func_US2_003378A0(self + 0x470);
        func_US2_003378A0(self + 0x578);
    }
}
