#include "include_asm.h"

#include "common.h"
extern char *func_002B9030(int);
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern void func_00283658(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern int func_00283CF0(float);
extern char *D_L00_001FE9B0;
#define FI(p, o) (*(int *)((char *)(p) + (o)))
#define FF(p, o) (*(float *)((char *)(p) + (o)))
#define FS(p, o) (*(short *)((char *)(p) + (o)))
#define FB(p, o) (*(unsigned char *)((char *)(p) + (o)))

void func_PAL_L00_00337918(char *position, char *matrix, float speed)
{
    float local[4], offset[4], velocity[4], inverse[16];

    char *p=func_002B9030(28);
    int r,g,b;
    char *q;
    if (p) {
        q=p+32;
        offset[0]=func_002A7878(-0.03f,0.03f);
        offset[1]=func_002A7878(-0.03f,0.03f);
        offset[2]=0;
        if (matrix) {
            func_00283658(inverse,matrix);
            func_002830C0(local,offset,inverse);
            func_00282CC0(p+16,local,position);
        } else func_00282CC0(p+16,offset,position);
        FF(p,24)-=0.05f;
        r=func_001163B0()%96; if (!r) r=1;
        g=(func_001163B0()%r)%64; if (!g) g=1;
        b=(func_001163B0()%g)%48;
        FI(p,4)=(r+143)|((g+143)<<8)|((b+111)<<16);
        FB(p,9)=func_00283CF0(4.0f)+64;
        FB(p,3)=72; FB(p,1)=0; FB(p,8)=0;
        FB(p,2)=FB(D_L00_001FE9B0,0);
        FF(q,4)=func_002A7878(0.0f,0.02234560064971447f)+0.00001f;
        FF(p,12)=func_002A7878(10080.0f,19950.0f);
        FF(q,8)=0.0f; FS(p,10)=210; FF(q,12)=1.0f;
        qzero_nc(velocity);
        if (matrix) {
            velocity[0]=speed; velocity[2]=-0.0025f;
            func_00283098(q+16,velocity,matrix);
        } else {
            FF(q,16)=func_002A7878(-speed,speed);
            FF(q,20)=func_002A7878(-speed,speed);
            FF(q,24)=-0.0025f;
        }
    }
}


