#include "include_asm.h"
#include "names.h"

extern int hud_draw_widget_text(void *);

extern int func_0027C878_2(int);

extern void FontPrintScaled(float, float, float, int, int, int, int, int);

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

extern int text_measure_width_first_set(char *, int);

extern void func_00115AC0_1(void *, int, int);

extern void func_00337E98_1(void *, int, int, float, float);

extern int text_measure_width_small(unsigned char *text, int length); /* text width */

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

extern int sprintf(char *, char *, ...); /* formats into a buffer */
extern char D_001ADB58[], D_001ADB68[], D_001ADB78[], D_001ADB90[];
extern char D_001ADBB0[], D_001ADBB8[], D_001ADBC8[];
extern int g_screen_width[] __attribute__((sda)); /* screen size: [1] = height */
extern void text_draw_window_small(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void text_draw_window_medium(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void text_draw_window_large(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void gfx_draw_rounded_box(int top, int bottom, int left, int right, int alpha, int color);
extern void text_box_draw_frame(char *, unsigned int, unsigned int, float, float, float, float);

/* Complete boot bodies from liolu PRs #72 and #75; refreshed in one combined batch. */
void func_PAL_003388E8(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x40) = a1; }

extern void func_00300618(void *);

extern int g_selected_item_material __attribute__((sda));





extern void *object_construct_derived_a(void *);

extern int *object_get_fourth_field(void *);
extern void object_set_flag_value(void *, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void object_set_helper_result(void *, int, int);
extern void object_set_value_float(void *, float);
extern void *memset(void *, int, unsigned int); /* memset */
extern char D_001ADB40[]; /* "aTxBrack" */
extern char D_001ADB50[]; /* "aTxTop" */
extern char *D_001A8CFC[] __attribute__((sda));



/* Partial view of the shared screen/render state (see src/game/00274128.c). */
typedef struct {
    char pad[0xB0];
    float fB0;
} ViewState;
extern ViewState D_001B9040;
extern void UpdateViewContext(void);
extern int object_get_stored_counter(void);
extern void gfx_draw_scaled_object_two_axes(int, float, float, unsigned int, float, float, float);

extern char *GetLocalizedString(int);

extern int sprintf(char *, char *, ...);