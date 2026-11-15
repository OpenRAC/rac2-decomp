#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern void func_00283658(void *a0, void *a1);
extern void func_002833F0(void *a0, void *a1);
extern s32  func_L01_0031BC68(u32 a0, u32 a1, f32 a2);
extern s32  func_00283D38(s32 a0, s32 a1, f32 a2);
extern void func_L02_002EF968(void *a0, s32 a1, s32 a2, void *a3, void *a4, s32 a5);
extern void func_L01_002E1510(void *a0, s32 a1, void *a2, s32 a3, void *a4);

extern u32 D_L03_001B0430[] __attribute__((sda));
extern u8   D_L03_001B0410 __attribute__((sda));
extern f32  D_L03_0029B9F0[];

/* Builds the actor's effect object: the track the level keeps, the two vectors
   the aim is folded into, and the level's own tables. */
void func_L03_003CBC40(char *a0)
{
    u8 work[0x1A0];
    s32 moby;
    s32 res;
    f32 f;

    moby = *(s32 *)(a0 + 0x68);
    copy_matrix_rotation(work + 0x150, a0 + 0xC0);
    qcopy(work + 0x180, a0 + 0x10);
    *(TI128 *)(work + 0x190) = 0;
    *(f32 *)(work + 0x18C) = 1.0f;
    *(f32 *)(work + 0x198) = 0.19634954f;
    euler_rotation_basis(work + 0x120, work + 0x190);
    res = PulseColor(D_L03_001B0430[0], D_L03_001B0430[1], *(f32 *)(moby + 0x30));
    f = *(f32 *)(moby + 0x18);
    if (f < 1.0f)
        res = FastTweenColor(res & 0xFFFFFF, res, f);
    FillQuadPacket(work, 5, res, &D_L03_001B0410, D_L03_0029B9F0, 1);
    FillQuadPacket(work + 0x90, 5, res, &D_L03_001B0410, D_L03_0029B9F0 + 0x10, 1);
    func_L01_002E1510(work, 2, work + 0x120, 0x20, work + 0x150);
}
