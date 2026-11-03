/* functional: high. From the near-miss draft (nonmatching/game/func_002FDBD8.c, register choice only), with its ref_ names replaced by the addresses retail forms ($gp-0x6440 = D_001A8BB0, lui 0x1B + 0x1688 = D_001B1688, $gp-0x1800 = D_001AD7F0) and qcopy written as a four-word copy (retail's lq/sq of the origin). Same calls, arguments and stores in retail's order. func_00280B90 is declared as the port's host routine defines it (game addresses as unsigned int). */

#include "common.h"

typedef struct {
    float corners[4][4];
    int colors[4];
    float tex[8];
    unsigned long zero, texture, blend, test;
} DrawPacketDB;

extern int D_0018C0B4 NOT_SDA;
extern int D_001A8BB0 __attribute__((sda));
extern int D_001B1688 NOT_SDA;
extern int D_001AD7F0[2] __attribute__((sda));
extern float func_00282C10(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283CE0(int);
extern float func_00283C28(float);
extern void func_00283410(float *, float *);
extern void func_00283788(float *, float *, float *);
extern unsigned long func_0027C878(int);
extern void func_00282D30(float *, float *, float);
extern void func_00280B90(unsigned int, int, int); /* as the port's host routine (host/render.c) defines it: a game address */

/* Draws two crossed textured quads (textures 17 and 18, the second spun the other way) at origin, oriented along
   direction and scaled by scale, spinning with the frame counter D_001B1688 (2 degrees a frame). colors gives the
   two quads' colours, or the defaults D_001AD7F0 when null. Skipped in some levels (D_0018C0B4 23, 24, 25, 26, 27,
   98, 111) and when D_001A8BB0 is 2. */
void func_002FDBD8(float *origin, float *direction, float scale, int *colors)
{
    DrawPacketDB packet;
    float transform[16];
    float rotation[16];
    float angles[4];
    float spin[4];
    int n, i, odd;

    if ((unsigned int)(D_0018C0B4 - 23) < 2 || D_0018C0B4 == 27 || D_0018C0B4 == 25 || D_0018C0B4 == 26
        || D_0018C0B4 == 111 || D_0018C0B4 == 98 || D_001A8BB0 == 2) {
        return;
    }

    n = 0;
    do {
        float turn;
        int color;

        odd = n & 1;
        angles[0] = func_00283B98(
            -func_00283248(func_00282C10(direction[0] * direction[0] + direction[2] * direction[2]), direction[1]),
            1.57079637f);
        angles[1] = func_00283248(direction[2], direction[0]);
        angles[2] = 0;
        angles[3] = 0;
        spin[0] = 0;
        turn = func_00283C28(func_00283CE0(D_001B1688 % 180) * 0.0349065885f);
        if (odd) {
            turn = -turn;
        }
        spin[1] = turn;
        spin[2] = 0;
        spin[3] = 0;
        func_00283410(rotation, spin);
        func_00283410(transform, angles);
        func_00283788(transform, transform, rotation);
        transform[12] = origin[0];
        transform[13] = origin[1];
        transform[14] = origin[2];
        transform[15] = origin[3];

        if (colors == 0) {
            color = D_001AD7F0[n];
            n++;
            for (i = 3; i >= 0; i--) {
                packet.colors[i] = color;
            }
        } else {
            color = colors[n];
            n++;
            for (i = 0; i < 4; i++) {
                packet.colors[i] = color;
            }
        }

        packet.texture = func_0027C878(odd ? 18 : 17);
        packet.test = 0x8000000044UL;
        packet.blend = 0xFF9000000260UL;
        packet.zero = 0;
        packet.corners[0][0] = -1.0f; packet.corners[0][1] = 0; packet.corners[0][2] = 1.0f; packet.corners[0][3] = 1.0f;
        packet.corners[1][0] = 1.0f; packet.corners[1][1] = 0; packet.corners[1][2] = 1.0f; packet.corners[1][3] = 1.0f;
        packet.corners[2][0] = -1.0f; packet.corners[2][1] = 0; packet.corners[2][2] = -1.0f; packet.corners[2][3] = 1.0f;
        packet.corners[3][0] = 1.0f; packet.corners[3][1] = 0; packet.corners[3][2] = -1.0f; packet.corners[3][3] = 1.0f;
        func_00282D30(packet.corners[0], packet.corners[0], scale);
        func_00282D30(packet.corners[1], packet.corners[1], scale);
        func_00282D30(packet.corners[2], packet.corners[2], scale);
        func_00282D30(packet.corners[3], packet.corners[3], scale);
        packet.tex[0] = 0; packet.tex[1] = 1; packet.tex[2] = 1; packet.tex[3] = 1;
        packet.tex[4] = 0; packet.tex[5] = 0; packet.tex[6] = 1; packet.tex[7] = 0;
        func_00280B90((unsigned int)&packet, (int)transform, 1);
    } while (n < 2);
}
