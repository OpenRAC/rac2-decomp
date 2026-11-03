#include "common.h"

/* One record of the level's table of 0xE0-byte entries at D_L00_00262570. */
typedef struct {
    u8 pad00[0x70];
    float scale;
    u8 pad74[0xE0 - 0x74];
} TableEntry_L00_003FEAC8;

/* The block an object points to at +0x68: one spawned object per slot from +0x10. */
typedef struct {
    u8 pad00[0x10];
    char *spawned[1];
} SpawnSlots_L00_003FEAC8;

/* The boot's resident byte that picks the table row. */
extern u8 D_00139581[];
extern TableEntry_L00_003FEAC8 D_L00_00262570[];
extern float D_L00_001B0C14 __attribute__((sda));

/* Call targets that sit at another address in each level (level 00: 0x3FEBA0 is
   func_L00_003FEBA0, then 0x2EE238, 0x31A768 and 0x3A98E8). */
extern void ref_L00_003FEAC8_00(void *unused, void *pos, void *direction);
extern float ref_L00_003FEAC8_01(void *vec);
extern int ref_L00_003FEAC8_02(int min, int max);
extern char *ref_L00_003FEAC8_03(void *pos, void *direction, void *owner, float length, float scale, int count, float param);

/* Sparks along direction from pos, then spawns an object there, stores it in the owner's
   slot and links it back to the owner. */
void func_L00_003FEAC8(char *obj, char *pos, void *direction, int slot)
{
    SpawnSlots_L00_003FEAC8 *slots = *(SpawnSlots_L00_003FEAC8 **)(obj + 0x68);
    float dir[4] __attribute__((aligned(16)));
    float scale;
    TableEntry_L00_003FEAC8 *entry;
    float length;
    char *spawned;

    qcopy(dir, direction);
    entry = D_L00_00262570 + D_00139581[0];
    scale = entry->scale;
    ref_L00_003FEAC8_00(obj, pos, direction);
    length = ref_L00_003FEAC8_01(dir);
    spawned = ref_L00_003FEAC8_03(pos, dir, obj, length, scale, ref_L00_003FEAC8_02(1, 30), D_L00_001B0C14);
    slots->spawned[slot] = spawned;
    if (spawned != 0) {
        *(char **)(spawned + 0xB8) = obj;
    }
}
