#include "names.h"
/* func_PAL_L00_004298B0, the PAL copy of func_L00_004243C0: the same C, where rename func_L00_004240D8 becomes func_PAL_L00_004295B8. */
#include "common.h"

/* func_PAL_L00_004298B0: -G8 for the $gp tuning value, -g for the line labels around the
 * division and the hold test, and -fstrict-aliasing as in its neighbour L00_004240D8:
 * type-based alias analysis gives the camera-type test and the registers after it their
 * retail form. The owner block (+0x70) is read through its position (+0x60),
 * aim (+0xB0), movement (+0x160) and state (+0x1F0) parts; `goal` is assigned inside the
 * loop (loop.c hoists it) so its spill slot precedes the scan and hidden pointers. */

extern char g_camera_move_state[],g_hero_l00_position[];
typedef struct { char pad[404]; char *active; char gap[620]; int counter; } GlobalCamera243;
typedef struct { char pad[256]; float x, y; } Controls243;
extern GlobalCamera243 g_scalar_transition_state;
extern Controls243 g_pad_state;
extern char *g_area_hit_targets[], *g_hidden_area_hit_targets[];
extern char *g_cam_collision_line_mask;
extern float g_cam_follow_probe_minimum __attribute__((sda));
typedef struct { char pad[0x2290]; char *owner; int mode; } Player243;
extern Player243 g_camera_player;
extern void lerp_vector(void *,void *,void *,float);
extern int coll_process_hit(void *,int,void *,int,float),level_has_pending_inner_flag(void *);
extern void FastVecSub(void *,void *,void *),FastVecScale(void *,void *,float),vec_scale_to_length(void *,void *,float);
extern float FastVecDot(void *,void *),math_fast_angle_helper(float),math_fabs(float);
extern void FastVecCross(void *,void *,void *),math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern int func_PAL_L00_004295B8(void *), cam_check_noop(void *);
extern void *cam_follow_probe_collision(void *);
extern int FastDecTimer(short *);
extern float IntToFloat(int),math_cosine_blend(float,float,float);
extern void FastVecAdd(void *,void *,void *);
extern int CollLine(void *,void *,void *,void *,int),coll_is_point_in_grid(void *);
extern void cam_reset_default(void);
#define S(p,n) (*(short *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
typedef struct { char pad[16]; float pos[4]; char pad20[4]; struct { char pad[16]; int value; } *info; char pad28[112]; int visible; char pad9C[14]; short type; } Moby243;
typedef struct { char pad[44]; float distance; } Move243;
typedef struct { char pad[48]; float offset; short timer; char gap[4]; short flag; char gap2[16]; short counter, locked; } State243;
void func_PAL_L00_004298B0(char *obj)
{
    char *base=P(obj,112);
    char *pos=base+96;
    Move243 *move=(Move243 *)(base+352);
    State243 *state=(State243 *)(base+496);
    char *camera=g_camera_move_state;
    char a[16],b[16],c[16],d[16],e[16];
    Moby243 *m;
    char *axis;
    int count,n,blocked=0,numhidden=0,type,camera_type,i;
    float distance=move->distance-state->offset+1.5f;
    float dot,t;
    unsigned short timer;
    Moby243 *entry;
    char *goal;
    lerp_vector(a,base+176,camera-96,0.5f);
    count=coll_process_hit(a,1,g_camera_player.owner,0,distance*0.5f);
    if(count>0) {
        char **scan,**hidden;
        scan=g_area_hit_targets;
        hidden=g_hidden_area_hit_targets;
        for(i=0;i<count;i++) {
            goal=base+176;
            m=(Moby243 *)*scan;
            if(m->visible && (!level_has_pending_inner_flag(m)||m->type==2923)) {
                type=m->type;
                if(type!=2234 && type!=3335 && type!=4304 && type!=1143 && type!=11) {
                    *hidden++=(char *)m;
                    numhidden++;
                    m->visible=0;
                } else {
                    FastVecSub(b,m->pos,goal);
                    axis=camera+48;
                    dot=FastVecDot(axis,b);
                    FastVecScale(c,axis,dot);
                    FastVecSub(d,b,c);
                    vec_scale_to_length(d,d,1.0f);
                    dot=FastVecDot(d,move);
                    {
                    float span=move->distance-state->offset;
                    span=dot/span;
                    t=math_fast_angle_helper(span);
                    }
                    t=math_fabs(1.5707963705062866f-t);
                    if(t<0.4363323450088501f) {
                        FastVecCross(e,move,axis);
                        vec_scale_to_length(e,e,1.0f);
                        if(FastVecDot(e,b)>0.0f)math_apply_axis_rotation_to_quat(move,move,camera+32,-0.01745329424738884f);
                        else math_apply_axis_rotation_to_quat(move,move,camera+32,0.01745329424738884f);
                    }
                }
            }
            scan++;
        }
    }
    if(!state->locked) {
        if(func_PAL_L00_004295B8(obj)) blocked=1;
        if(cam_check_noop(obj)) blocked=1;
    }
    if(cam_follow_probe_collision(obj))blocked=1;
    {
    float current_distance=move->distance;
    float minimum=g_cam_follow_probe_minimum;
    if(current_distance-state->offset<minimum) {
        state->timer=1667;
        state->offset=current_distance-minimum;
    }
    }
    {
    char *active_camera=g_scalar_transition_state.active;
    if(active_camera && ((camera_type=S(active_camera,134))==4 || camera_type==81) && g_scalar_transition_state.counter<8) state->timer=1417;
    }
    if(!state->flag) {
        timer=(unsigned short)state->timer;
        if(blocked || !(((unsigned)(timer-1)<1666) ||
            (g_pad_state.x<0.3f && g_pad_state.y<0.3f))) goto hold;
    }
    if(FastDecTimer(&state->timer))state->flag=0;
    if(state->flag) {
        if(FastDecTimer(&state->timer))state->flag=0;
    }
    t=IntToFloat(state->timer);
    t=t/IntToFloat(1667);
    state->offset=math_cosine_blend(0.0f,state->offset,t);
    goto scaled;
hold:
    if((short)timer>1667)FastDecTimer(&state->timer);
    else state->timer=1667;
scaled:
    vec_scale_to_length(move,move,move->distance-state->offset);
    FastVecAdd(b,move,pos+80);
    if(g_camera_player.mode!=49 && !state->locked &&
       CollLine(pos+80,b,g_cam_collision_line_mask,g_camera_player.owner,0) &&
       !coll_is_point_in_grid(g_hero_l00_position)) {
        state->counter++;
        if(state->counter>=25)cam_reset_default();
    } else state->counter=0;
    if(numhidden>0) {
        char **restore=g_hidden_area_hit_targets;
        int remaining=numhidden;
        do {
            entry=(Moby243 *)*restore++;
            entry->visible=entry->info->value;
        } while(--remaining);
    }
}
