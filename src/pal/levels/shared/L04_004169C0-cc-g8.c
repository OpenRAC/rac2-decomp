/* func_PAL_L04_004169C0, the PAL copy of func_L04_00412308: the same C, where rename func_L04_00410F80 becomes func_PAL_L04_004155D8. */
#include "common.h"
typedef struct {
    u8 pad000[0x11C];
    float route_distance;
    int path;
    u8 pad124[0x15C-0x124];
    int checkpoint_armed;
    int lap;
    int pad164;
    int nearest_player;
    u8 pad16C[0x1A0-0x16C];
    int finished;
    u8 pad1A4[0x1BC-0x1A4];
    int steering_timer;
    int boost_timer;
    u8 pad1C4[0x1E4-0x1C4];
    float boost_amount;
    float boost_scale;
    float boost_phase;
    int boost_requests;
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
    int unk_190;
    int unk_194;
    u8 pad198[0x1E4-0x198];
    int unk_1E4[21];
    u8 pad238[0x27C-0x238];
    float unk_27C;
    u8 pad280[0x310-0x280];
    float unk_310;
    int unk_314;
    int unk_318;
    int unk_31C;
    int unk_320;
    u8 pad324[0x330-0x324];
    int unk_330;
    int unk_334;
    u8 pad338[0x340-0x338];
    int unk_340;
    int unk_344;
    u8 pad348[0x398-0x348];
    int unk_398;
    u8 pad39C[0x3A4-0x39C];
    int unk_3A4;
    int unk_3A8;
    RaceObject *unk_3AC;
    RaceObject *unk_3B0;
    int unk_3B4;
    float unk_3B8;
    u8 pad3BC[0x48C-0x3BC];
    int unk_48C;
    u8 pad490[0x4C4-0x490];
    RaceObject *unk_4C4;
    u8 pad4C8[0x63C-0x4C8];
    float unk_63C;
    u8 pad640[0x654-0x640];
    int unk_654;
    int unk_658;
    int unk_65C;
    u8 pad660[0x6A0-0x660];
    int unk_6A0;
    u8 pad6A4[0x6D0-0x6A4];
    RaceRoute *unk_6D0;
    int unk_6D4;
    float unk_6D8;
    u8 pad6DC[0x6E0-0x6DC];
    int unk_6E0;
    u8 pad6E4[0x710-0x6E4];
    int unk_710;
    u8 pad714[0x75C-0x714];
    int unk_75C;
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
extern void race_sort_racers_by_finish_time_pal(void *);
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

/* Updates the player race each frame: follows the route position, counts laps, handles the finish with prizes and records, and works out the rank and the nearest rival, which may get a boost (PAL). */
int race_update_player_progress_pal(RaceObject *object,RaceState *state)
{
    float delta[4] __attribute__((aligned(16)));
    int old_path, old_point, n, level, ticks, limit, done, empty, *best_time;
    int *slot, i, rank;
    RaceRoute *route;
    RaceObject *other;
    RaceRivalState *vars, *loop_vars;
    float time, nearest, other_time, length, distance, start;
    racer_find_zone_slot(object);
    {
        float previous=state->unk_310;
        int lap=g_current_lap, mode=g_race_bike_mode;
        old_path=state->unk_314; old_point=state->unk_318;
        state->unk_3B8=previous;
        state->unk_310=UpdateNearestRoutePoint(object,state,&state->unk_314,&state->unk_318,lap,mode);
    }
    if (state->unk_310<state->unk_3B8 || (state->unk_318>=451 && old_point<3))
        state->unk_3A4++;
    else state->unk_3A4=0;
    if (old_path!=state->unk_314) state->unk_3A8=10;
    if (state->unk_3A8>0) math_fast_float_d(&state->unk_3A8);
    else UpdateRacerRanks(object,0);
    {
    g_race_progress_counter++;
    g_race_time_ticks++;
    if (IsPointInCuboid(object->position,state->unk_194)) {
        if (state->unk_3A4>0) state->unk_31C=0;
        else state->unk_31C=1;
    }
    }
    if (IsPointInCuboid(object->position,state->unk_190) && state->unk_31C) {
        if (g_current_lap<2) {
            g_current_lap++;
            g_race_banner_timer=150;
            PlayMobySound(13,0,object);
            g_race_saved_progress_counter=g_race_progress_counter;
            g_race_progress_counter=0;
            state->unk_31C=0;
        } else {
            state->unk_6D0=g_route_path_table[state->unk_6E0];
            length=IntToFloat(FindNearestRoutePointIndex(object,state->unk_6D0,0))*state->unk_6D0->length;
            if (g_race_bike_mode) start=length+20.0f;
            else start=length+5.0f;
            state->unk_6D8=start;
            route=state->unk_6D0;
            anim_sample_key_track(start,route->length,route,&state->unk_654,&state->unk_6D4,&state->unk_6A0);
            state->unk_65C=-1000; state->unk_710=200; state->unk_658=0;
            object->state=3;
            state->unk_398=50;
            g_race_extra_ticks=0;
            PlayMobySound(23,17,object);
            snd_stop_voice(state->unk_330);
            state->unk_330=PlayMobySound(20,4,object);
            snd_stop_voice(state->unk_334);
            state->unk_334=PlayMobySound(21,4,object);
            UpdateRacerRanks(object,1);
            race_sort_racers_by_finish_time_pal(object);
            racer_release_sound_handles(object,state);
            if (state->unk_320!=1) {
                int difficulty=g_current_race_index;
                state->unk_340++;
                race_increment_course_finish_count(difficulty);
                script_queue_keyed_request(state->unk_48C,-1);
            } else {
                script_queue_keyed_request(state->unk_75C,-1);
                {
                int difficulty=g_current_race_index;
                state->unk_344++;
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
            if (state->unk_320!=-1) {
                int offset=g_current_race_index*4;
                offset=g_current_map_index==4?offset:offset+20;
                best_time=(int *)((u8 *)g_race_best_times_primary+offset);
                if (g_race_time_ticks<*best_time || !*best_time) *best_time=g_race_time_ticks;
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
    time=state->unk_310;
    state->unk_320=1;
    nearest=999.0f;
    state->unk_3B0=0;
    if (time>700.0f && !state->unk_31C) time-=g_race_checkpoint_duration;
    empty=-1;
    slot=state->unk_1E4;
    for (i=20;i>=0;i--,slot++) {
        if (*slot==empty) continue;
        other=g_moby_l04_pool+*slot;
        if ((unsigned)(other->state-2)>=2) continue;
        loop_vars=other->vars;
        other_time=loop_vars->route_distance;
        if (other_time>700.0f && !loop_vars->checkpoint_armed) other_time-=g_race_checkpoint_duration;
        if (!loop_vars->finished) {
            int other_lap=loop_vars->lap, player_lap=g_current_lap;
            if (player_lap>=other_lap) {
                if (!(time<=other_time)) goto skip_rank;
                if (other_lap!=player_lap) goto skip_rank;
            }
        }
        state->unk_320++;
skip_rank:
        loop_vars->nearest_player=0;
        FastVecSub(delta,object->position,other->position);
        distance=func_L00_002EE290(delta);
        if (distance<nearest) {state->unk_3B0=other;nearest=distance;}
    }
    if (state->unk_3B0) {
        vars=state->unk_3B0->vars;
        vars->nearest_player=1;
        if (nearest<10.0f) {
            rank=(int)((4-g_current_race_index)*3.75f)+2+(int)(race_get_course_finish_count(g_current_race_index)*0.3f);
            if (g_race_time_ticks>=51 && vars->boost_requests<4 && vars->boost_timer<=0 &&
                !state->unk_4C4 && state->unk_3B0->state==2 && state->unk_314==vars->path &&
                (g_current_lap<=vars->lap || state->unk_27C<=0.0f) && !math_random_int_below(rank-1)) {
                int delay;
                rank=(g_current_race_index+1)*120;
                delay=math_random_int_range(120,360)+360;
                vars->steering_timer=0; vars->boost_timer=rank+delay;
                vars->boost_amount=1.0f; vars->boost_scale=1.0f; vars->boost_phase=0.0f;
                vars->boost_requests=0;
                state->unk_63C=1.0f;state->unk_4C4=state->unk_3B0;
            } else if (vars->boost_timer<=0) {
                if (nearest<10.0f) vars->boost_requests=4;
                else vars->boost_requests=0;
            }
        }
    }
    if (state->unk_3AC!=state->unk_3B0) {state->unk_3AC=state->unk_3B0;state->unk_3B4=0;}
    return 0;
}
