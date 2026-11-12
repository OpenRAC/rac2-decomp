#include "common.h"

/* func_US2_L10_00423CB8, the v2.00 copy of func_L10_004227A0: draws this level's menu panel
   (two sprites, two button icons, the header line, the selected entry's title, text box,
   reward line and option label or a locked-entry line, then three option labels).
   v2.00's changes: its own text ids, and the entry option label's x depends on the
   language byte (168 for 5, 164 for 4, 160 for 2, 181 otherwise). Entry 0 draws its title with func_L08_002F5CB8 at scale 0.9 (offset -1.0); entries 2 and 3 use func_0027FB40.

   The language byte is read as D_001A7BB0[4] (as in func_US2_0034E8D8): an element at an
   offset is a two-word load, which keeps it out of the entry-0 reward branch's delay slot
   as in retail (docs/contributing/matching-blockers.md). The y values go through the HUD
   label helpers, whose tests have no effect on the result; each do-while(0) group holds
   real statements. The unit builds with -malign-loops=2. */

extern s32 D_001A7340 MACRO_ADDR;
extern s32 D_001A8F00 MACRO_ADDR;
extern u8 D_001A7A0A MACRO_ADDR;
extern u8 D_001A7BB0[] __attribute__((sda)); /* the language byte is [4] */
extern s32 D_00138180[];
extern u8 *D_L10_001A904C MACRO_ADDR;
extern f32 D_L10_001B2D84;
extern s32 D_L10_001B2D80 MACRO_ADDR;
extern f32 D_L10_001B2D84_gp SDATA(D_L10_001B2D84);
extern s32 D_L10_001B2D80_gp SDATA(D_L10_001B2D80);
extern s32 D_L10_001B2048 MACRO_ADDR;
extern s32 D_L10_001B1F64 __attribute__((sda));
extern s32 D_L10_001B143C __attribute__((sda));
extern s32 D_L10_001B1390[] MACRO_ADDR;
extern s32 D_L10_001B1448[][3] MACRO_ADDR;
extern s32 D_L10_001B1390_gp[] SDATA(D_L10_001B1390);
extern s32 D_L10_001B1448_gp[][3] SDATA(D_L10_001B1448);

extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);
extern u32 func_00283D38(u32, u32, f32);
extern void *func_00336D50(void *, s32);
extern void func_00300968(void *, f32, f32, s32, f32, f32);
extern void func_00300A00(void *, s32, f32, f32, f32, f32, f32);
extern char *func_00288FB8(s32);
extern s32 func_00115DA8(char *, char *, ...);
extern s32 func_001157AC(char *);
extern s32 func_0027FBD8(s32, s32, u64, char *, s32);
extern s32 func_0027FAA8(s32, s32, u64, char *, s32);
extern s32 func_0027FB40(s32, s32, u64, char *, s32);
extern void func_L08_002F5CB8(s32, s32, u64, void *, s32, f32);
extern s32 func_L05_00303000(s32, s32, s32, s32, u64, u8 *, s32);
extern void func_0027F5B8(s32, s32, u64, char *, s32);

static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * D_L10_001B2D84 + 0.5f;

    if (mode == 1)
        return (s32)(scaled + offset);
    return (s32)scaled;
}

static __inline__ s32 screen_coord_gp(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * D_L10_001B2D84_gp + 0.5f;

    if (mode == 1)
        return (s32)(scaled + offset);
    return (s32)scaled;
}

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L10_001B2D80;
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

static __inline__ int label_y3(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L10_001B2D80;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    if (mode == active)
        scaled = scale;
    return result;
}

static __inline__ s32 sprite_y(void *handle, f32 y, f32 adjustment)
{
    f32 scaled = y * D_L10_001B2D84 + 0.5f;
    s32 result;
    void *copy;

    if (D_L10_001B2D80 == 1)
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

s32 func_US2_L10_00423CB8(void) {
    char buf[128];
    f32 center, fade, image_y;
    void *sprite;
    char *text;
    s32 x, y, t, hx;
    
    u32 blend, color;

    center = func_00283CE0(D_001A7340) * 0.5f;
    if (D_001A8F00 != 0)
        return 1;
    if (D_L10_001A904C != 0) {
        D_L10_001B1F64 = 0;
        sprite = func_00336D50(D_L10_001A904C + 0x8710, 0x45);
        func_00300968(sprite, center, (f32)label_y(sprite, 200.0f, D_L10_001B2D84, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
        sprite = func_00336D50(D_L10_001A904C + 0x8710, 0x44);
        func_00300968(sprite, center, (f32)label_y(sprite, 200.0f, D_L10_001B2D84, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
        t = D_L10_001B2048 % 50;
        if (t >= 25)
            fade = 1.0f - (f32)(t - 25) * 0.04f;
        else
            fade = (f32)t * 0.04f;
        blend = func_00283D38(0x80FFDE8D, 0x60442D00, fade);
        color = (D_00138180[0x68] & 0x2000) ? 0x80007FFF : blend;
        sprite = func_00336D50(D_L10_001A904C + 0x8710, 0x4A);
        image_y = (f32)sprite_y(sprite, 291.0f, 2.0f);
        func_00300A00(sprite, color, 259.0f, image_y, 1.0f, 1.0f, 0.0f);
        color = (D_00138180[0x68] & 0x8000) ? 0x80007FFF : blend;
        sprite = func_00336D50(D_L10_001A904C + 0x8710, 0x4B);
        image_y = (f32)sprite_y(sprite, 291.0f, 2.0f);
        func_00300A00(sprite, color, 251.0f, image_y, 1.0f, 1.0f, 0.0f);
        func_00115DA8(buf, func_00288FB8(0x2E08), D_L10_001B143C + 1);
        {
            s32 len;

            hx = func_00283CF0(center);
            len = func_001157AC(buf);
            func_0027FBD8(hx, 46, 0x80F0F0F0, buf, len);
        }
        x = func_00283CF0(center);
        switch (D_L10_001B143C) {
        case 0:
        {
            s32 index;

            text = func_00288FB8(0x2E78);
            y = screen_coord(D_L10_001B2D80, 101.0f, -1.0f);
            func_L08_002F5CB8(x, y, 0x80F0F0F0, text, func_001157AC(text), 0.9f);
            text = func_00288FB8(0x2E7D);
            {
                s32 ty = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
                func_L05_00303000(117, ty, 280, 400, 0x80F0F0F0, (u8 *)text, func_001157AC(text));
            }
            index = D_L10_001B1390_gp[0];
            if (index >= 3)
                index = 2;
            color = D_L10_001B1448_gp[0][index];
            if (D_001A7A0A != 0)
                color *= 10;
            if (color != 0) {
                s32 len, ty;
                do {
                    func_00115DA8(buf, func_00288FB8(0x2E76), color);
                    ty = label_y(buf, 242.0f, D_L10_001B2D84, 0.5f, 1);
                } while (0);
                len = func_001157AC(buf);
                func_L05_00303000(117, ty, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
            }
            if (D_001A7BB0[4] == 5) {
                func_0027F5B8(168, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
            } else if (D_001A7BB0[4] == 4) {
                func_0027F5B8(164, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
            } else if (D_001A7BB0[4] == 2) {
                func_0027F5B8(160, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
            } else {
                func_0027F5B8(181, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
            }
        }
            break;
        case 1:
            if (D_L10_001B1390_gp[0] != 0) {
                s32 index;
    
                text = func_00288FB8(0x2E79);
                y = screen_coord(D_L10_001B2D80, 101.0f, -2.0f);
                func_0027FAA8(x, y, 0x80F0F0F0, text, func_001157AC(text));
                text = func_00288FB8(0x2E7E);
                {
                    s32 len, ty, len1, ty1;
                    ty1 = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
                    do {
                        len1 = func_001157AC(text);
                        func_L05_00303000(117, ty1, 280, 400, 0x80F0F0F0, (u8 *)text, len1);
                        index = D_L10_001B1390[1];
                        if (index >= 3)
                            index = 2;
                        color = D_L10_001B1448[1][index];
                        if (D_001A7A0A != 0)
                            color *= 10;
                        func_00115DA8(buf, func_00288FB8(0x2E76), color);
                        ty = label_y3(buf, 242.0f, D_L10_001B2D84, 0.5f, 1);
                    } while (0);
                    len = func_001157AC(buf);
                    func_L05_00303000(117, ty, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
                }
                if (D_001A7BB0[4] == 5) {
                    func_0027F5B8(168, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                } else if (D_001A7BB0[4] == 4) {
                    func_0027F5B8(164, screen_coord_gp(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                } else if (D_001A7BB0[4] == 2) {
                    func_0027F5B8(160, screen_coord(D_L10_001B2D80_gp, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                } else {
                    func_0027F5B8(181, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                }
            } else {
                text = func_00288FB8(0x2E09);
                func_0027FBD8(x, label_y(text, 170.0f, D_L10_001B2D84, 0.5f, 1), 0x80F0F0F0, text, func_001157AC(text));
            }
            break;
        case 2:
            if (D_L10_001B1390_gp[0] != 0 && D_L10_001B1390[1] != 0) {
                s32 index;
    
                text = func_00288FB8(0x2E7B);
                y = screen_coord(D_L10_001B2D80, 101.0f, -2.0f);
                func_0027FB40(x, y, 0x80F0F0F0, text, func_001157AC(text));
                text = func_00288FB8(0x2E7F);
                {
                    s32 len, ty, len1, ty1;
                    ty1 = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
                    do {
                        len1 = func_001157AC(text);
                        func_L05_00303000(117, ty1, 280, 400, 0x80F0F0F0, (u8 *)text, len1);
                        index = D_L10_001B1390[2];
                        if (index >= 3)
                            index = 2;
                        color = D_L10_001B1448[2][index];
                        if (D_001A7A0A != 0)
                            color *= 10;
                        func_00115DA8(buf, func_00288FB8(0x2E76), color);
                        ty = label_y3(buf, 242.0f, D_L10_001B2D84, 0.5f, 1);
                    } while (0);
                    len = func_001157AC(buf);
                    func_L05_00303000(117, ty, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
                }
                if (D_001A7BB0[4] == 5) {
                    func_0027F5B8(168, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                } else if (D_001A7BB0[4] == 4) {
                    func_0027F5B8(164, screen_coord_gp(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                } else if (D_001A7BB0[4] == 2) {
                    func_0027F5B8(160, screen_coord(D_L10_001B2D80_gp, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                } else {
                    func_0027F5B8(181, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                }
            } else {
                text = func_00288FB8(0x2E09);
                func_0027FBD8(x, label_y(text, 170.0f, D_L10_001B2D84, 0.5f, 1), 0x80F0F0F0, text, func_001157AC(text));
            }
            break;
        case 3:
            if (D_L10_001B1390_gp[0] != 0 && D_L10_001B1390[1] != 0 && D_L10_001B1390[2] != 0) {
                s32 index;
    
                text = func_00288FB8(0x2E7C);
                y = screen_coord(D_L10_001B2D80, 101.0f, -2.0f);
                func_0027FB40(x, y, 0x80F0F0F0, text, func_001157AC(text));
                text = func_00288FB8(0x2E81);
                {
                    s32 len, ty, len1, ty1;
                    ty1 = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
                    do {
                        len1 = func_001157AC(text);
                        func_L05_00303000(117, ty1, 280, 400, 0x80F0F0F0, (u8 *)text, len1);
                        index = D_L10_001B1390[3];
                        if (index >= 3)
                            index = 2;
                        color = D_L10_001B1448[3][index];
                        if (D_001A7A0A != 0)
                            color *= 10;
                        func_00115DA8(buf, func_00288FB8(0x2E76), color);
                        ty = label_y3(buf, 242.0f, D_L10_001B2D84, 0.5f, 1);
                    } while (0);
                    len = func_001157AC(buf);
                    func_L05_00303000(117, ty, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
                }
                if (D_001A7BB0[4] == 5) {
                    func_0027F5B8(168, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                } else if (D_001A7BB0[4] == 4) {
                    func_0027F5B8(164, screen_coord_gp(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                } else if (D_001A7BB0[4] == 2) {
                    func_0027F5B8(160, screen_coord_gp(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                } else {
                    func_0027F5B8(181, screen_coord_gp(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD5), -1);
                }
            } else {
                text = func_00288FB8(0x2E09);
                func_0027FBD8(x, label_y(text, 170.0f, D_L10_001B2D84, 0.5f, 1), 0x80F0F0F0, text, func_001157AC(text));
            }
            break;
        }
        func_0027F5B8(119, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD6), -1);
        func_0027F5B8(356, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD7), -1);
        if (D_001A7BB0[4] == 5)
            func_0027F5B8(285, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD8), -1);
        else
            func_0027F5B8(279, screen_coord(D_L10_001B2D80, 294.0f, 3.0f), 0x80F0F0F0, func_00288FB8(0x2DD8), -1);
    }
    return 1;
}
