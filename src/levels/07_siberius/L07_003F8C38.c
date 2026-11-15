/* func_L07_003F8C38 (152 bytes): finds the controller's group member, takes the object's
   frame position, and hands both to func_L07_003F6C40 with the record's scale + 0.5. The
   record table pointer is read with the absolute macro (MACRO_ADDR), and func_002E5CF8
   returns a value. */
#include "common.h"


typedef struct { u8 pad38[0x38]; f32 f38; u8 rest[128 - 0x3C]; } SibRec128;
extern SibRec128 *D_L07_001B23CC MACRO_ADDR;
extern u8 *func_L07_003F6B88(u8 *a);
extern void func_L07_003F6C40(u8 *a, u8 *b, void *c, f32 d);
extern void func_0029FCC0(u8 *a, s32 b, void *c);
extern int func_002E5CF8(int, int, char *);

void func_L07_003F8C38(u8 *moby)
{
    u8 *member;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 framePos[16];

    member = FindActiveMobyInGroup(*(u8 **)(vars + 0x184));
    if (member == 0)
        return;
    TransformMobyJointToWorld(moby, 0, framePos);
    PlayMobySound(5, 0, (char *)moby);
    InitHomingBomb(member, moby, framePos, D_L07_001B23CC[*(s32 *)(vars + 0x174)].f38 + 0.5f);
}
