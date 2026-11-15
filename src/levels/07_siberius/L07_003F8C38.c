/* func_L07_003F8C38 (152 bytes): finds the controller's group member, takes the object's
   frame position, and hands both to func_L07_003F6C40 with the record's scale + 0.5. The
   record table pointer is read with the absolute macro (MACRO_ADDR), and PlayMobySound
   returns a value. */
#include "common.h"


typedef struct { u8 pad38[0x38]; f32 f38; u8 rest[128 - 0x3C]; } SibRec128;
extern SibRec128 *D_L07_001B23CC MACRO_ADDR;
extern u8 *func_L07_003F6B88(u8 *a);
extern void func_L07_003F6C40(u8 *a, u8 *b, void *c, f32 d);
extern void func_0029FCC0(u8 *a, s32 b, void *c);
extern int func_002E5CF8(int, int, char *);

void func_L07_003F8C38(u8 *a0)
{
    u8 *s1;
    u8 *s2 = *(u8 **)(a0 + 0x68);
    u8 buf[16];

    s1 = func_L07_003F6B88(*(u8 **)(s2 + 0x184));
    if (s1 == 0)
        return;
    func_0029FCC0(a0, 0, buf);
    PlayMobySound(5, 0, (char *)a0);
    func_L07_003F6C40(s1, a0, buf, D_L07_001B23CC[*(s32 *)(s2 + 0x174)].f38 + 0.5f);
}
