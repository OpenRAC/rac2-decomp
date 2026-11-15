#include "include_asm.h"
#include "common.h"

extern int D_L09_001B35E0[] MACRO_ADDR;
extern int D_L09_001B36E0[] MACRO_ADDR;
extern int D_L09_001B3720[] MACRO_ADDR;
extern int D_L09_00255E90[];
extern void gfx_free_point_light(int);

/* Clears one beam link slot by index and stops its two sounds. */
void beam_slot_clear_by_index(int index)
{
    int handle;

    D_L09_001B35E0[index] = 0;
    D_L09_00255E90[index * 2] = 0;
    handle = D_L09_001B36E0[index];
    *(int *)((u8 *)D_L09_00255E90 + index * 8 + 4) = 0;
    if (handle != -1) {
        gfx_free_point_light(handle);
        D_L09_001B36E0[index] = -1;
    }
    if (D_L09_001B3720[index] != -1) {
        gfx_free_point_light(D_L09_001B3720[index]);
        D_L09_001B3720[index] = -1;
    }
}
