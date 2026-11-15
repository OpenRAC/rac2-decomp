#include "include_asm.h"
#include "common.h"

extern char D_L03_00259A30[];
extern void func_L00_00322A98(u8 *, char *);
extern void func_L00_00322AC0(char *, s32, s32, float);
extern void func_L00_00322BE0(char *, s32);
extern void func_L00_00322EC8(char *);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_00273B70(u8 *);
extern void func_0029F338(void *);

/* Runs a short effect that starts up, lingers, then fades out and removes itself. */
void func_L03_00421930(u8 *obj)
{
    u8 *p = *(u8 **)(obj + 0x68);
    char *tbl;
    s32 n;
    s32 index;
    s32 k;

    switch (obj[0x20]) {
    case 0:
        index = *(s16 *)(p + 0x36);
        n = 0x150;
        tbl = D_L03_00259A30;
        InitPendingSlot(obj, &tbl[index * n]);
        AppendRecordToFourEntryTable(&tbl[*(s16 *)(p + 0x36) * n], 0x28, 2, 0.0f);
        AppendRecordToFourEntryTable(&tbl[*(s16 *)(p + 0x36) * n], 0x14, 4, 0.0f);
        AppendRecordToFourEntryTable(&tbl[*(s16 *)(p + 0x36) * n], 0xA, 6, 0.0f);
        SetMobyState(obj, 1, -1);
        break;
    case 1:
        k = 0x150;
        tbl = &D_L03_00259A30[*(s16 *)(p + 0x36) * k];
        UpdateTransformHistoryFollowers(tbl, 0);
        n = UpdateCameraMoby(obj);
        if (n != 0) {
            SetMobyState(obj, 2, -1);
            *(u16 *)(obj + 0x34) |= 0x2800;
        }
        break;
    case 2:
        UpdateCameraMoby(obj);
        tbl = &D_L03_00259A30[*(s16 *)(p + 0x36) * 0x150];
        ReleaseSlotList(tbl);
        if (obj[0x23] < 2) {
            MarkMobySpawned(obj);
        } else {
            obj[0x23] -= 2;
        }
        break;
    }
}
