#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
extern s32 func_L02_002F1658(void);
extern f32 D_L08_002603E0[3][4][4],D_L08_002604A0[6][20][4];
extern f32 D_L08_001B3A40[3][4] MACRO_ADDR;
extern s32 D_L08_001B39A0[3] MACRO_ADDR,D_L08_001B3A30[3] MACRO_ADDR,D_L08_001B3A10[3] MACRO_ADDR,D_L08_001B3A00[3] MACRO_ADDR;
extern s32 D_L08_001B39E0[3] MACRO_ADDR,D_L08_001B39F0[3] MACRO_ADDR;
extern f32 D_L08_001B39B0[3] MACRO_ADDR,D_L08_001B39C0[3] MACRO_ADDR,D_L08_001B39D0[3] MACRO_ADDR,D_L08_001B3A70[3][4] MACRO_ADDR;
extern f32 D_0018A0E0[];
extern f32 D_L08_001A8F20[] MACRO_ADDR;
typedef struct { char pad[0x1830]; char *owner; } BeamOwnerGlobals;
typedef struct { char pad[0x18]; char *owner; } BeamOwnerState;
extern BeamOwnerGlobals D_00189E20;
extern BeamOwnerState D_L08_001BFF40;
extern char D_L08_001C7C80[];
extern f32 D_L08_001B1D24 __attribute__((sda)),D_L08_001B1D20 __attribute__((sda));
extern void func_00282CF0(void *,void *,void *),func_00282CC0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *),func_002830C0(void *,void *,void *);
extern void func_00283098(void *,void *,void *),func_00282F20(void *,void *,f32),func_00282D30(void *,void *,f32);
extern f32 func_00282DF0(void *),func_00283B98(f32,f32),func_00283BE0(f32,f32),func_00283CE0(s32);
extern f32 func_002A89A8(void *,s32,f32),func_002ABB18(f32),func_00283198(f32),func_00283180(f32);
extern f32 func_002A7878(f32,f32),func_002A78D8(f32,f32);
extern s32 func_002A77E0(s32);
extern void func_002A7988(void *,f32,f32);
extern char *func_L08_0034A078(void *,void *,s32,s32);
extern s32 func_L00_002FCF18(void *,f32,f32,f32,f32,f32);
/* Per-frame update of one beam slot: lays out the two 20-point strips between the slot's ends
   (a sine wave and a noisy one on top of it), spawns sparks at both ends and keeps the two
   lights at the ends.  RAC1's counterpart is update_slot_panes_and_effects.

   The wording carries the allocation:
   - index is the last top-level local: PRE sorts (index<<k) after the stack addresses only when
     its pseudo number is at least 114, which puts &end before index*16 and index*64 in the
     spill slots.
   - first and second are set before the first call: sched1 lets them drift past it.
   - In loop 1 a row pointer indexed by i gives one combined giv, and loop.c emits its %hi/%lo
     after gcse, so the base stays a local pair instead of the PRE register.
   - In loop 2 the row element is stored and then updated: that store lasts until flow2 and
     makes the 50 insns that keep 1.0 in the loop while 0.3 is hoisted. */
void func_L08_00429560(s32 unused,s32 slot) {
    f32 delta[4],point[4],step[4],basis[4][4],enddelta[4],end[4],velocity[4],temp[4];
    s32 first,second,i,j,k,light;
    f32 spacing,previous,advance,height,half,angleStep,weight,wave,twist,sway,b,c,r,t,tn;
    char *effect,*data,*owner,*s,*s2;
    f32 (*p)[4],(*q)[4];
    s32 index=slot;

    if(!func_L02_002F1658()) return;
    first=index*2;
    second=first+1;
    func_00282CF0(delta,D_L08_001B3A40[index],D_L08_002603E0[index][3]);
    spacing=func_00282DF0(delta)*0.05f;
    if(D_L08_001B39A0[index]==2){
        D_L08_001B39A0[index]=3;
        for(j=0;j<20;j++){
            D_L08_002604A0[first][j][1]=D_L08_002604A0[first][j][2]=0;
            D_L08_002604A0[first][j][3]=1;
            D_L08_002604A0[first][j][0]=spacing*(f32)j;
            D_L08_002604A0[second][j][0]=D_L08_002604A0[first][j][0];
            D_L08_002604A0[second][j][1]=D_L08_002604A0[second][j][2]=0;
            D_L08_002604A0[second][j][3]=1;
        }
    }
    D_L08_001B39B0[index]=func_00283B98(D_L08_001B39B0[index],0.17453295f);
    D_L08_001B39C0[index]=func_00283BE0(D_L08_001B39C0[index],0.80285156f);
    D_L08_001B39D0[index]=func_00283B98(D_L08_001B39D0[index],0.05236f);
    *(Quadword *)(point)=*(Quadword *)(D_L08_002603E0[index][3]);
    func_00282F20(step,delta,spacing);
    previous=0;
    advance=0;
    angleStep=(360.0f/(func_00283CE0(20)*0.5f))*0.017453294f;
    for(i=0;i<19;i++){
        half=(advance+spacing)*0.5f;
        height=0;
        if(i>0){
            height=func_002A89A8(point,0,0.5f)+D_L08_001B1D24;
            owner=D_00189E20.owner;
            if(owner && D_L08_001BFF40.owner==owner) height=*(f32 *)(owner+0x18);
            height=point[2]-height;
            if(previous+half<height) height=previous+half;
            else if(height>0) height=(height+previous)*0.5f;
            advance=height-previous;
            previous=height;
        }
        func_00282CC0(point,point,step);
        t=(f32)i;
        weight=(func_00283CE0(i)/func_00283CE0(20))*0.3f+0.1f;
        wave=func_002ABB18(D_L08_001B39B0[index]+t*angleStep);
        weight=weight*func_00283198(wave);
        p=D_L08_002604A0[first];
        p[i][1]=0;
        p[i][3]=1;
        p[i][0]=spacing*t;
        p[i][2]=weight-height;
    }
    qcopy_nc(basis[3],D_L08_002603E0[index][3]);
    func_00282CF0(enddelta,D_L08_001B3A40[index],basis[3]);
    func_00282F20(basis[0],enddelta,1.0f);
    func_00282DD8(basis[1],basis[0],D_0018A0E0);
    func_00282F20(basis[1],basis[1],-1.0f);
    func_00282DD8(basis[2],basis[1],basis[0]);
    func_002830C0(end,D_L08_002604A0[first][18],basis);
    *(Quadword *)(D_L08_001B3A70[index])=*(Quadword *)(end);
    q=D_L08_002604A0[second];
    for(k=0;k<19;k++){
        tn=(f32)k;
        (*q)[2]=0;
        twist=func_002ABB18(D_L08_001B39C0[index]+tn*0.99483776f);
        sway=func_002ABB18(D_L08_001B39D0[index]+tn*0.20944f);
        b=func_00283198(sway)*0.5f;
        c=func_00283198(twist);
        r=func_002A78D8(0,0.2f);
        (*q)[2]=D_L08_002604A0[first][k][2];
        (*q)[2]=(*q)[2]+b*c+r;
        (*q)[1]=func_00283180(twist)*0.3f;
        (*q)[3]=1;
        (*q)[0]=spacing*tn;
        q++;
    }
    r=func_002A7878(0.03f,0.12f);
    *(Quadword *)velocity=0;
    velocity[0]=1;
    velocity[3]=1;
    velocity[1]=func_002A7878(-1,1);
    velocity[2]=func_002A7878(-1,1);
    func_00282F20(velocity,velocity,r);
    func_00283098(velocity,velocity,D_L08_002603E0[index]);
    func_L08_0034A078(D_L08_002603E0[index][3],velocity,127,D_L08_001B3A30[index]);
    if(!func_002A77E0(3)){
        func_00282D30(temp,D_L08_002603E0[index],0.3f);
        func_00282CC0(temp,temp,D_L08_002603E0[index][3]);
        effect=func_L08_0034A078(temp,D_L08_001A8F20,127,D_L08_001B3A30[index]);
        if(effect){
            *(s16 *)(effect+10)=4;
            *(f32 *)(effect+12)=120000.0f;
            data=effect+32;
            *(f32 *)(data+16)=1.0f/func_00283CE0(4);
            *(s32 *)(data+24)=0x7F7F7F;
            if(D_L08_001B3A10[index]==1) *(s16 *)(data+22)=1;
        }
    }
    func_002A7878(0.01f,0.05f);
    func_002A7988(velocity,0.01f,0.05f);
    func_L08_0034A078(end,velocity,127,D_L08_001B3A30[index]);
    if(!func_002A77E0(3)){
        effect=func_L08_0034A078(end,D_L08_001A8F20,127,D_L08_001B3A30[index]);
        if(effect){
            *(s16 *)(effect+10)=4;
            *(f32 *)(effect+12)=120000.0f;
            data=effect+32;
            *(f32 *)(data+16)=1.0f/func_00283CE0(4);
            *(s32 *)(data+24)=0x7F7F7F;
            if(D_L08_001B3A10[index]==1) *(s16 *)(data+22)=2;
        }
    }
    if(D_L08_001B3A00[index]){
        if(D_L08_001B3A00[index]&1){
            *(Quadword *)(temp)=*(Quadword *)(D_L08_002603E0[index][3]);
            temp[2]-=0.25f;
            if(D_L08_001B39E0[index]==-1) D_L08_001B39E0[index]=func_L00_002FCF18(temp,D_L08_001B1D20,0,2,1,2);
            light=D_L08_001B39E0[index];
            if(light>=0){
                s=D_L08_001C7C80+light*32;
                *(Quadword *)(s+16)=*(Quadword *)(temp);
                *(f32 *)(s+28)=D_L08_001B1D20;
            }
        }
        if(D_L08_001B3A00[index]&2){
            end[2]+=0.5f;
            if(D_L08_001B39F0[index]==-1) D_L08_001B39F0[index]=func_L00_002FCF18(end,D_L08_001B1D20,0,2,1,2);
            light=D_L08_001B39F0[index];
            if(light>=0){
                s2=D_L08_001C7C80+light*32;
                *(Quadword *)(s2+16)=*(Quadword *)(end);
                *(f32 *)(s2+28)=D_L08_001B1D20;
            }
        }
    }
}
