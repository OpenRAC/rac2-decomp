/* Tier: Claude Opus 5.5 (opus-1, xhigh effort), v2145, 3 November 2026.
 * Best check.py: 1156/1156 bytes, 0/2 USA v1.01 places; cdiff 67 of 289 rows differ, all of them
 * register names (every instruction corresponds after relocation).
 * Profile: -O2 -G8 -ffunction-sections -g, dedicated unit src/levels/shared/L03_003CA4B0-g8.c.
 * RAC1 counterpart: draw_gadgebot_spawn_container (overlays/shared/gadgebot_containers_and_frog.c).
 * Fixed since v1009: the face loop now uses RAC1's static inline TransformPoint wrapper, a do/while
 * and a `center` pointer, so no sp+0x90 copy is hoisted into s4 (the face-table base is back in s4).
 * The far loop is RAC1's indexed for (i < 57) over the two tables, which fixes its preheader order.
 * An index form of the near loop is far worse (138 rows), so the near loop keeps its pointers.
 * Remaining: reload register choice. The spilled `near` (sp+0x110, pseudo 85) reloads into v1 where
 * retail uses v0. The .greg dump says "Spilling reg 2" for its test (insn 118), but choose_reload_regs
 * gives v1. The rematerialised in-loop HIGH parts alternate v1/v0 where retail uses v0 throughout
 * (a0 for the D_L03_00240CF0 high in both preheaders). The last one makes retail's loop-end branch a
 * bnel, because its slot sets the tested v0; ours is a bnez.
 * Next: trace reload's per-insn used_spill_regs and its last_spill_reg round-robin in the .greg dump.
 * Find what makes retail's first reload after the near=1 store (insn 1052, v0) land on v0 again.
 */
#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
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
static inline void TransformPoint(float *dst,void *src,void *m){func_002830C0(dst,src,m);}

void func_L03_003CA4B0(char *m){
 ReflectPacket packet __attribute__((aligned(16)));
 typedef unsigned int ReflectQ __attribute__((mode(TI)));
 typedef union {float f[4];ReflectQ q;} ReflectVec;
 typedef struct {ReflectVec row[4];} ReflectMatrix;
 ReflectMatrix transform;
 ReflectVec dir,normal,reflected,temp;
#define matrix ((float *)&transform)
 int near=0,i,j,index;float scale,denom;u64 flags;
 scale=F(m,0x2c)/F(*(char **)(m+0x24),0x24);
 func_00282F20(transform.row[0].f,m+0xc0,scale);func_00282F20(transform.row[1].f,m+0xd0,scale);func_00282F20(transform.row[2].f,m+0xe0,scale);
 transform.row[3].f[0]=F(m,0x10);transform.row[3].f[1]=F(m,0x14);transform.row[3].f[2]=F(m,0x18);transform.row[3].f[3]=1;
 if(func_00282C48(D_L03_001B9840.pos[0]-F(m,0x10))<16&&func_00282C48(D_L03_001B9840.pos[1]-F(m,0x14))<16)near=1;
 if(near!=0){
 ReflectUV *uv=D_L03_00240B20;
 float (*pos)[4]=D_L03_00240CF0;
 for(i=0;i<57;i++,uv++,pos++){
 func_002830C0(pos,D_L03_0029A920[i],&transform);
 func_00282CF0(dir.f,pos,D_L03_001B9980);func_00282F20(dir.f,dir.f,1);
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
 for(i=0;i<57;i++){float *world=D_L03_00240CF0[i];func_002830C0(world,D_L03_0029A920[i],&transform);}
 }
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
