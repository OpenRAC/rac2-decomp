#include "common.h"

typedef struct {
    u8 prefix[0x1830];
    u8 *controller;
    u8 gap[0x2294 - 0x1834];
    int state;
} ResidentWaterView;
extern ResidentWaterView g_hero_state;

/* Counts and masks have unknown owning extents; these GP address views do not
 * give them invented small array bounds. The initializer consumes six masks. */
extern int D_L20_001B2330[] SDATA(D_L20_001B2330);
extern u16 D_L20_001B2338[] SDATA(D_L20_001B2338);
extern int D_L20_001B2344 __attribute__((sda));
extern int D_L20_001B2348 __attribute__((sda));
extern u8 *D_L20_001B2F9C __attribute__((sda));
extern u8 D_L20_002AB980[];
extern u8 D_L20_0025DD00[];
extern int D_L20_0025DD60[];
typedef struct { int id, offsets[2], size; } WaterHeaderSlot;
extern WaterHeaderSlot D_L20_002B22E0[];
extern void level_start_fixed_effect(void);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void water_init_object(u8 *);
extern void water_add_splash_entry(u32, float);
extern void water_update_controller(char *);
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

/* Runs a patch of water (moby class 4685). It builds and draws the water tiles and turns on the objects linked to it. */
void water_patch_update(u8 *object)
{
    WaterContext context;
    u8 *state;
    u8 *controller = g_hero_state.controller;
    int count;
    int remaining;
    int *child;
    int absent;

    if (controller != 0 && *(s16 *)(controller + 0xAA) == 0x45 /* moby class 69 */ &&
        controller[0x20] != 0xFE && controller[0x20] != 0xFD &&
        g_hero_state.state == 0x31)
        return;
    state = *(u8 **)(object + 0x68);
    if (state == 0)
        return;
    count = 1;
    if (*(int *)(state + 0x18) != -1)
        count = D_L20_001B2330[*(int *)(state + 0x18)];
    count += *(int *)(state + 0x10);
    context.count = 6;
    context.activeCount = count;
    context.slotCount = &D_L20_001B2344;
    context.used = &D_L20_001B2348;
    context.tiles = D_L20_002AB980;
    context.parameters = D_L20_0025DD00;
    context.masks = D_L20_001B2338;
    context.counts = D_L20_001B2330;
    context.buffer = D_L20_0025DD60;
    context.slots = D_L20_002B22E0;
    context.owner = object;
    context.draw = level_start_fixed_effect;
    context.enqueue = gfx_add_draw_callback_third;
    switch (object[0x20]) {
    case 0:
        water_init_object((u8 *)&context);
        water_add_splash_entry((u32)object, *(float *)(state + 0x28));
    case 1:
        water_update_controller((char *)&context);
        break;
    case 2:
        absent = -1;
        water_advance_controller_state((u8 *)&context);
        child = (int *)(state + 0x30);
        for (remaining = 3; remaining >= 0; --remaining, ++child) {
            if (*child != absent)
                moby_set_flag_bit(D_L20_001B2F9C + (*child << 8), state[0x14]);
        }
        break;
    }
    water_update_ripple_patches((u8 *)&context);
}
