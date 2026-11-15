#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union {TI128 q;float v[4];} Vector;

/* Measured camera prefix: its position precedes the three-row basis. */
typedef struct {
    float position[4];
    u8 reserved10[0x220];
    float basis[3][4];
} CameraBasisPrefix;
typedef struct NODE NODE;
typedef void (*DrawCallback_r002E6CF0)(void *);
extern unsigned int D_00138324[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern int mode_gp SDATA(D_L00_001A8F00);
extern int D_L00_001B1BE8 MACRO_ADDR;
extern float D_L00_001B18E0;
extern CameraBasisPrefix g_camera_l00_position;
extern float D_L00_001AFA44 __attribute__((sda));
extern int D_L00_001AFA4C __attribute__((sda));
extern void moby_set_state(unsigned char *,unsigned char,int),moby_mark_spawned(void *);
extern int request_begin_slot(int,int,int,int,unsigned char *),request_end_slot(int,int);
extern int InitializePairedObjects(void *);
extern void UpdatePairedObjects(void *),moby_update_same_class(void *),part_spawn_camera_sparkles(void *),pair_game_spawn_background_particles(void *);
extern void pair_game_draw_scores(void *),gfx_add_draw_callback_first(DrawCallback_r002E6CF0,void *),pair_game_destroy_objects(NODE *);
extern float ApproachValue(float *,float,float);
extern void euler_rotation_basis(float *,float *),matrix_from_basis_rows(void *,void *),FastVecSub(void *,void *,void *),matrix_mul_vec3(void *,void *,void *);
extern void pair_game_wrap_coordinates(float *,float *),pair_game_apply_centre_pull(float,float,float,float *,float *),FastVecAdd(void *,void *,void *),vec_scale_to_length(void *,void *,float);
extern void part_spawn_two_colored_sparkles(unsigned char *,void *);
extern int coll_sweep_from_object(void *,float *,float,int,float,float,int,int,int);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
/* Runs the two-ship minigame object and its shots. It starts the game, updates the scene, and moves each shot until it hits the middle or times out. */
void pair_game_update(unsigned char *object)
{
    Vector point;
    /* 00283698 reads three source rows and writes all four destination rows. */
    float inverse[4][4];
    Vector velocity,spawn,offset;
    char *context=*(char **)(object+0x68);
    int mode;
    switch(object[0x20]) { case 0: {
        if(!D_L00_001A8F00) {request_begin_slot(7,1,(int)object,2,0);return;}
        if(D_L00_001A8F00==7 && InitializePairedObjects(object)) {
            point.q=0;point.v[1]=1.5707964f;
            euler_rotation_basis(g_camera_l00_position.basis,point.v);
            moby_set_state(object,1,-1);return;
        }
        { unsigned timer=U(object,0x96),old=timer++;
          U(object,0x96)=timer; if(old<6)return; }
        moby_mark_spawned(object);return;
    break; } case 1: {
        D_L00_001B1BE8=1;
        UpdatePairedObjects(object);
        moby_update_same_class(object);
        part_spawn_camera_sparkles(object);
        pair_game_spawn_background_particles(object);
        gfx_add_draw_callback_first(pair_game_draw_scores,object);
        if(I(context,0x60) && I(context,0x64)++>=91) {
            ApproachValue(&D_L00_001B18E0,1.0f,0.06666667f);
            mode=mode_gp;
            if(D_L00_001B18E0>=1.0f) {
                pair_game_destroy_objects((NODE *)object);
                InitializePairedObjects(object);
                I(context,0x64)=0; I(context,0x60)=0;
                mode=D_L00_001A8F00;
            }
        } else {
            ApproachValue(&D_L00_001B18E0,0.0f,0.06666667f);
            mode=D_L00_001A8F00;
        }
        if(mode!=7) {
            pair_game_destroy_objects((NODE *)object);
            moby_mark_spawned(object);return;
        } else {
            if(!(D_00138324[0]&0x10))return;
            request_end_slot(1,0);return;
        }
    break; } case 2: {
        matrix_from_basis_rows(inverse,g_camera_l00_position.basis);
        FastVecSub(&point,object+0x10,g_camera_l00_position.position);
        matrix_mul_vec3(&point,&point,inverse);
        matrix_mul_vec3(&velocity,context,inverse);
        pair_game_wrap_coordinates(point.v+1,point.v+2);
        pair_game_apply_centre_pull(point.v[1],point.v[2],D_L00_001AFA44*0.00027777778f,velocity.v+1,velocity.v+2);
        velocity.v[0]=0.0f;
        FastVecAdd(&point,&point,&velocity);
        matrix_mul_vec3(object+0x10,&point,g_camera_l00_position.basis);
        FastVecAdd(object+0x10,object+0x10,g_camera_l00_position.position);
        matrix_mul_vec3(context,&velocity,g_camera_l00_position.basis);
        if(point.v[1]*point.v[1]+point.v[2]*point.v[2]<0.09f) {moby_mark_spawned(object);return;} else {
            part_spawn_two_colored_sparkles(object,object+0x10);
            vec_scale_to_length(&offset,g_camera_l00_position.basis,-0.1f);
            FastVecAdd(&spawn,object+0x10,&offset);
            coll_sweep_from_object(*(void **)(object+0xB8),spawn.v,0.1f,0x10000,1.0f,1.0f,0,1,0);
            FastVecSub(&spawn,object+0x10,&offset);
            coll_sweep_from_object(*(void **)(object+0xB8),spawn.v,0.1f,0x10000,1.0f,1.0f,0,1,0);
            FastVecSub(&spawn,object+0x10,&offset);
            coll_sweep_from_object(*(void **)(object+0xB8),spawn.v,0.1f,0x10000,1.0f,1.0f,0,1,0);
            if(D_L00_001A8F00==7) {int limit=D_L00_001AFA4C; unsigned timer=U(object,0x96),old=timer++;
              U(object,0x96)=timer; if((int)old<=limit)return;}
        }
    }
    break; default: return; }
    moby_mark_spawned(object);
}
