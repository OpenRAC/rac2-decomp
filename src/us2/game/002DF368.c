#include "common.h"

/* func_US2_002DF368, the USA v2.00 copy of func_002DE550: the same C, without
 * the first of the two calls to func_002DE6F0, whose result was unused. */

typedef struct {
    int key;
    int flags;
} Func002DE550Slot;

extern Func002DE550Slot g_menu_chunk_table[] __attribute__((sda));
extern int menu_stream_chunk_get_size(int key);
extern void mem_clear(void *data, unsigned int tag, int size);

int menu_stream_chunk_claim_free_us2(int mode)
{
    int i;
    int size;

    for (i = 0; i < 5; i++) {
        if ((mode ? g_menu_chunk_table[i].flags ^ 1 : g_menu_chunk_table[i].flags) & 1)
            continue;
        if (g_menu_chunk_table[i].key == 0)
            continue;
        if (g_menu_chunk_table[i].flags & 2)
            continue;
        g_menu_chunk_table[i].flags |= 2;
        size = menu_stream_chunk_get_size(g_menu_chunk_table[i].key);
        mem_clear((void *)g_menu_chunk_table[i].key, 0xDEADBEEF, size);
        return g_menu_chunk_table[i].key;
    }
    return 0;
}
