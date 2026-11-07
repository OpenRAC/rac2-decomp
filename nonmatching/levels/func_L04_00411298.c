/* 7 November 2026, label_y sweep: the sprite ys use label_y(sprite, ...), the 32/65-row texts label_y(str, ...), the bottom row label_y(text, fbottom, ...): 217 -> 135 differences, 3732/3732 bytes, first difference +0x178 -> +0x2DC (label_y(text) on the 65/106 rows: worse). The body below is the retained C with that change (label_y is
 * the accepted HUD label idiom, definition as in src/levels/15_gorn/L15_00431590-g8.c). Counts are
 * masked aligned instruction differences from a cc1 -S diff harness, not check.py rows. */
/*
 * Tier: opus-1 (Claude Opus 5.5 xhigh), task v1879, 31 October 2026. Retained near miss, USA v1.01.
 * Game profile: -O2 -G8 -ffunction-sections in a dedicated -g8.c unit (e.g. L04_0040F8F0-hud-g8.c).
 * Final check.py: 3732/3732 bytes, 0 of 2 places (04 Barlow, 11 Joba); 370 lines in a relocation-masked
 * two-sided diff, nearly all scheduling and register choice. No linked build; not a match. PAL and v2.00
 * have no catalogue row under this name. About 23 check.py compiles and 2 regalloc.py runs.
 *
 * All declarations it needs follow. Everything below is admissible wording. Corrected against earlier drafts:
 * - Table is a 64-byte row with times at +8, indexed lap - 1: retail forms base, then base + 8, and (lap-1)*4.
 * - One local (flag here) holds state->0x320 for the == 1 test. flag = 1 with D_L04_001B0A38 = flag gives
 *   retail's addiu $s3,1 and sw $s3. See below: retail's source probably just stores 1.
 * - time / 60 % 60 is a block-scoped local (seconds, $s0), reused as the sprintf argument.
 * - alpha is one expression over (f32)bottom, which stays in $f24; 1.0f is then a temporary, as in retail.
 * - No panelX/panelY locals: (f32)(D_001A7340 / 2) and the rounding are direct arguments.
 * - D_L04_001B2D44 and D_L04_001A8FE8 want one MACRO_ADDR declaration (`lui $at` in ordinary flow, $gp in a
 *   delay slot, automatically). That is the truthful form and the probes below use it, but it needs the right
 *   delay-slot filling: this plain C then gives 3736. The _gp aliases are only what keeps plain C at 3732.
 *
 * What still differs, all one cause: retail ends a basic block after each scale-and-round, and the boundary
 * survives sched2. Same family as func_L04_00416E38, func_0033A520, func_0033C028, func_002900B8.
 * Read from retail and measured here (compile with cc1 -dS -dR and read the scheduling tables):
 * - Boundary is after the fix, before (f32)y. In panels 2 and 4 the D_001A7B90 load sits between mfc1 $v1,$f1 and
 *   mtc1 $v1,$f13; in panels 1 and 3 li.s 0.92 takes the memory slot first, so y and the load can share $v0.
 *   Placing the test before the fix is worse (load moves ahead of the fix). Nothing bounds the start of a
 *   rounding: 194.0, 0.5, 2 and 0x8710 float above the calls, so it is not do/while (LOOP_BEG would stop them).
 * - Do/while note barrier (not admissible): an empty do { } while (0) in an inline helper after the fix gives
 *   3740 bytes and 270 diff lines, but the note makes (f32)y the first insn after it, and retail has 0.92 and
 *   the D_001A7B90 load before (f32)y, so a note is the wrong mechanism; it is a label.
 * - NEW, the test compares with the constant 1. A compare against a small constant leaves nothing: sched1 floats
 *   the constant above the call, so it takes a saved register, and flow2 deletes it with the test. With
 *     #define HUD_Y(v) ({ s32 r_ = (s32)((v) + 0.5f); if (r_ == 1) fy = 0.0f; r_; })
 *   in the arm and panels and a PLAIN D_L04_001B0A38 = 1, retail's addiu $s3,1 and sw $s3 appear with no extra
 *   local (cse reuses that pseudo for the store), and lap moves to $s4 as in retail. This also explains why $s3
 *   is skipped in the arm, and is one more candidate for the saved-but-unused registers of the sibling near
 *   misses. A placeholder test and dead store: a shape probe only, 295 diff lines, 3720 bytes. Do not land it.
 * - Tested value: not y. Testing y gives y three references, so y takes $s0 and x $s1; retail has x in $s0, y
 *   in $s1, and sra $s0,$v1,1. Testing the $s3 local itself fails: cse knows it is 1 and folds the test.
 * - Single-set arms become movn at jump1 and leave no block; a float set keeps the branch. An if/else (measured
 *   with func_002D3D88's helper, mode = D_L04_001B2D40, an assumed address) gives 3976: the cse table flushes, so
 *   0.92 and the scale constants rematerialize, and the load stays. It does give retail's sprite in $a2.
 * - What is missing: the probe's arm is dead at flow1, so the jump is at .+1 in flow2 and is gone before sched2,
 *   which then hoists 0.92 above the call and argument moves above the chain (loop rows). With the arm on all
 *   sites: 318 lines, 3724 bytes, and sd $a2,0x58($sp) already right. Retail needs an arm with a real insn at
 *   flow2's CFG build that dies in flow2's life analysis or at jump2. No natural construct found. Sprite stays
 *   in $a0 in the probes (retail $a2): perhaps the fix's scratch:SI (local-alloc) when $v0 and $v1 are both busy.
 * Next: an arm live at flow1 and dead only after reload, on a compare with 1 of something other than y.
 */
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
extern f32 D_L04_001B2D44_gp SDATA(D_L04_001B2D44);
extern s32 D_L04_001A8FE8;
extern s32 D_L04_001A8FE8_gp SDATA(D_L04_001A8FE8);
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

s32 func_L04_00411298(void) {
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
        if (lap > 2) lap = 2;
        sprite = func_00336D50(D_L04_001A904C + 0x8710, 0x39);
        func_00300A00(sprite, 0x60442D00, (f32)(D_001A7340 / 2), (f32)label_y(sprite, 194.0f, D_L04_001B2D44, 0.5f, 1), 0.92f, D_001A7B90 ? 0.9f : 0.92f, 0.0f);
        sprite = func_00336D50(D_L04_001A904C + 0x8710, 0x38);
        func_00300A00(sprite, 0x55F0C070, (f32)(D_001A7340 / 2), (f32)label_y(sprite, 194.0f, D_L04_001B2D44, 0.5f, 1), 0.92f, D_001A7B90 ? 0.9f : 0.92f, 0.0f);
        str = func_00288FB8(0x2F93);
        func_0027FAA8(D_001A7340 / 2, label_y(str, 32.0f, D_L04_001B2D44, 0.5f, 1), 0x80F0F0F0ULL, str, func_001157AC(str));
        if (D_L04_001B093C > 0) {
            func_0027FAA8(D_001A7340 / 2, label_y(str, 65.0f, D_L04_001B2D44_gp, 0.5f, 1), 0x80F0F0F0ULL, func_00288FB8(0x1233), -1);
            D_L04_001B093C--;
        } else if (D_L04_002C63C0[D_L04_001B090C].times[lap - 1]) {
            s32 recordTime;
            char *recordFormat = func_00288FB8(0x2FC6);
            recordTime = D_L04_002C63C0[D_L04_001B090C].times[lap - 1];
            if (D_001A7A0A) recordTime *= 10;
            func_00115DA8(text, recordFormat, recordTime);
            func_0027FAA8(D_001A7340 / 2, (s32)(D_L04_001B2D44 * 65.0f + 0.5f), 0x80F0F0F0ULL, text, func_001157AC(text));
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
    func_00115DA8(text, D_L04_001B0A40, func_00288FB8(0x2F7F),
        func_00288FB8(D_L04_002CA1E0[*(s32 *)(state + 0x320) - 1]), func_00288FB8(0x2F80));
    func_0027FAA8(D_001A7340 / 2, (s32)(D_L04_001B2D44 * 106.0f + 0.5f), 0x80F0F0F0ULL, text, func_001157AC(text));
    func_0027F5B8(339, label_y(text, fbottom, D_L04_001B2D44, 0.5f, 1), 0x80F0F0F0ULL, func_00288FB8(0x2F42), -1);
    y = 138;
    ahead = 0;
    racer = *(u8 **)(state + 0x39C);
    D_L04_001B0A38 = flag;
    while (racer) {
        s32 scroll = (s32)D_L04_001B0A30 - 138;
        fade = 0.1f;
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
            racer = *(u8 **)(rs + 0x1A4);
            time = *(s32 *)(rs + 0x1A0);
            if (rank > 10) goto next;
            if (*(s32 *)(state + 0x320) < rank) {
                s32 projected = D_L04_001A8FE8_gp + D_L04_001B08F8;
                if (projected < time) { D_L04_001B0A38 = 0; ahead++; }
                if (time == projected) func_002E5CF8(22, 17, object);
            }
        }
        if (y < 128) { if (rank <= 10) row++; goto next; }
        if (y > bottom - 10) goto next;
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
        func_00115DA8(text, D_L04_001B0A50, func_00288FB8(D_L04_002CA1E0[rank - 1]), func_00288FB8(0x2F81));
        func_0027FB40(175, (s32)(fy * D_L04_001B2D44 + 0.5f), (s64)color, text, -1);
        if (ahead > 0) {
            if (D_L04_001B0A24 == 3 || ahead >= 2) func_00115DA8(text, D_L04_001B0A58, func_00288FB8(0x2FB0));
            else if (D_L04_001B0A24 == 2) func_00115DA8(text, D_L04_001B0A70, func_00288FB8(0x2FB0));
            else if (D_L04_001B0A24 == 1) func_00115DA8(text, D_L04_001B0A88, func_00288FB8(0x2FB0));
            else func_00115DA8(text, D_L04_001B0A98, func_00288FB8(0x2FB0));
        } else {
            s32 seconds = time / 60 % 60;
            if (seconds < 10)
                func_00115DA8(text, D_L04_001B0AA8, func_00288FB8(0x2F83), time / 216000, time / 3600 % 60, seconds, time / 6 % 10);
            else
                func_00115DA8(text, D_L04_001B0AC0, func_00288FB8(0x2F83), time / 216000, time / 3600 % 60, seconds, time / 6 % 10);
        }
        row++;
        func_0027F5B8(220, (s32)(fy * D_L04_001B2D44_gp + 0.5f), (s64)color, text, -1);
next:
        if (row >= 10) break;
    }
    if (*(s32 *)(state + 0x320) > 10 && !D_L04_001B0A28 && !playerSeen) {
        func_00115DA8(text, D_L04_001B0A50, func_00288FB8(D_L04_002CA1E0[*(s32 *)(state + 0x320) - 1]), func_00288FB8(0x2F81));
        y += 15;
        func_0027FB40(175, (s32)((f32)y * D_L04_001B2D44 + 0.5f), 0x8000C0C0ULL, text, -1);
        if (D_L04_001A8FE8 / 60 % 60 < 10)
            func_00115DA8(text, D_L04_001B0AA8, func_00288FB8(0x2F83), D_L04_001A8FE8 / 216000, D_L04_001A8FE8 / 3600 % 60, D_L04_001A8FE8 / 60 % 60, D_L04_001A8FE8 / 6 % 10);
        else
            func_00115DA8(text, D_L04_001B0AC0, func_00288FB8(0x2F83), D_L04_001A8FE8 / 216000, D_L04_001A8FE8 / 3600 % 60, D_L04_001A8FE8 / 60 % 60, D_L04_001A8FE8 / 6 % 10);
        func_0027F5B8(220, (s32)((f32)y * D_L04_001B2D44 + 0.5f), 0x8000C0C0ULL, text, -1);
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
