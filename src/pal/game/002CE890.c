#include "include_asm.h"
#include "names.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern void tab_menu_set_enabled(void *, int);
extern char *D_001A8CFC[] __attribute__((sda));
extern void *tab_menu_get_selected_value(void *);
extern char *D_001A8CFC[] __attribute__((sda));

int func_PAL_002CE890(void *object) { char *root=D_001A8CFC[0]; if (root != 0) { tab_menu_set_enabled(root+0x3C210,1); *(void **)((char *)object+0x34)=tab_menu_get_selected_value(D_001A8CFC[0]+0x3C210); } return 0; }

