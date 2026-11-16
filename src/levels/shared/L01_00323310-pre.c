#include "names.h"
/* Unless 0x48 already holds the key with no pending value at 0x3C, stores the key at 0x48
   when 0x4E and 0x96 are clear, and otherwise queues it at 0x3C/0x3E. Own unit:
   -frac2-gcse-unsplit-edges lets PRE share the table's high half between the head and
   the tail block. */
typedef unsigned char u8;

extern u8 g_script_request_table[];

/* Queues a request key and value in a small table, unless the same key is already set and nothing is waiting. */
void script_queue_keyed_request(int request_key, int request_value)
{
    u8 *request_table = g_script_request_table;

    if (*(short *)(request_table + 0x48) == request_key && *(short *)(request_table + 0x3C) == -1)
        return;
    if (request_key != -1)
        request_key &= 0xFF;
    if (request_value != -1)
        request_key &= 0xFF;
    if (*(short *)(request_table + 0x4E) == 0 && *(short *)(request_table + 0x96) == 0) {
        *(short *)(request_table + 0x48) = request_key;
        return;
    }
    {
        u8 *table_again = g_script_request_table;

        *(short *)(table_again + 0x3C) = request_key;
        *(short *)(table_again + 0x3E) = request_value;
    }
}
