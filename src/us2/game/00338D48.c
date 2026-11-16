#include "names.h"
/* func_US2_00338D48: needs -frac2-keep-block-zero-copy (cse keeps `i = length`); see
   docs/build/compiler-notes.md. */

extern void *memset(void *, int, unsigned int);
extern int text_measure_width_small(unsigned char *text, int length); /* text width */

/* Text box laid out by func_US2_00338CD8: text at +0xA8, its line table at +0x1D8. */
typedef struct {
    float *position;
    float *scale;
    unsigned char pad_08[0xA0];
    unsigned char text[0x100];
    int unused_1A8;
    int unused_1AC;
    int line_count;
    int unused_1B4;
    int duration;
    unsigned char pad_1BC[8];
    int mode;
    unsigned char pad_1C8[0xC];
    int max_width;
    unsigned char *lines[30];
} TextBox;

/* Splits the box text at 0x01 characters into lines, records each line start and the widest line width (v2.00 version of LayoutTextBoxLines). */
void layout_text_box_lines_us2(TextBox *box, int mode, int duration, float x, float y)
{
    unsigned char line[0x100];
    unsigned char *text;
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
    text = box->text;
    box->lines[box->line_count - 1] = text;
    single = 1;
    for (; i < 0xFF && text[i] != 0; i++) {
        if (text[i] == 1) {
            line[length] = 0;
            text[i] = 0;
            single = 0;
            length = 0;
            box->lines[box->line_count] = &box->text[i + 1];
            box->line_count++;
            width = text_measure_width_small(line, -1);
            box->max_width = (box->max_width < width) ? width : box->max_width;
        } else {
            line[length] = text[i];
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
