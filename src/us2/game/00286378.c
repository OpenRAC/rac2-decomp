#include "include_asm.h"
#include "names.h"


/* func_US2_00287108: v2.00's own exit helper of the menu overlay: refresh, set D_0018A000 to 10, pop the state. */
extern short D_0018A000;
extern void pad_clear_port_state(void);
extern int request_end_slot(int, int);

void func_US2_00287108(void)
{
    pad_clear_port_state();
    D_0018A000 = 10;
    request_end_slot(0, 0);
}
