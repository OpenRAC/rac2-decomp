#include "common.h"

/* Advances a falling object through impact, particle emission and fade-out. */
typedef int Quad __attribute__((mode(TI)));
extern int D_L00_001B0528 __attribute__((sda));
typedef struct { char pad[0x34]; int owner; char tail[8]; } ParticleRecord;
extern ParticleRecord D_L00_00247900[100];
typedef struct { char pad[0x24]; int kind; char *owner; char tail[0x3C]; int active; } OwnerContext;
extern OwnerContext D_001A63A8;
extern char D_L00_001BF220[0x30];
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_00283B98(float, float), func_00282E48(void *, void *);
extern void func_00328848(void *), func_003290D0(void *, void *, float);
extern int func_003286D0(void *, void *);
extern void func_00328758(void *), func_002E5CF8(int, int, void *);
extern float func_002A7940(void), func_002A7878(float, float);
extern void func_002AF000(void *, float, float, float);
extern void func_002BE278(void *, void *, int, float);
extern int func_00282948(int *);
extern void func_0029F338(void *), func_00328918(void *), func_00329328(void *);
extern void ref_L00_003E0240_00(void *, void *);
extern void func_00328A20(void);
/* Updates a thrown projectile: it flies, bursts into sparks when it hits something, then fades away and is removed. */
void func_L00_003E0240(char *self)
{
    float previous[4], velocity[4];
    char *state = *(char **)(self + 0x68);
    float angle, elevation;
    switch (*(unsigned char *)(self + 0x20)) {
    case 0: {
        *(unsigned char *)(self + 0x20) = 1;
        *(int *)(state + 0x48) = 0;
        {
            int initialized = D_L00_001B0528;
            *(int *)(state + 0x4C) = 0;
            *(int *)(state + 0x50) = 0;
            if (!initialized) {
                int i;
                for (i = 99; i >= 0; i--) D_L00_00247900[i].owner = 0;
                D_L00_001B0528 = 1;
            }
        }
        {
            OwnerContext *context = &gMusicState;
            if (!context->active && context->kind == -1) {
                context->owner = self;
                context->kind = 0xDB9;
            }
        }
    }
    /* Fall through to move the object on its first update. */
    case 1:
        *(Quad *)previous = *(Quad *)(self + 0x10);
        FastVecAdd(self + 0x10, self + 0x10, state);
        *(float *)(state + 8) -= 0.00305555575f;
        *(float *)(self + 0xF4) = FastAddRotations(*(float *)(self + 0xF4), *(float *)(state + 0x14));
        *(float *)(self + 0xF8) = FastAddRotations(*(float *)(self + 0xF8), *(float *)(state + 0x18));
        ClaimSparkRecord_00328848(self);
        SpawnObjectParticle(self, self + 0x10, fast_vec_dist(previous, self + 0x10) * 0.5f);
        if (PlaceObjectAtCollisionPoint(self, previous)) {
            *(unsigned char *)(self + 0x20) = 2;
            *(int *)(state + 0x44) = 20;
            *(int *)(state + 0x58) = 128;
            *(unsigned short *)(self + 0x34) |= 8;
            ClearVector128(state);
            CheckPlayerHitByObject(self);
            PlayMobySound(0, 0, self);
            FastVecScale(state + 0x20, D_L00_001BF220 + 0x20, 0.0009765625f);
            vec_scale_to_length(state + 0x20, state + 0x20, 1.0f);
            *(Quad *)(state + 0x30) = *(Quad *)D_L00_001BF220;
            if (!*(int *)(state + 0x54)) {
                float *v = velocity;
                int i;
                for (i = 7; i >= 0; i--) {
                    angle = RandomAngle();
                    elevation = RandomFloatRange(0.392699093f, 3.14159274f);
                    BuildSphericalOffset(v, 0.13333334f, angle, elevation);
                    SpawnWhiteFlashParticle(self + 0x10, v, 0, -1.0f);
                }
            }
        }
        break;
    case 2:
        SpawnObjectParticle(self, self + 0x10, 0.1f);
        FastVecAdd(self + 0x10, self + 0x10, state);
        *(float *)(state + 8) -= 0.00152777787f;
        *(unsigned char *)(self + 0x23) -= 4;
        FastFloatHelperD((int *)(state + 0x44));
        if (*(unsigned char *)(self + 0x23) > 4) *(unsigned char *)(self + 0x23) -= 4;
        if (!*(int *)(state + 0x44) && *(unsigned char *)(self + 0x23) < 4) *(unsigned char *)(self + 0x20) = 3;
        break;
    case 3:
        if (*(unsigned char *)(self + 0x23)) --*(unsigned char *)(self + 0x23);
        if (*(int *)(state + 0x58) >= 5) *(int *)(state + 0x58) -= 4;
        else if (*(int *)(state + 0x58) > 0) --*(int *)(state + 0x58);
        if (!*(long long *)(state + 0x48) && !*(int *)(state + 0x58)) {
            *(unsigned char *)(self + 0x20) = 4;
            *(int *)(self + 0x98) = 0;
            *(unsigned short *)(self + 0x34) = (*(unsigned short *)(self + 0x34) | 0x41) & 0xEFFF;
        }
        break;
    case 4:
        if (FastFloatHelperD((int *)(state + 0x5C))) {
            MarkMobySpawned(self);
            return;
        }
        break;
    }
    UpdateOrbitingSparks(self);
    UpdateObjectParticles(self);
    ref_L00_003E0240_00(DrawObjectSpriteEffects, self);
}
