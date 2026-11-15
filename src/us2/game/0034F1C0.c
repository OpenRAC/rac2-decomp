#include "include_asm.h"
#include "names.h"

extern void UpdateItemStatusHud(void *);
extern void hud_update_subobject_primary(int);
extern void text_panel_update_mode(int);
extern void func_0029CB58(void);

void func_US2_0034F1C0(char *p)
{
    UpdateItemStatusHud(p + 0x7A0);
    hud_update_subobject_primary((int)p);
    text_panel_update_mode((int)(p + 0x1FDC));
    func_0029CB58();
}

void text_panel_update_mode(int);

void func_US2_0034F200(int param_1)
{
  text_panel_update_mode(param_1 + 0x1D8C);
}

void text_panel_draw_scaled(int);

void func_US2_0034F220(int param_1)
{
  text_panel_draw_scaled(param_1 + 0x1D8C);
  return;
}

