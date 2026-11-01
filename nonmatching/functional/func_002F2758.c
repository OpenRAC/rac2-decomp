/* functional: low. A piece of a larger routine that retail enters by a jump or call with its values in registers (v1 = matrix, s5 = packed vertices, a1 = quad count, sp = output cursor in the scratchpad), so the signature is a guess and the cursor is returned instead of left in sp; the code after its jr ra (retail 0x2F28EC on) is other blocks of the larger routine, not reached from here, and is not carried; the 128-bit rotate (qfsrv) depends on the shift register set elsewhere and is taken to be 32 bits, so the four words of each quad are used in order. */
#include "common.h"

extern float D_001AD0F0[4];         /* x = scale, y = offset */

/* Projects packed vertices to two floats each. Each 16-byte quad holds four 32-bit packed
   vertices: x = sign-extended low 11 bits << 2, y = bits 21..9 sign-extended (as the shifts leave
   them), z = (word >> 22 arithmetic) * 8; each divided by 4096 gives the vector, which three
   matrix rows (the three 16-byte rows at matrix + 96, x and y of each scaled by the row's w) turn
   into x' and y', then (v * scale) + offset. Eight bytes (x', y') per vertex go to the output,
   32 per quad. Returns the cursor after the last one. */
float *func_002F2758(float *matrix, int *verts, int count, float *out)
{
    float *m = matrix + 24;
    float r2x = m[0] * m[3], r2y = m[1] * m[3];
    float r3x = m[4] * m[7], r3y = m[5] * m[7];
    float r4x = m[8] * m[11], r4y = m[9] * m[11];
    float scale = D_001AD0F0[0], offset = D_001AD0F0[1];

    do {
        int k;

        count--;
        for (k = 0; k < 4; k++) {
            int w = verts[k];
            int xi = (int)((unsigned int)w << 21) >> 19;
            int yi = (int)((unsigned int)w << 10) >> 19;
            int zi = (w >> 22) * 8;
            float fx = (float)xi / 4096.0f;
            float fy = (float)yi / 4096.0f;
            float fz = (float)zi / 4096.0f;
            float ax, ay;

            ax = r2x * fx;
            ay = r2y * fx;
            ax = ax + r3x * fy;
            ay = ay + r3y * fy;
            ax = ax + r4x * fz;
            ay = ay + r4y * fz;
            out[0] = ax * scale + offset;
            out[1] = ay * scale + offset;
            out += 2;
        }
        verts += 4;
    } while (count != 0);
    return out;
}
