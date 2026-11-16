#include "include_asm.h"
#include "names.h"

extern int hud_draw_widget_text(void *);

extern int func_0027C878_2(int);

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

/* Reads a float through a pointer field; returns when it is zero or when a word field is zero, otherwise calls a helper, adjusts a float loaded from another pointer field by half or all of the helper's result depending on a small mode word, and finally calls a second helper with three pointers and three floats taken from the object and from two further pointer fields. */
/* Draws one line of text at its stored position, shifting it left by half or all of its width when it is centred or right-aligned. */
void text_label_draw(char *label)
{
    float drawX;
    int textWidth;
    int color;
    int fontId;
    char *position;
    char *depthPos;

    if (*(float *)(*(char **)(label + 16)) == 0.0f) {
        return;
    }
    if (*(int *)(label + 64) == 0) {
        return;
    }
    textWidth = hud_draw_widget_text(label);
    drawX = *(float *)(*(char **)(label));
    switch (*(int *)(label + 68)) {
    case 0:
        break;
    case 1:
        drawX = drawX - (float)(textWidth >> 1);
        break;
    case 2:
        drawX = drawX - (float)textWidth;
        break;
    }
    position = *(char **)(label);
    depthPos = *(char **)(label + 4);
    fontId = *(int *)(*(char **)(label + 12));
    color = func_0027C878_2(*(int *)(label + 56));
    FontPrintScaled(drawX, *(float *)(position + 4), *(float *)(depthPos), fontId, *(int *)(label + 64),
            textWidth, color, *(int *)(label + 52));
}

/* Complete boot bodies from liolu PRs #72 and #75; refreshed in one combined batch. */
/* Sets the largest value a progress meter can show. */
void meter_set_max(u8 *meter, s32 maxValue) { *(s32 *)(meter + 0x40) = maxValue; }

/* Sets how full a progress meter looks, never past its maximum, by resizing its bar. */
void meter_set_value(char *meter, int amount)
{
    unsigned int maximum = *(unsigned int *)(meter + 0x40);
    unsigned int shown;
    if (maximum < (unsigned int)amount) shown = maximum;
    else shown = amount;
    if ((float)maximum == 0.0f) {
        **(float **)(meter + 4) = 0.0f;
        return;
    }
    **(float **)(meter + 4) = ((float)shown / (float)*(unsigned int *)(meter + 0x40)) * (float)*(unsigned int *)(meter + 0x3C);
}


/* Measured target: byte-identical across all 27 levels. */
/* Stores a number in a widget's field at offset 0x38. */
void widget_store_field(u8 *widget, s32 value) { *(s32 *)(widget + 0x38) = value; }

/* Sets the vertical position of a widget. */
void widget_set_pos_y(u8 *widget,s32 y) {
 (*(f32 **)(widget+4))[1]=(f32)y;
}

/* Sets how a text label is lined up (left, centre or right). */
void text_set_alignment(u8 *label, s32 alignment) {
    *(s32 *)(label + 0x44) = alignment;
}

extern void *func_00300618(void *);

/* Turns the offsets stored in a table into real pointers and prepares each entry. */
void table_relocate_entries(char *table)
{
    int entryCount = *(int *)(table + 0x18);
    int i;
    int *entries = (int *)(table + 0x1C);
    for (i = 0; i < entryCount; i++) {
        entries[i * 2 + 1] += (int)table;
        func_00300618((void *)entries[i * 2 + 1]);
    }
}

/* Looks for an entry with the given id in a table and returns its data, or 0 if it is missing. */
void *table_find_by_id(u8 *table,s32 id) {
 s32 count=*(s32 *)(table+0x18); s32 i,result=0;u8 *entries=table+0x1c;
 for(i=0;i<count;i++) {
  s32 *entry=(s32 *)((i<<3)+(u32)entries);
  if(entry[0]==id) {result=entry[1];break;}
 }
 return result;
}

/* Does nothing. */
void ui_nop_a(void)
{
}

/* Returns its second argument and ignores the first. */
void *ui_return_second_arg(void *first, void *second) { (void) first; return second; }

/* Returns the object it was given. */
void *ui_return_self(void *self) {
    return self;
}

/* shared native body of family 5b6bba31 */
/* Sets up a pool that hands out fixed-size cells from a block of memory. */
void pool_init_cells(int *pool, unsigned int cellSize, int memory, int capacity)
{
    if (cellSize < 4)
        g_assert_fail(g_str_pool_cell_file, 37, g_str_pool_init_message);
    pool[1] = capacity;
    pool[2] = cellSize;
    pool[4] = 0;
    pool[5] = 0;
    pool[3] = 0;
    pool[0] = memory;
}


/* a bump/free-list allocator. `p` (the parameter, moved to `$a1`) is a six-word */
/* Takes one cell from a pool, reusing a freed cell first, and returns 0 if the pool is full. */
void *pool_alloc_cell(T *pool)
{
    unsigned int used, cellSize;
    void *cell;

    if (pool->f20 != 0)
    {
        unsigned int *freeCell = (unsigned int *)pool->f20;

        pool->f20 = freeCell[0];
        pool->f16 = pool->f16 + 1;
        return freeCell;
    }
    used = pool->f12;
    cellSize = pool->f8;
    if (pool->f4 < used + cellSize)
    {
        D_00115E38_1(D_L00_001ADDD8_1, 83, g_str_pool_alloc_message);
        return 0;
    }
    cell = (void *)(pool->f0 + used);
    pool->f12 = used + cellSize;
    pool->f16 = pool->f16 + 1;
    return cell;
}

/* Gives a cell back to its pool so it can be reused. */
void pool_free_cell(u8 *pool, u8 *cell) {
    *(u8 **)(cell + 0) = *(u8 **)(pool + 0x14);
    *(u8 **)(pool + 0x14) = cell;
    *(s32 *)(pool + 0x10) = *(s32 *)(pool + 0x10) - 1;
}

extern int g_selected_item_material __attribute__((sda));

/* Returns a stored menu setting value. */
int menu_get_setting_value(void) {
    return g_selected_item_material;
}




extern void *object_construct_derived_a(void *);

/* Shuts down the two border pieces of a text panel and returns the panel. */
void *text_panel_shutdown(char *panel) {
    object_construct_derived_a(panel + 0x10);
    object_construct_derived_a(panel + 0x5C);
    return panel;
}

extern int *object_get_fourth_field(void *);
extern void object_set_flag_value(void *, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void object_set_helper_result(void *, int, int);
extern void object_set_value_float(void *, float);
extern void *memset(void *, int, unsigned int); /* memset */
extern char g_str_text_bracket_name[]; /* "aTxBrack" */
extern char g_str_text_top_name[]; /* "aTxTop" */
extern char *g_resident_data_base[] __attribute__((sda));

/* Initialises a text panel: clears its state and, when a pool is given, takes four 16-byte
   cells from it with func_00336E40/func_00336DA8 (255,108 / colour 0x60442D00 / two cleared
   cells), then sets up the "aTxBrack" and "aTxTop" widgets at +0x10 and +0x5C with
   D_001A8CFC[0] + 0x8710 and colour 0x55F0C070. The cleared cells store word 0 last, as in
   func_00339078; the colour cell is cleared as floats before its integer colour is stored. */
/* Sets up a text panel that shows a message: its position, colours and border pieces. */
void text_panel_init(char *panel, void *pool)
{
    char *top;
    char *bracket;

    panel[0xA8] = 0;
    *(int *)(panel + 0x1AC) = 0;
    *(int *)(panel + 0x1A8) = 0;
    *(int *)(panel + 0x1C8) = 0;
    *(int *)(panel + 0x1CC) = 0;
    *(int *)(panel + 0x1D4) = 0x28;
    *(int *)(panel + 0x1C4) = 1;
    *(int *)(panel + 0x1B0) = 1;
    memset(panel + 0x1D8, 0, 0x78);
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
        *(float **)(panel + 0) = xy;
        colour = ui_return_second_arg((void *)16, pool_alloc_cell(pool));
        colour[0] = 0.0f;
        colour[1] = 0.0f;
        *(int *)colour = 0x60442D00;
        ((int *)colour)[2] = 0;
        ((int *)colour)[3] = 0;
        *(float **)(panel + 8) = colour;
        cell4 = ui_return_second_arg((void *)16, pool_alloc_cell(pool));
        *(int **)(panel + 4) = cell4;
        cell4[1] = 0;
        cell4[2] = 0;
        cell4[3] = 0;
        cell4[0] = 0;
        cellC = ui_return_second_arg((void *)16, pool_alloc_cell(pool));
        *(int **)(panel + 12) = cellC;
        cellC[1] = 0;
        cellC[2] = 0;
        cellC[3] = 0;
        cellC[0] = 0;
    }
    bracket = panel + 0x10;
    top = panel + 0x5C;
    object_init_derived_arrays(bracket, g_str_text_bracket_name, pool);
    object_set_helper_result(bracket, (int)(g_resident_data_base[0] + 0x8710), 0x57);
    object_set_value_float(bracket, 0.02f);
    object_set_flag_value(bracket, 1);
    *object_get_fourth_field(bracket) = 0x55F0C070;
    object_init_derived_arrays(top, g_str_text_top_name, pool);
    object_set_helper_result(top, (int)(g_resident_data_base[0] + 0x8710), 0x58);
    object_set_flag_value(top, 1);
    *object_get_fourth_field(top) = 0x55F0C070;
    **(int **)(panel + 12) = 0x80F0F0F0;
    *(int *)(panel + 0x1B8) = 0;
    **(int **)(panel + 4) = 0;
}


/* Initialises an object: two float stores through the pointer at +0, clears byte +423, stores an int at +440, calls a callee with (this+168, -1) storing its result at +468 and the address at +472, sets +432 to 1 and writes 1.0f through the pointer at +4. */
/* Starts a message box: sets its position, how long it shows and its text buffer. */
void msg_box_init_state(char *box, int a1, int duration, float x, float y)
{
    char *text = box + 168;

    *(float *)(*(int *)box) = x;
    *(float *)(*(int *)box + 4) = y;
    box[423] = 0;
    *(int *)(box + 440) = duration;
    *(int *)(box + 472) = (int)text;
    *(int *)(box + 468) = text_measure_width_first_set(text, -1);
    *(int *)(box + 432) = 1;
    *(float *)(*(int *)(box + 4)) = 1.0f;
}

/* Sets the box's text up: position, duration, then splits the text at each 1 byte into the line
   table, measuring every line with func_0027F178 and keeping the widest in maxWidth. */
void LayoutTextBoxLines(TextBox *box, int unused, int duration, float x, float y)
{
    unsigned char line[0x100];
    int length = 0;
    int single;
    int i;
    int width;

    box->position[0] = x;
    box->position[1] = y;
    box->duration = duration;
    box->text[0xFF] = 0;
    box->maxWidth = 0;
    box->lineCount = 1;
    memset(line, 0, sizeof(line));
    memset(box->lines, 0, sizeof(box->lines));
    box->lines[box->lineCount - 1] = box->text;
    single = 1;
    i = 0;
    if (box->text[0] != 0) {
        unsigned char *next = &box->text[1];

        for (; i < 0xFF && box->text[i] != 0; i++, next++) {
            if (box->text[i] == 1) {
                line[length] = 0;
                box->text[i] = 0;
                single = 0;
                length = 0;
                box->lines[box->lineCount] = next;
                box->lineCount++;
                width = text_measure_width_small(line, -1);
                box->maxWidth = (box->maxWidth < width) ? width : box->maxWidth;
            } else {
                line[length] = box->text[i];
                length++;
            }
        }
    }
    if (single) {
        box->maxWidth = text_measure_width_small(box->text, -1);
    } else {
        width = text_measure_width_small(line, -1);
        box->maxWidth = (box->maxWidth < width) ? width : box->maxWidth;
    }
    box->scale[0] = 1.0f;
}

/* clamps a caller-supplied terminator value (-1 meaning unset) to 360, then runs two callees on two sub-objects of one handle, the second with a float pair */
/* Prepares a long (about six seconds) message with its text value and position on screen. */
void msg_box_init_long(int screen, int textValue, int requestedDuration)
{
    int duration = (requestedDuration == -1) ? 360 : requestedDuration;
    int textBox = screen + 8124;

    func_00115AC0_1((void *)(screen + 8292), textValue, 255);
    func_00337E98_1((void *)textBox, 1, duration, 255.0f, 80.0f);
}

/* Formats text (with up to three extra strings) into a buffer, lays it out in the box with the
   font routine chosen by mode, optionally centres the box vertically on the screen, then draws a
   padded backing rectangle and frame behind it and lays the text out again on top. */
void text_draw_framed_box(void *object, short *box, int style, char *text, int mode,
                   int center, int length, int single, char *first, char *second, int third)
{
    char buffer[768];
    int flags = box[9];
    int top, bottom, left, right;
    int halfWidth, halfHeight;
    int x, y;

    box[9] |= 3;
    if (first) {
        if (second) {
            if (third) {
                if (single) sprintf(buffer, g_str_framed_box_fmt_single_spaced, text, 1, first, 1, second);
                else sprintf(buffer, g_str_framed_box_fmt_double_spaced, text, 1, 1, first, 1, second);
            } else {
                if (single) sprintf(buffer, g_str_framed_box_fmt_single_plain, text, 1, first, second);
                else sprintf(buffer, g_str_framed_box_fmt_double_plain, text, 1, 1, first, second);
            }
        } else {
            if (single) sprintf(buffer, g_str_framed_box_fmt_single_short, text, 1, first);
            else sprintf(buffer, g_str_framed_box_fmt_double_short, text, 1, 1, first);
        }
    } else {
        sprintf(buffer, g_str_string_format, text);
    }
    box[9] |= 4;
    switch (mode) {
    case 0: text_draw_window_medium(box, style, buffer, length); break;
    case 1: text_draw_window_small(box, style, buffer, length); break;
    case 2: text_draw_window_large(box, style, buffer, length); break;
    }
    if (center) {
        int height = (unsigned short)box[7];
        int newTop = (g_screen_width[1] - (short)height) >> 1;
        int middle = newTop + ((short)height >> 1);

        box[1] = newTop + height;
        box[5] = middle;
        box[0] = newTop;
    }
    switch (mode) {
    case 0: text_draw_window_medium(box, style, buffer, length); break;
    case 1: text_draw_window_small(box, style, buffer, length); break;
    case 2: text_draw_window_large(box, style, buffer, length); break;
    }
    halfWidth = (box[6] >> 1) + 10;
    halfHeight = (box[7] >> 1) + 5;
    box[9] &= ~4;
    x = box[4];
    y = box[5];
    top = y - halfHeight;
    left = x - halfWidth;
    right = x + halfWidth;
    bottom = y + halfHeight;
    gfx_draw_rounded_box(top, bottom, left, right, 96, 0x60442D00);
    text_box_draw_frame(object, 96, 0x55F0C070, (float)top, (float)bottom, (float)left, (float)right);
    switch (mode) {
    case 0: text_draw_window_medium(box, style, buffer, length); break;
    case 1: text_draw_window_small(box, style, buffer, length); break;
    case 2: text_draw_window_large(box, style, buffer, length); break;
    }
    box[9] = flags;
}

/* Partial view of the shared screen/render state (see src/game/00274128.c). */
typedef struct {
    char pad[0xB0];
    float fB0;
} ViewState;
extern ViewState g_view_params;
extern void UpdateViewContext(void);
extern int object_get_stored_counter(void);
extern void gfx_draw_scaled_object_two_axes(int, float, float, unsigned int, float, float, float);

/* Draws a frame when the level object exists: with the view scale at +0xB0 of D_001B9040
   set to 0.62 (restored afterwards), the two sprites at +0x220C go at the left and right
   ends and the four of +0x2210 at the corners, inset by 16; the last argument is computed
   from the frame's height, then from its width. Colour = alpha << 24 | color. */
void text_box_draw_frame(char *obj, unsigned int alpha, unsigned int color, float top, float bottom, float left, float right)
{
    ViewState *view;
    float saved, scale, uv, insetRight, insetLeft, border;

    if (g_resident_data_base[0]) {
        view = &g_view_params;
        scale = 1.0f;
        saved = view->fB0;
        view->fB0 = 0.62f;
        UpdateViewContext();
        uv = ((bottom - top) - 26.0f) * 0.008928571827709675f;
        uv = uv * 0.3110000193119049f + 0.03750000149011612f;
        if (object_get_stored_counter() == 1)
            scale = 0.9f;
        alpha <<= 24;
        alpha |= color;
        gfx_draw_scaled_object_two_axes(*(int *)(obj + 0x220c), left, top, alpha, -1.0f, scale, uv);
        border = 16.0f;
        gfx_draw_scaled_object_two_axes(*(int *)(obj + 0x220c), right, top, alpha, 1.0f, scale, uv);
        uv = ((right - left) - 150.0f) * 0.003267973894253373f;
        insetLeft = left + border;
        insetRight = right - border;
        uv = uv * 0.43300002813339233f + 0.10199999809265137f;
        gfx_draw_scaled_object_two_axes(*(int *)(obj + 0x2210), insetLeft, top, alpha, -1.0f, 1.0f, uv);
        gfx_draw_scaled_object_two_axes(*(int *)(obj + 0x2210), insetRight, top, alpha, 1.0f, 1.0f, uv);
        gfx_draw_scaled_object_two_axes(*(int *)(obj + 0x2210), insetLeft, bottom, alpha, -1.0f, -1.0f, uv);
        gfx_draw_scaled_object_two_axes(*(int *)(obj + 0x2210), insetRight, bottom, alpha, 1.0f, -1.0f, uv);
        view->fB0 = saved;
        UpdateViewContext();
    }
}

extern char *GetLocalizedString(int);

extern int sprintf(char *, char *, ...);

/* Writes the localised text `text_id` (with `value` as its only argument) into the
   buffer at +0x1E14 of the object, then initialises the sub-object at +0x1D6C with a
   count that defaults to 120 when the caller passes -1. The two pointers are defined
   in this order on purpose: it is what puts the buffer in $s1 and the count in $s2. */
void msg_box_init_localized(char *object, int text_id, int value, int count)
{
    char *sub = object + 0x1D6C;
    int limit = (count == -1) ? 120 : count;
    char *buffer = object + 0x1E14;

    sprintf(buffer, GetLocalizedString(text_id), value);
    msg_box_init_state(sub, 1, limit, 255.0f, 135.0f);
}
