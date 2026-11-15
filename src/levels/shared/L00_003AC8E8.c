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
extern void func_0032D758(int, int, int);
extern void func_002A9850(void *, void *, int *, int, int, int, int, int, float, float, float);
extern unsigned char D_00139568[];
extern Entry262570b D_L00_00262570[];
extern int D_L00_001C3280[];

typedef struct {
    float head[4];
    float vec[4];
    int arg;
} Trail_3AC8E8;

/* Makes the blast of a homing shot: hurts everything close by and shows the explosion. */
void func_L00_003AC8E8(char *moby, void *normal, int hitTarget)
{
    Trail_3AC8E8 blast;
    Entry262570b *entry;
    float scale;
    int count;
    int i;

    blast.arg = hitTarget;
    FastVecScale(blast.head, normal, -3.0f);
    entry = &gWeaponTable_L00[gItemSlotToRecord[0x1B]];
    scale = entry->scale;
    count = ProcessCollisionHit(entry->flag != 0 ? 3.0f : 4.0f, (int)(moby + 0x10), 0x10, (int)moby, 0);
    for (i = 0; i < count; i++) {
        if ((gWeaponTable_L00 + gItemSlotToRecord[0x1B])->flag != 0)
            StartAttachedEffect(gAreaHitTargets[i], 0x45, *(int *)(moby + 0xB8));
        else
            StartAttachedEffect(gAreaHitTargets[i], 0x1B, *(int *)(moby + 0xB8));
    }
    *(TI128 *)blast.vec = *(TI128 *)(moby + 0x10);
    QueueKnockbackForNodes(moby, blast.vec, gAreaHitTargets, count, blast.arg, 0x810000, 3, 1, scale, 1.0f, 1.0f);
}
