#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern int g_player_stats[] __attribute__((sda));
extern unsigned char g_language_settings[] __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern unsigned char g_special_items_flag;
extern unsigned char g_game_flag_table[];
extern int D_001AA438 __asm__("D_001AA438__gp") __attribute__((section(".sdata")));
extern unsigned char D_001ABA30 __asm__("D_001ABA30__gp") __attribute__((section(".sdata")));
extern unsigned char g_special_item_collected_b[] __attribute__((sda));
extern unsigned char g_special_item_collected_c[] __attribute__((sda));
extern unsigned char g_special_item_collected_d[] __attribute__((sda));
extern unsigned char g_special_item_collected_e[] __attribute__((sda));
extern unsigned char g_special_item_collected_f[] __attribute__((sda));
extern unsigned char g_special_item_collected_g[] __attribute__((sda));
extern unsigned char g_special_item_collected_h[] __attribute__((sda));

/* func_US2_002D2538, the v2.00 copy of func_002D1590: the same C, where the last test also needs D_001A79F0 > 0. */
int menu_record_collected_special_items_us2(void)
{
    if (g_resident_data_base[0] != 0 && ((unsigned char *)g_player_stats)[0xA] != 0) {
        if (g_language_settings[0x3A] != 0 && g_special_items_flag != 0)
            g_special_item_collected_flags = 1;
        if (g_language_settings[0x3C] != 0 && (g_game_flag_table[0x4D] != 0 || g_game_flag_table[0x52] != 0))
            g_special_item_collected_b[0] = 1;
        if (g_language_settings[0x43] != 0 && (g_game_flag_table[0x57] != 0 || g_game_flag_table[0x5C] != 0))
            g_special_item_collected_c[0] = 1;
        if (g_language_settings[0x43] != 0 && g_game_flag_table[0x3D] != 0)
            g_special_item_collected_d[0] = 1;
        if (g_language_settings[0x52] != 0)
            g_special_item_collected_e[0] = 1;
        if (g_language_settings[0x4E] != 0)
            g_special_item_collected_f[0] = 1;
        if (g_language_settings[0x4F] != 0)
            g_special_item_collected_g[0] = 1;
        if (g_special_items_unlock_flag != 0 && g_current_map_index > 0)
            g_special_item_collected_h[0] = 1;
    }
    return 0;
}
