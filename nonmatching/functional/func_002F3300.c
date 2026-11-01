/* functional: medium. Written from the assembly: the packet builder's data tables and GS packet template are named by address, nothing about their meaning is known beyond what the code does; shifts and sums are 32-bit as retail. */
#include "common.h"

extern int D_001B21B0;              /* number of first-pass records */
extern int D_001B21F0;              /* number of second-pass entries */
extern unsigned char *D_001B22A8;   /* output packet cursor */
extern int D_0021D480[];            /* first-pass value b per record */
extern int D_0021D680[];            /* accepted record numbers, ended by -1 */
extern unsigned char D_0021D880[];  /* 16-byte lists of map indices (255 ends, if shorter than 16) */
extern int D_0021D080[];            /* per entry: two halfwords of the page offset the packets were written at */
extern int D_0021CC80[];            /* per entry: its length code (top 4 bits) and a value (low 28) */
extern unsigned int D_001AC710[5][4];   /* the packet template: five quad words */

#define SCRATCH_KEYS ((int *)0x70003000)
#define SCRATCH_MAP ((unsigned char *)0x70003E00)

/* UploadTieTextures: first marks, per record whose key (scratchpad 0x70003000) is not 0x7FFFFFFF
   and has 2*b - key > 0, every map index in its list with 1 (when b - key <= 0) or 3, collecting
   the accepted record numbers at D_0021D680. Then for each of the D_001B21F0 map entries that is
   marked it appends one 112-byte packet (two if the mark has bit 1) to the buffer at D_001B22A8,
   advancing a page offset by the size each uses; a packet that would take the offset past 16379
   is dropped and the walk stops. Returns the final offset << 8. */
int func_002F3300(int frame)
{
    unsigned char *map = SCRATCH_MAP;
    int *keys = SCRATCH_KEYS;
    unsigned char *p;
    unsigned char *end;
    unsigned char *out;
    int *slot = D_0021D080;
    int *src = D_0021CC80;
    int count = D_001B21B0;
    int t9 = (int)((unsigned int)frame >> 8);
    int i, n = 0;

    for (i = 0; i < 256; i++) {
        map[i] = 0;
    }
    for (i = 0; i < count; i++) {
        int key = keys[i];
        int b = D_0021D480[i];
        unsigned char *list;
        int flag, idx;

        if (key == 0x7FFFFFFF) {
            continue;
        }
        if ((int)((unsigned int)b << 1) - key <= 0) {
            continue;
        }
        D_0021D680[n] = i;
        n++;
        flag = (b - key <= 0) ? 1 : 3;
        list = D_0021D880 + i * 16;
        for (;;) {
            idx = *list;
            list++;
            if (idx == 255) {
                break;
            }
            map[idx] = (unsigned char)(map[idx] | flag);
        }
    }
    D_0021D680[n] = -1;

    out = D_001B22A8;
    p = map;
    end = map + D_001B21F0;
    while (p != end) {
        int mark = *p;
        int code = *src;
        unsigned int a0, v, w, v2;
        int v1;
        unsigned int *o;

        p++;
        src++;
        *slot = 0;
        slot++;
        if (mark == 0) {
            continue;
        }
        v1 = (int)((unsigned int)code >> 28);
        a0 = (unsigned int)code & 0x0FFFFFFF;
        if (mark & 2) {
            int i4;

            o = (unsigned int *)out;
            for (i4 = 0; i4 < 16; i4++) {
                o[i4] = D_001AC710[i4 >> 2][i4 & 3];
            }
            o[16] = o[17] = o[18] = o[19] = 0;
            for (i4 = 0; i4 < 4; i4++) {
                o[20 + i4] = D_001AC710[4][i4];
            }
            o[18] = 83;
            ((unsigned short *)out)[18] = (unsigned short)t9;
            if (v1 - 6 > 0) {
                out[38] = (unsigned char)(1 << (v1 - 6));
            }
            w = 1u << v1;
            o[12] = w;
            o[13] = w;
            v = 1u << v1;
            v = v << v1;
            v = v >> 4;
            o[20] = 0x8000 + v;
            o[24] = o[25] = o[26] = o[27] = 0;
            o[25] = a0;
            o[24] = 0x30000000 + v;
            w = 0x50000000 + v;
            v2 = v >> 4;
            ((unsigned short *)slot)[-2] = (unsigned short)t9;
            t9 = t9 + (int)v2;
            o[27] = w;
            out += 112;
            if (t9 - 16379 > 0) {
                out -= 112;
                break;
            }
        }
        {
            int i4;

            o = (unsigned int *)out;
            for (i4 = 0; i4 < 16; i4++) {
                o[i4] = D_001AC710[i4 >> 2][i4 & 3];
            }
            o[16] = o[17] = o[18] = o[19] = 0;
            for (i4 = 0; i4 < 4; i4++) {
                o[20 + i4] = D_001AC710[4][i4];
            }
            v1 = v1 - 1;
            o[18] = 83;
            ((unsigned short *)out)[18] = (unsigned short)t9;
            if (v1 - 6 > 0) {
                out[38] = (unsigned char)(1 << (v1 - 6));
            }
            w = 1u << v1;
            o[12] = w;
            o[13] = w;
            v = 1u << v1;
            v = v << v1;
            a0 = a0 + (v << 2);
            v = v >> 4;
            o[20] = 0x8000 + v;
            o[24] = o[25] = o[26] = o[27] = 0;
            o[25] = a0;
            o[24] = 0x30000000 + v;
            w = 0x50000000 + v;
            v2 = v >> 4;
            ((unsigned short *)slot)[-1] = (unsigned short)t9;
            t9 = t9 + (int)v2;
            o[27] = w;
            out += 112;
            if (t9 - 16379 > 0) {
                out -= 112;
                break;
            }
        }
    }
    D_001B22A8 = out;
    return t9 << 8;
}
