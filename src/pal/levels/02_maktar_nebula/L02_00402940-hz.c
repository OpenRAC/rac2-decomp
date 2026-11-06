/* func_PAL_L02_00402940, the PAL copy of func_L02_003F9B70: the same C, where 0x31 becomes 0xe6d;
   0x32 becomes 0xe6e; 0x33 becomes 0xe6f; 0x34 becomes 0xe70; 0x35 becomes 0xe71; 0x36 becomes
   0xe72; 0x37 becomes 0xe73; 0x38 becomes 0xe74; 0x39 becomes 0xe93; 0x3A becomes 0xE75; 0x3B
   becomes 0xE76; 0x91 becomes 0x1409; 0x92 becomes 0x140a; 0x93 becomes 0x140b; - 1 becomes 3693. */
#include "include_asm.h"

typedef unsigned int u32;

typedef int s32;

extern int ref_L02_00402940_00[];

/* Maps a value below 14 to an id (0x31 to 0x3B and 0x91 to 0x93, in no regular order) and any
   other value to -1. The dispatch reads the level's own jump table (fourteen words in the level's
   data at 0x2A5440 in PAL, one per value; it is `ref_L02_00402940_00` because v1.01 has its own table at 0x2A5560); `cases` only keeps the labels alive, and each label is named
   after the value that reaches it. */
s32 func_PAL_L02_00402940(s32 a0) {
    static void *cases[14] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7, &&c8, &&c9, &&c10,
                              &&c11, &&c12, &&c13};
    if ((u32)a0 < 14)
        goto *ref_L02_00402940_00[a0];
    goto dflt;
c0:
    return 0xe6d;
c2:
    return 0xe6e;
c3:
    return 0xe6f;
c1:
    return 0xe70;
c4:
    return 0xe71;
c5:
    return 0xe72;
c6:
    return 0xe73;
c7:
    return 0xe74;
c9:
    return 0xe93;
c10:
    return 0xE75;
c11:
    return 0xE76;
c8:
    return 0x1409;
c12:
    return 0x140a;
c13:
    return 0x140b;
dflt:
    return 3693;
}
