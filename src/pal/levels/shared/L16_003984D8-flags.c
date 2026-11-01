#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 difference, local, previous, velocity, lateral; } MotionWorkspace;
extern char D_00189E20[];
extern float D_L16_001AF43C __attribute__((sda));
extern void func_L00_002B39F0(int,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002AFDD8(char *,char *,char *,char *);
extern void func_00282F70(void *,void *,float);
extern void func_00283098(void *,void *,void *);
extern float func_00282DB0(void *,void *);
extern float func_002AA2E8(float *,float,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282A88(void *,int);
extern void func_002AC9F8(float *,float);

void func_PAL_L16_00398C40(char *object)
{
    MotionWorkspace local;
    char *state=*(char **)(object+0x68);
    float alignment;
    func_L00_002B39F0(0,1.0f);
    qcopy(&local.previous,(D_00189E20+0x190));
    func_00282CF0(&local.difference,D_00189E20+0x80,object+0x10);
    func_00282DD8((D_00189E20+0x190),&local.difference,object+0xe0);
    func_00282F20((D_00189E20+0x190),(D_00189E20+0x190),1.0f);
    func_002AFDD8(object,(char *)&local.local,(char *)&local.difference,0);
    func_00282F70(&local.velocity,&local.local,D_L16_001AF43C);
    func_00283098(&local.velocity,&local.velocity,object+0xc0);
    alignment=func_00282DB0(&local.previous,(D_00189E20+0x190));
    if (*(float *)(D_00189E20+0x24b8)>0.5f && alignment>0.5f)
        func_002AA2E8((float *)(state+0x30),alignment*0.10000001f,0.002f);
    else func_002AA2E8((float *)(state+0x30),0.0f,0.002f);
    if (*(float *)(state+0x30)!=0.0f) {
        func_00282F20(&local.lateral,(D_00189E20+0x190),*(float *)(state+0x30));
        func_00282CC0(&local.velocity,&local.velocity,&local.lateral);
        *(float *)(state+0x34)+=*(float *)(state+0x30)/(*(float *)(state+8)*6.28318548f);
        if (*(float *)(state+0x34)>1.0f) *(float *)(state+0x34)=1.0f;
    }
    func_00282CC0(&local.velocity,&local.velocity,object+0x10);
    func_00282A88(D_00189E20+0xf0,0xa0);
    func_00282CF0(D_00189E20+0xf0,&local.velocity,D_00189E20+0x80);
    func_002AC9F8((float *)(D_00189E20+0xf0),0.120000005f);
}
