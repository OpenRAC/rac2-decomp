/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * Tier: sol-high (v1110), USA v1.01.
 * Profile: -O2 -G8 -ffunction-sections, in a separate -g8.c unit.
 * Best rechecked result: 1400/1400 bytes, 0/27 places, first mismatch +0xC.
 * Reusing the vertical-dot local for the later planar dot recovers retail's
 * f21/f23 allocation. A separate scoped raw angle recovers the branch and f13
 * argument sequence; an explicit sign variable preserves both multiplies.
 * Remaining: movement/axis s4/s5 swap, camera-address setup, resident pointer
 * load scheduling, and the level-13 collision loop's rotation/layout.
 * Initializing the counter before the level guard restores total retail size,
 * but does not recover the special loop. Earlier axis initialization swaps the
 * desired GPR pair but loses the saved camera base and changes the prologue.
 * Typed movement fields and aggregate vector scratch storage tied their plain
 * forms. No forbidden source methods used; no linked build run.
 * Required declarations are included below. Next: explain the movement/axis
 * priority and the unrotated special loop without changing real references.
 */
#include "common.h"
extern char D_L00_001B8E20[], D_L00_001BF220[], D_L00_001BF230[];
extern int D_001A79F0;
extern char *D_0018C0B0;
extern float D_L00_001B14E8 __attribute__((sda)), D_L00_001B14EC __attribute__((sda));
extern float D_L00_001B14F0 __attribute__((sda)), D_L00_001B14F4 __attribute__((sda));
extern void func_00282CC0(void *,void *,void *), func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float),func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float),func_002ACEC0(void *,void *,void *,float);
extern float func_00282DF0(void *),func_00282DB0(void *,void *),func_00282C48(float),func_002831B0(float);
extern float func_002702C8(void *,float,float,float,float,float),func_002703B0(void *,float,float,float,float,float);
extern int func_00277258(void *,int,int,float);
extern void func_L00_00425A98(char *,float *,float *);
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
void func_L00_00425CD0(char *obj)
{
    char *base=P(obj,112), *move=base+352, *pos=base+96, *camera=D_L00_001B8E20, *axis;
    char a[16],b[16],c[16],d[16],e[16],v[16],g[16],h[16],saved[16],delta[16];
    float out1,out2;
    float len1,len2,vert1,angle1,angle2,dot1,dot2,len,angle,turn;
    int changed,i;
    float ratio, sign;
    func_00282CC0(base,base+176,move);
    len1=func_00282DF0(move);
    len2=func_00282DF0(move+16);
    angle2=0.0f;
    func_L00_00425A98(obj,&out1,&out2);
    len2=func_002702C8(move+40,len2,len1,out1,out2,angle2);
    vert1=func_00282DB0(move,camera+32);
    if(func_00282C48(len1)<0.0001f) angle1=0.0f;
    else {
        ratio=vert1/len1;
        if(ratio>1.0f) ratio=1.0f;
        else if(ratio< -1.0f) ratio= -1.0f;
        angle1=func_002831B0(ratio);
    }
    axis=camera+32;
    len1=func_00282DB0(move+16,axis);
    if(func_00282C48(len2)<0.0001f) angle2=0.0f;
    else {
        ratio=len1/len2;
        if(ratio>1.0f) ratio=1.0f;
        else if(ratio< -1.0f) ratio= -1.0f;
        angle2=func_002831B0(ratio);
    }
    turn=func_002703B0(move+36,angle2,angle1,D_L00_001B14F0,D_L00_001B14F4,0.0f);
    func_00282D30(a,axis,vert1);
    func_00282CF0(b,move,a);
    func_00282D30(c,axis,len1);
    func_00282CF0(d,move+16,c);
    vert1=func_00282DB0(b,d);
    len=func_00282DF0(b);
    len*=func_00282DF0(d);
    {
        float raw;
        if(len<0.0001f) raw=0.0f;
        else raw=1.5707963705062866f-func_002831B0(vert1/len);
        angle=func_002703B0(move+32,0.0f,raw,D_L00_001B14E8,D_L00_001B14EC,0.0f);
    }
    func_00282DD8(e,d,axis);
    dot2=func_00282DB0(e,b);
    sign=-1.0f;
    if(dot2>=0.0f) sign=1.0f;
    func_002ACEC0(v,d,axis,angle*sign);
    func_00282DD8(e,axis,v);
    func_002ACEC0(v,v,e,turn);
    func_00282F20(move+16,v,len2);
    func_00282D30(g,axis,F(move,48));
    func_00282CC0(h,g,pos+96);
    func_00282CC0(obj+48,h,move+16);
    qcopy(saved,obj+48);
    changed=0;
    i=0;
    if(D_001A79F0==13 && F(D_0018C0B0,24)<120.0f) {
        for(;i<3;i++) {
            if(!func_00277258(obj+48,54,0,0.3f)) break;
            changed=1;
            qcopy(obj+48,D_L00_001BF230);
        }
    } else {
        do {
            if(!func_00277258(obj+48,54,0,0.25f)) break;
            func_00282CF0(delta,D_L00_001BF220,obj+48);
            func_00282F20(delta,delta,1.0f);
            if(func_00282C48(func_00282DB0(obj+32,delta))<=0.5f) break;
            changed=1;
            qcopy(obj+48,D_L00_001BF230);
        } while(++i<3);
    }
    if(changed) {
        func_00282CF0(delta,obj+48,saved);
        func_00282CC0(pos,pos,delta);
        func_00282CC0(pos+96,pos+96,delta);
        func_00282CC0(pos+144,pos+144,delta);
        func_00282CC0(pos+48,pos+48,delta);
    }
}
