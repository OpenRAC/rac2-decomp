#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 position,angles,delta; } MovingPathWorkspace;
extern char *D_L16_001FE7C0[];
extern char D_L16_002A4570[];
extern float g_hero_state[];
extern void STUB_printf(const char *,...);
extern void moby_set_state(unsigned char *,int,int);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern float fast_vec_dist(void *,void *);
extern float vec_distance_xy(void *,void *);
extern float math_fabs(float);
extern void mat_combine_and_store(void *,void *,void *,void *);
/* Moves an object along a path of points, waits, then walks back along the path in reverse. */
void path_l16_follower_update(char *object)
{
    MovingPathWorkspace local;
    char *state=*(char **)(object+0x68);
    char *path,*point;
    int index;
    qcopy(&local.position,(object+0x10));
    qcopy(&local.angles,(object+0xf0));
    switch(*(unsigned char *)(object+0x20)) {
    case 0: {
        char *initialPath;
        index=*(int *)(state+0x60);
        initialPath=D_L16_001FE7C0[index];
        qcopy((object+0x10),(initialPath+0x10));
        *(int *)(state+0x6c)=0;
        *(float *)(state+0x68)*=0.016666668f;
        if(index==-1) STUB_printf(D_L16_002A4570,*(short *)(object+0xaa),*(short *)(object+0xb2));
        moby_set_state((unsigned char *)object,1,-1);
        break;
    }
    case 1:
        if(*(unsigned char *)(object+0xbc)!=0) moby_set_state((unsigned char *)object,2,-1);
        break;
    case 2:
        path=D_L16_001FE7C0[*(int *)(state+0x60)];
        point=path+0x20+*(int *)(state+0x6c)*0x10;
        FastVecSub(&local.delta,point,object+0x10);
        vec_scale_to_length(&local.delta,&local.delta,*(float *)(state+0x68));
        FastVecAdd(object+0x10,object+0x10,&local.delta);
        if(fast_vec_dist(object+0x10,path+0x20+*(int *)(state+0x6c)*0x10)<=*(float *)(state+0x68)*0.88f) (*(int *)(state+0x6c))++;
        if(*(int *)(state+0x6c)>=*(int *)path-1) moby_set_state((unsigned char *)object,3,-1);
        break;
    case 3:
        if(*(int *)(state+0x64)<=*(unsigned short *)(object+0x96)) moby_set_state((unsigned char *)object,4,-1);
        break;
    case 4:
        path=D_L16_001FE7C0[*(int *)(state+0x60)];

        if(g_hero_state[34]<*(float *)(object+0x18)) {
            if(vec_distance_xy(object+0x10,g_hero_state+32)<3.0f && math_fabs(*(float *)(object+0x18)-g_hero_state[34])<2.5f) goto skipMovement;
        }
        {
            FastVecSub(&local.delta,path+*(int *)(state+0x6c)*0x10,object+0x10);
            vec_scale_to_length(&local.delta,&local.delta,*(float *)(state+0x68));
            FastVecAdd(object+0x10,object+0x10,&local.delta);
        }
        skipMovement:
        if(fast_vec_dist(object+0x10,path+*(int *)(state+0x6c)*0x10)<=*(float *)(state+0x68)*0.88f) (*(int *)(state+0x6c))--;
        if(*(int *)(state+0x6c)<=0) {
            object[0xbc]=0;
            moby_set_state((unsigned char *)object,1,-1);
        }
        break;
    }
    (*(short *)(object+0x96))++;
    FastVecSub(&local.delta,object+0x10,&local.position);
    mat_combine_and_store(state+0x20,&local.delta,&local.angles,object+0xf0);
}
