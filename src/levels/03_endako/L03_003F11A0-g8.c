#include "common.h"

/* The level's copies of three boot routines: the texture word of a texture id, a vector
 * scaled into the packet, and the packet's submission. */
extern u64 GetEffectTextureDescriptor(s32 texture);
extern void FastVecScale(void *dst, void *src, f32 scale);
extern void draw_world_quad(void *packet, s32 a, s32 b);

/* The quad set's draw settings, all reached through $gp: the four selectors and the fixed
 * value of the packet's blend word, the texture id, the colour and the vertex scale. */
extern s32 D_L03_001B0F24 __attribute__((sda));
extern s32 D_L03_001B0F28 __attribute__((sda));
extern s32 D_L03_001B0F2C __attribute__((sda));
extern s32 D_L03_001B0F30 __attribute__((sda));
extern s32 D_L03_001B0F34 __attribute__((sda));
extern s32 D_L03_001B0F38 __attribute__((sda));
extern s32 D_L03_001B0F3C __attribute__((sda));
extern f32 D_L03_001B0F40 __attribute__((sda));

/* 36 vertices, 25 quads of four (vertex, uv, colour) index triples, the uv pairs and the
 * colours they name. */
extern f32 D_L03_002A0A30[][4];
extern s16 D_L03_002A0C70[];
extern f32 D_L03_002A0EC8[][2];
extern s32 D_L03_002A11E8[];

/* The quad packet func_00280B90 takes, followed by the entity's matrix. */
typedef struct {
    f32 positions[4][4];
    s32 colors[4];
    f32 uv[4][2];
    u64 zero, texture, tag, mode;
    f32 matrix[4][4];
} DrawPacket;

/* Draws a scrolling textured shape made of quads, such as flowing water or goo. */
/* Flattens the 36 vertices, scrolls the uv offset at state+0x74 and draws the 25 quads
 * through the entity's matrix. */
void DrawScrollingQuadMesh(u8 *entity) {
    DrawPacket packet;
    u8 *state = *(u8 **)(entity + 0x68);
    f32 *ubase, *vbase;
    s32 i, j;
    s32 *cbase;
    u64 mode;
    packet.texture = GetEffectTextureDescriptor(D_L03_001B0F38);
    packet.tag = 0xFF9000000260ULL;
    mode = (u64)D_L03_001B0F24 | ((u64)D_L03_001B0F28 << 2);
    mode |= (u64)D_L03_001B0F2C << 4;
    mode |= (u64)D_L03_001B0F30 << 6;
    mode |= (u64)D_L03_001B0F34 << 32;
    packet.mode = mode;
    packet.zero = 0;
    qcopy(packet.matrix[0], entity + 0xC0);
    qcopy(packet.matrix[1], entity + 0xD0);
    qcopy(packet.matrix[2], entity + 0xE0);
    packet.matrix[3][0] = *(f32 *)(entity + 0x10);
    packet.matrix[3][1] = *(f32 *)(entity + 0x14);
    packet.matrix[3][2] = *(f32 *)(entity + 0x18);
    packet.matrix[3][3] = 1;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = D_L03_001B0F3C;
    *(f32 *)(state + 0x74) -= 0.00045f;
    if (*(f32 *)(state + 0x74) <= -8.0f) *(f32 *)(state + 0x74) += 8.0f;
    ubase = &packet.uv[0][0];
    vbase = ubase + 1;
    for (i = 0; i < 36; i++) D_L03_002A0A30[i][2] = 0;
    i = 0;
    cbase = packet.colors;
    for (; i < 25; i++) {
        s32 *c = cbase;
        f32 *v = vbase;
        f32 *u = ubase;
        f32 *out = packet.positions[0];
        s32 offset = i * 24;
        s16 *indices = (s16 *)((u8 *)D_L03_002A0C70 + offset);
        s16 *uvindices = (s16 *)((u8 *)D_L03_002A0C70 + (offset | 2));
        for (j = 3; j >= 0; j--) {
            s32 uv = *uvindices;
            s32 color = indices[2];
            FastVecScale(out, D_L03_002A0A30[*indices], D_L03_001B0F40);
            *u = D_L03_002A0EC8[uv][0] + *(f32 *)(state + 0x74);
            *v = D_L03_002A0EC8[uv][1];
            *c = D_L03_002A11E8[color];
            indices += 3;
            uvindices += 3;
            out += 4;
            u += 2;
            v += 2;
            c++;
        }
        draw_world_quad(&packet, 0, 0);
    }
}
