#include "include_asm.h"
#include "common.h"

/* func_US2_002D8E60, the v2.00 copy of func_002D81B0: the stream halving and the read are gone. */
typedef struct { char pad0[0x36C]; int offset; char pad370[0x16B0 - 0x370]; int start; int length; } Stream2D81B0;
typedef struct { unsigned int key; unsigned int flags; } Slot2D81B0;
typedef struct { char pad[0x118]; char *loaded; unsigned int limit; } State2D6E78;
extern Stream2D81B0 g_copy_setup_data;
extern Slot2D81B0 g_menu_chunk_table[] MACRO_ADDR;
extern int g_block_load_disc_handle;
extern State2D6E78 g_pause_menu_state;
extern void menu_stream_chunk_table_init(int);

/* Starts the block load: clears the loader's saved values and marks the chunk slots whose key is below the limit. */
int menu_block_load_start_us2(char *menu)
{
    int i;
    unsigned int *key;
    unsigned int *flags;

    menu_stream_chunk_table_init(1);
    *(int *)(menu + 0x54) = 0;
    *(int *)(menu + 0x38) = 0;
    flags = &g_menu_chunk_table[0].flags;
    key = &g_menu_chunk_table[0].key;
    for (i = 0; i < 5; i++) {
        if (*key != 0 && *key < g_pause_menu_state.limit)
            *flags |= 2;
        flags += 2;
        key += 2;
    }
    *(int *)(menu + 0x50) = 0;
    *(int *)(menu + 0x10) |= 4;
    return 0;
}
extern void load_request_disc_read_break(void);
extern short g_sequence_active_flag;
extern void load_request_disc_read_break(void);
extern int g_subtitle_entries __attribute__((sda));
extern int g_block_load_object_word;

/* Finishes the loader: stops a running read, then stores the loaded block values. */
int menu_block_load_finish_us2(char *menu)
{
    if (g_sequence_active_flag != 0 && *(int *)(menu + 0x50) == 3)
        load_request_disc_read_break();
    menu_stream_chunk_table_init(1);
    {
        int value = *(int *)(menu + 0x54);
        if (value != 0) {
            g_block_load_object_word = *(int *)(menu + 0x38);
            g_subtitle_entries = value;
        }
    }
    return 0;
}


extern unsigned char g_language MACRO_ADDR;
extern int g_subtitle_state[];
extern int g_data_header_offset SDATA(D_US2_001ABB38);
extern int load_start_disc_read(int, int, int);
extern void mem_copy_aligned(void *, void *, int);

/* The loader object of func_US2_002D8E60: its flags, the entry table it replaced and its state. */
typedef struct {
    char pad00[0x10];
    int flags;
    char pad14[0x38 - 0x14];
    int saved_count;
    char pad3C[0x50 - 0x3C];
    int state;
    int saved_base;
} Loader2D8338;

/* func_US2_002D8F70, the v2.00 copy of func_002D8338: the read now takes two steps, first one
   sector holding a table of byte offsets, then the block at the entry D_001A7BB4 selects. */
/* Advances the loader: reads the offset table, then the block for the current language, and unpacks and relocates its entries. */
int menu_block_loader_update_us2(char *menu)
{
    Loader2D8338 *loader = (Loader2D8338 *)menu;

    switch (loader->state) {
    case 4:
    case 5:
        break;
    case 0:
        g_data_header_offset = 0;
        if (g_sequence_active_flag == 0) {
            Stream2D81B0 *stream = &g_copy_setup_data;

            if (load_start_disc_read(g_block_load_disc_handle, stream->start + stream->offset, 1))
                loader->state = 1;
            else
                loader->state = 5;
        }
        break;
    case 1:
        if (g_sequence_active_flag == 0)
            loader->state = 2;
        break;
    case 2:
        if (g_sequence_active_flag == 0) {
            int data = g_block_load_disc_handle;
            int offset = ((int *)data)[g_language];
            Stream2D81B0 *stream = &g_copy_setup_data;

            g_data_header_offset = offset % 0x800;
            if (load_start_disc_read(data, stream->start + stream->offset + offset / 0x800, 100))
                loader->state = 3;
            else
                loader->state = 5;
        }
        break;
    case 3:
        if (g_sequence_active_flag == 0) {
            char *data = g_pause_menu_state.loaded;
            int *header = (int *)(data + g_data_header_offset);
            int count = *header++;
            int size = *header++;
            char *base;
            int i;

            mem_copy_aligned(data, header, ((size + 3) & ~3) - 8);
            loader->saved_base = g_subtitle_entries;
            loader->saved_count = g_subtitle_state[11];
            g_subtitle_state[11] = count;
            base = g_pause_menu_state.loaded;
            g_subtitle_entries = (int)base;
            for (i = 0; i < g_subtitle_state[11]; i++) {
                int reloc = (int)base - 8;

                ((int *)base)[i * 4] += reloc;
            }
            loader->state = 4;
            loader->flags &= ~4;
        }
        break;
    }
    return 0;
}

typedef struct { short fields[12]; } MenuTextRectangle;
extern char *g_active_menu_object;
extern char g_font_glyphs_small[], g_font_glyphs_large[], g_font_glyphs_medium[];
extern unsigned char g_item_enabled_flags[] MACRO_ADDR;
extern int g_initial_field_value SDATA(D_US2_001ABB3C);
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void SetupGifPaging(int);
extern void *memset(void *, int, int);
extern unsigned long tex_get_effect_descriptor_us2(int);
extern char *GetLocalizedString(int);
extern void gfx_disable_screen_flag(void), gfx_enable_screen_flag(void), DoGifPaging(void);
extern void FontPrintWindow_us2(short *, unsigned long, int, int, unsigned long, char *, float);
extern void DrawMenuCheckBox(int, int, int);
extern void gfx_draw_screen_line(int, int, int, int, int, int);

/* func_US2_002D9178, the v2.00 copy of func_002D84B0: the lower scroll limit is rounded to whole
   row steps, a scroll step is capped at four, and text goes through the scaled print function. */
/* Draws a scrolling list of menu rows with checkboxes, highlighting the selected row. */
int menu_text_list_draw_checkboxes_us2(char *menu)
{
    MenuTextRectangle rectangle, initial;
    short *row;
    int height = 12, texture = 1, line_height, top;
    int count, index, selected, enabled, text;
    int active = *(char **)(g_active_menu_object + 0xE8) == menu;
    char *font = g_font_glyphs_small;
    int spacing;
    unsigned long texture_word;
    int colour;
    int step, span, limit;
    if (*(int *)(menu + 0x30) & 4) { height = 14; font = g_font_glyphs_large; texture = 3; }
    if (*(int *)(menu + 0x30) & 8) { height = 11; font = g_font_glyphs_medium; texture = 2; }
    VU1_addGSregister(66, 68);
    line_height = height + 2;
    VU1_addGSregister(71, 0x2004B);
    SetupGifPaging(0);
    row = *(short **)(menu + 0x34);
    count = 0;
    while (row[0]) { row += 6; count++; }
    if (*(int *)(menu + 0x30) & 16) spacing = height + 3;
    else spacing = *(int *)(menu + 0x24) / (count + 1);
    top = height / 2 - 1;
    memset(&initial, 0, 24);
    initial.fields[0] = 4;
    initial.fields[1] = *(int *)(menu + 0x24) - 4;
    initial.fields[2] = g_initial_field_value;
    initial.fields[3] = *(int *)(menu + 0x20) - 2;
    initial.fields[5] = top - *(int *)(menu + 0x44);
    initial.fields[8] = line_height;
    rectangle = initial;
    step = rectangle.fields[8] * 2;
    if (*(int *)(menu + 0x30) & 0x20) step += 6 + spacing;
    span = rectangle.fields[1] - (rectangle.fields[0] + top) + 2;
    limit = step * ((span + rectangle.fields[8]) / step) + top;
    texture_word = tex_get_effect_descriptor_us2(texture);
    for (index = 0; (*(short **)(menu + 0x34))[index * 6]; index++) {
        selected = active && *(int *)(menu + 0x40) == index;
        enabled = (*(short **)(menu + 0x34))[index * 6 + 1] != 0;
        if (*(int *)(menu + 0x30) & 2) colour = (int)0x80F0F0F0u;
        else if (selected) colour = enabled ? (int)0x8020FFFFu : (int)0x80006060u;
        else colour = enabled ? (int)0x80F0F0F0u : (int)0x80303030u;
        if (!(*(int *)(menu + 0x30) & 0x10000) && selected && rectangle.fields[5] < top) {
            int delta = top - rectangle.fields[5];
            if (delta > 4) delta = 4;
            *(int *)(menu + 0x44) -= delta;
        }
        text = GetLocalizedString((*(short **)(menu + 0x34))[index * 6]);
        rectangle.fields[4] = (*(int *)(menu + 0x30) & 0xA00) ? 32 : 4;
        if (*(int *)(menu + 0x30) & 0x400) {
            rectangle.fields[9] = 1;
            rectangle.fields[4] = *(int *)(menu + 0x20) >> 1;
        }
        if (selected) gfx_disable_screen_flag();
        FontPrintWindow_us2(rectangle.fields, colour, text, -1, texture_word, font, 1.0f);
        if (selected) gfx_enable_screen_flag();
        if (*(int *)(menu + 0x30) & 0x200)
            DrawMenuCheckBox(15, rectangle.fields[5] + 9, g_item_enabled_flags[index] != 0);
        if (*(int *)(menu + 0x30) & 0x800)
            DrawMenuCheckBox(15, rectangle.fields[5] + 9, g_language == *(int *)(*(short **)(menu + 0x34) + index * 6 + 2));
        rectangle.fields[5] += rectangle.fields[7];
        if ((*(short **)(menu + 0x34))[index * 6 + 4]) {
            text = GetLocalizedString((*(short **)(menu + 0x34))[index * 6 + 4]);
            rectangle.fields[4] = 20;
            if (*(int *)(menu + 0x30) & 0x20) {
                int x, y;
                rectangle.fields[4] = *(int *)(menu + 0x20) >> 1;
                x = rectangle.fields[2] + rectangle.fields[4];
                y = rectangle.fields[0] + rectangle.fields[5] + 2;
                gfx_draw_screen_line(x - 8, y, x + 8, y, (colour & 0xFFFFFF) | 0x50000000, 0);
                rectangle.fields[5] += 6;
            }
            FontPrintWindow_us2(rectangle.fields, colour, text, -1, texture_word, font, 1.0f);
            rectangle.fields[5] += spacing;
        }
        rectangle.fields[5] += rectangle.fields[7];
        if (!(*(int *)(menu + 0x30) & 0x10000) && selected) {
            if (rectangle.fields[5] > limit) {
                if (*(int *)(menu + 0x30) & 0x8000)
                    *(int *)(menu + 0x44) += rectangle.fields[5] - limit;
                else {
                    int delta = rectangle.fields[5] - limit;
                    if (delta > 4) delta = 4;
                    *(int *)(menu + 0x44) += delta;
                }
            }
        }
    }
    DoGifPaging();
    if (*(int *)(menu + 0x30) & 0x8000) {
        *(int *)(menu + 0x30) ^= 0x8000;
        return 1;
    }
    return 2;
}

/* func_US2_002D9718 is defined in 002D8E60-listbox.c. */
