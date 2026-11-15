#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V;
extern char *D_L20_001FEC80[];
typedef struct { char pad[0x140]; float x,y; char pad2[0x10]; float yaw; } Camera;
extern Camera D_L20_001B9E80;
extern char D_00189EA0[];
extern int D_L20_001B20D0 __attribute__((sda));
extern float func_00282E80(void *,void *);
extern float func_00283248(float,float);
extern float func_00283C80(float,float);
extern float func_002A89A8(void *,int,float);
extern int func_00277258(void *,float,int,int);
extern int func_002A77E0(int);
extern char *func_L20_00443328(char *,void *);
extern char *func_L20_004431E0(char *,void *);
char *func_L20_00442F80(char *arg0) {
    V pos;
    char *state=*(char **)(arg0+0x68);
    char *points=D_L20_001FEC80[*(int *)(state+0x234)];
    int i,best=-1;
    float angle,limit=3.1415927f;
    for(i=0;i<6;i++) {
        char *p=points+0x10+i*0x10;
        if (*(int *)(state+0x182C)==0 && i!=0 && i!=3) continue;
        if (*(int *)(state+0x182C)==1 && (i==0 || i==3)) continue;
        if (vec_distance_xy(p,D_00189EA0)>3.0f && vec_distance_xy(p,arg0+0x10)>6.0f) {
            angle=func_00283248(*(float *)p-D_L20_001B9E80.x,*(float *)(p+4)-D_L20_001B9E80.y);
            angle=FastDiffRots(D_L20_001B9E80.yaw,angle);
            if (angle<limit) {
                qcopy(&pos,p);
                pos.f[2]=func_002A89A8(&pos,0,0.5f)+0.6f;
                if (!func_00277258(&pos,0.5f,0,0)) {limit=angle;best=i;}
            }
        }
    }
    if(best==-1) return 0;
    qcopy(&pos,points+best*0x10+0x10);
    pos.f[2]=func_002A89A8(&pos,0,0.5f);
    if(D_L20_001B20D0 || (*(int *)(state+0x182C)!=0 && func_002A77E0(2))) return func_L20_00443328(arg0,&pos);
    return func_L20_004431E0(arg0,&pos);
}
