#include "include_asm.h"



#include "common.h"
extern int g_moby_l11_table __attribute__((sda));
extern char g_hero_l11_position[];
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern int FloatToInt(float);
extern void moby_set_state(void *, int, int);
extern char *part_find_owned_effect_slot(char *, int, int);
extern float moby_update_aim_target_strength_pal(char *, char *);
extern void gfx_start_color_fade_pal(char *, char *);
extern int g_enemy_damage_accum[];
extern void part_spawn_blast_burst_pal(char *, char *);
extern void rotor_aim_at_entry_pal(char *, int, int);
extern void chain_creature_clear_sound_flags(char *);
extern void drone_kill_with_effects_pal(char *);
extern void arena_set_boss_owner(char *, char *);
extern void vec_random_direction(float *, float, float);
extern void part_spawn_masked_debris_pal(char *, int, float *, float, float, float, float, unsigned char);
extern int weapon_select_aim_target(char *, int, int, int, float, float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(char *);
typedef struct { char pad[0x330]; int children[10]; char gap[0x28]; unsigned char flags[10]; } ChildSlots;
#define CHILD(o,i) ((char *)(D_L11_001B359C + (((ChildSlots *)(*(char **)((o)+0x68)))->children[i] << 8)))
void chain_creature_update_damage(char *);

/* Sets up the chain creature, then handles damage to its head and body segments, losing segments,
   and its death burst (PAL: 50 Hz timings). */
void chain_creature_update_damage_pal(char *obj)
{
    char *state = *(char **)(obj+0x68);
    float vec[4], direction[4], velocity[4], random[4], pos[4];
    int i, j, k, consumed;
    char *hit;
    float damage, scale;
    if (*(unsigned char *)(obj+0x20)==0) {
        *(unsigned char *)(state+0x48)=FloatToInt(15.0f);
        *(unsigned char *)(state+0x4A)=FloatToInt(4.0f);
        *(int *)(state+0x38C)=-1;
        if (*(short *)(state+0x24)==0) {
            *(short *)(state+0x24)=30;
            *(float *)(state+0x20)=3e+01f;
        }
        chain_creature_clear_sound_flags(obj);
    }
    if (*(unsigned char *)(obj+0x20)>=3 && !*(int *)(state+0x364)) {
        consumed=0;
        for (i=0;i<10;i++) {
            if (!((ChildSlots *)state)->flags[i]) {
                hit=part_find_owned_effect_slot(CHILD(obj,i),0x10000,0);
                damage=moby_update_aim_target_strength_pal(obj,hit);
                if (damage!=0.0f) {
                    g_enemy_damage_accum[*(unsigned char *)(state+0x37)]+=(int)(damage*32.0f);
                    gfx_start_color_fade_pal(CHILD(obj,i),state+0x70);
                    if (*(float *)(hit+0x2C)>3.0f) {
                        scale=damage*0.125f;
                        if (scale>1.0f) scale=1.0f;
                        else if (scale<0.0f) scale=0.0f;
                        vec_scale_to_length((char *)vec,hit+0x10,scale*0.4f);
                        FastVecAdd(state+0x110+i*16,state+0x110+i*16,(char *)vec);
                        moby_set_state(obj,5,-1);
                    }
                }
                if (*(short *)(state+0x378)>=4) {
                    *(float *)(state+0x360)+=damage;
                    if (!consumed && *(float *)(state+0x360)>10.0f) {
                        char *records=(char *)g_moby_l11_table;
                        *(float *)(state+0x20)-=*(float *)(state+0x360);
                        (*(short *)(state+0x378))--;
                        *(float *)(state+0x360)=0;
                        consumed=1;
                        part_spawn_blast_burst_pal(obj,records+(((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+0x10);
                        rotor_aim_at_entry_pal(obj,i,1);
                        moby_set_state(obj,5,-1);
                    }
                } else *(float *)(state+0x20)-=damage;
                *(unsigned char *)((((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+g_moby_l11_table+0xA8)=255;
            }
        }
        hit=part_find_owned_effect_slot(obj,0x10000,0);
        damage=moby_update_aim_target_strength_pal(obj,hit);
        if (damage!=0.0f) {
            gfx_start_color_fade_pal(obj,state+0x70);
            g_enemy_damage_accum[*(unsigned char *)(state+0x37)]+=(int)(damage*32.0f);
            if (*(float *)(hit+0x2C)>3.0f) {
                scale=damage*0.125f;
                if (scale>1.0f) scale=1.0f;
                else if (scale<0.0f) scale=0.0f;
                vec_scale_to_length((char *)direction,hit+0x10,scale*0.8f);
                FastVecAdd(obj+0x10,obj+0x10,(char *)direction);
            }
            if (*(short *)(state+0x378)>=4) *(float *)(state+0x360)+=damage;
            else *(float *)(state+0x20)-=damage;
        }
        *(unsigned char *)(obj+0xA8)=255;
        if (*(unsigned char *)(obj+0x20)!=6 && *(unsigned char *)(obj+0x20)!=1 &&
            *(unsigned char *)(obj+0x20)!=7 && *(unsigned char *)(obj+0x20)!=0 && *(float *)(state+0x20)<=0.0f)
            moby_set_state(obj,6,2);
    } else {
        *(unsigned char *)(obj+0xA8)=255;
        for (j=0;j<10;j++) if (!((ChildSlots *)state)->flags[j]) *(unsigned char *)((((ChildSlots *)*(char **)(obj+0x68))->children[j]<<8)+g_moby_l11_table+0xA8)=255;
        *(float *)(state+0x360)=0;
    }
    if (*(char **)(state+0x364) && *(unsigned char *)(*(char **)(state+0x364)+0x20)<2) {
        *(int *)(state+0x364)=0;
        arena_set_boss_owner(*(char **)(obj+0xB8),obj);
    }
    if (*(unsigned char *)(obj+0x20)>=2 && *(unsigned char *)(state+0x2E)==2) {
        *(float *)(state+0x20)=0;
        chain_creature_clear_sound_flags(obj);
        FastVecSub(direction,(float *)g_hero_l11_position,(float *)(obj+0x10));
        vec_scale_to_length((char *)direction,(char *)direction,0.6f);
        qcopy(vec,state+0x100);
        part_spawn_blast_burst_pal(obj,(char *)vec);
        vec_random_direction(random,0.040000003f,0.080000006f);
        FastVecAdd((char *)velocity,(char *)direction,(char *)random);
        for (k=0;k<10;k++) {
            if (!((ChildSlots *)state)->flags[k]) {
                qcopy(pos,state+0x100+k*16);
                vec_random_direction(random,0.20000002f,0.40000004f);
                FastVecAdd((char *)velocity,(char *)direction,(char *)random);
                part_spawn_masked_debris_pal(CHILD(obj,k),3,velocity,3,6,3,6,255);
                part_spawn_blast_burst_pal(obj,(char *)pos);
                drone_kill_with_effects_pal(CHILD(obj,k));
            }
        }
    }
    *(int *)(state+0x328)=weapon_select_aim_target(obj,*(int *)(state+0x36C),0,0,255,255);
    if (*(unsigned char *)(obj+0x31) && fast_vec_dist(obj+0x10,g_hero_l11_position)<48.0f) {
        moby_update_ground_check(obj);
        *(unsigned char *)(obj+0x6F)=45;
    }
}


extern unsigned char g_moby_l11_script_data[];
extern void func_802F8AD0(void *a0, void *a1);
extern void func_80338398(void *a0, void *a1, int a2, int a3, float f12);
extern void rotor_tick_timers(char *p);
extern void IntegrateVerletChain(char *p);
extern void chain_creature_solve_length(char *p);
extern void chain_creature_update_segments(char *p);
extern void chain_creature_update_linked(char *p);

/* Runs the ten rotors' update, one frame each, and restarts the entry timer. */
void chain_creature_update_body_pal(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    int i;

    func_802F8AD0((void *)g_moby_l11_script_data, moby);

    for (i = 12; i >= 0; i--)
        ;

    if (*(unsigned char *)(moby + 0x20) >= 2) {
        rotor_tick_timers(moby);
        IntegrateVerletChain(moby);
        chain_creature_solve_length(moby);
        chain_creature_update_segments(moby);
        chain_creature_update_linked(moby);
    }
    if (*(unsigned short *)(moby + 0x96) <= 0xFFFE) {
        (*(unsigned short *)(moby + 0x96))++;
    }
    func_80338398(moby, state + 0x80, 1, 1, 2.5f);
}

