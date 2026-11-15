#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef signed int s32;
extern s32 D_L25_001AC4D8 __attribute__((sda));
extern u8 *D_L25_00225910[] __attribute__((nosda));
extern void entry_spawn_list_objects_with_flag(void *, void *);

/* Offers every live entry to the handler that takes one pointer through the loop. */
void func_PAL_L25_00377A28(u8 *a0) {
    s32 i;
    for (i = 0; i < D_L25_001AC4D8; i++) {
        entry_spawn_list_objects_with_flag(D_L25_00225910[i], a0);
    }
}
