#include "include_asm.h"
#include "names.h"

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef int TI128 __attribute__((mode(TI)));

extern s32 *D_L12_001FEAC0[];

typedef struct {
    char pad0[0x10];
    TI128 f10;
} Todano_Pos;

typedef struct {
    char pad0[0x1CA];
    s16 f1CA;
    char pad1[0x200 - 0x1CC];
    Todano_Pos *f200;
    char pad2[0x2DC - 0x204];
    s32 f2DC;
    char pad3[0x30F - 0x2E0];
    u8 f30F;
} Todano_Owned;

typedef struct {
    char pad0[0x24];
    char *f24;
} Todano_Hit;

typedef struct {
    char pad0[0x68];
    Todano_Owned *f68;
} Todano_Obj;

extern char D_L12_001B1860[];
extern char D_L12_001C0258[];
extern s32 func_002761F8(void *, void *, int, void *, int);
extern s32 func_00277258(void *, int, void *, float);
extern void func_0026FEB8(void *);

/* Checks whether the guard's line of sight to its target is blocked. Returns 1 when something
   is in the way. */
s32 func_L12_00414AB8(Todano_Obj *moby, s32 checkHitKind, s32 useAnchor, s32 crouched)
{
    Todano_Owned *vars = moby->f68;
    TI128 pos[1];
    TI128 aim[1];
    TI128 probe[1];
    s32 blocked;

    if (vars->f30F != 0)
        return 1;
    pos[0] = *(TI128 *)((char *)moby + 0x10);
    if (useAnchor != 0 && vars->f2DC != -1 && vars->f1CA != -1)
        pos[0] = *(TI128 *)((char *)D_L12_001FEAC0[vars->f2DC] + vars->f1CA * 16 + 0x10);
    if (crouched != 0)
        ((float *)pos)[2] += 1.0f;
    else
        ((float *)pos)[2] += 1.76f;
    aim[0] = vars->f200->f10;
    blocked = 0;
    ((float *)aim)[2] += 1.18f;
    if (CollLine(pos, aim, 0, moby, 0) == 0 || *(Todano_Hit **)D_L12_001C0258 == (Todano_Hit *)vars->f200)
        blocked = 1;
    STUB_printf(D_L12_001B1860);
    if (checkHitKind != 0 && blocked == 0) {
        probe[0] = *(TI128 *)(D_L12_001C0258 + 8);
        if (TestPointAgainstCollision(probe, 1, moby, 0.5f) != 0) {
            Todano_Hit *h = *(Todano_Hit **)D_L12_001C0258;
            if (h == 0 || h->f24 == 0 || *(s16 *)(h->f24 + 0x46) != 5)
                blocked = 1;
        }
    }
    return blocked;
}
