/* func_PAL_L00_004295B8, the PAL copy of func_L00_004240D8: the same C, where wrap D_L00_001B14B4 (({e}) * 1.2f). */
#include "common.h"

/* func_PAL_L00_004295B8: -G8 for the $gp constants, -g for the line label that pads the final
 * div.s, and -fstrict-aliasing: retail schedules the halfword store at state+0x34 after the
 * minimum-distance load and leaves the movement+0x2C reload free of it, which only
 * type-based alias analysis allows. The bias and minimum distance are read-only tuning
 * values (their loads move freely across the float stores); the increment is not. */

extern char D_L00_001BF220_1[], D_L00_001B8E50[];
/* The resident block at D_00189E20: an owner object pointer at +0x2290, a mode byte at +0x22B4. */
typedef struct {
    char pad0[0x2290];
    char *owner;
    char pad2294[0x22B4 - 0x2294];
    unsigned char mode;
} L00_004240D8_Player;
extern L00_004240D8_Player D_00189E20;
extern const float D_L00_001B14D0 __attribute__((sda));
extern float D_L00_001B14B4 __attribute__((sda));
extern const float D_L00_001B14C8 __attribute__((sda));
extern float D_00138280 NOT_SDA;
extern void *D_L00_001B1850[] __attribute__((sda));
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00282C48(float);
extern int func_00283CF0(float);
extern int func_L00_004204A0(void *);
extern int func_00277258(void *, void *, void *, float);
extern int func_L00_00424070(void *, int, void *, float);
extern int func_L00_00423CA8(void *, void *, int, float, float);
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define S(p,n) (*(short *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
/* Steps a probe from the owner block's position along its movement direction, testing each
   step for collisions; on a hit it records the result, may pull the follow distance in, and
   re-aims the movement vector at the hit point. */
int func_PAL_L00_004295B8(char *obj)
{
    float original[4], point[4], direction[4], saved[4], previous[4], difference[4];
    char *base=P(obj,112);
    char *camera=base+96;
    char *movement=base+352;
    char *state=base+496;
    int result=0, i;
    float step, total;
    qcopy(original,movement);
    total=0;
    qcopy(point,base+176);
    step=D_L00_001B14D0;
    func_00282F20(direction,original,1.0f);
    for(i=0;i<func_00283CF0(F(state,64)-1.0f);i++) {
        if(i>0 && !func_L00_004204A0(point) &&
           func_00277258(point,D_L00_001B1850[0],D_00189E20.owner,step) &&
           !func_L00_00424070(obj,i,point,step)) {
            qcopy(saved,D_L00_001BF220_1);
            qcopy(previous,point);
            if(func_L00_00423CA8(obj,point,i,total,step)) {
                result=1;
                if (D_00189E20.mode!=2 && func_00282C48(D_00138280)>0.05f) {
                    func_00282CF0(difference,saved,previous);
                    func_00282F20(difference,difference,1.0f);
                    if(func_00282C48(func_00282DB0(D_L00_001B8E50,difference))<0.75f) {
                        F(state,48) += ((D_L00_001B14B4) * 1.2f);
                        S(state,52)=1817;
                        if(F(movement,44)-F(state,48)<D_L00_001B14C8)
                            F(state,48)=F(movement,44)-D_L00_001B14C8;
                    }
                }
                func_00282CF0(difference,point,camera+80);
                func_00282F20(movement,difference,F(movement,44)-F(state,48));
                func_00282F20(direction,movement,1.0f);
            }
        }
        {
            float ratio=(F(movement,44)-F(state,48))/F(movement,44);
            step += F(state,68)*F(state,60);
            total += step;
            func_00282D30(saved,direction,step*ratio);
        }
        func_00282CC0(point,point,saved);
    }
    return result;
}
