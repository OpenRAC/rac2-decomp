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
extern int level_set_game_state_pair_pal(int, int, unsigned int);
extern void ref_L08_0041EA88_00(void *, int);
extern void moby_mark_spawned(void *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern int CollLine(void *, void *, int, void *, int);
extern int coll_test_point(void *, int, void *, float);

void func_PAL_L08_00423D30(u8 *a0)
{
    u8 *s0;
    u8 *r;
    L08Scratch sc;

    s0 = *(u8 **)(a0 + 0x68);
    script_queue_keyed_request(*(void **)(s0 + 0x198), *(void **)(s0 + 0x1A0));
    level_set_game_state_pair_pal(0, 0, 1);
    r = g_hero_state;
    *(u8 *)(r + 0x22B5) = 0;
    ref_L08_0041EA88_00(0, 1);
    *(f32 *)(r + 0x108) = 0.20000002f;
    *(s16 *)(r + 0x1834) = -1;
    *(s32 *)(r + 0x1830) = 0;
    if (*(u32 *)(s0 + 0x74) != 0)
        moby_mark_spawned((void *)*(u32 *)(s0 + 0x74));
    *(u32 *)(s0 + 0x74) = 0;
    *(s16 *)(s0 + 0x88) = 0;
    *(u8 *)(s0 + 0x8A) = 0;
    qcopy(&sc, g_hero_l08_matrix);
    sc.s.scale = 0.0f;
    vec_scale_to_length((char *)&sc, (char *)&sc, 2.5f);
    sc.s.scale = 0.7f;
    FastVecAdd((char *)&sc, (char *)(a0 + 0x10), (char *)&sc);
    *(u32 *)(a0 + 0x98) = 0;
    if (CollLine(r + 0x80, (char *)&sc, 2, (void *)*(u32 *)(r + 0x2290), 0) != 0) {
        qcopy(&sc, &g_collision_l08_hit_point);
        if (coll_test_point((char *)&sc, 2, (void *)*(u32 *)(r + 0x2290), 0.4f) != 0) {
            qcopy(&sc, &g_collision_l08_hit_point);
        }
    }
    qcopy(g_hero_position, &sc);
    *(u32 *)(a0 + 0x98) = *(u32 *)((u8 *)*(u32 **)(a0 + 0x24) + 0x10);
    *(u32 *)((u8 *)*(u32 **)(g_hero_position + 0x2210) + 0x9C) = 0;
}

