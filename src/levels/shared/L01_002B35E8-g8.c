/* func_L01_002B35E8 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern char D_00189E20[];

extern void func_0028BDB0(char *);

extern void func_0028BE00(char *);

extern int func_0028C6D0(char *);

extern char D_L01_001B4B00[];

extern char D_L01_001B5100[];

extern int D_001A8F40;

extern void func_L00_002A53B8(void);

extern int func_0028B3D0(int, int, void (*)(char *), void (*)(char *), int (*)(char *), int, int);

extern int func_L00_002F6B90(u32 a0);

extern void func_L00_002A6708(void);

extern void func_L00_002D24B8(void);

extern int func_L00_002A4DB0(char *a0, int a1, int a2, char *a3);

extern void func_L01_002BEB90(int a0, int a1);

/* Resets the hero when a new area starts: clears the old target, copies the spawn position from the spawn object and sets up the two attached objects. */
void func_L01_002B35E8(void) {
    char *hero;
    char *heroMoby;
    int attachedItem;

    ResetAllAttachmentRecords();
    hero = gHeroState;
    hero[0x22B4] = 0;
    SetHudSlotContents(0x23, 0, InitMenuPanelLayout, UpdateRadialWeaponSelect, DrawWeaponWheel, 0, 0);
    RunSlotCallback(3);
    {
        char *oldActor = *(char **)(hero + 0xC14);
        if (oldActor != 0)
            *(u16 *)(oldActor + 0x34) &= 0xFFF9;
    }
    *(int *)(hero + 0xC14) = 0;
    ClearTrackedSlots();
    {
        char *actor = *(char **)(hero + 0xC18);
        *(char **)(hero + 0x2290) = actor;
        qcopy(actor + 0x10, hero + 0x80);
        *(int *)(actor + 0x9C) = 0;
    }
    *(float *)(hero + 0xC24) = 1.0f;
    ClearHeroQueuedAnimation();
    heroMoby = *(char **)(hero + 0x2290);
    if (*(unsigned char *)((char *)heroMoby + 0x42) != 0xFF) {
        attachedItem = CopyAnimationEntryData(heroMoby, *(unsigned char *)((char *)heroMoby + 0x42),
                              *(unsigned char *)((char *)heroMoby + 0x40), D_L01_001B4B00);
        *(int *)(*(char **)(hero + 0x2290) + 0x58) = attachedItem;
    }
    heroMoby = *(char **)(hero + 0x2290);
    attachedItem = CopyAnimationEntryData(heroMoby, *(unsigned char *)((char *)heroMoby + 0x43),
                          *(unsigned char *)((char *)heroMoby + 0x41), D_L01_001B5100);
    *(int *)(*(char **)(hero + 0x2290) + 0x5C) = attachedItem;
    if (*(int *)(hero + 0x2294) != 0x61 ||
        (D_001A8F40 != 2 && D_001A8F40 != 6))
        SetHeroMoveState(0, 1);
}
