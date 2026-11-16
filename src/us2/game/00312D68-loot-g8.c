#include "include_asm.h"

#include "common.h"
extern int math_random_int_below(int);
extern int g_nanotech_cooldown __attribute__((sda));
extern void SetDeathBits_us2(void *, int, int);
extern int PickAmmoDropItem(void *, int *);
extern char *SpawnWeaponAmmoPickup_us2(void *, int, int, int);

/* Selects the object's drop kind, emits the requested count, and resets its
 * halfword at +0xB4 before handing it to the state helper. */
void crate_drop_loot_us2(unsigned char *moby)
{
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    int item = *(short *)(vars + 0xC6) == 0;
    int count, i;

    if (*(short *)(moby + 0xAA) == MOBY_CLASS_NANOTECH_CRATE || *(short *)(moby + 0xAA) == MOBY_CLASS_PURPLE_NANOTECH_CRATE)
        item = 0;
    if (item) {
        if (g_nanotech_cooldown >= 21)
            i = 0;
        else if (g_nanotech_cooldown >= 11)
            i = 1;
        else
            i = 2;
        SetDeathBits_us2(moby, 256, math_random_int_below(2) + i);
    } else {
        if (*(short *)(moby + 0xAA) != MOBY_CLASS_NANOTECH_CRATE && *(short *)(moby + 0xAA) != MOBY_CLASS_PURPLE_NANOTECH_CRATE) {
            {
                int kind = vars[0xCB];
                if (kind == 4)
                    goto kind4;
                if (kind < 5)
                    goto none;
                if (kind == 8)
                    goto kind8;
                if (kind == 9)
                    goto kind9;
                goto none;
            kind8:
                item = 14;
                goto selected;
            kind4:
                item = 15;
                goto selected;
            kind9:
                item = 17;
                goto selected;
            none:
                item = -1;
            selected:
                ;
            }
            count = PickAmmoDropItem(moby, &item);
            if (count > 0) {
                i = count;
                do {
                    SpawnWeaponAmmoPickup_us2(moby + 0x10, item, -1, 0);
                    --i;
                } while (i);
            }
        }
        if (*(short *)(moby + 0xB4))
            *(short *)(moby + 0xB4) = 0;
        SetDeathBits_us2(moby, 256, 0);
    }
}
