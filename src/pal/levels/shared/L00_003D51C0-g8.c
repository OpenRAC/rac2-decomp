#include "include_asm.h"

#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define S(p,o) (*(s16 *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern u8 g_item_slot_to_record[];
extern int g_item_ammo_counts[];
typedef struct {
    char pad_00[0x38]; s16 multiple_sound; s16 single_sound;
    char pad_3C[2]; s16 moby_class;
    char pad_40[0x4E]; u16 capacity;
    char pad_90[0x50];
} PickupResource;
extern PickupResource g_weapon_l00_table[];
typedef struct {
    char pad_00[0x20]; float axis[4];
    char pad_30[0x10]; float matrix[16];
    float position[4]; char pad_90[0x50]; float target[4];
    char pad_F0[0x60]; float motion[4];
    char pad_160[0x2162]; u8 override;
    char pad_22C3[0x1E1]; float range; float height;
    char pad_24AC[0x20]; int enabled;
} PickupPlayer;
extern char g_hero_state[];
#define PLAYER ((PickupPlayer *)D_00189E20)
extern int D_L00_001A8FF0[] __attribute__((sda));
extern int g_frame_l00_counter[] __attribute__((sda));
extern int D_L00_001B2ADC[] MACRO_ADDR;
extern void *g_hero_moby NOT_SDA;
extern void vec_store_helper(void *);
extern s32 func_PAL_00273A10(void *);
extern float fast_vec_dist(void *,void *);
extern int math_fast_float_d(void *);
extern float math_fabs(float);
extern float vec_distance_xy(void *,void *);
extern float gravity_get_center_distance(void *);
extern int weapon_add_ammo(int,int);
extern void func_PAL_L00_003282B0(int,int,int);
extern void moby_set_state(void *,int,int);
extern void vec_clear_128(void *);
extern int subtract_integer_with_clamp(int);
extern int PlayMobySound(int,int,void *);
extern void FastVecSub(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern f32 ApproachValue(void *,float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern float FastVecLength(void *);
extern void moby_mark_spawned(void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_set_direction_with_complement(void *,void *,float);
extern void quaternion_to_rotation_basis(void *,void *);
extern void multiply_matrix3x3(void *,void *,void *);
extern int vec_fast_helper_d(void *,void *);

void func_PAL_L00_003D51C0(char *m)
{
    char *d=*(char **)(m+0x68);
    PickupResource *e;
    int j,i,yes,changed,old,delta,sound;
    float speed,time,target_speed;
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16)));
    float v2[4] __attribute__((aligned(16)));
    float v3[4] __attribute__((aligned(16)));
    float v4[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    char matrix[48] __attribute__((aligned(16)));
    switch(B(m,0x20)) {
    case 0:
        B(m,0x20)=1;
        for(j=0;j<56;j++) {
            e=&g_weapon_l00_table[g_item_slot_to_record[j]];
            if(e->moby_class==S(m,0xaa))I(d,0x68)=j;
        }
        break;
    case 1:
        if(B(d,0x5c)==3 && (g_frame_l00_counter[0]&15)==(((int)m>>8)&15)) {
            qzero(d);vec_store_helper(d+0x10);B(d,0x5c)=0;
        }
        qcopy(a,d);
        func_PAL_00273A10(m);
        changed=0;
        if(fast_vec_dist(a,d)>F(d,0x48)*2.0f)changed=1;
        yes=1;
        if(B(d,0x5c)||changed) {
            if(math_fast_float_d(d+0x7c)) {
                if(math_fabs(F(m,0x18)-PLAYER->position[2])>PLAYER->height)yes=0;
                else if(vec_distance_xy(m+0x10,PLAYER->position)>PLAYER->range)yes=0;
            }
        } else {
            yes=0;
            if(math_fabs(F(m,0x18)-PLAYER->position[2])<PLAYER->height &&
               vec_distance_xy(m+0x10,PLAYER->position)<PLAYER->range)I(d,0x7c)=3;
        }
        if(g_item_ammo_counts[I(d,0x68)] >=
           ((PickupResource *)(g_item_slot_to_record[I(d,0x68)] * 224 + (unsigned int)g_weapon_l00_table))->capacity)yes=0;
        if(D_L00_001A8FF0[0]) {
            if(gravity_get_center_distance(m+0x10)<F(d,0x78)-2.0f)goto force_pickup;
        } else if(F(m,0x18)<F(d,0x78)-2.0f)goto force_pickup;
        if(!PLAYER->override)goto check_enabled;
force_pickup:
        yes=1;
check_enabled:
        if(!PLAYER->enabled)yes=0;
        if(yes) {
            i=I(d,0x68);old=g_item_ammo_counts[i];
            weapon_add_ammo(i,I(d,0x60));
            if(old<g_item_ammo_counts[i]) {
                delta=g_item_ammo_counts[i]-old;
                if(delta==1) {
                    e=&g_weapon_l00_table[g_item_slot_to_record[i]];
                    sound=e->single_sound;
                } else {
                    e=&g_weapon_l00_table[g_item_slot_to_record[i]];
                    sound=e->multiple_sound;
                }
                func_PAL_L00_003282B0(sound,delta,-1);
            }
            moby_set_state(m,2,-1);
            F(d,0x74)=0.16000001f;
            vec_clear_128(d);
            if(subtract_integer_with_clamp(g_frame_l00_counter[0]-D_L00_001B2ADC[0])>8) {
                PlayMobySound(0,0,m);D_L00_001B2ADC[0]=g_frame_l00_counter[0];
            }
        }
        break;
    case 2:
        FastVecSub(a,m+0x10,PLAYER->position);
        matrix_mul_vec3(a,a,PLAYER->matrix);
        target_speed=8.0f;
        if(a[2]>0.0f)target_speed=0.0f;
        ApproachValue(d+0x74,target_speed,0.0096f);
        vec_scale_to_length(b,PLAYER->axis,F(d,0x74));
        FastVecAdd(m+0x10,m+0x10,b);
        FastVecAdd(m+0x10,m+0x10,PLAYER->motion);
        speed=FastVecLength(d);
        ApproachValue(&speed,1.2800001f,0.0096f);
        FastVecSub(c,PLAYER->target,m+0x10);
        time=FastVecLength(c)/speed;
        if(time<25.0f)ApproachValue(m+0x2c,0.0f,F(*(char **)(m+0x24),0x24)*0.04f);
        if(F(m,0x2c)==0.0f) {moby_mark_spawned(m);return;}
        if(time<=1.0f) {moby_mark_spawned(m);return;}
        vec_scale_to_length(d,c,speed);
        FastVecAdd(m+0x10,m+0x10,d);
        FastVecCross(v,PLAYER->axis,d);
        vec_set_direction_with_complement(v,v,0.10471977f);
        *(Quadword *)up=0;up[2]=0.3f;
        matrix_mul_vec3(v2,up,m+0xc0);
        quaternion_to_rotation_basis(v,matrix);
        multiply_matrix3x3(m+0xc0,matrix,m+0xc0);
        matrix_mul_vec3(v3,up,m+0xc0);
        FastVecSub(v4,v3,v2);
        FastVecSub(m+0x10,m+0x10,v4);
        break;
    }
    if(B(m,0x20)==1 && vec_fast_helper_d(m,g_hero_moby)) {
        B(m,0x23)=B(m,0x23)>36?B(m,0x23)-4:36;
    } else {
        B(m,0x23)=B(m,0x23)<124?B(m,0x23)+4:128;
    }
    if(*(s8 *)(m+0x23)>=0)*(u16 *)(m+0x34)|=0x2000;
    else *(u16 *)(m+0x34)&=0xdfff;
}
