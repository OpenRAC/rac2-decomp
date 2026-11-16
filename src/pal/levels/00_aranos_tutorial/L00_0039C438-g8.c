#include "names.h"
/* func_PAL_L00_0039C438, the PAL copy of func_0030ECC8: the same C, with PAL's callee names and
 * the 50 Hz values: per-frame rates and speeds scaled by 6/5 or (6/5)^2, timers by 5/6, 30.0f
 * becoming 25.0f and 1.2f becoming 1.24f. The modulus % 60 stays. */
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
extern u32 weapon_add_ammo(s32, s32);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
extern f32 ApproachValue(f32 *, f32, f32);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_clear_128(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void value_forward_three_args_pal(s32, s32, s32);
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

/* Updates an ammo pickup. It falls and bounces, fades in when it can be collected, flies to the player when picked up and adds the ammo (PAL). */
void ammo_pickup_update_pal(u8 *moby)
{
    VecE start, next;
    f32 alpha;
    u8 *vars = *(u8 **)(moby+0x68);
    math_fast_float_d((s32 *)(vars+0x20));
    if (moby[0x20] == 1 || moby[0x20] == 4 || moby[0x20] == 3) {
        if (FastVecLength(vars+0x10) != 0.0f) {
            qcopy(start, moby+0x10);
            start[2] += 0.5f;
            if (coll_test_point(start,2,0,0.4f)) {
                qcopy(moby+0x10,g_coll_hit_point);
                EF(moby,0x18) -= 0.5f;
            }
        }
        EF(vars,0x18) -= 0.00196f;
        FastVecAdd(next,moby+0x10,vars+0x10);
        EF(vars,0x18) -= 0.00196f;
        qcopy(start,moby+0x10);
        start[2] += 0.1f;
        if (CollLine(start,next,2,0,0)) {
            vec_clear_128(vars+0x10);
            qcopy(moby+0x10,g_coll_hit_position);
        } else qcopy(moby+0x10,next);
    }
    switch (moby[0x20]) {
    case 0:
        moby[0x20]=1;
        break;
    case 1: {
        AmmoDef *entry, *defs;
        u8 *mapping;
        s32 *counts;
        s32 eligible, old, current, difference, item, sound_item, sound;
        s32 elapsed;
        alpha = (f32)moby[0x23];
        ApproachValue(&alpha,128.0f,5.0f);
        moby[0x23] = FloatToInt(alpha);
        if (EI(vars,0x20)>0) break;
        if (FastVecLength(vars+0x10) != 0.0f) break;
        eligible=1;
        if (math_fabs(EF(moby,0x18)-g_hero_state.position[2]) > g_hero_state.reach_height) eligible=0;
        else if (vec_distance_xy(moby+0x10,g_hero_state.position)>g_hero_state.reach_distance) eligible=0;
        item=EI(vars,8);
        mapping=g_item_slot_to_record;
        counts=g_item_ammo_counts;
        defs=(AmmoDef *)g_weapon_table;
        entry=&defs[mapping[item]];
        old=counts[item];
        if (old >= entry->max_ammo) eligible=0;
        if (EF(moby,0x18)<EF(vars,0x28)-2.0f) eligible=1;
        if (!g_hero_state.health) eligible=0;
        if (eligible) {
            weapon_add_ammo(item,EI(vars,0));
            sound_item=EI(vars,8);
            current=counts[sound_item];
            if (old<current) {
                difference=current-old;
                if (difference==1) sound=defs[mapping[sound_item]].sound_single;
                else sound=defs[mapping[sound_item]].sound_multiple;
                value_forward_three_args_pal(sound,difference,-1);
            }
            moby[0x20]=2;
            EF(moby,0x2C)*=1.24f;
            vec_clear_128(vars+0x10);
            elapsed=g_game_time[0]-g_ammo_pickup_time[0];
            EF(vars,0x24)=0.16000001f;
            if (subtract_integer_with_clamp(elapsed)>=9) {
                snd_play_from_class_bank(0,0,moby,0xD5);
                /* Last pickup-sound frame. */
                D_001B24A8_gp=g_game_time[0];
            }
        } else {
            if (moby[0x23]<255) moby[0x23]++;
            if (func_002A0558(moby,g_hero_state.moby)<=-0.2f) {
                moby[0x20]=3;
                *(s16 *)(vars+6)=50;
            }
        }
        break;
    }
    case 2: {
        f32 speed, ease;
        ApproachValue((f32 *)(vars+0x24),0.0f,0.0096f);
        EF(moby,0x18)+=EF(vars,0x24);
        speed=FastVecLength(vars+0x10);
        ApproachValue(&speed,1.2800001f,0.0096f);
        FastVecSub(vars+0x10,g_hero_state.pickup_target,moby+0x10);
        if (EF(moby,0x2C)==0.0f || FastVecLength(vars+0x10)<speed) { moby_mark_spawned(moby); break; }
        vec_scale_to_length(vars+0x10,vars+0x10,speed);
        FastVecAdd(moby+0x10,moby+0x10,vars+0x10);
        ease=fast_vec_dist(moby+0x10,g_hero_state.pickup_target)/(speed*25.0f+0.01f);
        if (ease>1.0f) ease=1.0f;
        else if (ease<0.3f) ease=0.3f;
        ApproachValue((f32 *)(moby+0x2C),EF(*(u8 **)(moby+0x24),0x24)*ease,EF(*(u8 **)(moby+0x24),0x24)*0.1f);
        break;
    }
    case 3: {
        f32 ease;
        s32 item, phase, pulse;
        AmmoDef *entry, *defs;
        u8 *mapping;
        s32 *counts;
        phase = g_game_time[0]%60;
        alpha=(f32)moby[0x23];
        ease=math_fast_sin_or_cos_a((f32)phase*0.104719676f-3.1415901f);
        pulse=FloatToInt(ease*5.0f+5.0f)+10;
        ApproachValue(&alpha,(f32)pulse,5.0f);
        moby[0x23]=FloatToInt(alpha);
        if (func_002A0558(moby,g_hero_moby)>=0.0f) goto reactivate;
        item=EI(vars,8);
        mapping=g_item_slot_to_record;
        counts=g_item_ammo_counts;
        defs=(AmmoDef *)g_weapon_table;
        entry=&defs[mapping[item]];
        if (counts[item]>=entry->max_ammo) break;
    reactivate:
        moby[0x20]=1;
        break;
    }
    case 4: {
        u8 *entry;
        entry=*(u8 **)(moby+0x24);
        EF(moby,0x2C)+=(EF(entry,0x24)-EF(moby,0x2C))*0.036000002f;
        if ((EF(entry,0x24)-EF(moby,0x2C))/EF(entry,0x24)<0.01f) {
            EF(moby,0x2C)=EF(entry,0x24);
            moby[0x20]=1;
            EI(moby,0x98)=EI(entry,0x10);
        }
        break;
    }
    }
}
