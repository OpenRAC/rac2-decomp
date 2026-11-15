/* func_PAL_L00_00386990, the PAL copy of func_L00_00383B90 (src/levels/shared/L00_0037E898-goal-g8.c):
 * the same C, where the step 0.13333334f becomes 0.16000001f, the angle -0.052359886f becomes
 * -0.062831864f, the score timer 240 becomes 200, the PAL callees take their func_PAL_ names, and both
 * timer limits are scaled for 50 Hz. Built with -O2 -G8 -ffunction-sections.
 *
 * The timer blocks: timer holds the scaled limit by the time of the test. That reassignment, and the
 * initial value that makes timer outlive the block for cse, keep the copy into old alive until
 * local-alloc ties the two, so the copy leaves no instruction and timer is allocated first.
 */
#include "common.h"
typedef struct { float x,y,z,w; } ControllerVector;
typedef struct { ControllerVector rows[4]; } __attribute__((aligned(16))) ControllerMatrix;
typedef struct {
    ControllerVector goals[2];
    unsigned char gap20[0x28];
    char *targets[2];
    unsigned char gap50[0x10];
    int scores[2];
} ControllerOwnerState;
typedef struct {
    ControllerVector position;
    unsigned char gap10[0x220];
    ControllerMatrix basis;
} ControllerCamera;
typedef struct { unsigned char prefix[0x18]; char *object; } ControllerContact;
extern int D_L00_001A8F00;
extern int D_L00_001A8F00_gp SDATA(D_L00_001A8F00);
extern int D_L00_001AEDD0[] __attribute__((sda));
extern int D_L00_001AEDD0_gp[2] SDATA(D_L00_001AEDD0);
extern int D_L00_001AED30 __attribute__((sda)),D_L00_001AED34 __attribute__((sda));
extern float D_L00_001AED64 __attribute__((sda));
extern int D_L00_001B1BE8 MACRO_ADDR;
extern float D_L00_001B18E4,D_L00_001B18E0;
extern int D_00138324 NOT_SDA,D_001386A4 NOT_SDA;
extern char *D_L00_001AC0C0;
extern char D_L00_001A8F20[] MACRO_ADDR;
extern ControllerContact g_collision_result;
extern ControllerCamera g_camera_l00_position;
extern int request_begin_slot(int,int,int,int,unsigned char *);
extern int request_end_slot(int,int);
extern int sheep_board_create_objects(char *);
extern void set_identity_rotation_rows(void *),moby_set_state(void *,int,int);
extern void DrawThreeObjectCounters(void *);
extern void gfx_add_draw_callback_first(void (*)(void *),void *);
extern float ApproachValue(float *,float,float),math_step_int_toward_target(int *,int,int);
extern void func_PAL_L00_00387088(void *),func_PAL_L00_003874B8(void *);
/* The retail caller passes the object even though the current callee body does not use it. */
extern void sheep_board_update_same_class(void *),part_l00_spawn_random_burst(void *),sheep_board_destroy_objects(void *);
extern void func_PAL_L00_00387C58(unsigned char *,void *);
extern int coll_process_hit(void *,float,int,char *,void *);
extern void FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *);
extern void vec_transform_by_object_or_given(void *,void *,void *,void *);
extern void part_queue_impact_effect(char *,int,int,void *,void *,float);
extern void moby_mark_spawned(void *),func_002A0F48(void *);
extern void func_PAL_L00_00388038(void *,void *);
extern int PlayMobySound(int,int,void *);
extern float FastAddRotations(float,float),math_fabs(float);
extern void matrix_from_basis_rows(void *,void *),matrix_mul_vec3(void *,void *,void *);

/* Update the two-player goal controller and its moving scoring objects. */
void func_PAL_L00_00386990(unsigned char *object)
{
    struct { ControllerVector local; ControllerMatrix inverse; } workspace;
    ControllerOwnerState *owner;
    char *position;
    int index;
    int phase=object[0x20];
    switch (phase) {
    case 0:
        {
            int mode=D_L00_001A8F00_gp;
            if (D_L00_001A8F00==0) {
                D_L00_001AEDD0_gp[0]=0;
                D_L00_001AEDD0[1]=0;
                request_begin_slot(7,1,(int)object,3,0);
                mode=D_L00_001A8F00;
            }
            if (mode==7 && sheep_board_create_objects((char *)object)) {
                set_identity_rotation_rows(&g_camera_l00_position.basis);
                moby_set_state(object,1,-1);
            } else {
                unsigned int timer=*(unsigned short *)(object+0x96);
                unsigned int old=timer++;
                *(unsigned short *)(object+0x96)=timer;
                if (old>=6) moby_mark_spawned(object);
            }
        }
        break;
    case 1:
        {
            float zero=0.0f;
            float step;
            D_L00_001B1BE8=phase;
            gfx_add_draw_callback_first(DrawThreeObjectCounters,object);
            step=0.16000001f;
            ApproachValue(&D_L00_001B18E4,zero,step);
            ApproachValue(&D_L00_001B18E0,zero,step);
            func_PAL_L00_00387088(object);
            func_PAL_L00_003874B8(object);
            sheep_board_update_same_class(object);
            part_l00_spawn_random_burst(object);
            if (D_L00_001A8F00!=7) {
                sheep_board_destroy_objects(object);
                goto destroy;
            }
            if ((D_00138324&0x810) || (D_001386A4&0x810) ||
                (D_L00_001AEDD0_gp[0] && D_L00_001AEDD0[1]))
                request_end_slot(0,0);
        }
        break;
    case 2:
        {
            int timer=0;
            position=(char *)object+0x10;
            FastVecAdd(position,position,*(void **)(object+0x68));
            func_PAL_L00_00387C58(object,position);
            if (coll_process_hit(position,0.01f,0,*(char **)(object+0xB8),0) &&
                g_collision_result.object) {
                FastVecSub(&workspace.local,position,g_collision_result.object+0x10);
                vec_transform_by_object_or_given(g_collision_result.object,&workspace.local,&workspace.local,0);
                if (workspace.local.z>=0.0f && workspace.local.z<=D_L00_001AED64) {
                    part_queue_impact_effect(g_collision_result.object,(int)object,0x10000,position,D_L00_001A8F20,1.0f);
                    {
                        ControllerOwnerState *state=*(ControllerOwnerState **)(D_L00_001AC0C0+0x68);
                        state->scores[object[0xBC]]+=10;
                    }
                    moby_mark_spawned(object);
                    break;
                }
            }
            if (D_L00_001A8F00==7) {
                int limit=D_L00_001AED30;
                int old;
                timer=*(unsigned short *)(object+0x96);
                *(unsigned short *)(object+0x96)=timer+1;
                old=timer;
                timer=((s32)(limit) * 5 + 2) / 6;
                if (timer<old)
                    moby_mark_spawned(object);
            } else {
destroy:
                moby_mark_spawned(object);
            }
        }
        break;
    case 3:
        {
            int timer=0;
            char *motion=*(char **)(object+0x68);
            char *vector=(char *)object+0x10;
            char *goal;
            owner=*(ControllerOwnerState **)(D_L00_001AC0C0+0x68);
            *(float *)(object+0xF0)=FastAddRotations(*(float *)(object+0xF0),-0.062831864f);
            FastVecAdd(vector,vector,motion);
            matrix_from_basis_rows(&workspace.inverse,&g_camera_l00_position.basis);
            FastVecSub(&workspace.local,vector,&g_camera_l00_position.position);
            matrix_mul_vec3(&workspace.local,&workspace.local,&workspace.inverse);
            if (math_fabs(workspace.local.y-0.5f)<0.02f) {
                for (index=0,goal=(char *)owner+0x8;index<2;index++) {
                    if (math_fabs((workspace.local.z-*(float *)goal)-0.045f)<0.05f) {
                        func_PAL_L00_00388038(object,(char *)object+0x10);
                        D_L00_001AEDD0_gp[index]=200;
                        PlayMobySound(2,0,owner->targets[index]);
                        math_step_int_toward_target(&owner->scores[index],0,100);
                        goto destroy;
                    }
                    goal+=0x10;
                }
            }
            func_002A0F48(object);
            if (D_L00_001A8F00==7) {
                int limit=D_L00_001AED34;
                int old;
                timer=*(unsigned short *)(object+0x96);
                *(unsigned short *)(object+0x96)=timer+1;
                old=timer;
                timer=((s32)(limit) * 5 + 2) / 6;
                if (timer>=old || object[0x31]!=0) break;
            }
            moby_mark_spawned(object);
        }
        break;
    }
}
