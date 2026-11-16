#include "include_asm.h"
#include "names.h"

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
extern unsigned int stub_empty_19(int);
extern int g_ground_check_inhibit;
extern unsigned char g_item_slot_to_record[];
extern AmmoSpawnWeapon g_weapon_table[];
extern unsigned char g_extras_unlocked_flag;
extern char D_00189E20_9[];
extern float math_random_angle(void);
extern float mat_fast_helper_a(float, float);
extern void cam_compute_view_direction(float *, float *, int);
extern float vec_length_xy(float *);
extern void vec_random_direction(float *, float, float);
extern float math_random_float_range(float, float);
extern void vec_transform_and_set_height(char *, float *, float *, int, float);
extern char *cam_moby_create(char *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void UpdateWeaponAmmoPickup_us2(void *);
extern float gravity_get_center_distance(float *);
extern void func_002A0F48(void *);
extern void hero_copy_field_to_moby(char *);

/* Spawns an ammo pickup (class 0xCDB, updated by func_US2_00320A20) for a weapon at a position;
   an amount of -1 takes the weapon's default, doubled while D_001A7A0A is set. */
char *SpawnWeaponAmmoPickup_us2(float *position, int weapon, int amount, int extra)
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

    stub_empty_19(weapon);
    slots = g_item_slot_to_record;
    weapons = g_weapon_table;
    stride = sizeof(AmmoSpawnWeapon);
    *(AmmoSpawnQuad *)velocity = 0;
    velocity[2] = math_random_angle();
    *(AmmoSpawnQuad *)rotation = *(AmmoSpawnQuad *)velocity;
    if (g_ground_check_inhibit) {
        cam_compute_view_direction(position, velocity, 1);
        rotation[1] = mat_fast_helper_a(velocity[2], vec_length_xy(velocity));
        rotation[2] = mat_fast_helper_a(velocity[0], velocity[1]);
    }
    vec_random_direction(velocity, 1.0f / 30.0f, 1.0f / 15.0f);
    hero = D_00189E20_9;
    vec_transform_and_set_height(*(char **)(hero + 0x2290), velocity, velocity, 0,
                  math_random_float_range(4.0f, 8.0f) * (1.0f / 60.0f));
    spread = math_random_float_range(180.0f, 360.0f);
    speed = math_random_float_range(10.0f, 15.0f);
    spawn = cam_moby_create(*(char **)(hero + 0x2290), 2, 0xCDB, 0, position, rotation, velocity,
                          255, spread, speed);
    if (spawn) {
        spawn[0x20] = 1;
        *(void (**)(void *))(spawn + 0x64) = UpdateWeaponAmmoPickup_us2;
        data = *(AmmoSpawnData **)(spawn + 0x68);
        if (amount == -1)
            data->amount = ((AmmoSpawnWeapon *)((char *)weapons
                + slots[stub_empty_19(weapon)] * stride))->pickupAmount;
        else
            data->amount = amount;
        if (g_extras_unlocked_flag)
            data->amount *= 2;
        data->weapon = weapon;
        data->f6C = (float)extra;
        data->f70 = 16;
        if (g_ground_check_inhibit)
            data->groundZ = gravity_get_center_distance((float *)(spawn + 0x10));
        else
            data->groundZ = *(float *)(spawn + 0x18);
        func_002A0F48(spawn);
        hero_copy_field_to_moby(spawn);
    }
    return spawn;
}
