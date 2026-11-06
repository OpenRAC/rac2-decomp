/* 6 November 2026, round 2: best body below (916/916, 0/27 USA, 9 words; was 11).
 * A one-pass group around the copy only, `do { qcopy(dst, src); } while (0);`,
 * fixes the s1/s2 roles (source pointer s1, vertices s2). Left: a0/a1 for D-16 vs
 * last*16, the source start still summed (last*16 + i*320) + (D-16), and the group's
 * loop note moves `addiu a1, sp, 0x160` into the jal slot. The loop dump shows the
 * source giv add as ((i*320) + -16) + D_reg; retail needs i*320 + X, X opaque.
 * Tied (9): &D[i][j] - 1, D[0] - 1 cast to a row array, (D[0] - 1)[i*20 + j], group
 * around `index = ...; qcopy`, the -g8-qcopy unit. Worse: group around the call or
 * the 0.05f store (15-213), a source local before qcopy (952/956), struct assign
 * in the -g8-qcopy unit (932), group around last= (16) or the counter clamp (11).
 */
/* Complete-owner follow-up, 2026-11-03; no linked match.
 * One new check under -O2 -G8 -ffunction-sections: int32 byte-offset cursors
 * over the actual four 20-point rows stay 916/916 bytes, 0/27 US placements.
 * The first residual moves to +0x4C (stack/cursor capture); equal extent and
 * frame 0x1F0 do not mean equal code. The earlier indexed body below is kept.
 * The offset probe formed pointers only inside j>0, so it never needed a
 * D-16 pointer outside the 1280-byte owner. Both forms use complete 16-byte
 * points, the 320-byte local vertex array and the measured draw/particle ABI.
 * No new source witness resolves the existing inner-loop source lifetime.
 * Reopen with independently grounded ownership/capture evidence, not an
 * invented alias, spill or before-owner pointer.
 */
/* Claude Opus 5.5 xhigh, v2208, 2026-11-03; not linked.
 * Best check: USA v1.01, -O2 -G8 -ffunction-sections (the L00_003B9CB8-g8.c unit),
 * 916/916 bytes, 0/27 places; declarations are included below. Improved from 912:
 * the texture table is nosda and read through a block-local `tables` pointer,
 * which gives retail's lui/addiu + lw 0xF8 and also fixes the i+1 temporary,
 * the first effect's context/scale order and the final context register.
 * Residual: only the inner copy loop's setup (+0xB8..+0x10C). Retail starts the
 * source pointer at last*16 + (i*320 + X), X = D-16, like the destination's
 * last*16 + (i*320 + D). Here cse1's related value rewrites D-16 as D_reg + -16
 * (the destination already loaded D in the same block), loop.c substitutes that
 * movable into the giv, and the start comes out as (last*16 + i*320) + (D-16);
 * a0/a1 and s1/s2 swap as a result. X must stay opaque at loop time (a LO_SUM
 * movable, related only in cse2). Tied: &D[i][j] - 1, D[i] + j - 1,
 * D[i] + (j - 1), flat (UiHistoryPoint *)D + i*20 + j - 1. Worse: source
 * pointer local computed first (952), count-up loop with reversed indices (936),
 * struct assignment (932, ld/sd pairs), separate prev = j - 1 index (924, no
 * strength reduction). Reopen with a form that keeps the source's D-16 out of
 * the destination's cse1 block.
 */
#include "common.h"


typedef struct { float f[4]; } __attribute__((aligned(16))) UiHistoryPoint;
extern int D_L00_001B2940[] MACRO_ADDR;
extern UiHistoryPoint D_L00_0023FB80[][20];
extern UiHistoryPoint D_L00_001B2900[] MACRO_ADDR;
extern float D_L00_001AFF4C __attribute__((sda));
extern int D_L00_001AFF50 __attribute__((sda));
extern int D_L00_001AFF54 __attribute__((sda));
extern int D_L00_001AFF58 __attribute__((sda));
extern float D_L00_001AFF5C __attribute__((sda));
extern float D_L00_001AFF60 __attribute__((sda));
extern char D_L00_001FE940[] __attribute__((nosda));
extern void func_00282CC0(void *, void *, void *);
/* The second integer-bank input is forwarded as the axis vector pointer. */
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_002ACB48(float *, float);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
typedef struct {
    char prefix[8];
    int flags;
    char pad[0x24];
    UiHistoryPoint origin;
} UiTrailState;
typedef struct {
    unsigned char prefix[2];
    unsigned char texture;
    unsigned char flags;
    int color;
    int unused;
    float size;
} UiTrailParticle;
extern UiTrailParticle *func_002C36D0(void *, int, int, int);
extern void func_L00_003C5310(void *, int, int, int, int, int, int, int,
                              int, int, int, float, float, float);

void func_L00_003C4F78(char *owner)
{
    UiHistoryPoint vertices[20], origin, change;
    UiTrailState *state = *(UiTrailState **)(owner + 0x68);
    int i;
    qcopy(&origin, &state->origin);
    for (i = 0; i < 4; i++) {
        int last, j;
        UiHistoryPoint *head, *tip;
        float length, limit;
        UiTrailParticle *effect;
        D_L00_001B2940[i]++;
        if (D_L00_001B2940[i] >= 20)
            D_L00_001B2940[i] = 20;
        last = D_L00_001B2940[i] - 1;
        for (j = last; j > 0; j--) {
            int index = last - j;
            do { qcopy(&D_L00_0023FB80[i][j], &D_L00_0023FB80[i][j - 1]); } while (0);
            func_00282CC0(&vertices[index], &origin, &D_L00_0023FB80[i][j]);
            vertices[index].f[3] = 0.05f;
        }
        head = &D_L00_0023FB80[i][0];
        func_002AB668(&change, &D_L00_001B2900[i], 0.10471976548433304f);
        func_002ACDE8(head, head, &change);
        func_002ACB48(head->f, 0.025f);
        length = func_00282DF0(head);
        limit = D_L00_001AFF4C * 1.1f;
        if (length > limit)
            func_00282D30(head, head, limit / length);
        else {
            limit = D_L00_001AFF4C * 0.9f;
            if (length < limit)
                func_00282D30(head, head, limit / length);
        }
        func_00282CC0(&vertices[last], &origin, &D_L00_0023FB80[i][0]);
        vertices[last].f[3] = 0.05f;
        {
            int endpoint = D_L00_001B2940[i] - 1;
            tip = vertices + endpoint;
        }
        effect = func_002C36D0(tip, 2, 0, 1);
        if (effect != 0) {
            char *tables = D_L00_001FE940;
            effect->color = D_L00_001AFF50 | state->flags;
            effect->size = D_L00_001AFF5C * 210000.0f;
            effect->texture = (*(char **)(tables + 0xF8))[1];
        }
        effect = func_002C36D0(tip, 2, 0, 1);
        if (effect != 0) {
            effect->color = 0x407F7F7F;
            effect->size = D_L00_001AFF5C * 31500.001953125f;
        }
        func_L00_003C5310(vertices, 20, 14, 14,
                          D_L00_001AFF54, D_L00_001AFF54 & 0xFFFFFF,
                          D_L00_001AFF58 | state->flags, D_L00_001AFF58,
                          0, D_L00_001B2940[i] - 1, D_L00_001B2940[i],
                          0.02f, 0.07f, D_L00_001AFF60);
    }
}
