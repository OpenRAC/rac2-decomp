/* func_US2_0034BDB0, the USA v2.00 copy of func_0034B070: the same C, where the
 * object's fields sit 0x10 and 0x20 further along. */
#include "common.h"

extern s32 func_00335AC8();
extern s32 func_003361A8();
extern s32 func_003366D0();
extern s32 func_00336968();
extern s32 func_00349498();
extern s32 func_00349918();
extern s32 func_00349CB8();

extern s8 D_001AD928[];
extern s8 D_001AD908[];
s32 func_US2_0034BDB0(s32 arg0) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s2_2;

    var_s2 = 7;
    var_s1 = arg0 + 0x378;
    func_003361A8(arg0);
    func_003361A8(arg0 + 0x4C);
    func_003361A8(arg0 + 0x98);
    func_00336968(arg0 + 0x100);
    func_003366D0(arg0 + 0x158);
    func_003361A8(arg0 + 0x194);
    func_003361A8(arg0 + 0x1E0);
    func_00336968(arg0 + 0x248);
    func_003366D0(arg0 + 0x2A0);
    func_003361A8(arg0 + 0x2E0);
    func_003361A8(arg0 + 0x32C);
    do {
        var_s2 -= 1;
        func_003361A8(var_s1);
        var_s1 += 0x4C;
    } while (var_s2 != -1);
    var_s1_2 = arg0 + 0x624;
    func_003361A8(arg0 + 0x5D8);
    var_s2_2 = 7;
    spC = arg0 + 0xE2C;
    sp20 = arg0 + 0xEB4;
    sp34 = arg0 + 0xF3C;
    sp14 = arg0 + 0xFD0;
    sp38 = arg0 + 0x1064;
    sp1C = arg0 + 0x10F8;
    sp28 = arg0 + 0x1180;
    sp0 = arg0 + 0x1214;
    sp2C = arg0 + 0x12A8;
    sp4 = arg0 + 0x133C;
    sp30 = arg0 + 0x13D0;
    sp8 = arg0 + 0x1464;
    sp10 = arg0 + 0x1468;
    sp18 = arg0 + 0x146C;
    sp24 = arg0 + 0x14F4;
    do {
        var_s2_2 -= 1;
        func_003366D0(var_s1_2);
        var_s1_2 += 0x3C;
    } while (var_s2_2 != -1);
    func_00349CB8(arg0 + 0x808);
    func_00349498(arg0 + 0xC0C);
    func_00349498(arg0 + 0xC94);
    func_00349498(arg0 + 0xD1C);
    func_00349498(arg0 + 0xDA4);
    func_00349498(spC);
    func_00349498(sp20);
    func_00349918(sp34);
    func_00349918(sp14);
    func_00349918(sp38);
    func_00349498(sp1C);
    func_00349918(sp28);
    func_00349918(sp0);
    func_00349918(sp2C);
    func_00349918(sp4);
    func_00349918(sp30);
    func_00335AC8(sp8);
    (*(s32 *)((s8 *)(arg0) + (0x1464))) = ((s32)D_001AD928);
    func_00335AC8(sp10);
    (*(s32 *)((s8 *)(arg0) + (0x1468))) = ((s32)D_001AD908);
    func_00349498(sp18);
    func_00349498(sp24);
    return arg0;
}
