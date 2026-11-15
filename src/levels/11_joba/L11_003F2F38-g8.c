#include "common.h"

/* Puts the object back on its rail: resets the flags, the state block and the
   animation, then places it on the rail point at the current angle. */

typedef struct {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[0x8];
    u8 *model;
    u8 pad28[0x9];
    u8 b31;
    u8 pad32[2];
    u16 flags;
    u8 pad36[0x49];
    u8 b7F;
    u8 pad80[0x18];
    u32 w98;
    u8 pad9C[0x1C];
    s32 slot;
    u8 padBC[0x4];
    u8 mtx[0x30];
    s32 rotW;
    f32 rotX;
    f32 rotZ;
} L11Moby;

extern void func_002A7750(u8 *arg0, s32 arg1, s32 arg2);
extern void func_002A0488(void *, int, int, int);
extern int func_002B3380(char *, char *, char *);
extern f32 func_00283180(f32 a0);
extern f32 func_00283198(f32 a0);
extern f32 func_00283B98(f32 a0, f32 a1);
extern void func_002833F0(void *a0, void *a1);
extern f32 *func_L11_004417E8(s32 a0);

extern f32 D_L11_001B0558 __attribute__((sda));
extern f32 D_L11_001B0540 __attribute__((sda));

/* Puts the Joba rail object back on its rail at angle zero and resets its state. */
void func_L11_003F2F38(u8 *mobyBytes) {
    L11Moby *moby = (L11Moby *)mobyBytes;
    u8 *vars = *(u8 **)(mobyBytes + 0x68);
    f32 *railPoint;
    f32 trig;
    f32 newY;
    u32 modelWord;

    *(f32 *)(vars + 0x20) = (f32)*(s16 *)(vars + 0x24);
    modelWord = *(u32 *)(moby->model + 0x10);
    moby->flags &= 0xFFFE;
    moby->b31 = 1;
    moby->w98 = modelWord;
    *(u8 *)(vars + 0x2E) = 1;
    moby->b7F = 0;
    moby->flags = (moby->flags & 0xFFB9) | 0x1000;
    *(s32 *)(vars + 0x60) = 0;
    SpawnDamageDebrisOnHealthLoss((char *)moby, (char *)(vars + 0x50), (char *)(vars + 0x20));
    if (*(s16 *)(vars + 0x70) != 0) {
        *(s16 *)(vars + 0x70) = 0;
        set_moby_color(moby, *(u32 *)(vars + 0x280), *(u32 *)(vars + 0x284),
                      *(u32 *)(vars + 0x288));
        *(s16 *)(vars + 0x72) = 1;
    }
    SetMobyState(mobyBytes, 2, 2);
    *(s32 *)(vars + 0x250) = 0;
    trig = FastSinOrCosA(*(f32 *)(vars + 0x250));
    railPoint = GetArenaCenterPoint(moby->slot);
    moby->x = D_L11_001B0558 * trig + railPoint[0];
    trig = FastSinOrCosB(*(f32 *)(vars + 0x250));
    railPoint = GetArenaCenterPoint(moby->slot);
    newY = D_L11_001B0558 * trig + railPoint[1];
    moby->z = D_L11_001B0540;
    moby->rotX = -1.5707965f;
    moby->rotW = 0;
    moby->y = newY;
    moby->rotZ = FastAddRotations(3.1415927f, *(f32 *)(vars + 0x250));
    euler_rotation_basis(moby->mtx, &moby->rotW);
}
