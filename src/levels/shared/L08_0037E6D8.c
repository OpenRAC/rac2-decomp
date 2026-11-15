#include "names.h"
typedef unsigned char u8;
typedef unsigned long long u64;
typedef int s32;
typedef short s16;

typedef struct {
    u8 reserved00[0x44];
    s16 count;
    u8 reserved46[0x18C - 0x46];
    s32 items[8];
} Group;

extern Group D_L08_001BD800;
extern void func_L00_00311DC0(s32);

/* hands the group's first member on, then copies its 8-byte word at +0x38 to every other member */
void func_L08_0037E6D8(void)
{
    s32 first = D_L08_001BD800.items[0];
    s32 i;

    ApplyNearestEnvironmentPreset(first);
    for (i = 1; i < D_L08_001BD800.count; i++)
        *(u64 *)(D_L08_001BD800.items[i] + 0x38) = *(u64 *)(first + 0x38);
}
