#include "names.h"
/* Manual retail reconstruction, 2026-10-24. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef long s64;
typedef unsigned long long u64;
typedef int QuadWord __attribute__((mode(TI)));
/* Actual inputs: three pointers, full64-bit texture word, integer mode.
 * Both loaded32-bit colour/UV words are sign-extended by retail lw before sd.
 * Scope refs: boot001B22A8 cursor, boot001AC8B0 full16-byte descriptor.
 */
/* The real stream cursor has multiple observed pointer/address views.
 * Layout reference: Lombyte GPL-3.0, pin c41bf1c324eecae8006bf82808ad19ed42ee5eb9,
 * include/rnc/rendering/dma_tag.h. Local changes: canonical scoped binding,
 * ordinary C fields, no assembler name/alias/SDA wrapper or SDK dependency.
 */
typedef struct { u32 tag, address, vif0, vif1; } DmaTag;
typedef union { DmaTag *tag; int *words; u8 *bytes; int address; } PacketCursor;
extern PacketCursor ref_0027E920_00;
extern QuadWord ref_0027E920_01;
/* Adds a picture quad with four corners and colours to the draw list. */
void AppendDisplayListEntry(const s64 *vertices, const int *uv, const int *colors,
                  u64 texture, int enabled)
{
    int *tag;
    u64 *packet;
    ref_0027E920_00.words[0] = 0x10000009;
    ref_0027E920_00.words[1] = 0;
    ref_0027E920_00.words[2] = 0;
    ref_0027E920_00.words[3] = 0x50000009;
    tag = ref_0027E920_00.words;
    ref_0027E920_00.words = tag + 4;
    *(QuadWord *)(tag + 4) = ref_0027E920_01;
    packet = (u64 *)(tag + 8);
    ref_0027E920_00.words = tag + 8;
    if (enabled) packet[0] = 5;
    else packet[0] = 0;
    packet[1] = texture;
    packet[2] = 0x154;
    packet[3] = (s64)colors[0];
    packet[4] = (s64)uv[0];
    packet[5] = vertices[0];
    packet[6] = (s64)colors[1];
    packet[7] = (s64)uv[1];
    packet[8] = vertices[1];
    packet[9] = (s64)colors[2];
    packet[10] = (s64)uv[2];
    packet[11] = vertices[2];
    packet[12] = (s64)colors[3];
    packet[13] = (s64)uv[3];
    packet[14] = vertices[3];
    packet[15] = 0;
    ref_0027E920_00.words += 32;
}
