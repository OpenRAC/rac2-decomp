#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define INT(p,o) (*(int *)((char *)(p)+(o)))
#define FLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define HALF(p,o) (*(short *)((char *)(p)+(o)))
#define UHALF(p,o) (*(u16 *)((char *)(p)+(o)))
typedef struct { u8 pad0[0xAA]; s16 oclass; u8 padAC[0xF8 - 0xAC]; float rotz; u8 padFC[0x100 - 0xFC]; } Moby;
extern int g_barlow_state_flags[];
extern int g_current_map_index __attribute__((sda));
extern char *g_moby_l04_pool[] __attribute__((sda));
extern float g_hound_chase_range __attribute__((sda)), g_hound_move_speed __attribute__((sda));
extern void barlow_enemy_update_common(char *);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended(void *,int,int,int);
extern void anim_start_immediate(char *,int,int);
extern int math_fast_float_d(int *);
extern int FastDecTimer(short *);
extern int math_random_int_below(int);
extern int math_random_int_range(int,int);
extern float math_random_float_range(float,float);
extern int FloatToInt(float);
extern unsigned int moby_dispatch_action_by_kind(void *,void *);
extern void SetDeathBits_us2(void *,int,int);
extern void part_queue_moby_for_glow(void *,int,int);
extern float ApproachValue(float *,float,float);
extern void moby_wander_around_home_point(void *,void *,float,float);
extern float mat_fast_helper_a(float,float);
extern float FastAddRotations(float,float);
extern float MobySpringTurn(void *,float,float *,float,float,float);
extern float vec_distance_xy(void *,void *);
extern int math_is_value_within_step_us2(char *,float);
extern int PlayMobySound(int,int,char *);
extern int coll_test_hit_at_bone(float,float,float,void *,int,int,int,int,int);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void add_vectors(void *,void *,void *);
extern int object_pull_toward_hero(char *);
extern void barlow_enemy_update_movement(char *);
extern void enemy_turn_toward_hero(u8 *);
extern void moby_mark_spawned(void *);

/* Per-frame update of the Gadgetron hound: picks its next action, moves it toward the hero and turns it to face them. */
void gadgetron_hound_update_us2(u8 *moby)
{
    char *vars;
    u8 *other;
    union { Quad q; float f[4]; } movement, position;
    unsigned int flags;
    int kind, choice, state;
    float delay;
    if (g_barlow_state_flags[0]) return;
    vars=*(char **)(moby+0x68);
    barlow_enemy_update_common(moby);
    kind=(u8)moby[0x95];
    switch(kind) {
    case 0:
        if(INT(vars,0x328)==-1 || INT(vars,0x32c)==-1 || (other=(u8 *)g_moby_l04_pool[0]+INT(vars,0x32c)*256)==moby ||
            !other || other[0x20]==254 || other[0x20]==253) {
            math_fast_float_d((int *)(vars+0x31c));
            if(INT(vars,0x254)==1) {
                if(INT(vars,0x328)!=-1) {
                    Moby *pool=(Moby *)g_moby_l04_pool[0];
                    UHALF(moby,0x34)&=0xffbe;
                    INT(moby,0x98)=INT(*(char **)(moby+0x24),0x10);
                    if(pool[INT(vars,0x328)].oclass==0x929) {
                        moby_set_state(moby,7,3); anim_start_immediate(moby,7,0);
                        FLOAT(moby,0xf8)=FLOAT(g_moby_l04_pool[0]+INT(vars,0x328)*256,0xf8);
                        INT(vars,0x328)=-1;
                        goto heightCheck;
                    }
                    INT(vars,0x328)=-1;
                    moby_set_state(moby,4,2);
                    if(moby[0x43]!=7) anim_start_blended(moby,7,0,14);
                } else {
                    if(math_random_int_below(9)==0) {
                        if(math_random_int_below(2)!=0) {
                            moby_set_state(moby,3,2);
                            if(moby[0x43]!=3) anim_start_blended(moby,3,0,14);
                            if(math_random_int_below(2)==1 && moby[0x43]!=4) anim_start_blended(moby,4,0,14);
                        } else {
                            moby_set_state(moby,4,2);
                            if(moby[0x43]!=7) anim_start_blended(moby,7,0,14);
                        }
                    }
                }
                UHALF(moby,0x34)&=0xffbe;
                INT(moby,0x98)=INT(*(char **)(moby+0x24),0x10);
            } else if(HALF(vars,0x306)!=0) {
                moby_set_state(moby,2,1);
                HALF(vars,0x306)=0;
                INT(vars,0x2fc)=FloatToInt(math_random_float_range(FLOAT(vars,0x2f8)*0.8f,FLOAT(vars,0x2f8)*1.2f)*60.0f);
                HALF(vars,0x300)=0;
            }
        }

        break;
    case 1:
        if(INT(vars,0x254)==1) {
            moby_set_state(moby,4,2);
            if(moby[0x43]!=7) anim_start_blended(moby,7,0,14);
        } else if(INT(vars,0x2fc)==0) {
            moby_set_state(moby,1,0);
            if(moby[0x43]!=2) anim_start_blended(moby,2,0,12);
        }

        break;
    case 2:
        if(INT(vars,0x254)!=1 && math_random_int_below(19)==0) {
            moby_set_state(moby,2,1);
            INT(vars,0x2fc)=FloatToInt(math_random_float_range(FLOAT(vars,0x2f8)*0.8f,FLOAT(vars,0x2f8)*1.2f)*60.0f);
            HALF(vars,0x300)=0;
        }

        break;
    case 3:
        if(moby[0x20]!=7) {
        flags=moby_dispatch_action_by_kind(moby,vars+0x60);
        if(flags&1) { HALF(vars,0x98)=0; SetDeathBits_us2(moby,0,3); part_queue_moby_for_glow(moby,0,0); return; }
        if(flags&2) {
            if(INT(vars,0x254)==1) {
                moby_set_state(moby,4,2);
                if(moby[0x43]!=7) anim_start_blended(moby,7,0,14);
            } else {
                moby_set_state(moby,2,1);
                INT(vars,0x2fc)=FloatToInt(math_random_float_range(FLOAT(vars,0x2f8)*0.8f,FLOAT(vars,0x2f8)*1.2f)*60.0f);
                HALF(vars,0x300)=math_random_int_range(120,700);
            }
        }

        }
        break;
    }
heightCheck:
    if(FLOAT(moby,0x18)-FLOAT(vars,0x2e8)>10.0f || FLOAT(moby,0x18)<10.0f) {
        HALF(vars,0x98)=0; qzero(moby+0xf0);
        SetDeathBits_us2(moby,0,3); moby_mark_spawned(moby); return;
    }
    if(FLOAT(moby,0x18)<75.0f && g_current_map_index==11) {
        HALF(vars,0x98)=0; qzero(moby+0xf0);
        SetDeathBits_us2(moby,0,3); moby_mark_spawned(moby); return;
    }
    state=(u8)moby[0x20];
    switch(state) {
    case 1:
        FastDecTimer((short *)(vars+0x300));
        if(moby[0x43]==0 && HALF(vars,0x300)) anim_start_blended(moby,7,0,14);
        if (HALF(vars,0x300)>=21)
            ApproachValue((float *)(vars+0x124),g_hound_move_speed*0.01666666753590107f,0.0019444444915279746f);
        else
            ApproachValue((float *)(vars+0x124),0.0f,0.0019444444915279746f);
        if(moby[0x43]==7) {
            FLOAT(moby,0x48)=0.8f;
            if(HALF(vars,0x300)==0) {
                if(moby[0x43]!=math_random_int_below(3)) {
                    choice=math_random_int_below(3)+(0);
                    anim_start_blended(moby,choice,0,12);
                }
            }
            moby_wander_around_home_point(moby,vars+0x110,0.35f,0.25f);
        } else if(((u8)moby[0x43]<=2) && (moby[0x60]&2)) {
            HALF(vars,0x300)=math_random_int_range(120,500);
            if(moby[0x43]!=7) anim_start_blended(moby,7,0,12);
        }
        break;
    case 2:
        FastDecTimer((short *)(vars+0x300));
        if(moby[0x43]==0 && HALF(vars,0x300)) anim_start_blended(moby,7,0,14);
        if (HALF(vars,0x300)>=21)
            ApproachValue((float *)(vars+0x124),g_hound_move_speed*0.01666666753590107f,0.0019444444915279746f);
        else
            ApproachValue((float *)(vars+0x124),0.0f,0.0019444444915279746f);
        if(moby[0x43]==7) {
            FLOAT(moby,0x48)=0.8f;
            if(HALF(vars,0x300)==0) {
                if(moby[0x43]!=math_random_int_below(2)+5) {
                    choice=math_random_int_below(2)+(5);
                    anim_start_blended(moby,choice,0,12);
                }
            }
            moby_wander_around_home_point(moby,vars+0x110,0.35f,0.25f);
        } else if(((u8)(moby[0x43]-5)<2) && (moby[0x60]&2)) {
            HALF(vars,0x300)=math_random_int_range(120,500);
            if(moby[0x43]!=7) anim_start_blended(moby,7,0,12);
        }
        FLOAT(moby,0x48)=1.0f;
        break;
    case 4:
        FLOAT(moby,0x48)=1.0f;
        if(vec_distance_xy(moby+0x10,vars+0x240)<=g_hound_chase_range) {
            moby_set_state(moby,5,2);
            if(moby[0x43]!=8) anim_start_blended(moby,8,2,6);
            FLOAT(vars,0x314)=0.0f;
        } else if(math_fast_float_d((int *)(vars+0x318))) {
            delay=math_random_float_range(0.2617994248867035f,0.523598849773407f);
            if(math_random_int_below(2)==0) delay=-delay;
            FLOAT(vars,0x314)=delay;
            INT(vars,0x318)=math_random_int_range(45,60);
        }
        break;
    case 5:
        if(moby[0x42]!=8) break;
        if(math_is_value_within_step_us2(moby,8.0f)) PlayMobySound(3,0,moby);
        if(moby[0x42]!=8) break;
        if(math_is_value_within_step_us2(moby,10.0f)) {
            coll_test_hit_at_bone(0.75f,FLOAT(vars,0x330),1.0f,moby,0,0x4000001,0,1,0);
            break;
        }
        if(moby[0x42]!=8) break;
        if((moby[0x60]&2) && vec_distance_xy(moby+0x10,vars+0x240)>g_hound_chase_range) {
            moby_set_state(moby,4,2);
            if(moby[0x43]!=7) anim_start_blended(moby,7,0,6);
        }
        break;
    case 7:
        movement.f[0]=math_fast_sin_or_cos_a(FLOAT(moby,0xf8))*0.01666666753590107f*(FLOAT(vars,0x30c)+FLOAT(vars,0x30c));
        movement.f[1]=math_fast_sin_or_cos_b(FLOAT(moby,0xf8))*0.01666666753590107f*(FLOAT(vars,0x30c)+FLOAT(vars,0x30c));
        movement.f[2]=0.0f;
        add_vectors(&position,moby+0x10,&movement);
        if(vec_distance_xy(moby+0x10,vars+0x2e0)>6.0f) moby_set_state(moby,4,2);
        break;
    case 3:
        delay=mat_fast_helper_a(FLOAT(vars,0x240)-FLOAT(moby,0x10),FLOAT(vars,0x244)-FLOAT(moby,0x14));
        delay=FastAddRotations(delay,FLOAT(vars,0x314));
        MobySpringTurn(moby,delay,(float *)(vars+0x310),0.05f,0.3f,0.10471977293491364f);
        if(moby[0x60]&2) {
            moby_set_state(moby,4,-1);
            if(moby[0x43]!=7) anim_start_blended(moby,7,0,15);
        }
        break;
    case 8:
        if(object_pull_toward_hero(moby)) {
            SetDeathBits_us2(moby,0,3); moby_mark_spawned(moby); return;
        }
        break;
    }
    if((unsigned)((u8)moby[0x20]-7)>1) barlow_enemy_update_movement(moby);
    enemy_turn_toward_hero((u8 *)moby);
    return;
}
