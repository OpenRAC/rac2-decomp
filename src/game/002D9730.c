#include "names.h"
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void DrawMapOverlay(int, unsigned long long);

/* Sets two draw states, makes one more draw setup call, and returns 8. */
int gfx_setup_draw_states(void)
{
    VU1_addGSregister(66, 68);
    VU1_addGSregister(71, 11);
    DrawMapOverlay(1, 0);
    return 8;
}
