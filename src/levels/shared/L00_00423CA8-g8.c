#include "common.h"
extern char *g_follow_camera_object __attribute__((section(".data")));
extern char D_L00_001BF220_1[],g_collision_position[];
typedef struct { char pad[0x2290]; char *owner; } Player3C;
extern Player3C g_hero_state;
extern void *g_cam_collision_point_mask[] __attribute__((sda));
extern float g_cam_collision_base_radius __attribute__((sda));
extern void vec_clear_128(void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern float fast_vec_dist(void *,void *);
extern float ProjectPointOntoSegment(void *,void *,void *,void *,float);
extern int coll_test_point(void *,void *,void *,float);
extern void cam_compute_push_out(void *,void *,void *,void *,void *,float,float);
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
/* Pushes a camera point out of nearby walls. It tries up to three times and returns 1 if the point had to move. */
int cam_push_point_out_of_walls(char *obj,void *point,int index,float blend,float radius)
{
    float accumulated[4], difference[4], original[4], plane[4], hit[4], endpoint[4], closest[4], correction[4];
    char *base=P(obj,112);
    char *movement=base+352;
    char *state=base+496;
    char *origin;
    char *global=P(g_follow_camera_object,112);
    float threshold;
    float distance, limit;
    int result=0;
    threshold=g_cam_collision_base_radius+F(global,564)*F(global,556)*(F(global,560)-1.0f);
    vec_clear_128(accumulated);
    qcopy(original,point);
    qcopy(plane,D_L00_001BF220_1);
    qcopy(hit,g_collision_position);
    origin=base+176;
    FastVecAdd(endpoint,origin,movement);
    distance=ProjectPointOntoSegment(closest,plane,origin,endpoint,0.0f);
    limit=fast_vec_dist(origin,closest);
    limit /= F(movement,44)-F(state,48);
    limit=(g_cam_collision_base_radius+(threshold-g_cam_collision_base_radius)*limit)*0.75f;
    if(distance<limit) {
        result=1;
        cam_compute_push_out(obj,accumulated,closest,plane,original,limit-distance,blend);
        qcopy(point,hit);
        if(coll_test_point(point,g_cam_collision_point_mask[0],g_hero_state.owner,radius)) {
            FastVecSub(difference,original,point);
            FastVecAdd(plane,D_L00_001BF220_1,difference);
            distance=ProjectPointOntoSegment(closest,plane,origin,endpoint,0.0f);
            limit=fast_vec_dist(origin,closest);
            limit /= F(movement,44)-F(state,48);
            limit=(g_cam_collision_base_radius+(threshold-g_cam_collision_base_radius)*limit)*0.75f;
            if(distance<limit) {
                cam_compute_push_out(obj,correction,closest,plane,original,limit-distance,blend);
                FastVecAdd(accumulated,accumulated,correction);
                qcopy(point,g_collision_position);
                if(coll_test_point(point,g_cam_collision_point_mask[0],g_hero_state.owner,radius)) {
                    FastVecSub(difference,original,point);
                    FastVecAdd(plane,D_L00_001BF220_1,difference);
                    distance=ProjectPointOntoSegment(closest,plane,origin,endpoint,0.0f);
                    limit=fast_vec_dist(origin,closest);
                    limit /= F(movement,44)-F(state,48);
                    limit=(g_cam_collision_base_radius+(threshold-g_cam_collision_base_radius)*limit)*0.75f;
                    if(distance<limit) {
                        cam_compute_push_out(obj,correction,closest,plane,original,limit-distance,blend);
                        FastVecAdd(accumulated,accumulated,correction);
                    }
                }
            }
        }
    }
    FastVecAdd(point,original,accumulated);
    return result;
}
