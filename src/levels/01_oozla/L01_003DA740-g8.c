#include "include_asm.h"
#include "common.h"

extern char *g_moby_l01_table __attribute__((sda));

extern u16 *g_group_list_table[];

/* Raises the measured flag on every record of the table the object's selector names. */
/* Sets a flag on every Mutant Muckdweller in this object's group. */
void muckdweller_alert_group(s32 moby) {
    s32 moby_base;
    s16 *member;
    s16 *group_list;

    if (*(u8 *)(moby + 0x21) == 0xFF)
        return;
    group_list = g_group_list_table[*(u8 *)(moby + 0x21)];
    if (group_list == 0)
        return;
    member = group_list;
    moby_base = (s32)g_moby_l01_table;
    do {
        u32 offset = (*(u16 *)member & 0x7FFF) << 8;

        if (*(s8 *)(moby_base + offset + 0x20) >= 0) {
            if (*(s16 *)(moby_base + offset + 0xAA) == MOBY_CLASS_MUTANT_MUCKDWELLER)
                *(u16 *)(*(u32 *)(moby_base + offset + 0x68) + 0x3DA) = 1;
        }
    } while (*member++ >= 0);
}

/* func_L01_00416A50 is defined in L01_003DA740.c (this unit has no $gp access for it). */

typedef unsigned int TI128 __attribute__((mode(TI)));

extern u8 *g_swamp_patrol_positions __attribute__((sda));

extern char g_hero_position[];

extern float vec_distance_xy(void *, void *);

extern float coll_probe_ground_height_below(void *, int, float);

/* Picks the farthest of up to three points from the hero and gives its position and ground height. */
void muckdweller_find_farthest_anchor(u8 *moby, u8 *out) {
    s32 *index_ptr = (s32 *)(*(u32 *)(moby + 0x68) + 0x3C4);
    TI128 point;
    int count = 3;
    f32 distance;

    *(f32 *)(out + 0xC) = 0.0f;
    while (--count >= 0) {
        s32 index = *index_ptr;

        if (index != -1) {
            u8 *base = g_swamp_patrol_positions;

            qcopy_nc(&point, base + index * 128 + 0x30);
            distance = vec_distance_xy(&point, g_hero_position);
            if (*(f32 *)(out + 0xC) < distance) {
                qcopy_nc(out, &point);
                *(f32 *)(out + 0xC) = distance;
            }
        }
        index_ptr++;
    }
    *(f32 *)(out + 0x8) = coll_probe_ground_height_below(out, 0, 10.0f);
}

extern s32 moby_is_in_selected_zone(void *);
extern f32 level_get_water_height(void);
extern f32 math_random_angle(void);
extern void moby_set_state(void *,s32,s32);
extern f32 math_ease_out_quad(f32);
extern void moby_scale_owner_words_by_angles(void *,void *,void *,f32,f32,f32);
extern void FastVecSub(void *,void *,void *);
extern void mat_combine_and_store(void *,void *,void *,void *);
extern f32 FastAddRotations(f32,f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern s32 FastTweenColor(u32,u32,f32);
extern f32 FastVecDot(void *,void *);
extern f32 math_approach_with_velocity(void *,f32,void *,f32,f32,f32,s32);
extern void mat_transform_offset_two_matrices(void *,void *,void *,void *,void *);
typedef struct {
 u8 pad0[0x80]; f32 position[4];
 u8 pad90[0x33C-0x90]; void *platform;
 u8 pad340[0xE]; s16 flag34E;
 u8 pad350[0x229C-0x350]; s32 mode;
} UpdateHero;
extern UpdateHero g_hero_state NOT_SDA;
typedef int UpdateQuad __attribute__((mode(TI)));
extern f32 g_muckdweller_ease_offset __attribute__((sda));
extern f32 g_muckdweller_back_speed __attribute__((sda));
extern f32 g_muckdweller_forward_speed __attribute__((sda));
extern f32 g_muckdweller_unused_float_a __attribute__((sda));
extern f32 g_muckdweller_unused_float_b __attribute__((sda));
extern f32 g_muckdweller_scale_param __attribute__((sda));
extern f32 g_muckdweller_angle_x_degrees __attribute__((sda));
extern f32 g_muckdweller_angle_y_degrees __attribute__((sda));
extern f32 g_muckdweller_tilt_gain __attribute__((sda));
extern f32 g_muckdweller_side_gain __attribute__((sda));
extern f32 g_muckdweller_approach_accel_a __attribute__((sda));
extern f32 g_muckdweller_approach_accel_b __attribute__((sda));
extern f32 g_muckdweller_approach_accel_c __attribute__((sda));
extern f32 g_muckdweller_settle_accel_a __attribute__((sda));
extern f32 g_muckdweller_settle_accel_b __attribute__((sda));
extern f32 g_muckdweller_settle_accel_c __attribute__((sda));
typedef struct {
 u8 pad0[0x60];
 f32 field60;
 f32 field64;
 f32 field68;
 f32 field6C;
 u8 pad70[0x8];
 f32 field78;
 f32 field7C;
 f32 field80;
 f32 field84;
 u8 pad88[0x18];
 s32 fieldA0;
 u8 padA4[0x8];
 f32 fieldAC;
} State0041C970;
typedef struct {
 u8 pad0[0x10]; f32 position[4];
 u8 state; u8 slot; u8 pad22[2];
 struct ObjectClass0041C970 { u8 pad0[0x10]; s32 flags; } *classData;
 u8 pad28[4]; f32 field2C;
 u8 pad30; u8 field31; u8 pad32[2]; u16 flags34;
 u8 pad36[0xD]; u8 animation;
 u8 pad44[0x24]; State0041C970 *stateData;
 u8 pad6C[0xC]; u32 color;
 u8 pad7C[0x1C]; s32 collisionFlags;
 u8 pad9C[0x24]; f32 matrix[12]; f32 rotation[4];
} Object0041C970;
/* Tilting lift: initializes its height range, moves while the hero rides it,
 * and tilts toward the hero's offset projected on the object's axes. */
void UpdateOozlaTiltingLift(Object0041C970 *obj) {
 f32 oldpos[4] __attribute__((aligned(16)));
 f32 oldrot[4] __attribute__((aligned(16)));
 f32 delta[4] __attribute__((aligned(16)));
 f32 local[4] __attribute__((aligned(16)));
 f32 oldstate[4] __attribute__((aligned(16)));
 f32 current[4] __attribute__((aligned(16)));
 f32 out[4] __attribute__((aligned(16)));
 State0041C970 *p;
 f32 height0, height1, height2, x, y, speed, scaledX;
 f32 timestep;
 s32 trigger;
 if(!moby_is_in_selected_zone(obj->position)) return;
 p=obj->stateData;
 qcopy(oldpos,obj->position);
 qcopy(oldrot,obj->rotation);
 switch(obj->state) {
 case 0:
  height0=level_get_water_height();
  *(s32 *)((u8 *)p+0xAC)=0;
  if(height0>100.0f) {
   p->field78=math_random_angle();
   p->field7C=math_random_angle();
   p->field6C=obj->position[2]-height0;
   p->field60=p->field6C;
   p->field64=p->field6C-g_muckdweller_ease_offset;
   p->field68=0;
   qcopy((u8 *)p+0x80,obj->rotation);
   qzero((u8 *)p+0x90);
   if(!p->fieldA0) moby_set_state(obj,2,-1);
   else moby_set_state(obj,1,-1);
  }
  break;
 case 1:
  height1=level_get_water_height();
  trigger=0;
  if(g_hero_state.mode==25 && p->field68<0.0f &&
     g_hero_state.position[2]>obj->position[2]-0.2f &&
     obj->position[2]<height1+0.1f) trigger=1;
  if((g_hero_state.platform==obj && !g_hero_state.flag34E) || trigger) {
   if(trigger) obj->collisionFlags=0;
   else obj->collisionFlags=obj->classData->flags;
   x=math_ease_out_quad((p->field6C-p->field64)/g_muckdweller_ease_offset);
   timestep=0.01666666753590107f;
   p->field68=-(g_muckdweller_back_speed*timestep)*x;
  } else {
   obj->collisionFlags=obj->classData->flags;
   x=math_ease_out_quad((g_muckdweller_ease_offset-(p->field6C-p->field64))/g_muckdweller_ease_offset);
   timestep=0.01666666753590107f;
   p->field68=g_muckdweller_forward_speed*(x*timestep);
  }
  p->field6C+=p->field68;
  obj->position[2]=height1+p->field6C;
  moby_scale_owner_words_by_angles(obj,(u8 *)p+0x78,(u8 *)p+0x7C,g_muckdweller_scale_param,g_muckdweller_angle_x_degrees*0.0002908882452175021f,g_muckdweller_angle_y_degrees*0.0002908882452175021f);
  FastVecSub(delta,obj->position,oldpos);
  mat_combine_and_store((u8 *)p+0x20,delta,oldrot,obj->rotation);
  break;
 case 2:
  if(obj->field31) {
   p->fieldAC=FastAddRotations(p->fieldAC,0.05235988646745682f);
   obj->color=FastTweenColor(0xFFEEFC0E,0xF03B4004,math_fast_sin_or_cos_b(p->fieldAC)*0.5f+0.5f);
  }
  height2=level_get_water_height();
  if(!g_hero_state.flag34E && g_hero_state.platform==obj) {
   FastVecSub(local,g_hero_state.position,obj->position);
   x=FastVecDot(local,obj->matrix);
   y=-g_muckdweller_tilt_gain * FastVecDot(local,obj->matrix+4);
   scaledX=g_muckdweller_side_gain*x;
   *(UpdateQuad *)oldstate=*(UpdateQuad *)((u8 *)p+0x80);
   *(UpdateQuad *)current=*(UpdateQuad *)(obj->position);
   math_approach_with_velocity((u8 *)p+0x80,y,(u8 *)p+0x90,g_muckdweller_approach_accel_a,g_muckdweller_approach_accel_b,g_muckdweller_approach_accel_c,0);
   math_approach_with_velocity((u8 *)p+0x84,scaledX,(u8 *)p+0x94,g_muckdweller_approach_accel_a,g_muckdweller_approach_accel_b,g_muckdweller_approach_accel_c,0);
   mat_transform_offset_two_matrices(g_hero_state.position,out,obj->position,oldstate,(u8 *)p+0x80);
  } else {
   math_approach_with_velocity((u8 *)p+0x80,0.0f,(u8 *)p+0x90,g_muckdweller_settle_accel_a,g_muckdweller_settle_accel_b,g_muckdweller_settle_accel_c,0);
   math_approach_with_velocity((u8 *)p+0x84,0.0f,(u8 *)p+0x94,g_muckdweller_settle_accel_a,g_muckdweller_settle_accel_b,g_muckdweller_settle_accel_c,0);
  }
  obj->position[2]=height2+p->field6C;
  moby_scale_owner_words_by_angles(obj,(u8 *)p+0x78,(u8 *)p+0x7C,g_muckdweller_scale_param,g_muckdweller_angle_x_degrees*0.0002908882452175021f,g_muckdweller_angle_y_degrees*0.0002908882452175021f);
  obj->rotation[0]=FastAddRotations(p->field80,obj->rotation[0]);
  obj->rotation[1]=FastAddRotations(p->field84,obj->rotation[1]);
  FastVecSub(delta,obj->position,oldpos);
  mat_combine_and_store((u8 *)p+0x20,delta,oldrot,obj->rotation);
  break;
 }
}

extern s32 FloatToInt(f32);
extern f32 math_random_signed_float_range(f32, f32);
extern float path_l01_compute_segment_lengths(void *);
extern void moby_set_controller_speed_limits(void *, f32, f32, f32, f32);
extern s32 math_random_int_range(s32, s32);
extern void anim_start_blended(void *, s32, s32, s32);
extern u8 *g_path_l01_table[] NOT_SDA;
extern u8 g_muckdweller_init_data[] SDATA(D_L01_001B0900);

/* Sets up the Muckdweller when it appears: its speeds, timers and path points, and its first animation. */
void muckdweller_init(u8 *obj) {
    u8 *vars = *(u8 **)(obj + 0x68);
    s32 idx;

    *(void **)(vars + 0x18) = vars + 0x1C0;
    vars[0x48] = FloatToInt(10.0f);
    vars[0x4A] = FloatToInt(9.6f);
    *(s32 *)(vars + 0x158) = 5;
    *(u8 *)(vars + 0x127) = 11;
    *(f32 *)(vars + 0x12C) = 0.20000001788139343f;
    *(f32 *)(vars + 0x130) = 0.10000000894069672f;
    *(f32 *)(vars + 0x134) = 0.006111111491918564f;
    *(f32 *)(vars + 0x138) = 0.010277777910232544f;
    *(f32 *)(vars + 0x13C) = 0.011111111380159855f;
    *(f32 *)(vars + 0x14C) = 0.4f;
    *(u8 *)(vars + 0x120) = 0;
    *(u8 *)(vars + 0x121) = 10;
    *(u8 *)(vars + 0x122) = 10;
    *(u8 *)(vars + 0x126) = 10;
    *(f32 *)(vars + 0x140) = 0.5f;
    *(f32 *)(vars + 0x144) = 0.5f;
    *(u8 *)(vars + 0x17C) = 6;
    *(u8 *)(vars + 0x17D) = 10;
    *(u8 *)(vars + 0x17E) = 6;
    *(u8 *)(vars + 0x17F) = 10;
    *(s16 *)(vars + 0x148) = 0;
    *(u8 *)(vars + 0x28) = 0;
    *(u8 *)(vars + 0x182) = 6;
    *(u8 *)(vars + 0x183) = 10;
    *(u8 *)(vars + 0x29) = 1;
    *(f32 *)(vars + 0x30) = 0.5f;
    *(TI128 *)(vars + 0x3A0) = *(TI128 *)(obj + 0x10);
    *(s16 *)(vars + 0x3D8) = 0;
    if (*(s32 *)(vars + 0x3C0) != -1) {
        path_l01_compute_segment_lengths(g_path_l01_table[*(s32 *)(vars + 0x3C0)]);
    }
    idx = *(s32 *)(vars + 0x3BC);
    if (idx != -1) {
        path_l01_compute_segment_lengths(g_path_l01_table[idx]);
    }
    qcopy(vars + 0x2B0, obj + 0x10);
    *(f32 *)(vars + 0x2C0) = 0.3f;
    *(f32 *)(vars + 0x2CC) = 5.0f;
    *(f32 *)(vars + 0x1C8) = 0.2f;
    *(f32 *)(vars + 0x1C4) = 0.1f;
    *(f32 *)(vars + 0x2D0) = 5.0f;
    *(f32 *)(vars + 0x1C0) = 0.3f;
    *(f32 *)(vars + 0x1CC) = 0.2f;
    *(f32 *)(vars + 0x1D0) = 0.8726646900177002f;
    *(f32 *)(vars + 0x1F0) = 0.523598849773407f;
    *(f32 *)(vars + 0x1EC) = 0.0055555556900799274f;
    *(s32 *)(vars + 0x1FC) = *(s32 *)(vars + 0x3BC);
    *(f32 *)(vars + 0x29C) = math_random_signed_float_range(25.0f, 35.0f) * 0.01745329424738884f;
    *(s16 *)(vars + 0x2A2) = 120;
    *(s16 *)(vars + 0x2A4) = 180;
    moby_set_controller_speed_limits(obj, 0.002222222276031971f, 0.06666667014360428f, 0.0021331803873181343f, 0.19198624789714813f);
    *(f32 *)(vars + 0xF0) = *(f32 *)(obj + 0x2C);
    *(f32 *)(vars + 0xE0) = *(f32 *)(vars + 0x30);
    *(void **)(vars + 0xC0) = g_muckdweller_init_data;
    *(s32 *)(obj + 0xF4) = 0;
    *(s32 *)(obj + 0xF0) = 0;
    qzero_nc(vars + 0x210);
    *(f32 *)(vars + 0x218) = 1.0f;
    if (obj[0x21] != 255) {
        **(s32 **)(vars + 0x3FC) = 0;
        **(s32 **)(vars + 0x400) = -1;
    }
    if (!vars[0x3D0]) {
        if (vars[0x3D1]) {
            if (*(s32 *)(vars + 0x414) != -1) *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x414);
            else if ((idx = *(s32 *)(vars + 0x418)) != -1) *(s32 *)(vars + 0x3F8) = idx;
            else *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x41C);
            if (vars[0x3D2]) {
                moby_set_state(obj, 0, 1);
            } else {
                moby_set_state(obj, 1, 3);
            }
        } else {
            if (*(s32 *)(vars + 0x418) != -1) *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x418);
            else if ((idx = *(s32 *)(vars + 0x414)) != -1) *(s32 *)(vars + 0x3F8) = idx;
            else *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x41C);
            moby_set_state(obj, 1, 3);
        }
        if (*(s32 *)(vars + 0x408) != -1) {
            if (obj[0x43] != 7) anim_start_blended(obj, 7, 0, math_random_int_range(2, 10));
        } else if (obj[0x43] != 0) {
            anim_start_blended(obj, 0, 0, math_random_int_range(2, 10));
        }
    } else {
        if (*(s32 *)(vars + 0x414) != -1) *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x414);
        else if ((idx = *(s32 *)(vars + 0x418)) != -1) *(s32 *)(vars + 0x3F8) = idx;
        else *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x41C);
        *(s32 *)(obj + 0x98) = 0;
        obj[0x31] = 0;
        *(u16 *)(obj + 0x34) |= 1;
        *(f32 *)(obj + 0x18) -= 2.0f;
        moby_set_state(obj, 0, 1);
        if (obj[0x43] != 0) anim_start_blended(obj, 0, 0, math_random_int_range(2, 10));
    }
}
