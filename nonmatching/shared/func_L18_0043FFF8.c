/* 8 November 2026, twin search: transcribing matched twin func_L09_003AE8C8 (its unit flags -O2 -G8 -ffunction-sections -g; state loaded first, byte 255 then signed short 256) adds nothing: the twin has no halfword 255 at 0x32, and its retail stores the byte first. All six orders of the three header stores in that spelling give 5 rows or more (best 0x34, 0x30, 0x32: byte constant still lands in $v0, not $a0); one-pass groups around each store and an int 255 local give 5 rows or worse. */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss. Final state: exact (3/3 in us, us2, pal) only with a one-field struct local that keeps cse from merging two 255 constants; the owner ruled that construct out, so it stays a held near miss. */
/* 6 November 2026, round 9: exact (3/3 in us, us2, pal; own -O2 -G0 -ffunction-sections -g unit) when the byte flag at 0x30 is stored from a local `struct { unsigned short value; } mark` set to 255 before the 0x34 store and the halfword at 0x32 from an `int half = 255` after it: cse2 then keeps the two 255 constants apart as retail does. A plain `unsigned short mark` gives 0/3. Held, not landed: the one-field struct exists only to steer cse, so it needs a maintainer ruling (compare blocker 26). */
/* 6 November 2026, round 3: unchanged, 488/488 bytes, 0/3 places, 5 rows.
 * All 120 orders of the three header stores, the state load and the 0x20 store,
 * with and without -frac2-qcopy, give 5 rows or more. sched1 issues two ALU
 * insns per cycle; the three constants tie on priority, so luid order decides,
 * and stores follow the same order. Retail needs the byte constant first but
 * the 0x34 store first: that needs a priority difference no plain store gives.
 * A byte local set before the stores merges with the halfword 255 (484 bytes).
 */
/* 6 November 2026: current game compiler, -O2 -G0 -ffunction-sections -g:
 * 488/488 bytes, 0/3 places in each release; five flag setup words remain.
 * New one-pass groups around individual/adjacent header writes either tie
 * or worsen the constant/store order. Grouped byte-constant initialization,
 * before or inside the null guard with char/int locals, also does not improve.
 * Retain the existing C; reopen with a measured constant lifetime explanation.
 */
/* 6 November 2026: on the current compiler, still 5 rows. Retail makes the byte 255, then 0x100,
 * then the halfword 255, but stores +0x34, +0x30, +0x32. Signed short stores in that store order
 * (as matched spawners write them) give 5 rows; the +0x30/+0x34/+0x32 order gives retail's
 * constant order but 6 rows; a struct view of the header ties; without -g about 43 rows differ. */
/* 5 November 2026: Scoped byte/word flag locals merge constants and give 484/488 bytes. Grouping the real header writes keeps 488 bytes but the same five flag constant/store words still differ. No variant is promoted.
 */
/* Retained nonmatching reconstruction, 27 October 2026.
 * Profile: -O2 -G0 -ffunction-sections -g. Candidate and retail: 488 bytes. USA v1.01, USA v2.00 and PAL each reject all three carrying places. Only five initial flag constant/store words differ: the byte and halfword 255 constants take different registers/order. The later spawn, vector operations, division hazards, stores and return agree. Reordering the stores either changes their order or merges the constants. A separately tested partial object-header view tied. Reopen with a measured allocation explanation; no volatile or artificial dependencies.
 */
#include "common.h"
extern void *func_0029EFD0(int);
extern float func_00283248(float, float);
extern float func_00282E20(void *);
extern char *func_L09_003364E0(char *, int, unsigned int, int, float, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern int func_002E5CF8(int, int, char *);
extern char D_0018A0E0[];
char *func_L18_0043FFF8(void *position, char *owner, float *direction,
                       int kind, int flags, float x, float y, float z)
{
    char *object = func_0029EFD0(0x1263);
    char *state;
    float angle;
    int lifetime;
    if (object) {
        *(unsigned short *)(object + 0x34) = 0x100;
        ((unsigned char *)object)[0x30] = 255;
        *(unsigned short *)(object + 0x32) = 255;
        state = *(char **)(object + 0x68);
        object[0x20] = 0;
        qcopy(state, direction);
        qcopy(object + 0x10, position);
        *(float *)(object + 0xf8) = func_00283248(direction[0], direction[1]);
        angle = func_00282E20(direction);
        *(float *)(object + 0xf4) = -func_00283248(angle, direction[2]);
        *(char **)(state + 0x30) = func_L09_003364E0(object, -1, 0xf0208080, 0x60, 0.1f, 0.01f);
        *(float *)(state + 0x1c) = y;
        qcopy(object + 0xc0, state);
        func_00282DD8(object + 0xd0, object + 0xc0, D_0018A0E0);
        func_00282F20(object + 0xd0, object + 0xd0, -1.0f);
        func_00282DD8(object + 0xe0, object + 0xd0, object + 0xc0);
        angle = func_00282DF0(direction);
        angle = *(float *)(state + 0x1c) / angle;
        lifetime = func_00283CF0(angle);
        *(float *)(state + 0x24) = z;
        *(int *)(state + 0x34) = lifetime;
        *(float *)(state + 0x20) = x;
        *(int *)(state + 0x28) = kind;
        *(int *)(state + 0x2c) = flags;
        *(char **)(state + 0x10) = owner;
        if (*(short *)(owner + 0xaa) == 0xee1)
            func_002E5CF8(5, 0, owner);
        object[0x31] = 0;
        *(unsigned short *)(object + 0x34) |= 1;
    }
    return object;
}
