#include "common.h"

/* QueueGsTextureUpload: builds the 64-bit GS word for a texture upload and, while the queue has room, records the upload in the next slot. */
typedef struct {
    u32 word0;
    u16 half4;
    u16 half6;
    u32 word8;
    u8 byteC;
    u8 byteD;
    u16 halfE;
} GsTextureUploadSlot;

extern GsTextureUploadSlot D_001B9340[];
extern u32 D_001B15FC __attribute__((sda));

u64 register_8bit_texture(int widthLog2, int heightLog2, u32 pixelData, u32 paletteData, int paletteAddr, int textureAddr)
{
    int shift;
    u64 value;
    u64 sizeBits;
    u64 paletteBits;
    u64 result;
    int count;

    shift = widthLog2 - 6;
    shift = (shift >= 0) ? shift : 0;
    shift = 1 << shift;
    value = (u64)shift << 14;
    value |= (u64)(textureAddr >> 8);
    sizeBits = (u64)widthLog2 << 26;
    sizeBits |= 0x01300000;
    value |= sizeBits;
    value |= (u64)heightLog2 << 30;
    paletteBits = (u64)(paletteAddr >> 8) << 37;
    paletteBits |= 0x400000000ULL;
    value |= paletteBits;
    result = value | 0x8000000000000000ULL;
    count = D_001B15FC;
    if (count < 0x40) {
        D_001B9340[count].word0 = pixelData;
        D_001B9340[count].half6 = paletteAddr >> 8;
        D_001B9340[count].half4 = 0;
        D_001B9340[count].word8 = paletteData;
        D_001B9340[count].byteC = widthLog2;
        D_001B9340[count].byteD = heightLog2;
        D_001B9340[count].halfE = textureAddr >> 8;
        D_001B15FC = count + 1;
    }
    return result;
}
