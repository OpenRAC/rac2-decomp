#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern float D_L17_001B0CA8 __attribute__((sda));
typedef struct { char pad[0x18]; void *object; } Contact;
extern Contact D_L17_001C0000;
extern char D_L17_001C0040[];
extern float mat_fast_helper_a(float,float), FastAddRotations(float,float);
extern int FloatToInt(float), moby_get_private_value_2(void *);
extern void MobySpringTurn(void *,void *,float,float,float,float), coll_probe_ahead_of_moby(void *,void *), path_push_point_away(int,void *,void *,float);
extern float coll_probe_ground_height_below(void *,int,float);
extern void moby_transform_point_and_rotation_by_parent(void *,void *,void *,void *,void *,void *), mat_build_axis_angle_rotation(void *,void *,float);

/* Turns the creature toward its target and lets gravity pull it down onto the ground (or
   onto a moving object it lands on). */
void grulch_turn_and_fall(char *obj) {
    float tmp[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    char *state=*(char **)(obj+0x68);
    char *target;
    float ground, angle, frame;
    int frames;
    if(B(obj,0x20)==4 && B(obj,0x42)==9) {
        target=*(char **)(state+0x408);
        angle=mat_fast_helper_a(F(target,0x10)-F(obj,0x10),F(target,0x14)-F(obj,0x14));
        angle=FastAddRotations(angle,F(state,0x414));
        MobySpringTurn(obj,state+0x410,angle,0.05f,0.3f,0.10471977f);
        frames=FloatToInt(D_L17_001B0CA8*1024.0f);
        frame=D_L17_001B0CA8;
        I(state,0x140)=frames;
        F(state,0x144)=frame;
        coll_probe_ahead_of_moby(obj,state+0x140);
        if(I(state,0x444)!=-1) path_push_point_away(I(state,0x444),obj+0x10,obj+0x10,D_L17_001B0CA8);
    } else if(B(obj,0x20)==5) {
        target=*(char **)(state+0x408);
        angle=mat_fast_helper_a(F(target,0x10)-F(obj,0x10),F(target,0x14)-F(obj,0x14));
        angle=FastAddRotations(angle,F(state,0x414));
        MobySpringTurn(obj,state+0x410,angle,0.05f,0.3f,0.10471977f);
    }
    if(I(state,0x420)) {
        *(Quad *)tmp=0;
        moby_transform_point_and_rotation_by_parent(obj,*(void **)(state+0x420),obj+0x10,obj+0xf0,obj+0x10,tmp);
        F(obj,0xf8)=tmp[2];
    }
    F(state,0x424)+=0.0055555557f;
    F(obj,0x18)-=F(state,0x424)-2.0f;
    ground=coll_probe_ground_height_below(obj+0x10,0,0.5f);
    F(obj,0x18)-=2.0f;
    if(F(obj,0x18)<ground) {
        if(D_L17_001C0000.object && moby_get_private_value_2(D_L17_001C0000.object)) I(state,0x420)=(int)D_L17_001C0000.object;
        else if(I(state,0x420)) I(state,0x420)=0;
        F(obj,0x18)=ground; F(state,0x424)=0;
        if(I(state,0x420)) {
            *(Quad *)rot=*(Quad *)(obj+0xf0); *(Quad *)tmp=*(Quad *)(D_L17_001C0040);
            mat_build_axis_angle_rotation(tmp,rot,F(obj,0xf8));
        }
    }
}
