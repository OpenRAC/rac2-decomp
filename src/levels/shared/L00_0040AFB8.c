#include "include_asm.h"
#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char pad0[4];
    unsigned char flag;
    unsigned char pad1[0x74 - 5];
    float scale;
    unsigned char pad2[0xE0 - 0x78];
} Entry262570b;

extern void func_00282D30(void *, void *, float);
extern int func_00277F48(float, int, int, int, int);
extern void func_002A9850(void *, void *, int *, int, int, int, int, int, float, float, float);
extern unsigned char D_00139568[];
extern Entry262570b D_L00_00262570[];
extern int D_L00_001C3280[];

/* Draws a short beam effect from the object, sized by the current weapon. */
void func_L00_0040AFB8(char *obj, void *source, int flags)
{
    float headVec[4];
    float startPos[4];
    float scale;
    int pointCount;

    FastVecScale(headVec, source, -3.0f);
    scale = (gWeaponTable_L00 + gItemSlotToRecord[0x2C])->scale;
    pointCount = ProcessCollisionHit(gWeaponTable_L00[gItemSlotToRecord[0x1B]].flag != 0 ? 3.0f : 4.0f, (int)(obj + 0x10), 0x10, (int)obj, 0);
    *(TI128 *)startPos = *(TI128 *)(obj + 0x10);
    QueueKnockbackForNodes(obj, startPos, gAreaHitTargets, pointCount, flags, 0x810000, 3, 1, scale, 1.0f, 1.0f);
}
