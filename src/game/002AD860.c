#include "include_asm.h"
#include "names.h"
typedef struct { char pad[12]; int state; int pad10; int handle; char rest[200]; } RequestRow224;
extern unsigned char D_00139568[];
extern RequestRow224 D_00239BA0[];
extern short D_001A63AC;
extern int D_0018C0E8, D_0018C0EC, D_0018C0F0, D_0018C0F4;
extern int func_00294630(int);
extern void func_00294420(int);
/* Finds the request slot for an index and records the index by the slot state. It starts the
   request if it is idle. Returns 1 if the slot was handled. */
int func_002AD860(int index)
{
    RequestRow224 *rows = gWeaponTable_00239BA0;
    unsigned char *key = gItemSlotToRecord + index;
    int result = 0;
    int state = rows[*key].state;
    if (state == 0) {
        if (!IsClassCached(rows[*key].handle) && D_001A63AC) goto done;
        D_0018C0E8 = index;
        if (!IsClassCached(rows[*key].handle)) LoadClassIntoFreeCacheSlot(rows[*key].handle);
        result = 1;
    } else if (state == 3) { D_0018C0F4 = index; result = 1; }
    else if (state == 2) { D_0018C0F0 = index; result = 1; }
    else if (state == 1) { D_0018C0EC = index; result = 1; }
done:
    return result;
}