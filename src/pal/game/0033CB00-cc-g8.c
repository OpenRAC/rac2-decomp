#include "names.h"
/* func_PAL_0033CB00, the PAL copy of func_0033ABD8: the same C, where rename func_003369A8 becomes func_PAL_00338688; swap locals *record *vel278; swap locals *rec198 *vel280. */

extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults_pal(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern char *GetLocalizedString(int);
extern char *g_resident_data_base[] __attribute__((sda));
/* Binds the screen to its owner: allocates the 16-byte position block, initialises the four
   76-byte and nine 72-byte widgets by name ("0".."3", "title", "missions", ...), sets their
   colours, fonts and labels, marks the "  Exit" label with glyph 0x12 and lays them out.
   The block's four zero stores are written 1, 2, 3, 0 for retail's 0, 4, 8, C order. */
/* The X bias lives in small data, so this file is built with -G8. */
extern void object_set_first_float4(char *, float, float, float, float);

/* Offsets the record position by the two resident biases and hands it to the
   shared spawn helper with no rotation. */
/* The table of four resident ints is reached through $gp and the resident
   pointer through the small-data unit, so this body needs -G8. */
extern char *g_resident_data_base[] __attribute__((sda));
extern char g_circle_menu_icon_data[];
extern int *object_get_fourth_field(void *);
extern char *GetLocalizedString(int);
typedef struct { int first, second, color; float angle; short id; short pad; int text; } Entry_0033A6D8;
#define ENTRY_0033A6D8 (*(Entry_0033A6D8 **)self)[i]

/* Draws the selection list: two fixed sprites, then one sprite per entry placed around the stored
   position (the radius at +0x204 scales the cosine and the sine of the entry's angle), and for the
   selected entry the cursor sprite and its label. A mode (the ints from +0x1B8) of 1 gives the
   sprite the tint 0x80808080 instead of the entry's own colour; a mode of 2 clears the flag given
   to func_00335E68 and keeps the cursor from being moved and labelled.
   ENTRY_0033A6D8 is entry i of the array that starts at self + 0. `one` holds the 1 of the mode
   test in a register of its own: written as a bare 1 in the comparison, the constant is not
   hoisted out of the loop. The pointer to the modes is assigned where it is first used, and the
   cursor sprite (self + 4) reaches its virtual call through a variable: these decide which
   induction variable and which register the compiler picks. */
#undef ENTRY_0033A6D8

extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults_pal(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void *memset(void *, int, int);
extern char g_circle_menu_header_data[], g_circle_menu_icon_data[];
extern int g_prompt_bar_slot_colors[2] __attribute__((sda));

/* Constructor of a gadget made of five sprite slots (76 bytes each from +0xC, switched on by the
   five shorts of LIST, which are also kept at +0x188) and three 72-byte sprites at +0x198, +0x1E0
   and +0x228, each with an 8-byte offset beside it at +0x278, +0x280 and +0x288.  The blank name
   is D_001ADC88; the slot loop reaches it as D_001ADC80 + 8 and the three sprites through the
   spent list pointer, which keeps the compiler from hoisting it across the loop. */
void prompt_bar_init_pal(char *object, char *owner, short *list)
{
    char *first_offset, *third_offset, *text_third, *text_second, *sprite, *text_first, *second_offset;
    short *flags, *p;
    int *color;
    int i;

    *(char **)(object + 8) = owner;
    if (owner) {
        int *allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)object = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    first_offset = object + 0x2a8;
    text_first = object + 0x198;
    second_offset = object + 0x2b8;
    text_second = object + 0x248;
    flags = (short *)(object + 0x188);
    text_third = object + 0x1f0;
    color = g_prompt_bar_slot_colors;
    sprite = object + 0xC;
    third_offset = object + 0x2b0;
    p = list;
    for (i = 4; i >= 0; i--) {
        if (*p != 0) {
            object_init_derived_arrays(sprite, g_circle_menu_header_data + 8, owner);
            *object_get_fourth_field(sprite) = *color;
            object_set_helper_result(sprite, g_resident_data_base[0] + 0x8710, *p);
        }
        *flags = *p;
        color++;
        sprite += 0x4C;
        p++;
        flags++;
    }
    p = (short *)g_circle_menu_icon_data;
    hud_init_widget_defaults_pal(text_first, p, owner);
    memset(first_offset, 0, 8);
    object_set_first_float4(text_first, 0.0f, 0.0f, 0.0f, 0.0f);
    *object_get_fourth_field(text_first) = 0x80F0F0F0;
    hud_init_widget_defaults_pal(text_second, p, owner);
    memset(second_offset, 0, 8);
    object_set_first_float4(text_second, 0.0f, 0.0f, 0.0f, 0.0f);
    *object_get_fourth_field(text_second) = 0x80F0F0F0;
    hud_init_widget_defaults_pal(text_third, p, owner);
    memset(third_offset, 0, 8);
    object_set_first_float4(text_third, 0.0f, 0.0f, 0.0f, 0.0f);
    *object_get_fourth_field(text_third) = 0x80F0F0F0;
    *(float *)(object + 0x2a4) = 0.0f;
    *(int *)(object + 0x2c0) = 1;
    *(int *)(object + 0x2c4) = 1;
    *(int *)(object + 4) = 0;
    *(int *)(object + 0x2cc) = 1;
}
