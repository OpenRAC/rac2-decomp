/* functional: high. Same reads, writes and calls as retail; near miss restructured only in register use. */
/* func_002C9CF8 (356 bytes, 28 places) - M27 near miss: 352/356 B, default flags.
 *
 * Everything but two spots is instruction-exact: retail holds the constant 1 in $v1 and
 * D_001A8BB0 in $v0 around the `open` store (here swapped), and the tail's six zero
 * stores go through `$v1`, a copy of the pause-state base `$s0` (`daddu $v1,$s0,$zero`)
 * while the mode store and the last two use $s0 itself. A pointer local for those
 * stores (block or function scope, before or after the mode store), a static
 * (inline) helper taking the base, and MACRO_ADDR/plain forms of D_001A8BB0 all
 * leave 352 B.
 */
#include "common.h"

typedef struct Menu_2C9CF8 {
    u8 pad00[0x38];
    struct Menu_2C9CF8 *next;
    struct Menu_2C9CF8 *prev;
} Menu_2C9CF8;

typedef struct {
    s32 open;
    u8 pad04[4];
    s32 mode;
    u8 pad0C[0x1C - 0xC];
    s32 f1C;
    s32 f20;
    u8 pad24[0xDB - 0x24];
    u8 fDB;
    u8 padDC[0xE8 - 0xDC];
    s32 wide;
    u8 padEC[0x104 - 0xEC];
    s32 forced;
    s32 f108;
    u8 pad10C[0x120 - 0x10C];
    s32 f120;
    u8 pad124[0x144 - 0x124];
    s32 f144;
    s32 f148;
    s32 f14C;
    s32 f150;
    u8 pad154[0x1C0 - 0x154];
    s32 f1C0;
    s32 f1C4;
    s32 f1C8;
} Pause_2C9CF8;

extern Pause_2C9CF8 D_001F2840;
extern s32 D_001A8BB0[] __attribute__((sda));
extern u32 D_001A7A08[] __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));
extern s32 D_0025B5F8;
extern Menu_2C9CF8 D_00259918;
extern Menu_2C9CF8 D_00259AA8;
extern Menu_2C9CF8 D_00259AF8;
extern void func_00132AF8(s32);
extern void func_002B72E8(s32);
extern void func_00132028(void);
extern void func_002CAF18(void);
extern void func_00295C50(s32);
extern void func_0029D830(void);
extern void func_002DF050(void);

/* Open the pause menu in a mode and link its pages for the screen format. */
void func_002C9CF8(int mode)
{
    func_00132AF8(0x5D);
    func_002B72E8(0);
    D_001F2840.fDB = 0;
    func_00132028();
    D_001F2840.open = 1;
    if (D_001A8BB0[0] == 0) func_002CAF18();
    D_001F2840.f144 = 0;
    D_001F2840.f148 = 0;
    D_001F2840.wide = (D_001A7A08[0] & 0xFFFF0000) || D_001F2840.f108 != 0;
    D_00259918.next = D_001F2840.wide ? &D_00259AF8 : &D_00259AA8;
    D_00259AA8.prev = D_001F2840.wide ? &D_00259AF8 : &D_00259918;
    D_001F2840.mode = D_001F2840.forced ? D_001F2840.forced : mode;
    D_001F2840.f1C8 = 0;
    D_001F2840.f1C = 0;
    D_001F2840.f20 = 0;
    D_001F2840.f120 = 0;
    D_001F2840.f1C0 = 0;
    D_001F2840.f1C4 = 0;
    if (mode != 6) {
        func_00295C50(D_001A79F0);
        func_0029D830();
        D_0025B5F8 = 0;
        func_002DF050();
    }
    D_001F2840.f150 = 0;
    D_001F2840.f14C = 1;
}
