#include "include_asm.h"
#include "names.h"

extern char D_001B5340[];
extern int func_002A77E0(int);
extern float D_001AF1A4 __attribute__((sda));
extern float D_001AF1A8 __attribute__((sda));
extern unsigned char D_001AF1AC __attribute__((sda));
extern void *D_001AF1B0 __attribute__((sda));
extern void *D_001AF1B4 __attribute__((sda));
extern void *D_001AF1B8 __attribute__((sda));
extern float D_001AF1BC __attribute__((sda));
extern float D_001AF1C0 __attribute__((sda));
extern char D_0018A0E0[];
extern void func_00282CF0(void *, void *, void *);
extern float func_002A7878(float, float);
extern void func_00282D30(void *, void *, float);
extern float func_002A7940(void);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_002C3150(void *, void *, void *, int, int, int, float);

/* Spawns two sparkle effects at the object, using a random spin and a color chosen by its flag. */
void func_003130F0(unsigned char *object)
{
    char first[16];
    char second[16];
    char third[16];
    unsigned char *state;
    char *basis;
    void *effect;
    unsigned char kind;
    unsigned char random;

    state = *(unsigned char **)(object + 0x68);
    FastVecSub(first, gCameraState_001B5340, object + 0x10);
    basis = D_0018A0E0;
    FastVecScale(second, basis,
                  RandomFloatRange(D_001AF1A4 * 0.016666668f,
                               D_001AF1A8 * 0.016666668f));
    ApplyAxisRotationToQuaternion(third, second, first, RandomAngle());

    effect = state[0x57] != 0 ? D_001AF1B8 : D_001AF1B0;
    kind = D_001AF1AC;
    random = (unsigned char)RandomIntBelow(255);
    SpawnHeroRelativeParticle(object + 0x10, third, effect, kind, random, 1, D_001AF1BC);

    kind = D_001AF1AC;
    random = (unsigned char)RandomIntBelow(255);
    SpawnHeroRelativeParticle(object + 0x10, third, D_001AF1B4, kind, random, 1, D_001AF1C0);
}

extern char *D_001AF880 __attribute__((sda));

/* Turns on a flag in the private data of the object stored in D_001AF880, if there is one. */
void func_00317390(void)
{
    char *p = D_001AF880;
    if (p != 0) {
        char *q = *(char **)(p + 0x68);
        *(int *)(q + 0x28) = 1;
    }
}

extern float D_001AF57C __attribute__((sda));
extern char D_001B2520[] __attribute__((sda));
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern int func_00283D38(int, int, float);
extern void func_003169D0(void *);
extern void func_00281EB8(char *, int, unsigned int, int, float, float, float);

/* Advances the shared angle of the effect, picks the three sprite colours for it and draws
   the three sprites. */
void func_00316248(void *object)
{
    float angle = FastAddRotations(D_001AF57C, 0.125f);
    float scale;
    float size_a;
    float size_b;
    float size_c;
    int colour_a;
    int colour_b;
    int colour_c;

    D_001AF57C = angle;
    scale = FastSinOrCosA(angle);
    scale = (scale + 1.0f) * 0.5f;
    size_b = scale * 0.0625f + 0.0625f;
    size_c = scale * 0.19999999f + 0.15f;
    size_a = scale * 0.125f + 0.125f;

    colour_a = FastTweenColor(0x2F007F00, 0x3F007F00, scale);
    colour_b = FastTweenColor(0x2F7F7F7F, 0x5F7F7F7F, scale);
    colour_c = FastTweenColor(0x10003F00, 0x10003F00, scale);

    DrawOwnerEffectSlots(object);
    DrawBillboardQuad_00281EB8(D_001B2520, 0x31, colour_a, 1, size_a, 0.125f, 0.0f);
    DrawBillboardQuad_00281EB8(D_001B2520, 0x31, colour_b, 1, size_b, 0.124f, 0.0f);
    DrawBillboardQuad_00281EB8(D_001B2520, 0x0B, colour_c, 1, size_c, 0.123f, 0.0f);
}
