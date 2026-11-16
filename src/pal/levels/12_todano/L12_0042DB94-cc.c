#include "names.h"
/* func_PAL_L12_0042DB94, the PAL copy of func_L12_004285A8: the same C, where rename func_002A96A0 becomes func_PAL_002AA108; rename func_002AB800 becomes func_PAL_002AC290; rename func_002B0A18 becomes func_PAL_002B1588; rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_L12_00429610 becomes func_PAL_L12_0042EC00; rename func_L12_004293A0 becomes func_PAL_L12_0042E990; rename func_L00_0032A258 becomes func_PAL_L00_0032C328; rename func_L00_00326110 becomes func_PAL_L00_003281C0; rename func_002B0A68 becomes func_PAL_002B15D8; rename func_002AB8C0 becomes func_PAL_002AC3C0. */
#include "common.h"
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern void timed_explosion_debris_update(void *);
extern void part_spawn_masked_debris_pal(void *,s32,void *,f32,f32,f32,f32,s32);
extern f32 coll_probe_ground_height_below(void *, s32, f32);
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern f32 moby_update_aim_target_strength_pal(void *, void *);
extern void gfx_start_color_fade_pal(void *, void *), gfx_update_color_fade_pal(void *, void *);
extern void moby_set_state(void *, s32, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern s32 snd_play_from_global_bank(s32, u32, void *);
extern void snd_stop_voice(s32);
extern void value_set_entry_by_index_pal(s32, s32);
extern s32 flag_set_first_pending(void *), math_fast_float_d(void *);
extern void *SpawnExplosion_pal(void *,s32,s32,s32,s32,s32,s32,s32,f32,f32,s32,s32,s32,s32);
extern void moby_compute_local_point(void *,void *,f32,f32,f32);
extern s32 coll_sweep_from_object(void *,f32,void *,s32,f32,f32,s32,s32,s32);
extern void part_spawn_three_sparks_pal(void *), part_l12_spawn_spark_spray_pal(void *,s32);
extern f32 vec_distance_xy(void *,void *);
extern void moby_set_flag_bit(void *,s32);
extern void part_explode_object_into_pieces_pal(void *,void *,void *,void *,s32,s32,s32,s32,s32,s32,void *);
extern void part_spawn_scaled_bolts_pal(void *,s32,f32);
extern void FastVecAdd(void *,void *,void *), FastVecScale(void *,void *,f32), euler_rotation_basis(void *,void *);
extern u8 *CreateMoby(s32);
extern void moby_mark_spawned(void *);
extern u8 g_sound_state[], g_hero_position[];
extern u8 g_item_enabled_flags[] __attribute__((sda));
typedef struct {
    u8 pad[0x160];
    f32 value160;
    s32 value164, value168, value16c;
    u8 gap[0x10];
    f32 value180;
    s32 value184, value188;
} L12EffectState;
extern L12EffectState g_hero_state_copy_a;
extern s32 g_flying_boss_piece_counter, g_scene_trigger_flag;
extern u8 *g_moby_l12_list_end, *g_moby_list_start;
extern u8 g_explosion_piece_table_a __attribute__((sda)), g_explosion_piece_table_b __attribute__((sda)), g_explosion_piece_table_c __attribute__((sda));
extern s32 g_explosion_piece_effect __attribute__((sda));
extern f32 g_flying_boss_vec_scales[4] __attribute__((sda));
extern s32 g_flying_boss_debris_ids[4] __attribute__((sda));
typedef struct { u8 pad[0x74]; u8 active; u8 gap[0x13]; u8 *owner; } L12Sound;
/* Updates a boss-like flying object. It has health, takes hits, goes through a set of moves, drops down and finally breaks into pieces (PAL: 50 Hz timings). */
void flying_boss_update_pal(u8 *self) {
    typedef u32 Q __attribute__((mode(TI)));
    union { Q q; f32 f[4]; } posv, vecv;
#define pos posv.f
#define vec vecv.f
    u8 *vars = P(self,0x68), *other;
    f32 damage;
    s32 count;
    switch (self[0x20]) {
    case 0:
        H(vars,0x24)=100;
        F(vars,0x20)=100.0f;
        F(vars,0x70)=F(self,0x18)+50.0f;
        F(vars,0x7c)=coll_probe_ground_height_below(self+0x10,0,0.5f);
        I(vars,0x80)=-1;
        g_flying_boss_piece_counter=0;
        moby_set_state(self,1,-1);
        break;
    case 1: {
        s32 i;
        damage=moby_update_aim_target_strength_pal(self,part_find_owned_effect_slot(self,0x230000,0));
        if (damage>0.0f) {
            vars[0x57]=255; vars[0x58]=128; vars[0x59]=128;
            gfx_start_color_fade_pal(self,vars+0x50);
            F(vars,0x20)-=damage;
        }
        if (F(vars,0x20)<0.0f) {
            u8 *other;
            count=0;
            for (other=g_moby_list_start;other<g_moby_l12_list_end;other+=0x100)
                if (*(s16 *)(other+0xaa)==*(s16 *)(self+0xaa) && other[0x20]<2 && other!=self) count++;
            if (!count && !g_item_enabled_flags[9]) {
                g_item_enabled_flags[9]=1;
                snd_play_from_global_bank(1,0,0);
                value_set_entry_by_index_pal(0x1233,-1);
                g_scene_trigger_flag=1;
            }
            i=g_flying_boss_piece_counter;
            if (i==0) moby_set_state(self,2,-1);
            else if (i==1) moby_set_state(self,7,-1);
            else if (i==2) moby_set_state(self,3,-1);
            else if (i==3) moby_set_state(self,4,-1);
            else moby_set_state(self,7,-1);
            g_flying_boss_piece_counter++;
        }
        self[0xa8]=255;
        break;
    }
    case 2: {
        s32 i;
        if (flag_set_first_pending(self)) {
            I(self,0x98)=0;
            SpawnExplosion_pal(self+0x10,1,20,20,20,20,20,0,2.5f,20.0f,1,1,1,0);
            PlayMobySound(0,0,self);
        }
        F(self,0xf0)+=F(vars,0x64);
        F(vars,0x64)+=0.00031415932f;
        if (F(self,0xf0)>0.7853982448577881f) {
            for (i=0;i<8;i++) {
                moby_compute_local_point(self,pos,0.0f,0.0f,(f32)i*2.033750057220459f);
                coll_sweep_from_object(self,1.2f,pos,0x30008,12.0f,1.0f,0,1,0);
            }
        }
        if (F(self,0xf0)>1.431170105934143f) {
            g_hero_state_copy_a.value180=0.2f; g_hero_state_copy_a.value188=75;
            g_hero_state_copy_a.value160=0.2f; g_hero_state_copy_a.value168=50; g_hero_state_copy_a.value16c=0;
            moby_set_state(self,8,-1);
        }
        break;
    }
    case 4:
        if (flag_set_first_pending(self)) {
            I(vars,0x68)=217; I(vars,0x6c)=0;
            g_hero_state_copy_a.value180=0.1f; g_hero_state_copy_a.value188=75;
            g_hero_state_copy_a.value160=0.2f; g_hero_state_copy_a.value168=50; g_hero_state_copy_a.value16c=0;
            self[0x30]=255;
        }
        part_l12_spawn_spark_spray_pal(self,0);
        {
            L12Sound *slot=(L12Sound *)(g_sound_state+I(vars,0x80)*0x70);
            if (slot->owner!=self || !slot->active) I(vars,0x80)=PlayMobySound(3,4,self);
        }
        if (!math_fast_float_d(vars+0x68) && I(vars,0x68)<183) part_spawn_three_sparks_pal(self);
        F(self,0x18)+=F(vars,0x6c); F(vars,0x6c)+=0.00032000002f;
        if (F(self,0x18)>F(vars,0x70) && !self[0x31]) {
            if (I(vars,0x80)!=-1) {
                {
                    L12Sound *slot=(L12Sound *)(g_sound_state+I(vars,0x80)*0x70);
                    if (slot->owner==self && slot->active) snd_stop_voice(I(vars,0x80));
                }
            }
            I(vars,0x80)=-1;
            moby_set_state(self,5,-1);
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) {
            I(vars,0x68)=150; I(vars,0x6c)=0;
            g_hero_state_copy_a.value180=0.1f; g_hero_state_copy_a.value188=75;
            g_hero_state_copy_a.value160=0.2f; g_hero_state_copy_a.value168=50; g_hero_state_copy_a.value16c=0;
        }
        if (I(vars,0x68)) {
            {
                L12Sound *slot=(L12Sound *)(g_sound_state+I(vars,0x80)*0x70);
                if (slot->owner!=self || !slot->active) I(vars,0x80)=PlayMobySound(3,4,self);
            }
            part_l12_spawn_spark_spray_pal(self,0);
            if (!math_fast_float_d(vars+0x68) && I(vars,0x68)<117) part_spawn_three_sparks_pal(self);
            F(self,0x18)+=F(vars,0x6c); F(vars,0x6c)+=0.00032000002f;
        } else {
            if (I(vars,0x80)!=-1) {
                {
                    L12Sound *slot=(L12Sound *)(g_sound_state+I(vars,0x80)*0x70);
                    if (slot->owner==self && slot->active) snd_stop_voice(I(vars,0x80));
                }
            }
            I(vars,0x80)=-1;
            F(self,0x18)+=F(vars,0x6c); F(vars,0x6c)-=0.00392f;
            if (F(self,0x18)<F(vars,0x7c)) moby_set_state(self,8,-1);
        }
        break;
    case 5: {
        u8 *other;
        other=g_moby_list_start+(I(vars,0x74)<<8);
        if (other && other[0x20]!=254 && other[0x20]!=253) {
            if (vec_distance_xy(other+0x10,g_hero_position)<45.0f && other[0x31]) {
                H(self,0x34)=(H(self,0x34)&0xffbe)|0x1000;
                I(self,0x98)=I(P(self,0x24),0x10);
                F(vars,0x78)=F(other,0x18);
                qcopy(self+0x10,other+0x10);
                F(self,0x18)+=60.0f; F(self,0xf0)=3.1415927410125732f;
                F(vars,0x6c)=-0.3f;
                moby_set_flag_bit(other,1);
                moby_set_state(self,6,-1);
                break;
            }
        }
        I(self,0x98)=0;
        H(self,0x34)=(H(self,0x34)|0x41)&0xefff;
        break;
    }
    case 6:
        vecv.q=0; vec[0]=F(self,0x10); vec[1]=F(self,0x14); vec[2]=F(vars,0x78);
        posv.q=vecv.q;
        F(self,0x18)+=F(vars,0x6c);
        {
            L12Sound *slot=(L12Sound *)(g_sound_state+I(vars,0x80)*0x70);
            if (slot->owner!=self || !slot->active) I(vars,0x80)=PlayMobySound(3,4,self);
        }
        if (F(self,0x18)<F(vars,0x78)+6.44f && (H(self,0x7c)&4)) {
            if (I(vars,0x80)!=-1) {
                {
                    L12Sound *slot=(L12Sound *)(g_sound_state+I(vars,0x80)*0x70);
                    if (slot->owner==self && slot->active) snd_stop_voice(I(vars,0x80));
                }
            }
            I(vars,0x80)=-1;
            SpawnExplosion_pal(pos,1,25,20,20,20,45,1,1.0f,20.0f,1,1,0,0);
            part_explode_object_into_pieces_pal(self,&g_explosion_piece_table_a,&g_explosion_piece_table_b,&g_explosion_piece_table_c,255,-1,g_explosion_piece_effect,15,4,255,timed_explosion_debris_update);
            part_spawn_scaled_bolts_pal(self,25,0.0f);
            moby_mark_spawned(self);
            return;
        }
        if (F(self,0x18)<F(vars,0x78)+11.2f && (H(self,0x7c)&2)) {
            SpawnExplosion_pal(pos,1,25,20,20,20,45,1,2.0f,20.0f,1,1,0,0);
            part_explode_object_into_pieces_pal(self,&g_explosion_piece_table_a,&g_explosion_piece_table_b,&g_explosion_piece_table_c,255,-1,g_explosion_piece_effect,15,2,255,timed_explosion_debris_update);
            H(self,0x7c)=0x8004;
        } else if (F(self,0x18)<F(vars,0x78)+16.27f && !H(self,0x7c)) {
            PlayMobySound(1,0,self);
            SpawnExplosion_pal(pos,1,25,20,20,20,45,1,3.0f,20.0f,1,1,0,0);
            part_explode_object_into_pieces_pal(self,&g_explosion_piece_table_a,&g_explosion_piece_table_b,&g_explosion_piece_table_c,255,-1,g_explosion_piece_effect,15,1,255,timed_explosion_debris_update);
            H(self,0x7c)=0x8006;
        } else {
        vecv.q=0; vec[2]=-12.27f;
        FastVecAdd(vec,self+0x10,vec);
        coll_sweep_from_object(self,4.0f,vec,0x10000,1000.0f,1.0f,0,1,0);
        }
        part_l12_spawn_spark_spray_pal(self,1);
        break;
    case 7:
        if (flag_set_first_pending(self)) PlayMobySound(4,0,self);
        qcopy(pos,self+0x10);
        SpawnExplosion_pal(pos,1,25,20,20,20,45,1,4.0f,20.0f,1,1,0,0);
        part_explode_object_into_pieces_pal(self,&g_explosion_piece_table_a,&g_explosion_piece_table_b,&g_explosion_piece_table_c,255,-1,g_explosion_piece_effect,15,255,255,timed_explosion_debris_update);
        part_spawn_scaled_bolts_pal(self,25,0.0f);
        moby_mark_spawned(self);
        return;
    case 8: {
        s32 i; u8 *other;
        for (i=0;i<3;i++) {
            other=CreateMoby(0x12e2-i);
            if (other) {
                FastVecScale(other+0x10,self+0xe0,g_flying_boss_vec_scales[i]);
                FastVecAdd(other+0x10,other+0x10,self+0x10);
                qcopy_nc(other+0xf0,self+0xf0);
                euler_rotation_basis(other+0xc0,self+0xf0);
                F(other,0x2c)=F(P(other,0x24),0x24)*(F(self,0x2c)/F(P(self,0x24),0x24));
                posv.q=0; pos[2]=0.16000001f;
                part_spawn_masked_debris_pal(other,g_flying_boss_debris_ids[i],pos,6.0f,12.0f,6.0f,12.0f,255);
                SpawnExplosion_pal(other+0x10,0,25,20,20,20,45,1,1.0f,20.0f,1,1,0,0);
                moby_mark_spawned(other);
            }
        }
        part_spawn_scaled_bolts_pal(self,25,0.0f);
        PlayMobySound(1,0,self);
        moby_mark_spawned(self);
        return;
    }
    }
    gfx_update_color_fade_pal(self,vars+0x50);
}
