#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float D_001B168C;
extern float D_001B1690 __attribute__((sda));
extern unsigned char *D_001F256C[];
typedef struct { float v[4]; int color,endcolor; unsigned char a,c,b,life; float size; } MotionBCB0;
extern int func_002A77E0(int);
extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern int func_001163B0(void);
extern float func_002A7878(float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
char *func_002BBCB0(void *pos,void *velocity,int color,int endcolor,int life,int a,int b,int c,float size,float jitter)
{
    char *p; MotionBCB0 *q;
    float v[4] __attribute__((aligned(16)));
    float r[4] __attribute__((aligned(16)));
    if(!life) return 0;
    {
        if ((D_001B168C>0.85f || D_001B1690>0.85f) && !func_002A77E0(3)) return 0;
        if ((D_001B168C>0.9f || D_001B1690>0.9f) && !func_002A77E0(2)) return 0;
        if ((D_001B168C>1.0f || D_001B1690>1.0f) && !func_002A77E0(1)) return 0;
    }
    p=func_002B9030(11);
    if(p) {
        qcopy(p+16,pos);
        *(int *)(p+4)=color;
        p[9]=FloatToInt(4.0f)-96;
        p[3]=func_002A77E0(100)<20?0x44:0x48;
        p[1]=0;
        *(float *)(p+12)=0;
        q=(MotionBCB0 *)(p+32);
        p[8]=func_001163B0();
        p[2]=D_001F256C[0][0];
        *(TI128 *)r=0;
        r[0]=func_002A7878(-1.0f,1.0f);
        r[1]=func_002A7878(-1.0f,1.0f);
        r[2]=func_002A7878(-1.0f,1.0f);
        *(TI128 *)v=*(TI128 *)r;
        vec_scale_to_length(v,v,jitter);
        FastVecAdd(q,velocity,v);
        q->v[3]=jitter*0.75f;
        *(short *)(p+10)=life;
        q->life=life;q->a=a;
        q->size=size;
        q->color=color;q->endcolor=endcolor;
        q->b=b;q->c=c;
    }
    return p;
}
