/* Carried from rac3-decomp (src/levels/shared/L01_004B1160.c, func_L01_004B11E0): the
   same instructions. Sends N 16-byte records from BUF to the record table IDX (of 64),
   starting at record START, in requests of at most 0xFFFF records through func_0011D620.
   N == -1 means all of them (func_002EEFE0). -3 for an empty or out-of-range table, -1
   when the records would run past its end. */

#include "common.h"

typedef struct {
    u8 *base;
    s32 count;
    s32 pad[2];
} RecordTable;

extern RecordTable D_00215050[];
extern s32 D_001A7248 MACRO_ADDR;
extern s32 func_002EEFE0(u32);
extern s32 func_0011D620(void *, s32, s32, u8 **, s32, u8 *, s32, s32, s32);

/* Copies records into one of the 64 buffer slots, in pieces of at most 0xFFFF records. Returns 0 on success or a negative error code. */
s32 func_002EEED0(u8 *src, u32 slot, s32 firstRecord, s32 count, s32 mode) {
    u8 *dest;
    s32 chunk;
    s32 bytes;
    if (count == -1) {
        count = GetBufferSlotRecordCount(slot);
    }
    if (slot >= 64 || D_00215050[slot].count == 0) {
        return -3;
    }
    if (D_00215050[slot].count < firstRecord + count) {
        return -1;
    }
    dest = D_00215050[slot].base + firstRecord * 16;
    while (count != 0) {
        chunk = count;
        if (chunk > 0xFFFF) {
            chunk = 0xFFFF;
        }
        bytes = chunk * 16;
        CallRpcServer(&D_001A7248, 1, mode, &dest, 16, src, bytes, 0, 0);
        count -= chunk;
        src += bytes;
        dest += bytes;
    }
    return 0;
}
