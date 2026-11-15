#include "include_asm.h"
#include "names.h"

extern void func_00284EA8(void);

typedef long s64;

extern void func_002CBC58(s64);

extern float func_00283BE0_6(float b, float a);

extern float func_00282C48_8(float t);

extern void func_00283B98_10(float a, float c);

/* Calls the engine routine at 0x00284EA8 with no arguments. */
void func_L00_002E5918(void) {
 AppendDrawListHeader();
}


/* Calls an engine routine with zero. */
void func_L00_002E6448(void) {
 DrawPauseMenuPanels(0);
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
/* Adds a draw callback and its argument to the first list, if there is room. */
void func_L00_002E6CF0(DrawCallback_r002E6CF0 fn, void *arg) {
    int count = r1_D_0015F564_002E6CF0;
    if (count < 0x40) {
        r1_D_0018DC40_002E6CF0[count] = fn;
        r1_D_0018DD40_002E6CF0[count] = arg;
        r1_D_0015F564_002E6CF0 = count + 1;
    }
}

/* Runs every callback in the first list with its argument. */
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
/* Adds a draw callback and its argument to the second list, if there is room. */
void func_L00_002E6DB8(DrawCallback_r002E6DB8 fn, void *arg) {
    int count = r1_D_0015F564_002E6DB8;
    if (count < 0x40) {
        r1_D_0018DC40_002E6DB8[count] = fn;
        r1_D_0018DD40_002E6DB8[count] = arg;
        r1_D_0015F564_002E6DB8 = count + 1;
    }
}

/* Runs every callback in the second list with its argument. */
typedef void (*Callback_r002E6E08)(void *);
extern volatile int D_L00_001B1950 __attribute__((sda));
extern Callback_r002E6E08 D_L00_001BE4C0[];
extern void *D_L00_001BE5C0[];
void func_L00_002E6E08(void) {
    int i;
    for (i = 0; i < D_L00_001B1950; i++)
        D_L00_001BE4C0[i](D_L00_001BE5C0[i]);
}

/* Runs every callback in the fourth list with its argument. */
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
/* Adds a draw callback and its argument to the third list, if there is room. */
void func_L00_002E6EF8(DrawCallback_r002E6EF8 fn, void *arg) {
    int count = r1_D_0015F564_002E6EF8;
    if (count < 0x40) {
        r1_D_0018DC40_002E6EF8[count] = fn;
        r1_D_0018DD40_002E6EF8[count] = arg;
        r1_D_0015F564_002E6EF8 = count + 1;
    }
}

/* Runs every callback in the third list with its argument. */
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

/* Measures the width of text using the first character set. */
int func_L00_002E9100(char *text, int length) {
 return measure_text_width(text, length, D_L00_0028C590);
}

extern char D_L00_0028C930[];

/* Measures the width of text using the second character set. */
int func_L00_002E9120(char *text, int length) {
 return measure_text_width(text, length, D_L00_0028C930);
}

extern char D_L00_0028CCD0[];

/* Measures the width of text using the third character set. */
int func_L00_002E9140(char *text, int length) {
 return measure_text_width(text, length, D_L00_0028CCD0);
}

extern void func_0027F1D8(void *a0, void *a1, void *a2);
extern char D_L00_0028C590[];

/* Runs a text helper on two buffers with the first character set. */
void func_L00_002E9210(void *first, void *second) {
 MeasureTextWidthScaled(first, second, D_L00_0028C590);
}


extern unsigned long func_0027C878(int);

extern void func_0027F2A8(int, int, unsigned long, char *, int, unsigned long, char *);

/* Draws coloured text at a screen position using the third character set. */
void func_L00_002E95C0(int x, int y, unsigned long colour, char *text, int length) {
 unsigned long texture = GetEffectTextureDescriptor(3);
 DrawTextLine(x, y, colour, text, length, texture, D_L00_0028CCD0);
}



extern void func_0027A9F0(void);

extern void func_0027AB40(void);

/* Refreshes the engine state and the view. */
void func_L00_002EA600(void) {
 AppendDrawListHeader();
 InitViewContext();
 UpdateViewContext();
}




/* func_L00_002EBE88 is in L00_002E5918-beams.c. */


typedef struct { float x,y,z,w; } BurstVector;
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void func_00283098(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_00282C88(void *);
extern int func_00283D38(int, int, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Spawns a burst of sparks around an object, with colours picked by the palette number. */
void func_L00_002EC248(char *object, void *positionOffset, void *velocityOffset,
                     int count, int palette, float positionSpread, float velocitySpread,
                     float width, float gravity, float duration)
{
    BurstVector position, velocity, endpoint;
    int start, end, i;
    int first, middle, last;
    int texture = 0x1003C;
    float scale, small;
    gravity *= 0.00027777778f;
    palette &= 0xFF;
    for (i = 0; i < count; i++) {
        RandomDirectionVector(&position, 0.0f, positionSpread);
        FastVecAdd(&position, &position, positionOffset);
        LocalOffsetToWorld(object, &position, position.x, position.y, position.z);
        RandomDirectionVector(&velocity, 0.0f, velocitySpread);
        FastVecAdd(&velocity, &velocity, velocityOffset);
        matrix_mul_vec3(&velocity, &velocity, object + 0xC0);
        scale = duration * RandomFloatRange(0.5f, 1.5f);
        small = scale * 10.0f;
        first = FloatToInt(small);
        middle = FloatToInt(scale * 40.0f);
        last = FloatToInt(small);
        velocity.w = width * RandomFloatRange(0.1f, 0.4f);
        ClearVector128(&endpoint);
        endpoint.z = -gravity * (float)(first + middle + last);
        FastVecAdd(&endpoint, &endpoint, &velocity);
        switch (palette) {
        case 1:
            start = FastTweenColor(0x80102040, 0x801010A0, RandomFloatRange(0.0f, 1.0f));
            end = FastTweenColor(0x00102040, 0x001010A0, RandomFloatRange(0.0f, 1.0f));
            break;
        case 3:
            start = FastTweenColor(0x80201608, 0x80402510, RandomFloatRange(0.0f, 1.0f));
            end = FastTweenColor(0x00201608, 0x00402510, RandomFloatRange(0.0f, 1.0f));
            break;
        case 2:
            start = FastTweenColor(0x80104010, 0x8020A020, RandomFloatRange(0.0f, 1.0f));
            end = FastTweenColor(0x00104010, 0x0020A020, RandomFloatRange(0.0f, 1.0f));
            break;
        case 0:
        default:
            start = FastTweenColor(0x80004080, 0x80408080, RandomFloatRange(0.0f, 1.0f));
            end = FastTweenColor(0x00004080, 0x00408080, RandomFloatRange(0.0f, 1.0f));
            break;
        }
        SpawnTrailParticle_002BAA28(&position, &velocity, &endpoint, start, end,
                     first, middle, last, texture);
    }
}

/* func_L00_002EC608 is defined in L00_002EC608-glow.c. */


/* func_L00_002ECFE8 is in L00_002ECFE8.c. */


/* Does nothing. */
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
    Entry_r002ED808 *entry = D_L00_001BECC0;
    int i = 15;

    do {
        if ((short)entry->f10 > 0) {
            entry->f18 = ref_L00_002ED808_00(entry->f18, 0.087266475f);
            if ((short)entry->f10 >= 13)
                entry->f12 += 5;
            else
                entry->f12 -= 5;
            entry->f10--;
            if ((short)entry->f10 <= 0)
                ref_L00_002ED808_01(entry, 0, 0x20);
        }
        i--;
        entry++;
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
void func_L00_002EF548(float angle, float other, float amount)
{
    float limit = func_00283BE0_6(other, angle);

    if (limit <= 0.0f)
        amount = -amount;
    if (func_00282C48_8(limit) < amount)
        amount = func_00282C48_8(limit);
    else if (amount < -func_00282C48_8(limit))
        amount = -func_00282C48_8(limit);
    func_00283B98_10(angle, amount);
}


