#include "include_asm.h"
#include "names.h"
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults(void *, void *, void *);
extern void hud_set_widget_field_a(void *, int);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, int);
extern int list_screen_layout(void *, int);
extern char D_001ADC10[], D_001ADC18[], D_001ADC20[], D_001ADC28[], D_001ADC30[];
extern char D_001ADC38[], D_001ADC40[], D_001ADC50[];
extern char D_001ADCA8[], D_001ADCB8[], D_001ADCC0[], D_001ADCC8[], D_001ADCD0[];
extern char *D_001A8CFC[] __attribute__((sda));
extern char D_001ADCA0[8] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern int *object_get_fourth_field(void *);
extern char *GetLocalizedString(int);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);

/* Binds the screen to its owner: allocates the 16-byte position block, initialises the four
   76-byte and nine 72-byte widgets by name ("0".."3", "title", "missions", ...), sets their
   colours, fonts and labels, marks the "  Exit" label with glyph 0x12 and lays them out.
   The block's four zero stores are written 1, 2, 3, 0 for retail's 0, 4, 8, C order. */
void func_US2_0033AB18(char *obj, void *arg)
{
    *(void **)obj = arg;
    *(int *)(obj + 0x490) = 1;
    if (arg) {
        int *p = ui_return_second_arg(16, pool_alloc_cell(arg));
        *(int **)(obj + 4) = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;
    }
    (*(float **)(obj + 4))[0] = 256.0f;
    (*(float **)(obj + 4))[1] = 198.0f;
    object_init_derived_arrays(obj + 0x8, D_001ADC10, arg);
    object_init_derived_arrays(obj + 0x54, D_001ADC18, arg);
    object_init_derived_arrays(obj + 0xA0, D_001ADC20, arg);
    object_init_derived_arrays(obj + 0xEC, D_001ADC28, arg);
    hud_init_widget_defaults(obj + 0x138, D_001ADC30, arg);
    hud_init_widget_defaults(obj + 0x190, D_001ADCA8, arg);
    hud_init_widget_defaults(obj + 0x1E8, D_001ADCB8, arg);
    hud_init_widget_defaults(obj + 0x240, D_001ADCC0, arg);
    hud_init_widget_defaults(obj + 0x298, D_001ADCC8, arg);
    hud_init_widget_defaults(obj + 0x2F0, D_001ADCD0, arg);
    hud_init_widget_defaults(obj + 0x348, D_001ADC38, arg);
    hud_init_widget_defaults(obj + 0x3A0, D_001ADC40, arg);
    hud_init_widget_defaults(obj + 0x3F8, D_001ADC50, arg);
    hud_set_widget_field_a(obj + 0x190, 0);
    hud_set_widget_field_a(obj + 0x1E8, 0);
    hud_set_widget_field_a(obj + 0x240, 0);
    hud_set_widget_field_a(obj + 0x298, 0);
    hud_set_widget_field_a(obj + 0x2F0, 0);
    hud_set_widget_field_a(obj + 0x348, 0);
    hud_set_widget_field_a(obj + 0x3A0, 0);
    hud_set_widget_field_a(obj + 0x3F8, 2);
    *object_get_fourth_field(obj + 0x8) = 0x60442D00;
    *object_get_fourth_field(obj + 0x54) = 0x60241700;
    *object_get_fourth_field(obj + 0xA0) = 0x55F0C070;
    *object_get_fourth_field(obj + 0xEC) = 0x55F0C070;
    *object_get_fourth_field(obj + 0x138) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x190) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x1E8) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x240) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x298) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x2F0) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x348) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x3A0) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x3F8) = 0x80F0F0F0;
    object_set_helper_result(obj + 0x8, D_001A8CFC[0] + 0x8710, 0x5F);
    object_set_helper_result(obj + 0x54, D_001A8CFC[0] + 0x8710, 0x60);
    object_set_helper_result(obj + 0xA0, D_001A8CFC[0] + 0x8710, 0x61);
    object_set_helper_result(obj + 0xEC, D_001A8CFC[0] + 0x8710, 0x62);
    D_001ADCA0[0] = 0x12;
    hud_set_widget_field_b(obj + 0x138, GetLocalizedString(0x2BFB));
    hud_set_widget_field_b(obj + 0x190, GetLocalizedString(0x2BF3));
    hud_set_widget_field_b(obj + 0x1E8, GetLocalizedString(0x3129));
    hud_set_widget_field_b(obj + 0x240, GetLocalizedString(0x2BFF));
    hud_set_widget_field_b(obj + 0x298, GetLocalizedString(0x2C00));
    hud_set_widget_field_b(obj + 0x2F0, GetLocalizedString(0x2C01));
    hud_set_widget_field_b(obj + 0x348, GetLocalizedString(0x2BE5));
    hud_set_widget_field_b(obj + 0x3A0, (int)(obj + 0x450));
    list_screen_layout(obj, 0);
}
