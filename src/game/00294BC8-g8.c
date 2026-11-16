#include "include_asm.h"
#include "names.h"

/* func_00297F98 needs the small-data profile: it materialises the address of
   the pair of 16-byte records through $gp.  Its other globals stay absolute. */

extern int g_current_map_index;

extern int g_map_mode __attribute__((nosda));

extern int g_map_coefficient_table __attribute__((sda));

typedef struct {
    int field00;
    int field04;
    int field08;
    int field0c;
} Quad16;

extern Quad16 g_map_coefficient_table_2[];

/* Returns the map scaling values for a level; on level 20 it picks one of two special sets. */
float *map_get_coefficients(int levelIndex)
{
    if (g_current_map_index == 20) {
        int value = g_map_mode;

        return (int)((char *)&g_map_coefficient_table + (value % 2) * 16);
    }
    return (int)&g_map_coefficient_table_2[levelIndex];
}
