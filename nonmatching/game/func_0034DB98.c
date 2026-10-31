/* func_0034DB98 - 1088 bytes, boot and all 27 levels. Called by func_0034E4F8 with
   object + 0x7A0: redraws the overlay's widgets (two of them twice with their scale
   negated), calls the second vtable entry of two arrays of eight widgets, then draws
   the counter digits in steps of three and, from the second lap, the lap number with
   a three-way shadow through func_0027FBD8.

   Attempt, 30 October 2026: 1088/1088 bytes, 0/28 USA places (tools/check.py), in
   src/game/0034CEA0-g8.c (the $gp reads are D_001ADAE8/EC/F0) after func_0034F690;
   func_0034E4F8 and func_0034F690 still pass 28/28 there. That unit declares
   func_0034DB98 as taking void *: change it to char *.
   Remaining differences:
   - register permutation: the first vtable loop's widget, vptr and counter are in
     s5/s4/s3 where retail has s4/s3/s5; retail keeps self + 0x238 in s0 and a copy in
     s4 (copied to s1 for the loop) and the digit count in s1, cc1 uses s1 and s3;
   - retail hoists (float)dy out of the digit loop (f24) and adds y in the loop; cc1
     converts dy in the loop;
   - retail loads the style field at 0x38 with ld and sign-extends the low word
     (dsll32/dsra32); cc1 narrows it to lw.
   Measured steps: 1108 with the offsets as float ternaries in the loop; 1072 with int
   offsets; 1080 with the widget arrays as structs (two induction pointers, as retail),
   separate scale temporaries and a 16-byte lap buffer; 1088 with the loop bound
   `k < count` instead of a float copy made before the sprintf.
   Tried without change: (float)dy + y; a float copy of dy (worse); a volatile or
   shifted 64-bit field read (1096); a long long parameter for func_0027C878, with and
   without the int cast or an int field; a separate widget pointer (1092). */

/* A text widget: pointers to its position, scale and colour, and a vtable whose second
 * entry redraws it. */
typedef struct {
    short delta;
    short index;
    void (*fn)(char *);
} VtableEntry;

typedef struct {
    char pad00[0x30];
    VtableEntry *vptr;
    char pad34[0x18];
} Widget4C;

typedef struct {
    char pad00[0x30];
    VtableEntry *vptr;
    char pad34[0x8];
} Widget3C;

extern int D_001A8C64;
extern int D_001A79F8;
extern unsigned char D_001A7BB4;
extern unsigned char D_001A7A32;
extern int D_001ADAE8 __attribute__((sda));
extern int D_001ADAEC __attribute__((sda));
extern int D_001ADAF0 __attribute__((sda));
extern char D_001AE6F8[], D_001AE700[], D_001AE708[];
extern void func_00336320(char *);
extern void func_00336828(char *);
extern void func_00336A78(char *);
extern float *func_00335E10(char *);
extern float *func_00335E18(char *);
extern unsigned int *func_00335E20(char *);
extern unsigned long long func_0027C878(int);
extern void func_0027F640(float, float, float, unsigned long long, char *, int, unsigned long long, int);
extern int func_0027FBD8(int, int, unsigned long long, char *, int);
extern int func_00115DA8(char *, const char *, ...);
extern void func_0034AD10(char *);

static inline void flip(char *widget)
{
    float *p = func_00335E18(widget);
    *p = -*p;
}

/* The pause overlay: redraws its widgets, then the counter digits and the lap number. */
void func_0034DB98(char *self)
{
    char text[32];
    char lap[16];
    char *a;
    char *b;
    char *digits;
    float x, y, k;
    unsigned int color;
    int count;
    int value;
    int wide;
    int dx, dy;
    int i;

    func_00336320(self);
    func_00336320(self + 0x4C);
    func_00336320(self + 0x98);
    func_00336828(self + 0x148);
    func_00336A78(self + 0x100);
    if (D_001A8C64 == 0) {
        a = self + 0x2C0;
        b = self + 0x30C;
        func_00336320(a);
        func_00336320(b);
        flip(a);
        flip(b);
        func_00336320(a);
        func_00336320(b);
        flip(a);
        flip(b);
        for (i = 0; i < 8; i++) {
            VtableEntry *vt = ((Widget4C *)(self + 0x358))[i].vptr;
            vt[1].fn((char *)&((Widget4C *)(self + 0x358))[i] + vt[1].delta);
        }
        for (i = 0; i < 8; i++) {
            VtableEntry *vt = ((Widget3C *)(self + 0x604))[i].vptr;
            vt[1].fn((char *)&((Widget3C *)(self + 0x604))[i] + vt[1].delta);
        }
        func_00336320(self + 0x5B8);
        *func_00335E20(self + 0x5B8) = 0x70FFFEED;
    }
    digits = self + 0x238;
    func_00336320(self + 0x184);
    func_00336320(self + 0x1D0);
    func_00336A78(digits);
    func_00336828(self + 0x280);
    x = func_00335E10(digits)[0];
    y = func_00335E10(digits)[1];
    x += 32.0f;
    y += -10.0f;
    color = *func_00335E20(digits);
    count = 1;
    for (value = D_001A79F8; value >= 10; value /= 10)
        count++;
    wide = D_001A7BB4 != 3 && D_001A7BB4 != 5;
    func_00115DA8(text, wide ? D_001AE6F8 : D_001AE700);
    dy = wide ? 0x15 : 0xA;
    dx = wide ? -0x22 : -0x1D;
    for (k = 3.0f; k < count; k += 3.0f) {
        float left = x + dx - (int)(k * 11.6f);
        float *scale = func_00335E18(digits);
        func_0027F640(left, y + dy, *scale, color, text, -1,
                      func_0027C878((int)*(long long *)(digits + 0x38)), *(int *)(digits + 0x34));
    }
    if (D_001A7A32 >= 2) {
        int alpha;
        int tint;

        func_00115DA8(lap, D_001AE708, D_001A7A32);
        alpha = color & 0xFF000000;
        tint = (D_001ADAF0 & 0xFFFFFF) | alpha;
        func_0027FBD8(D_001ADAE8, D_001ADAEC + 2, alpha, lap, -1);
        func_0027FBD8(D_001ADAE8 + 2, D_001ADAEC, alpha, lap, -1);
        func_0027FBD8(D_001ADAE8 + 2, D_001ADAEC + 2, alpha, lap, -1);
        func_0027FBD8(D_001ADAE8, D_001ADAEC, tint, lap, -1);
    }
    func_0034AD10(self + 0x7E8);
}
