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
extern void func_PAL_L04_004155D8(void *);
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

int func_PAL_L04_004169C0(RaceObject *object,RaceState *state)
{
    float delta[4] __attribute__((aligned(16)));
    int oldPath, oldPoint, n, level, ticks, limit, done, empty, *bestTime;
    int *slot, i, rank;
    RaceRoute *route;
    RaceObject *other;
    RaceRivalState *vars, *loopVars;
    float time, nearest, otherTime, length, distance, start;
    func_L04_00410F10(object);
    {
        float previous=state->x310;
        int lap=D_L04_001A8FE4, mode=D_L04_001B08F0;
        oldPath=state->x314; oldPoint=state->x318;
        state->x3B8=previous;
        state->x310=func_L04_00410788(object,state,&state->x314,&state->x318,lap,mode);
    }
    if (state->x310<state->x3B8 || (state->x318>=451 && oldPoint<3))
        state->x3A4++;
    else state->x3A4=0;
    if (oldPath!=state->x314) state->x3A8=10;
    if (state->x3A8>0) func_00282948(&state->x3A8);
    else func_L04_00412130(object,0);
    {
    D_L04_001B0918++;
    D_L04_001A8FE8++;
    if (func_002ACBC8(object->position,state->x194)) {
        if (state->x3A4>0) state->x31C=0;
        else state->x31C=1;
    }
    }
    if (func_002ACBC8(object->position,state->x190) && state->x31C) {
        if (D_L04_001A8FE4<2) {
            D_L04_001A8FE4++;
            D_L04_001B091C=150;
            func_002E5CF8(13,0,object);
            D_L04_001B0920=D_L04_001B0918;
            D_L04_001B0918=0;
            state->x31C=0;
        } else {
            state->x6D0=D_L04_001FE340[state->x6E0];
            length=func_00283CE0(func_L04_00400AB0(object,state->x6D0,0))*state->x6D0->length;
            if (D_L04_001B08F0) start=length+20.0f;
            else start=length+5.0f;
            state->x6D8=start;
            route=state->x6D0;
            func_002C96F8(start,route->length,route,&state->x654,&state->x6D4,&state->x6A0);
            state->x65C=-1000; state->x710=200; state->x658=0;
            object->state=3;
            state->x398=50;
            D_L04_001B08F8=0;
            func_002E5CF8(23,17,object);
            func_002E59F8(state->x330);
            state->x330=func_002E5CF8(20,4,object);
            func_002E59F8(state->x334);
            state->x334=func_002E5CF8(21,4,object);
            func_L04_00412130(object,1);
            func_PAL_L04_004155D8(object);
            func_L04_0040E248(object,state);
            if (state->x320!=1) {
                int difficulty=D_L04_001B090C;
                state->x340++;
                func_L04_0040A2B8(difficulty);
                func_L01_00323310(state->x48C,-1);
            } else {
                func_L01_00323310(state->x75C,-1);
                {
                int difficulty=D_L04_001B090C;
                state->x344++;
                func_L04_0040A220(difficulty);
                }
                n=func_L04_0040A1D0(D_L04_001B090C);
                if (n>3) n=3;
                if (n>0) {
                    int scale=10;
                    int reward=D_L04_002C63C0[D_L04_001B090C].reward[n-1];
                    int multiplier=D_001A7A0A;
                    int money=D_001A79F8;
                    int total;
                    if (multiplier) total=reward*scale+money;
                    else total=money+reward;
                    D_001A79F8=total;
                }
            }
            if (state->x320!=-1) {
                int offset=D_L04_001B090C*4;
                offset=D_001A79F0==4?offset:offset+20;
                bestTime=(int *)((u8 *)D_001A7368+offset);
                if (D_L04_001A8FE8<*bestTime || !*bestTime) *bestTime=D_L04_001A8FE8;
            }
                D_L04_001A8ED0[5]=1;
                func_00132AF8(93); func_00132028();
                level=D_001A79F0;
                limit=level==4?6500:7350;
                ticks=D_L04_001A8FE8;
                done=0;
                if (ticks>0) {
                    ticks/=5;
                    if (limit/5>=ticks) {
                    if (level==4) {
                        if (!D_001A7A60[2]) {D_001A7A60[2]=1;D_L04_001B093C=250;done=1;}
                    } else if (level==11) {
                        if (!D_001A7A60[3]) {D_001A7A60[3]=1;D_L04_001B093C=250;done=1;}
                    }
                    }
                }
                if (done || D_001A79F0==4 ||
                    (D_001A79F0==11 && (D_L04_001B090C!=0 || func_L04_0040A1D0(0)>=2)))
                    func_0029B3E0(0,-1);
            return 1;
        }
    }
    time=state->x310;
    state->x320=1;
    nearest=999.0f;
    state->x3B0=0;
    if (time>700.0f && !state->x31C) time-=D_L04_001B0928;
    empty=-1;
    slot=state->x1E4;
    for (i=20;i>=0;i--,slot++) {
        if (*slot==empty) continue;
        other=D_L04_001B24DC+*slot;
        if ((unsigned)(other->state-2)>=2) continue;
        loopVars=other->vars;
        otherTime=loopVars->routeDistance;
        if (otherTime>700.0f && !loopVars->checkpointArmed) otherTime-=D_L04_001B0928;
        if (!loopVars->finished) {
            int otherLap=loopVars->lap, playerLap=D_L04_001A8FE4;
            if (playerLap>=otherLap) {
                if (!(time<=otherTime)) goto skipRank;
                if (otherLap!=playerLap) goto skipRank;
            }
        }
        state->x320++;
skipRank:
        loopVars->nearestPlayer=0;
        func_00282CF0(delta,object->position,other->position);
        distance=func_L00_002EE290(delta);
        if (distance<nearest) {state->x3B0=other;nearest=distance;}
    }
    if (state->x3B0) {
        vars=state->x3B0->vars;
        vars->nearestPlayer=1;
        if (nearest<10.0f) {
            rank=(int)((4-D_L04_001B090C)*3.75f)+2+(int)(func_L04_0040A268(D_L04_001B090C)*0.3f);
            if (D_L04_001A8FE8>=51 && vars->boostRequests<4 && vars->boostTimer<=0 &&
                !state->x4C4 && state->x3B0->state==2 && state->x314==vars->path &&
                (D_L04_001A8FE4<=vars->lap || state->x27C<=0.0f) && !func_002A77E0(rank-1)) {
                int delay;
                rank=(D_L04_001B090C+1)*120;
                delay=func_002A7820(120,360)+360;
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
