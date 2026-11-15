#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_002A7940(void);
extern void func_00282CC0(void *,void *,void *),func_00300190(char *,char *);
extern void func_002FEE70(int,int *,int),func_002FEE50(int),func_0029F338(char *);
/* The callback dispatcher differs in levels 08, 09, 19 and 30. */
extern void ref_L00_004045E8_00(void (*)(char *),char *);
extern void func_00300248(void *,void *),func_002FE880(void *,void *,float);
extern void func_L00_00404DD8(void *,void *),func_L00_00404ED8(void *,void *,void *),func_L00_00404B48(char *);
extern void func_L00_00415740(void *,float,int,int,int,int,int,int,int,int,int);
extern int func_00277F48(void *,int,void *,int,float);
extern char *D_L00_001C3280[];
extern char D_00139568[],D_L00_00262570[],D_L00_001C6F40[];
extern void func_00282CF0(void *,void *,void *),func_00282F20(void *,void *,float);
extern void func_002A8C00(void *,void *,float,int,void *),func_002A8E20(void *,void *);
extern void func_0032D758(void *,int,int),func_00291450(int);
extern int func_L00_002FCF18(void *,float,float,float,float,float);

/* Moves a projectile, applies its explosion hit to nearby objects, and updates
 * its persistent trail record while active. */
void func_L00_004045E8(char *arg)
{
    float old[4],delta[4];
    char hit[48] __attribute__((aligned(16)));
    char *ctx=*(char **)(arg+104);
    int n, count, boosted;
    char **objects;
    char *obj,*entry,*power;
    float force;
    switch (*(unsigned char *)(arg+32)) {
    case 0:
        *(int *)(ctx+24)=-1;
        *(unsigned char *)(arg+32)=1;
        *(float *)(ctx+28)=func_002A7940();
        break;
    case 1:
        qcopy(old,arg+16);
        FastVecAdd(arg+16,(int *)ctx,arg+16);
        func_00300190(arg+16,arg+16);
        func_00300248(ctx,ctx);
        func_002FEE70(*(int *)(ctx+48),(int *)ctx,0);
        func_002FE880(arg+16,ctx,0.00083333335f);
        func_L00_00404DD8(arg,old);
        if (*(float *)(arg+16)<2.0f || *(float *)(arg+16)>1021.0f ||
            *(float *)(arg+20)<2.0f || *(float *)(arg+20)>1021.0f ||
            *(float *)(arg+24)<2.0f || *(float *)(arg+24)>1021.0f) {
            func_002FEE50(*(int *)(ctx+48));
            func_0029F338(arg);
            return;
        }
        break;
    case 2:
        func_L00_00415740(arg+16,0.5f,1,50,40,40,40,90,1,1,1);
        n=func_00277F48(arg+16,0,arg,0,3.0f);
        if(n>0) {
            objects=D_L00_001C3280;
            count=n;
            do {
                obj=*objects;
                if (*(short *)(*(char **)(obj+36)+70)==5 || (*(unsigned short *)(obj+52)&0x4000)) {
                    FastVecSub(delta,obj+16,arg+16);
                    vec_scale_to_length(delta,delta,1.0f);
                    vec_scale_to_length(hit,hit,1.0f);
                    force=10.0f;
                    power=D_L00_00262570+224*(unsigned char)D_00139568[32];
                    boosted=*(int *)power && (unsigned char)power[4]==3;
                    if(boosted) force=20.0f;
                    make_hit_descriptor(hit,arg,force,0x810000,delta);
                    *(TI128 *)(hit)=*(TI128 *)(delta);
                    *(float *)(hit+12)=5627.9248046875f;
                    hit[25]=3; *(int *)(hit+32)=1; hit[24]=5;
                    *(unsigned short *)(hit+26)=*(unsigned short *)(obj+170);
                    QueueMobyImpact(obj,hit);
                    StartAttachedEffect(obj,78,*(int *)(*(char **)(ctx+52)+184));
                }
                objects++;
            } while(--count);
        }
        if (*(int *)(ctx+24)!=-1) func_00291450(*(int *)(ctx+24));
        *(int *)(ctx+24)=-1;
        /* Fall through to the shared teardown. */
    case 3:
        func_002FEE50(*(int *)(ctx+48));
        func_0029F338(arg);
        return;
    }
    ref_L00_004045E8_00(func_L00_00404B48,arg);
    *(TI128 *)(delta)=*(TI128 *)(arg+16);
    func_L00_00404ED8(arg,delta,old);
    FastVecAdd((char *)delta,arg+16,ctx+32);
    FastVecAdd(hit,(char *)old,ctx+32);
    func_L00_00404ED8(arg,delta,hit);
    if (*(int *)(ctx+24)==-1)
        *(int *)(ctx+24)=func_L00_002FCF18(arg+16,5.0f,0.0f,1.0f,0.8f,0.25f);
    else {
        entry=D_L00_001C6F40+32**(int *)(ctx+24);
        qcopy(entry+16,arg+16);
        *(float *)(entry+24)+=1.0f;
        *(float *)(entry+28)=5.0f;
        *(float *)entry=1.0f; *(float *)(entry+4)=0.8f;
        *(float *)(entry+8)=0.25f; *(int *)(entry+12)=0;
    }
}
