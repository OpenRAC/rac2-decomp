#include "include_asm.h"
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

typedef union L08Scratch {
    TI128 ti;
    struct {
        u8 pad[8];
        f32 scale;
        u8 pad2[4];
    } s;
} L08Scratch;

extern u8 g_hero_state[];
extern u8 g_hero_position[];
extern float g_hero_l08_matrix[];
extern Vec g_collision_l08_hit_point;

extern void script_queue_keyed_request(void *, void *);
extern int level_set_game_state_pair_us2(int, int, unsigned int);
extern s32 ref_US2_L08_00420068_00(s32, s32);
extern void pad_clear_port_state(void);
extern void moby_mark_spawned(void *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern int CollLine(void *, void *, int, void *, int);
extern int coll_test_point(void *, int, void *, float);

/* func_US2_L08_00420068, the USA v2.00 copy of func_L08_0041EA88: the same C, plus the store of 10
   at 0x1E0, and the store at 0x1830 moved up with it ahead of a new call to func_002B8518.
   The ref is the player's change-action function, which returns s32 in both levels (L08 at
   func_US2_L08_002D31F8, L19 at func_US2_L19_002C4708). */
/* Ends a vehicle ride: resets the hero state and puts the hero back at a safe spot beside the vehicle (v2.00 copy). */
void vehicle_end_ride_us2(u8 *moby)
{
    u8 *vars;
    u8 *hero;
    L08Scratch scratch;

    vars = *(u8 **)(moby + 0x68);
    script_queue_keyed_request(*(void **)(vars + 0x198), *(void **)(vars + 0x1A0));
    level_set_game_state_pair_us2(0, 0, 1);
    hero = g_hero_state;
    *(u8 *)(hero + 0x22B5) = 0;
    ref_US2_L08_00420068_00(0, 1);
    *(s16 *)(hero + 0x1E0) = 10;
    *(s32 *)(hero + 0x1830) = 0;
    pad_clear_port_state();
    *(f32 *)(hero + 0x108) = 0.16666667f;
    *(s16 *)(hero + 0x1834) = -1;
    if (*(u32 *)(vars + 0x74) != 0)
        moby_mark_spawned((void *)*(u32 *)(vars + 0x74));
    *(u32 *)(vars + 0x74) = 0;
    *(s16 *)(vars + 0x88) = 0;
    *(u8 *)(vars + 0x8A) = 0;
    qcopy(&scratch, g_hero_l08_matrix);
    scratch.s.scale = 0.0f;
    vec_scale_to_length((char *)&scratch, (char *)&scratch, 2.5f);
    scratch.s.scale = 0.7f;
    FastVecAdd((char *)&scratch, (char *)(moby + 0x10), (char *)&scratch);
    *(u32 *)(moby + 0x98) = 0;
    if (CollLine(hero + 0x80, (char *)&scratch, 2, (void *)*(u32 *)(hero + 0x2290), 0) != 0) {
        qcopy(&scratch, &g_collision_l08_hit_point);
        if (coll_test_point((char *)&scratch, 2, (void *)*(u32 *)(hero + 0x2290), 0.4f) != 0) {
            qcopy(&scratch, &g_collision_l08_hit_point);
        }
    }
    qcopy(g_hero_position, &scratch);
    *(u32 *)(moby + 0x98) = *(u32 *)((u8 *)*(u32 **)(moby + 0x24) + 0x10);
    *(u32 *)((u8 *)*(u32 **)(g_hero_position + 0x2210) + 0x9C) = 0;
}
