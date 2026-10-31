#include "include_asm.h"

typedef struct {
    int active;
    int timer;
    int unk08;
    int unk0C;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
    int entryIndex;
    int unk24;
    char pad28[8];
    int unk30;
    char pad34[0xC];
    int unk40;
    int unk44;
} SubtitleState;

typedef struct { int unk00; int unk04; int id; int unk0C; } TextEntry;

extern SubtitleState D_00254E78;
extern TextEntry *D_001B1840 __attribute__((sda));
extern void func_00289AA0(void);

extern volatile unsigned short D_001A7B94 __attribute__((sda));
extern volatile unsigned char D_001A7B95 __attribute__((sda));
extern void func_0027EB88(int, int, int, int, int, int);
extern void func_0029B658(int, int, float, float, float, float);
extern void func_002802E0(unsigned short *, int, int, int, int, int, int, int, int);
extern void func_00280200(unsigned short *, int, char *, int);

/* Draws the subtitle box for the current state: it opens (1), grows (3), shows the text
   fading in or out (4 to 6) and shrinks (7). */
void func_00289AA8(void)
{
    if (--D_00254E78.unk44 < 0)
        D_00254E78.unk44 = 0;
    if (D_00254E78.unk44 == 0)
        D_00254E78.unk40 = 0;
    if (D_00254E78.active == 0 || D_00254E78.unk30 == 0 || D_001A7B94 == 0)
        return;

    switch (D_00254E78.active) {
    case 1:
        if (D_001A7B95 != 0) {
            D_00254E78.unk18 = 8;
            D_00254E78.unk1C = 8;
            func_0027EB88(D_00254E78.unk14 - D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk14 + D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk10 - D_00254E78.unk18, D_00254E78.unk10 + D_00254E78.unk18,
                          0x60, 0x60442D00);
            func_0029B658(0x60, 0x55F0C070,
                          D_00254E78.unk14 - D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk14 + D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk10 - D_00254E78.unk18, D_00254E78.unk10 + D_00254E78.unk18);
        } else {
            func_00289AA0();
        }
        break;
    case 2:
        func_00289AA0();
        break;
    case 3:
        if (D_001A7B95 != 0) {
            int t = D_00254E78.timer;

            if (t > 8)
                t = 8;
            if (t < 0)
                t = 0;
            D_00254E78.unk18 = (D_00254E78.unk08 - 32) * t / 8 + 32;
            D_00254E78.unk1C = (D_00254E78.unk0C - 32) * t / 8 + 32;
            func_0027EB88(D_00254E78.unk14 - D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk14 + D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk10 - D_00254E78.unk18, D_00254E78.unk10 + D_00254E78.unk18,
                          0x60, 0x60442D00);
            func_0029B658(0x60, 0x55F0C070,
                          D_00254E78.unk14 - D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk14 + D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk10 - D_00254E78.unk18, D_00254E78.unk10 + D_00254E78.unk18);
        } else {
            func_00289AA0();
        }
        break;
    case 4:
    case 5:
    case 6:
        if (D_001A7B95 != 0) {
            unsigned short layout[16];
            int color = 0x80FFA888;
            int t;
            char *text;

            D_00254E78.unk18 = D_00254E78.unk08;
            D_00254E78.unk1C = D_00254E78.unk0C;
            func_0027EB88(D_00254E78.unk14 - D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk14 + D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk10 - D_00254E78.unk18, D_00254E78.unk10 + D_00254E78.unk18,
                          0x60, 0x60442D00);
            func_0029B658(0x60, 0x55F0C070,
                          D_00254E78.unk14 - D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk14 + D_00254E78.unk1C + D_00254E78.unk40,
                          D_00254E78.unk10 - D_00254E78.unk18, D_00254E78.unk10 + D_00254E78.unk18);
            t = D_00254E78.timer;
            if (t > 4)
                t = 4;
            if (t < 0)
                t = 0;
            if (D_00254E78.active == 4)
                color = (t << 29) | 0xFFA888;
            else if (D_00254E78.active == 6)
                color = ((4 - t) << 29) | 0xFFA888;
            text = (char *)D_001B1840[D_00254E78.entryIndex].unk00;
            func_002802E0(layout, D_00254E78.unk40 + 0xF0, D_00254E78.unk40 + 0x1E0, 0x2C, 0x1D4, 0x100,
                          D_00254E78.unk14 + D_00254E78.unk40, 0x10, 3);
            func_00280200(layout, color, text, -1);
        } else {
            func_00289AA0();
        }
        break;
    case 7:
        if (D_001A7B95 != 0) {
            int t = D_00254E78.timer;
            int h;
            int w;
            int alpha;

            if (t > 8)
                t = 8;
            if (t < 0)
                t = 0;
            h = D_00254E78.unk18 - (D_00254E78.unk18 - 8) * t / 8;
            w = D_00254E78.unk1C - (D_00254E78.unk1C - 8) * t / 8;
            alpha = (8 - t) * 12;
            func_0027EB88(D_00254E78.unk14 - w + D_00254E78.unk40, D_00254E78.unk14 + w + D_00254E78.unk40,
                          D_00254E78.unk10 - h, D_00254E78.unk10 + h, alpha, 0x60442D00);
            func_0029B658(alpha, 0x55F0C070,
                          D_00254E78.unk14 - w + D_00254E78.unk40, D_00254E78.unk14 + w + D_00254E78.unk40,
                          D_00254E78.unk10 - h, D_00254E78.unk10 + h);
        } else {
            func_00289AA0();
        }
        break;
    }
}
