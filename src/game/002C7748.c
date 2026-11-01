#include "include_asm.h"
#include "common.h"

extern float func_002A7790(float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00283D38(int, int, float);
extern void func_00300190(char *, char *);
extern int func_00282978(char *);
extern void func_002B9180(char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282D30(char *, char *, float);
extern void func_00282F20(float *, float *, float);

typedef struct { char pad[0x20]; int buffer; char pad24[0xAC]; int saved; } CaptureState;
extern int D_001B1598 MACRO_ADDR __attribute__((sda));
extern int D_001A7344 MACRO_ADDR __attribute__((sda));
extern int D_001A72D4 __attribute__((sda));
extern void func_002FC3C0(int);
extern void func_0011AEA0(int);

extern int F250fbfa4_FUN_00282978(char *p);

extern void F250fbfa4_FUN_002B9180(char *p);

extern void F250fbfa4_FUN_00282CC0(char *p0, char *p1, char *p2);

extern int Ff4dd22f3_FUN_00282978(char *p);

extern void Ff4dd22f3_FUN_002B9180(char *p);

extern void Ff4dd22f3_FUN_00282CC0(char *p, char *q, float *v);

extern int Fc40b1162_FUN_00282978();

extern void Fc40b1162_FUN_002B9180();

extern void Fbdd4a4aa_FUN_00300190(char *a, char *b);

extern void Fbdd4a4aa_FUN_00282CC0(char *a, char *b, char *c);

extern void Fbdd4a4aa_FUN_00282D30(char *a, char *b, float f);

extern void Fbdd4a4aa_FUN_002FE8D8(char *a, char *b);

extern int Fbdd4a4aa_FUN_00283D38(unsigned int a, int b, float f);

extern void Fbdd4a4aa_FUN_002B9180(char *a);

/* Frozen Batch A A15-struct-pad-20; acknowledged claim 6d4515f9ca5619f8d02349c6c2ad116dc989f5a4c317c4d31105f9a9271aa080. */
typedef unsigned char BatchA_A15_u8;

typedef unsigned int BatchA_A15_u32;

extern BatchA_A15_u8 D_L15_001FF640[];

/* Frozen Batch A A10-twin-base-32; acknowledged claim b588059f8808a6607867ee41ec367b24cfb85d2f4cc33273a4392842e34233d5. */
typedef unsigned char BatchA_A10_u8;

typedef unsigned int BatchA_A10_u32;

extern BatchA_A10_u8 D_L03_001FF8C0[];

extern BatchA_A10_u8 D_L03_001FFAC0[];

extern int func_00288FB8_1 ();

extern void func_0027F5B8 (int v, int p7, long k, int r, int m1);

extern void func_0027FA10 (int v, int p7, long k, int r, int m1);

typedef int BatchA_A12_s32;

typedef struct { BatchA_A12_s32 a; BatchA_A12_s32 b; } BatchA_A12_BatchA24;

extern BatchA_A12_BatchA24 D_L08_001FF980;

/*
 * Disassembled at 0x002cd220
 * Signature: int FUN_002cd220(void)
 * Behavior:
 *   - Saves RA on stack
 *   - Calls func_0027C540(0)
 *   - Calls func_0029C138()
 *   - Calls func_0027C660()
 *   - Restores RA from stack
 *   - Returns 0
 */
extern void func_0027C540(long);
extern void func_0029C138(void);

extern void func_0027C660(void);


/*
 * Function: func_002D2EE0
 *
 * Disassembly summary:
 * - Saves return address on stack
 * - Calls func_0027C540(0) (with zero argument)
 * - Calls func_0029C7A0()
 * - Calls func_0027C660()
 * - Restores return address
 * - Returns 0
 *
 * Notes:
 * - The function follows standard MIPS ABI prologue/epilogue.
 * - Delay slots are filled with NOP or argument setup as seen in disassembly.
 * - No local variables used.
 * - All external function addresses come from the assigned externals list.
 */


/* External functions declared with exact aliases from task.externals */

/* func_002C7E28 is defined in 002C7E28-qcopy.c. */

/* func_002C7F78 is defined in 002C7F78.c. */

extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283C80(float, float);
extern float func_00282C48(float);

extern float Fbdd4a4aa_FUN_002A89A8(char *a, int b, float f);

extern float Fbdd4a4aa_FUN_00283B98(float a, float b);

extern float Fbdd4a4aa_FUN_00283198(float a);

extern void Fbdd4a4aa_FUN_00282F20(char *a, char *b, float f);

extern float Fbdd4a4aa_FUN_00283CE0(int a);

extern int Fbdd4a4aa_FUN_00283CF0(float a);

extern int D_001B1688 __attribute__((sda));

extern char D_001B5200[];

extern float func_002A7878(float a, float b);
extern void func_00300248(char *a, char *b);

extern void func_00282D08(float *out, float *a, float *b, float t);
extern void func_00282CF0(float *out, float *a, float *b);
extern float func_00282E20(float *v);
extern float func_00283248(float y, float x);

extern int D_001F2A30;

extern char *D_001A8CFC[] __attribute__((sda));
extern void func_00339770(void *, int);

extern char D_001F2840[];

/* func_002C9C60 is matched in 002C9C60.c (built with -g). */

extern int D_001A8BB0 __attribute__((sda));
extern int D_001A7A08 __attribute__((sda));
extern char D_00259918[];
extern char D_00259AF8[];
extern char D_00259AA8[];
extern int D_001A79F0 __attribute__((sda));
extern int D_0025B5F8;
extern void func_00132AF8(int);
extern void func_002B72E8(int);
extern int func_00132028(void);
extern void func_002CAF18(void);
extern void func_00295C50(int);
extern int func_0029D830(void);
extern void func_002DF050(void);

typedef struct {
    char pad[0x38];
    char *next;
    char *previous;
} Links_2C9CF8;

typedef struct {
    int f0, pad4, f8;
    char padC[0x10];
    int f1C, f20;
    char pad24[0xB7];
    char byteDB;
    char padDC[0xC];
    int fE8;
    char padEC[0x18];
    unsigned int f104;
    int f108;
    char pad10C[0x14];
    int f120;
    char pad124[0x20];
    int f144, f148, f14C, f150;
    char pad154[0x6C];
    int f1C0, f1C4, f1C8;
} State_2C9CF8;

/* Uploads the saved screen image back to VRAM in 0x4000-byte strips (0x600 bytes per
   line of the current height), from the start buffer or, when a0 is set, ending at
   0x3FB000, after setting the restore mode (2 with a0, else 1) and bumping the frame
   counter. */
typedef struct { long q[12]; } GsLoadImage2C9E60 __attribute__((aligned(16)));
extern int func_001261F0(int);
extern int func_00126288(GsLoadImage2C9E60 *, short, short, short, short, short, short, short);
extern int func_001265B0(GsLoadImage2C9E60 *, void *);
extern int func_001244B8(int, int);

extern void func_002CA070(void);
extern unsigned int D_L00_001FEC40[2];

extern void func_0027DDC0(int, int, int, int);

/* func_002CAB00 is defined in 002CAB00-g8.c. */

extern short D_001A63AC;
extern int D_001C51D0;
extern int D_00239BA0[];
extern unsigned char D_00139568[];
extern int func_002B4B70(int, int);
extern int func_002B49E0(int, int, int, int, void *);
extern void func_002B7CE0(int);
extern void func_00294420(int);

typedef struct {
    char pad00[0x1C];
    int mode;
    char pad20[0x04];
    volatile int count;
    char pad28[0x08];
    int field30;
    char pad34[0x0C];
    int field40;
    char pad44[0xB0];
    int fieldF4;
} GameState_1F2840;

extern int func_002D5B38(int, char *);
extern char D_0025BA90[];

extern short D_0018A000[];
extern void func_0029CE80(void);

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState_2CC490;

typedef struct {
    char reserved00[0x1C4];
    int flags;
} GameState_2CC490;

extern char D_00138180[];

/* The menu entries are 0x50 apart; D_001B1680 holds the selection and D_001A8B84
 * whether it is enabled. Both scalars and the enable flags are small data: the
 * -G0 compiler addresses them absolutely, and $gp-relative only in delay slots. */
typedef struct { char pad[0x1C4]; int flags; } InputState_2CCF68;
typedef struct { short x, kind; int a, b; } MenuEntry_2CCF68;
extern char D_00259148[], D_00259198[], D_002591E8[], D_00259238[], D_00259288[], D_002592D8[];
extern int func_002D5EC0(char *);
extern int D_001A8B84 __attribute__((sda));
extern int D_001B1680 __attribute__((sda));
typedef struct { unsigned char value; } ResidentFlag_2CCF68;
extern ResidentFlag_2CCF68 D_001A7BC9 __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCA __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCB __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCC __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCE __attribute__((sda));

extern int D_00138344;

extern int func_0029C168(int);

extern unsigned int func_0026F7C8(void);

extern unsigned int func_0026F7D0(void);

extern unsigned int func_0026F7D8(void);

extern unsigned int func_0026F7E0(void);

extern unsigned int func_0026F7E8(void);

extern unsigned int func_0026F7F0(void);

extern int func_002CB7D0(int);

extern int func_002CB820(int);

extern int func_002CB8A0(int);

extern int func_002CB950(int);

extern void func_002E5E58(int, unsigned int, void *);

typedef struct {
    char reserved00[0x44];
    int state;
    char reserved48[0x8];
    int handle;
    int last;
    int current;
} MenuObject_2CD4E0;

typedef struct {
    char reserved00[0x10];
    int flags;
} ToggleState_2CD4E0;

extern MenuObject_2CD4E0 D_00259C78;
extern ToggleState_2CD4E0 *D_00259C44;
extern int func_0029C248(int first, void *second);
extern int func_00336EF0(void);

/* func_002C7748 is defined in 002C7748-create-g8.c. */

void func_002C7AE8(char *a0)
{
    char local[16];
    char *s1 = a0;
    char *s0;
    int a1;
    int v1;
    char *p;

    if (F250fbfa4_FUN_00282978(a0 + 10) != 0) {
        F250fbfa4_FUN_002B9180(a0);
        return;
    }
    s0 = a0 + 32;
    a1 = *(int *)(s1 + 4);
    v1 = (a1 >> 24) + *(unsigned char *)(s0 + 20);
    *(int *)(s1 + 4) = (a1 & 0x00ffffff) | (v1 << 24);
    p = s1 + 16;
    *(float *)(local + 0) = *(float *)(s1 + 32);
    *(float *)(local + 4) = *(float *)(s0 + 4);
    *(float *)(local + 8) = *(float *)(s0 + 8);
    *(int *)(local + 12) = 0;
    F250fbfa4_FUN_00282CC0(p, p, local);
    *(float *)(s0 + 8) = *(float *)(s0 + 8) - *(float *)(s0 + 12);
    *(unsigned char *)(s1 + 8) = *(unsigned char *)(s1 + 8) + *(unsigned char *)(s0 + 21);
    *(float *)(s1 + 12) = *(float *)(s1 + 12) + *(float *)(s0 + 16);
}

/* func_002C7BB8 is defined in 002C7BB8.c. */

void func_002C7D58(char *self)
{
    char *p = self + 32;
    float v[4];
    int a1;

    if (Ff4dd22f3_FUN_00282978(self + 10) != 0)
    {
        Ff4dd22f3_FUN_002B9180(self);
        return;
    }

    a1 = *(int *)(self + 4);
    *(int *)(self + 4) = (a1 & 0xffffff) | (((a1 >> 24) + (int)*(unsigned char *)(p + 20)) << 24);
    v[0] = *(float *)(self + 32);
    v[1] = *(float *)(p + 4);
    v[2] = *(float *)(p + 8);
    v[3] = 0.0f;
    Ff4dd22f3_FUN_00282CC0(self + 16, self + 16, v);
    *(unsigned char *)(self + 8) += *(unsigned char *)(p + 21);
    *(float *)(self + 12) += *(float *)(p + 16);
    *(float *)(p + 8) -= *(float *)(p + 12);
}

void func_002C8348(char *a0)
{
    char *s1 = a0;
    char *s0 = s1 + 0x20;
    float t;

    *(u8 *)(s1 + 8) = *(u8 *)(s1 + 8) + *(u8 *)(s0 + 0x14);
    *(float *)(s0 + 8) = func_00283B98(*(float *)(s0 + 8), *(float *)(s0 + 0xC));
    *(float *)(s1 + 0xC) = *(float *)(s1 + 0xC) + *(float *)(s0 + 0x10);
    *(float *)(s1 + 0x10) = *(float *)(*(char **)(s1 + 0x20)) +
                            *(float *)(s0 + 4) * func_00283180(*(float *)(s0 + 8));
    *(float *)(s1 + 0x18) = *(float *)(*(char **)(s1 + 0x20) + 8) +
                            *(float *)(s0 + 4) * func_00283198(*(float *)(s0 + 8));
    t = func_00283C80(*(float *)(s0 + 8), *(float *)(*(char **)(s1 + 0x20) + 0x10));
    if (t < func_00282C48(*(float *)(s0 + 0xC) + *(float *)(s0 + 0xC)))
        func_002B9180(s1);
}

void func_002C8428(char *obj)
{
    char *s1 = obj;
    char *s0 = obj + 0x20;
    char *s2;
    char local[16];
    float f20;
    float f1;
    float f2;

    Fbdd4a4aa_FUN_00282D30(s0, s0, 0.9f);
    s2 = obj + 0x10;
    f20 = Fbdd4a4aa_FUN_002A89A8(s2, 0, 0.5f) + 0.25f;
    if (f20 < *(float *)(s1 + 0x18)) {
        *(float *)(s0 + 8) = *(float *)(s0 + 8) - *(float *)(s0 + 12);
        *(unsigned char *)(s1 + 8) = *(unsigned char *)(s1 + 8) + *(unsigned char *)(s0 + 22);
    }
    Fbdd4a4aa_FUN_00282CC0(s2, s2, s0);
    if (D_001B1688 % 10 == 0) {
        if (f20 < *(float *)(s1 + 0x18)) {
            *(float *)(s0 + 0x1C) = Fbdd4a4aa_FUN_00283B98(*(float *)(s0 + 0x1C), 1.0f);
            f2 = Fbdd4a4aa_FUN_00283198(*(float *)(s0 + 0x1C));
            Fbdd4a4aa_FUN_00282F20(local, D_001B5200, f2 * 0.0075f);
            Fbdd4a4aa_FUN_00282CC0(s0, s0, local);
        }
    }
    if (*(short *)(s1 + 0xA) < *(short *)(s0 + 0x14)) {
        f1 = Fbdd4a4aa_FUN_00283CE0(*(short *)(s1 + 0xA));
        f2 = Fbdd4a4aa_FUN_00283CE0(*(short *)(s0 + 0x14));
        *(int *)(s1 + 4) = (Fbdd4a4aa_FUN_00283CF0(f1 / f2 * 128.0f) << 24) | 0x00050505;
    } else {
        *(int *)(s1 + 4) = 0x9F050505;
    }
    if (F250fbfa4_FUN_00282978(s1 + 0xA)) {
        Fbdd4a4aa_FUN_002B9180(s1);
    }
}

void func_002C85D8(char *p)
{
    if (Fc40b1162_FUN_00282978(p + 10)) {
        Fc40b1162_FUN_002B9180(p);
    }
}

/* func_002C8610 is in 002C8610.c. */

void func_002C87B0(char *a0)
{
    char local[16];
    char *s1 = a0;
    char *s0;
    int a1;
    int v1;
    char *p;

    if (F250fbfa4_FUN_00282978(a0 + 10) != 0) {
        F250fbfa4_FUN_002B9180(a0);
        return;
    }
    s0 = a0 + 32;
    a1 = *(int *)(s1 + 4);
    v1 = (a1 >> 24) + *(unsigned char *)(s0 + 20);
    *(int *)(s1 + 4) = (a1 & 0x00ffffff) | (v1 << 24);
    p = s1 + 16;
    *(float *)(local + 0) = *(float *)(s1 + 32);
    *(float *)(local + 4) = *(float *)(s0 + 4);
    *(float *)(local + 8) = *(float *)(s0 + 8);
    *(int *)(local + 12) = 0;
    F250fbfa4_FUN_00282CC0(p, p, local);
    *(float *)(s0 + 8) = *(float *)(s0 + 8) - *(float *)(s0 + 12);
    *(unsigned char *)(s1 + 8) = *(unsigned char *)(s1 + 8) + *(unsigned char *)(s0 + 21);
    *(float *)(s1 + 12) = *(float *)(s1 + 12) + *(float *)(s0 + 16);
}

/* func_002C8A38 is defined in 002C8A38.c. */

/* Like func_002C8A38 with a second vector at +0x30 scaled into the motion. Its
 * address e is an integer: retail loads that vector's last two words only after
 * the first vector is stored, the order alias analysis gives an untraced base. */
void func_002C8CA0(char *p)
{
    char *d = p + 32;
    int e = (int)p + 48;
    float scaled[4], v[4], w[4], tmp[4];
    int color, alpha, fading, spin;
    float size0, size1, speed0, speed1, scale, t, inverse, a, b;
    v[3] = 0;
    v[0] = *(float *)(d + 0); v[1] = *(float *)(d + 4); v[2] = *(float *)(d + 8);
    w[0] = *(float *)(e + 0); w[1] = *(float *)(e + 4); w[2] = *(float *)(e + 8); w[3] = 0;
    color = *(unsigned char *)(d + 12) & 15;
    alpha = (*(unsigned char *)(d + 12) >> 4) | 0x70;
    color |= (color << 16) | (color << 8);
    spin = *(unsigned char *)(d + 13) >> 4;
    fading = *(unsigned char *)(d + 13) & 15;
    size0 = func_00283CE0(*(unsigned char *)(d + 30)) * 1640.625f;
    size1 = func_00283CE0(*(unsigned char *)(d + 31)) * 1640.625f;
    speed0 = func_00283CE0(*(unsigned char *)(d + 28)) * (1.0f / 128);
    speed1 = func_00283CE0(*(unsigned char *)(d + 29)) * (1.0f / 128);
    scale = func_00283CE0(*(unsigned char *)(d + 15)) * (1.0f / 128);
    func_00300190(p + 16, p + 16);
    t = func_00283CE0(*(short *)(p + 10));
    t /= func_00283CE0(*(unsigned char *)(d + 14)); inverse = 1.0f - t;
    if (!fading) {
        *(int *)(p + 4) = func_00283D38(0x103080, color, inverse) | (alpha << 24);
        *(float *)(p + 12) = size0 + (size1 - size0) * inverse;
        speed0 += (speed1 - speed0) * inverse;
        func_00282D30((char *)scaled, (char *)w, scale * func_002A7790(inverse));
    } else {
        speed0 = speed1;
        a = func_00283CE0(alpha); b = func_00283CE0(alpha);
        b *= func_002A7790(inverse);
        *(int *)(p + 4) = color | (func_00283CF0(a - b) << 24);
        func_00282D30((char *)scaled, (char *)w, scale);
    }
    func_00282F20(tmp, v, speed0);
    func_00282CC0(p + 16, p + 16, (char *)tmp);
    func_00282CC0(p + 16, (char *)scaled, p + 16);
    *(unsigned char *)(p + 8) += spin;
    if (func_00282978(p + 10)) {
        if (!fading) {
            *(unsigned char *)(d + 14) = 20;
            *(unsigned char *)(d + 13) |= 1;
            *(short *)(p + 10) = 20;
        } else func_002B9180(p);
    }
}

void func_002C8F40(int *obj)
{
    char *a = (char *)obj + 16;
    char *b = (char *)obj + 32;
    char tmp[16];

    Fbdd4a4aa_FUN_00300190(a, a);
    *(int *)(b + 16) = *(int *)(b + 16) - 1;
    if (*(int *)(b + 16) < 0)
        *(int *)(b + 16) = 0;
    *(unsigned char *)((char *)obj + 8) = *(unsigned char *)((char *)obj + 8) + 1;
    Fbdd4a4aa_FUN_00282CC0(a, b, a);
    *(float *)((char *)obj + 12) = *(float *)((char *)obj + 12) + 1.5750000000000000000000e+03f;
    Fbdd4a4aa_FUN_00282D30(b, b, 9.9000000953674316406250e-01f);
    Fbdd4a4aa_FUN_002FE8D8(a, tmp);
    if ((*(int *)((char *)obj + 4) & 0xFF) < 32) {
        Fbdd4a4aa_FUN_00282D30(tmp, tmp, 1.5000000130385160446167e-03f);
        Fbdd4a4aa_FUN_00282CC0(b, b, tmp);
    } else {
        Fbdd4a4aa_FUN_00282D30(tmp, tmp, -7.5000000651925802230835e-04f);
        Fbdd4a4aa_FUN_00282CC0(b, b, tmp);
    }
    *(int *)((char *)obj + 4) = Fbdd4a4aa_FUN_00283D38(*(unsigned int *)((char *)obj + 4) & 0x00FFFFFF, 0, 2.5000000372529029846191e-02f)
        | (*(int *)(b + 16) << 24);
    if (*(int *)(b + 16) == 0)
        Fbdd4a4aa_FUN_002B9180((char *)obj);
}

void func_002C9098(char *p)
{
    char *s0 = p + 32;
    char *s3 = p + 16;
    float r1, r2, r3, r4;
    int x, y;

    r1 = func_00283CE0(*(short *)(p + 10));
    r2 = func_00283CE0(*(int *)(s0 + 24));
    r1 = r1 / r2;
    r3 = func_00283CE0(*(int *)(s0 + 16));
    x = func_00283CF0(r3 * r1);
    y = func_00283D38(0, *(int *)(s0 + 20), r1 * 0.5f);
    *(char *)(p + 8) = *(unsigned char *)(p + 8) + 1;
    r4 = func_002A7878(0.004f, 0.012f);
    *(float *)(p + 12) = *(float *)(p + 12) + r4 * 210000.0f;
    func_00282CC0(s3, s3, s0);
    func_00282D30(s0, s0, 0.99f);
    func_00300190(s3, s3);
    func_00300248(s0, s0);
    *(int *)(p + 4) = y | (x << 24);
    if (func_00282978(p + 10) != 0) {
        func_002B9180(p);
    }
}

/* func_002C9218 is defined in 002C9218.c. */

/* func_002C94C8 is defined in 002C94C8.c. */

void func_002C9828(char *path, int clamp, float *out, float *angles, int flags, float t)
{
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float f[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    int idx = func_00283CF0(t);
    int hit = 0;
    int i0;
    int i1;
    int i2;
    int n;

    if (clamp == 0) {
        if (idx >= *(int *)path - 2) {
            idx = *(int *)path - 2;
            hit = 1;
        }
    }
    t -= idx;
    if (hit) {
        if (t > 1.0f)
            t = 1.0f;
    }
    n = *(int *)path;
    i0 = idx;
    i1 = idx + 1;
    i2 = idx + 2;
    if (i2 >= n) {
        i0 = i0 % n;
        i1 = i1 % n;
        i2 = i2 % n;
    }
    qcopy(a, path + 0x10 + i0 * 16);
    qcopy(b, path + 0x10 + i1 * 16);
    func_00282D08(out, a, b, t);
    if (flags & 1)
        return;
    if (hit) {
        func_00282CF0(f, b, a);
    } else {
        qcopy(c, path + 0x10 + i2 * 16);
        func_00282CF0(d, b, a);
        func_00282CF0(e, c, b);
        func_00282D08(f, d, e, t);
    }
    angles[1] = -func_00283248(func_00282E20(f), f[2]);
    angles[2] = func_00283248(f[0], f[1]);
    angles[3] = a[3] * (1.0f - t) + b[3] * t;
}

int func_002C9A50(void) {
    return D_001F2A30;
}

/* A15-struct-pad-20 freshly exact-verified under family reservation */
void func_002C9A60(void) {
    BatchA_A15_u8 *p = D_L15_001FF640;
    *(BatchA_A15_u32 *)(p + 0xF0) = 0;
    *(BatchA_A15_u32 *)(p + 0x1F0) = 0;
}

/* A10-twin-base-32 freshly exact-verified under family reservation */
void func_002C9A78(void) {
    BatchA_A10_u8 *p = D_L03_001FF8C0;
    *(BatchA_A10_u32 *)(p + 0xF0) = (BatchA_A10_u32)D_L03_001FFAC0;
    *(BatchA_A10_u32 *)(p + 0x1F0) = 1;
}

void func_002C9A98(s32 *a0) {
 s32 *base=a0+3; s32 v;
 do {
  v=--a0[1];
  if(v<=0) v=a0[0];
  a0[1]=v;
 } while(*(s32 *)((u32)base+(v<<2))==0);
}

void func_002C9AD8(s32 *a0) {
 s32 limit=a0[0]; s32 *base=a0+3; s32 v;
 do {
  v=a0[1]+1;
  if(limit<v) v=0;
  a0[1]=v;
 } while(*(s32 *)((u32)base+(v<<2))==0);
}

int func_002C9B18(void) {
    if (D_001A8CFC[0] != 0)
        func_00339770(D_001A8CFC[0] + 0x3CAA8, 0);
    return 0;
}

int func_002C9B50(void) {
    if (D_001A8CFC[0] != 0)
        func_00339770(D_001A8CFC[0] + 0x3CAA8, 1);
    return 0;
}

/* reads two object fields, forms centre plus and minus half of a third, and issues two five-argument draw calls taking an id-derived value and a fixed 64-bit attribute */
int func_002C9B88 (int *p)
{
  int a = p[6];
  int t = p[8] >> 1;
  int diff = a - t;
  int sum = a + t;
  int r;

  r = func_00288FB8_1 (4412);
  func_0027F5B8 (diff, p[7], (long) 0x80f0f0f0, r, -1);
  r = func_00288FB8_1 (4408);
  func_0027FA10 (sum, p[7], (long) 0x80f0f0f0, r, -1);
  return 0;
}

int func_002C9C20(void)
{
    char *b = D_001F2840;
    int value = -1;
    int *p = (int *)(b + 0x1BC);
    int i;

    for (i = 0x13; i >= 0; i--)
        *p-- = value;
}

void func_002C9CF8(int mode)
{
    func_00132AF8(0x5D);
    func_002B72E8(0);
    ((State_2C9CF8 *)D_001F2840)->byteDB = 0;
    func_00132028();
    ((State_2C9CF8 *)D_001F2840)->f0 = 1;
    if (!D_001A8BB0) func_002CAF18();
    ((State_2C9CF8 *)D_001F2840)->f144 = 0;
    ((State_2C9CF8 *)D_001F2840)->f148 = 0;
    ((State_2C9CF8 *)D_001F2840)->fE8 = (D_001A7A08 & 0xFFFF0000) || ((State_2C9CF8 *)D_001F2840)->f108 ? 1 : 0;
    ((Links_2C9CF8 *)D_00259918)->next = ((State_2C9CF8 *)D_001F2840)->fE8 ? D_00259AF8 : D_00259AA8;
    ((Links_2C9CF8 *)D_00259AA8)->previous = ((State_2C9CF8 *)D_001F2840)->fE8 ? D_00259AF8 : D_00259918;
    ((State_2C9CF8 *)D_001F2840)->f8 = ((State_2C9CF8 *)D_001F2840)->f104 ? (int)((State_2C9CF8 *)D_001F2840)->f104 : mode;
    ((State_2C9CF8 *)D_001F2840)->f1C = 0;
    ((State_2C9CF8 *)D_001F2840)->f20 = 0;
    ((State_2C9CF8 *)D_001F2840)->f120 = 0;
    ((State_2C9CF8 *)D_001F2840)->f1C0 = 0;
    ((State_2C9CF8 *)D_001F2840)->f1C4 = 0;
    ((State_2C9CF8 *)D_001F2840)->f1C8 = 0;
    if (mode != 6) {
        func_00295C50(D_001A79F0);
        func_0029D830();
        D_0025B5F8 = 0;
        func_002DF050();
    }
    ((State_2C9CF8 *)D_001F2840)->f150 = 0;
    ((State_2C9CF8 *)D_001F2840)->f14C = 1;
}

void func_002C9E60(int a0)
{
    GsLoadImage2C9E60 li;
    int remaining;
    int dest;
    char *src;
    char *state = D_001F2840;

    *(int *)(state + 0xD0) = a0 != 0 ? 2 : 1;
    func_002FC3C0(1);
    func_001261F0(0);
    D_001B1598++;
    remaining = D_001A7344 * 0x600;
    src = *(char **)(state + 0x20);
    dest = D_001A72D4;
    if (a0 != 0)
        dest = 0x3FB000 - remaining;
    for (; remaining >= 0; remaining -= 0x4000) {
        func_00126288(&li, dest >> 8, 1, 0, 0, 0, 64, 64);
        dest += 0x4000;
        func_0011AEA0(0);
        func_001265B0(&li, src);
        src += 0x4000;
        func_001244B8(0, 0);
    }
}

INCLUDE_ASM("asm/game", func_002CA070);

/* func_002CA5D0 is defined in 002C7748-g8.c. */

/* func_002CA790 is defined in 002CA790.c. */

INCLUDE_ASM("asm/game", func_002CA8A8);

void func_002CAA58(void)
{
    func_002CA070();
    D_L00_001FEC40[0] = 2;
    D_L00_001FEC40[1] = 0;
}

/* A12-struct-2field-24 freshly exact-verified under family reservation */
void func_002CAA88(void) {
    BatchA_A12_BatchA24 *p = &D_L08_001FF980;
    p->a = 3;
    p->b = 0;
}

void func_002CAAA0(void)
{
    int *p;

    func_0027DDC0(0, 0, 0, 0x38);
    p = (int *)D_001F2840;
    if (p[1] == 0)
        p[1] = 1;
    p[0] = 4;
    p[5] = p[6];
    p[6] = 0;
    p[1] = 0;
}

void func_002CADB0(void)
{
    int n = ((GameState_1F2840 *)D_001F2840)->count;

    if (n != 0)
        ((GameState_1F2840 *)D_001F2840)->count = n - 1;
    if (((GameState_1F2840 *)D_001F2840)->count != 0)
        return;
    if (D_001A63AC != 0)
        return;
    if (((GameState_1F2840 *)D_001F2840)->mode == 2) {
        func_002B4B70(0, D_001C51D0);
    } else if (((GameState_1F2840 *)D_001F2840)->mode == 3) {
        func_002B49E0(1, 1, 0, ((GameState_1F2840 *)D_001F2840)->fieldF4, 0);
    } else if (((GameState_1F2840 *)D_001F2840)->mode == 4) {
        func_002B49E0(1, 1, 0, ((GameState_1F2840 *)D_001F2840)->fieldF4, 0);
    } else if (((GameState_1F2840 *)D_001F2840)->mode == 6) {
        func_002B49E0(1, 1, 0, ((GameState_1F2840 *)D_001F2840)->fieldF4, 0);
    } else if (((GameState_1F2840 *)D_001F2840)->mode == 5) {
        func_002B49E0(2, 1, ((GameState_1F2840 *)D_001F2840)->fieldF4, 0, 0);
    } else {
        func_002B4B70(0, 0);
    }
    if (((GameState_1F2840 *)D_001F2840)->field40 != 0 &&
        ((GameState_1F2840 *)D_001F2840)->field30 != ((GameState_1F2840 *)D_001F2840)->field40) {
        int id;
        int *rec;
        func_002B7CE0(1);
        id = ((GameState_1F2840 *)D_001F2840)->field40;
        rec = (int *)((char *)D_00239BA0 + D_00139568[id] * 0xE0);
        func_00294420(rec[5]);
        func_002B7CE0(1);
    }
    func_002B7CE0(1);
}

/* func_002CB820 reads $gp slots: it is defined in 002C7748-g8.c. */


s32 func_002CB4E8(s32 a0) {
 s32 result=0;
 if(a0<0x15 || a0==0x18) result=1;
 return result;
}

/* func_002CB510 is defined in 002CB510.c. */

/* func_002CB648 is defined in 002CB648-g8.c. */

int func_002CB7D0(int mode)
{
    int result = 0;
    switch (mode) {
    case 0: result = 1; break;
    case 1: result = func_002D5B38(3, D_0025BA90); break;
    }
    return result;
}

int func_002CBA58(int mode)
{
    int result = 0;
    switch (mode) {
    case 0: D_0018A000[0] = 10; result = 1; break;
    case 1: result = func_002D5B38(3, D_0025BA90); break;
    case 2: func_0029CE80(); result = 1; break;
    }
    return result;
}

/* func_002CBAE0 is defined in 002C7748-g8.c. */

INCLUDE_ASM("asm/game", func_002CBC58);

int func_002CC490(int a0)
{
    if (*(int *)(((CallbackState_2CC490 *)D_001F2840)->source + 0xE8) != a0)
        return 0;
    if ((((GameState_2CC490 *)D_00138180)->flags & 0x900) != 0 &&
        ((CallbackState_2CC490 *)D_001F2840)->fallback == 0)
        return 1;
    if ((((GameState_2CC490 *)D_00138180)->flags & 0x10) != 0) {
        int value = *(int *)(((CallbackState_2CC490 *)D_001F2840)->source + 0xE0);
        int result;
        if (value != 0)
            ((CallbackState_2CC490 *)D_001F2840)->value = value;
        else if (((CallbackState_2CC490 *)D_001F2840)->fallback == 0) {
            result = -1;
            goto done;
        }
        result = 0;
done:
        return result;
    }
    return 0;
}

INCLUDE_ASM("asm/game", func_002CC528);

/* Near miss: nonmatching/game/func_002CC550.c (316/316 bytes; the two address
   materialisations in the loop preheader keep a separate %hi temporary). */

int func_002CC690(void) {
    return 0;
}

int func_002CC698(void) {
    return 0;
}

s32 func_002CC6A0(u8 *p) { *(s32 *)(p + 0x44) = -1; return 0; }

INCLUDE_ASM("asm/game", func_002CC6B0);

int func_002CCF68(char *obj)
{
    int old;
    int kind;
    MenuEntry_2CCF68 *entry;

    if (*(char **)(*(char **)(D_001F2840 + 0x14) + 0xE8) != obj) goto fallback;
    if ((((InputState_2CCF68 *)D_00138180)->flags & ~0x40) != 0 && obj == D_00259148) return 0;
    old = D_001B1680;
    if (D_001A8B84) goto fallback;
    entry = (MenuEntry_2CCF68 *)(*(int *)(obj + 0x40) * 12 + *(int *)(obj + 0x34));
    kind = entry->kind;
    if (kind != 3) goto fallback;
    if (obj == D_00259148) {
        D_001A8B84 = 1;
        D_001B1680 = 1;
        return 0;
    }
    if (((InputState_2CCF68 *)D_00138180)->flags & 0x40) {
        if (obj == D_00259198) {
            D_001A8B84 = D_001A7BC9.value != 0;
            D_001B1680 = 1;
        } else if (obj == D_002591E8) {
            D_001A8B84 = D_001A7BCA.value != 0;
            D_001B1680 = 2;
        } else if (obj == D_00259238) {
            D_001A8B84 = D_001A7BCB.value != 0;
            D_001B1680 = 3;
        } else if (obj == D_00259288) {
            D_001A8B84 = D_001A7BCC.value != 0;
            D_001B1680 = 4;
        } else if (obj == D_002592D8) {
            D_001A8B84 = D_001A7BCE.value != 0;
            D_001B1680 = 6;
        }
        if (!D_001A8B84)
            D_001B1680 = old;
        return 0;
    }
fallback:
    return func_002D5EC0(obj);
}

int func_002CD0E8(void)
{
    unsigned int flags = D_00138344;
    int res = 0;

    if (flags & 0x910) {
        res = 1;
    } else if (flags & 0x40) {
        res = func_0029C168(flags);
        if (func_0026F7C8() && func_0026F7D0()) {
            res = func_002CB950(res);
        } else if (func_0026F7E0()) {
            res = func_002CB820(res);
        } else if (func_0026F7D8()) {
            res = func_002CBA58(res);
        } else if (func_0026F7F0() == 0x31) {
            res = func_002CB7D0(res);
        } else if (func_0026F7E8()) {
            res = func_002CB7D0(res);
        } else if (func_0026F7F0() == 0x1C) {
            res = func_002CB7D0(res);
        } else {
            res = func_002CB8A0(res);
        }
    } else {
        func_0029C168(flags);
    }

    if (res) {
        func_002E5E58(0x12, 0, 0);
    }
    return res;
}

int func_002CD220(void)
{
  func_0027C540(0);
  func_0029C138();
  func_0027C660();
  return 0;
}

INCLUDE_ASM("asm/game", func_002CD3C0);

int func_002CD4E0(void)
{
    int local[4];
    int first = func_00336EF0();
    int result = 0;
    int flags = D_00138344;

    if (flags & 0x10) {
        int value = *(int *)(((CallbackState_2CC490 *)D_001F2840)->source + 0xE0);
        if (value != 0)
            ((CallbackState_2CC490 *)D_001F2840)->value = value;
        else if (((CallbackState_2CC490 *)D_001F2840)->fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }

    if (flags & 0x900) {
        result = 1;
    } else {
        func_0029C248(flags, local);
    }

    if (D_001A8CFC[0] != 0) {
        int second = func_00336EF0();
        if (first == second && D_001A63AC == 0 &&
            ((D_00259C78.handle == second && D_00259C78.state == 2) ||
             (D_00259C78.last == second && D_00259C78.state == 4))) {
            D_00259C44->flags &= -5;
        } else {
            D_00259C44->flags |= 4;
        }
        D_00259C78.current = second;
    }
    return result;
}
