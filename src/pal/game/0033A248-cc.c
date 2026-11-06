/* func_PAL_0033A248, the PAL copy of func_003384C0: the same C. */

typedef int s32;

typedef unsigned char u8;

typedef float f32;

typedef unsigned int u32;

 /* text width */

/* Text box laid out by func_00337C10/func_00337E30: text at +0xA8, its line table at +0x1D8. */
extern int func_00115DA8(char *, char *, ...); /* formats into a buffer */
 /* screen size: [1] = height */
extern void func_PAL_0033A248(char *, unsigned int, unsigned int, float, float, float, float);

/* Reads a float through a pointer field; returns when it is zero or when a word field is zero, otherwise calls a helper, adjusts a float loaded from another pointer field by half or all of the helper's result depending on a small mode word, and finally calls a second helper with three pointers and three floats taken from the object and from two further pointer fields. */
/* Complete boot bodies from liolu PRs #72 and #75; refreshed in one combined batch. */
/* Measured target: byte-identical across all 27 levels. */
/* shared native body of family 5b6bba31 */
/* a bump/free-list allocator. `p` (the parameter, moved to `$a1`) is a six-word */
 /* memset */
 /* "aTxBrack" */
 /* "aTxTop" */
extern char *D_001A8CFC[] __attribute__((sda));

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
/* Partial view of the shared screen/render state (see src/game/00274128.c). */
typedef struct {
    char pad[0xB0];
    float fB0;
} ViewState;
extern ViewState D_001B9040;
extern void func_0027AB40(void);
extern int func_00335E08(void);
extern void func_00300A00(int, float, float, unsigned int, float, float, float);

/* Draws a frame when the level object exists: with the view scale at +0xB0 of D_001B9040
   set to 0.62 (restored afterwards), the two sprites at +0x220C go at the left and right
   ends and the four of +0x2210 at the corners, inset by 16; the last argument is computed
   from the frame's height, then from its width. Colour = alpha << 24 | color. */
void func_PAL_0033A248(char *obj, unsigned int alpha, unsigned int color, float top, float bottom, float left, float right)
{
    ViewState *view;
    float saved, scale, uv, insetRight, insetLeft, border;

    if (D_001A8CFC[0]) {
        view = &D_001B9040;
        scale = 1.0f;
        saved = view->fB0;
        view->fB0 = 0.62f;
        func_0027AB40();
        uv = ((bottom - top) - 26.0f) * 0.008928571827709675f;
        uv = uv * 0.3110000193119049f + 0.03750000149011612f;
        if (func_00335E08() == 1)
            scale = 0.9f;
        alpha <<= 24;
        alpha |= color;
        func_00300A00(*(int *)(obj + 0x222c), left, top, alpha, -1.0f, scale, uv);
        border = 16.0f;
        func_00300A00(*(int *)(obj + 0x222c), right, top, alpha, 1.0f, scale, uv);
        uv = ((right - left) - 150.0f) * 0.003267973894253373f;
        insetLeft = left + border;
        insetRight = right - border;
        uv = uv * 0.43300002813339233f + 0.10199999809265137f;
        func_00300A00(*(int *)(obj + 0x2230), insetLeft, top, alpha, -1.0f, 1.0f, uv);
        func_00300A00(*(int *)(obj + 0x2230), insetRight, top, alpha, 1.0f, 1.0f, uv);
        func_00300A00(*(int *)(obj + 0x2230), insetLeft, bottom, alpha, -1.0f, -1.0f, uv);
        func_00300A00(*(int *)(obj + 0x2230), insetRight, bottom, alpha, 1.0f, -1.0f, uv);
        view->fB0 = saved;
        func_0027AB40();
    }
}

extern int func_00115DA8(char *, char *, ...);

/* Writes the localised text `text_id` (with `value` as its only argument) into the
   buffer at +0x1E14 of the object, then initialises the sub-object at +0x1D6C with a
   count that defaults to 120 when the caller passes -1. The two pointers are defined
   in this order on purpose: it is what puts the buffer in $s1 and the count in $s2. */
