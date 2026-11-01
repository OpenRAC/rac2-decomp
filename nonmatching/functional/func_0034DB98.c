/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, USA v1.01, pinned v2 game -O2 -G8 profile.
 * Retained attempt: 1076/1088 bytes, 0/28 places (check.py --diff).
 * Advancing the first array's completed object/vtable cursors by 0x4C
 * reaches the second array without hoisting its two bases. This recovers
 * retail's 0xB0 frame and seven saved GPRs, versus the old draft's 0xC0
 * frame and nine saved GPRs. Registers still differ; retail derives the
 * second pair from the owner instead of the completed first pair.
 * Other differences: count-to-float conversion moves before sprintf;
 * the font lookup narrows the text object's +0x38 field load to lw instead of
 * retail's ld followed by sign extension of its low word. Its complete
 * storage contract needs independent evidence before adding qualifiers.
 * Typed array records retain the old 1100-byte result. Indexed loops
 * collapse the two induction pointers (1048 bytes). A bounded
 * -fno-sched-interblock probe retains 1100 bytes and does not cure hoisting.
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
extern void *func_0027C878(long long);
extern void func_0027F640(unsigned long long, char *, int, void *, int, float, float, float);
extern void func_0027FBD8(int, int, unsigned int, char *, int);
extern int func_00115DA8(char *, const char *, ...);
extern int D_001A8C64[] __attribute__((sda));
extern int D_001A79F8[] __attribute__((sda));
extern unsigned char D_001A7BB4[] __attribute__((sda));
extern volatile unsigned char D_001A7A32[] __attribute__((sda));
extern char D_001AE6F8[], D_001AE700[], D_001AE708[];
extern int D_001ADAE8 __attribute__((sda));
extern int D_001ADAEC __attribute__((sda));
extern unsigned int D_001ADAF0 __attribute__((sda));

void func_0034DB98(char *object)
{
    char text[32], countText[16];
    char *left, *right, *p, *vtable, *final, *textObject;
    char *cursor;
    float *scale;
    float x, y, step, digits;
    unsigned int color, shadow, foreground;
    int i, count, n, alternate, yoffset, xoffset;

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
        {
        p = object + 0x358;
        cursor = p + 0x30;
        for (i = 7; i >= 0; i--, p += 0x4C, cursor += 0x4C) {
            vtable = *(char **)cursor;
            (*(void (**)(void *))(vtable + 12))(p + *(short *)(vtable + 8));
        }
        }
        {
        p += 0x4C;
        cursor += 0x4C;
        for (i = 7; i >= 0; i--, p += 0x3C, cursor += 0x3C) {
            vtable = *(char **)cursor;
            (*(void (**)(void *))(vtable + 12))(p + *(short *)(vtable + 8));
        }
        }
        func_00336320(object + 0x5B8);
        *func_00335E20(object + 0x5B8) = 0x70FFFEED;
    }
    func_00336320(object + 0x184);
    func_00336320(object + 0x1D0);
    textObject = p = object + 0x238;
    final = object + 0x7E8;
    func_00336A78(p);
    func_00336828(object + 0x280);
    x = func_00335E10(p)[0];
    y = func_00335E10(p)[1];
    x += 32.0f;
    y += -10.0f;
    color = *func_00335E20(p);
    count = 1;
    n = D_001A79F8[0];
    while (n >= 10) { n /= 10; count++; }
    alternate = D_001A7BB4[0] != 3 && D_001A7BB4[0] != 5;
    step = 3.0f;
    func_00115DA8(text, alternate ? D_001AE6F8 : D_001AE700);
    digits = (float)count;
    yoffset = alternate ? 21 : 10;
    xoffset = alternate ? -34 : -29;
    if (step < digits) {
        float start = x + (float)xoffset;
        p = textObject;
        do {
            float drawX = start - (float)(int)(step * 11.6f);
            step += 3.0f;
            scale = func_00335E18(p);
            func_0027F640((unsigned long long)color, text, -1, func_0027C878((long long)(int)*(long long *)(p + 0x38)),
                         *(int *)(p + 0x34), drawX, y + (float)yoffset, *scale);
        } while (step < digits);
    }
    if (D_001A7A32[0] >= 2) {
        func_00115DA8(countText, D_001AE708, D_001A7A32[0]);
        foreground = (D_001ADAF0 & 0xFFFFFF) | (color & 0xFF000000);
        shadow = color & 0xFF000000;
        func_0027FBD8(D_001ADAE8, D_001ADAEC + 2, shadow, countText, -1);
        func_0027FBD8(D_001ADAE8 + 2, D_001ADAEC, shadow, countText, -1);
        func_0027FBD8(D_001ADAE8 + 2, D_001ADAEC + 2, shadow, countText, -1);
        func_0027FBD8(D_001ADAE8, D_001ADAEC, foreground, countText, -1);
    }
    func_0034AD10(final);
}
