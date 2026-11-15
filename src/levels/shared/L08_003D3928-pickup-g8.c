#include "common.h"
typedef int PickupQuad __attribute__((mode(TI)));
extern u8 D_L08_0021EAF0[];
extern u8 D_0019B4A8[];
extern int g_current_map_index[] __attribute__((sda));
/* Partial resident view through the last state field read here. */
typedef struct {
    u8 unknown00[0x80];
    PickupQuad position;
    u8 unknown90[0x17A0];
    u8 *vehicle;
    u8 unknown1834[0xA60];
    int mode;
    u8 unknown2298[4];
    int world;
} ResidentPrefix;
extern ResidentPrefix g_hero_state;
typedef struct { int duration; int timer; float progress; } PickupState;
extern int D_00138320[];
extern float D_L08_001B031C __attribute__((sda));
extern float D_L08_001B0324 __attribute__((sda));
extern float D_L08_001B032C __attribute__((sda));
extern float D_L08_001B0330 __attribute__((sda));
extern float D_L08_001B0334 __attribute__((sda));
extern int D_L08_001B0370 __attribute__((sda));
extern void anim_start_blended(u8 *object, int bank, int anim, int frames);
extern float coll_probe_ground_height_below(void *position, int flags, float distance);
extern float vec_distance_xy(void *a, void *b);
extern void FastVecSub(void *out, void *a, void *b);
extern void FastVecScale(void *out, void *a, float scale);
extern void vec_fast_divide_helper(void *out, void *a, float magnitude);
extern void FastVecAdd(void *out, void *a, void *b);
extern int math_fast_float_d(int *timer);
extern void moby_mark_spawned(void *object);
extern void SpawnParticlesAndDrawGlowRings(u8 *object);

typedef struct { u8 p[0x464]; u8 x[1]; } Hist;
typedef struct { u8 p[0x8e]; short lock; } VData;
typedef struct { u8 p[0x31]; u8 held; u8 p2[2]; u16 flags; u8 p3[0x12]; float scale; } OView;
/* Updates a pickup (moby class 2458, Raritanium): it waits to be grabbed, is pulled towards the
   mining vehicle, then follows the hero while its amount drains, and disappears when used up. */
void raritanium_pickup_update(u8 *object)
{
    PickupState *vars = *(PickupState **)(object + 0x68);
    u8 *vehicle;
    u8 *vehicle_vars;
    unsigned short pickup_id;
    float drain_step;
    float pull[4] __attribute__((aligned(16)));
    if (object[0xb0] != 255) {
        pickup_id = *(unsigned short *)(object + 0xb2);
        {
        int saved_bits;
        if (((Hist *)D_L08_0021EAF0)->x[(short)pickup_id])
            goto kill;
        saved_bits = D_0019B4A8[((short)pickup_id >> 1) + (g_current_map_index[0] << 10)];
        if (pickup_id & 1) { if ((saved_bits >> 4) & 7) goto kill; }
        else if (saved_bits & 7) goto kill;
        }
    }
    switch (object[0x20]) {
    case 0: {
        float value;
        object[0x30] = 255;
        object[0x31] = 0;
        *(unsigned short *)(object + 0x34) |= 1;
        vars->timer = vars->duration * 60;
        if (object[0x43])
            anim_start_blended(object, 0, 0, 2);
        object[0x20] = 1;
        value = coll_probe_ground_height_below(object + 0x10, 0, 200.0f);
        if (value != 0.0f)
            *(float *)(object + 0x18) = value;
        break;
    }
    case 1: {
        float value;
        vehicle = g_hero_state.vehicle;
        if (vehicle == 0 || *(short *)(vehicle + 0xaa) != MOBY_CLASS_MINING_VEHICLE ||
            vehicle[0x20] == 254 || vehicle[0x20] == 253 ||
            g_hero_state.mode != 0x31)
            return;
        vehicle_vars = *(u8 **)(vehicle + 0x68);
        *(u8 **)(vehicle_vars + 0x1b0) = object;
        value = vec_distance_xy(object + 0x10, &g_hero_state.position);
        if (value < *(float *)(vehicle_vars + 0x68)) {
            *(float *)(vehicle_vars + 0x68) = value;
            *(u8 **)(vehicle_vars + 0x6c) = object;
        }
        if (!(value < D_L08_001B031C) || !(*D_00138320 & 0x80))
            return;
        { u8 *activeVehicle = g_hero_state.vehicle;
        if (activeVehicle == 0 || (activeVehicle[0x42] != 2 && activeVehicle[0x43] != 2))
            return; }
        FastVecSub(pull, &g_hero_state.position, object + 0x10);
        FastVecScale(pull, pull, 0.1f);
        pull[2] = 0;
        vec_fast_divide_helper(pull, pull, D_L08_001B0334 * 0.0166666675f);
        FastVecAdd(object + 0x10, object + 0x10, pull);
        if (!math_fast_float_d(&vars->timer))
            return;
        ((VData *)vehicle_vars)->lock = 180;
        vars->timer = D_L08_001B0370;
        qcopy(object + 0x10, &g_hero_state.position);
        ((OView *)object)->held = 1;
        ((OView *)object)->flags = (((OView *)object)->flags & 0xfffe) | 0x800;
        vars->progress = D_L08_001B032C;
        if (object[0x43] != 1)
            anim_start_blended(object, 1, 0, 30);
        ((OView *)object)->scale = vars->progress * 2.0f;
        object[0x20] = 2;
        break;
    }
    case 2: {
        float value;
        value = vars->progress;
        value += (1.0f - value) * D_L08_001B0324;
        vars->progress = value;
        *(float *)(object + 0x48) = value * 2.0f;
        qcopy(object + 0x10, &g_hero_state.position);
        if (math_fast_float_d(&vars->timer) || *(float *)(object + 0x2c) <= 0.0f) {
            drain_step = D_L08_001B0330 * *(float *)(*(u8 **)(object + 0x24) + 0x24);
            if (drain_step < *(float *)(object + 0x2c) || g_hero_state.world == 20 ||
                g_hero_state.world == 25 ||
                g_hero_state.mode == 0x39 ||
                g_hero_state.mode == 0x6f) {
                *(float *)(object + 0x2c) -= drain_step;
            } else {
                g_current_map_index[3]++;
                { unsigned short pickup_id2 = *(unsigned short *)(object + 0xb2);
                if (pickup_id2 & 1) {
                    u8 *saved_byte = &D_0019B4A8[((short)pickup_id2 >> 1) + (g_current_map_index[0] << 10)];
                    if (((*saved_byte >> 4) & 7) != 7)
                        *saved_byte += 16;
                } else {
                    u8 *saved_byte = &D_0019B4A8[((short)pickup_id2 >> 1) + (g_current_map_index[0] << 10)];
                    if ((*saved_byte & 7) != 7)
                        (*saved_byte)++;
                } }
kill:
                moby_mark_spawned(object);
                return;
            }
        }
        SpawnParticlesAndDrawGlowRings(object);
        break;
    }
    }
}
