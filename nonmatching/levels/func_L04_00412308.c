/* 2026-11-03 w02 faithful-contract review, US object checks only.
 * Profile: -O2 -G8 -ffunction-sections.
 * Current check.py: 2032/2032 bytes,0/2 places,first+0xF0.
 * Restored actual int returns of func_00132028 and func_0029B3E0. Counter/temp allocation and global/address scheduling remain.
 * Reopen: Independent race-state/global type and address-class evidence.
 * No linked or cross-release match is claimed; earlier records follow.
 */
/* GPT-6.1 Sol (high), 2026-10-29: retained near miss, no matching credit.
 * USA v1.01, default game -O2 -G8 -ffunction-sections (a dedicated -g8.c unit).
 * check.py: 2032/2032 bytes, 0/2 places; instruction at +0xF0 differs.
 * The frame, entry through the progress calculation, route-start FP sequence,
 * and rival-loop control flow/register allocation now agree with retail.
 * Remaining: counter v0/v1 allocation; route/table addressing and allocation;
 * best-time address scheduling; absolute award stores/delay slots; final stores.
 * Cached call arguments fix entry scheduling. A separate start variable fixes
 * the route FP sequence. A shared increment reached by skipRank fixes the loop.
 * Corrected earlier semantics: post-race work is outside rank != -1; finished
 * and ahead-on-lap racers increment rank; Joba help accepts nonzero difficulty.
 * func_L04_00400AB0 really takes three arguments and returns int (matched C).
 * func_002C96F8's independent EE FP and integer banks allow FP-first ordering.
 * Typed rival fields were byte-neutral. Three counter wordings tied. Caching
 * money changes reward allocation and shortens the body to 2024 bytes.
 * -mno-split-addresses with the structured reward row reproduces the assembler
 * assertion; byte offsets compile there but fold the reward base/offset.
 * Next: derive the surrounding race-state/global types and address classes;
 * avoid retrying counter wordings alone. Bindings/linking remain unvalidated.
 * All needed declarations are below. No other release or full build was run.
 */
#include "common.h"
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern int D_L04_001A8FE4[] __attribute__((sda));
extern int D_L04_001A8FE8[] __attribute__((sda));
extern int D_L04_001A8EE4 NOT_SDA;
extern int D_L04_001B08F0 __attribute__((sda));
extern int D_L04_001B0918 __attribute__((sda));
extern int D_L04_001B091C __attribute__((sda));
extern int D_L04_001B0920 __attribute__((sda));
extern int D_L04_001B08F8 __attribute__((sda));
extern int D_L04_001B090C __attribute__((sda));
extern int D_L04_001B093C __attribute__((sda));
extern float D_L04_001B0928 __attribute__((sda));
extern int D_001A79F8[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern int money_gp SDATA(D_001A79F8) __attribute__((sda));
extern int count_gp SDATA(D_L04_001A8FE4);
extern int ticks_gp SDATA(D_L04_001A8FE8);
extern u8 D_001A7A0A[] __attribute__((sda));
extern u8 D_001A7A62[] __attribute__((sda));
extern u8 D_001A7A63[] __attribute__((sda));
extern int D_001A7368[] __attribute__((sda));
typedef struct {
    int reserved[2];
    int reward[3];
    u8 pad14[0x40-0x14];
} RaceReward;
extern RaceReward D_L04_002C63C0[];
extern u8 *D_L04_001FE340[] __attribute__((sda));
extern u8 *D_L04_001B24DC;
extern void func_L04_00410F10(u8 *);
extern float func_L04_00410788(u8 *,u8 *,int *,int *,int,int);
extern void func_L04_00412130(u8 *,int);
extern int func_00282948(int *);
extern int func_002ACBC8(void *,int);
extern int func_002E5CF8(int,int,void *);
extern void func_002E59F8(int);
extern int func_L04_00400AB0(u8 *,u8 *,int);
extern float func_00283CE0(int);
extern void func_002C96F8(float,float,void *,void *,void *,void *);
extern void func_L04_00410F80(u8 *);
extern void func_L04_0040E248(u8 *,u8 *);
extern void func_L04_0040A2B8(int), func_L04_0040A220(int);
extern int func_L04_0040A1D0(int), func_L04_0040A268(int);
extern void func_L01_00323310(int,int);
extern void func_00132AF8(int);
extern int func_00132028(void);
extern int func_0029B3E0(int,int);
extern void func_00282CF0(void *,void *,void *);
extern float func_L00_002EE290(void *);
extern int func_002A77E0(int),func_002A7820(int,int);

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
    int boostPhase;
    int boostRequests;
} RaceRivalState;

int func_L04_00412308(u8 *object,u8 *state)
{
    float delta[4] __attribute__((aligned(16)));
    int oldPath, oldPoint, n, level, ticks, limit, done, *bestTime;
    int *slot, i, rank;
    u8 *route, *other;
    RaceRivalState *vars, *loopVars;
    float time, nearest, otherTime, length, distance, start;
    func_L04_00410F10(object);
    {
        float previous=F(state,0x310);
        int lap=D_L04_001A8FE4[0], mode=D_L04_001B08F0;
        oldPath=I(state,0x314); oldPoint=I(state,0x318);
        F(state,0x3B8)=previous;
        F(state,0x310)=func_L04_00410788(object,state,(int *)(state+0x314),(int *)(state+0x318),lap,mode);
    }
    if (F(state,0x310)<F(state,0x3B8) || (I(state,0x318)>=451 && oldPoint<3))
        I(state,0x3A4)++;
    else I(state,0x3A4)=0;
    if (oldPath!=I(state,0x314)) I(state,0x3A8)=10;
    if (I(state,0x3A8)>0) func_00282948((int *)(state+0x3A8));
    else func_L04_00412130(object,0);
    {
    int lapTicks=D_L04_001B0918+1, totalTicks=D_L04_001A8FE8[0]+1;
    int checkpoint=I(state,0x194);
    D_L04_001B0918=lapTicks;
    ticks_gp=totalTicks;
    if (func_002ACBC8(object+0x10,checkpoint)) {
        if (I(state,0x3A4)>0) I(state,0x31C)=0;
        else I(state,0x31C)=1;
    }
    }
    if (func_002ACBC8(object+0x10,I(state,0x190)) && I(state,0x31C)) {
        if (count_gp<2) {
            D_L04_001A8FE4[0]=count_gp+1;
            D_L04_001B091C=180;
            func_002E5CF8(13,0,object);
            D_L04_001B0920=D_L04_001B0918;
            D_L04_001B0918=0;
            I(state,0x31C)=0;
        } else {
            route=D_L04_001FE340[I(state,0x6E0)];
            P(state,0x6D0)=route;
            length=func_00283CE0(func_L04_00400AB0(object,route,0))*F(P(state,0x6D0),0x1C);
            if (D_L04_001B08F0) start=length+20.0f;
            else start=length+5.0f;
            F(state,0x6D8)=start;
            route=P(state,0x6D0);
            func_002C96F8(start,F(route,0x1C),route,state+0x654,state+0x6D4,state+0x6A0);
            I(state,0x710)=240; I(state,0x65C)=-1000; I(state,0x658)=0;
            object[0x20]=3;
            I(state,0x398)=60;
            D_L04_001B08F8=0;
            func_002E5CF8(23,17,object);
            func_002E59F8(I(state,0x330));
            I(state,0x330)=func_002E5CF8(20,4,object);
            func_002E59F8(I(state,0x334));
            I(state,0x334)=func_002E5CF8(21,4,object);
            func_L04_00412130(object,1);
            func_L04_00410F80(object);
            func_L04_0040E248(object,state);
            if (I(state,0x320)!=1) {
                int difficulty=D_L04_001B090C;
                I(state,0x340)++;
                func_L04_0040A2B8(difficulty);
                func_L01_00323310(I(state,0x48C),-1);
            } else {
                func_L01_00323310(I(state,0x75C),-1);
                {
                int difficulty=D_L04_001B090C;
                I(state,0x344)++;
                func_L04_0040A220(difficulty);
                }
                n=func_L04_0040A1D0(D_L04_001B090C);
                if (n>3) n=3;
                if (n>0) {
                    int reward=D_L04_002C63C0[D_L04_001B090C].reward[n-1];
                    int multiplier=D_001A7A0A[0];
                    int money;
                    if (multiplier) money=reward*10+money_gp;
                    else money=money_gp+reward;
                    D_001A79F8[0]=money;
                }
            }
            if (I(state,0x320)!=-1) {
                int offset=D_L04_001B090C*4;
                offset=D_001A79F0[0]==4?offset:offset+20;
                bestTime=(int *)((u8 *)D_001A7368+offset);
                if (D_L04_001A8FE8[0]<*bestTime || !*bestTime) *bestTime=D_L04_001A8FE8[0];
            }
                D_L04_001A8EE4=1;
                func_00132AF8(93); func_00132028();
                level=D_001A79F0[0];
                limit=level==4?7800:8820;
                ticks=D_L04_001A8FE8[0];
                done=0;
                if (ticks>0) {
                    ticks/=6;
                    if (limit/6<ticks) goto noAward;
                    if (level==4) {
                        if (!D_001A7A62[0]) {D_001A7A62[0]=1;D_L04_001B093C=300;}
                    } else if (level==11) {
                        if (!D_001A7A63[0]) {D_001A7A63[0]=1;D_L04_001B093C=300;}
                    }
                    done=1;
                }
noAward:
                if (done || D_001A79F0[0]==4 ||
                    (D_001A79F0[0]==11 && (D_L04_001B090C!=0 || func_L04_0040A1D0(0)>=2)))
                    func_0029B3E0(0,-1);
            return 1;
        }
    }
    time=F(state,0x310);
    I(state,0x320)=1;
    nearest=999.0f;
    I(state,0x3B0)=0;
    if (time>700.0f && !I(state,0x31C)) time-=D_L04_001B0928;
    slot=(int *)(state+0x1E4);
    for (i=20;i>=0;i--,slot++) {
        if (*slot==-1) continue;
        other=D_L04_001B24DC+*slot*256;
        if ((unsigned)(other[0x20]-2)>=2) continue;
        loopVars=(RaceRivalState *)P(other,0x68);
        otherTime=loopVars->routeDistance;
        if (otherTime>700.0f && !loopVars->checkpointArmed) otherTime-=D_L04_001B0928;
        if (!loopVars->finished) {
            int otherLap=loopVars->lap, playerLap=D_L04_001A8FE4[0];
            if (playerLap>=otherLap) {
                if (!(time<=otherTime)) goto skipRank;
                if (otherLap!=playerLap) goto skipRank;
            }
        }
        I(state,0x320)++;
skipRank:
        loopVars->nearestPlayer=0;
        func_00282CF0(delta,object+0x10,other+0x10);
        distance=func_L00_002EE290(delta);
        if (distance<nearest) {P(state,0x3B0)=other;nearest=distance;}
    }
    if (P(state,0x3B0)) {
        vars=(RaceRivalState *)P(P(state,0x3B0),0x68);
        vars->nearestPlayer=1;
        if (nearest<10.0f) {
            rank=(int)((4-D_L04_001B090C)*3.75f)+2+(int)(func_L04_0040A268(D_L04_001B090C)*0.3f);
            if (D_L04_001A8FE8[0]>=61 && vars->boostRequests<4 && vars->boostTimer<=0 &&
                !I(state,0x4C4) && P(state,0x3B0)[0x20]==2 && I(state,0x314)==vars->path &&
                (D_L04_001A8FE4[0]<=vars->lap || F(state,0x27C)<=0.0f) && !func_002A77E0(rank-1)) {
                rank=(D_L04_001B090C+1)*120;
                n=func_002A7820(120,360)+360;
                vars->boostRequests=0; vars->steeringTimer=0; vars->boostTimer=rank+(n);
                vars->boostAmount=1.0f; vars->boostScale=1.0f; vars->boostPhase=0.0f;
                F(state,0x63C)=1.0f;P(state,0x4C4)=P(state,0x3B0);
            } else if (vars->boostTimer<=0) {
                if (nearest<10.0f) vars->boostRequests=4;
                else vars->boostRequests=0;
            }
        }
    }
    if (I(state,0x3AC)!=I(state,0x3B0)) {I(state,0x3AC)=I(state,0x3B0);I(state,0x3B4)=0;}
    return 0;
}
