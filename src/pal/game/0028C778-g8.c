#include "include_asm.h"
#include "names.h"

extern int D_001A8DD8[2] __attribute__((sda));
extern int g_radial_menu_page_index __attribute__((sda));
extern int g_radial_slot_count[] __attribute__((sda));

void func_PAL_0028D6F0(void *a0)
{
    g_radial_slot_count[0] = 8;
    g_radial_slot_count[1] = (int)D_001A8DD8;
    *(short *)((char *)a0 + 0x48) = 0;
    *(short *)((char *)a0 + 0x4A) = 0;
    *(int *)((char *)a0 + 0x58) = 0xD2;
    *(int *)((char *)a0 + 0x5C) = 0xC8;
    *(int *)((char *)a0 + 0x74) = -2;
    *(int *)((char *)a0 + 0x78) = 0x19;
    g_radial_menu_page_index = 0;
}
