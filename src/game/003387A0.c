#include "include_asm.h"
#include "names.h"

extern void func_00115AC0(void *, int, int);

extern void func_00337E98(void *, int, int, float, float);

/* clamps a caller-supplied terminator value (-1 meaning unset) to 180, then runs two callees on two sub-objects of one handle, the second with a float pair */
/* Prepares a short (about three seconds) message with its text value and position on screen. */
void func_003387A0(int screen, int textValue, int requestedDuration)
{
    int duration = (requestedDuration == -1) ? 180 : requestedDuration;
    int textBox = screen + 7532;

    strncpy((void *)(screen + 7700), textValue, 254);
    LayoutTextBoxLines((void *)textBox, 1, duration, 255.0f, 123.0f);
}

/* Does nothing. */
void func_00338808(void)
{
}

/* func_00338810 needs $gp-relative data: it lives in the -g8 sibling file. */

/* Does nothing. */
void func_00338A58(void)
{
}
