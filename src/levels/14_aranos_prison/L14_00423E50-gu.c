#include "names.h"
/* func_L14_00423E50: own unit for -frac2-gcse-unsplit-edges. With the critical edge left whole,
 * gcse PRE leaves the group-index reload in the bnel delay slot (table-entry path only), as
 * retail has it; with L14_003F4F98.c's plain flags the same C is 160 bytes.
 */
#include "common.h"

/* The entity bank: `sda` makes its load one macro instruction, which the assembler expands to
   retail's lui/lw pair on one register. */
extern unsigned char *g_moby_l14_pool __attribute__((sda));
extern unsigned short *g_group_entity_lists[];

/* 1 when an entity of the object's group (the 0x7FFF-masked id list D_L14_001FB060[group],
   last id flagged by bit 15) is active (state byte +0x20 not negative) and its class (+0xAA)
   is not 0xF91, else 0.  Only group 0xFF with no list returns 0 before the walk: retail
   walks the list of any other group without testing it for null. */
int actor_group_has_active_non_tourist(unsigned char *self)
{
    unsigned short *p;
    unsigned char *base;
    unsigned char *e;

    if (self[0x21] == 0xFF && g_group_entity_lists[self[0x21]] == 0)
        return 0;
    p = g_group_entity_lists[self[0x21]];
    base = g_moby_l14_pool;
    for (;;) {
        e = base + ((*p & 0x7FFF) << 8);
        if ((signed char)e[0x20] >= 0 && *(short *)(e + 0xAA) != MOBY_CLASS_SPACE_TOURIST_2)
            return 1;
        if ((short)*p < 0)
            break;
        p++;
    }
    return 0;
}
