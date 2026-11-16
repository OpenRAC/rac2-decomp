#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int ref_L00_002D5570_00 __attribute__((sda));
extern int ref_L00_002D5570_01 __attribute__((sda));
extern void popup_init_texts_hidden(char *);
extern void popup_init_texts_shown(char *);

/* Starts one of two menu actions, depending on which of two known keys is passed in. (USA v2.00) */
int menu_start_key_action_us2(char *key)
{
    if (g_resident_data_base != 0) {
        if (key == (char *)&ref_L00_002D5570_00)
            popup_init_texts_hidden(g_resident_data_base + 0x3CEA0);
        else if (key == (char *)&ref_L00_002D5570_01)
            popup_init_texts_shown(g_resident_data_base + 0x3CEA0);
    }
    return 0;
}
