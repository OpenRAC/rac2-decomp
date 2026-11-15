#include "include_asm.h"
#include "names.h"

extern void strncpy(void *, int, int);

extern void LayoutTextBoxLines(void *, int, int, float, float);

/* clamps a caller-supplied terminator value (-1 meaning unset) to 180, then runs two callees on two sub-objects of one handle, the second with a float pair */
/* Prepares a short (about three seconds) message with its text value and position on screen. */
void msg_box_init_short(int screen, int textValue, int requestedDuration)
{
    int duration = (requestedDuration == -1) ? 180 : requestedDuration;
    int textBox = screen + 7532;

    strncpy((void *)(screen + 7700), textValue, 254);
    LayoutTextBoxLines((void *)textBox, 1, duration, 255.0f, 123.0f);
}

/* Does nothing. */
void ui_nop_b(void)
{
}

/* func_00338810 needs $gp-relative data: it lives in the -g8 sibling file. */

/* Does nothing. */
void ui_nop_c(void)
{
}
