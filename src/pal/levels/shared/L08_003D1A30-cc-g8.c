#include "names.h"
/* func_PAL_L08_003D1A30, the PAL copy of func_L08_003CDB78: the same C, where rename func_002ABBB8 becomes func_PAL_002AC718; rename func_L08_002D2ED8 becomes func_PAL_L08_002D3078; rename func_002A7470 becomes func_PAL_002A7E68; rename func_L00_002D2168 becomes func_PAL_L00_002D2668. */
#include "common.h"
typedef int ContactQuad __attribute__((mode(TI)));
typedef union { ContactQuad q; float f[4]; } ContactVector;
typedef struct { char pad[0x2290]; void *collision; char gap[0x24CC-0x2294]; int contact; } ContactHero;
extern ContactHero g_hero_state;
extern char D_L08_001BFF60[], D_L08_001A8F20[] MACRO_ADDR;
typedef struct { char pad[0x10]; ContactQuad position; char tail[0xE0]; } ContactEntry;
extern ContactEntry *D_L08_001B29DC __attribute__((sda));
extern float D_L08_001AFFF4 __attribute__((sda)), D_L08_001AFFF0 __attribute__((sda));
extern float D_L08_001AFFEC __attribute__((sda));
extern float D_L08_001B0118 __attribute__((sda)), D_L08_001B0120 __attribute__((sda));
extern float D_L08_001B3410 MACRO_ADDR, D_L08_001B3414 MACRO_ADDR;
extern float D_L08_001B2094 MACRO_ADDR, D_L08_001B2098 MACRO_ADDR;
extern int g_current_map_index;
extern void vec_scale_to_length(void *,void *,float),FastVecAdd(void *,void *,void *);
extern int coll_test_point(void *,int,float,void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern int CollLine(void *,void *,int,void *,void *);
extern float fast_vec_dist(void *,void *);
extern void FastVecSub(void *,void *,void *),vec_fast_normalize(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void func_PAL_002AC718(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern int snd_play_from_class_bank(int,int,void *,int),GetCollHitMaterial(void);
extern int func_PAL_L08_002D3078(int,int);
extern void func_PAL_002A7E68(void *,int,int,int),moby_set_state(void *,int,int);
extern void moby_place_at_stored_transform(void *),func_PAL_L00_002D2668(int,int,float);

/* Resolve the movement probes and update the D_L08_001BFF60 response. */
int func_PAL_L08_003D1A30(char *object, void *previous)
{
    ContactVector temporary, point;
    char *state=*(char **)(object+0x68);
    int hit,index,result;
    float whole,part,drop;
    ContactHero *hero=&g_hero_state;

    vec_scale_to_length(&temporary,object+0xC0,D_L08_001AFFF4);
    FastVecAdd(&point,&temporary,object+0x10);
    vec_scale_to_length(&temporary,object+0xE0,D_L08_001AFFF0);
    FastVecAdd(&point,&point,&temporary);
    hit=coll_test_point(&point,0,D_L08_001AFFEC,hero->collision);
    if (!hit) {
        moby_transform_joint_to_world(object,1,&temporary);
        hit=CollLine(&point,&temporary,0x10,hero->collision,0);
        if (!hit) {
            moby_transform_joint_to_world(object,4,&temporary);
            hit=CollLine(&point,&temporary,0x10,hero->collision,0);
            if (!hit) {
                qcopy(&point,previous);
                qcopy(&temporary,state);
                hit=CollLine(previous,state,0x10,hero->collision,0);
            }
        }
        if (hit) {
            whole=fast_vec_dist(&point,&temporary);
            part=fast_vec_dist(&point,D_L08_001BFF60);
            FastVecSub(D_L08_001BFF60+0x10,&point,&temporary);
            vec_scale_to_length(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,whole-part);
            FastVecAdd(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,&point);
        }
    }
    if (hit) {
        func_PAL_002AC718(object,D_L08_001A8F20,D_L08_001BFF60,0.0f,0.0f,3,3,3,0.0f,0.0f,9.0f,0.8f,-1,0.0f,0,3,-1,7,0x810001);
        if (!*(int *)(state+0xB0)) {
            snd_play_from_class_bank(4,0,object,0x988);
            *(int *)(state+0xB0)=12;
        }
        FastVecSub(&point,state,&point);
        FastVecAdd(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,&point);
        if (g_current_map_index!=9 && (result=GetCollHitMaterial())==1) {
            D_L08_001B2094=D_L08_001B3410;
            D_L08_001B2098=D_L08_001B3414;
            *(int *)(state+0x50)=0;
            func_PAL_L08_002D3078(0,1);
            if (*(unsigned char *)(object+0x43)) func_PAL_002A7E68(object,0,0,10);
            index=*(int *)(state+0x6C);
            if (index>0) {
                qcopy(state,&D_L08_001B29DC[index].position);
                moby_place_at_stored_transform(object);
            }
            moby_set_state(object,1,-1);
            g_hero_state.contact=result;
        } else {
            qcopy(state,D_L08_001BFF60+0x10);
            vec_fast_normalize(state+0x20,state+0x20,D_L08_001BFF60+0x20);
            FastVecScale(state+0x20,state+0x20,D_L08_001B0118);
            drop=D_L08_001B0120*0.00040000002f;
            *(float *)(state+0x28)-=drop;
            if (*(unsigned char *)(object+0x20)!=9) {
                if (*(float *)(state+0x28)>0.0f) *(float *)(state+0x28)=-drop;
                func_PAL_L00_002D2668(0x80,0,12.0f);
                moby_set_state(object,9,-1);
            }
            FastVecAdd(object+0x10,object+0x10,state+0x20);
        }
    }
    return hit;
}
