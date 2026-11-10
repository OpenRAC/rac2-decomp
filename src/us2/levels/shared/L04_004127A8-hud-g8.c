/* func_US2_L04_004127A8, the USA v2.00 copy of func_L04_00411298 (the race HUD: lap panels, record
 * time and the ranking list): the same C, where the lap cap becomes 3, the text ids move
 * (0x2F93 -> 0x2E29, 0x2FC6 -> 0x2E5C, 0x2F7F/0x2F80/0x2F81 -> 0x2E15/0x2E16/0x2E17,
 * 0x2F42 -> 0x2DD8, 0x2FB0 -> 0x2E46, 0x2F83 -> 0x2E19 in all four places), the bottom label is
 * drawn with func_0027FA10 at x 390 instead of func_0027F5B8 at 339, and the last row's time sits
 * at x 196 instead of 220. It needs -G8, so it has a unit of its own.
 * label_y and hud_coord are the template's HUD rounding helpers with dead display-mode tests
 * (allowed by owner ruling). The ranking list's 175 row passes the colour as label_y's handle (an
 * int cast to (void *), allowed by owner ruling) and `one`, a local holding 1, as `active` (allowed
 * by owner ruling); a literal 1 there is shared by cse with the later D_L04_001B0A24 == 1 test.
 * `half` holds the 0.5f rounding offset per row, so loop.c does not hoist it. */
#include "common.h"

extern u8 *D_L04_001B0914 __attribute__((sda));
extern s32 D_L04_001B08F8 __attribute__((sda));
extern s32 D_L04_001B090C __attribute__((sda));
extern s32 D_L04_001B093C __attribute__((sda));
extern s32 D_L04_001B0A24 __attribute__((sda));
extern s32 D_L04_001B0A28 __attribute__((sda));
extern s32 D_L04_001B0A2C __attribute__((sda));
extern s32 D_L04_001B0A38 __attribute__((sda));
extern f32 D_L04_001B0A30 __attribute__((sda));
extern f32 D_L04_001B0A34 __attribute__((sda));
extern f32 D_L04_001B2D44;
extern s32 D_L04_001A8FE8;
extern s32 D_001A7340, D_001A7B90;
extern u8 D_001A7A0A;
extern u8 *D_L04_001A904C;
typedef struct { u8 pad[0xB0]; f32 tangent; } HudCamera;
extern HudCamera D_L04_001BDB80;
typedef struct { s32 pad[2]; s32 times[14]; } RecordRow;
extern RecordRow D_L04_002C63C0[] NOT_SDA;
extern s32 D_L04_002CA1E0[] NOT_SDA;
extern char D_L04_001B0A40[] NOT_SDA, D_L04_001B0A50[] NOT_SDA;
extern char D_L04_001B0A58[] NOT_SDA, D_L04_001B0A70[] NOT_SDA;
extern char D_L04_001B0A88[] NOT_SDA, D_L04_001B0A98[] NOT_SDA;
extern char D_L04_001B0AA8[] NOT_SDA, D_L04_001B0AC0[] NOT_SDA;
extern f32 func_00283180(f32), func_00283198(f32);
extern void func_0027AB40(void);
extern s32 func_L04_0040A1D0(s32);
extern void *func_00336D50(void *, s32);
extern void func_00300A00(void *, s32, f32, f32, f32, f32, f32);
extern char *func_00288FB8(s32);
extern s32 func_001157AC(char *);
extern s32 func_00115DA8(char *, char *, ...);
extern s32 func_0027FAA8(s32, s32, u64, char *, s32);
extern void func_0027F5B8(s32, s32, u64, char *, s32);
extern void func_0027FA10(s32, s32, u64, char *, s32);
extern s32 func_0027FB40(s32, s32, u64, char *, s32);
extern s32 func_00283D38(s32, s32, f32);
extern s32 func_002E5CF8(s32, s32, void *);
extern void func_002FC560(u32, u64);

extern int D_L04_001B2D40;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
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

static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L04_001B2D40;
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

s32 func_US2_L04_004127A8(void) {
    char text[64];
    u8 *object = D_L04_001B0914;
    u8 *state = *(u8 **)(object + 0x68);
    s32 row = 0, bottom, ahead, playerSeen = 0;
    s32 rank, time, y, lap, flag;
    u8 *racer;
    f32 alpha, fy, angle, fade;
    char *str, *str2, *str3;
    void *sprite;
    f32 fbottom;
    s32 color1, color2;
    s32 color;
    f32 half;
    s32 one;
    if (D_L04_001B08F8 < 10) D_L04_001B0A38 = 0;
    if (*(s32 *)(state + 0x320) >= 10) {
        if (D_L04_001B08F8 < 601) {
            D_L04_001B0A30 = 0;
            D_L04_001B0A34 = 0;
            D_L04_001B0A28 = 0;
            D_L04_001B0A2C = 0;
            goto tick;
        }
        goto animate;
    }
    if (D_L04_001B0A38) {
animate:
        if (!D_L04_001B0A28) D_L04_001B0A30 += 0.41666669f;
        if (!D_L04_001B0A2C) D_L04_001B0A34 += 0.41666669f;
    } else {
        D_L04_001B0A30 = 0;
        D_L04_001B0A34 = 0;
        D_L04_001B0A28 = 0;
        D_L04_001B0A2C = 0;
    }
tick:
    if (D_L04_001B08F8 % 15 == 0) {
        D_L04_001B0A24++;
        if (D_L04_001B0A24 >= 4) D_L04_001B0A24 = 0;
    }
    angle = 0.56217057f;
    D_L04_001BDB80.tangent = func_00283198(angle) / func_00283180(angle);
    func_0027AB40();
    flag = *(s32 *)(state + 0x320);
    if (flag == 1) {
        lap = func_L04_0040A1D0(D_L04_001B090C);
        if (lap > 3) lap = 3;
        sprite = func_00336D50(D_L04_001A904C + 0x8710, 0x39);
        func_00300A00(sprite, 0x60442D00, (f32)(D_001A7340 / 2), (f32)label_y(sprite, 194.0f, D_L04_001B2D44, 0.5f, 1), 0.92f, D_001A7B90 ? 0.9f : 0.92f, 0.0f);
        sprite = func_00336D50(D_L04_001A904C + 0x8710, 0x38);
        func_00300A00(sprite, 0x55F0C070, (f32)(D_001A7340 / 2), (f32)label_y(sprite, 194.0f, D_L04_001B2D44, 0.5f, 1), 0.92f, D_001A7B90 ? 0.9f : 0.92f, 0.0f);
        { char *str_ = func_00288FB8(0x2e29); int x_ = D_001A7340 / 2; int row_ = label_y((void *)x_, 32.0f, D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FAA8(x_, row_, 0x80F0F0F0ULL, str_, len_); }
        if (D_L04_001B093C > 0) {
            { int x_ = D_001A7340 / 2; int row_ = label_y((void *)x_, 65.0f, D_L04_001B2D44, 0.5f, 1); char *str_ = func_00288FB8(0x1233); func_0027FAA8(x_, row_, 0x80F0F0F0ULL, str_, -1); }
            D_L04_001B093C--;
        } else if (D_L04_002C63C0[D_L04_001B090C].times[lap - 1]) {
            s32 recordTime;
            char *recordFormat = func_00288FB8(0x2e5c);
            recordTime = D_L04_002C63C0[D_L04_001B090C].times[lap - 1];
            if (D_001A7A0A) recordTime *= 10;
            { int n_ = func_00115DA8(text, recordFormat, recordTime); int x_ = D_001A7340 / 2; int row_ = label_y((void *)x_, 65.0f, D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(text); func_0027FAA8(x_, row_, 0x80F0F0F0ULL, text, len_); }
        }
    }
    bottom = 315 - (s32)D_L04_001B0A34;
    if (bottom <= 156) bottom = 157;
    if (bottom == 157) D_L04_001B0A2C = 1;
    flag = 1;
    fbottom = (f32)bottom;
    alpha = (1.0f - (315.0f - fbottom) * 0.006329114f) * 0.72f + 0.08f;
    sprite = func_00336D50(D_L04_001A904C + 0x8710, 0x47);
    func_00300A00(sprite, 0x60442D00, (f32)(D_001A7340 / 2), (f32)label_y(sprite, 196.0f, D_L04_001B2D44, 0.5f, 1), 0.92f, D_001A7B90 ? 0.9f : 0.92f, alpha);
    sprite = func_00336D50(D_L04_001A904C + 0x8710, 0x46);
    func_00300A00(sprite, 0x55F0C070, (f32)(D_001A7340 / 2), (f32)label_y(sprite, 196.0f, D_L04_001B2D44, 0.5f, 1), 0.92f, D_001A7B90 ? 0.9f : 0.92f, alpha);
    { int x_, row_, len_; func_00115DA8(text, D_L04_001B0A40, func_00288FB8(0x2e15),
        func_00288FB8(D_L04_002CA1E0[*(s32 *)(state + 0x320) - 1]), func_00288FB8(0x2e16));
      x_ = D_001A7340 / 2; row_ = label_y((void *)x_, 106.0f, D_L04_001B2D44, 0.5f, 1); len_ = func_001157AC(text); func_0027FAA8(x_, row_, 0x80F0F0F0ULL, text, len_); }
    { int row_ = hud_coord(fbottom, D_L04_001B2D44, 0.5f); char *str_ = func_00288FB8(0x2dd8); func_0027FA10(390, row_, 0x80F0F0F0ULL, str_, -1); }
    y = 138;
    ahead = 0;
    racer = *(u8 **)(state + 0x39C);
    D_L04_001B0A38 = flag;
    while (racer) {
        s32 scroll = (s32)D_L04_001B0A30 - 138;
        fade = 0.1f;
        one = 1;
        rank = 0;
        time = 0;
        y = row * 15 - scroll;
        if (*(s16 *)(racer + 0xAA) == 0xBBC) {
            if (y <= 138) { y = 138; D_L04_001B0A28 = 1; }
            rank = *(s32 *)(state + 0x320);
            time = D_L04_001A8FE8;
            playerSeen = 1;
            racer = *(u8 **)(state + 0x3A0);
        } else if (*(s16 *)(racer + 0xAA) == 0xB2D) {
            u8 *rs = *(u8 **)(racer + 0x68);
            rank = *(u8 *)(rs + 0xA2);
            time = *(s32 *)(rs + 0x1A0);
            racer = *(u8 **)(rs + 0x1A4);
            if (rank > 10) continue;
            if (*(s32 *)(state + 0x320) < rank) {
                s32 projected = D_L04_001A8FE8 + D_L04_001B08F8;
                if (projected < time) { D_L04_001B0A38 = 0; ahead++; }
                if (time == projected) func_002E5CF8(22, 17, object);
            }
        }
        if (y < 128) { if (rank <= 10) row++; continue; }
        if (y > bottom - 10) continue;
        if (rank == *(s32 *)(state + 0x320)) { color2 = 0x8000C0C0; color1 = 0x8000C0C0; }
        else { color2 = 0x80F0F0F0; color1 = 0xF0F0F0; }
        if (y < 138) {
            color = func_00283D38(color1, color2, ((f32)y - 128.0f) * fade);
        }
        else if (*(s32 *)(state + 0x320) < rank && bottom - y <= 20)
        {
            color = func_00283D38(color1, color2, (f32)(bottom - y - 10) * fade);
        }
        else { color = color2; }
        fy = (f32)y;
        func_00115DA8(text, D_L04_001B0A50, func_00288FB8(D_L04_002CA1E0[rank - 1]), func_00288FB8(0x2e17));
        half = 0.5f;
        func_0027FB40(175, label_y((void *)color, fy, D_L04_001B2D44, half, one), (s64)color, text, -1);
        if (ahead > 0) {
            if (D_L04_001B0A24 == 3 || ahead >= 2) func_00115DA8(text, D_L04_001B0A58, func_00288FB8(0x2e46));
            else if (D_L04_001B0A24 == 2) func_00115DA8(text, D_L04_001B0A70, func_00288FB8(0x2e46));
            else if (D_L04_001B0A24 == 1) func_00115DA8(text, D_L04_001B0A88, func_00288FB8(0x2e46));
            else func_00115DA8(text, D_L04_001B0A98, func_00288FB8(0x2e46));
        } else {
            if (time / 60 % 60 < 10)
                func_00115DA8(text, D_L04_001B0AA8, func_00288FB8(0x2e19), time / 216000, time / 3600 % 60, time / 60 % 60, time / 6 % 10);
            else
                func_00115DA8(text, D_L04_001B0AC0, func_00288FB8(0x2e19), time / 216000, time / 3600 % 60, time / 60 % 60, time / 6 % 10);
        }
        half = 0.5f;
        func_0027F5B8(220, hud_coord(fy, D_L04_001B2D44, half), (s64)color, text, -1); row++;
        if (row >= 10) break;
    }
    if (*(s32 *)(state + 0x320) > 10 && !D_L04_001B0A28 && !playerSeen) {
        func_00115DA8(text, D_L04_001B0A50, func_00288FB8(D_L04_002CA1E0[*(s32 *)(state + 0x320) - 1]), func_00288FB8(0x2e17));
        y += 15;
        { int row_ = hud_coord((f32)y, D_L04_001B2D44, 0.5f); func_0027FB40(175, row_, 0x8000C0C0ULL, text, -1); }
        if (D_L04_001A8FE8 / 60 % 60 < 10)
            func_00115DA8(text, D_L04_001B0AA8, func_00288FB8(0x2e19), D_L04_001A8FE8 / 216000, D_L04_001A8FE8 / 3600 % 60, D_L04_001A8FE8 / 60 % 60, D_L04_001A8FE8 / 6 % 10);
        else
            func_00115DA8(text, D_L04_001B0AC0, func_00288FB8(0x2e19), D_L04_001A8FE8 / 216000, D_L04_001A8FE8 / 3600 % 60, D_L04_001A8FE8 / 60 % 60, D_L04_001A8FE8 / 6 % 10);
        { int row_ = hud_coord((f32)y, D_L04_001B2D44, 0.5f); func_0027F5B8(196, row_, 0x8000C0C0ULL, text, -1); }
    }
    if (*(u8 *)(object + 0x20) != 3) {
        f32 angle;
        angle = *(f32 *)(state + 0x28C) * 0.008726647f;
        D_L04_001BDB80.tangent = func_00283198(angle) / func_00283180(angle);
        func_0027AB40();
    }
    func_002FC560(0x47, 0x5360B);
    return 1;
}
