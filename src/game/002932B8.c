#include "names.h"
/* Carried from rac3-decomp (src/frontbin/397D48.c, func_00399810): the same instructions.
   For each of N 16-byte batch records (pointer, count << 16 | last), stores the last index
   back alone and walks the batch's 64-byte entries in steps of four: each entry's index
   (+0x20) is remapped through C, then the entry is drawn with func_00292B88 when B is given
   (its 16-byte record at that index), else with func_00292EB0. */

#include "common.h"

extern void build_indexed_resident_render_packet();
extern void tex_build_packet_words();

void tex_draw_batches(s32 *batches, u8 *texture_table, u8 *index_map, s32 batch_count) {
    s32 i, j, entry_count, last_index, texture_index;
    s32 *entry, *next_batch;
    s32 *batch = batches;
    for (i = 0; i < batch_count; i++) {
        next_batch = batch + 4;
        entry_count = batch[1] >> 16;
        last_index = batch[1] & 0xFFFF;
        batch[1] = last_index;
        entry = (s32 *)((u8 *)batch[0] + ((last_index - entry_count) << 4));
        for (j = 0; j < entry_count; j += 4) {
            texture_index = entry[8];
            if (texture_index >= 0) texture_index = index_map[texture_index];
            if (texture_table) {
                build_indexed_resident_render_packet(entry, texture_table + (texture_index << 4), entry[0], entry[1], entry[4], entry[5], texture_index);
            } else {
                tex_build_packet_words((unsigned long *)entry, entry[0], entry[1], entry[4], entry[5], texture_index);
            }
            entry += 16;
        }
        batch = next_batch;
    }
}
