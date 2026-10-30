/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G8 -ffunction-sections.
 * 1100/1120 bytes; 0x30 frame instead of 0x20, initialization constant scheduling and route-state branches differ.
 * Reopen with an actual enemy-variable layout and constant-local lifetime witness.
 * ABI/bounds: No local packet/vector undersizing. Current 002B60B0 returns void pointer, preserved. Runtime fields retain signed route indices, byte modes, halfword timers and float bit values.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"

extern void *D_L01_001FE180[];
extern unsigned char D_L01_001B0900[] __attribute__((sda));
extern int func_00283CF0(float);
extern void func_L01_003377C8(void *);
extern float func_002A78D8(float, float);
extern void *func_002B60B0(void *, float, float, float, float);
extern void func_002A7750(void *, int, int);
extern int func_002A7820(int, int);
extern void func_002A7470(void *, int, int, int);

#define I(o) (*(int *)(p + (o)))
#define F(o) (*(float *)(p + (o)))
#define H(o) (*(short *)(p + (o)))

/* Initializes the complete enemy state, route handles and movement controls. */
void func_L01_003DCF40(unsigned char *m)
{
    unsigned char *p = *(unsigned char **)(m + 0x68);
    I(0x18) = (int)(p + 0x1c0);
    p[0x48] = func_00283CF0(10.0f);
    p[0x4a] = func_00283CF0(9.6f);
    I(0x158) = 5; p[0x127] = 11;
    F(0x12c) = 0.20000001788139343f;
    F(0x130) = 0.10000000894069672f;
    F(0x134) = 0.0061111114919185638f;
    F(0x138) = 0.010277777910232544f;
    F(0x13c) = 0.011111111380159855f;
    F(0x14c) = 0.4f;
    p[0x182] = 6; p[0x183] = 10; p[0x29] = 1;
    F(0x30) = 0.5f;
    p[0x120] = 0; p[0x121] = 10; p[0x122] = 10; p[0x126] = 10;
    F(0x140) = F(0x144) = 0.5f;
    p[0x17c] = 6; p[0x17d] = 10; p[0x17e] = 6; p[0x17f] = 10;
    H(0x148) = 0; p[0x28] = 0;
    H(0x3d8) = 0;
    qcopy(p + 0x3a0, m + 0x10);
    if (I(0x3c0) != -1) func_L01_003377C8(D_L01_001FE180[I(0x3c0)]);
    if (I(0x3bc) != -1) func_L01_003377C8(D_L01_001FE180[I(0x3bc)]);
    qcopy(p + 0x2b0, m + 0x10);
    F(0x2d0) = 5.0f; F(0x1c0) = 0.3f; F(0x1cc) = 0.2f;
    F(0x1d0) = 0.8726646900177002f;
    F(0x1f0) = 0.52359884977340698f;
    F(0x1ec) = 0.0055555556900799274f;
    I(0x1fc) = I(0x3bc);
    F(0x2c0) = 0.3f; F(0x2cc) = 5.0f; F(0x1c8) = 0.2f; F(0x1c4) = 0.1f;
    F(0x29c) = func_002A78D8(25.0f, 35.0f) * 0.01745329424738884f;
    H(0x2a2) = 120; H(0x2a4) = 180;
    func_002B60B0(m, 0.002222222276031971f, 0.066666670143604279f,
        0.0021331803873181343f, 0.19198624789714813f);
    F(0xf0) = *(float *)(m + 0x2c); F(0xe0) = F(0x30);
    I(0xc0) = (int)D_L01_001B0900;
    *(int *)(m + 0xf4) = *(int *)(m + 0xf0) = 0;
    qzero(p + 0x210); F(0x218) = 1.0f;
    if (m[0x21] != 255) {
        **(int **)(p + 0x3fc) = 0;
        **(int **)(p + 0x400) = -1;
    }
    if (p[0x3d0]) {
        if (I(0x414) != -1) I(0x3f8) = I(0x414);
        else if (I(0x418) != -1) I(0x3f8) = I(0x418);
        else I(0x3f8) = I(0x41c);
        *(float *)(m + 0x18) -= 2.0f;
        *(u16 *)(m + 0x34) |= 1; *(int *)(m + 0x98) = 0; m[0x31] = 0;
        func_002A7750(m, 0, 1);
        if (m[0x43]) func_002A7470(m, 0, 0, func_002A7820(2, 10));
        return;
    }
    if (p[0x3d1]) {
        if (I(0x414) != -1) I(0x3f8) = I(0x414);
        else if (I(0x418) != -1) I(0x3f8) = I(0x418);
        else I(0x3f8) = I(0x41c);
        if (p[0x3d2]) func_002A7750(m, 0, 1);
        else func_002A7750(m, 1, 3);
    } else {
        if (I(0x418) != -1) I(0x3f8) = I(0x418);
        else if (I(0x414) != -1) I(0x3f8) = I(0x414);
        else I(0x3f8) = I(0x41c);
        func_002A7750(m, 1, 3);
    }
    if (I(0x408) != -1) {
        if (m[0x43] != 7) func_002A7470(m, 7, 0, func_002A7820(2, 10));
    } else if (m[0x43]) func_002A7470(m, 0, 0, func_002A7820(2, 10));
}
