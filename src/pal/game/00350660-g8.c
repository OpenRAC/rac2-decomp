#include "include_asm.h"
#include "names.h"
extern char D_L00_001BD2C0[];
extern int D_L00_001A8FB4;
extern char *D_L00_001A904C;
extern int D_L00_001AEA7C __attribute__((sda));
extern int D_L00_001AEA80 __attribute__((sda));
extern void UpdateViewContext(void);
extern unsigned int menu_get_label_color_alpha(void *);
extern void radial_menu_layout_items(void *, int, int, int);
extern void menu_noop_hook(void *);
extern void DrawBoltCounterPanel(void *);
extern void text_panel_draw_scaled(void *);
extern void func_0029CB80(void);

void func_PAL_003506E0(char *object)
{
    float saved;
    char *camera;
    char *state = D_L00_001BD2C0;
    saved = *(float *)(state + 0xB0);
    *(float *)(state + 0xB0) = 0.62f;
    UpdateViewContext();
    if (D_L00_001A8FB4 == 0)
        radial_menu_layout_items(object, D_L00_001AEA7C, D_L00_001AEA80, menu_get_label_color_alpha(object + 0x7A0) >> 24);
    menu_noop_hook(object);
    DrawBoltCounterPanel(object + 0x7A0);
    camera = D_L00_001A904C + 0x38000;
    *(int *)(camera + 0x7A8C) = 0;
    *(int *)(camera + 0x7A90) = 0;
    text_panel_draw_scaled(object + 0x1FDC);
    func_0029CB80();
    *(float *)(state + 0xB0) = saved;
    UpdateViewContext();
}
