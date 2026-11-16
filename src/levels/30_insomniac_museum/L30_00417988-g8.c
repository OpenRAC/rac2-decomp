#include "common.h"
typedef struct MuseumPlayer {
    char pad00[0x40];
    float matrix40[16];
    float position[4];
    char pad90[8];
    float rotation[4];
    char padA8[0x58];
    float velocity[4];
    char pad110[0x112];
    short mode;
    char pad224[0x118];
    char *focus;
    char pad340[0x8E8];
    int flags;
    char padC2C[0x61C];
    int saved;
    char pad124C[0x1044];
    char *animation;
    int animationId;
    char pad2298[0x30];
    int action;
} MuseumPlayer;
extern MuseumPlayer g_hero_state;
typedef struct MuseumInput {
    char pad[0x1A0];
    union { unsigned long long mask; struct { unsigned low, high; } words; } buttons;
} MuseumInput;
extern MuseumInput g_pad_state;
typedef struct MuseumGameState { char pad[0x33]; unsigned char mode; } MuseumGameState;
extern MuseumGameState g_item_slot_to_record;
extern unsigned char g_moby_nibble_table[];
extern int g_current_map_index MACRO_ADDR;
extern unsigned char g_focus_lock_flag;
typedef struct MuseumCompletion { char pad[0x464]; unsigned char complete[0]; } MuseumCompletion;
extern char g_museum_completion[];
typedef struct MuseumSound { char pad[0x14]; int handle; char rest[0xC8]; } MuseumSound;
extern char g_item_l30_material_table[];
extern int g_hero_focus_frame_count;
extern char *g_moby_l30_table;
extern char D_L30_001B1FC0_gp[] SDATA(D_L30_001B1FC0), D_L30_001B1FD0_gp[] SDATA(D_L30_001B1FD0), D_L30_001B1FE0_gp[] SDATA(D_L30_001B1FE0);
extern char g_camera_l30_position[], g_camera_rotation_rows[];
extern float g_museum_angle_scale NOT_SDA, g_museum_fade_value MACRO_ADDR;
extern int g_museum_effect_mode;
extern int g_museum_effect_timer MACRO_ADDR, g_museum_effect_end_time MACRO_ADDR, g_museum_effect_duration MACRO_ADDR, g_museum_effect_limit MACRO_ADDR;
extern int g_track_slot_table[][4];
extern char g_str_effect_settings[],g_str_effect_duration[],g_str_effect_limit[],g_str_track_id_a[],g_str_track_id_b[],g_str_track_id_c[],g_str_track_id_d[],g_str_track_id_e[],g_str_track_id_f[],g_str_track_id_g[],g_str_track_id_h[],g_str_track_id_i[],g_str_track_id_j[],g_str_track_id_k[],g_str_track_id_l[],g_str_track_id_m[],g_str_track_id_n[];
extern void moby_set_state(char *,int,int), moby_set_flag_bit(char *,int);
extern int flag_set_first_pending(char *);
extern void museum_effect_object_spawn(char *),museum_effect_holder_update(char *),museum_effect_object_release(char *);
extern int ForceClaimNotice(int,int,int);
extern int load_is_class_cached(int);
extern void LoadClassIntoFreeCacheSlot(int), hero_start_loader_state(int);
extern s32 hero_l00_set_action(int,int);
extern void matrix_mul_vec3(void *,void *,void *),FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *);
extern float FastAddRotations(float,float),mat_fast_helper_a(float,float),vec_distance_xy(void *,void *);
extern void hero_start_target_state(void *,int,float);
extern int hero_get_target_state_kind(void);
extern void set_hero_animation(int,int,float),cam_set_value_target(int,int,float,float,float,float);
extern void func_L30_0042BEB8(void *,void *,int,int,int),func_L30_0042BDF0(void *),func_L30_0042BE48(void *);
extern void vec_clamp_length(void *,float);
extern void StepAngleTowardTarget(void *,int,float,float);
extern float ApproachValue(float *,float,float);
extern int request_begin_slot(int,int,char *,int,int);
extern void set_identity_rotation_rows(void *),vec_clear_128(void *),euler_rotation_basis(void *,void *),func_L30_0042E658(int);
extern char *museum_tweak_menu_spawn(char *);
extern void MuseumTweakMenuAddItem(char *,void *,void *,int,int,int);
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
static __inline__ unsigned int AdvanceMuseumTimer(char *obj) {
    unsigned int value = U(obj,0x96);
    unsigned int old = value++;
    U(obj,0x96) = value;
    return old;
}
typedef struct MuseumDisplayVars { char pad[0x6C]; unsigned short settings; } MuseumDisplayVars;
typedef struct MuseumDisplay { char pad[0x68]; MuseumDisplayVars *vars; } MuseumDisplay;
typedef struct MuseumExhibit {
    int childIds[2];
    int cleanupId;
    int trackIds[14];
    unsigned short settings;
    char pad46[2];
    int duration, limit;
    MuseumDisplay *display;
    char *menu;
    int completed, saved;
    int pad60;
    float fade;
} MuseumExhibit;
void func_L30_00417988(char *obj) {
    MuseumExhibit *st = (MuseumExhibit *)P(obj,0x68);
    float vec[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    switch (B(obj,0x20)) {
    case 0: {
        int j, state;
        unsigned short id = U(obj,0xB2);
        char *o;
        if (((MuseumCompletion *)g_museum_completion)->complete[(short)id]
            || (state = g_moby_nibble_table[((short)id>>1)+(g_current_map_index<<10)], (id & 1) ? (state>>4)&7 : state&7)) {
            moby_set_state(obj,8,-1);
            moby_set_flag_bit(obj,1);
            for (j=0;j<2;j++) if (st->childIds[j]!=-1) moby_set_flag_bit(g_moby_l30_table+(st->childIds[j]<<8),1);
        } else {
            moby_set_state(obj,1,-1);
            museum_effect_object_spawn(obj);
            o=(char *)st->display;
            qcopy(o+0x10,obj+0x10);
            F(o,0x18)+=1.0f;
            U(st->display,0x34)|=1;
            B(st->display,0x31)=0;
        }
        break;
    }
    case 1:
        if (g_hero_state.focus!=obj || g_hero_focus_frame_count<16 || !g_focus_lock_flag) break;
        ForceClaimNotice(12,0x2803,1);
        if (!load_is_class_cached(((MuseumSound *)g_item_l30_material_table)[g_item_slot_to_record.mode].handle)) {
            LoadClassIntoFreeCacheSlot(((MuseumSound *)g_item_l30_material_table)[g_item_slot_to_record.mode].handle);
            break;
        }
        if (g_pad_state.buttons.words.high&0x10) {
            st->saved=g_hero_state.saved;
            g_hero_state.action=0x33;
            moby_set_state(obj,2,-1);
        } else if ((g_current_map_index==21 || g_current_map_index==30) && ((g_pad_state.buttons.mask&3)==3)) moby_set_state(obj,9,-1);
        break;
    case 2: {
        unsigned int cameraState;
        if (flag_set_first_pending(obj)) {
            matrix_mul_vec3(vec,D_L30_001B1FC0_gp,obj+0xC0);
            FastVecAdd(vec,vec,obj+0x10);
            hero_start_target_state(vec,0,FastAddRotations(F(obj,0xF8),3.1415927f));
        }
        cameraState=hero_get_target_state_kind();
        if (cameraState==2) moby_set_state(obj,3,-1);
        else if ((AdvanceMuseumTimer(obj)>=301)) {hero_start_loader_state(0);moby_set_state(obj,1,-1);}
        else if (!cameraState) moby_set_state(obj,1,-1);
        break;
    }
    case 3:
        if (flag_set_first_pending(obj)) {
            hero_l00_set_action(0x6F,0);set_hero_animation(0x54,0,20.0f);
            FastVecSub(vec,g_camera_l30_position,g_hero_state.position);
            matrix_mul_vec3(vec,vec,g_hero_state.matrix40);
            func_L30_0042BEB8(g_camera_l30_position,g_camera_l30_position,3,120,0);
            st->fade=0;
        }
        matrix_mul_vec3(vec,D_L30_001B1FC0_gp,obj+0xC0);
        FastVecAdd(vec,vec,obj+0x10);
        FastVecSub(g_hero_state.velocity,vec,g_hero_state.position);
        g_hero_state.velocity[2]=0;
        vec_clamp_length(g_hero_state.velocity,0.012500001f);
        StepAngleTowardTarget(g_hero_state.rotation,0,FastAddRotations(F(obj,0xF8),3.1415927f),0.017453296f);
        g_hero_state.mode=3;
        if ((g_hero_state.flags&2) && B(g_hero_state.animation,0x43)==0x54) set_hero_animation(0x55,0,7.0f);
        if (g_hero_state.animationId!=0x6F) moby_set_state(obj,1,-1);
        matrix_mul_vec3(pos,D_L30_001B1FD0_gp,&g_hero_state);
        FastVecAdd(pos,pos,g_hero_state.position);
        qzero_nc(rot);
        matrix_mul_vec3(target,D_L30_001B1FE0_gp,&g_hero_state);
        FastVecAdd(target,target,g_hero_state.position);
        rot[2]=mat_fast_helper_a(target[0]-pos[0],target[1]-pos[1]);
        rot[1]=-mat_fast_helper_a(vec_distance_xy(pos,target),target[2]-pos[2]);
        func_L30_0042BDF0(pos);func_L30_0042BE48(rot);
        if ((AdvanceMuseumTimer(obj)>=61)) moby_set_state(obj,4,-1);
        break;
    case 4: {
        unsigned int elapsed;
        if (flag_set_first_pending(obj)) {
            g_museum_angle_scale=0.017453294f;
            cam_set_value_target(30,1,0.017453294f,0.005f,0.2f,0.0f);
        }
        g_hero_state.mode=3;
        if ((AdvanceMuseumTimer(obj)<21)) break;
        ApproachValue(&st->fade,1.0f,0.116666675f);
        elapsed=U(obj,0x96);
        g_museum_fade_value=st->fade;
        if (elapsed<31) break;
        g_museum_angle_scale=1.1243411f;
        cam_set_value_target(1,0,1.1243411f,0.005f,0.2f,0.0f);
        if (!request_begin_slot(7,1,obj,0,0)) moby_set_state(obj,5,-1);
        break;
    }
    case 5:
        if (g_museum_effect_mode==7) {
            int i;
            museum_effect_object_spawn(obj);
            g_museum_effect_timer=0;
            /* Pointer arithmetic, not trackIds[i]: an array field of a BLKmode struct would form st+0xC in its own
             * register ahead of the loop's duplicated exit test. The scalar globals leave the loop through load_mems. */
            for (i=0;i<14&&*(st->trackIds+i)>=0;i++) {
                g_track_slot_table[i][0]=*(st->trackIds+i);
                g_museum_effect_timer++;
                g_museum_effect_duration=st->duration;
                g_museum_effect_end_time=st->duration+120;
                g_museum_effect_limit=st->limit;
                st->display->vars->settings=st->settings;
            }
            U(st->display,0x34)&=~1;
            B(st->display,0x31)=1;
            U(st->display,0x34)&=~0x80;
            set_identity_rotation_rows(g_camera_rotation_rows);
            vec_clear_128((char *)st->display+0xF0);
            F(st->display,0xF4)=-1.5707964f;
            euler_rotation_basis((char *)st->display+0xC0,(char *)st->display+0xF0);
            moby_set_state(obj,6,-1);
        } else if ((AdvanceMuseumTimer(obj)>=6)) moby_set_state(obj,1,-1);
        break;
    case 6:
        if (g_museum_effect_mode==7) {set_identity_rotation_rows(g_camera_rotation_rows);museum_effect_holder_update(obj);break;}
        museum_effect_object_release(obj);
        if (st->cleanupId!=-1) func_L30_0042E658(st->cleanupId);
        if (st->completed) {
            unsigned short id;
            unsigned char *p;
            moby_set_state(obj,7,-1);
            if (B(obj,0xB0)==255) break;
            id=U(obj,0xB2);
            if (id&1) {p=g_moby_nibble_table+(((short)id>>1)+(g_current_map_index<<10));if (((*p>>4)&7)!=7) *p+=16;}
            else {p=g_moby_nibble_table+(((short)id>>1)+(g_current_map_index<<10));if ((*p&7)!=7) ++*p;}
        } else {hero_start_loader_state(0);moby_set_state(obj,1,-1);}
        break;
    case 7: {
        int j;
        moby_set_flag_bit(obj,1);
        for (j=0;j<2;j++) if (st->childIds[j]!=-1) moby_set_flag_bit(g_moby_l30_table+(st->childIds[j]<<8),1);
        hero_start_loader_state(0);moby_set_state(obj,8,-1);
        break;
    }
    case 8:
        if ((g_pad_state.buttons.mask&15)==15) moby_set_state(obj,9,-1);
        break;
    case 9:
        if (flag_set_first_pending(obj)) {
            st->menu=museum_tweak_menu_spawn(obj);
            MuseumTweakMenuAddItem(st->menu,&st->settings,g_str_effect_settings,0,0,10000);
            MuseumTweakMenuAddItem(st->menu,&st->duration,g_str_effect_duration,0,30,1000);
            MuseumTweakMenuAddItem(st->menu,&st->limit,g_str_effect_limit,0,15,1000);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[0],g_str_track_id_a,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[1],g_str_track_id_b,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[2],g_str_track_id_c,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[3],g_str_track_id_d,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[4],g_str_track_id_e,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[5],g_str_track_id_f,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[6],g_str_track_id_g,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[7],g_str_track_id_h,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[8],g_str_track_id_i,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[9],g_str_track_id_j,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[10],g_str_track_id_k,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[11],g_str_track_id_l,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[12],g_str_track_id_m,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[13],g_str_track_id_n,0,-1,3);
            st->completed=0;
        }
        ForceClaimNotice(1,0,1);
        if (!st->menu || H(st->menu,0xAA)!=0x118A || B(st->menu,0x20)==254 || B(st->menu,0x20)==253) moby_set_state(obj,1,-1);
        break;
    }
}
