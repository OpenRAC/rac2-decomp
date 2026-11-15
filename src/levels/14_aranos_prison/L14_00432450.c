#include "names.h"
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union {TI128 q;float v[4];} Vector;
typedef struct {Vector corners[4];u32 colors[4];Vector uv[2];u64 state[4];} SurfacePacket;
extern void func_00283098(void *,void *,void *);
extern void func_L14_00390DF8(void *,void *,void *);
/* Retail translates the matrix along its first axis by the incoming f12 value. */
extern void func_L14_00391B58(char *,float);
extern void func_L14_00390EC0(void *,void *,float,float,float);
extern int func_002A7820(int,int);
extern float func_002A7878(float,float);
extern void func_L03_0038B390(unsigned char *,int,int,int);
extern void func_002FC560(u32,u64),func_00280B90(void *,void *,int);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
/* Draws a small textured quad at the object, picking a random texture scroll each frame. */
void func_L14_00432450(void *argument)
{
    unsigned char *object=argument;
    SurfacePacket packet;
    float matrix[16];
    Vector transformed,source;
    char *state=*(char **)(object+0x68);
    int texture;
    source.q=0;
    source.v[0]=F(state,0x10);source.v[1]=F(state,0x14);source.v[2]=F(state,0x18);source.v[3]=1.0f;
    transformed.q=source.q;
    matrix_mul_vec3(&transformed,&transformed,object+0xC0);
    BuildRotationBasisFromVectors(matrix,object+0x10,&transformed);
    AddScaledVectorToOffset((char *)matrix,F(state,0x1C));
    BuildTransformedRows(&packet,matrix,F(state,0x20),F(state,0x24),0.0f);
    switch(object[0x20]) {
    case 0:
    case 1:
    case 2:
        texture=RandomIntRange(0,1);
        InitEffectRecord_L03((unsigned char *)&packet,I(state,0x28+texture*4),2,(int)0x80808080);
        packet.uv[0].v[0]=RandomFloatRange(0.0f,1.0f-F(state,8));
        packet.uv[0].v[1]=RandomFloatRange(0.0f,1.0f-F(state,8));
        packet.uv[0].v[2]=packet.uv[0].v[0];
        packet.uv[0].v[3]=packet.uv[0].v[1]+F(state,8);
        packet.uv[1].v[0]=packet.uv[0].v[0]+F(state,8);
        packet.uv[1].v[1]=packet.uv[0].v[1];
        packet.uv[1].v[2]=packet.uv[0].v[0]+F(state,8);
        packet.uv[1].v[3]=packet.uv[0].v[1]+F(state,8);
        break;
    case 3:
        texture=(I(state,0x0C)/I(state,0x3C))%3;
        InitEffectRecord_L03((unsigned char *)&packet,I(state,0x30+texture*4),2,(int)0x80808080);
        break;
    }
    VU1_addGSregister(0x47,0x53001);
    draw_world_quad(&packet,0,0);
    VU1_addGSregister(0x47,0x5360B);
}
