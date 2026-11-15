#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern float func_002A7878(float,float);
extern float func_002A7940(void);
extern void func_00282F20(void *,void *,float);
extern int func_002A7820(int,int);
extern float func_00283248(float,float);
extern float func_00282E80(void *,void *);
extern unsigned long func_0027C878(int);
extern void func_00283410(void *,void *);
extern void func_00280B90(void *,void *,int);
typedef struct { unsigned char prefix[0x140]; Vector4 position; } CameraPositionView;
/* A partial external view, not a complete camera allocation. */
extern CameraPositionView D_001B8C80;
extern void func_L00_0038AA40(char *);
/* Draws three flash sprites that face the camera at the given position. */
void func_L00_0038AAD0(void *unused,Vector4 *position)
{
    union { Quadword alignment; unsigned char bytes[144]; } packet;
    Vector4 transform[4],angles,delta;
    unsigned int color;
    float scale;
    InitDefaultBlockCopy((char *)packet.bytes);
    FIELD(unsigned long,packet.bytes,0x78)=GetEffectTextureDescriptor(44);
    FIELD(unsigned long,packet.bytes,0x80)=0xFF9000000260UL;
    FIELD(unsigned long,packet.bytes,0x88)=0x8000000048UL;
    FIELD(unsigned long,packet.bytes,0x70)=0;
    color=((unsigned int)RandomIntRange(48,64)<<24)+0x8183F;
    FIELD(unsigned int,packet.bytes,0x40)=FIELD(unsigned int,packet.bytes,0x44)=
        FIELD(unsigned int,packet.bytes,0x48)=FIELD(unsigned int,packet.bytes,0x4C)=color;
    angles.f[3]=0;
    angles.f[2]=FastMatrixHelperA(D_001B8C80.position.f[0]-position->f[0],D_001B8C80.position.f[1]-position->f[1]);
    angles.f[1]=-FastMatrixHelperA(vec_distance_xy(position,&D_001B8C80.position),D_001B8C80.position.f[2]-position->f[2]);
    angles.f[0]=RandomAngle();
    euler_to_matrix(transform,&angles);
    FastVecSub(&delta,&D_001B8C80.position,position);
    vec_scale_to_length(&delta,&delta,0.25f);
    transform[3].f[0]=position->f[0]+delta.f[0];
    transform[3].f[1]=position->f[1]+delta.f[1];
    transform[3].f[2]=position->f[2]+delta.f[2]; transform[3].f[3]=1;
    scale=RandomFloatRange(0.3f,0.4f);
    FastVecScale(packet.bytes,packet.bytes,scale);
    FastVecScale(packet.bytes+16,packet.bytes+16,scale);
    FastVecScale(packet.bytes+32,packet.bytes+32,scale);
    FastVecScale(packet.bytes+48,packet.bytes+48,scale);
    draw_world_quad(packet.bytes,transform,0);
    FastVecScale(packet.bytes,packet.bytes,0.5f);
    FastVecScale(packet.bytes+16,packet.bytes+16,0.5f);
    FastVecScale(packet.bytes+32,packet.bytes+32,0.5f);
    FastVecScale(packet.bytes+48,packet.bytes+48,0.5f);
    color=((unsigned int)RandomIntRange(64,127)<<24)+0x103080;
    FIELD(unsigned int,packet.bytes,0x40)=FIELD(unsigned int,packet.bytes,0x44)=
        FIELD(unsigned int,packet.bytes,0x48)=FIELD(unsigned int,packet.bytes,0x4C)=color;
    draw_world_quad(packet.bytes,transform,0);
    FastVecScale(packet.bytes,packet.bytes,0.5f);
    FastVecScale(packet.bytes+16,packet.bytes+16,0.5f);
    FastVecScale(packet.bytes+32,packet.bytes+32,0.5f);
    FastVecScale(packet.bytes+48,packet.bytes+48,0.5f);
    color=((unsigned int)RandomIntRange(64,127)<<24)+0x7F7F7F;
    FIELD(unsigned int,packet.bytes,0x40)=FIELD(unsigned int,packet.bytes,0x44)=
        FIELD(unsigned int,packet.bytes,0x48)=FIELD(unsigned int,packet.bytes,0x4C)=color;
    draw_world_quad(packet.bytes,transform,0);
}
