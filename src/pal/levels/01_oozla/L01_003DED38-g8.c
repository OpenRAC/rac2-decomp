#include "names.h"
/* func_PAL_L01_003DED38, the PAL copy of func_L01_003DA740: the same C at 50 Hz, with the frame
 * constants rescaled and the particle lifetimes passed through the 5/6 scale. */
#include "common.h"
extern s32 g_debris_sprite_a __attribute__((sda));
extern s32 g_debris_sprite_b __attribute__((sda));
extern f32 g_debris_color_a_base __attribute__((sda));
extern f32 g_debris_color_b_base __attribute__((sda));
extern f32 g_debris_color_c_base __attribute__((sda));
extern f32 g_debris_burst_speed __attribute__((sda));
extern f32 g_debris_rise_speed __attribute__((sda));
extern f32 g_debris_speed_a __attribute__((sda));
extern f32 g_debris_vel_w __attribute__((sda));
extern f32 g_debris_accel_w __attribute__((sda));
extern f32 g_debris_angle_spread __attribute__((sda));
extern s32 g_debris_count_a __attribute__((sda));
extern s32 g_debris_second_sprite_a __attribute__((sda));
extern s32 g_debris_second_sprite_b __attribute__((sda));
extern f32 g_debris_second_color_a_base __attribute__((sda));
extern f32 g_debris_second_color_b_base __attribute__((sda));
extern f32 g_debris_second_color_c_base __attribute__((sda));
extern f32 g_debris_second_speed_a __attribute__((sda));
extern f32 g_debris_second_speed_b __attribute__((sda));
extern f32 g_debris_second_vel_w __attribute__((sda));
extern f32 g_debris_second_accel_w __attribute__((sda));
extern f32 g_debris_second_angle_spread_a __attribute__((sda));
extern f32 g_debris_second_angle_spread_b __attribute__((sda));
extern s32 g_debris_count_b __attribute__((sda));
extern f32 mat_fast_helper_a(f32, f32);
extern f32 vec_length_xy(void *);
extern f32 math_random_float_range(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern s32 FloatToInt(f32);
extern void vec_build_spherical_offset(void *, f32, f32, f32);
extern u8 *part_spawn_trail(void *, void *, void *, s32, s32, s32, s32, s32, s32);
extern s32 func_001163B0(void);
void func_PAL_L01_003DED38(u8 *obj) {
    f32 vel[4] __attribute__((aligned(16)));
    f32 accel[4] __attribute__((aligned(16)));
    f32 pos[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj+0x68);
    f32 yaw, pitch, speed, angle;
    s32 i, a, b, c;
    u8 *part;
    u8 *position;
    f32 *dest;
    vel[3]=g_debris_vel_w;
    accel[3]=g_debris_accel_w;
    yaw=mat_fast_helper_a(*(f32 *)state,*(f32 *)(state+4));
    pitch=-mat_fast_helper_a(vec_length_xy(state),*(f32 *)(state+8));
    for(i=0;i<g_debris_count_a;i++) {
        dest=pos;
        position=obj+0x10;
        {
            qcopy(dest,position);
        }
        pos[0]+=math_random_float_range(-0.065f,0.065f);
        pos[1]+=math_random_float_range(-0.065f,0.065f);
        pos[2]+=math_random_float_range(-0.065f,0.065f);
        vec_build_spherical_offset(vel,g_debris_burst_speed*0.020000001f,yaw,pitch);
        vel[2]=math_random_float_range(g_debris_rise_speed*0.018000001f,g_debris_rise_speed*0.022000001f);
        angle=math_random_float_range(-g_debris_angle_spread,g_debris_angle_spread)*0.01745329424738884f;
        speed=g_debris_speed_a;
        speed*=0.020000001f;
        angle=FastAddRotations(yaw,angle);
        vec_build_spherical_offset(accel,speed,angle,pitch);
        a=FloatToInt((math_random_float_range(g_debris_color_a_base,g_debris_color_a_base*2)*5.0f+2.0f)*0.16666667f);
        b=FloatToInt((math_random_float_range(g_debris_color_b_base,g_debris_color_b_base*1.2f)*5.0f+2.0f)*0.16666667f);
        c=FloatToInt((math_random_float_range(g_debris_color_c_base,g_debris_color_c_base*1.2f)*5.0f+2.0f)*0.16666667f);
        part=part_spawn_trail(pos,vel,accel,g_debris_sprite_a,g_debris_sprite_b,a,b,c,-1);
        if(part && (func_001163B0()&1)) part[3]=0x48;
    }
    vel[3]=g_debris_second_vel_w;
    accel[3]=g_debris_second_accel_w;
    for(i=0;i<g_debris_count_b;i++) {
        qcopy(pos,obj+0x10);
        pos[0]+=math_random_float_range(-0.2f,0.2f);
        pos[1]+=math_random_float_range(-0.2f,0.2f);
        pos[2]+=math_random_float_range(-0.2f,0.2f);
        angle=math_random_float_range(-g_debris_second_angle_spread_b,g_debris_second_angle_spread_b)*0.01745329424738884f;
        speed=g_debris_second_speed_a;
        speed*=0.020000001f;
        angle=FastAddRotations(yaw,angle);
        vec_build_spherical_offset(vel,speed,angle,pitch);
        angle=math_random_float_range(-g_debris_second_angle_spread_a,g_debris_second_angle_spread_a)*0.01745329424738884f;
        speed=g_debris_second_speed_b;
        speed*=0.020000001f;
        angle=FastAddRotations(yaw,angle);
        vec_build_spherical_offset(accel,speed,angle,pitch);
        a=FloatToInt((math_random_float_range(g_debris_second_color_a_base,g_debris_second_color_a_base*2)*5.0f+2.0f)*0.16666667f);
        b=FloatToInt((math_random_float_range(g_debris_second_color_b_base,g_debris_second_color_b_base*1.2f)*5.0f+2.0f)*0.16666667f);
        c=FloatToInt((math_random_float_range(g_debris_second_color_c_base,g_debris_second_color_c_base*1.2f)*5.0f+2.0f)*0.16666667f);
        part=part_spawn_trail(pos,vel,accel,g_debris_second_sprite_a,g_debris_second_sprite_b,a,b,c,-1);
        if(part && (func_001163B0()&1)) part[3]=0x48;
    }
}
