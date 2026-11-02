/* func_L05_0041EF00: near miss, 3420/3420 bytes, 0 of 1 place (USA v1.01, 2 November 2026).

   Profile: its own unit, `-O2 -G8 -ffunction-sections -malign-loops=2`.

   Same opcodes as func_L10_004227A0 and func_L15_0042EFE0; this is the func_L10_004227A0
   draft, renamed. Its note found the vanished `if (D_L10_001B2D80 == 1)` test in MENU_ROW and
   that an empty do-while after it keeps retail's block boundary through sched2, but rejected it
   for the nops `.p2align 3` puts at the loop labels. -malign-loops=2 removes exactly those, as
   it does for family F7 (src/levels/06_notak/L06_0041DED8-f7-g8.c): the size is exact.
   What differs (9 rows; the other 52 of check.py's 61 are relocations): argument setup order
   in the two 200.0f rows (0.0f, %hi/%lo of the colour and $f12) and in the last
   func_0027F5B8 call ($a1 and $a3). Moving the colour among the float parameters of
   func_00300968, an unsigned colour and passing the row directly change nothing. */

#include "common.h"

extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);
extern s32 func_00283D38(s32, s32, f32);
extern s32 func_00336D50(u8 *, s32);
extern void func_00300968(char *, s32, f32, f32, f32, f32);
extern void func_00300A00(char *, s32, f32, f32, f32, f32, f32);
extern char *func_00288FB8(s32);
extern s32 func_00115DA8(char *, char *, ...);
extern s32 func_001157AC(char *);
extern s32 func_0027FBD8(s32, s32, u64, char *, s32);
extern s32 func_0027FB40(s32, s32, u64, char *, s32);
extern s32 func_0027FAA8(s32, s32, u64, char *, s32);
extern void func_0027F5B8(s32, s32, u64, char *, s32);
extern s32 func_L05_00303000(s32, s32, s32, s32, u64, char *, s32);
extern s32 D_001A7340;
typedef struct { u8 pad[0x1A0]; s32 buttons; } MenuInput;
extern MenuInput D_00138180;
extern u8 D_001A7A0A;
extern s32 D_L10_001A8F00;
extern u8 *D_L10_001A904C;
extern f32 D_L10_001B2D84;
extern s32 D_L10_001B2D80;
extern s32 D_L10_001B2048;
extern volatile s32 D_L10_001B1394, D_L10_001B1398, D_L10_001B139C;
extern s32 D_L10_001B1454[] __attribute__((sda)), D_L10_001B1460[] __attribute__((sda)), D_L10_001B146C[] __attribute__((sda));
extern s32 D_L10_001B1F64 __attribute__((sda));
extern s32 D_L10_001B143C __attribute__((sda));
extern s32 D_L10_001B1390 __attribute__((sda));
extern s32 D_L10_001B1448[] SDATA(D_L10_001B1448);

static __inline__ s32 MenuY(f32 y, f32 adjustment) {
    f32 scaled = y * D_L10_001B2D84 + 0.5f;
    if (D_L10_001B2D80 == 1)
        return (s32)(scaled + adjustment);
    return (s32)scaled;
}

#define MENU_ROW(dst, y0)                              \
    {                                                  \
        f32 y = (y0);                                  \
        f32 scaled = y * D_L10_001B2D84 + 0.5f;        \
        dst = (s32)scaled;                             \
        if (D_L10_001B2D80 == 1)                       \
            scaled = scaled + 1.0f;                    \
        do {                                           \
        } while (0);                                   \
    }

s32 func_L05_0041EF00(void) {
    char buf[128];
    f32 center, pulse, imageY;
    s32 r, remainder, color, blink, x, headerX, reward;
    char *text;

    center = func_00283CE0(D_001A7340) * 0.5f;
    if (D_L10_001A8F00 || !D_L10_001A904C) return 1;
    D_L10_001B1F64 = 0;
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x45);
    { s32 row; MENU_ROW(row, 200.0f); imageY = (f32)row; }
    func_00300968((char *)r, 0x60442D00, center, imageY, 1.0f, 0.0f);
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x44);
    { s32 row; MENU_ROW(row, 200.0f); imageY = (f32)row; }
    func_00300968((char *)r, 0x55F0C070, center, imageY, 1.0f, 0.0f);
    remainder = D_L10_001B2048 % 50;
    if (remainder >= 25) pulse = 1.0f - (remainder - 25) * 0.04f;
    else pulse = remainder * 0.04f;
    blink = func_00283D38(0x80FFDE8D, 0x60442D00, pulse);
    color = (D_00138180.buttons & 0x2000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x4A);
    imageY = (f32)MenuY(291.0f, 2.0f);
    func_00300A00((char *)r, color, 259.0f, imageY, 1.0f, 1.0f, 0.0f);
    color = (D_00138180.buttons & 0x8000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x4B);
    imageY = (f32)MenuY(291.0f, 2.0f);
    func_00300A00((char *)r, color, 251.0f, imageY, 1.0f, 1.0f, 0.0f);
    func_00115DA8(buf, func_00288FB8(0x2F72), D_L10_001B143C + 1);
    headerX = func_00283CF0(center);
    { s32 len;
    len = func_001157AC(buf);
    func_0027FBD8(headerX, 46, 0x80F0F0F0ULL, buf, len); }
    x = func_00283CF0(center);
    switch (D_L10_001B143C) {
    case 0:
        text = func_00288FB8(0x2FE2);
        {
            s32 len;
            s32 row = MenuY(101.0f, -2.0f);
            len = func_001157AC(text);
            func_0027FB40(x, row, 0x80F0F0F0ULL, text, len);
        }
        text = func_00288FB8(0x2FE7);
        {
            s32 len;
            s32 row;
            MENU_ROW(row, 131.0f);
            len = func_001157AC(text);
            func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, text, len);
        }
        {
            s32 index = D_L10_001B1390;
            if (index >= 3) index = 2;
            reward = D_L10_001B1448[index];
        }
        if (D_001A7A0A) reward *= 10;
        if (reward) {
        func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
        {
            s32 len;
            s32 row;
            MENU_ROW(row, 242.0f);
            len = func_001157AC(buf);
            func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, buf, len);
        }
        }
        func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        break;
    case 1:
        if (D_L10_001B1390) {
            text = func_00288FB8(0x2FE3);
            {
                s32 len;
                s32 row = MenuY(101.0f, -2.0f);
                len = func_001157AC(text);
                func_0027FAA8(x, row, 0x80F0F0F0ULL, text, len);
            }
            text = func_00288FB8(0x2FE8);
            {
                s32 len;
                s32 row;
                MENU_ROW(row, 131.0f);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, text, len);
            }
            {
                s32 index = D_L10_001B1394;
                if (index >= 3) index = 2;
                reward = D_L10_001B1454[index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                MENU_ROW(row, 242.0f);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                MENU_ROW(row, 170.0f);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 2:
        if (D_L10_001B1390 && D_L10_001B1394) {
            text = func_00288FB8(0x2FE5);
            {
                s32 len;
                s32 row = MenuY(101.0f, -2.0f);
                len = func_001157AC(text);
                func_0027FB40(x, row, 0x80F0F0F0ULL, text, len);
            }
            text = func_00288FB8(0x2FE9);
            {
                s32 len;
                s32 row;
                MENU_ROW(row, 131.0f);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, text, len);
            }
            {
                s32 index = D_L10_001B1398;
                if (index >= 3) index = 2;
                reward = D_L10_001B1460[index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                MENU_ROW(row, 242.0f);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                MENU_ROW(row, 170.0f);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 3:
        if (D_L10_001B1390 && D_L10_001B1394 && D_L10_001B1398) {
            text = func_00288FB8(0x2FE6);
            {
                s32 len;
                s32 row = MenuY(101.0f, -2.0f);
                len = func_001157AC(text);
                func_0027FB40(x, row, 0x80F0F0F0ULL, text, len);
            }
            text = func_00288FB8(0x2FEB);
            {
                s32 len;
                s32 row;
                MENU_ROW(row, 131.0f);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, text, len);
            }
            {
                s32 index = D_L10_001B139C;
                if (index >= 3) index = 2;
                reward = D_L10_001B146C[index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                MENU_ROW(row, 242.0f);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                MENU_ROW(row, 170.0f);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    }
    func_0027F5B8(119, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F40), -1);
    func_0027F5B8(356, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F41), -1);
    func_0027F5B8(279, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F42), -1);
    return 1;
}
