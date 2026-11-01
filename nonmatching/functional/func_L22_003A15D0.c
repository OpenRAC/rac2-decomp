/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* GPT-6.1 Sol (high), 29 October 2026. USA v1.01, levels 22 and 23.
 * Profile: -O2 -G8 -ffunction-sections -Wa,-G32 -g -frac2-zero-ti-por.
 * check.py: 2184 bytes versus 2176, 0/2 places. No linked match claimed.
 * Improves the earlier 2200-byte draft: the measured partial hero layout and
 * explicit health snapshots recover retail's 0x50 frame and saved s0-s6/ra.
 * Incomplete MACRO_ADDR arrays recover absolute stores through at; -Wa,-G32
 * addresses the actual 20-byte five-slot array through gp. The TI vector zero
 * with -frac2-zero-ti-por gives por/sq; chained float clears give mtc1/swc1.
 * Corrected the 0x7C float constant to retail's 0x3F155556.
 * Remaining: initialization-store order, duplicate width-specific constants,
 * FP/GPR allocation, and address/load scheduling. The pre-initialization branch
 * is +0x145 words versus retail +0x143. The function is eight bytes too large;
 * relocation binding across the two levels has not been qualified.
 * A typed boss-state view tied the corresponding raw accesses. Strict aliasing
 * reduced size but lost required child-pointer reloads; disabling sched1 or
 * GCSE damaged the prologue. No-sched-interblock and iterator block scope did
 * not solve initialization. Next useful input is a better measured boss-state
 * /configuration layout or a corresponding original engine initializer.
 * Declarations are below. Only the hardware timer read is volatile.
 */
#include "common.h"
typedef int Quad_003A15D0 __attribute__((mode(TI)));
typedef struct Hero_003A15D0 {
    char pad000[0x80];
    Quad_003A15D0 position;
    Quad_003A15D0 rotation;
    char pad0A0[0x140];
    short mode;
    char pad1E2[0x168E];
    int field1870;
    int health;
    int field1878;
    int field187C;
    char pad1880[0xA10];
    void *field2290;
    int field2294;
} Hero_003A15D0;
extern Hero_003A15D0 D_00189E20;
typedef struct Input_003A15D0 { char pad000[0x1A4]; int buttons; } Input_003A15D0;
extern Input_003A15D0 D_00138180;
#define FIELD(p,t,o) (*(t *)((char *)(p)+(o)))
extern int D_L22_001AF2E8 __attribute__((sda)), D_L22_001AF2F0 __attribute__((sda)), D_L22_001AF2EC __attribute__((sda));
extern int D_L22_001AF304 __attribute__((sda)), D_L22_001AF394 __attribute__((sda)), D_L22_001AF3C4 __attribute__((sda));
extern char *D_L22_001AF314 __attribute__((sda)), *D_L22_001AF2E0 __attribute__((sda));
extern float D_L22_001AF39C __attribute__((sda)), D_L22_001AF330 __attribute__((sda));
extern int D_L22_001AF3B0[5] __attribute__((sda));
extern int D_L22_001B2AA8[] MACRO_ADDR, D_L22_001B2A8C[] MACRO_ADDR, D_L22_001B2A90[] MACRO_ADDR;
extern int D_L22_001B2AD4[] MACRO_ADDR, D_L22_001B2AC8[] MACRO_ADDR, D_L22_001B2AD0[] MACRO_ADDR;
extern short D_L22_001B2A88[] MACRO_ADDR;
extern char *D_L22_001B2AB4[] MACRO_ADDR;
extern float D_L22_001B2AA4[] MACRO_ADDR;
extern char D_L22_001B1910[], D_L22_001AF5D0[], D_L22_001B9C80[];
extern char *D_L22_001B211C[] MACRO_ADDR, *D_L22_001B2120[] MACRO_ADDR;
extern void func_L22_003A6230(void *);
extern void func_L00_0042A500(void *);
extern void func_001163A0(unsigned int);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282DF0(void *);
extern int func_002A77E0(int);
extern void func_L22_003A3368(void *),func_L22_003A36A0(void *);
extern char *func_0029EFD0(int);
extern void func_00283360(void *);
extern void func_0029B758(void *,void *);
extern void func_L22_003A4FF8(void),func_L22_003A5018(void);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *),func_002A0F48(void *);
extern void func_002AFFD8(void *,void *,int),func_L00_00325600(void *,void *,int),func_002B0ED8(void *,void *,int);
extern void func_002A7750(void *,int,int),func_L00_002AF7D0(void),func_L00_00310C88(void *,void *),func_L22_002C9898(int,int);


void func_L22_003A15D0(char *obj) {
    char *p = FIELD(obj,char *,0x68);
    char *found = 0;
    char *it;
    int i;
    typedef int Quad __attribute__((mode(TI)));
    union { Quad q; float f[4]; } vec;
    func_L22_003A6230(obj);
    if (FIELD(obj,u8,0x20) == 0) {
        float factor, health, damageScale, rangeScale;
        int difficulty=D_L22_001AF2E8;
        if (D_L22_001AF2F0 < difficulty) factor = 0.6f;
        else if (D_L22_001AF2EC < difficulty) factor = 0.9f;
        else goto full_health;
        D_L22_001B2AA8[0] = (int)(FIELD(p,s16,0x326)*factor);
        goto health_done;
full_health:
        D_L22_001B2AA8[0] = FIELD(p,s16,0x326);
health_done:
        func_L00_0042A500(FIELD(p,void *,0x46C));
        D_L22_001AF304 = 1;
        func_001163A0(*(volatile unsigned int *)0x10000800);
        FIELD(p,int,0x4EC)=1;
        D_L22_001B2A8C[0]=0; D_L22_001B2AB4[0]=D_L22_001B1910;
        D_L22_001B2A90[0]=0;
        FIELD(p,short,0x460)=0; FIELD(p,short,0x41E)=0;
        D_L22_001AF394=1; D_L22_001B2A88[0]=0;
        FIELD(p,short,0x46A)=0; FIELD(p,short,0x468)=0;
        FIELD(p,int,0x464)=0; FIELD(p,int,0x344)=0;
        D_L22_001B2AD4[0]=5;
        for(i=5;i!=0;i--) D_L22_001AF3B0[5-i]=FIELD(D_L22_001AF5D0,int,(5-i)*4);
        D_L22_001B2AC8[0]=-1; D_L22_001AF3C4=0; D_L22_001B2AD0[0]=0;
        FIELD(p,short,0x34E)=0; FIELD(p,short,0x34C)=0;
        for(i=0; D_L22_001B211C[0]+i*256<D_L22_001B2120[0]; i++) {
            int id;
            char *it;
            it=D_L22_001B211C[0]+i*256;
            id=FIELD(it,s16,0xAA);
            if(id==0x27D) found=it;
            if(id==0xE0B) D_L22_001AF314=it;
            if(id==0x133A) FIELD(it,u16,0x34)|=0x41;
            if(FIELD(it,s16,0xAA)==0xF6E) {
                char *sub;
                D_L22_001AF2E0=it; FIELD(it,u8,0x30)=255;
                sub=FIELD(D_L22_001AF2E0,char *,0x68);
                FIELD(sub,s8,0xC)=-1; FIELD(sub,s8,8)=0; FIELD(sub,s8,0xA)=0;
            }
        }
        vec.q=0; vec.f[0]=0.00161f; vec.f[1]=0.29459f; vec.f[2]=1.57105f;
        qcopy(&D_00189E20.rotation,&vec); qcopy(&D_00189E20.position,found+0x10);
        D_00189E20.health=FIELD(p,s16,0x324);
        func_00282CF0(&vec,obj+0x10,(char *)&D_00189E20.rotation+0x20);
        D_L22_001B2AA4[0]=func_00282DF0(&vec);
        FIELD(obj,u16,0x34)|=0x100;
        FIELD(p,short,0x380)=func_002A77E0(30);
        FIELD(p,u8,0x77)=8; FIELD(p,u8,0x72)=8; FIELD(p,u8,0x76)=8;
        FIELD(p,u8,0xCE)=9; FIELD(p,u8,0xCF)=18; FIELD(p,s8,0xD3)=-1;
        FIELD(p,u8,0xCC)=9; FIELD(p,u8,0xCD)=18; FIELD(p,s8,0xD2)=-1;
        FIELD(p,u8,0xD7)=1; FIELD(p,u8,0x70)=37; FIELD(p,u8,0x71)=4;
        health=(float)D_L22_001B2AA8[0];
        damageScale=9.0f/health; rangeScale=900.0f/health;
        FIELD(p,float,0x80)=1.0f/15; FIELD(p,int,0xA8)=8;
        FIELD(p,float,0x7C)=0.5833333730697632f; FIELD(p,float,0x88)=1.0f/12;
        FIELD(p,float,0x8C)=1.0f/60; FIELD(p,float,0x90)=3; FIELD(p,float,0x94)=4;
        FIELD(p,float,0x9C)=0.4f; FIELD(p,float,0x134)=0.0044444446f;
        FIELD(p,float,0x138)=0.20000002f; FIELD(p,float,0x110)=2.5f;
        FIELD(p,float,0x114)=0.75f; FIELD(p,float,0x120)=2;
        FIELD(p,float,0x130)=0.0044444446f; FIELD(p,float,0x118)=2.75f;
        FIELD(p,float,0x84)=1.0f/24; FIELD(p,float,0xBC)=rangeScale;
        FIELD(p,float,0xB8)=damageScale; FIELD(p,int,0x144)=0;
        FIELD(p,float,0x11C)=2.75f; FIELD(p,u8,0x1F8)=12; FIELD(p,u8,0x1F9)=11;
        FIELD(p,float,0x140)=0.7853982448577881f; FIELD(p,u8,0x28)=3; FIELD(p,short,0x26)=60;
        { float health=(float)D_L22_001B2AA8[0];
        FIELD(p,float,0x20)=health; FIELD(p,int,0x148)|=1;
        FIELD(p,short,0x24)=(int)health; }
        FIELD(obj,short,0x32)=FIELD(obj,u8,0x30)=255; FIELD(obj,float,0x48)=1.0f;
        FIELD(p,int,0x3EC)=-1; FIELD(p,int,0x4E4)=300; FIELD(p,int,0x374)=-1;
        FIELD(p,short,0x382)=-1; FIELD(p,short,0x35C)=-1; FIELD(p,short,0x35A)=-1; FIELD(p,short,0x358)=-1;
        FIELD(p,float,0x3E4)=FIELD(p,float,0x3E8)=0.0f; FIELD(p,int,0x388)=0;
        FIELD(p,short,0x378)=0; FIELD(p,int,0x37C)=0; FIELD(p,short,0x37A)=0;
        FIELD(p,short,0x35E)=0; FIELD(p,short,0x350)=0;
        FIELD(obj,u16,0x34)|=0x4000;
        FIELD(obj,float,0x2C)=FIELD(FIELD(obj,char *,0x24),float,0x24)*D_L22_001AF39C;
        func_L22_003A3368(obj); func_L22_003A36A0(obj);
        FIELD(p,char *,0x440)=func_0029EFD0(0xE0A); func_00283360(FIELD(p,char *,0x440)+0xC0);
        FIELD(p,char *,0x444)=func_0029EFD0(0xE0C); FIELD(p,char *,0x448)=func_0029EFD0(0xF8F);
        FIELD(p,short,0x384)=30; FIELD(p,short,0x43A)=0;
    }
    func_0029B758(func_L22_003A4FF8,func_L22_003A5018);
    it=FIELD(p,char *,0x440);
    if(it) {
        FIELD(it,short,0x32)=FIELD(obj,short,0x32); FIELD(FIELD(p,char *,0x440),u8,0x30)=FIELD(obj,u8,0x30);
        FIELD(FIELD(p,char *,0x440),u64,0x38)=FIELD(obj,u64,0x38);
        FIELD(FIELD(p,char *,0x440),int,0x78)=FIELD(obj,int,0x78);
        FIELD(FIELD(p,char *,0x440),u8,0x31)=1;
        it=FIELD(p,char *,0x440); FIELD(it,float,0x2C)=FIELD(FIELD(it,char *,0x24),float,0x24)*D_L22_001AF39C;
        it=FIELD(p,char *,0x440);
        if(FIELD(it,u8,0x31) && func_00282E48(it+0x10,D_L22_001B9C80)<24.0f) {
            func_002A93B0(FIELD(p,char *,0x440)); FIELD(FIELD(p,char *,0x440),u8,0x6F)=22;
        }
    }
    it=FIELD(p,char *,0x444);
    if(it) {
        FIELD(it,short,0x32)=80; FIELD(FIELD(p,char *,0x444),u8,0x30)=FIELD(obj,u8,0x30);
        FIELD(FIELD(p,char *,0x444),u64,0x38)=FIELD(obj,u64,0x38);
        FIELD(FIELD(p,char *,0x444),int,0x78)=FIELD(obj,int,0x78);
        FIELD(FIELD(p,char *,0x444),u8,0x31)=1;
        it=FIELD(p,char *,0x444); FIELD(it,float,0x2C)=FIELD(FIELD(it,char *,0x24),float,0x24)*D_L22_001AF39C;
    }
    it=FIELD(p,char *,0x448);
    if(it) {
        FIELD(it,short,0x32)=80; FIELD(FIELD(p,char *,0x448),u8,0x30)=FIELD(obj,u8,0x30);
        FIELD(FIELD(p,char *,0x448),u64,0x38)=FIELD(obj,u64,0x38);
        FIELD(FIELD(p,char *,0x448),int,0x78)=FIELD(obj,int,0x78);
        FIELD(FIELD(p,char *,0x448),u8,0x31)=1;
        it=FIELD(p,char *,0x448); FIELD(it,float,0x2C)=FIELD(FIELD(it,char *,0x24),float,0x24)*D_L22_001AF330;
        func_002A0F48(FIELD(p,char *,0x448));
    }
    func_002AFFD8(obj+0x10,(char *)p+0x200,0); func_L00_00325600(obj+0xC0,(char *)p+0x200,0); func_002B0ED8(obj,(char *)p+0x60,0);
    FIELD(obj,float,0x2C)=FIELD(FIELD(obj,char *,0x24),float,0x24)*D_L22_001AF39C;
    if(D_L22_001AF304) {
        if(++D_L22_001AF304>32000) D_L22_001AF304=1;
        D_00189E20.mode=10;
        if(FIELD(obj,u8,0x95)!=1) {
            FIELD(p,short,0x350)=0; FIELD(p,float,0x3E4)=FIELD(p,float,0x3E8)=0.0f; func_002A7750(obj,1,1);
        }
        if(D_00138180.buttons&0x50) {
            D_L22_001AF304=0; func_002A7750(obj,5,0); D_00138180.buttons=0; D_00189E20.mode=20;
        } else if(D_L22_001AF304<30) {
            D_00189E20.field2294=0; func_L00_002AF7D0();
            func_L00_00310C88(D_00189E20.field2290,&D_00189E20.field1870);
            D_00189E20.field187C=0; func_L22_002C9898(0,1);
        }
    } else if(D_00189E20.health<=0 && FIELD(obj,u8,0x95)!=1) {
        FIELD(p,short,0x350)=0; FIELD(p,float,0x3E4)=FIELD(p,float,0x3E8)=0.0f;
        func_002A7750(obj,2,1); FIELD(p,short,0x384)=30;
    }
    if(FIELD(obj,u8,0x31) && func_00282E48(obj+0x10,D_L22_001B9C80)<24.0f) {
        func_002A93B0(obj); FIELD(obj,u8,0x6F)=22;
    }
}
