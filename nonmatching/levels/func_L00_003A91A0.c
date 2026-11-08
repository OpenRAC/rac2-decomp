/* Nonmatching C, updated 8 November 2026 (clean rewrite from retail asm); not a linked match.
 * Same family as func_L00_003F6308: identical opcodes, only data addresses and the 0x5CB/0xC04 id differ;
 * this body ports to the twin by renaming the globals (+0x1228) and the vertex table.
 * Profile: -O2 -G8 -ffunction-sections; place it in the unit's -g8.c sibling (the plain unit is -G0).
 * 1524/1524 bytes; tools/check.py 0 of 27; 37 of 381 instructions differ (was 57).
 * Reached: frame, loop shapes, the second ring loop's strength reduction (its outer counter must be
 * the first loop's inner counter: otherwise gcse PRE hoists counter+1 and kills the biv), float
 * registers and store order of the ribbon loop.
 * Remaining (before the second 8 November round below): (1) spill-slot order 0x4BC-0x4D8: retail spills {0x30, 0x490, ring+1, 0x4A0} in an
 * earlier reload round than {0x10, 0xC0, 0x20, 0xD0}; here all eight go in one round (slots follow
 * the PRE regno order, which follows the expression hash order). (2) combine merges the
 * func_00283CF0 return copy into the `sll 24`, so the shift sticks to the call; retail keeps the
 * copy and shifts into $v1 later. (3) the two strip loops build origin[j+1] as fp+(i*0x60+0x10)
 * instead of (fp+i*0x60)+0x10.
 * Tried without gain: -fno-gcse (1576 bytes), -fmove-all-movables, -fno-schedule-insns, -fno-sched-interblock,
 * j from 1 in the strip loops, a cursor pointer, narrow alpha types, do/while(0) groups around the shift.
 * 8 November 2026 round (no gain, still about 56 differ): origin[j+1] as (&rings[i])->origin[j+1],
 * (origin+1)[j], a byte-offset row pointer (all unchanged), a BeamRing *r local (1504 bytes), a second
 * counter from 1 (1568 bytes); return value kept apart: alpha as char/short/long/float, an inline
 * colour helper (value or pointer argument), primary computed after the uv stores, hill-climbs over the
 * sec3/sec4 prologue order. Combine still merges the return copy into the sll every time.
 * 8 November 2026, second round: FIXED (2): the shift goes into the call's own statement,
 * `alpha = func_00283CF0(...) << 24; primary = alpha | col;` (alpha is one variable over three blocks,
 * so it is a global pseudo and the sll writes $v1 as in retail): 57 -> 37 differ, ported to the twin.
 * Left: (1) slot order (30 instructions) and (3) the strip-loop origin adds (6).
 * Findings for (1): gcse's expression table has 175 buckets here (n_insns/2|1), and retail's two
 * groups {0x90,0xB0,0x30,0x490,0x4A0} and {0x10,0xC0,0x20,0xD0} are each in this same bucket order,
 * so retail's split is a second reload round (that group was allocated, then evicted), not a hash
 * change; -fno-caller-saves and -g leave this body unchanged. Lesson 42 named locals do take slots in
 * declaration order (m0,m2,p3,tp,nr,sd,p1,m3,p2 gave retail's 0x4B0-0x4D0 order), but a named temp,
 * side or vertices pointer gets a callee-saved register, so rings loses $fp and the row/strip loops
 * lose their copies (s6 = temp, s4 = side): 1504-1528 bytes, about 300 differ. Also no gain for (3):
 * origin[j] + 4, (rings + ring)->, origin[1] + j * 4 (unchanged), a block BeamRing *r or a block
 * `BeamVector *next = origin + 1` (hoisted by cse, 1504/1528 bytes), an inline strip helper (quad
 * goes into a register, 1504 bytes); -frac2-qcopy with TImode assignments (1500/1508 bytes).
 */
#include "common.h"

typedef float BeamVector[4] __attribute__((aligned(16)));
typedef struct { BeamVector point[4]; u32 color[4]; float uv[4][2]; long a,b,c,d; } BeamQuad;
typedef struct { BeamVector origin[3], basis[2]; short enabled, timer; float phase, phase2, rate; } BeamRing;
extern float D_L00_001AF75C __attribute__((sda));
extern float D_L00_001AF754 __attribute__((sda));
extern float D_L00_001AF758 __attribute__((sda));

extern float D_L00_001AF778 __attribute__((sda));
extern float D_L00_001AF788 __attribute__((sda));
extern u32 D_L00_001AF78C __attribute__((sda));
extern int D_L00_001AF794 __attribute__((sda));
extern float D_L00_001AF798 __attribute__((sda));
extern float D_L00_001AF7A4 __attribute__((sda));
extern int D_L00_001AF76C __attribute__((sda));
extern int D_L00_001AF784 __attribute__((sda));

extern u32 D_L00_001AF764 __attribute__((sda));
extern u32 D_L00_001AF768 __attribute__((sda));
extern u32 D_L00_001AF780 __attribute__((sda));
extern u32 D_L00_001AF77C __attribute__((sda));
extern u32 D_L00_001AF790 __attribute__((sda));
extern BeamVector D_L00_00294B60[];
extern BeamVector D_L00_001B8DC0;
extern char *func_L00_0032A088(int, int);
extern int *func_L00_0032A0B8(int, int);
extern void func_00281DE8(void *, int, int, int);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283CF0(float);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);


void func_L00_003A91A0(unsigned char *object)
{
    BeamQuad quad;
    BeamVector matrix[4];
    BeamVector vertices[3][20];
    BeamVector temp, side;
    unsigned char *vars = *(unsigned char **)(object + 0x68);
    char *base = func_L00_0032A088(0x5cb, *(short *)(vars + 0x1a));
    BeamRing *rings = (BeamRing *)(base + *func_L00_0032A0B8(0x5cb, *(short *)(vars + 0x1a)));
    int ring, row, j;
    u32 primary, col, alpha;
    float side_u, fade, phase, u, next, phase2;

    func_00281DE8(&quad, 21, 0, 128);
    for (ring = 0; ring < 3; ring++) {
        if (rings[ring].enabled == 0) continue;
        qcopy(matrix[0], rings[ring].basis[0]);
        qcopy(matrix[2], rings[ring].basis[1]);
        func_00282DD8(matrix[1], matrix[0], matrix[2]);
        fade = (float)rings[ring].timer * rings[ring].rate;
        alpha = func_00283CF0(fade * (float)D_L00_001AF76C) << 24;
        col = D_L00_001AF764;
        primary = alpha | col;
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = primary;
        for (row = 0; row < 3; row++) {
            qcopy(matrix[3], rings[ring].origin[row]);
            for (j = 0; j < 20; j++) {
                func_00282D30(temp, D_L00_00294B60[j], D_L00_001AF75C);
                func_002830C0(vertices[row][j], temp, matrix);
            }
        }
        phase = rings[ring].phase;
        col = D_L00_001AF768;
        for (j = 1; j < 3; j++) {
            u = 0;
            for (row = 0; row < 20; row++) {
                qcopy(quad.point[0], vertices[j][row]);
                qcopy(quad.point[1], vertices[j][(row + 1) % 20]);
                qcopy(quad.point[2], vertices[j - 1][row]);
                qcopy(quad.point[3], vertices[j - 1][(row + 1) % 20]);
                next = u + D_L00_001AF758;
                side_u = phase + D_L00_001AF754;
                quad.color[3] = quad.color[2] = col;
                quad.uv[0][0] = phase;
                quad.uv[0][1] = u;
                quad.uv[1][0] = phase;
                quad.uv[1][1] = next;
                quad.uv[2][0] = side_u;
                quad.uv[2][1] = u;
                quad.uv[3][0] = side_u;
                quad.uv[3][1] = next;
                u = next;
                func_00280B90(&quad, 0, 0);
            }
            col = primary;
        }
        func_00281DE8(&quad, 14, 1, 128);
        alpha = func_00283CF0(fade * (float)D_L00_001AF784) << 24;
        col = D_L00_001AF780;
        quad.uv[0][0] = 0;
        quad.uv[0][1] = 0;
        quad.uv[1][0] = 0;
        quad.uv[1][1] = 1;
        quad.uv[2][1] = 0;
        quad.uv[3][1] = 1;
        primary = alpha | col;
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = primary;
        quad.uv[3][0] = 0.5f;
        quad.uv[2][0] = 0.5f;
        col = D_L00_001AF77C;
        func_00282CF0(temp, &D_L00_001B8DC0, rings[ring].origin[0]);
        func_00282DD8(matrix[1], matrix[0], temp);
        func_00282F20(side, matrix[1], D_L00_001AF778);
        for (j = 0; j < 2; j++) {
            func_00282CC0(quad.point[0], rings[ring].origin[j + 1], side);
            func_00282CF0(quad.point[1], rings[ring].origin[j + 1], side);
            func_00282CC0(quad.point[2], rings[ring].origin[j], side);
            func_00282CF0(quad.point[3], rings[ring].origin[j], side);
            quad.color[3] = quad.color[2] = col;
            func_00280B90(&quad, 0, 0);
            col = primary;
            quad.uv[0][0] = quad.uv[1][0] = quad.uv[2][0];
            quad.uv[2][0] = quad.uv[3][0] = 3.0f;
        }
        func_00281DE8(&quad, 23, 1, 128);
        alpha = func_00283CF0(fade * (float)D_L00_001AF794) << 24;
        col = D_L00_001AF790;
        primary = alpha | col;
        quad.uv[2][0] = 1;
        quad.uv[3][0] = 1;
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = primary;
        quad.uv[0][0] = 0;
        quad.uv[0][1] = 0;
        quad.uv[1][0] = 0;
        quad.uv[1][1] = 1;
        quad.uv[2][1] = 0;
        quad.uv[3][1] = 1;
        phase2 = rings[ring].phase2;
        quad.uv[2][0] = quad.uv[3][0] = phase2 + 0.5f;
        col = D_L00_001AF78C;
        func_00282F20(side, matrix[1], D_L00_001AF788);
        for (j = 0; j < 2; j++) {
            func_00282CC0(quad.point[0], rings[ring].origin[j + 1], side);
            func_00282CF0(quad.point[1], rings[ring].origin[j + 1], side);
            func_00282CC0(quad.point[2], rings[ring].origin[j], side);
            func_00282CF0(quad.point[3], rings[ring].origin[j], side);
            quad.color[3] = quad.color[2] = col;
            func_00280B90(&quad, 0, 0);
            col = primary;
            quad.uv[0][0] = quad.uv[1][0] = quad.uv[2][0];
            quad.uv[2][0] = quad.uv[3][0] = phase2 + 3.0f;
        }
    }
}
