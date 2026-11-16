#include "include_asm.h"
#include "names.h"

extern void UpdateItemStatusHud(void *);
extern void hud_update_subobject_primary(int);
extern void text_panel_update_mode(int);
extern void func_0029CB58(void);

/* Updates the HUD parts and then runs a sync step (PAL layout). */
void hud_update_subsystems_pal(char *hud)
{
    UpdateItemStatusHud(hud + 0x7A0);
    hud_update_subobject_primary((int)hud);
    text_panel_update_mode((int)(hud + 0x1FDC));
    func_0029CB58();
}

void text_panel_update_mode(int);

/* Updates a part of the HUD stored inside this object (PAL layout). */
void hud_update_subobject_primary_pal(int hud_ptr)
{
  text_panel_update_mode(hud_ptr + 0x1D8C);
}

void text_panel_draw_scaled(int);

/* Draws another part of the HUD stored inside this object (PAL layout). */
void hud_update_subobject_alt_pal(int hud_ptr)
{
  text_panel_draw_scaled(hud_ptr + 0x1D8C);
  return;
}

