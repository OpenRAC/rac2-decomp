/* Complete nonmatching reconstruction. Default -O2 -G0 -ffunction-sections:
 * 932/932 bytes, US/US2/PAL 0/1 each. Four local
 * trials established the default TImode transfer as the exact corner shape;
 * qcopy and the register-address/barrier profile add spills. Remaining:
 * packet constant/store scheduling and UV-loop register allocation. Reopen
 * with independently grounded packet/UV pointer lifetimes. Full 144-byte
 * packet; texture helper returns a 64-bit EE unsigned long.
 */
#include "common.h"

typedef struct { float v[4]; } RibbonVector __attribute__((aligned(16)));
typedef struct {
    RibbonVector position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} RibbonPacket;
typedef char RibbonPacketExtent[sizeof(RibbonPacket) == 0x90 ? 1 : -1];
extern RibbonVector D_L19_001B9A40;
extern float D_L19_001B1DE8[];
extern float D_L19_001B1DEC[];
typedef int RibbonWord __attribute__((mode(TI)));
#define RIBBON_COPY(d, s) (*(RibbonWord *)(d) = *(RibbonWord *)(s))
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, void *, int);
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282DD8(void *, const void *, const void *);

/* Draw the two camera-facing edges of the moving object's extrusion. */
void func_L19_00420B48(unsigned char *object)
{
    RibbonPacket packet;
    RibbonVector startWidth, endWidth, extrusion, endpoint, corner;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    int i;
    func_00282F20(&extrusion, object + 0xE0, *(float *)(state + 0xC));
    func_00282CC0(&endpoint, object + 0x10, &extrusion);
    func_00282CF0(&startWidth, object + 0x10, &D_L19_001B9A40);
    func_00282CF0(&endWidth, &endpoint, &D_L19_001B9A40);
    func_00282DD8(&startWidth, &startWidth, &extrusion);
    func_00282F20(&startWidth, &startWidth, 0.15f);
    func_00282DD8(&endWidth, &endWidth, &extrusion);
    func_00282F20(&endWidth, &endWidth, 0.15f);
    packet.texture = func_0027C878(14);
    packet.registers = 0x8000000048UL;
    packet.mode = 0xFF9000000260UL;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = 0x80243278;
    packet.primitive = 0;
    for (i = 0; i < 4; i++) {
        packet.uv[i][0] = D_L19_001B1DE8[i * 2];
        packet.uv[i][1] = D_L19_001B1DEC[i * 2];
    }
    func_00282CF0(&corner, object + 0x10, &startWidth);
    RIBBON_COPY(&packet.position[0], &corner);
    func_00282CC0(&corner, object + 0x10, &startWidth);
    RIBBON_COPY(&packet.position[1], &corner);
    func_00282CF0(&corner, &endpoint, &endWidth);
    RIBBON_COPY(&packet.position[2], &corner);
    func_00282CC0(&corner, &endpoint, &endWidth);
    RIBBON_COPY(&packet.position[3], &corner);
    func_00280B90(&packet, 0, 0);
    func_00282CF0(&startWidth, object + 0x10, &D_L19_001B9A40);
    func_00282CF0(&endWidth, &endpoint, &D_L19_001B9A40);
    func_00282DD8(&startWidth, &startWidth, &extrusion);
    func_00282F20(&startWidth, &startWidth, 0.05f);
    func_00282DD8(&endWidth, &endWidth, &extrusion);
    func_00282F20(&endWidth, &endWidth, 0.05f);
    packet.texture = func_0027C878(14);
    packet.mode = 0xFF9000000260UL;
    packet.registers = 0x8000000048UL;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = 0x80808080;
    packet.primitive = 0;
    for (i = 0; i < 4; i++) {
        packet.uv[i][0] = D_L19_001B1DE8[i * 2];
        packet.uv[i][1] = D_L19_001B1DEC[i * 2];
    }
    func_00282CF0(&corner, object + 0x10, &startWidth);
    RIBBON_COPY(&packet.position[0], &corner);
    func_00282CC0(&corner, object + 0x10, &startWidth);
    RIBBON_COPY(&packet.position[1], &corner);
    func_00282CF0(&corner, &endpoint, &endWidth);
    RIBBON_COPY(&packet.position[2], &corner);
    func_00282CC0(&corner, &endpoint, &endWidth);
    RIBBON_COPY(&packet.position[3], &corner);
    func_00280B90(&packet, 0, 0);
}
