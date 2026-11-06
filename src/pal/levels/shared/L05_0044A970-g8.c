/* func_PAL_L05_0044A970, the PAL copy of func_L05_004445E8: the same C, with the chosen limit scaled to 50 Hz. */
#include "common.h"
extern int func_L05_0037AA88(int);
extern float *func_002AB1F0(void *);
extern void *func_L05_00444840(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282DF0(void *),func_00282DB0(void *,void *);
extern float func_002831B0(float),func_00282C48(float);
extern int func_002761F8(void *,void *,int,void *,int);
extern char D_L05_002A1800[];
extern int D_L05_001B1B0C __attribute__((sda)),D_L05_001B1B08 __attribute__((sda));
extern float D_L05_001B1B14 __attribute__((sda));
extern int D_L05_001B2048;
extern char D_L05_001B96C0[];
void func_PAL_L05_0044A970(char *object)
{
    float delta[4];
    char *state=*(char **)(object+0x68);
 int index=func_L05_0037AA88(1);
    char *table;
    int limit;
    char *target;
    float *health;
    float length,dot;
    if(index<0 || *(int *)((table=D_L05_002A1800)+index*40+20)<=0) {
        *(int *)(state+0x18)=0; *(int *)(state+0x14)=0; *(int *)(state+0x1c)=0;
        return;
    }
    limit=((s32)(*(int *)(table+0x168)?D_L05_001B1B0C:D_L05_001B1B08) * 5 + 2) / 6;
    target=*(char **)(state+0x18);
    if(!target) {
        char *nextTarget;
        *(int *)(object+0x98)=0;
        nextTarget=func_L05_00444840(state+0x20,0,*(void **)(state+0x14));
        *(int *)(object+0x98)=*(int *)(*(char **)(object+0x24)+0x10);
        if(nextTarget==*(char **)(state+0x14)) {
            if(++*(int *)(state+0x1c)<=limit) return;
            *(int *)(state+0x1c)=limit;
            goto clamp;
        }
        *(char **)(state+0x14)=nextTarget; goto reset;
    }
    {
        if ((u8)target[0x20] == 0xfe) goto invalid;
        if ((u8)target[0x20] == 0xfd) goto invalid;
        health=func_002AB1F0(target);
        if(health && *health<=0.0f) {
            invalid:
            *(int *)(state+0x1c)=*(int *)(state+0x18)=0; return;
        }
        func_00282CF0(delta,*(char **)(state+0x18)+0x10,object+0x10);
        length=func_00282DF0(delta);
        dot=func_00282DB0(object+0xc0,delta);
        if(length==0.0f) goto zeroLength;
        {
            *(int *)(object+0x98)=0;
            if(func_00282C48(1.5707964f-func_002831B0(dot/length))>D_L05_001B1B14*0.017453294f ||
               (D_L05_001B2048%5==0 && func_002761F8(D_L05_001B96C0,*(char **)(state+0x18)+0x10,16,*(void **)(state+0x18),0))) {
                *(int *)(state+0x18)=0; *(int *)(state+0x14)=0; *(int *)(state+0x1c)=0;
            } else { if(++*(int *)(state+0x1c)>limit) *(int *)(state+0x1c)=limit; }
            *(int *)(object+0x98)=*(int *)(*(char **)(object+0x24)+0x10);
        }
    }
    goto clamp;
zeroLength:
    *(int *)(state+0x18)=0;
    *(int *)(state+0x14)=0;
reset:
    *(int *)(state+0x1c)=0;
clamp:
    if(*(int *)(state+0x1c)>limit) *(int *)(state+0x1c)=limit;
}
