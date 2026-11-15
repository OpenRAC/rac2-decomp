#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern float math_random_float_range(float,float);
extern float math_random_angle(void);
extern void vec_scale_to_length(void *,void *,float);
extern int math_random_int_range(int,int);
extern float mat_fast_helper_a(float,float);
extern float vec_distance_xy(void *,void *);
extern unsigned long GetEffectTextureDescriptor(int);
extern void euler_to_matrix(void *,void *);
extern void draw_world_quad(void *,void *,int);
typedef struct { unsigned char prefix[0x140]; Vector4 position; } CameraPositionView;
/* A partial external view, not a complete camera allocation. */
extern CameraPositionView D_001B8C80;
extern void gfx_l00_init_default_block(char *);
/* Draws three flash sprites that face the camera at the given position. */
void part_l00_draw_camera_facing_flash(void *unused,Vector4 *position)
{
    union { Quadword alignment; unsigned char bytes[144]; } packet;
    Vector4 transform[4],angles,delta;
    unsigned int color;
    float scale;
    gfx_l00_init_default_block((char *)packet.bytes);
    FIELD(unsigned long,packet.bytes,0x78)=GetEffectTextureDescriptor(44);
    FIELD(unsigned long,packet.bytes,0x80)=0xFF9000000260UL;
    FIELD(unsigned long,packet.bytes,0x88)=0x8000000048UL;
    FIELD(unsigned long,packet.bytes,0x70)=0;
    color=((unsigned int)math_random_int_range(48,64)<<24)+0x8183F;
    FIELD(unsigned int,packet.bytes,0x40)=FIELD(unsigned int,packet.bytes,0x44)=
        FIELD(unsigned int,packet.bytes,0x48)=FIELD(unsigned int,packet.bytes,0x4C)=color;
    angles.f[3]=0;
    angles.f[2]=mat_fast_helper_a(D_001B8C80.position.f[0]-position->f[0],D_001B8C80.position.f[1]-position->f[1]);
    angles.f[1]=-mat_fast_helper_a(vec_distance_xy(position,&D_001B8C80.position),D_001B8C80.position.f[2]-position->f[2]);
    angles.f[0]=math_random_angle();
    euler_to_matrix(transform,&angles);
    FastVecSub(&delta,&D_001B8C80.position,position);
    vec_scale_to_length(&delta,&delta,0.25f);
    transform[3].f[0]=position->f[0]+delta.f[0];
    transform[3].f[1]=position->f[1]+delta.f[1];
    transform[3].f[2]=position->f[2]+delta.f[2]; transform[3].f[3]=1;
    scale=math_random_float_range(0.3f,0.4f);
    FastVecScale(packet.bytes,packet.bytes,scale);
    FastVecScale(packet.bytes+16,packet.bytes+16,scale);
    FastVecScale(packet.bytes+32,packet.bytes+32,scale);
    FastVecScale(packet.bytes+48,packet.bytes+48,scale);
    draw_world_quad(packet.bytes,transform,0);
    FastVecScale(packet.bytes,packet.bytes,0.5f);
    FastVecScale(packet.bytes+16,packet.bytes+16,0.5f);
    FastVecScale(packet.bytes+32,packet.bytes+32,0.5f);
    FastVecScale(packet.bytes+48,packet.bytes+48,0.5f);
    color=((unsigned int)math_random_int_range(64,127)<<24)+0x103080;
    FIELD(unsigned int,packet.bytes,0x40)=FIELD(unsigned int,packet.bytes,0x44)=
        FIELD(unsigned int,packet.bytes,0x48)=FIELD(unsigned int,packet.bytes,0x4C)=color;
    draw_world_quad(packet.bytes,transform,0);
    FastVecScale(packet.bytes,packet.bytes,0.5f);
    FastVecScale(packet.bytes+16,packet.bytes+16,0.5f);
    FastVecScale(packet.bytes+32,packet.bytes+32,0.5f);
    FastVecScale(packet.bytes+48,packet.bytes+48,0.5f);
    color=((unsigned int)math_random_int_range(64,127)<<24)+0x7F7F7F;
    FIELD(unsigned int,packet.bytes,0x40)=FIELD(unsigned int,packet.bytes,0x44)=
        FIELD(unsigned int,packet.bytes,0x48)=FIELD(unsigned int,packet.bytes,0x4C)=color;
    draw_world_quad(packet.bytes,transform,0);
}
