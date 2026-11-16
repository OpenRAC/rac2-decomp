#include "include_asm.h"
#include "common.h"

/* func_PAL_L23_003C3B70, the PAL copy of func_L23_003C02C8: the same C, where both 0x26E timer stores
 * take the 50 Hz scale, the speed step becomes 1/50 and the fourth argument of func_PAL_L23_003C3868
 * is 3. A unit of its own: it reads $gp data (D_L23_001AFA50, D_L23_001AFA54).
 * The probe's 0x326 store is a struct member at a varying address, which alias analysis keeps
 * apart from the fixed scalar D_L23_001AFA50, so the probe length loads straight into $f12. */

typedef int Quad __attribute__((mode(TI)));
typedef struct { u64 first,last; } L23PathLinks;
typedef struct { u8 pad[0x2B2]; s16 direction; u8 pad2B4[0x326-0x2B4]; s16 probeHit; } L23PathState;
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define S(p,o) (*(s16 *)((u8 *)(p)+(o)))
extern float g_hero_position[] __attribute__((aligned(16)));
extern float g_enemy_probe_length __attribute__((sda));
extern int g_enemy_timer_base __attribute__((sda));
extern u8 *g_tether_l23_hit_result NOT_SDA;
extern int *g_path_piece_table;
extern u8 *g_path_lists[];
extern L23PathLinks g_path_end_masks[];
extern void mothership_project_point_onto_surface(char *,float);
extern int IsPathClear(void *,void *,void *);
extern int enemy_probe_ahead_point_pal(void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int CollLine(void *,void *,int,void *,void *);
extern s32 math_random_int_below(s32);
extern void moby_play_anim_and_link_pal(char *,int,int,int,int,float);
extern s32 math_random_int_range(s32,s32);
extern int FastDecTimer(s16 *);
extern float fast_vec_dist(void *,void *);
extern void SelectNearestPathNode(void *,int);
extern f32 coll_project_point_on_segment(f32 *,const f32 *,const f32 *,const f32 *);
extern void path_choose_next_piece(char *,u64,int,int);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern int moby_check_target_point_from_offset(char *,void *);
extern int moby_copy_vector_to_child(char *,Quad *);
extern void enemy_snap_to_ground_pal(char *,int);
/* Moves an enemy toward its target: dodges obstacles ahead, otherwise follows the path nodes toward the target and steers the moby and its child. (PAL) */
void path_following_update_pal(u8 *moby)
{
    float destination[4] __attribute__((aligned(16))),reference[4] __attribute__((aligned(16))),node[4] __attribute__((aligned(16))),direction[4] __attribute__((aligned(16)));
    float *target;
    u8 *vars=*(u8 **)(moby+0x68),*path;
    int arrived,allow,mode,choice,index,path_index,next,base;
    unsigned short allow_mode;
    float side,first,second;
    {
        float *copy_target=*(float **)(vars+0x320);
        qcopy(destination, copy_target);
        qcopy(reference, copy_target);
    }
    mothership_project_point_onto_surface((char *)reference,0.0f);
    target=*(float **)(vars+0x320);
    arrived=target==g_hero_position ? S(vars,0x324) : IsPathClear(moby,moby+0x10,target);
    if (arrived==0 && S(vars,0x2B0)==0 && S(vars,0x26C)==0) S(vars,0x2B0)=1;
    if (S(vars,0x26C)!=0) goto timer;
    allow=1;
    allow_mode=*(u16 *)(vars+0x2B0);
    if (S(vars,0x2B0)==2) allow=0;
    else if (S(vars,0x2B0)==4) { if (arrived) allow=0; }
    else if (*(float **)(vars+0x320)==g_hero_position && S(vars,0x324)!=0) allow=0;
    else {
        if (allow_mode==0 && arrived!=0) allow=0;
        else allow = S(vars,0x2B0)==3 ? 0 : allow;
    }
    if (allow) {
        if (enemy_probe_ahead_point_pal(moby)) {
            qcopy(destination, (vars+0x2D0));
            qcopy((vars+0x2E0), (moby+0x10));
            S(vars,0x26E)=((s32)(g_enemy_timer_base+math_random_int_range(-g_enemy_timer_base/2,g_enemy_timer_base/2))*5+2)/6;
            goto follow;
        }
        goto follow;
    }
    {
        ((L23PathState *)vars)->probeHit=0;
        FastVecScale(node,moby+0xC0,g_enemy_probe_length);
        FastVecAdd(node,node,moby+0x10);
    if (CollLine(moby+0x10,node,17,moby,0) && g_tether_l23_hit_result && *(s16 *)(g_tether_l23_hit_result+0xAA)==0x7E5) {
        choice=math_random_int_below(3);
        switch (choice) {
        case 0: side=1.0f; S(vars,0x26C)=1; break;
        case 1: side=-1.0f; S(vars,0x26C)=1; break;
        case 2:
        default: {
            S(vars,0x26C)=-1;
            moby_play_anim_and_link_pal((char *)moby,3,0,3,1,1.0f);
            side=0.0f;
        }
        }
        if (side!=0.0f) {
            FastVecScale(direction,moby+0xD0,side);
            FastVecAdd(direction,direction,moby+0xC0);
            FastVecScale(direction,direction,12.0f);
            FastVecAdd(vars+0x2D0,moby+0x10,direction);
            mothership_project_point_onto_surface((char *)vars+0x2D0,0.0f);
        }
        base=g_enemy_timer_base;
        S(vars,0x2B0)=0;
        ((L23PathState *)vars)->probeHit=1;
        S(vars,0x26E)=((s32)(g_enemy_timer_base+math_random_int_range(-base/2,base/2))*5+2)/6;
        goto follow;
    }
    }
    goto follow;
timer:
    if (S(vars,0x26E)) FastDecTimer((s16 *)(vars+0x26E));
    if (!S(vars,0x26E)) S(vars,0x26C)=0;
    if (S(vars,0x26C)==-1) return;
    qcopy(destination, (vars+0x2D0));
follow:
    mode=S(vars,0x2B0);
    if (mode==0) goto update;
    switch (mode) {
    case 1: {
        u8 *path;
        SelectNearestPathNode(moby,1);
        path=g_path_lists[g_path_piece_table[S(vars,0x2B4)]];
        {
            int initial_index=S(vars,0x2B6);
            qcopy(node, (path+0x10+initial_index*16));
            S(vars,0x2B0)=2;
            first=fast_vec_dist(path+0x10+initial_index*16,reference);
        }
        index=S(vars,0x2B6);
        if (index==0) {
            second=fast_vec_dist(path+0x20,reference);
            if (second<first) {
                ((L23PathState *)vars)->direction=1;
                coll_project_point_on_segment((float *)(vars+0x2C0),node,(float *)(path+0x20+S(vars,0x2B6)*16),(float *)(moby+0x10));
            } else { Quad saved_node=*(Quad *)node; ((L23PathState *)vars)->direction=-1; *(Quad *)(vars+0x2C0)=saved_node; }
        } else if (index==I(path,0)-1) {
            second=fast_vec_dist(path+(I(path,0)*16-4*4),reference);
            if (second<first) {
                ((L23PathState *)vars)->direction=-1;
                coll_project_point_on_segment((float *)(vars+0x2C0),node,(float *)(path+S(vars,0x2B6)*16),(float *)(moby+0x10));
            } else { Quad saved_node=*(Quad *)node; ((L23PathState *)vars)->direction=1; *(Quad *)(vars+0x2C0)=saved_node; }
        } else {
            direction[0]=fast_vec_dist(path+index*16,reference);
            direction[1]=fast_vec_dist(path+0x20+S(vars,0x2B6)*16,reference);
            if (direction[0]<direction[1]) ((L23PathState *)vars)->direction=-1; else ((L23PathState *)vars)->direction=1;
            coll_project_point_on_segment((float *)(vars+0x2C0),node,(float *)(path+0x10+((L23PathState *)vars)->direction*16),(float *)(moby+0x10));
        }
        mothership_project_point_onto_surface((char *)vars+0x2C0,0.0f);
        goto update;
    }
    case 2: {
        float *path_target=(float *)(vars+0x2C0);
        if (fast_vec_dist(moby+0x10,path_target)<2.0f) { S(vars,0x2B0)=3; goto update; }
        qcopy(destination,path_target);
        goto update;
    }
    case 3: {
        if (fast_vec_dist(vars+0x300,reference)<20.0f && arrived) { S(vars,0x2B0)=4; goto update; }
        if (fast_vec_dist(moby+0x10,vars+0x2C0)<2.0f) {
            next=S(vars,0x2B6)+((L23PathState *)vars)->direction;
            if (next<0) path_choose_next_piece((char *)moby,g_path_end_masks[g_path_piece_table[S(vars,0x2B4)]].first,1,1);
            else {
                path_index=g_path_piece_table[S(vars,0x2B4)];
                if (next>=I(g_path_lists[path_index],0)) {
                    path_choose_next_piece((char *)moby,g_path_end_masks[path_index].last,1,1);
                    goto load_path;
                }
                S(vars,0x2B6)=next;
            }
load_path:
            path=g_path_lists[g_path_piece_table[S(vars,0x2B4)]];
            qcopy((vars+0x2C0), (path+0x10+S(vars,0x2B6)*16));
            mothership_project_point_onto_surface((char *)vars+0x2C0,0.0f);
        }
        qcopy(destination,vars+0x2C0);
        goto update;
    }
    case 4: S(vars,0x2B0)=0; goto update;
    default: goto update;
    }
update:
    FastVecSub(node,destination,moby+0x10);
    vec_scale_to_length(node,node,F(vars,0x2A8)*0.020000001f);
    moby_check_target_point_from_offset((char *)moby,destination);
    moby_copy_vector_to_child((char *)moby,(Quad *)node);
    enemy_snap_to_ground_pal((char *)moby,1);
}
