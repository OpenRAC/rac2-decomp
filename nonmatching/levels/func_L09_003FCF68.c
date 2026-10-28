/* func_L09_003FCF68 - 444 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L09_003FCF68 (444 B, 1 place). Needs a new file with flags `-O2 -G64
   -Wa,-G64 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-
   ti-por` (the 64-byte table at 0x1B1200 is addressed `gp+0x2210`; `float
   D[16] __attribute__((sda))` gives that only with -G64; at -G8 it falls to
   lui/addiu). Body includes common.h (qcopy, u32); remove its `typedef
   unsigned int u32`.
   Structure fully decoded: EffectPacket (same struct as
   src/game/00325430-q.c: position[4], color[4], uv[4][2], primitive, texture,
   mode, registers) at sp+0x50, matrix m[12] at sp+0, rot vec, call order
   matches retail. Output 448 B vs 444.
   Remaining difference: retail keeps &pk in $s3 across the 4-iteration loop
   (s0 = walking pos ptr, s1 = count 3.., s2 = gp table ptr) and sets those
   four right before the loop (after the colour stores); mine hoists `addiu
   $s4,$gp,..` and `addiu $s3,$zero,3` above the calls (one more saved
   register, $s4) and recomputes sp+0x50 for the last call.
   Tried: indexed loop, pointer-walk loop, `EffectPacket *q = &pk` used for
   the last call.
   tried -fno-gcse: no change */

typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    TI128 position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} EffectPacket;

extern float D_L09_001B1200[16] __attribute__((sda));
extern float D_L09_001B9A00[];
extern unsigned long func_0027C878(int);
extern void func_002FC560(u32, unsigned long);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00282E20(void *);
extern void func_002833F0(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);

void func_L09_003FCF68(char *obj) {
    float m[12] __attribute__((aligned(16)));
    float s1[4] __attribute__((aligned(16)));
    float s0[4] __attribute__((aligned(16)));
    EffectPacket pk;
    float e[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    char *st = *(char **)(obj + 0x68);
    u32 col;
    int i;
    TI128 *p;
    EffectPacket *q;
    float *g;

    qcopy(s1, st + 0x370);
    s1[3] = 1.0f;
    func_00282D30(s0, st + 0x340, 0.5f);
    func_00282CC0(s1, s1, s0);
    pk.texture = func_0027C878(11);
    pk.mode = 0x0000ff9000000260UL;
    pk.registers = 0x0000008000000048UL;
    pk.primitive = 0;
    func_002FC560(0x47, 0x51001);
    func_00282CF0(e, D_L09_001B9A00, s1);
    rot[2] = func_00283248(e[0], e[1]);
    rot[1] = -func_00283248(func_00282E20(e), e[2]);
    rot[0] = 0;
    func_002833F0(m, rot);
    pk.uv[2][0] = 1.0f;
    pk.uv[0][0] = 1.0f;
    pk.uv[0][1] = 1.0f;
    pk.uv[1][0] = 0;
    pk.uv[1][1] = 1.0f;
    pk.uv[2][1] = 0;
    pk.uv[3][0] = 0;
    pk.uv[3][1] = 0;
    col = *(short *)(st + 0x422) != 0 ? 0x7F40407F : 0x7F7F7F7F;
    pk.color[0] = col;
    pk.color[3] = col;
    pk.color[2] = col;
    pk.color[1] = col;
    q = &pk;
    p = q->position;
    g = D_L09_001B1200;
    for (i = 0; i < 4; i++) {
        func_00282D30(p, g, 0.75f);
        func_002830C0(p, p, m);
        p++;
        g += 4;
    }
    func_00280B90(q, 0, 0);
}
