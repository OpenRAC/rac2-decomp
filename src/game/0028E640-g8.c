#include "common.h"

typedef struct {
    u32 data;
    u16 address;
    u8 width, height;
} TextureEntry;
typedef struct {
    u32 palette;
    u16 zero, paletteAddress;
    u32 image;
    u8 width, height;
    u16 imageAddress;
} Upload;

extern short *g_hud_texture_pair_table;
extern TextureEntry *g_hud_group_entries_b, *g_hud_group_entries_a;
extern int g_palette_upload_count;
extern Upload g_upload_slots[];
/* Retail reads the allocation cursor absolutely, then updates the same word
   through small data, as in RAC1's GetFrameTex. */
extern int g_vram_cursor;
extern int D_001A72D0_gp SDATA(D_001A72D0);
extern int g_vram_display_address;

/* Finds a picture in video memory, sending it there first if it is not loaded yet, and gives the drawing setting for it. */
u64 GetFrameTexture(int index)
{
    short *pair = (short *)((index << 2) + (u32)g_hud_texture_pair_table);
    TextureEntry *palette = g_hud_group_entries_b + pair[0];
    TextureEntry *image = g_hud_group_entries_a + pair[1];
    int queued = 0;
    int shift, format;
    u64 result;
    u64 paletteWord;

    if (!palette->address || !image->address) {
        Upload *slot = g_upload_slots + g_palette_upload_count;
        slot->palette = palette->data;
        slot->zero = 0;
        slot->paletteAddress = 0x3ff0;
        g_upload_slots[g_palette_upload_count].image = palette->data;
        slot->width = 5;
        slot->height = 5;
        slot->imageAddress = 0x3ff0;
    }
    if (!palette->address) {
        palette->address = g_vram_cursor >> 8;
        D_001A72D0_gp = g_vram_cursor + 0x400;
        if (g_palette_upload_count < 64) {
            Upload *slot = g_upload_slots + g_palette_upload_count;
            queued = 1;
            slot->palette = palette->data;
            slot->zero = 0;
            slot->paletteAddress = palette->address;
        }
    }
    if (!image->address) {
        int base = D_001A72D0_gp;
        u8 ih = image->height;
        u8 iw = image->width;
        image->address = base >> 8;
        if (ih < iw) {
            ih += iw - ih;
        }
        D_001A72D0_gp = base + (1 << (ih * 2));
        if (g_palette_upload_count < 64) {
            Upload *slot = g_upload_slots + g_palette_upload_count;
            queued = 1;
            *(u32 *)((u8 *)g_upload_slots + g_palette_upload_count * 16 + 8) = image->data;
            slot->width = image->width;
            slot->height = image->height;
            slot->imageAddress = image->address;
        }
    }
    if (queued)
        g_palette_upload_count++;
    shift = image->width - 6;
    if (shift < 0)
        shift = 0;
    format = 0x13;
    if (image->address < (g_vram_display_address >> 8))
        format = 0x1b;
    shift = 1 << shift;
    result = image->address | ((u64)shift << 14);
    result |= (u64)format << 20;
    result |= (u64)image->width << 26;
    result |= (u64)image->height << 30;
    paletteWord = (u64)palette->address << 37;
    paletteWord |= (u64)0x8000 << 19;
    result |= paletteWord;
    return result | 0x8000000000000000ULL;
}
