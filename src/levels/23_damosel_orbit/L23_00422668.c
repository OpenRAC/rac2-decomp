#include "include_asm.h"
#include "names.h"

/* func_L23_00422668 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy) for the grouped `lq`/`sq` of its else branch, and
   -frac2-no-annulled-wide-stores (docs/build/compiler-notes.md): reorg's search of that branch's
   target then stops at the 16-byte copy, so the `beqz` keeps an empty slot and `$a0 = $sp`
   stays on each path, as retail has it, where it would otherwise take the `$a0` move from
   behind the copy and fill the return test's `beql` slot from the epilogue. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

typedef int TI16 __attribute__((mode(TI)));

extern void vec_scale_to_length(float *, float *, float);

typedef struct {
    u8 pad[0x18];
    u8 *f18;
} L23Block1C0A80;

extern L23Block1C0A80 g_last_ray_hit;

/* a 16-byte vector, aligned for the quadword copies */
typedef struct {
    float v[4];
} L23Vec __attribute__((aligned(16)));

/* the 48-byte record func_002A8C00 fills and func_002A8E20 reads */
typedef struct {
    u8 pad[0x18];
    u8 b18;
    u8 b19;
    u16 h1A;
    u8 pad1C[0x14];
} L23Hit;

extern u8 *g_hero_moby;

extern s32 CollLine(void *, void *, s32, void *, s32);

extern void make_hit_descriptor(float, L23Hit *, u8 *, s32, L23Vec *);

extern void QueueMobyImpact(u8 *, L23Hit *);

extern int actuator_play_pattern(s32);

extern void part_start_random_scale_effect(void *, s32, s32);

/* the object's first record is set up against the table entry, then its marker byte is set */
/* Checks if a shot has hit something. On a hit it damages the target, plays a sound and
   spark, then moves the shot to its next state. */
void shot_update_hit_check(u8 *moby, void *origin) {
    u8 *payload = *(u8 **)(moby + 0x68);
    L23Vec dir;
    L23Hit hit;
    u8 *hitMoby;

    if (CollLine(origin, moby + 0x10, 0, moby, 0) == 0) {
        return;
    }
    hitMoby = g_last_ray_hit.f18;
    if (hitMoby != 0) {
        if (*(s16 *)(hitMoby + 0xAA) == 0x7E5 /* moby class 2021 */) {
            return;
        }
        vec_scale_to_length(dir.v, (float *)payload, 1.0f);
        make_hit_descriptor(*(float *)(payload + 0x1C), &hit, moby, 0x8B0003, &dir);
        hit.b18 = 5;
        hit.b19 = 3;
        hit.h1A = *(u16 *)(moby + 0xAA);
        if (g_last_ray_hit.f18 == g_hero_moby) {
            QueueMobyImpact(g_last_ray_hit.f18, &hit);
            actuator_play_pattern(0x2B);
        }
        part_start_random_scale_effect(moby + 0x10, 0xA, 1);
    } else {
        *(TI16 *)&dir = *(TI16 *)(moby + 0x10);
        part_start_random_scale_effect(&dir, 0xF, 0);
    }
    moby[0x20] = 2;
}
