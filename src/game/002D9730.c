#include "names.h"
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_00295F60(int, unsigned long long);

/* Sets two draw states, makes one more draw setup call, and returns 8. */
int func_002D9730(void)
{
    VU1_addGSregister(66, 68);
    VU1_addGSregister(71, 11);
    DrawMapOverlay(1, 0);
    return 8;
}
