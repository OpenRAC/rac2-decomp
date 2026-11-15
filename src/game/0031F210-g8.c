#include "include_asm.h"
#include "names.h"
extern float D_L00_001B0464 __attribute__((sda));
extern float math_fabs(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void BuildEightDirectionOffsets(void *);
extern void moby_probe_surface_and_move(void *);
extern void vehicle_align_to_ground_surface(void *);

/* Moves the object forward by its speed, slowing it down when it is not driven. Then it rebuilds the object's corner points. */
void moby_move_with_friction(char *object)
{
    float vector[4];
    char *data = *(char **)(object + 0x68);
    float speed = *(float *)(data + 0x30);
    if (speed != 0.0f && *(int *)(data + 0x34)) {
        float magnitude;
        float step;
        *(float *)(data + 0x18) += speed * (1.0f / 120.0f);
        magnitude = math_fabs(*(float *)(data + 0x18));
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
    moby_probe_surface_and_move(object);
    vehicle_align_to_ground_surface(object);
}
extern char *g_spider_bot_moby __attribute__((sda));
/* These scalar symbols anchor eight adjacent small-data words in each table. */
extern float D_L00_001B03F0 __attribute__((sda));
extern int D_L00_001B0410 __attribute__((sda));
extern float moby_get_anim_value(void *);
extern int PlayMobySound(int, int, void *);

/* Plays a sound each time the tracked object's value crosses one of eight set levels. */
void snd_play_on_threshold_cross(void)
{
    char *object = g_spider_bot_moby;
    if (object) {
        char *data = *(char **)(object + 0x68);
        float current = moby_get_anim_value(object);
        int i;
        for (i = 0; i < 8; i++) {
            float threshold = (&D_L00_001B03F0)[i];
            float delta = current - threshold;
            if ((0.0f < delta || 0.0f < *(float *)(data + 0x2C) - threshold) &&
                (delta < 0.0f || *(float *)(data + 0x2C) - threshold < 0.0f)) {
                PlayMobySound((&D_L00_001B0410)[i], 0, g_spider_bot_moby);
                break;
            }
        }
        *(float *)(data + 0x2C) = current;
    }
}
extern int ref_L00_00325B28_00 __attribute__((sda));
extern char ref_L00_00325B28_01 __attribute__((sda));
extern int ref_L00_00325B28_02;
extern void part_draw_trail_ribbon(void *, int, void *, void *, int, int, int, int, float);

/* Draws the object's two trails from its saved trail points. */
void robot_draw_trails(char *object)
{
    int count = ref_L00_00325B28_00;
    int state = ref_L00_00325B28_02;
    char *data = *(char **)(object + 0x68);
    part_draw_trail_ribbon(&ref_L00_00325B28_01, 4, data + 0x320, data + 0x420,
        *(int *)(data + 0x2B4), *(int *)(data + 0x2B0),
        count, state, *(float *)(data + 0x2B8));
}

extern volatile int D_001AFFF0 __attribute__((sda));
extern volatile int D_001AFFF4 __attribute__((sda));
extern void gfx_draw_beam_quad_between_points_b(char *);
extern void gfx_draw_camera_facing_flash(char *, char *, float, int, int, int);
/* Draws three glowing effects on the object. In some states it also draws the beam between its two points. */
void robot_draw_glow_effects(char *object)
{
    char *data = *(char **)(object + 0x68);
    unsigned int state = *(unsigned char *)(object + 0x20);
    if (state == 4 || state == 5 || *(unsigned char *)(object + 0x95) == 2 || state == 10)
        gfx_draw_beam_quad_between_points_b(object);
    gfx_draw_camera_facing_flash(object, data + 0x3A0, 0.125f, D_001AFFF0, 0x20000000, 0x20000000);
    gfx_draw_camera_facing_flash(object, data + 0x3B0, 0.15f, D_001AFFF4, 0x30000000, 0x20000000);
    gfx_draw_camera_facing_flash(object, data + 0x3C0, 0.15f, D_001AFFF4, 0x10000000, 0x30000000);
}

extern unsigned short *D_001EE5A0[];
extern char *D_001B1B5C __attribute__((sda));

/* Walks the moby group list of the object's group id and raises the flag at data + 0x276
   on every peer of class 0xB0A whose class byte is not negative. */
void group_alert_peers_type_a(char *self)
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
void group_alert_peers_type_b(char *self)
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

extern unsigned int stub_empty_19(int);
extern int D_001A8CA0;
extern unsigned char g_item_slot_to_record[];
extern AmmoSpawnWeapon g_weapon_table[];
extern unsigned char D_001A7A0A;
extern char D_00189E20_9[];
extern float math_random_angle(void);
extern float mat_fast_helper_a(float, float);
extern void cam_compute_view_direction(float *, float *, int);
extern float vec_length_xy(float *);
extern void vec_random_direction(float *, float, float);
extern float math_random_float_range(float, float);
extern void vec_transform_and_set_height(char *, float *, float *, int, float);
extern char *cam_moby_create(char *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void UpdateWeaponAmmoPickup(void *);
extern float gravity_get_center_distance(float *);
extern void func_002A0F48(void *);
extern void hero_copy_field_to_moby(char *);

/* Spawns an ammo pickup (class 0xCDB, updated by func_0031FC28) for a weapon at a position;
   an amount of -1 takes the weapon's default, doubled while D_001A7A0A is set. */
char *SpawnWeaponAmmoPickup(float *position, int weapon, int amount, int extra)
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
    if (D_001A8CA0) {
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
        *(void (**)(void *))(spawn + 0x64) = UpdateWeaponAmmoPickup;
        data = *(AmmoSpawnData **)(spawn + 0x68);
        if (amount == -1)
            data->amount = ((AmmoSpawnWeapon *)((char *)weapons
                + slots[stub_empty_19(weapon)] * stride))->pickupAmount;
        else
            data->amount = amount;
        if (D_001A7A0A)
            data->amount *= 2;
        data->weapon = weapon;
        data->f6C = (float)extra;
        data->f70 = 16;
        if (D_001A8CA0)
            data->groundZ = gravity_get_center_distance((float *)(spawn + 0x10));
        else
            data->groundZ = *(float *)(spawn + 0x18);
        func_002A0F48(spawn);
        hero_copy_field_to_moby(spawn);
    }
    return spawn;
}
