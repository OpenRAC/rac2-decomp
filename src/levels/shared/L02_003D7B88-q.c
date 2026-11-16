#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char *g_positioned_entry_table[];
extern char *g_moby_group_entries MACRO_ADDR;
extern void moby_set_state(void *, int, int);

/* when the object is idle, retargets it at its state's table entry: takes the slot's limit
   and the entry's position, restarts the timer and switches to state 1 */
void table_positioned_update(char *object)
{
    char *vars = *(char **)(object + 0x68);
    char *entry;

    if (*(u8 *)(object + 0x20) != 0)
        return;
    *(u8 *)(object + 0x30) = 0x80;
    *(f32 *)(vars + 0xC) = -1.0f;
    *(s32 *)(vars + 0x8) = *(s32 *)(g_moby_group_entries + (*(s32 *)vars << 8) + 0x68);
    entry = g_positioned_entry_table[*(s32 *)(vars + 4)];
    *(char **)(vars + 0x18) = entry;
    *(s32 *)(vars + 0x14) = 0;
    *(TI128 *)(object + 0x10) = *(TI128 *)(entry + 0x10);
    moby_set_state(object, 1, -1);
}
