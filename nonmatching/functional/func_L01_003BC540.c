/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * Tier: sol-high, v1001. USA v1.01; -O2 -G8 -ffunction-sections -g.
 * Best check.py: 1272 / 1272 bytes, 0 of 1 places match. No linked match.
 * The prologue now agrees, and native TI stores recover both por/sq clears.
 * Initial progress-table register order, first trail-loop comparison, and
 * debris-copy scheduling/allocation still differ. The compiler hoists the
 * constant-vector address across the debris loops; retail rematerializes it.
 * Retained the in-place early removal block and exact 0x40060A93 angle step.
 * Measured alternatives: qcopy_nc plus TI clears: 1284 bytes with -g (1268
 * without); goto loops: 1268 bytes but a smaller frame and different invariant
 * allocation; -mno-split-addresses: 1268 bytes, worse; -fno-gcse: 1252 bytes,
 * worse; -frac2-qcopy/-frac2-qcopy-barrier: 1284 bytes, worse. Incomplete versus
 * four-element constant-vector externs tie. Splitting trail/debris step locals
 * changes FP allocation but leaves the initial comparison on the step register.
 * Next: independently recover the original vector/loop source shape before
 * retrying invariant-address allocation. All required declarations follow.
 */
#include "common.h"
typedef int BC540Quad __attribute__((mode(TI)));
extern float func_002A7878(float,float),func_002A7940(void),func_00283B98(float,float);
extern void func_L00_00326620(void *,int,int),func_0029F338(void *);
extern void func_00282F20(void *,void *,float),func_00282CC0(void *,void *,void *);
extern void func_L01_003BC490(void *,void *),func_002E5CF8(int,int,void *,void *);
extern char *func_002A9640(void *,int,int);
extern void func_0029FCC0(void *,int,void *),func_002A6C58(void *,int,int),func_002A7470(void *,int,int,int);
extern char *func_L01_003BCA38(char *,int,void *,void *,int,int,void *,void *,void *,float);
extern unsigned char D_L01_0021E4B0[];
extern int D_001A79F0;
extern unsigned char D_0019B4A8[];
extern float D_L01_001A8F60[4];
void func_L01_003BC540(char *obj)
{
    float delta[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float dimensions[4] __attribute__((aligned(16)));
    char *state=*(char **)(obj+0x68), *hit,*piece;
    float step,scale,t;
    int i,j,index,byte;
    float distance;
    if(*(unsigned char *)(obj+0x20)==0) {
        *(float *)(obj+0x2C)*=func_002A7878(0.8f,1.1f);
        if(*(unsigned char *)(obj+0xB0)!=255) {
            index=*(short *)(obj+0xB2);
            if(D_L01_0021E4B0[index+0x464]) goto remove_initial;
            byte=D_0019B4A8[(index>>1)+(D_001A79F0<<10)];
            if(index&1) {
                if((byte>>4)&7) goto remove_initial;
                goto initial_path;
            }
            if(!(byte&7)) goto initial_path;
remove_initial:
            func_L00_00326620(obj,0xA29,0);
            func_0029F338(obj);
            return;
        }
initial_path:
        distance=*(float *)(state+0x50);
        if(distance>0.0f) {
            step=distance/ *(float *)(state+0x54);
            t=step;
            func_00282F20(delta,obj+0xC0,step);
            func_00282CC0(position,obj+0x10,delta);
            while(t<*(float *)(state+0x50)) {
                func_L01_003BC490(obj,position);
                t+=step;
                func_00282CC0(position,position,delta);
            }
        }
        *(unsigned char *)(obj+0x20)=1;
    }
    else {
    hit=func_002A9640(obj,0x4010000,0);
    if(hit && *(float *)(hit+0x2C)>0.0f) {
        step=*(float *)(obj+0x2C)/ *(float *)(*(char **)(obj+0x24)+0x24);
        scale=step;
        *(BC540Quad *)position=*(BC540Quad *)(obj+0xF0);
        *(BC540Quad *)rotation=0;
        rotation[1]=-1.3790000f; rotation[2]=0.778f; rotation[3]=0.3f;
        func_002E5CF8(0,0,obj,position);
        for(i=0;i<4;i++) {
            func_0029FCC0(obj,i,delta);
            position[2]=func_002A7940();
            for(j=2;j>=0;j--) {
                piece=func_L01_003BCA38(obj,0xA28,delta,position,0,1,&D_L01_001A8F60,&D_L01_001A8F60,rotation,0.0f);
                *(float *)(piece+0x2C)*=scale;
                position[2]=func_00283B98(position[2],2.0943954f);
            }
            scale*=0.85f;
        }
        *(BC540Quad *)dimensions=0;
        dimensions[0]=0.175f;dimensions[1]=0.136f;dimensions[2]=-0.691f;dimensions[3]=0.05f;
        func_0029FCC0(obj,4,delta);
        *(BC540Quad *)position=*(BC540Quad *)(obj+0xF0);
        for(j=2;j>=0;j--) {
            piece=func_L01_003BCA38(obj,0xA27,delta,position,0,1,&D_L01_001A8F60,&D_L01_001A8F60,dimensions,0.0f);
            *(float *)(piece+0x2C)*=step;
            position[2]=func_00283B98(position[2],2.0943954f);
        }
        func_L00_00326620(obj,0xA29,0);
        func_002A6C58(obj,0,3);
        index=*(short *)(obj+0xB2);
        if(index&1) {
            byte=(index>>1)+(D_001A79F0<<10);
            if(((D_0019B4A8[byte]>>4)&7)!=7) D_0019B4A8[byte]+=16;
        } else {
            byte=(index>>1)+(D_001A79F0<<10);
            if((D_0019B4A8[byte]&7)!=7) D_0019B4A8[byte]++;
        }
        func_0029F338(obj);
    }
    }
    if(*(unsigned char *)(obj+0xBC)) {
        if(*(unsigned char *)(obj+0x43)!=1) func_002A7470(obj,1,0,10);
        *(unsigned char *)(obj+0xBC)=0;
    } else if((*(unsigned char *)(obj+0x60)&2) && *(unsigned char *)(obj+0x43)!=0) func_002A7470(obj,0,0,60);
    return;

}
