/* Nonmatching icon renderer reconstruction, 2026-10-28. No C coverage credit.
 * US0/1:632/692B ordinary source,660B with indexed qzero / UV accumulation
 * and -g; narrow keep-block-order plus unsplit edges remains660B. Broad
 * -fno-gcse is worse636B and rejected. Retained -O2 -G0 -ffunction-sections
 * -g profile reproduces frame0x150, but induction pointer allocation, UV
 * spills/reloads, initial constant scheduling, and conversion branches differ.
 * Reopen with independent original loop/index lifetime evidence.
 *
 * Complete packet audit: 00280B90 reads144B (four16B positions,16B colors,
 * 32B UV and four8B state words), plus64B matrix. 00281DE8 initializes the
 * state block at+0x70..+0x8F; the loop initializes every position, color and
 * UV component. qzero is a genuine whole16B clear before the normalize read.
 * Earlier trigonometric stores followed by the clear are observed in retail.
 * 00283658 initializes all64B matrix bytes, including the vf0 fourth row;
 * 002EFB60 scales all64B, then qcopy replaces the translation row and W=1.
 * Thus the renderer never consumes uninitialized locals or a shortened matrix.
 * Actual 004197A8 returns unsigned32 actor counter. Raw-only matrix/render
 * void-return hypotheses remain provisional; complete read/write extents
 * were audited independently. Actual definitions support the other returns.
 * UV tuning allocation is unknown/incomplete. Its two address views correspond
 * to the actual absolute pointer for V and GP pointer for U, not unused aliases.
 */

#include "common.h"
typedef struct { float u, v; } PrisonIconUV;
typedef struct {
    float position[4][4];
    unsigned int color[4];
    PrisonIconUV uv[4];
    unsigned long state[4];
} PrisonIconPacket __attribute__((aligned(16)));
extern unsigned char *D_L14_001B259C __attribute__((sda));
extern int D_L14_001B0394[] SDATA(D_L14_001B0394);
extern float D_L14_001B039C[] SDATA(D_L14_001B039C);
extern float D_L14_001B03A0[] SDATA(D_L14_001B03A0);
extern float D_L14_001B03A4[] SDATA(D_L14_001B03A4);
extern float D_L14_001B03A8[] SDATA(D_L14_001B03A8);
extern unsigned int D_L14_001B03AC[] SDATA(D_L14_001B03AC);
extern float D_L14_001B03B0[] SDATA(D_L14_001B03B0);
extern PrisonIconUV D_L14_001B03B8[];
extern PrisonIconUV D_L14_001B03B8_gp[] SDATA(D_L14_001B03B8);
extern unsigned char D_001A7A44;
extern unsigned int func_L03_004197A8(void *);
extern void func_00283658(void *, const void *);
extern void func_L03_002EFB60(void *, const void *, float);
extern void func_00281DE8(void *, int, int, int);
extern float func_00283B98(float, float), func_00283180(float), func_00283198(float);
extern void func_00282F20(void *, const void *, float);
extern void func_00280B90(void *, const void *, int);

void func_L14_003DFA60(unsigned char *object)
{
    float matrix[4][4] __attribute__((aligned(16)));
    PrisonIconPacket packet;
    unsigned int frame;
    float *position;
    unsigned int *color;
    PrisonIconUV *uv;
    const float *u;
    const float *v;
    float angle;
    int i;
    frame = func_L03_004197A8(D_L14_001B259C + *(int *)(*(unsigned char **)(object + 0x68) + 4) * 256);
    func_00283658(matrix, object + 0xC0);
    func_L03_002EFB60(matrix, matrix, *(float *)(object + 0x2C) / *(float *)(*(unsigned char **)(object + 0x24) + 0x24));
    qcopy(matrix[3], object + 0x10);
    matrix[3][3] = 1.0f;
    func_00281DE8(&packet, D_L14_001B0394[0], 0, 0x80);
    position = packet.position[0];
    color = packet.color;
    uv = packet.uv;
    u = &D_L14_001B03B8_gp[0].u;
    v = &D_L14_001B03B8[0].v;
    for (i = 0; i < 4; i++) {
        angle = func_00283B98(D_L14_001B03A0[0] * 0.01745329424738884f, (float)i * 1.5707963705062866f);
        position[0] = func_00283180(angle) * D_L14_001B03A4[0];
        position[1] = func_00283198(angle) * D_L14_001B03A4[0];
        position[2] = 0.0f;
        qzero(packet.position + i);
        if (i < 2) packet.position[i][1] = 1.0f;
        else packet.position[i][1] = -1.0f;
        if (i & 1) position[2] = -1.0f;
        else position[2] = 1.0f;
        if (D_001A7A44) position[1] = -position[1];
        func_00282F20(position, position, D_L14_001B03A4[0]);
        position[2] += D_L14_001B03B0[0];
        position[0] = D_L14_001B03A8[0];
        position[3] = 1.0f;
        *color = D_L14_001B03AC[0];
        uv->u = *u;
        {
        float numerator;
        if (i < 2) numerator = (float)(int)frame;
        else numerator = (float)(int)(frame + 1);
        uv->u += numerator / D_L14_001B039C[0];
        }
        uv->v = *v;
        position += 4;
        color++;
        uv++;
        u += 2;
        v += 2;
    }
    func_00280B90(&packet, matrix, 0);
}
