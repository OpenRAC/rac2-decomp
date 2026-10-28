/* func_L11_00397820 - 528 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Needs its own file with cflags: -O2 -G8 -ffunction-sections -frac2-qcopy
   -frac2-qcopy-barrier (twin: src/game/0031C970-q.c packet code, and the
   handoff for func_L06_00459620).
   532 vs 528 bytes. Frame layout, callee args, uv/mode/registers constants
   all match. Differences: register roles (retail: counter=s3, table
   pointer=s4, state=s5; mine state=s3, counter=s4)
   and retail builds the table base (lui/addiu s4 = 0x1AA2D0) before the first
   call func_00282CF0 while mine builds it later; mine is one instruction
   longer.
   D_L11_001AEC88 and D_L11_001AEC70 are sda floats (gp -0x368 / -0x380);
   D_L11_001AEC8C and D_L11_001AEC90 are absolute (lui $at; lwc1) - declared
   plain. */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    TI128 position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} EffectPacket;
typedef struct {
    float a[4];
    float b[4];
    float c[4];
    float pos[4];
    float axis[4];
    float tmp[4];
    EffectPacket packet;
} Frame;

extern unsigned long func_0027C878(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern char D_L11_001BA8C0[];
extern char D_L11_001AA2D0[];
extern float D_L11_001AEC88 __attribute__((sda));
extern float D_L11_001AEC70 __attribute__((sda));
extern float D_L11_001AEC8C;
extern float D_L11_001AEC90;

void func_L11_00397820(u8 *object)
{
    Frame f;
    u8 *state = *(u8 **)(object + 0x68);
    int i;
    TI128 *q;
    char *table;

    qcopy(f.axis, object + 0xE0);
    qcopy(f.pos, object + 0x10);
    func_00282CF0(f.a, D_L11_001BA8C0, f.pos);
    func_00282F20(f.a, f.a, 1.0f);
    func_00282DD8(f.b, f.a, f.axis);
    func_00282F20(f.b, f.b, 1.0f);
    func_00282DD8(f.c, f.b, f.a);
    func_00282F20(f.a, f.a, D_L11_001AEC88);
    func_00282F20(f.b, f.b, D_L11_001AEC8C);
    func_00282F20(f.c, f.c, D_L11_001AEC90);
    func_00282D30(f.tmp, f.a, D_L11_001AEC70);
    func_00282CC0(f.pos, f.pos, f.tmp);
    f.packet.registers = 0x0000008000000048UL;
    f.packet.mode = 0x0000ff9000000260UL;
    f.packet.primitive = 5;
    f.packet.uv[0][0] = 0;
    f.packet.uv[0][1] = 0;
    f.packet.uv[1][0] = 0;
    f.packet.uv[1][1] = 1.0f;
    f.packet.uv[2][0] = 1.0f;
    f.packet.uv[2][1] = 0;
    f.packet.uv[3][0] = 1.0f;
    f.packet.uv[3][1] = 1.0f;
    f.packet.color[0] = *(u32 *)(state + 0x30);
    f.packet.color[3] = *(u32 *)(state + 0x30);
    f.packet.color[2] = *(u32 *)(state + 0x30);
    f.packet.color[1] = *(u32 *)(state + 0x30);
    for (i = 3, q = f.packet.position, table = D_L11_001AA2D0; i >= 0; i--, q++, table += 0x10) {
        func_00282D30(q, table, *(float *)(state + 0x2C));
        func_002830C0(q, q, f.a);
    }
    f.packet.texture = func_0027C878(0xB);
    func_00280B90(&f.packet, 0, 0);
    f.packet.texture = func_0027C878(6);
    func_00280B90(&f.packet, 0, 0);
}
