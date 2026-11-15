#include "include_asm.h"
#include "names.h"

/* Small-data unit: the bodies whose state lives at $gp-relative offsets. */

extern int D_L04_001B1C2C __attribute__((sda));

/* Arms the mode flag the level reads from its small-data word. */
void barlow_enable_mode_flag(void)
{
    D_L04_001B1C2C = 1;
}
