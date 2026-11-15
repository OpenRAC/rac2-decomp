#include "include_asm.h"
#include "names.h"
extern float D_L00_001B0464 __attribute__((sda));
extern float func_00282C48(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00326EC0(void *);
extern void func_00327038(void *);
extern void func_00327380(void *);

/* Moves the object forward by its speed, slowing it down when it is not driven. Then it rebuilds the object's corner points. */
void func_00326D90(char *object)
{
    float vector[4];
    char *data = *(char **)(object + 0x68);
    float speed = *(float *)(data + 0x30);
    if (speed != 0.0f && *(int *)(data + 0x34)) {
        float magnitude;
        float step;
        *(float *)(data + 0x18) += speed * (1.0f / 120.0f);
        magnitude = FloatAbs(*(float *)(data + 0x18));
        step = D_L00_001B0464;
        if (step * (1.0f / 60.0f) < magnitude)
            *(float *)(data + 0x18) = step * *(float *)(data + 0x30) * (1.0f / 60.0f);
    } else {
        *(float *)(data + 0x18) *= 0.85f;
    }
    *(float *)(object + 0x48) = *(float *)(data + 0x18) * 25.0f;
    if (*(int *)(data + 0x34) == 0)
        *(float *)(object + 0x48) += *(float *)(data + 0x38) * 2.0f;
    vec_scale_to_length(vector, object + 0xC0, *(float *)(data + 0x18));
    FastVecAdd(object + 0x10, object + 0x10, vector);
    BuildEightDirectionOffsets(object);
    ProbeSurfaceAndMoveObject(object);
    UpdateGroundVehicleSurfaceAlignment(object);
}
extern char *D_L00_001B043C __attribute__((sda));
/* These scalar symbols anchor eight adjacent small-data words in each table. */
extern float D_L00_001B03F0 __attribute__((sda));
extern int D_L00_001B0410 __attribute__((sda));
extern float func_0029F530(void *);
extern int func_002E5CF8(int, int, void *);

/* Plays a sound each time the tracked object's value crosses one of eight set levels. */
void func_00326BD8(void)
{
    char *object = gSpiderBotMoby;
    if (object) {
        char *data = *(char **)(object + 0x68);
        float current = GetMobyAnimationValue(object);
        int i;
        for (i = 0; i < 8; i++) {
            float threshold = (&D_L00_001B03F0)[i];
            float delta = current - threshold;
            if ((0.0f < delta || 0.0f < *(float *)(data + 0x2C) - threshold) &&
                (delta < 0.0f || *(float *)(data + 0x2C) - threshold < 0.0f)) {
                PlayMobySound((&D_L00_001B0410)[i], 0, gSpiderBotMoby);
                break;
            }
        }
        *(float *)(data + 0x2C) = current;
    }
}
extern int ref_L00_00325B28_00 __attribute__((sda));
extern char ref_L00_00325B28_01 __attribute__((sda));
extern int ref_L00_00325B28_02;
extern void func_00281A08(void *, int, void *, void *, int, int, int, int, float);

/* Draws the object's two trails from its saved trail points. */
void func_00325B28(char *object)
{
    int count = ref_L00_00325B28_00;
    int state = ref_L00_00325B28_02;
    char *data = *(char **)(object + 0x68);
    DrawTrailRibbon_00281A08(&ref_L00_00325B28_01, 4, data + 0x320, data + 0x420,
        *(int *)(data + 0x2B4), *(int *)(data + 0x2B0),
        count, state, *(float *)(data + 0x2B8));
}

extern volatile int D_001AFFF0 __attribute__((sda));
extern volatile int D_001AFFF4 __attribute__((sda));
extern void func_00322138(char *);
extern void func_00322340(char *, char *, float, int, int, int);
/* Draws three glowing effects on the object. In some states it also draws the beam between its two points. */
void func_00321FE0(char *object)
{
    char *data = *(char **)(object + 0x68);
    unsigned int state = *(unsigned char *)(object + 0x20);
    if (state == 4 || state == 5 || *(unsigned char *)(object + 0x95) == 2 || state == 10)
        DrawBeamQuadBetweenPointsB(object);
    DrawCameraFacingFlash_00322340(object, data + 0x3A0, 0.125f, D_001AFFF0, 0x20000000, 0x20000000);
    DrawCameraFacingFlash_00322340(object, data + 0x3B0, 0.15f, D_001AFFF4, 0x30000000, 0x20000000);
    DrawCameraFacingFlash_00322340(object, data + 0x3C0, 0.15f, D_001AFFF4, 0x10000000, 0x30000000);
}

extern unsigned short *D_001EE5A0[];
extern char *D_001B1B5C __attribute__((sda));

/* Walks the moby group list of the object's group id and raises the flag at data + 0x276
   on every peer of class 0xB0A whose class byte is not negative. */
void func_00321F60(char *self)
{
    if (*(unsigned char *)(self + 0x21) != 0xFF) {
        unsigned short *list = D_001EE5A0[*(unsigned char *)(self + 0x21)];
        if (list != 0) {
            char *base = D_001B1B5C;
            unsigned short *entry = list;
            int key;
            do {
                char *object = (char *)((unsigned int)base + ((*entry & 0x7FFF) << 8));
                if (object[0x20] >= 0 && *(short *)(object + 0xAA) == 0xB0A)
                    *(short *)(*(char **)(object + 0x68) + 0x276) = 1;
                key = *(short *)entry++;
            } while (key >= 0);
        }
    }
}

/* Tells every other member of the object's group that is the matching kind to raise its alert flag. */
void func_00325320(char *self)
{
    if (*(unsigned char *)(self + 0x21) != 0xFF) {
        unsigned short *list = D_001EE5A0[*(unsigned char *)(self + 0x21)];
        if (list != 0) {
            char *base = D_001B1B5C;
            unsigned short *entry = list;
            int key;
            do {
                char *object = (char *)((unsigned int)base + ((*entry & 0x7FFF) << 8));
                if (object[0x20] >= 0 && *(short *)(object + 0xAA) == 0xB0B)
                    *(short *)(*(char **)(object + 0x68) + 0x276) = 1;
                key = *(short *)entry++;
            } while (key >= 0);
        }
    }
}

typedef int AmmoSpawnQuad __attribute__((mode(TI)));

/* Weapon-table entry (0xE0 bytes, slot from D_00139568): the default amount of an ammo pickup. */
typedef struct {
    char pad00[0x8C];
    unsigned short pickupAmount;
    char pad8e[0x52];
} AmmoSpawnWeapon;

/* The spawned pickup's data (PickupData in 0031F210-pickup-g8.c). */
typedef struct {
    char pad00[0x60];
    int amount;
    char pad64[4];
    int weapon;
    float f6C;
    int f70;
    char pad74[4];
    float groundZ;
} AmmoSpawnData;

extern unsigned int func_0026F7A0(int);
extern int D_001A8CA0;
extern unsigned char D_00139568[];
extern AmmoSpawnWeapon D_00239BA0[];
extern unsigned char D_001A7A0A;
extern char D_00189E20_9[];
extern float func_002A7940(void);
extern float func_00283248(float, float);
extern void func_002AFFD8(float *, float *, int);
extern float func_00282E20(float *);
extern void func_002A7A00(float *, float, float);
extern float func_002A7878(float, float);
extern void func_002AFEB8(char *, float *, float *, int, float);
extern char *func_00273730(char *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void func_0031FC28(void *);
extern float func_002B0360(float *);
extern void func_002A0F48(void *);
extern void func_002AB650(char *);

/* Spawns an ammo pickup (class 0xCDB, updated by func_0031FC28) for a weapon at a position;
   an amount of -1 takes the weapon's default, doubled while D_001A7A0A is set. */
char *func_003202E8(float *position, int weapon, int amount, int extra)
{
    float rotation[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    unsigned char *slots;
    AmmoSpawnWeapon *weapons;
    int stride;
    char *hero;
    char *spawn;
    AmmoSpawnData *data;
    float spread, speed;

    EmptyStubF7A0(weapon);
    slots = gItemSlotToRecord;
    weapons = gWeaponTable_00239BA0;
    stride = sizeof(AmmoSpawnWeapon);
    *(AmmoSpawnQuad *)velocity = 0;
    velocity[2] = RandomAngle();
    *(AmmoSpawnQuad *)rotation = *(AmmoSpawnQuad *)velocity;
    if (D_001A8CA0) {
        ComputeViewDirection(position, velocity, 1);
        rotation[1] = FastMatrixHelperA(velocity[2], vec_length_xy(velocity));
        rotation[2] = FastMatrixHelperA(velocity[0], velocity[1]);
    }
    RandomDirectionVector(velocity, 1.0f / 30.0f, 1.0f / 15.0f);
    hero = D_00189E20_9;
    TransformAndSetHeight(*(char **)(hero + 0x2290), velocity, velocity, 0,
                  RandomFloatRange(4.0f, 8.0f) * (1.0f / 60.0f));
    spread = RandomFloatRange(180.0f, 360.0f);
    speed = RandomFloatRange(10.0f, 15.0f);
    spawn = CreateCameraMoby(*(char **)(hero + 0x2290), 2, 0xCDB, 0, position, rotation, velocity,
                          255, spread, speed);
    if (spawn) {
        spawn[0x20] = 1;
        *(void (**)(void *))(spawn + 0x64) = UpdateWeaponAmmoPickup;
        data = *(AmmoSpawnData **)(spawn + 0x68);
        if (amount == -1)
            data->amount = ((AmmoSpawnWeapon *)((char *)weapons
                + slots[EmptyStubF7A0(weapon)] * stride))->pickupAmount;
        else
            data->amount = amount;
        if (D_001A7A0A)
            data->amount *= 2;
        data->weapon = weapon;
        data->f6C = (float)extra;
        data->f70 = 16;
        if (D_001A8CA0)
            data->groundZ = GetDistanceFromGravityCenter((float *)(spawn + 0x10));
        else
            data->groundZ = *(float *)(spawn + 0x18);
        func_002A0F48(spawn);
        CopyHeroField38ToMoby(spawn);
    }
    return spawn;
}
