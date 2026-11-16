#include "include_asm.h"
#include "names.h"

/* Does nothing and returns zero. */
unsigned int stub_empty_31_us2(void)
{
    return 0;
}


/* Returns zero (the actuator power calculation is stubbed out). */
unsigned int actuator_calc_power_us2(void)
{
    return 0;
}


