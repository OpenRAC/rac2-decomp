#include "names.h"
/* Special map coordinates for the current level. The absolute aliases name
 * the same adjoining float blocks as the GP scalars; offset accesses retain
 * retail's absolute loads. The four coordinate pairs occupy 32 bytes, hence
 * this unit's -G32 profile.
 */
extern float absolute_D_001A9410[] __attribute__((section(".sdata")));
extern float absolute_D_001A9680[] __attribute__((section(".sdata")));
extern float absolute_D_001A9678[] __attribute__((section(".sdata")));
extern float absolute_D_001A9670[] __attribute__((section(".sdata")));
extern float g_map_bounds_x __attribute__((sda));
extern float g_map_point_x_default_c __attribute__((sda));
extern float g_map_point_x_offset __attribute__((sda));
extern float g_map_point_x_default_a __attribute__((sda));
extern int g_map_point_flag __attribute__((section(".sdata")));
extern int g_current_map_index __attribute__((section(".sdata")));
extern int g_map_mode __attribute__((nosda));
typedef struct {
    unsigned char reserved00[0x80];
    float x, y, z;
} MapPlayerView;

extern MapPlayerView g_hero_state;
extern float g_map_point_x_default_b __attribute__((sda));
extern float g_map_variant_point_x[8] __attribute__((sda));
extern float g_map_variant_point_y[] __attribute__((section(".sdata")));
extern int moby_get_current_variant_index(void);
extern void map_convert_world_to_map_position(float, float, float *, float *, int);
/* Callers pass (x, y, &u, &v, level): the player's coordinates in $f12/$f13, the two result
 * pointers in $a2/$a3 and the level number on the stack. This body keys on the global level
 * and the player view, so the coordinates and the level are unused. */
/* Finds where the player's marker goes on the map in special levels and says whether it found one. */
int GetSpecialMapCoordinates(float unused_x, float unused_y, float *x, float *y, int unused_level)
{
    int found = 0;
    if (g_map_point_flag) {
        if (g_current_map_index == 2) {
            *x = g_map_point_x_default_a;
            *y = absolute_D_001A9670[1];
            found = 1;
        } else if (g_current_map_index == 11) {
            *x = g_map_point_x_default_b;
            *y = absolute_D_001A9678[1];
            found = 1;
        }
    }
    if (g_current_map_index == 7 && moby_get_current_variant_index() >= 0 && moby_get_current_variant_index() < 4) {
        found = 1;
        *x = g_map_variant_point_x[moby_get_current_variant_index() * 2];
        *y = g_map_variant_point_y[moby_get_current_variant_index() * 2];
    } else if (g_current_map_index == 20) {
        if (g_map_mode == 2) {
            found = 1;
            *x = g_map_point_x_default_c;
            *y = absolute_D_001A9680[1];
        } else if (g_map_mode == 0) {
            if (g_hero_state.x >= g_map_bounds_x && g_hero_state.y <= absolute_D_001A9410[1] &&
                g_hero_state.x <= absolute_D_001A9410[2] && g_hero_state.y >= absolute_D_001A9410[3]) {
                found = 1;
                map_convert_world_to_map_position(g_hero_state.x, g_hero_state.y, x, y, 20);
                *x += g_map_point_x_offset;
                *y += absolute_D_001A9410[5];
            }
        }
    }
    return found;
}
