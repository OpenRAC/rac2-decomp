#include "names.h"
typedef unsigned char u8;

typedef int s32;

typedef unsigned int u32;

typedef struct {
    u32 field00,field04;
    s32 field08;
    u8 gap0c[4];
} OrbitalPairTableView16;

extern u8 g_owner_key_table[];

extern int math_fast_float_d(void *p);

/* Clears the key of every sixteen-byte record whose key equals a0 when its moby is gone (flag
   0x1000 clear, null, or in state 0xFE/0xFD) or its timer runs out. Own unit: retail counts the
   loop up (-fno-strength-reduce), keeps the separate record copy `e` that gcse's copy propagation
   would fold (-fno-gcse), and leaves the counter increment at the join (-fno-sched-interblock). */
void ReleaseDeadOrExpiredSlots(u32 key)
{
    OrbitalPairTableView16 *entry = (OrbitalPairTableView16 *)g_owner_key_table;
    int i;

    for (i = 0; i < 32; i++, entry++) {
        if (entry->field04 == key) {
            u8 *moby = (u8 *)entry->field00;
            OrbitalPairTableView16 *entryCopy = entry;

            if ((*(unsigned short *)(moby + 0x34) & 0x1000) == 0) {
                entry->field04 = 0;
            } else if (moby == 0 || moby[0x20] == 0xFE || moby[0x20] == 0xFD) {
                entryCopy->field04 = 0;
            } else if (math_fast_float_d(&entry->field08) != 0) {
                entry->field04 = 0;
            }
        }
    }
}
