#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
extern void func_0028BCE8(void);

/* authored C for independently verified level-native body */
void func_PAL_0028C778(u8 *object) {
 func_0028BCE8();
 *(s32 *)(object+0x58)=210;*(s32 *)(object+0x5c)=200;
 *(s32 *)(object+0x74)=-2;*(s32 *)(object+0x78)=25;
 *(u16 *)(object+0x48)=0;*(u16 *)(object+0x4a)=0;*(s32 *)(object+0x70)=0;
}


INCLUDE_ASM("asm/pal/game", func_PAL_0028C7C8);

INCLUDE_ASM("asm/pal/game", func_PAL_0028D0C0);


INCLUDE_ASM("asm/pal/game", func_PAL_0028D738);

INCLUDE_ASM("asm/pal/game", func_PAL_0028DC40);
