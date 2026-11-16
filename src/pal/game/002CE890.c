#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern void tab_menu_set_enabled(void *, int);
extern char *g_resident_data_base[] __attribute__((sda));
extern void *tab_menu_get_selected_value(void *);
extern char *g_resident_data_base[] __attribute__((sda));

int menu_init_list_object_pal(void *object) { char *root=g_resident_data_base[0]; if (root != 0) { tab_menu_set_enabled(root+0x3C210,1); *(void **)((char *)object+0x34)=tab_menu_get_selected_value(g_resident_data_base[0]+0x3C210); } return 0; }

