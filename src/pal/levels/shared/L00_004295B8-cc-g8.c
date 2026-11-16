#include "names.h"
/* func_PAL_L00_004295B8, the PAL copy of func_L00_004240D8: the same C, where wrap D_L00_001B14B4 (({e}) * 1.2f). */
#include "common.h"

/* func_PAL_L00_004295B8: -G8 for the $gp constants, -g for the line label that pads the final
 * div.s, and -fstrict-aliasing: retail schedules the halfword store at state+0x34 after the
 * minimum-distance load and leaves the movement+0x2C reload free of it, which only
 * type-based alias analysis allows. The bias and minimum distance are read-only tuning
 * values (their loads move freely across the float stores); the increment is not. */

extern char D_L00_001BF220_1[], g_camera_up_vector[];
/* The resident block at D_00189E20: an owner object pointer at +0x2290, a mode byte at +0x22B4. */
typedef struct {
    char pad0[0x2290];
    char *owner;
    char pad2294[0x22B4 - 0x2294];
    unsigned char mode;
} L00_004240D8_Player;
extern L00_004240D8_Player g_hero_state;
extern const float g_cam_collision_base_radius __attribute__((sda));
extern float g_cam_follow_distance_margin __attribute__((sda));
extern const float g_cam_follow_min_distance __attribute__((sda));
extern float g_stick_axis_x NOT_SDA;
extern void *g_cam_collision_point_mask[] __attribute__((sda));
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fabs(float);
extern int FloatToInt(float);
extern int coll_is_point_in_grid(void *);
extern int coll_test_point(void *, void *, void *, float);
extern int cam_is_step_behind_plane(void *, int, void *, float);
extern int cam_push_point_out_of_walls(void *, void *, int, float, float);
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define S(p,n) (*(short *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
/* Steps a probe from the owner block's position along its movement direction, testing each
   step for collisions; on a hit it records the result, may pull the follow distance in, and
   re-aims the movement vector at the hit point. */
int cam_follow_sweep_probe_pal(char *obj)
{
    float original[4], point[4], direction[4], saved[4], previous[4], difference[4];
    char *base=P(obj,112);
    char *camera=base+96;
    char *movement=base+352;
    char *state=base+496;
    int result=0, i;
    float step, total;
    qcopy(original,movement);
    total=0;
    qcopy(point,base+176);
    step=g_cam_collision_base_radius;
    vec_scale_to_length(direction,original,1.0f);
    for(i=0;i<FloatToInt(F(state,64)-1.0f);i++) {
        if(i>0 && !coll_is_point_in_grid(point) &&
           coll_test_point(point,g_cam_collision_point_mask[0],g_hero_state.owner,step) &&
           !cam_is_step_behind_plane(obj,i,point,step)) {
            qcopy(saved,D_L00_001BF220_1);
            qcopy(previous,point);
            if(cam_push_point_out_of_walls(obj,point,i,total,step)) {
                result=1;
                if (g_hero_state.mode!=2 && math_fabs(g_stick_axis_x)>0.05f) {
                    FastVecSub(difference,saved,previous);
                    vec_scale_to_length(difference,difference,1.0f);
                    if(math_fabs(FastVecDot(g_camera_up_vector,difference))<0.75f) {
                        F(state,48) += ((g_cam_follow_distance_margin) * 1.2f);
                        S(state,52)=1817;
                        if(F(movement,44)-F(state,48)<g_cam_follow_min_distance)
                            F(state,48)=F(movement,44)-g_cam_follow_min_distance;
                    }
                }
                FastVecSub(difference,point,camera+80);
                vec_scale_to_length(movement,difference,F(movement,44)-F(state,48));
                vec_scale_to_length(direction,movement,1.0f);
            }
        }
        {
            float ratio=(F(movement,44)-F(state,48))/F(movement,44);
            step += F(state,68)*F(state,60);
            total += step;
            FastVecScale(saved,direction,step*ratio);
        }
        FastVecAdd(point,point,saved);
    }
    return result;
}
