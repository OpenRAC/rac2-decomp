#include "include_asm.h"
#include "names.h"

extern int *object_get_fourth_field(void *);
extern void object_set_flag_value(void *, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void object_set_helper_result(void *, int, int);
extern void object_set_value_float(void *, float);
extern void *memset(void *, int, unsigned int);
extern char g_str_text_bracket_name[];
extern char g_str_text_top_name[];
extern char *g_resident_data_base[] __attribute__((sda));

/* Initialises a text panel: clears its state and, when a pool is given, takes four 16-byte
   cells from it with func_00336E40/func_00336DA8 (255,108 / colour 0x60442D00 / two cleared
   cells), then sets up the "aTxBrack" and "aTxTop" widgets at +0x10 and +0x5C with
   D_001A8CFC[0] + 0x8710 and colour 0x55F0C070. The cleared cells store word 0 last, as in
   func_00339078; the colour cell is cleared as floats before its integer colour is stored. */
void text_panel_init_us2(char *obj, void *pool)
{
    char *top;
    char *bracket;

    obj[0xA8] = 0;
    *(int *)(obj + 0x1AC) = 0;
    *(int *)(obj + 0x1A8) = 0;
    *(int *)(obj + 0x1C8) = 0;
    *(int *)(obj + 0x1CC) = 0;
    *(int *)(obj + 0x1C4) = 2;
    *(int *)(obj + 0x1D4) = 0x28;
    *(int *)(obj + 0x1B0) = 1;
    memset(obj + 0x1D8, 0, 0x78);
    if (pool != 0) {
        float *xy;
        float *colour;
        int *cell4;
        int *cellC;

        xy = ui_return_second_arg((void *)16, pool_alloc_cell(pool));
        xy[0] = 255.0f;
        xy[1] = 108.0f;
        ((int *)xy)[2] = 0;
        ((int *)xy)[3] = 0;
        *(float **)(obj + 0) = xy;
        colour = ui_return_second_arg((void *)16, pool_alloc_cell(pool));
        colour[0] = 0.0f;
        colour[1] = 0.0f;
        *(int *)colour = 0x60442D00;
        ((int *)colour)[2] = 0;
        ((int *)colour)[3] = 0;
        *(float **)(obj + 8) = colour;
        cell4 = ui_return_second_arg((void *)16, pool_alloc_cell(pool));
        *(int **)(obj + 4) = cell4;
        cell4[1] = 0;
        cell4[2] = 0;
        cell4[3] = 0;
        cell4[0] = 0;
        cellC = ui_return_second_arg((void *)16, pool_alloc_cell(pool));
        *(int **)(obj + 12) = cellC;
        cellC[1] = 0;
        cellC[2] = 0;
        cellC[3] = 0;
        cellC[0] = 0;
    }
    bracket = obj + 0x10;
    top = obj + 0x5C;
    object_init_derived_arrays(bracket, g_str_text_bracket_name, pool);
    object_set_helper_result(bracket, (int)(g_resident_data_base[0] + 0x8710), 0x57);
    object_set_value_float(bracket, 0.02f);
    object_set_flag_value(bracket, 1);
    *object_get_fourth_field(bracket) = 0x55F0C070;
    object_init_derived_arrays(top, g_str_text_top_name, pool);
    object_set_helper_result(top, (int)(g_resident_data_base[0] + 0x8710), 0x58);
    object_set_flag_value(top, 1);
    *object_get_fourth_field(top) = 0x55F0C070;
    **(int **)(obj + 12) = 0x80F0F0F0;
    *(int *)(obj + 0x1B8) = 0;
    **(int **)(obj + 4) = 0;
}


extern int text_measure_width_small(unsigned char *text, int length); /* text width */

/* Sets up a message box: position, duration and text width (v2.00 version of msg_box_init_state, which also stores the mode at +0x1C4). */
void msg_box_init_state_us2(unsigned char *panel, int mode, int duration, float x, float y)
{
    unsigned char *text = panel + 168;

    *(int *)(panel + 452) = mode;
    *(float *)(*(int *)panel) = x;
    *(float *)(*(int *)panel + 4) = y;
    panel[423] = 0;
    *(int *)(panel + 440) = duration;
    *(int *)(panel + 472) = (int)text;
    *(int *)(panel + 468) = text_measure_width_small(text, -1);
    *(int *)(panel + 432) = 1;
    *(float *)(*(int *)(panel + 4)) = 1.0f;
}

extern char *strncpy(void *, int, int);
extern void layout_text_box_lines_us2(void *, int, int, float, float);

/* Copies the long message text into the box and lays it out; a duration of -1 means the default 360 frames (v2.00 version of msg_box_init_long). */
void msg_box_init_long_us2(int screen, int text, int requested_duration)
{
    int duration = (requested_duration == -1) ? 360 : requested_duration;
    int text_box = screen + 8156;

    strncpy((void *)(screen + 8324), text, 255);
    layout_text_box_lines_us2((void *)text_box, 2, duration, 255.0f, 80.0f);
}





/* Copies the short message text into the box and lays it out; a duration of -1 means the default 180 frames. */
void msg_box_init_short_us2(int screen, int text, int requested_duration)
{
    int duration = (requested_duration == -1) ? 180 : requested_duration;
    int text_box = screen + 7564;

    strncpy((void *)(screen + 7732), text, 254);
    layout_text_box_lines_us2((void *)text_box, 2, duration, 255.0f, 123.0f);
}

