#include "include_asm.h"
#include "names.h"
extern void func_002F0538(int);
extern void func_002E7D48(int, int, int, int);
extern unsigned int g_screen_overlay_color;
extern short g_screen_overlay_active;
extern void func_002E5C40(void);

void gfx_reset_screen_overlay_us2(void)
{
    func_002F0538(0);
    func_002E7D48(0, 0, 0, 0x80);
    if (g_screen_overlay_active != 0)
        g_screen_overlay_color = 0x100FF;
    else
        g_screen_overlay_color = 0x70;
    func_002E5C40();
}
