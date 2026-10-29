/* Retained selection-panel drawing, 2026-10-28: best 736/752 bytes, 0/1 US.
 * Four bounded trials: initial792/frame110; explicit message paths plus
 * no-split-addresses736/frameE0 versus retailF0. Real64-bit style local and
 * narrow no-regmove tie736; stop after three identical outputs.
 * Retail saves S2 without a visible later S2 use and allocates private state
 * toS3. C usesS2 for state and drops one saved register; other call scheduling
 * and conditional-message differences remain. No artificial register pins.
 * Text layout is twelve 16-bit fields24B with real 16-byte-aligned 32-byte stack slot;
 * initializer writes all fields, raw27FC70 reads through +0x16 (the last halfword).
 * The text buffer spans 112 bytes at sp+0x30..0x9F, formatted before strlen/draw.
 * Message lookup returns32-bit address; font handles/style scalar words
 * are 64-bit arguments, not dummy prototypes. 27F640 uses fiveGPR
 * and threeFP banks; its actual808B body was audited. No C matching credit.
 */
#include "common.h"
extern void func_L11_00443940(void *, int);
extern s32 func_00288FB8(s32);
extern u64 func_0027C878(int);
extern void func_0027F640(float, float, float, u64, u8 *, int, u64, void *);
extern void func_002802E0(u16 *, int, int, int, int, int, int, int, int);
extern void func_00280270(u16 *, u64, u8 *, int);
extern void func_00280190(u16 *, u64, u8 *, int);
extern unsigned int func_001157AC(const char *);
extern int func_00115DA8(char *, const char *, ...);
extern int func_L11_0043E108(unsigned int);
extern u8 D_001395B8[];
extern u8 D_L11_002A3AD0[];
extern const char D_L11_001B15A0[];
extern float D_L11_001B3E04 NOT_SDA;
extern int D_L11_001B1834 NOT_SDA;
extern int D_L11_001B1838 NOT_SDA;
extern int D_L11_001B183C NOT_SDA;
extern float D_L11_001B1808_gp SDATA(D_L11_001B1808);
extern int D_L11_001B180C_gp SDATA(D_L11_001B180C);
extern int D_L11_001B1810_gp SDATA(D_L11_001B1810);
extern int D_L11_001B1814_gp SDATA(D_L11_001B1814);
extern int D_L11_001B1818_gp SDATA(D_L11_001B1818);
extern int D_L11_001B181C_gp SDATA(D_L11_001B181C);
extern int D_L11_001B1820_gp SDATA(D_L11_001B1820);
extern int D_L11_001B1824_gp SDATA(D_L11_001B1824);
extern int D_L11_001B1828_gp SDATA(D_L11_001B1828);
extern int D_L11_001B182C_gp SDATA(D_L11_001B182C);
extern int D_L11_001B1830_gp SDATA(D_L11_001B1830);
extern int D_L11_001B1840_gp SDATA(D_L11_001B1840);

/* Font layout initializer/consumer agree on twelve 16-bit fields (24B); its
 * real aligned32B slot precedes the112B text buffer. All twelve fields are
 * initialized before text draw. Title font/style arguments are actually64-bit.
 * Canonical lookup returns s32 address words, not fabricated pointer returns. */
void func_L11_004456A0(u8 *object)
{
    u16 layout[12] __attribute__((aligned(16)));
    char buffer[112];
    u8 *state;
    u8 *text, *first, *last;
    u64 font, color;
    int message_id;
    float x, y;
    func_L11_00443940(object, 0);
    state = *(u8 **)(object + 0x68);
    text = (u8 *)func_00288FB8(0x2F45);
    y = (float)(int)((float)D_L11_001B1814_gp * D_L11_001B3E04 + 0.5f);
    x = (float)D_L11_001B1810_gp;
    color = D_L11_001B180C_gp;
    font = func_0027C878(1);
    func_0027F640(x, y, D_L11_001B1808_gp, (u64)color, text, -1, font, D_L11_002A3AD0);
    func_002802E0(layout,
        (int)((float)D_L11_001B1830_gp * D_L11_001B3E04 + 0.5f),
        (int)((float)D_L11_001B1834 * D_L11_001B3E04 + 0.5f),
        D_L11_001B1838, D_L11_001B183C, D_L11_001B181C_gp,
        (int)((float)D_L11_001B1820_gp * D_L11_001B3E04 + 0.5f), D_L11_001B1840_gp, 3);
    if (*(s16 *)(state + 0x1E8) == 0 && D_001395B8[func_L11_0043E108(0)] < 2) {
        message_id = 0x2F96;
        goto simple;
    }
    if (*(s16 *)(state + 0x1E8) == 1 && D_001395B8[func_L11_0043E108(1)] < 2) {
        message_id = 0x2F97;
        goto simple;
    }
    first = (u8 *)func_00288FB8(0x2F62);
    last = (u8 *)func_00288FB8(0x2F5E);
    func_00115DA8(buffer, D_L11_001B15A0, first, *(int *)(state + 0x1E0), last);
    color = D_L11_001B1818_gp;
    func_00280270(layout, (u64)color, (u8 *)buffer, func_001157AC(buffer));
    goto footer;
simple:
    text = (u8 *)func_00288FB8(message_id);
    color = D_L11_001B1818_gp;
    func_00280270(layout, (u64)color, text, func_001157AC((char *)text));
footer:
    text = (u8 *)func_00288FB8(0x2F47);
    func_002802E0(layout,
        (int)((float)D_L11_001B1830_gp * D_L11_001B3E04 + 0.5f),
        (int)((float)D_L11_001B1834 * D_L11_001B3E04 + 0.5f),
        D_L11_001B1838, D_L11_001B183C, D_L11_001B1828_gp,
        (int)((float)D_L11_001B182C_gp * D_L11_001B3E04 + 0.5f), D_L11_001B1840_gp, 3);
    color = D_L11_001B1824_gp;
    func_00280190(layout, (u64)color, text, func_001157AC((char *)text));
}
