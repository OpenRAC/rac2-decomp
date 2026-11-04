#include "common.h"

typedef int InitQuad __attribute__((mode(TI)));
typedef struct { u8 pad[0xB0]; float scale; } PathView;
extern PathView D_L00_001BD2C0;
extern u8 *D_L00_001FDA80[];
typedef struct { u8 pad[0x194]; InitQuad *transform; } PathCamera;
extern PathCamera D_L00_001B8C80;
extern float func_00283248(float x, float y);
extern void func_00282C88(InitQuad *v);
extern int func_L00_002C42E0(int event, int value);
/* Partial records follow only the fields used by the two path walks.
 * Retail reserves eight weight/index slots and assumes at most eight accepted
 * entries; it does not add a bounds check to the path scan. */
typedef struct {
    u8 unknown00[0x20];
    int pathIndex;
    int secondPathIndex;
    u8 unknown28[0x10];
    u8 active;
    u8 unknown39;
    short duration;
    float speed;
    u8 unknown40[0xC];
    int eventGate;
    int initialized;
    u8 unknown54[0xC];
    float weights[8];
    int indices[8];
} PathConfig;
typedef struct {
    int first;
    int second;
    float distance;
    float secondDistance;
    int current;
    short node;
    short duration;
} MotionPrefix;

extern void func_00283410(char *, char *);
extern int func_00282948(char *);
extern float func_00283CE0(int);
extern void func_L00_0031AC60(char *, char *, char *, float);
extern void func_L00_0031AD40(char *, char *, char *, float);
extern void func_00272550(char *, char *, char *);
extern float func_00283BE0(float, float);
extern float func_002A7C00(float, float, float);
extern float func_L00_0031ABE0(float, float, float);
extern float func_002A7AA8(float, float, float, float, float);
extern float func_002702C8(char *, float, float, float, float, float);
extern float func_002703B0(char *, float, float, float, float, float);
extern float D_L00_001B8DD8;


/* Measured child block reached at owner->sub + 0x40. */
typedef struct { char pad[0x4C]; float height; } Part_28CE0;



extern void func_L00_00426248(int);

extern void func_L00_00425490_1(int);

extern void func_L00_00424F98(int, float *, float *);

extern void func_L00_00425118(int, float, float);

extern void func_L00_004243C0(int);

extern void func_L00_00425CD0(int);

extern void func_L00_00425560(int);

extern void func_00282F20_1(char *a0, char *a1, float f);

extern void func_00282D30_5(char *a0, char *a1, float f);

extern void func_00282CC0_4(char *a0, char *a1, char *a2);

extern char D_00189E20_6[];

extern char D_00189EA0[];

extern void func_L00_002DA0B8(char *first, char *second, char *third);

extern float func_00283B98_6(float value, float reference);

extern void func_00283410_5(char *out, char *source);

extern void func_00283678(char *object, char *out);

extern void func_L00_002D7940_1(char *p);

extern void func_L00_002EE0C0(char *p);

extern void func_L00_00427B40_1(char *p);

extern char D_L00_001B8C80_1[];

extern char D_00189E20_3[];

extern float func_00283248_1(float a, float b);

extern float func_00283C80(float a, float b);

extern float func_00282E48(char *a, char *b);

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_6af85cabb56d3b41_SmallConditional52Owner {
    unsigned char unknown_00[0x7d];
    unsigned char value_7d;
    short value_7e;
    unsigned char unknown_80[6];
    short identity_86;
} Rac2Native_6af85cabb56d3b41_SmallConditional52Owner;

extern void ref_L00_00428EB0_00(char *);

extern void ref_L00_00428EB0_01(char *);

extern void func_L00_004276E8(char *);

extern void func_L00_002DA1E0(char *, float);

extern void func_L00_00426680(char *);

extern void func_0035F3A8(int, int, int);

extern void *func_00335FB0(void *);

extern void func_L00_00426560(char *);

#define SDA_OBJ __attribute__((section(".sdata")))

extern char *D_L00_001B1844 SDA_OBJ;

extern char *D_L00_001B8E10;

extern char D_L00_001ADD98[] SDA_OBJ;

extern char D_L00_001ADD38[] SDA_OBJ;

extern char D_L00_001ADD78[] SDA_OBJ;

extern char D_L00_001ADD58[] SDA_OBJ;

typedef struct Rac2Native_6af85cabb56d3b41_SmallConditional52Global {
    unsigned char unknown_00[0x2290];
    char *ptr_2290;
    int mode_2294;
    unsigned char unknown_2298[0x208];
    int identity_24a0;
} Rac2Native_6af85cabb56d3b41_SmallConditional52Global;

extern Rac2Native_6af85cabb56d3b41_SmallConditional52Global D_00189E20_20;

/* runs a fixed sequence of seven callees on one object handle, passing the address of two stack floats to the third callee and then their values to the fourth */
void func_L00_00426340(int object)
{
    float x;
    float y;

    func_L00_00426248(object);
    func_L00_00425490_1(object);
    func_L00_00424F98(object, &x, &y);
    func_L00_00425118(object, x, y);
    func_L00_004243C0(object);
    func_L00_00425CD0(object);
    func_L00_00425560(object);
}
void func_L00_00426478(void)
{
}

/* selects one of three scale factors from a flag byte in a fixed global table, builds two 16-byte stack values through two callees, then applies two transforms rooted at object+48 against two fixed global tables */
void func_L00_00426480(char *object)
{
    char local[16];
    char buf[16];
    char *p = D_00189E20_6;
    unsigned char v;

    func_00282F20_1(local, (char *)(*(int *)(p + 8848) + 224), 1.0f);
    v = *(unsigned char *)(p + 8884);
    if (v == 2) {
        func_00282D30_5(buf, local, 9.5f);
    } else if (v == 1) {
        func_00282D30_5(buf, local, 0.75f);
    } else {
        func_00282D30_5(buf, local, 1.6f);
    }
    func_00282CC0_4(object + 48, D_00189EA0, buf);
    func_00282CC0_4(object + 48, D_00189EA0 + 208, object + 48);
}

/* func_L00_00426560 is defined in L00_00426560-helpers.c. */

/* clears the seven words of the sub-object at +0x70 (the last after a refresh call), then
   clears the flag word and the identity word-16 of the table entry and the owner's +0x7E. */
void func_L00_00426680(char *self)
{
    char *p = *(char **)(self + 0x70);
    char *q;

    *(int *)(p + 0x0) = 0;
    *(int *)(p + 0x8) = 0;
    *(int *)(p + 0x4) = 0;
    *(int *)(p + 0xC) = 0;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0x14) = 0;
    *(int *)(p + 0x18) = 0;
    func_L00_00426560(self);
    q = *(char **)(D_L00_001B1844 + *(short *)(self + 0x84) * 0x20 + 0x1C);
    *(short *)(q + 0x26) = 0;
    *(short *)(self + 0x7E) = 0;
}


INCLUDE_ASM("asm/levels", func_L00_00426C78);

void func_L00_00427008(char *self)
{
    char *a = D_L00_001B8C80_1;
    char *b;
    short v = *(short *)(a + 0x290);

    if (v != 0) {
        *(short *)(a + 0x290) = 2;
    } else {
        *(short *)(a + 0x290) = 1;
    }
    b = D_L00_001B8C80_1;
    *(char *)(b + 0x293) = 0;
    *(float *)(b + 0x2B4) = 0.075f;
    *(float *)(b + 0x2A8) = 0.075f;
    func_L00_00426680(self);
    if (*(int *)(b + 0x264) != 0) {
        func_0035F3A8(0, 0, *(int *)(b + 0x264));
    }
}

/* when the mode halfword at +0x86 is 4 or 0x51, raises the flag halfword of the table entry
   selected by the owner's index halfword at +0x84. */
void func_L00_00427078(void)
{
    char *p = D_L00_001B8E10;
    short mode = *(short *)(p + 0x86);
    char *q;

    if (mode == 4 || mode == 0x51) {
        q = *(char **)(D_L00_001B1844 + *(short *)(p + 0x84) * 0x20 + 0x1C);
        *(short *)(q + 0x26) = 1;
    }
}

extern float func_00282DB0(char *a0, char *a1);

extern void func_00282D30(char *a0, char *a1, float f);

extern void func_00282CF0(char *a0, char *a1, char *a2);

extern float func_00282DF0(char *a0);

extern float func_002831B0(float f);

/* Restores the owner's half-turn state: it measures the two world vectors of the table
   entry, compares the angle they make with a fixed threshold, and writes the owner's
   half-word at +0x7E and the entry's flag half-word at +0x290. The block at the end
   resets the entry's two small floats and the owner's state; the two tests jump to it,
   and it needs its own copy of the entry's address. */
void func_L00_004270C0(char *owner)
{
    char tmp[16];
    char v1[16];
    char v2[16];
    char *base;
    char *b;
    float f1;
    float f2;
    float f20;
    float r;
    float s;

    if (D_00189E20_20.identity_24a0 == 0x51) {
        return;
    }
    if (D_00189E20_20.identity_24a0 == 4) {
        return;
    }
    base = D_L00_001B8C80_1;
    if (*(short *)(base + 0x290) == 0) {
        *(char *)(base + 0x293) = 0;
        *(short *)(owner + 0x7E) = 2;
        *(float *)(base + 0x2B4) = 0.018f;
        *(float *)(base + 0x2A8) = 0.018f;
        return;
    }
    f1 = func_00282DB0(base + 0x1D0, owner);
    func_00282D30(tmp, base + 0x1D0, f1);
    func_00282CF0(v1, owner, tmp);
    f2 = func_00282DB0(base + 0x1D0, D_00189E20_20.ptr_2290 + 0xC0);
    func_00282D30(tmp, base + 0x1D0, f2);
    func_00282CF0(v2, D_00189E20_20.ptr_2290 + 0xC0, tmp);
    f20 = func_00282DF0(v2);
    if (f20 == 0.0f) {
        goto small;
    }
    f20 = f20 * func_00282DF0(v1);
    if (f20 == 0.0f) {
        goto small;
    }
    r = func_00282DB0(v2, v1);
    s = func_002831B0(r / f20);
    if (1.3962636f <= 1.5707964f - s) {
        *(short *)(base + 0x290) = 0;
        *(short *)(owner + 0x7E) = 4;
        return;
    }
small:
    b = D_L00_001B8C80_1;

    *(char *)(b + 0x293) = 0;
    *(short *)(owner + 0x7E) = 2;
    *(float *)(b + 0x2B4) = 0.018f;
    *(float *)(b + 0x2A8) = 0.018f;
}

extern void func_002EE0D0(void *);
extern void func_002EE970(void *, void *);
extern void func_002EEBD8(void *, void *);

void func_L00_00427620(unsigned char *a0) {
    unsigned char buf[0x40];
    unsigned char *p;

    *(int *)(*(unsigned char **)(a0 + 0x70) + 0xC0) = 4;
    p = *(unsigned char **)(a0 + 0x70) + 0x30;
    *(float *)(p + 0x20) = 0.05f;
    *(float *)(p + 0x24) = 0.3f;
    *(float *)(p + 0x28) = 1.0f;
    *(unsigned short *)(p + 0x2C) = 1;
    func_002EE0D0(p);
    {
        unsigned char *q = *(unsigned char **)(a0 + 0x70);

        *(float *)(q + 0x10) = 0.3f;
        *(float *)(q + 0x14) = 0.3f;
        *(float *)(q + 0x18) = 1.0f;
        *(unsigned short *)(q + 0x1C) = 1;
        func_002EE0D0(q);
    }
    func_002EE970(buf, a0 + 0x40);
    func_002EEBD8(a0, buf);
    *(unsigned short *)(a0 + 0x7E) = 0;
}

/* Blends the saved camera position and orientation, then rebuilds its matrix. */
void func_L00_004276E8(char *object)
{
    char matrix[64];
    char *saved = *(char **)(object + 0x70);
    char *rotation = saved + 0x30;
    char *target = saved + 0x80;
    char *transition = saved + 0xE0;
    float x, y, delta, blend;

    if (*(unsigned char *)(object + 0x88) == 1) {
        goto snap;
    } else if (*(unsigned char *)(object + 0x88) == 2) {
        float fraction;

        func_00282948(transition);
        fraction = (float)(*(int *)(transition + 4) - *(int *)(saved + 0xE0)) /
                   func_00283CE0(*(int *)(transition + 4));
        func_L00_0031AC60(object + 0x30, object + 0x30, target, fraction);
        func_L00_0031AD40(object + 0x40, object + 0x40, saved + 0x90, fraction);
        goto finish;
    } else if (*(unsigned char *)(object + 0x88) == 3) {
        float fraction;

        if (func_00282948(transition)) {
        snap:
            qcopy(object + 0x30, target);
            qcopy(object + 0x40, saved + 0x90);
            goto finish;
        }
        fraction = (float)(*(int *)(transition + 4) - *(int *)(saved + 0xE0)) /
                   func_00283CE0(*(int *)(transition + 4));
        func_00272550(saved + 0xE8, target, D_00189EA0);
        x = func_00283BE0(*(float *)(transition + 8), *(float *)(transition + 0x1C));
        y = func_00283BE0(*(float *)(target + 0x18), D_L00_001B8DD8);
        if ((x > 0.3490659f && y < -0.3490659f) ||
            (x < -0.3490659f && y > 0.3490659f)) {
            float zero = 0.0f;

            delta = *(float *)(transition + 8) - *(float *)(transition + 0x1C);
            if (delta < zero && y > zero)
                delta = -delta;
            else if (delta > zero && y < zero)
                delta = -delta;
            *(float *)(transition + 0x1C) += func_002A7C00(0.0f, delta, fraction);
        } else {
            *(float *)(transition + 0x1C) = func_L00_0031ABE0(
                *(float *)(transition + 0x1C), *(float *)(transition + 8), fraction);
        }
        blend = func_002A7AA8(*(float *)(transition + 0x44), 0.0f, 1.0f,
                             *(float *)(transition + 0x48), fraction);
        *(float *)(transition + 0x24) +=
            (*(float *)(transition + 0x10) - *(float *)(transition + 0x24)) * blend;
        *(float *)(transition + 0x20) = func_L00_0031ABE0(
            *(float *)(transition + 0x20), *(float *)(transition + 0xC), fraction);
        func_L00_0031AC60(transition + 0x30, transition + 0x30, D_00189EA0, fraction);
        func_L00_002DA0B8(object + 0x30, transition + 0x1C, transition + 0x30);
        func_L00_0031AD40(object + 0x40, object + 0x40, target + 0x10, fraction);
        goto finish;
    }
    if (*(short *)(saved + 0x1C) == 1) {
        *(float *)(object + 0x30) = func_002702C8(saved,
            *(float *)(object + 0x30), *(float *)target,
            *(float *)(saved + 0x10), *(float *)(saved + 0x14), *(float *)(saved + 0x18));
        *(float *)(object + 0x34) = func_002702C8(saved + 4,
            *(float *)(object + 0x34), *(float *)(target + 4),
            *(float *)(saved + 0x10), *(float *)(saved + 0x14), *(float *)(saved + 0x18));
        *(float *)(object + 0x38) = func_002702C8(saved + 8,
            *(float *)(object + 0x38), *(float *)(target + 8),
            *(float *)(saved + 0x10), *(float *)(saved + 0x14), *(float *)(saved + 0x18));
    }
    if (*(short *)(rotation + 0x2C) == 1) {
        *(float *)(object + 0x40) = func_002703B0(rotation,
            *(float *)(object + 0x40), *(float *)(target + 0x10),
            *(float *)(rotation + 0x20), *(float *)(rotation + 0x24), *(float *)(rotation + 0x28));
        *(float *)(object + 0x44) = func_002703B0(saved + 0x34,
            *(float *)(object + 0x44), *(float *)(target + 0x14),
            *(float *)(rotation + 0x20), *(float *)(rotation + 0x24), *(float *)(rotation + 0x28));
        *(float *)(object + 0x48) = func_002703B0(saved + 0x38,
            *(float *)(object + 0x48), *(float *)(target + 0x18),
            *(float *)(rotation + 0x20), *(float *)(rotation + 0x24), *(float *)(rotation + 0x28));
    }
finish:
    func_00283410(matrix, object + 0x40);
    func_00283678(object, matrix);
}

unsigned int func_L00_00427AD8(void)
{
    return 0;
}

/* When the sub-object at +0x70 gains its flag word at +0x40, clears the byte at +0x89 and
   fades the block at +0x30 to a half-turn target. */
void func_L00_00427AE0(char *a0)
{
    char *p = *(char **)(a0 + 0x70) + 0xE0;

    func_L00_004276E8(a0);
    if (*(int *)(p + 0x40)) {
        *(char *)(a0 + 0x89) = 0;
        func_L00_002DA1E0(a0 + 0x30, 0.5f);
    }
}

void func_L00_00427B38(void)
{
}

/* Refreshes a child sub-structure through a setup helper, folds four float pairs (one measured against a fixed half-turn constant) through a shared two-float helper, and hands the resulting four-field block to a second helper. */
void func_L00_00427B40(char *object)
{
    float local[16];
    char *child = *(char **)(object + 112);

    child += 176;
    func_L00_002DA0B8(object + 48, object + 80, child);
    *(float *)(object + 80) = func_00283B98_6(*(float *)(object + 80), *(float *)(child + 24));
    *(int *)(object + 64) = 0;
    *(float *)(object + 68) = func_00283B98_6(*(float *)(object + 84), *(float *)(object + 92));
    *(float *)(object + 72) = func_00283B98_6(3.14159265f, *(float *)(object + 80));
    *(float *)(object + 72) = func_00283B98_6(*(float *)(object + 72), *(float *)(object + 96));
    *(int *)(object + 76) = 0;
    func_00283410_5((char *)local, object + 64);
    func_00283678(object, (char *)local);
}

extern void func_L00_002D7958_1(float *, void *, float);

/* 128-bit copies reach lq/sq only through TImode. */
typedef int TQ_00427BE8 __attribute__((mode(TI)));

/* func_L00_00427BE8 is defined in L00_00427BE8-helpers.c. */

/* resets a sub-object reached through field +112 of its argument: two int zeros through a pointer 176 bytes in, twelve float constants (0.3/0.04/0.07/1.0/0.99) and three int zeros over offsets 40..172, then four calls (sub-object, +80, +144, the argument) and a 16-bit zero at +126 */
void func_L00_00427C78(char *self)
{
    char *q = (char *)*(int **)(self + 112) + 176;
    float *f;

    *(int *)(q + 64) = 0;
    f = (float *)*(int **)(self + 112);
    f[40] = 3.0000001192092895507812e-01f;
    f[41] = 3.0000001192092895507812e-01f;
    f[39] = 0.0f;
    f[42] = 0.0f;
    *(int *)(q + 68) = 0;
    f[43] = 0.0f;
    f[18] = 9.9000000953674316406250e-01f;
    f[15] = 3.9999999105930328369141e-02f;
    f[16] = 3.9999999105930328369141e-02f;
    f[17] = 3.9999999105930328369141e-02f;
    f[10] = 7.0000000298023223876953e-02f;
    f[11] = 1.0000000000000000000000e+00f;
    f[19] = 3.9999999105930328369141e-02f;
    f[12] = 7.0000000298023223876953e-02f;
    f[13] = 1.0000000000000000000000e+00f;
    f[14] = 7.0000000298023223876953e-02f;

    func_L00_002D7940_1((char *)f + 80);
    func_L00_002D7940_1((char *)f);
    func_L00_002EE0C0((char *)f + 144);
    func_L00_00427B40_1(self);

    *(short *)(self + 126) = 0;
}

/* func_L00_00427D50 is defined in L00_00427D50-g8.c. */


/* func_L00_004282F0 is defined in L00_004282F0-spawn.c. */

/* Reads two floats from a data block, differences them against two globals, calls a two-float helper with the difference pair, refines the returned float through a second helper, then selects one of two small state codes and clears a flag byte according to two float thresholds. */
void func_L00_004283C8(char *o)
{
    char *B = D_L00_001B8C80_1;
    char *D = D_00189E20_3;
    float *p = *(float **)(D + 8848);
    float r = func_00283C80(*(float *)(B + 344),
                      func_00283248_1(p[4] - *(float *)(B + 320),
                              p[5] - *(float *)(B + 324)));

    if (r < 0.5585054f) {
        r = func_00282E48(D + 128, B + 320);
        if (r < 8.0f) {
            *(char *)(B + 659) = 0;
            *(short *)(o + 126) = 2;
            *(float *)(B + 692) = 0.018f;
            *(float *)(B + 680) = 0.018f;
        } else {
            *(short *)(o + 126) = 4;
        }
    } else {
        *(short *)(o + 126) = 4;
    }
    *(char *)(o + 125) = 0;
}

int func_L00_004284A8(void) {
    return 0;
}

/* func_L00_004284B0 is defined in L00_004284B0-helpers.c. */

void func_L00_00428580(void)
{
}

/* func_L00_00428588 is in L00_00428588.c. */



/* runs a fixed pair of callees on the same object handle */
void func_L00_00428EB0(char *a0)
{
    ref_L00_00428EB0_00(a0);
    ref_L00_00428EB0_01(a0);
}

/* A method that does nothing and returns 0, reached through a data pointer in every
   level that has it. Its entry is 24 bytes into the catalogued row, after linker fill. */
int func_L00_00428EE0(void) {
    return 0;
}


/* When the global identity differs from the signed owner identity at offset 0x86 and the global mode is not 6, clear the owner byte at offset 0x7D and write signed short value 3 at offset 0x7E. */
void func_L00_00428FE8(Rac2Native_6af85cabb56d3b41_SmallConditional52Owner *owner)
{
    if (D_00189E20_20.identity_24a0 != owner->identity_86 &&
        D_00189E20_20.mode_2294 != 6) {
        owner->value_7d = 0;
        owner->value_7e = 3;
    }
}

#define MACRO_ADDR __attribute__((section(".sdata")))

extern char * r1_D_L10_0015F050 MACRO_ADDR;

extern char *r1_D_L10_0015F050 MACRO_ADDR;

/* rac1-decomp src/overlays/shared/vendor_00299AF0.c: func_L10_002F6E10 */
/* Adapted from Lombyte (MIT) for PAL by OpenRAC's tools/port.py: src/overlays/shared/gameplay_vendor_002e3de8.c, FUN_L10_002f5a50. */
void func_L00_00429020(int i) {
    unsigned char *q;
    q = *(unsigned char **)(r1_D_L10_0015F050 + i * 0x20 + 0x1C);
    q[0x38] = 1;
    q[0x39] = 0;
}


extern char * r1_D_L10_001B0C30[];
extern int r1_func_00215570(void *, int);
extern int r1_func_L00_00260AB0(void *, int);
extern int r1_func_L00_00260B68(float *, int);
extern int r1_func_L00_0025A778(float *, float *, int);

/* rac1-decomp src/overlays/shared/rocket_and_path_camera.c: func_L00_004290C0 */
/* Adapted from Lombyte's project (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/overlays/shared/gameplay_vendor_002e3de8.c, FUN_L10_002f5a78. */
int func_L00_004290C0(char *moby, char *unused)
{
    unsigned char *e = *(unsigned char **)(r1_D_L10_0015F050 + *(short *)(moby + 0x84) * 32 + 0x1C);

    if (*(int *)(e + 0x0C) >= 0) {
        if (r1_func_00215570(D_00189EA0, *(int *)(e + 0x0C))) return 1;
    } else if (*(int *)(e + 0x10) >= 0) {
        if (r1_func_L00_00260AB0(D_00189EA0, *(int *)(e + 0x10))) return 1;
    } else if (*(int *)(e + 0x08) >= 0) {
        if (r1_func_L00_00260B68((float *)D_00189EA0, *(int *)(e + 0x08))) return 1;
    } else if (*(int *)(e + 0x14) >= 0) {
        int i = *(int *)(e + 0x14);
        if (r1_func_L00_0025A778((float *)D_00189EA0,
                                  (float *)(r1_D_L10_001B0C30[i] + 0x10),
                                  *(int *)r1_D_L10_001B0C30[i])) return 1;
    } else if (e[0x38] != 0 && e[0x39] == 0) {
        return 1;
    }
    return 0;
}

void func_L00_004291A0(u8 *object)
{
    PathConfig *data = *(PathConfig **)(D_L00_001B1844 + *(short *)(object + 0x84) * 32 + 0x1c);
    MotionPrefix *motion;
    u8 *pathState;
    float *weights = data->weights;
    int accepted;
    float distance;
    InitQuad *transform;
    data->active = 1;
    motion = (MotionPrefix *)(*(u8 **)(object + 0x70) + 0x40);
    motion->first = 0;
    motion->second = 0;
    motion->distance = 0;
    motion->secondDistance = 0;
    motion->current = 0;
    motion->node = 0;
    motion->duration = data->duration;
    pathState = *(u8 **)(object + 0x70) + 0x58;
    {
        int i;
        for (i = 0; i < 8; i++) {
            data->weights[i] = 0.0f;
            data->indices[i] = -1;
        }
    }
    accepted = 0;
    *(float *)(pathState + 0x30) = func_00283248(1.0f, D_L00_001BD2C0.scale) * 2.0f;
    if (data->initialized == 0 && data->pathIndex >= 0) {
        int i;
        u8 *path = D_L00_001FDA80[data->pathIndex];
        for (i = 0; i < *(int *)path; i++) {
            float weight = *(float *)(path + (i << 4) + 0x1C);
            if (weight > 0.0f) {
                weights[accepted] = weight;
                if (weight > 180.0f)
                    weights[accepted] = *(float *)(pathState + 0x30) * 57.2957763671875f;
                data->indices[accepted] = i;
                accepted++;
            }
            distance = func_00282E48((char *)(path + (i * 16 + 0x10)), (char *)(path + 0x10 + ((i + 1) % *(int *)path) * 16));
            *(float *)(path + (i << 4) + 0x1C) = distance;
            if (i < *(int *)path - 1)
                motion->distance += distance;
        }
    }
    if (data->duration > 0)
        data->speed = (motion->distance / func_00283CE0(data->duration)) * 60.0f;
    if (data->secondPathIndex >= 0) {
        int i;
        u8 *path = D_L00_001FDA80[data->secondPathIndex];
        for (i = 0; i < *(int *)path; i++) {
            int byteOffset = i * 16;
            distance = func_00282E48((char *)(path + (byteOffset + 0x10)), (char *)(path + 0x10 + ((i + 1) % *(int *)path) * 16));
            *(float *)(path + byteOffset + 0x1C) = distance;
            if (i < *(int *)path - 1)
                motion->secondDistance += distance;
        }
    }
    { u8 *saved = *(u8 **)(object + 0x70);
    *(float *)saved = 0.03f;
    *(float *)(saved + 4) = 0.2f;
    func_00282C88((InitQuad *)(saved + 0x10));
    }
    { u8 *saved = *(u8 **)(object + 0x70);
    *(float *)(saved + 0x20) = 0.03f;
    *(float *)(saved + 0x24) = 0.2f;
    func_00282C88((InitQuad *)(saved + 0x30));
    }
    transform = D_L00_001B8C80.transform;
    qcopy(object + 0x30, transform + 3);
    qcopy(object, transform);
    qcopy(object + 0x10, transform + 1);
    qcopy(object + 0x20, transform + 2);
    if (data->eventGate == 0)
        func_L00_002C42E0(0x6f, 1);
    data->initialized = 1;
}

extern int D_0018C0BC;
extern int D_0018C0B4;
extern int func_L00_004290C0(char *, char *);

int func_L00_00429C18(char *self, char *target)
{
    char *entry = *(char **)(D_L00_001B1844 + *(short *)(self + 0x84) * 0x20 + 0x1C);

    if (*(unsigned char *)(entry + 0x39) != 0) {
        return -1;
    }
    if (*(unsigned char *)(entry + 0x38) != 0 && *(short *)(target + 0x86) != 0x13) {
        return 1;
    }
    if (target != 0 && *(short *)(target + 0x7E) == 0 &&
        *(unsigned char *)(target + 0x7C) >= *(unsigned char *)(self + 0x7C)) {
        return 0;
    }
    if (func_L00_004290C0(self, target) == 0) {
        return 0;
    }
    if (*(int *)(entry + 0x48) >= 0 && D_0018C0BC != *(int *)(entry + 0x48)) {
        return 0;
    }
    if (*(int *)(entry + 0x44) >= 0 && D_0018C0B4 != *(int *)(entry + 0x44)) {
        return 0;
    }
    return 1;
}

void func_L00_00429CE0(void)
{
}

/* func_L00_00429CE8 is defined in L00_00429CE8.c. */

/* func_L00_00429F68 is defined in L00_00429F68.c. */

extern int D_L00_001A8F00 __attribute__((sda));

extern int func_L00_00429CE8(char *);

extern void func_L00_00429F68(char *);

/* Looks the owner's table entry up (index half-word at +0x84, 0x20 bytes per entry, the
   entry's own pointer at +0x1C) and clears its flag half-word at +0x26 and its word at
   +0x20, but only when the entry is still idle, the global gate allows it and the extra
   check accepts the owner. */
int func_L00_0042A460(char *a0)
{
    char *p = *(char **)(D_L00_001B1844 + *(short *)(a0 + 0x84) * 0x20 + 0x1C);

    if (*(short *)(p + 0x26) != 0) {
        return 0;
    }
    if (D_L00_001A8F00 != 0) {
        if (func_L00_00429CE8(a0) != 0) {
            *(short *)(p + 0x26) = 0;
            *(int *)(p + 0x20) = 0;
            return 0;
        }
    }
    func_L00_00429F68(a0);
    return 0;
}

INCLUDE_ASM("asm/levels", func_L00_0042A4E8);

/* clears the word at +0x20 and the halfword at +0x26 of the table entry selected by the
   index argument. */
void func_L00_0042A500(int i)
{
    char *q = *(char **)(D_L00_001B1844 + i * 0x20 + 0x1C);

    *(short *)(q + 0x26) = 0;
    *(int *)(q + 0x20) = 0;
}


/* func_L00_0042A698 is defined in L00_00426340-g8.c. */

/* func_L00_0042A908 is defined in L00_0042A908-g8.c. */

int func_L00_0042AB40(void) {
    return -1;
}

void func_L00_0042AB48(void)
{
}

/* func_L00_0042AC18 is defined in L00_0042AC18.c. */

/* func_L00_0042AD98 is defined in L00_0042AD98.c. */


extern void r1_func_001F9BF0(void *, void *, void *);
extern void r1_func_001F9EC0(void *, void *, void *);
extern float r1_func_001F9B88(float);
extern float r1_func_001FA888(int);
extern int r1_func_001FA898(float);
extern void r1_func_L01_002A2C90(int a, int b, int c, int d, int e);
extern char D_00189003[];


/* rac1-decomp src/overlays/shared/music_box_voices.c: func_L00_0042B038 */
/* reverb box sound update: starts or stops the sound as the listener enters or leaves the box */
void func_L00_0042B038(char *moby) {
    float a[4];
    float b[4];
    unsigned char *data = *(unsigned char **)(moby + 8);
    r1_func_001F9BF0(a, D_00189003 + 0xE9D, moby + 0x40);
    a[3] = 0;
    r1_func_001F9EC0(b, a, moby + 0x50);
    if (r1_func_001F9B88(b[0]) <= 1.0f && r1_func_001F9B88(b[1]) <= 1.0f && r1_func_001F9B88(b[2]) <= 1.0f) {
        float t = (b[0] + 1.0f) * 0.5f;
        int v = r1_func_001FA898(r1_func_001FA888(*(int *)(data + 4)) * t);
        int w = *(int *)(data + 4);
        if (!(w < v)) w = v;
        r1_func_L01_002A2C90((int)moby, data[0], w, data[1], data[2]);
        data[3] = 1;
    } else if (data[3] != 0) {
        if (b[0] > 0.0f) {
            r1_func_L01_002A2C90(0, data[0], *(int *)(data + 4), data[1], data[2]);
        } else {
            r1_func_L01_002A2C90((int)moby, 0, 0, 0, 0);
        }
        data[3] = 0;
    }
}


/* refreshes the object, installs the block at +0x30 and returns the object. */
char *func_L00_0042BAD0(char *a0)
{
    func_00335FB0(a0);
    *(char **)(a0 + 0x30) = D_L00_001ADD98;
    return a0;
}


char *func_L00_0042BCF8(char *a0)
{
    func_00335FB0(a0);
    *(char **)(a0 + 0x30) = D_L00_001ADD38;
    return a0;
}

char *func_L00_0042BFF8(char *a0)
{
    func_00335FB0(a0);
    *(char **)(a0 + 0x30) = D_L00_001ADD78;
    return a0;
}


char *func_L00_0042C290(char *a0)
{
    func_00335FB0(a0);
    *(char **)(a0 + 0x30) = D_L00_001ADD58;
    return a0;
}


/* Store the supplied unsigned 32-bit word at owner byte offset 0x 44. */
void func_L00_0042C358(int param_1, unsigned int param_2)
{
  *(unsigned int*)(param_1 + 0x44) = param_2;
  return;
}

/* Store the supplied unsigned 32-bit word at owner byte offset 0x 40. */
void func_L00_0042C360(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0x40) = param_2;
  return;
}


/* Store the supplied unsigned 32-bit word at owner byte offset 0x 40. */
void func_L00_0042C4B8(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0x40) = param_2;
  return;
}

/* Store the supplied unsigned 32-bit word at owner byte offset 0x 44. */
void func_L00_0042C608(int param_1, unsigned int param_2)
{
  *(unsigned int*)(param_1 + 0x44) = param_2;
  return;
}

void func_L00_0042C6C8(void)
{
}

/* Return the complete supplied unsigned-long 64-bit value unchanged. */
/* Target: FUN_003427B0 â€” identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long func_L00_0042C6D8(unsigned long param_1)
{
  return param_1;
}
