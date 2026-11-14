#include "include_asm.h"

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

extern void func_0027C660(void);

void func_0027C540(long);

void func_0027C660(void);

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

extern void func_0027C540(long arg0);

/* External functions declared with exact aliases from task.externals */
extern void func_0027C540(long param_1);

extern void func_0029C960(void);

extern char F7cb419c1_D_001F2840[];

extern int F7cb419c1_FUN_002DE618(int arg);

/* Candidate function: FUN_002d3390 */
unsigned long long func_002D3390(void)
{
    func_0027C540(0);
    func_0029C960();
    func_0027C660();
    return 0;
}

extern char *D_001A8CFC[] __attribute__((sda));
extern float ref_L00_002D33C0_00[];
extern void ref_L00_002D33C0_01(unsigned char *, float *);

int func_002D33C0(void)
{
    if (D_001A8CFC[0] != 0)
        ref_L00_002D33C0_01((unsigned char *)(D_001A8CFC[0] + 0x3EDB8), ref_L00_002D33C0_00);
    return 0;
}

typedef struct {
    char reserved00[0x1C0];
    int message;
    int flags;
} MenuGameState;

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;

extern MenuGameState D_00138180;
extern CallbackState D_001F2840;
extern void func_0029C5D0(int);

int func_002D3400(void)
{
    int flags = D_00138180.flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(D_001F2840.source + 0xE0);
        if (value != 0)
            D_001F2840.value = value;
        else if (D_001F2840.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        func_0029C5D0(D_00138180.message);
    return result;
}

extern void func_0029C5A0(void);

int func_002D3488(void) {
    func_0027C540(0);
    func_0029C5A0();
    func_0027C660();
    return 0;
}

extern char *D_001A8CFC[] __attribute__((sda));
extern void func_003435B0(char *, int);
extern void func_00343538(char *, char *);
extern void func_00343580(char *);
extern void func_003435A0(char *, char *);
extern char D_00259F58[];
extern char D_0025D0E0[];

int func_002D34B8(void)
{
    if (D_001A8CFC[0] != 0) {
        func_003435B0(D_001A8CFC[0] + 0x3C108, 0);
        func_00343538(D_001A8CFC[0] + 0x3C108, D_00259F58);
        func_00343580(D_001A8CFC[0] + 0x3C108);
        func_003435A0(D_001A8CFC[0] + 0x3C108, D_0025D0E0);
    }
    return 0;
}

extern char D_00259CE0[];
extern char D_0025D288[];

int func_002D3538(void)
{
    if (D_001A8CFC[0] != 0) {
        func_003435B0(D_001A8CFC[0] + 0x3C108, 1);
        func_00343538(D_001A8CFC[0] + 0x3C108, D_00259CE0);
        func_00343580(D_001A8CFC[0] + 0x3C108);
        func_003435A0(D_001A8CFC[0] + 0x3C108, D_0025D288);
    }
    return 0;
}



/* func_002D36A0 is in its -G8 sibling. */

extern int func_0028E588(int, int);
extern double func_001234F0(float);
extern int func_00123028(double, double);
extern double func_00122A98(double, double);
extern double func_00122B00(double, double);
extern int func_00123130(double);
extern int func_0028EA58(int, int, int, int, int, int *);
typedef struct {
    int value, displayChoice, selectionMask, requiredBits, icon;
} PreviewChoice;
extern PreviewChoice D_0026CFD0[];
extern int D_001B23A0[] __attribute__((sda));
extern float D_001B23A4[] __attribute__((sda));
/* A screen coordinate scaled for the display; mode 1 also takes an offset in unscaled pixels. */
static __inline__ int scaled_screen_coord(int mode, float value, float offset)
{
    float scaled = value * D_001B23A4[0] + 0.5f;
    if (mode == 1)
        return (int)(scaled + offset);
    return (int)scaled;
}
/* A size scaled for the display; any mode but 0 also takes a whole-pixel adjustment. */
static __inline__ int scaled_screen_size(int mode, float value, int adjust)
{
    if (mode != 0)
        return (int)(value * D_001B23A4[0] + 0.5f) + adjust;
    return (int)(value * D_001B23A4[0] + 0.5f);
}

/* Draws the icon of preview choice `index` at column `x`, fading its left and right edges by their
   distance from the middle of the 512-wide screen. */
int func_002D3D88(int index, int x)
{
    int colors[4];
    int leftAlpha;
    int rightAlpha;
    int right;
    int texture;
    int y;
    int height;
    int left = x + 2;
    int baseColor = 0xf0f0b0;
    double distance;
    int mode;

    texture = func_0028E588(0xea97, D_0026CFD0[index].icon);
    distance = func_001234F0(256.0f - (float)left);
    if (func_00123028(distance, 0.0) < 0)
        distance = func_00122A98(0.0, distance);
    leftAlpha = 128 - func_00123130(func_00122B00(distance, 0.75));
    distance = func_001234F0(256.0f - (float)(x + 40));
    if (func_00123028(distance, 0.0) < 0)
        distance = func_00122A98(0.0, distance);
    rightAlpha = 128 - func_00123130(func_00122B00(distance, 0.75));
    if (leftAlpha < 0)
        leftAlpha = 0;
    if (rightAlpha < 0)
        right = 0;
    else
        right = rightAlpha;
    leftAlpha <<= 24;
    right <<= 24;
    colors[2] = colors[0] = leftAlpha | baseColor;
    colors[3] = colors[1] = right | baseColor;
    mode = D_001B23A0[0];
    y = scaled_screen_coord(mode, 334.0f, 4.0f);
    height = scaled_screen_size(mode, 40.0f, 0);
    return func_0028EA58(texture, left, y, 40, height, colors);
}

/* func_002D3FA0 is defined in 002D3FA0-options-g8.c. */

/* func_002D4948 is defined in 002D4948-options-g8.c. */

int func_002D4E10(void)
{
    char *p = F7cb419c1_D_001F2840;

    *(int *)(p + 460) = F7cb419c1_FUN_002DE618(*(int *)(p + 460));
    return 0;
}

/* func_002D4E48 is in the -G8 sibling. */


extern int D_0025BA80;

int func_002D5038(void) {
    D_0025BA80 = 0;
    return 0;
}



extern char *D_001A8CFC[] __attribute__((sda));
extern void *func_00341558(void *);

int func_002D5290(char *object) {
    if (D_001A8CFC[0] != 0)
        *(void **)(object + 0x34) = func_00341558(D_001A8CFC[0] + 0x3BE08);
    return 0;
}

/* func_002D52D8 is in the -G8 sibling. */

/* func_002D53F0 is defined in 002D53F0.c. */

extern void func_00287E80(void);
extern void func_00341540(char *, char *, char *, char *);
extern void func_00341610(char *, int);
extern char D_002615F8[], D_00261698[], D_00261750[];

int func_002D5480(void)
{
    func_00287E80();
    if (D_001A8CFC[0] != 0) {
        func_00341540(D_001A8CFC[0] + 0x3BE08, D_002615F8, D_00261698, D_00261750);
        func_00341610(D_001A8CFC[0] + 0x3BE08, 1);
    }
    return 0;
}

extern int D_00138344;
extern void func_0029CF08(int);

int func_002D54F0(void) {
    func_0029CF08(D_00138344);
    return 0;
}

extern int D_00138344;
extern void func_0029CF08(int);

int func_002D5518(void) {
    func_0029CF08(D_00138344);
    return 0;
}
