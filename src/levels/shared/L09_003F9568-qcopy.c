#include "include_asm.h"
#include "names.h"

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef int TI128 __attribute__((mode(TI)));

extern s32 *D_L09_001FE6C0[];

typedef struct {
    char pad0[0x10];
    TI128 f10;
} T3F9568_Pos;

typedef struct {
    char pad0[0x1CA];
    s16 f1CA;
    char pad1[0x200 - 0x1CC];
    T3F9568_Pos *f200;
    char pad2[0x2DC - 0x204];
    s32 f2DC;
    char pad3[0x30F - 0x2E0];
    u8 f30F;
} T3F9568_Owned;

typedef struct {
    char pad0[0x24];
    char *f24;
} T3F9568_Hit;

typedef struct {
    char pad0[0x68];
    T3F9568_Owned *f68;
} T3F9568_Obj;

extern char D_L09_001BFE58[];
extern s32 CollLine(void *, void *, int, void *, int);
extern s32 coll_test_point(void *, int, void *, float);

/* Checks whether the enemy has a clear line to its target. Returns 1 if something blocks the view. */
s32 enemy_check_line_of_sight(T3F9568_Obj *moby, s32 checkSolid, s32 fromPathPoint, s32 lowShot)
{
    T3F9568_Owned *vars = moby->f68;
    TI128 pos[1];
    TI128 aim[1];
    TI128 probe[1];
    s32 blocked;

    if (vars->f30F != 0)
        return 1;
    pos[0] = *(TI128 *)((char *)moby + 0x10);
    if (fromPathPoint != 0 && vars->f2DC != -1 && vars->f1CA != -1)
        pos[0] = *(TI128 *)((char *)D_L09_001FE6C0[vars->f2DC] + vars->f1CA * 16 + 0x10);
    if (lowShot != 0)
        ((float *)pos)[2] += 1.0f;
    else
        ((float *)pos)[2] += 1.76f;
    aim[0] = vars->f200->f10;
    blocked = 0;
    ((float *)aim)[2] += 1.18f;
    if (CollLine(pos, aim, 0, moby, 0) == 0 || *(T3F9568_Hit **)D_L09_001BFE58 == (T3F9568_Hit *)vars->f200)
        blocked = 1;
    if (checkSolid != 0 && blocked == 0) {
        probe[0] = *(TI128 *)(D_L09_001BFE58 + 8);
        if (coll_test_point(probe, 1, moby, 0.5f) != 0) {
            T3F9568_Hit *hit = *(T3F9568_Hit **)D_L09_001BFE58;
            if (hit == 0 || hit->f24 == 0 || *(s16 *)(hit->f24 + 0x46) != 5)
                blocked = 1;
        }
    }
    return blocked;
}
