#include "names.h"
/* func_PAL_L15_00436870, the PAL copy of func_L15_00430C80: the same C, which also deletes the two tracked mobys. */
#include "common.h"

typedef struct {
    u8 pad00[0xAA];
    s16 uid;
} Moby430C80;

extern s32 g_cutscene_l15_started_flag __attribute__((sda));
extern char *g_gorn_path_first_node __attribute__((sda));
extern char *g_gorn_path_next_node __attribute__((sda));
extern s32 g_gorn_challenge_vars[];
extern u8 *g_scene_object_base[] __attribute__((sda));
extern s32 g_gorn_challenge_count[] __attribute__((sda));

extern void moby_mark_spawned(void *);
extern void music_Unpause(void);
extern s32 level_get_saved_value(void);
extern Moby430C80 **level_get_object_list(void);
extern void *level_find_object_by_class_id(int arg);
extern void hero_set_state_value_a(int);
extern void entry_init_all_registered(void);
extern void entry_spawn_list_objects_with_flag_pal(void *object, int handler);
extern void *SpawnFreeLevelObjectById_pal(int, int);
extern void func_L05_0037CEE0(void *, void *, f32);
extern void func_L05_0037D608(void *, void *, f32);
extern int CountActiveLinkedListObjects(int);
extern void func_PAL_L15_00436118(void *, int);
extern void func_PAL_L15_0043BB70(void *);
extern void func_PAL_L15_0043BD80(void *);

void func_PAL_L15_00436870(void *self) {
    Moby430C80 **list;
    void *obj;
    s32 n;
    s32 i;

    if (g_cutscene_l15_started_flag == 0) {
        g_cutscene_l15_started_flag = 1;
        g_gorn_challenge_vars[0x2C / 4] = 0;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        list = level_get_object_list();
        n = level_get_saved_value();
        for (i = 0; i < n; i++) {
            if (list[i]->uid == 0x957) {
                entry_spawn_list_objects_with_flag_pal(list[i], 1);
                func_L05_0037CEE0(list[i], g_scene_object_base[0] + g_gorn_challenge_vars[0] * 128 + 0x30, 64.0f);
                func_L05_0037D608(list[i], g_scene_object_base[0] + g_gorn_challenge_vars[0] * 128 + 0x30, 64.0f);
            }
        }
        obj = SpawnFreeLevelObjectById_pal(0x1211, 1);
        if (obj != 0) {
            func_PAL_L15_0043BB70(obj);
            func_PAL_L15_0043BD80(obj);
        }
        if (g_gorn_path_first_node != 0) {
            moby_mark_spawned(g_gorn_path_first_node);
            g_gorn_path_first_node = 0;
        }
        if (g_gorn_path_next_node != 0) {
            moby_mark_spawned(g_gorn_path_next_node);
            g_gorn_path_next_node = 0;
        }
    }
    if (CountActiveLinkedListObjects(level_find_object_by_class_id(0x1211)) == 0 && g_gorn_challenge_count[0] >= 6) {
        func_PAL_L15_00436118(self, 2);
    }
}
