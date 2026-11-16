#include "common.h"

/* A 0x40-byte manipulator record bound by func_0029F978 (AttachManipulator): +1 is set once
   it is attached, +0x20 holds the scale (the layout of GlowManipulator in L00_002A70F8-glow.c). */
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
extern void level_spawn_glow_object(char *);
extern void level_update_glow_objects(char *);

/* Sets the two option-dependent scales, attaches manipulator 24 to the object (scaled 0.92, or
   0.97 of the first scale and the first scale itself) unless object kind 0xF6B, then either
   runs the one-shot spawn or attaches manipulators 22 and 23 at scale 0.01 and runs
   func_L00_002D4C28. */
/* Sets up the glow effects on a level object, either spawning the glow object or attaching the glow records and running the level update. */
void level_setup_glow_effects(char *object, int spawn)
{
    Manipulator4E58 *glow_record;
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
        if (*(short *)(object + 0xAA) == 0xF6B /* moby class 3947 */) {
            g_glow_manipulator_state.scale[0] = 0.92f;
            g_glow_manipulator_state.scale[1] = 0.92f;
            g_glow_manipulator_state.scale[2] = 0.92f;
        } else {
            g_glow_manipulator_state.scale[0] = g_glow_angle_a * 0.97f;
            g_glow_manipulator_state.scale[1] = g_glow_angle_a * 0.97f;
            g_glow_manipulator_state.scale[2] = g_glow_angle_a;
        }
    }
    if (*(short *)(object + 0xAA) == 0xF6B /* moby class 3947 */)
        return;
    if (spawn) {
        level_spawn_glow_object(object);
        return;
    }
    if (g_glow_effect_flags[0]) {
        glow_record = g_glow_records;
        for (i = 0; i < 2; i++, glow_record++) {
            if (glow_record->initialized == 0) {
                AttachManipulator(object, i + 22, glow_record);
                glow_record->scale[0] = 0.01f;
                glow_record->scale[1] = 0.01f;
                glow_record->scale[2] = 0.01f;
            }
        }
    }
    level_update_glow_objects(object);
}
