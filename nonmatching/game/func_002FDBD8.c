/* Closer C3, 1 November 2026: priorities in the off variant: n 3*15/268, direction 3*11/157, odd 2*6/70. One more depth-1 read of n
 * (weight 2) gives 17 refs and floor_log2 4, enough over both; retail shows no such read.
 */
/* Closer C, 1 November 2026: 9 rows (arm 2 sets i first). Retail's `sll v1,s0,2` in bnez's plain slot is
 * one value computed before the branch, used as addu v0,v1,fp: `int off = n * 4; ... *(int *)((char *)colors + off)`
 * gives every row of that block, but n then has 15 weighted refs over 268 insns and loses to direction
 * (11/157) and odd (6/70), so the three saved registers rotate (23 rows). Next: one more loop-depth read of n.
 */
/* GPT-6.1 Sol (low effort), v0552. 868/868 bytes, 0/28 places; first mismatch +0x1bc. Color fill branches differ in shift sharing, branch-likely selection and registers. -O2 -G8 -ffunction-sections -g; physical ABI uses float scale before third integer argument.
   Declarations are included below. Reopen with a pointer-lifetime hypothesis. */
#include "common.h"
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
void func_002FDBD8(float *origin, float *direction, float scale, int *colors)
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
        { float turn = func_00283C28(func_00283CE0(ref_L00_002FDBD8_01[0] % 180) * 0.0349065885f);
        if (odd) turn = -turn;
        spin[1] = turn; }
        spin[2] = 0;
        spin[3] = 0;
        func_00283410(rotation, spin);
        func_00283410(transform, angles);
        func_00283788(transform, transform, rotation);
        qcopy(transform + 12, origin);
        if (!colors) { int color; int *p;
 color = ref_L00_002FDBD8_02[n]; n++; for (i = 3; i >= 0; i--) packet.colors[i] = color;
        } else { int color; int *p;
 i = 3; color = colors[n]; n++; p = packet.colors; for (; i >= 0; i--) *p++ = color;
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
