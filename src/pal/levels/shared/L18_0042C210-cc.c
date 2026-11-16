#include "names.h"
/* func_PAL_L18_0042C210, the PAL copy of func_L18_00427688: the same C, where rename func_L18_00426F78 becomes func_PAL_L18_0042BAE0; rename func_L18_00426F28 becomes func_PAL_L18_0042BA90. */
#include "common.h"
typedef struct { float f0,f4,f8,fC,f10,f14,f18; } MotionDefaults;
extern MotionDefaults g_shooter_motion_defaults __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern unsigned char g_moby_group_flags[];
extern unsigned char g_trigger_l18_flags[][0x464];
extern float math_random_float_range(float,float);
extern void moby_set_controller_speed_limits(unsigned char *,float,float,float,float);
extern int math_random_int_range(int,int);
extern float path_get_entry_length(int);
extern int moby_set_anim(unsigned char *,int,int);
extern void moby_rebuild_scale_matrix_pal(unsigned char *);
extern void moby_release_shared_resource(unsigned char *);
extern int func_001163B0(void);
extern void moby_start_or_forward_anim_pal(unsigned char *,int,int,float);
extern void moby_set_state(unsigned char *,int,int);
int func_PAL_L18_0042C210(unsigned char *object)
{
    unsigned char *state;
    float randomAngle;
    unsigned int ownerClass;
    if(object[0xb0]!=0xff) {
        if((g_moby_group_flags[object[0xb0]+g_current_map_index*16]&0x80)!=0) {
            if(g_trigger_l18_flags[1][*(short *)(object+0xb2)]!=0) return 1;
        }
    }
    state=*(unsigned char **)(object+0x68);
    ownerClass=object[0x30];
    *(int *)(state+0x98)=9;
    state[0x61]=7; state[0x62]=8;
    *(unsigned char *)(state+0x67)=0xff;
    *(float *)(state+0x80)=0.4f;
    *(float *)(state+0x84)=0.4f;
    *(float *)(state+0x74)=0.006f;
    state[0xbe]=5; state[0xbf]=11; state[0x2e]=1;
    state[0x60]=10;
    *(float *)(state+0x6c)=0.22000001f;
    *(float *)(state+0x70)=0.10000001f;
    *(float *)(state+0x78)=0.012f;
    *(float *)(state+0x8c)=0.4f;
    *(unsigned int *)(state+0x3e0)=ownerClass;
    state[0xbd]=6;
    state[0x66]=8; state[0x65]=9;
    *(float *)(state+0x7c)=0.006f;
    state[0xbc]=3; state[0xc2]=5; state[0xc3]=11;
    state[0x28]=1;
    *(float *)(state+0x30)=0.75f;
    *(unsigned char *)(state+0x2f)=0xff;
    state[0x2a]=4; state[0x4a]=7;
    *(float *)(state+0x100)=0.7f;
    state[0x4d]=0;
    *(float *)(state+0x104)=0.5f;
    *(float *)(state+0x108)=0.5f;
    *(float *)(state+0x10c)=0.5f;
    *(float *)(state+0x110)=1.22173059f;
    randomAngle=math_random_float_range(20.0f,25.0f);
    { float speed=g_shooter_motion_defaults.f18;
    *(float *)(state+0x134)=0.5f;
    state[0x1e8]=0; state[0x1e9]=0;
    *(float *)(state+0x130)=randomAngle*0.017453294f;
    *(float *)(state+0x12c)=speed*0.00040000002f; }
    if(*(short *)(object+0xaa)==0xed4) *(float *)(state+0x100)=1.0f;
    if(*(short *)(object+0xaa)==0xee1) *(float *)(state+0x100)=1.1f;
    if(*(float *)(state+0x3c4)==0.0f && *(float *)(state+0x3c0)==0.0f && *(float *)(state+0x3cc)==0.0f && *(float *)(state+0x3c8)==0.0f) {
        float a=g_shooter_motion_defaults.f0,b=g_shooter_motion_defaults.f4;
        float c=g_shooter_motion_defaults.f8,d=g_shooter_motion_defaults.fC;
        float e=g_shooter_motion_defaults.f10,f=g_shooter_motion_defaults.f14;
        *(float *)(state+0x3c4)=a;
        *(float *)(state+0x3c0)=b;
        *(float *)(state+0x3cc)=c;
        *(float *)(state+0x3c8)=d;
        *(float *)(state+0x3d4)=e;
        *(float *)(state+0x3d0)=f;
        *(float *)(state+0x3dc)=e;
        *(float *)(state+0x3d8)=f;
    }
    moby_set_controller_speed_limits(object,*(float *)(state+0x3c4)*0.00040000002f,*(float *)(state+0x3c0)*0.020000001f,*(float *)(state+0x3d4)*6.981318e-06f,*(float *)(state+0x3d0)*0.0003490659f);
    randomAngle=math_random_float_range(20.0f,40.0f);
    *(short *)(state+0x1e4)=120; *(short *)(state+0x1e2)=180;
    *(float *)(state+0x1dc)=randomAngle*0.017453294f;
    {
        void *initialPosition=state+0x1f0;
        void *position=object+0x10;
        qcopy(initialPosition,position);
    }
    *(float *)(state+0x200)=*(float *)(state+0x100);
    *(float *)(state+0x20c)=5.0f;
    *(float *)(state+0x210)=5.0f;
    *(int *)(state+0x37c)=*(int *)(state+0x360);
    *(short *)(state+0x392)=math_random_int_range(0,45);
    path_get_entry_length(*(int *)(state+0x368));
    path_get_entry_length(*(int *)(state+0x13c));
    path_get_entry_length(*(int *)(state+0xcc));
    path_get_entry_length(*(int *)(state+0x380));
    path_get_entry_length(*(int *)(state+0x384));
    *(int *)(state+0x13c)=*(int *)(state+0x380);
    moby_set_anim(object,*(int *)(state+0x36c),-1);
    if(state[0x399]!=0) state[0x399]=1;
    moby_rebuild_scale_matrix_pal(object);
    moby_release_shared_resource(object);
    switch(*(short *)(object+0xaa)) {
    case 0xec0: state[0x39b]=0; *(int *)(state+0x1c)=0; break;
    case 0xed4:
    case 0xee1: state[0x39b]=2; break;
    }
    moby_start_or_forward_anim_pal(object,func_001163B0()&1,0,1.0f);
    if(state[0x3e8]!=0) {
        moby_set_state(object,0,1);
        *(int *)(object+0x48)=0;
    } else if(state[0x39c]!=0) {
        object[0x31]=0;
        *(unsigned short *)(object+0x34)|=1;
        moby_set_state(object,0,2);
    } else moby_set_state(object,2,2);
    return 0;
}
