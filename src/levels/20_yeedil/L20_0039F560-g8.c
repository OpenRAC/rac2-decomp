/* func_L20_0039F560: draws the object's effect. It builds a basis from the object's
 * position, transforms the 290-vertex mesh into D_L20_0023D8D0 and submits it in three
 * overlapping strips, then draws 32 quads whose corners come from D_L20_0029FD60. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { Vector vertex[4]; unsigned int color[4]; float uv[8]; unsigned long long reserved,texture,state,flags; } QuadPacket;
extern int D_L20_001AED20 __attribute__((sda));
extern float D_L20_001AED24 __attribute__((sda));
extern float D_L20_001AED28 __attribute__((sda));
extern float D_L20_001AED2C __attribute__((sda));
extern int D_L20_001AED30 __attribute__((sda));
extern Vector D_L20_001B9FC0;
extern float D_L20_0023D8D0[][3];
extern Vector D_L20_0029DC20[];
extern float D_L20_0029EE40[][2];
extern Vector D_L20_0029F760[];
extern short D_L20_0029FD60[32][4];
extern unsigned long long func_0027C878(int);
extern void func_002FC560(unsigned int,unsigned long long);
extern void func_00282C98(void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern int func_00283CF0(float);
extern void func_00280328(void);
extern void func_002830C0(void *,void *,void *);
extern void func_00281810(int,void *,void *,void *,int);
extern void func_00280B90(QuadPacket *,void *,int);

void func_L20_0039F560(u8 *object)
{
    QuadPacket packet;
    Vector basis[4], up, relative, transformed;
    unsigned int colors[290];
    u8 *state=*(u8 **)(object+0x68);
    short *face;
    float wide,narrow;
    unsigned int rgba;
    int i,j;
    packet.texture=GetEffectTextureDescriptor(D_L20_001AED20);
    packet.state=0xff9000000260ULL;
    packet.flags=0x8000000044ULL;
    packet.reserved=0;
    VU1_addGSregister(0x47,0x53001);
    func_00282C98(&up);
    basis[3].q=*(Quadword *)(object+0x10);
    basis[3].f[3]=1.0f;
    FastVecSub(&relative,&D_L20_001B9FC0,&basis[3]);
    vec_scale_to_length(&basis[0],&relative,1.0f);
    FastVecCross(&basis[1],&basis[0],&up);
    vec_scale_to_length(&basis[1],&basis[1],1.0f);
    FastVecCross(&basis[2],&basis[1],&basis[0]);
    FastVecScale(&basis[0],&basis[0],D_L20_001AED24);
    FastVecScale(&basis[1],&basis[1],D_L20_001AED24);
    FastVecScale(&basis[2],&basis[2],D_L20_001AED24);
    rgba=FloatToInt((float)D_L20_001AED30 * *(float *)(state+0x14));
    packet.color[0]=packet.color[1]=packet.color[2]=packet.color[3]=(rgba&0xffffff)|*(u32 *)(state+4);
    VU1_addGSregister(6,GetEffectTextureDescriptor(D_L20_001AED20));
    VU1_addGSregister(0x42,0x8000000044ULL);
    VU1_addGSregister(8,0);
    VU1_addGSregister(0x14,0xff9000000260ULL);
    VU1_addGSregister(0x4a,0);
    font_queue_vu_state();
    for (j=0;j<290;j++) {
        transform_vector(&transformed,&D_L20_0029DC20[j],basis);
        D_L20_0023D8D0[j][0]=transformed.f[0];
        D_L20_0023D8D0[j][1]=transformed.f[1];
        D_L20_0023D8D0[j][2]=transformed.f[2];
        colors[j]=packet.color[0];
    }
    func_00281810(148,D_L20_0023D8D0,colors,D_L20_0029EE40,1);
    func_00281810(109,D_L20_0023D8D0[146],colors+146,D_L20_0029EE40[146],1);
    func_00281810(36,D_L20_0023D8D0[254],colors+254,D_L20_0029EE40[254],1);
    packet.texture=GetEffectTextureDescriptor(11);
    packet.flags=0x8000000048ULL;
    rgba=FloatToInt(*(float *)(state+0x14)*64.0f);
    packet.color[0]=packet.color[1]=(rgba<<24)|*(u32 *)(state+4);
    packet.color[3]=0;packet.color[2]=0;
    wide=D_L20_001AED28*D_L20_001AED2C;
    narrow=D_L20_001AED28;
    for (i=0;i<32;i++) {
        face=D_L20_0029FD60[i];
        for (j=0;j<4;j++,face++) {
            int index=*face;
            if (j>=2) FastVecScale(&packet.vertex[j],&D_L20_0029F760[index],wide);
            else FastVecScale(&packet.vertex[j],&D_L20_0029F760[index],narrow);
        }
        packet.uv[0]=0.5f;
        packet.uv[1]=0.5f;
        packet.uv[2]=0.5f;
        packet.uv[3]=0.5f;
        packet.uv[4]=0.5f;
        packet.uv[5]=1.0f;
        packet.uv[6]=0.5f;
        packet.uv[7]=1.0f;
        draw_world_quad(&packet,basis,0);
    }
}
