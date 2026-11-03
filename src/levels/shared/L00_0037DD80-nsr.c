typedef unsigned char u8;

typedef int s32;

typedef unsigned int u32;

typedef struct {
    u32 field00,field04;
    s32 field08;
    u8 gap0c[4];
} OrbitalPairTableView16;

extern u8 D_L00_00231340[];

extern int func_00282948(void *p);

/* Clears the key of every sixteen-byte record whose key equals a0 when its moby is gone (flag
   0x1000 clear, null, or in state 0xFE/0xFD) or its timer runs out. Own unit: retail counts the
   loop up (-fno-strength-reduce), keeps the separate record copy `e` that gcse's copy propagation
   would fold (-fno-gcse), and leaves the counter increment at the join (-fno-sched-interblock). */
void func_L00_0037E000(u32 a0)
{
    OrbitalPairTableView16 *entry = (OrbitalPairTableView16 *)D_L00_00231340;
    int i;

    for (i = 0; i < 32; i++, entry++) {
        if (entry->field04 == a0) {
            u8 *p = (u8 *)entry->field00;
            OrbitalPairTableView16 *e = entry;

            if ((*(unsigned short *)(p + 0x34) & 0x1000) == 0) {
                entry->field04 = 0;
            } else if (p == 0 || p[0x20] == 0xFE || p[0x20] == 0xFD) {
                e->field04 = 0;
            } else if (func_00282948(&entry->field08) != 0) {
                entry->field04 = 0;
            }
        }
    }
}
