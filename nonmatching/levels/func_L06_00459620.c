/* func_L06_00459620 - 516 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Needs its own file (draft.c) with cflags: -O2 -G64 -Wa,-G64 -ffunction-
   sections -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-ti-por
   (twin: src/game/0031C970-q.c packet code). Right size. 9 masked diff lines,
   all scheduling/placement:
   retail emits `addiu $s1,$sp,0x90` (=&f.a) and `daddu $s6,$s1,$zero` before
   the first call func_00282CF0 (between the colour stores);
   mine emits them after that call's setup (addiu s1 in the call's delay slot
   area). Also sw 0x44 position differs by one slot.
   Tried: local float *pa = f.a at top (75 lines, worse), assigned before
   colour stores (118 lines, worse). movz needs `!f() ? 0x7F7F4040 :
   0x307F4040`;
   mode/registers must be assigned registers first then mode. */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    TI128 position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} EffectPacket;
typedef struct {
    EffectPacket packet;
    float a[4];
    float b[4];
    float c[4];
    float tmp[4];
    TI128 pos;
    TI128 axis;
    float d[4];
} Frame;

extern unsigned long func_0027C878(int);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern char D_L06_001B9840[];
extern float D_L06_001B1930[16] __attribute__((sda));

void func_L06_00459620(u8 *a0)
{
    Frame f;
    u32 color;
    int i;

    qcopy(&f.pos, a0 + 0x10);
    ((float *)&f.pos)[3] = 1.0f;
    f.packet.texture = func_0027C878(8);
    f.packet.registers = 0x0000008000000048UL;
    f.packet.mode = 0x0000ff9000000260UL;
    f.packet.primitive = 0;
    f.packet.uv[0][0] = 0;
    f.packet.uv[0][1] = 0;
    f.packet.uv[1][0] = 0;
    f.packet.uv[1][1] = 1.0f;
    f.packet.uv[2][0] = 1.0f;
    f.packet.uv[2][1] = 0;
    f.packet.uv[3][0] = 1.0f;
    f.packet.uv[3][1] = 1.0f;
    color = !func_002A77E0(4) ? 0x7F7F4040 : 0x307F4040;
    color = (color & 0x00FFFFFF) | (func_00283CF0(func_00283CE0(color >> 24)) << 24);
    f.packet.color[0] = color;
    f.packet.color[3] = color;
    f.packet.color[2] = color;
    f.packet.color[1] = color;
    f.axis = 0;
    ((float *)&f.axis)[3] = 1.0f;
    ((float *)&f.axis)[2] = 1.0f;
    func_00282CF0(f.d, D_L06_001B9840, &f.pos);
    func_00282F20(f.a, f.d, 1.0f);
    func_00282DD8(f.b, f.a, &f.axis);
    func_00282F20(f.b, f.b, 1.0f);
    func_00282DD8(f.c, f.b, f.a);
    func_00282D30(f.d, f.a, 0.2f);
    func_00282CC0(&f.pos, &f.pos, f.d);
    for (i = 0; i < 4; i++) {
        func_00282D30(f.tmp, &D_L06_001B1930[i * 4], 0.2f);
        func_002830C0(&f.packet.position[i], f.tmp, f.a);
    }
    func_00280B90(&f.packet, 0, 0);
}
