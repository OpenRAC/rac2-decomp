#include "common.h"

/* func_PAL_L00_003C7B10, the PAL copy of func_L00_003C3D90: the same C, where the timer reload and the
   ratio's divisor, the particle id, the lock timer and the ribbon timer take the 50 Hz scale
   ((x) * 5 + 2) / 6, and the upgrade threshold 23 becomes 19.
   Per-frame update of an electric-arc effect moby (both oclass 0xA5C and 0x1192):
   sound upkeep, colour fade, eight particle pairs, area damage, target locking and five ribbon arcs.
   Its own unit for -G8, -g (the nop pair before the ratio's div.s) and -frac2-mult-add-no-flatten (the
   ribbon point givs); flags in config/cflags.txt. */
extern int g_game_l00_mode;
extern char g_hero_position[];
extern char g_sound_state[];
extern unsigned char g_item_slot_to_record[];
typedef struct { char pad0[4]; unsigned char active; char pad5[0x6b]; float strength; char pad74[0x6c]; } WeaponEntry;
extern WeaponEntry g_weapon_l00_table[];
typedef struct { char pad[0xb4]; int changed; } ChangedState;
extern ChangedState g_help_entry_state;
typedef struct { char pad0[0x80]; float position[4]; char pad90[0x11b0]; int upgrades; char pad1244[0x104c]; char *moby; char pad2294[0x28]; unsigned char busy; } HeroState;
extern HeroState D_00189E20_13;
extern char g_camera_l00_position[];
typedef struct { float v[4]; } __attribute__((aligned(16))) EffectVector;
extern EffectVector g_tesla_barrier_points[][10];
extern EffectVector D_L00_00240080_1[][10];
extern int g_tesla_barrier_effects[] MACRO_ADDR;
extern int g_tesla_barrier_timers[] MACRO_ADDR;
/* Ribbon state, one short per ribbon in three parallel arrays (as upstream's L25 tether declares
   its D_L25_001B2948/2950/2958): respawn timer, fade and the timer's starting value. */
extern short g_tesla_ribbon_ids[] MACRO_ADDR;
extern short g_electric_ribbon_alphas[] MACRO_ADDR;
extern short g_electric_ribbon_lengths[] MACRO_ADDR;

typedef struct { char pad[0xf8]; unsigned char *f8; } ParticleDefs;
extern ParticleDefs g_effect_definitions;
extern int g_trail_owner __attribute__((sda));
extern int g_tesla_hit_counter __attribute__((sda));
extern int g_tesla_timer_length __attribute__((sda));
extern int g_tesla_barrier_color_a __attribute__((sda));
extern int g_tesla_barrier_color_b __attribute__((sda));
extern int g_tesla_barrier_alt_color_a __attribute__((sda));
extern int g_tesla_barrier_alt_color_b __attribute__((sda));
extern int g_tesla_arc_param __attribute__((sda));
extern float g_glow_sphere_scale __attribute__((sda));
extern float g_tesla_hit_damage __attribute__((sda));
extern float g_trail_effect_length __attribute__((sda));
extern int g_tesla_sound_id_min __attribute__((sda));
extern int g_tesla_sound_id_max __attribute__((sda));
extern float g_tesla_effect_size __attribute__((sda));
extern int g_tesla_effect_color __attribute__((sda));
/* Ribbon spread: D_L00_001AFF7C in most levels, 0x001AFF80 in 00_aranos_tutorial. */
extern float ref_L00_003C3D90_00 __attribute__((sda));
extern void fade_tick_timer(void);
extern int snd_is_voice_playing_for_owner(void *,int);
extern int PlayMobySound(int,int,void *);
extern void snd_stop_voice(int);
extern unsigned char *CreateTrailOwnerMoby_pal(int);
extern float fade_get_value(void);
extern int weapon_can_use_held(float);
extern void fade_reset_level(void);
extern void moby_mark_spawned(void *);
extern float math_fabs(float);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern int FastTweenColor(float,int,int);
extern int FastDecTimer(void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern int math_random_int_range(int,int);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *,float,float,float);
extern char *part_spawn_bluish_fade(void *,int,int,int);
extern int math_fast_float_d(void *);
extern int vec_fast_helper_b(void *);
extern int coll_process_hit(void *,int,void *,int,float);
extern float *moby_get_private_value_0(void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecSub(void *,void *,void *);
extern void QueueMobyImpact(void *,void *);
extern void part_l00_spawn_spark_pairs_2_pal(void *,int);
extern char *lightning_arc_spawn_pal(void *,int);
extern void part_spawn_random_direction_effect(void *,float,float);
extern float math_random_float_range(float,float);
extern void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern void gfx_add_draw_callback_first(void *,void *);
extern void trail_effect_update_draw(void *);
typedef struct { char pad0[0x46]; short category; } MobyInfo;
typedef struct EffectContext EffectContext;
typedef struct Moby { char pad0[0x10]; float x,y,z,w; unsigned char state; char pad21[3]; MobyInfo *info; char pad28[9]; unsigned char enabled; char pad32[0x68-0x32]; EffectContext *ctx; char pad6c[0xaa-0x6c]; short oclass; char padac[0xe0-0xac]; float forward[4]; } Moby;
typedef struct { char pad0[4]; Moby *moby; char pad8[8]; float dx,dy,dz; } ParticleOwner;
typedef struct { char pad0[2]; unsigned char sprite; char pad3; int colour; char pad8[4]; float size; float x,y,z; char pad1c[4]; ParticleOwner owner; char pad3c[0xb8-0x3c]; Moby *source; } Particle;
typedef struct { float x,y,z; float damage; Moby *source; int flags; unsigned char kind; unsigned char mode; short oclass; float strength; int one; char pad24[0xc]; } HitPacket;
struct EffectContext { float value; short timer; short pad6; int colour; int sound; float cooldown; int lock; short timers[4]; Moby *targets[4]; };
extern Moby *g_area_hit_targets[];
/* A sound slot as src/game/002B6120-sound-g8.c views it: D_00188660 + slot * 0x70. */
typedef struct { char pad0[0x74]; unsigned char active; char pad75[0x13]; Moby *object; } SoundAnchor;
static __inline__ void clearSound(Moby *self,EffectContext *ctx)
{
    int id=ctx->sound;
    if(id!=-1) {
        SoundAnchor *sound=(SoundAnchor *)(g_sound_state+id*0x70);
        if(sound->object==self && sound->active)
            snd_stop_voice(id);
    }
    ctx->sound=-1;
}
void tesla_barrier_update_pal(Moby *self)
{
    float offset[4],origin[4],position[4];
    EffectContext *ctx=self->ctx;
    float value,ratio,sign;
    int i,j,k,slot;
    if(g_game_l00_mode) return;
    qcopy(&self->x,g_hero_position);
    fade_tick_timer();
    if(!g_game_l00_mode) {
        if(!snd_is_voice_playing_for_owner(self,ctx->sound))
            ctx->sound=PlayMobySound(3,4,self);
    } else if(snd_is_voice_playing_for_owner(self,ctx->sound)) clearSound(self,ctx);
    if(g_weapon_l00_table[g_item_slot_to_record[0x2d]].active && self->oclass==0xa5c) {
        int saved=g_trail_owner;
        g_trail_owner=0;
        if(CreateTrailOwnerMoby_pal(1)) {
            clearSound(self,ctx);
            PlayMobySound(2,0,self);
            g_trail_owner=0;
            moby_mark_spawned(self);
            return;
        }
        g_trail_owner=saved;
    }
    value=fade_get_value();
    if(!weapon_can_use_held(value) || g_tesla_hit_counter==40) {
        clearSound(self,ctx);
        g_tesla_hit_counter=0;
        fade_reset_level();
        PlayMobySound(2,0,self);
        g_trail_owner=0;
        moby_mark_spawned(self);
        return;
    }
    if(value!=ctx->value) {
        g_help_entry_state.changed+=FloatToInt(math_fabs(ctx->value-value));
        ctx->value=value;
        ctx->timer=((int)(g_tesla_timer_length) * 5 + 2) / 6;
    }
    ratio=IntToFloat(ctx->timer)/IntToFloat(((int)(g_tesla_timer_length) * 5 + 2) / 6);
    if(self->oclass==0xa5c) ctx->colour=FastTweenColor(ratio,g_tesla_barrier_color_a,g_tesla_barrier_color_b);
    else ctx->colour=FastTweenColor(ratio,g_tesla_barrier_alt_color_a,g_tesla_barrier_alt_color_b);
    FastDecTimer(&ctx->timer);
    FastVecScale(offset,D_00189E20_13.moby+0xe0,0.75f);
    FastVecAdd(&self->x,D_00189E20_13.position,offset);
    moby_transform_joint_to_world(D_00189E20_13.moby,10,origin);
    for(i=0;i<8;i++) {
        if(!g_tesla_barrier_effects[i]) {
            Particle *effect;
            int id=((int)(math_random_int_range(g_tesla_sound_id_min,g_tesla_sound_id_max)) * 5 + 2) / 6;
            value=math_random_angle();
            ratio=math_random_angle();
            vec_build_spherical_offset(position,g_trail_effect_length,value,ratio);
            FastVecAdd(position,position,origin);
            effect=(Particle *)(g_tesla_barrier_effects[i]=(int)part_spawn_bluish_fade(position,id,2,1));
            if(effect) {
                ParticleOwner *sub=&effect->owner;
                sub->dx=effect->x-self->x;
                sub->dy=effect->y-self->y;
                sub->dz=effect->z-self->z;
                sub->moby=self;
                effect->colour=g_tesla_effect_color|ctx->colour;
                effect->size=g_tesla_effect_size*210000.0f;
                effect->sprite=g_effect_definitions.f8[1];
                g_tesla_barrier_timers[i]=id;
            }
            effect=(Particle *)part_spawn_bluish_fade(position,id,2,1);
            if(effect) {
                ParticleOwner *sub=&effect->owner;
                sub->dx=effect->x-self->x;
                sub->dy=effect->y-self->y;
                sub->dz=effect->z-self->z;
                sub->moby=self;
                effect->colour=0x307f7f7f;
                effect->size=g_tesla_effect_size*63000.00390625f;
                effect->sprite=g_effect_definitions.f8[1];
            }
        } else if(math_fast_float_d(g_tesla_barrier_timers+i)) g_tesla_barrier_effects[i]=0;
    }
    slot=0;
    math_fast_float_d(&ctx->lock);
    {
    int t;
    for(t=0;t<4;t++) if(FastDecTimer(&ctx->timers[t])) {
        ctx->targets[t]=0;
        slot=t;
    }
    }
    if(vec_fast_helper_b(&ctx->cooldown)) {
        int count=coll_process_hit(&self->x,1,D_00189E20_13.moby,0,g_glow_sphere_scale*0.3f);
        if(count) {
            HitPacket packet;
            float scaled[4],output[4];
            int p;
            WeaponEntry *weapon=&g_weapon_l00_table[g_item_slot_to_record[0x2d]];
            packet.flags=65536;
            packet.one=1;
            packet.damage=5627.9248046875f;
            packet.kind=3;
            packet.strength=weapon->strength;
            packet.mode=2;
            packet.oclass=self->oclass;
            packet.source=self;
            for(p=0;p<count;p++) {
                Moby *object=g_area_hit_targets[p];
                float *health=0;
                if(!object->enabled || !object || object->state==0xfe || object->state==0xfd || !object->info || object->info->category!=5) continue;
                health=moby_get_private_value_0(object);
                if(health) {
                    if(health[0]<=0) continue;
                    FastVecScale(scaled,self->forward,health[4]);
                    FastVecAdd(position,&object->x,scaled);
                } else qcopy(position,&object->x);
                FastVecSub(&packet,position,&self->x);
                vec_scale_to_length(&packet,&packet,1.0f);
                QueueMobyImpact(object,&packet);
                FastVecScale(scaled,&packet,g_glow_sphere_scale*0.3f);
                FastVecAdd(output,&self->x,scaled);
                part_l00_spawn_spark_pairs_2_pal(output,ctx->colour);
                ctx->cooldown=0.5f;
            }
        }
    }
    if(!g_game_l00_mode && slot && self->oclass==0x1192 && !ctx->lock && !D_00189E20_13.busy && D_00189E20_13.upgrades>=19) {
        int hits=coll_process_hit(&self->x,1,D_00189E20_13.moby,0,g_tesla_hit_damage);
        if(hits) for(j=0;j<hits;j++) {
            float *health=0;
            int freeSlot;
            if(!g_area_hit_targets[j]->enabled || !g_area_hit_targets[j] || g_area_hit_targets[j]->state==0xfe || g_area_hit_targets[j]->state==0xfd || !g_area_hit_targets[j]->info || g_area_hit_targets[j]->info->category!=5) continue;
            health=moby_get_private_value_0(g_area_hit_targets[j]);
            if(health && health[0]<=0) continue;
            freeSlot=-1;
            /* ctx->targets[k] through the byte offset k << 2: retail forms ctx + (k << 2) first. */
            for(k=0;k<4 && g_area_hit_targets[j]!=((Moby **)((char *)ctx+(k<<2)))[8];k++) {
                if(!((Moby **)((char *)ctx+(k<<2)))[8]) freeSlot=k;
            }
            if(k==4) {
                Particle *effect;
                Moby *object;
                if(freeSlot<0) break;
                object=g_area_hit_targets[j];
                ((Moby **)((char *)ctx+(freeSlot<<2)))[8]=object;
                effect=(Particle *)lightning_arc_spawn_pal(object,g_tesla_arc_param);
                if(effect) {
                    effect->source=self;
                    g_tesla_hit_counter++;
                    PlayMobySound(5,0,self);
                    ctx->timers[slot]=((int)(math_random_int_range(20,60)) * 5 + 2) / 6;
                }
                break;
            }
        }
    }
    qcopy(position,origin);
    {
    int r;
    for(r=0;r<5;r++) {
        if(FastDecTimer(&g_tesla_ribbon_ids[r])) g_tesla_ribbon_ids[r]=0;
        if(!g_tesla_ribbon_ids[r]) {
            float velocity[4],scaled[4];
            int id=((int)(math_random_int_range(3,45)) * 5 + 2) / 6;
            g_tesla_ribbon_ids[r]=id;
            g_electric_ribbon_lengths[r]=id;
            g_electric_ribbon_alphas[r]=64;
            part_spawn_random_direction_effect(velocity,ref_L00_003C3D90_00,ref_L00_003C3D90_00);
            qcopy(g_tesla_barrier_points[r],position);
            g_tesla_barrier_points[r]->v[3]=0.04f;
            sign=1.0f;
            {
            int n;
            for(n=1;n<10;n++) {
                float width=0.04f;
                FastVecSub(scaled,D_L00_00240080_1[r][n-1].v,g_camera_l00_position);
                math_apply_axis_rotation_to_quat(velocity,velocity,scaled,math_random_float_range(0.0872664749622345f,1.3089970350265503f)*sign);
                sign=-sign;
                FastVecAdd(g_tesla_barrier_points[r][n].v,D_L00_00240080_1[r][n-1].v,velocity);
                g_tesla_barrier_points[r][n].v[3]=width;
            }
            }
        }
    }
    }
    gfx_add_draw_callback_first(trail_effect_update_draw,self);
}
