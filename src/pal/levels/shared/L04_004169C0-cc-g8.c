/* func_PAL_L04_004169C0, the PAL copy of func_L04_00412308: the same C, where rename func_L04_00410F80 becomes func_PAL_L04_004155D8. */
#include "common.h"
typedef struct {
    u8 pad000[0x11C];
    float routeDistance;
    int path;
    u8 pad124[0x15C-0x124];
    int checkpointArmed;
    int lap;
    int pad164;
    int nearestPlayer;
    u8 pad16C[0x1A0-0x16C];
    int finished;
    u8 pad1A4[0x1BC-0x1A4];
    int steeringTimer;
    int boostTimer;
    u8 pad1C4[0x1E4-0x1C4];
    float boostAmount;
    float boostScale;
    float boostPhase;
    int boostRequests;
} RaceRivalState;

typedef struct {
    u8 pad00[0x1C];
    float length;
} RaceRoute;
typedef struct RaceObject {
    u8 pad00[0x10];
    int position[4];
    u8 state;
    u8 pad21[0x68-0x21];
    RaceRivalState *vars;
    u8 pad6C[0x100-0x6C];
} RaceObject;
typedef struct {
    u8 pad000[0x190-0x0];
    int x190;
    int x194;
    u8 pad198[0x1E4-0x198];
    int x1E4[21];
    u8 pad238[0x27C-0x238];
    float x27C;
    u8 pad280[0x310-0x280];
    float x310;
    int x314;
    int x318;
    int x31C;
    int x320;
    u8 pad324[0x330-0x324];
    int x330;
    int x334;
    u8 pad338[0x340-0x338];
    int x340;
    int x344;
    u8 pad348[0x398-0x348];
    int x398;
    u8 pad39C[0x3A4-0x39C];
    int x3A4;
    int x3A8;
    RaceObject *x3AC;
    RaceObject *x3B0;
    int x3B4;
    float x3B8;
    u8 pad3BC[0x48C-0x3BC];
    int x48C;
    u8 pad490[0x4C4-0x490];
    RaceObject *x4C4;
    u8 pad4C8[0x63C-0x4C8];
    float x63C;
    u8 pad640[0x654-0x640];
    int x654;
    int x658;
    int x65C;
    u8 pad660[0x6A0-0x660];
    int x6A0;
    u8 pad6A4[0x6D0-0x6A4];
    RaceRoute *x6D0;
    int x6D4;
    float x6D8;
    u8 pad6DC[0x6E0-0x6DC];
    int x6E0;
    u8 pad6E4[0x710-0x6E4];
    int x710;
    u8 pad714[0x75C-0x714];
    int x75C;
} RaceState;

extern int g_current_lap MACRO_ADDR;
extern int g_race_time_ticks MACRO_ADDR;
extern int g_race_state_flags[] MACRO_ADDR;
extern int g_race_bike_mode __attribute__((sda));
extern int g_race_progress_counter __attribute__((sda));
extern int g_race_banner_timer __attribute__((sda));
extern int g_race_saved_progress_counter __attribute__((sda));
extern int g_race_extra_ticks __attribute__((sda));
extern int g_current_race_index __attribute__((sda));
extern int g_race_hud_message_timer __attribute__((sda));
extern float g_race_checkpoint_duration __attribute__((sda));
extern int g_player_bolts MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern u8 g_extras_unlocked_flag MACRO_ADDR;
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern int g_race_best_times_primary[] __attribute__((sda));
typedef struct {
    int reserved[2];
    int reward[3];
    u8 pad14[0x40-0x14];
} RaceReward;
extern RaceReward g_race_challenge_table[];
extern RaceRoute *g_route_path_table[];
extern RaceObject *g_moby_l04_pool;
extern void racer_find_zone_slot(void *);
extern float UpdateNearestRoutePoint(void *,void *,int *,int *,int,int);
extern void UpdateRacerRanks(void *,int);
extern int math_fast_float_d(int *);
extern int IsPointInCuboid(void *,int);
extern int PlayMobySound(int,int,void *);
extern void snd_stop_voice(int);
extern int FindNearestRoutePointIndex(void *,void *,int);
extern float IntToFloat(int);
extern void anim_sample_key_track(float,float,void *,void *,void *,void *);
extern void func_PAL_L04_004155D8(void *);
extern void racer_release_sound_handles(void *,void *);
extern void race_increment_course_finish_count(int), race_increment_course_win_count(int);
extern int race_get_course_win_count(int), race_get_course_finish_count(int);
extern void script_queue_keyed_request(int,int);
extern void snd_send_cmd22(int);
extern int snd_Pump(void);
extern int MemcardSave(int,int);
extern void FastVecSub(void *,void *,void *);
extern float func_L00_002EE290(void *);
extern int math_random_int_below(int),math_random_int_range(int,int);

int race_update_player_progress_pal(RaceObject *object,RaceState *state)
{
    float delta[4] __attribute__((aligned(16)));
    int oldPath, oldPoint, n, level, ticks, limit, done, empty, *bestTime;
    int *slot, i, rank;
    RaceRoute *route;
    RaceObject *other;
    RaceRivalState *vars, *loopVars;
    float time, nearest, otherTime, length, distance, start;
    racer_find_zone_slot(object);
    {
        float previous=state->x310;
        int lap=g_current_lap, mode=g_race_bike_mode;
        oldPath=state->x314; oldPoint=state->x318;
        state->x3B8=previous;
        state->x310=UpdateNearestRoutePoint(object,state,&state->x314,&state->x318,lap,mode);
    }
    if (state->x310<state->x3B8 || (state->x318>=451 && oldPoint<3))
        state->x3A4++;
    else state->x3A4=0;
    if (oldPath!=state->x314) state->x3A8=10;
    if (state->x3A8>0) math_fast_float_d(&state->x3A8);
    else UpdateRacerRanks(object,0);
    {
    g_race_progress_counter++;
    g_race_time_ticks++;
    if (IsPointInCuboid(object->position,state->x194)) {
        if (state->x3A4>0) state->x31C=0;
        else state->x31C=1;
    }
    }
    if (IsPointInCuboid(object->position,state->x190) && state->x31C) {
        if (g_current_lap<2) {
            g_current_lap++;
            g_race_banner_timer=150;
            PlayMobySound(13,0,object);
            g_race_saved_progress_counter=g_race_progress_counter;
            g_race_progress_counter=0;
            state->x31C=0;
        } else {
            state->x6D0=g_route_path_table[state->x6E0];
            length=IntToFloat(FindNearestRoutePointIndex(object,state->x6D0,0))*state->x6D0->length;
            if (g_race_bike_mode) start=length+20.0f;
            else start=length+5.0f;
            state->x6D8=start;
            route=state->x6D0;
            anim_sample_key_track(start,route->length,route,&state->x654,&state->x6D4,&state->x6A0);
            state->x65C=-1000; state->x710=200; state->x658=0;
            object->state=3;
            state->x398=50;
            g_race_extra_ticks=0;
            PlayMobySound(23,17,object);
            snd_stop_voice(state->x330);
            state->x330=PlayMobySound(20,4,object);
            snd_stop_voice(state->x334);
            state->x334=PlayMobySound(21,4,object);
            UpdateRacerRanks(object,1);
            func_PAL_L04_004155D8(object);
            racer_release_sound_handles(object,state);
            if (state->x320!=1) {
                int difficulty=g_current_race_index;
                state->x340++;
                race_increment_course_finish_count(difficulty);
                script_queue_keyed_request(state->x48C,-1);
            } else {
                script_queue_keyed_request(state->x75C,-1);
                {
                int difficulty=g_current_race_index;
                state->x344++;
                race_increment_course_win_count(difficulty);
                }
                n=race_get_course_win_count(g_current_race_index);
                if (n>3) n=3;
                if (n>0) {
                    int scale=10;
                    int reward=g_race_challenge_table[g_current_race_index].reward[n-1];
                    int multiplier=g_extras_unlocked_flag;
                    int money=g_player_bolts;
                    int total;
                    if (multiplier) total=reward*scale+money;
                    else total=money+reward;
                    g_player_bolts=total;
                }
            }
            if (state->x320!=-1) {
                int offset=g_current_race_index*4;
                offset=g_current_map_index==4?offset:offset+20;
                bestTime=(int *)((u8 *)g_race_best_times_primary+offset);
                if (g_race_time_ticks<*bestTime || !*bestTime) *bestTime=g_race_time_ticks;
            }
                g_race_state_flags[5]=1;
                snd_send_cmd22(93); snd_Pump();
                level=g_current_map_index;
                limit=level==4?6500:7350;
                ticks=g_race_time_ticks;
                done=0;
                if (ticks>0) {
                    ticks/=5;
                    if (limit/5>=ticks) {
                    if (level==4) {
                        if (!g_item_enabled_flags[2]) {g_item_enabled_flags[2]=1;g_race_hud_message_timer=250;done=1;}
                    } else if (level==11) {
                        if (!g_item_enabled_flags[3]) {g_item_enabled_flags[3]=1;g_race_hud_message_timer=250;done=1;}
                    }
                    }
                }
                if (done || g_current_map_index==4 ||
                    (g_current_map_index==11 && (g_current_race_index!=0 || race_get_course_win_count(0)>=2)))
                    MemcardSave(0,-1);
            return 1;
        }
    }
    time=state->x310;
    state->x320=1;
    nearest=999.0f;
    state->x3B0=0;
    if (time>700.0f && !state->x31C) time-=g_race_checkpoint_duration;
    empty=-1;
    slot=state->x1E4;
    for (i=20;i>=0;i--,slot++) {
        if (*slot==empty) continue;
        other=g_moby_l04_pool+*slot;
        if ((unsigned)(other->state-2)>=2) continue;
        loopVars=other->vars;
        otherTime=loopVars->routeDistance;
        if (otherTime>700.0f && !loopVars->checkpointArmed) otherTime-=g_race_checkpoint_duration;
        if (!loopVars->finished) {
            int otherLap=loopVars->lap, playerLap=g_current_lap;
            if (playerLap>=otherLap) {
                if (!(time<=otherTime)) goto skipRank;
                if (otherLap!=playerLap) goto skipRank;
            }
        }
        state->x320++;
skipRank:
        loopVars->nearestPlayer=0;
        FastVecSub(delta,object->position,other->position);
        distance=func_L00_002EE290(delta);
        if (distance<nearest) {state->x3B0=other;nearest=distance;}
    }
    if (state->x3B0) {
        vars=state->x3B0->vars;
        vars->nearestPlayer=1;
        if (nearest<10.0f) {
            rank=(int)((4-g_current_race_index)*3.75f)+2+(int)(race_get_course_finish_count(g_current_race_index)*0.3f);
            if (g_race_time_ticks>=51 && vars->boostRequests<4 && vars->boostTimer<=0 &&
                !state->x4C4 && state->x3B0->state==2 && state->x314==vars->path &&
                (g_current_lap<=vars->lap || state->x27C<=0.0f) && !math_random_int_below(rank-1)) {
                int delay;
                rank=(g_current_race_index+1)*120;
                delay=math_random_int_range(120,360)+360;
                vars->steeringTimer=0; vars->boostTimer=rank+delay;
                vars->boostAmount=1.0f; vars->boostScale=1.0f; vars->boostPhase=0.0f;
                vars->boostRequests=0;
                state->x63C=1.0f;state->x4C4=state->x3B0;
            } else if (vars->boostTimer<=0) {
                if (nearest<10.0f) vars->boostRequests=4;
                else vars->boostRequests=0;
            }
        }
    }
    if (state->x3AC!=state->x3B0) {state->x3AC=state->x3B0;state->x3B4=0;}
    return 0;
}
