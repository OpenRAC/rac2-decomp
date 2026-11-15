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

extern short *D_001B1890;
extern TextureEntry *D_001B1898, *D_001B1894;
extern int D_001B15FC;
extern Upload D_001B9340[];
/* Retail reads the allocation cursor absolutely, then updates the same word
   through small data, as in RAC1's GetFrameTex. */
extern int D_001A72D0;
extern int D_001A72D0_gp SDATA(D_001A72D0);
extern int D_001A72DC;

/* Finds a picture in video memory, sending it there first if it is not loaded yet, and gives the drawing setting for it. */
u64 func_0028E640(int index)
{
    short *pair = (short *)((index << 2) + (u32)D_001B1890);
    TextureEntry *palette = D_001B1898 + pair[0];
    TextureEntry *image = D_001B1894 + pair[1];
    int queued = 0;
    int shift, format;
    u64 result;
    u64 paletteWord;

    if (!palette->address || !image->address) {
        Upload *slot = D_001B9340 + D_001B15FC;
        slot->palette = palette->data;
        slot->zero = 0;
        slot->paletteAddress = 0x3ff0;
        D_001B9340[D_001B15FC].image = palette->data;
        slot->width = 5;
        slot->height = 5;
        slot->imageAddress = 0x3ff0;
    }
    if (!palette->address) {
        palette->address = D_001A72D0 >> 8;
        D_001A72D0_gp = D_001A72D0 + 0x400;
        if (D_001B15FC < 64) {
            Upload *slot = D_001B9340 + D_001B15FC;
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
        if (D_001B15FC < 64) {
            Upload *slot = D_001B9340 + D_001B15FC;
            queued = 1;
            *(u32 *)((u8 *)D_001B9340 + D_001B15FC * 16 + 8) = image->data;
            slot->width = image->width;
            slot->height = image->height;
            slot->imageAddress = image->address;
        }
    }
    if (queued)
        D_001B15FC++;
    shift = image->width - 6;
    if (shift < 0)
        shift = 0;
    format = 0x13;
    if (image->address < (D_001A72DC >> 8))
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
