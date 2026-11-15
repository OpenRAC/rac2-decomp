#include "common.h"
typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char g_hero_state[];
#define H ((Hero *)D_00189E20)
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 position,angles,delta,step; } RotatingMoverWorkspace;
extern char *D_L16_001B2B1C MACRO_ADDR;
extern char g_sound_state[];
extern float fast_subtract_rotations(float,float);
extern float FastAddRotations(float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int PlayMobySound(int,int,char *);
extern void FastVecSub(void *,void *,void *);
extern void mat_combine_and_store(void *,void *,void *,void *);
/* Moves and turns a platform when its switch is on, and carries a linked object along with it. */
void rotating_platform_update(char *object)
{
    RotatingMoverWorkspace local;
    char *state=*(char **)(object+0x68);
    char *target;
    char *sound;
    qcopy(&local.position,(object+0x10));
    qcopy(&local.angles,(object+0xf0));
    if(*(unsigned char *)(object+0x20)==0) {
        *(unsigned char *)(object+0x30)=0xff;
        object[0x20]=1;
        *(int *)(state+0x70)=-1;
        if(*(short *)(object+0xaa)==0x10fc) {
            *(int *)(object+0x98)=0;
            *(unsigned short *)(object+0x34)=(*(unsigned short *)(object+0x34)|0x41)&0xefff;
        }
    }
    if(*(unsigned char *)(object+0x20)==1 && *(unsigned char *)(D_L16_001B2B1C+(*(int *)(state+0x6c)<<8)+0x20)==2) object[0x20]=2;
    if(*(unsigned char *)(object+0x20)==2) {
        if(*(int *)(state+0x68)==0) {
            if(*(short *)(object+0xaa)==0x10fe) {
                *(float *)(object+0xf8)=fast_subtract_rotations(*(float *)(object+0xf8),0.0045378562063f);
                vec_scale_to_length(&local.step,object+0xc0,0.05333333835f);
                FastVecAdd(object+0x10,&local.step,object+0x10);
            }
            if(*(short *)(object+0xaa)==0x10fd) {
                *(float *)(object+0xf8)=fast_subtract_rotations(*(float *)(object+0xf8),0.00450294977f);
                vec_scale_to_length(&local.step,object+0xc0,0.03333333507f);
                FastVecAdd(object+0x10,&local.step,object+0x10);
            }
            if(*(short *)(object+0xaa)==0x10fc) {
                *(float *)(object+0xf8)=fast_subtract_rotations(*(float *)(object+0xf8),0.0045378562063f);
                vec_scale_to_length(&local.step,object+0xc0,0.04333333299f);
                FastVecAdd(object+0x10,&local.step,object+0x10);
                FastVecAdd(D_L16_001B2B1C+*(int *)(state+0x6c)*0x100+0x10,&local.step,D_L16_001B2B1C+*(int *)(state+0x6c)*0x100+0x10);
                sound=g_sound_state+0x70**(int *)(state+0x70);
                if((*(char **)(sound+0x88))!=object || (*(unsigned char *)(sound+0x74))==0) *(int *)(state+0x70)=PlayMobySound(0,4,object);
            }
        } else {
            if(*(short *)(object+0xaa)==0x10fe) {
                *(float *)(object+0xf8)=FastAddRotations(*(float *)(object+0xf8),0.0045378562063f);
                vec_scale_to_length(&local.step,object+0xc0,-1.0f);
                vec_scale_to_length(&local.step,&local.step,0.05333333835f);
                FastVecAdd(object+0x10,&local.step,object+0x10);
            }
            if(*(short *)(object+0xaa)==0x10fd) {
                *(float *)(object+0xf8)=FastAddRotations(*(float *)(object+0xf8),0.0045378562063f);
                vec_scale_to_length(&local.step,object+0xc0,-1.0f);
                vec_scale_to_length(&local.step,&local.step,0.03333333507f);
                FastVecAdd(object+0x10,&local.step,object+0x10);
            }
            if(*(short *)(object+0xaa)==0x10fc) {
                *(float *)(object+0xf8)=FastAddRotations(*(float *)(object+0xf8),0.0045378562063f);
                vec_scale_to_length(&local.step,object+0xc0,-1.0f);
                vec_scale_to_length(&local.step,&local.step,0.04333333299f);
                FastVecAdd(object+0x10,&local.step,object+0x10);
                FastVecAdd(D_L16_001B2B1C+*(int *)(state+0x6c)*0x100+0x10,&local.step,D_L16_001B2B1C+*(int *)(state+0x6c)*0x100+0x10);
            }
        }
    }
    FastVecSub(&local.delta,object+0x10,&local.position);
    mat_combine_and_store(state+0x20,&local.delta,&local.angles,object+0xf0);
}
