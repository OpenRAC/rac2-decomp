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

/* Builds and returns the GS texture register value for an 8-bit texture from its size, base and format arguments. */
u64 func_00294D80(int a0, int a1, u32 a2, u32 a3, int arg5, int arg6)
{
    int shift;
    u64 value;
    u64 term;
    u64 term2;
    u64 result;
    int count;

    shift = a0 - 6;
    shift = (shift >= 0) ? shift : 0;
    shift = 1 << shift;
    value = (u64)shift << 14;
    value |= (u64)(arg6 >> 8);
    term = (u64)a0 << 26;
    term |= 0x01300000;
    value |= term;
    value |= (u64)a1 << 30;
    term2 = (u64)(arg5 >> 8) << 37;
    term2 |= 0x400000000ULL;
    value |= term2;
    result = value | 0x8000000000000000ULL;
    count = D_001B15FC;
    if (count < 0x40) {
        D_001B9340[count].word0 = a2;
        D_001B9340[count].half6 = arg5 >> 8;
        D_001B9340[count].half4 = 0;
        D_001B9340[count].word8 = a3;
        D_001B9340[count].byteC = a0;
        D_001B9340[count].byteD = a1;
        D_001B9340[count].halfE = arg6 >> 8;
        D_001B15FC = count + 1;
    }
    return result;
}
