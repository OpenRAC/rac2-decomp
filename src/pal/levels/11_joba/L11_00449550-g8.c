#include "include_asm.h"

#include "common.h"
extern s32 D_0018C0B4 __attribute__((nosda));
extern u8 D_001395B8[];
extern u8 D_00139568[];
extern void func_002A7750(char *, int, int);
extern char *ref_L11_00445990_00[2] __attribute__((sda));
typedef struct {
    char pad0[4];
    u8 f4;
    char pad1[0xDB];
} L11_00445990_Rec;
extern L11_00445990_Rec D_L11_00279BA0[];
extern void func_PAL_L11_002D9038(s32, s32);
extern s32 func_L00_0032EF10(s32, s32, s32 *);
extern s32 func_L11_0043E108(s32);
extern s32 func_00288D58(void);
extern void func_PAL_L11_00447E20(char *);
extern void func_PAL_L11_0044B0B0(char *);
extern void func_L00_002E6CF0(void *, void *);

/* Same shape as func_L02_003FF9A0: the selection moves to the next usable table entry (this
   table has 13 entries and only the record of entry 8 is checked). */
void func_PAL_L11_0044B3B8(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    s32 i;
    L11_00445990_Rec *r;

    if (D_0018C0B4 != 0x6F)
        func_PAL_L11_002D9038(0x6F, 1);
    if (func_L00_0032EF10(0x40, 0x32, 0) != 0) {
        func_002A7750(a0, 7, -1);
        *(s16 *)(state + 0x1E8) = *(u16 *)(state + 0x1F0);
        D_001395B8[0x49] = *(u8 *)(state + 0x1E8);
        for (i = *(s16 *)(state + 0x1E8) + 1; i < 0xD; i++) {
            if (D_001395B8[func_L11_0043E108(*(s32 *)(ref_L11_00445990_00[i] + 8))] == 0)
                continue;
            if (i >= 0xB && func_00288D58() == 0)
                continue;
            if (i == 8) {
                r = &D_L11_00279BA0[D_00139568[0x1E]];
                if (r->f4 == 0)
                    continue;
            }
            *(s16 *)(state + 0x1E8) = i;
            D_001395B8[0x49] = *(u8 *)(state + 0x1E8);
            return;
        }
    } else if (func_L00_0032EF10(0x10, 0x32, 0) != 0) {
        func_PAL_L11_00447E20(a0);
    } else {
        func_L00_002E6CF0(func_PAL_L11_0044B0B0, a0);
    }
}
