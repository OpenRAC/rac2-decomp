#include "include_asm.h"

#include "common.h"
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define P(p,o) (*(int **)((u8 *)(p)+(o)))
extern int g_oozla_intro_stage MACRO_ADDR;
extern void *g_path_l01_table[];
extern float g_swamp_beast_accel_param __attribute__((sda));
extern float g_swamp_beast_speed_param __attribute__((sda));
extern float g_swamp_beast_move_step_param __attribute__((sda));
extern float g_swamp_beast_angular_accel_param __attribute__((sda));
extern float g_swamp_beast_angular_speed_param __attribute__((sda));
extern float g_swamp_beast_angular_step_param __attribute__((sda));
extern float level_get_water_height_pal(void);
extern int FloatToInt(float);
extern int math_random_int_range(int,int);
extern void moby_set_controller_speed_limits(u8 *,float,float,float,float);
extern float path_l01_compute_segment_lengths(unsigned char *);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended_pal(void *,int,int,int);
extern float coll_probe_ground_height_below(void *,int,float);
extern void *moby_spawn_linked_helper(u8 *,void *,u32,float,float);

/* Sets up a swimming creature when it appears: fixes its water height, speeds, turn rates and starting animation (PAL version). */
void swamp_beast_init_state_pal(u8 *moby)
{
    u8 *state = *(u8 **)(moby+0x68);
    float height, scale, angular_step, movement_step;
    float acceleration, velocity, angular_acceleration, angular_velocity;
    int wait_time;
    if (g_oozla_intro_stage == 0 && moby[0x21] != 255) *P(state,0x33C) = 0;
    height = level_get_water_height_pal();
    if (height > 0.0f) F(state,0x34C) = height;
    if (!(height > 0.0f) && g_oozla_intro_stage < 4) return;
    I(state,0x378) = 0;
    if (moby[0x21] != 255) {
        *P(state,0x368) = 0;
        *P(state,0x36C) = -1;
        *P(state,0x370) = -1;
    }
    qcopy((state+0x2D0), (moby+0x10));
    state[0x48] = FloatToInt(10.0f);
    state[0x4A] = FloatToInt(8.0f);
    I(state,0xA8) = 5;
    F(state,0x9C) = 0.4f;
    state[0x79] = 1;
    state[0x70] = 0;
    F(state,0x90) = 0.5f;
    F(state,0x94) = 0.5f;
    if (F(state,0x37C) == 0.0f) F(state,0x37C) = 1.0f;
    state[0x28] = 3;
    state[0x2A] = 6;
    angular_step = g_swamp_beast_angular_step_param * 0.0003490659f;
    movement_step = g_swamp_beast_move_step_param * 0.020000001f;
    F(state,0x30) = 0.5f;
    F(state,0x210) = 1.0f;
    F(state,0x21C) = 5.0f;
    F(state,0x220) = 6.0f;
    F(state,0x218) = angular_step;
    F(state,0x214) = movement_step;
    wait_time = math_random_int_range(100,0);
    scale = F(state,0x37C);
    acceleration = g_swamp_beast_accel_param*(scale*0.00040000002f);
    velocity = g_swamp_beast_speed_param*(scale*0.020000001f);
    angular_acceleration = g_swamp_beast_angular_accel_param*(scale*6.981318e-06f);
    angular_velocity = g_swamp_beast_angular_speed_param*(scale*0.0003490659f);
    F(state,0x110) = 1.0f;
    I(state,0x32C) = wait_time;
    F(state,0x114) = 0.2f;
    F(state,0x118) = 0.25f;
    F(state,0x120) = 0.52359885f;
    F(state,0x11C) = 0.25f;
    F(state,0x140) = 0.52359885f;
    F(state,0x13C) = 0.0072000003f;
    moby_set_controller_speed_limits(moby,acceleration,velocity,angular_acceleration,angular_velocity);
    if (I(state,0x30C) != -1) path_l01_compute_segment_lengths(g_path_l01_table[I(state,0x30C)]);
    if (I(state,0x364) != -1) path_l01_compute_segment_lengths(g_path_l01_table[I(state,0x364)]);
    if (I(state,0x308) == -1) {
        if (I(state,0x374) == 0) goto grounded;
    } else {
        path_l01_compute_segment_lengths(g_path_l01_table[I(state,0x308)]);
        I(state,0x14C) = I(state,0x308);
        moby_set_state(moby,1,1);
        F(moby,0x18) = F(state,0x34C);
    }
    if (I(state,0x374) != 0) {
        moby_set_state(moby,5,1);
        F(moby,0x18) = F(state,0x34C) + -2.0f;
    }
    I(moby,0x98) = 0;
    if (moby[0x43] != 4) anim_start_blended_pal(moby,4,0,2);
    goto next;
grounded:
    F(moby,0x18) = coll_probe_ground_height_below(moby+0x10,0,0.5f);
    if (I(state,0x364) != -1)
        I(state,0x14C) = I(state,0x364);
    else
        I(state,0x14C) = I(state,0x30C);
    moby[0xBC] = 0;
    I(state,0x398) = I(state,0x394);
    F(state,0x39C) = F(state,0x388);
    moby_set_state(moby,1,3);
    if (moby[0x43] != 0) anim_start_blended_pal(moby,0,0,2);
next:
    if (I(state,0x380) != -1) {
        if (moby[0x43] != 20) anim_start_blended_pal(moby,20,0,2);
        I(state,0x14C) = I(state,0x30C);
        I(state,0x398) = I(state,0x390);
        F(state,0x39C) = F(state,0x388);
        moby_set_state(moby,6,3);
    }
    qcopy((state+0x200), (moby+0x10));
    moby_spawn_linked_helper(moby,moby+0x10,5,0.2f,2.0f);
    I(state,0x39C) = 0;
    I(state,0x398) = I(state,0x390);
}
