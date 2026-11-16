#include "include_asm.h"

#include "common.h"
typedef struct {
    int kind;
    int count;
    void *table0;
    void *table1;
    void *small0;
    void *counts;
    void *table2;
    void *table3;
    void *small1;
    void *small2;
    void *owner;
    void *callback;
    void *callback2;
} L08SpawnBlock;
extern char g_hero_state[];
extern char g_water_spawn_table_zero[];
extern char g_water_spawn_table_one[];
extern char g_water_spawn_table_two[];
extern char g_water_spawn_table_three[];
extern int g_water_spawn_counts[2] __attribute__((sda));
extern u16 g_water_small_spawn_table[] SDATA(D_L08_001B01C8);
extern int g_water_small_spawn_value_a __attribute__((sda));
extern int g_water_small_spawn_value_b __attribute__((sda));
extern void water_start_effect(void);
extern void gfx_add_draw_callback_first(void);
extern void water_init_object_pal(L08SpawnBlock *);
extern void water_add_splash_entry(void *, float);
extern void water_update_controller_pal(L08SpawnBlock *);
extern void water_advance_controller_state(L08SpawnBlock *);
extern void water_update_ripple_patches(L08SpawnBlock *);

/* Runs the shared spawn routines for the object, unless the level's player (the entity at
   D_00189E20+0x1830, kind 0x45) is alive while the mode word at +0x2294 is 0x31. The count
   is the state's +0x10 plus an entry of D_L08_001B01B8 picked by +0x18 (1 when -1); state
   0 sets the object up first and then shares state 1's step, state 2 has its own. */
void water_update_pal(char *object)
{
    L08SpawnBlock block;
    char *level = g_hero_state;
    char *player = *(char **)(level + 0x1830);
    char *state;
    int count;

    if (player != 0 && *(short *)(player + 0xAA) == 0x45 &&
        *(unsigned char *)(player + 0x20) != 0xFE && *(unsigned char *)(player + 0x20) != 0xFD &&
        *(int *)(level + 0x2294) == 0x31)
        return;
    state = *(char **)(object + 0x68);
    if (state == 0)
        return;
    count = 1;
    if (*(int *)(state + 0x18) != -1)
        count = g_water_spawn_counts[*(int *)(state + 0x18)];
    count += *(int *)(state + 0x10);
    block.kind = 7;
    block.count = count;
    block.small1 = &g_water_small_spawn_value_a;
    block.small2 = &g_water_small_spawn_value_b;
    block.table0 = g_water_spawn_table_zero;
    block.table1 = g_water_spawn_table_one;
    block.small0 = g_water_small_spawn_table;
    block.counts = g_water_spawn_counts;
    block.table2 = g_water_spawn_table_two;
    block.table3 = g_water_spawn_table_three;
    block.owner = object;
    block.callback = water_start_effect;
    block.callback2 = gfx_add_draw_callback_first;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        water_init_object_pal(&block);
        water_add_splash_entry(object, *(float *)(state + 0x28));
    case 1:
        water_update_controller_pal(&block);
        break;
    case 2:
        water_advance_controller_state(&block);
        break;
    }
    water_update_ripple_patches(&block);
}
