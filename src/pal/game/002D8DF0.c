#include "include_asm.h"
#include "common.h"

typedef struct { char pad[0xDB]; unsigned char active; char padDC[0x118 - 0xDC]; char *loaded; unsigned int limit; } State2D6E78;
extern State2D6E78 g_pause_menu_state;
typedef struct { char pad0[0x36C]; int offset; char pad370[0x16B0 - 0x370]; int start; int length; } Stream2D81B0;
typedef struct { unsigned int key; unsigned int flags; } Slot2D81B0;
extern Stream2D81B0 g_copy_setup_data;
extern Slot2D81B0 D_001B1F50[] MACRO_ADDR;
extern int D_001F2958;
extern int load_start_disc_read(int, int, int);
extern void menu_stream_chunk_table_init(int);

/* func_PAL_002D8DF0, the PAL copy of func_002D81B0: the same C without the stream halving and the read. */
int func_PAL_002D8DF0(char *object)
{
    int i;
    unsigned int *key;
    unsigned int *flags;

    menu_stream_chunk_table_init(1);
    *(int *)(object + 0x54) = 0;
    *(int *)(object + 0x38) = 0;
    flags = &D_001B1F50[0].flags;
    key = &D_001B1F50[0].key;
    for (i = 0; i < 5; i++) {
        if (*key != 0 && *key < g_pause_menu_state.limit)
            *flags |= 2;
        flags += 2;
        key += 2;
    }
    *(int *)(object + 0x50) = 0;
    *(int *)(object + 0x10) |= 4;
    return 0;
}
extern short D_001A63AC;
extern void load_request_disc_read_break(void);
extern int g_subtitle_entries __attribute__((sda));
extern int D_00254EA4;

int func_PAL_002D8E90(char *object)
{
    if (D_001A63AC != 0 && *(int *)(object + 0x50) == 3)
        load_request_disc_read_break();
    menu_stream_chunk_table_init(1);
    {
        int value = *(int *)(object + 0x54);
        if (value != 0) {
            D_00254EA4 = *(int *)(object + 0x38);
            g_subtitle_entries = value;
        }
    }
    return 0;
}


extern unsigned char D_001A7BB4 __attribute__((sda));
extern int g_subtitle_state[];
extern int D_PAL_001ABBA0 SDATA(D_PAL_001ABBA0);
extern void mem_copy_aligned(void *, void *, int);

/* The loader object of func_PAL_002D8DF0: its flags, the entry table it replaced and its state. */
typedef struct {
    char pad00[0x10];
    int flags;
    char pad14[0x38 - 0x14];
    int saved_count;
    char pad3C[0x50 - 0x3C];
    int state;
    int saved_base;
} Loader2D8338;

/* func_PAL_002D8F00, the PAL copy of func_002D8338: the read is split in two. State 0 reads a
   length of 1 and state 2 a length of 100, at the 2048-byte block that the D_001A7BB4th word of
   the first read names, keeping the remainder as the offset state 3 unpacks from. A failed read
   ends in state 5, a finished load in state 4. */
int func_PAL_002D8F00(char *object)
{
    Loader2D8338 *loader = (Loader2D8338 *)object;

    switch (loader->state) {
    case 0:
        D_PAL_001ABBA0 = 0;
        if (D_001A63AC == 0) {
            Stream2D81B0 *stream = &g_copy_setup_data;

            if (load_start_disc_read(D_001F2958, stream->start + stream->offset, 1))
                loader->state = 1;
            else
                loader->state = 5;
        }
        break;
    case 1:
        if (D_001A63AC == 0)
            loader->state = 2;
        break;
    case 2:
        if (D_001A63AC == 0) {
            Stream2D81B0 *stream = &g_copy_setup_data;
            int *table = (int *)D_001F2958;
            int position = table[D_001A7BB4];

            D_PAL_001ABBA0 = position % 2048;
            if (load_start_disc_read((int)table, stream->start + stream->offset + position / 2048, 100))
                loader->state = 3;
            else
                loader->state = 5;
        }
        break;
    case 3:
        if (D_001A63AC == 0) {
            char *data = g_pause_menu_state.loaded;
            int *header = (int *)(data + D_PAL_001ABBA0);
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
    case 4:
    case 5:
        break;
    }
    return 0;
}

/* Menu list draw: one text row per entry with selection colours, check boxes and an
   optional second line. */
typedef struct { short fields[12]; } MenuTextRectangle;
extern char *D_001F2854;
extern char D_00263B50[], D_00264290[], D_00263EF0[];
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void SetupGifPaging(int);
extern void *memset(void *, int, int);
extern unsigned long GetEffectTextureDescriptor(int);
extern int GetLocalizedString(int);
extern void gfx_disable_screen_flag(void), gfx_enable_screen_flag(void), DoGifPaging(void);
extern void func_PAL_002804A8(short *, unsigned long, int, int, float, unsigned long, char *);
extern int D_PAL_001ABBA4 SDATA(D_PAL_001ABBA4);
extern int D_PAL_001ABBA8 SDATA(D_PAL_001ABBA8);
extern int D_PAL_001ABBAC SDATA(D_PAL_001ABBAC);
extern void DrawMenuCheckBox(int, int, int);
extern void gfx_draw_screen_line(int, int, int, int, int, int);

/* func_PAL_002D9108, the PAL copy of func_002D84B0: flag 0x20 gets an X offset and 0.9 text scale
   (func_PAL_002804A8 takes the scale between its integer arguments; each register bank keeps its
   order), and scrolling keeps the selected row inside a limit snapped to whole row steps, moving
   at most 4 at a time. */
int func_PAL_002D9108(char *object)
{
    MenuTextRectangle rectangle, initial;
    short *row;
    int height = 12, texture = 1, lineHeight, top, bottomLimit, step, span;
    int count, index, selected, enabled, text;
    int active = *(char **)(D_001F2854 + 0xE8) == object;
    char *font = D_00263B50;
    int spacing;
    unsigned long textureWord;
    int colour;
    float scale;
    if (*(int *)(object + 0x30) & 4) { height = 14; font = D_00264290; texture = 3; }
    if (*(int *)(object + 0x30) & 8) { height = 11; font = D_00263EF0; texture = 2; }
    VU1_addGSregister(66, 68);
    lineHeight = height + 2;
    VU1_addGSregister(71, 0x2004B);
    SetupGifPaging(0);
    row = *(short **)(object + 0x34);
    count = 0;
    while (row[0]) { row += 6; count++; }
    if (*(int *)(object + 0x30) & 16) spacing = height + 3;
    else spacing = *(int *)(object + 0x24) / (count + 1);
    D_PAL_001ABBA4 = (*(int *)(object + 0x30) & 0x20) ? D_PAL_001ABBA8 : 0;
    top = height / 2 - 1;
    memset(&initial, 0, 24);
    initial.fields[0] = 4;
    initial.fields[1] = *(int *)(object + 0x24) - 4;
    initial.fields[2] = D_PAL_001ABBA4;
    initial.fields[3] = *(int *)(object + 0x20) - 2;
    initial.fields[5] = top - *(int *)(object + 0x44);
    initial.fields[8] = lineHeight;
    rectangle = initial;
    step = rectangle.fields[8] * 2;
    if (*(int *)(object + 0x30) & 0x20) step += 6 + spacing;
    span = rectangle.fields[1] - (rectangle.fields[0] + top) + 2;
    bottomLimit = step * ((span + rectangle.fields[8]) / step) + top;
    textureWord = GetEffectTextureDescriptor(texture);
    for (index = 0; (*(short **)(object + 0x34))[index * 6]; index++) {
        selected = active && *(int *)(object + 0x40) == index;
        enabled = (*(short **)(object + 0x34))[index * 6 + 1] != 0;
        if (*(int *)(object + 0x30) & 2) colour = (int)0x80F0F0F0u;
        else if (selected) colour = enabled ? (int)0x8020FFFFu : (int)0x80006060u;
        else colour = enabled ? (int)0x80F0F0F0u : (int)0x80303030u;
        if (!(*(int *)(object + 0x30) & 0x10000) && selected && rectangle.fields[5] < top) {
            int distance = top - rectangle.fields[5];
            if (distance > 4) distance = 4;
            *(int *)(object + 0x44) -= distance;
        }
        text = GetLocalizedString((*(short **)(object + 0x34))[index * 6]);
        rectangle.fields[4] = (*(int *)(object + 0x30) & 0xA00) ? 32 : 4;
        if (*(int *)(object + 0x30) & 0x400) {
            rectangle.fields[9] = 1;
            rectangle.fields[4] = (*(int *)(object + 0x20) + D_PAL_001ABBAC) >> 1;
        }
        if (selected) gfx_disable_screen_flag();
        scale = 1.0f;
        if (*(int *)(object + 0x30) & 0x20) scale = 0.9f;
        func_PAL_002804A8(rectangle.fields, colour, text, -1, scale, textureWord, font);
        if (selected) gfx_enable_screen_flag();
        if (*(int *)(object + 0x30) & 0x200)
            DrawMenuCheckBox(15, rectangle.fields[5] + 9, D_001A7A60[index] != 0);
        if (*(int *)(object + 0x30) & 0x800)
            DrawMenuCheckBox(15, rectangle.fields[5] + 9, D_001A7BB4 == *(int *)(*(short **)(object + 0x34) + index * 6 + 2));
        rectangle.fields[5] += rectangle.fields[7];
        if ((*(short **)(object + 0x34))[index * 6 + 4]) {
            text = GetLocalizedString((*(short **)(object + 0x34))[index * 6 + 4]);
            rectangle.fields[4] = 20;
            if (*(int *)(object + 0x30) & 0x20) {
                int x, y;
                rectangle.fields[4] = *(int *)(object + 0x20) >> 1;
                x = rectangle.fields[2] + rectangle.fields[4];
                y = rectangle.fields[0] + rectangle.fields[5] + 2;
                gfx_draw_screen_line(x - 8, y, x + 8, y, (colour & 0xFFFFFF) | 0x50000000, 0);
                rectangle.fields[5] += 6;
            }
            scale = 1.0f;
            if (*(int *)(object + 0x30) & 0x20) scale = 0.9f;
            func_PAL_002804A8(rectangle.fields, colour, text, -1, scale, textureWord, font);
            rectangle.fields[5] += spacing;
        }
        rectangle.fields[5] += rectangle.fields[7];
        if (!(*(int *)(object + 0x30) & 0x10000) && selected) {
            int bottom = rectangle.fields[5];
            if (bottom > bottomLimit) {
                if (*(int *)(object + 0x30) & 0x8000)
                    *(int *)(object + 0x44) += bottom - bottomLimit;
                else {
                    int distance = bottom - bottomLimit;
                    if (distance > 4) distance = 4;
                    *(int *)(object + 0x44) += distance;
                }
            }
        }
    }
    DoGifPaging();
    if (*(int *)(object + 0x30) & 0x8000) {
        *(int *)(object + 0x30) ^= 0x8000;
        return 1;
    }
    return 2;
}
