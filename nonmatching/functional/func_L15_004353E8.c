/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* func_L15_004353E8 - opus-1, Claude Opus 5.5 (xhigh), 31 October 2026.
 * Best check.py: 1104/1104 bytes, 0/1 places, 4 lines differ (default -O2 -G0 -ffunction-sections).
 *
 * Still differs: -1 for state+0x458 is in $v1 where retail has $a3, and because of that sched2
 * issues the 0x2C store before the 0x32 store (retail: 0x32, then 0x2C).
 *
 * Closed here: the timer store in the call's delay slot. GI(0x444) has to come after the six
 * final vector stores in the source and before GI(0x440): as the last use of `state` it would
 * carry a second REG_DEAD, which lowers its weight in rank_for_schedule and puts it ahead of them.
 *
 * Ties (same bytes): setup store orders 2C/32/34, 34/32/2C and 0x458 last; -fstrict-aliasing.
 * Worse: `int unset = -1` before the first call (gets $s3, moves the prologue).
 * No gain: `unset = -1` right after func_L05_0037AEC0 (cse/rank leave it at the same place).
 * Next: local-alloc gives $v1 because the constant is born after 0x1FF's store. $a3 needs it to
 * overlap $v1, or to have no hard register and be reloaded. Its rank is low because the 0x458 store
 * only has an anti dependence on the next call.
 *
 * Needs: func_002ED688, func_00283CF0, func_L05_0037AEC0, func_0029FC20, func_00282CF0,
 * func_00282D30, func_L05_00379C68 as declared in L15_004328E8.c.
 */
#include "common.h"

extern int func_002ED688(unsigned char *);
extern int func_00283CF0(float);
extern void func_L05_0037AEC0(char *, int);
extern void func_0029FC20(void *, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_L05_00379C68(int, int);
#define GF(offset) (((GornState *)state)->f[(offset) / 4])
#define GI(offset) (((GornState *)state)->i[(offset) / 4])

/* Measured prefixes with integer/float views of the same game records. */
typedef union { float f[0x660 / 4]; int i[0x660 / 4]; } GornState;
typedef union { float f[0x80 / 4]; unsigned short h[0x80 / 2]; unsigned char b[0x80]; } GornOwnerFields;

void func_L15_004353E8(char *object)
{
    GornOwnerFields *fields = (GornOwnerFields *)object;
    char *state = *(char **)(object + 0x68);
    char *record;
    char *a = state + 0x2B0;
    char *b = state + 0x2F0;
    char *c = state + 0x330;
    char *d = state + 0x370;
    char *e = state + 0x3B0;
    char *f = state + 0x3F0;
    char *position = object + 0x10;
    record = (char *)func_002ED688((unsigned char *)object);
    *(int *)(record + 0x148) = func_00283CF0(150.0f);
    func_L05_0037AEC0(object, 1);
    GF(0x180) = 150.0f;
    *(unsigned short *)(object + 0x32) = 0x1FF;
    *(float *)(object + 0x2C) = 0.675f;
    *(unsigned short *)(object + 0x34) |= 0x100;
    object[0x20] = 1;
    *(unsigned char *)(object + 0x30) = 255;
    *(unsigned short *)(object + 0x7C) = 63;
    GI(0x458) = -1;
    GI(0x268) = 1;
    GI(0x270) = 0;
    GI(0x27C) = 0;
    GI(0x45C) = 0;
    GI(0x278) = 0;
    func_0029FC20(object, 14, state + 0x280);
    func_0029FC20(object, 16, state + 0x2C0);
    func_0029FC20(object, 18, state + 0x300);
    func_0029FC20(object, 15, state + 0x340);
    func_0029FC20(object, 17, state + 0x380);
    func_0029FC20(object, 19, state + 0x3C0);
    func_00282CF0(a, a, position);
    func_00282CF0(d, d, position);
    func_00282CF0(d, d, a);
    func_00282D30(a, a, 1.0f / fields->f[0x2C / 4]);
    func_00282D30(d, d, 1.0f / fields->f[0x2C / 4]);
    func_00282CF0(b, b, position);
    func_00282CF0(e, e, position);
    func_00282CF0(e, e, b);
    func_00282D30(b, b, 1.0f / fields->f[0x2C / 4]);
    func_00282D30(e, e, 1.0f / fields->f[0x2C / 4]);
    func_00282CF0(c, c, position);
    func_00282CF0(f, f, position);
    func_00282CF0(f, f, c);
    func_00282D30(c, c, 1.0f / fields->f[0x2C / 4]);
    func_00282D30(f, f, 1.0f / fields->f[0x2C / 4]);
    func_0029F978((unsigned char *)object, 12, (unsigned char *)(state + 0x460));
    func_0029F978((unsigned char *)object, 13, (unsigned char *)(state + 0x4A0));
    func_0029F978((unsigned char *)object, 14, (unsigned char *)(state + 0x4E0));
    func_0029F978((unsigned char *)object, 15, (unsigned char *)(state + 0x520));
    func_0029F978((unsigned char *)object, 16, (unsigned char *)(state + 0x560));
    func_0029F978((unsigned char *)object, 17, (unsigned char *)(state + 0x5A0));
    func_0029F978((unsigned char *)object, 18, (unsigned char *)(state + 0x5E0));
    func_0029F978((unsigned char *)object, 19, (unsigned char *)(state + 0x620));
    GF(0x510) = GF(0x2B0) * 1024.0f;
    GF(0x514) = GF(0x2B4) * 1024.0f;
    GF(0x518) = GF(0x2B8) * 1024.0f;
    GF(0x550) = GF(0x370) * 1024.0f;
    GF(0x554) = GF(0x374) * 1024.0f;
    GF(0x558) = GF(0x378) * 1024.0f;
    GF(0x590) = GF(0x2F0) * 1024.0f;
    GF(0x594) = GF(0x2F4) * 1024.0f;
    GF(0x598) = GF(0x2F8) * 1024.0f;
    GF(0x5D0) = GF(0x3B0) * 1024.0f;
    GF(0x5D4) = GF(0x3B4) * 1024.0f;
    *(unsigned char *)(state + 0x4E3) = 1;
    *(unsigned char *)(state + 0x523) = 1;
    *(unsigned char *)(state + 0x563) = 1;
    *(unsigned char *)(state + 0x5A3) = 1;
    GF(0x4EC) = 1.0f;
    GF(0x51C) = 1.0f;
    GF(0x52C) = 1.0f;
    GF(0x55C) = 1.0f;
    GF(0x56C) = 1.0f;
    GF(0x59C) = 1.0f;
    GF(0x5AC) = 1.0f;
    GF(0x5D8) = GF(0x3B8) * 1024.0f;
    GF(0x5DC) = 1.0f;
    *(unsigned char *)(state + 0x5E3) = 1;
    GF(0x610) = GF(0x330) * 1024.0f;
    GF(0x614) = GF(0x334) * 1024.0f;
    GF(0x618) = GF(0x338) * 1024.0f;
    GF(0x650) = GF(0x3F0) * 1024.0f;
    GF(0x654) = GF(0x3F4) * 1024.0f;
    GF(0x658) = GF(0x3F8) * 1024.0f;
    *(unsigned char *)(state + 0x623) = 1;
    GF(0x5EC) = 1.0f;
    GF(0x61C) = 1.0f;
    GF(0x62C) = 1.0f;
    GF(0x65C) = 1.0f;
    GI(0x444) = 300;
    GI(0x440) = 0;
    func_L05_00379C68((int)object, 0xFFFF);
    func_L15_003804B8((int)object, (void *)1);
}
