#include "include_asm.h"

extern int func_00336A40(void *);

extern int func_0027C878_2(int);

extern void func_0027F640(float, float, float, int, int, int, int, int);

typedef int s32;

typedef unsigned char u8;

typedef float f32;

typedef unsigned int u32;

extern void D_00115E38(char *assertion, int line, char *file);

extern char D_L00_001ADDD8[];

extern char D_L00_001ADDF8[];

typedef struct { unsigned int f0, f4, f8, f12, f16, f20; } T;

extern char D_L00_001ADDD8_1[];

extern char D_L00_001ADE20[];

extern void D_00115E38_1(char *a0, int a1, char *a2);

extern int func_L00_002E9100(char *, int);

extern void func_00115AC0_1(void *, int, int);

extern void func_00337E98_1(void *, int, int, float, float);

extern int func_0027F178(unsigned char *text, int length); /* text width */

/* Text box laid out by func_00337C10/func_00337E30: text at +0xA8, its line table at +0x1D8. */
typedef struct {
    float *position;
    float *scale;
    unsigned char pad08[0xA0];
    unsigned char text[0x100];
    int unused1A8;
    int unused1AC;
    int lineCount;
    int unused1B4;
    int duration;
    unsigned char pad1BC[0x18];
    int maxWidth;
    unsigned char *lines[30];
} TextBox;

extern int func_00115DA8(char *, char *, ...); /* formats into a buffer */
extern char D_001ADB58[], D_001ADB68[], D_001ADB78[], D_001ADB90[];
extern char D_001ADBB0[], D_001ADBB8[], D_001ADBC8[];
extern int D_001A7340[] __attribute__((sda)); /* screen size: [1] = height */
extern void func_00280190(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void func_00280200(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void func_00280270(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void func_0027EB88(int top, int bottom, int left, int right, int alpha, int color);
extern void func_003384C0(char *, unsigned int, unsigned int, float, float, float, float);

/* Complete boot bodies from liolu PRs #72 and #75; refreshed in one combined batch. */
void func_PAL_003388E8(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x40) = a1; }

extern void func_00300618(void *);

extern int D_001ADB10 __attribute__((sda));





extern void *func_003361A8(void *);

extern int *func_00335E20(void *);
extern void func_00335E68(void *, int);
extern void func_003361E0(void *, void *, void *);
extern void func_00336390(void *, int, int);
extern void func_003363C0(void *, float);
extern void *func_00115484(void *, int, unsigned int); /* memset */
extern char D_001ADB40[]; /* "aTxBrack" */
extern char D_001ADB50[]; /* "aTxTop" */
extern char *D_001A8CFC[] __attribute__((sda));



/* Partial view of the shared screen/render state (see src/game/00274128.c). */
typedef struct {
    char pad[0xB0];
    float fB0;
} ViewState;
extern ViewState D_001B9040;
extern void func_0027AB40(void);
extern int func_00335E08(void);
extern void func_00300A00(int, float, float, unsigned int, float, float, float);

extern char *func_00288FB8(int);

extern int func_00115DA8(char *, char *, ...);