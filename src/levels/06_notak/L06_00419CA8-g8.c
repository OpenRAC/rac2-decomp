#include "common.h"
typedef unsigned int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
typedef struct {
    char pad0000[0x80];
    float position[4];
    char pad0090[0x8];
    float yaw;
    char pad009C[0x54];
    char motionState[0xA0];
    char pad0190[0x10];
    float targetYaw;
    char pad01A4[0x14];
    int modeTimer;
    char pad01BC[0xA6C];
    int animFlags;
    int animBusy;
    char pad0C30[0x5F0];
    int canInteract;
    char pad1224[0x16];
    unsigned char interactBusy;
    char pad123B[0xD];
    int groundState;
    char pad124C[0xD64];
    float stickY;
    float stickX;
    char pad1FB8[0x2D8];
    char * moby;
    int moveState;
    char pad2298[0x1C];
    unsigned char disabled;
} CrankPlayer;
extern CrankPlayer g_hero_state;
extern float g_player_yaw[];
extern char g_moby_nibble_table[], g_moby_group_flags[];
extern int g_current_map_index MACRO_ADDR;
extern unsigned char g_state_flag_c;
typedef struct { char pad[0x464]; unsigned char collected[0]; } CrankLevelState;
extern CrankLevelState g_level_collected_flags;
typedef struct { float position[4]; float rotation[4]; } CrankCamera;
extern CrankCamera g_hero_l06_position;
extern char g_record_label[];
extern char *g_region_table MACRO_ADDR, *g_target_l06_list[];
extern int g_camera_l06_state_ptr[];
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern float g_hero_spring_distance SDATA(D_L06_001B06E8);
extern char *D_L06_001B290C_sda SDATA(D_L06_001B290C);
extern float FastAddRotations(float,float);
extern float vec_distance_xy(void *,void *);
extern float FastDiffRots(float,float);
extern float mat_fast_helper_a(float,float);
extern float math_fabs(float);
extern int PadPressedWithin(int,int,int);
extern float fast_vec_dist(void *,void *);
extern int hero_l00_set_move_state(int,int);
extern void SetCamera5Pose(void *,void *,int,int,int);
extern void cam_set_state_rotation(void *);
extern void object_copy_vector_to_selected(void *);
extern void object_set_kind_five_settings(float,float);
extern void cam_set_mode_state(int);
extern float ApproachValue(void *,float,float);
extern float fast_subtract_rotations(float,float);
extern void record_add_or_update_entry(void *,int,void *,int,void *);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(void *,void *);
extern int PlayMobySound(int,int,void *);
extern float vec_length_xy(void *);
extern void divide_vector_xyz(void *,void *,float);
extern void euler_to_matrix(void *,void *);
extern void transform_vector(void *,void *,void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastVecDot(void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void set_hero_animation(int,int,float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern float math_spring_float_to_goal(void *,void *,float,float,float,float);
/* EE argument banks preserve this ordering of the two integers and two floats. */
extern void StepAngleTowardTarget(void *angle, float target, int direction, float step);
extern float coll_probe_ground_height_below(void *,int,float);
extern void mem_fast_helper_b(void *,int);
/* Bolt crank interaction, completion tracking and player motion around the crank. */
void UpdateBoltCrank(char *obj)
{
    float matrix[16];
    V input, motion, facing, axis, temp, delta;
    float distance;
    char *ctx=P(obj,0x68);
    float angle, turn, inputLength, targetYaw, heroZ, groundHeight, difference;
    int i, clear;
    unsigned short id;
    unsigned char *save;
    char *nearby;
    int packed;
    if (!ctx) { F(obj,0xF8)=FastAddRotations(F(obj,0xF8),0.10471977f); return; }
    if (g_hero_state.moveState!=0x37 && U(obj,0x20)==3) {
        U(obj,0x20)=1;
        if (g_camera_l06_state_ptr[0]) cam_set_mode_state(4);
        return;
    }
    switch (U(obj,0x20)) {
    case 0:
        F(ctx,0x3C)=F(obj,0x18); U(obj,0x20)=1; break;
    case 1:
        id=*(unsigned short *)(obj+0xB2);
        if (g_level_collected_flags.collected[(short)id]) goto used;
        packed=U(g_moby_nibble_table,((short)id>>1)+(g_current_map_index<<10));
        if ((id&1) ? ((packed>>4)&7) : (packed&7)) {
used:
            U(obj,0x20)=5; F(obj,0x18)-=0.5f; F(ctx,0)=1.0f; break;
        }
        if (vec_distance_xy(obj+0x10,g_hero_state.position)<1.75f && !g_hero_state.interactBusy && !g_hero_state.disabled
            && FastDiffRots(g_hero_state.yaw,mat_fast_helper_a(F(obj,0x10)-g_hero_state.position[0],F(obj,0x14)-g_hero_state.position[1]))<1.5707965f
            && math_fabs(g_hero_state.position[2]-0.3f-F(obj,0x18))<0.2f && g_hero_state.groundState==10
            && g_hero_state.canInteract && PadPressedWithin(0x80,7,0) && (unsigned)I(ctx,0x14)>=31
            && F(obj,0x18)==F(ctx,0x3C) && F(ctx,0)<1.0f) {
            I(ctx,0x14)=0; clear=1; g_hero_spring_distance=0;
            for(i=0,nearby=g_target_l06_list[0]; nearby; nearby=g_target_l06_list[++i]) {
                if(fast_vec_dist(obj+0x10,nearby+0x10)<3.25f) {clear=0;break;}
            }
            if(clear) {
                hero_l00_set_move_state(0x37,1);
                SetCamera5Pose(g_hero_l06_position.position,g_hero_l06_position.rotation,3,0xB4,0);
                cam_set_state_rotation(g_region_table+(I(ctx,0x20)<<7)+0x70);
                object_copy_vector_to_selected(g_region_table+(I(ctx,0x20)<<7)+0x30);
                object_set_kind_five_settings(F(ctx,0x28),F(ctx,0x2C));
                U(obj,0x20)=3; I(ctx,0x24)=0; F(ctx,0x18)=F(ctx,0)*6.2831854820251465f*F(ctx,0x30);
            }
            break;
        }
        if(F(ctx,0)<1.0f) {
            I(ctx,0x14)++;
            ApproachValue(ctx,0.0f,0.016666668f);
            if(F(ctx,0)>0.0f) F(obj,0xF8)=fast_subtract_rotations(F(obj,0xF8),F(ctx,0x30)*0.104719765f);
            F(obj,0x18)+=0.008333334f;
            if(F(obj,0x18)>=F(ctx,0x3C)) F(obj,0x18)=F(ctx,0x3C);
        } else if(I(ctx,0x38)) {
            if(I(ctx,0x34)!=-1 && !(U(g_moby_group_flags,U(obj,0xB0)+(D_001A79F0_gp<<4))&0x80)) {
                record_add_or_update_entry(ctx,4,obj,2,g_record_label); moby_mark_table_entry_flagged(U(obj,0xB0));
                if(I(ctx,0x34)!=-1) level_capture_checkpoint_state(g_region_table+(I(ctx,0x34)<<7)+0x30,g_region_table+(I(ctx,0x34)<<7)+0x70);
            }
            F(obj,0x18)-=0.008333334f;
            if(F(obj,0x18)<=F(ctx,0x3C)-0.5f) F(obj,0x18)=F(ctx,0x3C)-0.5f;
        }
        break;
    case 3:
        temp.q=0; temp.f[2]=g_hero_l06_position.rotation[2]; axis.q=temp.q;
        angle=mat_fast_helper_a(g_hero_state.position[0]-F(obj,0x10),g_hero_state.position[1]-F(obj,0x14));
        if((PadPressedWithin(0x80,7,0) && g_hero_state.modeTimer>=61) || F(ctx,0)==1.0f) {
            hero_l00_set_move_state(0,1);
            if(I(ctx,0x38)) {U(obj,0x20)=1;}
            else
            if(F(ctx,0)==1.0f) {
                record_add_or_update_entry(ctx,4,obj,2,g_record_label); U(obj,0x20)=4;
                id=*(unsigned short *)(obj+0xB2);
                if(id&1) {
                    save=(unsigned char *)g_moby_nibble_table+(((short)id>>1)+(g_current_map_index<<10));
                    if(((*save>>4)&7)!=7) *save+=16;
                } else {
                    save=(unsigned char *)g_moby_nibble_table+(((short)id>>1)+(g_current_map_index<<10));
                    if((*save&7)!=7) ++*save;
                }
                PlayMobySound(0,0,obj);
                if(I(ctx,0x34)!=-1 && !(U(g_moby_group_flags,U(obj,0xB0)+(D_001A79F0_gp<<4))&0x80)) {
                    record_add_or_update_entry(ctx,4,obj,2,g_record_label); moby_mark_table_entry_flagged(U(obj,0xB0));
                    if(I(ctx,0x34)!=-1) level_capture_checkpoint_state(D_L06_001B290C_sda+(I(ctx,0x34)<<7)+0x30,D_L06_001B290C_sda+(I(ctx,0x34)<<7)+0x70);
                }
            }
            cam_set_mode_state(3); break;
        }
        input.f[1]=-g_hero_state.stickY; input.f[0]=-g_hero_state.stickX;
        inputLength=vec_length_xy(&input);
        if(inputLength>1.0f) divide_vector_xyz(&input,&input,inputLength);
        euler_to_matrix(matrix,&axis); transform_vector(&input,&input,matrix);
        facing.f[0]=math_fast_sin_or_cos_a(F(g_hero_state.moby,0xF8));
        facing.f[1]=math_fast_sin_or_cos_b(F(g_hero_state.moby,0xF8)); I(&facing,8)=0;
        difference=FastVecDot(&facing,&input)-F(ctx,0x1C);
        if(difference>0.001527777872979641f) difference=0.001527777872979641f;
        if(difference< -0.001527777872979641f) difference= -0.001527777872979641f;
        F(ctx,0x1C)+=difference;
        if(F(ctx,0x1C)>0.06166667118668556f) F(ctx,0x1C)=0.06166667118668556f;
        if(F(ctx,0x1C)<0) F(ctx,0x1C)=0;
        if(math_fabs(F(ctx,0x1C))<0.00038194446824491024f) F(ctx,0x1C)=0;
        vec_scale_to_length(&motion,&facing,F(ctx,0x1C));
        if((g_hero_state.animFlags&2) && U(g_hero_state.moby,0x43)==0x44) set_hero_animation(0x3F,0,7.0f);
        if(U(g_hero_state.moby,0x43)!=0x44 && !g_hero_state.animBusy) {
            if(U(g_hero_state.moby,0x42)==0x40 && math_fabs(F(ctx,0x1C))==0) set_hero_animation(0x3F,0,14.0f);
            else if(U(g_hero_state.moby,0x42)==0x3F) {if(F(ctx,0x1C)>0) set_hero_animation(0x40,0,14.0f);}
            else if(U(g_hero_state.moby,0x42)==0x40 && F(ctx,0x1C)>0.03700000420212746f) set_hero_animation(0x41,0,14.0f);
            else if(U(g_hero_state.moby,0x42)==0x41 && F(ctx,0x1C)<0.024666668847203255f) set_hero_animation(0x40,0,16.0f);
        }
        heroZ=g_hero_state.position[2]; FastVecAdd(g_hero_state.position,g_hero_state.position,&motion);
        turn=mat_fast_helper_a(g_hero_state.position[0]-F(obj,0x10),g_hero_state.position[1]-F(obj,0x14));
        motion.f[0]=math_fast_sin_or_cos_a(turn)*1.05f; motion.f[1]=math_fast_sin_or_cos_b(turn)*1.05f; I(&motion,8)=0;
        FastVecAdd(&temp,obj+0x10,&motion); FastVecSub(&delta,&temp,g_hero_state.position);
        I(&delta,8)=0; distance=-vec_length_xy(&delta);
        math_spring_float_to_goal(&distance,&g_hero_spring_distance,0.0f,0.015f,0.3f,0.116666675f);
        vec_scale_to_length(&delta,&delta,g_hero_spring_distance); FastVecAdd(g_hero_state.position,g_hero_state.position,&delta);
        g_hero_state.position[2]=heroZ;
        if (g_state_flag_c) g_hero_state.targetYaw=FastAddRotations(-1.5707964f,turn);
        else g_hero_state.targetYaw=FastAddRotations(1.5707964f,turn);
        {
        /* The yaw is part of the player state at offset 0x98. */
        float *playerYaw=g_player_yaw;
        CrankPlayer *player=(CrankPlayer *)((char *)playerYaw-0x98);
        StepAngleTowardTarget(playerYaw,player->targetYaw,0,0.10471977f);
        F(ctx,0x24)+=0.0027222223579883575f;
        player->position[2]-=F(ctx,0x24)-2.0f;
        groundHeight=coll_probe_ground_height_below(player->position,0,0.5f);
        player->position[2]-=2.0f;
        if(player->position[2]<groundHeight) {player->position[2]=groundHeight; I(ctx,0x24)=0;}
        if(U(player->moby,0x43)!=0x44) {
            targetYaw=FastAddRotations(0.26179942f,turn);
            StepAngleTowardTarget(obj+0xF8,targetYaw,0,0.052359886f);
            if(fast_subtract_rotations(F(obj,0xF8),targetYaw)>1.0471977f) F(obj,0xF8)=fast_subtract_rotations(F(obj,0xF8),1.0471977f);
            else if(fast_subtract_rotations(F(obj,0xF8),targetYaw)< -1.0471977f) F(obj,0xF8)=FastAddRotations(F(obj,0xF8),1.0471977f);
        }
        F(ctx,0x18)+=FastDiffRots(turn,angle);
        F(ctx,0)=F(ctx,0x18)/(F(ctx,0x30)*6.2831854820251465f);
        if(F(ctx,0)>1) F(ctx,0)=1;
        if(F(ctx,0)<0) F(ctx,0)=0;
        mem_fast_helper_b(g_hero_state.motionState,0xA0);
        }
        break;
    case 4: {
        float bottom;
        F(obj,0x18)-=0.008333334f;
        bottom=F(ctx,0x3C)-0.5f;
        if(F(obj,0x18)<=bottom) {
            F(obj,0x18)=bottom;
            U(obj,0x20)=5;
            F(ctx,0)=1.0f;
        }
        break;
    }
    case 5: F(ctx,0)=1.0f; break;
    }
}
