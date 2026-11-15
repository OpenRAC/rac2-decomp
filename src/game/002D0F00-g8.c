#include "include_asm.h"
#include "names.h"

/* func_002D0F00: a -G8 unit, so a word load of a global gives the base and the value one
 * register as retail does. The loop pointers are set up in the order whose schedule puts
 * the constant 1 before the destination, as retail has it. The clear address is an
 * integer sum so its operands come out in retail's order. */

extern char *D_001A8CFC;

extern int D_001F2848[];

extern short D_0026185A[];

extern unsigned int D_00139768[];

extern unsigned char D_001A7A0A;

/* Marks each movie in the list as available if the player has seen it, or all of them when everything is unlocked. */
int movie_list_update_availability(void)
{
    unsigned int *seenMask;
    unsigned char allUnlocked;
    char *entryTable;
    char *tableEnd;
    int clearBase;
    char *idPtr;
    char *enabledPtr;
    int clearOffset;
    int one;

    if (D_001A8CFC == 0)
        goto done;
    D_001F2848[0] = 1;
    entryTable = (char *)D_0026185A;
    seenMask = D_00139768;
    allUnlocked = D_001A7A0A;
    clearBase = (int)entryTable + 2;
    one = 1;
    enabledPtr = entryTable + 8;
    idPtr = entryTable + 6;
    tableEnd = entryTable + 0xC6;
    clearOffset = 6;
    do {
        int entryId;
        if (allUnlocked != 0) {
            *(short *)enabledPtr = one;
        } else {
            entryId = *(short *)idPtr;
            if (seenMask[(unsigned int)entryId >> 2] & (one << (entryId & 31)))
                *(short *)enabledPtr = one;
            else
                *(short *)(clearOffset + clearBase) = 0;
        }
        idPtr += 6;
        enabledPtr += 6;
        clearOffset += 6;
    } while ((int)idPtr < (int)tableEnd);
done:
    return 0;
}
