#include "common.h"

typedef struct { float x,y,z,w; } GridVec;
extern int D_L30_001AEBC0 __attribute__((sda));
extern float D_L30_001AEBD0 __attribute__((sda)), D_L30_001AEBD4 __attribute__((sda)), D_L30_001AEBD8 __attribute__((sda)), D_L30_001AEBDC __attribute__((sda));
extern float D_L30_001AEBE0 __attribute__((sda)), D_L30_001AEBE4 __attribute__((sda)), D_L30_001AEBE8 __attribute__((sda)), D_L30_001AEBEC __attribute__((sda));
extern float D_L30_00233A60[][24][24];
extern float D_L30_00235560[24][24][2];
extern float D_L30_00236760[24][24][2];
extern float D_L30_00237960[24][24][2];
extern unsigned char D_L30_00238B60[24][24];
extern GridVec D_L30_001B9DC0;
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282DB0(void *,void *);
extern float func_00282C10(float);
extern void func_00282D30(void *,void *,float);
extern void func_00283028(void *,void *,void *);
extern float func_00282DF0(void *);

/* Derive refraction/reflection coordinates and brightness for the 24-by-24 grid. */
void func_L30_00383398(GridVec *origin)
{
    GridVec p, a, b, n, v, r, scaled, negative;
    float quarter=0.25f;
    float ox=origin->x, oy=origin->y;
    int i,j;
    for(i=0;i<24;i++) {
        for(j=0;j<24;j++) {
            float dot,ratio,square,t,brightness,upper,lower;
            p.x=D_L30_00235560[i][j][0];
            p.y=D_L30_00235560[i][j][1];
            p.z=D_L30_00233A60[D_L30_001AEBC0][i][j];
            p.w=1.0f;
            if(!(i<23 && j<23)) { n.x=0; n.y=0; n.z=1; } else {
                a.x=p.x-D_L30_00235560[i][j+1][0];
                a.y=p.y-D_L30_00235560[i][j+1][1];
                a.z=p.z-D_L30_00233A60[D_L30_001AEBC0][i][j+1];
                b.x=D_L30_00235560[i][j+1][0]-D_L30_00235560[i+1][j][0];
                b.y=D_L30_00235560[i][j+1][1]-D_L30_00235560[i+1][j][1];
                b.z=D_L30_00233A60[D_L30_001AEBC0][i][j+1]-D_L30_00233A60[D_L30_001AEBC0][i+1][j];
                a.w=1; b.w=1;
                func_00282DD8(&n,&a,&b);
                func_00282F20(&n,&n,1.0f);
            }
            n.w=1; func_00282CC0(&p,&p,origin);
            func_00282CF0(&v,&D_L30_001B9DC0,&p); v.w=1;
            func_00282F20(&scaled,&v,D_L30_001AEBDC);
            dot=func_00282DB0(&n,&v);
            square=dot*dot;
            ratio=D_L30_001AEBD0 / -D_L30_001AEBD4;
            t=func_00282C10(1.0f-ratio*ratio*(1.0f-square));
            func_00282D30(&r,&n,ratio*dot-t);
            func_00282D30(&scaled,&scaled,ratio);
            func_00282CF0(&r,&r,&scaled);
            t=(D_L30_001AEBD8+D_L30_00233A60[D_L30_001AEBC0][i][j])/r.z;
            D_L30_00236760[i][j][0]=(p.x+r.x*t-ox)*quarter+0.5f;
            D_L30_00236760[i][j][1]=(p.y+r.y*t-oy)*quarter+0.5f;
            if(D_L30_00236760[i][j][0]>4.0f) D_L30_00236760[i][j][0]=4.0f;
            else if(D_L30_00236760[i][j][0]<-4.0f) D_L30_00236760[i][j][0]=-4.0f;
            if(D_L30_00236760[i][j][1]>4.0f) D_L30_00236760[i][j][1]=4.0f;
            else if(D_L30_00236760[i][j][1]<-4.0f) D_L30_00236760[i][j][1]=-4.0f;
            func_00282F20(&v,&v,D_L30_001AEBDC);
            func_00282D30(&negative,&n,-1.0f);
            func_00283028(&r,&v,&negative);
            t=1.0f/(func_00282DF0(&r)*2.0f);
            D_L30_00237960[i][j][0]=r.x*D_L30_001AEBE0*t+0.5f;
            D_L30_00237960[i][j][1]=r.y*D_L30_001AEBE0*t+0.5f;
            dot=func_00282DB0(&v,&n);
            square=dot*dot;
            t=func_00282DB0(&v,&v);
            /* Keep the complete brightness update on one debug source line:
               address arithmetic for the final store is interleaved with the
               bounds loads, and retail has no division label between them. */
            lower=D_L30_001AEBE8; upper=D_L30_001AEBEC; brightness=D_L30_001AEBE4*square/t; brightness=upper<brightness?upper:brightness; brightness=lower>brightness?lower:brightness; D_L30_00238B60[i][j]=~(int)brightness;
        }
    }
}
