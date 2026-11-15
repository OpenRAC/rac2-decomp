/* func_L02_003FE8B8: draws the level's six HUD text boxes (layout table scaled by D_L02_001B3E04
 * and rounded), then per mode (data + 0x120 == 3, 5, 12, else) the titles, the time or count
 * through sprintf (func_00115DA8), and the boss bar (func_L02_003FE768). Twin of
 * func_L11_00444400.
 * one/k2/k3 are set-once label_y actives and three/three2/three3 set-once box constants; plain
 * &r90 lets gcse keep the rectangle in $s5. -frac2-frame-pointer-liveness lets flow2 drop the
 * dead `one` set in $fp. The label_y/label_y4/hud_coord dead-test helpers, set-once constant
 * locals, the nonempty do-while(0) groups and func_00300A00's bank-preserving argument order are
 * allowed by owner rulings (2026-11-08/09). */
#include "common.h"

typedef struct {
    u16 w[12];
} Rect;

extern s32 D_L02_001A904C[] __attribute__((sda));
extern f32 D_L02_001B3E04;
typedef struct {
    u8 pad[0xB0];
    f32 text_scale;
} HudRenderState;
extern u8 D_L02_001BEA00[];
extern char D_L02_001B1428[];
extern char D_L02_001B1430[];
extern s16 *D_L02_001B1190[] SDATA(D_L02_001B1190);
extern s32 D_L02_001B1358 __attribute__((sda));

extern s32 D_L02_001B13D8 __attribute__((sda));
extern s32 D_L02_001B13DC __attribute__((sda));
extern s32 D_L02_001B13E0 __attribute__((sda));
extern s32 D_L02_001B13E4[] __attribute__((sda));
extern s32 D_L02_001B13E8[] __attribute__((sda));
extern s32 D_L02_001B13EC[] __attribute__((sda));
extern s32 D_L02_001B13C0 __attribute__((sda));
extern s32 D_L02_001B13C4 __attribute__((sda));
extern s32 D_L02_001B13C8 __attribute__((sda));
extern s32 D_L02_001B13CC[] __attribute__((sda));
extern s32 D_L02_001B13D0[] __attribute__((sda));
extern s32 D_L02_001B13D4[] __attribute__((sda));
extern s32 D_L02_001B1378 __attribute__((sda));
extern s32 D_L02_001B137C __attribute__((sda));
extern s32 D_L02_001B1380 __attribute__((sda));
extern s32 D_L02_001B1384[] __attribute__((sda));
extern s32 D_L02_001B1388[] __attribute__((sda));
extern s32 D_L02_001B138C[] __attribute__((sda));
extern s32 D_L02_001B135C __attribute__((sda));
extern s32 D_L02_001B1360 __attribute__((sda));
extern s32 D_L02_001B1368 __attribute__((sda));
extern s32 D_L02_001B136C[] __attribute__((sda));
extern s32 D_L02_001B1370[] __attribute__((sda));
extern s32 D_L02_001B1374[] __attribute__((sda));
extern s32 D_L02_001B13A8 __attribute__((sda));
extern s32 D_L02_001B13AC __attribute__((sda));
extern s32 D_L02_001B13B0 __attribute__((sda));
extern s32 D_L02_001B13B4[] __attribute__((sda));
extern s32 D_L02_001B13B8[] __attribute__((sda));
extern s32 D_L02_001B13BC[] __attribute__((sda));
extern s32 D_L02_001B1390 __attribute__((sda));
extern s32 D_L02_001B1394 __attribute__((sda));
extern s32 D_L02_001B1398 __attribute__((sda));
extern s32 D_L02_001B139C[] __attribute__((sda));
extern s32 D_L02_001B13A0[] __attribute__((sda));
extern s32 D_L02_001B13A4[] __attribute__((sda));

extern s32 D_L02_001B13F0 __attribute__((sda));
extern s32 D_L02_001B13F4 __attribute__((sda));
extern s32 D_L02_001B13F8 __attribute__((sda));
extern s32 D_L02_001B13FC __attribute__((sda));
extern s32 D_L02_001B1400 __attribute__((sda));
extern f32 D_L02_001B1404 __attribute__((sda));
extern f32 D_L02_001B1408 __attribute__((sda));
extern f32 D_L02_001B140C __attribute__((sda));
extern f32 D_L02_001B1410 __attribute__((sda));
extern f32 D_L02_001B1414 __attribute__((sda));
extern f32 D_L02_001B1418 __attribute__((sda));
extern f32 D_L02_001B141C __attribute__((sda));
extern s32 D_L02_001B1420 __attribute__((sda));
extern s32 D_L02_001B1424 __attribute__((sda));

extern void UpdateViewContext(void);
extern void text_draw_window_small(Rect *, u64, char *, s32);
extern void text_draw_window_large(Rect *, u64, char *, s32);
extern void FontSetWindow(Rect *, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 IntToFloat(s32);
extern char *GetLocalizedString(s32);
extern void VU1_addGSregister(u32, u64);
extern void gfx_append_draw_list_packet_c(void);
extern void gfx_draw_scaled_object_two_axes(char *, f32, s32, f32, f32, f32, f32);
extern void hud_draw_boss_health_bar(f32);
extern char *table_find_by_id(s32, s32);
extern s32 func_001157AC(char *);
extern s32 sprintf(char *, char *, ...);


#define LBL0(id, c, xv, yv, a1, a2, a3, H, A) { char *ls = func_00336D50(D_L02_001A904C[0] + ofs, id); func_00300A00(ls, xv, c, (f32)label_y(ls, (f32)(yv), D_L02_001B3E04, H, A), a1, a2, a3); }
#define LBL4(id, c, xv, yv, a1, a2, a3, H, A) { char *ls = func_00336D50(D_L02_001A904C[0] + ofs, id); func_00300A00(ls, xv, c, (f32)label_y4(ls, (f32)(yv), D_L02_001B3E04, H, A), a1, a2, a3); }
#define TITLE(B, A) \
        LBL0(0x4C, D_L02_001B1424, D_L02_001B1410, D_L02_001B1414, -1.0f, D_L02_001B1404, 0.0f, half, B); \
        LBL0(0x4D, D_L02_001B1420, D_L02_001B1410, D_L02_001B1414, -1.0f, D_L02_001B1404, 0.0f, half, A)
#define LABEL(B, A) \
        LBL0(0x4C, D_L02_001B1424, D_L02_001B1408, D_L02_001B140C, D_L02_001B1404, 1.0f, 0.0f, half, B); \
        LBL0(0x4D, D_L02_001B1420, D_L02_001B1408, D_L02_001B140C, D_L02_001B1404, 1.0f, 0.0f, half, A)
#define LABEL50(A) \
        LBL4(0x50, D_L02_001B1420, D_L02_001B13FC, D_L02_001B1400, D_L02_001B1404, 1.0f, 0.0f, half, A)
#define SUM() \
            sum = 0; \
            for (obj = data + 0x90, i = 5; i >= 0; i--, obj += 4) { \
                sum += *(s32 *)obj; \
            }
#define DRAW(fn, r, s) \
            str = (s); \
            fn((r), D_L02_001B1358, str, func_001157AC(str))
#define DRAWBUF(fn, r) \
            { s32 c = D_L02_001B1358; s32 n = func_001157AC(buf); fn((r), c, buf, n); }
#define sprintf_n func_00115DA8

extern int D_L02_001B3E00;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L02_001B3E00;
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
    int mode = D_L02_001B3E00;
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

static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L02_001B3E00;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

/* Draws the heads-up display during a challenge: the time left or the score, the wave number and the boss health bar. */
void DrawMaktarChallengeHud(u8 *moby)
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
    f32 t;
    f32 half;
    s32 one;
    s32 k2;
    s32 k3;
    s32 x, y, h;
    char *str;
    s32 three;
    s32 three2;
    s32 three3;

    if (D_L02_001A904C[0] == 0) {
        return;
    }
    gfx_append_draw_list_packet_c();
    one = 1;
    half = 0.5f;
    data = *(u8 **)(moby + 0x68);
    x = hud_coord((f32)D_L02_001B13E0, D_L02_001B3E04, half);
    y = hud_coord((f32)D_L02_001B13E4[0], D_L02_001B3E04, half);
    h = hud_coord((f32)D_L02_001B13DC, D_L02_001B3E04, half);
    three = 3;
    FontSetWindow(&r50, x, y, D_L02_001B13E8[0], D_L02_001B13EC[0], D_L02_001B13D8, h, 0, three);
    x = hud_coord((f32)D_L02_001B13C8, D_L02_001B3E04, half);
    do { y = hud_coord((f32)D_L02_001B13CC[0], D_L02_001B3E04, half); } while (0);
    h = hud_coord((f32)D_L02_001B13C4, D_L02_001B3E04, half);
    FontSetWindow(&r70, x, y, D_L02_001B13D0[0], D_L02_001B13D4[0], D_L02_001B13C0, h, 0, three);
    x = hud_coord((f32)D_L02_001B1380, D_L02_001B3E04, half);
    k2 = 1;
    k3 = 1;
    do { t = (f32)D_L02_001B1384[0] * D_L02_001B3E04 + half; y = t; } while (0);
    h = hud_coord((f32)D_L02_001B137C, D_L02_001B3E04, half);
    FontSetWindow(&r90, x, y, D_L02_001B1388[0], D_L02_001B138C[0], D_L02_001B1378, h, 0, three);
    three2 = 3;
    x = hud_coord((f32)D_L02_001B1368, D_L02_001B3E04, half);
    do { t = (f32)D_L02_001B136C[0] * D_L02_001B3E04 + half; y = t; } while (0);
    do { h = hud_coord((f32)D_L02_001B1360, D_L02_001B3E04, half); } while (0);
    FontSetWindow(&rB0, x, y, D_L02_001B1370[0], D_L02_001B1374[0], D_L02_001B135C, h, 0, three);
    x = hud_coord((f32)D_L02_001B13B0, D_L02_001B3E04, half);
    do { t = (f32)D_L02_001B13B4[0] * D_L02_001B3E04 + half; y = t; } while (0);
    three3 = 3;
    FontSetWindow(&rF0, x, y, D_L02_001B13B8[0], D_L02_001B13BC[0], D_L02_001B13A8, hud_coord((f32)D_L02_001B13AC, D_L02_001B3E04, half), 0, three3);
    x = hud_coord((f32)D_L02_001B1398, D_L02_001B3E04, half);
    do { t = (f32)D_L02_001B139C[0] * D_L02_001B3E04 + half; y = t; } while (0);
    FontSetWindow(&rD0, x, y, D_L02_001B13A0[0], D_L02_001B13A4[0], D_L02_001B1390, hud_coord((f32)D_L02_001B1394, D_L02_001B3E04, half), 0, three2);
    save = ((HudRenderState *)D_L02_001BEA00)->text_scale;
    ((HudRenderState *)D_L02_001BEA00)->text_scale = 0.62f;
    UpdateViewContext();
    if (*(s16 *)(data + 0x120) == three2) {
        s32 ofs = 0x8710;
        TITLE(1, 1);
        sprintf_n(buf, D_L02_001B1428, 0x1E - *(s32 *)(data + 0xD4) / 60);
        DRAWBUF(text_draw_window_large, &r90);
        DRAW(text_draw_window_small, &rB0, GetLocalizedString(0x2F63));
        LABEL(k2, one);
        SUM();
        sprintf(buf, D_L02_001B1428, 15 * *(s16 *)(data + 0x122) + sum - *(s32 *)(data + 0x60));
        DRAWBUF(text_draw_window_large, &r50);
        DRAW(text_draw_window_small, &r70, GetLocalizedString(0x2F61));
    } else if (*(s16 *)(data + 0x120) == 5) {
        s32 ofs = 0x8710;
        TITLE(1, 1);
        sprintf_n(buf, D_L02_001B1428, 0x3C - *(s32 *)(data + 0xD4) / 60);
        DRAWBUF(text_draw_window_large, &r90);
        DRAW(text_draw_window_small, &rB0, GetLocalizedString(0x2F63));
        LABEL(k2, one);
        SUM();
        sprintf(buf, D_L02_001B1428, 15 * *(s16 *)(data + 0x122) + sum - *(s32 *)(data + 0x60));
        DRAWBUF(text_draw_window_large, &r50);
        DRAW(text_draw_window_small, &r70, GetLocalizedString(0x2F61));
    } else if (*(s16 *)(data + 0x120) == 0xC) {
        s32 ofs = 0x8710;
        TITLE(1, 1);
        n = 120 - *(s32 *)(data + 0xD4) / 60;
        sprintf(buf, D_L02_001B1428, n);
        if (n >= 100) {
            DRAWBUF(text_draw_window_small, &r90);
        } else {
            do { DRAWBUF(text_draw_window_large, &r90); } while (0);
        }
        DRAW(text_draw_window_small, &rB0, GetLocalizedString(0x2F63));
    } else {
        if (*(u8 **)(data + 0xD0) != 0) {
            s32 ofs = 0x8710;
            LABEL(k2, 1);
            LABEL50(1);
            obj = *(u8 **)(data + 0xD0);
            switch (*(s16 *)(obj + 0xAA)) {
            case 0x9F8 /* Chainblade */:
                pv = *(u8 **)(obj + 0x68);
                hud_draw_boss_health_bar(*(f32 *)(pv + 0x20) / IntToFloat(*(s16 *)(pv + 0x24)));
                LBL4(0x51, D_L02_001B13F0, D_L02_001B13F4, D_L02_001B13F8, D_L02_001B1404, 1.0f, 2.0f, half, k3);
                break;
            case 0xA44 /* B2 Brawler Legs */:
                pv = *(u8 **)(obj + 0x68);
                hud_draw_boss_health_bar(*(f32 *)(pv + 0x20) / IntToFloat(*(s16 *)(pv + 0x24)));
                LBL4(0x51, D_L02_001B13F0, D_L02_001B13F4, D_L02_001B13F8, D_L02_001B1404, 1.0f, 1.0f, half, k2);
                break;
            }
        }
        {
        s32 ofs = 0x8710;
        LBL0(0x4E, D_L02_001B1424, D_L02_001B1418, D_L02_001B141C, -1.0f, D_L02_001B1404, 0.0f, 0.5f, 1);
        LBL0(0x4F, D_L02_001B1420, D_L02_001B1418, D_L02_001B141C, -1.0f, D_L02_001B1404, 0.0f, 0.5f, 1);
        }
        sprintf(buf, D_L02_001B1430, *(s16 *)(data + 0x122) + 1, *D_L02_001B1190[*(s16 *)(data + 0x120)]);
        DRAWBUF(text_draw_window_large, &rF0);
        DRAW(text_draw_window_small, &rD0, GetLocalizedString(0x2F60));
    }
    VU1_addGSregister(0x47, 0x5360B);
    ((HudRenderState *)D_L02_001BEA00)->text_scale = save;
    UpdateViewContext();
}
