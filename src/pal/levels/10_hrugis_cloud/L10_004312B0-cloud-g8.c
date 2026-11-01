#include "include_asm.h"

#include "common.h"
typedef int CloudQuad __attribute__((mode(TI)));
typedef union { struct { float x,y,z,w; } v; CloudQuad q; } CloudVec;
extern int D_L10_001A9018[] MACRO_ADDR;
extern unsigned short **D_L10_001A9014 MACRO_ADDR;
extern char *D_L10_001B2B94 MACRO_ADDR;
extern char *D_L10_001B2B9C MACRO_ADDR;
extern char D_L10_001B9680[];
extern CloudVec D_L10_0026CEA0[];
extern short D_L10_002273C0[];
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L02_002F1FB8(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_002831B0(float);
extern float func_L04_004554F8(float);
extern void func_L04_00363CA0(void *, int, float);

/* Two-state update. State 0 builds three z rotations (0, 2pi/3, -2pi/3), eighteen local
   points, and for each entry of the object's D_L10_001A9014 list transforms six of them
   (set chosen through the primitive's D_L10_002273C0 class) into D_L10_0026CEA0. State 1
   advances a phase and, for each of the 1056 stored points in front of the view, draws a
   0x33AA00 glow whose alpha follows the angle to a wandering direction.
   This unit is built with -fno-rerun-loop-opt (config/cflags.txt): the second loop pass
   would hoist D_L10_0026CEA0's high half out of the list loop, which retail recomputes.
   The initial values of k, entry, prim, transform and case 0's i only size gcse's
   expression table (185 buckets), which orders the matrix pointers' registers as retail. */
void func_PAL_L10_004312B0(char *p) {
    union {
        struct { float m[3][12]; CloudVec rotations[3]; } init;
        struct { CloudVec temp, visible, direction, position, offset; } update;
    } scratch;
    CloudVec points[18], temp;
    char *st = *(char **)(p + 0x68);
    int n, k = 0;
    unsigned short *entry = 0;
    char *prim = 0, *transform = 0;
    float a,b,c,t,weight;
    int color;
    switch ((unsigned char)p[0x20]) {
    case 0: {
        int i = 0;
        int index = *(int *)st;
        if (index >= D_L10_001A9018[0] || !D_L10_001A9014[index] || index == -1) {
            func_0029F338(p);
            return;
        }
        {
        float step = 0.019867549f;
        float angle0 = 1.047197699546814f;
        float angle1 = 2.094395399093628f;
        float angle2;
        int alpha=255;
        *(float *)(st+4) = 0.0f;
        *(float *)(st+8) = step;
        angle2=-2.094395399093628f;
        scratch.init.rotations[0].q=0; scratch.init.rotations[1].q=0; scratch.init.rotations[2].q=0;
        scratch.init.rotations[0].v.z=angle0;
        scratch.init.rotations[1].v.z=angle1;
        scratch.init.rotations[2].v.z=angle2;
        p[0x30] = alpha;
        }
        func_002833F0(scratch.init.m[0],scratch.init.rotations);
        func_002833F0(scratch.init.m[1],scratch.init.rotations+1);
        func_002833F0(scratch.init.m[2],scratch.init.rotations+2);
        { int j; for(j=17;j>=0;j--) points[j].v.w=0; }
        n=0;
        points[0].v.x=0; points[0].v.y=10; points[0].v.z=-4;
        func_00283098(points+1,points,scratch.init.m[1]);
        func_00283098(points+2,points,scratch.init.m[2]);
        points[3].v.x=0; points[3].v.y=30; points[3].v.z=-3.5f;
        func_00283098(points+4,points+3,scratch.init.m[1]);
        func_00283098(points+5,points+3,scratch.init.m[2]);
        points[6].v.x=3.5f; points[6].v.y=0; points[6].v.z=-2;
        func_00283098(points+7,points+6,scratch.init.m[1]);
        func_00283098(points+8,points+6,scratch.init.m[2]);
        func_00283098(points+9,points+6,scratch.init.m[0]);
        func_00283098(points+10,points+9,scratch.init.m[1]);
        func_00283098(points+11,points+9,scratch.init.m[2]);
        points[12].v.x=15; points[12].v.y=30; points[12].v.z=2;
        points[13].v.x=15; points[13].v.y=15; points[13].v.z=2;
        points[14].v.x=15; points[14].v.y=0; points[14].v.z=2;
        points[15].v.x=30; points[15].v.y=15; points[15].v.z=2.5f;
        points[16].v.x=60; points[16].v.y=-15; points[16].v.z=8;
        points[17].v.x=60; points[17].v.y=-30; points[17].v.z=10;
        entry=D_L10_001A9014[*(int *)st];
        while(entry) {
            if ((short)entry[-1]<0 && entry!=D_L10_001A9014[*(int *)st]) break;
            transform=D_L10_001B2B9C+(*entry&0x7fff)*64;
            if(!transform) break;
            prim=D_L10_001B2B94+(*entry&0x7fff)*32;
            {
            unsigned short *next = entry + 1;
            for(i=0;i<6;i++) {
                k=D_L10_002273C0[(unsigned char)prim[0x1d]];
                k=k==0xdf6 ? 0 : k==0xdf7 ? 6 : 12;
                func_00283098(&temp,points+(i+k),transform);
                func_00282CC0(D_L10_0026CEA0+n,transform+0x30,&temp);
                n++;
            }
            entry = next;
            }
        }
        p[0x20]=1;
        break;
    }
    case 1: {
        int i;
        *(float *)(st+4)+=*(float *)(st+8);
        for(i=0;i<1056;i++) {
            qcopy(&scratch.update.temp,D_L10_0026CEA0+i);
            func_L02_002F1FB8(&scratch.update.visible,&scratch.update.temp,D_L10_001B9680);
            if(func_00282DB0(D_L10_001B9680+0x230,&scratch.update.visible)<=0.0f) continue;
            {
            float one=1.0f, lower=1.396263599395752f, lowEnd, highStart, upper;
            weight=0.0f;
            lowEnd=1.466076731681824f;
            a=func_002ABB18(*(float *)(st+4)*0.392699122f);
            highStart=1.65806293f;
            upper=2.26892829f;
            b=func_002ABB18(*(float *)(st+4)*0.581194639f);
            c=func_00283198(b);
            scratch.update.direction.v.x=c*func_00283180(a);
            scratch.update.direction.v.y=c*func_00283198(a);
            scratch.update.direction.v.z=func_00283180(b);
            func_L02_002F1FB8(&scratch.update.position,&scratch.update.temp,p+0x10);
            func_00282F20(&scratch.update.position,&scratch.update.position,one);
            t=1.57079637f-func_002831B0(func_00282DB0(&scratch.update.position,&scratch.update.direction));
            if(t>lower) {
                if(t<=lowEnd) weight=func_L04_004554F8((t-lower)/0.0698131323f);
                else if(t<=highStart) weight=one;
                else if(t<=upper) weight=one-func_L04_004554F8((t-highStart)/0.610865355f);
            }
            color=32;
            if(weight!=0) {
                if(weight!=1) color=(int)(weight*color);
                color <<= 24;
                color |= 0x33aa00;
                func_00282CF0(&scratch.update.offset,D_L10_001B9680,&scratch.update.temp);
                func_00282F20(&scratch.update.offset,&scratch.update.offset,4.0f);
                func_00282CC0(&scratch.update.temp,&scratch.update.temp,&scratch.update.offset);
                func_L04_00363CA0(&scratch.update.temp,color,2100000.0f);
            }
            }
        }
        break;
    }
    }
}
