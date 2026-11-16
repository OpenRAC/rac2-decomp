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

extern GsTextureUploadSlot g_upload_slots[];
extern u32 g_palette_upload_count __attribute__((sda));

u64 register_8bit_texture(int width_log2, int height_log2, u32 pixel_data, u32 palette_data, int palette_addr, int texture_addr)
{
    int shift;
    u64 value;
    u64 size_bits;
    u64 palette_bits;
    u64 result;
    int count;

    shift = width_log2 - 6;
    shift = (shift >= 0) ? shift : 0;
    shift = 1 << shift;
    value = (u64)shift << 14;
    value |= (u64)(texture_addr >> 8);
    size_bits = (u64)width_log2 << 26;
    size_bits |= 0x01300000;
    value |= size_bits;
    value |= (u64)height_log2 << 30;
    palette_bits = (u64)(palette_addr >> 8) << 37;
    palette_bits |= 0x400000000ULL;
    value |= palette_bits;
    result = value | 0x8000000000000000ULL;
    count = g_palette_upload_count;
    if (count < 0x40) {
        g_upload_slots[count].word0 = pixel_data;
        g_upload_slots[count].half6 = palette_addr >> 8;
        g_upload_slots[count].half4 = 0;
        g_upload_slots[count].word8 = palette_data;
        g_upload_slots[count].byteC = width_log2;
        g_upload_slots[count].byteD = height_log2;
        g_upload_slots[count].halfE = texture_addr >> 8;
        g_palette_upload_count = count + 1;
    }
    return result;
}
