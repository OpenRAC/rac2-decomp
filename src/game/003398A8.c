#include "names.h"


extern int g_menu_input_flags[4];

extern int g_popup_label_y_offsets[4] __attribute__((sda));

extern int g_popup_label_x_offset __attribute__((sda));

extern int g_popup_row_spacing __attribute__((sda));

extern void mem_store_two_floats_through_cell(char *, float, float);

extern void prompt_bar_update(char *);

extern int func_002A9588_1(int, int, int, int, int);

extern void *object_get_fourth_field(char *);

extern void func_00335E38_3(char *, float, float, float, float);

/* Moves the pop-up's box and label to follow its position and row, and updates the label colour. */
int popup_update_position(char *popup)
{
    char *box = popup + 8;
    char *label;
    void *colorSlot;
    float labelX;
    float labelY;

    mem_store_two_floats_through_cell(box, ((float *)(*(int *)(popup + 756)))[0], ((float *)(*(int *)(popup + 756)))[1]);
    prompt_bar_update(box);
    if (g_menu_input_flags[0] & 0x5000)
        func_002A9588_1(0, 0, 1, 0, 1);
    label = popup + 680;
    colorSlot = object_get_fourth_field(label);
    *(int *)colorSlot = func_002A9588_1(0x60442D00, 0x70FFFEED, 20, 0, 0);
    labelX = ((float *)(*(int *)(popup + 756)))[0] + (float)g_popup_label_x_offset;
    labelY = ((float *)(*(int *)(popup + 756)))[1]
        + (float)(*(int *)(popup + 760) * g_popup_row_spacing);
    labelY = labelY + (float)g_popup_label_y_offsets[0];
    func_00335E38_3(label, labelX, labelY, 0.0f, 0.0f);
    return 0;
}
