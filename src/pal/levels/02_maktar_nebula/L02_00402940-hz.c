/* func_PAL_L02_00402940, the PAL copy of func_L02_003FE1B0: the same C, where 0x2F48 becomes 0xe6d;
   0x2F49 becomes 0xe6e; 0x2F4A becomes 0xe6f; 0x2F4B becomes 0xe70; 0x2F4C becomes 0xe71; 0x2F4D
   becomes 0xe72; 0x2F4E becomes 0xe73; 0x2F4F becomes 0xe74; 0x2F6E becomes 0xe93; 0x2F50 becomes
   0xe75; 0x2F51 becomes 0xe76; 0x3240 becomes 0x1409; 0x3241 becomes 0x140a; 0x3242 becomes
   0x140b. */
#include "include_asm.h"

typedef unsigned int u32;

typedef int s32;

extern int D_L02_002A5600[];

/* Maps a value below 14 to an id (0xe6d to 0xe76, 0xe93 and 0x1409 to 0x140b, in no regular
   order); any other value gives 0xe6d. The dispatch reads the level's own jump table (fourteen
   words in the level's data at 0x2A5440 in PAL, one per value); `cases` only keeps the labels
   alive, and each label is named after the value that reaches it. */
s32 func_PAL_L02_00402940(u32 a0) {
    static void *cases[14] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7, &&c8, &&c9, &&c10,
                              &&c11, &&c12, &&c13};
    if (a0 < 14)
        goto *D_L02_002A5600[a0];
    goto dflt;
c0:
    return 0xe6d;
c2:
    return 0xe6e;
c4:
    return 0xe6f;
c9:
    return 0xe70;
c6:
    return 0xe71;
c3:
    return 0xe72;
c1:
    return 0xe73;
c5:
    return 0xe74;
c7:
    return 0xe93;
c10:
    return 0xe75;
c11:
    return 0xe76;
c8:
    return 0x1409;
c12:
    return 0x140a;
c13:
    return 0x140b;
dflt:
    return 0xe6d;
}
