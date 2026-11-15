#include "include_asm.h"

#include "common.h"
extern int g_current_map_index;
extern u8 D_001A7B00;
extern u8 D_0019B4A8[];
extern u8 D_0019B2E8[];
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
extern int D_00138324 NOT_SDA;
extern int currentLevelGp SDATA(D_001A79F0);
extern int D_L06_001A8FB4 __attribute__((sda));
extern int D_L06_001AF524 __attribute__((sda));
extern float D_L06_001AF528 __attribute__((sda));
extern float D_L06_001AF530 __attribute__((sda));
extern float D_L06_001AF53C __attribute__((sda));
extern char *g_path_list[];
typedef struct { char pad0[0x464]; u8 collected[1]; } RouteLevelState;
extern RouteLevelState D_L06_0021E830;
extern void moby_mark_spawned(void *);
extern int taxi_is_flying(void *);
extern void table_set_entry_field(void *, int);
extern void effect_create_timed(void *, void *, int, int, int, int, int, float);
extern float mat_fast_helper_a(float, float);
extern int moby_fuse_linked_objects(void *, void *, void *, int, int);
extern int IsPointInCuboid(void *, int);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern float MobySpringTurn(void *, void *, float, float, float, float);
extern int moby_move_along_path(void *, int, void *);
extern float math_approach_target_with_direction_mode(void *, float, void *, float, float, float, int);
extern void func_US2_L06_003E5228(void *, int);
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
    int unknown68;
    float pitchRate;
    float rollRate;
    int forcedRoute;
    int pointIndex;
    int enabled;
    int trigger[5], approach[5], depart[5], back[5];
    char padD0[0x2C];
    float yawRate;
    int persistent;
    int returnTimer;
    float baseHeight;
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

void func_US2_L06_003E5460(char *moby)
{
    float oldpos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    Routes *st = *(Routes **)(moby+0x68);
    char *node;
    if (g_current_map_index == 11) {
      if (!st->persistent && D_001A7B00) {
        moby_mark_spawned(moby);
        return;
      }
    }
    table_set_entry_field(moby,taxi_is_flying(moby));
    if (D_L06_001AF524) {
        int i;
        for(i=0;i<I(g_path_list[st->approach[0]],0);i++)
            effect_create_timed(g_path_list[st->approach[0]]+16+i*16,moby,4,0x800000FF,127,2,255,0.333f);
        for(i=0;i<I(g_path_list[st->depart[0]],0);i++)
            effect_create_timed(g_path_list[st->depart[0]]+16+i*16,moby,4,0x8000FF00,127,2,255,0.333f);
        for(i=0;i<I(g_path_list[st->back[0]],0);i++)
            effect_create_timed(g_path_list[st->back[0]]+16+i*16,moby,4,0x80FF0000,127,2,255,0.333f);
    }
    qcopy(oldpos,moby+0x10);
    qcopy(oldrot,moby+0xF0);
    switch(M->state) {
    case 0:
        st->baseHeight=F(moby,0x18);
        if(st->approach[0]!=-1) {
            rot[2]=mat_fast_helper_a(F(g_path_list[st->approach[0]],0x20)-F(moby,0x10),F(g_path_list[st->approach[0]],0x24)-F(moby,0x14));
            if ((H(moby,0x34)^1)&1) {
                node=g_path_list[st->approach[0]];
                qcopy(moby+0x10,node+0x10);
                qcopy(moby+0xF0,rot);
                st->baseHeight=F(node,0x18);
            } else {
                moby_fuse_linked_objects(moby,g_path_list[st->approach[0]]+16,rot,0,0);
                st->baseHeight=F(g_path_list[st->approach[0]],0x18);
            }
        } else if(st->depart[0]!=-1) {
            rot[2]=mat_fast_helper_a(F(g_path_list[st->depart[0]],0x20)-F(moby,0x10),F(g_path_list[st->depart[0]],0x24)-F(moby,0x14));
            if ((H(moby,0x34)^1)&1) {
                node=g_path_list[st->depart[0]];
                qcopy(moby+0x10,node+0x10);
                qcopy(moby+0xF0,rot);
                st->baseHeight=F(node,0x18);
            } else {
                moby_fuse_linked_objects(moby,g_path_list[st->depart[0]]+16,rot,0,0);
                st->baseHeight=F(g_path_list[st->depart[0]],0x18);
            }
        }
        M->flags32=0x80; B(moby,0x30)=255; st->forcedRoute=-1;
        M->state=1; I(moby,0x98)=0;
        {
            u16 id=H(moby,0xB2);
            if (!D_L06_0021E830.collected[(s16)id]) {
                int bits=D_0019B4A8[((s16)id>>1)+(currentLevelGp<<10)];
                if (!((id & 1) ? ((bits >> 4) & 7) != 0 : (bits & 7) != 0)) break;
            }
            moby_mark_spawned(moby); return;
        }
    case 1: {
        int i;
        if (!st->enabled) break;
        if (!(D_0019B2E8[B(moby,0xB0)+(currentLevelGp<<4)]&0x80)) break;
        for(i=0;i<5;i++) {
            if(st->trigger[i]==-1 && st->forcedRoute!=i) continue;
            if(!IsPointInCuboid(g_hero_position,st->trigger[i]) && st->forcedRoute!=i) continue;
            I(moby,0x98)=I(*(char **)(moby+0x24),0x10);
            if(st->approach[i]!=-1) {
                rot[2]=mat_fast_helper_a(F(g_path_list[st->approach[i]],0x20)-F(moby,0x10),F(g_path_list[st->approach[i]],0x24)-F(moby,0x14));
                moby_fuse_linked_objects(moby,g_path_list[st->approach[i]]+16,rot,0,0);
                st->baseHeight=F(g_path_list[st->approach[i]],0x18);
            } else if (st->depart[i]!=-1) {
                if(fast_vec_dist(moby+0x10,g_path_list[st->depart[i]]+16)>4) {
                    rot[2]=mat_fast_helper_a(F(g_path_list[st->depart[i]],0x20)-F(moby,0x10),F(g_path_list[st->depart[i]],0x24)-F(moby,0x14));
                    moby_fuse_linked_objects(moby,g_path_list[st->depart[i]]+16,rot,0,0);
                    st->baseHeight=F(g_path_list[st->depart[i]],0x18);
                }
                MobySpringTurn(moby,&st->yawRate,mat_fast_helper_a(F(g_path_list[st->depart[i]],0x20)-F(moby,0x10),F(g_path_list[st->depart[i]],0x24)-F(moby,0x14)),0.00116355298087f,0.00116355298087f,0.104719772935f);
            }
            M->route=i; M->state=2; M->flags32=0x80;
            st->timer=D_L06_001AF528*(1.0f/60); st->moving=1; st->forcedRoute=-1;
            break;
        }
        break;
    }
    case 2:
        if(st->approach[M->route]==-1 || moby_move_along_path(moby,st->approach[M->route],&st->pointIndex)) {
            M->state=3; I((char *)st,0xE4)=-1;
        }
        break;
    case 3: {
        int i;
        MobySpringTurn(moby,&st->yawRate,mat_fast_helper_a(F(g_path_list[st->depart[M->route]],0x20)-F(moby,0x10),F(g_path_list[st->depart[M->route]],0x24)-F(moby,0x14)),0.000581776490435f,0.000581776490435f,0.0203621778637f);
        math_approach_target_with_direction_mode(moby+0xF4,0,&st->pitchRate,D_L06_001AF530*0.000004848137291264255f,D_L06_001AF530*0.000004848137291264255f,0.20943954586982727f,0);
        math_approach_target_with_direction_mode(moby+0xF0,0,&st->rollRate,D_L06_001AF53C*0.000004848137291264255f,D_L06_001AF53C*0.000004848137291264255f,0.20943954586982727f,0);
        if(g_hero_state.attached==moby && !g_hero_state.animation) {
            func_US2_L06_003E5228(moby,M->route);
            if((D_00138324&16) && D_L06_001A8FB4==8) {
                st->timer=0; M->state=5; st->moving=1;
            }
        }
        for(i=0;i<5;i++) {
            if(st->trigger[i]==-1 && st->forcedRoute!=i) continue;
            if(i==M->route) continue;
            if(!IsPointInCuboid(g_hero_position,st->trigger[i]) && st->forcedRoute!=i) continue;
            I(moby,0x98)=I(*(char **)(moby+0x24),0x10);
            if(st->approach[i]!=-1) {
                rot[2]=mat_fast_helper_a(F(g_path_list[st->approach[i]],0x20)-F(moby,0x10),F(g_path_list[st->approach[i]],0x24)-F(moby,0x14));
                moby_fuse_linked_objects(moby,g_path_list[st->approach[i]]+16,rot,0,0);
                st->baseHeight=F(g_path_list[st->approach[i]],0x18);
            } else if (st->depart[i]!=-1) {
                if(fast_vec_dist(moby+0x10,g_path_list[st->depart[i]]+16)>4) {
                    rot[2]=mat_fast_helper_a(F(g_path_list[st->depart[i]],0x20)-F(moby,0x10),F(g_path_list[st->depart[i]],0x24)-F(moby,0x14));
                    moby_fuse_linked_objects(moby,g_path_list[st->depart[i]]+16,rot,0,0);
                    st->baseHeight=F(g_path_list[st->depart[i]],0x18);
                }
                MobySpringTurn(moby,&st->yawRate,mat_fast_helper_a(F(g_path_list[st->depart[i]],0x20)-F(moby,0x10),F(g_path_list[st->depart[i]],0x24)-F(moby,0x14)),0.00116355298087f,0.00116355298087f,0.104719772935f);
            }
            M->route=i; M->state=2; M->flags32=0x80;
            st->timer=D_L06_001AF528*(1.0f/60); st->moving=1; st->forcedRoute=-1;
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
        if(moby_move_along_path(moby,st->depart[M->route],&st->pointIndex)) {
            M->state=6; st->returnTimer=120;
        }
        break;
    case 6:
        math_approach_target_with_direction_mode(moby+0xF4,0,&st->pitchRate,D_L06_001AF530*0.000004848137291264255f,D_L06_001AF530*0.000004848137291264255f,0.20943954586982727f,0);
        math_approach_target_with_direction_mode(moby+0xF0,0,&st->rollRate,D_L06_001AF53C*0.000004848137291264255f,D_L06_001AF53C*0.000004848137291264255f,0.20943954586982727f,0);
        if(st->back[M->route]!=-1 && fast_vec_dist(moby+0x10,g_hero_position)>15) {
            M->state=7; st->moving=1;
        } else if(st->back[M->route]==-1 && vec_distance_xy(moby+0x10,g_hero_position)>5) M->state=1;
        break;
    case 7:
        if(moby_move_along_path(moby,st->back[M->route],&st->pointIndex)) {
            M->flags32=0; M->state=1; I(moby,0x98)=0;
        }
        break;
    }
    moby_turn_parts_toward_targets(moby);
    FastVecSub(delta,moby+0x10,oldpos);
    mat_combine_and_store((char *)st+0x20,delta,oldrot,moby+0xF0);
}
