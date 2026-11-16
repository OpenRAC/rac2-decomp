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
/* Sets up a new shooter enemy: speeds, turn rates, sight angles and starting state (idle, hidden or active) (PAL). */
int shooter_init_pal(unsigned char *moby)
{
    unsigned char *vars;
    float random_angle;
    unsigned int owner_class;
    if(moby[0xb0]!=0xff) {
        if((g_moby_group_flags[moby[0xb0]+g_current_map_index*16]&0x80)!=0) {
            if(g_trigger_l18_flags[1][*(short *)(moby+0xb2)]!=0) return 1;
        }
    }
    vars=*(unsigned char **)(moby+0x68);
    owner_class=moby[0x30];
    *(int *)(vars+0x98)=9;
    vars[0x61]=7; vars[0x62]=8;
    *(unsigned char *)(vars+0x67)=0xff;
    *(float *)(vars+0x80)=0.4f;
    *(float *)(vars+0x84)=0.4f;
    *(float *)(vars+0x74)=0.006f;
    vars[0xbe]=5; vars[0xbf]=11; vars[0x2e]=1;
    vars[0x60]=10;
    *(float *)(vars+0x6c)=0.22000001f;
    *(float *)(vars+0x70)=0.10000001f;
    *(float *)(vars+0x78)=0.012f;
    *(float *)(vars+0x8c)=0.4f;
    *(unsigned int *)(vars+0x3e0)=owner_class;
    vars[0xbd]=6;
    vars[0x66]=8; vars[0x65]=9;
    *(float *)(vars+0x7c)=0.006f;
    vars[0xbc]=3; vars[0xc2]=5; vars[0xc3]=11;
    vars[0x28]=1;
    *(float *)(vars+0x30)=0.75f;
    *(unsigned char *)(vars+0x2f)=0xff;
    vars[0x2a]=4; vars[0x4a]=7;
    *(float *)(vars+0x100)=0.7f;
    vars[0x4d]=0;
    *(float *)(vars+0x104)=0.5f;
    *(float *)(vars+0x108)=0.5f;
    *(float *)(vars+0x10c)=0.5f;
    *(float *)(vars+0x110)=1.22173059f;
    random_angle=math_random_float_range(20.0f,25.0f);
    { float speed=g_shooter_motion_defaults.f18;
    *(float *)(vars+0x134)=0.5f;
    vars[0x1e8]=0; vars[0x1e9]=0;
    *(float *)(vars+0x130)=random_angle*0.017453294f;
    *(float *)(vars+0x12c)=speed*0.00040000002f; }
    if(*(short *)(moby+0xaa)==0xed4) *(float *)(vars+0x100)=1.0f;
    if(*(short *)(moby+0xaa)==0xee1) *(float *)(vars+0x100)=1.1f;
    if(*(float *)(vars+0x3c4)==0.0f && *(float *)(vars+0x3c0)==0.0f && *(float *)(vars+0x3cc)==0.0f && *(float *)(vars+0x3c8)==0.0f) {
        float a=g_shooter_motion_defaults.f0,b=g_shooter_motion_defaults.f4;
        float c=g_shooter_motion_defaults.f8,d=g_shooter_motion_defaults.fC;
        float e=g_shooter_motion_defaults.f10,f=g_shooter_motion_defaults.f14;
        *(float *)(vars+0x3c4)=a;
        *(float *)(vars+0x3c0)=b;
        *(float *)(vars+0x3cc)=c;
        *(float *)(vars+0x3c8)=d;
        *(float *)(vars+0x3d4)=e;
        *(float *)(vars+0x3d0)=f;
        *(float *)(vars+0x3dc)=e;
        *(float *)(vars+0x3d8)=f;
    }
    moby_set_controller_speed_limits(moby,*(float *)(vars+0x3c4)*0.00040000002f,*(float *)(vars+0x3c0)*0.020000001f,*(float *)(vars+0x3d4)*6.981318e-06f,*(float *)(vars+0x3d0)*0.0003490659f);
    random_angle=math_random_float_range(20.0f,40.0f);
    *(short *)(vars+0x1e4)=120; *(short *)(vars+0x1e2)=180;
    *(float *)(vars+0x1dc)=random_angle*0.017453294f;
    {
        void *initial_position=vars+0x1f0;
        void *position=moby+0x10;
        qcopy(initial_position,position);
    }
    *(float *)(vars+0x200)=*(float *)(vars+0x100);
    *(float *)(vars+0x20c)=5.0f;
    *(float *)(vars+0x210)=5.0f;
    *(int *)(vars+0x37c)=*(int *)(vars+0x360);
    *(short *)(vars+0x392)=math_random_int_range(0,45);
    path_get_entry_length(*(int *)(vars+0x368));
    path_get_entry_length(*(int *)(vars+0x13c));
    path_get_entry_length(*(int *)(vars+0xcc));
    path_get_entry_length(*(int *)(vars+0x380));
    path_get_entry_length(*(int *)(vars+0x384));
    *(int *)(vars+0x13c)=*(int *)(vars+0x380);
    moby_set_anim(moby,*(int *)(vars+0x36c),-1);
    if(vars[0x399]!=0) vars[0x399]=1;
    moby_rebuild_scale_matrix_pal(moby);
    moby_release_shared_resource(moby);
    switch(*(short *)(moby+0xaa)) {
    case 0xec0: vars[0x39b]=0; *(int *)(vars+0x1c)=0; break;
    case 0xed4:
    case 0xee1: vars[0x39b]=2; break;
    }
    moby_start_or_forward_anim_pal(moby,func_001163B0()&1,0,1.0f);
    if(vars[0x3e8]!=0) {
        moby_set_state(moby,0,1);
        *(int *)(moby+0x48)=0;
    } else if(vars[0x39c]!=0) {
        moby[0x31]=0;
        *(unsigned short *)(moby+0x34)|=1;
        moby_set_state(moby,0,2);
    } else moby_set_state(moby,2,2);
    return 0;
}
