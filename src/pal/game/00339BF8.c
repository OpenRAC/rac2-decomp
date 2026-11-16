#include "names.h"
/* func_PAL_00339BF8: needs -frac2-keep-block-zero-copy (cse keeps `i = length`); see
   docs/build/compiler-notes.md. */

extern void *memset(void *, int, unsigned int);
extern int text_measure_width_small(unsigned char *text, int length); /* text width */

/* Text box laid out by func_PAL_00339B88: text at +0xA8, its line table at +0x1D8. */
typedef struct {
    float *position;
    float *scale;
    unsigned char pad08[0xA0];
    unsigned char text[0x100];
    int unused_1A8;
    int unused_1AC;
    int line_count;
    int unused_1B4;
    int duration;
    unsigned char pad1BC[8];
    int mode;
    unsigned char pad1C8[0xC];
    int max_width;
    unsigned char *lines[30];
} TextBox;

/* func_PAL_00339BF8, the PAL copy of func_00337E98: the same C as v2.00's func_US2_00338D48, which
   stores the second argument at +0x1C4 and terminates the last line after the loop. */
void text_box_layout_lines_pal(TextBox *box, int mode, int duration, float x, float y)
{
    unsigned char line[0x100];
    int length = 0;
    int i = length;
    int single;
    int width;

    box->mode = mode;
    box->position[0] = x;
    box->position[1] = y;
    box->duration = duration;
    box->text[0xFF] = 0;
    box->max_width = 0;
    box->line_count = 1;
    memset(line, 0, sizeof(line));
    memset(box->lines, 0, sizeof(box->lines));
    box->lines[box->line_count - 1] = box->text;
    single = 1;
    for (; i < 0xFF && box->text[i] != 0; i++) {
        if (box->text[i] == 1) {
            line[length] = 0;
            box->text[i] = 0;
            single = 0;
            length = 0;
            box->lines[box->line_count] = &box->text[i + 1];
            box->line_count++;
            width = text_measure_width_small(line, -1);
            box->max_width = (box->max_width < width) ? width : box->max_width;
        } else {
            line[length] = box->text[i];
            length++;
        }
    }
    if (i < 0xFF && box->text[i] == 0) {
        line[length] = 0;
    }
    if (single) {
        box->max_width = text_measure_width_small(box->text, -1);
    } else {
        width = text_measure_width_small(line, -1);
        box->max_width = (box->max_width < width) ? width : box->max_width;
    }
    box->scale[0] = 1.0f;
}
