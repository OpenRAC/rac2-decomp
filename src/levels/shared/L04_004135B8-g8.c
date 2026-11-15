#include "common.h"
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
extern void func_L04_00412EC0(void *);
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
void func_L04_004135B8(char *bike,RouteState1006 *state) {
 int oldRouteIndex,i; float gap,angle; float v[4] __attribute__((aligned(16))); float out[4] __attribute__((aligned(16)));
 UpdateLinkedRouteSelection(bike);
 state->progress=UpdateNearestRoutePoint(bike,state,&state->pathIndex,&state->pointIndex,gCurrentLap,D_L04_001B08F0);
 oldRouteIndex=state->routeIndex;
 gap=vec_distance_xy(&state->routePos[0],bike+0x10);
 if (D_L04_001B08F0 ? gap<20.0f : gap<5.0f) {
  state->distance+=(D_L04_001B08F0 ? 20.0f:5.0f)-gap;
  if (state->distance>state->route->points[0][3]*IntToFloat(state->route->count))
   state->distance-=state->route->points[0][3]*IntToFloat(state->route->count);
  SampleKeyTrack(state->distance,state->route->points[0][3],state->route,&state->routeIndex,&state->fraction,state->routePos);
 } else {
  SampleKeyTrack(state->distance,state->route->points[0][3],state->route,&state->routeIndex,&state->fraction,state->routePos);
 }
 {
  angle=FastMatrixHelperA(state->routePos[0]-F(bike,0x10),state->routePos[1]-F(bike,0x14));
  if(FastDiffRots(F(bike,0xf8),angle)>1.0471977f) {
   angle=IntToFloat(FindNearestRoutePointIndex(bike,state->route,0))*state->route->points[0][3];
   state->distance=angle+(D_L04_001B08F0?20.0f:5.0f);
   SampleKeyTrack(state->distance,state->route->points[0][3],state->route,&state->routeIndex,&state->fraction,state->routePos);
  }
 }
 for(i=oldRouteIndex;i<=state->routeIndex;i++) {
  float knot=state->route->points[i][3];
  if(knot>=1000.0f) {
   state->lateral+=RandomFloatRange(-0.25f,0.25f);
   if(state->lateral>1.5f) state->lateral=1.5f;
   if(state->lateral<-1.5f) state->lateral=-1.5f;
   state->lateralTimer=FloatToInt(RandomFloatRange(3.0f,6.0f)*60.0f);
  } else if(knot<=-1000.0f) { state->lateral=0; state->lateralTimer=-1000; }
 }
 if(state->lateralTimer>0 && --state->lateralTimer==-1) {
  state->lateral+=RandomFloatRange(-0.25f,0.25f);
  if(state->lateral>1.5f) state->lateral=1.5f;
  if(state->lateral<-1.5f) state->lateral=-1.5f;
  state->lateralTimer=FloatToInt(RandomFloatRange(3.0f,6.0f)*60.0f);
 }
 v[0]=FastSinOrCosA(FastAddRotations(F(bike,0xf8),1.5707965f))*state->lateral*0.15f;
 v[1]=FastSinOrCosB(FastAddRotations(F(bike,0xf8),1.5707965f))*state->lateral*0.15f;
 v[2]=0;
 add_vectors(out,state->routePos,v);
}

