#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
typedef struct { Quad16 vector; int owner,flags; unsigned char enabled,kind; unsigned short id; float distance; int active; } CollisionRequest;
typedef struct { Vector128 beam; CollisionRequest request; Vector128 closest; } LaserWorkspace;
extern char D_00188660[];
extern char *D_L16_001BFF58;
extern char *D_0018C0B0;
extern char *D_L16_001B0664 MACRO_ADDR;
extern char *D_L16_001B0F80 MACRO_ADDR;
extern Quad16 D_L16_001A8F20 MACRO_ADDR;
extern float func_00283B98(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern int func_002E5DA0(int,int,char *,int);
extern float func_002AA458(void *,void *,void *,float,float,float);
extern float func_00282E80(void *,void *);
extern void func_002A7750(unsigned char *,int,int);
extern void func_L00_002E6CF0(void (*)(void *),void *);
extern void func_L16_0041CF80(void *);
extern void func_002A8C00(char *,int,int,float,Quad16 *);
extern int func_002761F8(void *,void *,int,void *,void *);
extern float func_L01_00311C18(void *,void *,void *,void *);
extern void func_PAL_L00_003E38E8(int,int);
extern void func_PAL_L00_004071F0(char *,int);

void func_PAL_L16_00421F00(char *object)
{
    LaserWorkspace local;
    char *state=*(char **)(object+0x68);
    char *target;
    char *sound,*sound2,*sound4;
    int handle;
    switch(*(unsigned char *)(object+0x20)) {
    case 0:
        *(float *)(object+0x18)+=0.57f;
        qcopy(state,(object+0x10));
        ((float *)&local.beam)[0]=func_00283180(func_00283B98(*(float *)(object+0xf8),1.570796490f))*9.5f;
        ((float *)&local.beam)[1]=func_00283198(func_00283B98(*(float *)(object+0xf8),1.570796490f))*9.5f;
        ((float *)&local.beam)[2]=0.0f;
        func_00282CC0(state+0x10,((float *)&local.beam),object+0x10);
        *(int *)(state+0x24)=-1;
        *(int *)(state+0x28)=-1;
        func_002A7750((unsigned char *)object,1,-1);
        break;
    case 1:
        sound4=D_00188660+0x70**(int *)(state+0x24);
        if((*(char **)(sound4+0x88))!=object || (*(unsigned char *)(sound4+0x74))==0) *(int *)(state+0x24)=func_002E5DA0(0,4,object,0x113a);
        func_002AA458(object+0x10,state+0x10,state+0x20,0.0016000001f,0.0032000002f,0.080000006f);
        if(func_00282E80(object+0x10,state+0x10)<0.040000003f) func_002A7750((unsigned char *)object,2,-1);
        break;
    case 2:
        sound2=D_00188660+0x70**(int *)(state+0x24);
        if((*(char **)(sound2+0x88))!=object || (*(unsigned char *)(sound2+0x74))==0) *(int *)(state+0x24)=func_002E5DA0(0,4,object,0x113a);
        func_002AA458(object+0x10,state,state+0x20,0.0016000001f,0.0032000002f,0.080000006f);
        if(func_00282E80(object+0x10,state)<0.040000003f) func_002A7750((unsigned char *)object,1,-1);
        break;
    }
    func_L00_002E6CF0(func_L16_0041CF80,object);
    func_002A8C00((char *)&local.request,(int)object,1,4.0f,&D_L16_001A8F20);
    local.request.id=*(unsigned short *)(object+0xaa);
    ((float *)&local.beam)[0]=func_00283180(*(float *)(object+0xf8))*25.0f;
    ((float *)&local.beam)[1]=func_00283198(*(float *)(object+0xf8))*25.0f;
    ((float *)&local.beam)[2]=0.0f;
    func_00282CC0(((float *)&local.beam),object+0x10,((float *)&local.beam));
    if(func_002761F8(object+0x10,((float *)&local.beam),0,object,&local.request)!=0 && D_L16_001BFF58==D_0018C0B0) {
        handle=*(int *)(state+0x28);
        if(handle!=-1) {
            sound=D_00188660+handle*0x70;
            if((*(char **)(sound+0x88))==object && (*(unsigned char *)(sound+0x74))!=0) goto sound_ready;
        }
        *(int *)(state+0x28)=func_002E5DA0(1,0,object,0x113a);
    }
sound_ready:
    target=D_L16_001B0664;
    if(target==0) target=D_L16_001B0F80;
    if(target!=0) {
        func_L01_00311C18(&local.closest,object+0x10,((float *)&local.beam),target+0x10);
        if(func_00282E80(&local.closest,target+0x10)<0.15f) {
            if(*(short *)(target+0xaa)==0xb58) {
                if(*(unsigned char *)(target+0x20)!=5) func_PAL_L00_003E38E8(1,2);
            } else if(*(unsigned char *)(target+0x20)!=5) func_PAL_L00_004071F0((char *)1,2);
        }
    }
}

