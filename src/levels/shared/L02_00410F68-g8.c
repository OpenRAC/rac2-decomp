#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct {
    Vector point[4];
    unsigned int color[4];
    float uv[4][2];
    u64 reserved, texture, setup, state;
} EffectPacket;
extern int ref_L02_00410F68_0 __attribute__((sda));
extern int ref_L02_00410F68_1 __attribute__((sda));
extern int ref_L02_00410F68_2 __attribute__((sda));
extern int ref_L02_00410F68_3 __attribute__((sda));
extern int ref_L02_00410F68_4 __attribute__((sda));
extern float ref_L02_00410F68_5 __attribute__((sda));
extern unsigned int ref_L02_00410F68_6[2] __attribute__((sda));
extern float ref_L02_00410F68_7[][2] SDATA(ref_L02_00410F68_7);
extern float ref_L02_00410F68_8 __attribute__((sda));
extern float ref_L02_00410F68_9 __attribute__((sda));
extern u8 g_hero_state[];
extern float ref_L02_00410F68_10[][2] MACRO_ADDR;
extern void copy_matrix_rotation(void *,void *);
extern u64 GetEffectTextureDescriptor(int);
extern void FastVecSub(void *,void *,void *);
extern void vec_clamp_length(void *,float);
extern unsigned int FastTweenColor(unsigned int,unsigned int,float);
extern void vec_store_helper(void *);
extern void euler_rotation_basis(void *,void *);
extern void gfx_transform_and_draw_entries(void *,int,void *,int,void *);

/* GS ALPHA register. */
static __inline__ u64 GsField(int value,int shift)
{
    return (u64)(long long)value<<shift;
}

static __inline__ u64 GsAlpha(int a,int b,int c,int d,int fix)
{
    u64 fixed=GsField(fix,32);
    u64 value=GsField(a,0)|GsField(b,2);
    value |= GsField(c,4);
    value |= GsField(d,6);
    value |= fixed;
    return value;
}

static __inline__ float GetFloat(u8 *base,int offset)
{
    return *(float *)(base+offset);
}

static __inline__ int GetInt(u8 *base,int offset)
{
    return *(int *)(base+offset);
}

static __inline__ u8 *GetPointer(u8 *base,int offset)
{
    return *(u8 **)(base+offset);
}

static __inline__ int EffectState(u8 *effect)
{
    return GetInt(effect,0x38);
}

static __inline__ float EffectTime(u8 *effect)
{
    return GetFloat(effect,0x34);
}

/* Assemble four animated strips in the object's coordinate frame. */
void DrawAnimatedEffectQuads(u8 *object)
{
    EffectPacket packet[4];
    Vector frame[4];
    Vector rotation[3];
    Vector angle;
    u8 *effect=GetPointer(object,0x68);
    u8 *resident;
    float alpha,spread,shrink,time;
    int k;
    copy_matrix_rotation(frame,object+0xC0);
    qcopy(&frame[3],object+0x10);
    for(k=0;k<4;k++) {
        packet[k].texture=GetEffectTextureDescriptor(ref_L02_00410F68_0);
        packet[k].setup=0xFF9000000260ULL;
        packet[k].reserved=0;
        packet[k].state=GsAlpha(ref_L02_00410F68_1,ref_L02_00410F68_2,ref_L02_00410F68_3,ref_L02_00410F68_4,0x80);
    }
    spread=0.1f;
    alpha=(1.95f-EffectTime(effect))*2.0f;
    if(alpha>1.0f) alpha=1.0f;
    else if(alpha<0.0f) alpha=0.0f;
    if(EffectTime(effect)<1.15f) {
        FastVecSub(g_hero_state+0x100,object+0x10,g_hero_state+0x80);
        resident=g_hero_state;
        *(float *)(resident+0x108)=0;
        vec_clamp_length(g_hero_state+0x100,0.016666668f);
        time=EffectTime(effect);
        shrink=1.15f-time;
        if(shrink<0) shrink=0;
        {
            float fade=(0.2f-time)*5.0f;
            if(fade<0) fade=0;
            if(EffectState(effect)<0) ref_L02_00410F68_5=fade;
        }
        spread=shrink+0.1f;
        if(time<0.65f) {
            float scale=time*1.538461566f;
            *(short *)(resident+0x2500)=1;
            *(float *)(resident+0x2024)=scale;
            *(float *)(resident+0x2020)=scale;
            *(float *)(resident+0x2028)=2.0f-scale;
        } else *(short *)(resident+0x2500)=0;
    }
    {
    unsigned int color;
    float x;
    int j,i;
    for(i=0;i<4;i++) {
        j=0;
        do {
            packet[i].uv[j][0]=ref_L02_00410F68_7[j][0];
            packet[i].uv[j][1]=ref_L02_00410F68_10[j][0];
            color=ref_L02_00410F68_6[i!=0];
            packet[i].color[j]=color;
            packet[i].color[j]=FastTweenColor(color&0xFFFFFF,color,alpha);
            vec_store_helper(&packet[i].point[j]);
            x=*(float *)(effect+0x34);
            if(i!=0) x+=0.01f;
            packet[i].point[j].f[0]=x;
            if(j&1) {
                switch(i) {
                case 0: { Vector *v=packet[0].point; float z=ref_L02_00410F68_8+spread; v[j].f[2]+=z; } break;
                case 1: { Vector *v=packet[1].point; float z=ref_L02_00410F68_8+ref_L02_00410F68_9; v[j].f[2]+=z; } break;
                case 2: { Vector *v=packet[2].point; float z=(ref_L02_00410F68_8-spread*0.8f)+ref_L02_00410F68_9; v[j].f[2]+=z; } break;
                case 3: { Vector *v=packet[3].point; float z=(ref_L02_00410F68_8+spread*0.8f)+ref_L02_00410F68_9; v[j].f[2]+=z; } break;
                }
            } else {
                switch(i) {
                case 0: { Vector *v=packet[0].point; float z=ref_L02_00410F68_8-spread; v[j].f[2]+=z; } break;
                case 1: { Vector *v=packet[1].point; float z=ref_L02_00410F68_8-ref_L02_00410F68_9; v[j].f[2]+=z; } break;
                case 2: { Vector *v=packet[2].point; float z=(ref_L02_00410F68_8-spread*0.8f)-ref_L02_00410F68_9; v[j].f[2]+=z; } break;
                case 3: { Vector *v=packet[3].point; float z=(ref_L02_00410F68_8+spread*0.8f)-ref_L02_00410F68_9; v[j].f[2]+=z; } break;
                }
            }
            j++;
        } while (j<4);
    }
    }
    angle.q=0; angle.f[2]=0.19634955f;
    euler_rotation_basis(rotation,&angle);
    gfx_transform_and_draw_entries(packet,4,rotation,32,frame);
}
