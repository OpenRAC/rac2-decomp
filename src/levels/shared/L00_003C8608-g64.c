/* The complete 64-byte corner table needs -G64 -Wa,-G64 for GP addressing.
 * Same packet and traversal as DrawTwoPassCameraQuad, with this effect's data.
 */
#include "common.h"
typedef struct {
    float points[4][4];
    int colours[4];
    float params[8];
    u64 regs[4];
} DrawPacket8608;
extern float D_L00_001B00A0[4][4] __attribute__((sda));
extern float D_L00_001B00E0 __attribute__((sda));
extern float D_L00_001B00E4 __attribute__((sda));
extern float D_L00_001B00E8 __attribute__((sda));
extern int D_L00_001B00EC __attribute__((sda));
extern char D_L00_002403C0[];
extern char D_L00_001B8DC0[];
extern char D_0018A0E0[];
extern u64 func_0027C878(int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);
typedef unsigned int Quad83E0 __attribute__((mode(TI)));
typedef union { Quad83E0 q; float f[4]; } Vec83E0;
typedef struct {
    Vec83E0 points[4];
    unsigned int colours[4];
    float params[8];
    u64 regs[4];
} DrawPacket83E0;
extern int func_00283CF0(float);
extern unsigned int D_L00_001B003C __attribute__((sda));
extern int D_L00_001B2AC0[] __attribute__((sda));
extern float D_L00_001B2A90[] __attribute__((sda));
extern float D_L00_001B2AB0[] __attribute__((sda));
extern Vec83E0 D_L00_001B2A20[] __attribute__((sda));
extern Vec83E0 D_L00_001B2A50[] __attribute__((sda));
/* Two passes of a camera-facing quad placed from object + 0xD0 (scaled by D_L00_001B00E8) and
   D_L00_002403C0: first with colour D_L00_001B00EC and corner scale D_L00_001B00E0, then
   white with corner scale D_L00_001B00E4. */
void func_L00_003C8608(char *object)
{
    DrawPacket8608 packet;
    float basis[4][4];
    float vertex[4], offset[4];
    int i;
    packet.regs[1] = GetEffectTextureDescriptor(11);
    packet.regs[3] = 0x8000000048ULL;
    packet.regs[2] = 0xFF9000000260ULL;
    packet.regs[0] = 0;
    packet.params[0] = 0; packet.params[1] = 0; packet.params[2] = 0; packet.params[3] = 1;
    packet.params[4] = 1; packet.params[5] = 0; packet.params[6] = 1; packet.params[7] = 1;
    packet.colours[0] = packet.colours[1] =
        packet.colours[2] = packet.colours[3] = D_L00_001B00EC;
    vec_scale_to_length(offset, object + 0xD0, D_L00_001B00E8);
    FastVecAdd(basis[3], D_L00_002403C0, offset);
    FastVecSub(offset, D_L00_001B8DC0, basis[3]);
    vec_scale_to_length(basis[0], offset, 1.0f);
    FastVecCross(basis[1], basis[0], D_0018A0E0);
    vec_scale_to_length(basis[1], basis[1], -1.0f);
    FastVecCross(basis[2], basis[1], basis[0]);
    for (i = 3; i >= 0; i--) {
        FastVecScale(vertex, D_L00_001B00A0[3 - i], D_L00_001B00E0);
        transform_vector(packet.points[3 - i], vertex, basis);
    }
    draw_world_quad(&packet, 0, 0);
    packet.colours[3] = -1; packet.colours[2] = -1; packet.colours[1] = -1; packet.colours[0] = -1;
    for (i = 3; i >= 0; i--) {
        FastVecScale(vertex, D_L00_001B00A0[3 - i], D_L00_001B00E4);
        transform_vector(packet.points[3 - i], vertex, basis);
    }
    draw_world_quad(&packet, 0, 0);
}

/* Twin of func_L00_004079C8 with this level code's data: a quad for each of the three active
   sparks of func_L00_003C6B98's table, basis from the spark's direction D_L00_001B2A50[i] and
   the up vector D_0018A0E0, placed at D_L00_001B2A20[i], corners D_L00_001B00A0 scaled by
   D_L00_001B2AB0[i], alpha from D_L00_001B2A90[i] and colour D_L00_001B003C. The spark tables
   are incomplete sda arrays, which gives retail's unsplit lui/addiu addresses. */
void func_L00_003C83E0(void)
{
    DrawPacket83E0 packet;
    Vec83E0 basis[4], vertex;
    Vec83E0 *corner;
    unsigned int color, c;
    int i, j;

    packet.regs[1] = GetEffectTextureDescriptor(8);
    packet.regs[3] = 0x8000000048ULL;
    packet.regs[2] = 0xFF9000000260ULL;
    color = D_L00_001B003C & 0xFFFFFF;
    packet.regs[0] = 0;
    packet.params[0] = 0; packet.params[1] = 0; packet.params[2] = 0; packet.params[3] = 1;
    packet.params[4] = 1; packet.params[5] = 0; packet.params[6] = 1; packet.params[7] = 1;
    for (i = 0; i < 3; i++) {
        if (D_L00_001B2AC0[i]) {
            c = color | (FloatToInt(D_L00_001B2A90[i]) << 24);
            packet.colours[0] = packet.colours[1] = packet.colours[2] = packet.colours[3] = c;
            qcopy(&basis[3], &D_L00_001B2A20[i]);
            qcopy(&basis[0], &D_L00_001B2A50[i]);
            FastVecScale(&basis[2], D_0018A0E0, -1.0f);
            FastVecCross(&basis[1], &basis[0], &basis[2]);
            vec_scale_to_length(&basis[1], &basis[1], 1.0f);
            FastVecCross(&basis[2], &basis[1], &basis[0]);
            corner = (Vec83E0 *)D_L00_001B00A0;
            for (j = 3; j >= 0; corner++, j--) {
                FastVecScale(&vertex, corner, D_L00_001B2AB0[i]);
                transform_vector(&packet.points[3 - j], &vertex, basis);
            }
            draw_world_quad(&packet, 0, 0);
        }
    }
}
