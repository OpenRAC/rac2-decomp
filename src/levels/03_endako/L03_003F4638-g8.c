/* The 15-state per-frame update of one Endako entity. -G8 for its small data;
 * -g (config/cflags.txt) gives the two nops retail has before state 12's div.s.
 *
 * func_002AA800 returns the angle still left, the result of its last call to
 * func_002AA738, as RAC1's ApproachValue returns the distance left. No caller
 * here reads it, but the call still defines $f0: that is why state 14's copy
 * right after it takes $f1.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define S(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define Q(p,o) (*(Quad *)((u8 *)(p)+(o)))
extern u8 D_L03_00189EA0[], D_L03_001BFB80[], D_L03_001B9980[];
typedef struct {u8 pad[0x80]; float position[4];} HeroState;
extern HeroState D_L03_00189E20;
extern u8 D_001395C2[2] NOT_SDA;
extern u8 *D_L03_001FE700[], *D_L03_001B2A1C;
extern u8 D_L03_00188660[];
extern int D_L03_001B104C __attribute__((sda)), D_L03_001B106C __attribute__((sda)), D_L03_001A8F00 __attribute__((sda));
extern float D_L03_001B1054 __attribute__((sda)), D_L03_001B103C __attribute__((sda)), D_L03_001B1068 __attribute__((sda));
extern int D_L03_001B1044 __attribute__((sda)), D_L03_001B1040 __attribute__((sda));
extern float D_L03_001B1030[3] SDATA(D_L03_001B1030);
extern float D_L03_001B105C __attribute__((sda));
extern int g_frame_l03_counter;
extern void endako_boss_update_damage(void *);
extern int IsPointInCuboid(void *, int);
extern void moby_set_state(void *, int, int);
extern float mat_fast_helper_a(float,float);
extern int req_push_queue(void *,int);
extern s32 req_launch_queued(void *);
extern void moby_set_flag_bit(void *,int);
extern void script_queue_keyed_request(int,int);
extern int flag_set_first_pending(void *);
extern void anim_start_blended(void *,int,int,int);
extern void endako_boss_pick_pose(void *,int);
extern int math_fast_float_d(void *);
extern void boss_choose_next_behaviour(void *);
extern float math_fabs(float);
extern f32 ApproachValue(void *,float,float);
extern float math_random_signed_float_range(float,float);
extern void moby_transform_joint_point(void *,int,void *);
extern void transform_vector(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern int PlayMobySound(int,int,void *);
extern u8 *spark_shot_spawn(void *,void *,void *,int);
extern void endako_boss_add_target(void *,int);
extern int math_random_int_range(int,int);
extern int math_is_value_within_step(void *,float);
extern void moby_transform_joint_to_world(void *,int,void *);
extern u8 *object_spawn_and_init(void *,void *,void *,void *,int,float,float,int,int,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern char *part_create_interpolated_emitter(void *,int,void *,void *,void *,int,int,int);
extern float math_random_float_range(float,float);
extern char *SpawnExplosion(void *,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern float StepAngleTowardTarget(void *,int,float,float);
extern char *part_spawn_blast_effect_moby(void *,void *,void *,float);
extern float FastAddRotations(float,float);
extern float IntToFloat(int);
extern void SetDeathBits(void *,int,int);
extern void cam_end_override(int);
extern void moby_mark_spawned(void *);
extern void moby_mark_table_entry_flagged(int);
extern void snd_stop_voice(int);
extern void endako_boss_update_helpers(void *);

typedef struct {
    u8 pad[0x80];
    int paths[3], activation[2], trigger, ready[2];
    u8 padA0[0x2A0-0xA0];
    float angles[4];
    u8 pad2B0[0x2E8-0x2B0];
    float blend[4], target[2];
} AttackState;

/* Runs one frame of the Endako boss: waits for the hero, flies along its paths, picks
 * attacks (fire shots, throw bombs, spin up) and plays its death. */
void endako_boss_update(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68);
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[16] __attribute__((aligned(16)));
    int i;
    endako_boss_update_damage(moby);
    switch(moby[0x20]) {
    case 1:
        if (IsPointInCuboid(D_L03_00189EA0,((AttackState *)vars)->activation[I(vars,0x2D4)])) {
            u8 *p;
            moby_set_state(moby,2,-1);
            H(moby,0x34)=(H(moby,0x34)&0xFFBE)|0x1000;
            I(moby,0x98)=I(*(u8 **)(moby+0x24),0x10);
            p=D_L03_001FE700[((AttackState *)vars)->paths[I(vars,0x2D4)]];
            I(vars,0x2D8)=0; *(u8 **)(vars+0x2CC)=p; I(vars,0x2DC)=0;
            qcopy(vars+0x290,p+0x10);
            F(vars,0x298)-=7.0f;
            qcopy(moby+0x10,vars+0x290); qzero(vars+0x2A0);
            F(vars,0x2A8)=mat_fast_helper_a(D_L03_00189E20.position[0]-F(moby,0x10),D_L03_00189E20.position[1]-F(moby,0x14));
            F(vars,0x2D0)=0.16666667f;
        }
        if(IsPointInCuboid(D_L03_00189EA0,I(vars,0x94))) moby_set_state(moby,4,-1);
        break;
    case 2:
        if(IsPointInCuboid(D_L03_00189EA0,((AttackState *)vars)->ready[I(vars,0x2D4)])) {
            D_001395C2[0]=1; moby_set_state(moby,3,-1);
            I(vars,0x2DC)=I(*(u8 **)(vars+0x2CC),0)-1;
        }
        break;
    case 3:
        if(I(vars,0x2D8)==I(vars,0x2DC)) {
            if(I(vars,0x2D4)==0) {
                I(moby,0x98)=0; H(moby,0x34)=(H(moby,0x34)|0x41)&0xEFFF;
                moby_set_state(moby,1,-1); I(vars,0x2D4)++;
            } else {
                I(moby,0x98)=0; H(moby,0x34)=(H(moby,0x34)|0x41)&0xEFFF;
                moby_set_state(moby,4,-1);
            }
        }
        break;
    case 4:
        if(D_L03_001B104C && IsPointInCuboid(D_L03_00189EA0,I(vars,0x94))) {
            if(D_L03_001B106C) moby_set_state(moby,5,-1);
            else if(req_push_queue(D_L03_001BFB80,0x36)) {
                D_L03_001B106C=1;req_launch_queued(D_L03_001BFB80);moby_set_state(moby,5,-1);
            }
        }
        break;
    case 5:
        if(H(moby,0x96)>=21 && D_L03_001A8F00!=2) {
            u8 *p;
            moby_set_state(moby,6,2);
            H(moby,0x34)=(H(moby,0x34)&0xFFBE)|0x1000;
            I(moby,0x98)=I(*(u8 **)(moby+0x24),0x10);
            p=D_L03_001FE700[I(vars,0x88)];
            I(vars,0x2DC)=I(vars,0x320); *(u8 **)(vars+0x2CC)=p; I(vars,0x2D8)=I(vars,0x320);
            qcopy(vars+0x290,p+I(vars,0x320)*16+0x10); qcopy(moby+0x10,vars+0x290);
            F(vars,0x2A8)=mat_fast_helper_a(D_L03_00189E20.position[0]-F(moby,0x10),D_L03_00189E20.position[1]-F(moby,0x14));
            F(moby,0xF8)=F(vars,0x2A8);
            {u8 *linked=D_L03_001B2A1C+(I(vars,0xA8)<<8);
            F(vars,0x2D0)=0.16666667f; I(vars,0x2E0)=60; F(vars,0x298)-=7.0f;
            moby_set_flag_bit(linked,0);}
            script_queue_keyed_request(I(vars,0xB0),-1);
        }
        break;
    case 6:
        if(flag_set_first_pending(moby)) {
            if(moby[0x43]!=0) anim_start_blended(moby,0,0,5);
            if(moby[0x94]!=4) endako_boss_pick_pose(moby,moby[0x94]!=8);
        }
        if(I(vars,0x2D8)==I(vars,0x2DC) && math_fast_float_d(vars+0x2E0)) boss_choose_next_behaviour(moby);
        break;
    case 7: {
        int done=1;
        F(vars,0x178)=F(vars,0x2F8); F(vars,0x1F8)=F(vars,0x2FC);
        if(math_fabs(F(vars,0x158)-F(vars,0x2F8))>0.01f) done=0;
        else if(math_fabs(F(vars,0x1D8)-F(vars,0x2FC))>0.01f) done=0;
        if(done) {
            if(F(vars,0x2F8)!=0 && F(vars,0x2FC)!=0) {if(moby[0x43]!=3) anim_start_blended(moby,3,0,5);}
            else if(F(vars,0x2F8)!=0) {if(moby[0x43]!=1) anim_start_blended(moby,1,0,5);}
            else {if(moby[0x43]!=2) anim_start_blended(moby,2,0,5);}
            moby_set_state(moby,8,-1);
            {float first=((AttackState *)vars)->target[0],second=((AttackState *)vars)->target[1];
            ((AttackState *)vars)->blend[2]=(((AttackState *)vars)->blend[0]=first,((AttackState *)vars)->blend[1]=second,((AttackState *)vars)->blend[3]=0.0f);}
        }
        break;
    }
    case 8: {
        int done=1,n;
        for(i=0;i<2;i++) {
            if(((AttackState *)vars)->target[i]!=0) {
                ApproachValue(&((AttackState *)vars)->blend[i],-((AttackState *)vars)->target[i],D_L03_001B1054*0.0002908882452175021f);
                F(vars,0x178+i*0x80)=((AttackState *)vars)->blend[i];
                if(math_fabs(((AttackState *)vars)->blend[i]+((AttackState *)vars)->target[i])>0.01f) done=0;
                if(((g_frame_l03_counter+i*4)&7)==0) {
                    Q(b,0)=0; b[1]=math_random_signed_float_range(0,0.1f);b[2]=math_random_signed_float_range(0,0.1f);b[3]=1;
                    Q(a,0)=Q(b,0);moby_transform_joint_point(moby,i+2,c);transform_vector(a,a,c);
                    vec_scale_to_length(b,c,D_L03_001B103C*0.016666668f);
                    PlayMobySound(3,0,moby);n=spark_shot_spawn(moby,a,b,vars[0x34]);endako_boss_add_target(moby,n);
                }
            }
        }
        if(done) {F(vars,0x2F8)=F(vars,0x2FC)=0;moby_set_state(moby,6,2);}
        break;
    }
    case 9: break;
    case 10:
        if(flag_set_first_pending(moby)) {
            switch(S(vars,0x3C2)) {
            case 3: I(vars,0x33C)=math_random_int_range(4,6); break;
            case 2: I(vars,0x33C)=math_random_int_range(3,5); break;
            case 1: default: I(vars,0x33C)=math_random_int_range(2,3); break;
            }
            if(moby[0x43]!=4) anim_start_blended(moby,4,0,5);
        }
        if(moby[0x60]&2) moby_set_state(moby,11,-1);
        break;
    case 11: {
        int n;
        if(flag_set_first_pending(moby) && moby[0x43]!=6) anim_start_blended(moby,6,0,5);
        if(math_is_value_within_step(moby,2.0f)) {
            moby_transform_joint_to_world(moby,4,a);qcopy(b,moby+0xC0);b[2]=0;
            vec_scale_to_length(b,b,D_L03_001B1068*0.016666668f);
            n=vars[0x36];PlayMobySound(4,0,moby);
            object_spawn_and_init(moby,a,b,b,30,(float)n,(float)n,80,1,1.0f);
        }
        if((moby[0x60]&2) && math_fast_float_d(vars+0x33C)) moby_set_state(moby,6,2);
        break;
    }
    case 12: {
        int n;
        if(math_fast_float_d(vars+0x2E4)) {moby_set_state(moby,6,2);break;}
        if(H(moby,0x96) && H(moby,0x96)%D_L03_001B1044==0) {
            moby_transform_joint_to_world(moby,I(vars,0x330)>0?6:5,a);
            {float limit=D_L03_001B105C, height, side, lateral;
            n=D_L03_001B1040; I(vars,0x330)=-I(vars,0x330);
            height=limit-a[2];
            Q(c,0)=0; c[0]=0.016666668f;
            side=(float)I(vars,0x330)*0.016666668f;
            lateral=D_L03_001B1030[S(vars,0x3C2)-1]*side;
            c[2]=2*height/(float)n; c[1]=lateral;}
            Q(b,0)=Q(c,0);matrix_mul_vec3(b,b,moby+0xC0);
            FastVecScale(c,b,(float)(n>>1));FastVecAdd(c,c,a);FastVecSub(c,vars+0x50,c);c[2]=0;
            vec_scale_to_length(c,c,D_L03_001B1030[S(vars,0x3C2)-1]*0.016666668f);
            part_create_interpolated_emitter(moby,0,a,b,c,n,300,vars[0x35]);
        }
        break;
    }
    case 13:
        if(flag_set_first_pending(moby) && moby[0x43]!=8) anim_start_blended(moby,8,0,5);
        if(moby[0x60]&2) {moby_set_state(moby,10,4);endako_boss_pick_pose(moby,1);I(vars,0x2D0)=0;}
        break;
    case 14:
        if(flag_set_first_pending(moby)) {if(moby[0x43]!=8)anim_start_blended(moby,8,0,5);}
        else if(moby[0x43]!=0)anim_start_blended(moby,0,0,5);
        if(H(moby,0x96)%45==0) {
            Q(b,0)=0;b[0]=math_random_float_range(-2,2);b[1]=math_random_float_range(-4,4);b[2]=math_random_float_range(-1,3);
            Q(a,0)=Q(b,0);matrix_mul_vec3(a,a,moby+0xC0);FastVecAdd(a,a,moby+0x10);PlayMobySound(2,0,moby);
            SpawnExplosion(a,0,25,20,20,20,45,1,0,0,0,0,1,20);
        }
        StepAngleTowardTarget(vars+0x2A0,0,0.26179942f,0.0014544413425028324f);
        ((AttackState *)vars)->angles[1]=((AttackState *)vars)->angles[0];I(vars,0x2DC)=I(vars,0x2D8);
        if(H(moby,0x96)>=180) {
            FastVecSub(a,D_L03_001B9980,moby+0x10);vec_scale_to_length(a,a,1);part_spawn_blast_effect_moby(moby,moby+0x10,a,0);
            moby_set_state(moby,15,-1);I(vars,0x2CC)=0;F(vars,0x2D0)=-0.083333336f;
        } else F(vars,0x2C0)=FastAddRotations(F(vars,0x2C0),(float)H(moby,0x96)*0.0024240687489509583f);
        break;
    case 15: {
        int n;
        float x;
        if(H(moby,0x96)%15==0) {
            Q(b,0)=0;b[0]=math_random_float_range(-2,2);b[1]=math_random_float_range(-2,2);b[2]=math_random_float_range(0,3);
            Q(a,0)=Q(b,0);matrix_mul_vec3(a,a,moby+0xC0);FastVecAdd(a,a,moby+0x10);PlayMobySound(2,0,moby);
            SpawnExplosion(a,0,25,20,20,20,45,0,0,0,0,0,1,20);
        }
        StepAngleTowardTarget(vars+0x2A0,0,0.78539824f,0.02617994323372841f);StepAngleTowardTarget(vars+0x2A4,0,1.5707965f,0.02617994323372841f);
        x=IntToFloat(H(moby,0x96));F(vars,0x2D0)-=x*9.259259968530387e-05f;F(vars,0x298)+=F(vars,0x2D0);
        if(!S(vars,0x3C0) && F(vars,0x298)<F(vars,0x2B8)-1) {S(vars,0x3C0)=1;SetDeathBits(moby,0,3);}
        if(F(vars,0x298)<F(vars,0x2B8)-12) {
            cam_end_override(I(vars,0x2C8));moby_set_flag_bit(D_L03_001B2A1C+(I(vars,0xA4)<<8),0);script_queue_keyed_request(I(vars,0xB4),I(vars,0xB8));
            if(I(vars,0x2C4))moby_mark_spawned(*(void **)(vars+0x2C4));
            D_001395C2[1]=1;moby_mark_table_entry_flagged(moby[0xB0]);n=I(vars,0x3CC);
            if(n!=-1) {u8 *sound=D_L03_00188660+n*0x70;if(*(u8 **)(sound+0x88)==moby && sound[0x74])snd_stop_voice(n);}
            I(vars,0x3CC)=-1;moby_mark_spawned(moby);return;
        }
        break;
    }
    }
    endako_boss_update_helpers(moby);
}
