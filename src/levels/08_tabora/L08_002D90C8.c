#include "include_asm.h"

typedef unsigned int ti_word __attribute__((mode(TI)));

typedef float f32;

extern void func_2F9E60(void *, void *, f32);

extern void func_2F9DF0(void *, void *, void *);

extern f32 func_2F9FD0(void *, void *);

extern int *D_L08_001FE7C0[];

extern float func_00282E80(void *, void *);

extern float func_L08_0032EB48(ti_word *, int, float);

extern float func_L08_0032EC38(ti_word *, int, float);

extern float func_L08_0032ED98(ti_word *, int, float);

extern char D_L08_002A0D00[];

extern char *D_L08_001B2ACC __attribute__((sda));

extern char *D_L08_001B2AD4 __attribute__((sda));

extern char *D_L08_001B2ADC __attribute__((sda));

extern void func_L04_003A21F8(void *, int);

extern void func_L04_003A02A0(void *, int);

extern void func_0029FCC0(void *, int, void *);

INCLUDE_ASM("asm/levels", func_L08_00308888);

void func_L08_00329EC0(float value, float *object) {
    object[29] = 0.2f;
    object[28] = value - object[6];
}

f32 func_L08_0032EA60(char *a0, char *a1, char *a2, f32 f0, f32 f1, f32 f2, f32 f3) {
    f32 out[4];
    f32 t[4];
    f32 r;

    func_2F9E60(t, a1, f1);
    func_2F9DF0(out, a2, t);
    func_2F9E60(t, a1 + 0x10, f2);
    func_2F9DF0(out, out, t);
    func_2F9E60(t, a1 + 0x20, f3);
    func_2F9DF0(out, out, t);
    r = func_2F9FD0(a0, out);
    if (f0 < r) f0 = r;
    return f0;
}

float func_L08_0032EB48(ti_word *object, int index, float minimum) {
    char *entry;
    float a, b, c;

    if (index == -1) return minimum;
    entry = (char *)D_L08_001B2ACC + index * 128;
    for (c = -1.0f; c <= 1.0f; c += 1.0f)
        for (b = -1.0f; b <= 1.0f; b += 1.0f)
            for (a = -1.0f; a <= 1.0f; a += 1.0f)
                minimum = func_L08_0032EA60((char *)object, entry, entry + 0x30, minimum, a, b, c);
    return minimum;
}

float func_L08_0032EC38(ti_word *object, int index, float minimum) {
    char *entry;
    float x;

    if (index == -1) return minimum;
    entry = (char *)D_L08_001B2AD4 + index * 128;
    for (x = -1.0f; x <= 1.0f; x += 2.0f)
        minimum = func_L08_0032EA60((char *)object, entry, entry + 0x30, minimum, 0.0f, 0.0f, x);
    for (x = -1.0f; x <= 1.0f; x += 2.0f)
        minimum = func_L08_0032EA60((char *)object, entry, entry + 0x30, minimum, 0.0f, x, 0.0f);
    for (x = -1.0f; x <= 1.0f; x += 2.0f)
        minimum = func_L08_0032EA60((char *)object, entry, entry + 0x30, minimum, x, 0.0f, 0.0f);
    return minimum;
}

float func_L08_0032ED98(ti_word *object, int index, float minimum) {
    char *entry;
    float a, b, c;

    if (index == -1) return minimum;
    entry = (char *)D_L08_001B2ADC + index * 128;
    for (c = -1.0f; c <= 1.0f; c += 1.0f) {
        for (a = -1.0f; a <= 1.0f; a += 2.0f)
            minimum = func_L08_0032EA60((char *)object, entry, entry + 0x30, minimum, 0.0f, a, c);
        for (b = -1.0f; b <= 1.0f; b += 2.0f)
            minimum = func_L08_0032EA60((char *)object, entry, entry + 0x30, minimum, b, 0.0f, c);
    }
    return minimum;
}

float func_L08_0032EED8(ti_word *object, int index, float minimum) {
    int *list;
    int i;
    if (index == -1) return minimum;
    list = D_L08_001FE7C0[index];

    for (i = 0; i < *list; i++) {
        float value = func_00282E80((char *)(list + 4) + i * 0x10, object);
        if (minimum < value) minimum = value;
    }
    return minimum;
}

float func_L08_0032EF80(ti_word *input, int initial, int first, int second, int third) {
    ti_word value = *input;
    float result;
    result = func_L08_0032EED8(&value, initial, 0.0f);
    result = func_L08_0032EB48(&value, first, result);
    result = func_L08_0032EC38(&value, second, result);
    return func_L08_0032ED98(&value, third, result);
}

INCLUDE_ASM("asm/levels", func_L08_0032F898);

INCLUDE_ASM("asm/levels", func_L08_003CC750);

INCLUDE_ASM("asm/levels", func_L08_003CCC30);

INCLUDE_ASM("asm/levels", func_L08_003CCD80);

/* func_L08_003CFE68 is in the sibling file L08_002D90C8-g8.c (it uses $gp addresses). */

void func_L08_003CFFE8(void) {
    func_L04_003A21F8(D_L08_002A0D00, 7);
}

void func_L08_003D0010(void) {
    func_L04_003A02A0(D_L08_002A0D00, 7);
}

void func_L08_003D0040(void *object) {
    void **parts = *(void ***)((char *)object + 0x68);
    if (parts[0]) func_0029FCC0(object, 0, (char *)parts[0] + 0x10);
    if (parts[1]) func_0029FCC0(object, 1, (char *)parts[1] + 0x10);
}

INCLUDE_ASM("asm/levels", func_L08_003D00C8);

/* func_L08_003D0508 is defined in L08_003D0508-qcopy.c. */

INCLUDE_ASM("asm/levels", func_L08_003D2F50);



INCLUDE_ASM("asm/levels", func_L08_003D3EF8);

extern f32 func_3279B8(void);

extern f32 func_3278F0(f32, f32);

extern int func_327898(int, int);

extern f32 func_2FA3C8(f32);

extern f32 func_2FA3E0(f32);

extern void func_347A38(void *, int, int, f32, f32, int);

/* five draws of a random point around the object: a random angle and radius,
   the object's own position added, and the height the driver reads as the
   third component; each point goes to func_347A38 */
void func_L08_003D7E68(void *arg0) {
    f32 vec[4];
    f32 t;
    f32 f20, f21, f22, f23;
    void *s3;
    int count;
    int i;

    s3 = *(void **)((char *)arg0 + 0x68);
    i = 4;
    do {
        i--;
        f20 = func_3279B8();
        f21 = func_3278F0(0.0f, 0.8f);
        f23 = func_3278F0(0.0f, 3.5f);
        f22 = func_3278F0(3.5f, 8.7f);
        count = func_327898(100, 180);
        vec[0] = func_2FA3C8(f20) * f21;
        t = func_2FA3E0(f20) * f21;
        vec[2] = 0.0f;
        vec[1] = t;
        func_2F9DF0(vec, vec, (f32 *)((char *)arg0 + 0x10));
        vec[2] = *(f32 *)((char *)s3 + 0x434) + 0.025f;
        func_347A38(vec, 0x38002028, 0x2020, f23, f22, count);
    } while (i >= 0);
}


/* func_L08_003D8290 is defined in L08_003D8290-qcopy.c. */

