/* func_PAL_002FEC30, the PAL copy of func_002FDBD8: the same C. */
#include "common.h"

/* func_PAL_002FEC30 (from 002FC8D0.c): two textured quads at ORIGIN, turned to face
   DIRECTION and spun in opposite senses, drawn with textures 17 and 18.  Its own
   -G8 unit, as for func_002FD828 and func_002FDF40. */

extern int D_0018C0B4 NOT_SDA;
extern int ref_L00_002FDBD8_00;
extern int ref_L00_002FDBD8_01[] __attribute__((sda));
extern int ref_L00_002FDBD8_02[2] __attribute__((sda));
extern float func_00282C10(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283CE0(int);
extern float func_00283C28(float);
extern void func_00283410(float *, float *);
extern void func_00283788(float *, float *, float *);
extern u64 func_0027C878(int);
extern void func_00282D30(float *, float *, float);
extern void func_00280B90(void *, float *, int);
typedef struct {
    float corners[4][4];
    int colors[4];
    float tex[8];
    u64 zero, texture, blend, test;
} DrawPacketDB;

void func_PAL_002FEC30(float *origin, float *direction, float scale, int *colors)
{
    DrawPacketDB packet;
    float transform[16];
    float rotation[16];
    float angles[4];
    float spin[4];
    int n, i, odd;
    if ((unsigned int)(D_0018C0B4 - 23) < 2 || D_0018C0B4 == 27 ||
        D_0018C0B4 == 25 || D_0018C0B4 == 26 || D_0018C0B4 == 111 ||
        D_0018C0B4 == 98 || ref_L00_002FDBD8_00 == 2) return;
    n = 0;
    do {
        odd = n & 1;
        angles[0] = func_00283B98(-func_00283248(func_00282C10(direction[0]*direction[0] + direction[2]*direction[2]), direction[1]), 1.57079637f);
        angles[1] = func_00283248(direction[2], direction[0]);
        angles[2] = 0;
        angles[3] = 0;
        spin[0] = 0;
        {
            /* Two degrees per tick of the counter, mirrored on odd passes. */
            float turn = func_00283C28(func_00283CE0(ref_L00_002FDBD8_01[0] % 150) * 0.041795027f);
            if (odd)
                turn = -turn;
            spin[1] = turn;
        }
        spin[2] = 0;
        spin[3] = 0;
        func_00283410(rotation, spin);
        func_00283410(transform, angles);
        func_00283788(transform, transform, rotation);
        qcopy(transform + 12, origin);
        {
            int off;
            int color;
            int *p;
            /* The colour comes from the caller's table or the default pair; both arms
               keep the byte offset in one variable and add it to the table address. */
            if (!colors) {
                off = n * 4;
                color = *(int *)(off + (int)ref_L00_002FDBD8_02);
                n++;
                for (i = 3; i >= 0; i--)
                    packet.colors[i] = color;
            } else {
                i = 3;
                off = n * 4;
                color = *(int *)(off + (int)colors);
                n++;
                p = packet.colors;
                for (; i >= 0; i--)
                    *p++ = color;
            }
        }
        packet.texture = func_0027C878(odd ? 18 : 17);
        packet.blend = 0xFF9000000260ULL;
        packet.test = 0x8000000044ULL;
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
        func_00280B90(&packet, transform, 1);
    } while (n < 2);
}
