#include "include_asm.h"
#include "names.h"

extern void UpdateItemStatusHud(void *);
extern void hud_update_subobject_primary(int);
extern void text_panel_update_mode(int);
extern void func_0029CB58(void);

/* Updates the item status HUD, the primary HUD sub object and the text panel, then a fixed HUD hook. (USA v2.00) */
void hud_update_subsystems_us2(char *hud)
{
    UpdateItemStatusHud(hud + 0x7A0);
    hud_update_subobject_primary((int)hud);
    text_panel_update_mode((int)(hud + 0x1FDC));
    func_0029CB58();
}

void text_panel_update_mode(int);

/* Updates the text panel of the HUD's primary sub object. (USA v2.00) */
void hud_update_subobject_primary_us2(int hud)
{
  text_panel_update_mode(hud + 0x1D8C);
}

void text_panel_draw_scaled(int);

/* Draws the text panel of the HUD's alternate sub object, scaled. (USA v2.00) */
void hud_update_subobject_alt_us2(int hud)
{
  text_panel_draw_scaled(hud + 0x1D8C);
  return;
}

