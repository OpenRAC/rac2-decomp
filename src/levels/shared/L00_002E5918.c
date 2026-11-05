#include "include_asm.h"

extern void func_00284EA8(void);

typedef long s64;

extern void func_002CBC58(s64);

extern float func_00283BE0_6(float b, float a);

extern float func_00282C48_8(float t);

extern void func_00283B98_10(float a, float c);

/* calls the measured no-argument callee */
void func_L00_002E5918(void) {
 func_00284EA8();
}


/* calls the measured callee with zero */
void func_L00_002E6448(void) {
 func_002CBC58(0);
}

#define MACRO_ADDR __attribute__((section(".sdata")))

extern int r1_D_0015F564_002E6CF0 MACRO_ADDR;

 /* GetEffectTex(int, int) */

/*
 * Four parallel callback lists, each a (function, argument) pair of
 * arrays with its own count, plus a "register" and a "run them all"
 * function per list. The counts are reached with retail's one-register
 * macro form, so they are MACRO_ADDR.
 */
typedef void (*DrawCallback_r002E6CF0)(void *);

extern DrawCallback_r002E6CF0 r1_D_0018DC40_002E6CF0[];

extern void *r1_D_0018DD40_002E6CF0[];

/* rac1-decomp src/game/draw.c: func_001F49B0 */
void func_L00_002E6CF0(DrawCallback_r002E6CF0 fn, void *arg) {
    int count = r1_D_0015F564_002E6CF0;
    if (count < 0x40) {
        r1_D_0018DC40_002E6CF0[count] = fn;
        r1_D_0018DD40_002E6CF0[count] = arg;
        r1_D_0015F564_002E6CF0 = count + 1;
    }
}

/* Runs the queued callbacks. */
typedef void (*Callback_r002E6D40)(void *);
extern volatile int D_L00_001B1948 __attribute__((sda));
extern Callback_r002E6D40 D_L00_001BE0C0[];
extern void *D_L00_001BE1C0[];
void func_L00_002E6D40(void) {
    int i;
    for (i = 0; i < D_L00_001B1948; i++)
        D_L00_001BE0C0[i](D_L00_001BE1C0[i]);
}

#define MACRO_ADDR __attribute__((section(".sdata")))

extern int r1_D_0015F564_002E6DB8 MACRO_ADDR;

 /* GetEffectTex(int, int) */

/*
 * Four parallel callback lists, each a (function, argument) pair of
 * arrays with its own count, plus a "register" and a "run them all"
 * function per list. The counts are reached with retail's one-register
 * macro form, so they are MACRO_ADDR.
 */
typedef void (*DrawCallback_r002E6DB8)(void *);

extern DrawCallback_r002E6DB8 r1_D_0018DC40_002E6DB8[];

extern void *r1_D_0018DD40_002E6DB8[];

/* rac1-decomp src/game/draw.c: func_001F49B0 */
void func_L00_002E6DB8(DrawCallback_r002E6DB8 fn, void *arg) {
    int count = r1_D_0015F564_002E6DB8;
    if (count < 0x40) {
        r1_D_0018DC40_002E6DB8[count] = fn;
        r1_D_0018DD40_002E6DB8[count] = arg;
        r1_D_0015F564_002E6DB8 = count + 1;
    }
}

/* Runs the next queued callback set. */
typedef void (*Callback_r002E6E08)(void *);
extern volatile int D_L00_001B1950 __attribute__((sda));
extern Callback_r002E6E08 D_L00_001BE4C0[];
extern void *D_L00_001BE5C0[];
void func_L00_002E6E08(void) {
    int i;
    for (i = 0; i < D_L00_001B1950; i++)
        D_L00_001BE4C0[i](D_L00_001BE5C0[i]);
}

/* Runs the next queued callback set. */
typedef void (*Callback_r002E6E80)(void *);
extern volatile int D_L00_001B1954 __attribute__((sda));
extern Callback_r002E6E80 D_L00_001BE6C0[];
extern void *D_L00_001BE7C0[];
void func_L00_002E6E80(void) {
    int i;
    for (i = 0; i < D_L00_001B1954; i++)
        D_L00_001BE6C0[i](D_L00_001BE7C0[i]);
}

#define MACRO_ADDR __attribute__((section(".sdata")))

extern int r1_D_0015F564_002E6EF8 MACRO_ADDR;

 /* GetEffectTex(int, int) */

/*
 * Four parallel callback lists, each a (function, argument) pair of
 * arrays with its own count, plus a "register" and a "run them all"
 * function per list. The counts are reached with retail's one-register
 * macro form, so they are MACRO_ADDR.
 */
typedef void (*DrawCallback_r002E6EF8)(void *);

extern DrawCallback_r002E6EF8 r1_D_0018DC40_002E6EF8[];

extern void *r1_D_0018DD40_002E6EF8[];

/* rac1-decomp src/game/draw.c: func_001F49B0 */
void func_L00_002E6EF8(DrawCallback_r002E6EF8 fn, void *arg) {
    int count = r1_D_0015F564_002E6EF8;
    if (count < 0x40) {
        r1_D_0018DC40_002E6EF8[count] = fn;
        r1_D_0018DD40_002E6EF8[count] = arg;
        r1_D_0015F564_002E6EF8 = count + 1;
    }
}

/* Runs the next queued callback set. */
typedef void (*Callback_r002E6F48)(void *);
extern volatile int D_L00_001B194C __attribute__((sda));
extern Callback_r002E6F48 D_L00_001BE2C0[];
extern void *D_L00_001BE3C0[];
void func_L00_002E6F48(void) {
    int i;
    for (i = 0; i < D_L00_001B194C; i++)
        D_L00_001BE2C0[i](D_L00_001BE3C0[i]);
}





extern int func_0027F128(char *text, int length, char *charset);
extern char D_L00_0028C590[];

int func_L00_002E9100(char *text, int length) {
 return func_0027F128(text, length, D_L00_0028C590);
}

extern char D_L00_0028C930[];

int func_L00_002E9120(char *text, int length) {
 return func_0027F128(text, length, D_L00_0028C930);
}

extern char D_L00_0028CCD0[];

int func_L00_002E9140(char *text, int length) {
 return func_0027F128(text, length, D_L00_0028CCD0);
}

extern void func_0027F1D8(void *a0, void *a1, void *a2);
extern char D_L00_0028C590[];

void func_L00_002E9210(void *a0, void *a1) {
 func_0027F1D8(a0, a1, D_L00_0028C590);
}


extern unsigned long func_0027C878(int);

extern void func_0027F2A8(int, int, unsigned long, char *, int, unsigned long, char *);

void func_L00_002E95C0(int x, int y, unsigned long colour, char *text, int length) {
 unsigned long texture = func_0027C878(3);
 func_0027F2A8(x, y, colour, text, length, texture, D_L00_0028CCD0);
}



extern void func_0027A9F0(void);

extern void func_0027AB40(void);

void func_L00_002EA600(void) {
 func_00284EA8();
 func_0027A9F0();
 func_0027AB40();
}




/* func_L00_002EBE88 is in L00_002E5918-beams.c. */


INCLUDE_ASM("asm/levels", func_L00_002EC248);

INCLUDE_ASM("asm/levels", func_L00_002EC608);

INCLUDE_ASM("asm/levels", func_L00_002EC970);

/* func_L00_002ECFE8 is in L00_002ECFE8.c. */


void func_L00_002ED420(void)
{
}


/* Measured partial layout of the 0x20-byte slots of D_L00_001BECC0. */
typedef struct {
    char pad_00[0x10];
    unsigned short f10;
    unsigned short f12;
    char pad_14[4];
    float f18;
    char pad_1c[4];
} Entry_r002ED808;

extern Entry_r002ED808 D_L00_001BECC0[];

extern float ref_L00_002ED808_00(float, float);

extern void ref_L00_002ED808_01(void *, int, int);

/* Steps the sixteen slots: eases the angle down by five degrees a tick and drops a slot
   when its countdown reaches zero. 0.087266475f is 0x3DB2B8C4 as retail materialises it. */
void func_L00_002ED808(void) {
    Entry_r002ED808 *e = D_L00_001BECC0;
    int i = 15;

    do {
        if ((short)e->f10 > 0) {
            e->f18 = ref_L00_002ED808_00(e->f18, 0.087266475f);
            if ((short)e->f10 >= 13)
                e->f12 += 5;
            else
                e->f12 -= 5;
            e->f10--;
            if ((short)e->f10 <= 0)
                ref_L00_002ED808_01(e, 0, 0x20);
        }
        i--;
        e++;
    } while (i >= 0);
}

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9850. */
ASM_FUNC("asm/levels", func_L00_002EDC90);

/* Original assembly: `lwc1; nop; jr $ra; mul.s` keeps a load-delay nop before the return that this cc1 never emits (MATCHING-BLOCKERS 4); its neighbours are RAC1 fast_vector_math original assembly. */
ASM_FUNC("asm/levels", func_L00_002EDCB8);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9850. */
ASM_FUNC("asm/levels", func_L00_002EDCC8);

/* Original assembly: `lwc1; nop; jr $ra; mul.s` keeps a load-delay nop before the return that this cc1 never emits (MATCHING-BLOCKERS 4); its neighbours are RAC1 fast_vector_math original assembly. */
ASM_FUNC("asm/levels", func_L00_002EDCF0);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9850. */
ASM_FUNC("asm/levels", func_L00_002EDD00);

/* Original assembly: `lwc1; nop; jr $ra; mul.s` keeps a load-delay nop before the return that this cc1 never emits (MATCHING-BLOCKERS 4); its neighbours are RAC1 fast_vector_math original assembly. */
ASM_FUNC("asm/levels", func_L00_002EDD28);

/* Original assembly: `lwc1; nop; jr $ra; mul.s` keeps a load-delay nop before the return that this cc1 never emits (MATCHING-BLOCKERS 4); its neighbours are RAC1 fast_vector_math original assembly. */
ASM_FUNC("asm/levels", func_L00_002EDD38);

/* func_L00_002EE050 (the two-argument float maximum) is matched in its own
   unit, src/levels/shared/L00_002EE050.c: it needs the -O1 -ffast-math
   profile, which changes the other bodies of this file. */

ASM_FUNC("asm/levels", func_L00_002EE058);

ASM_FUNC("asm/levels", func_L00_002EE078);

/* Original assembly: `sd; nop; jr $ra; sw` keeps a nop before the return that this cc1 never emits (MATCHING-BLOCKERS 4); its neighbours are RAC1 fast_vector_math original assembly. */
ASM_FUNC("asm/levels", func_L00_002EE0C0);

ASM_FUNC("asm/levels", func_L00_002EE290);

ASM_FUNC("asm/levels", func_L00_002EE340);

ASM_FUNC("asm/levels", func_L00_002EE4D8);

ASM_FUNC("asm/levels", func_L00_002EE660);

/* Takes three floats, computes a value from the second and first, negates the third when that value is not positive, clamps the third against that value and its negation (recomputing it in each branch), then calls a helper with the first and the clamped third. */
void func_L00_002EF548(float a, float b, float c)
{
    float t = func_00283BE0_6(b, a);

    if (t <= 0.0f)
        c = -c;
    if (func_00282C48_8(t) < c)
        c = func_00282C48_8(t);
    else if (c < -func_00282C48_8(t))
        c = -func_00282C48_8(t);
    func_00283B98_10(a, c);
}


