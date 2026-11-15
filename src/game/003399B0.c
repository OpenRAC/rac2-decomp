#include "include_asm.h"
#include "names.h"

extern int D_L00_001A8FD8 __attribute__((sda));

extern int D_L00_001A8FDC __attribute__((sda));

extern void func_0033AE20(int *p, int flag);

extern void func_0033AF48_1(int *p);

extern void func_00336320(int *p);

extern void func_L00_0042BAD0_1(char *object);

extern void func_L00_0042C290_1(char *object);

extern void F8ad956d6_FUN_00336320(char *target);

extern void F8ad956d6_FUN_002FC560(int marker, int code);

extern void F8ad956d6_FUN_00295F60(int first, int second);

extern void F8ad956d6_FUN_002DAF68(char *target);

extern void F8ad956d6_FUN_00336A78(char *target);

extern void func_L00_0042BAD0_5(void *);

extern void func_L00_0042BFF8_4(void *);

extern void func_L00_0042C290_5(void *);

typedef float f32;

typedef unsigned char u8;

typedef int s32;

extern int func_0033AB50(int);

extern void F7d9c8805_FUN_003361A8(int);

extern void F7d9c8805_FUN_00336968(int);

extern void func_0033AE18(unsigned char *owner, int value);

/* Lazily initialises a sub-object of the argument behind two global flags and a field, runs one guarded setup step on it, then hands it to two callees. */
/* Draws a menu screen and its button prompt bar, then updates one more part of the screen. */
void func_003399B0(int *obj)
{
    if (D_L00_001A8FD8 != 0 || D_L00_001A8FDC != 0 || obj[192] != 0)
        SetButtonPromptExtrasEnabled(obj + 2, 0);
    if (obj[191] == 1)
        SetButtonPromptExtrasEnabled(obj + 2, 1);
    func_0033AF48_1(obj + 2);
    DrawScreenElementAtStoredPosition(obj + 170);
}

/* calls two one-argument functions on a sequence of sub-objects of the argument (four at 8..236 stride 76, nine at 312..888 stride 72) and returns the argument */
/* Cleans up every picture and text piece of the list screen and gives the screen back. */
char *func_00339A38(char *object)
{
    func_L00_0042BAD0_1(object + 8);
    func_L00_0042BAD0_1(object + 84);
    func_L00_0042BAD0_1(object + 160);
    func_L00_0042BAD0_1(object + 236);
    func_L00_0042C290_1(object + 312);
    func_L00_0042C290_1(object + 384);
    func_L00_0042C290_1(object + 456);
    func_L00_0042C290_1(object + 528);
    func_L00_0042C290_1(object + 600);
    func_L00_0042C290_1(object + 672);
    func_L00_0042C290_1(object + 744);
    func_L00_0042C290_1(object + 816);
    func_L00_0042C290_1(object + 888);
    return object;
}


/* func_00339AD0 is matched in 003399B0-g8.c (-G8 small data). */


typedef struct {
    float x, y;
} Point2_00339F28;

extern void *func_00115484(void *, int, int);
extern void func_00335F88(void *, float, float, float, float);
extern void func_00335E38(void *, float, float, float, float);
extern int func_002DF1F8(void *, int);
extern int func_00288FB8(int);
extern void func_00336A38(void *, int);
extern Point2_00339F28 D_001ADCE0, D_001ADCE8, D_001ADCF0, D_001ADCF8, D_001ADD00;
extern char D_001C4FA0[];
extern int D_00258D70[];
extern char D_001ADC88[];

/* Lays the screen out: scales the six list widgets, places every widget at its offset from
   the position block, then labels the zoom widget from the current planet's text id (" " when
   it has none). The second argument is unused. func_00115484 (memset) and func_002DF1F8 must
   be declared as returning a value: the $v0 they set right before the struct copies and the
   table lookup is what pushes those registers to retail's $v1/$v0 choice. */
int func_00339F28(char *obj, int unused)
{
    Point2_00339F28 z0, z1, z2, z3;
    Point2_00339F28 title, list, prev, next, scale;
    char *base;
    int index;

    memset(&z0, 0, 8);
    memset(&z1, 0, 8);
    memset(&z2, 0, 8);
    memset(&z3, 0, 8);
    title = D_001ADCE0;
    list = D_001ADCE8;
    prev = D_001ADCF0;
    next = D_001ADCF8;
    scale = D_001ADD00;
    SetSecondFloat4(obj + 0x180, scale.x, scale.y, 0.0f, 0.0f);
    SetSecondFloat4(obj + 0x1C8, scale.x, scale.y, 0.0f, 0.0f);
    SetSecondFloat4(obj + 0x210, scale.x, scale.y, 0.0f, 0.0f);
    SetSecondFloat4(obj + 0x258, scale.x, scale.y, 0.0f, 0.0f);
    SetSecondFloat4(obj + 0x2A0, scale.x, scale.y, 0.0f, 0.0f);
    SetSecondFloat4(obj + 0x2E8, scale.x, scale.y, 0.0f, 0.0f);
    SetFirstFloat4(obj + 0x8, z0.x + (*(float **)(obj + 4))[0],
                  z0.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    SetFirstFloat4(obj + 0x54, z3.x + (*(float **)(obj + 4))[0],
                  z3.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    SetFirstFloat4(obj + 0xA0, z1.x + (*(float **)(obj + 4))[0],
                  z1.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    SetFirstFloat4(obj + 0xEC, z2.x + (*(float **)(obj + 4))[0],
                  z2.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    SetFirstFloat4(obj + 0x138, title.x + (*(float **)(obj + 4))[0],
                  title.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    SetFirstFloat4(obj + 0x180, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    SetFirstFloat4(obj + 0x1C8, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 18.0f, 0.0f, 0.0f);
    SetFirstFloat4(obj + 0x210, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 36.0f, 0.0f, 0.0f);
    SetFirstFloat4(obj + 0x258, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 54.0f, 0.0f, 0.0f);
    SetFirstFloat4(obj + 0x2A0, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 72.0f, 0.0f, 0.0f);
    SetFirstFloat4(obj + 0x2E8, list.x + 8.0f + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 90.0f, 0.0f, 0.0f);
    SetFirstFloat4(obj + 0x330, prev.x + (*(float **)(obj + 4))[0],
                  prev.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    SetFirstFloat4(obj + 0x378, next.x + (*(float **)(obj + 4))[0],
                  next.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    base = gMapOverlayState;
    FormatLocationName(obj + 0x3C0, *(int *)(base + 0x230));
    index = D_00258D70[*(int *)(base + 0x230) * 2 + 1];
    if (index >= 0)
        SetWidgetField40(obj + 0x378, GetLocalizedString(index));
    else
        SetWidgetField40(obj + 0x378, (int)D_001ADC88);
    return 0;
}

/* Draws the whole list screen (its pictures and texts) if the screen is switched on. */
void func_0033A3E0(char *object)
{
    char *screen = object;

    if (*(int *)(screen + 1024) == 0)
        return;
    F8ad956d6_FUN_00336320(screen + 8);
    F8ad956d6_FUN_00336320(screen + 84);
    F8ad956d6_FUN_002FC560(66, 68);
    F8ad956d6_FUN_002FC560(71, 11);
    F8ad956d6_FUN_00295F60(0, 1);
    F8ad956d6_FUN_002DAF68(0);
    F8ad956d6_FUN_00336320(screen + 160);
    F8ad956d6_FUN_00336320(screen + 236);
    F8ad956d6_FUN_00336A78(screen + 312);
    F8ad956d6_FUN_00336A78(screen + 384);
    F8ad956d6_FUN_00336A78(screen + 456);
    F8ad956d6_FUN_00336A78(screen + 528);
    F8ad956d6_FUN_00336A78(screen + 600);
    F8ad956d6_FUN_00336A78(screen + 672);
    F8ad956d6_FUN_00336A78(screen + 744);
    F8ad956d6_FUN_00336A78(screen + 816);
    F8ad956d6_FUN_00336A78(screen + 888);
}

/* walks four 76-byte records calling one function on each, then calls two more functions on later fields and returns its argument */
/* Cleans up the four picture pieces and two other parts of the title screen and gives it back. */
void *func_0033A4A0(char *screen)
{
    int i;
    char *piece = screen + 4;

    for (i = 3; i != -1; i--) {
        func_L00_0042BAD0_5(piece);
        piece += 76;
    }
    func_L00_0042BFF8_4(screen + 308);
    func_L00_0042C290_5(screen + 368);
    return screen;
}


typedef struct { float x, y, width, height; } TitlePosition;
extern void func_00336710(void *, void *, void *);
extern int func_00335E20(void *);
extern void func_003369A8(void *, void *, void *);
extern int *func_00336DA8(int, int);
extern int func_00336E40(void *);
extern float D_001B23A4 __attribute__((sda));
/* Allocate the title position (scaled y, rounded) and set up its two labels.
 * The scale is read after the x store: retail issues 300.0 before it. */
void func_0033A520(unsigned char *obj, void *arg)
{
    float value;
    TitlePosition *p;
    char *text;

    *(int *)(obj + 0x1F8) = 0;
    *(void **)(obj + 0x200) = arg;
    if (arg != 0) {
        int *alloc = ReturnSecondArgument(16, AllocPoolCell(arg));
        *(int **)(obj + 0x1FC) = alloc;
        alloc[1] = 0;
        alloc[2] = 0;
        alloc[3] = 0;
        alloc[0] = 0;
    }
    do {
        float position;
        int y;
        p = *(TitlePosition **)(obj + 0x1FC);
        p->x = 70.0f;
        position = 300.0f;
        y = (int)(D_001B23A4 * position + 0.5f);
        value = y;
    } while (0);
    text = D_001ADC88;
    p = *(TitlePosition **)(obj + 0x1FC);
    p->y = value;
    InitDerivedObjectC(obj + 0x134, text, *(void **)(obj + 0x200));
    SetSecondFloat4(obj + 0x134, 24.0f, 24.0f, 0.0f, 0.0f);
    *(int *)GetFieldC(obj + 0x134) = 0x60F0F0B0;
    value = 65.0f;
    *(float *)(obj + 0x204) = value;
    InitWidgetDefaults(obj + 0x170, text, *(void **)(obj + 0x200));
    *(int *)GetFieldC(obj + 0x170) = 0x80F0F0F0;
    SetSecondFloat4(obj + 0x170, 0.7f, 0.7f, 0.0f, 0.0f);
}

/* func_0033A688 is matched in 003399B0-g8.c (-G8 small data). */

/* func_0033A6D8 is matched in 003399B0-g8.c (-G8 small data). */

/* Measured target: byte-identical across all 27 levels. */
/* Sets how wide the circle of menu entries is. */
void func_0033A9C8(u8 *menu, f32 radius) { *(f32 *)(menu + 0x204) = radius; }

/* lot6 -- measured bodies with sizes recorded in the catalogue. */
/* Sets the display mode of one entry in the circle menu. */
void func_0033A9D0(u8 *menu, s32 index, s32 mode) { menu += index * 4; *(s32 *)(menu + 0x1B8) = mode; }

/* writes the value if it is below the maximum; byte-identical across all 27 levels. */
/* Selects an entry in the circle menu if the number is within the entry count. */
void func_0033A9E0(u8 *menu, s32 index) { if (index < *(s32 *)(menu + 0x1F8)) *(s32 *)(menu + 0x208) = index; }

/* Measured target: byte-identical across all 27 levels. */
/* Turns the circle menu on or off. */
void func_0033A9F8(u8 *menu, s32 enabled) { *(s32 *)(menu + 0x20c) = enabled; }

/* Cleans up the five icon pieces and three text pieces of the button prompt bar and gives it back. */
int func_0033AB50(int bar)
{
	char *piece = (char *)bar + 12;
	int i;

	for (i = 4; i != -1; i--) {
		F7d9c8805_FUN_003361A8(piece);
		piece += 76;
	}
	F7d9c8805_FUN_00336968(bar + 408);
	F7d9c8805_FUN_00336968(bar + 480);
	F7d9c8805_FUN_00336968(bar + 552);
	return bar;
}


/* func_0033ABD8 is matched in 003399B0-g8.c (-G8 small data). */

/* Measured target: byte-identical across all 27 levels. */
/* Turns the text labels of the button prompt bar on or off. */
void func_0033AE18(u8 *bar, s32 enabled) { *(s32 *)(bar + 0x290) = enabled; }
