/* func_PAL_L00_003CB888, the PAL copy of func_L00_003C79F8: the same C, where each scroll step is scaled by 1.2f for 50 Hz.
 * Ring renderer, following draw_beam_ring_and_rail_effects in
 * OpenRAC/rac1-decomp's walloper_and_beam_effects.c (GPL-3.0).
 * The two texture scrolls cover the same visible ring segments.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } SurfaceVector;
typedef struct { SurfaceVector vertex[4]; int color[4]; float uv[8]; u64 primitive, texture, mode, flags; } SurfacePacket;
extern float D_L00_001B007C __attribute__((sda)), D_L00_001B0080 __attribute__((sda));
extern int D_L00_001B005C __attribute__((sda)), D_L00_001B0060 __attribute__((sda));
extern float D_L00_001B0064 __attribute__((sda)), D_L00_001B0068 __attribute__((sda)), D_L00_001B006C __attribute__((sda));
extern int D_L00_001B0074 __attribute__((sda)), D_L00_001B0078 __attribute__((sda)), D_L00_001B0084 __attribute__((sda)), D_L00_001B008C __attribute__((sda));
extern float D_L00_001AFFEC __attribute__((sda)), D_L00_001AFFF0 __attribute__((sda)), D_L00_001AFFF4 __attribute__((sda)), D_L00_001AFFF8 __attribute__((sda));
extern float D_L00_001AFFFC __attribute__((sda)), D_L00_001B0000 __attribute__((sda)), D_L00_001B0004 __attribute__((sda));
extern SurfaceVector D_L00_00240480[], D_L00_00240540[], D_L00_00240600[][20], D_L00_002404C0[][20];
extern char D_L00_001B8DC0[];
extern void func_L00_003C7DF0(void *, int, int, float, float, float, int, int);
extern void func_L00_003C83E0(void *), func_L00_003C8608(void *);
extern u64 func_0027C878(int);
extern void func_00282CF0(void *, void *, void *), func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00280B90(void *, void *, int);
void func_PAL_L00_003CB888(void *object)
{
    SurfacePacket packet;
    SurfaceVector edge, side, normal, eye;
    int row, i;
    float u, v, w;
    D_L00_001B007C -= D_L00_001B0080 * 1.2f;
    if (D_L00_001B007C <= -8.0f) D_L00_001B007C += 8.0f;
    func_L00_003C7DF0(D_L00_00240480, D_L00_001B005C, D_L00_001B0060, D_L00_001B0064, D_L00_001B0068, D_L00_001B006C, 12, D_L00_001B0074);
    func_L00_003C7DF0(D_L00_00240540, D_L00_001B005C, D_L00_001B0060, D_L00_001B0064, D_L00_001B0068, D_L00_001B006C, 12, D_L00_001B0078);
    func_L00_003C83E0(object);
    func_L00_003C8608(object);
    {
        int color = D_L00_001B0084;
        packet.texture = func_0027C878(D_L00_001B008C);
        u = D_L00_001AFFF4;
        packet.mode = 0xFF9000000260ULL;
        packet.flags = 0x8000000048ULL;
        packet.primitive = 0;
        packet.color[3] = color; packet.color[2] = color; packet.color[1] = color; packet.color[0] = color;
    }
    D_L00_001AFFF4 -= D_L00_001AFFF8 * 1.2f;
    if (D_L00_001AFFF4 <= -8.0f) D_L00_001AFFF4 += 8.0f;
    D_L00_001AFFFC -= D_L00_001B0004 * 1.2f;
    if (D_L00_001AFFFC <= -7.0f) D_L00_001AFFFC += 7.0f;
    D_L00_001B0000 += D_L00_001B0004 * 1.2f;
    if (D_L00_001B0000 >= 5.0f) D_L00_001B0000 -= 5.0f;
    {
        SurfaceVector *point2;
        for (row = 2; row < 12;) {
            int nextRow = row + 1;
            v = D_L00_001AFFFC; w = D_L00_001B0000;
            for (i = 0; i < 20; i++) {
                qcopy_nc(&packet.vertex[0], &D_L00_00240600[row][i]);
                qcopy_nc(&packet.vertex[1], &D_L00_00240600[row][(i + 1) % 20]);
                qcopy_nc(point2 = &packet.vertex[2], &D_L00_002404C0[row][i]);
                qcopy_nc(&packet.vertex[3], &D_L00_002404C0[row][(i + 1) % 20]);
                func_00282CF0(&edge, &packet.vertex[0], &packet.vertex[1]);
                func_00282CF0(&side, point2, &packet.vertex[1]);
                func_00282DD8(&normal, &side, &edge);
                func_00282CF0(&eye, &packet.vertex[1], D_L00_001B8DC0);
                if (func_00282DB0(&normal, &eye) >= 0) {
                    v += D_L00_001AFFF0; w += D_L00_001AFFF0;
                } else {
                    if (row == 11) { packet.color[1] = D_L00_001B0084 & 0xFFFFFF; packet.color[0] = D_L00_001B0084 & 0xFFFFFF; }
                    packet.uv[5] = v;
                    packet.uv[1] = v;
                    packet.uv[3] = v + D_L00_001AFFF0;
                    packet.uv[4] = u - D_L00_001AFFEC;
                    packet.uv[0] = u;
                    packet.uv[2] = u;
                    packet.uv[7] = v + D_L00_001AFFF0;
                    packet.uv[6] = u - D_L00_001AFFEC;
                    v = v + D_L00_001AFFF0;
                    func_00280B90(&packet, 0, 0);
                    packet.uv[0] = u;
                    packet.uv[1] = w;
                    packet.uv[2] = u;
                    packet.uv[3] = w + D_L00_001AFFF0;
                    packet.uv[5] = w;
                    packet.uv[4] = u - D_L00_001AFFEC;
                    packet.uv[6] = u - D_L00_001AFFEC;
                    packet.uv[7] = w + D_L00_001AFFF0;
                    w = w + D_L00_001AFFF0;
                    func_00280B90(&packet, 0, 0);
                }
            }
            row = nextRow;
            u += D_L00_001AFFEC;
        }
    }
}
