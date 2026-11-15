#include "include_asm.h"
#include "names.h"
typedef int V4_L00_004170A8 __attribute__((mode(TI)));
extern char D_L00_0025A920[];
extern V4_L00_004170A8 D_L00_001BF220;
extern int func_00282948(void *);
extern void func_L00_004173B0(char *);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_L00_00417A40(char *, void *, int);
extern void func_L00_00417D70(char *);
extern void func_L00_00417218(char *);
extern void func_L00_00417700(char *);
extern void func_0029F338(char *);
extern void ref_L00_004170A8_00(void (*)(char *), char *);

/* Updates the spark effect object (moby class 5022). Each frame it picks a random spot nearby for a new spark, and when its time is up it frees all the sparks and removes itself. */
void func_L00_004170A8(char *object)
{
    char *state = *(char **)(object + 0x68);
    V4_L00_004170A8 target;
    float randA, randB;
    int i;
    char *record;
    if (FastFloatHelperD(state) == 0) {
        if (*(int *)(state + 4) == 0)
            EmitSparkBurstAtMoby(object);
        if (*(int *)(state + 4) == 0) {
            randA = RandomAngle();
            randB = RandomAngle();
            BuildSphericalOffset(&target, 7.0f, randA, randB);
        } else {
            randA = RandomAngle();
            randB = RandomAngle();
            BuildSphericalOffset(&target, 5.0f, randA, randB);
        }
        FastVecAdd(&target, &target, object + 0x10);
        if (CollLine(object + 0x10, &target, 0, object, 0) != 0)
            target = D_L00_001BF220;
        ClaimSparkRecord_L00(object, &target, 20);
        UpdateSparkRecords(object);
        ref_L00_004170A8_00(UpdateOwnedBeamGlowSprites, object);
    } else {
        record = gSparkRecords_L00;
        record += 0x106C;
        for (i = 23; i >= 0; --i, record -= 0xB0)
            *(int *)record = 0;
        if (*(int *)(state + 4) == 0)
            SpawnDriftingParticles(object);
        MarkMobySpawned(object);
    }
}
