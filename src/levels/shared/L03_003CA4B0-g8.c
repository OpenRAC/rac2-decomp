#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern void func_00282F20(void *,void *,float),func_002830C0(void *,void *,void *),func_00282CF0(void *,void *,void *),func_00282D30(void *,void *,float),func_00283098(void *,void *,void *);
extern float func_00282C48(float),func_00282DB0(void *,void *),func_00282C10(float);
extern u64 func_0027C878(int);
extern void func_00280B90(void *,int,int);
extern char D_L03_001B9980[];
typedef float ReflectUV[2];
extern ReflectUV D_L03_00240B20[57];
extern float D_L03_00240CF0[57][4];
extern float D_L03_0029A920[57][4],D_L03_0029B3C0[57][4],D_L03_0029B750[42][4],D_L03_0029B120[42][4],D_L03_0029AF50[][2];
extern short D_L03_0029ACB0[42][4][2];
extern int D_L03_001B0330 __attribute__((sda)),D_L03_001B031C __attribute__((sda)),D_L03_001B0320 __attribute__((sda)),D_L03_001B0324 __attribute__((sda)),D_L03_001B0328 __attribute__((sda)),D_L03_001B032C __attribute__((sda)),D_L03_001B0334 __attribute__((sda));
extern float D_L03_001B0338 __attribute__((sda));
typedef struct {
 float position[4][4];
 int color0,color1,color2,color3;
 float uv[4][2];
 u64 zero, texture, mode, blend;
} ReflectPacket;
typedef struct {char pad[0x140];float pos[4];} ReflectCamera;
extern ReflectCamera D_L03_001B9840;

/* Transform src by the matrix into dst (RAC1 TransformPoint). */
static inline void TransformPoint(float *dst,void *src,void *m)
{
    func_002830C0(dst,src,m);
}

/* Draws the reflective container moby: 57 vertices, 42 faces (RAC1 draw_gadgebot_spawn_container). */
void func_L03_003CA4B0(char *m){
 ReflectPacket packet __attribute__((aligned(16)));
 typedef unsigned int ReflectQ __attribute__((mode(TI)));
 typedef union {float f[4];ReflectQ q;} ReflectVec;
 typedef struct {ReflectVec row[4];} ReflectMatrix;
 ReflectMatrix transform;
 ReflectVec dir,normal,reflected,temp;
 float (*verts)[4];
 int near=0,i,j,index;float scale,denom;u64 flags;
 scale=F(m,0x2c)/F(*(char **)(m+0x24),0x24);
 func_00282F20(transform.row[0].f,m+0xc0,scale);func_00282F20(transform.row[1].f,m+0xd0,scale);func_00282F20(transform.row[2].f,m+0xe0,scale);
 transform.row[3].f[0]=F(m,0x10);transform.row[3].f[1]=F(m,0x14);transform.row[3].f[2]=F(m,0x18);transform.row[3].f[3]=1;
 if(func_00282C48(D_L03_001B9840.pos[0]-F(m,0x10))<16&&func_00282C48(D_L03_001B9840.pos[1]-F(m,0x14))<16)near=1;
 if(near!=0){
 ReflectUV *uv=D_L03_00240B20;
 for(i=0;i<57;i++,uv++){
 verts=D_L03_00240CF0;
 func_002830C0(verts[i],D_L03_0029A920[i],&transform);
 func_00282CF0(dir.f,verts[i],D_L03_001B9980);func_00282F20(dir.f,dir.f,1);
 func_002830C0(reflected.f,D_L03_0029B3C0[i],&transform);
 func_00282F20(reflected.f,reflected.f,D_L03_001B0338);
 denom=func_00282DB0(reflected.f,dir.f);func_00282D30(temp.f,reflected.f,denom+denom);
 func_00282CF0(temp.f,dir.f,temp.f);func_00282F20(temp.f,temp.f,1);
 temp.f[2]+=1;
 denom=func_00282C10(temp.f[2]+temp.f[2]);
 denom+=denom;
 {float u=temp.f[0]/denom;
 float v=temp.f[1]/denom;
 (*uv)[1]=v+0.5f;(*uv)[0]=u+0.5f;}
 }
 }else{
 for(i=0;i<57;i++){func_002830C0(D_L03_00240CF0[i],D_L03_0029A920[i],&transform);}
 }
  /* Dead store: keeps gcse's reaching register for the table's high half alive until cse2,
    so both preheaders share it (flow then deletes this statement). */
 verts=D_L03_00240CF0;
 {u64 texture=func_0027C878(D_L03_001B0330);
 flags=(u64)D_L03_001B031C;
 flags|=(u64)D_L03_001B0320<<2;
 flags|=(u64)D_L03_001B0324<<4;
 flags|=(u64)D_L03_001B0328<<6;
 flags|=(u64)D_L03_001B032C<<32;
 packet.texture=texture;packet.mode=0x0000ff9000000260ULL;packet.blend=flags;}
 packet.zero=0;
 packet.color3=D_L03_001B0334;
 packet.color2=D_L03_001B0334;
 packet.color1=D_L03_001B0334;
 packet.color0=D_L03_001B0334;
 i=0;
 do{
 float *center=normal.f;
 TransformPoint(center,D_L03_0029B750[i],&transform);
 func_00282CF0(dir.f,center,D_L03_001B9980);func_00282F20(dir.f,dir.f,1);
 func_00283098(center,D_L03_0029B120[i],&transform);
 if(!(0.0f<func_00282DB0(dir.f,center))){
 short *idx=D_L03_0029ACB0[i][0];
 for(j=0;j<4;j++,idx+=2){
 index=idx[0];qcopy(packet.position[j],D_L03_00240CF0[index]);
 if(near){packet.uv[j][0]=D_L03_00240B20[index][0];packet.uv[j][1]=D_L03_00240B20[index][1];}
 else {packet.uv[j][0]=D_L03_0029AF50[idx[1]][0];packet.uv[j][1]=D_L03_0029AF50[idx[1]][1];}
 }
 func_00280B90(&packet,0,0);
 }
 i++;
 }while(i<42);
}
