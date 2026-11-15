#include "include_asm.h"
#include "names.h"

extern int g_current_map_index __attribute__((sda));
extern void data_set_small_value_and_refresh(int, int);

/* Picks a number based on the current level (9 or 18 for two levels, else 0) and passes it on. */
void level_set_dependent_value(void)
{
    int value = 0;
    switch (g_current_map_index) {
    case 22: value = 9; break;
    case 23: value = 18; break;
    }
    data_set_small_value_and_refresh(value, 1);
}
