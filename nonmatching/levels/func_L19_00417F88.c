/* Complete nonmatching reconstruction; 1336/1336 bytes.
 * -O2 -G0 -ffunction-sections.
 * Local release results: US 0/1, US2 0/1, PAL 0/1.
 * 4 bounded source hypotheses. Remaining: Saved FP constant/scale permutation and packet UV/constant setup.
 * Reopen with independent original lifetime/control-flow evidence.
 * Complete 64-byte joint matrix and 144-byte draw packet; texture result
 * is a 64-bit EE unsigned long. 002A7988 writes XYZ only. The random W
 * lane is transferred unchanged, never read by C as a float. The billboard
 * basis carries that W into packet W; draw 00280B90 with a null matrix
 * reconstructs homogeneous W from XYZ/vf0.w, excluding incoming packet W.
 * No synthetic initialization. Named constants give 1328 bytes; separate
 * angle capture and a bank-preserving FP-first interface tie at 1336.
 */
#include "common.h"
typedef int BeamQuad __attribute__((mode(TI)));
typedef struct { float v[4]; } BeamVector __attribute__((aligned(16)));
typedef struct {
    BeamVector position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} BeamPacket;
typedef char BeamPacketExtent[sizeof(BeamPacket) == 0x90 ? 1 : -1];
extern BeamVector D_L19_001B9A40;
extern u8 D_L19_001BFEA0[];
extern float D_L19_001B1C08[], D_L19_001B1C0C[];
extern void func_0029FC20(void *, int, void *), func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *), func_00282CF0(void *, const void *, const void *);
extern void func_00282DD8(void *, const void *, const void *), func_002A7988(void *, float, float);
extern float func_002A7940(void);
extern void func_00281EB8(void *, int, u32, int, float, float, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, void *, int);
#define BEAM_COPY(d, s) (*(BeamQuad *)(d) = *(BeamQuad *)(s))

/* Draw the muzzle flares and camera-facing beam, then retain its hit point. */
void func_L19_00417F88(u8 *object)
{
    BeamVector matrix[4], origin, offset, random, flarePoint;
    BeamPacket packet;
    BeamVector endWidth, up, end, projected, corner;
    u8 *state = *(u8 **)(object + 0x68);
    float scale, angle;
    int i;
    func_0029FC20(object, 0, matrix);
    qcopy(&origin, &matrix[3]);
    func_00282F20(&offset, &matrix[0], 0.25f);
    func_00282CC0(&origin, &origin, &offset);
    origin.v[2] += 1.0f;
    func_002A7988(&random, 0.25f, 0.45f);
    func_00282CC0(&flarePoint, &random, &origin);
    scale = *(float *)(state + 0x228) + *(float *)(state + 0x228);
    angle = func_002A7940();
    func_00281EB8(&origin, 0x31, 0x60804020, 1, scale, 0.08f, angle);
    scale = *(float *)(state + 0x228) * 1.5f;
    angle = func_002A7940();
    func_00281EB8(&origin, 0x31, 0x80808080, 1, scale, 0.08f, angle);
    func_002A7988(&random, 0.25f, 0.45f);
    func_00282CC0(&flarePoint, &random, &origin);
    scale = *(float *)(state + 0x228) + *(float *)(state + 0x228);
    angle = func_002A7940();
    func_00281EB8(&flarePoint, 0x31, 0x60804020, 1, scale, 0.08f, angle);
    scale = *(float *)(state + 0x228) * 1.5f;
    angle = func_002A7940();
    func_00281EB8(&flarePoint, 0x31, 0x80808080, 1, scale, 0.08f, angle);
    func_002A7988(&random, 0.25f, 0.45f);
    func_00282CC0(&flarePoint, &random, &origin);
    scale = *(float *)(state + 0x228) + *(float *)(state + 0x228);
    angle = func_002A7940();
    func_00281EB8(&flarePoint, 0x31, 0x60804020, 1, scale, 0.08f, angle);
    scale = *(float *)(state + 0x228) * 1.5f;
    angle = func_002A7940();
    func_00281EB8(&flarePoint, 0x31, 0x80808080, 1, scale, 0.08f, angle);
    func_00282CF0(&projected, state + 0x2E0, &origin);
    func_00282F20(&projected, &projected, *(float *)(state + 0x238) * 60.0f);
    func_00282CC0(&projected, &projected, &origin);
    if (func_002761F8(&origin, &projected, 2, object, 0)) qcopy(&end, D_L19_001BFEA0);
    else qcopy(&end, &projected);
    up.v[0] = 0.0f; up.v[1] = 0.0f; up.v[2] = 1.0f; up.v[3] = 1.0f;
    func_00282CF0(&random, &origin, &D_L19_001B9A40);
    func_00282CF0(&endWidth, &end, &D_L19_001B9A40);
    func_00282F20(&random, &random, 1.0f);
    func_00282F20(&endWidth, &endWidth, 1.0f);
    func_00282DD8(&random, &random, &up);
    func_00282F20(&random, &random, *(float *)(state + 0x234) + *(float *)(state + 0x234));
    func_00282DD8(&endWidth, &endWidth, &up);
    func_00282F20(&endWidth, &endWidth, *(float *)(state + 0x234) + *(float *)(state + 0x234));
    packet.texture = func_0027C878(14);
    packet.mode = 0xFF9000000260UL;
    packet.registers = 0x8000000048UL;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = 0x80804020;
    packet.primitive = 0;
    for (i = 0; i < 4; i++) {
        packet.uv[i][0] = D_L19_001B1C08[i * 2];
        packet.uv[i][1] = D_L19_001B1C0C[i * 2];
    }
    func_00282CF0(&corner, &origin, &random);
    BEAM_COPY(&packet.position[0], &corner);
    func_00282CC0(&corner, &origin, &random);
    BEAM_COPY(&packet.position[1], &corner);
    func_00282CF0(&corner, &end, &endWidth);
    BEAM_COPY(&packet.position[2], &corner);
    func_00282CC0(&corner, &end, &endWidth);
    BEAM_COPY(&packet.position[3], &corner);
    func_00280B90(&packet, 0, 0);
    /* Retail updates these vectors but reuses the first packet's corners. */
    func_00282F20(&random, &random, *(float *)(state + 0x234) * 1.5f);
    func_00282F20(&endWidth, &endWidth, *(float *)(state + 0x234) * 1.5f);
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = 0x80806060;
    func_00280B90(&packet, 0, 0);
    qcopy(state + 0x2C0, &end);
}
