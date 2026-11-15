#include "include_asm.h"

#include "common.h"

/* func_PAL_L09_003F4B40, the PAL copy of func_L09_003F04D0: the same C, where the reloaded
   timers are scaled to 50 Hz and the frame time 1/60 becomes 0.02. */

/* Region limits of the level: while `mode` is set, an object on the wrong side of `low` (or,
   in mode 2, of `high`) is not updated. */
typedef struct {
    int side;
    char pad04[8];
    int mode;
    char pad10[0x18];
    float low;
    char pad2C[0xC];
    float high;
} DobboLimits;
extern DobboLimits D_L09_001C9F80;

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

struct DobboMoby;
extern void counter_tick_release_sounds(unsigned char *);
extern void func_PAL_L09_003F49E8(unsigned char *);
extern void PlayMobySound(int, int, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void moby_mark_spawned(void *);
extern void SetDeathBits(void *, int, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void func_002A7750_3(unsigned char *, int, int);
extern void anim_start_blended(unsigned char *, int, int, int);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float,
                          float, int, float, int, int, int, int, int);
extern struct DobboMoby *func_PAL_L09_003FB0D8(void *, void *, struct DobboMoby *, struct DobboMoby *,
                                           int, float, float, float);
extern int ReserveDobboPairSlot(unsigned char *, unsigned char *, int, int);

#define S32(p, o) (*(int *)((p) + (o)))
#define S16(p, o) (*(short *)((p) + (o)))
#define F32(p, o) (*(float *)((p) + (o)))

/* Updates the beam-link emitter; outside the region limits it does nothing. The mode byte at
   +0x95 can move it to state 1 or 0, then the state at +0x20 runs the cycle: 1 waits for the
   timer at +0x92, then moves to 2; 2 waits for the animation flag, reloads the timer, plays
   sound 2 and spawns three pairs of beam links (class 0xD09) at joints i and i + 1, keeping a
   pair only when both links spawned, then moves to 3; 3 waits for the timer and moves to 4; 4
   moves back to 1 once the animation flag is set; 5 does the same to 4; and 6 destroys the
   emitter in an explosion. Every state but 6 then steps the emitter's counter and timers. */
void func_PAL_L09_003F4B40(unsigned char *object)
{
    unsigned char *state, *first, *second;
    Vec point, direction;
    int i;

    if (D_L09_001C9F80.mode) {
        if (F32(object, 0x18) < D_L09_001C9F80.low && D_L09_001C9F80.side == 1)
            return;
        if (D_L09_001C9F80.low < F32(object, 0x18) && D_L09_001C9F80.side == 0)
            return;
        if (D_L09_001C9F80.mode == 2) {
            if (D_L09_001C9F80.high < F32(object, 0x18) && D_L09_001C9F80.side == 1)
                return;
            if (F32(object, 0x18) < D_L09_001C9F80.high && D_L09_001C9F80.side == 2)
                return;
        }
    }
    state = *(unsigned char **)(object + 0x68);
    func_PAL_L09_003F49E8(object);
    /* the jump table has entries 0 to 4; 0, 3 and 4 do nothing */
    switch (object[0x95]) {
    case 0:
    case 3:
    case 4:
        break;
    case 1:
        if (S32(state, 0x64) == 1) {
            S32(state, 0x8C) = S32(state, 0xA4);
            func_002A7750_3(object, 1, 2);
        }
        break;
    case 2:
        if (S32(state, 0x64) != 1 && object[0x20] == 1) {
            S32(state, 0x8C) = S32(state, 0xA8);
            if (object[0x43])
                anim_start_blended(object, 0, 0, 3);
            func_002A7750_3(object, 0, 1);
        }
        break;
    }
    /* the jump table starts at state 0, which only steps the timers */
    switch (object[0x20]) {
    case 0:
        break;
    case 1:
        if (!S16(state, 0x92)) {
            if (object[0x43] != 1)
                anim_start_blended(object, 1, 0, 3);
            func_002A7750_3(object, 2, -1);
        }
        break;
    case 2:
        if (object[0x60] & 2) {
            S16(state, 0x92) = ((s32)S16(state, 0x9C) * 5 + 2) / 6;
            if (object[0x43] != 2)
                anim_start_blended(object, 2, 0, 3);
            PlayMobySound(2, 0, object);
            for (i = 0; i < 6; i += 2) {
                vec_scale_to_length(&direction, object + 0xC0, F32(state, 0x98) * 0.020000001f);
                moby_transform_joint_to_world(object, i, &point);
                first = (unsigned char *)func_PAL_L09_003FB0D8(&point, &direction,
                    (struct DobboMoby *)object, 0, (i / 2) * S16(state, 0xA0) + S16(state, 0xA2),
                    F32(state, 0x94), (float)state[0x34], F32(state, 0x80));
                if (first && S16(first, 0xAA) == 0xD09 && first[0x20] != 254 && first[0x20] != 253) {
                    moby_transform_joint_to_world(object, i + 1, &point);
                    second = (unsigned char *)func_PAL_L09_003FB0D8(&point, &direction,
                        (struct DobboMoby *)object, (struct DobboMoby *)first,
                        (i / 2) * S16(state, 0xA0) + S16(state, 0xA2),
                        F32(state, 0x94), (float)state[0x34], F32(state, 0x80));
                    /* the first link's partner */
                    *(unsigned char **)(*(unsigned char **)(first + 0x68) + 0x24) = second;
                    if (second && S16(second, 0xAA) == 0xD09 && second[0x20] != 254 &&
                        second[0x20] != 253)
                        ReserveDobboPairSlot(first, second, 1, 0);
                    else
                        moby_mark_spawned(first);
                }
            }
            func_002A7750_3(object, 3, -1);
        }
        break;
    case 3:
        if (!S16(state, 0x92)) {
            S16(state, 0x92) = ((s32)S16(state, 0x9E) * 5 + 2) / 6;
            if (object[0x43] != 3)
                anim_start_blended(object, 3, 0, 3);
            func_002A7750_3(object, 4, -1);
        }
        break;
    case 4:
        if (object[0x60] & 2) {
            if (object[0x43])
                anim_start_blended(object, 0, 0, 3);
            func_002A7750_3(object, 1, -1);
        }
        break;
    case 5:
        if (object[0x60] & 2) {
            S32(state, 0x8C) = S32(state, 0xA4);
            S16(state, 0x92) = ((s32)S16(state, 0x9E) * 5 + 2) / 6;
            if (object[0x43] != 3)
                anim_start_blended(object, 3, 0, 1);
            func_002A7750_3(object, 4, -1);
        }
        break;
    case 6:
        SetDeathBits(object, 0, 3);
        moby_transform_joint_to_world(object, 6, &direction);
        FastVecSub(&point, &direction, object + 0x10);
        SpawnExplosionEffects(object, &point, &direction, 0, 0, 10, 3, 16, 4, 2, 9, 1, -1, 15, 1, 1, -1, 0,
                      0x810001);
        PlayMobySound(3, 0, object);
        moby_mark_spawned(object);
        return;
    }
    counter_tick_release_sounds(object);
}
