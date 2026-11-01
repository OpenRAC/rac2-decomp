/* Tier: sol-high. USA v1.01, Todano only.
 * Best check: 1420/1420 bytes, 0 of 1 places match; five instruction positions
 * differ after allowing for relocation immediates. Profile: isolated -g8.c,
 * -O2 -G8 -ffunction-sections -g. No linked build was run.
 * Remaining at 0x00300504..0x00300518: the callback jal has the state-base
 * addiu in its delay slot instead of the callback-address addiu; the mode
 * load/constant use v1/v0 instead of v0/v1 and are scheduled in reverse order.
 * Improvements over sol-low: incomplete sda arrays retain absolute macro loads
 * without scalar-address hoists; distinct loop counters match retail allocation;
 * advancing entries before the final emission matches the loop scheduling;
 * one velocity pointer used in both effect loops fixes its initialization order;
 * moving fade initialization before the vector fixes FP allocation in case 0x8D2.
 * Tied: reversed comparison, single-case switch, positive guard, and a named
 * expected-mode constant. -fno-force-mem was also object-neutral. Moving the
 * state assignment after the guard fixes the callback slot and mode registers
 * but uses a0 instead of s0 for the base and changes bnel to bne. Loading mode
 * into a local before assigning the state pointer adds a move. Reusing a separate
 * context pointer for state and scene worsens allocation. An early velocity
 * pointer used only in the emitter loop adds a duplicate pointer and eight bytes.
 * Opus G2, 1 November 2026: the five rows are one cause. sched2 issues the $s0 set in the second
 * slot of the cycle before the call, and reorg then fills the call's slot with it. Retail keeps it
 * after the call, so the a0 low half fills the slot. Int-returning callee: tied. Nothing else
 * competes for the slot, unlike func_00334A88; it needs a barrier or a real dependence.
 * Next useful investigation: why the mode-check pointer's allocation and the
 * post-call scheduling differ together; equivalent comparisons have tied.
 * All required declarations are below. To reproduce, compile this alone in
 * L12_00300410-g8.c and remove the original INCLUDE_ASM marker.
 */
#include "common.h"
typedef unsigned int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;
typedef struct { char p[0x30]; int mode, event; char p2[0xC]; short count; char p3[0x146]; char *objects[5]; char *emitters[2]; } State;
extern State D_L12_001BDB00;
typedef struct { char p[0x140]; V pos; char p2[0x1C]; int flag; char p3[0x10]; float fade; int p4; int time; char p5[0x1E4]; V rot; } Scene;
extern Scene D_L12_001B9CC0;
extern char *D_L12_001B2E9C[] __attribute__((sda)), *D_L12_001B2EA4[] __attribute__((sda));
extern int D_L12_001B29C8[] __attribute__((sda));
extern float D_L12_001A93E0 __attribute__((sda));
extern float D_L12_001A93E4[] __attribute__((sda));
extern int D_L12_001A93E8 __attribute__((sda)), D_L12_001A9400 __attribute__((sda));
extern int D_L12_001A93EC[] __attribute__((sda)), D_L12_001A93F0[] __attribute__((sda)), D_L12_001A93F4[] __attribute__((sda));
extern int D_L12_001A93F8[] __attribute__((sda)), D_L12_001A93FC[] __attribute__((sda)), D_L12_001A9408[] __attribute__((sda)), D_L12_001A9404[] __attribute__((sda));
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(void *,void *,unsigned int,unsigned int,float);
extern void func_L00_002E6CF0(void (*)(void),void *);
extern void func_L12_00300138(void);
extern void func_0029FCC0(void *,int,void *);
extern void func_00282D08(void *,void *,void *,float);
extern float func_002A7878(float,float);
extern int func_002A7820(int,int);
extern void func_002BAE50(void *,void *,unsigned int,int,int,int,int,int);
extern void func_0029F338(void *);
extern void func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_0032DA58(void *,void *,void *,float);
extern void func_00283098(void *,void *,void *);
extern void func_002ACB48(void *,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_L00_0033FFB8(void *,void *,int);
void func_L12_00300410(void) {
    V a,b,c,d;
    V *velocity;
    int i, j, k;
    char *obj;
    #define state ((char *)&D_L12_001BDB00)
    char **entries;
    func_L00_002FC980();
    for(i=0;i<D_L12_001BDB00.count;i++) {
        obj=D_L12_001BDB00.objects[i];
        if(obj && *(short *)(obj+0xAA)==0xE29) *(unsigned short *)(obj+0x34)|=0x800;
        if(*(short *)(obj+0xAA)==0xD54) func_002E64A0(obj);
        if(obj && *(short *)(obj+0xAA)==0xFA0) {
            char *p=*(char **)(obj+0x68);
            if(p) func_L00_00326048(obj,p+0xC,0x80AAAAD2,0x80396464,0.061086535f);
        }
    }
    func_L00_002E6CF0(func_L12_00300138,0);
    obj=state;
    if(D_L12_001BDB00.mode!=5) return;
    entries=(char **)(obj+0x1A0);
    velocity=&c;
    for(j=1;j>=0;j--) {
        obj=*entries;
        func_0029FCC0(obj,3,&a);
        func_0029FCC0(obj,5,&b);
        func_00282D08(&a,&a,&b,0.5f);
        d.q=0;
        d.f[2]=-(func_002A7878(D_L12_001A93E0,D_L12_001A93E4[0])*0.016666668f);
        c.q=d.q;
        if(D_L12_001B29C8[0]&1)
            func_002BAE50(&a,velocity,D_L12_001A93E8,D_L12_001A93EC[0],func_002A7820(18,22),D_L12_001A9400,-10,1);
        else
            func_002BAE50(&a,velocity,D_L12_001A93F0[0],D_L12_001A93F4[0],func_002A7820(20,24),D_L12_001A9404[0],-10,1);
        entries++;
        func_002BAE50(&a,velocity,D_L12_001A93F8[0],D_L12_001A93FC[0],func_002A7820(10,15),D_L12_001A9408[0],-10,1);
    }
    switch(D_L12_001BDB00.event) {
    case 2:
        for(obj=D_L12_001B2E9C[0];obj<D_L12_001B2EA4[0];obj+=0x100) {
            int cls=*(short *)(obj+0xAA);
            if(cls==0x11EB || cls==0x1F5 || cls==0x326) func_0029F338(obj);
        }
        break;
    case 0x603:
        D_L12_001B9CC0.fade=0.5f;
        D_L12_001B9CC0.time=45;
        D_L12_001B9CC0.flag=0;
        func_0029FCC0(*(void **)(state+0x19C),0,&a);
        func_0032C700(&a,1,25,20,20,20,45,1,0.666f,20.0f,1,1,0,0);
        break;
    case 0x6F5:
        D_L12_001B9CC0.fade=0.5f;
        D_L12_001B9CC0.time=60;
        D_L12_001B9CC0.flag=0;
        func_00282F20(&a,&D_L12_001B9CC0.rot,4.0f);
        func_00282CC0(&a,&a,&D_L12_001B9CC0.pos);
        func_00282F20(&b,&D_L12_001B9CC0.rot,-1.0f);
        func_0032DA58(*(void **)(state+0x194),&a,&b,0.0f);
        break;
    case 0x8D2:
        D_L12_001B9CC0.fade=0.5f;
        a.q=0; a.f[0]=4.0f; a.f[1]=-1.0f; a.f[2]=1.0f;
        D_L12_001B9CC0.time=45;
        D_L12_001B9CC0.flag=0;
        func_00283098(&a,&a,&D_L12_001B9CC0.rot);
        func_00282CC0(&a,&a,&D_L12_001B9CC0.pos);
        func_0032C700(&a,1,25,20,20,20,45,1,0.666f,20.0f,1,1,0,0);
        for(k=24;k>=0;k--) {
            qcopy(&b,&a);
            func_002ACB48(&b,0.3f);
            func_00282CF0(velocity,&b,&a);
            func_00282F20(velocity,velocity,func_002A7878(0.0f,1.0f)*0.016666668f);
            func_L00_0033FFB8(&b,velocity,300);
        }
        break;
    }
}
