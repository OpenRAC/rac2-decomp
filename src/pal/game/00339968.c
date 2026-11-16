#include "include_asm.h"
#include "names.h"


extern int text_measure_width_small(unsigned char *text, int length); /* text width */

/* func_PAL_00339B88, the PAL copy of func_00337E30: the same C, plus a store of the second argument at +0x1C4. */
/* Sets up a message box: position, mode and duration, and measures its text width. */
void msg_box_init_state_pal(char *box, int mode, int duration, float x, float y)
{
    char *text = box + 168;

    *(int *)(box + 452) = mode;
    *(float *)(*(int *)box) = x;
    *(float *)(*(int *)box + 4) = y;
    box[423] = 0;
    *(int *)(box + 440) = duration;
    *(int *)(box + 472) = (int)text;
    *(int *)(box + 468) = text_measure_width_small((unsigned char *)text, -1);
    *(int *)(box + 432) = 1;
    *(float *)(*(int *)(box + 4)) = 1.0f;
}

extern char *strncpy(void *, int, int);
extern void text_box_layout_lines_pal(void *, int, int, float, float);

/* clamps a caller-supplied terminator value (-1 meaning unset) to 360, then runs two callees on two sub-objects of one handle, the second with a float pair */
void msg_box_init_long_pal(int object, int value, int count)
{
    int limit = (count == -1) ? 300 : count;
    int inner = object + 8156;

    strncpy((void *)(object + 8324), value, 255);
    text_box_layout_lines_pal((void *)inner, 2, limit, 255.0f, 80.0f);
}





/* clamps a caller-supplied terminator value (-1 meaning unset) to 180, then runs two callees on two sub-objects of one handle, the second with a float pair */
void msg_box_init_short_pal(int object, int value, int count)
{
    int limit = (count == -1) ? 150 : count;
    int inner = object + 7564;

    strncpy((void *)(object + 7732), value, 254);
    text_box_layout_lines_pal((void *)inner, 2, limit, 255.0f, 123.0f);
}

