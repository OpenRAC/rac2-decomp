/* Multi-stage switch: hero target clear keeps the candidate pointer a named local, read after its index. */
#include "common.h"
typedef struct { char pad[0x464]; unsigned char flags[0]; } L02E1A40Progress;
extern L02E1A40Progress g_cell_flags;
extern unsigned char g_moby_nibble_table[];
extern int g_current_map_index[] __attribute__((sda));
extern int currentLevel_gp SDATA(D_001A79F0);
typedef struct L02E1A40Object L02E1A40Object;
extern L02E1A40Object *g_moby_l02_pool[] __attribute__((sda));
extern L02E1A40Object *entityPool_gp SDATA(D_L02_001B359C);
extern char *g_platform_actor_ref[];

typedef struct {
    char pad0[0x24]; int message; int timer;
    char pad1[0x3c]; int disabled; short f6c; char pad2[4]; short f72;
} L02E1A40Hud;
extern L02E1A40Hud g_music_state;
extern float g_pickup_spin_speed SDATA(D_L02_001B0760);
extern float g_pickup_second_spin_speed SDATA(D_L02_001B0764);
extern float g_pickup_sparkle_size_range SDATA(D_L02_001B0768);
extern float D_L02_001B0768_abs[] __asm__("D_L02_001B0768") __attribute__((sda));
extern int g_pickup_sparkle_color_pair SDATA(D_L02_001B0770);
extern int D_L02_001B0770_abs[] __asm__("D_L02_001B0770") __attribute__((sda));
extern int g_pickup_init_done SDATA(D_L02_001B0778);
extern int g_pickup_color_a SDATA(D_L02_001B0780);
extern int D_L02_001B0780_abs[] __asm__("D_L02_001B0780") __attribute__((sda));
extern int g_pickup_color_b SDATA(D_L02_001B0788);
extern int D_L02_001B0788_abs[] __asm__("D_L02_001B0788") __attribute__((sda));
extern int g_frame_l02_counter[] __attribute__((sda));
extern void moby_set_flag_bit(void *,int);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *,int,int);
extern float FastAddRotations(float,float);
extern void gfx_add_draw_callback_first(void *,void *);
extern void DrawPulsingRingEffect(void *);
extern float ApproachValue(void *,float,float);
extern int math_random_int_below(int);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *,void *,void *);
extern float math_random_float_range(float,float);
extern int FastTweenColor(int,int,float);
extern int math_random_int_range(int,int);
extern void vec_clear_128(void *);
extern float IntToFloat(int);
extern void *part_spawn_hero_relative(void *,void *,int,float,int,int,int);
extern void hero_start_target_state(void *,int,float);
extern float vec_distance_xy(void *,void *),math_fabs(float);
extern int flag_set_first_pending(void *);
extern int PlayMobySound(int,int,char *);
extern void value_set_entry_by_index(int,int);
extern s32 snd_resume_music_stream(void);
typedef struct {
    int other, first, second; char pad0[8]; int auxiliary;
    float angle, angle2, fade; char pad1[4]; int color0, color1, alpha;
    char pad2[4]; int f38, f3c, count, message0, message1;
} L02E1A40Data;
struct L02E1A40Object {
    char pad0[0x10]; float position[4]; unsigned char state;
    char pad21[0x10]; unsigned char active; char pad32[0x36]; L02E1A40Data *data;
    char pad6c[0x2a]; unsigned short ticks; char pad98[0x1a]; unsigned short index;
    char padb4[0x44]; float radius; char padfc[4];
};
typedef struct { char pad[0x5c0]; L02E1A40Object *target; } L02E1A40Hero;
extern L02E1A40Hero g_hero_state;
#define I(p,o) (*(int *)((char *)(p)+(o)))
/* Runs a collectible that glows, reacts when the player reaches it, shows a message and saves its progress when it is done. */
void progress_pickup_update(L02E1A40Object *obj)
{
    float pos[4], vel[4];
    L02E1A40Data *d=obj->data;
    L02E1A40Object *other;
    unsigned short index;
    unsigned short completedIndex;
    int color, duration;
    int initialPacked, message0, message1;
    unsigned int ticks, savedByte;
    unsigned int frame;
    float angle, size, speed;
    unsigned char *save;
    switch(obj->state) {
    case 0:
        d->f38=0; d->f3c=0; d->count=0;
        index=obj->index;
        if(g_cell_flags.flags[(short)index] ||
           ((initialPacked=g_moby_nibble_table[((short)index>>1)+(g_current_map_index[0]<<10)]),
            (index&1) ? ((initialPacked>>4)&7) : (initialPacked&7))) {
            moby_set_flag_bit((g_moby_l02_pool[0]+d->first),1);
            moby_set_flag_bit((g_moby_l02_pool[0]+d->second),1);
            if(d->auxiliary!=-1) moby_mark_spawned(entityPool_gp+d->auxiliary);
            moby_set_state(obj,5,-1);
        } else moby_set_state(obj,1,-1);
        break;
    case 1:
        d->angle=FastAddRotations(d->angle,g_pickup_spin_speed*0.0002908882452175021f);
        gfx_add_draw_callback_first(DrawPulsingRingEffect,obj);
        if(d->fade!=0.0f) ApproachValue(&d->fade,0.0f,0.033333335f);
        if(obj->active && !math_random_int_below(5)) {
            angle=math_random_angle();
            pos[0]=math_fast_sin_or_cos_a(angle)*1.15f;
            pos[1]=math_fast_sin_or_cos_b(angle)*1.15f;
            pos[2]=0;
            FastVecAdd(pos,pos,obj->position);
            pos[2]+=0.1f;
            size=math_random_float_range(g_pickup_sparkle_size_range,D_L02_001B0768_abs[1]);
            color=FastTweenColor(g_pickup_sparkle_color_pair,D_L02_001B0770_abs[1],math_random_float_range(0,1));
            speed=math_random_float_range(1,2);
            duration=math_random_int_range(60,180);
            vec_clear_128(vel);
            vel[2]=speed/IntToFloat(duration);
            part_spawn_hero_relative(pos,vel,color,size,(unsigned char)duration,(unsigned char)math_random_int_below(255),0);
        }
        if(g_platform_actor_ref[0]==(char *)obj) {
            moby_set_state(obj,2,-1);
            if(!g_pickup_init_done) {
                g_pickup_init_done=1;
                hero_start_target_state(obj->position,1,obj->radius);
            }
        } else {
            other=(g_moby_l02_pool[0]+d->other);
            if(vec_distance_xy(obj->position,other->position)<1.5f && math_fabs(obj->position[2]-other->position[2])<0.5f)
                moby_set_state(obj,3,-1);
        }
        break;
    case 2:
        if(flag_set_first_pending(obj)) {
            PlayMobySound(1,0,(char *)obj);
            d->color0=g_pickup_color_a;
            d->color1=D_L02_001B0780_abs[1];
            d->fade=0;d->alpha=0;
            value_set_entry_by_index(0x27cb,180);
            if(!g_music_state.disabled && g_music_state.message==-1) {
                message0=d->message0;
                g_music_state.timer=0;
                g_music_state.message=(message0&0x3fff)+2000;
            }
        }
        if(g_platform_actor_ref[0]!=(char *)obj) moby_set_state(obj,1,-1);
        d->angle=FastAddRotations(d->angle,g_pickup_spin_speed*0.0002908882452175021f);
        angle=FastAddRotations(d->angle2,g_pickup_second_spin_speed*0.0002908882452175021f);
        frame=g_frame_l02_counter[0];
        d->angle2=angle;
        if((frame&1) && d->alpha<255) d->alpha++;
        gfx_add_draw_callback_first(DrawPulsingRingEffect,obj);
        ApproachValue(&d->fade,1,0.033333335f);
        break;
    case 3:
        if(flag_set_first_pending(obj)) {
            I(d,0x40)++;
            d->color0=g_pickup_color_b;
            d->color1=D_L02_001B0788_abs[1];
            d->fade=0;d->alpha=0;
            value_set_entry_by_index(0x27cc,180);
            message1=d->message1;
            g_music_state.timer=0;
            g_music_state.message=(message1&0x3fff)+2000;
        }
        ticks = obj->ticks;
        obj->ticks = ticks + 1;
        if(ticks>180) moby_set_state(obj,4,-1);
        else if(obj->ticks>60) {
{ L02E1A40Object *candidate; int i=d->other; candidate=g_moby_l02_pool[0]+i; if(g_hero_state.target==candidate) g_hero_state.target=0; }
            moby_set_flag_bit((g_moby_l02_pool[0]+d->first),1);
            moby_set_flag_bit((g_moby_l02_pool[0]+d->second),1);
        }
        d->angle=FastAddRotations(d->angle,g_pickup_spin_speed*0.0002908882452175021f);
        angle=FastAddRotations(d->angle2,g_pickup_second_spin_speed*0.0002908882452175021f);
        frame=g_frame_l02_counter[0];
        d->angle2=angle;
        if((frame&1) && d->alpha<255) d->alpha++;
        gfx_add_draw_callback_first(DrawPulsingRingEffect,obj);
        ApproachValue(&d->fade,1,0.033333335f);
        break;
    case 4:
        gfx_add_draw_callback_first(DrawPulsingRingEffect,obj);
        ApproachValue(&d->fade,0,0.033333335f);
        if(d->fade<=0) {
            completedIndex=obj->index;
            if(completedIndex&1) {
                save=&g_moby_nibble_table[((short)completedIndex>>1)+(currentLevel_gp<<10)];
                savedByte=*save;
                if(((savedByte>>4)&7)!=7) *save=savedByte+16;
            } else {
                save=&g_moby_nibble_table[((short)completedIndex>>1)+(currentLevel_gp<<10)];
                savedByte=*save;
                if((savedByte&7)!=7) *save=savedByte+1;
            }
            moby_set_state(obj,5,-1);
        }
        break;
    }
    if(g_music_state.f72==3 && g_music_state.f6c<6000) snd_resume_music_stream();
}
