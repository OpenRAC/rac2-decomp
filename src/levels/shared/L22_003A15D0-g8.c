#include "include_asm.h"
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
typedef struct Sub_15D0 {
    char pad0[0x8];
    signed char f8;
    char pad9[0x1];
    signed char fA;
    char padB[0x1];
    signed char fC;
} Sub_15D0;
typedef struct Cls_15D0 { char pad0[0x24]; float f24; } Cls_15D0;
struct Vars_15D0;
typedef struct Obj_15D0 {
    char pad0[0x20];
    unsigned char f20;
    char pad21[0x3];
    struct Cls_15D0 *f24;
    char pad28[0x4];
    float f2C;
    unsigned char f30;
    unsigned char f31;
    short f32;
    unsigned short f34;
    char pad36[0x2];
    unsigned long f38;
    char pad40[0x8];
    float f48;
    char pad4C[0x1C];
    struct Vars_15D0 *f68;
    char pad6C[0x3];
    unsigned char f6F;
    char pad70[0x8];
    int f78;
    char pad7C[0x19];
    unsigned char f95;
    char pad96[0x14];
    short fAA;
} Obj_15D0;
typedef struct Vars_15D0 {
    char pad0[0x20];
    float f20;
    short f24;
    short f26;
    unsigned char f28;
    char pad29[0x47];
    unsigned char f70;
    unsigned char f71;
    unsigned char f72;
    char pad73[0x3];
    unsigned char f76;
    unsigned char f77;
    char pad78[0x4];
    float f7C;
    float f80;
    float f84;
    float f88;
    float f8C;
    float f90;
    float f94;
    char pad98[0x4];
    float f9C;
    char padA0[0x8];
    int fA8;
    char padAC[0xC];
    float fB8;
    float fBC;
    char padC0[0xC];
    unsigned char fCC;
    unsigned char fCD;
    unsigned char fCE;
    unsigned char fCF;
    char padD0[0x2];
    signed char fD2;
    signed char fD3;
    char padD4[0x3];
    unsigned char fD7;
    char padD8[0x38];
    float f110;
    float f114;
    float f118;
    float f11C;
    float f120;
    char pad124[0xC];
    float f130;
    float f134;
    float f138;
    char pad13C[0x4];
    float f140;
    int f144;
    int f148;
    char pad14C[0xAC];
    unsigned char f1F8;
    unsigned char f1F9;
    char pad1FA[0x12A];
    short f324;
    short f326;
    char pad328[0x1C];
    int f344;
    char pad348[0x4];
    short f34C;
    short f34E;
    short f350;
    char pad352[0x6];
    short f358;
    short f35A;
    short f35C;
    short f35E;
    char pad360[0x14];
    int f374;
    short f378;
    short f37A;
    int f37C;
    short f380;
    short f382;
    short f384;
    char pad386[0x2];
    int f388;
    char pad38C[0x58];
    float f3E4;
    float f3E8;
    int f3EC;
    char pad3F0[0x2E];
    short f41E;
    char pad420[0x1A];
    short f43A;
    char pad43C[0x4];
    Obj_15D0 *f440;
    Obj_15D0 *f444;
    Obj_15D0 *f448;
    char pad44C[0x14];
    short f460;
    char pad462[0x2];
    int f464;
    short f468;
    short f46A;
    void * f46C;
    char pad470[0x74];
    int f4E4;
    char pad4E8[0x4];
    int f4EC;
} Vars_15D0;
extern int D_L22_001AF2E8 __attribute__((sda)), D_L22_001AF2F0 __attribute__((sda)), D_L22_001AF2EC __attribute__((sda));
extern int D_L22_001AF304 __attribute__((sda)), D_L22_001AF394 __attribute__((sda)), D_L22_001AF3C4 __attribute__((sda));
extern struct Obj_15D0 *ref_L22_003A15D0_00 __attribute__((sda)); /* D_L22_001AF314 in level 22 */
extern struct Obj_15D0 *D_L22_001AF2E0 __attribute__((sda));
extern float D_L22_001AF39C __attribute__((sda)), D_L22_001AF330 __attribute__((sda));
extern int D_L22_001AF3B0[5] __attribute__((sda));
extern int D_L22_001B2AA8, D_L22_001B2A8C, D_L22_001B2A90;
extern int D_L22_001B2AD4, D_L22_001B2AC8, D_L22_001B2AD0;
extern short D_L22_001B2A88;
extern char *D_L22_001B2AB4;
extern float D_L22_001B2AA4;
extern char D_L22_001B1910[], D_L22_001B9C80[];
extern char D_L22_001AF5D0[] MACRO_ADDR;
extern char *D_L22_001B211C, *D_L22_001B2120;
extern void func_L22_003A6230(void *);
extern void func_L00_0042A500(void *);
extern void func_001163A0(unsigned int);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282DF0(void *);
extern int func_002A77E0(int);
extern void func_L22_003A3368(void *),func_L22_003A36A0(char *);
extern char *func_0029EFD0(int);
extern void func_00283360(void *);
extern void func_0029B758(void *,void *);
extern int func_L22_003A4FF8(void);
extern void func_L22_003A5018(void);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *),func_002A0F48(void *);
extern void func_002AFFD8(void *,void *,int),func_L00_00325600(void *,void *,int),func_002B0ED8(void *,void *,int);
extern void func_002A7750(void *,int,int),func_L00_002AF7D0(void),func_L00_00310C88(void *,void *),func_L22_002C9898(int,int);

/* Sets the record up on the first update (health scaled by difficulty, the object table
   scan, then the tuning block) and keeps the three child objects in step. The tuning
   block's order matters to the scheduler: f11C is the 34th memory reference after the
   call, so it flushes the pending list, and f1F8 and f1F9 precede the second health read. */
void func_L22_003A15D0(Obj_15D0 *obj) {
    Vars_15D0 *p = obj->f68;
    Obj_15D0 *found = 0;
    Obj_15D0 *it;
    int i;
    char *base;
    typedef int Quad __attribute__((mode(TI)));
    union { Quad q; float f[4]; } vec;
    func_L22_003A6230(obj);
    if (obj->f20 == 0) {
        float factor, health, damageScale, rangeScale;
        short x380;
        int eight, alpha;
        int difficulty=D_L22_001AF2E8;
        if (D_L22_001AF2F0 < difficulty) factor = 0.6f;
        else if (D_L22_001AF2EC < difficulty) factor = 0.9f;
        else goto full_health;
        D_L22_001B2AA8 = (int)(p->f326*factor);
        goto health_done;
full_health:
        D_L22_001B2AA8 = p->f326;
health_done:
        func_L00_0042A500(p->f46C);
        D_L22_001AF304 = 1;
        func_001163A0(T1_COUNT);
        p->f4EC=1;
        D_L22_001B2A8C=0; D_L22_001B2AB4=D_L22_001B1910;
        D_L22_001B2A90=0;
        p->f460=0; p->f41E=0;
        D_L22_001AF394=1; D_L22_001B2A88=0;
        p->f46A=0; p->f468=0;
        p->f464=0; p->f344=0;
        D_L22_001B2AD4=5;
        { int *d=D_L22_001AF3B0; int *s=(int *)D_L22_001AF5D0; int n; for(n=5;n!=0;n--) *d++=*s++; }
        D_L22_001B2AC8=-1; D_L22_001AF3C4=0; D_L22_001B2AD0=0;
        p->f34E=0; p->f34C=0;
        i=0; base=D_L22_001B211C;
        if(base<D_L22_001B2120) do {
            int id;
            Obj_15D0 *it;
            it=(Obj_15D0 *)(base+i*256);
            id=it->fAA;
            if(id==0x27D) found=it;
            if(id==0xE0B) ref_L22_003A15D0_00=it;
            if(id==0x133A) it->f34|=0x41;
            if(it->fAA==0xF6E) {
                Sub_15D0 *sub;
                D_L22_001AF2E0=it; it->f30=255;
                sub=(Sub_15D0 *)D_L22_001AF2E0->f68;
                sub->f8=0; sub->fA=0; sub->fC=-1;
            }
            i++;
            base=D_L22_001B211C;
        } while(base+i*256<D_L22_001B2120);
        vec.q=0; vec.f[0]=0.00161f; vec.f[1]=0.29459f; vec.f[2]=1.57105f;
        qcopy(&D_00189E20.rotation,&vec); qcopy(&D_00189E20.position,(char *)found+0x10);
        D_00189E20.health=p->f324;
        func_00282CF0(&vec,(char *)obj+0x10,(char *)&D_00189E20.rotation+0x20);
        D_L22_001B2AA4=func_00282DF0(&vec);
        obj->f34|=0x100;
        x380=func_002A77E0(30);
        eight=8;
        p->fD7=1; p->f70=37; p->f71=4;
        p->f77=eight; p->f72=eight; p->f76=eight;
        p->fCC=9; p->fCD=18; p->fCE=9; p->fCF=18; p->fD2=-1; p->fD3=-1;
        health=(float)D_L22_001B2AA8;
        rangeScale=900.0f/health; damageScale=9.0f/health;
        p->f7C=0.5833333730697632f; p->f80=1.0f/15;
        p->f84=1.0f/24; p->f88=1.0f/12;
        p->f8C=1.0f/60; p->f90=3; p->f94=4;
        p->f9C=0.4f; p->fA8=eight;
        p->fBC=rangeScale; p->fB8=damageScale;
        p->f130=0.0044444446f; p->f134=0.0044444446f;
        p->f138=0.20000002f; p->f110=2.5f; p->f114=0.75f;
        p->f120=2; p->f118=2.75f; p->f144=0; p->f380=x380;
        p->f11C=2.75f; p->f1F8=12; p->f1F9=11;
        { float health=(float)D_L22_001B2AA8;
        p->f148|=1; p->f140=0.7853982448577881f;
        p->f28=3; p->f26=60;
        p->f20=health;
        p->f24=(int)health; }
        alpha=255; obj->f32=alpha; obj->f30=alpha; obj->f48=1.0f;
        p->f374=-1; p->f382=-1; p->f35C=-1; p->f35A=-1; p->f358=-1;
        p->f3EC=-1; p->f4E4=300;
        p->f3E4=p->f3E8=0.0f; p->f388=0;
        p->f378=0; p->f37C=0; p->f37A=0;
        p->f35E=0; p->f350=0;
        obj->f34|=0x4000;
        obj->f2C=obj->f24->f24*D_L22_001AF39C;
        func_L22_003A3368(obj); func_L22_003A36A0((char *)obj);
        p->f440=func_0029EFD0(0xE0A); func_00283360((char *)p->f440+0xC0);
        p->f444=func_0029EFD0(0xE0C); p->f448=func_0029EFD0(0xF8F);
        p->f384=30; p->f43A=0;
    }
    func_0029B758(func_L22_003A4FF8,func_L22_003A5018);
    if(p->f440) {
        p->f440->f32=obj->f32; p->f440->f30=obj->f30;
        p->f440->f38=obj->f38;
        p->f440->f78=obj->f78;
        p->f440->f31=1;
        it=p->f440; it->f2C=it->f24->f24*D_L22_001AF39C;
        it=p->f440;
        if(it->f31 && func_00282E48((char *)it+0x10,D_L22_001B9C80)<24.0f) {
            func_002A93B0(p->f440); p->f440->f6F=22;
        }
    }
    if(p->f444) {
        p->f444->f32=80; p->f444->f30=obj->f30;
        p->f444->f38=obj->f38;
        p->f444->f78=obj->f78;
        p->f444->f31=1;
        it=p->f444; it->f2C=it->f24->f24*D_L22_001AF39C;
    }
    if(p->f448) {
        p->f448->f32=80; p->f448->f30=obj->f30;
        p->f448->f38=obj->f38;
        p->f448->f78=obj->f78;
        p->f448->f31=1;
        it=p->f448; it->f2C=it->f24->f24*D_L22_001AF330;
        func_002A0F48(p->f448);
    }
    func_002AFFD8((char *)obj+0x10,(char *)p+0x200,0); func_L00_00325600((char *)obj+0xC0,(char *)p+0x200,0); func_002B0ED8(obj,(char *)p+0x60,0);
    obj->f2C=obj->f24->f24*D_L22_001AF39C;
    if(D_L22_001AF304) {
        if(++D_L22_001AF304>32000) D_L22_001AF304=1;
        D_00189E20.mode=10;
        if(obj->f95!=1) {
            p->f350=0; p->f3E4=p->f3E8=0.0f; func_002A7750(obj,1,1);
        }
        if(D_00138180.buttons&0x50) {
            D_L22_001AF304=0; func_002A7750(obj,5,0); D_00138180.buttons=0; D_00189E20.mode=20;
        } else if(D_L22_001AF304<30) {
            D_00189E20.field2294=0; func_L00_002AF7D0();
            func_L00_00310C88(D_00189E20.field2290,&D_00189E20.field1870);
            D_00189E20.field187C=0; func_L22_002C9898(0,1);
        }
    } else if(D_00189E20.health<=0 && obj->f95!=1) {
        p->f350=0; p->f3E4=p->f3E8=0.0f;
        func_002A7750(obj,2,1); p->f384=30;
    }
    if(obj->f31 && func_00282E48((char *)obj+0x10,D_L22_001B9C80)<24.0f) {
        func_002A93B0(obj); obj->f6F=22;
    }
}
