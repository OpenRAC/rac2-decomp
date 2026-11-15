#include "common.h"
typedef struct {
    float position[4], previous[4], origin[4], target[4], velocity[4];
    u8 *object;
    float distance;
    int flags,color,effect,mode;
    float rate,spin,life;
    u8 pad74[12];
} L05Projectile;
extern L05Projectile D_L05_00221DD0[];
extern int D_L05_00221D10[];
extern void *D_L05_00225DD0[];
extern void (*D_L05_00225ED0[])(void *);
extern int D_L05_001A8F00;
extern int D_L05_001AC4D4 __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern u8 g_sound_state[];
typedef struct { u8 pad[0x160]; float slow; int pad164,frames,flags; } L05ImpactState;
extern L05ImpactState D_L05_001B9580;
typedef struct { int on; int pad; float pos[4]; } L05Hit;
extern L05Hit D_L05_001BFB18;
extern u8 D_L05_001A8F20[] MACRO_ADDR;
extern int level_get_saved_value(void);
extern char *moby_get_motion_data(u8 *);
extern float math_random_float_range(float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern float fast_vec_dist(void *,void *);
extern int math_random_int_below(int);
extern int snd_play_from_class_bank(int,int,char *,int);
extern void hero_apply_damage(float);
extern int math_fast_helper_a(void *,float);
extern int CollLine(void *,void *,int,void *,void *);
extern void EmitParticlePairBurst(void *,int,int,int);
extern void part_queue_impact_effect(void *,void *,int,void *,void *,float);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(void *,int,int,int,float,float,float);
extern void func_L05_0037D7D8(void *,void *,u32,int,float);
/* Update active object callbacks, then advance and resolve the projectile pool. */
void UpdateSpaceProjectilePool(void *unused)
{
    float step[4],check[4];
    float scale,speed,angle;
    u8 *state,*target,*sound;
    L05Projectile *record; float *pos;
    int i,j;
    (void)unused;
    if (D_L05_001A8F00 == 2) return;
    for (i=0;i<level_get_saved_value();i++) {
        if (D_L05_00225ED0[i]) D_L05_00225ED0[i](D_L05_00225DD0[i]);
    }
    for (j=0;j<128;j++) {
        unsigned int base = (unsigned int)D_L05_00221DD0;
        unsigned int offset = j * sizeof(L05Projectile);
        record = (L05Projectile *)(base + offset);
        if (!record->object) continue;
        pos = record->position;
        state = (u8 *)moby_get_motion_data(record->object);
        if (D_L05_00221D10[0x2C/4] == 1 || *(int *)(state+0x110) == 0 || record->distance >= 350.0f) {
            record->object = 0;
            continue;
        }
        scale = math_random_float_range(1.1f,0.6f);
        speed = record->life;
        vec_scale_to_length(step,record->velocity,scale*speed);
        FastVecAdd(record->position,record->position,step);
        FastVecAdd(record->previous,record->previous,step);
        record->distance += scale*speed;
        if (record->flags == 0 && record->mode && fast_vec_dist(record->position,*(u8 **)(state+0x120)+0x10) < record->rate) {
            D_L05_001B9580.frames = 30;
            D_L05_001B9580.slow = 0.05f;
            D_L05_001B9580.flags = 0;
            if (math_random_int_below(6) && (target=*(u8 **)(state+0x120)) && *(s16 *)(target+0xAA) == 0xFBF) {
                sound = g_sound_state+D_L05_001AC4D4*0x70;
                if ((*(u8 **)(sound+0x88) != target || !sound[0x74]) && g_current_map_index != 10)
                    D_L05_001AC4D4 = snd_play_from_class_bank(14,0,(char *)target,0xFBF);
            }
            hero_apply_damage(1.0f);
            record->flags = 1;
            record->object = 0;
        }
        if (record->effect && *(u8 **)(state+0x120) && fast_vec_dist(record->position,*(u8 **)(state+0x120)+0x10) < 32.0f) {
            qcopy(check, pos);
            check[3] = 1.0f;
            if (math_fast_helper_a(check,256.0f) != -1 && CollLine(record->previous,record->position,0,0,0)) {
                EmitParticlePairBurst(D_L05_001BFB18.pos,20,record->color,60);
                if (D_L05_001BFB18.on)
                    part_queue_impact_effect(*(u8 **)(state+0x120),record->object,0x10000,D_L05_001BFB18.pos,D_L05_001A8F20,0.25f);
                record->object = 0;
            }
        }
        angle = math_random_angle();
        gfx_draw_billboard_quad(record->position,0x31,record->color,1,0.35f,0.0f,angle);
        func_L05_0037D7D8(record->position,record->previous,0x807F7F7F,14,record->spin*0.05f);
        func_L05_0037D7D8(record->position,record->previous,record->color,14,record->spin*0.1f);
    }
}
