/* GPT-6.1 Sol high, task v1402, USA v1.01 retained near miss.
 * Profile: -O2 -G8 -ffunction-sections -g -frac2-zero-ti-por.
 * Best/final check.py: 2272/2272 bytes, 0 of 4 places match.
 * All four placements have 18 non-relocation instruction differences:
 * +0x33c..348, +0x418..424, +0x4f8..504, +0x690..69c move por before
 * the negative float constant rather than after it; +0x56c/570 use v0
 * instead of v1 for the triple-shot upgrade condition.
 * Corrected the earlier draft's weapon-7 control flow: a negative index or
 * empty ammo takes the sound-stop/recharge else path, rather than skipping
 * it. Scoped sound pointers with integer byte-offset arithmetic recover
 * retail's a0/v1 address results and ordinary bne (all weapon-7 text agrees).
 * An inline vector initializer and struct/TImode-cast clear tied the union
 * wording. -fno-sched-interblock tied; -fno-schedule-insns grew to 2280 bytes
 * and introduced earlier differences. Stopped the tied clear approach.
 * Earlier b1395 trials: -frac2-zero-ti-barrier first differed at +0x338;
 * -mno-split-addresses grew to 2300; a local z initializer did not help.
 * Next useful work must explain the zero-producer/FP-constant scheduling
 * and upgrade-condition allocation, rather than repeat equivalent clears.
 * All declarations are below. Relocation binding and linked validation
 * have not been reached; equal size and the diagnostic count are no match.
 *
 * closer D, 1 November 2026: 10 words. The `por` sits after the negative constant at the four 0($sp)
 * clears; a local 1.0f, no z local and storing word 3 first tie or worsen it (10, 10, 28, 28).
 */
#include "common.h"
typedef unsigned int ShotQuad __attribute__((mode(TI)));
typedef union { ShotQuad q; float f[4]; } ShotVector;
extern int D_L05_001B2048, D_00138320[], D_L05_002A1940[];
typedef struct { int upgrade; char pad[12]; int maximum, ammo; char tail[16]; } WeaponSlot;
extern WeaponSlot D_L05_002A1800[];
extern char D_00188660[],D_L05_002B8770[];
extern float D_L05_001B1A9C __attribute__((sda)), D_L05_001B1B70 __attribute__((sda));
extern unsigned short D_L05_001B1AA0 __attribute__((sda)),D_L05_001B1AA4 __attribute__((sda)),D_L05_001B1AA8 __attribute__((sda));
extern int D_L05_001B1AAC __attribute__((sda)),D_L05_001B1AB0 __attribute__((sda)),D_L05_001B1AFC __attribute__((sda));
extern float D_L05_001B1B30 __attribute__((sda)),D_L05_001B1B40 __attribute__((sda)),D_L05_001B1B50 __attribute__((sda)),D_L05_001B1B60 __attribute__((sda));
extern int func_00282978(void *),func_00282948(void *),func_L05_0037AA88(int);
extern void func_00282CF0(void *,void *,void *),func_00282CC0(void *,void *,void *),func_00282F20(void *,void *,float),func_00283098(void *,void *,void *),func_00282D30(void *,void *,float);
extern void func_002E5CF8(int,int,void *),func_L05_0037AB18(int,int);
extern char *func_L05_00419CC8(void *,void *,float,void *,int,int,int,int,int);
extern void func_L05_003D0960(void *,void *,int,void *,int),func_L05_003979B0(void *,void *,int,void *,int),func_L05_00427090(void *,void *,int,void *,int,int),func_L05_00427988(void *,void *,int,void *,int);
extern int func_002E5DA0(int,int,void *,int),func_L00_002D6998(void *);
extern void func_002E59F8(int);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
void func_L05_00443D08(char *m,char *driver)
{
 ShotVector a,b,c,d,e,f;
 char *driverState=P(driver,0x70),*s=P(m,0x68),*shot;
 int mode,index;
 if(H(driverState,0xd8) && (D_L05_001B2048&1)) return;
 if(func_00282978(s+8) && (D_00138320[0]&0x40)) {
 H(s,8)=D_L05_001B1AA0;
 func_00282CF0(&a,s+0x20,driver+0x30);
 func_00282F20(&a,&a,D_L05_001B1A9C);
 func_00282CC0(&b,&a,driver+0x30);
 mode=D_L05_002A1940[0];
 if(mode) func_00283098(&c,&D_L05_001B1B50,m+0xc0);
 else func_00283098(&c,&D_L05_001B1B30,m+0xc0);
 func_00282CC0(&c,&c,m+0x10);
 func_00282CF0(&d,&b,&c);
 func_002E5CF8(3,0,m);
 shot=func_L05_00419CC8(m,&c,-1.0f,&d,0x2020ff,0x20207f,0,mode,0);
 if(shot) {
 char *v=P(shot,0x68); I(v,0x28)=0;
 F(v,0x10)+=F(driverState,0x30); F(v,0x14)+=F(driverState,0x34); F(v,0x18)+=F(driverState,0x38);
 if(mode) {func_00282D30(&e,m+0xd0,D_L05_001B1B70*0.01666666753590107f);func_00282CC0(v+0x10,v+0x10,&e);}
 }
 if(mode) func_00283098(&e,&D_L05_001B1B60,m+0xc0);
 else func_00283098(&e,&D_L05_001B1B40,m+0xc0);
 func_00282CC0(&e,&e,m+0x10);func_00282CF0(&d,&b,&e);
 shot=func_L05_00419CC8(m,&e,1.0f,&d,0x2020ff,0x20207f,0,mode,0);
 if(shot) {
 char *v=P(shot,0x68);I(v,0x28)=0;
 F(v,0x10)+=F(driverState,0x30);F(v,0x14)+=F(driverState,0x34);F(v,0x18)+=F(driverState,0x38);
 if(mode) {func_00282D30(&f,m+0xd0,-(D_L05_001B1B70*0.01666666753590107f));func_00282CC0(v+0x10,v+0x10,&f);}
 }
 }
 { int slot=func_L05_0037AA88(1);
 if(slot>=0 && D_L05_002A1800[slot].ammo!=0 && func_00282978(s+0xa) && (D_00138320[0]&0x20)) {
 func_L05_0037AB18(1,1);{ float z=-0.1f; a.q=0;a.f[2]=z;a.f[3]=1.0f; }
 func_00283098(&b,&a,m+0xc0);func_00282CC0(&b,&b,m+0x10);func_002E5CF8(2,0,m);
 func_L05_003D0960(&b,m+0xc0,I(s,0x18),m,D_L05_002A1800[9].upgrade);H(s,0xa)=D_L05_001B1AA4;I(s,0x218)=5;
 }
 }
 { int slot=func_L05_0037AA88(3);
 if(slot>=0 && D_L05_002A1800[slot].ammo!=0 && func_00282978(s+0xa8) && (D_00138320[0]&0x20)) {
 func_L05_0037AB18(3,1);{ float z=-0.1f; a.q=0;a.f[2]=z;a.f[3]=1.0f; }
 func_00283098(&b,&a,m+0xc0);func_00282CC0(&b,&b,m+0x10);func_002E5CF8(2,0,m);
 func_L05_003979B0(&b,m+0xc0,I(s,0x18),m,D_L05_002A1800[11].upgrade);H(s,0xa8)=D_L05_001B1AA8;I(s,0x218)=5;
 }
 }
 { int slot=func_L05_0037AA88(2);
 if(slot>=0 && D_L05_002A1800[slot].ammo!=0 && func_00282948(s+0x20c) && (D_00138320[0]&0x20)) {
 func_L05_0037AB18(2,1);{ float z=-0.2f; a.q=0;a.f[2]=z;a.f[3]=1.0f; }
 func_00283098(&b,&a,m+0xc0);func_00282CC0(&b,&b,m+0x10);func_002E5CF8(2,0,m);
 func_L05_00427090(&b,m+0xc0,I(s,0x18),m,D_L05_002A1800[10].upgrade,1);
 if(D_L05_002A1800[10].upgrade) {
 c.q=0;c.f[1]=-0.275f;c.f[3]=1.0f;func_00283098(&b,&c,m+0xc0);func_00282CC0(&b,&b,m+0x10);
 func_L05_00427090(&b,m+0xc0,I(s,0x18),m,D_L05_002A1800[10].upgrade,0);
 d.q=0;d.f[1]=0.275f;d.f[3]=1.0f;func_00283098(&b,&d,m+0xc0);func_00282CC0(&b,&b,m+0x10);
 func_L05_00427090(&b,m+0xc0,I(s,0x18),m,D_L05_002A1800[10].upgrade,0);
 }
 I(s,0x20c)=D_L05_001B1AAC;I(s,0x218)=7;
 }
 }
 { int slot=func_L05_0037AA88(4);
 if(slot>=0 && D_L05_002A1800[slot].ammo!=0 && func_00282948(s+0x210) && (D_00138320[0]&0x20)) {
 func_L05_0037AB18(4,1);{ float z=-0.1f; a.q=0;a.f[2]=z;a.f[3]=1.0f; }
 func_00283098(&b,&a,m+0xc0);func_00282CC0(&b,&b,m+0x10);func_002E5CF8(2,0,m);
 func_L05_00427988(&b,m+0xc0,I(s,0x18),m,0);I(s,0x210)=D_L05_001B1AB0;I(s,0x218)=10;
 }
 }
 index=func_L05_0037AA88(7);
 if(index>=0 && D_L05_002A1800[index].ammo!=0 && (D_00138320[0]&0x80)) {
 char *v=(char *)(D_L05_001B1AFC*112+(int)D_00188660);
 if(P(v,0x88)!=m || !B(v,0x74)) D_L05_001B1AFC=func_002E5DA0(0x11,4,m,0xfbf);
 if(++I(s,0x34)>=8) {I(s,0x34)=8;func_00282948(&D_L05_002A1800[index].ammo);}
 } else {
 if(D_L05_001B1AFC!=-1) {char *v=(char *)(D_L05_001B1AFC*112+(int)D_00188660);if(P(v,0x88)==m && B(v,0x74)) func_002E59F8(D_L05_001B1AFC);}
 D_L05_001B1AFC=-1;func_00282948(s+0x34);
 if(I(s,0x34)==0 && D_L05_001B2048%3==0 && !(D_00138320[0]&0x80)) {
 ++D_L05_002A1800[index].ammo;
 if(D_L05_002A1800[index].ammo>D_L05_002A1800[index].maximum) D_L05_002A1800[index].ammo=D_L05_002A1800[index].maximum;
 }
 }
 if(!func_00282948(s+0x218)) I(s,0x214)=func_L00_002D6998(D_L05_002B8770);
}
