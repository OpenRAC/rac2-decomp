#include "include_asm.h"
#include "names.h"

typedef struct {
    char pad0[0x2290];
    char *moby;
    int state;
    char pad2298[0x229C - 0x2298];
    int mode;
    char pad22A0[0x22B7 - 0x22A0];
    unsigned char b22B7;
    char pad22B8[0x22BC - 0x22B8];
    unsigned char b22BC;
    unsigned char pad22BD;
    unsigned char b22BE;
} Hero_2B2120;
extern Hero_2B2120 g_hero_state;
extern int hero_is_in_special_kind_or_mode(void);
extern void SpawnHeroItemMobies_pal(void);
extern void update_hero_item_mobys_pal(char *);
extern void level_fade_glow_colors_pal(void);
extern void hero_update_item_glow_pal(void);
extern void UpdateHeroSlotCallbacks_pal(void);

void hero_update_items_and_flags_pal(void)
{
    int m = g_hero_state.mode;

    if ((unsigned int)(m - 0x15) < 2 || m == 0x1F || hero_is_in_special_kind_or_mode() != 0) {
        g_hero_state.b22B7 = 1;
        g_hero_state.b22BC = 1;
    }
    if (hero_is_in_special_kind_or_mode() != 0 || g_hero_state.state == 0x31 || g_hero_state.mode == 3 ||
        g_hero_state.state == 0x12 || g_hero_state.state == 0x82)
        g_hero_state.b22BE = 1;
    else
        g_hero_state.b22BE = 0;
    SpawnHeroItemMobies_pal();
    update_hero_item_mobys_pal(g_hero_state.moby);
    level_fade_glow_colors_pal();
    hero_update_item_glow_pal();
    UpdateHeroSlotCallbacks_pal();
}
