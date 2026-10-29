/* Complete C near miss; not linked and no matching credit.
 * -O2 -G8 -ffunction-sections -fno-strength-reduce: 584/600 bytes, USA 0/28.
 * Eight trials. The post-tested table scans preserve the unconditional first
 * lookup and fallback only after exhausting an empty run. The two flat-array
 * column views have their real two-halfword stride, without fabricated bounds.
 * Strength-reduction control restores integer-index arithmetic; GCSE edge
 * control ties, while GCSE/no-expensive profiles do not recover the retail
 * table-address and fallback-value lifetimes. No volatile or padding remedy.
 * Real sound helper returns int(int,int,void*), verified in 002E10B8.c.
 * No local buffers. Reopen with grounded scan/table lifetime evidence.
 */
#include "common.h"

typedef struct {
    char prefix[0x14];
    char *source;
    int value;
    char gap[0x118];
    int fallback;
} SelectionCallback;
extern SelectionCallback D_001F2840;
extern unsigned int D_00138344 NOT_SDA;
extern int D_001AB9B8 __attribute__((sda));
extern int D_001AB9BC __attribute__((sda));
extern int D_001AB9C0 __attribute__((sda));
extern unsigned short D_00188510[];
extern char D_0025ABC0[];
extern char D_0025AC28[];
typedef struct { char prefix[10]; short icon; char tail[12]; } IconRow;
extern IconRow D_00264630[];
extern int func_002E5E58(int, int, void *);

int func_002CDB30(void)
{
    int flags = D_00138344;
    int old = D_001AB9B8;
    int result = 0;
    int i;
    unsigned short *first;
    unsigned short *second;
    if (flags & 0x10) {
        int value = *(int *)(D_001F2840.source + 0xE0);
        int status;
        if (value != 0)
            D_001F2840.value = value;
        else if (D_001F2840.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900)
        result = 1;
    else if (flags & 0x8000) {
        if (old != D_001AB9BC)
            func_002E5E58(3, 0, 0);
        else
            func_002E5E58(5, 0, 0);
        D_001AB9B8 = D_001AB9BC;
        if (D_001AB9B8 <= 0)
            D_001AB9B8 = 1;
    } else if (flags & 0x2000) {
        if (old != D_001AB9C0)
            func_002E5E58(3, 0, 0);
        else
            func_002E5E58(5, 0, 0);
        D_001AB9B8 = D_001AB9C0;
        if (D_001AB9B8 >= 64)
            D_001AB9B8 = 63;
    }
    D_001AB9BC = D_001AB9B8 - 1;
    D_001AB9C0 = D_001AB9B8 + 1;
    first = D_00188510;
    second = D_00188510 + 1;
    i = D_001AB9BC;
    do {
        if (first[i * 2] != 0 || second[i * 2] != 0)
            break;
        if (--i <= 0) {
            i = 1;
            break;
        }
    } while (1);
    D_001AB9BC = i;
    i = D_001AB9C0;
    do {
        if (first[i * 2] != 0 || second[i * 2] != 0)
            break;
        if (++i >= 64) {
            i = D_001AB9B8;
            break;
        }
    } while (1);
    D_001AB9C0 = i;
    if (D_00188510[D_001AB9B8 * 2] == 0 && D_00188510[D_001AB9B8 * 2 + 1] == 0) {
        *(int *)(D_0025ABC0 + 0x58) = 63;
        *(int *)(D_0025AC28 + 0x34) = 0;
    } else {
        *(int *)(D_0025ABC0 + 0x58) = D_001AB9B8 - 1;
        *(int *)(D_0025AC28 + 0x34) = D_00264630[D_001AB9B8].icon;
    }
    if (D_001AB9B8 != old)
        *(int *)(D_0025AC28 + 0x3C) = -576;
    return result;
}
