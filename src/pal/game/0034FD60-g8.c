/* func_PAL_0034FD60, the PAL copy of func_0034DB98: the same C, where panel100 grows by 0x10 and
   the padding after the text element by another 0x10, callee func_00336A78 becomes
   func_PAL_00338770 and func_0027F640 becomes func_PAL_0027FB48. PAL's languages change the
   thousands separator: language 4 also takes the dot, the dot's offsets are 11 and -35, and
   language 2 draws no separator at all. */

extern void func_00336320(void *);
extern void func_00336828(void *);
extern void func_PAL_00338770(void *);
extern float *func_00335E18(void *);
extern float *func_00335E10(void *);
extern unsigned int *func_00335E20(void *);
extern void func_0034AD10(void *);
extern unsigned long func_0027C878(int);
extern void func_PAL_0027FB48(float, float, unsigned long, char *, int, float, unsigned long, unsigned char *);
extern int func_0027FBD8(int, int, unsigned long, char *, int);
extern int func_00115DA8(char *, char *, ...);
extern int D_001A8C64[] __attribute__((sda));
extern int D_001A79F8[] __attribute__((sda)); /* the player's bolts */
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern unsigned char D_001A7A32[] __attribute__((sda)); /* bolt multiplier */
extern char D_001AE6F8[], D_001AE700[], D_001AE708[]; /* "'", ".", "x%d" */
extern int D_001ADAE8 __attribute__((sda));
extern int D_001ADAEC __attribute__((sda));
extern unsigned int D_001ADAF0 __attribute__((sda));

/* A g++ 2.95 vtable entry: this-adjustment, index, function. */
typedef struct HudVEntry {
    short delta;
    short index;
    void (*fn)(void *);
} HudVEntry;

typedef struct HudElem4C {
    char pad0[0x30];
    HudVEntry *vtable; /* 0x30 */
    char pad34[0x18];
} HudElem4C;

typedef struct HudElem3C {
    char pad0[0x30];
    HudVEntry *vtable; /* 0x30 */
    char pad34[0x8];
} HudElem3C;

typedef struct HudText {
    char pad0[0x34];
    unsigned char *metrics; /* 0x34 */
    long long style;        /* 0x38 */
} HudText;

typedef struct HudOwner {
    HudElem4C top[3];       /* 0x0 */
    char pad0E4[0x1C];
    char panel100[0x58];    /* 0x100 */
    char panel148[0x3C];    /* 0x158 */
    HudElem4C mid[2];       /* 0x194 */
    char pad22C[0x1C];
    HudText text;           /* 0x248 */
    char pad288[0x2A0 - 0x248 - sizeof(HudText)];
    char panel2A0[0x40];    /* 0x2A0 */
    HudElem4C side[2];      /* 0x2E0 */
    HudElem4C a[8];         /* 0x378 */
    HudElem4C b;            /* 0x5D8 */
    HudElem3C c[8];         /* 0x624 */
    char pad804[4];
    char final[4];          /* 0x808 */
} HudOwner;

/* Draws the bolt counter panel: thousands separators by language (as RAC1's
 * bolt counter) and the "x%d" multiplier. The vtable pointers are read through
 * &a[i] + 0x30 so that every induction value is object-relative, and each
 * loop keeps its own vtable local, as in RAC2's DRAW idiom (00337210.c). */
void func_PAL_0034FD60(void *arg)
{
    HudOwner *object = arg;
    char separator[32];
    char multiplierText[16];
    float *scale;
    float x, y, step;
    unsigned int color;
    int foreground, shadow;
    int i, j, digits, n, apostrophe, yoffset, xoffset;

    func_00336320(&object->top[0]);
    func_00336320(&object->top[1]);
    func_00336320(&object->top[2]);
    func_00336828(object->panel148);
    func_PAL_00338770(object->panel100);
    if (!D_001A8C64[0]) {
        HudElem4C *left = &object->side[0];
        HudElem4C *right = &object->side[1];
        func_00336320(left);
        func_00336320(right);
        { float *value = func_00335E18(left); *value = -*value; }
        { float *value = func_00335E18(right); *value = -*value; }
        func_00336320(left);
        func_00336320(right);
        { float *value = func_00335E18(left); *value = -*value; }
        { float *value = func_00335E18(right); *value = -*value; }
        for (i = 0; i < 8; i++) {
            HudVEntry *vt = *(HudVEntry **)((char *)&object->a[i] + 0x30);
            vt[1].fn((char *)&object->a[i] + vt[1].delta);
        }
        for (j = 0; j < 8; j++) {
            HudVEntry *vt = *(HudVEntry **)((char *)&object->c[j] + 0x30);
            vt[1].fn((char *)&object->c[j] + vt[1].delta);
        }
        func_00336320(&object->b);
        *func_00335E20(&object->b) = 0x70FFFEED;
    }
    func_00336320(&object->mid[0]);
    func_00336320(&object->mid[1]);
    func_PAL_00338770(&object->text);
    func_00336828(object->panel2A0);
    x = func_00335E10(&object->text)[0];
    y = func_00335E10(&object->text)[1];
    x += 32.0f;
    y += -10.0f;
    color = *func_00335E20(&object->text);
    digits = 1;
    n = D_001A79F8[0];
    while (n >= 10) { n /= 10; digits++; }
    apostrophe = D_001A7BB0[4] != 3 && D_001A7BB0[4] != 5 && D_001A7BB0[4] != 4;
    func_00115DA8(separator, apostrophe ? D_001AE6F8 : D_001AE700);
    yoffset = apostrophe ? 21 : 11;
    xoffset = apostrophe ? -34 : -35;
    if (D_001A7BB0[4] != 2) {
        step = 3.0f;
        if (step < (float)digits) {
            float start = x + (float)xoffset;
            do {
                HudText *t = &object->text;
                float drawX = start - (float)(int)(step * 11.6f);
                long long style;
                unsigned long texture;
                step += 3.0f;
                scale = func_00335E18(t);
                style = t->style;
                texture = func_0027C878((int)style);
                func_PAL_0027FB48(drawX, y + (float)yoffset, color, separator, -1, *scale, texture, t->metrics);
            } while (step < (float)digits);
        }
    }
    if (D_001A7A32[0] >= 2) {
        func_00115DA8(multiplierText, D_001AE708, D_001A7A32[0]);
        foreground = (D_001ADAF0 & 0xFFFFFF) | (color & 0xFF000000);
        shadow = color & 0xFF000000;
        func_0027FBD8(D_001ADAE8, D_001ADAEC + 2, shadow, multiplierText, -1);
        func_0027FBD8(D_001ADAE8 + 2, D_001ADAEC, shadow, multiplierText, -1);
        func_0027FBD8(D_001ADAE8 + 2, D_001ADAEC + 2, shadow, multiplierText, -1);
        func_0027FBD8(D_001ADAE8, D_001ADAEC, foreground, multiplierText, -1);
    }
    func_0034AD10(object->final);
}
