/*
 * Tier: opus (v2199). USA v1.01; build as its own unit with
 * -O2 -G8 -ffunction-sections -g (e.g. L01_003BB9D0-debris-g8.c).
 * Best check.py: 1280 / 1272 bytes, 0 of 1 places match. After aligning
 * the listings, 288 of 318 retail instructions agree; the previous draft
 * had 237. Fixes against that draft:
 *  - D_L01_001A8F60 declared MACRO_ADDR (as in L01_00388FD0-tether-g8.c).
 *    Its unsplit la is not hoisted, so both debris loops rebuild
 *    lui/addiu $t2 per call with daddu $t3,$t2, and no fp is saved.
 *  - The progress table is D_L01_0021E4B0.collected[] (header 0x464),
 *    with *(short *)(obj+0xB2) re-read at each use, not a local.
 *  - Both position copies use qcopy (lq/sq through pointer registers).
 * Still differs:
 *  (1) Initial trail path: retail loads distance into $f12 (ours $f1).
 *      Its first loop test uses t in $f20; ours CSE-substitutes step ($f21).
 *  (2) Position pointer before func_002E5CF8: retail ties it to $a3
 *      (sq to 0($a3), then daddu $s4,$a3). Ours keeps it in $t0 and adds
 *      daddu $a3,$t0, and lui $s7 lands after the call plus one nop;
 *      that is the +8 bytes. The pointer copy is probably scheduled
 *      before the $a3 setup in retail (sched1 order of the copy).
 *  (3) Progress increment: retail address in $a0 and byte in $v1; ours
 *      $v1/$a2 (local-alloc).
 * The other declarations needed follow.
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
extern struct { u8 header[0x464]; u8 collected[0]; } D_L01_0021E4B0;
extern int D_001A79F0;
extern unsigned char D_0019B4A8[];
extern float D_L01_001A8F60[] MACRO_ADDR;
void func_L01_003BC540(char *obj)
{
    float delta[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float dimensions[4] __attribute__((aligned(16)));
    char *state=*(char **)(obj+0x68), *hit,*piece;
    float step,scale,t;
    int i,j,byte;
    float distance;
    if(*(unsigned char *)(obj+0x20)==0) {
        *(float *)(obj+0x2C)*=func_002A7878(0.8f,1.1f);
        if(*(unsigned char *)(obj+0xB0)!=255) {
            if(D_L01_0021E4B0.collected[*(short *)(obj+0xB2)]) goto remove_initial;
            byte=D_0019B4A8[(*(short *)(obj+0xB2)>>1)+(D_001A79F0<<10)];
            if(*(short *)(obj+0xB2)&1) {
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
        qcopy(position,obj+0xF0);
        *(BC540Quad *)rotation=0;
        rotation[1]=-1.3790000f; rotation[2]=0.778f; rotation[3]=0.3f;
        func_002E5CF8(0,0,obj,position);
        for(i=0;i<4;i++) {
            func_0029FCC0(obj,i,delta);
            position[2]=func_002A7940();
            for(j=2;j>=0;j--) {
                piece=func_L01_003BCA38(obj,0xA28,delta,position,0,1,D_L01_001A8F60,D_L01_001A8F60,rotation,0.0f);
                *(float *)(piece+0x2C)*=scale;
                position[2]=func_00283B98(position[2],2.0943954f);
            }
            scale*=0.85f;
        }
        *(BC540Quad *)dimensions=0;
        dimensions[0]=0.175f;dimensions[1]=0.136f;dimensions[2]=-0.691f;dimensions[3]=0.05f;
        func_0029FCC0(obj,4,delta);
        qcopy(position,obj+0xF0);
        for(j=2;j>=0;j--) {
            piece=func_L01_003BCA38(obj,0xA27,delta,position,0,1,D_L01_001A8F60,D_L01_001A8F60,dimensions,0.0f);
            *(float *)(piece+0x2C)*=step;
            position[2]=func_00283B98(position[2],2.0943954f);
        }
        func_L00_00326620(obj,0xA29,0);
        func_002A6C58(obj,0,3);
        if(*(short *)(obj+0xB2)&1) {
            byte=(*(short *)(obj+0xB2)>>1)+(D_001A79F0<<10);
            if(((D_0019B4A8[byte]>>4)&7)!=7) D_0019B4A8[byte]+=16;
        } else {
            byte=(*(short *)(obj+0xB2)>>1)+(D_001A79F0<<10);
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
