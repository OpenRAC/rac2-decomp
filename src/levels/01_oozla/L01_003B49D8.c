#include "include_asm.h"
#include "common.h"

extern void func_L01_003B45D8(void *, void **, int *);

extern void func_L01_003B46C8(char **, int *);

extern void func_L01_003B4700(void *);

extern void func_L01_00318638(void *, void *, void *);

extern int func_002B4FF0(void *, void *, f32);

/* Doubles the two speeds while the object list is not empty, runs the two helpers
   and clamps the 0x1B8 rate to an eighth; the speeds are put back afterwards.
   The clamp needs -ffast-math (the retail's min.s): it is in a file of its own
   because the flag changes the other bodies of a shared unit. */
/* Moves a swimming creature for one frame. It moves faster while it is touching other objects, and limits how fast it can turn. */
void func_L01_003B49D8(u8 *object, void *input) {
    u8 *vars = *(u8 **)(object + 0x68);
    void *list[16];
    int count = 0;
    f32 savedSpeedA, savedSpeedB;

    if (vars[0x35D] != 0) {
        CollectNearbyCreatures(object, list, &count);
    }
    savedSpeedA = *(f32 *)(vars + 0x130);
    savedSpeedB = *(f32 *)(vars + 0x138);
    if (count > 0) {
        *(f32 *)(vars + 0x138) = savedSpeedB + savedSpeedB;
        *(f32 *)(vars + 0x130) = savedSpeedA + savedSpeedA;
    }
    UpdateWanderHeading(object, input, vars + 0x110);
    FollowAttachedTarget(object);
    if (*(f32 *)(vars + 0x1B8) > 0.083333336f) {
        f32 scaled = *(f32 *)(vars + 0x1B8) * 0.9f;

        *(f32 *)(vars + 0x1B8) = (scaled < 0.083333336f) ? scaled : 0.083333336f;
    }
    *(f32 *)(vars + 0x130) = savedSpeedA;
    *(f32 *)(vars + 0x138) = savedSpeedB;
    if (vars[0x35D] != 0) {
        ClearCollectedCreatureMarks(list, &count);
    }
}

/* The same as func_L01_003B49D8, with the extra helper call the object asks for. */
/* Same as the function above but uses a different move helper and returns its result. */
int func_L01_003B4AD0(u8 *object, void *input, f32 *speed) {
    u8 *vars = *(u8 **)(object + 0x68);
    void *list[16];
    int count = 0;
    f32 savedSpeedA, savedSpeedB;
    int result;

    if (vars[0x35D] != 0) {
        CollectNearbyCreatures(object, list, &count);
    }
    savedSpeedA = *(f32 *)(vars + 0x130);
    savedSpeedB = *(f32 *)(vars + 0x138);
    if (count > 0) {
        *(f32 *)(vars + 0x138) = savedSpeedB + savedSpeedB;
        *(f32 *)(vars + 0x130) = savedSpeedA + savedSpeedA;
    }
    result = TurnTowardTargetAndStepMovement(object, input, *speed);
    FollowAttachedTarget(object);
    if (*(f32 *)(vars + 0x1B8) > 0.083333336f) {
        f32 scaled = *(f32 *)(vars + 0x1B8) * 0.9f;

        *(f32 *)(vars + 0x1B8) = (scaled < 0.083333336f) ? scaled : 0.083333336f;
    }
    *(f32 *)(vars + 0x130) = savedSpeedA;
    *(f32 *)(vars + 0x138) = savedSpeedB;
    if (vars[0x35D] != 0) {
        ClearCollectedCreatureMarks(list, &count);
    }
    return result;
}
