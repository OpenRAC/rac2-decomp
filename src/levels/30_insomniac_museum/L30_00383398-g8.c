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
            p.x=gMuseumWaterGridPoints[i][j][0];
            p.y=gMuseumWaterGridPoints[i][j][1];
            p.z=gMuseumWaterHeights[D_L30_001AEBC0][i][j];
            p.w=1.0f;
            if(!(i<23 && j<23)) { n.x=0; n.y=0; n.z=1; } else {
                a.x=p.x-gMuseumWaterGridPoints[i][j+1][0];
                a.y=p.y-gMuseumWaterGridPoints[i][j+1][1];
                a.z=p.z-gMuseumWaterHeights[D_L30_001AEBC0][i][j+1];
                b.x=gMuseumWaterGridPoints[i][j+1][0]-gMuseumWaterGridPoints[i+1][j][0];
                b.y=gMuseumWaterGridPoints[i][j+1][1]-gMuseumWaterGridPoints[i+1][j][1];
                b.z=gMuseumWaterHeights[D_L30_001AEBC0][i][j+1]-gMuseumWaterHeights[D_L30_001AEBC0][i+1][j];
                a.w=1; b.w=1;
                FastVecCross(&n,&a,&b);
                vec_scale_to_length(&n,&n,1.0f);
            }
            n.w=1; FastVecAdd(&p,&p,origin);
            FastVecSub(&v,&D_L30_001B9DC0,&p); v.w=1;
            vec_scale_to_length(&scaled,&v,D_L30_001AEBDC);
            dot=FastVecDot(&n,&v);
            square=dot*dot;
            ratio=D_L30_001AEBD0 / -D_L30_001AEBD4;
            t=square_root(1.0f-ratio*ratio*(1.0f-square));
            FastVecScale(&r,&n,ratio*dot-t);
            FastVecScale(&scaled,&scaled,ratio);
            FastVecSub(&r,&r,&scaled);
            t=(D_L30_001AEBD8+gMuseumWaterHeights[D_L30_001AEBC0][i][j])/r.z;
            gMuseumWaterRefractUv[i][j][0]=(p.x+r.x*t-ox)*quarter+0.5f;
            gMuseumWaterRefractUv[i][j][1]=(p.y+r.y*t-oy)*quarter+0.5f;
            if(gMuseumWaterRefractUv[i][j][0]>4.0f) gMuseumWaterRefractUv[i][j][0]=4.0f;
            else if(gMuseumWaterRefractUv[i][j][0]<-4.0f) gMuseumWaterRefractUv[i][j][0]=-4.0f;
            if(gMuseumWaterRefractUv[i][j][1]>4.0f) gMuseumWaterRefractUv[i][j][1]=4.0f;
            else if(gMuseumWaterRefractUv[i][j][1]<-4.0f) gMuseumWaterRefractUv[i][j][1]=-4.0f;
            vec_scale_to_length(&v,&v,D_L30_001AEBDC);
            FastVecScale(&negative,&n,-1.0f);
            FastVectorNormalize(&r,&v,&negative);
            t=1.0f/(FastVecLength(&r)*2.0f);
            gMuseumWaterReflectUv[i][j][0]=r.x*D_L30_001AEBE0*t+0.5f;
            gMuseumWaterReflectUv[i][j][1]=r.y*D_L30_001AEBE0*t+0.5f;
            dot=FastVecDot(&v,&n);
            square=dot*dot;
            t=FastVecDot(&v,&v);
            /* Keep the complete brightness update on one debug source line:
               address arithmetic for the final store is interleaved with the
               bounds loads, and retail has no division label between them. */
            lower=D_L30_001AEBE8; upper=D_L30_001AEBEC; brightness=D_L30_001AEBE4*square/t; brightness=upper<brightness?upper:brightness; brightness=lower>brightness?lower:brightness; gMuseumWaterBrightness[i][j]=~(int)brightness;
        }
    }
}
