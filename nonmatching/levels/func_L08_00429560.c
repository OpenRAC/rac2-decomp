/* Current retained result, 1 November 2026: 2440/2440 bytes, not exact. Remove all twelve z0..z11 dummy
 * declarations; they existed only to change pseudo numbering. Keep the real buffers and locals. The
 * previous spill-slot arrangement is not creditable without an evidenced source form.
 * Not a functional-port qualification or a complete matching-build result.
 * Profile: -O2 -G8 -ffunction-sections -g -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-ti-barrier -frac2-hazard-labels.
 * Earlier measurements below remain historical where superseded by this note.
 */
/* opus-1 (Claude Opus 5.5, xhigh), task v1950, USA v1.01: 2440/2440 bytes, 0/1 places
 * (check.py: "instruction at +0x68 differs"); 302 cdiff rows differ, 271 excluding call
 * relocations.  Previous best (sol-high) was 2444 bytes / 450 rows.
 * Profile (own unit, e.g. src/levels/08_tabora/L08_00429560.c + cflags line):
 *   -O2 -G8 -ffunction-sections -g -frac2-qcopy -frac2-qcopy-barrier
 *   -frac2-zero-ti-barrier -frac2-hazard-labels
 * (-frac2-hazard-labels: retail's .p2align nops before both loop heads.)
 *
 * Now matching: frame/save slots; every spill slot 0xB0..0xD0; entry `sll v0,s0,1`
 * after the first call; GPR roles s0..s7/fp in both loops; f24 (1.0) / f25 (spacing);
 * loop 2 keeps 1.0 inside the loop and shares it with velocity and the first effect.
 *
 * What fixed what (all measured):
 *  - Spill slots: spilled pseudos take slots in pseudo order.  The PRE regs for the
 *    sp+N addresses hash as C+N and (ashift index k) as C+R+11+k (R = pseudo number
 *    of the index register).  Retail's order (enddelta, end before idx*16, idx*64)
 *    needs R >= 114, so `index` is a late-declared copy of the parameter.  The twelve
 *    z0..z11 dummies only push R to 120: NOT acceptable as-is; find the real locals
 *    (or block) that number the index copy >= 114.
 *  - first/second: `second=index*2+1; first=index*2;` makes index*2 a short temp that
 *    crosses no call, so sched1 cannot hoist it above func_00282CF0.  first/second must
 *    stay SImode pseudos: an s32[2] array is BLKmode and rounds to 16 bytes, which
 *    moves the spill area to 0xC0.
 *  - Separate counters i (s2) / k (s3), and a separate `light` for the light index:
 *    reusing i there gave i hard-reg preferences s0..s2, which pushed p out of pass 0.
 *  - loop.c: the effective hoisting threshold drops with each movable moved.  In the
 *    -frerun-loop-opt pass, loop 2 has 49 insns and 5 constants (0.9948, 0.20944,
 *    0.5, 0.3, 1.0), so all are hoisted and 1.0 becomes a copy of loop 1's register
 *    (wrong).  `a=t*0.99483776f;` delays the &D_L08_001B39C0[index] add past pass 1:
 *    50 insns, 6 movables, so 1.0 stays in the loop (as retail does) but 0.3 does too.
 *    Retail = this with 49 insns (or the plain form with 50).  Find the one natural
 *    extra/missing insn in loop 2.
 *
 * Still differs: (1) loop 2's 0.3 (retail hoists it as mov.s f29,f27, which then
 * shifts f27/f28/f29 in loop 1); (2) entry scheduling and temp registers before
 * func_00282CF0 (retail: idx*16 in v1, idx*64 in v0); (3) init-loop temp registers
 * (retail loads second (0xB4) first; rows in a0/a1, 320 in a0, base in v1);
 * (4) assorted v0/v1/a0/a1 temp choices and sched2 order.
 * cse1 stops at NOTE_INSN_LOOP_END, so the post-loop 1.0 sharing comes from cse2.
 * A do-while loop 2 made no difference.
 * Required declarations and common.h helpers are below.
 */
#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
extern s32 func_L02_002F1658(void);
extern f32 D_L08_001B3A40[3][4],D_L08_002603E0[3][4][4],D_L08_002604A0[6][20][4];
extern s32 D_L08_001B39A0[3] MACRO_ADDR,D_L08_001B3A30[3] MACRO_ADDR,D_L08_001B3A10[3] MACRO_ADDR,D_L08_001B3A00[3] MACRO_ADDR;
extern s32 D_L08_001B39E0[3] MACRO_ADDR,D_L08_001B39F0[3] MACRO_ADDR;
extern f32 D_L08_001B39B0[3] MACRO_ADDR,D_L08_001B39C0[3] MACRO_ADDR,D_L08_001B39D0[3] MACRO_ADDR,D_L08_001B3A70[3][4];
extern f32 D_0018A0E0[],D_L08_001A8F20[];
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
void func_L08_00429560(s32 unused,s32 slot) {
    f32 delta[4],point[4],step[4],basis[4][4],enddelta[4],end[4],velocity[4],temp[4];
    s32 first,second,i,k,light;
    f32 spacing,previous,advance,height,half,angleStep,t,weight,a,b,c,r;
    f32 (*p)[4],(*q)[4];
    char *effect,*data,*owner;
    s32 index;
    index=slot;
    if(!func_L02_002F1658()) return;
    func_00282CF0(delta,D_L08_001B3A40[index],D_L08_002603E0[index][3]);
    second=index*2+1;first=index*2;
    spacing=func_00282DF0(delta)*0.05f;
    if(D_L08_001B39A0[index]==2){

        D_L08_001B39A0[index]=3;
        { s32 j; for(j=0;j<20;j++){
            D_L08_002604A0[first][j][1]=D_L08_002604A0[first][j][2]=0;
            D_L08_002604A0[first][j][3]=1;D_L08_002604A0[first][j][0]=spacing*(f32)j;
            D_L08_002604A0[second][j][0]=D_L08_002604A0[first][j][0];
            D_L08_002604A0[second][j][1]=D_L08_002604A0[second][j][2]=0;D_L08_002604A0[second][j][3]=1;
        }}
    }
    D_L08_001B39B0[index]=func_00283B98(D_L08_001B39B0[index],0.17453295f);
    D_L08_001B39C0[index]=func_00283BE0(D_L08_001B39C0[index],0.80285156f);
    D_L08_001B39D0[index]=func_00283B98(D_L08_001B39D0[index],0.05236f);
    *(Quadword *)(point)=*(Quadword *)(D_L08_002603E0[index][3]);
    func_00282F20(step,delta,spacing);
    previous=0;advance=0;
    angleStep=(360.0f/(func_00283CE0(20)*0.5f))*0.017453294f;
    { f32 (*p)[4]=D_L08_002604A0[first];
    f32 t;
    for(i=0;i<19;i++){
        half=(advance+spacing)*0.5f;height=0;
        if(i>0){
            height=func_002A89A8(point,0,0.5f)+D_L08_001B1D24;
            owner=D_00189E20.owner;
            if(owner && D_L08_001BFF40.owner==owner) height=*(f32 *)(owner+0x18);
            height=point[2]-height;
            if(previous+half<height)height=previous+half;
            else if(height>0)height=(height+previous)*0.5f;
            advance=height-previous;previous=height;
        }
        func_00282CC0(point,point,step);
        t=(f32)i;
        weight=(func_00283CE0(i)/func_00283CE0(20))*0.3f+0.1f;
        a=func_002ABB18(D_L08_001B39B0[index]+t*angleStep);
        weight=weight*func_00283198(a);
        (*p)[1]=0;(*p)[3]=1;(*p)[0]=spacing*t;(*p)[2]=weight-height;p++;
    }
    }
    *(Quadword *)(basis[3])=*(Quadword *)(D_L08_002603E0[index][3]);
    func_00282CF0(enddelta,D_L08_001B3A40[index],basis[3]);
    func_00282F20(basis[0],enddelta,1.0f);
    func_00282DD8(basis[1],basis[0],D_0018A0E0);
    func_00282F20(basis[1],basis[1],-1.0f);
    func_00282DD8(basis[2],basis[1],basis[0]);
    func_002830C0(end,D_L08_002604A0[first][18],basis);
    *(Quadword *)(D_L08_001B3A70[index])=*(Quadword *)(end);
    { f32 (*p)[4]=D_L08_002604A0[second];

    f32 t,a;
    for(k=0;k<19;k++){
        t=(f32)k;(*p)[2]=0;
        a=t*0.99483776f;
        a=func_002ABB18(D_L08_001B39C0[index]+a);
        b=func_002ABB18(D_L08_001B39D0[index]+t*0.20944f);
        b=func_00283198(b)*0.5f;
        c=func_00283198(a);
        r=func_002A78D8(0,0.2f);
        (*p)[2]=D_L08_002604A0[first][k][2]+b*c+r;
        (*p)[1]=func_00283180(a)*0.3f;(*p)[3]=1;(*p)[0]=spacing*t;
        p++;
    }
    }
    r=func_002A7878(0.03f,0.12f);
    *(Quadword *)velocity=0;velocity[0]=1;velocity[3]=1;
    velocity[1]=func_002A7878(-1,1);velocity[2]=func_002A7878(-1,1);
    func_00282F20(velocity,velocity,r);
    func_00283098(velocity,velocity,D_L08_002603E0[index]);
    func_L08_0034A078(D_L08_002603E0[index][3],velocity,127,D_L08_001B3A30[index]);
    if(!func_002A77E0(3)){
        func_00282D30(temp,D_L08_002603E0[index],0.3f);
        func_00282CC0(temp,temp,D_L08_002603E0[index][3]);
        effect=func_L08_0034A078(temp,D_L08_001A8F20,127,D_L08_001B3A30[index]);
        if(effect){
            *(s16 *)(effect+10)=4;*(f32 *)(effect+12)=120000.0f;data=effect+32;
            *(f32 *)(data+16)=1.0f/func_00283CE0(4);*(s32 *)(data+24)=0x7F7F7F;
            if(D_L08_001B3A10[index]==1)*(s16 *)(data+22)=1;
        }
    }
    r=func_002A7878(0.01f,0.05f);
    func_002A7988(velocity,0.01f,0.05f);
    func_L08_0034A078(end,velocity,127,D_L08_001B3A30[index]);
    if(!func_002A77E0(3)){
        effect=func_L08_0034A078(end,D_L08_001A8F20,127,D_L08_001B3A30[index]);
        if(effect){
            *(s16 *)(effect+10)=4;*(f32 *)(effect+12)=120000.0f;data=effect+32;
            *(f32 *)(data+16)=1.0f/func_00283CE0(4);*(s32 *)(data+24)=0x7F7F7F;
            if(D_L08_001B3A10[index]==1)*(s16 *)(data+22)=2;
        }
    }
    if(D_L08_001B3A00[index]){
        if(D_L08_001B3A00[index]&1){
            *(Quadword *)(temp)=*(Quadword *)(D_L08_002603E0[index][3]);temp[2]-=0.25f;
            if(D_L08_001B39E0[index]==-1)D_L08_001B39E0[index]=func_L00_002FCF18(temp,D_L08_001B1D20,0,2,1,2);
            light=D_L08_001B39E0[index];
            if(light>=0){ data=D_L08_001C7C80+light*32;*(Quadword *)(data+16)=*(Quadword *)(temp);*(f32 *)(data+28)=D_L08_001B1D20; }
        }
        if(D_L08_001B3A00[index]&2){
            end[2]+=0.5f;
            if(D_L08_001B39F0[index]==-1)D_L08_001B39F0[index]=func_L00_002FCF18(end,D_L08_001B1D20,0,2,1,2);
            light=D_L08_001B39F0[index];
            if(light>=0){ data=D_L08_001C7C80+light*32;*(Quadword *)(data+16)=*(Quadword *)(end);*(f32 *)(data+28)=D_L08_001B1D20; }
        }
    }
}
