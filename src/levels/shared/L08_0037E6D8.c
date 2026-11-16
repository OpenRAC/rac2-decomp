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

extern Group g_tabora_scene;
extern void level_apply_nearest_env_preset(s32);

/* hands the group's first member on, then copies its 8-byte word at +0x38 to every other member */
void moby_copy_group_word_to_members(void)
{
    s32 first = g_tabora_scene.items[0];
    s32 i;

    level_apply_nearest_env_preset(first);
    for (i = 1; i < g_tabora_scene.count; i++)
        *(u64 *)(g_tabora_scene.items[i] + 0x38) = *(u64 *)(first + 0x38);
}
