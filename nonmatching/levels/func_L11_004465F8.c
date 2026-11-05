/* 5 November 2026: retained, not linked. USA v1.01, -O2 -G32
 * -ffunction-sections -Wa,-G32, with the repaired reload exclusion.
 * The old qcopy_nc version is locally exact but violates common.h's contract:
 * the following C reads and modifies the copied vertices. A correct qcopy
 * memory clobber gives 1668/1660 bytes, 0/1 USA places. Typed TI copies with
 * the existing qcopy pattern, with and without its scheduling barrier, both
 * give 1636/1660. None is promoted. Reopen with a truthful dependency model
 * or a source lifetime improvement; do not suppress the copy's effects.
 */
#include "common.h"

typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { Vec pos[4]; u32 color[4]; float uv[4][2]; u64 gs[4]; } Quad;
extern u64 func_0027C878(int);
extern float func_00283C28(float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern u32 func_00283D38(u32, u32, float);
extern void func_00280B90(Quad *, int, int);
extern char *D_L11_001FF580[] NOT_SDA;
extern s32 D_L11_001B18D4[] __attribute__((sda));
extern s32 D_L11_001B18D8[] __attribute__((sda));
extern s32 D_L11_001B18DC[] __attribute__((sda));
extern s32 D_L11_001B18E0[] __attribute__((sda));
extern s32 D_L11_001B18E4[] __attribute__((sda));
extern s32 D_L11_001B18A0 __attribute__((sda));
extern float D_L11_001B18CC[] __attribute__((sda));
extern s32 D_L11_001B18D0 __attribute__((sda));
extern s32 D_L11_001B1890 __attribute__((sda));
extern s32 D_L11_001B188C __attribute__((sda));
extern s32 D_L11_001B1894 __attribute__((sda));
extern s32 D_L11_001B1898 __attribute__((sda));
extern s32 D_L11_001B189C __attribute__((sda));
extern float D_L11_001B18F4[] __attribute__((sda));
extern float D_L11_001B18B4[] __attribute__((sda));
extern float D_L11_001B18BC[] __attribute__((sda));
extern float D_L11_001B18C4[] __attribute__((sda));
extern float D_L11_001B18FC __attribute__((sda));
extern float D_L11_001B187C __attribute__((sda));
extern float D_L11_001B18F0 __attribute__((sda));
extern float D_L11_001B18E8 __attribute__((sda));
extern float D_L11_001B18F8 __attribute__((sda));
extern s32 D_L11_001B18A8[2] __attribute__((sda));
extern float D_L11_001B18B0[4][2] __attribute__((sda));
void func_L11_004465F8(char *self) {
    Quad q;
    u32 mask;
    int i, j;
    int next_i;
    float *pos1, *pos2, *pos3;
    char *state = *(char **)(self + 0x68);
    char *points;
    float height;
    if (*(float *)(state + 0x1BC) < D_L11_001B18FC) return;
    q.gs[1] = func_0027C878(D_L11_001B18A0);
    pos1 = q.pos[1];
    pos2 = q.pos[2];
    pos3 = q.pos[3];
    q.gs[2] = 0xFF9000000260ULL;
    q.gs[0] = D_L11_001B18D0 | ((u64)D_L11_001B18D4[0] << 2);
    q.gs[0] |= (u64)D_L11_001B18D8[0] << 4;
    q.gs[0] |= (u64)D_L11_001B18DC[0] << 14;
    q.gs[0] |= (u64)D_L11_001B18E0[0] << 24;
    q.gs[0] |= (u64)D_L11_001B18E4[0] << 34;
    q.gs[3] = D_L11_001B188C | ((u64)D_L11_001B1890 << 2);
    q.gs[3] |= (u64)D_L11_001B1894 << 4;
    q.gs[3] |= (u64)D_L11_001B1898 << 6;
    q.gs[3] |= (u64)D_L11_001B189C << 32;
    height = D_L11_001B18F4[0] + (D_L11_001B18F0 - D_L11_001B18F4[0]) *
        (*(float *)(state + 0x1BC) / D_L11_001B187C);
    points = D_L11_001FF580[*(int *)(state + 0x1C8)];
    for (i = 0; i < *(int *)points - 1; i = next_i) {
        mask = 0xFFFFFF;
        qcopy(q.pos[0], points + (i * 16 + 0x20));
        q.pos[0][2] -= D_L11_001B18E8;
        qcopy(pos1, points + (i * 16 + 0x10));
        q.pos[1][2] -= D_L11_001B18E8;
        qcopy(pos2, points + (i * 16 + 0x20));
        q.pos[2][2] += height + D_L11_001B18F8 * func_00283180(func_00283C28(q.pos[0][1]));
        qcopy(pos3, points + (i * 16 + 0x10));
        next_i = i + 1;
        q.pos[3][2] += height + D_L11_001B18F8 * func_00283180(func_00283C28(q.pos[1][1]));
        q.uv[0][1] = D_L11_001B18B4[0];
        q.uv[1][1] = D_L11_001B18BC[0];
        q.uv[2][1] = D_L11_001B18C4[0];
        q.uv[3][1] = D_L11_001B18CC[0];
        for (j = 0; j < 4; j++) {
            int index = func_00283CF0(q.uv[j][1] + 0.2f);
            float alpha;
            u32 c;
            q.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xD8);
            alpha = func_00283198(*(float *)(state + 0xD0) * 3.1415927410125732f);
            c = D_L11_001B18A8[index];
            q.color[j] = func_00283D38(c & mask, c, alpha);
        }
        func_00280B90(&q, 0, 0);
        for (j = 0; j < 4; j++) {
            int index = func_00283CF0(q.uv[j][1] + 0.2f);
            float alpha;
            u32 c;
            q.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xDC);
            alpha = func_00283198(*(float *)(state + 0xD4) * 3.1415927410125732f);
            c = D_L11_001B18A8[index];
            q.color[j] = func_00283D38(c & 0xFFFFFF, c, alpha);
        }
        func_00280B90(&q, 0, 0);
    }
    qcopy(q.pos[0], points + 0x10);
    q.pos[0][2] -= D_L11_001B18E8;
    qcopy(pos1, points + (*(int *)points * 16));
    q.pos[1][2] -= D_L11_001B18E8;
    qcopy(pos2, points + 0x10);
    q.pos[2][2] += height + D_L11_001B18F8 * func_00283180(func_00283C28(q.pos[0][1]));
    qcopy(pos3, points + (*(int *)points * 16));
    q.pos[3][2] += height + D_L11_001B18F8 * func_00283180(func_00283C28(q.pos[1][1]));
    q.uv[0][1] = D_L11_001B18B4[0];
    q.uv[1][1] = D_L11_001B18BC[0];
    q.uv[2][1] = D_L11_001B18C4[0];
    q.uv[3][1] = D_L11_001B18CC[0];
    for (j = 0; j < 4; j++) {
        int index = func_00283CF0(q.uv[j][1] + 0.2f);
        float alpha;
        u32 c;
        q.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xD8);
        alpha = func_00283198(*(float *)(state + 0xD0) * 3.1415927410125732f);
        c = D_L11_001B18A8[index];
        q.color[j] = func_00283D38(c & 0xFFFFFF, c, alpha);
    }
    func_00280B90(&q, 0, 0);
    for (j = 0; j < 4; j++) {
        int index = func_00283CF0(q.uv[j][1] + 0.2f);
        float alpha;
        u32 c;
        q.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xDC);
        alpha = func_00283198(*(float *)(state + 0xD4) * 3.1415927410125732f);
        c = D_L11_001B18A8[index];
        q.color[j] = func_00283D38(c & 0xFFFFFF, c, alpha);
    }
    func_00280B90(&q, 0, 0);
}
