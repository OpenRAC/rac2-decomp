#include "include_asm.h"
#include "names.h"

/* The first table column uses a GP address; the other columns use absolute
 * addresses. Keep the compiler at -G8 and assemble with -G64 for this table. */
typedef struct { unsigned char pad[0x9C]; unsigned char bits; } Flags;
extern Flags g_game_flag_table;
extern int g_current_map_index __attribute__((section(".sdata")));
extern int g_map_event_flag __attribute__((section(".sdata")));
extern int g_grid_clear_rect_a[] __attribute__((section(".sdata")));
extern int g_grid_clear_rect_b[] __attribute__((section(".sdata")));
extern int g_grid_clear_rect_min_x[16] __attribute__((sda));
extern int g_grid_clear_rect_min_y[] __attribute__((section(".sdata")));
extern int g_grid_clear_rect_max_x[] __attribute__((section(".sdata")));
extern int g_grid_clear_rect_max_y[] __attribute__((section(".sdata")));
typedef struct { int x[4]; } IndexMap;
extern IndexMap g_index_map;
extern void level_clear_grid_bits_in_rect(int, int, int, int);
extern int moby_get_current_variant_index(void);

/* Dispatch a level-specific event once for its corresponding state bit. */
int level_dispatch_event_once(void)
{
    IndexMap map = g_index_map;
    if (g_current_map_index == 2 && g_map_event_flag && ((g_game_flag_table.bits ^ 1) & 1)) {
        level_clear_grid_bits_in_rect(g_grid_clear_rect_a[0], g_grid_clear_rect_a[1],
                            g_grid_clear_rect_a[2], g_grid_clear_rect_a[3]);
        g_game_flag_table.bits |= 1;
    } else if (g_current_map_index == 11 && g_map_event_flag && !(g_game_flag_table.bits & 2)) {
        level_clear_grid_bits_in_rect(g_grid_clear_rect_b[0], g_grid_clear_rect_b[1],
                            g_grid_clear_rect_b[2], g_grid_clear_rect_b[3]);
        g_game_flag_table.bits |= 2;
    } else if (g_current_map_index == 7 && moby_get_current_variant_index() >= 0) {
        int i = moby_get_current_variant_index();
        int bit = map.x[i];
        if ((unsigned)bit >= 8 || (((g_game_flag_table.bits >> bit) ^ 1) & 1)) {
            if ((unsigned)bit < 8) g_game_flag_table.bits |= 1 << bit;
            level_clear_grid_bits_in_rect(g_grid_clear_rect_min_x[i * 4], g_grid_clear_rect_min_y[i * 4],
                                g_grid_clear_rect_max_x[i * 4], g_grid_clear_rect_max_y[i * 4]);
        }
    }
    return 0;
}
