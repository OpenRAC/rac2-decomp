#include "common.h"

/* This unit is built with -G8: func_L20_0039E0A0 needs the -G8 profile. Its register
   allocation differs from the -G0 one this cc1 makes: in a -G0 unit the address of
   D_L20_001FBB20[arg0] lands in $t0 instead of $v1 (the retail coalesces it with the
   shift), the loads of D_L20_001B2FB8 come out split instead of absolute. */

extern char *D_L20_001FBB20[];

extern int D_L20_001B2FB8;

extern char *D_L20_001B2F9C;

/* Counts how many objects of a group are still alive (not in state 6). */
s32 func_L20_0039E0A0(s32 group) {
    char *idList = D_L20_001FBB20[group];
    s32 groupByte = group & 0xFF;
    s32 count = 0;

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
        char *member = D_L20_001B2F9C + ((*(u16 *)idList & 0x7FFF) << 8);

        if (member == 0) {
            goto end;
        }
        if (*(u8 *)(member + 0x20) != 6) {
            count++;
        }
        idList += 2;
        if ((group & 0xFF) == 0xFF) {
            goto end;
        }
        if (D_L20_001B2FB8 < group) {
            goto end;
        }
        if (idList == 0) {
            goto end;
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
    return count;
}
