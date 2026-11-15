#include "include_asm.h"
#include "names.h"

extern void menu_update_entry_states(int *);
extern int menu_list_active_entries(unsigned int, unsigned int, unsigned int, int);
extern int D_001C51D0;
typedef struct { char pad[0x34]; int f34; int f38; int f3C; } Base2D75E8;
extern Base2D75E8 D_0025A6E0;
extern int D_0025A620[];

int func_US2_002D8270(int *arg0)
{
    menu_update_entry_states(arg0);
    *(int *)((char *)arg0 + 0xA0) = menu_list_active_entries(0x70000000, 0, 0x70000100, 1);
    {
        char *base = (char *)arg0 + 0x30;
        int index = D_001C51D0;

        if (*(int *)(base + (index << 2)) != -1) {
            D_0025A6E0.f3C = -0x240;
            D_0025A6E0.f34 = *(int *)(0x70000000 + 4 * *(int *)(base + (index << 2)));
            *(int *)D_0025A620 = *(int *)(0x70000100 + 4 * *(int *)(base + (index << 2)));
        }
    }
    *(int *)((char *)arg0 + 0xA4) = 0;
    return 0;
}
