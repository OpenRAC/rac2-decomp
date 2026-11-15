#include "names.h"
/* func_PAL_003469E8, the PAL copy of func_00344938: the same C with the PAL field offsets and string ids, where
 * the language byte D_PAL_001A7C3C picks string 0xAD3 for language 2, func_00336A78 is PAL's own func_PAL_00338770,
 * and cases 1 to 3 lose the 16.0f and pass an int local holding 0 instead of 0.0f. */
#include "include_asm.h"

extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, char *);
extern void sprintf(char *, const char *, ...);
extern void hud_set_widget_field_a(void *, int);
extern void func_PAL_00338770(void *);
extern int save_count_filled_slots(void);
extern int save_get_baseline_count(void);
extern int save_count_items_above_baseline(void);
extern float *object_get_first_field(void *);
extern void object_set_first_float4(void *, float, float, float, float);
extern void object_set_flag_value(void *, int);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern char D_001ADBC8[], D_001ADF98[], D_001AE2F8[];
extern unsigned char D_PAL_001A7C3C;
extern short D_001A7A1A;
extern int D_001A7A1C;
extern int D_001A79FC;
extern int D_001AE2F0 __attribute__((sda));
extern int D_001AE2E0 __attribute__((sda));
extern int D_001AE2E4;
extern int D_001AE2E8 __attribute__((sda));
extern int D_001AE2EC;

void func_PAL_003469E8(char *self)
{
    int sel = 0;
    float zero;
    int off;

    if (*(int *)(self + 0x4B8) == 3)
        sel = *(int *)(self + 0x4AC) + *(int *)(self + 0x4B0) * 2;
    self[0x480] = 0;
    self[0x490] = 0;
    if (D_PAL_001A7C3C == 2)
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xAD3));
    else
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xAD2));
    off = 0;
    switch (sel) {
    case 0:
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0xAD2));
        zero = 0.0f;
        sprintf(self + 0x470, D_001ADBC8, GetLocalizedString(0xBCC));
        hud_set_widget_field_a(self + 0x368, 0);
        func_PAL_00338770(self + 0x368);
        sprintf(self + 0x470, D_001ADF98, save_count_filled_slots());
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)D_001AE2F0,
                      object_get_first_field(self + 0x368)[1], zero, zero);
        hud_set_widget_field_a(self + 0x368, 2);
        func_PAL_00338770(self + 0x368);
        sprintf(self + 0x480, D_001ADBC8, GetLocalizedString(0xBCD));
        hud_set_widget_field_a(self + 0x3C0, 0);
        func_PAL_00338770(self + 0x3C0);
        sprintf(self + 0x480, D_001ADF98, save_get_baseline_count());
        object_set_first_float4(self + 0x3C0, object_get_first_field(self + 0x3C0)[0] + (float)D_001AE2F0,
                      object_get_first_field(self + 0x3C0)[1], zero, zero);
        hud_set_widget_field_a(self + 0x3C0, 2);
        func_PAL_00338770(self + 0x3C0);
        sprintf(self + 0x490, D_001ADBC8, GetLocalizedString(0xBCE));
        hud_set_widget_field_a(self + 0x418, 0);
        func_PAL_00338770(self + 0x418);
        sprintf(self + 0x490, D_001ADF98, save_count_items_above_baseline());
        object_set_first_float4(self + 0x418, object_get_first_field(self + 0x418)[0] + (float)D_001AE2F0,
                      object_get_first_field(self + 0x418)[1], zero, zero);
        hud_set_widget_field_a(self + 0x418, 2);
        func_PAL_00338770(self + 0x418);
        break;
    case 1:
        sprintf(self + 0x470, D_001ADBC8, GetLocalizedString(0xBCC));
        hud_set_widget_field_a(self + 0x368, 0);
        func_PAL_00338770(self + 0x368);
        sprintf(self + 0x470, D_001ADF98, D_001A7A1A);
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)D_001AE2F0,
                      object_get_first_field(self + 0x368)[1], off, off);
        hud_set_widget_field_a(self + 0x368, 2);
        func_PAL_00338770(self + 0x368);
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xAD1));
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0xAD1));
        break;
    case 2:
        sprintf(self + 0x470, D_001ADBC8, GetLocalizedString(0xBCC));
        hud_set_widget_field_a(self + 0x368, 0);
        func_PAL_00338770(self + 0x368);
        sprintf(self + 0x470, D_001ADF98, D_001A7A1C);
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)D_001AE2F0,
                      object_get_first_field(self + 0x368)[1], off, off);
        hud_set_widget_field_a(self + 0x368, 2);
        func_PAL_00338770(self + 0x368);
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xAD0));
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0xAD0));
        break;
    case 3:
        sprintf(self + 0x470, D_001ADBC8, GetLocalizedString(0xBCC));
        hud_set_widget_field_a(self + 0x368, 0);
        func_PAL_00338770(self + 0x368);
        sprintf(self + 0x470, D_001ADF98, D_001A79FC);
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)D_001AE2F0,
                      object_get_first_field(self + 0x368)[1], off, off);
        hud_set_widget_field_a(self + 0x368, 2);
        func_PAL_00338770(self + 0x368);
        sprintf(self + 0x470, D_001AE2F8, GetLocalizedString(0xBCC), D_001A79FC);
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xACF));
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0xACF));
        break;
    }
    func_PAL_00338770(self + 0x310);
    if (*(int *)(self + 0x4B4) == sel) {
        object_set_flag_value(self + 0x220, 1);
        object_set_first_float4(self + 0x220, (*(float **)(self + 0x4A0))[0] + -117.0f,
                      (*(float **)(self + 0x4A0))[1] + 3.0f, 0.0f, 0.0f);
        func_PAL_00338770(self + 0x220);
    }
    if (sel == 0) {
        int x = (*(float **)(self + 0x4A0))[0];
        int y = (*(float **)(self + 0x4A0))[1];
        AppendScreenRectPacket(x + D_001AE2E0, y + D_001AE2E4, x + D_001AE2E8, y + D_001AE2EC,
                      0x55F0C070, 0);
    }
}
