#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base[] __attribute__((sda));
extern float ref_L00_002D33C0_00[];
extern void ref_L00_002D33C0_01(unsigned char *, float *);
extern char *g_resident_data_base[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));

/* Sets up the model preview helper object for the menu if the menu is open. (USA v2.00) */
int menu_preview_helper_init_us2(void)
{
    if (g_resident_data_base[0] != 0)
        ref_L00_002D33C0_01((unsigned char *)(g_resident_data_base[0] + 0x3F3F0), ref_L00_002D33C0_00);
    return 0;
}
