#include "common.h"

/* func_US2_002D4ED8, the v2.00 copy of func_002D3FA0: draws the preview menu (four logo
   sprite layers, the frame rectangles and corners, the header text and the two rows of
   choice icons, func_US2_002D4D38 for each unlocked choice either side of D_001ABA74), then
   renders the preview model. v2.00 drops the display scaling of every coordinate, reads the
   logo layers' scale from D_001B2688 and uses text 0x30A8/0x30A9 and 0x2BE5.

   Each logo layer is drawn by the inline draw_logo: its inlined copies keep their own 1.0
   argument, rematerialised before each call as in retail, while the shared 0x8710 offset and
   the 0.0 local each stay in one saved register. The default profile (expensive
   optimizations on) gives the choice loops' pointer start its separate temporary. */

typedef struct { char pad[0x1CC]; unsigned char *entries; int count; int timer; } MenuEntryState;
typedef struct {
    int value, displayChoice, selectionMask, requiredBits, icon;
} PreviewChoice;
typedef struct { unsigned char bytes[16]; } MenuCorners;

extern MenuEntryState D_001F2840;
extern PreviewChoice D_0026CFD0[];
extern unsigned int D_001A7AF0[] __attribute__((sda));
extern int D_001ABA74 __attribute__((sda));
extern int D_001ABA80 __attribute__((sda));
extern int D_001A7340[] __attribute__((sda)), D_001A7344[] __attribute__((sda));
extern float D_001B2688[] __attribute__((sda));
extern MenuCorners D_001ABA78;
extern char D_001ABC78[];
extern char *D_001A8CFC[] __attribute__((sda));
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
extern int func_US2_002D4D38(int, int);
extern void func_002FC620(int, int, int, int);
extern void func_002A0250(void), func_002A01C8(void), func_002A01F0(void);
extern void func_002A0300(char *, int), func_002A0220(void), func_002A0380(void);
extern void func_002ECB70(char *);
extern void func_0027C540(int), func_0027C660(void);

static __inline__ void draw_logo(int id, int color, float zero)
{
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, id), color, (float)(D_001A7340[0] / 2), (float)(D_001ABA80 / 2), 1.0f, D_001B2688[0], zero);
}

int func_US2_002D4ED8(void)
{
    MenuCorners corners = D_001ABA78;
    char text[32];
    int color = func_002A9588(0x60241700, 0x55F0C070, 30, 0, 0);
    int x, index, i;
    char *fmt;
    float z;

    z = 0.0f;
    func_0027C540(0);
    draw_logo(0xD0, 0x60442D00, z);
    draw_logo(0xD1, 0x60241700, z);
    draw_logo(0xD2, 0x55F0C070, z);
    draw_logo(0xD3, 0x55F0C070, z);
    func_0028FC48(228, 326, 230, 387, color, 0);
    func_0028FC48(286, 326, 288, 387, color, 0);
    func_0028FC48(228, 325, 288, 327, color, 0);
    func_0028FC48(228, 386, 288, 388, color, 0);
    func_0028EA58(func_0028E588(0xEAA8, 0), 16, 36, 192, 96, &corners);
    func_0028EA58(func_0028E588(0xEAA8, 0), 400, 36, -192, 96, &corners);
    func_0028EA58(func_0028E588(0xEAA8, 0), 16, 228, 192, -96, &corners);
    func_0028EA58(func_0028E588(0xEAA8, 0), 400, 228, -192, -96, &corners);
    func_0028E868(func_0028E588(0xEAA8, 1), 402, 50, 89, 115, 64);
    func_0027FB40(445, 116, 0x80F0F0F0ULL, func_00288FB8(0x30A8), -1);
    func_0027FB40(445, 134, 0x80F0F0F0ULL, func_00288FB8(0x30A9), -1);
    fmt = D_001ABC78;
    func_00115DA8(text, fmt, func_00288FB8(0x30A9));
    func_0027FAA8(159, 18, 0x80F0F0F0ULL, text, -1);
    func_0027FAA8(445, 187, 0x80F0F0F0ULL, func_00288FB8(0x2BE5), -1);
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
            func_US2_002D4D38(index, x);
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
            func_US2_002D4D38(index, x);
        }
        x += 56;
    }
    func_0027C660();
    func_002FC620(30, 385, 50, 213);
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
