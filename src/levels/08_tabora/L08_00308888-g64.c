/*
 * func_L08_00308888: scripted level effects, one phase per D_L08_001BD800.phase.
 * Built with -G64 and gcse left on: the per-phase lui of the scene is reload
 * rematerializing PRE's spilled reaching register for %hi(D_L08_001BD800).
 */
#include "common.h"

typedef unsigned int u128 __attribute__((mode(TI)));

typedef struct TaboraParticleData {
    int pad00;
    int kind;
    short pad08;
    unsigned char alpha;
    unsigned char lifetime;
} TaboraParticleData;
typedef struct TaboraParticle {
    char pad00[3];
    unsigned char kind;
    char pad04[6];
    short lifetime;
    char pad0C[0x14];
    TaboraParticleData data;
} TaboraParticle;
typedef struct TaboraObject {
    char pad00[0x10];
    float position[4];
    char pad20[0x14];
    unsigned short flags;
    char pad36[0x32];
    char *vars;
    char pad6C[0x3E];
    short classId;
} TaboraObject;
typedef struct TaboraScene {
    char pad00[0x30];
    int phase;
    int frame;
    char pad38[0xC];
    short count;
    char pad46[0x146];
    TaboraObject *objects[0]; /* Variable-length actor list; only a prefix is described. */
} TaboraScene;
typedef struct TaboraEffectEntry {
    float position[4];
    int frame;
    float radius;
    float shake;
    int pad1C;
} TaboraEffectEntry;
typedef struct TaboraShake {
    char pad00[0x160];
    float amount0;
    int pad164;
    int duration0;
    int delay;
    float amount1;
    int pad174;
    int duration1;
    int pad17C;
    float amount2;
    int pad184;
    int duration2;
} TaboraShake;
extern TaboraScene g_tabora_scene;
extern TaboraShake g_hero_l08_extra_state;
extern float g_hero_position_vec[];
extern TaboraEffectEntry g_tabora_effect_entries[];
extern float g_cutscene_effect_offset[4] __attribute__((sda));
extern float g_cutscene_effect_directions[4][4] __attribute__((sda));
extern int g_current_map_index MACRO_ADDR;
extern int g_cutscene_effect_frame __attribute__((sda));
extern int g_frame_l08_counter MACRO_ADDR;
extern float g_tabora_rotation_angles[4] MACRO_ADDR;
extern float g_cutscene_rotation_speed_x __attribute__((sda));
extern float g_cutscene_rotation_speed_y, g_cutscene_rotation_speed_z, g_cutscene_rotation_speed_w;
extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(void *);
extern void math_store_angle_update_result(void *, void *, int, int, float);
extern void moby_copy_group_word_to_members(void);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern float FastAddRotations(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float math_fabs(float);
extern int FastTweenColor(int, int, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void vec_random_direction(void *, float, float);
extern void vec_add_random_offset(void *, float);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern TaboraParticle *SpawnSpinningSparkParticle(void *, float, float, float, int, void *, int, float, int);
extern void SpawnTintedEffects(int, void *, int, int, void *, int, int, float, float, float, float);
extern char *part_spawn_fading_drift(void *, void *, int, int, int, int, int, int, float, float, float);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);
extern unsigned char *part_spawn_fading(void *, int, int, int, int, int, int, float);

/* Runs the scripted effects of the Tabora cutscene: sparks, screen shake, and glowing rings that change with each phase of the scene. */
void tabora_cutscene_update_effects(void) {
    float vec_a[4] __attribute__((aligned(16)));
    float vec_b[4] __attribute__((aligned(16)));
    /* Adjacent in the frame: func_002833F0 fills all three as rows of one matrix. */
    float matrix[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float forward[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    anim_start_startup_animations();
    {
        int j = 0;
        TaboraObject *moby;
        for (; j < g_tabora_scene.count; ++j) {
            moby = g_tabora_scene.objects[j];
            if (moby && moby->classId==0xE29 /* moby class 3625 */) moby->flags |= 0x800;
            if (moby->classId==0xD54 /* moby class 3412 */) UpdateEquipmentPieces(moby);
            if (moby && moby->classId==MOBY_CLASS_TV_SCREENS && moby->vars)
            math_store_angle_update_result(moby,moby->vars+12,0x80AAAAD2,0x80396464,0.061086535f);
        }
    }
    if (g_current_map_index != 8) return;
    {
        if (g_tabora_scene.phase==0) {
            int j;
            moby_copy_group_word_to_members();
            for (j=0;j<4;++j) {
                TaboraEffectEntry *entry=&g_tabora_effect_entries[j];
                if (g_tabora_scene.frame==entry->frame) {
                    *(u128 *)vec_a=*(u128 *)entry->position;
                    FastVecAdd(vec_a,vec_a,g_cutscene_effect_offset);
                    SpawnExplosion(vec_a,0,25,20,20,20,45,1,1,1,0,0,entry->radius,20.0f);
                    if (entry->shake>0.0f) {
                        g_hero_l08_extra_state.duration0=55;
                        g_hero_l08_extra_state.duration2=70;
                        g_hero_l08_extra_state.delay=0;
                        g_hero_l08_extra_state.amount2=g_hero_l08_extra_state.amount0=entry->shake*0.08f;
                    }
                }
            }
        }
    }
    {
        if (g_tabora_scene.phase==1) moby_copy_group_word_to_members();
        if (g_tabora_scene.phase==2) {
            TaboraObject *moby;
            int burst_count;
            int i;
            int colour, life, alpha, spin, packed;
            TaboraParticle *particle;
            float scale, size, angle, frameStep;
            moby=0;
            moby_copy_group_word_to_members();
            burst_count=0;
            scale=1.0f;
            if (g_tabora_scene.frame==53) {moby=g_tabora_scene.objects[1];scale=0.7f;burst_count=30;}
            else if (g_tabora_scene.frame==58) {moby=g_tabora_scene.objects[0];burst_count=50;}
            if (moby) {
                *(u128 *)vec_a = 0;
                vec_a[2]=0.01f;
                vec_a[3]=1.0f;
                frameStep=0.008333334f;
                for (i=0;i<burst_count;++i) {
                    life=math_random_int_range(90,117);
                    qzero(vec_b);
                    vec_add_random_offset(vec_b,scale*0.7f);
                    vec_b[2]*=0.3f;
                    FastVecAdd(vec_b,vec_b,moby->position);
                    alpha=math_random_int_range(64,112);
                    colour=math_random_int_range(64,127);
                    packed=(alpha<<24)|(FloatToInt((float)colour*0.3f)<<16);
                    packed|=colour<<8;
                    colour|=packed;
                    angle=math_random_float_range(1.0f,1.013f);
                    spin=math_random_int_range(-2,2);
                    size=math_random_float_range(0.1f,0.3f);
                    vec_a[0]=math_random_signed_float_range(0.0f,0.011666667f);
                    vec_a[1]=math_random_signed_float_range(0.0f,0.011666667f);
                    vec_a[2]=math_random_float_range(frameStep*0.1f,0.008333334f);
                    FastVecScale(vec_a,vec_a,scale);
                    particle=SpawnSpinningSparkParticle(vec_b,0.1f,1.0f,angle,spin,vec_a,colour,size*210000.0f,0);
                    if (particle) {
                        TaboraParticleData *particleData=&particle->data;
                        if (math_random_int_below(2)) particle->kind=0x44;
                        particle->lifetime=life;
                        {
                            particleData->kind=2;
                            particleData->alpha=alpha;
                            particleData->lifetime=life;
                        }
                    }
                }
            }
        }
    }
    if (g_tabora_scene.phase==3 && g_tabora_scene.frame==g_cutscene_effect_frame) {
        TaboraObject *first=g_tabora_scene.objects[1];
        TaboraObject *second=g_tabora_scene.objects[2];
        qcopy(vec_a,second->position);
        vec_a[2]+=0.8f;
        FastVecSub(vec_b,first->position,second->position);
        vec_scale_to_length(vec_b,vec_b,0.035f);
        vec_b[2]=0.041666668f;
        SpawnTintedEffects(0,vec_a,40,0,vec_b,0x39969696,0,0.75f,1.3f,0.2f,0.37f);
        g_hero_l08_extra_state.amount2=0.047f;
        g_hero_l08_extra_state.duration2=35;
        g_hero_l08_extra_state.amount0=0.037f;
        g_hero_l08_extra_state.duration0=30;
        g_hero_l08_extra_state.amount1=0.04f;
        g_hero_l08_extra_state.duration1=20;
        g_hero_l08_extra_state.delay=0;
    }
    if (g_tabora_scene.phase==5) {
        g_tabora_scene.objects[2]->flags&=0xFBFF;
        g_tabora_scene.objects[3]->flags&=0xFBFF;
    }
    if (g_tabora_scene.phase!=7) return;
    if (g_tabora_scene.frame==0) {
        g_tabora_rotation_angles[0]=0;
        g_tabora_rotation_angles[1]=0;
        g_tabora_rotation_angles[2]=0;
    }
    if ((unsigned)(g_tabora_scene.frame-421)>=177) return;
    *(u128 *)vec_a=*(u128 *)g_tabora_scene.objects[3]->position;
    vec_a[2]+=0.5f;
    if (g_tabora_scene.frame<568) {
        int j;
        int spin;
        float size;
        g_tabora_rotation_angles[0]=FastAddRotations(g_tabora_rotation_angles[0],g_cutscene_rotation_speed_x*0.00029088824f);
        g_tabora_rotation_angles[1]=FastAddRotations(g_tabora_rotation_angles[1],g_cutscene_rotation_speed_y*0.00029088824f);
        g_tabora_rotation_angles[2]=FastAddRotations(g_tabora_rotation_angles[2],g_cutscene_rotation_speed_z*0.00029088824f);
        g_tabora_rotation_angles[3]=FastAddRotations(g_tabora_rotation_angles[3],g_cutscene_rotation_speed_w*0.00029088824f);
        euler_rotation_basis(matrix,g_tabora_rotation_angles);
        for(j=0;j<4;++j) {
            FastVecSub(start,g_hero_position_vec,vec_a);
            vec_scale_to_length(start,start,5.0f);
            FastVecAdd(end,start,vec_a);
            end[2]+=0.5f;
            spin=FloatToInt(math_random_signed_float_range(2.0f,5.0f));
            matrix_mul_vec3(direction,g_cutscene_effect_directions[j],matrix);
            vec_scale_to_length(direction,direction,3.5f);
            FastVecAdd(direction,direction,end);
            FastVecSub(vec_b,end,direction);
            vec_scale_to_length(vec_b,vec_b,0.058333337f);
            size=math_random_float_range(0.2f,0.32f);
            part_spawn_fading_drift(direction,vec_b,60,0x804080,spin,0,63,6,size*210000.0f,147000.0f,0.0f);
        }
    }
    if (g_tabora_scene.frame<=480) return;
    {
        float amount=6.0f;
        float rate=0.0f;
        float frameStep, timeScale, t, scale;
        float size;
        int alpha;
        int j;
        int duration, lifeStep;
        *(u128 *)vec_b=*(u128 *)vec_a;
        vec_b[2]+=1.0f;
        if (math_random_int_below(4)==0) {
            FastVecSub(forward,g_hero_position_vec,vec_b);
            timeScale=0.016666668f;
            frameStep=0.008333334f;
            vec_scale_to_length(forward,forward,5.0f);
            FastVecAdd(vec_b,forward,vec_b);
            vec_random_direction(matrix,rate,rate);
            size=(g_tabora_scene.frame-480);
            size*=0.06666667f;
            alpha=math_random_int_below(255)&255;
            duration=60;
            lifeStep=0;
            part_spawn_hero_relative(vec_b,matrix,0x50804080,duration,alpha,0,size);
            for (j=0;j<1;++j) {
                t=rate*timeScale;
                vec_random_direction(offset,t,t);
                FastVecAdd(matrix,matrix,offset);
                t=0.0f; /* Second set in the loop: keeps rate*timeScale from being hoisted and folded. */
                scale=amount*frameStep*(g_tabora_scene.frame-480);
                alpha=math_random_int_below(255)&255;
                part_spawn_hero_relative(vec_b,matrix,0x40804080,duration,alpha,0,scale);
                duration+=lifeStep;
            }
        }
    }
    vec_scale_to_length(direction,forward,0.1f);
    {
        int j, alpha, colour, full, value;
        float size;
        j=0;
        full=255;
        for (;j<=0;++j) {
            size=IntToFloat(full-((g_frame_l08_counter+j*20)&255));
            size=math_fabs(0.5f-size*0.003921569f);
            colour=FastTweenColor(0x40FF40FF,0x10FF40FF,size);
            alpha=(unsigned char)g_frame_l08_counter;
            if(j&2) alpha<<=1;
            if(j&1) alpha=full-alpha;
            value=alpha&255;
            size=(IntToFloat(j)+5.0f)*0.008333334f;
            size*=(g_tabora_scene.frame-480);
            part_spawn_fading(forward,colour,value,53,1,2,0,size);
            FastVecAdd(forward,forward,direction);
        }
    }
}
