#include "include_asm.h"
#include "names.h"

extern void object_set_first_float4(void *, float, float, float, float);
extern void hud_set_widget_value_pair(void *, int, int);
extern int *object_get_fourth_field(void *);
extern void hud_draw_colored_quad_widget(void *);
extern float D_L01_001AE420 __attribute__((sda));
extern float D_L01_001AE424;
extern float D_L01_001AE428 __attribute__((sda));
struct Obj {
    char pad[380];
    int h380;
    char pad2[56];
    int tbl440[3];
    int a452;
    int *p456;
    int count460;
    char pad3[88];
    float *fp536;
    char pad4[240];
    int mode764;
};

void func_PAL_00343AF0(struct Obj *o)
{
    int i;

    for (i = 0; i < o->count460; i++) {
        object_set_first_float4(&o->h380, o->fp536[0] + D_L01_001AE420,
                o->fp536[1] + D_L01_001AE424 + D_L01_001AE428 * (float)i, 0.0f, 0.0f);
        if (o->mode764 == 2) {
            int v = o->p456[i];

            if (v == 5)
                hud_set_widget_value_pair(&o->h380, 60062, 5);
            else
                hud_set_widget_value_pair(&o->h380, v, 0);
        } else if (o->mode764 == 0) {
            int w = o->p456[i];

            if (w == 6)
                hud_set_widget_value_pair(&o->h380, 60055, 0);
            else
                hud_set_widget_value_pair(&o->h380, o->a452, w);
        } else {
            hud_set_widget_value_pair(&o->h380, o->a452, o->p456[i]);
        }
        {
            int *r = object_get_fourth_field(&o->h380);
            int t = o->tbl440[o->mode764] ^ i;
            int alt = 0x70FFFEED;

            *r = t ? 0x60F0F0B0 : alt;
        }
        hud_draw_colored_quad_widget(&o->h380);
    }
}
