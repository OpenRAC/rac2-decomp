#include "names.h"
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct { float vertex[4][4]; u32 color[4]; float uv[8]; u64 reserved,texture,setup,state; } QuadPacket;
extern void ref_L02_00422BB8_00(char *);
extern u64 GetEffectTextureDescriptor(int);
extern int math_random_int_range(int,int);
extern float mat_fast_helper_a(float,float);
extern float vec_distance_xy(void *,void *);
extern float math_random_angle(void);
extern void euler_to_matrix(void *,void *);
extern float math_random_float_range(float,float);
extern void FastVecScale(void *,void *,float);
extern void draw_world_quad(void *,void *,int);
/* Observed target prefix: retail addresses its position at base + 0x140. */
typedef struct { u8 reserved[0x140]; float position[4]; } FlareTargetView;
extern FlareTargetView D_L02_001BA3C0 __attribute__((nosda));
extern u32 D_L02_001B1FDC __attribute__((sda));

/* Submit one billboarding flare at the object's current endpoint. */
void gfx_draw_beam_end_flare(u8 *object)
{
    QuadPacket packet;
    float transform[16];
    float rotation[4];
    u8 *state=*(u8 **)(object+0x68);
    float size;
    u32 color;
    ref_L02_00422BB8_00((char *)&packet);
    packet.texture=GetEffectTextureDescriptor(11);
    packet.setup=0xFF9000000260ULL;
    packet.state=0x8000000048ULL;
    packet.reserved=0;
    color=(D_L02_001B1FDC&0xFFFFFF)+(math_random_int_range(32,48)<<24);
    packet.color[3]=color; packet.color[2]=color; packet.color[1]=color; packet.color[0]=color;
    rotation[3]=0;
    rotation[2]=mat_fast_helper_a(D_L02_001BA3C0.position[0]-*(float *)(object+0x10),D_L02_001BA3C0.position[1]-*(float *)(object+0x14));
    rotation[1]=-mat_fast_helper_a(vec_distance_xy(object+0x10,D_L02_001BA3C0.position),D_L02_001BA3C0.position[2]-*(float *)(object+0x18));
    rotation[0]=math_random_angle();
    euler_to_matrix(transform,rotation);
    transform[12]=*(float *)(object+0x10); transform[13]=*(float *)(object+0x14); transform[14]=*(float *)(object+0x18); transform[15]=1;
    size=math_random_float_range(0.35f,0.45f)**(float *)(state+0x60);
    FastVecScale(packet.vertex[0],packet.vertex[0],size);
    FastVecScale(packet.vertex[1],packet.vertex[1],size);
    FastVecScale(packet.vertex[2],packet.vertex[2],size);
    FastVecScale(packet.vertex[3],packet.vertex[3],size);
    draw_world_quad(&packet,transform,0);
}
