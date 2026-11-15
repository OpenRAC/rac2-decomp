#include "include_asm.h"
#include "names.h"

extern int D_L01_001A8F40;
extern char D_L01_001A90C8 __attribute__((sda));
extern int D_L01_001A90D0 __attribute__((sda));
extern int func_00282948(char *);
extern void func_0029B810(int);

/* Counts down a timer while the level flag is clear, then returns a stored value. */
int func_L01_002F1888(void) {
    if (D_L01_001A8F40 == 0) {
        if (FastFloatHelperD(&D_L01_001A90C8))
            ClearLevelObjectTableEntry(0);
    }
    return D_L01_001A90D0;
}

extern int D_001B2088;
extern int D_001B2458;

/* Looks up a 16-bit value for an entry in a table, or gives -1 when the game is too early to have it. */
int func_L01_00305E18(int index)
{
    int entryIndex = index;
    int table;

    if (D_001B2088 < 5 || (table = D_001B2458) == 0)
        return -1;
    return *(short *)(table + entryIndex * 0x28 + 0x24);
}

/* func_L01_002F1F70 is defined in L01_002A7248.c (this unit has no $gp access for it). */

typedef unsigned char u8;
typedef signed short s16;
typedef float f32;

extern u8 D_L01_00189E20[];

/* The same object as plain D_L01_001A8F40 above: that use stays absolute, this one is the
   $gp form the reach test reads. */
extern int D_L01_001A8F40_gp __asm__("D_L01_001A8F40") __attribute__((sda));

extern f32 func_002E3618(void *a0, void *a1);

/* Reach test against the level's live record: rejects the two "gone" states, an empty
   pair, a closed door, a nonzero key field, the third mode and the $gp flag, then asks
   the helper whether the doubled radius fits, and finally whether the stored count
   covers the caller's index. */
int func_L01_003245E0(u8 *target, int minCount, f32 radius) {
    u8 *hero = D_L01_00189E20;
    int limit = minCount;
    f32 radiusCopy = radius;
    int heroState = *(int *)(hero + 0x2294);
    f32 distance;

    if (heroState == 0x1C)
        return 0;
    if (heroState == 0x31)
        return 0;
    if (*(int *)(hero + 0x24CC) == 0)
        return 0;
    if (*(int *)(hero + 0x340) == 0)
        return 0;
    if (*(s16 *)(hero + 0x34E) != 0)
        return 0;
    if (*(int *)(hero + 0x229C) == 3)
        return 0;
    if (D_L01_001A8F40_gp != 0)
        return 0;
    distance = func_002E3618(target + 0x10, hero + 0x80);
    if (radiusCopy + radiusCopy < distance)
        return 0;
    return D_001B2088 >= limit;
}
