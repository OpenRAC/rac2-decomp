#include "common.h"

extern int math_random_int_below(int);
extern int g_nanotech_cooldown __attribute__((sda));
extern void SetDeathBits(void *, int, int);
extern int PickAmmoDropItem(void *, int *);
extern char *SpawnWeaponAmmoPickup(void *, int, int, int);

/* Selects the object's drop kind, emits the requested count, and resets its
 * halfword at +0xB4 before handing it to the state helper. */
void crate_drop_loot(unsigned char *self)
{
    unsigned char *data = *(unsigned char **)(self + 0x68);
    int item = *(short *)(data + 0xC6) == 0;
    int n, i;

    if (*(short *)(self + 0xAA) == MOBY_CLASS_NANOTECH_CRATE || *(short *)(self + 0xAA) == MOBY_CLASS_PURPLE_NANOTECH_CRATE)
        item = 0;
    if (item) {
        if (g_nanotech_cooldown >= 21)
            i = 0;
        else if (g_nanotech_cooldown >= 11)
            i = 1;
        else
            i = 2;
        SetDeathBits(self, 256, math_random_int_below(2) + i);
    } else {
        if (*(short *)(self + 0xAA) != MOBY_CLASS_NANOTECH_CRATE && *(short *)(self + 0xAA) != MOBY_CLASS_PURPLE_NANOTECH_CRATE) {
            {
                int kind = data[0xCB];
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
            n = PickAmmoDropItem(self, &item);
            if (n > 0) {
                i = n;
                do {
                    SpawnWeaponAmmoPickup(self + 0x10, item, -1, 0);
                    --i;
                } while (i);
            }
        }
        if (*(short *)(self + 0xB4))
            *(short *)(self + 0xB4) = 0;
        SetDeathBits(self, 256, 0);
    }
}
