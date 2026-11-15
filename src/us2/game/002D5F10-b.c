#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int ref_L00_002D5570_00 __attribute__((sda));
extern int ref_L00_002D5570_01 __attribute__((sda));
extern void popup_init_texts_hidden(char *);
extern void popup_init_texts_shown(char *);

int func_US2_002D61D8(char *a0)
{
    if (D_001A8CFC != 0) {
        if (a0 == (char *)&ref_L00_002D5570_00)
            popup_init_texts_hidden(D_001A8CFC + 0x3CEA0);
        else if (a0 == (char *)&ref_L00_002D5570_01)
            popup_init_texts_shown(D_001A8CFC + 0x3CEA0);
    }
    return 0;
}
