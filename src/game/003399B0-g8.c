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

/* Binds the screen to its owner: allocates the 16-byte position block, initialises the four
   76-byte and nine 72-byte widgets by name ("0".."3", "title", "missions", ...), sets their
   colours, fonts and labels, marks the "  Exit" label with glyph 0x12 and lays them out.
   The block's four zero stores are written 1, 2, 3, 0 for retail's 0, 4, 8, C order. */
void list_screen_init(char *obj, void *arg)
{
    *(void **)obj = arg;
    *(int *)(obj + 0x400) = 1;
    if (arg) {
        int *position = ui_return_second_arg(16, pool_alloc_cell(arg));
        *(int **)(obj + 4) = position;
        position[1] = 0;
        position[2] = 0;
        position[3] = 0;
        position[0] = 0;
    }
    (*(float **)(obj + 4))[0] = 256.0f;
    (*(float **)(obj + 4))[1] = 198.0f;
    object_init_derived_arrays(obj + 0x8, D_001ADC10, arg);
    object_init_derived_arrays(obj + 0x54, D_001ADC18, arg);
    object_init_derived_arrays(obj + 0xA0, D_001ADC20, arg);
    object_init_derived_arrays(obj + 0xEC, D_001ADC28, arg);
    hud_init_widget_defaults(obj + 0x138, D_001ADC30, arg);
    hud_init_widget_defaults(obj + 0x180, D_001ADCA8, arg);
    hud_init_widget_defaults(obj + 0x1C8, D_001ADCB8, arg);
    hud_init_widget_defaults(obj + 0x210, D_001ADCC0, arg);
    hud_init_widget_defaults(obj + 0x258, D_001ADCC8, arg);
    hud_init_widget_defaults(obj + 0x2A0, D_001ADCD0, arg);
    hud_init_widget_defaults(obj + 0x2E8, D_001ADC38, arg);
    hud_init_widget_defaults(obj + 0x330, D_001ADC40, arg);
    hud_init_widget_defaults(obj + 0x378, D_001ADC50, arg);
    hud_set_widget_field_a(obj + 0x180, 0);
    hud_set_widget_field_a(obj + 0x1C8, 0);
    hud_set_widget_field_a(obj + 0x210, 0);
    hud_set_widget_field_a(obj + 0x258, 0);
    hud_set_widget_field_a(obj + 0x2A0, 0);
    hud_set_widget_field_a(obj + 0x2E8, 0);
    hud_set_widget_field_a(obj + 0x330, 0);
    hud_set_widget_field_a(obj + 0x378, 2);
    *object_get_fourth_field(obj + 0x8) = 0x60442D00;
    *object_get_fourth_field(obj + 0x54) = 0x60241700;
    *object_get_fourth_field(obj + 0xA0) = 0x55F0C070;
    *object_get_fourth_field(obj + 0xEC) = 0x55F0C070;
    *object_get_fourth_field(obj + 0x138) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x180) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x1C8) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x210) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x258) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x2A0) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x2E8) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x330) = 0x80F0F0F0;
    *object_get_fourth_field(obj + 0x378) = 0x80F0F0F0;
    object_set_helper_result(obj + 0x8, D_001A8CFC[0] + 0x8710, 0x5F);
    object_set_helper_result(obj + 0x54, D_001A8CFC[0] + 0x8710, 0x60);
    object_set_helper_result(obj + 0xA0, D_001A8CFC[0] + 0x8710, 0x61);
    object_set_helper_result(obj + 0xEC, D_001A8CFC[0] + 0x8710, 0x62);
    D_001ADCA0[0] = 0x12;
    hud_set_widget_field_b(obj + 0x138, GetLocalizedString(0x2D65));
    hud_set_widget_field_b(obj + 0x180, GetLocalizedString(0x2D5D));
    hud_set_widget_field_b(obj + 0x1C8, GetLocalizedString(0x3293));
    hud_set_widget_field_b(obj + 0x210, GetLocalizedString(0x2D69));
    hud_set_widget_field_b(obj + 0x258, GetLocalizedString(0x2D6A));
    hud_set_widget_field_b(obj + 0x2A0, GetLocalizedString(0x2D6B));
    hud_set_widget_field_b(obj + 0x2E8, GetLocalizedString(0x2D4F));
    hud_set_widget_field_b(obj + 0x330, (int)(obj + 0x3C0));
    list_screen_layout(obj, 0);
}

/* The X bias lives in small data, so this file is built with -G8. */
extern float ref_L00_0033A688_00 __attribute__((sda));
extern float D_001ADD0C;
extern void object_set_first_float4(char *, float, float, float, float);

/* Offsets the record position by the two resident biases and hands it to the
   shared spawn helper with no rotation. */
/* Moves the circle menu label to sit next to the menu centre. */
void circle_menu_position_label(char *menu)
{
    if (*(int *)(menu + 0x20C) != 0) {
        float *position = *(float **)(menu + 0x1FC);

        object_set_first_float4(menu + 0x170, position[0] + ref_L00_0033A688_00,
                      position[1] + D_001ADD0C, 0.0f, 0.0f);
    }
}

/* The table of four resident ints is reached through $gp and the resident
   pointer through the small-data unit, so this body needs -G8. */
extern char *D_001A8CFC[] __attribute__((sda));
extern char D_001ADC88[];
extern int D_001ADD30 __attribute__((sda));
extern void object_set_flag_value(char *, int);

/* Sets up the four button icons of the circle menu and counts how many entries its table has. */
void circle_menu_init_entries(char *obj, int *iconIds, char *table)
{
    char *icon = obj + 4;
    int *iconColor = (int *)&D_001ADD30;
    int i;
    int entryCount;
    int *entryMode;
    int tableOffset;

    for (i = 3; i >= 0; i--) {
        if (*iconIds != 0) {
            object_init_derived_arrays(icon, D_001ADC88, *(int *)(obj + 0x200));
            *(int *)object_get_fourth_field(icon) = *iconColor;
            object_set_helper_result(icon, D_001A8CFC[0] + 0x8710, *iconIds);
        } else {
            object_set_helper_result(icon, D_001A8CFC[0] + 0x8710, 0);
            object_set_flag_value(icon, 0);
        }
        icon += 76;
        iconColor += 1;
        iconIds += 1;
    }
    *(int *)(obj + 0x1F8) = 0;
    *(int *)obj = (int)table;
    entryCount = 0;
    if (*(int *)(table + 4) != -1) {
        /* The named -1 makes the compiler keep the loop's comparison constant
           in the preheader, where the retail body has it. */
        int minus = -1;
        tableOffset = 0;
        entryMode = (int *)(obj + 0x1B8);
        do {
            *entryMode++ = 0;
            tableOffset += 0x18;
            *(int *)(obj + 0x1F8) = *(int *)(obj + 0x1F8) + 1;
            entryCount++;
            if (*(int *)(tableOffset + (int)*(int *)obj + 4) == minus)
                break;
        } while (entryCount < 16);
    }
}

extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void object_set_second_float4(char *, float, float, float, float);
extern int *object_get_fourth_field(void *);
extern void hud_draw_colored_quad_widget(char *);
extern void hud_set_widget_value_pair(char *, int, int);
extern char *GetLocalizedString(int);
extern void text_label_draw(char *);
extern float D_001ADD20 __attribute__((sda));
extern float D_001ADD24;
extern int D_001ADD10 __attribute__((sda));
extern int D_001ADD14;
extern float D_001ADD18 __attribute__((sda));
extern float D_001ADD28 __attribute__((sda));
extern float D_001ADD2C;

typedef struct { int first, second, color; float angle; short id; short pad; int text; } Entry_0033A6D8;
typedef struct { char pad[8]; short n; void (*fn)(char *); } Vtable_0033A6D8;
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
void circle_menu_draw(char *self)
{
    if (*(int *)(self + 0x20C) != 0) {
        char *rec0 = self + 0x50;
        char *rec1 = self + 0x9C;
        float *position = *(float **)(self + 0x1FC);
        int i;

        object_set_first_float4(rec0, position[0], position[1], 0.0f, 0.0f);
        object_set_second_float4(rec0, D_001ADD20, D_001ADD24, 0.0f, 0.0f);
        (*(Vtable_0033A6D8 **)(self + 0x80))->fn(rec0 + (*(Vtable_0033A6D8 **)(self + 0x80))->n);
        position = *(float **)(self + 0x1FC);
        object_set_first_float4(rec1, position[0], position[1], 0.0f, 0.0f);
        object_set_second_float4(rec1, D_001ADD20, D_001ADD24, 0.0f, 0.0f);
        (*(Vtable_0033A6D8 **)(self + 0xCC))->fn(rec1 + (*(Vtable_0033A6D8 **)(self + 0xCC))->n);
        for (i = 0; i < *(int *)(self + 0x1F8); i++) {
            char *rec = self + 0x134;
            int *mode;
            int one = 1;
            float cs, sn;

            cs = *(float *)(self + 0x204) * math_fast_sin_or_cos_a(ENTRY_0033A6D8.angle);
            sn = *(float *)(self + 0x204) * math_fast_sin_or_cos_b(ENTRY_0033A6D8.angle);
            hud_set_widget_value_pair(rec, ENTRY_0033A6D8.first, ENTRY_0033A6D8.second);
            position = *(float **)(self + 0x1FC);
            object_set_first_float4(rec, position[0] + (float)D_001ADD10 + cs,
                          position[1] + (float)D_001ADD14 + D_001ADD18 * sn, 0.0f, 0.0f);
            mode = (int *)(self + 0x1B8) + i;
            *object_get_fourth_field(rec) = (*mode == one) ? 0x80808080 : ENTRY_0033A6D8.color;
            object_set_flag_value(rec, *mode != 2);
            hud_draw_colored_quad_widget(rec);
            if (i == *(int *)(self + 0x208)) {
                char *cursor;

                object_set_second_float4(self + 4, D_001ADD20, D_001ADD24, 0.0f, 0.0f);
                if (*mode != 2) {
                    position = *(float **)(self + 0x1FC);
                    object_set_first_float4(self + 4, position[0] + D_001ADD28 + cs,
                                  position[1] + D_001ADD2C + D_001ADD18 * sn, 0.0f, 0.0f);
                    {
                        int text = ENTRY_0033A6D8.text;

                        if (text != 0) {
                            hud_set_widget_field_b(self + 0x170, text);
                        } else {
                            text = GetLocalizedString(ENTRY_0033A6D8.id);
                            hud_set_widget_field_b(self + 0x170, text);
                        }
                        text_label_draw(self + 0x170);
                    }
                }
                cursor = self + 4;
                (*(Vtable_0033A6D8 **)(self + 0x34))->fn(cursor + (*(Vtable_0033A6D8 **)(self + 0x34))->n);
            }
        }
    }
}
#undef ENTRY_0033A6D8

extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void *memset(void *, int, int);
extern char D_001ADC80[], D_001ADC88[];
extern int D_001ADD40[2] __attribute__((sda));

/* Constructor of a gadget made of five sprite slots (76 bytes each from +0xC, switched on by the
   five shorts of LIST, which are also kept at +0x188) and three 72-byte sprites at +0x198, +0x1E0
   and +0x228, each with an 8-byte offset beside it at +0x278, +0x280 and +0x288.  The blank name
   is D_001ADC88; the slot loop reaches it as D_001ADC80 + 8 and the three sprites through the
   spent list pointer, which keeps the compiler from hoisting it across the loop. */
void prompt_bar_init(char *object, char *owner, short *list)
{
    char *slotRecord, *rec198, *rec1E0, *rec228, *vel278, *vel280, *vel288;
    short *slotFlags, *slotIds;
    int *slotColor;
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
    vel278 = object + 0x278;
    rec198 = object + 0x198;
    vel288 = object + 0x288;
    rec228 = object + 0x228;
    slotFlags = (short *)(object + 0x188);
    rec1E0 = object + 0x1E0;
    slotColor = D_001ADD40;
    slotRecord = object + 0xC;
    vel280 = object + 0x280;
    slotIds = list;
    for (i = 4; i >= 0; i--) {
        if (*slotIds != 0) {
            object_init_derived_arrays(slotRecord, D_001ADC80 + 8, owner);
            *object_get_fourth_field(slotRecord) = *slotColor;
            object_set_helper_result(slotRecord, D_001A8CFC[0] + 0x8710, *slotIds);
        }
        *slotFlags = *slotIds;
        slotColor++;
        slotRecord += 0x4C;
        slotIds++;
        slotFlags++;
    }
    slotIds = (short *)D_001ADC88;
    hud_init_widget_defaults(rec198, slotIds, owner);
    memset(vel278, 0, 8);
    object_set_first_float4(rec198, 0.0f, 0.0f, 0.0f, 0.0f);
    *object_get_fourth_field(rec198) = 0x80F0F0F0;
    hud_init_widget_defaults(rec228, slotIds, owner);
    memset(vel288, 0, 8);
    object_set_first_float4(rec228, 0.0f, 0.0f, 0.0f, 0.0f);
    *object_get_fourth_field(rec228) = 0x80F0F0F0;
    hud_init_widget_defaults(rec1E0, slotIds, owner);
    memset(vel280, 0, 8);
    object_set_first_float4(rec1E0, 0.0f, 0.0f, 0.0f, 0.0f);
    *object_get_fourth_field(rec1E0) = 0x80F0F0F0;
    *(float *)(object + 0x274) = 0.0f;
    *(int *)(object + 0x290) = 1;
    *(int *)(object + 0x294) = 1;
    *(int *)(object + 4) = 0;
    *(int *)(object + 0x29C) = 1;
}
