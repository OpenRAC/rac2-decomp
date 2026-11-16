#include "include_asm.h"
#include "names.h"
extern float ref_L00_0033A688_00 __attribute__((sda));
extern float g_circle_menu_label_offset_y;
extern void object_set_first_float4(char *, float, float, float, float);

/* Offsets the record position by the two resident biases and hands it to the
   shared spawn helper with no rotation. */
void circle_menu_position_label_us2(char *a0)
{
    if (*(int *)(a0 + 0x21C) != 0) {
        float *position = *(float **)(a0 + 0x20C);

        object_set_first_float4(a0 + 0x170, position[0] + ref_L00_0033A688_00,
                      position[1] + g_circle_menu_label_offset_y, 0.0f, 0.0f);
    }
}

extern int *object_get_fourth_field(void *);
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, int);
extern void object_set_flag_value(char *, int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void object_set_second_float4(char *, float, float, float, float);
extern int *object_get_fourth_field(void *);
extern void hud_draw_colored_quad_widget(char *);
extern void hud_set_widget_value_pair(char *, int, int);
extern char *GetLocalizedString(int);
extern void text_label_draw(char *);
extern float g_circle_menu_second_value_x __attribute__((sda));
extern float g_circle_menu_second_value_y;
extern int g_circle_menu_icon_offset_x __attribute__((sda));
extern int g_circle_menu_icon_offset_y;
extern float g_circle_menu_sin_scale __attribute__((sda));
extern float g_circle_menu_self_offset_x __attribute__((sda));
extern float g_circle_menu_self_offset_y;
typedef struct { int first, second, color; float angle; short id; short pad; int text; } Entry_0033A6D8;
typedef struct { char pad[8]; short n; void (*fn)(char *); } Vtable_0033A6D8;
#define ENTRY_0033A6D8 (*(Entry_0033A6D8 **)self)[i]
extern int *object_get_fourth_field(void *);

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
void circle_menu_draw_us2(char *self)
{
    if (*(int *)(self + 0x21C) != 0) {
        char *rec0 = self + 0x50;
        char *rec1 = self + 0x9C;
        float *position = *(float **)(self + 0x20C);
        int i;

        object_set_first_float4(rec0, position[0], position[1], 0.0f, 0.0f);
        object_set_second_float4(rec0, g_circle_menu_second_value_x, g_circle_menu_second_value_y, 0.0f, 0.0f);
        (*(Vtable_0033A6D8 **)(self + 0x80))->fn(rec0 + (*(Vtable_0033A6D8 **)(self + 0x80))->n);
        position = *(float **)(self + 0x20C);
        object_set_first_float4(rec1, position[0], position[1], 0.0f, 0.0f);
        object_set_second_float4(rec1, g_circle_menu_second_value_x, g_circle_menu_second_value_y, 0.0f, 0.0f);
        (*(Vtable_0033A6D8 **)(self + 0xCC))->fn(rec1 + (*(Vtable_0033A6D8 **)(self + 0xCC))->n);
        for (i = 0; i < *(int *)(self + 0x208); i++) {
            char *rec = self + 0x134;
            int *mode;
            int one = 1;
            float cs, sn;

            cs = *(float *)(self + 0x214) * math_fast_sin_or_cos_a(ENTRY_0033A6D8.angle);
            sn = *(float *)(self + 0x214) * math_fast_sin_or_cos_b(ENTRY_0033A6D8.angle);
            hud_set_widget_value_pair(rec, ENTRY_0033A6D8.first, ENTRY_0033A6D8.second);
            position = *(float **)(self + 0x20C);
            object_set_first_float4(rec, position[0] + (float)g_circle_menu_icon_offset_x + cs,
                          position[1] + (float)g_circle_menu_icon_offset_y + g_circle_menu_sin_scale * sn, 0.0f, 0.0f);
            mode = (int *)(self + 0x1C8) + i;
            *object_get_fourth_field(rec) = (*mode == one) ? 0x80808080 : ENTRY_0033A6D8.color;
            object_set_flag_value(rec, *mode != 2);
            hud_draw_colored_quad_widget(rec);
            if (i == *(int *)(self + 0x218)) {
                char *cursor;

                object_set_second_float4(self + 4, g_circle_menu_second_value_x, g_circle_menu_second_value_y, 0.0f, 0.0f);
                if (*mode != 2) {
                    position = *(float **)(self + 0x20C);
                    object_set_first_float4(self + 4, position[0] + g_circle_menu_self_offset_x + cs,
                                  position[1] + g_circle_menu_self_offset_y + g_circle_menu_sin_scale * sn, 0.0f, 0.0f);
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

extern void object_init_derived_arrays(void *, void *, void *);
extern void object_set_helper_result(void *, void *, int);
extern char *g_resident_data_base[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));
extern char g_circle_menu_icon_data[];
extern int g_circle_menu_icon_colors __attribute__((sda));
extern void object_init_derived_arrays(void *, void *, void *);
extern void object_set_helper_result(void *, void *, int);
extern char g_circle_menu_header_data[], g_circle_menu_icon_data[];

void circle_menu_init_entries_us2(char *obj, int *arr, char *third)
{
    char *p = obj + 4;
    int *q = (int *)&g_circle_menu_icon_colors;
    int i;
    int n;
    int *out;
    int off;

    for (i = 3; i >= 0; i--) {
        if (*arr != 0) {
            object_init_derived_arrays(p, g_circle_menu_icon_data, *(int *)(obj + 0x210));
            *(int *)object_get_fourth_field(p) = *q;
            object_set_helper_result(p, g_resident_data_base[0] + 0x8710, *arr);
        } else {
            object_set_helper_result(p, g_resident_data_base[0] + 0x8710, 0);
            object_set_flag_value(p, 0);
        }
        p += 76;
        q += 1;
        arr += 1;
    }
    *(int *)(obj + 0x208) = 0;
    *(int *)obj = (int)third;
    n = 0;
    if (*(int *)(third + 4) != -1) {
        /* The named -1 makes the compiler keep the loop's comparison constant
           in the preheader, where the retail body has it. */
        int minus = -1;
        off = 0;
        out = (int *)(obj + 0x1C8);
        do {
            *out++ = 0;
            off += 0x18;
            *(int *)(obj + 0x208) = *(int *)(obj + 0x208) + 1;
            n++;
            if (*(int *)(off + (int)*(int *)obj + 4) == minus)
                break;
        } while (n < 16);
    }
}
