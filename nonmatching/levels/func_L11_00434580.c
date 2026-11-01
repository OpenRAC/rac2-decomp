/* GPT-6.1 Sol high, task v0887; USA v1.01.
 * Best: 1144/1144 bytes, 0/1 places. Profile: -O2 -G8 -ffunction-sections -g.
 * Frame and saved-register set agree; object is s4 instead of s2, with the
 * position/velocity addresses correspondingly shifted. Conditional retirement
 * argument scheduling/likely branches still differ. All declarations follow.
 * Corrects the prior draft: the first age interval also installs the callback;
 * its third particle reverses the second particle's spin. Retail's first last
 * particle call branches into the second interval's shared call/hook tail.
 * Ordinary TI impact copies recover the store in the predicate-call delay slot.
 * A 16-byte MACRO_ADDR velocity declaration prevents address hoisting across
 * particle calls. Separate branch-local sizes recover f22 versus f20.
 * Explicit collision labels and a shared expiry label reach retail size, but
 * merging expiry removes an object reference and lowers its allocation priority.
 * Keeping separate expiry calls recovers the GPR allocation at 1152 bytes.
 * Next: original collision/expiry CFG and source lifetime evidence, without
 * artificial references. No linked build was run because no checker match exists.
 * 1 November 2026: the shared expiry tail copied into the guard arm takes this
 * from 54 rows to 14 (object in s2, retail's frame and order). Left: the two
 * impact branches are bnel with a0=object where retail has bnez with a0=impact
 * in the slot (reorg's simple pass, fall-through), and two mov.s/t2 orders.
 * Writing func_L11_00434F48 per arm makes the a0 load right but keeps bnel.
 */
#include "common.h"
typedef int Quad34580 __attribute__((mode(TI)));
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_00282E48(void *,void *);
extern void func_002A8C00(void *,void *,int,void *,float);
extern int func_002761F8(void *,void *,int,void *,void *);
extern int func_002B38B8(void *);
extern void func_L11_00434F48(float *,int);
extern void func_L00_003294F0(void *,int);
extern void func_0029F338(void *);
extern float func_002A7878(float,float);
extern int func_002A7820(int,int);
extern void *func_002C2210(void *,int,float,float,unsigned int,int,int,void *,int,float);
extern void func_L00_002E6EF8(void *,void *);
extern char D_L11_001C0D20[];
extern char D_L11_001A8F20[16] MACRO_ADDR;
extern unsigned int D_L11_001B11E0 __attribute__((sda));
extern unsigned int D_L11_001B11E8 __attribute__((sda));
extern unsigned int D_L11_001B11F0 __attribute__((sda));
extern unsigned int D_L11_001B11F8 __attribute__((sda));
extern void func_L11_00434AA8(char *);
void func_L11_00434580(char *obj) {
    float vel[4]; char collision[48]; float pos[4],pos2[4];
    char *st=*(char **)(obj+0x68);
    float scale=*(float *)(st+0x3C);
    int count;
    float *impact;
    *(float *)(st+0x38)+=1;
    if (*(float *)(st+0x38)<25) {
        float size; int sign;
        *(float *)(st+0x34)+=1;
        func_00282F20(st+0x10,st+0x20,*(float *)(st+0x34));
        func_00282F20(vel,st+0x20,0.06666667f);
        func_002A8C00(collision,obj,0x10001,vel,scale);
        *(unsigned short *)(collision+0x1A)=*(unsigned short *)(obj+0xAA);
        func_00282CC0(st+0x10,st,st+0x10);
        if(func_002761F8(st,st+0x10,0,obj,collision)) {
            impact=(float *)D_L11_001C0D20;
            *(Quad34580 *)(st+0x10)=*(Quad34580 *)impact;
            if(!func_002B38B8(obj)) { count=6; goto burst; }
            {
                func_L00_003294F0(obj,1); func_0029F338(obj); return;
}
        }
        size=func_002A7878(1,4);
        sign=func_002A7820(25,35); if(!sign) sign--;
        qcopy(pos,st+0x10); pos[2]-=0.1f;
        func_002C2210(pos,15,size*0.3f,size,D_L11_001B11E0,0,sign,D_L11_001A8F20,0,0);
        sign = -sign;
        func_002C2210(st,10,size*0.3f,size,D_L11_001B11E8,0,sign,D_L11_001A8F20,0,0);
        func_002C2210(st,10,size*0.04f,size*0.4f,D_L11_001B11F0,1,-sign,D_L11_001A8F20,0,0);
        func_L00_002E6EF8(func_L11_00434AA8,obj);
        return;
    } else if (*(float *)(st+0x38)>=25 && *(float *)(st+0x38)<34) {
        if(func_00282E48(st,st+0x10)>1) {
            float size; int sign;
            *(float *)(st+0x34)+=1;
            func_00282F20(st+0x10,st+0x20,*(float *)(st+0x34));
            func_00282F20(vel,st+0x20,0.06666667f);
            func_002A8C00(collision,obj,0x10001,vel,scale);
            *(unsigned short *)(collision+0x1A)=*(unsigned short *)(obj+0xAA);
            func_00282CC0(st+0x10,st,st+0x10);
            if(func_002761F8(st,st+0x10,0,obj,collision)) {
                impact=(float *)D_L11_001C0D20;
            *(Quad34580 *)(st+0x10)=*(Quad34580 *)impact;
                if(!func_002B38B8(obj)) {
                    count=3;
                burst:
                    func_L11_00434F48(impact,count);
                }
                func_L00_003294F0(obj,1); func_0029F338(obj); return;
            }
            func_00282F20(pos,st+0x20,1.66666675f);
            func_00282CC0(st,st,pos);
            size=func_002A7878(1,4);
            sign=func_002A7820(25,35); if(!sign) sign--;
            qcopy(pos2,st+0x10); pos2[2]-=0.1f;
            func_002C2210(pos2,15,size*0.3f,size,D_L11_001B11E0,0,sign,D_L11_001A8F20,0,0);
            func_002C2210(pos2,20,size*0.4f,size*0.2f,D_L11_001B11F8,1,-sign,D_L11_001A8F20,0,0);
            func_L00_002E6EF8(func_L11_00434AA8,obj);
            return;

        } else goto expire;
    } else goto expire;
expire:
    func_0029F338(obj);
}
