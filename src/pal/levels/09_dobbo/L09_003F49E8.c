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
extern DobboLimits g_dobbo_limits;

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

struct DobboMoby;
extern void counter_tick_release_sounds(unsigned char *);
extern void dobbo_handle_damage_pal(unsigned char *);
extern int PlayMobySound(int, int, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void moby_mark_spawned(void *);
extern void SetDeathBits(void *, int, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void func_002A7750_3(unsigned char *, int, int);
extern void anim_start_blended(unsigned char *, int, int, int);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float,
                          float, int, float, int, int, int, int, int);
extern struct DobboMoby *spawn_beam_link_pal(void *, void *, struct DobboMoby *, struct DobboMoby *,
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
void beam_link_emitter_update_pal(unsigned char *moby)
{
    unsigned char *vars, *first_link, *second_link;
    Vec point, direction;
    int i;

    if (g_dobbo_limits.mode) {
        if (F32(moby, 0x18) < g_dobbo_limits.low && g_dobbo_limits.side == 1)
            return;
        if (g_dobbo_limits.low < F32(moby, 0x18) && g_dobbo_limits.side == 0)
            return;
        if (g_dobbo_limits.mode == 2) {
            if (g_dobbo_limits.high < F32(moby, 0x18) && g_dobbo_limits.side == 1)
                return;
            if (F32(moby, 0x18) < g_dobbo_limits.high && g_dobbo_limits.side == 2)
                return;
        }
    }
    vars = *(unsigned char **)(moby + 0x68);
    dobbo_handle_damage_pal(moby);
    /* the jump table has entries 0 to 4; 0, 3 and 4 do nothing */
    switch (moby[0x95]) {
    case 0:
    case 3:
    case 4:
        break;
    case 1:
        if (S32(vars, 0x64) == 1) {
            S32(vars, 0x8C) = S32(vars, 0xA4);
            func_002A7750_3(moby, 1, 2);
        }
        break;
    case 2:
        if (S32(vars, 0x64) != 1 && moby[0x20] == 1) {
            S32(vars, 0x8C) = S32(vars, 0xA8);
            if (moby[0x43])
                anim_start_blended(moby, 0, 0, 3);
            func_002A7750_3(moby, 0, 1);
        }
        break;
    }
    /* the jump table starts at state 0, which only steps the timers */
    switch (moby[0x20]) {
    case 0:
        break;
    case 1:
        if (!S16(vars, 0x92)) {
            if (moby[0x43] != 1)
                anim_start_blended(moby, 1, 0, 3);
            func_002A7750_3(moby, 2, -1);
        }
        break;
    case 2:
        if (moby[0x60] & 2) {
            S16(vars, 0x92) = ((s32)S16(vars, 0x9C) * 5 + 2) / 6;
            if (moby[0x43] != 2)
                anim_start_blended(moby, 2, 0, 3);
            PlayMobySound(2, 0, moby);
            for (i = 0; i < 6; i += 2) {
                vec_scale_to_length(&direction, moby + 0xC0, F32(vars, 0x98) * 0.020000001f);
                moby_transform_joint_to_world(moby, i, &point);
                first_link = (unsigned char *)spawn_beam_link_pal(&point, &direction,
                    (struct DobboMoby *)moby, 0, (i / 2) * S16(vars, 0xA0) + S16(vars, 0xA2),
                    F32(vars, 0x94), (float)vars[0x34], F32(vars, 0x80));
                if (first_link && S16(first_link, 0xAA) == 0xD09 && first_link[0x20] != 254 && first_link[0x20] != 253) {
                    moby_transform_joint_to_world(moby, i + 1, &point);
                    second_link = (unsigned char *)spawn_beam_link_pal(&point, &direction,
                        (struct DobboMoby *)moby, (struct DobboMoby *)first_link,
                        (i / 2) * S16(vars, 0xA0) + S16(vars, 0xA2),
                        F32(vars, 0x94), (float)vars[0x34], F32(vars, 0x80));
                    /* the first link's partner */
                    *(unsigned char **)(*(unsigned char **)(first_link + 0x68) + 0x24) = second_link;
                    if (second_link && S16(second_link, 0xAA) == 0xD09 && second_link[0x20] != 254 &&
                        second_link[0x20] != 253)
                        ReserveDobboPairSlot(first_link, second_link, 1, 0);
                    else
                        moby_mark_spawned(first_link);
                }
            }
            func_002A7750_3(moby, 3, -1);
        }
        break;
    case 3:
        if (!S16(vars, 0x92)) {
            S16(vars, 0x92) = ((s32)S16(vars, 0x9E) * 5 + 2) / 6;
            if (moby[0x43] != 3)
                anim_start_blended(moby, 3, 0, 3);
            func_002A7750_3(moby, 4, -1);
        }
        break;
    case 4:
        if (moby[0x60] & 2) {
            if (moby[0x43])
                anim_start_blended(moby, 0, 0, 3);
            func_002A7750_3(moby, 1, -1);
        }
        break;
    case 5:
        if (moby[0x60] & 2) {
            S32(vars, 0x8C) = S32(vars, 0xA4);
            S16(vars, 0x92) = ((s32)S16(vars, 0x9E) * 5 + 2) / 6;
            if (moby[0x43] != 3)
                anim_start_blended(moby, 3, 0, 1);
            func_002A7750_3(moby, 4, -1);
        }
        break;
    case 6:
        SetDeathBits(moby, 0, 3);
        moby_transform_joint_to_world(moby, 6, &direction);
        FastVecSub(&point, &direction, moby + 0x10);
        SpawnExplosionEffects(moby, &point, &direction, 0, 0, 10, 3, 16, 4, 2, 9, 1, -1, 15, 1, 1, -1, 0,
                      0x810001);
        PlayMobySound(3, 0, moby);
        moby_mark_spawned(moby);
        return;
    }
    counter_tick_release_sounds(moby);
}
