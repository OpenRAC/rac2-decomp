#include "include_asm.h"
#include "names.h"
/* Copies two fields of the current class record (picked by func_00343560 through the
 * D_00139568 index table) into the object and its target. */
typedef struct {
    char pad00[6];
    short f06;
    char pad08[0x3A];
    short f42;
    char pad44[0x9C];
} ClassRecord;

extern char *D_001A8CFC __attribute__((sda));
extern unsigned char D_00139568[];
extern ClassRecord D_00239BA0[];

extern void func_00341550(void *, int);
extern int func_00343560(unsigned char *);
extern char *func_003435A8(char *);

int func_002D35B8(char *object)
{
    char *target;
    int i;

    if (D_001A8CFC != 0) {
        SetTabbedMenuEnabled(D_001A8CFC + 0x3BE08, 1);
        i = GetMenuSelectedId((unsigned char *)D_001A8CFC + 0x3C108);
        {
            ClassRecord *r = &gWeaponTable_00239BA0[gItemSlotToRecord[i]];
            int v = r->f42;
            char *a = D_001A8CFC + 0x3C108;
            *(int *)(object + 0x34) = v;
            target = GetMenuExtraValue(a);
        }
        i = GetMenuSelectedId((unsigned char *)D_001A8CFC + 0x3C108);
        *(int *)(target + 0x58) = gWeaponTable_00239BA0[gItemSlotToRecord[i]].f06;
    }
    return 0;
}
