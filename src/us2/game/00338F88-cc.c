/* func_US2_00338F88, the USA v2.00 copy of func_003380B0: the same C, where rename func_003384C0 becomes func_US2_00339398. */

typedef int s32;

typedef unsigned char u8;

typedef float f32;

typedef unsigned int u32;

 /* text width */

/* Text box laid out by func_00337C10/func_00337E30: text at +0xA8, its line table at +0x1D8. */
extern int func_00115DA8(char *, char *, ...); /* formats into a buffer */
extern char D_001ADB58[], D_001ADB68[], D_001ADB78[], D_001ADB90[];
extern char D_001ADBB0[], D_001ADBB8[], D_001ADBC8[];
extern int D_001A7340[] __attribute__((sda)); /* screen size: [1] = height */
extern void func_00280190(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void func_00280200(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void func_00280270(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void func_0027EB88(int top, int bottom, int left, int right, int alpha, int color);
extern void func_US2_00339398(char *, unsigned int, unsigned int, float, float, float, float);

/* Reads a float through a pointer field; returns when it is zero or when a word field is zero, otherwise calls a helper, adjusts a float loaded from another pointer field by half or all of the helper's result depending on a small mode word, and finally calls a second helper with three pointers and three floats taken from the object and from two further pointer fields. */
/* Complete boot bodies from liolu PRs #72 and #75; refreshed in one combined batch. */
/* Measured target: byte-identical across all 27 levels. */
/* shared native body of family 5b6bba31 */
/* a bump/free-list allocator. `p` (the parameter, moved to `$a1`) is a six-word */
 /* memset */
 /* "aTxBrack" */
 /* "aTxTop" */
/* Initialises a text panel: clears its state and, when a pool is given, takes four 16-byte
   cells from it with func_00336E40/func_00336DA8 (255,108 / colour 0x60442D00 / two cleared
   cells), then sets up the "aTxBrack" and "aTxTop" widgets at +0x10 and +0x5C with
   D_001A8CFC[0] + 0x8710 and colour 0x55F0C070. The cleared cells store word 0 last, as in
   func_00339078; the colour cell is cleared as floats before its integer colour is stored. */
/* Initialises an object: two float stores through the pointer at +0, clears byte +423, stores an int at +440, calls a callee with (this+168, -1) storing its result at +468 and the address at +472, sets +432 to 1 and writes 1.0f through the pointer at +4. */
/* Sets the box's text up: position, duration, then splits the text at each 1 byte into the line
   table, measuring every line with func_0027F178 and keeping the widest in maxWidth. */
/* clamps a caller-supplied terminator value (-1 meaning unset) to 360, then runs two callees on two sub-objects of one handle, the second with a float pair */
/* Formats text (with up to three extra strings) into a buffer, lays it out in the box with the
   font routine chosen by mode, optionally centres the box vertically on the screen, then draws a
   padded backing rectangle and frame behind it and lays the text out again on top. */
void func_US2_00338F88(void *object, short *box, int style, char *text, int mode,
                   int center, int length, int single, char *first, char *second, int third)
{
    char buffer[768];
    int flags = box[9];
    int top, bottom, left, right;
    int halfWidth, halfHeight;
    int x, y;

    box[9] |= 3;
    if (first) {
        if (second) {
            if (third) {
                if (single) func_00115DA8(buffer, D_001ADB58, text, 1, first, 1, second);
                else func_00115DA8(buffer, D_001ADB68, text, 1, 1, first, 1, second);
            } else {
                if (single) func_00115DA8(buffer, D_001ADB78, text, 1, first, second);
                else func_00115DA8(buffer, D_001ADB90, text, 1, 1, first, second);
            }
        } else {
            if (single) func_00115DA8(buffer, D_001ADBB0, text, 1, first);
            else func_00115DA8(buffer, D_001ADBB8, text, 1, 1, first);
        }
    } else {
        func_00115DA8(buffer, D_001ADBC8, text);
    }
    box[9] |= 4;
    switch (mode) {
    case 0: func_00280200(box, style, buffer, length); break;
    case 1: func_00280190(box, style, buffer, length); break;
    case 2: func_00280270(box, style, buffer, length); break;
    }
    if (center) {
        int height = (unsigned short)box[7];
        int newTop = (D_001A7340[1] - (short)height) >> 1;
        int middle = newTop + ((short)height >> 1);

        box[1] = newTop + height;
        box[5] = middle;
        box[0] = newTop;
    }
    switch (mode) {
    case 0: func_00280200(box, style, buffer, length); break;
    case 1: func_00280190(box, style, buffer, length); break;
    case 2: func_00280270(box, style, buffer, length); break;
    }
    halfWidth = (box[6] >> 1) + 10;
    halfHeight = (box[7] >> 1) + 5;
    box[9] &= ~4;
    x = box[4];
    y = box[5];
    top = y - halfHeight;
    left = x - halfWidth;
    right = x + halfWidth;
    bottom = y + halfHeight;
    func_0027EB88(top, bottom, left, right, 96, 0x60442D00);
    func_US2_00339398(object, 96, 0x55F0C070, (float)top, (float)bottom, (float)left, (float)right);
    switch (mode) {
    case 0: func_00280200(box, style, buffer, length); break;
    case 1: func_00280190(box, style, buffer, length); break;
    case 2: func_00280270(box, style, buffer, length); break;
    }
    box[9] = flags;
}

/* Partial view of the shared screen/render state (see src/game/00274128.c). */
typedef struct {
    char pad[0xB0];
    float fB0;
} ViewState;
extern ViewState D_001B9040;
/* Draws a frame when the level object exists: with the view scale at +0xB0 of D_001B9040
   set to 0.62 (restored afterwards), the two sprites at +0x220C go at the left and right
   ends and the four of +0x2210 at the corners, inset by 16; the last argument is computed
   from the frame's height, then from its width. Colour = alpha << 24 | color. */
void func_US2_00339398(char *obj, unsigned int alpha, unsigned int color, float top, float bottom, float left, float right);

extern int func_00115DA8(char *, char *, ...);

/* Writes the localised text `text_id` (with `value` as its only argument) into the
   buffer at +0x1E14 of the object, then initialises the sub-object at +0x1D6C with a
   count that defaults to 120 when the caller passes -1. The two pointers are defined
   in this order on purpose: it is what puts the buffer in $s1 and the count in $s2. */
