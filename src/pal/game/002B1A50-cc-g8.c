#include "names.h"
/* func_PAL_002B1A50, the PAL copy of func_002B0ED8: the same C, where rename func_002AB8C0 becomes func_PAL_002AC3C0; rename func_002A96A0 becomes func_PAL_002AA108; rename func_002B3380 becomes func_PAL_002B3F18; rename func_002B1350 becomes func_PAL_002B1EE8; scale timeout. */
#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u8 *)((char *)(p)+(o)))
extern void gfx_update_color_fade_pal(void *,void *);
extern char *part_find_owned_effect_slot(void *,int,int);
extern int FastDecTimer(void *);
extern float moby_update_aim_target_strength_pal(void *,void *);
extern int part_spawn_damage_debris_pal(void *,void *,void *);
extern char *g_moby_pool_start;
typedef struct { int frame; } DamageClock;
extern DamageClock g_game_time;
extern int D_001B1688_1;
extern u8 g_item_slot_to_record[];
typedef struct { char pad[0x54]; float scale; char tail[0x88]; } DamageClass;
extern DamageClass g_weapon_table[];
extern int subtract_integer_with_clamp(int);
extern float vec_get_horizontal_offset_length(void *,void *,int);
extern void FastVecSub(void *,void *,void *);
extern char g_hero_position[];
extern void vec_transform_and_scale(void *,void *,void *,int,float);
extern void FastVecScale(void *,void *,float);
extern int moby_start_hit_reaction_pal(void *,void *,void *,int);
extern void moby_set_state(void *,int,int);

/* Applies a hit to an object: subtracts the damage from its health, grades the hit from light to fatal and starts the matching hit reaction (PAL: 50 Hz timeout). */
int moby_apply_damage_to_object_pal(char *object,char *state,int special)
{
    float vector[4] __attribute__((aligned(16)));
    char *health,*callback,*hit;
    float original,damage;
    int result=0,timeout;
    int kind;
    if (!(*(u16 *)(object+0x34)&0x20)) return 0;
    health=P(P(object,0x68),0);
    callback=P(P(object,0x68),0x1c);
    if (!state || !health) return 0;
    gfx_update_color_fade_pal(object,state);
    original=0.0f;
    hit=part_find_owned_effect_slot(object,0x10000,0);
    if (!FastDecTimer(health+6)) hit=0;
    if (hit) {
        original=F(hit,0x2c);
        if (F(state,0xa8)!=0.0f && P(hit,0x20) && H(object,0xaa)==H(P(hit,0x20),0xaa))
            F(hit,0x2c)=original*F(state,0xa8);
        if (special) F(hit,0x2c)*=F(state,0xac);
    }
    damage=moby_update_aim_target_strength_pal(object,hit);
    U(object,0xa8)=255;
    F(health,0)-=damage;
    if (callback) part_spawn_damage_debris_pal(object,callback,health);
    if (damage==0.0f) return 0;
    H(state,0x70)=-1;
    if (hit && P(hit,0x20)) H(state,0x70)=(P(hit,0x20)-g_moby_pool_start)>>8;
    kind=U(health,0x17);
    if (damage*((DamageClass *)(g_item_slot_to_record[kind]*224+(char *)g_weapon_table))->scale>=H(health,4)*F(state,0x58)) timeout=90;
    else timeout=300;
    if (!U(state,0x77) && subtract_integer_with_clamp(g_game_time.frame-I(state,0x44))>(((int)(timeout) * 5 + 2) / 6)) {
        if (damage<H(health,4)*F(state,0x58)) damage=H(health,4)*F(state,0x58);
    }
    if (F(health,0)<=0.0f) result=4;
    else if (damage>=H(health,4)*F(state,0x5c)) result=3;
    else if (damage>=H(health,4)*F(state,0x58)) result=2;
    else if (damage!=0.0f && !U(state,0x77) && hit && P(hit,0x20) && H(P(hit,0x20),0xaa)==0x47) result=2;
    else if (original!=0.0f) result=1;
    if (special && (unsigned)(result-1)<=2) result=6;
    if (result>=2 && hit && U(health,0x17)==10) {
        damage=vec_get_horizontal_offset_length(object,hit+0x10,0);
        FastVecSub(hit+0x10,object+0x10,g_hero_position);
        vec_transform_and_scale(object,hit+0x10,hit+0x10,0,damage);
    }
    if (!result || (*(u16 *)(state+0x38)&3)) return 0;
    if (U(object,0x95)==I(state,0x48) && result<4) {
        if (U(state,0x75)) return 0;
        if (U(state,0x1a)<2) return 0;
    }
    if (hit && (I(hit,0x30)&1)) qcopy(vector,hit+0x10);
    else {
        FastVecScale(vector,object+0xc0,-1.0f);
        vector[2]=1.0f;
        vector[3]=5627.925f;
    }
    if (moby_start_hit_reaction_pal(object,state,vector,result)) {
        I(state,0x44)=D_001B1688_1;
        if (I(state,0x48)!=-1) moby_set_state(object,U(state,0x10),I(state,0x48));
        else moby_set_state(object,U(state,0x10),-1);
        U(state,0x1a)=0;
    }
    return result;
}
