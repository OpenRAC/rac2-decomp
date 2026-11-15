#include "common.h"

extern char *D_L02_001FF1C0[];
extern void func_002A7750(u8 *, s32, s32);

struct TableState {
    s32 index;
    u8 unknown04[4];
    s32 elapsed;
    f32 phase;
    char *target;
};

/* when the object is idle, retargets it at its state's table entry: takes the entry's
   position, restarts the timer and switches to state 1 */
void func_L02_003DBEC8(char *object)
{
    struct TableState *q = *(struct TableState **)(object + 0x68);
    char *entry;

    if (*(u8 *)(object + 0x20) != 0)
        return;
    *(u8 *)(object + 0x30) = 0x80;
    q->phase = -1.0f;
    entry = gRoutePolygons[q->index];
    q->target = entry;
    q->elapsed = 0;
    qcopy(object + 0x10, entry + 0x10);
    SetMobyState((u8 *)object, 1, -1);
}
