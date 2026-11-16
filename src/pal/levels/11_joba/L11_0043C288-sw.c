#include "include_asm.h"

#include "common.h"
extern int g_moby_l11_table __attribute__((sda));
extern char g_hero_l11_position[];
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern void part_spawn_blast_burst_pal(char *, char *);
extern void rotor_aim_at_entry_pal(char *, int, int);
extern void chain_creature_clear_sound_flags(char *);
extern void drone_kill_with_effects_pal(char *);
extern void chain_creature_choose_path(char *);
extern int chain_creature_follow_path_pal(char *);
extern int chain_creature_pick_move_state(char *);
extern void chain_creature_reset_projectile_seq(char *);
extern void chain_creature_fire_projectile_pal(char *);
extern void LayOutVerletChain(char *);
extern void chain_creature_update_body_pal(char *);
extern void moby_set_anim_type_three_pal(char *, int, int);
extern int flag_set_first_pending(char *);
extern int PlayMobySound(int, int, char *);
extern void snd_stop_voice(int);
extern int snd_is_voice_playing_for_owner(char *, int);
extern char g_sound_state[];
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern void euler_rotation_basis(char *, char *);
extern void vec_random_direction(float *, float, float);
extern void func_PAL_002B15D8(char *, int, float *, float, float, float, float, unsigned char);
typedef struct { char pad[0x330]; int children[10]; char gap[0x28]; unsigned char flags[10]; } ChildSlots;
#define CHILD(o,i) ((char *)(D_L11_001B359C + (((ChildSlots *)(*(char **)((o)+0x68)))->children[i] << 8)))
void func_PAL_L11_0043CB48(char *);

void func_PAL_L11_0043C500(char *obj)
{
    char *s=*(char **)(obj+0x68);
    float target[4], pos[4], direction[4], velocity[4], random[4];
    int i, count;
    char *p;
    func_PAL_L11_0043CB48(obj);
    qcopy(target,s+0x50);
    vec_distance_xy(obj+0x10,(char *)target);
    { float x=target[0], y=target[1];
      float ox=*(float *)(obj+0x10), oy=*(float *)(obj+0x14);
      x-=ox;
      y-=oy;
      FastDiffRots(*(float *)(obj+0xF8),mat_fast_helper_a(x,y)); }

    switch (*(unsigned char *)(obj+0x95)) {
    case 0: break;
    case 1:
        if (!snd_is_voice_playing_for_owner(obj,*(int *)(s+0x38C))) *(int *)(s+0x38C)=PlayMobySound(0,4,obj);
        break;
    }
    switch (*(unsigned char *)(obj+0x20)) {
    case 2:
        if (flag_set_first_pending(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) func_PAL_002A7E68(obj,0,0,8);
            chain_creature_choose_path(obj);
            p=*(char **)(s+0x324);
            qcopy(obj+0x10,p+0x10);
            *(float *)(obj+0xF8)=mat_fast_helper_a(*(float *)(p+0x20)-*(float *)(obj+0x10),*(float *)(p+0x24)-*(float *)(obj+0x14));
            euler_rotation_basis(obj+0xC0,obj+0xF0);
            LayOutVerletChain(obj);
        } else if (chain_creature_follow_path_pal(obj)==1) moby_set_state(obj,3,-1);
        break;
    case 3:
        if (flag_set_first_pending(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) func_PAL_002A7E68(obj,0,0,8);
            chain_creature_choose_path(obj);
        } else if (chain_creature_follow_path_pal(obj)==1)
            moby_set_state(obj,chain_creature_pick_move_state(obj),-1);
        break;
    case 4:
        if (flag_set_first_pending(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) func_PAL_002A7E68(obj,0,0,8);
            chain_creature_choose_path(obj);
        } else {
            if (chain_creature_follow_path_pal(obj)==1) moby_set_state(obj,chain_creature_pick_move_state(obj),-1);
            if (*(unsigned char *)(obj+0x31)) {
                if (*(short *)(s+0x374)==-1) chain_creature_reset_projectile_seq(obj);
                chain_creature_fire_projectile_pal(obj);
            }
        }
        break;
    case 5:
        if (flag_set_first_pending(obj)) {
            if (*(unsigned char *)(obj+0x43)!=4) func_PAL_002A7E68(obj,4,0,8);
            if (*(int *)(s+0x38C)!=-1) {
                char *entry=g_sound_state+*(int *)(s+0x38C)*0x70;
                if (*(char **)(entry+0x88)==obj && *(unsigned char *)(entry+0x74)) snd_stop_voice(*(int *)(s+0x38C));
            }
            *(int *)(s+0x38C)=-1;
        }
        if (*(unsigned char *)(obj+0x60)&2) {
            if (*(unsigned char *)(obj+0x43)!=0) func_PAL_002A7E68(obj,0,0,6);
        }
        if (chain_creature_follow_path_pal(obj)==1) moby_set_state(obj,chain_creature_pick_move_state(obj),-1);
        break;
    case 7: break;
    case 6:
        if (flag_set_first_pending(obj)) {
            *(unsigned short *)(obj+0x96)=0;
            if (*(unsigned char *)(obj+0x43)!=4) func_PAL_002A7E68(obj,4,0,8);
        }
        if (*(unsigned short *)(obj+0x96)>8) {
            FastVecSub(direction,(float *)g_hero_l11_position,(float *)(obj+0x10));
            vec_scale_to_length((char *)direction,(char *)direction,0.6f);
            qcopy(pos,s+0x100);
            part_spawn_blast_burst_pal(obj,(char *)pos);
            vec_random_direction(random,0.040000003f,0.080000006f);
            FastVecAdd((char *)velocity,(char *)direction,(char *)random);
                count=0;
            func_PAL_002B15D8(obj,1,velocity,3,6,3,6,255);
            for (i=0;i<10;i++) {
                if (!((ChildSlots *)s)->flags[i]) {
                    if (count>=4) {
                        qcopy(pos,s+0x100+i*16);
                        vec_random_direction(random,0.20000002f,0.40000004f);
                        FastVecAdd((char *)velocity,(char *)direction,(char *)random);
                        func_PAL_002B15D8(CHILD(obj,i),3,velocity,3,6,3,6,255);
                        part_spawn_blast_burst_pal(obj,(char *)pos);
                        drone_kill_with_effects_pal(CHILD(obj,i));
                    } else {
                        char *records=(char *)g_moby_l11_table;
                        (*(short *)(s+0x378))--;
                        count++;
                        part_spawn_blast_burst_pal(obj,records+(((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+0x10);
                        rotor_aim_at_entry_pal(obj,i,0);
                    }
                }
            }
            qcopy(pos,s+0x1B0);
            vec_random_direction(random,0.40000004f,0.6f);
            FastVecAdd((char *)velocity,(char *)direction,(char *)random);
            func_PAL_002B15D8((char *)(g_moby_l11_table+(*(int *)(*(char **)(obj+0x68)+0x358)<<8)),7,velocity,3,6,3,6,255);
            part_spawn_blast_burst_pal(obj,(char *)pos);
            moby_set_anim_type_three_pal(obj,0,-1);
            chain_creature_clear_sound_flags(obj);
        }
        break;
    }
    chain_creature_update_body_pal(obj);
}
