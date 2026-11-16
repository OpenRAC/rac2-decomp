#include "common.h"

typedef struct {
    int key;
    int flags;
} Func002DE550Slot;

extern Func002DE550Slot g_menu_chunk_table[] __attribute__((sda));
extern int menu_stream_chunk_get_size(int key);
extern void mem_clear(void *data, unsigned int tag, int size);

/* Takes the next free stream chunk of the wanted kind, marks it used and returns its key. Returns 0 if none is free. */
char *menu_stream_chunk_claim_free(int mode)
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
        menu_stream_chunk_get_size(g_menu_chunk_table[i].key);
        size = menu_stream_chunk_get_size(g_menu_chunk_table[i].key);
        mem_clear((void *)g_menu_chunk_table[i].key, 0xDEADBEEF, size);
        return g_menu_chunk_table[i].key;
    }
    return 0;
}
