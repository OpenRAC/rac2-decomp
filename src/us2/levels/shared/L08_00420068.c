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
extern float D_L08_001B9D30[];
extern Vec D_L08_001BFF60;

extern void script_queue_keyed_request(void *, void *);
extern int func_US2_L08_0031A090(int, int, unsigned int);
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
void func_US2_L08_00420068(u8 *a0)
{
    u8 *s0;
    u8 *r;
    L08Scratch sc;

    s0 = *(u8 **)(a0 + 0x68);
    script_queue_keyed_request(*(void **)(s0 + 0x198), *(void **)(s0 + 0x1A0));
    func_US2_L08_0031A090(0, 0, 1);
    r = g_hero_state;
    *(u8 *)(r + 0x22B5) = 0;
    ref_US2_L08_00420068_00(0, 1);
    *(s16 *)(r + 0x1E0) = 10;
    *(s32 *)(r + 0x1830) = 0;
    pad_clear_port_state();
    *(f32 *)(r + 0x108) = 0.16666667f;
    *(s16 *)(r + 0x1834) = -1;
    if (*(u32 *)(s0 + 0x74) != 0)
        moby_mark_spawned((void *)*(u32 *)(s0 + 0x74));
    *(u32 *)(s0 + 0x74) = 0;
    *(s16 *)(s0 + 0x88) = 0;
    *(u8 *)(s0 + 0x8A) = 0;
    qcopy(&sc, D_L08_001B9D30);
    sc.s.scale = 0.0f;
    vec_scale_to_length((char *)&sc, (char *)&sc, 2.5f);
    sc.s.scale = 0.7f;
    FastVecAdd((char *)&sc, (char *)(a0 + 0x10), (char *)&sc);
    *(u32 *)(a0 + 0x98) = 0;
    if (CollLine(r + 0x80, (char *)&sc, 2, (void *)*(u32 *)(r + 0x2290), 0) != 0) {
        qcopy(&sc, &D_L08_001BFF60);
        if (coll_test_point((char *)&sc, 2, (void *)*(u32 *)(r + 0x2290), 0.4f) != 0) {
            qcopy(&sc, &D_L08_001BFF60);
        }
    }
    qcopy(g_hero_position, &sc);
    *(u32 *)(a0 + 0x98) = *(u32 *)((u8 *)*(u32 **)(a0 + 0x24) + 0x10);
    *(u32 *)((u8 *)*(u32 **)(g_hero_position + 0x2210) + 0x9C) = 0;
}
