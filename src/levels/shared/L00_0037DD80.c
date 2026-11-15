#include "include_asm.h"
#include "names.h"

extern int D_L05_00231E40_1[][4];

typedef unsigned char u8;

typedef int s32;

typedef unsigned int u32;

typedef struct {
    u32 field00,field04;
    s32 field08;
    u8 gap0c[4];
} OrbitalPairTableView16;

extern u8 D_L00_00231340[];

extern u8 D_L00_001B26B4[];

extern int func_00282948(void *p);

extern void func_L00_0037FE08(void);

extern void func_L00_00387F98(void);

extern void func_L00_0038A9E0(void);

/* shared native body of family 954231c412 */
/* Returns 1 when no slot in the key table already holds this key and owner pair, otherwise 0. */
int func_L00_0037DD80(int key, int owner)
{
    int i;
    int isFree = 1;

    for (i = 0; i < 32; i++)
        if (D_L05_00231E40_1[i][1] == key && D_L05_00231E40_1[i][0] == owner) {
            isFree = 0;
            break;
        }
    return isFree;
}

/* searches 32 sixteen-byte records for matching key and owner words and returns the value word or minus one */
s32 func_L00_0037DDE8(u32 key,u32 owner) {
    OrbitalPairTableView16 *entry=(OrbitalPairTableView16 *)gOwnerKeyTable;
    s32 checked=0;
    do {
        ++checked;
        if(entry->field04==key && entry->field00==owner) return entry->field08;
        ++entry;
    } while(checked<32);
    return -1;
}

extern int func_L00_0037DD80(int a0, int a1);
extern int func_L00_0037DE30(char *a0, char **a1, int a2, int a3);

/* Picks an owner from the list that is not yet paired with the key, or falls back to the one with the best score. */
int func_L00_0037DEF8(char *key, char **candidates, int count, int *outFreePick, int kind)
{
    int i;

    *outFreePick = 1;
    for (i = 0; i < count; i++) {
        if (kind > 0 && *(short *)(*(int *)(candidates[i] + 0x24) + 0x46) != kind)
            continue;
        if (IsOwnerKeyPairFree((int)key, (int)candidates[i]) == 1)
            return (int)candidates[i];
    }
    if (count < 2)
        return 0;
    {
        int result = PickOwnerWithLowestScore(key, candidates, count, kind);

        if (result != 0)
            *outFreePick = 0;
        return result;
    }
}

/* clears the second word of every sixteen-byte record whose second word equals a0 */
void func_L00_0037E0C0(int key)
{
    OrbitalPairTableView16 *entry = (OrbitalPairTableView16 *)gOwnerKeyTable;
    u32 *field = &entry->field04;
    int i;

    for (i = 31; i >= 0; i--) {
        if (*field == (u32)key)
            *field = 0;
        field += 4;
    }
}

/* func_L00_0037E418 is built with -G8: see L00_0037DD80-init-g8.c. */

/* runs the three per-frame passes in the order the level expects */
void func_L00_0037E5C0(void)
{
    ApplySharedResetToStateWords();
    ApplySharedResetToStateWordsCopy();
    FindNearestPoolEntry();
}

/* func_L00_0037E5F0 is built with -G8: see L00_0037DD80-g8.c. */

/* func_L00_0037E640 is matched in L00_0037E640.c (built with -mno-split-addresses). */
