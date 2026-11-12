/* func_PAL_L11_00449CBC: the PAL copy of v2.00's func_US2_L11_00445CB4
 * (src/us2/levels/11_joba/L11_00445CB4-g8.c), itself the v2.00 copy of func_L11_00444400, the Joba
 * six-box HUD. The same C, flags and helpers, with PAL's text ids, and its countdowns and clock read
 * the 50 Hz frame counter: seconds are frames / 50 and minutes frames / 3000 (v2.00: / 60, / 3600).
 * Built with -frac2-frame-pointer-liveness, as in v2.00: the flag lets flow2 drop a dead set-once
 * store left in $fp. */
#include "common.h"

typedef struct {
    u16 w[12];
} Rect;

typedef struct {
    u8 pad[0xB0];
    f32 text_scale;
} HudRenderState;

extern s32 D_L11_001A904C[] __attribute__((sda));
extern f32 D_L11_001B3E04;
extern u8 D_L11_001BEDC0[];
extern char D_L11_001B17E8[];
extern char D_L11_001B17F0[];
extern char D_L11_001B17F8[];
extern char D_L11_001B1800[];
extern s32 D_L11_001B14B8[] SDATA(D_L11_001B14B8);
extern s32 D_L11_001B14D0[] SDATA(D_L11_001B14D0);
extern s32 D_L11_001B14D8[] SDATA(D_L11_001B14D8);
extern s16 *D_L11_001B14F8[] SDATA(D_L11_001B14F8);
extern s32 D_L11_001B1718 __attribute__((sda));

extern s32 D_L11_001B1798 __attribute__((sda));
extern s32 D_L11_001B179C __attribute__((sda));
extern s32 D_L11_001B17A0 __attribute__((sda));
extern s32 D_L11_001B17A4[] __attribute__((sda));
extern s32 D_L11_001B17A8[] __attribute__((sda));
extern s32 D_L11_001B17AC[] __attribute__((sda));
extern s32 D_L11_001B1780 __attribute__((sda));
extern s32 D_L11_001B1784 __attribute__((sda));
extern s32 D_L11_001B1788[][4] SDATA(D_L11_001B1788);
extern s32 D_L11_001B178C[][4] __attribute__((sda));
extern s32 D_L11_001B1790[][4] __attribute__((sda));
extern s32 D_L11_001B1794[][4] __attribute__((sda));
extern s32 D_L11_001B1738 __attribute__((sda));
extern s32 D_L11_001B173C __attribute__((sda));
extern s32 D_L11_001B1740 __attribute__((sda));
extern s32 D_L11_001B1744[] __attribute__((sda));
extern s32 D_L11_001B1748[] __attribute__((sda));
extern s32 D_L11_001B174C[] __attribute__((sda));
extern s32 D_L11_001B171C __attribute__((sda));
extern s32 D_L11_001B1720 __attribute__((sda));
extern s32 D_L11_001B1728[][4] SDATA(D_L11_001B1728);
extern s32 D_L11_001B172C[][4] __attribute__((sda));
extern s32 D_L11_001B1730[][4] __attribute__((sda));
extern s32 D_L11_001B1734[][4] __attribute__((sda));
extern s32 D_L11_001B1768 __attribute__((sda));
extern s32 D_L11_001B176C __attribute__((sda));
extern s32 D_L11_001B1770 __attribute__((sda));
extern s32 D_L11_001B1774[] __attribute__((sda));
extern s32 D_L11_001B1778[] __attribute__((sda));
extern s32 D_L11_001B177C[] __attribute__((sda));
extern s32 D_L11_001B1750 __attribute__((sda));
extern s32 D_L11_001B1754 __attribute__((sda));
extern s32 D_L11_001B1758 __attribute__((sda));
extern s32 D_L11_001B175C[] __attribute__((sda));
extern s32 D_L11_001B1760[] __attribute__((sda));
extern s32 D_L11_001B1764[] __attribute__((sda));

extern s32 D_L11_001B17B0 __attribute__((sda));
extern s32 D_L11_001B17B4 __attribute__((sda));
extern s32 D_L11_001B17B8 __attribute__((sda));
extern s32 D_L11_001B17BC __attribute__((sda));
extern s32 D_L11_001B17C0 __attribute__((sda));
extern f32 D_L11_001B17C4 __attribute__((sda));
extern f32 D_L11_001B17C8 __attribute__((sda));
extern f32 D_L11_001B17CC __attribute__((sda));
extern f32 D_L11_001B17D0 __attribute__((sda));
extern f32 D_L11_001B17D4 __attribute__((sda));
extern f32 D_L11_001B17D8 __attribute__((sda));
extern f32 D_L11_001B17DC __attribute__((sda));
extern s32 D_L11_001B17E0 __attribute__((sda));
extern s32 D_L11_001B17E4 __attribute__((sda));

extern void func_0027AB40(void);
extern void func_00280190(Rect *, u64, char *, s32);
extern void func_00280200(Rect *, u64, char *, s32);
extern void func_00280270(Rect *, u64, char *, s32);
extern int func_PAL_L02_00402928(void);
extern void func_002802E0(Rect *, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 func_00283CE0(s32);
extern int func_00288FB8(s32);
extern void func_002FC560(u32, u64);
extern void func_L00_0037B7B0(void);
extern void func_00300A00(char *, f32, s32, f32, f32, f32, f32);
extern void func_L02_003FE768(f32);
extern int func_00336D50(s32, s32);
extern s32 func_001157AC(char *);
extern s32 func_00115DA8(char *, char *, ...);

extern s32 D_L11_001B3E00;
#define LBL(id, c, xv, yv, a1, a2, a3, A) { char *ls = (char *)func_00336D50(D_L11_001A904C[0] + ofs, id); func_00300A00(ls, xv, c, (f32)label_y(ls, (yv), D_L11_001B3E04, half, A), a1, a2, a3); }
#define LBL4(id, c, xv, yv, a1, a2, a3, A) { char *ls = (char *)func_00336D50(D_L11_001A904C[0] + ofs, id); func_00300A00(ls, xv, c, (f32)label_y4(ls, (yv), D_L11_001B3E04, half, A), a1, a2, a3); }
#define TITLE(A2, A) \
        LBL(0x4C, D_L11_001B17E4, D_L11_001B17D0, D_L11_001B17D4, -1.0f, D_L11_001B17C4, 0.0f, A2); \
        LBL(0x4D, D_L11_001B17E0, D_L11_001B17D0, D_L11_001B17D4, -1.0f, D_L11_001B17C4, 0.0f, A)
#define LABEL(A2, A) \
        LBL(0x4C, D_L11_001B17E4, D_L11_001B17C8, D_L11_001B17CC, D_L11_001B17C4, 1.0f, 0.0f, A2); \
        LBL(0x4D, D_L11_001B17E0, D_L11_001B17C8, D_L11_001B17CC, D_L11_001B17C4, 1.0f, 0.0f, A)
#define LABEL50(A) \
        LBL4(0x50, D_L11_001B17E0, D_L11_001B17BC, D_L11_001B17C0, D_L11_001B17C4, 1.0f, 0.0f, A)
#define SUM() \
            sum = 0; \
            for (obj = data + 0x100, i = 7; i >= 0; i--, obj += 4) { \
                sum += *(s32 *)obj; \
            }
#define DRAW(fn, r, s) \
            str = (s); \
            fn((r), D_L11_001B1718, str, func_001157AC(str))
#define DRAWBUF(fn, r) \
            { s32 c = D_L11_001B1718; s32 n = func_001157AC(buf); fn((r), c, buf, n); }
#define sprintf_n func_00115DA8

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L11_001B3E00;
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

/* label_y4: label_y with the mode test before the rounding and dead stores to value. */
static __inline__ int label_y4(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L11_001B3E00;
    float scaled = value * scale + half;
    int result;
    void *copy;
    if (mode == active) value = scale;
    result = (int)scaled;
    if (handle != 0) value = scale;
    copy = handle;
    if (copy != 0) value = half;
    return result;
}

static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    int mode = D_L11_001B3E00;
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

void func_PAL_L11_00449CBC(u8 *moby)
{
    char buf[0x40];
    Rect r50;
    Rect r70;
    Rect r90;
    Rect rB0;
    Rect rD0;
    Rect rF0;
    u8 *data;
    u8 *obj;
    u8 *pv;
    f32 save;
    s32 sum;
    s32 i;
    s32 n;
    s32 tm;
    s32 x, y, h;
    char *str;
    f32 half;
    f32 t;
    s32 one;
    s32 k2;
    s32 k3;
    s32 three;
    s32 three2;
    s32 three3;

    if (D_L11_001A904C[0] == 0) {
        return;
    }
    func_L00_0037B7B0();
    half = 0.5f;
    data = *(u8 **)(moby + 0x68);
    x = hud_coord((f32)D_L11_001B17A0, D_L11_001B3E04, half, 1);
    y = hud_coord((f32)D_L11_001B17A4[0], D_L11_001B3E04, half, 1);
    h = hud_coord((f32)D_L11_001B179C, D_L11_001B3E04, half, 1);
    three = 3;
    func_002802E0(&r50, x, y, D_L11_001B17A8[0], D_L11_001B17AC[0], D_L11_001B1798, h, 0, three);
    {
    s32 x, y;
    x = label_y(&r70, (f32)D_L11_001B1788[func_PAL_L02_00402928()][0], D_L11_001B3E04, half, 1);
    y = label_y(data, (f32)D_L11_001B178C[func_PAL_L02_00402928()][0], D_L11_001B3E04, half, 1);
    func_002802E0(&r70, x, y, D_L11_001B1790[func_PAL_L02_00402928()][0], D_L11_001B1794[func_PAL_L02_00402928()][0], D_L11_001B1780, hud_coord((f32)D_L11_001B1784, D_L11_001B3E04, half, 1), 0, three);
    }
    x = hud_coord((f32)D_L11_001B1740, D_L11_001B3E04, half, 1);
    do { t = (f32)D_L11_001B1744[0] * D_L11_001B3E04 + half; y = t; } while (0);
    h = hud_coord((f32)D_L11_001B173C, D_L11_001B3E04, half, 1);
    func_002802E0(&r90, x, y, D_L11_001B1748[0], D_L11_001B174C[0], D_L11_001B1738, h, 0, three);
    three2 = 3;
    {
    s32 x, y;
    x = label_y(moby, (f32)D_L11_001B1728[func_PAL_L02_00402928()][0], D_L11_001B3E04, half, 1);
    do { k3 = 1; } while (0);
    y = label_y(&rB0, (f32)D_L11_001B172C[func_PAL_L02_00402928()][0], D_L11_001B3E04, half, k3);
    func_002802E0(&rB0, x, y, D_L11_001B1730[func_PAL_L02_00402928()][0], D_L11_001B1734[func_PAL_L02_00402928()][0], D_L11_001B171C, hud_coord((f32)D_L11_001B1720, D_L11_001B3E04, half, k3), 0, three);
    }
    x = hud_coord((f32)D_L11_001B1770, D_L11_001B3E04, half, 1);
    y = hud_coord((f32)D_L11_001B1774[0], D_L11_001B3E04, half, 1);
    func_002802E0(&rF0, x, y, D_L11_001B1778[0], D_L11_001B177C[0], D_L11_001B1768, hud_coord((f32)D_L11_001B176C, D_L11_001B3E04, half, 1), 0, three2);
    x = hud_coord((f32)D_L11_001B1758, D_L11_001B3E04, half, k3);
    do { t = (f32)D_L11_001B175C[0] * D_L11_001B3E04 + half; y = t; } while (0);
    three3 = 3;
    func_002802E0(&rD0, x, y, D_L11_001B1760[0], D_L11_001B1764[0], D_L11_001B1750, hud_coord((f32)D_L11_001B1754, D_L11_001B3E04, half, k3), 0, three3);
    one = 1;
    k2 = 1;
    save = ((HudRenderState *)D_L11_001BEDC0)->text_scale;
    ((HudRenderState *)D_L11_001BEDC0)->text_scale = 0.62f;
    func_0027AB40();
    if (*(s16 *)(data + 0x1F0) == 5) {
        s32 ofs = 0x8710;
        TITLE( k3, 1);
        sprintf_n(buf, D_L11_001B17E8, 0x5A - *(s32 *)(data + 0x188) / 50);
        DRAWBUF(func_00280270, &r90);
        DRAW(func_00280200, &rB0, ((char *)func_00288FB8(0xE88)));
        LABEL( k3, k2);
        SUM();
        sprintf_n(buf, D_L11_001B17E8, D_L11_001B14B8[*(s16 *)(data + 0x1F2)] + sum - *(s32 *)(data + 0x140));
        DRAWBUF(func_00280270, &r50);
        str = (char *)func_00288FB8(0xE86);
        if (func_PAL_L02_00402928()) {
            func_00280200(&r70, D_L11_001B1718, str, func_001157AC(str));
        } else {
            func_00280190(&r70, D_L11_001B1718, str, func_001157AC(str));
        }
    } else if (*(s16 *)(data + 0x1F0) == 9) {
        s32 ofs = 0x8710;
        TITLE( k3, one);
        tm = *(s32 *)(data + 0x188);
        { s32 hh = 2 - tm / 3000; s32 m = 0x3B - tm / 50 % 60; sprintf_n(buf, D_L11_001B17F0, hh, m); }
        DRAWBUF(func_00280200, &r90);
        DRAW(func_00280200, &rB0, ((char *)func_00288FB8(0xE88)));
        LABEL( k3, one);
        LABEL50( one);
        pv = *(u8 **)(*(u8 **)(data + 0x180) + 0x68);
        func_L02_003FE768(*(f32 *)(pv + 0x20) / func_00283CE0(*(s16 *)(pv + 0x24)));
        LBL4(0xE3, D_L11_001B17B0, D_L11_001B17B4, D_L11_001B17B8, D_L11_001B17C4, 1.0f, 1.0f, k2);
    } else if (*(s16 *)(data + 0x1F0) == 8) {
        s32 ofs = 0x8710;
        TITLE( k3, 1);
        sprintf_n(buf, D_L11_001B17E8, 60 - *(s32 *)(data + 0x188) / 50);
        DRAWBUF(func_00280270, &r90);
        DRAW(func_00280200, &rB0, ((char *)func_00288FB8(0xE88)));
        LABEL( k2, 1);
        SUM();
        sprintf_n(buf, D_L11_001B17E8, D_L11_001B14D0[*(s16 *)(data + 0x1F2)] + sum - *(s32 *)(data + 0x140));
        DRAWBUF(func_00280270, &r50);
        str = (char *)func_00288FB8(0xE86);
        if (func_PAL_L02_00402928()) {
            func_00280200(&r70, D_L11_001B1718, str, func_001157AC(str));
        } else {
            func_00280190(&r70, D_L11_001B1718, str, func_001157AC(str));
        }
    } else if (*(s16 *)(data + 0x1F0) == 0xC) {
        s32 ofs = 0x8710;
        TITLE( 1, k2);
        n = 100 - *(s32 *)(data + 0x188) / 50;
        sprintf_n(buf, D_L11_001B17E8, n);
        if (n >= 100) {
            DRAWBUF(func_00280190, &r90);
        } else {
            do { DRAWBUF(func_00280270, &r90); } while (0);
        }
        DRAW(func_00280200, &rB0, ((char *)func_00288FB8(0xE88)));
        if (moby[0xBC] != 0) {
            s32 ofs = 0x8710; f32 half = 0.5f;
            LABEL( one, one);
            SUM();
            if (moby[0xBC] < 2) {
                sprintf_n(buf, D_L11_001B17E8, D_L11_001B14D8[*(s16 *)(data + 0x1F2)] + sum - *(s32 *)(data + 0x140));
                DRAWBUF(func_00280270, &r50);
            } else {
                sprintf_n(buf, D_L11_001B17E8, 100);
                DRAWBUF(func_00280190, &r50);
            }
            str = (char *)func_00288FB8(0xE86);
        if (func_PAL_L02_00402928()) {
            func_00280200(&r70, D_L11_001B1718, str, func_001157AC(str));
        } else {
            func_00280190(&r70, D_L11_001B1718, str, func_001157AC(str));
        }
        }
    } else {
        if (*(u8 **)(data + 0x180) != 0) {
            s32 ofs = 0x8710;
            LABEL( one, k3);
            LABEL50( 1);
            obj = *(u8 **)(data + 0x180);
            switch (*(s16 *)(obj + 0xAA)) {
            case 0xD4A:
                pv = *(u8 **)(obj + 0x68);
                if (*(f32 *)(pv + 0x20) > 0.0f) {
                    func_L02_003FE768(*(f32 *)(pv + 0x20) / func_00283CE0(*(s16 *)(pv + 0x24)));
                }
                LBL4(0xE3, D_L11_001B17B0, D_L11_001B17B4, D_L11_001B17B8, D_L11_001B17C4, 1.0f, 1.0f, 1);
                break;
            case 0xB3A:
                pv = *(u8 **)(obj + 0x68);
                func_L02_003FE768(*(f32 *)(pv + 0x20) / func_00283CE0(*(s16 *)(pv + 0x24)));
                LBL4(0xE3, D_L11_001B17B0, D_L11_001B17B4, D_L11_001B17B8, D_L11_001B17C4, 1.0f, 2.0f, one);
                break;
            }
        }
        {
            s32 ofs = 0x8710; f32 half = 0.5f;
            LBL(0x4E, D_L11_001B17E4, D_L11_001B17D8, D_L11_001B17DC, -1.0f, D_L11_001B17C4, 0.0f, k2);
            LBL(0x4F, D_L11_001B17E0, D_L11_001B17D8, D_L11_001B17DC, -1.0f, D_L11_001B17C4, 0.0f, k3);
        }
        if (*(s16 *)(data + 0x1F0) == 0xA) {
            sprintf_n(buf, D_L11_001B17F8, *(s16 *)(data + 0x1F2) + 1);
        } else {
            sprintf_n(buf, D_L11_001B1800, *(s16 *)(data + 0x1F2) + 1, *D_L11_001B14F8[*(s16 *)(data + 0x1F0)]);
        }
        DRAWBUF(func_00280270, &rF0);
        DRAW(func_00280190, &rD0, ((char *)func_00288FB8(0xE85)));
    }
    func_002FC560(0x47, 0x5360B);
    func_002FC560(0x47, 0x5360B);
    ((HudRenderState *)D_L11_001BEDC0)->text_scale = save;
    func_0027AB40();
}
