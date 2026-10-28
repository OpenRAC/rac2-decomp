/* functional: high. Passes map and count on to the callee too, which retail leaves in $a2/$a3. Same reads, writes and calls as retail; the limit is read as the word at 0x1BAEC8. */
#include "include_asm.h"


extern int D_001BAEC8;

/* Turns the offsets of a loaded block into addresses: the first table's
   entries below the limit, the second table's offsets, and the byte lists the
   second table's records name are translated through map. */
void func_002933D0(u8 *hdr, int arg1, u8 *map)
{
    int count = hdr[0] + hdr[1] + hdr[2];
    int *entry = (int *)(hdr + *(int *)(hdr + 4));
    int *first = entry;
    u8 *recs = hdr + *(int *)(hdr + 8);
    u8 *rec;
    u8 *p;
    int i;

    if (count != 0) {
        i = count;
        do {
            int off = entry[0];

            if (off < D_001BAEC8) {
                entry[0] = off + (int)hdr;
                entry[2] += (int)hdr;
            }
            i--;
            entry += 4;
        } while (i != 0);
    }
    rec = recs;
    for (;;) {
        *(int *)(rec + 0xC) += (int)hdr;
        p = rec;
        if (*p != 0xFF) {
            do {
                *p = map[*p];
                p++;
            } while (*p != 0xFF);
        }
        if (*(int *)(rec + 0xC) < 0)
            break;
        rec += 0x10;
    }
    func_002932B8(first, arg1, (int)map, count);
}
