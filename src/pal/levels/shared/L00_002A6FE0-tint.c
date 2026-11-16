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
extern unsigned char g_item_slot_to_record[];
extern char g_weapon_l00_table[];
extern void get_moby_color(void *owner, int *a1, int *a2, int *a3);
extern void set_moby_color(void *owner, int a1, int a2, int a3);
extern void hero_copy_color_to_slot_objects(void);
extern void hero_empty_hook(int first, void *second);

/* Flashes the hero a dark and light blue tint for the first half second of certain states. Then, if an item is equipped and ready, updates its effect (PAL). */
void UpdateHeroBlinkAndItemTint_pal(void)
{
    int r, g, b;
    int active = 0;
    if (D_00189E20_2.mode == 125 || D_00189E20_2.mode == 127)
        active = D_00189E20_2.frame < 25;
    if (active) {
        get_moby_color(D_00189E20_2.owner, &r, &g, &b);

        if (D_00189E20_2.frame % 4 < 3) {
            r = 0;
            g = 0;
            b = 0;
        } else {
            r = 0x90;
            g = 0x90;
            b = 0xF0;
        }

        set_moby_color(D_00189E20_2.owner, r, g, b);
        hero_copy_color_to_slot_objects();
    }

    if (D_00189E20_2.index >= 0) {
        unsigned char index = g_item_slot_to_record[D_00189E20_2.index];
        char *record = g_weapon_l00_table + index * 0xE0;

        if (*(u8 *)(record + 4) != 0) {
            int state = D_00189E20_2.state;

            if (state != 0)
                hero_empty_hook(state, D_00189E20_2.owner);
        }
    }
}
