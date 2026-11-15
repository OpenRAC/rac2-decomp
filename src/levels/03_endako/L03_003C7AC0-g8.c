#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float D_L03_001B01BC __attribute__((sda)),D_L03_001B01A4 __attribute__((sda)),D_L03_001B01B4 __attribute__((sda)),D_L03_001B01AC __attribute__((sda));
extern float D_L03_001B01A8 __attribute__((sda)),D_L03_001B01B8 __attribute__((sda)),D_L03_001B01B0 __attribute__((sda));
extern u8 D_L03_001B01D4 __attribute__((sda));
extern float D_L03_001B9998 NOT_SDA, D_L03_001BFDE8 NOT_SDA;
typedef struct { float vec[4]; char pad[0x2d4]; int mode; } PlayerState;
extern PlayerState D_0018BDD0;
typedef struct { char pad[0x74]; u8 active; char pad75[0x13]; char *owner; } L03ControlEntry;
extern u8 g_sound_state[];
extern float FastAddRotations(float,float);
extern void euler_rotation_basis(void *,void *);
extern float FastVecLength(void *);
extern int PlayMobySound(int,int,void *);
extern void snd_stop_voice(int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void vec_clear_128(void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_clamp_length(void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void path_push_point_away(int,void *,void *,float);
extern void moby_transform_joint_to_world(void *,int,void *);
extern int CollLine(void *,void *,int,void *,int);
extern void moby_update_ground_check(void *);
/* Moves the held platform for one frame: reads the player input, pushes the platform around and checks the ground below it. */
void held_platform_move_by_input(char *moby)
{
    float a[4],b[4],c[4];
    union { float m[12]; struct { float pad[4], d[4]; } v; } scratch;
    char *vars=*(char **)(moby+0x68);
    char *heldMoby;
    int slot;
    if(*(u8 *)(moby+0x20)==2) {
        *(TI128 *)c=0;
        c[2]=FastAddRotations(D_L03_001B9998,D_L03_001B01BC*0.017453294f);
        *(TI128 *)(b)=*(TI128 *)(c);
        euler_rotation_basis(scratch.m,b);
        qcopy(a,D_0018BDD0.vec);
        if(FastVecLength(a)>0.0f && D_0018BDD0.mode==0x31) {
            L03ControlEntry *controlEntry=(L03ControlEntry *)(g_sound_state+*(int *)(vars+0x108)*0x70);
            if(controlEntry->owner!=moby || !controlEntry->active)
                *(int *)(vars+0x108)=PlayMobySound(0,4,moby);
        } else {
            slot=*(int *)(vars+0x108);
            if(slot!=-1) {
                L03ControlEntry *controlEntry=(L03ControlEntry *)(g_sound_state+slot*0x70);
                if(controlEntry->owner==moby && controlEntry->active) snd_stop_voice(slot);
            }
            *(int *)(vars+0x108)=-1;
        }
        a[0]=-a[0];
        matrix_mul_vec3(a,a,scratch.m);
        heldMoby=*(char **)(vars+0xf0);
        if(heldMoby) {
            if(*(short *)(heldMoby+0xaa)==0xb85 /* moby class 2949 */) FastVecScale(a,a,D_L03_001B01AC*(1.0f/60.0f));
            else FastVecScale(a,a,D_L03_001B01B4*(1.0f/60.0f));
        } else FastVecScale(a,a,D_L03_001B01A4*(1.0f/60.0f));
    } else {
        slot=*(int *)(vars+0x108);
        if(slot!=-1) {
            L03ControlEntry *controlEntry=(L03ControlEntry *)(g_sound_state+slot*0x70);
            if(controlEntry->owner==moby && controlEntry->active) snd_stop_voice(slot);
        }
        *(int *)(vars+0x108)=-1;
        vec_clear_128(a);
    }
    FastVecSub(b,a,vars+0xe0);
    b[2]=0;
    heldMoby=*(char **)(vars+0xf0);
    if(heldMoby) {
        if(*(short *)(heldMoby+0xaa)==0xb85 /* moby class 2949 */) vec_clamp_length(b,D_L03_001B01B0*0.000277777785f);
        else vec_clamp_length(b,D_L03_001B01B8*0.000277777785f);
    } else {
        vec_clamp_length(b,D_L03_001B01A8*0.000277777785f);
    }
    FastVecAdd(vars+0xe0,vars+0xe0,b);
    FastVecAdd(moby+0x10,moby+0x10,vars+0xe0);
    path_push_point_away(*(int *)vars,moby+0x10,moby+0x10,1.25f);
    moby_transform_joint_to_world(moby,2,c);
    qcopy(scratch.m,c);
    scratch.m[2]+=20.0f;
    qcopy(scratch.v.d,c);
    scratch.v.d[2]+=0.5f;
    if(CollLine(scratch.v.d,scratch.m,2,moby,0)) *(float *)(vars+0xf4)=D_L03_001BFDE8;
    moby_update_ground_check(moby);
    *(u8 *)(moby+0xbd)=D_L03_001B01D4;
}
