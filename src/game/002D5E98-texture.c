#include "common.h"

/* The menu screen with the input, as a grid, a list or a save slot screen. */
typedef struct {
    u8 pad00[0x30];
    union {
        struct {
            int flags;
            u8 pad34[8];
            int cell;
        } grid;
        struct {
            int flags;
            u8 pad34[0xC];
            int selected;
        } list;
        struct {
            int flags;
            u8 pad34[0xC];
            int slot;
        } save;
    } data;
} MenuScreen;

typedef struct {
    u8 pad00[0xE8];
    MenuScreen *focus;
} MenuPage;

/* The menu system D_001F2840, as far as this file reads it. */
typedef struct {
    u8 pad000[0x14];
    MenuPage *current;
    u8 pad018[0x14C];
    int age;
} MenuSystem;

/* The level map screen D_001C4FA0: the selected page and the preview texture. */
typedef struct {
    u8 pad000[0x230];
    int page;
    u8 pad234[0x1C];
    int clutVram;
    int imageVram;
    u8 pad258[0x10];
    u64 tex0;
} LevelMap;

/* The memory card state D_001393E0: the card type, the resource of each slot's save and
 * the card's state. */
typedef struct {
    int resource;
    u8 pad04[0x18];
} SaveSlot;

typedef struct {
    u8 pad000[8];
    int type;
    u8 pad00C[0x24];
    SaveSlot slots[5];
    u8 pad0BC[0xA0];
    int state;
    int pad160;
    int pendingState;
} MemoryCardState;

/* A resource on disc: its first sector and its length in sectors. */
typedef struct {
    int sector;
    int count;
} StreamEntry;

/* A menu screen that streams resources from disc into its two buffers. */
typedef struct {
    u8 pad00[0x30];
    StreamEntry *entries;
    int flags;
    u8 pad38[8];
    int *languageBase;
    int state;
    int buffer[2];
    int loaded[2];
    int fixed;
    int frames;
    int offset;
} MenuStream;

/* A streamed 8-bit image: its size, its 256-entry palette and its pixels. */
typedef struct {
    u8 pad00[8];
    int width;
    int height;
    u8 pad10[0x10];
    u8 clut[0x400];
    u8 pixels[1];
} StreamImage;

extern MenuSystem g_pause_menu_state;
extern LevelMap g_map_overlay_state;
extern MemoryCardState g_memcard_state;
extern int D_0014B8AC, D_0014D11C;
extern s16 D_001A63AC;
extern int menu_stream_chunk_get_size(int), menu_stream_chunk_set_latch(int), menu_stream_chunk_clear_latch(int);
extern int load_start_disc_read(int, int, int), log2dim(int);
extern void func_0029D0E0(void);
extern int fast_decompress(void *, void *);
extern u64 register_8bit_texture(int, int, void *, void *, int, int);

/* Starts reading entry index into buffer (at its end when the entry is to be unpacked in
 * place); returns nonzero when the read started. */
static inline int startRead(MenuStream *stream, int index, int buffer)
{
    if (stream->flags & 0x20) {
        int offset = menu_stream_chunk_get_size(buffer) - stream->entries[index].count * 2048;

        stream->offset = offset;
        buffer += offset;
    }
    if (stream->flags & 0x10000)
        return load_start_disc_read(buffer, stream->entries[index].sector + D_0014D11C,
                             stream->entries[index].count);
    /* Flag 0x10 reads from the same base as the default. */
    if (stream->flags & 0x10)
        return load_start_disc_read(buffer, stream->entries[index].sector + D_0014B8AC,
                             stream->entries[index].count);
    return load_start_disc_read(buffer, stream->entries[index].sector + D_0014B8AC,
                         stream->entries[index].count);
}

/* Selects a preview, starts its disc read, and uploads the completed image. */
int UpdateMenuPreviewTexture(MenuStream *stream)
{
    int index;
    int flags = stream->flags;

    if (flags & 1) {
        index = stream->fixed;
        if (index == -1)
            return 0;
    } else if (flags & 2) {
        index = g_map_overlay_state.page;
    } else if (flags & 4) {
        index = g_pause_menu_state.current->focus->data.grid.cell;
    } else if (flags & 0x100) {
        index = g_pause_menu_state.current->focus->data.save.slot;
        if (index < 0)
            index = 0;
        if (index > 4)
            index = 4;
        if (g_memcard_state.state < 3 && g_memcard_state.pendingState < 0 && g_pause_menu_state.age > 10) {
            if (stream->state == -1)
                stream->state = 0;
            index = g_memcard_state.slots[index].resource;
        } else {
            stream->state = -1;
        }
    } else {
        index = g_pause_menu_state.current->focus->data.list.selected;
        if (index < 0)
            index = 0;
    }

    switch (stream->state) {
    case 0:
    case 2:
        if (index == stream->loaded[0] || stream->buffer[0] == 0 || D_001A63AC != 0)
            break;
        if (stream->entries[index].count == 0)
            break;
        if (startRead(stream, index, stream->buffer[0])) {
            menu_stream_chunk_set_latch(stream->buffer[0]);
            stream->loaded[0] = index;
            stream->state++;
        } else {
            stream->state = -1;
        }
        stream->frames = 0;
        return 0;
    case 1:
    case 3:
        if (D_001A63AC == 0 && (!(stream->flags & 0x40000) || stream->frames > 4)) {
            StreamImage *image;
            u8 *clut;
            u8 *pixels;
            int logWidth;
            int logHeight;

            menu_stream_chunk_clear_latch(stream->buffer[0]);
            if (stream->flags & 0x20) {
                fast_decompress((u8 *)stream->buffer[0] + stream->offset, (u8 *)stream->buffer[0]);
                stream->offset = 0;
            }
            image = (StreamImage *)stream->buffer[0];
            clut = image->clut;
            pixels = image->pixels;
            logWidth = log2dim(image->width);
            logHeight = log2dim(image->height);
            g_map_overlay_state.tex0 = register_8bit_texture(logWidth, logHeight, clut, pixels,
                                            g_map_overlay_state.clutVram, g_map_overlay_state.imageVram);
            func_0029D0E0();
            stream->frames = 0;
            stream->state = 2;
            return 0;
        }
        break;
    default:
        return 0;
    }

    /* Count the frames spent waiting, up to 256. */
    if (++stream->frames > 256)
        stream->frames = 256;
    return 0;
}
