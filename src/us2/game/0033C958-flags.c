#include "include_asm.h"
#include "names.h"
extern void Fe524d931_FUN_0033AE28(char *p);
extern void Fe524d931_FUN_0033B018(char *p, float x, float y);
extern int Fe524d931_FUN_002E5E58(int a, int b, int c);
extern void UpdateViewContext(void);
extern unsigned char g_display_mode_flag;

/* Handles input for the on/off option menu and flips the option on confirm. */
int onoff_menu_update_us2(char *object, int mask)
{
    float *v;

    Fe524d931_FUN_0033AE28(object + 8);
    v = *(float **)(object + 0x2DC);
    Fe524d931_FUN_0033B018(object + 8, v[0], v[1]);
    if ((mask & 0x40) != 0 && *(int *)(object + 0x2D8) == 0) {
        g_display_mode_flag = g_display_mode_flag == 0;
        Fe524d931_FUN_002E5E58(4, 0, 0);
        UpdateViewContext();
    }
    return (mask >> 6) & 1;
}
