#include "include_asm.h"
#include "names.h"

extern float func_002E5460(int);

extern void func_003109C8(char *, int, int);

/* Starts a timer on the object: stores how fast it counts down for the given length, then switches the object to state 1. */
void moby_start_timer_state(char *moby, int length, int param)
{
    int *vars = *(int **)(moby + 0x68);
    float length_float;

    vars[0] = 0;
    length_float = func_002E5460(length);
    vars[2] = param;
    *(float *)((char *)vars + 4) = 1.0f / length_float;
    func_003109C8(moby, 1, -1);
}
