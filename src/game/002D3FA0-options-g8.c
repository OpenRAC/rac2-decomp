/* func_002D3FA0 (2,468 bytes, 28 places): the options page with three rectangles and labels.
 * Own unit: -O2 -G8 -ffunction-sections -fno-gcse -frac2-frame-pointer-liveness -frac2-la-fp-const-first
 * (config/cflags.txt; docs/build/compiler-notes.md). Rectangle 2's two y values go through
 * hud_coord5, the dead-test rounding helper with five tests: cse follows at most 9 jumps per
 * path, so the colour copy cC survives to the call as retail. A compiler rule was tried first
 * (cse path length, copy-variable merges, argument-source rules) and did not close it; the
 * helper is allowed by owner ruling, 13 November 2026. y3 uses label_y3 on (void *)e.
 */
#include "include_asm.h"
typedef struct { char pad[0x1CC]; unsigned char *entries; int count; int timer; } MenuEntryState;
extern MenuEntryState D_001F2840;
typedef struct {
    int value, displayChoice, selectionMask, requiredBits, icon;
} PreviewChoice;
extern PreviewChoice D_0026CFD0[];
extern unsigned int D_001A7AF0[] __attribute__((sda));
extern int D_001ABA74 __attribute__((sda));
extern int D_001A7340[] __attribute__((sda)), D_001A7344[] __attribute__((sda));
extern float D_001B23A4[] __attribute__((sda));
typedef struct { unsigned char bytes[16]; } MenuCorners;
extern MenuCorners D_001ABA78;
extern char D_001AB998[];
extern int func_002A9588(int, int, int, int, int);
extern int func_00336D50(char *, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern int func_0028E588(int, int);
extern void func_0028EA58(int, int, int, int, int, MenuCorners *);
extern void func_0028E868(int, int, int, int, int, int);
extern char *func_00288FB8(int);
extern int func_0027FB40(int, int, unsigned long long, char *, int);
extern int func_0027FAA8(int, int, unsigned long long, char *, int);
extern int func_00115DA8(char *, char *, ...);
extern int func_002D3D88(int, int);
extern void func_002FC620(int, int, int, int);
extern void func_002A0250(void), func_002A01C8(void), func_002A01F0(void);
extern void func_002A0300(char *, int), func_002A0220(void), func_002A0380(void);
extern void func_002ECB70(char *);
extern void func_0027C540(int), func_0027C660(void);
extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001B23A0;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;
    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int label_y2(void *handle, float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;
    if (mode == active)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_coord5(float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;
    if (mode == active)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    copy = result;
    if (copy != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int label_y3(void *handle, float value, float scale, float half, int active)
{
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;
    int mode;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    mode = D_001B23A0;
    if (mode == active)
        scaled = scale;
    return result;
}
int func_002D3FA0(void)
{
    MenuCorners corners = D_001ABA78;
    char text[32];
    int color = func_002A9588(0x60241700, 0x55F0C070, 30, 0, 0);
    int x, index, i;
    char *first, *second;
    int t, r, e;
    int y1, y2, y3;
    int on2 = 1, on3 = 1;
    int one = 1;
    int one2 = 1;
    int one3 = 1;
    int ya, yb;
    unsigned long cB;
    unsigned long cC;
    float px, py;
    func_0027C540(0);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD0), 0x60442D00, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD1), 0x60241700, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD2), 0x55F0C070, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD3), 0x55F0C070, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    ya = hud_coord(326.0f, D_001B23A4[0], 0.5f, one);
    yb = hud_coord(387.0f, D_001B23A4[0], 0.5f, one);
    cB = color;
    cC = cB;
    func_0028FC48(228, ya, 230, yb, cB, 0);
    func_0028FC48(286, hud_coord5(326.0f, D_001B23A4[0], 0.5f, one), 288, hud_coord5(387.0f, D_001B23A4[0], 0.5f, one), cC, 0);
    func_0028FC48(228, hud_coord(325.0f, D_001B23A4[0], 0.5f, one), 288, hud_coord(327.0f, D_001B23A4[0], 0.5f, one), cC, 0);
    func_0028FC48(228, hud_coord(386.0f, D_001B23A4[0], 0.5f, one2), 288, hud_coord(388.0f, D_001B23A4[0], 0.5f, one2), cB, 0);
    t = func_0028E588(0xEAA8, 0); func_0028EA58(t, 16, label_y((void *)t, 36.0f, D_001B23A4[0], 0.5f, one2), 192, label_y((void *)t, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    t = func_0028E588(0xEAA8, 0); func_0028EA58(t, 400, label_y((void *)t, 36.0f, D_001B23A4[0], 0.5f, one2), -192, label_y((void *)t, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    t = func_0028E588(0xEAA8, 0); func_0028EA58(t, 16, label_y((void *)t, 228.0f, D_001B23A4[0], 0.5f, one2), 192, -label_y((void *)t, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    t = func_0028E588(0xEAA8, 0); func_0028EA58(t, 400, label_y((void *)t, 228.0f, D_001B23A4[0], 0.5f, one2), -192, -label_y((void *)t, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    t = func_0028E588(0xEAA8, 1); func_0028E868(t, 402, label_y((void *)t, 50.0f, D_001B23A4[0], 0.5f, one2), 89, label_y((void *)t, 115.0f, D_001B23A4[0], 0.5f, one2), 64);
    y1 = hud_coord(116.0f, D_001B23A4[0], 0.5f, one2);
    e = func_0027FB40(445, y1, 0x80F0F0F0ULL, func_00288FB8(0x3212), -1);
    y2 = hud_coord(134.0f, D_001B23A4[0], 0.5f, one2);
    e = func_0027FB40(445, y2, 0x80F0F0F0ULL, func_00288FB8(0x3213), -1);
    e = func_00115DA8(text, D_001AB998, func_00288FB8(0x3213), func_00288FB8(0x2D55));
    e = func_0027FAA8(159, hud_coord(18.0f, D_001B23A4[0], 0.5f, on3), 0x80F0F0F0ULL, text, -1);
    do {
    y3 = label_y3((void *)e, 187.0f, D_001B23A4[0], 0.5f, on3);
    } while (0);
    r = func_0027FAA8(445, y3, 0x80F0F0F0ULL, func_00288FB8(0x2D4F), -1);
    x = 235;
    for (i = 0; i < 12; i++) {
        index = D_001ABA74 - i;
        if (index >= 0 && index < 12) {
            while (index >= 0) {
                if ((D_001A7AF0[0] & D_0026CFD0[index].selectionMask) == D_0026CFD0[index].requiredBits)
                    break;
                index--;
                i++;
            }
            if (index < 0)
                continue;
            func_002D3D88(index, x);
        }
        x -= 56;
    }
    x = 291;
    for (i = 1; i < 12; i++) {
        index = D_001ABA74 + i;
        if (index >= 0 && index < 12) {
            while (index < 12) {
                if ((D_001A7AF0[0] & D_0026CFD0[index].selectionMask) == D_0026CFD0[index].requiredBits)
                    break;
                index++;
                i++;
            }
            if (index >= 12)
                continue;
            func_002D3D88(index, x);
        }
        x += 56;
    }
    func_0027C660();
    func_002FC620(30, 385, label_y2((void *)r, 50.0f, D_001B23A4[0], 0.5f, on2), label_y((void *)i, 213.0f, D_001B23A4[0], 0.5f, on3));
    func_002A0250();
    func_002A01C8();
    func_002A01F0();
    func_002A0300(D_001F2840.entries, D_001F2840.count);
    func_002A0220();
    func_002A0380();
    func_0027C540(0);
    func_002ECB70(D_001F2840.entries);
    func_0027C660();
    func_002FC620(0, D_001A7340[0] - 1, 0, D_001A7344[0] - 1);
    return 0;
}
