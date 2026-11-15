#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int g_moby_l11_table __attribute__((sda));
extern char D_L11_001BA8C0[];
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern int FloatToInt(float);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern char *part_find_owned_effect_slot(char *, int, int);
extern float moby_update_aim_target_strength(char *, char *);
extern void gfx_start_color_fade(char *, char *);
extern int D_L11_001FFA78[];
extern void part_spawn_blast_burst(char *, char *);
extern void rotor_aim_at_entry(char *, int, int);
extern void chain_creature_clear_sound_flags(char *);
extern void drone_kill_with_effects(char *);
extern void arena_set_boss_owner(char *, char *);
extern void chain_creature_choose_path(char *);
extern int chain_creature_follow_path(char *);
extern int chain_creature_pick_move_state(char *);
extern void chain_creature_reset_projectile_seq(char *);
extern void chain_creature_fire_projectile(char *);
extern void LayOutVerletChain(char *);
extern void chain_creature_update_body(char *);
extern void moby_set_anim_type_three(char *, int, int);
extern int flag_set_first_pending(char *);
extern int PlayMobySound(int, int, char *);
extern void func_3739C0(int);
extern int func_373978(char *, int);
extern char g_sound_state[];
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern void euler_rotation_basis(char *, char *);
extern void vec_random_direction(float *, float, float);
extern void part_spawn_masked_debris(char *, int, float *, float, float, float, float, unsigned char);
extern int weapon_select_aim_target(char *, int, int, int, float, float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(char *);
typedef struct { char pad[0x330]; int children[10]; char gap[0x28]; unsigned char flags[10]; } ChildSlots;
#define CHILD(o,i) ((char *)(D_L11_001B359C + (((ChildSlots *)(*(char **)((o)+0x68)))->children[i] << 8)))

void chain_creature_update_damage(char *);

/* Runs the chain creature through its states: following its path, firing at the hero, and bursting apart when it dies. */
void UpdateRotorGroupState(char *obj)
{
    char *vars=*(char **)(obj+0x68);
    float target[4], pos[4], direction[4], velocity[4], random[4];
    int i, count;
    char *p;
    chain_creature_update_damage(obj);
    qcopy(target,vars+0x50);
    vec_distance_xy(obj+0x10,(char *)target);
    { float x=target[0], y=target[1];
      float ox=*(float *)(obj+0x10), oy=*(float *)(obj+0x14);
      x-=ox;
      y-=oy;
      FastDiffRots(*(float *)(obj+0xF8),mat_fast_helper_a(x,y)); }

    switch (*(unsigned char *)(obj+0x95)) {
    case 0: break;
    case 1:
        if (!func_373978(obj,*(int *)(vars+0x38C))) *(int *)(vars+0x38C)=PlayMobySound(0,4,obj);
        break;
    }
    switch (*(unsigned char *)(obj+0x20)) {
    case 2:
        if (flag_set_first_pending(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) anim_start_blended(obj,0,0,10);
            chain_creature_choose_path(obj);
            p=*(char **)(vars+0x324);
            qcopy(obj+0x10,p+0x10);
            *(float *)(obj+0xF8)=mat_fast_helper_a(*(float *)(p+0x20)-*(float *)(obj+0x10),*(float *)(p+0x24)-*(float *)(obj+0x14));
            euler_rotation_basis(obj+0xC0,obj+0xF0);
            LayOutVerletChain(obj);
        } else if (chain_creature_follow_path(obj)==1) moby_set_state(obj,3,-1);
        break;
    case 3:
        if (flag_set_first_pending(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) anim_start_blended(obj,0,0,10);
            chain_creature_choose_path(obj);
        } else if (chain_creature_follow_path(obj)==1)
            moby_set_state(obj,chain_creature_pick_move_state(obj),-1);
        break;
    case 4:
        if (flag_set_first_pending(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) anim_start_blended(obj,0,0,10);
            chain_creature_choose_path(obj);
        } else {
            if (chain_creature_follow_path(obj)==1) moby_set_state(obj,chain_creature_pick_move_state(obj),-1);
            if (*(unsigned char *)(obj+0x31)) {
                if (*(short *)(vars+0x374)==-1) chain_creature_reset_projectile_seq(obj);
                chain_creature_fire_projectile(obj);
            }
        }
        break;
    case 5:
        if (flag_set_first_pending(obj)) {
            if (*(unsigned char *)(obj+0x43)!=4) anim_start_blended(obj,4,0,10);
            if (*(int *)(vars+0x38C)!=-1) {
                char *entry=g_sound_state+*(int *)(vars+0x38C)*0x70;
                if (*(char **)(entry+0x88)==obj && *(unsigned char *)(entry+0x74)) func_3739C0(*(int *)(vars+0x38C));
            }
            *(int *)(vars+0x38C)=-1;
        }
        if (*(unsigned char *)(obj+0x60)&2) {
            if (*(unsigned char *)(obj+0x43)!=0) anim_start_blended(obj,0,0,7);
        }
        if (chain_creature_follow_path(obj)==1) moby_set_state(obj,chain_creature_pick_move_state(obj),-1);
        break;
    case 7: break;
    case 6:
        if (flag_set_first_pending(obj)) {
            *(unsigned short *)(obj+0x96)=0;
            if (*(unsigned char *)(obj+0x43)!=4) anim_start_blended(obj,4,0,10);
        }
        if (*(unsigned short *)(obj+0x96)>10) {
            FastVecSub(direction,(float *)D_L11_001BA8C0,(float *)(obj+0x10));
            vec_scale_to_length((char *)direction,(char *)direction,0.5f);
            qcopy(pos,vars+0x100);
            part_spawn_blast_burst(obj,(char *)pos);
            vec_random_direction(random,0.03333333507180214f,0.06666667014360428f);
            FastVecAdd((char *)velocity,(char *)direction,(char *)random);
                count=0;
            part_spawn_masked_debris(obj,1,velocity,3,6,3,6,255);
            for (i=0;i<10;i++) {
                if (!((ChildSlots *)vars)->flags[i]) {
                    if (count>=4) {
                        qcopy(pos,vars+0x100+i*16);
                        vec_random_direction(random,0.1666666716337204f,0.3333333432674408f);
                        FastVecAdd((char *)velocity,(char *)direction,(char *)random);
                        part_spawn_masked_debris(CHILD(obj,i),3,velocity,3,6,3,6,255);
                        part_spawn_blast_burst(obj,(char *)pos);
                        drone_kill_with_effects(CHILD(obj,i));
                    } else {
                        char *records=(char *)g_moby_l11_table;
                        (*(short *)(vars+0x378))--;
                        count++;
                        part_spawn_blast_burst(obj,records+(((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+0x10);
                        rotor_aim_at_entry(obj,i,0);
                    }
                }
            }
            qcopy(pos,vars+0x1B0);
            vec_random_direction(random,0.3333333432674408f,0.5f);
            FastVecAdd((char *)velocity,(char *)direction,(char *)random);
            part_spawn_masked_debris((char *)(g_moby_l11_table+(*(int *)(*(char **)(obj+0x68)+0x358)<<8)),7,velocity,3,6,3,6,255);
            part_spawn_blast_burst(obj,(char *)pos);
            moby_set_anim_type_three(obj,0,-1);
            chain_creature_clear_sound_flags(obj);
        }
        break;
    }
    chain_creature_update_body(obj);
}

