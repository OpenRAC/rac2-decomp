#include "include_asm.h"

#include "common.h"
extern int g_current_map_index;
extern u8 g_inventory_have_flags;
extern u8 g_moby_nibble_table[];
extern u8 g_moby_group_flags[];
typedef struct {
    char pad0[0x212];
    u16 action, mode;
    char pad216[0x126];
    char *attached;
    char pad340[0xE];
    s16 animation;
} RouteHero;
extern RouteHero g_hero_state;
extern char g_hero_position[];
extern int g_pad_held_flags NOT_SDA;
extern int currentLevelGp SDATA(D_001A79F0);
extern int g_route_state_value __attribute__((sda));
extern int g_route_l06_flag __attribute__((sda));
extern float g_path_wait_seconds __attribute__((sda));
extern float g_path_pitch_rate __attribute__((sda));
extern float g_path_roll_rate __attribute__((sda));
extern char *g_path_list[];
typedef struct { char pad0[0x464]; u8 collected[1]; } RouteLevelState;
extern RouteLevelState g_level_collected_flags;
extern void moby_mark_spawned(void *);
extern int taxi_is_flying(void *);
extern void table_set_entry_field(void *, int);
extern unsigned char *effect_create_timed(void *, void *, int, int, int, int, int, float);
extern float mat_fast_helper_a(float, float);
extern int moby_fuse_linked_objects(void *, void *, void *, int, int);
extern int IsPointInCuboid(void *, int);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern float MobySpringTurn(void *, void *, float, float, float, float);
extern int moby_move_along_path(void *, int, void *);
extern float math_approach_target_with_direction_mode(void *, float, void *, float, float, float, int);
extern void hud_show_event_notice_us2(void *, int);
extern int hero_is_on_moby(void *);
extern void path_update_attached_point_table(void *);
extern void moby_turn_parts_toward_targets(void *);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
#define B(p,o) (*(u8 *)((p)+(o)))
typedef struct {
    char pad[0x60];
    float timer;
    int moving;
    int unk_68;
    float pitch_rate;
    float roll_rate;
    int forced_route;
    int point_index;
    int enabled;
    int trigger[5], approach[5], depart[5], back[5];
    char padD0[0x2C];
    float yaw_rate;
    int persistent;
    int return_timer;
    float base_height;
} Routes;
typedef struct {
    char pad0[0x20];
    u8 state;
    char pad21[0x11];
    u16 flags32;
    char pad34[0x88];
    u8 route;
} RouteMoby;
#define M ((RouteMoby *)moby)

/* Moves a route moby (taxi or ship) along its approach, depart and back paths, started by trigger cuboids (v2.00 copy). */
void UpdateRouteMoby_us2(char *moby)
{
    float old_pos[4] __attribute__((aligned(16)));
    float old_rot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    Routes *vars = *(Routes **)(moby+0x68);
    char *node;
    if (g_current_map_index == 11) {
      if (!vars->persistent && g_inventory_have_flags) {
        moby_mark_spawned(moby);
        return;
      }
    }
    table_set_entry_field(moby,taxi_is_flying(moby));
    if (g_route_l06_flag) {
        int i;
        for(i=0;i<I(g_path_list[vars->approach[0]],0);i++)
            effect_create_timed(g_path_list[vars->approach[0]]+16+i*16,moby,4,0x800000FF,127,2,255,0.333f);
        for(i=0;i<I(g_path_list[vars->depart[0]],0);i++)
            effect_create_timed(g_path_list[vars->depart[0]]+16+i*16,moby,4,0x8000FF00,127,2,255,0.333f);
        for(i=0;i<I(g_path_list[vars->back[0]],0);i++)
            effect_create_timed(g_path_list[vars->back[0]]+16+i*16,moby,4,0x80FF0000,127,2,255,0.333f);
    }
    qcopy(old_pos,moby+0x10);
    qcopy(old_rot,moby+0xF0);
    switch(M->state) {
    case 0:
        vars->base_height=F(moby,0x18);
        if(vars->approach[0]!=-1) {
            rot[2]=mat_fast_helper_a(F(g_path_list[vars->approach[0]],0x20)-F(moby,0x10),F(g_path_list[vars->approach[0]],0x24)-F(moby,0x14));
            if ((H(moby,0x34)^1)&1) {
                node=g_path_list[vars->approach[0]];
                qcopy(moby+0x10,node+0x10);
                qcopy(moby+0xF0,rot);
                vars->base_height=F(node,0x18);
            } else {
                moby_fuse_linked_objects(moby,g_path_list[vars->approach[0]]+16,rot,0,0);
                vars->base_height=F(g_path_list[vars->approach[0]],0x18);
            }
        } else if(vars->depart[0]!=-1) {
            rot[2]=mat_fast_helper_a(F(g_path_list[vars->depart[0]],0x20)-F(moby,0x10),F(g_path_list[vars->depart[0]],0x24)-F(moby,0x14));
            if ((H(moby,0x34)^1)&1) {
                node=g_path_list[vars->depart[0]];
                qcopy(moby+0x10,node+0x10);
                qcopy(moby+0xF0,rot);
                vars->base_height=F(node,0x18);
            } else {
                moby_fuse_linked_objects(moby,g_path_list[vars->depart[0]]+16,rot,0,0);
                vars->base_height=F(g_path_list[vars->depart[0]],0x18);
            }
        }
        M->flags32=0x80; B(moby,0x30)=255; vars->forced_route=-1;
        M->state=1; I(moby,0x98)=0;
        {
            u16 id=H(moby,0xB2);
            if (!g_level_collected_flags.collected[(s16)id]) {
                int bits=g_moby_nibble_table[((s16)id>>1)+(currentLevelGp<<10)];
                if (!((id & 1) ? ((bits >> 4) & 7) != 0 : (bits & 7) != 0)) break;
            }
            moby_mark_spawned(moby); return;
        }
    case 1: {
        int i;
        if (!vars->enabled) break;
        if (!(g_moby_group_flags[B(moby,0xB0)+(currentLevelGp<<4)]&0x80)) break;
        for(i=0;i<5;i++) {
            if(vars->trigger[i]==-1 && vars->forced_route!=i) continue;
            if(!IsPointInCuboid(g_hero_position,vars->trigger[i]) && vars->forced_route!=i) continue;
            I(moby,0x98)=I(*(char **)(moby+0x24),0x10);
            if(vars->approach[i]!=-1) {
                rot[2]=mat_fast_helper_a(F(g_path_list[vars->approach[i]],0x20)-F(moby,0x10),F(g_path_list[vars->approach[i]],0x24)-F(moby,0x14));
                moby_fuse_linked_objects(moby,g_path_list[vars->approach[i]]+16,rot,0,0);
                vars->base_height=F(g_path_list[vars->approach[i]],0x18);
            } else if (vars->depart[i]!=-1) {
                if(fast_vec_dist(moby+0x10,g_path_list[vars->depart[i]]+16)>4) {
                    rot[2]=mat_fast_helper_a(F(g_path_list[vars->depart[i]],0x20)-F(moby,0x10),F(g_path_list[vars->depart[i]],0x24)-F(moby,0x14));
                    moby_fuse_linked_objects(moby,g_path_list[vars->depart[i]]+16,rot,0,0);
                    vars->base_height=F(g_path_list[vars->depart[i]],0x18);
                }
                MobySpringTurn(moby,&vars->yaw_rate,mat_fast_helper_a(F(g_path_list[vars->depart[i]],0x20)-F(moby,0x10),F(g_path_list[vars->depart[i]],0x24)-F(moby,0x14)),0.00116355298087f,0.00116355298087f,0.104719772935f);
            }
            M->route=i; M->state=2; M->flags32=0x80;
            vars->timer=g_path_wait_seconds*(1.0f/60); vars->moving=1; vars->forced_route=-1;
            break;
        }
        break;
    }
    case 2:
        if(vars->approach[M->route]==-1 || moby_move_along_path(moby,vars->approach[M->route],&vars->point_index)) {
            M->state=3; I((char *)vars,0xE4)=-1;
        }
        break;
    case 3: {
        int i;
        MobySpringTurn(moby,&vars->yaw_rate,mat_fast_helper_a(F(g_path_list[vars->depart[M->route]],0x20)-F(moby,0x10),F(g_path_list[vars->depart[M->route]],0x24)-F(moby,0x14)),0.000581776490435f,0.000581776490435f,0.0203621778637f);
        math_approach_target_with_direction_mode(moby+0xF4,0,&vars->pitch_rate,g_path_pitch_rate*0.000004848137291264255f,g_path_pitch_rate*0.000004848137291264255f,0.20943954586982727f,0);
        math_approach_target_with_direction_mode(moby+0xF0,0,&vars->roll_rate,g_path_roll_rate*0.000004848137291264255f,g_path_roll_rate*0.000004848137291264255f,0.20943954586982727f,0);
        if(g_hero_state.attached==moby && !g_hero_state.animation) {
            hud_show_event_notice_us2(moby,M->route);
            if((g_pad_held_flags&16) && g_route_state_value==8) {
                vars->timer=0; M->state=5; vars->moving=1;
            }
        }
        for(i=0;i<5;i++) {
            if(vars->trigger[i]==-1 && vars->forced_route!=i) continue;
            if(i==M->route) continue;
            if(!IsPointInCuboid(g_hero_position,vars->trigger[i]) && vars->forced_route!=i) continue;
            I(moby,0x98)=I(*(char **)(moby+0x24),0x10);
            if(vars->approach[i]!=-1) {
                rot[2]=mat_fast_helper_a(F(g_path_list[vars->approach[i]],0x20)-F(moby,0x10),F(g_path_list[vars->approach[i]],0x24)-F(moby,0x14));
                moby_fuse_linked_objects(moby,g_path_list[vars->approach[i]]+16,rot,0,0);
                vars->base_height=F(g_path_list[vars->approach[i]],0x18);
            } else if (vars->depart[i]!=-1) {
                if(fast_vec_dist(moby+0x10,g_path_list[vars->depart[i]]+16)>4) {
                    rot[2]=mat_fast_helper_a(F(g_path_list[vars->depart[i]],0x20)-F(moby,0x10),F(g_path_list[vars->depart[i]],0x24)-F(moby,0x14));
                    moby_fuse_linked_objects(moby,g_path_list[vars->depart[i]]+16,rot,0,0);
                    vars->base_height=F(g_path_list[vars->depart[i]],0x18);
                }
                MobySpringTurn(moby,&vars->yaw_rate,mat_fast_helper_a(F(g_path_list[vars->depart[i]],0x20)-F(moby,0x10),F(g_path_list[vars->depart[i]],0x24)-F(moby,0x14)),0.00116355298087f,0.00116355298087f,0.104719772935f);
            }
            M->route=i; M->state=2; M->flags32=0x80;
            vars->timer=g_path_wait_seconds*(1.0f/60); vars->moving=1; vars->forced_route=-1;
            break;
        }
        break;
    }
    case 4: M->state=5; break;
    case 5:
        if(hero_is_on_moby(moby)) {
            g_hero_state.action=4; g_hero_state.mode=8;
            path_update_attached_point_table(moby);
        }
        if(moby_move_along_path(moby,vars->depart[M->route],&vars->point_index)) {
            M->state=6; vars->return_timer=120;
        }
        break;
    case 6:
        math_approach_target_with_direction_mode(moby+0xF4,0,&vars->pitch_rate,g_path_pitch_rate*0.000004848137291264255f,g_path_pitch_rate*0.000004848137291264255f,0.20943954586982727f,0);
        math_approach_target_with_direction_mode(moby+0xF0,0,&vars->roll_rate,g_path_roll_rate*0.000004848137291264255f,g_path_roll_rate*0.000004848137291264255f,0.20943954586982727f,0);
        if(vars->back[M->route]!=-1 && fast_vec_dist(moby+0x10,g_hero_position)>15) {
            M->state=7; vars->moving=1;
        } else if(vars->back[M->route]==-1 && vec_distance_xy(moby+0x10,g_hero_position)>5) M->state=1;
        break;
    case 7:
        if(moby_move_along_path(moby,vars->back[M->route],&vars->point_index)) {
            M->flags32=0; M->state=1; I(moby,0x98)=0;
        }
        break;
    }
    moby_turn_parts_toward_targets(moby);
    FastVecSub(delta,moby+0x10,old_pos);
    mat_combine_and_store((char *)vars+0x20,delta,old_rot,moby+0xF0);
}
