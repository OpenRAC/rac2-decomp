#include "include_asm.h"
#include "names.h"

extern void func_0034CEA0(void *);
extern void func_0034E4B8(int);
extern void func_00338A60(int);
extern void func_0029CB58(void);
/* Updates the HUD parts and then runs a sync step. */
void func_0034E478(char *p)
{
    UpdateItemStatusHud(p + 0x7A0);
    UpdateHudSubobjectAt1D6C((int)p);
    UpdateTextPanelByMode((int)(p + 0x1FBC));
    func_0029CB58();
}
