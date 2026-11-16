/* func_PAL_L00_002D5380, the PAL copy of func_L00_002D4E58: the same C with the callees are PAL's
   func_PAL_L00_002D52C0 and func_PAL_L00_002D5150. */
#include "common.h"

typedef struct {
    unsigned char pad0;
    unsigned char initialized;
    unsigned char pad2[0x20 - 2];
    float scale[3];
    unsigned char pad2C[0x40 - 0x2C];
} Manipulator4E58;

extern unsigned char g_unlocked_item_flags[] __attribute__((sda));
extern float g_glow_angle_a __attribute__((sda));
extern float g_glow_scale __attribute__((sda));
extern Manipulator4E58 g_glow_manipulator_state __attribute__((sda));
extern Manipulator4E58 g_glow_records[];
extern int g_glow_effect_flags[];
extern void AttachManipulator(char *, int, Manipulator4E58 *);
extern void level_spawn_glow_object_pal(char *);
extern void level_update_glow_objects_pal(char *);

/* Sets the two option-dependent scales, attaches manipulator 24 to the object (scaled 0.92, or
   0.97 of the first scale and the first scale itself) unless object kind 0xF6B, then either
   runs the one-shot spawn or attaches manipulators 22 and 23 at scale 0.01 and runs
   func_PAL_L00_002D5150. */
void level_setup_glow_effects_pal(char *object, int spawn)
{
    Manipulator4E58 *record;
    int i;

    if (g_unlocked_item_flags[1])
        g_glow_angle_a = 1.57f;
    else
        g_glow_angle_a = 0.875f;
    if (g_unlocked_item_flags[3])
        g_glow_scale = 1.8f;
    else
        g_glow_scale = 1.0f;
    if (g_glow_manipulator_state.initialized == 0) {
        AttachManipulator(object, 24, &g_glow_manipulator_state);
        if (*(short *)(object + 0xAA) == 0xF6B) {
            g_glow_manipulator_state.scale[0] = 0.92f;
            g_glow_manipulator_state.scale[1] = 0.92f;
            g_glow_manipulator_state.scale[2] = 0.92f;
        } else {
            g_glow_manipulator_state.scale[0] = g_glow_angle_a * 0.97f;
            g_glow_manipulator_state.scale[1] = g_glow_angle_a * 0.97f;
            g_glow_manipulator_state.scale[2] = g_glow_angle_a;
        }
    }
    if (*(short *)(object + 0xAA) == 0xF6B)
        return;
    if (spawn) {
        level_spawn_glow_object_pal(object);
        return;
    }
    if (g_glow_effect_flags[0]) {
        record = g_glow_records;
        for (i = 0; i < 2; i++, record++) {
            if (record->initialized == 0) {
                AttachManipulator(object, i + 22, record);
                record->scale[0] = 0.01f;
                record->scale[1] = 0.01f;
                record->scale[2] = 0.01f;
            }
        }
    }
    level_update_glow_objects_pal(object);
}
