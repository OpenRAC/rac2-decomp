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
    int finishLine;
    int checkpointLine;
    u8 pad198[0x1E4-0x198];
    int racerSlots[21];
    u8 pad238[0x27C-0x238];
    float speed;
    u8 pad280[0x310-0x280];
    float routeDistance;
    int path;
    int pathPoint;
    int checkpointArmed;
    int rank;
    u8 pad324[0x330-0x324];
    int x330;
    int x334;
    u8 pad338[0x340-0x338];
    int lossCount;
    int winCount;
    u8 pad348[0x398-0x348];
    int x398;
    u8 pad39C[0x3A4-0x39C];
    int wrongWayCount;
    int pathChangeTimer;
    RaceObject *trackedRacer;
    RaceObject *nearestRacer;
    int trackedTime;
    float prevRouteDistance;
    u8 pad3BC[0x48C-0x3BC];
    int x48C;
    u8 pad490[0x4C4-0x490];
    RaceObject *boostTarget;
    u8 pad4C8[0x63C-0x4C8];
    float x63C;
    u8 pad640[0x654-0x640];
    int routePoint;
    int x658;
    int routeTimer;
    u8 pad660[0x6A0-0x660];
    int x6A0;
    u8 pad6A4[0x6D0-0x6A4];
    RaceRoute *route;
    int x6D4;
    float routeSpeed;
    u8 pad6DC[0x6E0-0x6DC];
    int homeRoute;
    u8 pad6E4[0x710-0x6E4];
    int switchTimer;
    u8 pad714[0x75C-0x714];
    int x75C;
} RaceState;

extern int D_L04_001A8FE4 MACRO_ADDR;
extern int D_L04_001A8FE8 MACRO_ADDR;
extern int D_L04_001A8ED0[] MACRO_ADDR;
extern int D_L04_001B08F0 __attribute__((sda));
extern int D_L04_001B0918 __attribute__((sda));
extern int D_L04_001B091C __attribute__((sda));
extern int D_L04_001B0920 __attribute__((sda));
extern int D_L04_001B08F8 __attribute__((sda));
extern int D_L04_001B090C __attribute__((sda));
extern int D_L04_001B093C __attribute__((sda));
extern float D_L04_001B0928 __attribute__((sda));
extern int D_001A79F8 MACRO_ADDR;
extern int D_001A79F0 MACRO_ADDR;
extern u8 D_001A7A0A MACRO_ADDR;
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_001A7368[] __attribute__((sda));
typedef struct {
    int reserved[2];
    int reward[3];
    u8 pad14[0x40-0x14];
} RaceReward;
extern RaceReward D_L04_002C63C0[];
extern RaceRoute *D_L04_001FE340[];
extern RaceObject *D_L04_001B24DC;
extern void func_L04_00410F10(void *);
extern float func_L04_00410788(void *,void *,int *,int *,int,int);
extern void func_L04_00412130(void *,int);
extern int func_00282948(int *);
extern int func_002ACBC8(void *,int);
extern int func_002E5CF8(int,int,void *);
extern void func_002E59F8(int);
extern int func_L04_00400AB0(void *,void *,int);
extern float func_00283CE0(int);
extern void func_002C96F8(float,float,void *,void *,void *,void *);
extern void func_L04_00410F80(void *);
extern void func_L04_0040E248(void *,void *);
extern void func_L04_0040A2B8(int), func_L04_0040A220(int);
extern int func_L04_0040A1D0(int), func_L04_0040A268(int);
extern void func_L01_00323310(int,int);
extern void func_00132AF8(int);
extern int func_00132028(void);
extern int func_0029B3E0(int,int);
extern void func_00282CF0(void *,void *,void *);
extern float func_L00_002EE290(void *);
extern int func_002A77E0(int),func_002A7820(int,int);

/* Updates the player race each frame: follows the route position, counts laps, handles the finish with prizes and records, and works out the rank and the nearest rival, which may get a boost. */
int func_L04_00412308(RaceObject *object,RaceState *state)
{
    float delta[4] __attribute__((aligned(16)));
    int oldPath, oldPoint, winTotal, level, ticks, limit, done, empty, *bestTime;
    int *slot, i, rank;
    RaceRoute *route;
    RaceObject *other;
    RaceRivalState *vars, *loopVars;
    float myDistance, nearestDistance, otherTime, length, distance, start;
    FindRacerZoneSlot(object);
    {
        float previous=state->routeDistance;
        int lap=gCurrentLap, mode=D_L04_001B08F0;
        oldPath=state->path; oldPoint=state->pathPoint;
        state->prevRouteDistance=previous;
        state->routeDistance=UpdateNearestRoutePoint(object,state,&state->path,&state->pathPoint,lap,mode);
    }
    if (state->routeDistance<state->prevRouteDistance || (state->pathPoint>=451 && oldPoint<3))
        state->wrongWayCount++;
    else state->wrongWayCount=0;
    if (oldPath!=state->path) state->pathChangeTimer=10;
    if (state->pathChangeTimer>0) FastFloatHelperD(&state->pathChangeTimer);
    else UpdateRacerRanks(object,0);
    {
    D_L04_001B0918++;
    gRaceTimeTicks++;
    if (IsPointInCuboid(object->position,state->checkpointLine)) {
        if (state->wrongWayCount>0) state->checkpointArmed=0;
        else state->checkpointArmed=1;
    }
    }
    if (IsPointInCuboid(object->position,state->finishLine) && state->checkpointArmed) {
        if (gCurrentLap<2) {
            gCurrentLap++;
            D_L04_001B091C=180;
            PlayMobySound(13,0,object);
            D_L04_001B0920=D_L04_001B0918;
            D_L04_001B0918=0;
            state->checkpointArmed=0;
        } else {
            state->route=gRoutePathTable[state->homeRoute];
            length=IntToFloat(FindNearestRoutePointIndex(object,state->route,0))*state->route->length;
            if (D_L04_001B08F0) start=length+20.0f;
            else start=length+5.0f;
            state->routeSpeed=start;
            route=state->route;
            SampleKeyTrack(start,route->length,route,&state->routePoint,&state->x6D4,&state->x6A0);
            state->routeTimer=-1000; state->switchTimer=240; state->x658=0;
            object->state=3;
            state->x398=60;
            D_L04_001B08F8=0;
            PlayMobySound(23,17,object);
            StopSoundVoice(state->x330);
            state->x330=PlayMobySound(20,4,object);
            StopSoundVoice(state->x334);
            state->x334=PlayMobySound(21,4,object);
            UpdateRacerRanks(object,1);
            SortRacersByFinishTime(object);
            ReleaseRacerSoundHandles(object,state);
            if (state->rank!=1) {
                int difficulty=gCurrentRaceIndex;
                state->lossCount++;
                IncrementCourseFinishCount(difficulty);
                QueueKeyedRequest(state->x48C,-1);
            } else {
                QueueKeyedRequest(state->x75C,-1);
                {
                int difficulty=gCurrentRaceIndex;
                state->winCount++;
                IncrementCourseWinCount(difficulty);
                }
                winTotal=GetCourseWinCount(gCurrentRaceIndex);
                if (winTotal>3) winTotal=3;
                if (winTotal>0) {
                    int scale=10;
                    int reward=gRaceChallengeTable[gCurrentRaceIndex].reward[winTotal-1];
                    int multiplier=D_001A7A0A;
                    int money=gPlayerBolts;
                    int total;
                    if (multiplier) total=reward*scale+money;
                    else total=money+reward;
                    gPlayerBolts=total;
                }
            }
            if (state->rank!=-1) {
                int offset=gCurrentRaceIndex*4;
                offset=gCurrentMapIndex==4?offset:offset+20;
                bestTime=(int *)((u8 *)D_001A7368+offset);
                if (gRaceTimeTicks<*bestTime || !*bestTime) *bestTime=gRaceTimeTicks;
            }
                D_L04_001A8ED0[5]=1;
                SendSoundCommand22(93); snd_Pump();
                level=gCurrentMapIndex;
                limit=level==4?7800:8820;
                ticks=gRaceTimeTicks;
                done=0;
                if (ticks>0) {
                    ticks/=6;
                    if (limit/6>=ticks) {
                    if (level==4) {
                        if (!D_001A7A60[2]) {D_001A7A60[2]=1;D_L04_001B093C=300;done=1;}
                    } else if (level==11) {
                        if (!D_001A7A60[3]) {D_001A7A60[3]=1;D_L04_001B093C=300;done=1;}
                    }
                    }
                }
                if (done || gCurrentMapIndex==4 ||
                    (gCurrentMapIndex==11 && (gCurrentRaceIndex!=0 || GetCourseWinCount(0)>=2)))
                    MemcardSave(0,-1);
            return 1;
        }
    }
    myDistance=state->routeDistance;
    state->rank=1;
    nearestDistance=999.0f;
    state->nearestRacer=0;
    if (myDistance>700.0f && !state->checkpointArmed) myDistance-=D_L04_001B0928;
    empty=-1;
    slot=state->racerSlots;
    for (i=20;i>=0;i--,slot++) {
        if (*slot==empty) continue;
        other=gMobyPool_L04+*slot;
        if ((unsigned)(other->state-2)>=2) continue;
        loopVars=other->vars;
        otherTime=loopVars->routeDistance;
        if (otherTime>700.0f && !loopVars->checkpointArmed) otherTime-=D_L04_001B0928;
        if (!loopVars->finished) {
            int otherLap=loopVars->lap, playerLap=gCurrentLap;
            if (playerLap>=otherLap) {
                if (!(myDistance<=otherTime)) goto skipRank;
                if (otherLap!=playerLap) goto skipRank;
            }
        }
        state->rank++;
skipRank:
        loopVars->nearestPlayer=0;
        FastVecSub(delta,object->position,other->position);
        distance=func_L00_002EE290(delta);
        if (distance<nearestDistance) {state->nearestRacer=other;nearestDistance=distance;}
    }
    if (state->nearestRacer) {
        vars=state->nearestRacer->vars;
        vars->nearestPlayer=1;
        if (nearestDistance<10.0f) {
            rank=(int)((4-gCurrentRaceIndex)*3.75f)+2+(int)(GetCourseFinishCount(gCurrentRaceIndex)*0.3f);
            if (gRaceTimeTicks>=61 && vars->boostRequests<4 && vars->boostTimer<=0 &&
                !state->boostTarget && state->nearestRacer->state==2 && state->path==vars->path &&
                (gCurrentLap<=vars->lap || state->speed<=0.0f) && !RandomIntBelow(rank-1)) {
                int delay;
                rank=(gCurrentRaceIndex+1)*120;
                delay=RandomIntRange(120,360)+360;
                vars->steeringTimer=0; vars->boostTimer=rank+delay;
                vars->boostAmount=1.0f; vars->boostScale=1.0f; vars->boostPhase=0.0f;
                vars->boostRequests=0;
                state->x63C=1.0f;state->boostTarget=state->nearestRacer;
            } else if (vars->boostTimer<=0) {
                if (nearestDistance<10.0f) vars->boostRequests=4;
                else vars->boostRequests=0;
            }
        }
    }
    if (state->trackedRacer!=state->nearestRacer) {state->trackedRacer=state->nearestRacer;state->trackedTime=0;}
    return 0;
}
