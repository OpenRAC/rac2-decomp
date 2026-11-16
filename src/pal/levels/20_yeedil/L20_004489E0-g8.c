#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V;
extern char *g_path_point_tables[];
typedef struct { char pad[0x140]; float x,y; char pad2[0x10]; float yaw; } Camera;
extern Camera g_hero_l20_extra_state;
extern char g_hero_position[];
extern int g_yeedil_force_minion_spawn __attribute__((sda));
extern float vec_distance_xy(void *,void *);
extern float mat_fast_helper_a(float,float);
extern float FastDiffRots(float,float);
extern float coll_probe_ground_height_below(void *,int,float);
extern int coll_test_point(void *,float,int,int);
extern int math_random_int_below(int);
extern char *moby_activate_linked_child_pal(char *,void *);
extern char *yeedil_boss_place_group_member_pal(char *,void *);

char *yeedil_boss_spawn_minion_at_point_pal(char *arg0) {
    V pos;
    char *state=*(char **)(arg0+0x68);
    char *points=g_path_point_tables[*(int *)(state+0x234)];
    int i,best=-1;
    float angle,limit=3.1415927f;
    for(i=0;i<6;i++) {
        char *p=points+0x10+i*0x10;
        if (*(int *)(state+0x182C)==0 && i!=0 && i!=3) continue;
        if (*(int *)(state+0x182C)==1 && (i==0 || i==3)) continue;
        if (vec_distance_xy(p,g_hero_position)>3.0f && vec_distance_xy(p,arg0+0x10)>6.0f) {
            angle=mat_fast_helper_a(*(float *)p-g_hero_l20_extra_state.x,*(float *)(p+4)-g_hero_l20_extra_state.y);
            angle=FastDiffRots(g_hero_l20_extra_state.yaw,angle);
            if (angle<limit) {
                qcopy(&pos,p);
                pos.f[2]=coll_probe_ground_height_below(&pos,0,0.5f)+0.6f;
                if (!coll_test_point(&pos,0.5f,0,0)) {limit=angle;best=i;}
            }
        }
    }
    if(best==-1) return 0;
    qcopy(&pos,points+best*0x10+0x10);
    pos.f[2]=coll_probe_ground_height_below(&pos,0,0.5f);
    if(g_yeedil_force_minion_spawn || (*(int *)(state+0x182C)!=0 && math_random_int_below(2))) return moby_activate_linked_child_pal(arg0,&pos);
    return yeedil_boss_place_group_member_pal(arg0,&pos);
}
