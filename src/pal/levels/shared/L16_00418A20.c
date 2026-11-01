#include "include_asm.h"

#include "common.h"
typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
typedef struct {
    Quad16 direction;
    int owner,flags;
    u8 kind,active;
    u16 oclass;
    float damage;
    int enabled;
} L16Hit;
extern float D_L16_001BFF80[4];
extern u8 *D_L16_001BFF58;
extern int func_002A8C28(void *,float,float *,int,float,float,int,int,int);
extern void func_002A7750(u8 *,s32,s32);
extern void func_00282D30(void *,void *,float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_002761F8(void *,void *,int,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern float func_00282DB0(void *,void *);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_002837D0(void *,void *,void *);
extern void func_002A8C00(char *,int,int,float,Quad16 *);
extern int func_00277258(void *,int,void *,float);
extern int func_00277F48(void *,int,void *,void *,float);
extern void func_PAL_L00_003FB330(void *,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern void func_0029F338(void *);
extern void ref_L16_00413850_00(void *);
extern void ref_L16_00413850_01(void (*)(void *),void *);

/* Projectile update: expires after 240 frames, rotates its velocity by a half-angle
 * quaternion built from the surface normal under it, moves and, on a hit, unless the
 * object hit is the one its state records at +0x10, sends a blast request (velocity
 * scaled 1.5, or 3 with no object hit). Both blast branches are written out in full;
 * the compiler's cross-jumping merges their common tails, as in retail. */
void func_PAL_L16_00418A20(u8 *object)
{
    float destination[4],backward[4],normal[4],quaternion[4],inverse[4],rotated[4],start[4],finish[4];
    L16Hit hit;
    float impact[4];
    L16Hit blast;
    u8 *state=*(u8 **)(object+0x68);
    float savedW,speed,angle;
    *(int *)(state+0x24) += 1;
    if (*(int *)(state+0x24)>240) {
        func_002A8C28(object,0.6f,(float *)(object+0x10),0x10001,*(float *)(state+0x14),0.0f,0,1,0);
        func_002A7750(object,1,-1);
    }
    switch (object[0x20]) {
    case 0: {
        qcopy(backward,object+0xE0);
        func_00282D30(backward,backward,-1.0f);
        savedW=*(float *)(state+0xC);
        *(float *)(state+0xC)=0.0f;
        speed=func_00282DF0(state);
        func_00282F20(start,object+0xE0,0.1f);
        func_00282F20(finish,object+0xE0,-3.0f);
        func_00282CC0(start,start,object+0x10);
        func_00282CC0(finish,finish,object+0x10);
        if (func_002761F8(start,finish,2,object,0)) func_00282F20(normal,D_L16_001BFF80,1.0f);
        else func_00282F20(normal,object+0xE0,-1.0f);
        func_00282D30(normal,normal,-1.0f);
        func_00282F20(state,state,1.0f);
        func_00282DD8(normal,backward,normal);
        angle=-func_00282DB0(backward,normal)*0.5f;
        func_00282D30(quaternion,normal,func_00283198(angle));
        quaternion[3]=func_00283180(angle);
        inverse[0]=-quaternion[0];
        inverse[1]=-quaternion[1];
        inverse[2]=-quaternion[2];
        inverse[3]=quaternion[3];
        func_002837D0(rotated,quaternion,state);
        func_002837D0(state,rotated,inverse);
        func_00282F20(state,state,speed);
        *(float *)(state+0xC)=savedW;
        func_00282D30(normal,normal,-1.0f);
        qcopy(object+0xE0,normal);
        func_00282CC0(destination,object+0x10,state);
        func_002A8C00((char *)&hit,(int)object,1,*(float *)(state+0x14),(Quad16 *)state);
        hit.oclass=*(u16 *)(object+0xAA);
        if (func_002761F8(object+0x10,destination,0,object,&hit) || func_00277258(object+0x10,0,object,0.3f)) {
            if (D_L16_001BFF58) {
                if (D_L16_001BFF58 != *(u8 **)(state+0x10)) {
                    qcopy(impact,state);
                    func_00282D30(impact,impact,1.5f);
                    impact[2]=1.0f;
                    impact[3]=5627.9248046875f;
                    func_002A8C00((char *)&blast,(int)object,0x10001,*(float *)(state+0x14),(Quad16 *)impact);
                    blast.active=1;
                    blast.oclass=*(u16 *)(object+0xAA);
                    blast.kind=0;
                    func_00277F48(object+0x10,0,object,&blast,0.6f);
                    func_002A7750(object,1,-1);
                    return;
                }
            } else {
                qcopy(impact,state);
                func_00282D30(impact,impact,3.0f);
                impact[2]=1.0f;
                impact[3]=5627.9248046875f;
                func_002A8C00((char *)&blast,(int)object,0x10001,*(float *)(state+0x14),(Quad16 *)impact);
                blast.active=1;
                blast.oclass=*(u16 *)(object+0xAA);
                blast.kind=0;
                func_00277F48(object+0x10,0,object,&blast,0.6f);
                func_002A7750(object,1,-1);
                return;
            }
        }
        qcopy(object+0x10,destination);
        func_00282D30(impact,state,-0.5f);
    break;
    }
    case 1: {
        func_PAL_L00_003FB330(object+0x10,0,25,20,20,20,45,0,0,0,0,0,0.25f,20.0f);
        func_0029F338(object);
        return;
    }
    }
    ref_L16_00413850_01(ref_L16_00413850_00,object);
}

