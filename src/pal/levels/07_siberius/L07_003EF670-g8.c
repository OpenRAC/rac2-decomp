#include "names.h"
/* func_PAL_L07_003EF670, the PAL copy of func_L07_003EB2C0: the same C, where 0x7C becomes 0.008f
   and the two timers at 0x132 and 0x134 are word values scaled to 50 Hz. */
#include "common.h"
#define INT_AT(p,n) (*(int *)((p)+(n)))
#define U16_AT(p,n) (*(unsigned short *)((p)+(n)))
#define FLOAT_AT(p,n) (*(float *)((p)+(n)))
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended_pal(void *,int,int,int);
extern float coll_get_ground_distance_below(void *,void *,void *);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern char *part_find_owned_effect_slot(void *,int,int);
extern int CollLine(void *,void *,int,void *,void *);
extern int moby_apply_damage_to_object_pal(void *,void *,int);
extern int weapon_select_aim_target(void *,int,float,float,int,int);
extern void moby_mark_spawned(void *);
extern void entity_set_group_alert_c(void *);
extern void entity_spawn_death_effects_b_pal(void *);
extern float g_shooter_alt_turn_rate __attribute__((sda));
extern int g_shooter_alt_timer_init __attribute__((sda));
extern int g_shooter_alt_timer_table[] __attribute__((sda));
extern int g_cutscene_l07_active_flag NOT_SDA;
extern char *g_shooter_path_table[] __attribute__((sda));
extern char g_hero_position_block[];

/* Initialize the entity, handle nearby collision targets, and update its animation. */
void shooter_entity_base_update_b_pal(unsigned char *moby)
{
    float from[4] __attribute__((aligned(16)));
    float to[4] __attribute__((aligned(16)));
    unsigned char *vars=*(unsigned char **)(moby+0x68);
    char *effect_slot;
    float turn;
    if (!moby[0x20]) {
        vars[0x48]=FloatToInt(15.0f);
        vars[0x4A]=FloatToInt(9.6f);

        if (math_random_int_below(2)) U16_AT(moby,0x34)|=0x8000;
        else U16_AT(moby,0x34)&=0x7FFF;
        vars[0x150]=6;
        INT_AT(vars,0x188)=3;
        FLOAT_AT(vars,0x17C)=0.15f;
        FLOAT_AT(vars,0x170)=1.0f;
        FLOAT_AT(vars,0x174)=1.0f;
        turn=g_shooter_alt_turn_rate;
        turn*=0.017453294f;
        FLOAT_AT(vars,0x180)=FLOAT_AT(moby,0x18)-3.0f;
        INT_AT(vars,0x88)|=0x201;
        FLOAT_AT(vars,0x54)=0.3f;
        FLOAT_AT(vars,0x50)=1.0f;
        FLOAT_AT(vars,0x60)=3.1415927f;
        if (math_random_int_below(2)) turn=-turn;
        FLOAT_AT(vars,0x12C)=turn;
        U16_AT(vars,0x132)=((s32)(g_shooter_alt_timer_init)*5+2)/6;
        U16_AT(vars,0x134)=((s32)(g_shooter_alt_timer_table[0])*5+2)/6;
        FLOAT_AT(vars,0x7C)=0.008f;
        if (INT_AT(vars,0x2B0)!=-1) {
            char *entry=g_shooter_path_table[0]+INT_AT(vars,0x2B0)*0x30;
            if (*(short *)(entry+0x30)) INT_AT(vars,0x8C)=**(int **)(entry+0x3C);
            else INT_AT(vars,0x8C)=-1;
        }
        qcopy(vars+0x2E0,moby+0x10);
        if (FLOAT_AT(moby,0x18)>FLOAT_AT((char *)&g_cutscene_l07_active_flag,0x28)) {
            moby[0x30]=255;
            INT_AT(vars,0x320)=1;
        }
        FLOAT_AT(moby,0x18)+=0.5f;
        coll_get_ground_distance_below(moby+0x10,moby,moby+0x10);
        if (INT_AT(vars,0x2B0)!=-1) {
            char *entry=g_shooter_path_table[0]+INT_AT(vars,0x2B0)*0x30;
            if (*(short *)(entry+0x30)) INT_AT(vars,0x8C)=**(int **)(entry+0x3C);
            else INT_AT(vars,0x8C)=-1;
        }
        if (!INT_AT(vars,0x2BC)) {
            INT_AT(moby,0x98)=0;
            U16_AT(moby,0x34)=(U16_AT(moby,0x34)|0x41)&0xEFFF;
            moby_set_state(moby,11,4);
            if (moby[0x43]) anim_start_blended_pal(moby,0,0,0);
        } else if (INT_AT(vars,0x2B8)==-1) {
            moby_set_state(moby,1,0);
            if (moby[0x43]!=2) anim_start_blended_pal(moby,2,0,0);
        } else {
            moby_set_state(moby,7,4);
            if (moby[0x43]) anim_start_blended_pal(moby,0,0,0);
        }
    }
    if (moby[0x31] && fast_vec_dist(moby+0x10,g_hero_position_block)<24.0f) {
        moby_update_ground_check(moby);
        moby[0x6F]=22;
    }
    effect_slot=part_find_owned_effect_slot(moby,0x10000,0);
    if (effect_slot && *(char **)(effect_slot+0x20)) {
        if (*(short *)(*(char **)(effect_slot+0x20)+0xAA)==0xB7F) moby[0xA8]=255;
        else if (fast_vec_dist(*(char **)(effect_slot+0x20)+0x10,moby+0x10)<32.0f) {
            qcopy(from,*(char **)(effect_slot+0x20)+0x10);
            from[2]+=0.5f;
            qcopy(to,moby+0x10);
            to[2]+=0.5f;
            if (CollLine(from,to,2,moby,0)) moby[0xA8]=255;
        }
    }
    if (moby_apply_damage_to_object_pal(moby,vars+0x140,0)) {
        entity_set_group_alert_c(moby);
        if (FLOAT_AT(vars,0x20)<=0) {
            entity_spawn_death_effects_b_pal(moby);
            moby_mark_spawned(moby);
            return;
        }
    }
    INT_AT(vars,0x2DC)=weapon_select_aim_target(moby,INT_AT(vars,0x2B0),FLOAT_AT(vars,0x2B4),0,0,0);
}
