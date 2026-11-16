#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int ref_L00_002D5570_00 __attribute__((sda));
extern int ref_L00_002D5570_01 __attribute__((sda));
extern void popup_init_texts_hidden(char *);
extern void popup_init_texts_shown(char *);

int menu_start_key_action_us2(char *a0)
{
    if (g_resident_data_base != 0) {
        if (a0 == (char *)&ref_L00_002D5570_00)
            popup_init_texts_hidden(g_resident_data_base + 0x3CEA0);
        else if (a0 == (char *)&ref_L00_002D5570_01)
            popup_init_texts_shown(g_resident_data_base + 0x3CEA0);
    }
    return 0;
}
