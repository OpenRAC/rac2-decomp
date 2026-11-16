#include "include_asm.h"
#include "names.h"



extern unsigned int g_group_l20_member_table __attribute__((sda));
extern int func_L20_00449AC8(char *);
extern void func_0039BDF0(char *, char *, int, int);

char *moby_activate_linked_child_pal(char *arg0, char *arg1) {
    char *state = *(char **)(arg0 + 0x68);
    unsigned int p = g_group_l20_member_table + (*(int *)(state + 0x238) << 8);

    if (func_L20_00449AC8((char *)p) != 0) {
        moby_start_path_movement((char *)p, arg0, arg1);
        func_0039BDF0((char *)p, (char *)(p + 0x10), 0x12C, 0);
        return (char *)p;
    }
    return 0;
}

