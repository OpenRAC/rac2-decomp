/* sol-high (v1232), USA v1.01, game -O2 -G8 -ffunction-sections.
 * Best check.py result: 1700/1700 bytes, 0/4 places; ten instructions differ
 * at +0x2D0..+0x318 in the first shared alpha/RGB packing block.
 * Red << 16 and green << 8 use v1/a2 in the opposite assignment to retail;
 * two loads, two shifts, four ORs and two transparent-color stores differ.
 * All other instructions agree modulo relocations.
 * Recompiled the earlier sol-low draft on this checkout's pinned compiler.
 * Incremental transparent-color ORs, shifted unsigned component temporaries,
 * and unshifted unsigned component temporaries tie the earlier bytes. A
 * green-first interleaved build changes OR scheduling without improving the
 * allocation. Accumulating the opaque color in vertex 0 adds two store-order
 * differences. Stopped on the tied forms, rather than exhaust equivalent C.
 * Allocator dump: red load/shift pseudos 212/213 -> v1; green 216/217 -> a2.
 * A new hypothesis must change that allocation while retaining the OR DAG.
 * Compile as a separate -G8 unit; required declarations follow.
 *
 * closer D, 1 November 2026: same dataflow and order as retail; only the qty sort differs. The red
 * chain 212/213/228/230 has 10 refs (priority about 0.88), the green chain 216/217 has 5 (0.71), so
 * red takes $v1. Retail gives green $v1, which needs fewer refs tied to red or a longer red life.
 * Nine more spellings of the opaque/transparent pair tie or are worse.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    TI128 corner[4];
    s32 rgba[4];
    float uv[4][2];
    s64 d70;
    s64 d78;
    s64 d80;
    s64 d88;
} L13Quad;

extern float D_L13_001B12D0 __attribute__((sda));
extern float D_L13_001B12D8 __attribute__((sda));
extern float D_L13_001B12DC __attribute__((sda));
extern float D_L13_001B12E4 __attribute__((sda));
extern float D_L13_001B12FC __attribute__((sda));
extern int D_L13_001B12E0 __attribute__((sda));
extern int D_L13_001B12E8 __attribute__((sda));
extern int D_L13_001B1300 __attribute__((sda));
extern int D_L13_001B1304 __attribute__((sda));
extern int D_L13_001B1318 __attribute__((sda));
extern int D_L13_001B131C __attribute__((sda));
extern int D_L13_001B1320 __attribute__((sda));
extern int D_L13_001B1324 __attribute__((sda));
extern int D_L13_001B1328 __attribute__((sda));
extern int D_L13_001B132C __attribute__((sda));
extern int D_L13_001B1330 __attribute__((sda));
extern int D_L13_001B1334 __attribute__((sda));
extern int D_L13_001B1338 __attribute__((sda));
extern int D_L13_001B133C __attribute__((sda));
extern int D_L13_001B1340 __attribute__((sda));
extern int D_L13_001B1344 __attribute__((sda));
extern int D_L13_001B1348 __attribute__((sda));
extern int D_L13_001B134C __attribute__((sda));
extern int D_L13_001B1350 __attribute__((sda));
extern int D_L13_001B1354 __attribute__((sda));
extern float D_L13_001B98C0[];
extern void func_L00_00412088(L13Quad *);
extern void func_00281DE8(L13Quad *, int, int, int);
extern void func_00280B90(L13Quad *, void *, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7940(void);
extern void func_00281EB8(void *,int,int,int,float,float,float);
void func_L13_0040DFC0(int a0,int a1,int a2,int a3,int a4,char *obj) {
    L13Quad q;
    float base[4] __attribute__((aligned(16)));
    float rel[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float tip[4] __attribute__((aligned(16)));
    float side[4] __attribute__((aligned(16)));
    float *rp;
    char *vars=*(char **)(obj+0x68);
    int i;
    func_L00_00412088(&q);
    func_00281DE8(&q,D_L13_001B1300,0,0x80);
    q.rgba[1]=D_L13_001B1324<<24;
    q.rgba[1]|=D_L13_001B1320<<16;
    q.rgba[1]|=D_L13_001B131C<<8;
    q.rgba[1]|=D_L13_001B1318;
    q.rgba[0]=q.rgba[1];
    q.rgba[3]=D_L13_001B1334<<24;
    q.rgba[3]|=D_L13_001B1330<<16;
    q.rgba[3]|=D_L13_001B132C<<8;
    q.rgba[3]|=D_L13_001B1328;
    q.rgba[2]=q.rgba[3];
    q.uv[0][0]=0; q.uv[0][1]=0; q.uv[1][0]=0; q.uv[1][1]=1;
    q.uv[2][0]=1; q.uv[2][1]=0; q.uv[3][0]=1; q.uv[3][1]=1;
    rp=rel;
    for(i=0;i<4;i++) {
        q.uv[i][0]-=*(float *)(vars+0x28);
        if(q.uv[i][0]<=7.0f) q.uv[i][0]+=7.0f;
    }
    *(float *)(vars+0x28)+=0.1f;
    if(*(float *)(vars+0x28)>=4.0f) *(float *)(vars+0x28)-=4.0f;
    func_00282F20(base,vars,-0.17f);
    func_00282CC0(base,obj+0x10,base);
    func_00282CF0(rp,obj+0x10,D_L13_001B98C0);
    func_00282F20(axis,vars,-D_L13_001B12FC);
    func_00282CC0(tip,base,axis);
    func_00282DD8(side,rp,axis);
    func_00282F20(side,side,D_L13_001B12DC);
    func_00282CC0(&q.corner[0],obj+0x10,side);
    func_00282CF0(&q.corner[1],obj+0x10,side);
    func_00282CC0(&q.corner[2],tip,side);
    func_00282CF0(&q.corner[3],tip,side);
    func_00280B90(&q,0,0);
    q.rgba[0]=q.rgba[2]; q.rgba[1]=q.rgba[3];
    q.rgba[3]=0x801010;
    q.rgba[2]=q.rgba[3];
    qcopy(&q.corner[0],&q.corner[2]); qcopy(&q.corner[1],&q.corner[3]);
    func_00282CC0(&q.corner[2],&q.corner[2],axis);
    func_00282CC0(&q.corner[3],&q.corner[3],axis);
    func_00280B90(&q,0,0);
    func_00281DE8(&q,D_L13_001B1304,1,0x80);
    q.rgba[1]=D_L13_001B1344<<24;
    q.rgba[1]|=D_L13_001B1340<<16;
    q.rgba[1]|=D_L13_001B133C<<8;
    q.rgba[1]|=D_L13_001B1338;
    q.rgba[0]=q.rgba[1];
    q.rgba[2]=q.rgba[3]=(D_L13_001B1340<<16)|(D_L13_001B133C<<8)|D_L13_001B1338;
    q.uv[0][0]=0; q.uv[0][1]=0; q.uv[1][0]=0; q.uv[1][1]=1;
    q.uv[2][0]=1; q.uv[2][1]=0; q.uv[3][0]=1; q.uv[3][1]=1;
    func_00282F20(side,side,D_L13_001B12D8);
    func_00282CC0(&q.corner[0],obj+0x10,side);
    func_00282CF0(&q.corner[1],obj+0x10,side);
    func_00282CC0(tip,obj+0x10,axis);
    func_00282CC0(tip,tip,axis);
    func_00282CC0(&q.corner[2],tip,side);
    func_00282CF0(&q.corner[3],tip,side);
    func_00280B90(&q,0,0);
    q.rgba[1]=D_L13_001B1344<<24;
    q.rgba[1]|=D_L13_001B1340<<16;
    q.rgba[1]|=D_L13_001B133C<<8;
    q.rgba[1]|=D_L13_001B1338;
    q.rgba[0]=q.rgba[1];
    q.rgba[3]=D_L13_001B1340<<16;
    q.rgba[3]|=D_L13_001B133C<<8;
    q.rgba[3]|=D_L13_001B1338;
    q.rgba[2]=q.rgba[3];
    func_00282F20(side,side,D_L13_001B12D0);
    func_00282F20(base,vars,-0.1f);
    func_00282CC0(base,obj+0x10,base);
    func_00282CC0(&q.corner[0],base,side);
    func_00282CF0(&q.corner[1],base,side);
    func_00282CC0(tip,base,axis);
    func_00282CC0(tip,tip,axis);
    func_00282CC0(&q.corner[2],tip,side);
    func_00282CF0(&q.corner[3],tip,side);
    func_00280B90(&q,0,0);
    q.rgba[1]=D_L13_001B1354<<24;
    q.rgba[1]|=D_L13_001B1350<<16;
    q.rgba[1]|=D_L13_001B134C<<8;
    q.rgba[1]|=D_L13_001B1338;
    q.rgba[0]=q.rgba[1];
    q.rgba[3]=D_L13_001B1350<<16;
    q.rgba[3]|=D_L13_001B134C<<8;
    q.rgba[3]|=D_L13_001B1348;
    q.rgba[2]=q.rgba[3];
    func_00282F20(side,side,D_L13_001B12D0);
    func_00282F20(base,vars,-0.1f);
    func_00282CC0(base,obj+0x10,base);
    func_00282CC0(&q.corner[0],base,side);
    func_00282CF0(&q.corner[1],base,side);
    func_00282CC0(tip,base,axis);
    func_00282CC0(tip,tip,axis);
    func_00282CC0(&q.corner[2],tip,side);
    func_00282CF0(&q.corner[3],tip,side);
    func_00280B90(&q,0,0);
    q.rgba[1]=0x40ffffff;
    q.rgba[0]=q.rgba[1];
    q.rgba[3]=D_L13_001B1340<<16;
    q.rgba[3]|=D_L13_001B133C<<8;
    q.rgba[3]|=D_L13_001B1338;
    q.rgba[2]=q.rgba[3];
    func_00282F20(side,side,D_L13_001B12D8);
    func_00282CC0(&q.corner[0],obj+0x10,side);
    func_00282CF0(&q.corner[1],obj+0x10,side);
    func_00282F20(axis,vars,-0.6f);
    func_00282CC0(tip,obj+0x10,axis);
    func_00282CC0(tip,tip,axis);
    func_00282CC0(&q.corner[2],tip,side);
    func_00282CF0(&q.corner[3],tip,side);
    func_00280B90(&q,0,0);
    func_00281EB8(obj+0x10,D_L13_001B12E0,D_L13_001B12E8,1,D_L13_001B12E4,0.08f,func_002A7940());
}
