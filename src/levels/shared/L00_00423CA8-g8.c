#include "common.h"
extern char *D_L00_001B8E10 __attribute__((section(".data")));
extern char D_L00_001BF220_1[],D_L00_001BF230[];
typedef struct { char pad[0x2290]; char *owner; } Player3C;
extern Player3C D_00189E20;
extern void *D_L00_001B1850[] __attribute__((sda));
extern float D_L00_001B14D0 __attribute__((sda));
extern void func_00282C88(void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282E48(void *,void *);
extern float func_L00_00341D08(void *,void *,void *,void *,float);
extern int func_00277258(void *,void *,void *,float);
extern void func_L00_00423BC0(void *,void *,void *,void *,void *,float,float);
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
int func_L00_00423CA8(char *obj,void *point,int index,float blend,float radius)
{
    float accumulated[4], difference[4], original[4], plane[4], hit[4], endpoint[4], closest[4], correction[4];
    char *base=P(obj,112);
    char *movement=base+352;
    char *state=base+496;
    char *origin;
    char *global=P(D_L00_001B8E10,112);
    float threshold;
    float distance, limit;
    int result=0;
    threshold=D_L00_001B14D0+F(global,564)*F(global,556)*(F(global,560)-1.0f);
    func_00282C88(accumulated);
    qcopy(original,point);
    qcopy(plane,D_L00_001BF220_1);
    qcopy(hit,D_L00_001BF230);
    origin=base+176;
    FastVecAdd(endpoint,origin,movement);
    distance=ProjectPointOntoSegment(closest,plane,origin,endpoint,0.0f);
    limit=fast_vec_dist(origin,closest);
    limit /= F(movement,44)-F(state,48);
    limit=(D_L00_001B14D0+(threshold-D_L00_001B14D0)*limit)*0.75f;
    if(distance<limit) {
        result=1;
        func_L00_00423BC0(obj,accumulated,closest,plane,original,limit-distance,blend);
        qcopy(point,hit);
        if(func_00277258(point,D_L00_001B1850[0],D_00189E20.owner,radius)) {
            FastVecSub(difference,original,point);
            FastVecAdd(plane,D_L00_001BF220_1,difference);
            distance=ProjectPointOntoSegment(closest,plane,origin,endpoint,0.0f);
            limit=fast_vec_dist(origin,closest);
            limit /= F(movement,44)-F(state,48);
            limit=(D_L00_001B14D0+(threshold-D_L00_001B14D0)*limit)*0.75f;
            if(distance<limit) {
                func_L00_00423BC0(obj,correction,closest,plane,original,limit-distance,blend);
                FastVecAdd(accumulated,accumulated,correction);
                qcopy(point,D_L00_001BF230);
                if(func_00277258(point,D_L00_001B1850[0],D_00189E20.owner,radius)) {
                    FastVecSub(difference,original,point);
                    FastVecAdd(plane,D_L00_001BF220_1,difference);
                    distance=ProjectPointOntoSegment(closest,plane,origin,endpoint,0.0f);
                    limit=fast_vec_dist(origin,closest);
                    limit /= F(movement,44)-F(state,48);
                    limit=(D_L00_001B14D0+(threshold-D_L00_001B14D0)*limit)*0.75f;
                    if(distance<limit) {
                        func_L00_00423BC0(obj,correction,closest,plane,original,limit-distance,blend);
                        FastVecAdd(accumulated,accumulated,correction);
                    }
                }
            }
        }
    }
    FastVecAdd(point,original,accumulated);
    return result;
}
