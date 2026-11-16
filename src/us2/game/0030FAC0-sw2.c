#include "include_asm.h"

#include "common.h"
typedef float VecE[4] __attribute__((aligned(16)));
extern VecE g_coll_hit_point, g_coll_hit_position;
typedef struct {
    u8 pad00[0x80]; VecE position; u8 pad90[0x50]; VecE pickup_target;
    u8 padF0[0x2290-0xF0]; void *moby;
    u8 pad2294[0x24A4-0x2294]; f32 reach_distance, reach_height;
    u8 pad24AC[0x20]; s32 health;
} AmmoHero;
extern AmmoHero g_hero_state;
typedef struct {
    u8 pad00[0x38]; s16 sound_multiple, sound_single;
    u8 pad3C[0x8E - 0x3C]; u16 max_ammo; u8 pad90[0x50];
} AmmoDef;
extern u8 g_weapon_table[];
extern u8 g_item_slot_to_record[];
extern s32 g_item_ammo_counts[];
extern void *g_hero_moby NOT_SDA;
extern s32 g_game_time[] __attribute__((sda));
extern s32 g_ammo_pickup_time[] __attribute__((sda));
extern s32 D_001B24A8_gp SDATA(D_001B24A8);
extern s32 math_fast_float_d(s32 *);
extern u32 stub_empty_8(s32, s32);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
extern f32 ApproachValue(f32 *, f32, f32);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_clear_128(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void value_forward_three_args_us2(s32, s32, s32);
extern void moby_mark_spawned(void *);
extern f32 FastVecLength(void *);
extern f32 math_fabs(f32);
extern f32 vec_distance_xy(void *, void *);
extern f32 func_002A0558(void *, void *);
extern f32 fast_vec_dist(void *, void *);
extern f32 math_fast_sin_or_cos_a(f32);
extern s32 coll_test_point(void *, s32, s32, f32);
extern s32 CollLine(void *, void *, s32, s32, s32);
extern s32 FloatToInt(f32);
extern s32 subtract_integer_with_clamp(s32);
#define EF(p, n) (*(f32 *)((u8 *)(p) + (n)))
#define EI(p, n) (*(s32 *)((u8 *)(p) + (n)))
extern u32 ref_US2_0030FAC0_00(s32, s32);

void ammo_pickup_update_us2(u8 *object)
{
    VecE start, next;
    f32 alpha;
    u8 *state = *(u8 **)(object+0x68);
    math_fast_float_d((s32 *)(state+0x20));
    if (object[0x20] == 1 || object[0x20] == 4 || object[0x20] == 3) {
        if (FastVecLength(state+0x10) != 0.0f) {
            qcopy(start, object+0x10);
            start[2] += 0.5f;
            if (coll_test_point(start,2,0,0.4f)) {
                qcopy(object+0x10,g_coll_hit_point);
                EF(object,0x18) -= 0.5f;
            }
        }
        EF(state,0x18) -= 0.0013611112f;
        FastVecAdd(next,object+0x10,state+0x10);
        EF(state,0x18) -= 0.0013611112f;
        qcopy(start,object+0x10);
        start[2] += 0.1f;
        if (CollLine(start,next,2,0,0)) {
            vec_clear_128(state+0x10);
            qcopy(object+0x10,g_coll_hit_position);
        } else qcopy(object+0x10,next);
    }
    switch (object[0x20]) {
    case 0:
        object[0x20]=1;
        break;
    case 1: {
        AmmoDef *entry, *defs;
        u8 *mapping;
        s32 *counts;
        s32 eligible, old, current, difference, item, sound_item, sound;
        s32 elapsed;
        alpha = (f32)object[0x23];
        ApproachValue(&alpha,128.0f,4.0f);
        object[0x23] = FloatToInt(alpha);
        if (EI(state,0x20)>0) break;
        if (FastVecLength(state+0x10) != 0.0f) break;
        eligible=1;
        if (math_fabs(EF(object,0x18)-g_hero_state.position[2]) > g_hero_state.reach_height) eligible=0;
        else if (vec_distance_xy(object+0x10,g_hero_state.position)>g_hero_state.reach_distance) eligible=0;
        item=EI(state,8);
        mapping=g_item_slot_to_record;
        counts=g_item_ammo_counts;
        defs=(AmmoDef *)g_weapon_table;
        entry=&defs[mapping[item]];
        old=counts[item];
        if (old >= entry->max_ammo) eligible=0;
        if (EF(object,0x18)<EF(state,0x28)-2.0f) eligible=1;
        if (!g_hero_state.health) eligible=0;
        if (eligible) {
            ref_US2_0030FAC0_00(item,EI(state,0));
            sound_item=EI(state,8);
            current=counts[sound_item];
            if (old<current) {
                difference=current-old;
                if (difference==1) sound=defs[mapping[sound_item]].sound_single;
                else sound=defs[mapping[sound_item]].sound_multiple;
                value_forward_three_args_us2(sound,difference,-1);
            }
            object[0x20]=2;
            EF(object,0x2C)*=1.2f;
            vec_clear_128(state+0x10);
            elapsed=g_game_time[0]-g_ammo_pickup_time[0];
            EF(state,0x24)=0.13333334f;
            if (subtract_integer_with_clamp(elapsed)>=11) {
                snd_play_from_class_bank(0,0,object,0xD5);
                /* Last pickup-sound frame. */
                D_001B24A8_gp=g_game_time[0];
            }
        } else {
            if (object[0x23]<255) object[0x23]++;
            if (func_002A0558(object,g_hero_state.moby)<=-0.2f) {
                object[0x20]=3;
                *(s16 *)(state+6)=60;
            }
        }
        break;
    }
    case 2: {
        f32 speed, f;
        ApproachValue((f32 *)(state+0x24),0.0f,0.006666667f);
        EF(object,0x18)+=EF(state,0x24);
        speed=FastVecLength(state+0x10);
        ApproachValue(&speed,1.0666667f,0.006666667f);
        FastVecSub(state+0x10,g_hero_state.pickup_target,object+0x10);
        if (EF(object,0x2C)==0.0f || FastVecLength(state+0x10)<speed) { moby_mark_spawned(object); break; }
        vec_scale_to_length(state+0x10,state+0x10,speed);
        FastVecAdd(object+0x10,object+0x10,state+0x10);
        f=fast_vec_dist(object+0x10,g_hero_state.pickup_target)/(speed*30.0f+0.01f);
        if (f>1.0f) f=1.0f;
        else if (f<0.3f) f=0.3f;
        ApproachValue((f32 *)(object+0x2C),EF(*(u8 **)(object+0x24),0x24)*f,EF(*(u8 **)(object+0x24),0x24)*0.1f);
        break;
    }
    case 3: {
        f32 f;
        s32 item, phase, pulse;
        AmmoDef *entry, *defs;
        u8 *mapping;
        s32 *counts;
        phase = g_game_time[0]%60;
        alpha=(f32)object[0x23];
        f=math_fast_sin_or_cos_a((f32)phase*0.104719676f-3.1415901f);
        pulse=FloatToInt(f*5.0f+5.0f)+10;
        ApproachValue(&alpha,(f32)pulse,4.0f);
        object[0x23]=FloatToInt(alpha);
        if (func_002A0558(object,g_hero_moby)>=0.0f) goto reactivate;
        item=EI(state,8);
        mapping=g_item_slot_to_record;
        counts=g_item_ammo_counts;
        defs=(AmmoDef *)g_weapon_table;
        entry=&defs[mapping[item]];
        if (counts[item]>=entry->max_ammo) break;
    reactivate:
        object[0x20]=1;
        break;
    }
    case 4: {
        u8 *entry;
        entry=*(u8 **)(object+0x24);
        EF(object,0x2C)+=(EF(entry,0x24)-EF(object,0x2C))*0.03f;
        if ((EF(entry,0x24)-EF(object,0x2C))/EF(entry,0x24)<0.01f) {
            EF(object,0x2C)=EF(entry,0x24);
            object[0x20]=1;
            EI(object,0x98)=EI(entry,0x10);
        }
        break;
    }
    }
}
