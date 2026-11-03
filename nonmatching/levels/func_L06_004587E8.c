/* 2 November 2026: lawful retained reconstruction, not a match.
 * Removed the older draft's always-true regen test and unreachable else arm.
 * Those branches were invented to influence compiler PRE/loop behavior; they
 * do not describe runtime state and cannot support matching credit. The
 * unconditional timer/alpha reset and trail regeneration remain explicit.
 * Current check.py: 1596/1572 bytes, 0/1 USA v1.01 placement. The old
 * 1564/1572-byte measurement depended on the diagnostic and does not qualify
 * this source. Scratch collision[112] remains an inferred capacity;
 * the owner-hit position copy, null-hit emission and real state reloads are
 * preserved. Reopen matching work with evidence for the genuine original
 * loop/control-flow and local lifetimes. No linked match is claimed.
 */
#include "common.h"
extern short D_L06_001B3790[] __attribute__((sda));
extern short D_L06_001B37A0[] __attribute__((sda));
extern char D_L06_0025FFC0[];
extern float func_00283B98(float, float);
typedef unsigned int NotakQuad __attribute__((mode(TI)));
extern char D_00188660[];
extern char D_L06_001A8F20[] __attribute__((sda));
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern char D_L06_001B9840[];
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern int func_002A77E0(int);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern void func_002A7750(char *, int, int);
extern float func_002A7878(float, float);
extern void func_00350388(char *);
typedef struct {
    char prefix[0x18];
    char *hit;
    int count;
    float point[4];
} NotakCollision;
extern NotakCollision D_L06_001BFC80;
extern char D_L06_001C79C0[];
extern int D_L06_001B3778[], D_L06_001B3760[];
extern void func_002A8C00(void *, char *, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_0031EBF8(float, void *, int, void *);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_L06_00459828(float *, int);
extern void func_00291450(int);
extern void func_002A7988(void *, float, float);
extern float func_00282DF0(void *);
extern int func_002E59B0(void *, int);
extern int func_002E5DA0(int, int, void *, int);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L06_00458F30(char *);

void func_L06_004587E8(char *o) {
    float pos[4];
    typedef union { NotakQuad q; float f[4]; } Vec;
    union { char collision[112]; struct { Vec velocity, axis; } vectors; } scratch;
    char *st = *(char **)(o + 0x68);
    int i, j, sign, snd;
    typedef NotakQuad Trail[6][4];
    float direction;
    float size;
    switch (*(unsigned char *)(o + 0x20)) {
    case 0:
        *(float *)(o + 0xF0) = func_00283B98(*(float *)(o + 0xF0), 0.104719773f);
        func_00282CC0(pos, o + 0x10, st);
        func_002A8C00(scratch.collision, o, 1, st, *(float *)(st + 0x40));
        *(unsigned short *)(scratch.collision + 0x1A) = *(unsigned short *)(o + 0xAA);
        if (func_002761F8(o + 0x10, pos, 0, o, scratch.collision) ||
            func_0031EBF8(0.3f, o + 0x10, 0, o) || func_00282948(st + 0x38)) {
            char *hit = D_L06_001BFC80.hit;
            float *impact = D_L06_001BFC80.point;
            if (hit) {
                if (hit == *(char **)(st + 0x3C)) goto update_position;
                if (*(short *)(hit + 0xAA) != 0x4E)
                    func_002A8C28(o, o + 0x10, 0x10001, 0, 1, 0, 0.5f, *(float *)(st + 0x40), 1.0f);
                impact = (float *)(o + 0x10);
            }
            func_L06_00459828(impact, 20);
            snd = *(int *)(st + 0x4C);
            if (snd != -1) {
                char *s = D_00188660 + snd * 0x70;
                if (*(char **)(s + 0x88) == o && *(unsigned char *)(s + 0x74)) func_002E59F8(snd);
            }
            *(int *)(st + 0x4C) = -1;
            func_002A7750(o, 1, -1);
            return;
        }
    update_position:
        qcopy(o + 0x10, pos);
        break;
    case 1: {
        int index, row, col;
        index = D_L06_001B3778[*(int *)(st + 0x48)];
        if (index >= 0) {
            char *p = D_L06_001C79C0 + index * 32;
            *(float *)(p + 0x1C) -= 0.166666672f;
            if (!(*(float *)(p + 0x1C) <= 0)) return;
            func_00291450(D_L06_001B3778[*(int *)(st + 0x48)]);
            D_L06_001B3778[*(int *)(st + 0x48)] = -1;
            D_L06_001B3760[*(int *)(st + 0x48)] = 0;
            for (row = 0; row < 6; row++) {
                int off = *(int *)(st + 0x48) * 0x180 + (row << 6);
                for (col = 1; col < 4; col++)
                    qzero_nc(&((NotakQuad *)(D_L06_0025FFC0 + off))[col]);
            }
            func_00350388(o);
            return;
        }
        D_L06_001B3760[*(int *)(st + 0x48)] = 0;
        func_00350388(o);
        return;
    }
    }
    qcopy(pos, o + 0x10);
    {
        int k = 0;
        if (D_L06_001B3790[k]) goto scanned;
    next:
        k++;
        while (k < 6) {
            if (!D_L06_001B3790[k]) goto next;
            break;
        }
    scanned:;
    }
    for (i = 0; i < 6; i++) {
        if (--D_L06_001B3790[i] < 0) D_L06_001B3790[i] = 0;
        D_L06_001B3790[i] = 2;
        D_L06_001B37A0[i] = 64;
        func_002A7988(scratch.vectors.velocity.f, 0.2f, 0.2f);
        if (func_00282DF0(scratch.vectors.velocity.f) > 0.2f) func_00282F20((char *)scratch.vectors.velocity.f, (char *)scratch.vectors.velocity.f, 0.2f);
        qcopy(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][0], pos);
        direction = 1.0f;
        for (j = 1; j < 4; j++) {
            func_00282CF0(scratch.vectors.axis.f, (float *)(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j - 1]), (float *)D_L06_001B9840);
            func_002ACEC0(scratch.vectors.velocity.f, scratch.vectors.velocity.f, scratch.vectors.axis.f, func_002A7878(0.17453295f, 0.7853982448577881f) * direction);
            direction = -direction;
            func_00282CC0(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j], &((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j - 1], scratch.vectors.velocity.f);
        }
    }
    if (!func_002A77E0(2)) {
        size = func_002A7878(0.2f, 0.9f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        func_002C2210(o + 0x10, 2, size * 0.1f, size, 0x7F7F2020, 0, sign, D_L06_001A8F20, 0, 0);
        func_002C2210(o + 0x10, 2, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, D_L06_001A8F20, 0, 0);
    }
    if (!func_002E59B0(o, *(int *)(st + 0x4C)))
        *(int *)(st + 0x4C) = func_002E5DA0(7, 4, o, *(short *)(*(char **)(st + 0x3C) + 0xAA));
    func_L00_002E6EF8(func_L06_00458F30, o);
}
