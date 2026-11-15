#include "common.h"


extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283098(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);






extern int D_001A79F0 __attribute__((sda));

extern char D_0019B4A8[];

extern void func_L01_003115E8(int, int);

extern void func_002A7750(char *, int, int);

/* Counts one more press on the saved switch counter for this moby, then moves it to its next state. */
void func_L01_00398008(char *moby)
{
    unsigned short indexWord = *(unsigned short *)(moby + 0xB2);

    if (indexWord & 1) {
        char *counterPtr = (char *)(((short)indexWord >> 1) + (gCurrentMapIndex << 10)) + (int)D_0019B4A8;
        unsigned char counterByte = *(unsigned char *)counterPtr;

        if (((counterByte >> 4) & 7) != 7)
            *(unsigned char *)counterPtr = counterByte + 0x10;
    } else {
        char *counterPtr = (char *)(((short)indexWord >> 1) + (gCurrentMapIndex << 10)) + (int)D_0019B4A8;
        unsigned char counterByte = *(unsigned char *)counterPtr;

        if ((counterByte & 7) != 7)
            *(unsigned char *)counterPtr = counterByte + 1;
    }

    if (*(unsigned char *)(moby + 0x21) != 0xFF)
        SetMobyStateInList(*(unsigned char *)(moby + 0x21), 1);
    else
        SetMobyState(moby, 1, -1);
}

/* Hides a moby and its three linked parts. */
void func_L01_00399098(char *moby)
{
    int i;
    char **part;

    *(unsigned short *)(moby + 0x34) |= 1;
    *(unsigned char *)(moby + 0x31) = 0;
    *(unsigned int *)(moby + 0x98) = 0;
    part = (char **)(*(char **)(moby + 0x68) + 0x14);
    for (i = 2; i >= 0; i--) {
        if (*part != 0) {
            *(unsigned short *)(*part + 0x34) |= 1;
            *(unsigned char *)(*part + 0x31) = 0;
        }
        part++;
    }
}



/* Spawns a burst of dust puffs around a point, flying outward and slightly up. */
void func_L01_003BD178(char *moby, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4];
    int life1, life2, life3;
    char *particle;

    {
        int i;
        for (i = 0; i < count; i++) {
            float x, y;
            x = FastSinOrCosA(RandomFloatRange(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * RandomFloatRange(minRadius, maxRadius);
            y = FastSinOrCosB(RandomFloatRange(-3.1415927410125732f, 3.1415927410125732f));
            y *= RandomFloatRange(minRadius, maxRadius);
            offset[1] = y;
            offset[2] = 0;
            matrix_mul_vec3(offset, offset, moby + 0xC0);
            {
                float range = speed * ((maxRadius - FastVecLength(offset)) * 0.01666666753590107f) / maxRadius;
                vec_scale_to_length(velocity, offset, RandomFloatRange(range * 0.25f, range));
            }
            velocity[2] += RandomFloatRange(rise * 0.25f, rise) * 0.01666666753590107f;
            qzero_nc(accel);
            FastVecAdd(offset, offset, position);
            velocity[3] = size;
            accel[3] = endSize;
            life1 = FloatToInt(RandomFloatRange(15.0f, 25.0f));
            life2 = FloatToInt(RandomFloatRange(20.0f, 40.0f));
            life3 = FloatToInt(RandomFloatRange(30.0f, 60.0f));
            particle = SpawnTrailParticle_002BAA28(offset, velocity, accel, 0x50204050, 0x7F7F7F, life1, life2, life3, -1);
            if (particle && (Rand() & 1))
                particle[3] = 0x48;
        }
    }
}





typedef union { int whole __attribute__((mode(TI))); float f[4]; } EffectVector;
extern void func_L00_003263D0(void *, void *, float, int, int, void *, float, float, unsigned int, void *, float);

/* Spawns a ring of sparks around a moby that fly outward. */
void func_L01_003D6B00(char *object, int count, float low, float high, float radius, float speed)
{
    EffectVector position, velocity;
    float angle;
    int i;
    position.whole = 0;
    velocity.whole = 0;
    for (i = 0; i < count; i++) {
        angle = RandomFloatRange(-3.1415927410125732f, 3.1415927410125732f);
        position.f[0] = radius * FastSinOrCosA(angle);
        position.f[1] = radius * FastSinOrCosB(angle);
        position.f[2] = RandomFloatRange(0.0f, 1.0f);
        vec_scale_to_length(&velocity, &position, RandomFloatRange(speed * 0.75f, speed * 1.25f));
        position.f[2] = RandomFloatRange(low, high);
        FastVecAdd(&position, object + 0x10, &position);
        SpawnTintedEffects(object, &position, 0.0f, 1, 1, &velocity, 0.0f, 1.0f,
                          0x50808040, 0, 5.5f);
    }
}


extern int func_002A9640(char *, int, int);

extern void func_002A8598(int, int);

/* revives the round a moby belongs to and drops what it was carrying */
void func_L01_003EE8E0(char *moby)
{
    char *owner = (char *)FindOwnedEffectSlot(moby, 0x10000, 0);

    if (owner != 0) {
        char *ownerTarget = *(char **)(owner + 0x20);

        if (ownerTarget != 0) {
            if (*(short *)(ownerTarget + 0xAA) == 0x825 /* Dynamo */) {
                if (*(unsigned char *)(moby + 0x21) != 0xFF)
                    SetByteOnGroupMobys(*(unsigned char *)(moby + 0x21), 2);
            }
        }
    }

    *(unsigned char *)(moby + 0xA8) = 0xFF;
}

extern void func_0026FEB8(void *, int);
extern void func_0029F338(void *);
extern int func_L00_00329520(void *, int);
extern void func_0027D330(int);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_L00_00303530(int, int);
extern int func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern void func_002F5CC8(void);
extern int func_002F5D10(void);
extern void func_002AD7B8(int);
extern void func_002AF0A8(int);
extern void func_002A0430(int);
extern void func_002DF3F8(void *, void *);
extern void func_L01_002C1988(int);
extern void func_L01_002BEB90(int, int);
extern void func_L01_00323310(int, int);
extern void func_0029B3E0(int, int);
extern unsigned char D_0019B2E8[];
extern char D_00189EA0[];

/* Level data, at another address in each level that has this function. The trigger flag is
   read at an offset from its owner: retail never moves it into a delay slot. */
extern int ref_L01_003FFFE8_00[] __attribute__((sda));
extern char ref_L01_003FFFE8_01[];
extern char ref_L01_003FFFE8_02[];
extern char ref_L01_003FFFE8_03[];
extern char ref_L01_003FFFE8_04[];
extern char *ref_L01_003FFFE8_05 __attribute__((sda));
extern char ref_L01_003FFFE8_06[];
extern int ref_L01_003FFFE8_07 __attribute__((sda));

/* a trigger moby: reports bad setup, waits to be activated, plays its effects and removes itself */
void func_L01_003FFFE8(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int active;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        if (*(int *)vars == -1)
            STUB_printf(ref_L01_003FFFE8_01, *(short *)(moby + 0xB2));
        if (*(short *)(vars + 4) == -1)
            STUB_printf(ref_L01_003FFFE8_02, *(short *)(moby + 0xB2));
        if (*(int *)(vars + 8) == -1)
            STUB_printf(ref_L01_003FFFE8_03, *(short *)(moby + 0xB2));
        if (*(unsigned char *)(moby + 0xB0) != 255) {
            if (D_0019B2E8[*(unsigned char *)(moby + 0xB0) + (gCurrentMapIndex << 4)] & 128) {
                MarkMobySpawned(moby);
                break;
            }
        } else
            STUB_printf(ref_L01_003FFFE8_04, *(short *)(moby + 0xB2));
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        active = 0;
        if (*(unsigned char *)(moby + 0xBC) ||
            (*(int *)vars != -1 && IsPointInsideRegion(gHeroPosition, *(int *)vars) &&
             (*(int *)(vars + 0x18) || *(int *)(gHeroPosition + 0x2C0))))
            active = 1;
        if (active) {
            int ready;

            *(unsigned char *)(moby + 0x30) = 255;
            FadeToBlack(20);
            if (*(int *)(vars + 0xC) != -1) {
                char *entry = ref_L01_003FFFE8_05 + (*(int *)(vars + 0xC) << 7);

                ResetHeroPositionAndDirection(entry + 0x30, entry + 0x70, 0x6F, 1);
            }
            if (*(int *)(vars + 8) != -1)
                LoadSceneChunk(*(int *)(vars + 8), 0);
            ready = 1;
            if (gCurrentMapIndex == 8 && *(short *)(vars + 4) == 0) {
                if (PushRequestQueue(ref_L01_003FFFE8_06, 0x57)) {
                    PushRequestQueue(ref_L01_003FFFE8_06, 9);
                    PushRequestQueue(ref_L01_003FFFE8_06, 0x58);
                    LaunchQueuedRequest(ref_L01_003FFFE8_06);
                    SetSlowdownFactorAndLowFpsFade();
                    ref_L01_003FFFE8_07 = 1;
                } else
                    ready = 0;
            }
            if (ready)
                SetMobyState(moby, 3, -1);
        }
        break;
    case 3:
        ref_L01_003FFFE8_00[1] = 1;
        if (!IsEitherModeTwo()) {
            ref_L01_003FFFE8_00[1] = 0;
            if (*(short *)(vars + 6) != -1) {
                MarkFlagAndAppendToList(*(short *)(vars + 6));
                PlayIndexedSound(*(short *)(vars + 6));
            }
            SetMobyState(moby, 4, -1);
        }
        break;
    case 4:
        if (*(unsigned char *)(moby + 0xB0) != 255) {
            int n = *(unsigned char *)(moby + 0xB0);

            if (!(D_0019B2E8[n + (gCurrentMapIndex << 4)] & 128)) {
                MarkTableEntryFlagged(n);
                CaptureCheckpointState(moby + 0x10, moby + 0xF0);
            }
        }
        StartHeroMoveStateOneOrTwo(0);
        SetHeroMoveState(0, 1);
        QueueKeyedRequest(*(int *)(vars + 0x14), *(int *)(vars + 0x10));
        MemcardSave(0, -1);
        MarkMobySpawned(moby);
        break;
    }
}

extern void func_002A7750(char *, int, int);

extern void func_L00_00326048(char *, char *, float, int, int);

extern int D_L01_001A8F40 __attribute__((sda));

/* Updates a TV Screens moby: starts it, then keeps its screen effect running. */
void func_L01_004110E0(char *moby)
{
    unsigned char state = *(unsigned char *)(moby + 0x20);
    char *vars = *(char **)(moby + 0x68);

    switch (state) {
    case 0:
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (vars == 0)
            break;
        if (D_L01_001A8F40 == 2)
            StoreAngleUpdateResult(moby, vars + 0xC, 0.055268768f,
                              (int)0x80AABED2u, (int)0x80466464u);
        else
            StoreAngleUpdateResult(moby, vars + 0xC, 0.037815473f,
                              (int)0x8096AAAAu, (int)0x80466464u);
        break;
    }
}

extern void func_L00_004117B8(void *);
extern void ref_L01_004132D8_00(void (*)(void *), void *);
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
extern ParticleEffectSlot D_L01_00257920[];
extern char *D_L01_001C3980[];

/* Updates up to 30 glow effects attached to other mobys: pulses their colour, throws sparks near them and frees them when the target is gone. */
void func_L01_004132D8(char *moby) {
    float sparkA[4], sparkB[4];
    int i;

    qcopy_nc(moby + 0x10, gHeroState);
    for (i = 0; i < 30; i++) {
        char *slot;
        char *other;
        int dead;

        if (!D_L01_00257920[i].target)
            continue;
        slot = (char *)&D_L01_00257920[i];
        *(float *)(slot + 0xC) = FastAddRotations(*(float *)(slot + 0xC), 0.20943954586982727f);
        dead = 0;
        if (*(signed char *)(*(char **)(slot + 0x18) + 0x20) < 0)
            dead = 1;
        if (!*(int *)(*(char **)(slot + 0x18) + 0x98))
            dead = 1;
        if (FastFloatHelperD(slot))
            dead = 1;
        if (FastVectorHelperB(slot + 0x1C)) {
            int count, j;
            char *target = *(char **)(slot + 0x18);

            *(float *)(slot + 0x1C) = *(float *)(slot + 0x14);
            count = ProcessCollisionHit(target + 0x10, 0, target, 0, 8.0f);
            for (j = 0; j < count; j++) {
                other = D_L01_001C3980[j];
                if ((*(unsigned short *)(other + 0x34) & 0x1000) && other &&
                    *(unsigned char *)(other + 0x20) != 254 && *(unsigned char *)(other + 0x20) != 253 &&
                    *(short *)(*(char **)(other + 0x24) + 0x46) == 5)
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

                BuildSphericalOffset(sparkA, x, y, z);
            }
            {
                float scale = RandomFloatRange(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(slot + 0x18) + 0xC) * scale;
                float y = RandomAngle();
                float z = RandomAngle();

                BuildSphericalOffset(sparkB, x, y, z);
            }
            j = RandomIntRange(5, 15);
            count = RandomIntRange(15, 30);
            SpawnTumblingPiece(moby, *(char **)(slot + 0x18), *(char **)(slot + 0x18), sparkA, sparkB, 0, j, count, slot, 0.0f);
        }
        if (dead) {
            ApplySlotColorToTarget(slot);
            *(char **)(slot + 0x18) = 0;
            continue;
        }
        goto timer;
    collide:
        ClearVector128(sparkA);
        SpawnTumblingPiece(moby, *(char **)(slot + 0x18), other, sparkA, sparkA, 1, 10, 30, slot, *(float *)(slot + 0x10));
        SpawnTumblingPiece(moby, *(char **)(slot + 0x18), other, sparkA, sparkA, 0, 10, 30, slot, 0.0f);
        goto random_particles;
    timer:
        if (*(int *)(slot + 0x24) == 0) {
            int c = FastTweenColor(*(int *)(slot + 4), *(int *)(slot + 8),
                                  (FastSinOrCosA(*(float *)(slot + 0xC)) + 1.0f) * 0.5f);

            set_moby_color(*(char **)(slot + 0x18), c & 255, (c >> 8) & 255, (c >> 16) & 255);
        } else
            --*(int *)(slot + 0x24);
    }
    UpdateTumblingPieces(moby);
    ref_L01_004132D8_00(UpdateTrackedTargetOffsets, moby);
}


extern char *D_001B9510;

extern float func_2E3618(char *);

extern char D_001B9380[];

extern char D_00189EA0[];

extern void func_2CF938(char *, char *);

typedef int TI128 __attribute__((mode(TI)));


extern void func_2E34A0(void *, char *, char *);

extern void func_2E3918(void *, void *, char *);

extern float func_2E33E0(float);

extern void func_323310(int, int);



extern void func_002A6CF0(void *, void *);

extern int ref_L01_004480C8_00;

/* Passes the object to the shared resident handler. */
void func_L01_004480C8(void *object)
{
    func_002A6CF0(&ref_L01_004480C8_00, object);
}
