#include "include_asm.h"
#include "names.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern void list_menu_set_enabled(char *, int);
extern void list_menu_set_record_table(char *, char *);
extern char D_00261590[];

int func_US2_002D6508(void)
{
    if (D_001A8CFC[0] != 0) {
        list_menu_set_enabled(D_001A8CFC[0] + 0x3E760, 1);
        list_menu_set_record_table(D_001A8CFC[0] + 0x3E760, D_00261590);
    }
    return 0;
}

