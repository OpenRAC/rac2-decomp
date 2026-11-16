#include "include_asm.h"
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));

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
extern void moby_rebuild_scale_matrix(unsigned char *);
extern void moby_release_shared_resource(unsigned char *);
extern int func_001163B0(void);
extern void moby_start_or_forward_anim(unsigned char *,int,int,float);
extern void moby_set_state(unsigned char *,int,int);
/* Sets up a new shooter enemy: speeds, turn rates, sight angles and starting state (idle, hidden or active). */
int shooter_init(unsigned char *object)
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
    *(float *)(state+0x74)=0.004166666884f;
    state[0xbe]=5; state[0xbf]=11; state[0x2e]=1;
    state[0x60]=10;
    *(float *)(state+0x6c)=0.1833333373f;
    *(float *)(state+0x70)=0.08333333582f;
    *(float *)(state+0x78)=0.008333333768f;
    *(float *)(state+0x8c)=0.4f;
    *(unsigned int *)(state+0x3e0)=ownerClass;
    state[0xbd]=6;
    state[0x66]=8; state[0x65]=9;
    *(float *)(state+0x7c)=0.004166666884f;
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
    { float turn_speed=g_shooter_motion_defaults.f18;
    *(float *)(state+0x134)=0.5f;
    state[0x1e8]=0; state[0x1e9]=0;
    *(float *)(state+0x130)=randomAngle*0.017453294f;
    *(float *)(state+0x12c)=turn_speed*0.0002777777845f; }
    if(*(short *)(object+0xaa)==0xed4 /* moby class 3796 */) *(float *)(state+0x100)=1.0f;
    if(*(short *)(object+0xaa)==MOBY_CLASS_RECEIVER_BOT) *(float *)(state+0x100)=1.1f;
    if(*(float *)(state+0x3c4)==0.0f && *(float *)(state+0x3c0)==0.0f && *(float *)(state+0x3cc)==0.0f && *(float *)(state+0x3c8)==0.0f) {
        float walk_speed=g_shooter_motion_defaults.f0,run_speed=g_shooter_motion_defaults.f4;
        float strafe_speed=g_shooter_motion_defaults.f8,back_speed=g_shooter_motion_defaults.fC;
        float turn_rate=g_shooter_motion_defaults.f10,aim_rate=g_shooter_motion_defaults.f14;
        *(float *)(state+0x3c4)=walk_speed;
        *(float *)(state+0x3c0)=run_speed;
        *(float *)(state+0x3cc)=strafe_speed;
        *(float *)(state+0x3c8)=back_speed;
        *(float *)(state+0x3d4)=turn_rate;
        *(float *)(state+0x3d0)=aim_rate;
        *(float *)(state+0x3dc)=turn_rate;
        *(float *)(state+0x3d8)=aim_rate;
    }
    moby_set_controller_speed_limits(object,*(float *)(state+0x3c4)*0.0002777777845f,*(float *)(state+0x3c0)*0.016666668f,*(float *)(state+0x3d4)*0.000004848137451f,*(float *)(state+0x3d0)*0.0002908882452f);
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
    moby_rebuild_scale_matrix(object);
    moby_release_shared_resource(object);
    switch(*(short *)(object+0xaa)) {
    case 0xec0 /* moby class 3776 */: state[0x39b]=0; *(int *)(state+0x1c)=0; break;
    case 0xed4 /* moby class 3796 */:
    case MOBY_CLASS_RECEIVER_BOT: state[0x39b]=2; break;
    }
    moby_start_or_forward_anim(object,func_001163B0()&1,0,1.0f);
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
