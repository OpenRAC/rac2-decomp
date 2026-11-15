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

extern u8 g_owner_key_table[];

extern u8 D_L00_001B26B4[];

extern int math_fast_float_d(void *p);

extern void moby_find_nearest_pool_entry(void);

extern void state_l00_apply_shared_reset_words(void);

extern void state_l00_apply_shared_reset_words_2(void);

/* shared native body of family 954231c412 */
/* Returns 1 when no slot in the key table already holds this key and owner pair, otherwise 0. */
int pair_is_owner_key_free(int key, int owner)
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
s32 pair_find_owner_key_value(u32 key,u32 owner) {
    OrbitalPairTableView16 *entry=(OrbitalPairTableView16 *)g_owner_key_table;
    s32 checked=0;
    do {
        ++checked;
        if(entry->field04==key && entry->field00==owner) return entry->field08;
        ++entry;
    } while(checked<32);
    return -1;
}

extern int pair_is_owner_key_free(int a0, int a1);
extern char *pair_pick_owner_lowest_score(char *a0, char **a1, int a2, int a3);

/* Picks an owner from the list that is not yet paired with the key, or falls back to the one with the best score. */
char *pair_choose_owner_for_key(char *key, char **candidates, int count, int *outFreePick, int kind)
{
    int i;

    *outFreePick = 1;
    for (i = 0; i < count; i++) {
        if (kind > 0 && *(short *)(*(int *)(candidates[i] + 0x24) + 0x46) != kind)
            continue;
        if (pair_is_owner_key_free((int)key, (int)candidates[i]) == 1)
            return (int)candidates[i];
    }
    if (count < 2)
        return 0;
    {
        int result = pair_pick_owner_lowest_score(key, candidates, count, kind);

        if (result != 0)
            *outFreePick = 0;
        return result;
    }
}

/* clears the second word of every sixteen-byte record whose second word equals a0 */
void pair_clear_owner_key_entries(int key)
{
    OrbitalPairTableView16 *entry = (OrbitalPairTableView16 *)g_owner_key_table;
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
void level_run_per_frame_passes(void)
{
    state_l00_apply_shared_reset_words();
    state_l00_apply_shared_reset_words_2();
    moby_find_nearest_pool_entry();
}

/* func_L00_0037E5F0 is built with -G8: see L00_0037DD80-g8.c. */

/* func_L00_0037E640 is matched in L00_0037E640.c (built with -mno-split-addresses). */
