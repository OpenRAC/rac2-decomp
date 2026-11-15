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
extern int g_current_lap;
/* Route selection takes the object only; it reads its own state pointer. */
extern void UpdateLinkedRouteSelection(void *);
extern float UpdateNearestRoutePoint(void *,void *,void *,void *,int,int);
extern float vec_distance_xy(void *,void *);
extern float IntToFloat(int);
extern float mat_fast_helper_a(float,float);
extern float FastDiffRots(float,float);
extern float math_random_float_range(float,float);
extern int FloatToInt(float);
extern float FastAddRotations(float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int FindNearestRoutePointIndex(void *,void *,int);
extern void anim_sample_key_track(float,float,void *,void *,void *,void *);
extern void add_vectors(void *,void *,void *);

/* Advance the sampled route and update its bounded lateral offset. */
void hoverbike_update_route_steering(char *bike,RouteState1006 *state) {
 int old_route_index,i; float gap,angle; float v[4] __attribute__((aligned(16))); float out[4] __attribute__((aligned(16)));
 UpdateLinkedRouteSelection(bike);
 state->progress=UpdateNearestRoutePoint(bike,state,&state->pathIndex,&state->pointIndex,g_current_lap,D_L04_001B08F0);
 old_route_index=state->routeIndex;
 gap=vec_distance_xy(&state->routePos[0],bike+0x10);
 if (D_L04_001B08F0 ? gap<20.0f : gap<5.0f) {
  state->distance+=(D_L04_001B08F0 ? 20.0f:5.0f)-gap;
  if (state->distance>state->route->points[0][3]*IntToFloat(state->route->count))
   state->distance-=state->route->points[0][3]*IntToFloat(state->route->count);
  anim_sample_key_track(state->distance,state->route->points[0][3],state->route,&state->routeIndex,&state->fraction,state->routePos);
 } else {
  anim_sample_key_track(state->distance,state->route->points[0][3],state->route,&state->routeIndex,&state->fraction,state->routePos);
 }
 {
  angle=mat_fast_helper_a(state->routePos[0]-F(bike,0x10),state->routePos[1]-F(bike,0x14));
  if(FastDiffRots(F(bike,0xf8),angle)>1.0471977f) {
   angle=IntToFloat(FindNearestRoutePointIndex(bike,state->route,0))*state->route->points[0][3];
   state->distance=angle+(D_L04_001B08F0?20.0f:5.0f);
   anim_sample_key_track(state->distance,state->route->points[0][3],state->route,&state->routeIndex,&state->fraction,state->routePos);
  }
 }
 for(i=old_route_index;i<=state->routeIndex;i++) {
  float knot=state->route->points[i][3];
  if(knot>=1000.0f) {
   state->lateral+=math_random_float_range(-0.25f,0.25f);
   if(state->lateral>1.5f) state->lateral=1.5f;
   if(state->lateral<-1.5f) state->lateral=-1.5f;
   state->lateralTimer=FloatToInt(math_random_float_range(3.0f,6.0f)*60.0f);
  } else if(knot<=-1000.0f) { state->lateral=0; state->lateralTimer=-1000; }
 }
 if(state->lateralTimer>0 && --state->lateralTimer==-1) {
  state->lateral+=math_random_float_range(-0.25f,0.25f);
  if(state->lateral>1.5f) state->lateral=1.5f;
  if(state->lateral<-1.5f) state->lateral=-1.5f;
  state->lateralTimer=FloatToInt(math_random_float_range(3.0f,6.0f)*60.0f);
 }
 v[0]=math_fast_sin_or_cos_a(FastAddRotations(F(bike,0xf8),1.5707965f))*state->lateral*0.15f;
 v[1]=math_fast_sin_or_cos_b(FastAddRotations(F(bike,0xf8),1.5707965f))*state->lateral*0.15f;
 v[2]=0;
 add_vectors(out,state->routePos,v);
}

