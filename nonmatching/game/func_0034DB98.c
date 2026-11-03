/* Claude Opus 5.5 (v2112), USA v1.01, pinned v2 game -O2 -G8 profile.
 * Retained attempt: 1084/1088 bytes, 0/28 places (check.py --diff).
 * Shape, frame (0xB0) and almost all registers now match. Key changes from
 * the 1076-byte draft: separate counters i/j for the two vtable loops; the
 * single-use giv for the element pointer stays apart from the vtable-slot giv;
 * a long long local truncated to int gives retail's ld/dsll32/dsra32; drawY
 * computed early in the loop; char *t = object + 0x238 in the loop body
 * reproduces retail's gcse copy chain (daddu s4,s0 / daddu s1,s4).
 * Remaining differences:
 * 1. Both vtable calls: retail jalr through v1, ours v0. sched1 gives the
 *    delta load priority 5 and the fn load priority 4, so the delta goes first
 *    and fn reuses the dying vtable register; retail needs the fn load first.
 * 2. Shadow block: retail computes T = color & 0xFF000000 in v1, copies it to
 *    s0 (shadow) before the or. CSE keeps that copy only if the shadow variable
 *    is referenced outside its CSE block (make_regs_eqv). Reusing an earlier
 *    variable reproduces the copy (1088 bytes) but shifts global allocation;
 *    retail's countText in s2 suggests shadow/foreground stay block-local.
 * 3. One instruction short, so the D_001A7A32 branch offset is 0x2A not 0x2B.
 * D_001A7A32 is declared volatile here to get retail's two byte loads; check
 * whether retail rereads it everywhere before keeping that qualifier.
 * D_001A7BB0[4] is the sda block read at offset 4 (cf. 0028BE00-g8.c).
 * The declarations below are sufficient in a standalone -g8.c unit.
 */
#include "include_asm.h"

extern void func_00336320(void *);
extern void func_00336828(void *);
extern void func_00336A78(void *);
extern float *func_00335E18(void *);
extern float *func_00335E10(void *);
extern unsigned int *func_00335E20(void *);
extern void func_0034AD10(void *);
extern unsigned long long func_0027C878(int);
extern void func_0027F640(float, float, unsigned long long, unsigned char *, int, float, unsigned long long, unsigned char *);
extern void func_0027FBD8(int, int, unsigned int, char *, int);
extern int func_00115DA8(char *, const char *, ...);
extern int D_001A8C64[] __attribute__((sda));
extern int D_001A79F8[] __attribute__((sda));
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern volatile unsigned char D_001A7A32[] __attribute__((sda));
extern char D_001AE6F8[], D_001AE700[], D_001AE708[];
extern int D_001ADAE8 __attribute__((sda));
extern int D_001ADAEC __attribute__((sda));
extern unsigned int D_001ADAF0 __attribute__((sda));

void func_0034DB98(void *self)
{
    char *object = self;
    char text[32], countText[16];
    char *left, *right, *e, *vtable;
    float x, y, step;
    unsigned int color, shadow, foreground;
    int i, j, count, n, alternate, yoffset, xoffset;

    func_00336320(object);
    func_00336320(object + 0x4C);
    func_00336320(object + 0x98);
    func_00336828(object + 0x148);
    func_00336A78(object + 0x100);
    if (!D_001A8C64[0]) {
        left = object + 0x2C0;
        right = object + 0x30C;
        func_00336320(left);
        func_00336320(right);
        { float *value = func_00335E18(left); *value = -*value; }
        { float *value = func_00335E18(right); *value = -*value; }
        func_00336320(left);
        func_00336320(right);
        { float *value = func_00335E18(left); *value = -*value; }
        { float *value = func_00335E18(right); *value = -*value; }
        for (i = 0; i < 8; i++) {
            vtable = *(char **)(object + 0x358 + i * 0x4C + 0x30);
            e = object + 0x358 + i * 0x4C;
            (*(void (**)(void *))(vtable + 12))(e + *(short *)(vtable + 8));
        }
        for (j = 0; j < 8; j++) {
            vtable = *(char **)(object + 0x604 + j * 0x3C + 0x30);
            e = object + 0x604 + j * 0x3C;
            (*(void (**)(void *))(vtable + 12))(e + *(short *)(vtable + 8));
        }
        func_00336320(object + 0x5B8);
        *func_00335E20(object + 0x5B8) = 0x70FFFEED;
    }
    func_00336320(object + 0x184);
    func_00336320(object + 0x1D0);
    func_00336A78(object + 0x238);
    func_00336828(object + 0x280);
    x = func_00335E10(object + 0x238)[0];
    y = func_00335E10(object + 0x238)[1];
    x += 32.0f;
    y += -10.0f;
    color = *func_00335E20(object + 0x238);
    count = 1;
    n = D_001A79F8[0];
    while (n >= 10) { n /= 10; count++; }
    alternate = D_001A7BB0[4] != 3 && D_001A7BB0[4] != 5;
    func_00115DA8(text, alternate ? D_001AE6F8 : D_001AE700);
    yoffset = alternate ? 21 : 10;
    xoffset = alternate ? -34 : -29;
    for (step = 3.0f; step < count; step += 3.0f) {
        float drawX = x + xoffset - (int)(step * 11.6f);
        float drawY = y + yoffset;
        char *t = object + 0x238;
        float *scale = func_00335E18(t);
        long long tex = *(long long *)(t + 0x38);
        unsigned long long texture = func_0027C878(tex);
        func_0027F640(drawX, drawY, color, (unsigned char *)text, -1, *scale, texture, *(unsigned char **)(t + 0x34));
    }
    if (D_001A7A32[0] >= 2) {
        func_00115DA8(countText, D_001AE708, D_001A7A32[0]);
        shadow = color & 0xFF000000;
        foreground = (D_001ADAF0 & 0xFFFFFF) | (color & 0xFF000000);
        func_0027FBD8(D_001ADAE8, D_001ADAEC + 2, shadow, countText, -1);
        func_0027FBD8(D_001ADAE8 + 2, D_001ADAEC, shadow, countText, -1);
        func_0027FBD8(D_001ADAE8 + 2, D_001ADAEC + 2, shadow, countText, -1);
        func_0027FBD8(D_001ADAE8, D_001ADAEC, foreground, countText, -1);
    }
    func_0034AD10(object + 0x7E8);
}
