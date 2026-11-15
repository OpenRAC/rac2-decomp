#include "include_asm.h"
#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
extern unsigned char D_0013957F[];
typedef struct { char pad[112]; float scale; char tail[108]; } TableEntry;
extern char D_L00_00262570[];
extern void *D_0018C0B0;
/* The collision query writes this prefix and additional vector fields after it. */
typedef struct {
    char state[24];
    void *object;
    unsigned int detail;
    float position[4];
} CollisionResultPrefix;
extern CollisionResultPrefix D_L00_001BF200;
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_L00_003A8238(char *, void *);
extern void func_00334160(void *, int, int);

/* Checks if the beam hits something on its way, and if so shows the impact and returns 1. */
int func_L00_003A80F8(char *object, void *target)
{
    char local[64];
    char *state = *(char **)(object + 104);
    *(char **)(local + 16) = object;
    *(int *)(local + 20) = 0x10000;
    *(int *)(local + 32) = 1;
    *(float *)(local + 28) = ((TableEntry *)(gWeaponTable_L00 + D_0013957F[0] * 224))->scale;
    *(TI128 *)local = *(TI128 *)state;
    vec_scale_to_length(local, local, 1.0f);
    *(unsigned short *)(local + 26) = *(unsigned short *)(object + 0xAA);
    *(float *)(local + 12) = 5627.925f;
    *(unsigned char *)(local + 24) = 1;
    *(unsigned char *)(local + 25) = 1;
    if (*(short *)(state + 18) == 1)
        *(TI128 *)(local + 48) = *(TI128 *)(state + 48);
    else
        *(TI128 *)(local + 48) = *(TI128 *)(object + 16);
    if (CollLine(target, local + 48, 0, gHeroMoby_0018C0B0, local) != 0) {
        SpawnConfiguredImpactEffects(object, gCollisionResult.position);
        if (gCollisionResult.object != 0)
            StartHealthDrainOnTarget(gCollisionResult.object, 23, *(int *)(object + 184));
        return 1;
    }
    return 0;
}
