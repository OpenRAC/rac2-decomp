#include "names.h"
typedef signed short s16;
typedef unsigned char u8;
typedef signed int s32;
typedef float f32;

extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(s32 a0);
extern u8 **level_get_object_list(void);
extern s32 level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag(u8 *a0, s32 a1);
extern void func_L05_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_L05_0037D608(u8 *a0, u8 *a1, f32 f12);
extern void gorn_finish_challenge_stage(u8 *a0, s32 a1);

extern s32 g_cutscene_l15_started_flag __attribute__((sda));
typedef struct StageState {
    s32 initial;
    s32 pad04[3];
    s32 active;
    s32 pad14[6];
    s32 timer;
} StageState;
extern StageState g_gorn_challenge_vars;
extern s32 g_gorn_challenge_count;
extern u8 *g_scene_object_base;

/* Applies both material passes to matching objects once, then advances the stage. */
void ApplyGornStageMaterials(u8 *moby) {
    s32 remaining;
    s32 count;
    u8 **listPtr;

    if (g_cutscene_l15_started_flag == 0) {
        g_gorn_challenge_vars.timer = 0;
        g_cutscene_l15_started_flag = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        listPtr = level_get_object_list();
        count = level_get_saved_value();
        if (count > 0) {
            remaining = count;
            do {
                if (*(s16 *)(*listPtr + 0xAA) == 0xF93 /* moby class 3987 */) {
                    entry_spawn_list_objects_with_flag(*listPtr, 1);
                    func_L05_0037CEE0(*listPtr, (u8 *)g_scene_object_base + (g_gorn_challenge_vars.initial << 7) + 0x30, 64.0f);
                    func_L05_0037D608(*listPtr, (u8 *)g_scene_object_base + (g_gorn_challenge_vars.initial << 7) + 0x30, 64.0f);
                }
                remaining--;
                listPtr++;
            } while (remaining);
        }
    }
    if (g_gorn_challenge_vars.active == 0 && g_gorn_challenge_count >= 6)
        gorn_finish_challenge_stage(moby, 1);
}
