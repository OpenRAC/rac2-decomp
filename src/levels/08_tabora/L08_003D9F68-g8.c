#include "common.h"
#define B(p,o) (*(u8 *)((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define S(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern void crawler_update_hits_aim(void *), herd_animal_init(void *), crawler_choose_goal(void *), crawler_tick_timers(void *), crawler_spawn_spit_effect(void *);
extern int math_random_int_below(int),math_random_int_range(int,int),func_001163B0(void);
extern int moby_l08_is_linked_running(int),moby_l08_is_linked_gone_2(int),moby_l08_is_linked_gone(int),moby_l08_is_linked_running_or_gone(int);
extern void STUB_printf(void *,int,int),anim_start_blended(void *,int,int,int),moby_set_state(void *,int,int);
extern int SelectNearestListedMoby(void *,void *,float,float,int,int,int,int);
extern int math_fast_float_d(void *);
extern int moby_step_at_own_position(void *);
extern void moby_mark_spawned(void *);
extern float moby_get_anim_value(void *);
extern void part_spawn_radial_dust_puffs(void *,void *,int,float,float,float,float,float,float);
extern int crawler_move_toward_goal(void *,float,float,float,float,float,float,float);
extern int coll_check_object_inside_polygon(void *),moby_dispatch_action_by_kind(void *,void *);
extern int moby_l01_turn_toward_target(void *,void *);
extern int moby_step_at_own_position_factor(void *,float);
extern void FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *),vec_scale_to_length(void *,void *,float);
extern int CollLine(void *,void *,int,void *,int),coll_test_point(void *,int,void *,float);
extern void vec_fast_normalize(void *,void *,void *),FastVecScale(void *,void *,float);
extern float vec_distance_xy(void *,void *),mat_fast_helper_a(float,float),FastDiffRots(float,float);
extern s32 math_closest_point_on_polygon_edge(void *,void *,void *,int);
extern u8 D_L08_002B5270[];
typedef struct { u8 pad[0x18]; u8 *moby; u32 pad1C; float point[4], adjusted[4], normal[4]; } Collision;
extern Collision D_L08_001BFF40;
typedef struct {
    u8 pad00[0x24];
    u8 *anim;
    u8 pad28[9];
    u8 active;
    u16 field32, flags;
    u8 pad36[0x62];
    int animation;
} GroundMoby;
extern u8 *D_L08_001FE7C0[];
extern u8 g_hero_position[];
extern int D_0018C0B4[];
extern void part_spawn_sparks_around(void *),part_spawn_yellow_spark_burst(void *,void *);
extern void SpawnExplosionEffects(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void SetDeathBits(void *,int,int);
extern u8 D_L08_001A8F20[] MACRO_ADDR;
typedef struct { u8 pad[0x464]; u8 flags[0]; } MobyFlags;
extern MobyFlags D_L08_0021DE80, D_L08_0021EAF0;
extern u8 D_L08_001B2840[] MACRO_ADDR;
extern u8 D_0019B2E8[],D_0019B4A8[];
extern int g_current_map_index MACRO_ADDR;
/* Per-frame state machine of the Spitting Dune Crawler (moby class 2502): waits for its trigger, pops up, walks and chases the hero, spits, gets hurt and dies. */
void UpdateTaboraChaseEnemyAI(u8 *object)
{
    u8 *state=P(object,0x68);
    float old[4], delta[4];
    int ready, result;
    crawler_update_hits_aim(object);
    switch(B(object,0x20)) {
    case 0:
        herd_animal_init(object);
        if(!object || B(object,0x20)==0xFE || B(object,0x20)==0xFD) return;
        break;
    case 1: {
        int trigger;
        ready=0;
        switch(B(state,0x40D)) {
        case 0:
            if(!math_random_int_below(7))
                {trigger=SelectNearestListedMoby(object,state+0x210,(float)S(state,0x408),0,I(state,0x410),I(state,0x418),I(state,0x414),-1)^2; goto trigger_test;}
            break;
        case 1:
            if(I(state,0x400)!=-1) ready=moby_l08_is_linked_running(I(state,0x400))!=0;
            else {STUB_printf(D_L08_002B5270,S(object,0xAA),S(object,0xB2)); B(state,0x40D)=0;}
            break;
        case 2: trigger=B(object,0xBC);goto trigger_test;
        case 3: ready=moby_l08_is_linked_gone_2(I(state,0x468))!=0;break;
        case 4: ready=moby_l08_is_linked_gone(I(state,0x400))!=0;break;
        case 5: trigger=moby_l08_is_linked_running_or_gone(I(state,0x404));
        trigger_test: ready=trigger!=0;break;
        }
        if(B(object,0xBC)&2) ready=1;
        if(ready) {
            I(state,0x15C)=I(state,0x428); I(object,0x98)=I(P(object,0x24),0x10);
            B(object,0x30)=B(state,0x408); qzero_nc(state+0x1C0);
            I(state,0x440)=math_random_int_range(0,180); moby_set_state(object,3,-1);
        }
        break;
    }
    case 3:
        if(math_fast_float_d(state+0x440)) {
            if(B(object,0x43)!=4) anim_start_blended(object,4,0,10);
            B(object,0x31)=1; H(object,0x34)&=0xFFFE;moby_set_state(object,2,0);
        }
        break;
    case 2:
        if(moby_get_anim_value(object)<12.0f) {
            qcopy_nc(old,object+0x10); old[2]=F(state,0x434);
            part_spawn_radial_dust_puffs(object,old,3,1,1.5f,0.5f,0,0.1f,0.8f);
        }
        if(B(object,0x60)&2) {
            switch(B(object,0x95)) { case 0: {
                H(object,0x34)&=0xFFFE; B(object,0x31)=1; H(object,0x34)|=0x1000;
                I(state,0x440)=math_random_int_range(180,360);crawler_choose_goal(object);
                if(B(object,0x43)!=9) anim_start_blended(object,9,0,10);
                moby_set_state(object,6,1);
            break; } case 1: {
                H(object,0x34)&=0xEFFF;
                if(B(object,0x43)!=11) anim_start_blended(object,11,0,10);
                I(state,0x440)=0; B(object,0x31)=0; H(object,0x34)|=1;
                moby_set_state(object,1,-1);
            break; } }
        }
        break;
    case 4: {
        u8 *collisionMoby;
        GroundMoby *ground=(GroundMoby *)object;
        qcopy_nc(old,object+0x10);FastVecAdd(object+0x10,object+0x10,state+0xD0);
        F(state,0xD8)-=0.0027222223579883575f;F(object,0x18)+=1.5f;
        if(CollLine(old,object+0x10,0,object,0)) {
            u8 *hitMoby=D_L08_001BFF40.moby;
            if(hitMoby) {
                if(S(hitMoby,0xAA)==0x945 /* moby class 2373 */ || S(hitMoby,0xAA)==MOBY_CLASS_SPITTING_DUNE_CRAWLER) goto no_ray_response;
            }
            FastVecSub(delta,old,D_L08_001BFF40.point);
            vec_scale_to_length(delta,delta,1.5f);FastVecAdd(object+0x10,object+0x10,delta);
        }
        no_ray_response:
        if(coll_test_point(object+0x10,0,object,1.5f)) {
            collisionMoby=D_L08_001BFF40.moby;
            if(collisionMoby) {
                if(S(collisionMoby,0xAA)==0x945 /* moby class 2373 */ || S(collisionMoby,0xAA)==MOBY_CLASS_SPITTING_DUNE_CRAWLER) goto no_overlap_response;
            } else {
                if(F(object,0x18)<=F(state,0x434)+1.5f+0.1f && F(state,0xD8)<0) {
                    ground->flags|=0x1000;
                    ground->animation=I(ground->anim,0x10);ground->active=1;ground->flags&=0xFFFE;
                    I(state,0x440)=math_random_int_range(180,360);crawler_choose_goal(object);
                    if(B(object,0x43)!=15) anim_start_blended(object,15,0,5);
                    moby_set_state(object,5,-1);
                    goto no_overlap_response;
                }
            }
            qcopy_nc(object+0x10,D_L08_001BFF40.adjusted);
            vec_fast_normalize(state+0xD0,state+0xD0,D_L08_001BFF40.normal);
            FastVecScale(state+0xD0,state+0xD0,0.8f);
        }
        no_overlap_response:
        F(object,0x18)-=1.5f; F(state,0xD8)-=0.0027222223579883575f;
        if(F(object,0x18)<F(state,0x434)) F(object,0x18)=F(state,0x434);
        break;
    }
    case 5:
        moby_step_at_own_position(object);
        if(B(object,0x60)&2) {
            if(B(object,0x43)!=9) anim_start_blended(object,9,0,2);
            moby_set_state(object,6,1);
        }
        break;
    case 6:
        switch(B(object,0x95)) {
        case 0:
            moby_step_at_own_position(object);
            if(B(object,0x60)&2) {
                if(!I(state,0x440)) {
                    I(state,0x440)=math_random_int_range(180,360);crawler_choose_goal(object);
                    if(B(object,0x43)!=9) anim_start_blended(object,9,0,10);
                    moby_set_state(object,6,1);
                } else if(B(object,0x43)!=(func_001163B0()&1)) anim_start_blended(object,func_001163B0()&1,0,10);
            }
            break;
        case 1:
            if((crawler_move_toward_goal(object,120,360,90,8,0,2,1)&0x80)||!I(state,0x440)) {
                I(state,0x440)=math_random_int_range(30,90);
                if(B(object,0x43)!=(func_001163B0()&1)) anim_start_blended(object,func_001163B0()&1,0,10);
                moby_set_state(object,6,0);
            }
            break;
        case 2:
            qcopy_nc(state+0x3F0,state+0x3E0);
            if(crawler_move_toward_goal(object,120,360,90,8,0,2,1)&0x80) {
                if(B(object,0x43)!=5) anim_start_blended(object,5,0,10);
                moby_set_state(object,2,1);
            }
            break;
        }
        if(math_random_int_below(7)) break;
        if(I(state,0x448) || SelectNearestListedMoby(object,state+0x210,(float)S(object,0x32),(float)S(state,0x40E),I(state,0x41C),I(state,0x424),I(state,0x420),-1)!=2) {
            if(I(state,0x428)!=-1) {u8 *waypoint_list=D_L08_001FE7C0[I(state,0x428)];math_closest_point_on_polygon_edge(state+0x210,state+0x210,waypoint_list+0x10,I(waypoint_list,0));}
            if(B(state,0x40C)==3) {
                I(state,0x48C)=600;I(state,0x15C)=I(state,0x428);B(state,0x40C)=1;
                qcopy_nc(state+0x3F0,state+0x230);
                if(B(object,0x43)!=9)anim_start_blended(object,9,0,math_random_int_range(3,6));
                moby_set_state(object,8,0);I(state,0x480)=0;
                break;
            }
            if(!math_random_int_below(9)) {
                I(state,0x15C)=I(state,0x428);I(state,0x448)=math_random_int_range(300,360)*2;
                if(B(object,0x43)!=((func_001163B0()&1)+2))anim_start_blended(object,(func_001163B0()&1)|2,0,10);
                moby_set_state(object,7,0);
            }
        } else if(B(object,0x20)==6 && B(state,0x40C)==0 && B(object,0x95)!=2) {
            if(B(object,0x43)!=9)anim_start_blended(object,9,0,10);
            moby_set_state(object,6,2);
        }
        break;
    case 7:
        switch(B(object,0x95)) { case 0: {
            moby_step_at_own_position(object);
            if((B(object,0x60)&2) && (unsigned)(B(object,0x42)-2)<2)I(state,0x440)=0;
            if(!I(state,0x440)) {
                I(state,0x440)=math_random_int_range(180,360);
                if(B(object,0x43)!=9)anim_start_blended(object,9,0,10);
                moby_set_state(object,7,1);
            }
        break; } case 1: {
            int moved;
            if(I(state,0x44C)) moved=crawler_move_toward_goal(object,720,180,720,12,0.1f,4,1);
            else moved=crawler_move_toward_goal(object,180,180,180,12,0.1f,4,1);
            if(moved&0x80) I(state,0x440)=0;
            if(!I(state,0x440)) {
                crawler_choose_goal(object);I(state,0x440)=math_random_int_range(20,60);
                if(B(object,0x43)!=(func_001163B0()&1))anim_start_blended(object,func_001163B0()&1,0,10);
                moby_set_state(object,7,0);
            }
        break; } }
        if(math_random_int_below(7))break;
        if(!I(state,0x48C)) {
            result=SelectNearestListedMoby(object,state+0x210,(float)S(object,0x32),(float)S(state,0x40E),I(state,0x41C),I(state,0x424),I(state,0x420),-1);
            if(result==2 || D_0018C0B4[0]==49) {
                I(state,0x254)=2;
                if(!math_random_int_below(4)) {
                    if(B(object,0x43)!=6)anim_start_blended(object,6,0,math_random_int_range(3,6));
                    moby_set_state(object,8,1);
                }
                if(!I(state,0x448)) {
                    if(B(object,0x43)!=(func_001163B0()&1))anim_start_blended(object,func_001163B0()&1,0,10);
                    moby_set_state(object,6,0);
                }
                break;
            }
        }
        if(!I(state,0x44C) && (vec_distance_xy(object+0x10,state+0x230)<12 || I(state,0x48C))) {
            qcopy_nc(state+0x3F0,state+0x230);
            if(B(object,0x43)!=9)anim_start_blended(object,9,0,math_random_int_range(3,6));
            moby_set_state(object,8,0);I(state,0x480)=0;
        }
        break;
    case 8: {
        int blocked=0;
        qcopy_nc(state+0x3F0,state+0x230);
        switch(B(object,0x95)) {
        case 0:
            if(crawler_move_toward_goal(object,360,180,180,16,0.2f,4,0.5f))I(state,0x480)++;
            if(I(state,0x480)>60) {
                if(vec_distance_xy(object+0x10,state+0x230)<6 && FastDiffRots(F(object,0xF8),mat_fast_helper_a(F(state,0x230)-F(object,0x10),F(state,0x234)-F(object,0x14)))<1.5707964897155762f) {
                    if(B(object,0x43)!=6)anim_start_blended(object,6,0,math_random_int_range(3,6));
                    moby_set_state(object,8,1);
                } else { I(state,0x480)=0; blocked=1; }
            }
            if(vec_distance_xy(object+0x10,state+0x230)<4.2f) {
                if(FastDiffRots(F(object,0xF8),mat_fast_helper_a(F(state,0x230)-F(object,0x10),F(state,0x234)-F(object,0x14)))<1.5707964897155762f) {
                    if(B(object,0x43)!=6)anim_start_blended(object,6,0,math_random_int_range(3,6));
                    moby_set_state(object,8,1);
                }
            }
            if(!I(state,0x48C)) {
                if(blocked || SelectNearestListedMoby(object,state+0x210,(float)S(object,0x32),(float)S(state,0x40E),I(state,0x41C),I(state,0x424),I(state,0x420),-1)==2) {
                    if(!I(state,0x448)) {
                        I(state,0x440)=0;
                        if(B(object,0x43)!=(func_001163B0()&1))anim_start_blended(object,func_001163B0()&1,0,10);
                        moby_set_state(object,6,0);
                    } else {
                        crawler_move_toward_goal(object,360,180,180,16,0.2f,4,0.5f);
                        I(state,0x440)=0;I(state,0x44C)=math_random_int_range(90,180);
                        crawler_choose_goal(object);moby_set_state(object,7,0);
                    }
                    goto update_timers;
                }
            }
            if(I(state,0x48C)>0) {qcopy_nc(state+0x210,g_hero_position);qcopy_nc(state+0x230,g_hero_position);F(state,0x238)+=0.4f;}
            break;
        case 1:
            moby_step_at_own_position(object);
            if(B(object,0x42)==6 && (B(object,0x60)&2)) {
                if(B(object,0x43)!=7)anim_start_blended(object,7,0,5);
                moby_set_state(object,8,2);
            }
            break;
        case 2:
            {u8 *hit=P(state,0x250);
            if(hit)moby_step_at_own_position_factor(object,mat_fast_helper_a(F(hit,0x10)-F(object,0x10),F(hit,0x14)-F(object,0x14)));
            else moby_step_at_own_position_factor(object,mat_fast_helper_a(F(state,0x210)-F(object,0x10),F(state,0x214)-F(object,0x14)));}
            if(B(object,0x42)==7 && moby_get_anim_value(object)>24) {
                crawler_spawn_spit_effect(object);
                if(B(object,0x60)&2) {
                    if(B(object,0x43)!=8)anim_start_blended(object,8,0,10);
                    moby_set_state(object,8,3);
                }
            }
            break;
        case 3:
            moby_step_at_own_position(object);
            if(B(object,0x60)&2) {
                I(state,0x48C)=0;I(state,0x440)=0;I(state,0x448)=0;I(state,0x480)=0;
                I(state,0x44C)=math_random_int_range(90,180);moby_set_state(object,7,0);crawler_choose_goal(object);
            }
            break;
        }
        break;
    }
    case 9:
        I(state,0x430)++; result=moby_dispatch_action_by_kind(object,state+0x50);
        if(result&1)moby_set_state(object,11,-1);
        else if((result&2) || I(state,0x430)>360) {
            I(state,0x430)=0;B(state,0x6A)=2;qzero_nc(state+0x1C0);I(state,0x440)=0;
            if(F(state,0x20)<=0)moby_set_state(object,11,-1);
            else if(!coll_check_object_inside_polygon(object)) {
                if(B(object,0x43)!=9)anim_start_blended(object,9,0,10);
                moby_set_state(object,10,-1);
            } else {
                if(B(object,0x43))anim_start_blended(object,0,0,10);
                moby_set_state(object,7,0);
            }
        }
        break;
    case 10:
        F(state,0x154)=0.1f;moby_l01_turn_toward_target(object,state+0x3E0);
        if(!(I(state,0x1B4)&0x100))moby_set_state(object,7,0);
        break;
    case 11: {
        int index;
        u8 idx;
        part_spawn_sparks_around(object);part_spawn_yellow_spark_burst(object,D_L08_001A8F20);
        SpawnExplosionEffects(object,D_L08_001A8F20,0,0,0,4,0,0,2,1,9,1,-1,0,0,0,-1,1,0x810001);
        SetDeathBits(object,0,3);
        D_L08_0021DE80.flags[S(object,0xB2)]=B(object,0xB0)+2;
        index=B(object,0xB0);
        if(index==0xFF || (idx=index, !(D_L08_001B2840[idx]&0x80) && (D_0019B2E8[idx+(g_current_map_index<<4)]&0x80)))
            D_L08_0021EAF0.flags[S(object,0xB2)]=B(object,0xB0)+2;
        if(H(object,0xB2)&1) {
            u8 *flag=D_0019B4A8+((S(object,0xB2)>>1)+(g_current_map_index<<10));
            if(((*flag>>4)&7)!=7)*flag+=0x10;
        } else {
            u8 *flag=D_0019B4A8+((S(object,0xB2)>>1)+(g_current_map_index<<10));
            if((*flag&7)!=7)++*flag;
        }
        moby_mark_spawned(object);
        return;
    }
    }
    update_timers:
    crawler_tick_timers(object);
    if(F(object,0x10)<30 || F(object,0x10)>993 || F(object,0x14)<30 || F(object,0x14)>993 || F(object,0x18)<30 || F(object,0x18)>993)moby_mark_spawned(object);
}
