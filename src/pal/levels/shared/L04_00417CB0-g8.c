#include "common.h"

/* func_PAL_L04_00417CB0, the PAL copy of func_L04_004135B8: the same C, where the 60 Hz lateral timer
 * x * 60.0f becomes (x * 300.0f + 2.0f) * 0.16666667f. */
typedef struct {
 int count; char pad4[12]; float points[0][4];
} Route1006;
typedef struct {
 char pad0[0x310]; float progress;
 int path_index, point_index;
 char pad31c[0x654-0x31c]; int route_index;
 float lateral; int lateral_timer;
 char pad660[0x6a0-0x660]; float route_pos[4];
 char pad6b0[0x6d0-0x6b0]; Route1006 *route;
 int fraction; float distance;
} RouteState1006;


#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(void **)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))

extern int g_race_bike_mode __attribute__((sda));
extern int g_current_lap;
/* Route selection takes the object only; it reads its own state pointer. */
extern void update_linked_route_selection_pal(void *);
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
void hoverbike_update_route_steering_pal(char *moby,RouteState1006 *s) {
 int old,i; float d,t; float v[4] __attribute__((aligned(16))); float out[4] __attribute__((aligned(16)));
 update_linked_route_selection_pal(moby);
 s->progress=UpdateNearestRoutePoint(moby,s,&s->path_index,&s->point_index,g_current_lap,g_race_bike_mode);
 old=s->route_index;
 d=vec_distance_xy(&s->route_pos[0],moby+0x10);
 if (g_race_bike_mode ? d<20.0f : d<5.0f) {
  s->distance+=(g_race_bike_mode ? 20.0f:5.0f)-d;
  if (s->distance>s->route->points[0][3]*IntToFloat(s->route->count))
   s->distance-=s->route->points[0][3]*IntToFloat(s->route->count);
  anim_sample_key_track(s->distance,s->route->points[0][3],s->route,&s->route_index,&s->fraction,s->route_pos);
 } else {
  anim_sample_key_track(s->distance,s->route->points[0][3],s->route,&s->route_index,&s->fraction,s->route_pos);
 }
 {
  t=mat_fast_helper_a(s->route_pos[0]-F(moby,0x10),s->route_pos[1]-F(moby,0x14));
  if(FastDiffRots(F(moby,0xf8),t)>1.0471977f) {
   t=IntToFloat(FindNearestRoutePointIndex(moby,s->route,0))*s->route->points[0][3];
   s->distance=t+(g_race_bike_mode?20.0f:5.0f);
   anim_sample_key_track(s->distance,s->route->points[0][3],s->route,&s->route_index,&s->fraction,s->route_pos);
  }
 }
 for(i=old;i<=s->route_index;i++) {
  float knot=s->route->points[i][3];
  if(knot>=1000.0f) {
   s->lateral+=math_random_float_range(-0.25f,0.25f);
   if(s->lateral>1.5f) s->lateral=1.5f;
   if(s->lateral<-1.5f) s->lateral=-1.5f;
   s->lateral_timer=FloatToInt((math_random_float_range(3.0f,6.0f)*300.0f+2.0f)*0.16666667f);
  } else if(knot<=-1000.0f) { s->lateral=0; s->lateral_timer=-1000; }
 }
 if(s->lateral_timer>0 && --s->lateral_timer==-1) {
  s->lateral+=math_random_float_range(-0.25f,0.25f);
  if(s->lateral>1.5f) s->lateral=1.5f;
  if(s->lateral<-1.5f) s->lateral=-1.5f;
  s->lateral_timer=FloatToInt((math_random_float_range(3.0f,6.0f)*300.0f+2.0f)*0.16666667f);
 }
 v[0]=math_fast_sin_or_cos_a(FastAddRotations(F(moby,0xf8),1.5707965f))*s->lateral*0.15f;
 v[1]=math_fast_sin_or_cos_b(FastAddRotations(F(moby,0xf8),1.5707965f))*s->lateral*0.15f;
 v[2]=0;
 add_vectors(out,s->route_pos,v);
}

