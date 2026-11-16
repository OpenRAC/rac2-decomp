#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

extern TI128 g_level_quad_first __attribute__((sda));
extern TI128 g_level_quad_second __attribute__((sda));
extern TI128 g_level_quad_third __attribute__((sda));
extern TI128 g_level_quad_fourth __attribute__((sda));
extern TI128 *g_level_quad_source __attribute__((sda));

/* Copies four 16-byte blocks into global storage and remembers where the data after them starts. */
void level_load_quadword_block(TI128 *src) {
    g_level_quad_first = *src++;
    g_level_quad_second = *src++;
    g_level_quad_third = *src++;
    g_level_quad_fourth = *src++;
    g_level_quad_source = src;
}
