/* Carried from rac3-decomp (src/frontbin/397D48.c, func_00399810): the same instructions.
   For each of N 16-byte batch records (pointer, count << 16 | last), stores the last index
   back alone and walks the batch's 64-byte entries in steps of four: each entry's index
   (+0x20) is remapped through C, then the entry is drawn with build_indexed_resident_render_packet when B is given
   (its 16-byte record at that index), else with func_00292EB0. */

#include "common.h"

extern void func_00292B88();
extern void func_00292EB0();

void func_002932B8(s32 *a0, u8 *b, u8 *c, s32 n) {
    s32 i, j, cnt, lo, idx;
    s32 *e, *nx;
    s32 *p = a0;
    for (i = 0; i < n; i++) {
        nx = p + 4;
        cnt = p[1] >> 16;
        lo = p[1] & 0xFFFF;
        p[1] = lo;
        e = (s32 *)((u8 *)p[0] + ((lo - cnt) << 4));
        for (j = 0; j < cnt; j += 4) {
            idx = e[8];
            if (idx >= 0) idx = c[idx];
            if (b) {
                build_indexed_resident_render_packet(e, b + (idx << 4), e[0], e[1], e[4], e[5], idx);
            } else {
                func_00292EB0((unsigned long *)e, e[0], e[1], e[4], e[5], idx);
            }
            e += 16;
        }
        p = nx;
    }
}
