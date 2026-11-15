#include "names.h"
/* Manual retail reconstruction, 2026-10-24. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef long s64;
typedef unsigned long long u64;
typedef int QuadWord __attribute__((mode(TI)));
/* Two signed 32-bit register words and four complete 64-bit coordinates.
 * Scope refs: boot001B22A8 cursor and boot001AC880 actual16-byte descriptor.
 * The source writes coordinates in the measured0,2,1,3 order, no omitted quad.
 */
/* The real stream cursor has multiple observed pointer/address views.
 * Layout reference: Lombyte GPL-3.0, pin c41bf1c324eecae8006bf82808ad19ed42ee5eb9,
 * include/rnc/rendering/dma_tag.h. Local changes: canonical scoped binding,
 * ordinary C fields, no assembler name/alias/SDA wrapper or SDK dependency.
 */
typedef struct { u32 tag, address, vif0, vif1; } DmaTag;
typedef union { DmaTag *tag; int *words; u8 *bytes; int address; } PacketCursor;
extern PacketCursor ref_0027EA28_00;
extern QuadWord ref_0027EA28_01;
/* Adds a plain colour quad with four corners to the draw list. */
void gfx_append_flat_quad_packet(const s64 *vertices, const int *registers)
{
    int *tag;
    u64 *packet;
    ref_0027EA28_00.words[0] = 0x10000005;
    ref_0027EA28_00.words[1] = 0;
    ref_0027EA28_00.words[2] = 0;
    ref_0027EA28_00.words[3] = 0x50000005;
    tag = ref_0027EA28_00.words;
    ref_0027EA28_00.words = tag + 4;
    *(QuadWord *)(tag + 4) = ref_0027EA28_01;
    packet = (u64 *)(tag + 8);
    ref_0027EA28_00.words = tag + 8;
    packet[0] = 0x4C;
    packet[1] = (s64)registers[0];
    packet[2] = vertices[0];
    packet[3] = vertices[2];
    packet[4] = (s64)registers[1];
    packet[5] = vertices[1];
    packet[6] = vertices[3];
    packet[7] = 0;
    ref_0027EA28_00.words += 16;
}
