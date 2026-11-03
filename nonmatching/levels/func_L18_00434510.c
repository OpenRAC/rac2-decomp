/* opus-1, USA v1.01 game -O2 -G0 -ffunction-sections (file default).
 * Best check.py: 1176/1176 bytes, 0 of 1 places match. Every instruction
 * agrees except about 11 words: before the loop retail puts basis[2]
 * (sp+0x20) in s7 and the points[i+1] induction pointer (fp+0x20) in s6,
 * with mov.s f21,f24 issued before addiu s6,fp,0x20; this draft swaps
 * s6/s7 (all loop uses and the loop-end addiu follow) and the order of
 * those two instructions.
 * Cause (tools/regalloc.py): pseudo 134 (sp+16 before the loop, priority
 * 1515) is allocated before the induction pointer 257 (refs 7, live 93,
 * priority 1505), which takes s7; basis[2] 199 (refs 9, live 190, 1421)
 * then gets s6. The loop's 0.33f constant is not hoisted in loop pass 1
 * (life 2, savings 1, threshold reduced by 8 earlier hoists); pass 2 hoists
 * it after the induction-pointer setups, adding one insn to 257's life.
 * Retail would need 257 live <= 92 (or 199 before 257). Operand order,
 * a named float step (worse: frame 0x200) and -g made no difference.
 * Fixed versus the sol-high draft: width[2] store slot, UV order (u, u,
 * next, next), template structure as two TI/float unions.
 * Declarations needed by this standalone draft follow (the first five are
 * already in L18_00433460.c).
 */
#include "common.h"
extern float D_L18_001B97C0[];
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern void func_00282D30(void *, void *, float);
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } RibbonVector;
struct RibbonQuad { RibbonVector position[4]; u32 color[4]; float uv[4][2]; u64 clear, texture, giftag, flags; };
extern unsigned long func_0027C878(int);
extern void func_L00_00412088(void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern float func_00283CE0(int);

void func_L18_00434510(RibbonVector *points, int count, int flags, u32 color0, u32 color1, float width, float scale) {
    RibbonVector basis[4];
    struct RibbonQuad mainQuad, innerQuad;
    RibbonVector template0, template1;
    float u, nextU;
    int i;
    mainQuad.texture = func_0027C878(0x2B);
    mainQuad.flags = ((u64)(u32)flags << 32) | 0x68;
    mainQuad.giftag = 0xFF9000000260ULL;
    mainQuad.color[0] = mainQuad.color[1] = mainQuad.color[2] = mainQuad.color[3] = color0;
    mainQuad.clear = 0;
    func_L00_00412088(&mainQuad);
    mainQuad.uv[0][0] = 0.0f; mainQuad.uv[0][1] = 0.0f;
    mainQuad.uv[1][0] = 0.0f; mainQuad.uv[1][1] = 1.0f;
    mainQuad.uv[2][0] = 1.0f; mainQuad.uv[2][1] = 0.0f;
    mainQuad.uv[3][0] = 1.0f; mainQuad.uv[3][1] = 1.0f;
    innerQuad.texture = func_0027C878(0x2B);
    innerQuad.giftag = 0xFF9000000260ULL;
    innerQuad.clear = 0;
    innerQuad.flags = ((u64)(long)(flags / 3) << 32) | 0x68;
    innerQuad.color[0] = innerQuad.color[1] = innerQuad.color[2] = innerQuad.color[3] = color1;
    func_L00_00412088(&innerQuad);
    innerQuad.uv[0][0] = 0.0f; innerQuad.uv[0][1] = 0.0f;
    innerQuad.uv[1][0] = 0.0f; innerQuad.uv[1][1] = 1.0f;
    innerQuad.uv[2][0] = 0.33f; innerQuad.uv[2][1] = 0.0f;
    innerQuad.uv[3][0] = 0.33f; innerQuad.uv[3][1] = 1.0f;
    template0.q = 0;
    template1.q = 0;
    template0.f[3] = 1.0f;
    template1.f[3] = 1.0f;
    template0.f[2] = width;
    template1.f[2] = width * scale;
    func_00282CF0((float *)&basis[0], (float *)&points[1], (float *)&points[0]);
    func_00282F20((char *)&basis[0], (char *)&basis[0], 1.0f);
    func_00282CF0((float *)&basis[1], D_L18_001B97C0, (float *)&points[0]);
    func_00282DD8(&basis[2], &basis[1], &basis[0]);
    func_00282F20((char *)&basis[2], (char *)&basis[2], 1.0f);
    func_00282DD8(&basis[1], &basis[0], &basis[2]);
    qcopy(&basis[3], &points[0]);
    qcopy(&mainQuad.position[0], &template0);
    func_00282D30(&mainQuad.position[1], &mainQuad.position[0], -1.0f);
    func_002830C0(&mainQuad.position[0], &mainQuad.position[0], basis);
    func_002830C0(&mainQuad.position[1], &mainQuad.position[1], basis);
    qcopy(&innerQuad.position[0], &template1);
    func_00282D30(&innerQuad.position[1], &innerQuad.position[0], -1.0f);
    func_002830C0(&innerQuad.position[0], &innerQuad.position[0], basis);
    func_002830C0(&innerQuad.position[1], &innerQuad.position[1], basis);
    for (i = 1; i < count - 1; i++) {
        qcopy(&mainQuad.position[2], &template0);
        func_00282D30(&mainQuad.position[3], &mainQuad.position[2], -1.0f);
        qcopy(&innerQuad.position[2], &template1);
        func_00282D30(&innerQuad.position[3], &innerQuad.position[2], -1.0f);
        func_00282CF0((float *)&basis[0], (float *)&points[i + 1], (float *)&points[i]);
        func_00282F20((char *)&basis[0], (char *)&basis[0], 1.0f);
        func_00282CF0((float *)&basis[1], D_L18_001B97C0, (float *)&points[i]);
        func_00282DD8(&basis[2], &basis[1], &basis[0]);
        func_00282F20((char *)&basis[2], (char *)&basis[2], 1.0f);
        func_00282DD8(&basis[1], &basis[0], &basis[2]);
        qcopy(&basis[3], &points[i]);
        func_002830C0(&mainQuad.position[2], &mainQuad.position[2], basis);
        func_002830C0(&mainQuad.position[3], &mainQuad.position[3], basis);
        func_002830C0(&innerQuad.position[2], &innerQuad.position[2], basis);
        func_002830C0(&innerQuad.position[3], &innerQuad.position[3], basis);
        if (i == count - 2) {
            mainQuad.color[2] = 0; mainQuad.color[3] = 0;
            innerQuad.color[2] = 0; innerQuad.color[3] = 0;
        }
        func_00280B90(&mainQuad, 0, 0);
        func_00280B90(&innerQuad, 0, 0);
        u = 0.33f * func_00283CE0(i);
        nextU = u + 0.33f;
        if (u >= 1.0f) {
            u -= 1.0f;
            nextU -= 1.0f;
        }
        innerQuad.uv[0][0] = u; innerQuad.uv[1][0] = u;
        innerQuad.uv[2][0] = nextU; innerQuad.uv[3][0] = nextU;
        qcopy(&mainQuad.position[0], &mainQuad.position[2]);
        qcopy(&mainQuad.position[1], &mainQuad.position[3]);
        qcopy(&innerQuad.position[0], &innerQuad.position[2]);
        qcopy(&innerQuad.position[1], &innerQuad.position[3]);
    }
}
