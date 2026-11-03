/* func_L08_0042A980 needs -G64: the 64-byte corner template is addressed through $gp. */
#include "common.h"

extern f32 D_L08_00260410[][16];
extern f32 D_L08_001B9B00[];
extern f32 D_0018A0E0[];
/* sda on the incomplete array keeps its address one unsplit `la` (lui+addiu at the use). */
extern f32 D_L08_001B3A70[][4] __attribute__((sda));
extern f32 D_L08_001B1CE0[4][4] __attribute__((sda));

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282D30(void *, void *, f32);
extern void func_002830C0(void *, void *, void *);
extern s64 func_0027C878(s32);
extern void func_00280B90(void *, s32, s32);
extern f32 func_002A7878(f32, f32);
extern f32 func_002A78D8(f32, f32);
extern s32 func_L02_002F1658(void);

void func_L08_0042A980(s32 unused, s32 index)
{
    struct {
        f32 vertices[4][4];
        s32 colors[4];
        f32 uv[8];
        s64 primitive, texture, blend, tag;
    } packet;
    f32 basis[3][4], position[4], jitter[4];
    f32 size;

    qcopy(position, D_L08_00260410[index]);
    position[3] = 1.0f;
    func_00282CF0(basis[0], D_L08_001B9B00, position);
    func_00282F20(basis[0], basis[0], 1.0f);
    func_00282DD8(basis[1], basis[0], D_0018A0E0);
    func_00282F20(basis[1], basis[1], -1.0f);
    func_00282DD8(basis[2], basis[1], basis[0]);

    packet.texture = func_0027C878(11);
    packet.tag = 0xFF00000044LL;
    packet.blend = 0xFF9000000260LL;
    packet.primitive = 5;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = -1;
    packet.uv[0] = 0;
    packet.uv[1] = 0;
    packet.uv[2] = 0;
    packet.uv[3] = 1;
    packet.uv[4] = 1;
    packet.uv[5] = 0;
    packet.uv[6] = 1;
    packet.uv[7] = 1;

    size = func_002A7878(0.3f, 0.325f);
    if (!func_L02_002F1658()) size = 0.3125f;
    jitter[0] = func_002A78D8(0, 0.05f);
    jitter[1] = func_002A78D8(0, 0.05f);
    jitter[2] = func_002A78D8(0, 0.05f);
    if (!func_L02_002F1658()) jitter[2] = jitter[1] = jitter[0] = 0.025f;

    {
        s32 corner;
        f32 (*p)[4];
        f32 (*out)[4];
        for (corner = 0; corner < 4; corner++) {
            out = &packet.vertices[corner];
            p = &D_L08_001B1CE0[corner];
            func_00282D30(out, p, size);
            func_002830C0(out, out, basis[0]);
            func_00282CC0(out, out, jitter);
        }
    }
    func_00280B90(packet.vertices, 0, 0);

    packet.tag = 0xFF00000048LL;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = 0x60FF10FF;
    {
        s32 corner;
        f32 (*p)[4];
        f32 (*out)[4];
        for (corner = 0; corner < 4; corner++) {
            out = &packet.vertices[corner];
            p = &D_L08_001B1CE0[corner];
            func_00282D30(out, p, size * 3.0f);
            func_002830C0(out, out, basis[0]);
        }
    }
    func_00280B90(packet.vertices, 0, 0);

    qcopy(position, D_L08_001B3A70[index]);
    func_00282CF0(basis[0], D_L08_001B9B00, position);
    func_00282F20(basis[0], basis[0], 1.0f);
    func_00282DD8(basis[1], basis[0], D_0018A0E0);
    func_00282F20(basis[1], basis[1], -1.0f);
    func_00282DD8(basis[2], basis[1], basis[0]);

    size = func_002A7878(0.2f, 0.225f);
    if (!func_L02_002F1658()) size = 0.2225f;
    packet.tag = 0xFF00000044LL;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = -1;
    {
        s32 corner;
        f32 (*p)[4];
        f32 (*out)[4];
        for (corner = 0; corner < 4; corner++) {
            out = &packet.vertices[corner];
            p = &D_L08_001B1CE0[corner];
            func_00282D30(out, p, size);
            func_002830C0(out, out, basis[0]);
            func_00282CC0(out, out, jitter);
        }
    }
    func_00280B90(packet.vertices, 0, 0);

    packet.tag = 0xFF00000048LL;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = 0x60FF10FF;
    {
        s32 corner;
        f32 (*p)[4];
        f32 (*out)[4];
        for (corner = 0; corner < 4; corner++) {
            out = &packet.vertices[corner];
            p = &D_L08_001B1CE0[corner];
            func_00282D30(out, p, size * 3.0f);
            func_002830C0(out, out, basis[0]);
        }
    }
    func_00280B90(packet.vertices, 0, 0);
}
