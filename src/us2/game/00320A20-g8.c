#include "include_asm.h"

typedef int AmmoSpawnQuad __attribute__((mode(TI)));
typedef struct {
    char pad00[0x8C];
    unsigned short pickupAmount;
    char pad8e[0x52];
} AmmoSpawnWeapon;
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
extern void func_US2_00320A20(void *);
extern float func_002B0360(float *);
extern void func_002A0F48(void *);
extern void func_002AB650(char *);

/* Spawns an ammo pickup (class 0xCDB, updated by func_US2_00320A20) for a weapon at a position;
   an amount of -1 takes the weapon's default, doubled while D_001A7A0A is set. */
char *func_US2_003210E0(float *position, int weapon, int amount, int extra)
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

    func_0026F7A0(weapon);
    slots = D_00139568;
    weapons = D_00239BA0;
    stride = sizeof(AmmoSpawnWeapon);
    *(AmmoSpawnQuad *)velocity = 0;
    velocity[2] = func_002A7940();
    *(AmmoSpawnQuad *)rotation = *(AmmoSpawnQuad *)velocity;
    if (D_001A8CA0) {
        func_002AFFD8(position, velocity, 1);
        rotation[1] = func_00283248(velocity[2], func_00282E20(velocity));
        rotation[2] = func_00283248(velocity[0], velocity[1]);
    }
    func_002A7A00(velocity, 1.0f / 30.0f, 1.0f / 15.0f);
    hero = D_00189E20_9;
    func_002AFEB8(*(char **)(hero + 0x2290), velocity, velocity, 0,
                  func_002A7878(4.0f, 8.0f) * (1.0f / 60.0f));
    spread = func_002A7878(180.0f, 360.0f);
    speed = func_002A7878(10.0f, 15.0f);
    spawn = func_00273730(*(char **)(hero + 0x2290), 2, 0xCDB, 0, position, rotation, velocity,
                          255, spread, speed);
    if (spawn) {
        spawn[0x20] = 1;
        *(void (**)(void *))(spawn + 0x64) = func_US2_00320A20;
        data = *(AmmoSpawnData **)(spawn + 0x68);
        if (amount == -1)
            data->amount = ((AmmoSpawnWeapon *)((char *)weapons
                + slots[func_0026F7A0(weapon)] * stride))->pickupAmount;
        else
            data->amount = amount;
        if (D_001A7A0A)
            data->amount *= 2;
        data->weapon = weapon;
        data->f6C = (float)extra;
        data->f70 = 16;
        if (D_001A8CA0)
            data->groundZ = func_002B0360((float *)(spawn + 0x10));
        else
            data->groundZ = *(float *)(spawn + 0x18);
        func_002A0F48(spawn);
        func_002AB650(spawn);
    }
    return spawn;
}
