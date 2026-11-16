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
extern int func_PAL_L23_003C4CE8(void *);
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
extern void func_PAL_L23_003C3AA0(char *,int);
void func_PAL_L23_003C3B70(u8 *object)
{
    float destination[4] __attribute__((aligned(16))),reference[4] __attribute__((aligned(16))),node[4] __attribute__((aligned(16))),direction[4] __attribute__((aligned(16)));
    float *target;
    u8 *state=*(u8 **)(object+0x68),*path;
    int arrived,allow,mode,choice,index,pathIndex,next,base;
    unsigned short allowMode;
    float side,first,second;
    {
        float *copyTarget=*(float **)(state+0x320);
        qcopy(destination, copyTarget);
        qcopy(reference, copyTarget);
    }
    mothership_project_point_onto_surface((char *)reference,0.0f);
    target=*(float **)(state+0x320);
    arrived=target==g_hero_position ? S(state,0x324) : IsPathClear(object,object+0x10,target);
    if (arrived==0 && S(state,0x2B0)==0 && S(state,0x26C)==0) S(state,0x2B0)=1;
    if (S(state,0x26C)!=0) goto timer;
    allow=1;
    allowMode=*(u16 *)(state+0x2B0);
    if (S(state,0x2B0)==2) allow=0;
    else if (S(state,0x2B0)==4) { if (arrived) allow=0; }
    else if (*(float **)(state+0x320)==g_hero_position && S(state,0x324)!=0) allow=0;
    else {
        if (allowMode==0 && arrived!=0) allow=0;
        else allow = S(state,0x2B0)==3 ? 0 : allow;
    }
    if (allow) {
        if (func_PAL_L23_003C4CE8(object)) {
            qcopy(destination, (state+0x2D0));
            qcopy((state+0x2E0), (object+0x10));
            S(state,0x26E)=((s32)(g_enemy_timer_base+math_random_int_range(-g_enemy_timer_base/2,g_enemy_timer_base/2))*5+2)/6;
            goto follow;
        }
        goto follow;
    }
    {
        ((L23PathState *)state)->probeHit=0;
        FastVecScale(node,object+0xC0,g_enemy_probe_length);
        FastVecAdd(node,node,object+0x10);
    if (CollLine(object+0x10,node,17,object,0) && g_tether_l23_hit_result && *(s16 *)(g_tether_l23_hit_result+0xAA)==0x7E5) {
        choice=math_random_int_below(3);
        switch (choice) {
        case 0: side=1.0f; S(state,0x26C)=1; break;
        case 1: side=-1.0f; S(state,0x26C)=1; break;
        case 2:
        default: {
            S(state,0x26C)=-1;
            moby_play_anim_and_link_pal((char *)object,3,0,3,1,1.0f);
            side=0.0f;
        }
        }
        if (side!=0.0f) {
            FastVecScale(direction,object+0xD0,side);
            FastVecAdd(direction,direction,object+0xC0);
            FastVecScale(direction,direction,12.0f);
            FastVecAdd(state+0x2D0,object+0x10,direction);
            mothership_project_point_onto_surface((char *)state+0x2D0,0.0f);
        }
        base=g_enemy_timer_base;
        S(state,0x2B0)=0;
        ((L23PathState *)state)->probeHit=1;
        S(state,0x26E)=((s32)(g_enemy_timer_base+math_random_int_range(-base/2,base/2))*5+2)/6;
        goto follow;
    }
    }
    goto follow;
timer:
    if (S(state,0x26E)) FastDecTimer((s16 *)(state+0x26E));
    if (!S(state,0x26E)) S(state,0x26C)=0;
    if (S(state,0x26C)==-1) return;
    qcopy(destination, (state+0x2D0));
follow:
    mode=S(state,0x2B0);
    if (mode==0) goto update;
    switch (mode) {
    case 1: {
        u8 *path;
        SelectNearestPathNode(object,1);
        path=g_path_lists[g_path_piece_table[S(state,0x2B4)]];
        {
            int initialIndex=S(state,0x2B6);
            qcopy(node, (path+0x10+initialIndex*16));
            S(state,0x2B0)=2;
            first=fast_vec_dist(path+0x10+initialIndex*16,reference);
        }
        index=S(state,0x2B6);
        if (index==0) {
            second=fast_vec_dist(path+0x20,reference);
            if (second<first) {
                ((L23PathState *)state)->direction=1;
                coll_project_point_on_segment((float *)(state+0x2C0),node,(float *)(path+0x20+S(state,0x2B6)*16),(float *)(object+0x10));
            } else { Quad savedNode=*(Quad *)node; ((L23PathState *)state)->direction=-1; *(Quad *)(state+0x2C0)=savedNode; }
        } else if (index==I(path,0)-1) {
            second=fast_vec_dist(path+(I(path,0)*16-4*4),reference);
            if (second<first) {
                ((L23PathState *)state)->direction=-1;
                coll_project_point_on_segment((float *)(state+0x2C0),node,(float *)(path+S(state,0x2B6)*16),(float *)(object+0x10));
            } else { Quad savedNode=*(Quad *)node; ((L23PathState *)state)->direction=1; *(Quad *)(state+0x2C0)=savedNode; }
        } else {
            direction[0]=fast_vec_dist(path+index*16,reference);
            direction[1]=fast_vec_dist(path+0x20+S(state,0x2B6)*16,reference);
            if (direction[0]<direction[1]) ((L23PathState *)state)->direction=-1; else ((L23PathState *)state)->direction=1;
            coll_project_point_on_segment((float *)(state+0x2C0),node,(float *)(path+0x10+((L23PathState *)state)->direction*16),(float *)(object+0x10));
        }
        mothership_project_point_onto_surface((char *)state+0x2C0,0.0f);
        goto update;
    }
    case 2: {
        float *pathTarget=(float *)(state+0x2C0);
        if (fast_vec_dist(object+0x10,pathTarget)<2.0f) { S(state,0x2B0)=3; goto update; }
        qcopy(destination,pathTarget);
        goto update;
    }
    case 3: {
        if (fast_vec_dist(state+0x300,reference)<20.0f && arrived) { S(state,0x2B0)=4; goto update; }
        if (fast_vec_dist(object+0x10,state+0x2C0)<2.0f) {
            next=S(state,0x2B6)+((L23PathState *)state)->direction;
            if (next<0) path_choose_next_piece((char *)object,g_path_end_masks[g_path_piece_table[S(state,0x2B4)]].first,1,1);
            else {
                pathIndex=g_path_piece_table[S(state,0x2B4)];
                if (next>=I(g_path_lists[pathIndex],0)) {
                    path_choose_next_piece((char *)object,g_path_end_masks[pathIndex].last,1,1);
                    goto loadPath;
                }
                S(state,0x2B6)=next;
            }
loadPath:
            path=g_path_lists[g_path_piece_table[S(state,0x2B4)]];
            qcopy((state+0x2C0), (path+0x10+S(state,0x2B6)*16));
            mothership_project_point_onto_surface((char *)state+0x2C0,0.0f);
        }
        qcopy(destination,state+0x2C0);
        goto update;
    }
    case 4: S(state,0x2B0)=0; goto update;
    default: goto update;
    }
update:
    FastVecSub(node,destination,object+0x10);
    vec_scale_to_length(node,node,F(state,0x2A8)*0.020000001f);
    moby_check_target_point_from_offset((char *)object,destination);
    moby_copy_vector_to_child((char *)object,(Quad *)node);
    func_PAL_L23_003C3AA0((char *)object,1);
}
