#include "include_asm.h"

#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
typedef struct { float f[4]; } __attribute__((aligned(16))) ChargeWeaponVec;
typedef struct {
char pad0[1888];
char camera[16];
char pad770[1160];
char * held;
char padbfc[1588];
int mask;
char pad1234[12];
int frame;
char pad1244[524];
char *selected;
char pad1454[3644];
char * player;
int mode;
char pad2298[36];
unsigned char locked;
char pad22bd[559];
short direction;
char pad24ee[70];
int timer;
} ChargeWeaponHero;
extern ChargeWeaponHero D_00189E20;
typedef struct { char pad[0x50]; float speed; char tail[0x8C]; } ChargeWeaponMaterial;
extern ChargeWeaponMaterial D_L00_00262570[];
typedef struct { char pad[0x1A0]; int pressed, released; } ChargeWeaponInput;
extern ChargeWeaponInput D_00138180;
typedef struct { float values[18]; char pad[8]; ChargeWeaponVec a, b; char tail[16]; } ChargeWeaponEffect;
extern ChargeWeaponEffect D_L00_0024F7C0[];
extern char D_L00_001B8DC0[0x100];
extern unsigned char D_00139584 NOT_SDA;
typedef struct { int active; char gap[0x18]; float reticle; } ChargeWeaponEffects;
extern ChargeWeaponEffects D_L00_001B2B70 __attribute__((sda));
extern char *D_L00_001C3280[];
extern int D_L00_001B06D0 __attribute__((sda)), D_L00_001B06B8 __attribute__((sda)), D_L00_001B06D8 __attribute__((sda));
extern char *D_L00_001B06D4 __attribute__((sda));
extern float D_L00_001B06BC __attribute__((sda)), D_L00_001B06C0 __attribute__((sda)), D_L00_001B06C4 __attribute__((sda)), D_L00_001B06C8 __attribute__((sda)), D_L00_001B06CC __attribute__((sda));
extern void func_PAL_002A7E68(void *,int,int,int);
extern void func_0029F978(void *,int,void *);
extern int func_L00_00329E90(void *,int,void *);
extern int func_L00_0032A088(int,int);
extern float func_002A78D8(float,float), func_002A7878(float,float);
extern void func_00282C88(void *), func_L00_003CBBE0(void);
extern void func_PAL_L01_002BEC60(int,int);
extern int func_00282948(void *), func_L00_002D4040(int);
extern void func_00273318(void *,unsigned int,float,void *,float,int,int,float,int);
extern void func_0029FCC0(void *,int,void *);
extern void func_L00_0032A1A8(char *,void *,void *,float);
extern char *func_L00_00324E48(void *,int,float,float,float,float,float);
extern char *func_002AB1F0(char *);
extern void func_002AFFD8(void *,void *,int),func_L00_003252A8(void *,void *,int);
extern void func_00282D30(void *,void *,float),func_00282CC0(void *,void *,void *);
extern float func_00282E48(void *,void *),func_00282C48(float);
extern int func_002829D8(void *),func_L00_003CBBD0(void),func_L00_002D3F30(int,int);
extern void func_002E5CF8(int,int,void *);
extern void func_00282F20(void *,void *,float);
extern int func_00277F48(void *,int,void *,int,float);
extern void func_00282CF0(void *,void *,void *);
extern char *func_PAL_L00_003CF868(void *,int,void *,void *);
extern void ref_L00_003E8180_00(void *,void *),func_PAL_L00_003ECD58(void);
extern float func_00283BE0(float,float),func_00283198(float),func_00283180(float);
typedef struct { float timer; int handle, anim, unknown; float charge, angle; char pad[8]; ChargeWeaponVec origin; float gap, sine, gap2, cosine; } ChargeWeaponVars;
typedef struct { char position[0x20]; unsigned char state; char pad21[0x22]; unsigned char animation; char pad44[0x1C]; unsigned char flags; char pad61[7]; ChargeWeaponVars *vars; } ChargeWeaponMoby;

void func_PAL_L01_003EE6C4(ChargeWeaponMoby *obj) {
    ChargeWeaponVec velocity, origin, target, delta, point;
    int unused;
    char *hit = 0;
    ChargeWeaponVars *st = obj->vars;
    ChargeWeaponMaterial *material = &D_L00_00262570[D_00139584];
    float speed = material->speed * 0.020000001f;
    int i, enabled, count;
    switch (obj->state) {
    case 0: {
        int i;
        if (obj->animation != 0 || (obj->flags&2)) func_PAL_002A7E68(obj,1,0,0);
        func_0029F978(obj,0,&st->origin);
        st->timer=0.36666667f;
        st->unknown=-1;
        st->charge=0;
        st->angle=0;
        obj->state=1;
        D_L00_001B2B70.reticle=-1.0f;
        D_L00_001B06D0=0;
        D_L00_001B06B8=0;
        st->handle=func_L00_00329E90(obj,0,&unused);
        st->anim=func_L00_0032A088(H(obj,0xAA),st->handle);
        for (i=0;i<4;i++) {
            D_L00_0024F7C0[i].values[0]=0; D_L00_0024F7C0[i].values[1]=0; D_L00_0024F7C0[i].values[2]=0;
            D_L00_0024F7C0[i].values[3]=func_002A78D8(0.05f,0.3f);
            D_L00_0024F7C0[i].values[4]=func_002A78D8(0.05f,0.3f);
            D_L00_0024F7C0[i].values[5]=func_002A78D8(0.05f,0.3f);
            D_L00_0024F7C0[i].values[6]=func_002A7878(0.25f,0.75f);
            D_L00_0024F7C0[i].values[7]=func_002A7878(0.25f,0.75f);
            D_L00_0024F7C0[i].values[8]=func_002A7878(0.25f,0.75f);
            D_L00_0024F7C0[i].values[9]=0; D_L00_0024F7C0[i].values[10]=0; D_L00_0024F7C0[i].values[11]=0;
            D_L00_0024F7C0[i].values[12]=func_002A78D8(0.05f,0.3f);
            D_L00_0024F7C0[i].values[13]=func_002A78D8(0.05f,0.3f);
            D_L00_0024F7C0[i].values[14]=func_002A78D8(0.05f,0.3f);
            D_L00_0024F7C0[i].values[15]=func_002A7878(0.25f,0.75f);
            D_L00_0024F7C0[i].values[16]=func_002A7878(0.25f,0.75f);
            D_L00_0024F7C0[i].values[17]=func_002A7878(0.25f,0.75f);
            func_00282C88(&D_L00_0024F7C0[i].a);
            func_00282C88(&D_L00_0024F7C0[i].b);
        }
        func_L00_003CBBE0();
        break;
    }
    case 1:
        D_L00_001B2B70.reticle=-1;
        if (D_00189E20.selected) D_00189E20.held=D_00189E20.selected;
        if (!D_L00_001B06B8) D_L00_001B06B8=1;
        if (D_00189E20.mode==1) func_PAL_L01_002BEC60(29,1);
        enabled=1;
        if (D_00189E20.mode==29) {
            if (!func_00282948(&D_00189E20.timer)) enabled=0;
            {
                unsigned int color;
                if (st->timer!=0 && func_L00_002D4040(-1)) color=0x600000FF;
                else color=0x600FFF0F;
                func_00273318(obj,color,1,0,0,38,-1,90,4);
            }
        } else D_00189E20.timer=33;
        func_0029FCC0(obj,0,&origin);
        if (D_00189E20.held) func_L00_0032A1A8(D_00189E20.held,&origin,&velocity,speed);
        else hit=func_L00_00324E48(&D_00189E20.camera,1,0.17453295f,0.17453295f,20,0.7853982448577881f,0.7853982448577881f);
        if (st->timer==0 && hit && func_L00_002D4040(-1)) {
            char *extra;
            /* The copy only writes target; no scalar local or source field aliases it. */
            qcopy_nc(&target,hit+0x10);
            extra=func_002AB1F0(hit);
            if (extra) {
                func_002AFFD8(hit+0x10,&delta,1);
                func_00282D30(&delta,&delta,F(extra,0x10));
                func_00282CC0(&target,&delta,hit+0x10);
            }
            {
                float scale=func_00282C48(0.9f-func_00282E48(D_L00_001B8DC0,&target)*0.006666667f*0.65f);
                func_00273318(obj,0xFF0FFF0F,scale,&target,0,38,-1,90,4);
            }
        }
        if (func_002829D8(st) && !D_00189E20.locked) {
            if ((D_00138180.pressed&D_00189E20.mask) && enabled && !func_L00_003CBBD0() && D_00189E20.frame>=19) {
                if (func_L00_002D3F30(-1,1)) {
                    D_L00_001B2B70.active=1;
                    func_002E5CF8(2,0,obj);
                    switch (D_L00_001B06D0) {
                    case 0:
                        D_L00_001B06D0=1; st->charge=D_L00_001B06C4; st->timer=0.5f;
                        break;
                    case 2:
                        D_L00_001B06D0=1; st->timer=0.5f;
                        break;
                    }
                } else if ((D_00138180.released&D_00189E20.mask) || D_L00_001B2B70.active==1) {
                    func_002E5CF8(7,0,obj); D_L00_001B2B70.active=0;
                }
            }
        }
        switch (D_L00_001B06D0) {
        case 0:
            if (st->charge<D_L00_001B06C4) {
                st->charge+=D_L00_001B06C8;
                if (st->charge>D_L00_001B06C4) st->charge=D_L00_001B06C4;
            }
            break;
        case 1:
            st->charge+=D_L00_001B06BC;
            if (st->charge>D_L00_001B06CC) {
                func_0029FCC0(obj,0,&target);
                if (D_00189E20.direction==1) func_00282F20(&velocity,(char *)obj+0xD0,-speed);
                else func_00282F20(&velocity,&D_00189E20.camera,speed);
                count=func_00277F48(&target,0,obj,0,1.0f);
                for(i=0;i<count;i++) {
                    char *candidate=D_L00_001C3280[i];
                    char *details=func_002AB1F0(candidate);
                    if (candidate==D_00189E20.player || !(U(candidate,0x34)&0x1000) || H(candidate,0xAA)==0xC87 || H(candidate,0xAA)==0xECC) continue;
                    qcopy(&point,candidate+0x10);
                    if (details) {
                        func_L00_003252A8(candidate,&delta,1);
                        func_00282D30(&delta,&delta,F(details,0x10));
                        func_00282CC0(&point,&delta,&point);
                    }
                    func_00282CF0(&velocity,&point,&target);
                    func_00282F20(&velocity,&velocity,speed);
                    break;
                }
                if (hit) {
                    char *extra;
                    qcopy(&delta,hit+0x10);
                    extra=func_002AB1F0(hit);
                    if (extra) {
                        func_002AFFD8(hit+0x10,&point,1);
                        func_00282D30(&point,&point,F(extra,0x10));
                        func_00282CC0(&delta,&point,hit+0x10);
                    }
                    func_00282CF0(&velocity,&delta,&target);
                    func_00282F20(&velocity,&velocity,speed);
                }
                D_L00_001B06D4=func_PAL_L00_003CF868(obj,st->handle,&target,&velocity);
                if (D_L00_001B06D4) *(ChargeWeaponMoby **)(D_L00_001B06D4+0xB8)=obj;
                D_L00_001B06D8=42; D_L00_001B06D0=2;
            }
            break;
        case 2:
            st->charge-=D_L00_001B06C0;
            if (st->charge<=D_L00_001B06C4) { st->charge=D_L00_001B06C4; D_L00_001B06D0=0; }
            break;
        }
        if (B(obj,0x31)) ref_L00_003E8180_00(func_PAL_L00_003ECD58,obj);
        st->angle=func_00283BE0(st->angle,st->charge*0.37699118f);
        st->sine=func_00283198(st->angle*0.5f);
        st->cosine=func_00283180(st->angle*0.5f);
        break;
    }
}
