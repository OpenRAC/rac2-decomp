#include "include_asm.h"
#include "names.h"

typedef signed int s32;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

extern s32 math_fast_float_d(u8 *a0);
extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(s32 a0);
extern u8 **level_get_object_list(void);
extern s32 level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag(u8 *a0, s32 a1);
extern void func_L05_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_L05_0037D608(u8 *a0, u8 *a1, f32 f12);
extern void UpdateFeltzinMissionReward(u8 *a0, s32 a1);
extern void feltzin_mission_handle_failure(u8 *a0, s32 a1);

extern s32 D_L05_001B1364 __attribute__((sda));
extern s32 D_L05_001B2048 __attribute__((sda));
typedef struct { s32 count; u8 pad04[12]; s32 active; u8 pad14[24]; s32 reset; } FeltzinState;
extern u8 D_L05_00221D10[];
extern u8 D_L05_001B3550[] __attribute__((section(".sdata")));
extern u8 *D_L05_001B2614;

/* Controls the second Feltzin mission: sets up the scene once, then starts the reward when the
   timer is done or reports a failure when the time runs out. */
void feltzin_mission_two_update(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 **objects;
    u32 count;
    s32 index;
    s32 objectCount;

    math_fast_float_d(D_L05_001B3550);
    if (D_L05_001B1364 == 0) {
        ((FeltzinState *)D_L05_00221D10)->reset = 0;
        *(s32 *)D_L05_001B3550 = 0x1C20;
        *(s32 *)(vars + 0x44) = 0x1C20;
        D_L05_001B1364 = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        objects = level_get_object_list();
        objectCount = level_get_saved_value();
        if (objectCount > 0) {
            count = objectCount;
            do {
                u8 *object = *objects;

                if (*(s16 *)(object + 0xAA) == 0x10F5 /* moby class 4341 */) {
                    f32 scale = 64.0f;

                    entry_spawn_list_objects_with_flag(object, 1);
                    index = ((FeltzinState *)D_L05_00221D10)->count;
                    func_L05_0037CEE0(*objects, (u8 *)D_L05_001B2614 + (index << 7) + 0x30, scale);
                    index = ((FeltzinState *)D_L05_00221D10)->count;
                    func_L05_0037D608(*objects, (u8 *)D_L05_001B2614 + (index << 7) + 0x30, scale);
                }
                count--;
                objects++;
            } while (count != 0);
        }
    }
    if (((FeltzinState *)D_L05_00221D10)->active == 0 && D_L05_001B2048 >= 6) {
        UpdateFeltzinMissionReward(moby, 1);
        return;
    }
    if (math_fast_float_d(vars + 0x44) != 0)
        feltzin_mission_handle_failure(moby, 1);
}
