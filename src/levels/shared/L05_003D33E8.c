#include "include_asm.h"
#include "common.h"

extern char *func_0029EFD0(int);
extern char D_L05_001B96C0[];
extern void func_002AFFD8(void *, void *, int);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_L05_00425058(void *, void *);

/* Glow ring: four pulsing sprites along the actor's facing, each faded in. */
typedef int GlowRingVector __attribute__((mode(TI)));
extern unsigned char ref_L05_00426348_00[];
extern unsigned char ref_L05_004268E8_00[];
extern void func_00282CF0(float *, void *, float *);
extern void func_00282F20(float *, float *, float);

extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern u32 func_00283D38(u32, u32, float);
extern int func_00283CF0(float);

typedef struct { unsigned char pad[9]; unsigned char fade; } GlowRingSprite;
extern GlowRingSprite *func_002C2FD8(void *, u32, int, int, int, int, int, float);

typedef struct { float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowRingState;

typedef int TI128 __attribute__((mode(TI)));

extern char *D_L05_001B2614 __attribute__((sda));

extern int D_L05_00221D10[];

extern char *func_002ED688(char *object);

extern void func_L05_0037AEC0(char *object, int flag);

extern float func_002A7878(float a, float b);

extern float func_002A7940(void);

extern void func_002AF000(char *dst, float a, float b, float c);

extern void func_00282CC0(char *dst, char *src, char *src2);

extern int func_332AB8(int kind);

extern void func_L00_002E6EF8(void *, void *);

extern int ref_L05_00424780_00;

extern void func_0029F338(char *);

extern int func_00282978(char *);

extern int ref_L05_00424C88_00;

extern void ref_L05_00424C88_01(void *, void *);

extern float D_L05_0023F920[][4][137][4];
extern float D_L05_0024A460[][4][137];
extern float D_L05_0024D020[][4][4];
extern int D_L05_0024CFD0[][4], D_L05_0024CF30[][4], D_L05_0024CF80[][4];
extern float D_L05_001B2F58[] __attribute__((sda)), D_L05_001B2F88[] __attribute__((sda));
extern float D_L05_001B2FB8[] __attribute__((sda)), D_L05_001B2FD0[] __attribute__((sda));
extern int D_L05_001B2F70[] __attribute__((sda)), D_L05_001B2FE8[] __attribute__((sda));
extern int D_L05_001B2FA0[] __attribute__((sda));
extern int func_001163B0(void);
extern void func_00282C88(void *);

/* Clears the four emitters' 137 vectors of the object's slot, gives each a random speed, and
   starts the emitters around the object's position with random fades and lifetimes. */
void func_L05_003D33E8(char *obj)
{
    int *st = *(int **)(obj + 0x68);
    char *position = obj + 0x10;
    int i, j;
    float *v;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 137; j++) {
            float speed = func_002A7878(0.5f, 4.0f);

            func_00282C88(D_L05_0023F920[*st][i][j]);
            D_L05_0024A460[*st][i][j] = speed;
        }
        /* This slot and the actor position do not contain the private index. */
        qcopy_nc(D_L05_0024D020[*st][i], position);
        D_L05_0024CFD0[*st][i] = 6;
        D_L05_0024CF30[*st][i] = func_001163B0() % 128 + 128;
        D_L05_0024CF80[*st][i] = func_001163B0() % 2 + 6;
        {
            float jitter = func_002A7878(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)D_L05_0024D020 + offset);
            v[0] += jitter;
        }
        {
            float jitter = func_002A7878(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)D_L05_0024D020 + offset);
            v[1] += jitter;
        }
        {
            float jitter = func_002A7878(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)D_L05_0024D020 + offset);
            v[2] += jitter;
        }
    }
    D_L05_001B2F58[*st] = 0.01f;
    D_L05_001B2F70[*st] = 128;
    D_L05_001B2F88[*st] = 0.1f;
    D_L05_001B2FE8[*st] = 6;
    D_L05_001B2FA0[*st] = 128;
    D_L05_001B2FB8[*st] = 0.0f;
    D_L05_001B2FD0[*st] = 0.0f;
}


/* shared native body of family 5a97ab89858c */
void func_L05_00416630(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}


/* Spawns the object's effect: marks the object, takes one record of the shared
   128-byte table by the global index and gives it a random position. */
void func_L05_00417448(char *object)
{
    char *sub = *(char **)(object + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(object + 0x20) = 1;
    *(unsigned short *)(object + 0x34) = *(unsigned short *)(object + 0x34) | 0x100;
    *(int *)(func_002ED688(object) + 0x148) = 1;
    func_L05_0037AEC0(object, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x1C8) = 0x78;
    *(int *)(sub + 0x1C0) = -1;
    *(int *)(sub + 0x1C4) = -1;
    *(float *)(sub + 0x180) = 1.0f;
    a = func_002A7878(0.0f, *(float *)table);
    b = func_002A7940();
    c = func_002A7940();
    func_002AF000(object + 0x10, a, b, c);
    func_00282CC0(object + 0x10, table + 0x30, object + 0x10);
    *(int *)(sub + 0x1B8) = 0;
    *(float *)(object + 0x2C) = 0.02f;
}


INCLUDE_ASM("asm/levels", func_L05_00417D48);


/* func_L05_00418440 is matched in L05_00418440.c (built with -mno-split-addresses). */

extern void func_L05_0041C7E8(char *, int);

extern void func_L05_00432158(char *, int);

extern void func_002A10E8(int);

/* Walks the state's fifteen id fields: a live one is handed to the level's own
    helper together with the object, then to the shared one. */
void func_L05_00418508(char *a0)
{
    char *s0;

    s0 = *(char **)(a0 + 0x68);
    if (*(int *)(s0 + 0x40) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x40));
        func_002A10E8(*(int *)(s0 + 0x40));
    }
    if (*(int *)(s0 + 0x44) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x44));
        func_002A10E8(*(int *)(s0 + 0x44));
    }
    if (*(int *)(s0 + 0x48) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x48));
        func_002A10E8(*(int *)(s0 + 0x48));
    }
    if (*(int *)(s0 + 0x4C) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x4C));
        func_002A10E8(*(int *)(s0 + 0x4C));
    }
    if (*(int *)(s0 + 0x50) != 0) {
        func_L05_00432158(a0, *(int *)(s0 + 0x50));
        func_002A10E8(*(int *)(s0 + 0x50));
    }
    if (*(int *)(s0 + 0xAC) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0xAC));
        func_002A10E8(*(int *)(s0 + 0xAC));
    }
    if (*(int *)(s0 + 0x1F0) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x1F0));
        func_002A10E8(*(int *)(s0 + 0x1F0));
    }
    if (*(int *)(s0 + 0x1F4) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x1F4));
        func_002A10E8(*(int *)(s0 + 0x1F4));
    }
    if (*(int *)(s0 + 0x1F8) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x1F8));
        func_002A10E8(*(int *)(s0 + 0x1F8));
    }
    if (*(int *)(s0 + 0x1FC) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x1FC));
        func_002A10E8(*(int *)(s0 + 0x1FC));
    }
    if (*(int *)(s0 + 0x200) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x200));
        func_002A10E8(*(int *)(s0 + 0x200));
    }
    if (*(int *)(s0 + 0x204) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x204));
        func_002A10E8(*(int *)(s0 + 0x204));
    }
    if (*(int *)(s0 + 0x208) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x208));
        func_002A10E8(*(int *)(s0 + 0x208));
    }
    if (*(int *)(s0 + 0x274) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x274));
        func_002A10E8(*(int *)(s0 + 0x274));
    }
    if (*(int *)(s0 + 0x278) != 0) {
        func_L05_0041C7E8(a0, *(int *)(s0 + 0x278));
        func_002A10E8(*(int *)(s0 + 0x278));
    }
}
/* func_L05_004186D8 is defined in L05_004186D8-g8.c. */




/* func_L05_00419370 is defined in L05_00419370-g8.c. */

INCLUDE_ASM("asm/levels", func_L05_00419888);

INCLUDE_ASM("asm/levels", func_L05_00419CC8);

/* func_L05_00419F10 is defined in L05_00419F10-g8.c. */

void func_L05_0041A218(void)
{
    char buf[0x20];
}

INCLUDE_ASM("asm/levels", func_L05_0041A228);


/* func_L05_0041C1F0 is defined in L05_0041C1F0-g8.c. */

void func_L05_0041C410(char *object)
{
    char *state = *(char **)(object + 0x68);
    float *f = (float *)state;
    int *w;
    int i;
    int j;
    int v;

    for (i = 3; i >= 0; i--)
        *f++ = (float)func_332AB8(0xFF);
    *(float *)(state + 0x10) = -1.0f;
    *(float *)(state + 0x14) = -2.25f;
    *(float *)(state + 0x18) = 1.25f;
    *(float *)(state + 0x1C) = 2.5f;
    j = 3;
    w = (int *)(state + 0x2C);
    v = 0xFF;
    for (; j >= 0; j--) {
        *w = v;
        w = (int *)((char *)w - 4);
        v -= 0x40;
    }
    *(float *)(state + 0x30) = 3.0f;
    *(float *)(state + 0x34) = 3.7f;
    *(float *)(state + 0x3C) = 3.0f;
    *(float *)(state + 0x38) = 3.7f;
}





/* func_L05_0041D570 is defined in L05_003D33E8-g8.c (it reaches D_L05_001B1348 through $gp). */

void func_L05_0041D728(char *object)
{
    char *state = *(char **)(object + 0x68);
    float *f = (float *)state;
    int *w;
    int i;
    int j;
    int v;

    for (i = 3; i >= 0; i--)
        *f++ = (float)func_332AB8(0xFF);
    *(float *)(state + 0x10) = -1.0f;
    *(float *)(state + 0x14) = -2.25f;
    *(float *)(state + 0x18) = 1.25f;
    *(float *)(state + 0x1C) = 2.5f;
    j = 3;
    w = (int *)(state + 0x2C);
    v = 0xFF;
    for (; j >= 0; j--) {
        *w = v;
        w = (int *)((char *)w - 4);
        v -= 0x40;
    }
    *(float *)(state + 0x30) = 2.8f;
    *(float *)(state + 0x34) = 3.5f;
    *(float *)(state + 0x3C) = 2.8f;
    *(float *)(state + 0x38) = 3.5f;
}


/* func_L05_0041ED18 is defined in L05_0041ED18-g8.c. */


/* func_L05_00421908 is in L05_003D33E8-reward-g8.c: -G8, with its own jump table. */

void func_L05_00424780(char *object)
{
    char *state = *(char **)(object + 0x68);

    if (*(int *)(state + 0xC) != 0)
        func_L00_002E6EF8(&ref_L05_00424780_00, object);
    *(unsigned short *)(object + 0x34) |= 0x41;
}

#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)
extern void ref_L05_004247C8_00(char *, void *);
extern char ref_L05_004247C8_01[];
extern float ref_L05_004247C8_02(void);
extern float ref_L05_004247C8_03(float);
extern float ref_L05_004247C8_04(float);
extern void ref_L05_004247C8_05(float *, float *, char *);
extern void ref_L05_004247C8_06(float *, float *, char *);
extern int ref_L05_004247C8_07(float);
extern void ref_L05_004247C8_08(float *, int, int, int, float, float, float);
extern float ref_L05_004247C8_09(float, float);
extern float ref_L05_004247C8_10(float);

void func_L05_004247C8(char *obj) {
    float v[4];
    char *state;
    int color;
    int grey;
    int i;
    float full;

    full = 128.0f;
    grey = 0x808080;
    state = FLD(obj, char *, 0x68);
    ref_L05_004247C8_00(obj + 0x10, ref_L05_004247C8_01);
    for (i = 29; i >= 0; i--) {
        float angle = ref_L05_004247C8_02();
        v[0] = 0.0f;
        v[1] = ref_L05_004247C8_03(angle);
        v[2] = -ref_L05_004247C8_04(angle);
        ref_L05_004247C8_05(v, v, obj + 0xC0);
        ref_L05_004247C8_06(v, v, obj + 0x10);
        ref_L05_004247C8_08(v, 0x13, (ref_L05_004247C8_07(full) << 24) | grey, 1, 0.25f, 0.1f, ref_L05_004247C8_02());
        {
            float half = 0.5f;
            int alpha = ref_L05_004247C8_07(full * half);
            color = FLD(state, int, 8);
            color &= 0xFFFFFF;
            color |= alpha << 24;
            ref_L05_004247C8_08(v, 0x13, color, 1, half, 0.1f, ref_L05_004247C8_02());
        }
    }
    FLD(state, float, 4) = 0.13380859792232513f;
    FLD(state, float, 0) = ref_L05_004247C8_09(FLD(state, float, 0), 0.13380859792232513f);
    ref_L05_004247C8_10(FLD(state, float, 0));
}

void func_L05_00424970(char *object, int value)
{
    char *state = *(char **)(object + 0x68);

    *(int *)(state + 0x8) = value;
}

void func_L05_00424980(char *object, int value)
{
    char *state = *(char **)(object + 0x68);

    *(int *)(state + 0xC) = value;
}

/* Creates a camera-facing burst, sets its lifetime and colors, and shakes
   the camera when a visible burst is nearby. */
char *func_L05_00424990(void *pos, int shake, int c20, int c24, int c28,
                         int c2c, int c30, int unused, int c34, int mode,
                         int c38, float scale)
{
    float toward[4], up[4], sphere[4], cameraDir[4];
    char *obj = func_0029EFD0(0x116A);
    char *st;

    if (obj) {
        st = *(char **)(obj + 0x68);
        *(unsigned char *)(obj + 0x30) = 255;
        *(unsigned short *)(obj + 0x32) = 255;
        obj[0x20] = 0;
        qcopy(obj + 0x10, pos);
        *(float *)(obj + 0x1C) = 1.0f;
        func_00282CF0(toward, D_L05_001B96C0, (float *)(obj + 0x10));
        func_00282F20(toward, toward, 1.0f);
        func_002AFFD8(obj + 0x10, up, 1);
        qcopy(obj + 0xC0, toward);
        func_00282DD8(obj + 0xD0, obj + 0xC0, up);
        func_00282F20((float *)(obj + 0xD0), (float *)(obj + 0xD0), 1.0f);
        func_00282DD8(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
        *(short *)st = 60;
        *(short *)(st + 2) = 60;
        *(float *)(st + 8) = scale + scale;
        *(float *)(st + 0xC) = scale * 4.0f;
        *(int *)(st + 0x20) = c20;
        *(int *)(st + 0x24) = c24;
        *(int *)(st + 0x28) = c28;
        *(int *)(st + 0x2C) = c2c;
        *(int *)(st + 0x30) = c30;
        *(int *)(st + 0x34) = c34;
        *(int *)(st + 0x1C) = mode;
        *(int *)(st + 0x38) = c38;
        *(float *)(st + 0x14) = scale;
        *(int *)(st + 0x18) = 0;
        qcopy(sphere, obj + 0x10);
        sphere[3] = scale * 3.0f;
        if (func_00283DB8(sphere, 128.0f) == 1) {
            *(short *)(st + 4) = 10;
            *(float *)(st + 0x10) = 0.1f;
            if (func_00282E48(pos, D_L05_001B96C0) < 48.0f && shake) {
                char *mgr = D_L05_001B96C0 - 0x140;

                *(int *)(mgr + 0x16C) = 0;
                *(int *)(mgr + 0x168) = 40;
                *(float *)(mgr + 0x160) = 0.075f;
            }
            if (*(int *)(st + 0x18)) {
                func_00282CF0(cameraDir, obj + 0x10, (float *)D_L05_001B96C0);
                func_00282F20(cameraDir, cameraDir, 1.0f);
                if (1.5707964f - func_002831B0(func_00282DB0(cameraDir, D_L05_001B96C0 + 0x230)) < 0.45378566f)
                    *(int *)(st + 0x18) = 1;
                else
                    *(int *)(st + 0x18) = 0;
            }
        } else {
            *(short *)(st + 4) = 0;
            *(int *)(st + 0x18) = 0;
        }
        func_L05_00425058(obj, up);
    }
    return obj;
}

void func_L05_00424C88(char *object)
{
    char *state = *(char **)(object + 0x68);

    if (func_00282978(state) == 0) {
        func_00282978(state + 4);
        ref_L05_00424C88_01(&ref_L05_00424C88_00, object);
    } else {
        func_0029F338(object);
    }
}


/* func_L05_00425058 is defined in L05_00425058-g8.c. */


/* func_L05_004260B8 is defined in L05_003D33E8-g8.c (it reaches D_L05_001B14FC through $gp). */

void func_L05_00426270(char *object)
{
    char *state = *(char **)(object + 0x68);
    float *f = (float *)state;
    int *w;
    int i;
    int j;
    int v;

    for (i = 3; i >= 0; i--)
        *f++ = (float)func_332AB8(0xFF);
    *(float *)(state + 0x10) = -1.0f;
    *(float *)(state + 0x14) = -2.25f;
    *(float *)(state + 0x18) = 1.25f;
    *(float *)(state + 0x1C) = 2.5f;
    j = 3;
    w = (int *)(state + 0x2C);
    v = 0xFF;
    for (; j >= 0; j--) {
        *w = v;
        w = (int *)((char *)w - 4);
        v -= 0x40;
    }
    *(float *)(state + 0x30) = 2.4f;
    *(float *)(state + 0x34) = 3.0f;
    *(float *)(state + 0x3C) = 2.4f;
    *(float *)(state + 0x38) = 3.0f;
}

void func_L05_00426348(unsigned char *a0)
{
    GlowRingState *st = *(GlowRingState **)(a0 + 0x68);
    float m[4];
    float q[4];
    float src[4];
    int i;

    *(GlowRingVector *)src = *(GlowRingVector *)(a0 + 0x10);
    src[2] += 0.25f;
    func_00282CF0(m, ref_L05_00426348_00, src);
    func_00282F20(m, m, -0.3f);
    func_00282F20(q, m, 0.1f);
    func_00282CC0((char *)m, (char *)m, (char *)src);

    for (i = 0; i < 4; i++) {
        float v = st->phase[i] + st->rate[i];
        u32 color;
        GlowRingSprite *s;
        st->phase[i] = v;
        if (v >= 255.0f)
            st->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            st->phase[i] = v + 255.0f;
        if (func_00282948(&st->alpha[i]))
            st->alpha[i] = 0xFF;
        v = func_00282C48(0.5f - func_00283CE0(0xFF - st->alpha[i]) * 0.0039215689f);
        color = func_00283D38(0x502020FF, 0x102020FF, v);
        s = func_002C2FD8(m, color, func_00283CF0(st->phase[i]) & 0xFF, 0x35, 1, 2, 0, st->size[i]);
        if (s)
            s->fade = func_00283CF0(1.0f) + 0x60;
        func_00282CC0((char *)m, (char *)m, (char *)q);
    }
}


INCLUDE_ASM("asm/levels", func_L05_00426568);

/* func_L05_00426658 is defined in L05_003D33E8-g8.c (it reaches D_L05_001B1500 through $gp). */

void func_L05_00426810(char *object)
{
    char *state = *(char **)(object + 0x68);
    float *f = (float *)state;
    int *w;
    int i;
    int j;
    int v;

    for (i = 3; i >= 0; i--)
        *f++ = (float)func_332AB8(0xFF);
    *(float *)(state + 0x10) = -1.0f;
    *(float *)(state + 0x14) = -2.25f;
    *(float *)(state + 0x18) = 1.25f;
    *(float *)(state + 0x1C) = 2.5f;
    j = 3;
    w = (int *)(state + 0x2C);
    v = 0xFF;
    for (; j >= 0; j--) {
        *w = v;
        w = (int *)((char *)w - 4);
        v -= 0x40;
    }
    *(float *)(state + 0x30) = 2.0f;
    *(float *)(state + 0x34) = 2.5f;
    *(float *)(state + 0x3C) = 2.0f;
    *(float *)(state + 0x38) = 2.5f;
}

void func_L05_004268E8(unsigned char *a0)
{
    GlowRingState *st = *(GlowRingState **)(a0 + 0x68);
    float m[4];
    float q[4];
    float src[4];
    int i;

    *(GlowRingVector *)src = *(GlowRingVector *)(a0 + 0x10);
    src[2] += 0.25f;
    func_00282CF0(m, ref_L05_004268E8_00, src);
    func_00282F20(m, m, -0.3f);
    func_00282F20(q, m, 0.1f);
    func_00282CC0((char *)m, (char *)m, (char *)src);

    for (i = 0; i < 4; i++) {
        float v = st->phase[i] + st->rate[i];
        u32 color;
        GlowRingSprite *s;
        st->phase[i] = v;
        if (v >= 255.0f)
            st->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            st->phase[i] = v + 255.0f;
        if (func_00282948(&st->alpha[i]))
            st->alpha[i] = 0xFF;
        v = func_00282C48(0.5f - func_00283CE0(0xFF - st->alpha[i]) * 0.0039215689f);
        color = func_00283D38(0x50207FFF, 0x10207FFF, v);
        s = func_002C2FD8(m, color, func_00283CF0(st->phase[i]) & 0xFF, 0x35, 1, 2, 0, st->size[i]);
        if (s)
            s->fade = func_00283CF0(1.0f) + 0x60;
        func_00282CC0((char *)m, (char *)m, (char *)q);
    }
}



/* func_L05_00426BE0 is defined in L05_003D33E8-g8.c (it reaches D_L05_001B1504 through $gp). */

void func_L05_00426D98(char *object)
{
    char *state = *(char **)(object + 0x68);
    float *f = (float *)state;
    int *w;
    int i;
    int j;
    int v;

    for (i = 3; i >= 0; i--)
        *f++ = (float)func_332AB8(0xFF);
    *(float *)(state + 0x10) = -1.0f;
    *(float *)(state + 0x14) = -2.25f;
    *(float *)(state + 0x18) = 1.25f;
    *(float *)(state + 0x1C) = 2.5f;
    j = 3;
    w = (int *)(state + 0x2C);
    v = 0xFF;
    for (; j >= 0; j--) {
        *w = v;
        w = (int *)((char *)w - 4);
        v -= 0x40;
    }
    *(float *)(state + 0x30) = 2.5f;
    *(float *)(state + 0x34) = 3.2f;
    *(float *)(state + 0x3C) = 2.5f;
    *(float *)(state + 0x38) = 3.2f;
}



INCLUDE_ASM("asm/levels", func_L05_00427238);

/* func_L05_004276E8 is defined in L05_004276E8-g8.c. */



/* func_L05_00427B20 is defined in L05_00427B20.c. */

/* func_L05_00427E10 lives in L05_00427E10-g8.c. */
