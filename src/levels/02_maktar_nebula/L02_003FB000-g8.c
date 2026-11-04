#include "common.h"

extern char *D_L02_001B359C __attribute__((sda));
extern u32 D_L02_001FC060[];
extern u16 D_L02_001B1214 __attribute__((sda));
extern char D_00189E20[];

/* Accumulate the active group entries and reset their current report state. */
void func_L02_003FB000(char *object)
{
    char *state = *(char **)(object + 0x68);
    u32 index = *(u32 *)(state + 0x40);
    u32 entry;
    short *cursor;
    char *table;
    char *record;
    char *hero;

    *(int *)(state + 0x60) = 0;
    *(float *)(state + 0x64) = 0;
    if (index == 0xFF)
        return;
    entry = D_L02_001FC060[index];
    if (entry == 0)
        return;
    cursor = (short *)entry;
    table = D_L02_001B359C;
    do {
        short type;
        record = table + ((*(u16 *)cursor & 0x7FFF) << 8);
        if (record == 0)
            continue;
        if ((u8)record[0x20] == 0xFE)
            continue;
        if ((u8)record[0x20] == 0xFD)
            continue;
        if ((u8)record[0x20] == 1)
            continue;
        type = *(short *)(record + 0xAA);
        if (type == 0x9CA || type == 0xB22 || type == 0xC3B || type == 0xC3E || type == 0x9F8 || type == 0xA44) {
            *(int *)(state + 0x60) += 1;
            *(float *)(state + 0x64) += *(float *)(*(char **)(record + 0x68) + 0x20);
        }
    } while (*cursor++ >= 0);
    hero = D_00189E20;
    *(float *)(state + 0x68) = (float)*(int *)(hero + 0x24CC);
    *(short *)(state + 0x11C) = 0;
    do {
        *(u16 *)(state + 0x11E) = D_L02_001B1214;
    } while (0);
}
