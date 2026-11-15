#include "common.h"

extern char *D_L08_001B29DC __attribute__((sda));

typedef int TI128 __attribute__((mode(TI)));

/* Tuning words read by func_L08_003D3EF8. */
extern float D_L08_001B0338 __attribute__((sda));
extern float D_L08_001B033C __attribute__((sda));
extern float D_L08_001B0340 __attribute__((sda));
extern float D_L08_001B0344 __attribute__((sda));
extern unsigned char D_L08_001B0348 __attribute__((sda));
extern int D_L08_001B034C __attribute__((sda));
extern int D_L08_001B0350 __attribute__((sda));
extern float D_L08_001B0354 __attribute__((sda));
extern float D_L08_001B0358 __attribute__((sda));
extern int D_L08_001B035C __attribute__((sda));
extern int D_L08_001B0360 __attribute__((sda));
extern int D_L08_001B0368 __attribute__((sda));
extern int D_L08_001B036C __attribute__((sda));
/* The frame counter: absolute loads, $gp in a delay slot. */
extern int D_L08_001B2508 MACRO_ADDR;
extern char D_L08_001B9B00[];

extern void moby_transform_joint_to_world(void *, int, void *);
extern int math_random_int_below(int);
extern void vec_random_direction(void *, float, float);
extern void part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);
extern unsigned char *part_spawn_fading(void *, int, unsigned char, int, int, int, int, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(int, int, float);

/* Returns the height of the object with the given index, or 0 when there is none. */
float moby_get_height(int moby_index) {
    if (moby_index != -1)
        return *(float *)(D_L08_001B29DC + ((unsigned int)moby_index << 8) + 0x18);
    return 0.0f;
}

/* Tells whether the linked object is switched on. */
int moby_is_linked_switched_on(int moby_index) {
    if (moby_index != -1) {
        if (*(unsigned char *)(*(unsigned char **)(D_L08_001B29DC
                                                  + ((unsigned int)moby_index << 8) + 0x68)
                              + 0x14) != 0)
            return 1;
    }
    return 0;
}

/* The parameter block of the shared spawn routines (func_L04_003A1A78 and its siblings). */
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
extern char D_L08_002A0D00[];
extern char D_L08_0023EC80[];
extern char D_L08_0023ECF0[];
extern char D_L08_002A87F0[];
extern int D_L08_001B01B8[2] __attribute__((sda));
/* Kind 7 consumes seven halfwords; the full owner extent remains unknown. */
extern u16 D_L08_001B01C8[] SDATA(D_L08_001B01C8);
extern int D_L08_001B01D8 __attribute__((sda));
extern int D_L08_001B01DC __attribute__((sda));
extern void water_start_effect(void);
extern void gfx_add_draw_callback_first(void);
extern void water_init_object(L08SpawnBlock *);
extern void water_add_splash_entry(void *, float);
extern void water_update_controller(L08SpawnBlock *);
extern void water_advance_controller_state(L08SpawnBlock *);
extern void water_update_ripple_patches(L08SpawnBlock *);

/* Runs the shared spawn routines for the object, unless the level's player (the entity at
   D_00189E20+0x1830, kind 0x45) is alive while the mode word at +0x2294 is 0x31. The count
   is the state's +0x10 plus an entry of D_L08_001B01B8 picked by +0x18 (1 when -1); state
   0 sets the object up first and then shares state 1's step, state 2 has its own. */
/* Water object: runs the shared spawn routines that make the water splash and ripple effects. */
void water_update(char *owner)
{
    L08SpawnBlock spawn_block;
    char *world = g_hero_state;
    char *hero = *(char **)(world + 0x1830);
    char *vars;
    int spawn_count;

    if (hero != 0 && *(short *)(hero + 0xAA) == 0x45 &&
        *(unsigned char *)(hero + 0x20) != 0xFE && *(unsigned char *)(hero + 0x20) != 0xFD &&
        *(int *)(world + 0x2294) == 0x31)
        return;
    vars = *(char **)(owner + 0x68);
    if (vars == 0)
        return;
    spawn_count = 1;
    if (*(int *)(vars + 0x18) != -1)
        spawn_count = D_L08_001B01B8[*(int *)(vars + 0x18)];
    spawn_count += *(int *)(vars + 0x10);
    spawn_block.kind = 7;
    spawn_block.count = spawn_count;
    spawn_block.small1 = &D_L08_001B01D8;
    spawn_block.small2 = &D_L08_001B01DC;
    spawn_block.table0 = D_L08_002A0D00;
    spawn_block.table1 = D_L08_0023EC80;
    spawn_block.small0 = D_L08_001B01C8;
    spawn_block.counts = D_L08_001B01B8;
    spawn_block.table2 = D_L08_0023ECF0;
    spawn_block.table3 = D_L08_002A87F0;
    spawn_block.owner = owner;
    spawn_block.callback = water_start_effect;
    spawn_block.callback2 = gfx_add_draw_callback_first;
    switch (*(unsigned char *)(owner + 0x20)) {
    case 0:
        water_init_object(&spawn_block);
        water_add_splash_entry(owner, *(float *)(vars + 0x28));
    case 1:
        water_update_controller(&spawn_block);
        break;
    case 2:
        water_advance_controller_state(&spawn_block);
        break;
    }
    water_update_ripple_patches(&spawn_block);
}

/* Tells whether the linked object is switched on. */
int seesaw_is_linked_switched_on(int moby_index) {
    if (moby_index != -1) {
        if (*(unsigned char *)(*(unsigned char **)(D_L08_001B29DC
                                                  + ((unsigned int)moby_index << 8) + 0x68)
                              + 0x14) != 0)
            return 1;
    }
    return 0;
}

/* After a one-in-four roll, spawns four particles from joint 0 whose velocity grows by a
   random step each time; then draws four rings between the moby and the point at
   D_L08_001B9B00, laid out as RAC1's update_gold_bolt_glow_rings lays out its rings: each
   ring's colour follows the frame counter, and its byte argument (the ring angle in RAC1)
   is the counter's low byte, doubled and/or inverted by the ring index. */
/* Spawns sparks and draws four glowing rings around the object that pulse with the frame counter. */
void SpawnParticlesAndDrawGlowRings(char *moby)
{
    TI128 joint_pos, spark_velocity, velocity_step, ring_pos, ring_step;
    int spark_index;
    int ring_index;
    int angle_byte;
    float phase;
    float reciprocal, half, size;
    int ring_color;

    moby_transform_joint_to_world(moby, 0, &joint_pos);
    if (math_random_int_below(4) == 0) {
        vec_random_direction(&spark_velocity, D_L08_001B0338 * 0.016666668f, D_L08_001B033C * 0.016666668f);
        angle_byte = D_L08_001B0348;
        part_spawn_hero_relative(&joint_pos, &spark_velocity, D_L08_001B034C, angle_byte, math_random_int_below(255), 0, D_L08_001B0354);
        for (spark_index = 2; spark_index >= 0; spark_index--) {
            vec_random_direction(&velocity_step, D_L08_001B0340 * 0.016666668f, D_L08_001B0344 * 0.016666668f);
            FastVecAdd(&spark_velocity, &spark_velocity, &velocity_step);
            angle_byte = D_L08_001B0348;
            part_spawn_hero_relative(&joint_pos, &spark_velocity, D_L08_001B0350, angle_byte, math_random_int_below(255), 0, D_L08_001B0358);
        }
    }
    FastVecSub(&ring_pos, D_L08_001B9B00, &joint_pos);
    vec_scale_to_length(&ring_pos, &ring_pos, -0.3f);
    vec_scale_to_length(&ring_step, &ring_pos, 0.1f);
    FastVecAdd(&ring_pos, &ring_pos, &joint_pos);
    reciprocal = 0.003921569f;
    half = 0.5f;
    size = 3.0f;
    for (ring_index = 0; ring_index < 4; ring_index++) {
        phase = IntToFloat(0xFF - ((D_L08_001B2508 + ring_index * 20) & 0xFF));
        ring_color = FastTweenColor(D_L08_001B035C, D_L08_001B0360, math_fabs(half - phase * reciprocal));
        angle_byte = D_L08_001B2508 & 0xFF;
        if (ring_index & 2)
            angle_byte = angle_byte * 2;
        if (ring_index & 1)
            angle_byte = 0xFF - angle_byte;
        part_spawn_fading(&ring_pos, ring_color, angle_byte, D_L08_001B036C, D_L08_001B0368, 2, 0,
                      (IntToFloat(ring_index) + size)
                          * (*(float *)(moby + 0x2C) / *(float *)(*(char **)(moby + 0x24) + 0x24)));
        FastVecAdd(&ring_pos, &ring_pos, &ring_step);
    }
}
