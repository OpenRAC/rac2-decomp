#include "common.h"
extern void func_L00_004117B8(void *);
extern void ref_L00_00410D20_00(void (*)(void *), void *);
extern void func_L00_00411B30(void *);
extern void func_002A0488(void *, int, int, int);
extern int func_00283D38(int, int, float);
extern float func_00283180(float);
extern void func_L00_004110D8(void *);
extern void func_00282C88(void *);
extern void func_L00_004118A8(void *, void *, void *, void *, void *, int, int, int, void *, float);
extern int func_002A7820(int, int);
extern void func_002AF000(void *, float, float, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern int func_00277F48(void *, int, void *, int, float);
extern int func_002829D8(void *);
extern int func_00282948(void *);
extern float func_00283B98(float, float);
typedef struct {
    char data[0x18];
    char *target;
    char end[0x14];
} ParticleEffectSlot;
extern char D_00189E20[];
extern ParticleEffectSlot ref_L00_00410D20_01[];
extern char *ref_L00_00410D20_02[];

/* Keeps up to 30 tracked targets lit with colour changes and little sparks, and cleans each one up when its target is gone. Also creates extra sparks when a target touches something. */
void func_L00_00410D20(char *moby) {
    float sparkDirA[4], sparkDirB[4];
    int i;

    qcopy_nc(moby + 0x10, gHeroState);
    for (i = 0; i < 30; i++) {
        char *slot;
        char *hitMoby;
        int isDead;

        if (!ref_L00_00410D20_01[i].target)
            continue;
        slot = (char *)&ref_L00_00410D20_01[i];
        *(float *)(slot + 0xC) = FastAddRotations(*(float *)(slot + 0xC), 0.20943954586982727f);
        isDead = 0;
        if (*(signed char *)(*(char **)(slot + 0x18) + 0x20) < 0)
            isDead = 1;
        if (!*(int *)(*(char **)(slot + 0x18) + 0x98))
            isDead = 1;
        if (FastFloatHelperD(slot))
            isDead = 1;
        if (FastVectorHelperB(slot + 0x1C)) {
            int count, j;
            char *target = *(char **)(slot + 0x18);

            *(float *)(slot + 0x1C) = *(float *)(slot + 0x14);
            count = ProcessCollisionHit(target + 0x10, 0, target, 0, 8.0f);
            for (j = 0; j < count; j++) {
                hitMoby = ref_L00_00410D20_02[j];
                if ((*(unsigned short *)(hitMoby + 0x34) & 0x1000) && hitMoby &&
                    *(unsigned char *)(hitMoby + 0x20) != 254 && *(unsigned char *)(hitMoby + 0x20) != 253 &&
                    *(short *)(*(char **)(hitMoby + 0x24) + 0x46) == 5)
                    goto collide;
            }
        }
    random_particles:
        if (Rand() % 11 == 0) {
            int j, count;

            {
                float scale = RandomFloatRange(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(slot + 0x18) + 0xC) * scale;
                float y = RandomAngle();
                float z = RandomAngle();

                BuildSphericalOffset(sparkDirA, x, y, z);
            }
            {
                float scale = RandomFloatRange(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(slot + 0x18) + 0xC) * scale;
                float y = RandomAngle();
                float z = RandomAngle();

                BuildSphericalOffset(sparkDirB, x, y, z);
            }
            j = RandomIntRange(5, 15);
            count = RandomIntRange(15, 30);
            SpawnTumblingPiece(moby, *(char **)(slot + 0x18), *(char **)(slot + 0x18), sparkDirA, sparkDirB, 0, j, count, slot, 0.0f);
        }
        if (isDead) {
            ApplySlotColorToTarget(slot);
            *(char **)(slot + 0x18) = 0;
            continue;
        }
        goto timer;
    collide:
        ClearVector128(sparkDirA);
        SpawnTumblingPiece(moby, *(char **)(slot + 0x18), hitMoby, sparkDirA, sparkDirA, 1, 10, 30, slot, *(float *)(slot + 0x10));
        SpawnTumblingPiece(moby, *(char **)(slot + 0x18), hitMoby, sparkDirA, sparkDirA, 0, 10, 30, slot, 0.0f);
        goto random_particles;
    timer:
        if (*(int *)(slot + 0x24) == 0) {
            int color = FastTweenColor(*(int *)(slot + 4), *(int *)(slot + 8),
                                  (FastSinOrCosA(*(float *)(slot + 0xC)) + 1.0f) * 0.5f);

            set_moby_color(*(char **)(slot + 0x18), color & 255, (color >> 8) & 255, (color >> 16) & 255);
        } else
            --*(int *)(slot + 0x24);
    }
    UpdateTumblingPieces(moby);
    ref_L00_00410D20_00(UpdateTrackedTargetOffsets, moby);
}
