#include "names.h"
/* func_PAL_L01_003BEB40, the PAL copy of func_L01_003BAFB0: the same C. */
#include "common.h"

extern float g_water_l01_height __attribute__((sda));

/* Returns the height of the water surface in this level (PAL version). */
float level_get_water_height_pal(void) {
    return g_water_l01_height;
}

/* func_L01_003B57A8 is defined in L01_003835D8.c. */

extern int g_current_map_index MACRO_ADDR;
extern u8 g_item_enabled_flags[] MACRO_ADDR;
typedef struct { u8 pad[0x2290]; u8 *target; } OozlaHero;
extern OozlaHero g_hero_state;
extern int g_oozla_intro_stage MACRO_ADDR;
