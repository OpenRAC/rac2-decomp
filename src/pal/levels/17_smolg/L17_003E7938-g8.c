#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern float g_grulch_frame_scalar __attribute__((sda));
typedef struct { char pad[0x18]; void *object; } Contact;
extern Contact g_collision_l17_result;
extern char g_rotation_template_quad[];
extern float mat_fast_helper_a(float,float), FastAddRotations(float,float);
extern int FloatToInt(float);
extern char *moby_get_private_value_2(void *);
extern void MobySpringTurn(void *,void *,float,float,float,float), coll_probe_ahead_of_moby_pal(void *,void *);
extern int path_push_point_away(int,void *,void *,float);
extern float coll_probe_ground_height_below(void *,int,float);
extern void mat_build_axis_angle_rotation(void *,void *,float);
extern int moby_transform_point_and_rotation_by_parent(void *,void *,void *,void *,void *,void *);

void func_PAL_L17_003E8D68(char *obj) {
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
        MobySpringTurn(obj,state+0x410,angle,0.05f,0.3f,0.12566373f);
        frames=FloatToInt(g_grulch_frame_scalar*1024.0f);
        frame=g_grulch_frame_scalar;
        I(state,0x140)=frames;
        F(state,0x144)=frame;
        coll_probe_ahead_of_moby_pal(obj,state+0x140);
        if(I(state,0x444)!=-1) path_push_point_away(I(state,0x444),obj+0x10,obj+0x10,g_grulch_frame_scalar);
    } else if(B(obj,0x20)==5) {
        target=*(char **)(state+0x408);
        angle=mat_fast_helper_a(F(target,0x10)-F(obj,0x10),F(target,0x14)-F(obj,0x14));
        angle=FastAddRotations(angle,F(state,0x414));
        MobySpringTurn(obj,state+0x410,angle,0.05f,0.3f,0.12566373f);
    }
    if(I(state,0x420)) {
        *(Quad *)tmp=0;
        moby_transform_point_and_rotation_by_parent(obj,*(void **)(state+0x420),obj+0x10,obj+0xf0,obj+0x10,tmp);
        F(obj,0xf8)=tmp[2];
    }
    F(state,0x424)+=0.008f;
    F(obj,0x18)-=F(state,0x424)-2.0f;
    ground=coll_probe_ground_height_below(obj+0x10,0,0.5f);
    F(obj,0x18)-=2.0f;
    if(F(obj,0x18)<ground) {
        if(g_collision_l17_result.object && moby_get_private_value_2(g_collision_l17_result.object)) I(state,0x420)=(int)g_collision_l17_result.object;
        else if(I(state,0x420)) I(state,0x420)=0;
        F(obj,0x18)=ground; F(state,0x424)=0;
        if(I(state,0x420)) {
            *(Quad *)rot=*(Quad *)(obj+0xf0); *(Quad *)tmp=*(Quad *)(g_rotation_template_quad);
            mat_build_axis_angle_rotation(tmp,rot,F(obj,0xf8));
        }
    }
}
