#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void FastVecScale(void *,void *,float);
extern void moby_mark_spawned(void *);
extern char *part_spawn_object_following_effect(void *,void *,unsigned int,int,int,int,int,int,float,float);
extern void moby_set_state(unsigned char *,int,int);
extern void *part_find_owned_effect_slot(void *,unsigned int,int);
extern void part_explode_object_into_pieces_pal(void *,void *,void *,void *,int,int,int,int,int,unsigned char,int);
extern void vec_local_offset_to_world(char *,char *,float,float,float);
extern void func_PAL_L00_002ED7E8(void *,void *,void *,int,int,float,float,float,float,float);
extern Vector4 g_lamp_piece_vectors[2] __attribute__((sda));
extern float g_lamp_piece_params_b[2] __attribute__((sda));
extern float g_lamp_piece_params_c[2] __attribute__((sda));
extern int g_lamp_piece_color __attribute__((sda));

void lamp_update_pal(unsigned char *object)
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
        part_explode_object_into_pieces_pal(object,g_lamp_piece_vectors,g_lamp_piece_params_b,g_lamp_piece_params_c,65535,0,g_lamp_piece_color,0,65535,255,0);
        zero.bits=0; vec_local_offset_to_world((char *)object,(char *)&zero,velocity.f[0],velocity.f[1],velocity.f[2]);
        acceleration.bits=0; acceleration.f[2]=-0.10000001f;
        func_PAL_L00_002ED7E8(object,&velocity,&acceleration,40,0,FIELD(float,object,0x2C)+FIELD(float,object,0x2C),0.24000001f,1,5,1);
        moby_mark_spawned(object); break;
    }
}
