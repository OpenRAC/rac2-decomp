#include "common.h"

/* This unit is built with -G8: func_L20_00409480 needs the -G8 profile. Its register
   allocation differs from the -G0 one this cc1 makes (in a -G0 unit the address of
   D_L20_001FBB20[arg0] lands in $a1 instead of $v1, and the loads of D_L20_001B2FB8
   come out split instead of absolute). */

extern char *D_L20_001FBB20[];

extern int D_L20_001B2FB8;

extern char *D_L20_001B2F9C;

extern void func_L09_003F73E8(char *);

extern void func_L09_003F77D0(char *);

extern void func_0029F338(void *);

/* Destroys every Megacorp Trooper Legs object in the given group. */
void func_L20_00409480(s32 group) {
    char *idList = D_L20_001FBB20[group];
    s32 groupByte = group & 0xFF;
    char *member;

    if (groupByte == 0xFF) {
        goto end;
    }
    if (D_L20_001B2FB8 < group) {
        goto end;
    }
    if (idList == 0) {
        goto end;
    }
    for (;;) {
        member = D_L20_001B2F9C + ((*(u16 *)idList & 0x7FFF) << 8);

        if (member == 0) {
            goto end;
        }
        if (*(s16 *)(member + 0xAA) == 0xD0F /* Megacorp Trooper Legs */) {
            if (*(u8 *)(member + 0x20) != 0xFE) {
                if (*(u8 *)(member + 0x20) != 0xFD) {
                    *(int *)(*(char **)(member + 0x68) + 0x20) = 0;
                    ReleaseSharedCounter(member);
                    DestroyLinkedMobys(member);
                    MarkMobySpawned(member);
                }
            }
        }
        idList += 2;
        if ((group & 0xFF) == 0xFF) {
            goto end;
        }
        if (D_L20_001B2FB8 < group) {
            goto end;
        }
        if (idList == 0) {
            return;
        }
        if (*(s16 *)(idList - 2) >= 0) {
            continue;
        }
        if (idList == D_L20_001FBB20[group]) {
            continue;
        }
        break;
    }
end:
    return;
}
