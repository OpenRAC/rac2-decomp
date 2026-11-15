#include "include_asm.h"

#include "common.h"
extern void level_apply_colour_tint(char *);
extern void moby_copy_color(char *, char *);
extern void func_PAL_L09_003FC118(char *);
extern void moby_transform_joint_to_world(char *, int, void *);
extern void math_approach_target_with_direction_mode(void *, void *, int, float, float,float, float);
extern void FastVecSub(void *, void *,void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern void moby_update_eased_node(char *,void *, int, float, float);
extern float math_random_float_range(float, float);
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define B(p, o) (*(unsigned char *)((p) + (o)))
#define P(p, o) (*(char **)((p) + (o)))

void func_PAL_L09_003FDB18(char *object)
{
    char *data=P(object,0x68);

    float v[4] __attribute__((aligned(16)));
    int i;
    float angle;
    level_apply_colour_tint(object);
    {
        char *partner = P(data, 0x2F8);
        if (!partner || *(short *)(partner + 0xAA) != 0xD0E ||
            B(partner, 0x20) == 254 || B(partner, 0x20) == 253)
            return;
        moby_copy_color(object, partner);
    }
    level_apply_colour_tint(P(data,0x2F8));
    moby_transform_joint_to_world(object,0,P(data,0x2F8)+0x10);
    math_approach_target_with_direction_mode(P(data,0x2F8)+0xF8,data+0x2FC,0,F(data,0x2EC),F(data,0x114),F(data,0x118),F(data,0x11C));
    F(P(data,0x2F8),0x48)=F(object,0x48);
    if ((unsigned)(B(object,0x20)-1)<3 || B(object,0x20)==16) func_PAL_L09_003FC118(object);
    if (I(data,0x204)==1 && !B(data,0x30F)) {
        moby_transform_joint_to_world(P(data,0x2F8),4,v);
        FastVecSub(v,data+0x1F0,v);
        angle=vec_length_xy(v);
        angle=-mat_fast_helper_a(angle,v[2]);
        F(data,0x274)=fast_subtract_rotations(angle,F(P(data,0x2F8),0xF4));
        angle=mat_fast_helper_a(v[0],v[1]);
        F(data,0x278)=fast_subtract_rotations(angle,F(P(data,0x2F8),0xF8));
    }
    moby_update_eased_node(P(data,0x2F8),data+0x210,3,0.028800001f,0.43200004f);
    if (!B(data,0x30F) && (unsigned)B(P(data,0x2F8),0x42)>=8 && (unsigned)B(P(data,0x2F8),0x42)<11) {
        for(i=0;i<2;i++) {
            char *part=data+i*0x80;
            if ((*(unsigned short *)(P(data,0x2F8)+0x7C)>>(i+4))&1) {
                moby_transform_joint_to_world(P(data,0x2F8),i,v);
                FastVecSub(v,data+0x1F0,v);
                angle=vec_length_xy(v);
                F(part,0x384)=-mat_fast_helper_a(angle,v[2]);
                angle=mat_fast_helper_a(v[0],v[1]);
                F(part,0x388)=fast_subtract_rotations(angle,F(P(data,0x2F8),0xF8));
                if (i) {
                    if (F(part, 0x388) > 0.087266475f)
                        F(part, 0x388) = 0.087266475f;
                } else {
                    if (F(data, 0x388) < -0.087266475f)
                        F(data, 0x388) = -0.087266475f;
                }
            }
        }
    } else if (B(data,0x30F)) {
        char *part=data;
        for(i=1;i>=0;i--,part+=0x80) {
            F(part,0x384)=math_random_float_range(-1.57079637f,1.57079637f)*0.5f;
            F(part,0x388)=math_random_float_range(-1.57079637f,1.57079637f)*0.5f;
        }
    }
    for(i=0;i<2;i++)
        moby_update_eased_node(P(data,0x2F8),data+0x320+i*0x80,i+7,0.028800001f,0.43200004f);
}
