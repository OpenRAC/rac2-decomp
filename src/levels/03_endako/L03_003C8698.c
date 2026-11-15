#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* The state the actor's effect keeps: a 128-bit word, the actor, two words and
   a float. */
typedef struct {
    TI128 q;
    void *p;
    u32 flags;
    u32 pad;
    f32 f;
    u32 z;
} L03_003C8698_State;

/* Four floats: the level's table of them at 0x29A8D0. */
typedef struct {
    f32 x, y, z, w;
} L03_V4;

/* The frame of func_L03_003C8698: the state, the two corners it computes, the
   effect track and the copy of the actor's aim. */
typedef struct {
    L03_003C8698_State st;
    TI128 q30;
    TI128 q40;
    TI128 v[3];
    TI128 q80;
} L03_003C8698_Body;

extern void func_002A8BD0(void *moby, void *a1, u32 a2, f32 a3);
extern void func_002A8C28(void *moby, void *a1, s32 a2, f32 a3, f32 a4, f32 a5,
                          s32 a6, s32 a7, s32 a8);
extern void func_00283658(void *moby, void *a1);
extern void func_002830C0(void *moby, void *a1, void *a2);
extern void func_002761F8(void *moby, void *a1, void *a2, void *a3, void *a4);
extern L03_V4 D_L03_0029A8D0[];

/* Seeds the actor's effect: the state, the aim, the effect track and then the
   four corners of the level's table. */
void func_L03_003C8698(char *moby)
{
    L03_003C8698_Body b;
    f32 one = 1.0f;
    TI128 *aim = (TI128 *)(moby + 0x10);
    L03_V4 *p;
    int i;

    InitEffectRecord_002A8BD0(&b.st, moby, 0x10000, 2.0f);
    SweepCollisionFromObject(moby, aim, 0x10000, 1.25f, 100.0f, one, 0, 1, 0);
    copy_matrix_rotation(&b.v[0], moby + 0xC0);
    qcopy(&b.q80, aim);
    *(f32 *)((u8 *)&b.q80 + 12) = one;
    transform_vector(&b.q30, &D_L03_0029A8D0[0], &b.v[0]);
    p = &D_L03_0029A8D0[1];
    for (i = 3; i >= 0; i--) {
        transform_vector(&b.q40, p, &b.v[0]);
        CollLine(&b.q30, &b.q40, 0, moby, &b.st);
        qcopy(&b.q30, &b.q40);
        p++;
    }
}
