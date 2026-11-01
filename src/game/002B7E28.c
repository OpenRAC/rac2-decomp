#include "include_asm.h"
#include "common.h"

extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern int func_002AAE98(float, float, float, float);
extern unsigned char *D_001F2574, *D_001F25A4;
extern void func_002B9180(char *);
extern void func_00282CC0(char *, char *, char *);

#ifndef RAC2_T_REC_F4EC78016
#define RAC2_T_REC_F4EC78016
typedef struct Rec_F4ec78016 {
    int f0;
    unsigned char pad4[6];
    short h10;
    unsigned char pad12[20];
    int f32;
} Rec_F4ec78016;
#endif

#ifndef RAC2_T_SLOT_F4EC78016
#define RAC2_T_SLOT_F4EC78016
typedef struct Slot_F4ec78016 {
    int f0;
    unsigned char pad4[108];
} Slot_F4ec78016;
#endif

#ifndef RAC2_T_GLOBALS_F4EC78016
#define RAC2_T_GLOBALS_F4EC78016
typedef struct Globals_F4ec78016 {
    unsigned char pad0[108];
    short h108;
    short h110;
    short h112;
    unsigned char pad114[18];
    int f132;
} Globals_F4ec78016;
#endif

extern Slot_F4ec78016 D_00188660_1[];

extern Globals_F4ec78016 D_001A63A8_4[];

extern void func_002B6958(int a, int b, int c, int d);

extern float Fe617c30b_FUN_00283CE0(int a);

extern void Fe617c30b_FUN_00282D30(char *p, char *q, float f);

extern void Fe617c30b_FUN_00282CC0(char *p, char *q, char *r);

extern int Fe617c30b_FUN_002A9568(int a, int b, float f);

extern int Fe617c30b_FUN_00282978(char *p);

extern void Fe617c30b_FUN_002B9180(char *p);

extern int Fb77d67f1_FUN_00282948(char *p);

extern void Fb77d67f1_FUN_002B9180(char *p);

extern int func_00282978_4(char *p);

extern void func_002B9180_8(char *p);

extern int func_00283CF0_4(float f);

extern void func_00282CC0_14(char *a, char *b, char *c);

extern void func_00282D30_14(char *a, char *b, float f);

extern int Fd1c348f5_FUN_00282978(char *p);

extern int Fd1c348f5_FUN_00283CF0(float v);

extern void Fd1c348f5_FUN_002B9180(char *p);

extern int F3c007b59_FUN_00282978(void *p);

extern void F3c007b59_FUN_002B9180(void *p);

extern unsigned int F3c007b59_FUN_00283CF0(float x);

#ifndef RAC2_T_OBJ_F3C007B59
#define RAC2_T_OBJ_F3C007B59
typedef struct {
    unsigned char pad0[4];
    unsigned int w04;
    unsigned char c08;
    unsigned char c09;
    unsigned char c10;
    unsigned char c11;
    float f12;
    unsigned char pad16[8];
    float f24;
    unsigned char pad28[4];
    float f36;
    float f40;
    float f44;
} OBJ_F3c007b59;
#endif

extern void func_00282CC0_8(void *, void *, void *);

extern s32 func_00282948(void *);

extern void func_002B9180_4(void *);

extern int Fc10c1216_FUN_00282978(char *);

extern void Fc10c1216_FUN_002B9180(char *);

extern int Fc10c1216_FUN_00283CF0(float);

extern void Fc10c1216_FUN_00282CC0(char *, char *, char *);

extern void func_002B6D80(s32, s32, s32);

extern short D_001A63D4;

#define NOT_SDA __attribute__((section(".data")))

extern short r1_D_001517F0 NOT_SDA;

extern void func_0026FEB8(const char *, ...);
extern char D_001AA220[];

typedef struct {
    char pad00[0x2C];
    short state;
    char pad2E[2];
    int value;
    int quarter;
} FileLoadVoiceState_002B8048;
extern FileLoadVoiceState_002B8048 g_fileLoadVoiceState;

typedef struct {
    char reserved[0x18E];
    short active;
    int value;
} State_2B8518;

extern State_2B8518 D_00138180;

typedef int TI __attribute__((mode(TI)));

extern float func_002B0520(TI *pos);
extern int D_001A79F0 MACRO_ADDR;
extern float D_001B1DC0[] MACRO_ADDR;

extern unsigned char *D_001F2544;

extern void func_00300190(char *, char *);

/* func_002BB838 uses the profile in 002BB838-qcopy.c. */

extern int func_00283D38(int, int, float);
extern unsigned char *D_001F2560;


/* Stores the incoming handle into the record's first word and, for a non-negative index, into the next slot of a 112-byte-stride table, then either bumps a state short from 1 to 2 or passes three shorts and one word of a global block to a helper. */
void func_002B7E28(void *a0, long a1)
{
    Rec_F4ec78016 *n = (Rec_F4ec78016 *)a1;
    Slot_F4ec78016 *p;
    int i;

    if (n == 0)
        return;
    n->f0 = (int)a0;
    i = n->f32;
    if (i >= 0) {
        p = D_00188660_1 + i;
        *(int *)((char *)p + 112) = (int)a0;
    }
    if (a0 != 0) {
        if (n->h10 == 1)
            n->h10 = 2;
    } else {
        func_002B6958(D_001A63A8_4->h108, D_001A63A8_4->h112, D_001A63A8_4->f132, D_001A63A8_4->h110);
    }
}

void func_002B7EA8(s32 a0, long a1)
{
    s32 p = (s32)a1;
    if (p == 0)
        return;
    *(s32 *)p = a0;
    if (a0 != 0) {
        if (*(short *)(p + 10) == 1)
            *(short *)(p + 10) = 2;
    } else {
        u8 *g = (u8 *)D_001A63A8_4;
        func_002B6D80(*(short *)(g + 0x48),
                      *(short *)(g + 0x4C),
                      *(short *)(g + 0x4A));
    }
}

void func_002B7F08(int arg0, long arg1)
{
    short *p = (short *)(int)arg1;
    short state;
    if (p != 0) {
        *(int *)p = arg0;
        if (arg0 != 0) {
            state = p[5];
            if (state == 1) {
                p[5] = 4;
                if (p[8] != 0) D_001A63D4 = state;
            }
        } else {
            p[5] = 0;
        }
    }
}

/* rac1-decomp src/game/stream.c: func_00217970 */
void func_002B7F58(int arg0, long arg1) {
    short *p = (short *)(int)arg1;
    if (p != 0) {
        if (arg0 < 0) {
            *(int *)p = arg0;
        }
        if (arg0 != 0) {
            if (p[5] == 9) {
                p[5] = 4;
                if (p[8] != 0) {
                    r1_D_001517F0 = 1;
                }
            }
        } else {
            p[5] = 0;
        }
    }
}

void func_002B7FB0(int arg0, long arg1) {
    short *p = (short *)(int)arg1;

    if (p != 0) {
        *(int *)p = arg0;
        if (arg0 != 0) {
            if (p[5] == 1) {
                p[5] = 8;
            }
        } else {
            p[5] = 0;
        }
    }
}

void func_002B7FF0(int value, long address)
{
    char *p = (char *)(int)address;
    if (p == 0)
        return;
    if (*(unsigned int *)p != 0xFFFFFFFFU) {
        func_0026FEB8(D_001AA220);
        return;
    }
    *(int *)p = value;
    if (value == 0)
        *(short *)(p + 10) = 7;
}

void func_002B8048(int value, long address)
{
    char *p = (char *)(int)address;
    int stored = value;
    if (p == 0)
        return;
    *(int *)(p + 0x18) = stored;
    if (*(short *)(p + 0x10) == 0)
        return;
    {
        FileLoadVoiceState_002B8048 *state = &g_fileLoadVoiceState;
        if (state->state != 1)
            return;
        if (stored == 0)
            return;
        state->state = 2;
        state->value = *(int *)(p + 0x18);
        state->quarter = *(int *)(p + 0x18) / 4;
    }
}

INCLUDE_ASM("asm/game", func_002B80B8);

/* func_002B8108 is in 002B7E28-g8.c. */

void func_002B8518(void) {
    D_00138180.active = 0;
    D_00138180.value = 0;
}

INCLUDE_ASM("asm/game", func_002B8530);

/* func_002B85F8 is in 002B7E28-g8.c. */

void func_002B8888(u8 *a0) {
 s32 *p=(s32 *)(a0+0x140);s32 count=15;
 *(s32 *)(a0+0x1b0)=0;*(volatile s32 *)(a0+0x1d4)=1;
 *(volatile s32 *)(a0+0x1a0)=0;*(volatile s32 *)(a0+0x1a4)=0;*(volatile s32 *)(a0+0x1a8)=0;
 *(volatile s32 *)(a0+0x1d0)=1;*(volatile s32 *)(a0+0x1b4)=0;*(volatile s32 *)(a0+0x1b8)=0;
 *(volatile s32 *)(a0+0x1c0)=0;*(volatile s32 *)(a0+0x1c4)=0;*(volatile s32 *)(a0+0x1c8)=0;*(volatile s32 *)(a0+0x1d8)=0;
 do { p[-16]=0;count--;p[0]=0;p++; }while(count>=0);
}


void func_002B9000(void) {
    extern void func_002B85F8(void *);
    extern State_2B8518 D_00138500;
    func_002B85F8(&D_00138180);
    func_002B85F8(&D_00138500);
}

INCLUDE_ASM("asm/game", func_002B9030);

ASM_FUNC("asm/game", func_002B9038);

INCLUDE_ASM("asm/game", func_002B9180);

INCLUDE_ASM("asm/game", func_002B9288);

INCLUDE_ASM("asm/game", func_002B9380);

INCLUDE_ASM("asm/game", func_002B9390);

ASM_FUNC("asm/game", func_002B9420);

INCLUDE_ASM("asm/game", func_002BA048);

INCLUDE_ASM("asm/game", func_002BA0E0);

void func_002BA6A0(char *p)
{
    float *f = (float *)p;
    float *s = f + 0xC;
    float lim = s[3];
    float tmp[4] __attribute__((aligned(16)));
    TI c1, c2;
    int x, y;
    float h;

    if (D_001A79F0 == 15) {
        if (f[6] < lim) {
            func_002B9180(p);
            return;
        }
    } else if (f[6] < lim || f[4] < 0.0f || f[5] < 0.0f || f[4] > 1024.0f || f[5] > 1024.0f) {
        func_002B9180(p);
        return;
    }
    x = (int)f[8];
    y = (int)f[9];
    func_00282CC0((char *)tmp, (char *)s, (char *)D_001B1DC0);
    func_00282CC0((char *)(f + 8), (char *)(f + 8), (char *)tmp);
    func_00282CC0((char *)(f + 4), (char *)(f + 4), (char *)tmp);
    if (*(short *)(p + 0xA) != 2 && (x != (int)f[8] || y != (int)f[9])) {
        c1 = *(TI *)(f + 8);
        h = func_002B0520(&c1);
        if (h >= D_001B1DC0[4]) {
            c2 = *(TI *)(f + 8);
            lim = func_002B0520(&c2);
        } else {
            lim = D_001B1DC0[4];
        }
        if (f[10] < lim) {
            func_002B9180(p);
            return;
        }
    }
    s[2] -= 0.0027222223f;
    s[3] = lim + D_001B1DC0[2];
}

void func_002BA978(char *self)
{
    int alpha = *(short *)(self + 0xA) * *(int *)(self + 0x20) / 27;
    *(unsigned int *)(self + 4) = (*(unsigned int *)(self + 4) & 0xFFFFFFu) | (alpha << 24);
    if (func_00282978_4(self + 0xA)) {
        func_002B9180_8(self);
    } else {
        self[2] = D_001F2544[(27 - *(short *)(self + 0xA)) / 3];
    }
}

/* func_002BABE8 is in 002B7E28-g8.c (its global read uses the retail's one-register
   `lui`/`lw` pair, which only a -G8 unit emits). */

void func_002BAE48(void) {
}

/* func_002BAE50 is matched in its own unit, src/game/002BAE50.c (default flags). */

void func_002BAF68(char *a0)
{
    char *s0 = a0 + 32;
    int x;
    int u;
    int t;
    float f;

    x = *(int *)(s0 + 28);
    t = *(short *)(a0 + 10);
    u = *(short *)(s0 + 24) * (x - t) / x + *(short *)(s0 + 26);

    f = Fe617c30b_FUN_00283CE0(u) * 1000.0f;
    *(float *)(a0 + 12) = f;
    Fe617c30b_FUN_00282D30(s0, s0, 9.8000001907348632812500e-01f);
    Fe617c30b_FUN_00282CC0(a0 + 16, a0 + 16, s0);
    *(unsigned char *)(a0 + 8) = *(unsigned char *)(a0 + 8) + 1;
    f = Fe617c30b_FUN_00283CE0(*(int *)(s0 + 28));
    *(int *)(a0 + 4) = Fe617c30b_FUN_002A9568(*(int *)(s0 + 20), *(int *)(s0 + 16),
                               (float)*(short *)(a0 + 10) / f);
    if (Fe617c30b_FUN_00282978(a0 + 10) != 0)
        Fe617c30b_FUN_002B9180(a0);
}

void func_002BB050(u8 *a0)
{
    u8 *s0 = a0;
    u8 *s1 = a0 + 0x20;

    if (func_00282948((char *)s1) != 0) {
        func_002B9180((char *)s0);
        return;
    }
    {
        u8 *p = s0 + 0x10;

        func_00300190((char *)p, (char *)p);
    }
    *(f32 *)(s0 + 0xC) = *(f32 *)(s0 + 0xC) + *(f32 *)(s1 + 4);
    if (*(s32 *)(s1) < 6) {
        *(unsigned int *)(s0 + 4) = (*(unsigned int *)(s0 + 4) & 0xFFFFFF)
            | ((unsigned int)(*(s32 *)(s1) * 127 / 6) << 24);
    }
}

INCLUDE_ASM("asm/game", func_002BB100);

void func_002BB798(char *a0)
{
    char *p = a0 + 32;

    if (Fb77d67f1_FUN_00282948(p) != 0) {
        Fb77d67f1_FUN_002B9180(a0);
        return;
    }
    *(float *)(a0 + 12) = *(float *)(a0 + 12) + *(float *)(p + 4);
    if (*(int *)(a0 + 32) < 6)
        *(int *)(a0 + 4) = (*(int *)(a0 + 4) & 0xFFFFFF)
                         | ((*(int *)(a0 + 32) * 127 / 6) << 24);
}

/* blends a sub-object into a position, adds a float field, stores an interpolated value in the
   word at +4 and scales the frame count into a byte table at +2 */
void func_002BB928(char *a0)
{
    char *s0 = a0;
    char *s1 = a0 + 32;
    unsigned int r;
    float f;

    Fe617c30b_FUN_00282CC0(s0 + 16, s0 + 16, s1);
    if (Fe617c30b_FUN_00282978(s0 + 10) != 0) {
        Fe617c30b_FUN_002B9180(s0);
        return;
    }
    *(float *)(s0 + 12) = *(float *)(s0 + 12) + *(float *)(s1 + 0x1C);
    f = Fe617c30b_FUN_00283CE0(*(int *)(s1 + 0x18));
    r = func_00283D38(*(int *)(s1 + 0x14), *(int *)(s1 + 0x10),
                      (float)*(short *)(s0 + 0xA) / f);
    *(int *)(s0 + 4) = r;
    if (*(short *)(s0 + 0xA) < 6) {
        *(int *)(s0 + 4) = (r & 0xFFFFFF) | (((int)(*(short *)(s0 + 0xA) * (r >> 24))) / 6 << 24);
    }
    *(unsigned char *)(s0 + 2) = D_001F2560[((*(int *)(s1 + 0x18) - *(short *)(s0 + 0xA)) * 10) / *(int *)(s1 + 0x18)];
}

/* decays a float field by 0.04 with a saturating early-out that consults a helper and returns; otherwise adds 12000 to a second field, nudges a third by 0.0484 while it stays below 0.225, merges two 255-scaled byte lanes into a header word, hands a sub-object to two helpers and decrements a byte counter */
void func_002BBB70(char *p)
{
    char *q = p + 32;
    float v;
    int a, b;
    int h;

    v = *(float *)(q + 28) + (-0.04f);
    *(float *)(q + 28) = v;
    if (v <= 0.0f || func_00282978_4(p + 10) != 0) {
        func_002B9180_8(p);
        return;
    }
    *(float *)(p + 12) = *(float *)(p + 12) + 12000.0f;
    if (*(float *)(q + 24) < 0.225f) {
        *(float *)(q + 24) = *(float *)(q + 24) + 0.0484f;
    }
    a = func_00283CF0_4(*(float *)(q + 24) * 255.0f) & 0xff;
    b = func_00283CF0_4(*(float *)(q + 28) * 255.0f);
    h = *(unsigned short *)(p + 4);
    *(int *)(p + 4) = h | (a << 16) | (b << 24);
    func_00282CC0_14(p + 16, p + 16, q);
    func_00282D30_14(q, q, 0.9f);
    *(char *)(p + 8) = *(unsigned char *)(p + 8) - 1;
}

/* func_002BBCB0 is in 002BBCB0-g8-qcopy.c. */


/* func_002BC508 is in 002BC508-g8.c. */

char *func_002BC768(char *pos, int spin, int color, float spread, float low, float high, float accel, float size)
{
    char *p = func_002B9030(13);
    char *q;
    if (p) {
        qcopy(p + 16, pos);
        q = p + 32;
        *(int *)(p + 4) = color;
        p[9] = func_00283CF0(4.0f) + 64;
        p[3] = 0x48;
        *(float *)(p + 12) = size;
        p[1] = 0;
        p[8] = 0;
        p[2] = D_001F2574[0];
        *(float *)(p + 16) += func_002A78D8(0.0f, spread);
        *(float *)(p + 20) += func_002A78D8(0.0f, spread);
        *(float *)(p + 24) += func_002A78D8(0.0f, spread);
        *(short *)(p + 10) = 10;
        *(int *)(q + 4) = 0;
        if (func_002A77E0(2))
            *(int *)(q + 8) = spin;
        else
            *(int *)(q + 8) = -spin;
        *(int *)(q + 20) = color & 0xffffff;
        *(float *)(q + 12) = func_002A7878(low, high);
        *(float *)(q + 16) = accel;
    }
    return p;
}

void func_002BC8E8(char *p)
{
    char *q = p + 32;
    int r;
    int v;
    float f;

    *(unsigned char *)(p + 8) = *(unsigned char *)(p + 8) + *(unsigned char *)(q + 8);
    *(float *)(p + 24) = *(float *)(p + 24) + *(float *)(q + 16);
    *(float *)(p + 12) = *(float *)(p + 12) * *(float *)(q + 12);
    if (*(int *)(q + 4) == 0) {
        r = Fd1c348f5_FUN_00282978(p + 10);
        if (r != 0) {
            *(int *)(q + 4) = 1;
            *(short *)(p + 10) = 30;
            *(int *)(p + 4) = *(int *)(q + 20) | 0x7f000000;
        } else {
            f = (float)(10 - *(short *)(p + 10)) * 9.6000003814697265625000e+00f;
            v = Fd1c348f5_FUN_00283CF0(f);
            *(int *)(p + 4) = ((v + 32) << 24) | *(int *)(q + 20);
        }
    } else {
        r = Fd1c348f5_FUN_00282978(p + 10);
        if (r != 0) {
            Fd1c348f5_FUN_002B9180(p);
        } else {
            f = (float)*(short *)(p + 10) * 4.2333333492279052734375e+00f;
            v = Fd1c348f5_FUN_00283CF0(f);
            *(int *)(p + 4) = (v << 24) | *(int *)(q + 20);
        }
    }
}

/* func_002BCB00 is defined in 002BCB00-zero-ti-barrier.c. */

/* func_002BCC58 is in 002BCC58-g8.c. */


/* func_002BD0D0 is in 002BD0D0-g8.c. */

void func_002BD390(void) {
}

void func_002BD398(OBJ_F3c007b59 *o)
{
    float *p = (float *)((char *)o + 32);
    float f;
    float y;

    f = p[1] + p[3] * 1.3000000268220901489258e-02f;
    p[1] = f;
    if (f <= 0.0f || F3c007b59_FUN_00282978(&o->c10) != 0) {
        F3c007b59_FUN_002B9180(o);
    } else {
        f = p[1];
        if (2.1999999880790710449219e-01f <= f) {
            y = p[3];
            y = -y;
            p[3] = y;
            p[1] = f + y * 1.3000000268220901489258e-02f;
        }
        o->f12 = o->f12 + 8.1900000000000000000000e+03f;
        o->w04 = (o->w04 & 0xFFFFFFu) |
                 (F3c007b59_FUN_00283CF0(p[1] * 2.5500000000000000000000e+02f) << 24);
        p[2] = p[2] + 1.2000000104308128356934e-02f;
        if (p[2] > 1.0f)
            p[2] = p[2] - 1.0f;
        o->c08 = (unsigned char)(p[2] * 2.5500000000000000000000e+02f);
        o->f24 = o->f24 - 1.9999999552965164184570e-02f;
    }
}

void func_002BD500(char *a)
{
    char *p1 = a + 16;
    char *p2 = a + 32;
    char *p3 = a + 48;
    int v;

    func_00282CC0(p1, p1, p3);
    func_00282CC0(p2, p2, p3);
    func_00300190(p1, p1);
    func_00300190(p2, p2);
    v = *(int *)(a + 4) - (func_00283CF0(*(float *)(p3 + 12)) << 24);
    *(int *)(a + 4) = v;
    *(int *)(a + 12) = v;
    if (v < 0)
        func_002B9180(a);
}

/* func_002BDCE8 uses the qcopy profile in 002BDCE8.c. */

/* func_002BDEB0 is in 002BDEB0.c. */


/* func_002BE278 uses the quadword-copy profile in 002BE278-qcopy.c. */

/* func_002BE400 uses the no-gcse profile in 002BE400.c. */

/* func_002BE7E8 uses the quadword-copy profile in 002BE7E8-qcopy.c. */

/* calls a three-argument helper on the sub-objects at +16 and +32, then packs ((v[6]*v[4])/v[5])<<24 into the low 24 bits of the word at +4 and conditionally calls a second helper on +48 before a final call. */
void func_002BE928(s32 *self) {
    s32 *base = (s32 *)((char *)self + 32);
    s32 *state = (s32 *)((char *)self + 16);
    func_00282CC0_8(state, state, base);
    self[1] = (self[1] & 0x00ffffff) + ((base[6] * base[4] / base[5]) << 24);
    if (func_00282948((s32 *)((char *)self + 48)) != 0) {
        func_002B9180_4(self);
    }
}

void func_002BE9B8(char *p)
{
    float *q = (float *)(p + 32);

    if (0.0f < q[3])
        q[1] = q[1] + q[3] * 0.007f;
    else if (0.03f < q[1])
        q[1] = q[1] + q[3] * 0.007f;
    else {
        q[1] = q[1] + q[3] * 1.4000000664964318275452e-03f;
        *(float *)(p + 12) = *(float *)(p + 12) + 5460.0f;
    }

    if (q[1] <= 0.0244f || Fc10c1216_FUN_00282978(p + 10) != 0) {
        Fc10c1216_FUN_002B9180(p);
        return;
    }

    if (q[1] >= 0.12f) {
        q[3] = -q[3];
        q[1] = q[1] + q[3] * 0.007f;
    }
    *(float *)(p + 12) = *(float *)(p + 12) + 5460.0f;
    *(int *)(p + 4) = (*(int *)(p + 4) & 0xffffff) | (Fc10c1216_FUN_00283CF0(q[1] * 255.0f) << 24);
    q[2] = q[2] + 0.002f;
    if (q[2] > 1.0f)
        q[2] = q[2] - 1.0f;
    *(char *)(p + 8) = (char)(q[2] * 255.0f);
    Fc10c1216_FUN_00282CC0(p + 16, p + 16, (char *)(q + 4));
}

/* func_002BEBC0 is in 002BEBC0-hazard-labels.c (retail keeps a branch label on its
   mtc1 hazard nop, which only a -frac2-hazard-labels unit reproduces). */

/* func_002BEE70 is in 002BEE70-g.c (it needs -g for its line notes' pre-division nops). */

void func_002BF518(char *o)
{
    float *s;
    char *parent;
    float t;

    if (o == 0)
        return;
    s = (float *)(o + 0x20);
    parent = *(char **)s;
    if (parent == 0 || (*(unsigned char *)(parent + 0x20) & 0xF0) == 0xF0) {
        func_002B9180(o);
        return;
    }
    qcopy(o + 0x10, parent + 0x10);
    t = s[1] + s[2];
    s[1] = t;
    if (t < 0.0f) {
        func_002B9180(o);
        return;
    }
    if (t > 0.6f) {
        s[2] = -s[2];
        s[1] = t + s[2];
    }
    s[4] += -0.0174f;
    if (s[4] < 0.0f)
        s[4] = 0.0f;
    s[5] += -0.01446f;
    if (s[5] < 0.0f)
        s[5] = 0.0f;
    s[6] += -0.0015f;
    if (s[6] < 0.0f)
        s[6] = 0.0f;
    *(int *)(o + 4) = func_002AAE98(s[4], s[5], s[6], s[1]);
    s[3] += 0.0011f;
    if (s[3] > 1.0f)
        s[3] -= 1.0f;
    *(char *)(o + 8) = func_00283CF0(s[3] * 255.0f);
    *(float *)(o + 0xC) = (*(float **)(o + 0x20))[0xB] * 3000000.0f + 50000.0f;
}
