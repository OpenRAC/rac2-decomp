/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, v0897, 2026-10-29: 1040/1040 bytes, 0/27 US places.
 * Profile: -O2 -G0 -ffunction-sections -frac2-qcopy; declarations below.
 * check.py first reports +0x268. Registration, stream relocation, frame,
 * remap transfer, packet loop setup and fallback branch now agree; texture
 * field-load allocation and GS packing schedule remain different.
 * Measured remedies: .sdata macro-address declarations for the registration
 * count and GS allocation base; typed header/stream views; a threshold-slot
 * pointer captured before increment; distinct packet base and iterator;
 * qcopy for the remap; a flat triple table and local draw/clamp words.
 * Reusing widthBits for the clut block restores the retail loop allocation.
 * Corrected the second texture word's high flag from bit 39 to bit 54.
 * A flat OR expression (as in RAC1 register_object_render_class) regressed
 * to 1036 bytes and changed allocation. Next: model the texture packing
 * temporaries; retail keeps the base in a1, clut in a0, mip offsets in a3/t1.
 * The source marker is restored; no linked build or cross-release credit.
 */
#include "common.h"

/* Relocates three streams and updates four GS words in each 80-byte packet. */
typedef unsigned long U64FF6A8;
typedef unsigned int QuadFF6A8 __attribute__((mode(TI)));
typedef union PacketWordFF6A8 {
    U64FF6A8 d;
    struct { int low, high; } w;
} PacketWordFF6A8;
typedef struct PacketFF6A8 {
    PacketWordFF6A8 tex0;
    U64FF6A8 tag0;
    PacketWordFF6A8 mip0;
    U64FF6A8 tag1;
    PacketWordFF6A8 tex1;
    U64FF6A8 tag2;
    PacketWordFF6A8 flags;
    U64FF6A8 tag3;
    U64FF6A8 tail[2];
} PacketFF6A8;
typedef struct TextureFF6A8 {
    int unknown;
    short width, height, controlCount, first, second, third;
} TextureFF6A8;
typedef struct StreamRecordFF6A8 {
    unsigned char *data;
    unsigned char pad04[12];
} StreamRecordFF6A8;
typedef struct ImageFF6A8 {
    StreamRecordFF6A8 *streams[3];
    unsigned char counts[3], packetCount;
    unsigned char pad10[4];
    float distance1, distance2;
    PacketFF6A8 *packets;
    int instance;
    unsigned char pad24[12];
    int field30;
    unsigned char *field34;
    unsigned char pad38[6];
    short count;
    unsigned char pad40[6];
    unsigned short slot;
    float threshold;
} ImageFF6A8;
extern int D_L00_001B2510 __attribute__((section(".sdata")));
extern ImageFF6A8 *D_L00_00226700[];
extern short D_L00_00226900[];
extern unsigned char D_L00_00226A00[];
extern int D_L00_0022DA00[];
extern QuadFF6A8 D_L00_0022DE00[];
extern U64FF6A8 D_L00_001C91C0[];
extern int D_001A72F4 __attribute__((section(".sdata")));
extern int func_00283CF0(float);
extern int func_00282A18(int);
void func_L00_002FF6A8(ImageFF6A8 *image, TextureFF6A8 *textures, QuadFF6A8 *remap, int key)
{
    int packetIndex;
    unsigned char *permutation;
    PacketFF6A8 *packet, *basePackets;
    D_L00_00226900[D_L00_001B2510] = key;
    D_L00_00226A00[key] = *(unsigned char *)&D_L00_001B2510;
    D_L00_00226700[D_L00_001B2510] = image;
    image->slot = *(unsigned short *)&D_L00_001B2510;
    {
        int threshold = func_00283CF0(image->threshold * 1024.0f);
        int *thresholdSlot = &D_L00_0022DA00[D_L00_001B2510];
        D_L00_001B2510++;
        *thresholdSlot = threshold;
    }
    image->instance = 0;
    image->count = 0;
    {
        int i, j;
        for (i = 0; i < 3; i++) {
            if (image->streams[i]) {
                image->streams[i] = (StreamRecordFF6A8 *)((int)image->streams[i] + (int)image);
                for (j = 0; j < image->counts[i]; j++) {
                    StreamRecordFF6A8 *stream = image->streams[i];
                    stream[j].data = (unsigned char *)((int)stream[j].data + (int)stream);
                }
            }
        }
    }
    if (image->counts[1] == 0) image->distance1 = 8190.0f;
    if (image->counts[2] == 0) image->distance2 = 8192.0f;
    image->field34 = (unsigned char *)((int)image->field34 + (int)image);
    basePackets = image->packets = (PacketFF6A8 *)((int)image->packets + (int)image);
    image->field30 = 0;
    permutation = (unsigned char *)&D_L00_0022DE00[D_L00_00226A00[key]];
    qcopy(permutation, remap);
    packet = basePackets;
    for (packetIndex = 0; packetIndex < image->packetCount; packetIndex++, packet++) {
        int index, lod, address, flags, override;
        index = permutation[packetIndex];
        lod = packet->mip0.w.low;
        address = packet->mip0.w.high;
        flags = packet->flags.w.low;
        override = packet->flags.w.high;
        if (textures) {
            TextureFF6A8 *texture = &textures[index];
            int w, h, logW, logH, offset;
            U64FF6A8 tex0, tex1, mip, format, texHigh, mipHigh, drawBits;
            int widthBits = (unsigned short)texture->width << 16;
            w = widthBits >> 22;
            h = widthBits >> 23;
            if (w <= 0) w = 1;
            if (h <= 0) h = 1;
            logW = func_00282A18(widthBits >> 16);
            logH = func_00282A18(texture->height);
            offset = D_001A72F4 >> 8;
            {
            int third, second;
            third = texture->third + offset;
            second = texture->second + offset;
            widthBits = texture->first + offset;
            format = ((U64FF6A8)logW << 26) | 0x01300000;
            tex0 = ((U64FF6A8)w << 14) | format | ((U64FF6A8)logH << 30);
            mipHigh = ((U64FF6A8)third << 40) | ((U64FF6A8)1 << 34);
            texHigh = ((U64FF6A8)widthBits << 37) | ((U64FF6A8)1 << 34);
            tex1 = ((U64FF6A8)h << 14) | ((U64FF6A8)second << 20);
            tex1 |= mipHigh;
            tex0 |= texHigh;
            tex0 |= (U64FF6A8)1 << 63;
            tex1 |= (U64FF6A8)1 << 54;
            drawBits = ((U64FF6A8)address << 6) | 0x20;
            mip = ((U64FF6A8)(texture->controlCount - 1) << 2) | drawBits;
            mip |= (U64FF6A8)lod << 32;
            packet->tex0.d = tex0;
            packet->mip0.d = mip;
            packet->tex1.d = tex1;
            packet->flags.d = (U64FF6A8)flags | ((U64FF6A8)override << 2) | ((U64FF6A8)index << 24);
            }
        } else {
            U64FF6A8 first = D_L00_001C91C0[index * 3];
            U64FF6A8 second = D_L00_001C91C0[index * 3 + 1];
            U64FF6A8 third = D_L00_001C91C0[index * 3 + 2];
            U64FF6A8 drawBits = ((U64FF6A8)address << 6) | 0x20;
            U64FF6A8 drawWord = (second & 0x1c) | drawBits | ((U64FF6A8)lod << 32);
            U64FF6A8 clampWord = (U64FF6A8)flags | ((U64FF6A8)override << 2) | ((U64FF6A8)index << 24);
            packet->tex0.d = first;
            packet->mip0.d = drawWord;
            packet->tex1.d = third;
            packet->flags.d = clampWord;
        }
    }
}
