#include "include_asm.h"
#include "common.h"

/* func_L00_003EB610 has a unit of its own, as its twin func_L00_003D3DE0 does: the four-slot
 * table is a 16-byte small-data object (-G16), and its three-row copy loop keeps retail's
 * upward counter only without the second loop pass (-fno-rerun-loop-opt, config/cflags.txt). */
typedef int Quad __attribute__((mode(TI)));
/* One 0xE0-byte entry of the weapon table at D_L00_00262570. */
typedef struct { char pad[0x58]; int value; char tail[0x84]; } ClassEntry;
extern char *D_L00_001B0798[4] __attribute__((sda));
/* The hero moby pointer: resident data, not small data. */
extern char *D_0018C0B0 NOT_SDA;
extern unsigned char D_00139568[];
extern ClassEntry D_L00_00262570[];
extern int func_L00_002D3F30(int, int);
extern char *func_0029EFD0(int);

/* Spawn the owner's companion moby into the first free one of four slots. */
char *func_L00_003EB610(char *owner, Quad *position)
{
    char *moby;
    char *state;
    char *src, *dst;
    int slot = -1;
    int i, j;
    i = 0;
    do {
        char *slotMoby = gSynthenoidSlots[i];
        if (slotMoby == 0 || *(short *)(slotMoby + 0xAA) != 0xCB2 /* Synthenoid */ || (unsigned char)slotMoby[0x20] == 0xFE
            || (unsigned char)slotMoby[0x20] == 0xFD) {
            slot = i;
            break;
        }
        i++;
    } while (i < 4);
    if (slot < 0)
        return 0;
    if (SpendWeaponAmmo(0x1F, 1) == 0)
        return 0;
    moby = CreateMoby(0xCB2 /* Synthenoid */);
    if (moby != 0) {
        state = *(char **)(moby + 0x68);
        *(char **)(state + 0x34) = owner;
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(short *)(moby + 0x32) = 0x7F;
        moby[0x31] = 1;
        *(long long *)(moby + 0x38) = *(long long *)(owner + 0x38);
        src = gHeroMoby_0018C0B0 + 0xC0;
        dst = moby + 0xC0; /* the moby's 3x4 rotation matrix takes the hero's */
        for (j = 0; j < 3; j++) {
            qcopy(dst + j * 16, src);
            src += 16;
        }
        qzero(moby + 0xF0);
        *(unsigned short *)(moby + 0x34) |= 0x100;
        qcopy(moby + 0x10, position);
        *(float *)(moby + 0x2C) *= 0.1f;
        *(int *)(state + 0x38) = -1;
        *(int *)(state + 0x3C) = 0;
        *(int *)(state + 0x40) = ((ClassEntry *)((unsigned int)gWeaponTable_L00
                                   + gItemSlotToRecord[0x1F] * sizeof(ClassEntry)))->value;
        gSynthenoidSlots[slot] = moby;
        *(int *)(state + 0x38) = slot;
        moby[0x20] = 0;
    }
    return moby;
}
