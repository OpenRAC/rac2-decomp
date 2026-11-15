#include "include_asm.h"
#include "names.h"

extern void UpdateItemStatusHud(void *);
extern void hud_update_subobject_primary(int);
extern void text_panel_update_mode(int);
extern void func_0029CB58(void);
/* Updates the HUD parts and then runs a sync step. */
void hud_update_subsystems(char *p)
{
    UpdateItemStatusHud(p + 0x7A0);
    hud_update_subobject_primary((int)p);
    text_panel_update_mode((int)(p + 0x1FBC));
    func_0029CB58();
}
