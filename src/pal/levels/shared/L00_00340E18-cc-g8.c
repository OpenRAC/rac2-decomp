/* func_PAL_L00_00340E18, the PAL copy of func_L00_0033EA00: the same C, where rename func_002BCB00 becomes func_PAL_002BD790; scale func_002A7820(15,30). */
#include "common.h"
typedef int EffectQuad __attribute__((mode(TI)));
#define FI(p,o) (*(int *)((char *)(p)+(o)))
#define FF(p,o) (*(float *)((char *)(p)+(o)))
#define FS(p,o) (*(short *)((char *)(p)+(o)))
#define FB(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern int func_00282978(short *);
extern void func_002B9180(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_L00_0031C998(int,int,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00300190(char *,char *);
extern float func_002A7878(float,float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern int func_002A7820(int,int);
extern void func_PAL_002BD790(void *,void *,int,int,int,int,int,int,float,int);
extern int D_L00_001B19C8 MACRO_ADDR;
void func_PAL_L00_00340E18(char *p)
{
    float old[4], velocity[4], random[4];
    char *q=p+32;
    char *pos;
    char *initial;
    float t, length;
    int life;
    if (func_00282978((short *)(p+10))) { func_002B9180(p); return; }
    initial=p+16;
    t=func_00283CE0(FS(p,10));
    t=t/func_00283CE0(FS(q,24));
    FI(p,4)=func_L00_0031C998(FI(q,20),FI(q,16),t);
    func_00282CC0(initial,initial,q);
    FF(q,8)-=FF(q,12);
    qcopy(old,initial);
    pos=initial;
    if (FF(p,28)!=0.0f) {
        if (FF(p,28)==2.0f) func_00300190(pos,pos);
        FF(p,28)=2.0f;
    }
    if (FS(q,26) && (D_L00_001B19C8&1)) {
        *(EffectQuad *)random=0;
        random[0]=func_002A7878(-1.0f,1.0f);
        random[1]=func_002A7878(-1.0f,1.0f);
        random[2]=func_002A7878(-1.0f,1.0f);
        *(EffectQuad *)velocity=*(EffectQuad *)random;
        length=func_00282DF0(q);
        func_00282F20(velocity,velocity,length*func_002A7878(0.15f,0.25f));
        func_00282CC0(velocity,velocity,q);
        func_00282D30(velocity,velocity,func_002A7878(0.75f,0.95f));
        life=(((int)(func_002A7820(15,30)) * 5 + 2) / 6);
        func_PAL_002BD790(pos,velocity,FI(p,4),FI(q,20),life,0,FB(p,2),FB(p,3),FF(p,12),func_00283CF0(FF(p,28)));
    } else func_00282D30(q,q,0.96f);
}
