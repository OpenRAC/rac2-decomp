#include "include_asm.h"
#include "names.h"

extern int hud_draw_widget_text(void *);

extern long long func_0027C878_2(int);

extern void FontPrintScaled(float, float, float, int, int, int, int, int);

typedef int s32;

typedef unsigned char u8;

typedef float f32;

typedef unsigned int u32;

extern void g_assert_fail(char *assertion, int line, char *file);

extern char g_str_pool_cell_file[];

extern char g_str_pool_init_message[];

typedef struct { unsigned int f0, f4, f8, f12, f16, f20; } T;

extern char D_L00_001ADDD8_1[];

extern char g_str_pool_alloc_message[];

extern void D_00115E38_1(char *a0, int a1, char *a2);

extern int text_measure_width_first_set(char *, int);

extern char *func_00115AC0_1(void *, int, int);

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
extern char g_str_framed_box_fmt_single_spaced[], g_str_framed_box_fmt_double_spaced[], g_str_framed_box_fmt_single_plain[], g_str_framed_box_fmt_double_plain[];
extern char g_str_framed_box_fmt_single_short[], g_str_framed_box_fmt_double_short[], g_str_string_format[];
extern int g_screen_width[] __attribute__((sda)); /* screen size: [1] = height */
extern void text_draw_window_small(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void text_draw_window_medium(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void text_draw_window_large(unsigned short *layout, unsigned long style, unsigned char *text, int length);
extern void gfx_draw_rounded_box(int top, int bottom, int left, int right, int alpha, int color);
extern void text_box_draw_frame(char *, unsigned int, unsigned int, float, float, float, float);

/* Complete boot bodies from liolu PRs #72 and #75; refreshed in one combined batch. */
void func_PAL_003388E8(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x40) = a1; }

extern void *func_00300618(void *);

extern int g_selected_item_material __attribute__((sda));





extern void *object_construct_derived_a(void *);

extern int *object_get_fourth_field(void *);
extern void object_set_flag_value(void *, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void object_set_helper_result(void *, int, int);
extern void object_set_value_float(void *, float);
extern void *memset(void *, int, unsigned int); /* memset */
extern char g_str_text_bracket_name[]; /* "aTxBrack" */
extern char g_str_text_top_name[]; /* "aTxTop" */
extern char *g_resident_data_base[] __attribute__((sda));



/* Partial view of the shared screen/render state (see src/game/00274128.c). */
typedef struct {
    char pad[0xB0];
    float fB0;
} ViewState;
extern ViewState g_view_params;
extern void UpdateViewContext(void);
extern int object_get_stored_counter(void);
extern void gfx_draw_scaled_object_two_axes(int, float, float, unsigned int, float, float, float);

extern char *GetLocalizedString(int);

extern int sprintf(char *, char *, ...);