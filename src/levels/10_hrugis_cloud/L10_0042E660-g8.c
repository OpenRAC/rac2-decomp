#include "common.h"

typedef struct { char pad[16]; int limit, value; char tail[16]; } RewardSlot;
extern RewardSlot D_L10_002A3C70[];
extern int D_L10_00221CD0[];
extern int g_current_map_index __attribute__((sda));
extern int D_0013A148[];
extern int math_random_int_below(int);
extern int table_find_last_used_entry(int);
extern char *func_L05_003CD1A8(char *);
extern char *moby_spawn_class_a(char *);
extern char *moby_spawn_class_b(char *);
extern char *moby_spawn_class_c(char *);
extern void func_L10_0042E5B8(char *);
extern char *pickup_spawn_homing(char *);
extern int D_L10_001B17A0 __attribute__((sda));

/* Select an available reward kind, update the per-kind and total spawn counts,
 * and optionally roll an additional reward using the current level chance. */
void cloud_drop_reward(char *object, int bonus)
{
    int slot;
    int chance;

    if (math_random_int_below(*(int *)(*(char **)(object + 0x68) + 0x14)) == 0 || !D_L10_001B17A0) {
        slot = math_random_int_below(48);
        D_L10_001B17A0 = 1;
        switch (slot) {
        case 0: case 1: case 2: case 3:
            slot = table_find_last_used_entry(6);
            if (slot < 0 || D_L10_002A3C70[slot].value == D_L10_002A3C70[slot].limit)
                goto ordinary;
            func_L05_003CD1A8(object);
            D_L10_00221CD0[24]++;
            D_L10_00221CD0[28]++;
            break;
        case 5:
            slot = table_find_last_used_entry(2);
            if (slot < 0 || D_L10_002A3C70[slot].value == D_L10_002A3C70[slot].limit)
                goto fallback;
            moby_spawn_class_a(object);
            D_L10_00221CD0[26]++;
            D_L10_00221CD0[28]++;
            break;
        case 6:
            slot = table_find_last_used_entry(3);
            if (slot < 0 || D_L10_002A3C70[slot].value == D_L10_002A3C70[slot].limit)
                goto fallback;
            moby_spawn_class_b(object);
            D_L10_00221CD0[22]++;
            D_L10_00221CD0[28]++;
            break;
        case 7:
            slot = table_find_last_used_entry(4);
            if (slot < 0 || D_L10_002A3C70[slot].value == D_L10_002A3C70[slot].limit) {
        case 4:
        fallback:
                func_L10_0042E5B8(object);
                break;
            }
            moby_spawn_class_c(object);
            D_L10_00221CD0[27]++;
            D_L10_00221CD0[28]++;
            break;
        default:
        ordinary:
            pickup_spawn_homing(object);
            D_L10_00221CD0[23]++;
            D_L10_00221CD0[28]++;
            break;
        }
    }
    if (bonus) {
        chance = D_0013A148[g_current_map_index] * 2;
        if (chance > 11)
            chance = 11;
        if (chance >= math_random_int_below(100)) {
            func_L05_003CD1A8(object);
            D_L10_00221CD0[24]++;
            D_L10_00221CD0[28]++;
        }
    }
}
