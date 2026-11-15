#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void FastVecScale(void *,void *,float);
extern void moby_mark_spawned(void *);
extern unsigned char D_001B8C80[];
extern char *part_spawn_object_following_effect(void *,void *,unsigned int,int,int,int,int,int,float,float);
extern void moby_set_state(unsigned char *,int,int);
extern void *part_find_owned_effect_slot(void *,unsigned int,int);
extern void part_explode_object_into_pieces(void *,void *,void *,void *,int,int,int,int,int,unsigned char,int);
extern void vec_local_offset_to_world(char *,char *,float,float,float);
extern void part_l00_spawn_spark_burst(void *,void *,void *,int,int,float,float,float,float,float);
/* Two complete vectors supply the lower and upper component ranges. */
extern Vector4 D_L00_001AEC90[2] __attribute__((sda));
extern float D_L00_001AEC88[2] __attribute__((sda));
extern float D_L00_001AEC80[2] __attribute__((sda));
extern int D_L00_001AECB0 __attribute__((sda));
/* Updates a Lamp: when it breaks it throws out a burst of sparks and then removes itself. */
void lamp_update(unsigned char *object)
{
    Vector4 velocity,zero,acceleration;
    int *work=FIELD(int *,object,0x68);
    velocity.bits=0; velocity.f[2]=-23;
    switch(object[0x20]) {
    case 0:
        FastVecScale(&velocity,&velocity,FIELD(float,object,0x2C));
        part_spawn_object_following_effect(&velocity,object,0x32608080,-1,1,-1,0,96,FIELD(float,object,0x2C)*5250000,FIELD(float,object,0x2C)*15);
        moby_set_state(object,1,-1); break;
    case 1:
        if(part_find_owned_effect_slot(object,0x4010000,0) && !work[0])moby_set_state(object,2,-1);
        object[0xA8]=255; break;
    case 2:
        part_explode_object_into_pieces(object,D_L00_001AEC90,D_L00_001AEC88,D_L00_001AEC80,65535,0,D_L00_001AECB0,0,65535,255,0);
        zero.bits=0; vec_local_offset_to_world((char *)object,(char *)&zero,velocity.f[0],velocity.f[1],velocity.f[2]);
        acceleration.bits=0; acceleration.f[2]=-0.083333336f;
        part_l00_spawn_spark_burst(object,&velocity,&acceleration,40,0,FIELD(float,object,0x2C)+FIELD(float,object,0x2C),0.20000002f,1,5,1);
        moby_mark_spawned(object); break;
    }
}
