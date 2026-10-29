/* Retained ring rendering, 2026-10-28: 732/748B,0/2US, frame240/2D0.
 * Two bounded trials; sequencing cosine before real globals ties732.
 * Required profile -O2 -G0 -ffunction-sections -frac2-zero-ti-por.
 * Two144B packets are proved by helper trip counts, not stride alone:
 * L01_002E1510 +1C takes A1 as S6; +4C copies it toS2; +68 decrements;
 * +80 BNEL S2,zero loops. Its render loop +CC resetsS2, +E4 decrements,
 * +114 BNEZ loops. Argument2 executes exactly2 records in both loops.
 * Later caller only draws packet0/1. Retail's third144B stack region120..1AF
 * has no observed consumer; no packet[3] added just to force the frame.
 * 283658 writes64B: three LQ/SQ rows plus SQC2 VF0 at+30; both affine64B.
 * 833F0 outputs48B rotation, 83738 consumes/writes three rows, and packet
 * constructor fills all144B. Global UV32B/vertex64B consumers have open owners.
 * Need independent qualified family/struct ownership evidence to reopen gap.
 */
#include "common.h"
typedef s32 Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { Vector vertex[4]; u32 colors[4]; float uv[4][2]; u64 state[4]; } Packet;
typedef char PacketExtent[sizeof(Packet) == 0x90 ? 1 : -1];
typedef float Matrix[4][4] __attribute__((aligned(16)));
extern void func_00283658(void *, void *);
extern void func_002833F0(void *, void *);
extern int func_L01_0031BC68(float, int, int);
extern void func_L02_002EF968(Packet *, int, int, float (*)[2], Vector *, int);
extern void func_L01_002E1510(Packet *, int, void *, int, void *);
extern float func_00283198(float);
extern u32 func_00283D38(u32, u32, float);
extern void func_00280B90(void *, void *, int);
extern void func_00283738(void *, void *, void *);
extern Vector D_L02_002A85C0[];
extern float D_L02_001B0798_gp[][2] SDATA(D_L02_001B0798);
extern int D_L02_001B0808_gp SDATA(D_L02_001B0808);
extern int D_L02_001B080C __attribute__((sda));
extern int D_L02_001B07B8_gp SDATA(D_L02_001B07B8);
extern int D_L02_001B07BC_gp SDATA(D_L02_001B07BC);
extern float D_L02_001B07C0_gp[][2] SDATA(D_L02_001B07C0);
extern int D_L02_001B07E0_gp SDATA(D_L02_001B07E0);
extern float D_L02_001B07E8_gp[][2] SDATA(D_L02_001B07E8);
extern float D_L02_001B0810_gp SDATA(D_L02_001B0810);
extern float D_L02_001B0814_gp SDATA(D_L02_001B0814);
extern Vector D_L02_001B0820_gp[] SDATA(D_L02_001B0820);
extern Vector D_L02_001B0860_gp[] SDATA(D_L02_001B0860);

/* Two packets are consumed by the measured count2 helper. Retail reserves an
 * additional unused144-byte region; its true owner is not yet established.
 * Use the proved two-packet extent rather than padding the frame to match.
 * 283658 copies three rows and writes VF0 to row3, so both affine buffers64B. */
void func_L02_003E2150(u8 *object)
{
    Packet packets[2];
    float rotation[12] __attribute__((aligned(16)));
    Matrix original;
    Vector angles;
    Matrix transform;
    u8 *state = *(u8 **)(object + 0x68);
    int color, i, repeat;
    float height;
    func_00283658(original, object + 0xC0);
    qcopy(original[3], object + 0x10);
    original[3][3] = 1.0f;
    angles.q = 0;
    angles.f[2] = 0.19634954631328583f;
    func_002833F0(rotation, &angles);
    color = func_L01_0031BC68(*(float *)(state + 0x18), D_L02_001B0808_gp, D_L02_001B080C);
    func_L02_002EF968(packets, 5, color, D_L02_001B0798_gp, D_L02_002A85C0, 1);
    func_L02_002EF968(packets + 1, 5, color, D_L02_001B0798_gp, D_L02_002A85C0 + 4, 1);
    func_L01_002E1510(packets, 2, rotation, 32, original);
    func_00283658(transform, object + 0xC0);
    qcopy(transform[3], object + 0x10);
    transform[3][3] = 1.0f;
    height = func_00283198(*(float *)(state + 0x1C));
    height = D_L02_001B0814_gp + D_L02_001B0810_gp * height;
    transform[3][2] += height;
    angles.f[2] = 6.2831854820251465f / (float)D_L02_001B07B8_gp;
    func_002833F0(rotation, &angles);
    color = func_L01_0031BC68(*(float *)(state + 0x18), *(int *)(state + 0x28), *(int *)(state + 0x2C));
    color = func_00283D38(color & 0xFFFFFF, color, *(float *)(state + 0x20));
    func_L02_002EF968(packets, D_L02_001B07BC_gp, color, D_L02_001B07C0_gp, D_L02_001B0820_gp, 1);
    func_L01_002E1510(packets, 1, rotation, D_L02_001B07B8_gp, transform);
    angles.f[2] = 2.094395160675049f;
    func_002833F0(rotation, &angles);
    func_L02_002EF968(packets, D_L02_001B07E0_gp, color, D_L02_001B07E8_gp, D_L02_001B0860_gp, 1);
    func_L02_002EF968(packets + 1, D_L02_001B07E0_gp, color, D_L02_001B07E8_gp, D_L02_001B0860_gp, 1);
    for (i = 0; i < 4; i++)
        packets[1].vertex[i].f[2] += 0.1f;
    repeat = 2;
    do {
        func_00280B90(packets, transform, 1);
        func_00280B90(packets + 1, transform, 1);
        func_00283738(transform, transform, rotation);
    } while (--repeat >= 0);
}
