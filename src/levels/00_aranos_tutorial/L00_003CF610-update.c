#include "common.h"
typedef unsigned int UpdateBits __attribute__((mode(TI)));
#define D_00189EA0 (D_00189E20+0x80)
#define D_00189EB0 (D_00189E20+0x90)
extern unsigned char D_001395B8;
extern char g_hero_state[];
extern unsigned char D_0019B2E8[];
extern int g_current_map_index __attribute__((sda));
extern int D_L00_001A8F00 __attribute__((sda));
extern char *D_L00_001B1F8C __attribute__((sda));
extern int D_L00_001FA920[];
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void euler_rotation_basis(void *,void *);
extern void euler_to_matrix(void *,void *);
extern float FastAddRotations(float,float);
extern float FastDiffRots(float,float);
extern void moby_mark_table_entry_flagged(int);
extern void moby_set_state(void *,int,int);
extern int moby_count_group_not_in_state(int,int);
extern void StepAngleTowardTarget(void *,int,float,float);
extern int flag_set_first_pending(void *);
extern void level_capture_checkpoint_state(void *,void *);
extern int PlayMobySound(int,int,void *);
extern void hero_reset_position_and_direction(void *,void *,int,int);
extern void hero_start_target_state(void *,int,float);
extern void moby_set_flag_bit(void *,int);
extern void cam_lock_entry(int);
extern int cam_is_trigger_ready(int);

/* Turns the object by a set angle when triggered, with a sound and an optional camera cut, then settles at the final angle. */
void triggered_turn_update(unsigned char *obj) {
    union { UpdateBits q; float f[4]; } first,second;
    int *ctx=*(int **)(obj+0x68);
    if(!ctx) return;
    if((unsigned char)obj[0x20]==0) {
        if(D_L00_001FA920[ctx[0]]==0) {
            if(ctx[2]) { obj[0x20]=3; return; }
            if(!ctx[5]) { obj[0x20]=2; return; }
            *(float *)(ctx+6)=*(float *)(obj+0xF4);
            *(float *)(obj+0xF4)=FastAddRotations(*(float *)(obj+0xF4),-1.5707965f);
            moby_set_state(obj,4,-1);
            return;
        }
        if(moby_count_group_not_in_state(ctx[0],-1)==0) {
            if((D_0019B2E8[(unsigned char)obj[0xB0]+g_current_map_index*16]&0x80)==0) {
                obj[0x20]=1;
                if(!ctx[2]) return;
                D_001395B8=1;
                cam_lock_entry(ctx[4]);
                moby_mark_table_entry_flagged((unsigned char)obj[0xB0]);
                first.q=*(UpdateBits *)(D_L00_001B1F8C+ctx[3]*128+0x30);
                second.q=*(UpdateBits *)(D_L00_001B1F8C+ctx[3]*128+0x70);
                level_capture_checkpoint_state(&first,&second);
                return;
            }
            obj[0x20]=3;
        } else if(D_0019B2E8[(unsigned char)obj[0xB0]+g_current_map_index*16]&0x80) obj[0x20]=3;
    }
    if((unsigned char)obj[0x20]==1) {
        if(ctx[4]) {
            if(cam_is_trigger_ready(ctx[4])) {
                char *bank=D_L00_001B1F8C+ctx[3]*128;
                qcopy_nc(g_hero_position,bank+0x30);
                qcopy_nc(D_00189EB0,bank+0x70);
                obj[0x20]=3;
                moby_set_flag_bit(obj,1);
            }
        }
    }
    if((unsigned char)obj[0x20]==3) {
        if(*(float *)(ctx+1)==0.0f) PlayMobySound(0,0,obj);
        *(float *)(obj+0xF4)+=-0.017453294f;
        euler_rotation_basis(obj+0xC0,obj+0xF0);
        *(float *)(ctx+1)+=1.0f;
        if(*(float *)(ctx+1)>135.0f) { PlayMobySound(1,0,obj); obj[0x20]=2; }
    }
    if((unsigned char)obj[0x20]!=4) return;
    if(D_L00_001A8F00) return;
    if(flag_set_first_pending(obj)) {
        PlayMobySound(1,0,obj);
        qcopy(&second,g_hero_position);
        euler_to_matrix(g_hero_state,D_00189EB0);
        vec_scale_to_length(&first,g_hero_state,-2.5f);
        FastVecAdd(&first,&second,&first);
        hero_reset_position_and_direction(&first,D_00189EB0,0,1);
        hero_start_target_state(&second,1,*(float *)(D_00189EB0+8));
    }
    StepAngleTowardTarget(obj+0xF4,0,*(float *)(ctx+6),0.02617994323372841f);
    if(FastDiffRots(*(float *)(obj+0xF4),*(float *)(ctx+6))<0.001f) obj[0x20]=2;
}
