#include "common.h"

/* A list entry: its label and the action it runs. */
typedef struct {
    short text;
    short action;
    int value;
    short text2;
    unsigned short fadeTimer;
} ListEntry;

/* A grid cell: the resource its preview shows. */
typedef struct {
    u8 pad00[8];
    short resource;
} GridCell;

/* The menu screen with the input, as a grid, a list or a save slot screen. */
typedef struct {
    u8 pad00[0x30];
    union {
        struct {
            int flags;
            u8 pad34[8];
            int cell;
            int rows;
            u8 pad44[4];
            GridCell *cells;
        } grid;
        struct {
            int flags;
            ListEntry *entries;
            u8 pad38[8];
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

/* The resource offset of each language. */
typedef struct {
    int values[6];
} LanguageOffsets;

/* The saved settings block D_001A7B90, which func_00298E08 copies as 40 bytes. */
typedef struct {
    u8 pad00[0x24];
    u8 language;
    u8 pad25[3];
} Settings;

extern int request_is_current_slot(int);
extern short snd_pump_music_and_disc_read(int);
extern int menu_stream_chunk_get_size(int);
extern int menu_stream_chunk_set_latch(int);
extern int menu_stream_chunk_clear_latch(int);
extern int fast_decompress(int, int);
extern int load_start_disc_read(int, int, int);
extern int D_001C51D0;
/* The menu system's current page, D_001F2840.current. */
extern MenuPage *D_001F2854;
extern MenuSystem g_pause_menu_state;
extern MemoryCardState g_memcard_state;
extern Settings g_is_pal_video __attribute__((sda));
extern unsigned char D_001A7A60[] __attribute__((sda));
extern ListEntry D_001AAB48[] SDATA(D_001AAB48);
extern ListEntry D_0025A9F8[];
extern LanguageOffsets D_001ABB30;
extern short D_001A63AC;
extern int D_0014D11C;
extern int D_0014B8AC;

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

/* Reads entry index into buffer slot when the disc is free, then moves to the next state. */
static inline void loadEntry(MenuStream *stream, int index, int slot)
{
    if (D_001A63AC != 0 || stream->entries[index].count == 0)
        return;
    if (startRead(stream, index, stream->buffer[slot])) {
        menu_stream_chunk_set_latch(stream->buffer[slot]);
        stream->loaded[slot] = index;
        stream->state++;
    } else {
        stream->state = -1;
    }
}

/* Picks the resource to show from the screen's flags, then streams it into the two buffers
 * and unpacks it. Adapted from RAC1 src/game/pause.c, update_menu_resource_stream (GPL-3.0). */
int UpdateMenuResourceStream(MenuStream *stream)
{
    int flags;
    int index;
    LanguageOffsets offsets;

    if (request_is_current_slot(6)) {
        snd_pump_music_and_disc_read(1);
        return 0;
    }
    stream->frames++;
    flags = stream->flags;
    if (flags & 1) {
        index = stream->fixed;
        if (index == -1)
            return 0;
    } else if (flags & 2) {
        index = D_001C51D0;
    } else if (flags & 4) {
        index = D_001F2854->focus->data.grid.cell;
    } else if (flags & 0x100) {
        MenuSystem *menus = &g_pause_menu_state;
        MemoryCardState *card = &g_memcard_state;

        index = menus->current->focus->data.save.slot;
        if (index < 0)
            index = 0;
        if (index >= 5)
            index = 4;
        if (card->state < 3 && card->pendingState < 0 && menus->age >= 11) {
            if (stream->state == -1)
                stream->state = 0;
            index = card->slots[index].resource;
            if (index == -1)
                stream->state = index;
            if (card->type != 2)
                stream->state = -1;
        } else {
            stream->state = -1;
        }
    } else if (flags & 8) {
        MenuScreen *grid = D_001F2854->focus;

        index = grid->data.grid.cells[grid->data.grid.cell].resource;
        if (grid->data.grid.rows == 0)
            stream->state = -1;
    } else if (flags & 0x400) {
        index = (stream->frames / 300) % 19;
    } else if (flags & 0x1000) {
        offsets = D_001ABB30;
        index = *stream->languageBase + offsets.values[g_is_pal_video.language];
    } else {
        MenuScreen *list = D_001F2854->focus;
        ListEntry *entries = list->data.list.entries;

        index = list->data.list.selected;
        if (index < 0)
            index = 0;
        if (entries == D_001AAB48) {
            if (index >= 1)
                index += 2;
            index = index > 5 ? 0 : index;
        }
        if (entries == D_0025A9F8)
            index = index > 3 ? 0 : index;
        if ((flags & 0x4000) && entries[index].action == 2)
            index = 9;
    }
    if ((stream->flags & 0x2000) && D_001A7A60[index] == 0)
        index = 30;

    switch (stream->state) {
    case 0:
        if (stream->buffer[0] != 0)
            loadEntry(stream, index, 0);
        break;
    case 1:
    case 3:
    case 5:
        if (D_001A63AC == 0) {
            if (stream->flags & 0x20) {
                /* State 3 has read into the second buffer. */
                int *slot = &stream->buffer[0];
                int second = stream->state == 3;

                slot += second;
                menu_stream_chunk_clear_latch(*slot);
                fast_decompress(*slot + stream->offset, *slot);
                stream->offset = 0;
            }
            stream->state++;
        }
        break;
    case 6:
        stream->state = 2;
        /* fall through */
    case 2:
        if (index == stream->loaded[0])
            break;
        if (index == stream->loaded[1])
            stream->state = 4;
        else if (stream->buffer[1] == 0)
            stream->state = 0;
        else
            loadEntry(stream, index, 1);
        break;
    case 4:
        if (index == stream->loaded[1])
            break;
        if (index == stream->loaded[0])
            stream->state = 2;
        else if (stream->buffer[0] == 0)
            stream->state = -1;
        else
            loadEntry(stream, index, 0);
        break;
    }
    return 0;
}
