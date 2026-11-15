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
extern void gorn_finish_challenge_stage(void *, int);
extern void ResetGroupToPathStart(void *);
extern void gorn_ship_start_falling(void *);

/* On first call sets up the level's special objects, then starts the next scene once its condition is met. */
void scene_trigger_update(void *self) {
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
            if (list[i]->uid == 0x957 /* moby class 2391 */) {
                entry_spawn_list_objects_with_flag(list[i], 1);
                func_L05_0037CEE0(list[i], D_L15_001B2714[0] + D_L15_00221E10[0] * 128 + 0x30, 64.0f);
                func_L05_0037D608(list[i], D_L15_001B2714[0] + D_L15_00221E10[0] * 128 + 0x30, 64.0f);
            }
        }
        obj = SpawnFreeLevelObjectById(0x1211 /* moby class 4625 */, 1);
        if (obj != 0) {
            ResetGroupToPathStart(obj);
            gorn_ship_start_falling(obj);
        }
    }
    if (CountActiveLinkedListObjects(level_find_object_by_class_id(0x1211 /* moby class 4625 */)) == 0 && D_L15_001B2148[0] >= 6) {
        gorn_finish_challenge_stage(self, 2);
    }
}
