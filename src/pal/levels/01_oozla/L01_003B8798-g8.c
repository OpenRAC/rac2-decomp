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
extern float func_PAL_L01_003BEB40(void);
extern int FloatToInt(float);
extern int math_random_int_range(int,int);
extern void moby_set_controller_speed_limits(u8 *,float,float,float,float);
extern float path_l01_compute_segment_lengths(unsigned char *);
extern void moby_set_state(void *,int,int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern float coll_probe_ground_height_below(void *,int,float);
extern void *moby_spawn_linked_helper(u8 *,void *,u32,float,float);

void swamp_beast_init_state_pal(u8 *object)
{
    u8 *state = *(u8 **)(object+0x68);
    float height, scale, angularStep, movementStep;
    float acceleration, velocity, angularAcceleration, angularVelocity;
    int handle;
    if (g_oozla_intro_stage == 0 && object[0x21] != 255) *P(state,0x33C) = 0;
    height = func_PAL_L01_003BEB40();
    if (height > 0.0f) F(state,0x34C) = height;
    if (!(height > 0.0f) && g_oozla_intro_stage < 4) return;
    I(state,0x378) = 0;
    if (object[0x21] != 255) {
        *P(state,0x368) = 0;
        *P(state,0x36C) = -1;
        *P(state,0x370) = -1;
    }
    qcopy((state+0x2D0), (object+0x10));
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
    angularStep = g_swamp_beast_angular_step_param * 0.0003490659f;
    movementStep = g_swamp_beast_move_step_param * 0.020000001f;
    F(state,0x30) = 0.5f;
    F(state,0x210) = 1.0f;
    F(state,0x21C) = 5.0f;
    F(state,0x220) = 6.0f;
    F(state,0x218) = angularStep;
    F(state,0x214) = movementStep;
    handle = math_random_int_range(100,0);
    scale = F(state,0x37C);
    acceleration = g_swamp_beast_accel_param*(scale*0.00040000002f);
    velocity = g_swamp_beast_speed_param*(scale*0.020000001f);
    angularAcceleration = g_swamp_beast_angular_accel_param*(scale*6.981318e-06f);
    angularVelocity = g_swamp_beast_angular_speed_param*(scale*0.0003490659f);
    F(state,0x110) = 1.0f;
    I(state,0x32C) = handle;
    F(state,0x114) = 0.2f;
    F(state,0x118) = 0.25f;
    F(state,0x120) = 0.52359885f;
    F(state,0x11C) = 0.25f;
    F(state,0x140) = 0.52359885f;
    F(state,0x13C) = 0.0072000003f;
    moby_set_controller_speed_limits(object,acceleration,velocity,angularAcceleration,angularVelocity);
    if (I(state,0x30C) != -1) path_l01_compute_segment_lengths(g_path_l01_table[I(state,0x30C)]);
    if (I(state,0x364) != -1) path_l01_compute_segment_lengths(g_path_l01_table[I(state,0x364)]);
    if (I(state,0x308) == -1) {
        if (I(state,0x374) == 0) goto grounded;
    } else {
        path_l01_compute_segment_lengths(g_path_l01_table[I(state,0x308)]);
        I(state,0x14C) = I(state,0x308);
        moby_set_state(object,1,1);
        F(object,0x18) = F(state,0x34C);
    }
    if (I(state,0x374) != 0) {
        moby_set_state(object,5,1);
        F(object,0x18) = F(state,0x34C) + -2.0f;
    }
    I(object,0x98) = 0;
    if (object[0x43] != 4) func_PAL_002A7E68(object,4,0,2);
    goto next;
grounded:
    F(object,0x18) = coll_probe_ground_height_below(object+0x10,0,0.5f);
    if (I(state,0x364) != -1)
        I(state,0x14C) = I(state,0x364);
    else
        I(state,0x14C) = I(state,0x30C);
    object[0xBC] = 0;
    I(state,0x398) = I(state,0x394);
    F(state,0x39C) = F(state,0x388);
    moby_set_state(object,1,3);
    if (object[0x43] != 0) func_PAL_002A7E68(object,0,0,2);
next:
    if (I(state,0x380) != -1) {
        if (object[0x43] != 20) func_PAL_002A7E68(object,20,0,2);
        I(state,0x14C) = I(state,0x30C);
        I(state,0x398) = I(state,0x390);
        F(state,0x39C) = F(state,0x388);
        moby_set_state(object,6,3);
    }
    qcopy((state+0x200), (object+0x10));
    moby_spawn_linked_helper(object,object+0x10,5,0.2f,2.0f);
    I(state,0x39C) = 0;
    I(state,0x398) = I(state,0x390);
}
