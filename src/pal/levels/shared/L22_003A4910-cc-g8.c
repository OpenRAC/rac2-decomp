#include "names.h"
/* func_PAL_L22_003A4910, the PAL copy of func_L22_003A15D0: the same C, where rename func_L22_003A6230 becomes func_PAL_L22_003A95C8; rename func_0029B758 becomes func_PAL_0029C0F0; rename func_002B0ED8 becomes func_PAL_002B1A50; rename func_L00_002AF7D0 becomes func_PAL_L00_002AF6C0; rename func_L22_002C9898 becomes func_PAL_L22_002C99C8; expr 0.06666667f becomes 0.080000006f; expr 0.083333336f becomes 0.120000005f; expr 0.016666668f becomes 0.024f; expr 0.041666668f becomes 0.060000002f. */
#include "common.h"
typedef int Quad_003A15D0 __attribute__((mode(TI)));
typedef struct Hero_003A15D0 {
    char pad000[0x80];
    Quad_003A15D0 position;
    Quad_003A15D0 rotation;
    char pad0A0[0x140];
    short mode;
    char pad1E2[0x168E];
    int field1870;
    int health;
    int field1878;
    int field187C;
    char pad1880[0xA10];
    void *field2290;
    int field2294;
} Hero_003A15D0;
extern Hero_003A15D0 g_hero_state;
typedef struct Input_003A15D0 { char pad000[0x1A4]; int buttons; } Input_003A15D0;
extern Input_003A15D0 g_pad_state;
typedef struct Sub_15D0 {
    char pad0[0x8];
    signed char f8;
    char pad9[0x1];
    signed char fA;
    char padB[0x1];
    signed char fC;
} Sub_15D0;
typedef struct Cls_15D0 { char pad0[0x24]; float f24; } Cls_15D0;
struct Vars_15D0;
typedef struct Obj_15D0 {
    char pad0[0x20];
    unsigned char f20;
    char pad21[0x3];
    struct Cls_15D0 *f24;
    char pad28[0x4];
    float f2C;
    unsigned char f30;
    unsigned char f31;
    short f32;
    unsigned short f34;
    char pad36[0x2];
    unsigned long f38;
    char pad40[0x8];
    float f48;
    char pad4C[0x1C];
    struct Vars_15D0 *f68;
    char pad6C[0x3];
    unsigned char f6F;
    char pad70[0x8];
    int f78;
    char pad7C[0x19];
    unsigned char f95;
    char pad96[0x14];
    short fAA;
} Obj_15D0;
typedef struct Vars_15D0 {
    char pad0[0x20];
    float f20;
    short f24;
    short f26;
    unsigned char f28;
    char pad29[0x47];
    unsigned char f70;
    unsigned char f71;
    unsigned char f72;
    char pad73[0x3];
    unsigned char f76;
    unsigned char f77;
    char pad78[0x4];
    float f7C;
    float f80;
    float f84;
    float f88;
    float f8C;
    float f90;
    float f94;
    char pad98[0x4];
    float f9C;
    char padA0[0x8];
    int fA8;
    char padAC[0xC];
    float fB8;
    float fBC;
    char padC0[0xC];
    unsigned char fCC;
    unsigned char fCD;
    unsigned char fCE;
    unsigned char fCF;
    char padD0[0x2];
    signed char fD2;
    signed char fD3;
    char padD4[0x3];
    unsigned char fD7;
    char padD8[0x38];
    float f110;
    float f114;
    float f118;
    float f11C;
    float f120;
    char pad124[0xC];
    float f130;
    float f134;
    float f138;
    char pad13C[0x4];
    float f140;
    int f144;
    int f148;
    char pad14C[0xAC];
    unsigned char f1F8;
    unsigned char f1F9;
    char pad1FA[0x12A];
    short f324;
    short f326;
    char pad328[0x1C];
    int f344;
    char pad348[0x4];
    short f34C;
    short f34E;
    short f350;
    char pad352[0x6];
    short f358;
    short f35A;
    short f35C;
    short f35E;
    char pad360[0x14];
    int f374;
    short f378;
    short f37A;
    int f37C;
    short f380;
    short f382;
    short f384;
    char pad386[0x2];
    int f388;
    char pad38C[0x58];
    float f3E4;
    float f3E8;
    int f3EC;
    char pad3F0[0x2E];
    short f41E;
    char pad420[0x1A];
    short f43A;
    char pad43C[0x4];
    Obj_15D0 *f440;
    Obj_15D0 *f444;
    Obj_15D0 *f448;
    char pad44C[0x14];
    short f460;
    char pad462[0x2];
    int f464;
    short f468;
    short f46A;
    void * f46C;
    char pad470[0x74];
    int f4E4;
    char pad4E8[0x4];
    int f4EC;
} Vars_15D0;
extern int g_space_ship_difficulty __attribute__((sda)), g_space_ship_difficulty_threshold_b __attribute__((sda)), g_space_ship_difficulty_threshold_a __attribute__((sda));
extern int g_space_ship_timer __attribute__((sda)), g_space_ship_active_flag __attribute__((sda)), g_lane_check_index __attribute__((sda));
extern struct Obj_15D0 *ref_L22_003A15D0_00 __attribute__((sda)); /* D_L22_001AF314 in level 22 */
extern struct Obj_15D0 *g_space_ship_target_moby __attribute__((sda));
extern float g_space_ship_part_scale_b __attribute__((sda)), g_space_ship_part_scale_a __attribute__((sda));
extern int g_lane_slot_list[5] __attribute__((sda));
extern int g_space_ship_max_health, g_flying_enemy_spawn_count, g_flying_enemy_spawn_blocked;
extern int g_space_ship_lane_count, g_pickup_message_kind, g_pickup_message_timer;
extern short g_space_ship_mode;
extern char *g_space_ship_pickup_slots;
extern float g_planet_radius;
extern char g_ship_pickup_table[], g_tether_origin[];
extern char g_ship_init_params_template[] MACRO_ADDR;
extern char *g_ship_slot_array_start, *g_ship_slot_array_end;
extern void anim_choose_next_pal(void *);
extern void cam_reset_entry(void *);
extern void func_001163A0(unsigned int);
extern void FastVecSub(void *,void *,void *);
extern float FastVecLength(void *);
extern int math_random_int_below(int);
extern void lane_build_connection_masks(void *),pickup_spawn_initial(char *);
extern char *CreateMoby(int);
extern void set_identity_rotation_rows(void *);
extern void level_store_value_pair_pal(void *,void *);
extern int level_call_helper_return_true(void);
extern int DrawSpaceCombatHud(void);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *),func_002A0F48(void *);
extern void cam_compute_view_direction(void *,void *,int), vec_negate_and_forward(void *,void *,int);
extern int moby_apply_damage_to_object_pal(void *,void *,int);
extern void moby_set_state(void *,int,int), cancel_hero_item_animation_pal(void), release_moby_animation_slot(void *,void *);
extern s32 hero_l22_set_move_state_pal(int,int);

/* Space ship setup and upkeep (PAL: 50 Hz tuning). Sets the record up on the first update (health scaled by difficulty, the object table
   scan, then the tuning block) and keeps the three child objects in step. The tuning
   block's order matters to the scheduler: f11C is the 34th memory reference after the
   call, so it flushes the pending list, and f1F8 and f1F9 precede the second health read. */
void space_ship_init_and_update_pal(Obj_15D0 *obj) {
    Vars_15D0 *vars = obj->f68;
    Obj_15D0 *found = 0;
    Obj_15D0 *child;
    int i;
    char *base;
    typedef int Quad __attribute__((mode(TI)));
    union { Quad q; float f[4]; } vec;
    anim_choose_next_pal(obj);
    if (obj->f20 == 0) {
        float factor, health, damage_scale, range_scale;
        short random_roll;
        int eight, alpha;
        int difficulty=g_space_ship_difficulty;
        if (g_space_ship_difficulty_threshold_b < difficulty) factor = 0.6f;
        else if (g_space_ship_difficulty_threshold_a < difficulty) factor = 0.9f;
        else goto full_health;
        g_space_ship_max_health = (int)(vars->f326*factor);
        goto health_done;
full_health:
        g_space_ship_max_health = vars->f326;
health_done:
        cam_reset_entry(vars->f46C);
        g_space_ship_timer = 1;
        func_001163A0(T1_COUNT);
        vars->f4EC=1;
        g_flying_enemy_spawn_count=0; g_space_ship_pickup_slots=g_ship_pickup_table;
        g_flying_enemy_spawn_blocked=0;
        vars->f460=0; vars->f41E=0;
        g_space_ship_active_flag=1; g_space_ship_mode=0;
        vars->f46A=0; vars->f468=0;
        vars->f464=0; vars->f344=0;
        g_space_ship_lane_count=5;
        { int *dst=g_lane_slot_list; int *src=(int *)g_ship_init_params_template; int count; for(count=5;count!=0;count--) *dst++=*src++; }
        g_pickup_message_kind=-1; g_lane_check_index=0; g_pickup_message_timer=0;
        vars->f34E=0; vars->f34C=0;
        i=0; base=g_ship_slot_array_start;
        if(base<g_ship_slot_array_end) do {
            int class_id;
            Obj_15D0 *child;
            child=(Obj_15D0 *)(base+i*256);
            class_id=child->fAA;
            if(class_id==0x27D) found=child;
            if(class_id==0xE0B) ref_L22_003A15D0_00=child;
            if(class_id==0x133A) child->f34|=0x41;
            if(child->fAA==0xF6E) {
                Sub_15D0 *sub;
                g_space_ship_target_moby=child; child->f30=255;
                sub=(Sub_15D0 *)g_space_ship_target_moby->f68;
                sub->f8=0; sub->fA=0; sub->fC=-1;
            }
            i++;
            base=g_ship_slot_array_start;
        } while(base+i*256<g_ship_slot_array_end);
        vec.q=0; vec.f[0]=0.00161f; vec.f[1]=0.29459f; vec.f[2]=1.57105f;
        qcopy(&g_hero_state.rotation,&vec); qcopy(&g_hero_state.position,(char *)found+0x10);
        g_hero_state.health=vars->f324;
        FastVecSub(&vec,(char *)obj+0x10,(char *)&g_hero_state.rotation+0x20);
        g_planet_radius=FastVecLength(&vec);
        obj->f34|=0x100;
        random_roll=math_random_int_below(25);
        eight=8;
        vars->fD7=1; vars->f70=37; vars->f71=4;
        vars->f77=eight; vars->f72=eight; vars->f76=eight;
        vars->fCC=9; vars->fCD=18; vars->fCE=9; vars->fCF=18; vars->fD2=-1; vars->fD3=-1;
        health=(float)g_space_ship_max_health;
        range_scale=900.0f/health; damage_scale=9.0f/health;
        vars->f7C=0.70000005f; vars->f80=0.080000006f;
        vars->f84=0.060000002f; vars->f88=0.120000005f;
        vars->f8C=0.024f; vars->f90=3; vars->f94=4;
        vars->f9C=0.4f; vars->fA8=eight;
        vars->fBC=range_scale; vars->fB8=damage_scale;
        vars->f130=0.0064000003f; vars->f134=0.0064000003f;
        vars->f138=0.24000001f; vars->f110=2.5f; vars->f114=0.75f;
        vars->f120=2; vars->f118=2.75f; vars->f144=0; vars->f380=random_roll;
        vars->f11C=2.75f; vars->f1F8=12; vars->f1F9=11;
        { float health=(float)g_space_ship_max_health;
        vars->f148|=1; vars->f140=0.7853982448577881f;
        vars->f28=3; vars->f26=50;
        vars->f20=health;
        vars->f24=(int)health; }
        alpha=255; obj->f32=alpha; obj->f30=alpha; obj->f48=1.0f;
        vars->f374=-1; vars->f382=-1; vars->f35C=-1; vars->f35A=-1; vars->f358=-1;
        vars->f3EC=-1; vars->f4E4=250;
        vars->f3E4=vars->f3E8=0.0f; vars->f388=0;
        vars->f378=0; vars->f37C=0; vars->f37A=0;
        vars->f35E=0; vars->f350=0;
        obj->f34|=0x4000;
        obj->f2C=obj->f24->f24*g_space_ship_part_scale_b;
        lane_build_connection_masks(obj); pickup_spawn_initial((char *)obj);
        vars->f440=CreateMoby(0xE0A); set_identity_rotation_rows((char *)vars->f440+0xC0);
        vars->f444=CreateMoby(0xE0C); vars->f448=CreateMoby(0xF8F);
        vars->f384=25; vars->f43A=0;
    }
    level_store_value_pair_pal(level_call_helper_return_true,DrawSpaceCombatHud);
    if(vars->f440) {
        vars->f440->f32=obj->f32; vars->f440->f30=obj->f30;
        vars->f440->f38=obj->f38;
        vars->f440->f78=obj->f78;
        vars->f440->f31=1;
        child=vars->f440; child->f2C=child->f24->f24*g_space_ship_part_scale_b;
        child=vars->f440;
        if(child->f31 && fast_vec_dist((char *)child+0x10,g_tether_origin)<24.0f) {
            moby_update_ground_check(vars->f440); vars->f440->f6F=22;
        }
    }
    if(vars->f444) {
        vars->f444->f32=80; vars->f444->f30=obj->f30;
        vars->f444->f38=obj->f38;
        vars->f444->f78=obj->f78;
        vars->f444->f31=1;
        child=vars->f444; child->f2C=child->f24->f24*g_space_ship_part_scale_b;
    }
    if(vars->f448) {
        vars->f448->f32=80; vars->f448->f30=obj->f30;
        vars->f448->f38=obj->f38;
        vars->f448->f78=obj->f78;
        vars->f448->f31=1;
        child=vars->f448; child->f2C=child->f24->f24*g_space_ship_part_scale_a;
        func_002A0F48(vars->f448);
    }
    cam_compute_view_direction((char *)obj+0x10,(char *)vars+0x200,0); vec_negate_and_forward((char *)obj+0xC0,(char *)vars+0x200,0); moby_apply_damage_to_object_pal(obj,(char *)vars+0x60,0);
    obj->f2C=obj->f24->f24*g_space_ship_part_scale_b;
    if(g_space_ship_timer) {
        if(++g_space_ship_timer>32000) g_space_ship_timer=1;
        g_hero_state.mode=8;
        if(obj->f95!=1) {
            vars->f350=0; vars->f3E4=vars->f3E8=0.0f; moby_set_state(obj,1,1);
        }
        if(g_pad_state.buttons&0x50) {
            g_space_ship_timer=0; moby_set_state(obj,5,0); g_pad_state.buttons=0; g_hero_state.mode=17;
        } else if(g_space_ship_timer<30) {
            g_hero_state.field2294=0; cancel_hero_item_animation_pal();
            release_moby_animation_slot(g_hero_state.field2290,&g_hero_state.field1870);
            g_hero_state.field187C=0; hero_l22_set_move_state_pal(0,1);
        }
    } else if(g_hero_state.health<=0 && obj->f95!=1) {
        vars->f350=0; vars->f3E4=vars->f3E8=0.0f;
        moby_set_state(obj,2,1); vars->f384=25;
    }
    if(obj->f31 && fast_vec_dist((char *)obj+0x10,g_tether_origin)<24.0f) {
        moby_update_ground_check(obj); obj->f6F=22;
    }
}
