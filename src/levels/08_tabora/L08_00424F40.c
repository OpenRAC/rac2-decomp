#include "names.h"
typedef unsigned char u8;
typedef int s32;

extern char *func_00328C40(int *a, s32 b, s32 c, s32 d);
extern char *func_00328D28(int *a, s32 b, s32 c, s32 d);
extern void group_advance_turn(char *a);

/* Walks the 0x21 slot's entry list: one record per step, each clamps its byte 0x20D down
   against the context's, and the walk ends when the helper reports the list empty. */
/* Removes this creature from its group: the others behind it move up one place and the group gets one smaller. */
void group_remove_member(char *object)
{
    char *state;
    s32 cursor;

    if (*(u8 *)(object + 0x21) == 0xFF)
        return;
    state = *(char **)(object + 0x68);
    cursor = 0;
    func_00328C40(&cursor, *(u8 *)(object + 0x21), 0, 0);
    while (cursor != 0) {
        char *q = *(char **)(object + 0x68);
        if (*(u8 *)(q + 0x20D) >= *(u8 *)(state + 0x20D))
            *(u8 *)(q + 0x20D) = *(u8 *)(q + 0x20D) - 1;
        func_00328D28(&cursor, cursor, 0, 0);
    }
    *(s32 *)(*(char **)(state + 0x1FC)) = *(s32 *)(*(char **)(state + 0x1FC)) - 1;
    group_advance_turn(object);
}
