/* Museum vehicle update: collision damage, activation, driving and respawn.
 * func_PAL_L30_00410A38, the PAL copy of func_L30_0040B9D8: the same C, where the hit timer,
 * the throttle steps, the speed threshold, the turn rate and the respawn delay are scaled to
 * 50 Hz and the activation prompt id becomes 0x12EA. */
#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))
typedef struct { char pad[10]; unsigned short offset; char pad2[4]; } PaletteRow;
typedef struct {
 char pad0[0x80]; unsigned int position[4], rotation[4];
 char padA0[0xD0-0xA0]; unsigned int copyD0[4],copyE0[4];
 char padF0[0x33C-0xF0]; char *ground; int ground_flag;
 char pad344[0x1830-0x344]; char *vehicle; short vehicle_id;
 char pad1836[6]; float health, max_health; int pad1844, health_percent;
 char pad184C[0x1FB0-0x184C]; int camera_x; float camera_y;
 char pad1FB8[0x2290-0x1FB8]; char *hero; int state; int pad2298,mode;
 char pad22A0[0x24CC-0x22A0]; int hero_health;
} VehicleHeroState;
extern VehicleHeroState g_hero_state;
extern struct { char pad[0x1A0]; int held, pressed; } g_pad_state;
extern int g_pad_held_flags;
extern int g_museum_effect_mode __attribute__((sda));
extern int g_vehicle_hit_timer_reset __attribute__((sda));
extern float g_vehicle_damage_scale __attribute__((sda));
extern float g_vehicle_max_health __attribute__((sda));
extern float g_vehicle_near_distance __attribute__((sda));
extern float g_vehicle_l30_bob_amplitude_2 __attribute__((sda));
extern float g_vehicle_scale_factor __attribute__((sda));
extern float g_vehicle_roll_rate __attribute__((sda));
extern float g_vehicle_yaw_rate __attribute__((sda));
extern float g_vehicle_pitch_rate __attribute__((sda));
extern float g_vehicle_throttle_decay __attribute__((sda));
extern float g_vehicle_throttle_gain __attribute__((sda));
extern float g_vehicle_hero_height_offset __attribute__((sda));
extern float g_vehicle_turn_speed __attribute__((sda));
extern int g_effect_texture_offset __attribute__((sda));
extern int g_gauge_palette_loaded __attribute__((sda));
extern int g_vehicle_animation_id __attribute__((sda));
extern int g_vehicle_prev_animation_id __attribute__((sda));
extern char *g_vehicle_joint_index __attribute__((sda));
extern char *g_gauge_palette_ptr __attribute__((sda));
extern char *g_class_palette_data;
extern void DrawMuseumStatusGauge(char *);
extern unsigned short g_palette_row_table[][8];
extern char g_palette_copy[], g_camera_l30_position[];
extern char *part_find_owned_effect_slot(char *,int,int);
extern void gfx_start_color_fade_pal(char *,void *), gfx_update_color_fade_pal(char *,void *);
extern float vec_length_xy(void *), func_002A0558(char *,char *), FastAddRotations(float,float), math_fast_sin_or_cos_b(float), fast_vec_dist(void *,void *);
extern int TryClaimNotice(int,int,int), math_random_int_below(int), flag_set_first_pending(char *);
extern int hero_l00_set_action_pal(int,int);
extern void UpdateHoverVehicleMotion_pal(char *,int), set_hero_animation_pal(int,int,float), moby_mark_in_range(char *);
extern void moby_set_state(char *,int,int), moby_update_ground_check(char *), gfx_add_draw_callback_third(void (*)(char *),void *);
extern void moby_transform_joint_to_world(char *,int,void *);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void moby_scale_owner_words_by_angles(char *,void *,void *,float,float,float);
extern void *memcpy(void *,const void *,unsigned int);
typedef struct {
 float velocity[4]; char pad10[16]; float pitch,yaw,roll,pad2C;
 float spawn[4]; char pad40[8]; float phase, bob, yaw_rate, pitch_rate, height, pad5C, health;
 int class_index; union { float throttle; int bits; } power;
 char pad6C[2]; unsigned char hit_timer; char pad6F[0x80-0x6F];
 unsigned char flash[16]; char *last_hit; int flags, alpha, count;
} VehicleVars;
typedef struct {
 char pad0[0x10]; float position[4]; unsigned char state; char pad21[3];
 char *class_data; char pad28[4]; float damage; unsigned char color, visible;
 char pad32[0x68-0x32]; VehicleVars *vars; char pad6C[3]; unsigned char delay;
 char pad70[0x96-0x70]; unsigned short timer; int flags, animation;
 char padA0[8]; unsigned char hit_flag; char padA9[0xF0-0xA9]; float rotation[4];
} MuseumVehicle;
/* dead-test helper allowed by owner ruling (master precedent).
 * As in label_y, the dead test preserves a block until reload; flow2 removes it.
 * The returned health is always the level's initial vehicle health. */
static __inline__ float initial_health(void)
{
    float health;
    if (g_museum_effect_mode)
        health = 1.0f;
    health = g_vehicle_max_health;
    return health;
}

void MuseumVehicleUpdate_pal(MuseumVehicle *obj) {
    VehicleVars *vars; char *hit;

    char activate;
    float angle_scale, scaled, roll_rate, yaw_rate, pitch_rate, bob;
    unsigned int pos[4] __attribute__((aligned(16)));
    vars=obj->vars;
    if (obj->state) {
        obj->position[2]=vars->height;
        hit=part_find_owned_effect_slot(obj,1,0);
        if (hit && P(hit,0x20) && *(short *)(P(hit,0x20)+0xAA)!=0xF2F && *(short *)(P(hit,0x20)+0xAA)!=0x942) {
            if (*(short *)(P(hit,0x20)+0xAA)!=0xFFF && (P(hit,0x20)!=vars->last_hit || !vars->hit_timer)) {
                B(vars,0x87)=0xD2;B(vars,0x88)=0xD2;B(vars,0x89)=0xD2;
                gfx_start_color_fade_pal(obj,&vars->flash);
                vars->health-=F(hit,0x2C);
                g_hero_state.health=vars->health;
                if (vars->health<=0.0f) obj->state=5;
                vars->last_hit=P(hit,0x20);
                vars->hit_timer=((s32)(g_vehicle_hit_timer_reset) * 5 + 2) / 6;
            }
        }
        obj->hit_flag=0xFF;
    } else vars->height=obj->position[2];
    gfx_update_color_fade_pal(obj,&vars->flash);

    obj->damage=F(obj->class_data,0x24)*g_vehicle_damage_scale;
    if (g_hero_state.vehicle==obj) g_hero_state.health_percent=(int)(g_hero_state.health/g_vehicle_max_health*200.0f);
    activate=0;
    switch (obj->state) {
    case 0: {
        char *palette; int copied;
        palette=g_class_palette_data+((PaletteRow *)((vars->class_index+g_effect_texture_offset)*16+(char *)g_palette_row_table))->offset*16;
        g_gauge_palette_ptr=palette;copied=g_gauge_palette_loaded;
        vars->alpha=255; vars->flags=0;
        if (!copied) memcpy(g_palette_copy,palette,0x400);
        g_gauge_palette_loaded=1;
        qcopy(&vars->spawn,obj->position); qzero_nc(vars);
        g_hero_state.max_health=g_hero_state.health=vars->health=initial_health();
        obj->state=1;
        vars->power.bits=0;vars->count=0;
        break; }
    case 1:
        if (vec_length_xy(vars)>0.0050000004f) UpdateHoverVehicleMotion_pal(obj,0);
        if (g_hero_state.state==28 || g_hero_state.state==22 || g_hero_state.state==57 || g_hero_state.state==111 ||
            g_hero_state.mode==2 || g_hero_state.mode==4 || g_hero_state.mode==3 || g_hero_state.mode>=13 ||
            g_hero_state.mode==7 || g_hero_state.mode==10 || g_hero_state.mode==16 || g_hero_state.mode==5 || g_hero_state.state==98 ||
            g_hero_state.hero_health<=0 || g_museum_effect_mode || !g_hero_state.ground_flag) break;
        if (g_hero_state.ground && (*(short *)(g_hero_state.ground+0xAA)==0x13E || *(short *)(g_hero_state.ground+0xAA)==0x46F)) break;
        if (func_002A0558(obj,g_hero_state.hero)<g_vehicle_near_distance && g_hero_state.state!=49) {
            int prompt_shown=TryClaimNotice(7,0x12ea,1)!=0;
            if (g_pad_state.pressed&16) activate=prompt_shown;
        }
        if (activate) {
            hero_l00_set_action_pal(49,0);set_hero_animation_pal(g_vehicle_animation_id,0,15.0f);
            qcopy(g_hero_state.rotation,obj->rotation);qcopy(g_hero_state.position,obj->position);
            g_hero_state.vehicle=obj;obj->state=3;obj->flags=0;I(g_hero_state.hero,0x9C)=-1;
        }
        break;
    case 3:
        if (g_pad_state.held&4) {
            vars->power.throttle-=g_vehicle_throttle_decay*1.2f;
            if (!math_random_int_below(9) || (g_pad_state.pressed&4)) moby_mark_in_range(obj);
        } else vars->power.throttle+=g_vehicle_throttle_gain*1.2f;
        if (g_vehicle_prev_animation_id!=g_vehicle_animation_id && g_vehicle_animation_id!=-1) set_hero_animation_pal(g_vehicle_animation_id,0,15.0f);
        UpdateHoverVehicleMotion_pal(obj,1);
        if (vars->power.throttle>1.0f) vars->power.throttle=1.0f; else if (vars->power.throttle<0.0f) vars->power.throttle=0.0f;
        if (g_hero_state.vehicle==obj) {
            if (g_pad_state.pressed&16) moby_set_state(obj,4,-1);
            qcopy(g_hero_state.copyD0,g_hero_state.copyE0);
        }
        break;
    case 4:
        if (flag_set_first_pending(obj)) {
            g_hero_state.camera_x=0;g_hero_state.camera_y=-1.0f;hero_l00_set_action_pal(11,1);
            g_hero_state.vehicle=0;g_hero_state.vehicle_id=-1;
        }
        obj->flags=0;I(g_hero_state.hero,0x9C)=0;UpdateHoverVehicleMotion_pal(obj,0);
        { unsigned int timer=obj->timer; unsigned int old=timer++; obj->timer=timer;
        if (old>=26) {obj->flags=I(obj->class_data,0x10);obj->state=1;} }
        break;
    case 6: break;
    case 5:
        obj->flags=I(obj->class_data,0x10);I(g_hero_state.hero,0x9C)=0;
        hero_l00_set_action_pal(0,1);moby_transform_joint_to_world(obj,0,pos);
        SpawnExplosionEffects_pal(obj,vars,pos,0.0f,0.0f,10,3,16,4.0f,2.0f,9.0f,1.0f,-1,15.0f,1,1,-1,0,0x810001);
        qcopy(obj->position,&vars->spawn);g_hero_state.vehicle_id=-1;g_hero_state.vehicle=0;obj->state=0;
        break;
    }
    scaled=vars->power.throttle;
    angle_scale=0.0003490659f;
    scaled=g_vehicle_scale_factor*(scaled*angle_scale);
    vars->height=obj->position[2];
    vars->phase=FastAddRotations(vars->phase,scaled);
    bob=math_fast_sin_or_cos_b(vars->phase)*g_vehicle_l30_bob_amplitude_2*vars->power.throttle;
    roll_rate=g_vehicle_roll_rate; yaw_rate=g_vehicle_yaw_rate; pitch_rate=g_vehicle_pitch_rate;
    vars->bob=bob;
    obj->position[2]+=vars->bob*vars->power.throttle;
    moby_scale_owner_words_by_angles(obj,&vars->yaw_rate,&vars->pitch_rate,roll_rate*0.017453294f,yaw_rate*(vars->power.throttle*angle_scale),pitch_rate*(vars->power.throttle*angle_scale));
    obj->rotation[2]=vars->roll;obj->rotation[0]=FastAddRotations(obj->rotation[0],vars->pitch);obj->rotation[1]=FastAddRotations(obj->rotation[1],vars->yaw);
    if (obj->state==3) {moby_transform_joint_to_world(obj,(int)g_vehicle_joint_index,g_hero_state.position);{char *h=(char *)&g_hero_state;F(h,0x88)+=g_vehicle_hero_height_offset;}qcopy(g_hero_state.rotation,obj->rotation);
        gfx_add_draw_callback_third(DrawMuseumStatusGauge,obj);
    }
    if (obj->visible && fast_vec_dist(obj->position,g_camera_l30_position)<64.0f) {moby_update_ground_check(obj);obj->delay=60;}
}
