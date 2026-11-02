/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/*
 * Claude Opus 5.5 (xhigh), task v1820, USA v1.01. Replaces the 3300-byte draft from v1754.
 * Game -O2 -G8 -ffunction-sections, in its own -g8.c unit (for example
 * src/levels/10_hrugis_cloud/L10_003170D0-menu-g8.c; no cflags line needed):
 * 3440/3420 bytes, 0/1 places. Relocation-masked sequence alignment: 802 of retail's 855
 * instructions (the v1754 draft scores 517 on the same script). No linked build was run.
 * No exact-bytes form was found with any wording, admissible or not.
 *
 * Main finding: the "block boundary with no instruction" in MenuRow is a vanished no-else test,
 * `row = (s32)scaled; if (D_L10_001B2D80 == 1) <body that flow1 deletes>`. The flow1, sched1 and
 * flow2 points were read in the gcse, sched and sched2 dumps; the cse points are inferred from bytes:
 * - The body has to be a set that cse cannot delete: `scaled` qualifies because it was already
 *   used by the conversion. Testing before the conversion loses the row: a `y` or unused-local
 *   body dies in cse, so jump removes the test before flow.
 * - The test is single-use and has no label in its body, so cse skips it and 200.0f, 0.5f, 1.0f,
 *   0.0f and 0x8710 stay shared. An `a && b` test gives the label two uses and loses the sharing.
 * - Flow1 deletes the body; sched1 and local-alloc still see the jump, the mode load and the 1.
 *   That alone gives retail's $v1 row, $f20-$f24, $s1, chain registers and the $s3 = 1 hoist.
 * - Flow2 then deletes the jump (tidy_fallthru_edge), merges the blocks and deletes the mode and
 *   1 loads, so this test can read a global and leave no word. This refines the rule in
 *   WORKER2.md, which covers tests that survive until jump2.
 *
 * What still differs, nearly all from one cause: retail keeps a block boundary at this test
 * through sched2, and this draft does not, because flow2 merged the blocks. So sched2 interleaves
 * the row with later arguments, which changes argument order and breaks tail merges such as case
 * 1's locked label into case 2's (20 extra bytes overall, net of 5 words).
 * Diagnostic, not admissible and not kept: the empty `do { } while (0);` after the test in
 * MENU_ROW adds loop notes, a sched2 barrier. It scores 833/855 at 3444 bytes. It has 7 more nops
 * than retail (48 against 41) at labels aligned by `.p2align 3`, for a net 6 surplus words; retail
 * has no such nops, so loop notes are probably not what retail had. `while (0) ;` and
 * `for (;0;) ;` score the same. What else differs: the order of 0.0f, %lo($a1) and $f12 in the
 * 200.0f rows, and a final row's argument order. With the test inside the do-while it scores 773.
 * Next: find what keeps that boundary through flow2 with no word left. It cannot be a jump
 * reading the mode load, since that load would then stay. flow.c merges unless the label has a
 * second predecessor or cannot be deleted.
 *
 * Unproven choices, for review:
 * - The body's `scaled + 1.0f` leaves no trace in retail: the test is measured, its body is a
 *   guess. A test whose body is dead may not be admissible; maintainers have not ruled on it.
 * - D_L10_001B1394/98/9C are volatile. Retail reads them with a lui/lw pair and leaves the branch
 *   slots empty, and volatile reproduces both. Plain, NOT_SDA, nosda and array forms fill the slot
 *   or split the load. Retail never rereads one on a path, so the guide's volatile test is not
 *   shown to be met. D_L10_001B1390 cannot be volatile: retail loads it in a delay slot.
 * - func_L05_00303000 returns s32 here. This gives retail's $v1 index and $v0 slti, because the
 *   call's value makes $v0 unavailable. Its epilogue leaves $v0 from its last call, which fits
 *   but does not prove a return value.
 * - MENU_ROW is a macro because an inline adds a copy of the row (`mfc1 $a1; daddu $s0, $a1`),
 *   7 extra words. Its local `y` gives retail's $f0 constant and $f1 chain.
 *
 * Ruled out (measured): -mno-split-addresses, -fno-schedule-insns2, -g,
 * -frac2-keep-block-order, -frac2-gcse-unsplit-edges, -frac2-no-null-pointer-checks, a -G0 unit;
 * an inline reward helper and ternary index forms (movn, not retail's movz).
 * All required declarations follow.
 */
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
    }

s32 func_L10_004227A0(void) {
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
