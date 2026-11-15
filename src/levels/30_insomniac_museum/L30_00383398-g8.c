#include "common.h"

typedef struct { float x,y,z,w; } GridVec;
extern int D_L30_001AEBC0 __attribute__((sda));
extern float D_L30_001AEBD0 __attribute__((sda)), D_L30_001AEBD4 __attribute__((sda)), D_L30_001AEBD8 __attribute__((sda)), D_L30_001AEBDC __attribute__((sda));
extern float D_L30_001AEBE0 __attribute__((sda)), D_L30_001AEBE4 __attribute__((sda)), D_L30_001AEBE8 __attribute__((sda)), D_L30_001AEBEC __attribute__((sda));
extern float g_museum_water_heights[][24][24];
extern float g_museum_water_grid_points[24][24][2];
extern float g_museum_water_refract_uv[24][24][2];
extern float g_museum_water_reflect_uv[24][24][2];
extern unsigned char g_museum_water_brightness[24][24];
extern GridVec D_L30_001B9DC0;
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern float FastVecDot(void *,void *);
extern float square_root(float);
extern void FastVecScale(void *,void *,float);
extern void vec_fast_normalize(void *,void *,void *);
extern float FastVecLength(void *);

/* Derive refraction/reflection coordinates and brightness for the 24-by-24 grid. */
void UpdateMuseumWaterGridOptics(GridVec *origin)
{
    GridVec p, a, b, n, v, r, scaled, negative;
    float quarter=0.25f;
    float ox=origin->x, oy=origin->y;
    int i,j;
    for(i=0;i<24;i++) {
        for(j=0;j<24;j++) {
            float dot,ratio,square,t,brightness,upper,lower;
            p.x=g_museum_water_grid_points[i][j][0];
            p.y=g_museum_water_grid_points[i][j][1];
            p.z=g_museum_water_heights[D_L30_001AEBC0][i][j];
            p.w=1.0f;
            if(!(i<23 && j<23)) { n.x=0; n.y=0; n.z=1; } else {
                a.x=p.x-g_museum_water_grid_points[i][j+1][0];
                a.y=p.y-g_museum_water_grid_points[i][j+1][1];
                a.z=p.z-g_museum_water_heights[D_L30_001AEBC0][i][j+1];
                b.x=g_museum_water_grid_points[i][j+1][0]-g_museum_water_grid_points[i+1][j][0];
                b.y=g_museum_water_grid_points[i][j+1][1]-g_museum_water_grid_points[i+1][j][1];
                b.z=g_museum_water_heights[D_L30_001AEBC0][i][j+1]-g_museum_water_heights[D_L30_001AEBC0][i+1][j];
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
            t=(D_L30_001AEBD8+g_museum_water_heights[D_L30_001AEBC0][i][j])/r.z;
            g_museum_water_refract_uv[i][j][0]=(p.x+r.x*t-ox)*quarter+0.5f;
            g_museum_water_refract_uv[i][j][1]=(p.y+r.y*t-oy)*quarter+0.5f;
            if(g_museum_water_refract_uv[i][j][0]>4.0f) g_museum_water_refract_uv[i][j][0]=4.0f;
            else if(g_museum_water_refract_uv[i][j][0]<-4.0f) g_museum_water_refract_uv[i][j][0]=-4.0f;
            if(g_museum_water_refract_uv[i][j][1]>4.0f) g_museum_water_refract_uv[i][j][1]=4.0f;
            else if(g_museum_water_refract_uv[i][j][1]<-4.0f) g_museum_water_refract_uv[i][j][1]=-4.0f;
            vec_scale_to_length(&v,&v,D_L30_001AEBDC);
            FastVecScale(&negative,&n,-1.0f);
            vec_fast_normalize(&r,&v,&negative);
            t=1.0f/(FastVecLength(&r)*2.0f);
            g_museum_water_reflect_uv[i][j][0]=r.x*D_L30_001AEBE0*t+0.5f;
            g_museum_water_reflect_uv[i][j][1]=r.y*D_L30_001AEBE0*t+0.5f;
            dot=FastVecDot(&v,&n);
            square=dot*dot;
            t=FastVecDot(&v,&v);
            /* Keep the complete brightness update on one debug source line:
               address arithmetic for the final store is interleaved with the
               bounds loads, and retail has no division label between them. */
            lower=D_L30_001AEBE8; upper=D_L30_001AEBEC; brightness=D_L30_001AEBE4*square/t; brightness=upper<brightness?upper:brightness; brightness=lower>brightness?lower:brightness; g_museum_water_brightness[i][j]=~(int)brightness;
        }
    }
}
