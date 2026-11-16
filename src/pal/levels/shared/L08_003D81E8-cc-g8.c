#include "names.h"
/* func_PAL_L08_003D81E8, the PAL copy of func_L08_003D4190: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_L08_003D3EF8 becomes func_PAL_L08_003D7F30; scale D_L08_001B0370; wrap *(float *)(*(u8 **)(object + 0x24) + 0x24) (({e}) * 1.2. */
#include "common.h"
typedef int PickupQuad __attribute__((mode(TI)));
extern u8 g_moby_spawn_state_flags_b[];
extern u8 g_moby_nibble_table[];
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
extern int g_pad_pressed_flags[];
extern float g_hud_l08_bar_threshold __attribute__((sda));
extern float g_raritanium_pickup_blend __attribute__((sda));
extern float g_raritanium_pickup_start_progress __attribute__((sda));
extern float g_raritanium_pickup_drain_scale __attribute__((sda));
extern float g_pickup_pull_scale __attribute__((sda));
extern int g_raritanium_pickup_timer __attribute__((sda));
extern void func_PAL_002A7E68(u8 *object, int bank, int anim, int frames);
extern float coll_probe_ground_height_below(void *position, int flags, float distance);
extern float vec_distance_xy(void *a, void *b);
extern void FastVecSub(void *out, void *a, void *b);
extern void FastVecScale(void *out, void *a, float scale);
extern void vec_fast_divide_helper(void *out, void *a, float magnitude);
extern void FastVecAdd(void *out, void *a, void *b);
extern int math_fast_float_d(int *timer);
extern void moby_mark_spawned(void *object);
extern void func_PAL_L08_003D7F30(u8 *object);

typedef struct { u8 p[0x464]; u8 x[1]; } Hist;
typedef struct { u8 p[0x8e]; short lock; } VData;
typedef struct { u8 p[0x31]; u8 held; u8 p2[2]; u16 flags; u8 p3[0x12]; float scale; } OView;
void func_PAL_L08_003D81E8(u8 *object)
{
    PickupState *data = *(PickupState **)(object + 0x68);
    u8 *vehicle;
    u8 *vehicleData;
    unsigned short id;
    float cost;
    float movement[4] __attribute__((aligned(16)));
    if (object[0xb0] != 255) {
        id = *(unsigned short *)(object + 0xb2);
        {
        int n;
        if (((Hist *)g_moby_spawn_state_flags_b)->x[(short)id])
            goto kill;
        n = g_moby_nibble_table[((short)id >> 1) + (g_current_map_index[0] << 10)];
        if (id & 1) { if ((n >> 4) & 7) goto kill; }
        else if (n & 7) goto kill;
        }
    }
    switch (object[0x20]) {
    case 0: {
        float value;
        object[0x30] = 255;
        object[0x31] = 0;
        *(unsigned short *)(object + 0x34) |= 1;
        data->timer = data->duration * 50;
        if (object[0x43])
            func_PAL_002A7E68(object, 0, 0, 2);
        object[0x20] = 1;
        value = coll_probe_ground_height_below(object + 0x10, 0, 200.0f);
        if (value != 0.0f)
            *(float *)(object + 0x18) = value;
        break;
    }
    case 1: {
        float value;
        vehicle = g_hero_state.vehicle;
        if (vehicle == 0 || *(short *)(vehicle + 0xaa) != 0xeef ||
            vehicle[0x20] == 254 || vehicle[0x20] == 253 ||
            g_hero_state.mode != 0x31)
            return;
        vehicleData = *(u8 **)(vehicle + 0x68);
        *(u8 **)(vehicleData + 0x1b0) = object;
        value = vec_distance_xy(object + 0x10, &g_hero_state.position);
        if (value < *(float *)(vehicleData + 0x68)) {
            *(float *)(vehicleData + 0x68) = value;
            *(u8 **)(vehicleData + 0x6c) = object;
        }
        if (!(value < g_hud_l08_bar_threshold) || !(*g_pad_pressed_flags & 0x80))
            return;
        { u8 *activeVehicle = g_hero_state.vehicle;
        if (activeVehicle == 0 || (activeVehicle[0x42] != 2 && activeVehicle[0x43] != 2))
            return; }
        FastVecSub(movement, &g_hero_state.position, object + 0x10);
        FastVecScale(movement, movement, 0.1f);
        movement[2] = 0;
        vec_fast_divide_helper(movement, movement, g_pickup_pull_scale * 0.020000001f);
        FastVecAdd(object + 0x10, object + 0x10, movement);
        if (!math_fast_float_d(&data->timer))
            return;
        ((VData *)vehicleData)->lock = 180;
        data->timer = (((int)(g_raritanium_pickup_timer) * 5 + 2) / 6);
        qcopy(object + 0x10, &g_hero_state.position);
        ((OView *)object)->held = 1;
        ((OView *)object)->flags = (((OView *)object)->flags & 0xfffe) | 0x800;
        data->progress = g_raritanium_pickup_start_progress;
        if (object[0x43] != 1)
            func_PAL_002A7E68(object, 1, 0, 30);
        ((OView *)object)->scale = data->progress * 2.0f;
        object[0x20] = 2;
        break;
    }
    case 2: {
        float value;
        value = data->progress;
        value += (1.0f - value) * g_raritanium_pickup_blend;
        data->progress = value;
        *(float *)(object + 0x48) = value * 2.0f;
        qcopy(object + 0x10, &g_hero_state.position);
        if (math_fast_float_d(&data->timer) || *(float *)(object + 0x2c) <= 0.0f) {
            cost = g_raritanium_pickup_drain_scale * ((*(float *)(*(u8 **)(object + 0x24) + 0x24)) * 1.2f);
            if (cost < *(float *)(object + 0x2c) || g_hero_state.world == 20 ||
                g_hero_state.world == 25 ||
                g_hero_state.mode == 0x39 ||
                g_hero_state.mode == 0x6f) {
                *(float *)(object + 0x2c) -= cost;
            } else {
                g_current_map_index[3]++;
                { unsigned short id2 = *(unsigned short *)(object + 0xb2);
                if (id2 & 1) {
                    u8 *h = &g_moby_nibble_table[((short)id2 >> 1) + (g_current_map_index[0] << 10)];
                    if (((*h >> 4) & 7) != 7)
                        *h += 16;
                } else {
                    u8 *h = &g_moby_nibble_table[((short)id2 >> 1) + (g_current_map_index[0] << 10)];
                    if ((*h & 7) != 7)
                        (*h)++;
                } }
kill:
                moby_mark_spawned(object);
                return;
            }
        }
        func_PAL_L08_003D7F30(object);
        break;
    }
    }
}
