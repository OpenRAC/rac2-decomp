/* Nonmatching reconstruction. Profile: -O2 -G8 -ffunction-sections.
 * 572/588 bytes; 0/27 in US and US2; PAL ABSENT. Direct hero-prefix casts restore the high-half lifetime and frame; retained slot/retest control flow and call setup still differ. A persistent full hero pointer gives 536 bytes, unchanged by G8 alone. Reopen with the remaining slot-control-flow shape.
 * No complete strict linked validation or matching credit.
 */
#include "common.h"

typedef struct {
    u8 before[0x1FC]; short field1FC;
    u8 gap1FE[0xC2C - 0x1FE]; s32 fieldC2C;
    u8 gapC30[0xEA0 - 0xC30]; u8 *slot;
    u8 gapEA4[0x2290 - 0xEA4]; u8 *owner;
    u8 gap2294[8]; s32 mode;
    u8 gap22A0[0x22B8 - 0x22A0]; u8 enabled;
    u8 gap22B9[0x2490 - 0x22B9]; u8 *target;
    u8 gap2494[0x24CC - 0x2494]; s32 field24CC;
    u8 gap24D0[0x24F4 - 0x24D0]; short field24F4;
} HeroFields;
extern u8 D_00189E20[];
extern u8 D_L00_001B5000[];
extern s32 func_002AB1F0(u8 *);
extern s32 func_L00_002AEAC0(s32);
extern s32 func_L00_002ADEA0(s32);
extern u8 *func_L00_00310BC8(u8 *, s32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_L00_00310C88(u8 *, u8 **);
extern void func_L00_00311080(u8 *, u8 *, s32, s32, s32, s32);
extern void func_L00_00310D30(u8 *);

void func_L00_002AEB18(void)
{
    s32 enabled = 0, id = 0, item;
    f32 weight = 1.0f;
    u8 *info;
    if (((HeroFields *)D_00189E20)->target != 0) {
        enabled = 1;
        info = (u8 *)func_002AB1F0(((HeroFields *)D_00189E20)->target);
        id = 0x72;
        if (info[0x2C] != 0) {
            id = func_L00_002AEAC0(info[0x2C]);
            if (((HeroFields *)D_00189E20)->mode == 1)
                weight = 0.7f;
        }
    }
    if (((HeroFields *)D_00189E20)->field1FC != 0) {
        id = func_L00_002AEAC0(((HeroFields *)D_00189E20)->field24F4);
        enabled = 1;
    }
    if (((HeroFields *)D_00189E20)->field24CC == 1) {
        enabled = 1;
        if (((HeroFields *)D_00189E20)->owner[0x43] == 0x51 || (((HeroFields *)D_00189E20)->owner[0x43] == 0x7B || ((HeroFields *)D_00189E20)->owner[0x43] == 0x57)) {
            if (((HeroFields *)D_00189E20)->fieldC2C == 0)
                enabled = 0;
        }
        weight = 0.8f;
        id = 0x74;
    }
    item = func_L00_002ADEA0(0);
    if (item == 0x1E || (item == 0x1C || item == 0x1D)) {
        if (((HeroFields *)D_00189E20)->enabled != 0) {
            weight = 0.8f;
            enabled = 1;
            id = 0x6F;
        }
    }
    if (enabled != 0) {
        if (((HeroFields *)D_00189E20)->slot == 0) {
            ((HeroFields *)D_00189E20)->slot = func_L00_00310BC8(((HeroFields *)D_00189E20)->owner, 0x18);
            *(f32 *)(((HeroFields *)D_00189E20)->slot + 8) = 0.0f;
        }
    } else {
        if (((HeroFields *)D_00189E20)->slot == 0)
            return;
        if (func_002AA2E8((f32 *)(((HeroFields *)D_00189E20)->slot + 8), 0.0f, 0.05f) == 0.0f)
            func_L00_00310C88(((HeroFields *)D_00189E20)->owner, &((HeroFields *)D_00189E20)->slot);
    }
    if (((HeroFields *)D_00189E20)->slot != 0 && enabled != 0) {
        func_002AA2E8((f32 *)(((HeroFields *)D_00189E20)->slot + 8), weight, 0.05f);
        *(u8 **)(((HeroFields *)D_00189E20)->slot + 0x38) = D_L00_001B5000;
        *(u8 **)(((HeroFields *)D_00189E20)->slot + 0x3C) = D_L00_001B5000 + 0x600;
        if (((HeroFields *)D_00189E20)->slot[0x23] != id)
            func_L00_00311080(((HeroFields *)D_00189E20)->owner, ((HeroFields *)D_00189E20)->slot, id, 0, 8, 1);
        else
            func_L00_00310D30(((HeroFields *)D_00189E20)->owner);
    }
}
