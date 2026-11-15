#include "common.h"

typedef int EffectVector __attribute__((mode(TI)));
typedef struct { char pad[0x10]; EffectVector position; } EffectObject;
typedef struct { char pad[0x24]; int kind; char *object; char pad2[0x3C]; int active; } EffectWorld;

extern EffectWorld D_001A63A8;
extern float D_001B0228 SDATA(D_001B0228);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(float *, float *, float);
extern float func_00283B98(float, float);
extern float func_002A90F8(void *, void *);
extern void func_00282C88(void *);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void func_002C7748(void *, void *, int);
extern float func_00282E48(void *, void *);
extern int func_00329DC0(void *, void *);
extern void func_00329F40(void *);
extern void func_002B0668(void *);
extern int func_002FD828(void *, void *, float, float, float);
extern void func_00329E60(void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002BF728(void *, void *, float, float);
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern void func_0027CFD0(void *, void *);
extern void func_0032A130(void);

/* Updates a flying chunk (class 3032): it drops under gravity, sprays sparks, lands on the ground, bounces and fades out. */
void func_00329768(char *moby)
{
    float previousPos[4] __attribute__((aligned(16)));
    float hit[4], zero[4], random[4];
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(moby + 0x68);
    int i;
    float height;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        moby[0x20]=1;
        *(unsigned short *)(moby + 0x34)|=8;
        *(int *)(state + 0x40)=0;
        *(int *)(state + 0x38)=0;
        *(int *)(state + 0x48)=0;
        if (!gMusicState.active && gMusicState.kind==-1) {
            gMusicState.object=moby;
            gMusicState.kind=0xDB8;
        }
    case 1:
        qcopy(previousPos, moby + 0x10);
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        *(float *)(state + 8)-=0.003055555745959282f;
        *(float *)(moby + 0xF4)=FastAddRotations(*(float *)(moby + 0xF4), *(float *)(state + 0x14));
        *(float *)(moby + 0xF8)=FastAddRotations(*(float *)(moby + 0xF8), *(float *)(state + 0x18));
        GetGroundHeightAtPosition(moby + 0x10, hit);
        ClearVector128(zero);
        for (i=7;i>=0;i--) {
            random[0]=RandomSignedFloatRange(0, D_001B0228);
            random[1]=RandomSignedFloatRange(0, D_001B0228);
            random[2]=RandomSignedFloatRange(0, D_001B0228);
            FastVecAdd(random, random, moby + 0x10);
            SpawnDriftingParticle_002C7748(random, state, RandomIntRange(20, 40));
        }
        fast_vec_dist(previousPos, moby + 0x10);
        if (PlaceObjectAtCollisionPointAndMirror(moby, previousPos)) {
            CheckPlayerUnderFallingObject(moby);
            if (*(int *)(state + 0x38)==2) moby[0x20]=2;
            else {
                if (*(int *)(state + 0x38)) {
                    *(float *)(moby + 0x18)+=1;
                    *(EffectVector *)velocity = ((EffectObject *)moby)->position;
                    SpawnGroundImpactEffect(velocity);
                    *(float *)(moby + 0x18)-=1;
                    SampleSurfaceHeightMap(moby + 0x18, velocity, *(float *)(moby + 0x10), *(float *)(moby + 0x14), *(float *)(moby + 0x18));
                    if (!*(int *)(state + 0x44)) EmitSparkBurst_00329E60(moby);
                }
                moby[0x20]=3;
                *(int *)(state + 0x34)=80;
            }
        }
        break;
    case 2:
        qcopy(previousPos, moby + 0x10);
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        *(float *)(state + 8)-=0.003055555745959282f;
        *(float *)(moby + 0xF4)=FastAddRotations(*(float *)(moby + 0xF4), *(float *)(state + 0x14));
        *(float *)(moby + 0xF8)=FastAddRotations(*(float *)(moby + 0xF8), *(float *)(state + 0x18));
        CheckPlayerUnderFallingObject(moby);
        if (*(int *)(state + 0x38)==1) {
            PlayMobySound(0, 0, moby);
            moby[0x20]=3;
            *(int *)(state + 0x34)=80;
            *(float *)(moby + 0x18)+=1;
            *(EffectVector *)position = ((EffectObject *)moby)->position;
            SpawnGroundImpactEffect(position);
            *(float *)(moby + 0x18)-=1;
            SampleSurfaceHeightMap(moby + 0x18, velocity, *(float *)(moby + 0x10), *(float *)(moby + 0x14), *(float *)(moby + 0x18));
            if (!*(int *)(state + 0x44)) EmitSparkBurst_00329E60(moby);
        }
        break;
    case 3: {
        float one, low, high, scale;
        qcopy(previousPos, moby + 0x10);
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        FastVecScale(state, state, 0.8f);
        *(float *)(state + 8)-=0.002444444689899683f;
        *(float *)(moby + 0xF4)=FastAddRotations(*(float *)(moby + 0xF4), *(float *)(state + 0x14));
        *(float *)(moby + 0xF8)=FastAddRotations(*(float *)(moby + 0xF8), *(float *)(state + 0x18));
        fast_vec_dist(previousPos, moby + 0x10);
        *(float *)(state + 0x14)*=0.8f;
        *(float *)(state + 0x18)*=0.8f;
        if ((unsigned char)moby[0x23] >= 3)
            moby[0x23] -= 2;
        else
            moby[0x23] = 0;
        one = 1.0f;
        low = -0.5f;
        high = 0.5f;
        scale = 0.2f;
        *(float *)(moby + 0x18)+=one;
        height=GetGroundHeightAtPosition(moby + 0x10, hit);
        *(float *)(moby + 0x18)-=one;
        velocity[0]=RandomFloatRange(low, high);
        velocity[1]=RandomFloatRange(low, high);
        velocity[2]=RandomFloatRange(low, 2);
        velocity[3]=0;
        vec_scale_to_length(velocity, velocity, RandomFloatRange(0.06666667f, 0.13333334f)*scale);
        SpawnBubbleParticle(moby + 0x10, velocity, RandomFloatRange(0.05f, 0.1f)*210000.0f, height);
        if (FastFloatHelperD(state + 0x34)) moby[0x20]=4;
        break;
    }
    case 4:
        if (!*(int *)(state + 0x40)) {
            MarkMobySpawned(moby);
            return;
        }
        break;
    }
    RegisterOverlayDrawCallback(DoNothingCallback, moby);
}
