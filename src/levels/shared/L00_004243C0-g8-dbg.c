#include "common.h"

/* func_L00_004243C0: -G8 for the $gp tuning value, -g for the line labels around the
 * division and the hold test, and -fstrict-aliasing as in its neighbour L00_004240D8:
 * type-based alias analysis gives the camera-type test and the registers after it their
 * retail form. The owner block (+0x70) is read through its position (+0x60),
 * aim (+0xB0), movement (+0x160) and state (+0x1F0) parts; `goal` is assigned inside the
 * loop (loop.c hoists it) so its spill slot precedes the scan and hidden pointers. */

extern char D_L00_001B8E20[],D_L00_001BF220[];
typedef struct { char pad[404]; char *active; char gap[620]; int counter; } GlobalCamera243;
typedef struct { char pad[256]; float x, y; } Controls243;
extern GlobalCamera243 D_L00_001B8C80;
extern Controls243 g_pad_state;
extern char *g_area_hit_targets[], *D_L00_0025B9A0[];
extern char *D_L00_001B184C;
extern float D_L00_001B14CC __attribute__((sda));
typedef struct { char pad[0x2290]; char *owner; int mode; } Player243;
extern Player243 D_L00_00189E20;
extern void lerp_vector(void *,void *,void *,float);
extern int coll_process_hit(void *,int,void *,int,float),level_has_pending_inner_flag(void *);
extern void FastVecSub(void *,void *,void *),FastVecScale(void *,void *,float),vec_scale_to_length(void *,void *,float);
extern float FastVecDot(void *,void *),math_fast_angle_helper(float),math_fabs(float);
extern void FastVecCross(void *,void *,void *),math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern int cam_follow_sweep_probe(void *),cam_check_noop(void *),cam_follow_probe_collision(void *);
extern int FastDecTimer(short *);
extern float IntToFloat(int),math_cosine_blend(float,float,float);
extern void FastVecAdd(void *,void *,void *);
extern int CollLine(void *,void *,void *,void *,int),coll_is_point_in_grid(void *);
extern void cam_reset_default(void);
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define S(p,n) (*(short *)((char *)(p)+(n)))
#define U(p,n) (*(unsigned short *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
#define I(p,n) (*(int *)((char *)(p)+(n)))
typedef struct { char pad[16]; float pos[4]; char pad20[4]; struct { char pad[16]; int value; } *info; char pad28[112]; int visible; char pad9C[14]; short type; } Moby243;
typedef struct { char pad[44]; float distance; } Move243;
typedef struct { char pad[48]; float offset; short timer; char gap[4]; short flag; char gap2[16]; short counter, locked; } State243;
/* Runs the follow camera each frame. It hides objects that block the view, pushes the camera away from walls, and slowly pulls it back out. */
void FollowCameraHideObstructions(char *obj)
{
    char *base=P(obj,112);
    char *pos=base+96;
    Move243 *move=(Move243 *)(base+352);
    State243 *state=(State243 *)(base+496);
    char *camera=D_L00_001B8E20;
    char probe[16],to_moby[16],along_axis[16],perpendicular[16],side[16];
    Moby243 *moby;
    char *axis;
    int count,n,blocked=0,numhidden=0,type,camera_type,i;
    float distance=move->distance-state->offset+1.5f;
    float dot,angle;
    unsigned short timer;
    Moby243 *entry;
    char *goal;
    lerp_vector(probe,base+176,camera-96,0.5f);
    count=coll_process_hit(probe,1,D_L00_00189E20.owner,0,distance*0.5f);
    if(count>0) {
        char **scan,**hidden;
        scan=g_area_hit_targets;
        hidden=D_L00_0025B9A0;
        for(i=0;i<count;i++) {
            goal=base+176;
            moby=(Moby243 *)*scan;
            if(moby->visible && (!level_has_pending_inner_flag(moby)||moby->type==2923 /* moby class 2923 */)) {
                type=moby->type;
                if(type!=2234 /* moby class 2234 */ && type!=MOBY_CLASS_JOBIAN_SAUR_BEAST && type!=MOBY_CLASS_YETI && type!=MOBY_CLASS_MEGACORP_VENDOR_LOGO && type!=MOBY_CLASS_MEGACORP_VENDOR) {
                    *hidden++=(char *)moby;
                    numhidden++;
                    moby->visible=0;
                } else {
                    FastVecSub(to_moby,moby->pos,goal);
                    axis=camera+48;
                    dot=FastVecDot(axis,to_moby);
                    FastVecScale(along_axis,axis,dot);
                    FastVecSub(perpendicular,to_moby,along_axis);
                    vec_scale_to_length(perpendicular,perpendicular,1.0f);
                    dot=FastVecDot(perpendicular,move);
                    {
                    float span=move->distance-state->offset;
                    span=dot/span;
                    angle=math_fast_angle_helper(span);
                    }
                    angle=math_fabs(1.5707963705062866f-angle);
                    if(angle<0.4363323450088501f) {
                        FastVecCross(side,move,axis);
                        vec_scale_to_length(side,side,1.0f);
                        if(FastVecDot(side,to_moby)>0.0f)math_apply_axis_rotation_to_quat(move,move,camera+32,-0.01745329424738884f);
                        else math_apply_axis_rotation_to_quat(move,move,camera+32,0.01745329424738884f);
                    }
                }
            }
            scan++;
        }
    }
    if(!state->locked) {
        if(cam_follow_sweep_probe(obj)) blocked=1;
        if(cam_check_noop(obj)) blocked=1;
    }
    if(cam_follow_probe_collision(obj))blocked=1;
    {
    float current_distance=move->distance;
    float minimum=D_L00_001B14CC;
    if(current_distance-state->offset<minimum) {
        state->timer=2000;
        state->offset=current_distance-minimum;
    }
    }
    {
    char *active_camera=D_L00_001B8C80.active;
    if(active_camera && ((camera_type=S(active_camera,134))==4 || camera_type==81) && D_L00_001B8C80.counter<10) state->timer=1700;
    }
    if(!state->flag) {
        timer=(unsigned short)state->timer;
        if(blocked || !(((unsigned)(timer-1)<1999) ||
            (g_pad_state.x<0.3f && g_pad_state.y<0.3f))) goto hold;
    }
    if(FastDecTimer(&state->timer))state->flag=0;
    if(state->flag) {
        if(FastDecTimer(&state->timer))state->flag=0;
    }
    angle=IntToFloat(state->timer);
    angle=angle/IntToFloat(2000);
    state->offset=math_cosine_blend(0.0f,state->offset,angle);
    goto scaled;
hold:
    if((short)timer>2000)FastDecTimer(&state->timer);
    else state->timer=2000;
scaled:
    vec_scale_to_length(move,move,move->distance-state->offset);
    FastVecAdd(to_moby,move,pos+80);
    if(D_L00_00189E20.mode!=49 && !state->locked &&
       CollLine(pos+80,to_moby,D_L00_001B184C,D_L00_00189E20.owner,0) &&
       !coll_is_point_in_grid(D_L00_001BF220)) {
        state->counter++;
        if(state->counter>=30)cam_reset_default();
    } else state->counter=0;
    if(numhidden>0) {
        char **restore=D_L00_0025B9A0;
        int remaining=numhidden;
        do {
            entry=(Moby243 *)*restore++;
            entry->visible=entry->info->value;
        } while(--remaining);
    }
}
