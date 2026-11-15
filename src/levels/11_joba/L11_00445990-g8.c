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

extern void func_L11_002D8EF8(s32, s32);
extern s32 func_L00_0032EF10(s32, s32, s32 *);
extern s32 func_L11_0043E108(s32);
extern s32 func_00288D58(void);
extern void func_L11_004425C8(char *);
extern void func_L11_004456A0(char *);
extern void func_L00_002E6CF0(void *, void *);

/* Same shape as func_L02_003FF9A0: the selection moves to the next usable table entry (this
   table has 13 entries and only the record of entry 8 is checked). */
void func_L11_00445990(char *moby) {
    char *state = *(char **)(moby + 0x68);
    s32 i;
    L11_00445990_Rec *record;

    if (D_0018C0B4 != 0x6F)
        EnterHeroState_L11(0x6F, 1);
    if (PadPressedWithin(0x40, 0x3C, 0) != 0) {
        SetMobyState(moby, 7, -1);
        *(s16 *)(state + 0x1E8) = *(u16 *)(state + 0x1F0);
        D_001395B8[0x49] = *(u8 *)(state + 0x1E8);
        for (i = *(s16 *)(state + 0x1E8) + 1; i < 0xD; i++) {
            if (D_001395B8[GetChallengeFlagIndex(*(s32 *)(ref_L11_00445990_00[i] + 8))] == 0)
                continue;
            if (i >= 0xB && IsFlagByteSet() == 0)
                continue;
            if (i == 8) {
                record = &D_L11_00279BA0[gItemSlotToRecord[0x1E]];
                if (record->f4 == 0)
                    continue;
            }
            *(s16 *)(state + 0x1E8) = i;
            D_001395B8[0x49] = *(u8 *)(state + 0x1E8);
            return;
        }
    } else if (PadPressedWithin(0x10, 0x3C, 0) != 0) {
        ResetArenaEncounter(moby);
    } else {
        AddDrawCallbackToList1(DrawJobaMenuHeaderAndCountBox, moby);
    }
}
