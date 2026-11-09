#include "common.h"

/* func_L05_0041EF00: draws a Feltzin System menu panel: two sprites, two button icons, the header
   line, then for the selected entry (D_L05_001B13EC) its title, a wrapped text box, the reward
   line and one option label, or a locked-entry line; then three option labels. The same code as
   func_L10_004227A0 and func_L15_0042EFE0, with this level's data and text ids.

   The row y values go through the HUD label helpers (label_y, label_y3, MenuSpriteY); their tests
   have no effect on the result. Each do-while(0) group holds real statements (allowed,
   docs/COMPILER-NOTES.md); it ends the scheduling block after the reward row's y. */

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
extern s32 D_L05_001A8F00;
extern u8 *D_L05_001A904C;
extern f32 D_L05_001B2D84;
extern s32 D_L05_001B2D80;
extern s32 D_L05_001B2048;
extern s32 D_L05_001B1404[] __attribute__((sda)), D_L05_001B1410[] __attribute__((sda)), D_L05_001B141C[] __attribute__((sda));
extern s32 D_L05_001B1F64 __attribute__((sda));
extern s32 D_L05_001B13EC __attribute__((sda));
extern s32 D_L05_001B1350[] __attribute__((sda));
extern s32 D_L05_001B1350_gp[] SDATA(D_L05_001B1350);
extern s32 D_L05_001B13F8[] SDATA(D_L05_001B13F8);

/* MenuY with label_y's two dead handle tests, for the two sprite rows (allowed by owner ruling,
   7 November 2026, as the dead-test helper). The tests do not change the result; they end blocks
   that allocation and both scheduling passes see. */
static __inline__ s32 MenuSpriteY(void *handle, f32 y, f32 adjustment) {
    f32 scaled = y * D_L05_001B2D84 + 0.5f;
    s32 result;
    void *copy;
    if (D_L05_001B2D80 == 1)
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
    f32 scaled = y * D_L05_001B2D84 + 0.5f;
    if (D_L05_001B2D80 == 1)
        return (s32)(scaled + adjustment);
    return (s32)scaled;
}

/* label_y: the accepted HUD label helper (src/levels/10_hrugis_cloud/L10_00421790-g8.c). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L05_001B2D80;
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

/* label_y3: label_y with the mode test after its two dead handle tests (allowed by owner ruling,
   9 November 2026). */
static __inline__ int label_y3(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L05_001B2D80;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;
    if (handle != 0) scaled = scale;
    copy = handle;
    if (copy != 0) scaled = half;
    if (mode == active) scaled = scale;
    return result;
}

s32 func_L05_0041EF00(void) {
    char buf[128];
    f32 center, pulse, imageY;
    s32 r, remainder, color, blink, x, headerX, reward;
    char *text;

    center = func_00283CE0(D_001A7340) * 0.5f;
    if (D_L05_001A8F00) return 1;
    if (D_L05_001A904C) {
    D_L05_001B1F64 = 0;
    r = func_00336D50(D_L05_001A904C + 0x8710, 0x45);
    func_00300968((void *)r, center, (f32)label_y((void *)r, 200.0f, D_L05_001B2D84, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
    r = func_00336D50(D_L05_001A904C + 0x8710, 0x44);
    func_00300968((void *)r, center, (f32)label_y((void *)r, 200.0f, D_L05_001B2D84, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
    remainder = D_L05_001B2048 % 50;
    if (remainder >= 25) pulse = 1.0f - (remainder - 25) * 0.04f;
    else pulse = remainder * 0.04f;
    blink = func_00283D38(0x80FFDE8D, 0x60442D00, pulse);
    color = (D_00138180.buttons & 0x2000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L05_001A904C + 0x8710, 0x4A);
    imageY = (f32)MenuSpriteY((void *)r, 291.0f, 2.0f);
    func_00300A00((char *)r, color, 259.0f, imageY, 1.0f, 1.0f, 0.0f);
    color = (D_00138180.buttons & 0x8000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L05_001A904C + 0x8710, 0x4B);
    imageY = (f32)MenuSpriteY((void *)r, 291.0f, 2.0f);
    func_00300A00((char *)r, color, 251.0f, imageY, 1.0f, 1.0f, 0.0f);
    func_00115DA8(buf, func_00288FB8(0x2F72), D_L05_001B13EC + 1);
    headerX = func_00283CF0(center);
    { s32 len;
    len = func_001157AC(buf);
    func_0027FBD8(headerX, 46, 0x80F0F0F0ULL, buf, len); }
    x = func_00283CF0(center);
    switch (D_L05_001B13EC) {
    case 0:
        text = func_00288FB8(0x2FD6);
        {
            s32 row = MenuY(101.0f, -2.0f);
            func_0027FAA8(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
        }
        text = func_00288FB8(0x2FDB);
        {
            s32 len;
            s32 row;
            row = label_y(text, 131.0f, D_L05_001B2D84, 0.5f, 1);
            len = func_001157AC(text);
            func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
        }
        {
            s32 index = D_L05_001B1350_gp[0];
            if (index >= 3) index = 2;
            reward = D_L05_001B13F8[index];
        }
        if (D_001A7A0A) reward *= 10;
        if (reward) {
        {
            s32 len;
            s32 row;
            do {
                func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
                row = label_y(buf, 242.0f, D_L05_001B2D84, 0.5f, 1);
            } while (0);
            len = func_001157AC(buf);
            func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
        }
        }
        func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        break;
    case 1:
        if (D_L05_001B1350_gp[0]) {
            text = func_00288FB8(0x2FD8);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FB40(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            {
                s32 len;
                s32 row;
                s32 len1, row1;
                text = func_00288FB8(0x2FDD);
                row1 = label_y(text, 131.0f, D_L05_001B2D84, 0.5f, 1);
                do {
                    len1 = func_001157AC(text);
                    func_L05_00303000(117, row1, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len1);
                    {
                        s32 index = D_L05_001B1350[1];
                        if (index >= 3) index = 2;
                        reward = D_L05_001B1404[index];
                    }
                    if (D_001A7A0A) reward *= 10;
                    func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
                    row = label_y3(buf, 242.0f, D_L05_001B2D84, 0.5f, 1);
                } while (0);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L05_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 2:
        if (D_L05_001B1350_gp[0] && D_L05_001B1350[1]) {
            text = func_00288FB8(0x2FD7);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FAA8(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            {
                s32 len;
                s32 row;
                s32 len1, row1;
                text = func_00288FB8(0x2FDC);
                row1 = label_y(text, 131.0f, D_L05_001B2D84, 0.5f, 1);
                do {
                    len1 = func_001157AC(text);
                    func_L05_00303000(117, row1, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len1);
                    {
                        s32 index = D_L05_001B1350[2];
                        if (index >= 3) index = 2;
                        reward = D_L05_001B1410[index];
                    }
                    if (D_001A7A0A) reward *= 10;
                    func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
                    row = label_y3(buf, 242.0f, D_L05_001B2D84, 0.5f, 1);
                } while (0);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L05_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 3:
        if (D_L05_001B1350_gp[0] && D_L05_001B1350[1] && D_L05_001B1350[2]) {
            text = func_00288FB8(0x2FDA);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FAA8(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = func_00288FB8(0x2FDF);
            {
                s32 len;
                s32 row;
                s32 len1, row1;
                row1 = label_y(text, 131.0f, D_L05_001B2D84, 0.5f, 1);
                do {
                    len1 = func_001157AC(text);
                    func_L05_00303000(117, row1, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len1);
                    {
                        s32 index = D_L05_001B1350[3];
                        if (index >= 3) index = 2;
                        reward = D_L05_001B141C[index];
                    }
                    if (D_001A7A0A) reward *= 10;
                    func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
                    row = label_y3(buf, 242.0f, D_L05_001B2D84, 0.5f, 1);
                } while (0);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L05_001B2D84, 0.5f, 1);
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
