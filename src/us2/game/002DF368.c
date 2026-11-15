#include "common.h"

/* func_US2_002DF368, the USA v2.00 copy of func_002DE550: the same C, without
 * the first of the two calls to func_002DE6F0, whose result was unused. */

typedef struct {
    int key;
    int flags;
} Func002DE550Slot;

extern Func002DE550Slot D_001B1F50[] __attribute__((sda));
extern int menu_stream_chunk_get_size(int key);
extern void mem_clear(void *data, unsigned int tag, int size);

int func_US2_002DF368(int mode)
{
    int i;
    int size;

    for (i = 0; i < 5; i++) {
        if ((mode ? D_001B1F50[i].flags ^ 1 : D_001B1F50[i].flags) & 1)
            continue;
        if (D_001B1F50[i].key == 0)
            continue;
        if (D_001B1F50[i].flags & 2)
            continue;
        D_001B1F50[i].flags |= 2;
        size = menu_stream_chunk_get_size(D_001B1F50[i].key);
        mem_clear((void *)D_001B1F50[i].key, 0xDEADBEEF, size);
        return D_001B1F50[i].key;
    }
    return 0;
}
