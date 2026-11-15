#include "names.h"
/* Carried from rac3-decomp (src/frontbin/397D48.c, func_00399810): the same instructions.
   For each of N 16-byte batch records (pointer, count << 16 | last), stores the last index
   back alone and walks the batch's 64-byte entries in steps of four: each entry's index
   (+0x20) is remapped through C, then the entry is drawn with func_00292B88 when B is given
   (its 16-byte record at that index), else with func_00292EB0. */

#include "common.h"

extern void build_indexed_resident_render_packet();
extern void tex_build_packet_words();

void tex_draw_batches(s32 *batches, u8 *textureTable, u8 *indexMap, s32 batchCount) {
    s32 i, j, entryCount, lastIndex, textureIndex;
    s32 *entry, *nextBatch;
    s32 *batch = batches;
    for (i = 0; i < batchCount; i++) {
        nextBatch = batch + 4;
        entryCount = batch[1] >> 16;
        lastIndex = batch[1] & 0xFFFF;
        batch[1] = lastIndex;
        entry = (s32 *)((u8 *)batch[0] + ((lastIndex - entryCount) << 4));
        for (j = 0; j < entryCount; j += 4) {
            textureIndex = entry[8];
            if (textureIndex >= 0) textureIndex = indexMap[textureIndex];
            if (textureTable) {
                build_indexed_resident_render_packet(entry, textureTable + (textureIndex << 4), entry[0], entry[1], entry[4], entry[5], textureIndex);
            } else {
                tex_build_packet_words((unsigned long *)entry, entry[0], entry[1], entry[4], entry[5], textureIndex);
            }
            entry += 16;
        }
        batch = nextBatch;
    }
}
