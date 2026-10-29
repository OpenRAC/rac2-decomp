/* Bounded near miss, 2026-10-28: 688/688 bytes after six forms.
 * Named sequential64-bit flag assembly reproduces the initial packet. Real
 * row-offset/second-halfword cursors restore mult/ori rather than MADD and
 * collapsed point/UV cursors; ordinary SDA color-table addressing avoids
 * hoisting its base. Value snapshots preserve retail UV/color read order.
 * Remaining first+0xe0 is independent matrix/color stores; inner output GPR
 * lifetimes also differ. Narrow -fno-regmove ties and is not retained.
 * Reopen with a real matrix/output-cursor lifetime witness.
 * All table bounds are measured:600-byte index table gives point0..35,
 * UV0..99,color0..99. Source vectors576 bytes, UV800 bytes,color400 bytes.
 * Only each vectorZ is reset; its other words remain initialized retail data.
 * Packet144 and historical matrix64 are complete; qcopy inputs are full
 * existing object matrix rows. Direct state read/write ends+0x78.
 */
#include "common.h"

struct BeamSettings { int f0, f1, f2, f3, f4, texture; unsigned int color; float scale; };
extern struct BeamSettings D_L03_001B0F24[];
extern struct BeamSettings D_L03_001B0F24_gp[] SDATA(D_L03_001B0F24);
#define SETUP (D_L03_001B0F24_gp[0])
extern float D_L03_002A0A30[][4];
extern short D_L03_002A0C70[][12];
struct BeamUV { float u, v; };
extern struct BeamUV D_L03_002A0EC8[] __attribute__((sda));
extern unsigned int D_L03_002A11E8[] __attribute__((sda));
struct BeamPacket { float vertex[4][4]; unsigned int color[4]; float uv[8]; u64 state[4]; };
struct BeamFrame {
    struct BeamPacket packet;
    float matrix[4][4];
    char *data;
    float *u, *v;
    int next;
    unsigned int *color;
};
extern unsigned long func_0027C878(int);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

/* Complete renderer packet144 bytes and historical local matrix64 bytes.
 * The template update touches exactly the Z word of each of36 vectors;
 * the renderer consumes25 indexed four-vertex packets with initialized UVs. */
void func_L03_003F11A0(unsigned char *object)
{
    struct BeamFrame f;
    unsigned long texture, flags;
    int i, j;
    f.data = *(char **)(object + 0x68);
    texture = func_0027C878(SETUP.texture);
    f.packet.state[1] = texture;
    f.packet.state[2] = 0xFF9000000260UL;
    flags = (u64)SETUP.f0;
    flags |= (u64)SETUP.f1 << 2;
    flags |= (u64)SETUP.f2 << 4;
    flags |= (u64)SETUP.f3 << 6;
    flags |= (u64)SETUP.f4 << 32;
    f.packet.state[3] = flags;
    f.packet.state[0] = 0;
    qcopy(f.matrix[0], object + 0xc0);
    qcopy(f.matrix[1], object + 0xd0);
    qcopy(f.matrix[2], object + 0xe0);
    f.matrix[3][0] = *(float *)(object + 0x10);
    f.matrix[3][1] = *(float *)(object + 0x14);
    f.matrix[3][2] = *(float *)(object + 0x18);
    f.matrix[3][3] = 1.0f;
    f.packet.color[3] = SETUP.color;
    f.packet.color[2] = SETUP.color;
    f.packet.color[1] = SETUP.color;
    f.packet.color[0] = SETUP.color;
    {
        char *data = f.data;
        float offset = *(float *)(data + 0x74) - 0.00045f;
        *(float *)(data + 0x74) = offset;
        if (offset <= -8.0f) *(float *)(data + 0x74) = offset + 8.0f;
    }
    f.v = f.packet.uv + 1;
    f.color = f.packet.color;
    f.u = f.packet.uv;
    for (i = 35; i >= 0; --i) D_L03_002A0A30[i][2] = 0.0f;
    i = 0;
    do {
        int offset = i * 24;
        short *point_cursor = (short *)((char *)D_L03_002A0C70 + offset);
        short *uv_cursor = (short *)((char *)D_L03_002A0C70 + (offset | 2));
        float *vertex;
        unsigned int *color = f.color;
        float *v = f.v, *u = f.u;
        f.next = i+1;
        vertex = f.packet.vertex[0];
        for (j = 3; j >= 0; --j) {
            int point = point_cursor[0];
            int uv = uv_cursor[0];
            int tint = point_cursor[2];
            func_00282D30(vertex, D_L03_002A0A30[point], SETUP.scale);
            {
                float offset = *(float *)(f.data + 0x74);
                float next_u = D_L03_002A0EC8[uv].u + offset;
                float next_v = D_L03_002A0EC8[uv].v;
                unsigned int next_color = D_L03_002A11E8[tint];
                *u = next_u;
                *v = next_v;
                *color = next_color;
            }
            vertex += 4;
            point_cursor += 3;
            uv_cursor += 3;
            u += 2;
            v += 2;
            ++color;
        }
        func_00280B90(&f.packet, 0, 0);
        i = f.next;
    } while (i < 25);
}
