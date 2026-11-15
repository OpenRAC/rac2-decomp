#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int g_moby_l11_table __attribute__((sda));
extern char D_L11_001BA8C0[];
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern int FloatToInt(float);
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
extern void vec_random_direction(float *, float, float);
extern void part_spawn_masked_debris(char *, int, float *, float, float, float, float, unsigned char);
extern int weapon_select_aim_target(char *, int, int, int, float, float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(char *);
typedef struct { char pad[0x330]; int children[10]; char gap[0x28]; unsigned char flags[10]; } ChildSlots;
#define CHILD(o,i) ((char *)(D_L11_001B359C + (((ChildSlots *)(*(char **)((o)+0x68)))->children[i] << 8)))

void chain_creature_update_damage(char *);

/* Sets up the chain creature, then handles damage to its head and body segments, losing segments, and its death burst. */
void chain_creature_update_damage(char *obj)
{
    char *vars = *(char **)(obj+0x68);
    float v[4], direction[4], velocity[4], random[4], pos[4];
    int i, j, k, consumed;
    char *hit;
    float damage, scale;
    if (*(unsigned char *)(obj+0x20)==0) {
        *(unsigned char *)(vars+0x48)=FloatToInt(15.0f);
        *(unsigned char *)(vars+0x4A)=FloatToInt(4.0f);
        *(int *)(vars+0x38C)=-1;
        if (*(short *)(vars+0x24)==0) {
            *(short *)(vars+0x24)=30;
            *(float *)(vars+0x20)=30.0f;
        }
        chain_creature_clear_sound_flags(obj);
    }
    if (*(unsigned char *)(obj+0x20)>=3 && !*(int *)(vars+0x364)) {
        consumed=0;
        for (i=0;i<10;i++) {
            if (!((ChildSlots *)vars)->flags[i]) {
                hit=part_find_owned_effect_slot(CHILD(obj,i),0x10000,0);
                damage=moby_update_aim_target_strength(obj,hit);
                if (damage!=0.0f) {
                    D_L11_001FFA78[*(unsigned char *)(vars+0x37)]+=(int)(damage*32.0f);
                    gfx_start_color_fade(CHILD(obj,i),vars+0x70);
                    if (*(float *)(hit+0x2C)>3.0f) {
                        scale=damage*0.125f;
                        if (scale>1.0f) scale=1.0f;
                        else if (scale<0.0f) scale=0.0f;
                        vec_scale_to_length((char *)v,hit+0x10,scale*0.2777777910232544f);
                        FastVecAdd(vars+0x110+i*16,vars+0x110+i*16,(char *)v);
                        moby_set_state(obj,5,-1);
                    }
                }
                if (*(short *)(vars+0x378)>=4) {
                    *(float *)(vars+0x360)+=damage;
                    if (!consumed && *(float *)(vars+0x360)>10.0f) {
                        char *records=(char *)g_moby_l11_table;
                        *(float *)(vars+0x20)-=*(float *)(vars+0x360);
                        (*(short *)(vars+0x378))--;
                        *(float *)(vars+0x360)=0;
                        consumed=1;
                        part_spawn_blast_burst(obj,records+(((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+0x10);
                        rotor_aim_at_entry(obj,i,1);
                        moby_set_state(obj,5,-1);
                    }
                } else *(float *)(vars+0x20)-=damage;
                *(unsigned char *)((((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+g_moby_l11_table+0xA8)=255;
            }
        }
        hit=part_find_owned_effect_slot(obj,0x10000,0);
        damage=moby_update_aim_target_strength(obj,hit);
        if (damage!=0.0f) {
            gfx_start_color_fade(obj,vars+0x70);
            D_L11_001FFA78[*(unsigned char *)(vars+0x37)]+=(int)(damage*32.0f);
            if (*(float *)(hit+0x2C)>3.0f) {
                scale=damage*0.125f;
                if (scale>1.0f) scale=1.0f;
                else if (scale<0.0f) scale=0.0f;
                vec_scale_to_length((char *)direction,hit+0x10,scale*0.5555555820465088f);
                FastVecAdd(obj+0x10,obj+0x10,(char *)direction);
            }
            if (*(short *)(vars+0x378)>=4) *(float *)(vars+0x360)+=damage;
            else *(float *)(vars+0x20)-=damage;
        }
        *(unsigned char *)(obj+0xA8)=255;
        if (*(unsigned char *)(obj+0x20)!=6 && *(unsigned char *)(obj+0x20)!=1 &&
            *(unsigned char *)(obj+0x20)!=7 && *(unsigned char *)(obj+0x20)!=0 && *(float *)(vars+0x20)<=0.0f)
            moby_set_state(obj,6,2);
    } else {
        *(unsigned char *)(obj+0xA8)=255;
        for (j=0;j<10;j++) if (!((ChildSlots *)vars)->flags[j]) *(unsigned char *)((((ChildSlots *)*(char **)(obj+0x68))->children[j]<<8)+g_moby_l11_table+0xA8)=255;
        *(float *)(vars+0x360)=0;
    }
    if (*(char **)(vars+0x364) && *(unsigned char *)(*(char **)(vars+0x364)+0x20)<2) {
        *(int *)(vars+0x364)=0;
        arena_set_boss_owner(*(char **)(obj+0xB8),obj);
    }
    if (*(unsigned char *)(obj+0x20)>=2 && *(unsigned char *)(vars+0x2E)==2) {
        *(float *)(vars+0x20)=0;
        chain_creature_clear_sound_flags(obj);
        FastVecSub(direction,(float *)D_L11_001BA8C0,(float *)(obj+0x10));
        vec_scale_to_length((char *)direction,(char *)direction,0.5f);
        qcopy(v,vars+0x100);
        part_spawn_blast_burst(obj,(char *)v);
        vec_random_direction(random,0.03333333507180214f,0.06666667014360428f);
        FastVecAdd((char *)velocity,(char *)direction,(char *)random);
        for (k=0;k<10;k++) {
            if (!((ChildSlots *)vars)->flags[k]) {
                qcopy(pos,vars+0x100+k*16);
                vec_random_direction(random,0.1666666716337204f,0.3333333432674408f);
                FastVecAdd((char *)velocity,(char *)direction,(char *)random);
                part_spawn_masked_debris(CHILD(obj,k),3,velocity,3,6,3,6,255);
                part_spawn_blast_burst(obj,(char *)pos);
                drone_kill_with_effects(CHILD(obj,k));
            }
        }
    }
    *(int *)(vars+0x328)=weapon_select_aim_target(obj,*(int *)(vars+0x36C),0,0,255,255);
    if (*(unsigned char *)(obj+0x31) && fast_vec_dist(obj+0x10,D_L11_001BA8C0)<48.0f) {
        moby_update_ground_check(obj);
        *(unsigned char *)(obj+0x6F)=45;
    }
}
