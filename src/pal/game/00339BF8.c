/* func_PAL_00339BF8: needs -frac2-keep-block-zero-copy (cse keeps `i = length`); see
   docs/build/compiler-notes.md. */

extern void *func_00115484(void *, int, unsigned int);
extern int func_0027F178(unsigned char *text, int length); /* text width */

/* Text box laid out by func_PAL_00339B88: text at +0xA8, its line table at +0x1D8. */
typedef struct {
    float *position;
    float *scale;
    unsigned char pad08[0xA0];
    unsigned char text[0x100];
    int unused1A8;
    int unused1AC;
    int lineCount;
    int unused1B4;
    int duration;
    unsigned char pad1BC[8];
    int mode;
    unsigned char pad1C8[0xC];
    int maxWidth;
    unsigned char *lines[30];
} TextBox;

/* func_PAL_00339BF8, the PAL copy of func_00337E98: the same C as v2.00's func_US2_00338D48, which
   stores the second argument at +0x1C4 and terminates the last line after the loop. */
void func_PAL_00339BF8(TextBox *box, int mode, int duration, float x, float y)
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
    box->maxWidth = 0;
    box->lineCount = 1;
    func_00115484(line, 0, sizeof(line));
    func_00115484(box->lines, 0, sizeof(box->lines));
    box->lines[box->lineCount - 1] = box->text;
    single = 1;
    for (; i < 0xFF && box->text[i] != 0; i++) {
        if (box->text[i] == 1) {
            line[length] = 0;
            box->text[i] = 0;
            single = 0;
            length = 0;
            box->lines[box->lineCount] = &box->text[i + 1];
            box->lineCount++;
            width = func_0027F178(line, -1);
            box->maxWidth = (box->maxWidth < width) ? width : box->maxWidth;
        } else {
            line[length] = box->text[i];
            length++;
        }
    }
    if (i < 0xFF && box->text[i] == 0) {
        line[length] = 0;
    }
    if (single) {
        box->maxWidth = func_0027F178(box->text, -1);
    } else {
        width = func_0027F178(line, -1);
        box->maxWidth = (box->maxWidth < width) ? width : box->maxWidth;
    }
    box->scale[0] = 1.0f;
}
