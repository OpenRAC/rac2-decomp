#include "names.h"
/*
 * func_PAL_L01_003DC780, the PAL copy of func_L01_003D8358 (oozla, -G8
 * profile): the same C, where the frame step 1/60 becomes 1/50, the two turn
 * rates grow by 6/5 and the spring gains are scaled by 1.44 and 1.2.
 *
 * Case 0 waits for a positive height from func_PAL_L01_003BEB40, then either
 * picks two random angles and moves to case 1 (linked object at s+0x8C) or calls func_0026FEB8 and
 * moves to case 2. Case 1 falls to case 2 once the linked object is gone or
 * in state 0xFE/0xFD. In case 2, when hero mode (0x34E) is 0 and hero+0x33C
 * points at this object, two func_002AA898 springs are driven by dot
 * products of the hero offset and the hero is moved by the resulting change;
 * otherwise the height eases towards s+0x84, the springs relax and a
 * one-shot func_002E5CF8 fires when the threshold is crossed.
 *
 * Shape notes: height stays distinct from the first dot product. The scale
 * constant is its own variable (k), read once for -k*y and k*x; reusing one
 * variable for the constant and the product made sched2 issue the zero
 * direction argument before k*x. speed*step is added to the height as one
 * product so the multiply keeps retail's operand order.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
typedef struct { u8 pad[0x34E]; s16 mode; } Hero;
extern Hero g_hero_state NOT_SDA;
extern u8 *g_moby_l01_table;
extern u8 g_str_water_raft_debug[];
extern f32 g_raft_water_splash_margin __attribute__((sda));
extern f32 g_raft_tilt_scale __attribute__((sda));
extern f32 g_raft_speed __attribute__((sda));
extern f32 g_raft_tilt_approach_accel __attribute__((sda));
extern f32 g_raft_tilt_approach_max_speed __attribute__((sda));
extern f32 g_raft_tilt_approach_damping __attribute__((sda));
extern f32 g_raft_level_approach_accel __attribute__((sda));
extern f32 g_raft_level_approach_max_speed __attribute__((sda));
extern f32 g_raft_level_approach_damping __attribute__((sda));
extern void FastVecScale(void *,void *,f32);
extern f32 func_PAL_L01_003BEB40(void);
extern f32 math_random_float_range(f32,f32);
extern void STUB_printf(void *,s32,s32);
extern void FastVecSub(void *,void *,void *);
extern f32 FastVecDot(void *,void *);
extern f32 math_approach_with_velocity(void *,f32,void *,f32,f32,f32,s32);
extern void mat_transform_offset_two_matrices(void *,void *,void *,void *,void *);
extern s32 PlayMobySound(s32,s32,void *);
extern void moby_scale_owner_words_by_angles(void *,void *,void *,f32,f32,f32);
extern f32 FastAddRotations(f32,f32);
extern void FastVecAdd(void *,void *,void *);
extern void mat_combine_and_store(void *,void *,void *,void *);
void func_PAL_L01_003DC780(u8 *m)
{
    f32 delta[4] __attribute__((aligned(16)));
    f32 rotation[4] __attribute__((aligned(16)));
    f32 relative[4] __attribute__((aligned(16)));
    f32 oldAngle[4] __attribute__((aligned(16)));
    f32 oldPos[4] __attribute__((aligned(16)));
    f32 move[4] __attribute__((aligned(16)));
    u8 *s = *(u8 **)(m+0x68);
    f32 k, height, previous, x, y, pitch, scale, speed, step;
    u8 *other;
    FastVecScale(delta,m+0x10,-1.0f);
    qcopy(rotation,m+0xF0);
    previous=F(m,0x18);
    height=func_PAL_L01_003BEB40();
    F(s,0x84)=height+0.2f;
    switch(m[0x20]) {
    case 0:
        if(height>0.0f) {
            I(s,0x80)=1;
            qcopy(s+0x60,m+0xF0);
            qzero_nc(s+0x70);
            if(I(s,0x8C)!=-1) {
                F(m,0x18)=F(s,0x84)-5.0f;
                F(m,0xF0)=math_random_float_range(-1.57079637f,1.57079637f);
                F(m,0xF4)=math_random_float_range(-1.57079637f,1.57079637f);
                m[0x20]=1;
            } else {
                STUB_printf(g_str_water_raft_debug,H(m,0xB2),H(m,0xAA));
                m[0x20]=2;
            }
        }
        break;
    case 1:
        other=g_moby_l01_table+(I(s,0x8C)<<8);
        if(!other || other[0x20]==0xFE || other[0x20]==0xFD) m[0x20]=2;
        break;
    case 2:
        if(g_hero_state.mode==0 && *(u8 **)(((u8 *)&g_hero_state)+0x33C)==m) {
            FastVecSub(relative,((u8 *)&g_hero_state)+0x80,m+0x10);
            x=FastVecDot(relative,m+0xC0);
            y=FastVecDot(relative,m+0xD0);
            k=g_raft_tilt_scale;
            pitch=-k*y;
            *(Quad *)oldAngle=*(Quad *)(s+0x60);
            *(Quad *)oldPos=*(Quad *)(m+0x10);
            scale=k*x;
            math_approach_with_velocity(s+0x60,pitch,s+0x70,g_raft_tilt_approach_accel*1.44f,g_raft_tilt_approach_max_speed*1.44f,g_raft_tilt_approach_damping*1.2f,0);
            math_approach_with_velocity(s+0x64,scale,s+0x74,g_raft_tilt_approach_accel*1.44f,g_raft_tilt_approach_max_speed*1.44f,g_raft_tilt_approach_damping*1.2f,0);
            mat_transform_offset_two_matrices(((u8 *)&g_hero_state)+0x80,move,m+0x10,oldAngle,s+0x60);
            FastVecSub(((u8 *)&g_hero_state)+0x100,move,((u8 *)&g_hero_state)+0x80);
            F(((u8 *)&g_hero_state),0x108)+=F(m,0x18)-oldPos[2];
        } else {
            speed=g_raft_speed;
            step=(F(s,0x84)-F(m,0x18))*0.020000001f;
            F(m,0x18)=F(m,0x18)+speed*step;
            if(F(m,0x18)<F(s,0x84)-2.0f) F(m,0x18)+=speed*0.020000001f;
            else {
                math_approach_with_velocity(s+0x60,0.0f,s+0x70,g_raft_level_approach_accel*1.44f,g_raft_level_approach_max_speed*1.44f,g_raft_level_approach_damping*1.2f,0);
                math_approach_with_velocity(s+0x64,0.0f,s+0x74,g_raft_level_approach_accel*1.44f,g_raft_level_approach_max_speed*1.44f,g_raft_level_approach_damping*1.2f,0);
            }
            if(F(m,0x18)>F(s,0x84)) F(m,0x18)=F(s,0x84);
            if(previous<height-g_raft_water_splash_margin && F(m,0x18)>=height-g_raft_water_splash_margin && !I(s,0xA0)) {
                PlayMobySound(0,0,m);
                I(s,0xA0)=1;
            }
        }
        moby_scale_owner_words_by_angles(m,s+0x90,s+0x94,0.0200712885708f,0.008726647f,0.010821043f);
        F(m,0xF0)=FastAddRotations(F(s,0x60),F(m,0xF0));
        F(m,0xF4)=FastAddRotations(F(s,0x64),F(m,0xF4));
        FastVecAdd(delta,delta,m+0x10);
        mat_combine_and_store(s+0x20,delta,rotation,m+0xF0);
        break;
    }
}
