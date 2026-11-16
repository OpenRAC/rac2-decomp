#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned int u32;

typedef struct { u32 items[5]; } NativeTable20;

extern const NativeTable20 g_level_native_table;

extern void req_reset_queue(unsigned char *);

/* indexed copy of overlay-owned five-entry table */
u32 level_get_native_table_entry(s32 index) {
    NativeTable20 values=g_level_native_table;
    return values.items[index];
}


/* Pass the supplied owner pointer to the measured owner initializer. */
void level_init_owner_object(void *owner)
{
    req_reset_queue(owner);
}
