#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern void func_00283658(void *moby, void *a1);
extern void func_002833F0(void *moby, void *a1);
extern s32  func_L01_0031BC68(u32 moby, u32 a1, f32 a2);
extern s32  func_00283D38(s32 moby, s32 a1, f32 a2);
extern void func_L02_002EF968(void *moby, s32 a1, s32 a2, void *a3, void *a4, s32 a5);
extern void func_L01_002E1510(void *moby, s32 a1, void *a2, s32 a3, void *a4);

extern u32 D_L03_001B0430[] __attribute__((sda));
extern u8   D_L03_001B0410 __attribute__((sda));
extern f32  D_L03_0029B9F0[];

/* Builds the actor's effect object: the track the level keeps, the two vectors
   the aim is folded into, and the level's own tables. */
void func_L03_003CBC40(char *moby)
{
    u8 packet[0x1A0];
    s32 vars;
    s32 color;
    f32 fade;

    vars = *(s32 *)(moby + 0x68);
    copy_matrix_rotation(packet + 0x150, moby + 0xC0);
    qcopy(packet + 0x180, moby + 0x10);
    *(TI128 *)(packet + 0x190) = 0;
    *(f32 *)(packet + 0x18C) = 1.0f;
    *(f32 *)(packet + 0x198) = 0.19634954f;
    euler_rotation_basis(packet + 0x120, packet + 0x190);
    color = PulseColor(D_L03_001B0430[0], D_L03_001B0430[1], *(f32 *)(vars + 0x30));
    fade = *(f32 *)(vars + 0x18);
    if (fade < 1.0f)
        color = FastTweenColor(color & 0xFFFFFF, color, fade);
    FillQuadPacket(packet, 5, color, &D_L03_001B0410, D_L03_0029B9F0, 1);
    FillQuadPacket(packet + 0x90, 5, color, &D_L03_001B0410, D_L03_0029B9F0 + 0x10, 1);
    TransformAndDrawEntries(packet, 2, packet + 0x120, 0x20, packet + 0x150);
}
