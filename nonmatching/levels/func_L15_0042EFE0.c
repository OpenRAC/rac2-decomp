/* func_L15_0042EFE0: near miss, 3420/3420 bytes, 0 of 1 place (USA v1.01, 7 November 2026).
 *
 * Same body as func_L10_004227A0. This is that note's round-three draft, with this level's data
 * names (the addresses come from this level's relocations): 847/855 aligned, the same 8 rows,
 * which are the four 101 rows' a0/t0 order. The L10 note has the analysis. Unit: its own -g8.c,
 * -O2 -G8 -ffunction-sections. MenuSpriteY's dead tests are allowed by owner ruling (7 November 2026).
 */
#include "common.h"

extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);
extern s32 func_00283D38(s32, s32, f32);
extern s32 func_00336D50(u8 *, s32);
extern void func_00300968(void *, f32, f32, s32, f32, f32);
extern void func_00300A00(char *, s32, f32, f32, f32, f32, f32);
extern char *func_00288FB8(s32);
extern s32 func_00115DA8(char *, char *, ...);
extern s32 func_001157AC(char *);
extern s32 func_0027FBD8(s32, s32, u64, char *, s32);
extern s32 func_0027FB40(s32, s32, u64, char *, s32);
extern s32 func_0027FAA8(s32, s32, u64, char *, s32);
extern void func_0027F5B8(s32, s32, u64, char *, s32);
/* Retail builds the colour with the 64-bit ori/dsll/ori form, so the caller passes a u64, as
   func_L05_00302CE8 (which the wrapper forwards to) takes it; the wrapper's matched C still says int. */
extern s32 func_L05_00303000(s32, s32, s32, s32, u64, u8 *, s32);
extern s32 D_001A7340;
typedef struct { u8 pad[0x1A0]; s32 buttons; } MenuInput;
extern MenuInput D_00138180;
extern u8 D_001A7A0A;
extern s32 D_L15_001A8F00;
extern u8 *D_L15_001A904C;
extern f32 D_L15_001B2E84;
extern s32 D_L15_001B2E80;
extern s32 D_L15_001B2148;
extern s32 D_L15_001B15E4[] __attribute__((sda)), D_L15_001B15F0[] __attribute__((sda)), D_L15_001B15FC[] __attribute__((sda));
extern s32 D_L15_001B2064 __attribute__((sda));
extern s32 D_L15_001B15C8 __attribute__((sda));
extern s32 D_L15_001B1520[] __attribute__((sda));
extern s32 D_L15_001B1520_gp[] SDATA(D_L15_001B1520);
extern s32 D_L15_001B15D8[] SDATA(D_L15_001B15D8);

/* MenuY with label_y's two dead handle tests, for the two sprite rows (allowed by owner ruling,
   7 November 2026, as the dead-test helper). The tests do not change the result; they end blocks
   that allocation and both scheduling passes see. */
static __inline__ s32 MenuSpriteY(void *handle, f32 y, f32 adjustment) {
    f32 scaled = y * D_L15_001B2E84 + 0.5f;
    s32 result;
    void *copy;
    if (D_L15_001B2E80 == 1)
        result = (s32)(scaled + adjustment);
    else
        result = (s32)scaled;
    if (handle != 0)
        scaled = y;
    copy = handle;
    if (copy != 0)
        scaled = adjustment;
    return result;
}
static __inline__ s32 MenuY(f32 y, f32 adjustment) {
    f32 scaled = y * D_L15_001B2E84 + 0.5f;
    if (D_L15_001B2E80 == 1)
        return (s32)(scaled + adjustment);
    return (s32)scaled;
}

/* label_y: the accepted HUD label helper (src/levels/10_hrugis_cloud/L10_00421790-g8.c). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L15_001B2E80;
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

s32 func_L15_0042EFE0(void) {
    char buf[128];
    f32 center, pulse, imageY;
    s32 r, remainder, color, blink, x, headerX, reward;
    char *text;

    center = func_00283CE0(D_001A7340) * 0.5f;
    if (D_L15_001A8F00) return 1;
    if (D_L15_001A904C) {
    D_L15_001B2064 = 0;
    r = func_00336D50(D_L15_001A904C + 0x8710, 0x45);
    func_00300968((void *)r, center, (f32)label_y((void *)r, 200.0f, D_L15_001B2E84, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
    r = func_00336D50(D_L15_001A904C + 0x8710, 0x44);
    func_00300968((void *)r, center, (f32)label_y((void *)r, 200.0f, D_L15_001B2E84, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
    remainder = D_L15_001B2148 % 50;
    if (remainder >= 25) pulse = 1.0f - (remainder - 25) * 0.04f;
    else pulse = remainder * 0.04f;
    blink = func_00283D38(0x80FFDE8D, 0x60442D00, pulse);
    color = (D_00138180.buttons & 0x2000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L15_001A904C + 0x8710, 0x4A);
    imageY = (f32)MenuSpriteY((void *)r, 291.0f, 2.0f);
    func_00300A00((char *)r, color, 259.0f, imageY, 1.0f, 1.0f, 0.0f);
    color = (D_00138180.buttons & 0x8000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L15_001A904C + 0x8710, 0x4B);
    imageY = (f32)MenuSpriteY((void *)r, 291.0f, 2.0f);
    func_00300A00((char *)r, color, 251.0f, imageY, 1.0f, 1.0f, 0.0f);
    func_00115DA8(buf, func_00288FB8(0x2F72), D_L15_001B15C8 + 1);
    headerX = func_00283CF0(center);
    { s32 len;
    len = func_001157AC(buf);
    func_0027FBD8(headerX, 46, 0x80F0F0F0ULL, buf, len); }
    x = func_00283CF0(center);
    switch (D_L15_001B15C8) {
    case 0:
        text = func_00288FB8(0x2FE2);
        {
            s32 row = MenuY(101.0f, -2.0f);
            func_0027FB40(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
        }
        text = func_00288FB8(0x2FE7);
        {
            s32 len;
            s32 row;
            row = label_y(text, 131.0f, D_L15_001B2E84, 0.5f, 1);
            len = func_001157AC(text);
            func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
        }
        {
            s32 index = D_L15_001B1520_gp[0];
            if (index >= 3) index = 2;
            reward = D_L15_001B15D8[index];
        }
        if (D_001A7A0A) reward *= 10;
        if (reward) {
        func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
        {
            s32 len;
            s32 row;
            row = label_y((void *)x, 242.0f, D_L15_001B2E84, 0.5f, 1);
            len = func_001157AC(buf);
            func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
        }
        }
        func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        break;
    case 1:
        if (D_L15_001B1520_gp[0]) {
            text = func_00288FB8(0x2FE3);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FAA8(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = func_00288FB8(0x2FE8);
            {
                s32 len;
                s32 row;
                row = label_y(text, 131.0f, D_L15_001B2E84, 0.5f, 1);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L15_001B1520[1];
                if (index >= 3) index = 2;
                reward = D_L15_001B15E4[index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 242.0f, D_L15_001B2E84, 0.5f, 1);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L15_001B2E84, 0.5f, 1);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 2:
        if (D_L15_001B1520_gp[0] && D_L15_001B1520[1]) {
            text = func_00288FB8(0x2FE5);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FB40(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = func_00288FB8(0x2FE9);
            {
                s32 len;
                s32 row;
                row = label_y(text, 131.0f, D_L15_001B2E84, 0.5f, 1);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L15_001B1520[2];
                if (index >= 3) index = 2;
                reward = D_L15_001B15F0[index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 242.0f, D_L15_001B2E84, 0.5f, 1);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L15_001B2E84, 0.5f, 1);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 3:
        if (D_L15_001B1520_gp[0] && D_L15_001B1520[1] && D_L15_001B1520[2]) {
            text = func_00288FB8(0x2FE6);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FB40(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = func_00288FB8(0x2FEB);
            {
                s32 len;
                s32 row;
                row = label_y(text, 131.0f, D_L15_001B2E84, 0.5f, 1);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L15_001B1520[3];
                if (index >= 3) index = 2;
                reward = D_L15_001B15FC[index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 242.0f, D_L15_001B2E84, 0.5f, 1);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L15_001B2E84, 0.5f, 1);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    }
    func_0027F5B8(119, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F40), -1);
    func_0027F5B8(356, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F41), -1);
    func_0027F5B8(279, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F42), -1);
    }
    return 1;
}
