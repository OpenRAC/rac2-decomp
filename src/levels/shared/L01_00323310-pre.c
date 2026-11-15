#include "names.h"
/* Unless 0x48 already holds the key with no pending value at 0x3C, stores the key at 0x48
   when 0x4E and 0x96 are clear, and otherwise queues it at 0x3C/0x3E. Own unit:
   -frac2-gcse-unsplit-edges lets PRE share the table's high half between the head and
   the tail block. */
typedef unsigned char u8;

extern u8 D_L01_001A63A8[];

/* Queues a request key and value in a small table, unless the same key is already set and nothing is waiting. */
void script_queue_keyed_request(int requestKey, int requestValue)
{
    u8 *requestTable = D_L01_001A63A8;

    if (*(short *)(requestTable + 0x48) == requestKey && *(short *)(requestTable + 0x3C) == -1)
        return;
    if (requestKey != -1)
        requestKey &= 0xFF;
    if (requestValue != -1)
        requestKey &= 0xFF;
    if (*(short *)(requestTable + 0x4E) == 0 && *(short *)(requestTable + 0x96) == 0) {
        *(short *)(requestTable + 0x48) = requestKey;
        return;
    }
    {
        u8 *tableAgain = D_L01_001A63A8;

        *(short *)(tableAgain + 0x3C) = requestKey;
        *(short *)(tableAgain + 0x3E) = requestValue;
    }
}
