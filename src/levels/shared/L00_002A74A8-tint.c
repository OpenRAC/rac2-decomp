/* Source-shape reference: OpenRAC/rac1-decomp (GPL-3.0),
 * src/overlays/shared/hero_idle_and_animation.c. */
/* Blinks the hero tint, then updates an active equipped-item effect. */
#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef struct {
    char pad0[0x1B8];
    int frame;
    char pad1bc[0x1220 - 0x1BC];
    int state;
    char pad1224[0x1248 - 0x1224];
    int index;
    char pad124c[0x2290 - 0x124C];
    void *owner;
    int mode;
} FlashResidentFields;
extern FlashResidentFields D_00189E20_2;
extern unsigned char D_00139568[];
extern char D_L00_00262570[];
extern void func_002A04B8(void *owner, int *a1, int *a2, int *a3);
extern void func_002A0488(void *owner, int a1, int a2, int a3);
extern void func_L00_002A7070(void);
extern void func_L00_002A70F0(int first, void *second);

/* Flashes the hero a dark and light blue tint for the first half second of certain states. Then, if an item is equipped and ready, updates its effect. */
void func_L00_002A74A8(void)
{
    int red, green, blue;
    int active = 0;
    if (D_00189E20_2.mode == 125 || D_00189E20_2.mode == 127)
        active = D_00189E20_2.frame < 30;
    if (active) {
        get_moby_color(D_00189E20_2.owner, &red, &green, &blue);

        if (D_00189E20_2.frame % 4 < 3) {
            red = 0;
            green = 0;
            blue = 0;
        } else {
            red = 0x90;
            green = 0x90;
            blue = 0xF0;
        }

        set_moby_color(D_00189E20_2.owner, red, green, blue);
        CopyHeroColorToSlotObjects();
    }

    if (D_00189E20_2.index >= 0) {
        unsigned char index = gItemSlotToRecord[D_00189E20_2.index];
        char *record = gWeaponTable_L00 + index * 0xE0;

        if (*(u8 *)(record + 4) != 0) {
            int state = D_00189E20_2.state;

            if (state != 0)
                EmptyHeroHook(state, D_00189E20_2.owner);
        }
    }
}
