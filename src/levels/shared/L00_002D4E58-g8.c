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

extern unsigned char D_001A7A40[] __attribute__((sda));
extern float D_L00_001A7CF4 __attribute__((sda));
extern float D_L00_001A7CF8 __attribute__((sda));
extern Manipulator4E58 D_L00_001B16D0 __attribute__((sda));
extern Manipulator4E58 D_L00_001B2D80[];
extern int D_0018B090[];
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
    Manipulator4E58 *glowRecord;
    int i;

    if (D_001A7A40[1])
        D_L00_001A7CF4 = 1.57f;
    else
        D_L00_001A7CF4 = 0.875f;
    if (D_001A7A40[3])
        D_L00_001A7CF8 = 1.8f;
    else
        D_L00_001A7CF8 = 1.0f;
    if (D_L00_001B16D0.initialized == 0) {
        AttachManipulator(object, 24, &D_L00_001B16D0);
        if (*(short *)(object + 0xAA) == 0xF6B /* moby class 3947 */) {
            D_L00_001B16D0.scale[0] = 0.92f;
            D_L00_001B16D0.scale[1] = 0.92f;
            D_L00_001B16D0.scale[2] = 0.92f;
        } else {
            D_L00_001B16D0.scale[0] = D_L00_001A7CF4 * 0.97f;
            D_L00_001B16D0.scale[1] = D_L00_001A7CF4 * 0.97f;
            D_L00_001B16D0.scale[2] = D_L00_001A7CF4;
        }
    }
    if (*(short *)(object + 0xAA) == 0xF6B /* moby class 3947 */)
        return;
    if (spawn) {
        level_spawn_glow_object(object);
        return;
    }
    if (D_0018B090[0]) {
        glowRecord = D_L00_001B2D80;
        for (i = 0; i < 2; i++, glowRecord++) {
            if (glowRecord->initialized == 0) {
                AttachManipulator(object, i + 22, glowRecord);
                glowRecord->scale[0] = 0.01f;
                glowRecord->scale[1] = 0.01f;
                glowRecord->scale[2] = 0.01f;
            }
        }
    }
    level_update_glow_objects(object);
}
