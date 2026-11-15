#include "common.h"

typedef struct {
    int key;
    int flags;
} Func002DE550Slot;

extern Func002DE550Slot D_001B1F50[] __attribute__((sda));
extern int func_002DE6F0(int key);
extern void func_00282A60(void *data, unsigned int tag, int size);

/* Takes the next free stream chunk of the wanted kind, marks it used and returns its key. Returns 0 if none is free. */
int func_002DE550(int mode)
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
        GetStreamChunkSize(D_001B1F50[i].key);
        size = GetStreamChunkSize(D_001B1F50[i].key);
        ClearMemory((void *)D_001B1F50[i].key, 0xDEADBEEF, size);
        return D_001B1F50[i].key;
    }
    return 0;
}
