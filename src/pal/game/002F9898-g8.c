#include "include_asm.h"
#include "names.h"
extern void UpdateShopMenuInput(void);

/* Runs one frame of the shop menu input. */
void shop_run_menu_input_pal(void)
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
extern char g_shop_saved_state[];
extern Three_002F9198 g_shop_preview_data MACRO_ADDR;
extern float g_shop_zoom_a __attribute__((sda));
extern float g_shop_zoom_b __attribute__((sda));
extern int g_shop_color_r, g_shop_color_g, g_shop_color_b, g_shop_alt_color_r, g_shop_alt_color_g, g_shop_alt_color_b;
extern int g_shop_sub_menu_flag __attribute__((sda));
extern int g_shop_bolts_level_override __attribute__((sda));
extern unsigned short g_shop_bolts_level_alt __attribute__((sda)), g_shop_saved_bolts_level __attribute__((sda));
typedef struct { char pad0[0x20]; short level; char pad22[0x1E]; } Settings_002F9198;
extern Settings_002F9198 g_player_bolts MACRO_ADDR;
extern Five_002F9198 g_shop_close_table;
extern HeroMenu_002F9198 g_hero_moby_default;
extern int g_equipment_bits;
extern unsigned short g_hero_texture_bits;
extern void gfx_select_packet_buffer_setup(void);
extern int PlayMobySound(int, int, void *);
extern void tex_load_level_pack_pal(int);
extern char *GetLocalizedString(int);
extern void resident_msg_box_init_short(int, int);
extern void load_disc_table_entry_for_draw_pal(int);
extern void LoadDiscTableTexture_pal(int);
extern void SpawnEquipmentPieces(int);

/* Leaves the shop sub menu: restores the saved camera, zoom and colours, and puts back the equipment or
   armor that was being previewed. */
void shop_close_sub_menu_pal(void)
{
    Shop_002F9198 *s = &g_vendor_menu_state;
    Five_002F9198 table;
    gfx_select_packet_buffer_setup();
    PlayMobySound(5, 17, s->moby);
    if (s->restore) {
        qcopy(g_shop_saved_state, &s->saved);
        { Quad_002F9198 *dst = (Quad_002F9198 *)(g_shop_saved_state + 0x220);
          Three_002F9198 *src = &g_shop_preview_data;
          dst[0] = src->a; dst[1] = src->b; dst[2] = src->c; }
    }
    *(unsigned short *)(s->moby + 0x34) |= 0x100;
    g_vendor_menu_state.state = 2;
    g_shop_zoom_a = 1.0f;
    g_shop_zoom_b = 1.1f;
    g_shop_sub_menu_flag = 0;
    g_shop_alt_color_r = 0; g_shop_alt_color_g = 0; g_shop_alt_color_b = 0;
    g_shop_color_r = 96;
    g_shop_color_g = 96;
    g_shop_color_b = 85;
    if (g_vendor_menu_state.mode == 3) {
        if (g_shop_bolts_level_override) g_player_bolts.level = g_shop_bolts_level_alt; else g_player_bolts.level = g_shop_saved_bolts_level;
        tex_load_level_pack_pal(g_player_bolts.level);
        table = g_shop_close_table;
        if (g_shop_bolts_level_override) resident_msg_box_init_short(GetLocalizedString(table.words[g_player_bolts.level]), -1);
    }
    if (g_vendor_menu_state.mode == 2) {
        if (g_hero_moby_default.a != g_equipment_bits) {
            char *m;
            load_disc_table_entry_for_draw_pal(g_equipment_bits & 3);
            m = g_hero_moby_default.moby;
            if (m && *(int *)(m + 0x98)) *(int *)(m + 0x98) = *(int *)(*(char **)(m + 0x24) + 0x10);
        }
        if (g_hero_moby_default.b != (g_hero_texture_bits & 31)) LoadDiscTableTexture_pal(g_hero_texture_bits & 31);
        SpawnEquipmentPieces(0);
    }
}
