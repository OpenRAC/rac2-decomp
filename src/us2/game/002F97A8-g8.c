#include "include_asm.h"
#include "names.h"
extern void UpdateShopMenuInput(void);

void func_US2_002FA608(void)
{
    UpdateShopMenuInput();
}

#include "common.h"
#include "common.h"
typedef unsigned int Quad_002F9198 __attribute__((mode(TI), aligned(16)));
typedef struct { Quad_002F9198 a, b, c; } Three_002F9198;
typedef struct { int words[5]; } Five_002F9198;
typedef struct { int state; char pad4[0x24]; char *moby; char pad2C[0x24]; int mode; char pad54[0xC]; int restore; char pad64[0x7C]; Quad_002F9198 saved; } Shop_002F9198;
typedef struct { char *moby; char pad4[0x14]; int a; char pad1C[0x14]; int b; } HeroMenu_002F9198;
extern Shop_002F9198 g_vendor_menu_state;
extern char D_001B5350[];
extern Three_002F9198 D_001B2250 MACRO_ADDR;
extern float D_001AD234 __attribute__((sda));
extern float D_001AD238 __attribute__((sda));
extern int D_001B2284, D_001B2288, D_001B228C, D_001B2290, D_001B2294, D_001B2298;
extern int D_001AD230 __attribute__((sda));
extern int D_001AD1B8 __attribute__((sda));
extern unsigned short D_001AD1BC __attribute__((sda)), D_001AD1C0 __attribute__((sda));
typedef struct { char pad0[0x20]; short level; char pad22[0x1E]; } Settings_002F9198;
extern Settings_002F9198 g_player_bolts MACRO_ADDR;
extern Five_002F9198 D_001AD308;
extern HeroMenu_002F9198 g_hero_moby_default;
extern int g_equipment_bits;
extern unsigned short D_001A7AF2;
extern void gfx_select_packet_buffer_setup(void);
extern int PlayMobySound(int, int, void *);
extern void func_US2_00292C70(int);
extern char *GetLocalizedString(int);
extern void func_US2_0029DAD0(int, int);
extern void load_disc_table_entry_for_draw(int);
extern void LoadDiscTableTexture(int);
extern void SpawnEquipmentPieces(int);

void func_US2_002FA028(void)
{
    Shop_002F9198 *s = &g_vendor_menu_state;
    Five_002F9198 table;
    gfx_select_packet_buffer_setup();
    PlayMobySound(5, 17, s->moby);
    if (s->restore) {
        qcopy(D_001B5350, &s->saved);
        { Quad_002F9198 *dst = (Quad_002F9198 *)(D_001B5350 + 0x220);
          Three_002F9198 *src = &D_001B2250;
          dst[0] = src->a; dst[1] = src->b; dst[2] = src->c; }
    }
    *(unsigned short *)(s->moby + 0x34) |= 0x100;
    g_vendor_menu_state.state = 2;
    D_001AD234 = 1.0f;
    D_001AD238 = 1.1f;
    D_001AD230 = 0;
    D_001B2290 = 0; D_001B2294 = 0; D_001B2298 = 0;
    D_001B2284 = 96;
    D_001B2288 = 96;
    D_001B228C = 85;
    if (g_vendor_menu_state.mode == 3) {
        if (D_001AD1B8) g_player_bolts.level = D_001AD1BC; else g_player_bolts.level = D_001AD1C0;
        func_US2_00292C70(g_player_bolts.level);
        table = D_001AD308;
        if (D_001AD1B8) func_US2_0029DAD0(GetLocalizedString(table.words[g_player_bolts.level]), -1);
    }
    if (g_vendor_menu_state.mode == 2) {
        if (g_hero_moby_default.a != g_equipment_bits) {
            char *m;
            load_disc_table_entry_for_draw(g_equipment_bits & 3);
            m = g_hero_moby_default.moby;
            if (m && *(int *)(m + 0x98)) *(int *)(m + 0x98) = *(int *)(*(char **)(m + 0x24) + 0x10);
        }
        if (g_hero_moby_default.b != (D_001A7AF2 & 31)) LoadDiscTableTexture(D_001A7AF2 & 31);
        SpawnEquipmentPieces(0);
    }
}
