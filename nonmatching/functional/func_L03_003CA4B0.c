/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Tier: GPT-6.1 Sol (high effort), v1009, 29 October 2026.
 * Best check.py: 1156/1156 bytes, 0/2 USA v1.01 places.
 * Profile: -O2 -G8 -ffunction-sections -g, dedicated -g8 unit.
 * The 0x180 frame and all instructions before +0x25C agree after relocation:
 * the typed camera fixes its base and -g supplies the division padding.
 * Pointer-based transformed-position/UV loops and separate u/v divisions recover
 * the complete near-camera reflection loop. Signed widening matches retail lw.
 * First difference +0x25C: the far-loop destination high half uses v1, not a0;
 * its shared scratch preparation and argument moves are differently scheduled.
 * In packet setup, GCC hoists the matrix address into s4; retail forms it at use
 * and retains the face-table base in s4 (ours s5). This adds one early instruction,
 * shifts the otherwise corresponding flag/store sequence and consumes a later nop.
 * Scalar/aggregate matrix views and aligned vector unions do not fix this.
 * -fno-gcse worsens size to 1132; -frac2-gcse-unsplit-edges is byte-neutral.
 * closer D successor, 1 November 2026: the s4 address is insn 900, hoisted only by the second
 * loop pass (regno 330, life 20, savings 2); forcing gcse bucket counts changes nothing (17 words).
 * Both placements fail at the same first instruction; bindings remain unvalidated.
 * The culling guard is !(dot > 0), preserving retail unordered behavior, rather
 * than dot <= 0. All required declarations are retained below.
 * Reopen with evidence for the shared far-branch/packet pointer lifetimes, rather
 * than repeating division padding, camera typing, or algebraic blend experiments.
 *
 * closer D, 1 November 2026: sp+0x90 is PRE's reaching pseudo 321, set before the near test, with no hard
 * register, so reload rematerialises it at each use (retail's s7 and the far loop's addiu). The third loop keeps
 * a copy, pseudo 200 = 321, that loop.c hoists (life 22) and global allocates to s4. Retail has no such copy: both
 * a2 loads there are rematerialised and s5-s7, fp stay free. It needs each use to stay a life-1 pseudo (undesirable
 * to hoist), so cse1 must not merge the two addresses.
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
 float (*source)[4]=D_L03_0029A920;
 float (*dest)[4]=D_L03_00240CF0;
 for(i=56;i>=0;i--){func_002830C0(dest,source++,&transform);dest++;}
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
 for(i=0;i<42;i++){
 func_002830C0(normal.f,D_L03_0029B750[i],&transform);
 func_00282CF0(dir.f,normal.f,D_L03_001B9980);func_00282F20(dir.f,dir.f,1);
 func_00283098(normal.f,D_L03_0029B120[i],&transform);
 if(!(func_00282DB0(dir.f,normal.f)>0)){
 for(j=0;j<4;j++){
 index=D_L03_0029ACB0[i][j][0];qcopy(packet.position[j],D_L03_00240CF0[index]);
 if(near){packet.uv[j][0]=D_L03_00240B20[index][0];packet.uv[j][1]=D_L03_00240B20[index][1];}
 else {int textureIndex=D_L03_0029ACB0[i][j][1];packet.uv[j][0]=D_L03_0029AF50[textureIndex][0];packet.uv[j][1]=D_L03_0029AF50[textureIndex][1];}
 }
 func_00280B90(&packet,0,0);
 }
 }
}
