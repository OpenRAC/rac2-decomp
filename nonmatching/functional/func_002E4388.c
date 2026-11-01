/* functional: high. Plain floats in place of VU0 macro code; the visibility test reads the sign bits as retail's 64-bit register test does. */
#include "common.h"

extern float D_001B92C0[8][4];
extern float D_001B20F0[4][4];
extern float fabsf(float);

static int negative_002E4388(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i < 0;
}

/* CullSkyPieceVisibility: one byte per sphere of source (0x20 bytes each, centre and radius, scaled
   by the view's w): 1 when it is inside the clip volume's x and y bounds. */
void func_002E4388(void *source, int count, unsigned char *visible)
{
    float *s = source;
    float m[4][3];
    int i, k;

    for (k = 0; k < 4; k++) {
        for (i = 0; i < 3; i++) {
            float at = D_001B92C0[0][i] * D_001B20F0[k][0];
            at = at + D_001B92C0[1][i] * D_001B20F0[k][1];
            m[k][i] = at + D_001B92C0[2][i] * D_001B20F0[k][2];
        }
    }
    do {
        float scale = D_001B92C0[3][3];
        float x = s[0] * scale, y = s[1] * scale, z = s[2] * scale, r = s[3] * scale;
        float v[3], ax, ay, dx, dy;

        for (i = 0; i < 3; i++) {
            float at = m[0][i] * x;
            at = at + m[1][i] * y;
            at = at + m[2][i] * z;
            v[i] = at + m[3][i];
        }
        ax = fabsf(v[0]);
        ay = fabsf(v[1]);
        dx = D_001B92C0[4][0] * v[2] - (ax - D_001B92C0[6][0] * r);
        dy = D_001B92C0[4][1] * v[2] - (ay - D_001B92C0[6][1] * r);
        *visible++ = !(negative_002E4388(dy) || negative_002E4388(dx));
        s += 8;
    } while (--count != 0);
}
