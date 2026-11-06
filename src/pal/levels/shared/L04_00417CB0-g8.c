#include "common.h"

/* func_PAL_L04_00417CB0, the PAL copy of func_L04_004135B8: the same C, where the 60 Hz lateral timer
 * x * 60.0f becomes (x * 300.0f + 2.0f) * 0.16666667f. */
typedef struct {
 int count; char pad4[12]; float points[0][4];
} Route1006;
typedef struct {
 char pad0[0x310]; float progress;
 int pathIndex, pointIndex;
 char pad31c[0x654-0x31c]; int routeIndex;
 float lateral; int lateralTimer;
 char pad660[0x6a0-0x660]; float routePos[4];
 char pad6b0[0x6d0-0x6b0]; Route1006 *route;
 int fraction; float distance;
} RouteState1006;


#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(void **)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))

extern int D_L04_001B08F0 __attribute__((sda));
extern int D_L04_001A8FE4;
/* Route selection takes the object only; it reads its own state pointer. */
extern void func_PAL_L04_00417578(void *);
extern float func_L04_00410788(void *,void *,void *,void *,int,int);
extern float func_00282E80(void *,void *);
extern float func_00283CE0(int);
extern float func_00283248(float,float);
extern float func_00283C80(float,float);
extern float func_002A7878(float,float);
extern int func_00283CF0(float);
extern float func_00283B98(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_L04_00400AB0(void *,void *,int);
extern void func_002C96F8(float,float,void *,void *,void *,void *);
extern void func_00282CD8(void *,void *,void *);

/* Advance the sampled route and update its bounded lateral offset. */
void func_PAL_L04_00417CB0(char *m,RouteState1006 *s) {
 int old,i; float d,t; float v[4] __attribute__((aligned(16))); float out[4] __attribute__((aligned(16)));
 func_PAL_L04_00417578(m);
 s->progress=func_L04_00410788(m,s,&s->pathIndex,&s->pointIndex,D_L04_001A8FE4,D_L04_001B08F0);
 old=s->routeIndex;
 d=func_00282E80(&s->routePos[0],m+0x10);
 if (D_L04_001B08F0 ? d<20.0f : d<5.0f) {
  s->distance+=(D_L04_001B08F0 ? 20.0f:5.0f)-d;
  if (s->distance>s->route->points[0][3]*func_00283CE0(s->route->count))
   s->distance-=s->route->points[0][3]*func_00283CE0(s->route->count);
  func_002C96F8(s->distance,s->route->points[0][3],s->route,&s->routeIndex,&s->fraction,s->routePos);
 } else {
  func_002C96F8(s->distance,s->route->points[0][3],s->route,&s->routeIndex,&s->fraction,s->routePos);
 }
 {
  t=func_00283248(s->routePos[0]-F(m,0x10),s->routePos[1]-F(m,0x14));
  if(func_00283C80(F(m,0xf8),t)>1.0471977f) {
   t=func_00283CE0(func_L04_00400AB0(m,s->route,0))*s->route->points[0][3];
   s->distance=t+(D_L04_001B08F0?20.0f:5.0f);
   func_002C96F8(s->distance,s->route->points[0][3],s->route,&s->routeIndex,&s->fraction,s->routePos);
  }
 }
 for(i=old;i<=s->routeIndex;i++) {
  float knot=s->route->points[i][3];
  if(knot>=1000.0f) {
   s->lateral+=func_002A7878(-0.25f,0.25f);
   if(s->lateral>1.5f) s->lateral=1.5f;
   if(s->lateral<-1.5f) s->lateral=-1.5f;
   s->lateralTimer=func_00283CF0((func_002A7878(3.0f,6.0f)*300.0f+2.0f)*0.16666667f);
  } else if(knot<=-1000.0f) { s->lateral=0; s->lateralTimer=-1000; }
 }
 if(s->lateralTimer>0 && --s->lateralTimer==-1) {
  s->lateral+=func_002A7878(-0.25f,0.25f);
  if(s->lateral>1.5f) s->lateral=1.5f;
  if(s->lateral<-1.5f) s->lateral=-1.5f;
  s->lateralTimer=func_00283CF0((func_002A7878(3.0f,6.0f)*300.0f+2.0f)*0.16666667f);
 }
 v[0]=func_00283180(func_00283B98(F(m,0xf8),1.5707965f))*s->lateral*0.15f;
 v[1]=func_00283198(func_00283B98(F(m,0xf8),1.5707965f))*s->lateral*0.15f;
 v[2]=0;
 func_00282CD8(out,s->routePos,v);
}

