#include "include_asm.h"

extern int func_00336A40(void *);

extern int func_0027C878_2(int);

extern void func_0027F640(float, float, float, int, int, int, int, int);

typedef int s32;

typedef unsigned char u8;

typedef float f32;

typedef unsigned int u32;

extern void D_00115E38(char *assertion, int line, char *file);

extern char D_L00_001ADDD8[];

extern char D_L00_001ADDF8[];

typedef struct { unsigned int f0, f4, f8, f12, f16, f20; } T;

extern char D_L00_001ADDD8_1[];

extern char D_L00_001ADE20[];

extern void D_00115E38_1(char *a0, int a1, char *a2);

extern int func_L00_002E9100(char *, int);

extern void func_00115AC0_1(void *, int, int);

extern void func_00337E98_1(void *, int, int, float, float);

extern int func_0027F178(unsigned char *text, int length); /* text width */

/* Text box laid out by func_00337C10/func_00337E30: text at +0xA8, its line table at +0x1D8. */
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
    unsigned char pad1BC[0x18];
    int maxWidth;
    unsigned char *lines[30];
} TextBox;

extern int func_00115DA8(char *, char *, ...); /* formats into a buffer */
extern char D_001ADB58[], D_001ADB68[], D_001ADB78[], D_001ADB90[];
extern char D_001ADBB0[], D_001ADBB8[], D_001ADBC8[];
extern int D_001A7340[] __attribute__((sda)); /* screen size: [1] = height */
extern void func_00280190(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void func_00280200(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void func_00280270(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void func_0027EB88(int top, int bottom, int left, int right, int alpha, int color);
extern void func_003384C0(char *, unsigned int, unsigned int, float, float, float, float);

/* Reads a float through a pointer field; returns when it is zero or when a word field is zero, otherwise calls a helper, adjusts a float loaded from another pointer field by half or all of the helper's result depending on a small mode word, and finally calls a second helper with three pointers and three floats taken from the object and from two further pointer fields. */
void func_00336A78(char *o)
{
    float f20;
    int s4;
    int r;
    int s2v;
    char *p0;
    char *p1;

    if (*(float *)(*(char **)(o + 16)) == 0.0f) {
        return;
    }
    if (*(int *)(o + 64) == 0) {
        return;
    }
    s4 = func_00336A40(o);
    f20 = *(float *)(*(char **)(o));
    switch (*(int *)(o + 68)) {
    case 0:
        break;
    case 1:
        f20 = f20 - (float)(s4 >> 1);
        break;
    case 2:
        f20 = f20 - (float)s4;
        break;
    }
    p0 = *(char **)(o);
    p1 = *(char **)(o + 4);
    s2v = *(int *)(*(char **)(o + 12));
    r = func_0027C878_2(*(int *)(o + 56));
    func_0027F640(f20, *(float *)(p0 + 4), *(float *)(p1), s2v, *(int *)(o + 64),
            s4, r, *(int *)(o + 52));
}

/* Complete boot bodies from liolu PRs #72 and #75; refreshed in one combined batch. */
void func_00336B90(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x40) = a1; }

void func_00336B98(char *object, int value)
{
    unsigned int limit = *(unsigned int *)(object + 0x40);
    unsigned int clamped;
    if (limit < (unsigned int)value) clamped = limit;
    else clamped = value;
    if ((float)limit == 0.0f) {
        **(float **)(object + 4) = 0.0f;
        return;
    }
    **(float **)(object + 4) = ((float)clamped / (float)*(unsigned int *)(object + 0x40)) * (float)*(unsigned int *)(object + 0x3C);
}


/* Measured target: byte-identical across all 27 levels. */
void func_00336CC0(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x38) = a1; }

void func_00336CC8(u8 *a0,s32 a1) {
 (*(f32 **)(a0+4))[1]=(f32)a1;
}

void func_00336CE0(u8 *object, s32 value) {
    *(s32 *)(object + 0x44) = value;
}

extern void func_00300618(void *);

void func_00336CE8(char *object)
{
    int count = *(int *)(object + 0x18);
    int i;
    int *row = (int *)(object + 0x1C);
    for (i = 0; i < count; i++) {
        row[i * 2 + 1] += (int)object;
        func_00300618((void *)row[i * 2 + 1]);
    }
}

s32 func_00336D50(u8 *a0,s32 a1) {
 s32 count=*(s32 *)(a0+0x18); s32 i,out=0;u8 *base=a0+0x1c;
 for(i=0;i<count;i++) {
  s32 *p=(s32 *)((i<<3)+(u32)base);
  if(p[0]==a1) {out=p[1];break;}
 }
 return out;
}

void func_00336DA0(void)
{
}

void *func_00336DA8(void *first, void *second) { (void) first; return second; }

void *func_00336DB0(void *object) {
    return object;
}

/* shared native body of family 5b6bba31 */
void func_00336DB8(int *p, unsigned int a1, int a2, int a3)
{
    if (a1 < 4)
        D_00115E38(D_L00_001ADDD8, 37, D_L00_001ADDF8);
    p[1] = a3;
    p[2] = a1;
    p[4] = 0;
    p[5] = 0;
    p[3] = 0;
    p[0] = a2;
}


/* a bump/free-list allocator. `p` (the parameter, moved to `$a1`) is a six-word */
void *func_00336E40(T *p)
{
    unsigned int off, size;
    void *r;

    if (p->f20 != 0)
    {
        unsigned int *x = (unsigned int *)p->f20;

        p->f20 = x[0];
        p->f16 = p->f16 + 1;
        return x;
    }
    off = p->f12;
    size = p->f8;
    if (p->f4 < off + size)
    {
        D_00115E38_1(D_L00_001ADDD8_1, 83, D_L00_001ADE20);
        return 0;
    }
    r = (void *)(p->f0 + off);
    p->f12 = off + size;
    p->f16 = p->f16 + 1;
    return r;
}

void func_00336ED0(u8 *a0, u8 *a1) {
    *(u8 **)(a1 + 0) = *(u8 **)(a0 + 0x14);
    *(u8 **)(a0 + 0x14) = a1;
    *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) - 1;
}

extern int D_001ADB10 __attribute__((sda));

int func_00336EF0(void) {
    return D_001ADB10;
}



INCLUDE_ASM("asm/game", func_00337210);

extern void *func_003361A8(void *);

void *func_00337BD8(char *object) {
    func_003361A8(object + 0x10);
    func_003361A8(object + 0x5C);
    return object;
}

extern int *func_00335E20(void *);
extern void func_00335E68(void *, int);
extern void func_003361E0(void *, void *, void *);
extern void func_00336390(void *, int, int);
extern void func_003363C0(void *, float);
extern void *func_00115484(void *, int, unsigned int); /* memset */
extern char D_001ADB40[]; /* "aTxBrack" */
extern char D_001ADB50[]; /* "aTxTop" */
extern char *D_001A8CFC[] __attribute__((sda));

/* Initialises a text panel: clears its state and, when a pool is given, takes four 16-byte
   cells from it with func_00336E40/func_00336DA8 (255,108 / colour 0x60442D00 / two cleared
   cells), then sets up the "aTxBrack" and "aTxTop" widgets at +0x10 and +0x5C with
   D_001A8CFC[0] + 0x8710 and colour 0x55F0C070. The cleared cells store word 0 last, as in
   func_00339078; the colour cell is cleared as floats before its integer colour is stored. */
void func_00337C10(char *obj, void *pool)
{
    char *top;
    char *bracket;

    obj[0xA8] = 0;
    *(int *)(obj + 0x1AC) = 0;
    *(int *)(obj + 0x1A8) = 0;
    *(int *)(obj + 0x1C8) = 0;
    *(int *)(obj + 0x1CC) = 0;
    *(int *)(obj + 0x1D4) = 0x28;
    *(int *)(obj + 0x1C4) = 1;
    *(int *)(obj + 0x1B0) = 1;
    func_00115484(obj + 0x1D8, 0, 0x78);
    if (pool != 0) {
        float *xy;
        float *colour;
        int *cell4;
        int *cellC;

        xy = func_00336DA8((void *)16, func_00336E40(pool));
        xy[0] = 255.0f;
        xy[1] = 108.0f;
        ((int *)xy)[2] = 0;
        ((int *)xy)[3] = 0;
        *(float **)(obj + 0) = xy;
        colour = func_00336DA8((void *)16, func_00336E40(pool));
        colour[0] = 0.0f;
        colour[1] = 0.0f;
        *(int *)colour = 0x60442D00;
        ((int *)colour)[2] = 0;
        ((int *)colour)[3] = 0;
        *(float **)(obj + 8) = colour;
        cell4 = func_00336DA8((void *)16, func_00336E40(pool));
        *(int **)(obj + 4) = cell4;
        cell4[1] = 0;
        cell4[2] = 0;
        cell4[3] = 0;
        cell4[0] = 0;
        cellC = func_00336DA8((void *)16, func_00336E40(pool));
        *(int **)(obj + 12) = cellC;
        cellC[1] = 0;
        cellC[2] = 0;
        cellC[3] = 0;
        cellC[0] = 0;
    }
    bracket = obj + 0x10;
    top = obj + 0x5C;
    func_003361E0(bracket, D_001ADB40, pool);
    func_00336390(bracket, (int)(D_001A8CFC[0] + 0x8710), 0x57);
    func_003363C0(bracket, 0.02f);
    func_00335E68(bracket, 1);
    *func_00335E20(bracket) = 0x55F0C070;
    func_003361E0(top, D_001ADB50, pool);
    func_00336390(top, (int)(D_001A8CFC[0] + 0x8710), 0x58);
    func_00335E68(top, 1);
    *func_00335E20(top) = 0x55F0C070;
    **(int **)(obj + 12) = 0x80F0F0F0;
    *(int *)(obj + 0x1B8) = 0;
    **(int **)(obj + 4) = 0;
}


/* Initialises an object: two float stores through the pointer at +0, clears byte +423, stores an int at +440, calls a callee with (this+168, -1) storing its result at +468 and the address at +472, sets +432 to 1 and writes 1.0f through the pointer at +4. */
void func_00337E30(char *p, int a1, int a2, float f12, float f13)
{
    char *q = p + 168;

    *(float *)(*(int *)p) = f12;
    *(float *)(*(int *)p + 4) = f13;
    p[423] = 0;
    *(int *)(p + 440) = a2;
    *(int *)(p + 472) = (int)q;
    *(int *)(p + 468) = func_L00_002E9100(q, -1);
    *(int *)(p + 432) = 1;
    *(float *)(*(int *)(p + 4)) = 1.0f;
}

/* Sets the box's text up: position, duration, then splits the text at each 1 byte into the line
   table, measuring every line with func_0027F178 and keeping the widest in maxWidth. */
void func_00337E98(TextBox *box, int unused, int duration, float x, float y)
{
    unsigned char line[0x100];
    int length = 0;
    int single;
    int i;
    int width;

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
    i = 0;
    if (box->text[0] != 0) {
        unsigned char *next = &box->text[1];

        for (; i < 0xFF && box->text[i] != 0; i++, next++) {
            if (box->text[i] == 1) {
                line[length] = 0;
                box->text[i] = 0;
                single = 0;
                length = 0;
                box->lines[box->lineCount] = next;
                box->lineCount++;
                width = func_0027F178(line, -1);
                box->maxWidth = (box->maxWidth < width) ? width : box->maxWidth;
            } else {
                line[length] = box->text[i];
                length++;
            }
        }
    }
    if (single) {
        box->maxWidth = func_0027F178(box->text, -1);
    } else {
        width = func_0027F178(line, -1);
        box->maxWidth = (box->maxWidth < width) ? width : box->maxWidth;
    }
    box->scale[0] = 1.0f;
}

/* clamps a caller-supplied terminator value (-1 meaning unset) to 360, then runs two callees on two sub-objects of one handle, the second with a float pair */
void func_00338040(int object, int value, int count)
{
    int limit = (count == -1) ? 360 : count;
    int inner = object + 8124;

    func_00115AC0_1((void *)(object + 8292), value, 255);
    func_00337E98_1((void *)inner, 1, limit, 255.0f, 80.0f);
}

INCLUDE_ASM("asm/game", func_003380A8);

/* Formats text (with up to three extra strings) into a buffer, lays it out in the box with the
   font routine chosen by mode, optionally centres the box vertically on the screen, then draws a
   padded backing rectangle and frame behind it and lays the text out again on top. */
void func_003380B0(void *object, short *box, int style, char *text, int mode,
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
    func_003384C0(object, 96, 0x55F0C070, (float)top, (float)bottom, (float)left, (float)right);
    switch (mode) {
    case 0: func_00280200(box, style, buffer, length); break;
    case 1: func_00280190(box, style, buffer, length); break;
    case 2: func_00280270(box, style, buffer, length); break;
    }
    box[9] = flags;
}

INCLUDE_ASM("asm/game", func_003384C0);

extern char *func_00288FB8(int);

extern int func_00115DA8(char *, char *, ...);

/* Writes the localised text `text_id` (with `value` as its only argument) into the
   buffer at +0x1E14 of the object, then initialises the sub-object at +0x1D6C with a
   count that defaults to 120 when the caller passes -1. The two pointers are defined
   in this order on purpose: it is what puts the buffer in $s1 and the count in $s2. */
void func_00338718(char *object, int text_id, int value, int count)
{
    char *sub = object + 0x1D6C;
    int limit = (count == -1) ? 120 : count;
    char *buffer = object + 0x1E14;

    func_00115DA8(buffer, func_00288FB8(text_id), value);
    func_00337E30(sub, 1, limit, 255.0f, 135.0f);
}
