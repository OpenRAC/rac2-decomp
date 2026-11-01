#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 position,angles,delta; } MovingPathWorkspace;
extern char *D_L16_001FE7C0[];
extern char D_L16_002A4570[];
extern float D_00189E20[];
extern void func_0026FEB8(const char *,...);
extern void func_002A7750(unsigned char *,int,int);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_00282E48(void *,void *);
extern float func_00282E80(void *,void *);
extern float func_00282C48(float);
extern void func_002AD6F0(void *,void *,void *,void *);

void func_PAL_L16_0041DC38(char *object)
{
    MovingPathWorkspace local;
    char *state=*(char **)(object+0x68);
    char *path,*point;
    int index;
    qcopy(&local.position,(object+0x10));
    qcopy(&local.angles,(object+0xf0));
    switch(*(unsigned char *)(object+0x20)) {
    case 0: {
        char *initialPath;
        index=*(int *)(state+0x60);
        initialPath=D_L16_001FE7C0[index];
        qcopy((object+0x10),(initialPath+0x10));
        *(int *)(state+0x6c)=0;
        *(float *)(state+0x68)*=0.020000001f;
        if(index==-1) func_0026FEB8(D_L16_002A4570,*(short *)(object+0xaa),*(short *)(object+0xb2));
        func_002A7750((unsigned char *)object,1,-1);
        break;
    }
    case 1:
        if(*(unsigned char *)(object+0xbc)!=0) func_002A7750((unsigned char *)object,2,-1);
        break;
    case 2:
        path=D_L16_001FE7C0[*(int *)(state+0x60)];
        point=path+0x20+*(int *)(state+0x6c)*0x10;
        func_00282CF0(&local.delta,point,object+0x10);
        func_00282F20(&local.delta,&local.delta,*(float *)(state+0x68));
        func_00282CC0(object+0x10,object+0x10,&local.delta);
        if(func_00282E48(object+0x10,path+0x20+*(int *)(state+0x6c)*0x10)<=*(float *)(state+0x68)*0.88f) (*(int *)(state+0x6c))++;
        if(*(int *)(state+0x6c)>=*(int *)path-1) func_002A7750((unsigned char *)object,3,-1);
        break;
    case 3:
        if(*(int *)(state+0x64)<=*(unsigned short *)(object+0x96)) func_002A7750((unsigned char *)object,4,-1);
        break;
    case 4:
        path=D_L16_001FE7C0[*(int *)(state+0x60)];

        if(D_00189E20[34]<*(float *)(object+0x18)) {
            if(func_00282E80(object+0x10,D_00189E20+32)<3.0f && func_00282C48(*(float *)(object+0x18)-D_00189E20[34])<2.5f) goto skipMovement;
        }
        {
            func_00282CF0(&local.delta,path+*(int *)(state+0x6c)*0x10,object+0x10);
            func_00282F20(&local.delta,&local.delta,*(float *)(state+0x68));
            func_00282CC0(object+0x10,object+0x10,&local.delta);
        }
        skipMovement:
        if(func_00282E48(object+0x10,path+*(int *)(state+0x6c)*0x10)<=*(float *)(state+0x68)*0.88f) (*(int *)(state+0x6c))--;
        if(*(int *)(state+0x6c)<=0) {
            object[0xbc]=0;
            func_002A7750((unsigned char *)object,1,-1);
        }
        break;
    }
    (*(short *)(object+0x96))++;
    func_00282CF0(&local.delta,object+0x10,&local.position);
    func_002AD6F0(state+0x20,&local.delta,&local.angles,object+0xf0);
}
