#include "include_asm.h"

#include "common.h"
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
typedef int TI4BF0 __attribute__((mode(TI)));
typedef float Vec4BF0[4] __attribute__((aligned(16)));
typedef struct { char prefix[0x74]; float damage; char tail[0x68]; } Weapon4BF0;
extern Weapon4BF0 g_weapon_l00_table[] __attribute__((nosda));
extern unsigned char g_item_slot_to_record[];
typedef struct { char pad[0x2290]; char *target; } Hero4BF0;
extern Hero4BF0 g_hero_state;
typedef struct { char pad[0x160]; float amount; int unused, timer, state; } Camera4BF0;
extern Camera4BF0 g_scalar_transition_state;
extern char *g_blast_effect_records __attribute__((sda));
extern char *g_blast_l00_pool;
extern int *g_blast_l00_ripple_particles[] MACRO_ADDR;
extern float g_blast_uv_scroll_u __attribute__((sda));
extern float g_blast_uv_scroll_v __attribute__((sda));
extern char *D_L00_001B2B50_1 MACRO_ADDR;
extern char *g_area_hit_targets[];
extern int save_is_record_value(short,int);
extern void vec_transform_or_copy(void *,void *);
extern int AcquireEntitySlot(void *,int,void *);
extern char *level_get_slot_body(short,int);
extern int mem_align_size_16(int);
extern void cam_compute_view_direction(void *,void *,int);
extern void FastVecAdd(void *,void *,void *);
extern void part_spawn_explosion_with_sparks_pal(void *,void *,int,float,float);
extern void blast_init_effect_record(void *,int,void *,void *,float);
extern void part_spawn_blast_sparks_pal(void *,void *);
extern int math_fast_helper_a(void *,float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int coll_process_hit(void *,int,void *,int,float);
extern char *moby_get_private_value_0(void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void make_hit_descriptor(float,void *,void *,int,void *);
extern void QueueMobyImpact(void *,void *);
extern int StartAttachedEffect_pal(void *,int,int);
extern int math_fast_float_d(void *);
extern void blast_clear_state(void);
extern void moby_mark_spawned(void *);
extern void blast_update_effect_records(void *);
extern void ref_L00_003E4BF0_00(void (*)(void *),void *);
extern void mini_nuke_blast_draw(void *);
typedef struct { char pad[0x10]; float phase; int timer; float rate; int alpha, unused, count, handle; } State4BF0;

/* Updates the Mini-Nuke blast: it grows, hurts everything inside its radius, shakes the camera, then fades out and removes itself (PAL: 50 Hz timings). */
void mini_nuke_blast_update_pal(char *object)
{
    Vec4BF0 center, offset, query, direction;
    struct { Vec4BF0 point; char pad[8]; unsigned char type, flags; short id; int unused; int active; } hit;
    int allocation;
    int *timer;
    State4BF0 *data = *(State4BF0 **)(object+0x68);
    float scale;
    if (*(unsigned char *)(object+0x20) && !save_is_record_value(*(short *)(object+0xAA),data->handle)) goto destroy;
    vec_transform_or_copy(object+0x10,object+0x10);
    switch (*(unsigned char *)(object+0x20)) {
    case 0: {
        int i;
        char *mem;
        *(unsigned char *)(object+0x20)=1;
        data->phase=0;
        data->timer=17;
        data->rate=0.8000001f;
        data->alpha=127;
        data->count=111;
        data->handle=AcquireEntitySlot(object,0,&allocation);
        mem=level_get_slot_body(*(short *)(object+0xAA),data->handle);
        g_blast_effect_records=mem;
        g_blast_l00_pool=(char *)mem_align_size_16((int)(mem+0x50));
        g_blast_l00_ripple_particles[0]=(int *)mem_align_size_16((int)(g_blast_l00_pool+0xA000));
        i=0;
        do { g_blast_l00_ripple_particles[0][i]=0; i++; } while(i<144);
        { char *p = g_blast_l00_pool+319*128+124;
        for(i=319;i>=0;i--,p-=128) *(int *)p=0; }
        *(int *)(D_L00_001B2B50_1+0x30)=0;
        qcopy(center,object+0x10);
        cam_compute_view_direction(object+0x10,offset,1);
        FastVecAdd(center,object+0x10,offset);
        part_spawn_explosion_with_sparks_pal(object,center,-1,2.0f,20.0f);
        blast_init_effect_record(object,17,object+0x10,data,0.20000002f);
        part_spawn_blast_sparks_pal(object,object+0x10);
        qcopy(query,center);
        query[3]=2.0f;
        if(math_fast_helper_a(query,100.0f)!=-1) {
            g_scalar_transition_state.amount=0.45f;
            g_scalar_transition_state.timer=33;
            g_scalar_transition_state.state=0;
        }
    }
    case 1: {
        int count;
        int i;
        data->count-=5;
        if(data->count<0) data->count=0;
        data->phase+=data->rate;
        timer=&data->timer;
        scale=1.0f-IntToFloat(*timer)/IntToFloat(17);
        scale*=8.0f;
        count=coll_process_hit(object+0x10,0,object,0,scale+0.001f);
        for(i=0;i<count;i++) {
            if((moby_get_private_value_0(g_area_hit_targets[i]) || (*(unsigned short *)(g_area_hit_targets[i]+0x34)&0x4000)) && g_area_hit_targets[i]!=g_hero_state.target && *(short *)(g_area_hit_targets[i]+0xAA)!=0xA5A) {
                FastVecSub(direction,g_area_hit_targets[i]+0x10,object+0x10);
                vec_scale_to_length(direction,direction,1.0f);
                vec_scale_to_length(&hit,&hit,1.0f);
                make_hit_descriptor(((Weapon4BF0 *)((unsigned int)g_weapon_l00_table + g_item_slot_to_record[0x2A] * sizeof(Weapon4BF0)))->damage,&hit,object,0x830000,direction);
                *(TI4BF0 *)hit.point = *(TI4BF0 *)direction;
                hit.flags=3; hit.type=5; hit.active=1;
                hit.point[3]=5627.925f;
                hit.id=*(short *)(g_area_hit_targets[i]+0xAA);
                QueueMobyImpact(g_area_hit_targets[i],&hit);
                StartAttachedEffect_pal(g_area_hit_targets[i],71,*(int *)(object+0xB8));
            }
        }
        if(math_fast_float_d(timer)) {
            *(unsigned char *)(object+0x20)=2;
            data->timer=33;
        }
        break;
    }
    case 2:
        data->phase+=data->rate;
        scale=IntToFloat(data->timer)*0.025f;
        if(data->timer==20) part_spawn_blast_sparks_pal(object,object+0x10);
        if(math_fast_float_d(&data->timer)) {
            if(data->alpha) --data->alpha;
            else { data->alpha=0; *(unsigned char *)(object+0x20)=6; }
        } else data->alpha=FloatToInt(IntToFloat(127)*scale);
        break;
    case 6:
        data->rate-=0.020000001f;
        if(data->rate<0.10000001f) data->rate=0.10000001f;
        data->phase+=data->rate;
        if(!*(int *)(D_L00_001B2B50_1+0x38)) {
destroy:
            blast_clear_state();
            moby_mark_spawned(object); return;
        }
        break;
    }
    g_blast_uv_scroll_v-=0.04f;
    if(g_blast_uv_scroll_u < -8.0f) g_blast_uv_scroll_u+=8.0f;
    if(g_blast_uv_scroll_v < -8.0f) g_blast_uv_scroll_v+=8.0f;
    blast_update_effect_records(object);
    ref_L00_003E4BF0_00(mini_nuke_blast_draw,object);
}
