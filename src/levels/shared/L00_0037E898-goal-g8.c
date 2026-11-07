/* func_L00_00383B90, built with -G8 in a unit of its own. Its data needs three address forms:
 * the D_..._gp views take the plain $gp access, D_L00_001AEDD0[1] is the two-word small
 * symbol+offset load, and the NOT_SDA pad words split into %hi/%lo.
 */
#include "common.h"
typedef struct { float x,y,z,w; } ControllerVector;
typedef struct { ControllerVector rows[4]; } __attribute__((aligned(16))) ControllerMatrix;
typedef struct {
    ControllerVector goals[2];
    unsigned char gap20[0x28];
    char *targets[2];
    unsigned char gap50[0x10];
    int scores[2];
} ControllerOwnerState;
typedef struct {
    ControllerVector position;
    unsigned char gap10[0x220];
    ControllerMatrix basis;
} ControllerCamera;
typedef struct { unsigned char prefix[0x18]; char *object; } ControllerContact;
extern int D_L00_001A8F00;
extern int D_L00_001A8F00_gp SDATA(D_L00_001A8F00);
extern int D_L00_001AEDD0[] __attribute__((sda));
extern int D_L00_001AEDD0_gp[2] SDATA(D_L00_001AEDD0);
extern int D_L00_001AED30 __attribute__((sda)),D_L00_001AED34 __attribute__((sda));
extern float D_L00_001AED64 __attribute__((sda));
extern int D_L00_001B1BE8 MACRO_ADDR;
extern float D_L00_001B18E4,D_L00_001B18E0;
extern int D_00138324 NOT_SDA,D_001386A4 NOT_SDA;
extern char *D_L00_001AC0C0;
extern char D_L00_001A8F20[] MACRO_ADDR;
extern ControllerContact D_L00_001BF200;
extern ControllerCamera D_L00_001B8DC0;
extern int func_002B49E0(int,int,int,int,unsigned char *);
extern int func_002B4B70(int,int);
extern int func_L00_00384070(char *);
extern void func_00283360(void *),func_002A7750(void *,int,int);
extern void func_L00_003852A0(void *);
extern void func_L00_002E6CF0(void (*)(void *),void *);
extern float func_002AA2E8(float *,float,float),func_002AA340(int *,int,int);
extern void func_L00_00384248(void *),func_L00_00384678(void *);
/* The retail caller passes the object even though the current callee body does not use it. */
extern void func_L00_00384F28(void *),func_L00_00385040(void *),func_L00_00384C20(void *);
extern void func_L00_00384E08(unsigned char *,void *);
extern int func_00277F48(void *,float,int,char *,void *);
extern void func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *);
extern void func_002AFDD8(void *,void *,void *,void *);
extern void func_002A8F70(char *,int,int,void *,void *,float);
extern void func_0029F338(void *),func_002A0F48(void *);
extern void func_L00_003851A0(void *,void *);
extern int func_002E5CF8(int,int,void *);
extern float func_00283B98(float,float),func_00282C48(float);
extern void func_00283698(void *,void *),func_00283098(void *,void *,void *);

/* Update the two-player goal controller and its moving scoring objects. */
void func_L00_00383B90(unsigned char *object)
{
    struct { ControllerVector local; ControllerMatrix inverse; } workspace;
    ControllerOwnerState *owner;
    char *position;
    int index;
    int phase=object[0x20];
    switch (phase) {
    case 0:
        {
            int mode=D_L00_001A8F00_gp;
            if (D_L00_001A8F00==0) {
                D_L00_001AEDD0_gp[0]=0;
                D_L00_001AEDD0[1]=0;
                func_002B49E0(7,1,(int)object,3,0);
                mode=D_L00_001A8F00;
            }
            if (mode==7 && func_L00_00384070((char *)object)) {
                func_00283360(&D_L00_001B8DC0.basis);
                func_002A7750(object,1,-1);
            } else {
                unsigned int timer=*(unsigned short *)(object+0x96);
                unsigned int old=timer++;
                *(unsigned short *)(object+0x96)=timer;
                if (old>=6) func_0029F338(object);
            }
        }
        break;
    case 1:
        {
            float zero=0.0f;
            float step;
            D_L00_001B1BE8=phase;
            func_L00_002E6CF0(func_L00_003852A0,object);
            step=0.13333334028720856f;
            func_002AA2E8(&D_L00_001B18E4,zero,step);
            func_002AA2E8(&D_L00_001B18E0,zero,step);
            func_L00_00384248(object);
            func_L00_00384678(object);
            func_L00_00384F28(object);
            func_L00_00385040(object);
            if (D_L00_001A8F00!=7) {
                func_L00_00384C20(object);
                goto destroy;
            }
            if ((D_00138324&0x810) || (D_001386A4&0x810) ||
                (D_L00_001AEDD0_gp[0] && D_L00_001AEDD0[1]))
                func_002B4B70(0,0);
        }
        break;
    case 2:
        position=(char *)object+0x10;
        func_00282CC0(position,position,*(void **)(object+0x68));
        func_L00_00384E08(object,position);
        if (func_00277F48(position,0.01f,0,*(char **)(object+0xB8),0) &&
            D_L00_001BF200.object) {
            func_00282CF0(&workspace.local,position,D_L00_001BF200.object+0x10);
            func_002AFDD8(D_L00_001BF200.object,&workspace.local,&workspace.local,0);
            if (workspace.local.z>=0.0f && workspace.local.z<=D_L00_001AED64) {
                func_002A8F70(D_L00_001BF200.object,(int)object,0x10000,position,D_L00_001A8F20,1.0f);
                {
                    ControllerOwnerState *state=*(ControllerOwnerState **)(D_L00_001AC0C0+0x68);
                    state->scores[object[0xBC]]+=10;
                }
                func_0029F338(object);
                break;
            }
        }
        if (D_L00_001A8F00==7) {
            int limit=D_L00_001AED30;
            int timer=*(unsigned short *)(object+0x96);
            int old=timer++;
            *(unsigned short *)(object+0x96)=timer;
            if (limit<old)
                func_0029F338(object);
        } else {
destroy:
            func_0029F338(object);
        }
        break;
    case 3:
        {
            char *motion=*(char **)(object+0x68);
            char *vector=(char *)object+0x10;
            char *goal;
            owner=*(ControllerOwnerState **)(D_L00_001AC0C0+0x68);
            *(float *)(object+0xF0)=func_00283B98(*(float *)(object+0xF0),-0.05235988646745682f);
            func_00282CC0(vector,vector,motion);
            func_00283698(&workspace.inverse,&D_L00_001B8DC0.basis);
            func_00282CF0(&workspace.local,vector,&D_L00_001B8DC0.position);
            func_00283098(&workspace.local,&workspace.local,&workspace.inverse);
            if (func_00282C48(workspace.local.y-0.5f)<0.02f) {
                for (index=0,goal=(char *)owner+0x8;index<2;index++) {
                    if (func_00282C48((workspace.local.z-*(float *)goal)-0.045f)<0.05f) {
                        func_L00_003851A0(object,(char *)object+0x10);
                        D_L00_001AEDD0_gp[index]=240;
                        func_002E5CF8(2,0,owner->targets[index]);
                        func_002AA340(&owner->scores[index],0,100);
                        goto destroy;
                    }
                    goal+=0x10;
                }
            }
            func_002A0F48(object);
            if (D_L00_001A8F00==7) {
                int limit=D_L00_001AED34;
                int timer=*(unsigned short *)(object+0x96);
                int old=timer++;
                *(unsigned short *)(object+0x96)=timer;
                if (limit>=old || object[0x31]!=0) break;
            }
            func_0029F338(object);
        }
        break;
    }
}
