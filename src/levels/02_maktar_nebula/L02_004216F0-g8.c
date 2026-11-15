#include "include_asm.h"
#include "names.h"

/* func_L02_004216F0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it;
   -g gives the two nops retail has before its `div.s` (a -g unit's line labels). */

typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));

extern void *CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern void moby_rebuild_frame_from_transform(u8 *);
extern int PlayMobySound(int, int, void *);
extern char D_0018A0E0[];
extern float D_L02_001B1F98 __attribute__((sda));
extern float D_L02_001B1FA0 __attribute__((sda));
extern float D_L02_001B1FA4 __attribute__((sda));

/* Creates a new moving object (moby class 3336) at the given position, aimed along the given direction, and starts it. Returns the new object, or 0 if none could be made. */
u8 *projectile_l02_spawn(u8 *position, int owner, u8 *direction, float speed) {
    u8 *spawned = CreateMoby(0xD08 /* moby class 3336 */);
    u8 *vars;
    int steps;
    float frameTime;

    if (spawned != 0) {
        *(u8 *)(spawned + 0x20) = 0;
        *(u8 *)(spawned + 0x30) = 0xFF;
        frameTime = D_L02_001B1FA0 * 0.016666668f;
        vars = *(u8 **)(spawned + 0x68);
        *(float *)(vars + 0x64) = speed;
        vec_scale_to_length(vars + 0x40, direction, frameTime);
        *(TI128 *)(spawned + 0x10) = *(TI128 *)position;
        *(TI128 *)(spawned + 0xC0) = *(TI128 *)(vars + 0x40);
        FastVecCross(spawned + 0xD0, spawned + 0xC0, D_0018A0E0);
        vec_scale_to_length(spawned + 0xD0, spawned + 0xD0, -1.0f);
        FastVecCross(spawned + 0xE0, spawned + 0xD0, spawned + 0xC0);
        frameTime = D_L02_001B1FA0 * 0.016666668f;
        steps = FloatToInt(D_L02_001B1FA4 / frameTime);
        *(int *)(vars + 0x58) = steps;
        *(float *)(vars + 0x5C) = 1.0f / IntToFloat(steps);
        *(int *)(vars + 0x50) = owner;
        *(u8 *)(spawned + 0x20) = 0;
        *(float *)(vars + 0x60) = D_L02_001B1F98;
        moby_rebuild_frame_from_transform(spawned);
        PlayMobySound(1, 0, spawned);
    }
    return spawned;
}
