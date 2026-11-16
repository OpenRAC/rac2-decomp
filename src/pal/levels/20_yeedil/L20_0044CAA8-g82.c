#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 prefix[0x1830];
    u8 *controller;
    u8 gap[0x2294 - 0x1834];
    int state;
} ResidentWaterView;
extern ResidentWaterView g_hero_state;
extern int g_water_patch_slot_counts[] SDATA(D_L20_001B2330);
extern u16 g_water_patch_masks[] SDATA(D_L20_001B2338);
extern int g_water_patch_slot_count __attribute__((sda));
extern int g_water_patch_used __attribute__((sda));
extern u8 *g_group_l20_member_table __attribute__((sda));
extern u8 g_water_tile_grid[];
extern u8 g_water_patch_parameters[];
extern int g_water_patch_buffer[];
typedef struct { int id, offsets[2], size; } WaterHeaderSlot;
extern WaterHeaderSlot g_water_header_slots[];
extern void level_start_fixed_effect(void);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void water_init_object_pal(u8 *);
extern void water_add_splash_entry(u32, float);
extern void water_update_controller_pal(char *);
extern void water_advance_controller_state(u8 *);
extern void water_update_ripple_patches(u8 *);
extern void moby_set_flag_bit(void *, int);
typedef struct {
    int count, activeCount;
    u8 *tiles;
    u8 *parameters;
    u16 *masks;
    int *counts;
    int *buffer;
    WaterHeaderSlot *slots;
    int *slotCount, *used;
    u8 *owner;
    void (*draw)(void);
    void (*enqueue)(void (*)(void *), void *);
} WaterContext;

void water_patch_update_pal(u8 *object)
{
    WaterContext context;
    u8 *state;
    u8 *controller = g_hero_state.controller;
    int count;
    int remaining;
    int *child;
    int absent;

    if (controller != 0 && *(s16 *)(controller + 0xAA) == 0x45 &&
        controller[0x20] != 0xFE && controller[0x20] != 0xFD &&
        g_hero_state.state == 0x31)
        return;
    state = *(u8 **)(object + 0x68);
    if (state == 0)
        return;
    count = 1;
    if (*(int *)(state + 0x18) != -1)
        count = g_water_patch_slot_counts[*(int *)(state + 0x18)];
    count += *(int *)(state + 0x10);
    context.count = 6;
    context.activeCount = count;
    context.slotCount = &g_water_patch_slot_count;
    context.used = &g_water_patch_used;
    context.tiles = g_water_tile_grid;
    context.parameters = g_water_patch_parameters;
    context.masks = g_water_patch_masks;
    context.counts = g_water_patch_slot_counts;
    context.buffer = g_water_patch_buffer;
    context.slots = g_water_header_slots;
    context.owner = object;
    context.draw = level_start_fixed_effect;
    context.enqueue = gfx_add_draw_callback_third;
    switch (object[0x20]) {
    case 0:
        water_init_object_pal((u8 *)&context);
        water_add_splash_entry((u32)object, *(float *)(state + 0x28));
    case 1:
        water_update_controller_pal((char *)&context);
        break;
    case 2:
        absent = -1;
        water_advance_controller_state((u8 *)&context);
        child = (int *)(state + 0x30);
        for (remaining = 3; remaining >= 0; --remaining, ++child) {
            if (*child != absent)
                moby_set_flag_bit(g_group_l20_member_table + (*child << 8), state[0x14]);
        }
        break;
    }
    water_update_ripple_patches((u8 *)&context);
}
