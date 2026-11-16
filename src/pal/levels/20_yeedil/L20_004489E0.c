#include "include_asm.h"
#include "names.h"



extern unsigned int g_group_l20_member_table __attribute__((sda));
extern int func_L20_00449AC8(char *);
extern void func_0039BDF0(char *, char *, int, int);

/* Sets up the linked child moby at the target and returns it, or returns nothing if it is busy. (PAL) */
char *moby_activate_linked_child_pal(char *moby, char *target) {
    char *state = *(char **)(moby + 0x68);
    unsigned int child_addr = g_group_l20_member_table + (*(int *)(state + 0x238) << 8);

    if (func_L20_00449AC8((char *)child_addr) != 0) {
        moby_start_path_movement((char *)child_addr, moby, target);
        func_0039BDF0((char *)child_addr, (char *)(child_addr + 0x10), 0x12C, 0);
        return (char *)child_addr;
    }
    return 0;
}

