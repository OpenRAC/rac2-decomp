/* func_US2_L15_004329F0, the USA v2.00 copy of func_L15_00430C80: the same C, where the
 * first-time setup also releases the two path markers still held from an earlier state. */
#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[0xAA];
    s16 uid;
} Moby430C80;

extern s32 D_L15_001B1534 __attribute__((sda));
extern s32 D_L15_00221E10[];
extern u8 *D_L15_001B2714[] __attribute__((sda));
extern s32 D_L15_001B2148[] __attribute__((sda));

extern void music_Unpause(void);
extern s32 level_get_saved_value(void);
extern Moby430C80 **level_get_object_list(void);
extern void *level_find_object_by_class_id(int arg);
extern void hero_set_state_value_a(int);
extern void entry_init_all_registered(void);
extern void entry_spawn_list_objects_with_flag(void *object, int handler);
extern void *SpawnFreeLevelObjectById(int, int);
extern void func_L05_0037CEE0(void *, void *, f32);
extern void func_L05_0037D608(void *, void *, f32);
extern int CountActiveLinkedListObjects(int);
extern void func_US2_L15_00432238(void *, int);
extern void ResetGroupToPathStart(void *);
extern void gorn_ship_start_falling(void *);
extern void moby_mark_spawned(void *);

typedef struct {
    u8 pad00[0x34];
    u16 flags;
} Marker;

extern Marker *D_L15_001B1584 __attribute__((sda));
extern Marker *D_L15_001B1588 __attribute__((sda));

void func_US2_L15_004329F0(void *self) {
    Moby430C80 **list;
    void *obj;
    s32 n;
    s32 i;

    if (D_L15_001B1534 == 0) {
        D_L15_001B1534 = 1;
        D_L15_00221E10[0x2C / 4] = 0;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        list = level_get_object_list();
        n = level_get_saved_value();
        for (i = 0; i < n; i++) {
            if (list[i]->uid == 0x957) {
                entry_spawn_list_objects_with_flag(list[i], 1);
                func_L05_0037CEE0(list[i], D_L15_001B2714[0] + D_L15_00221E10[0] * 128 + 0x30, 64.0f);
                func_L05_0037D608(list[i], D_L15_001B2714[0] + D_L15_00221E10[0] * 128 + 0x30, 64.0f);
            }
        }
        obj = SpawnFreeLevelObjectById(0x1211, 1);
        if (obj != 0) {
            ResetGroupToPathStart(obj);
            gorn_ship_start_falling(obj);
        }
        if (D_L15_001B1584 != 0 && D_L15_001B1584->flags != 0) {
            moby_mark_spawned(D_L15_001B1584);
            D_L15_001B1584 = 0;
        }
        if (D_L15_001B1588 != 0 && D_L15_001B1588->flags != 0) {
            moby_mark_spawned(D_L15_001B1588);
            D_L15_001B1588 = 0;
        }
    }
    if (CountActiveLinkedListObjects(level_find_object_by_class_id(0x1211)) == 0 && D_L15_001B2148[0] >= 6) {
        func_US2_L15_00432238(self, 2);
    }
}
