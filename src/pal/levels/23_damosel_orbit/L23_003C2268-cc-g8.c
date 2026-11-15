/* func_PAL_L23_003C2268, the PAL copy of func_L23_003BEA00: the same C, where rename func_L23_003BF9B0 becomes func_PAL_L23_003C3258; rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_L23_003BFFC0 becomes func_PAL_L23_003C3868; rename func_L23_003C00D0 becomes func_PAL_L23_003C3978; rename func_L23_003C01F8 becomes func_PAL_L23_003C3AA0; rename func_L23_003C1B58 becomes func_PAL_L23_003C5480; rename func_L11_003404E0 becomes func_PAL_L11_00342558; rename func_L23_003C02C8 becomes func_PAL_L23_003C3B70; rename func_002AEB60 becomes func_PAL_002AF6C0; rename func_L23_003BFE90 becomes func_PAL_L23_003C3738; rename func_L23_003C16D8 becomes func_PAL_L23_003C4FC0; rename func_L23_003C1AE8 becomes func_PAL_L23_003C5410; .... */
#include "common.h"

/* func_PAL_L23_003C2268 is a unit of its own: it reads $gp (hence -g8) and has a switch.
   Two return types decide its bytes, and both are the callees' real ones:
   - func_PAL_L11_00342558 returns int: it leaves func_L02_00333480's status in v0, which that function
     sets on every path. A call's unused result still occupies v0 for a local set by the next insn,
     so the f110 test right after the call loads into v1 as retail does.
   - func_002A8F70 is void (002A7750-records.c): a result would change the post-reload ranking of
     its argument setup. */

typedef int Quad __attribute__((mode(TI)));
typedef struct Moby_003BF9B0 Moby_003BF9B0;
typedef struct {
    u8 reserved_00[0x18]; u8 enabled,count,kind;
    u8 reserved_1b[0x65]; u8 payload[1];
} Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext;
typedef struct {
    u8 pad_000[0x26];
    short f26;
    u8 pad_028[0x10];
    char * f38;
    u8 pad_03C[0xD4];
    short f110;
    u8 pad_112[0x62];
    float f174;
    unsigned short f178;
    u8 pad_17A[0xD6];
    int f250;
    u8 pad_254[0x1C];
    float f270;
    u8 pad_274[0x8];
    float f27C;
    u8 pad_280[0x20];
    char * f2A0;
    short f2A4;
    short f2A6;
    float f2A8;
    u8 pad_2AC[0x74];
    char * f320;
    short f324;
    short f326;
    char * f328;
    char * f32C;
    u8 pad_330[0x84];
    int f3B4;
    float f3B8;
    short f3BC;
    short f3BE;
} DispatchState;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
extern int D_L23_001B1424,D_L23_001B36F0;
extern u8 *D_L23_001B36B0;
typedef struct { u8 pad00[0x80]; float position[4] __attribute__((aligned(16))); u8 pad90[0x2200]; u8 *object; } DispatchHero;
extern DispatchHero g_hero_state;
extern u8 *g_hero_moby __attribute__((nosda));
extern float D_L23_001B36A4,D_L23_001B36F4,D_L23_001B36F8;
extern float D_L23_001B36D0[4] __attribute__((aligned(16))) MACRO_ADDR;
extern float D_L23_001C0AA0[] __attribute__((aligned(16)));
extern u8 D_00189F00[];
extern float D_L23_001B3708;
extern float D_L23_001AFA14 __attribute__((sda));
extern int D_L23_001AFA38 __attribute__((sda));
extern float D_L23_001AFA4C __attribute__((sda));
extern float D_L23_001AFA58 __attribute__((sda));
extern float D_L23_001AFA5C __attribute__((sda));
extern float D_L23_001AFA60 __attribute__((sda));
extern float D_L23_001AFA6C __attribute__((sda));
extern float D_L23_001AFA78 __attribute__((sda));
extern float D_L23_001AFA80 __attribute__((sda));
extern float D_L23_001AFA88 __attribute__((sda));
extern float D_L23_001AFA8C __attribute__((sda));
extern float D_L23_001AFA90 __attribute__((sda));
extern int D_L23_001AFA94 __attribute__((sda));
extern int D_L23_001AFA98 __attribute__((sda));
extern int D_L23_001AFA9C __attribute__((sda));
extern void func_PAL_L23_003C3258(Moby_003BF9B0 *);
extern int boss_is_fight_state_four(void),boss_pick_random_ready_attack(void);
extern int part_start_effect_default_table(int,int,int,int,float);
extern void part_queue_impact_effect(int,int,int,int,int,float);
extern int coll_sweep_from_object(void *,void *,int,int,int,int,float,float,float);
extern u8 *func_PAL_L00_003FB330(void *,int,int,int,int,int,int,int,float,float,int,int,int,void *);
extern void moby_clear_selected(char *),moby_stop_effects(char *);
extern void moby_reset_idle_clear_links(char *),func_PAL_L23_003C3978(char *);
extern void func_PAL_L23_003C5480(char *),func_PAL_L23_003C5410(char *);
extern void func_PAL_L23_003C4FC0(char *),moby_tick_timers(char *);
extern void gfx_draw_pulsing_beam(void *);
extern void func_PAL_L23_003C3AA0(char *,int);
extern void func_PAL_L23_003C3B70(u8 *);
extern float gravity_get_center_distance(char *);
extern void FastVecSub(void *,void *,void *);
extern float moby_measure_step_angle(char *,Quad *,char *);
extern float fast_vec_dist(void *,void *),FastVecLength(void *);
extern int IsPathClear(void *,void *,void *);
extern void mothership_project_point_onto_surface(char *,float);
extern unsigned long moby_dispatch_action_by_kind(void *,Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *);
extern void snd_stop_voice(int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float),FastVecScale(void *,void *,float);
extern int snd_play_from_class_bank(int,int,char *,int);
extern void stored_object_forward(int,int);
extern int flag_set_first_pending(u8 *),flag_set_second_pending(u8 *);
extern int snd_start_in_slot(int,int,int);
extern void func_PAL_L23_003C3868(char *,int,int,int,int,float);
extern void func_PAL_L23_003C3738(char *,float,int,int);
extern void moby_set_state(u8 *,s32,int);
extern void gfx_add_draw_callback_first(void (*)(void *),void *);
extern int func_PAL_L11_00342558(char *);
extern int CollLine(void *,void *,int,void *,void *);
extern float moby_get_anim_value(char *),math_random_float_range(float,float);
extern int func_PAL_002AF6C0(char *,float);
extern void *ribbon_trail_create(u8 *,u8 *,u8 *,u8,u8,float,float,float,float,short,short,int,int,int,int,int);
extern void moby_transform_joint_to_world(char *,int,char *);
extern int queue_copy_record_by_index(unsigned int);

void func_PAL_L23_003C2268(u8 *object)
{
    float difference[4] __attribute__((aligned(16))),point[4] __attribute__((aligned(16))),local[4] __attribute__((aligned(16)));
    char *state=*(char **)(object+0x68);
    int facing,selected,index,mask;
    unsigned long flags;
    float distance,range;
    func_PAL_L23_003C3258((Moby_003BF9B0 *)object);
    if (D_L23_001B1424>200) return;
    if (boss_is_fight_state_four())
        part_start_effect_default_table((int)object,(int)object,0x10000,(int)(object+0x10),(float)D_L23_001B36F0);
    selected=D_L23_001B36B0==object;
    facing=0;
    ((DispatchState *)state)->f326=0;
    if (selected && (unsigned int)(object[0x20]-9)>2)
        moby_clear_selected((char *)object);
    if (object[0x20]!=13) {
        ((DispatchState *)state)->f270=gravity_get_center_distance((char *)object+0x10);
        FastVecSub(difference,g_hero_state.position,object+0x10);
        if (moby_measure_step_angle((char *)object,(Quad *)difference,0)<=0.7853982f) facing=1;
        distance=fast_vec_dist(g_hero_state.position,object+0x10);
        range=D_L23_001AFA6C;
        ((DispatchState *)state)->f27C=distance;
        ((DispatchState *)state)->f324=0;
        if (distance<range)
            ((DispatchState *)state)->f324=IsPathClear(object,object+0x10,g_hero_state.position);
        qcopy((state+0x300), (object+0x10));
        mothership_project_point_onto_surface(state+0x300,0.0f);
    }
    if (object[0x95]==3) {
        flags=moby_dispatch_action_by_kind(object,(Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *)(state+0x140));
        if (((DispatchState *)state)->f3B4!=-1) {
            snd_stop_voice(((DispatchState *)state)->f3B4); ((DispatchState *)state)->f3B4=-1;
        }
        if (object[0x43]==8 && FastVecLength(state+0x1C0)>0.0f) {
            if (((DispatchState *)state)->f270<D_L23_001B36A4) mothership_project_point_onto_surface((char *)object+0x10,0.0f);
            *(Quad *)local=0; local[2]=((DispatchState *)state)->f174;
            *(Quad *)point=*(Quad *)local;
            matrix_mul_vec3(point,point,object+0xC0);
            FastVecAdd(point,point,object+0x10);
            vec_scale_to_length(difference,state+0x1C0,4.0f);
            FastVecAdd(point,point,difference);
            coll_sweep_from_object(object,point,0x90000,0,1,0,5.0f,100.0f,0.0f);
        }
        if ((((DispatchState *)state)->f178&1) && ((DispatchState *)state)->f2A4==0) {
            snd_play_from_class_bank(5,0,(char *)object,0x7E5);
            func_PAL_L00_003FB330(((DispatchState *)state)->f2A0+0x10,1,35,20,20,20,45,1,2.5f,20.0f,1,0,0,0);
            ((DispatchState *)state)->f2A4=1;
            if (((DispatchState *)state)->f38==(char *)g_hero_state.object) {
                qcopy(difference, (object+0x10));
                mothership_project_point_onto_surface((char *)difference,0.0f);
                index=boss_pick_random_ready_attack();
                if (index!=-1) stored_object_forward((int)g_hero_state.position,index);
            }
            qcopy((object+0x10), g_hero_state.position);
            mothership_project_point_onto_surface((char *)object+0x10,(-D_L23_001B36A4)*2.0f);
        }
        if ((flags & 1UL) == 1UL) moby_reset_idle_clear_links((char *)object);
        else if (flag_set_first_pending(object) && object[0x43]==8) {
            snd_start_in_slot(31,0,0);
            func_PAL_L23_003C3868((char *)object,8,0,3,2,1.0f);
            ((DispatchState *)state)->f26=21; ((DispatchState *)state)->f2A6=0;
            func_PAL_L00_003FB330(((DispatchState *)state)->f2A0+0x10,0,10,15,15,15,15,0,1.0f,20.0f,0,0,0,0);
        } else if ((flags & 2UL) == 2UL) moby_set_state(object,5,0);
    }
    switch (object[0x20]) {
    case 5:
        if (flag_set_second_pending(object)) {
            func_PAL_L23_003C3868((char *)object,3,0,3,3,1.0f);
            if (((DispatchState *)state)->f3B4!=-1) { snd_stop_voice(((DispatchState *)state)->f3B4); ((DispatchState *)state)->f3B4=-1; }
        }
        if (U(object,0x96)>7) moby_set_state(object,7,1);
        else if (U(object,0x96)>=9) {
            mask=0;
            if (object[0x43]!=3) mask|=1;
            if (((u8 *)((DispatchState *)state)->f2A0)[0x43]!=3) mask|=2;
            if (mask) func_PAL_L23_003C3868((char *)object,3,0,17,mask,1.0f);
            func_PAL_L11_00342558((char *)object);
        }
        break;
    case 1:
        if (flag_set_second_pending(object)) func_PAL_L23_003C3978((char *)object);
        else if (U(object,0x96)>=5) moby_set_state(object,3,0);
        break;
    case 2:
        I(object,0x98)=0;
        if (flag_set_second_pending(object)) {
            func_PAL_L23_003C3978((char *)object);
            func_PAL_L23_003C3868((char *)object,9,0,0,1,1.0f);
            func_PAL_L23_003C3868((char *)object,1,0,0,2,1.0f);
            func_PAL_L23_003C3AA0((char *)object,1);
            ((DispatchState *)state)->f3BC=1; ((DispatchState *)state)->f3B8=(float)D_L23_001AFA38;
        }
        gfx_add_draw_callback_first(gfx_draw_pulsing_beam,object);
        break;
    case 6:
        func_PAL_L23_003C5480((char *)object); break;
    case 3:
        if (flag_set_second_pending(object) && object[0x43]!=1)
            func_PAL_L23_003C3868((char *)object,1,0,3,3,1.0f);
        func_PAL_L11_00342558((char *)object);
        if (((DispatchState *)state)->f110) {
            moby_set_state(object,5,0);
            func_PAL_L23_003C3868((char *)object,3,0,8,3,1.0f);
        } else {
            FastVecScale(point,object+0xE0,-3.0f);
            FastVecAdd(point,point,object+0x10);
            FastVecScale(difference,object+0xE0,0.2f);
            FastVecAdd(difference,difference,object+0x10);
            if (CollLine(difference,point,18,0,0) && fast_vec_dist(D_L23_001C0AA0,object+0x10)<4.0f)
                moby_set_state(object,4,0);
        }
        break;
    case 4:
        if (flag_set_second_pending(object) && object[0x43]!=2)
            func_PAL_L23_003C3868((char *)object,2,0,5,3,1.0f);
        else if ((object[0x60]&2) || moby_get_anim_value((char *)object)>12.0f) {
            moby_set_state(object,5,0);
            func_PAL_L23_003C3868((char *)object,3,0,17,3,1.0f);
        }
        func_PAL_L11_00342558((char *)object);
        break;
    case 7:
        if (flag_set_second_pending(object)) {
            ((DispatchState *)state)->f250=167;
            ((DispatchState *)state)->f2A8=D_L23_001AFA58+math_random_float_range(0.0f,D_L23_001AFA58*0.5f);
            ((DispatchState *)state)->f320=(char *)g_hero_state.position;
        }
        if (!object[0x31]) ((DispatchState *)state)->f2A8=D_L23_001AFA60;
        else if (((DispatchState *)state)->f2A8==D_L23_001AFA60)
            ((DispatchState *)state)->f2A8=D_L23_001AFA58+math_random_float_range(0.0f,D_L23_001AFA58*0.5f);
        if (((DispatchState *)state)->f250==0) moby_set_state(object,5,0);
        else if (((DispatchState *)state)->f324 && facing && ((DispatchState *)state)->f27C<D_L23_001AFA78)
            moby_set_state(object,8,2);
        else func_PAL_L23_003C3B70(object);
        break;
    case 8:
        if (flag_set_first_pending(object)) ((DispatchState *)state)->f2A8=D_L23_001AFA58+math_random_float_range(0.0f,D_L23_001AFA58*0.5f);
        if (((u8 *)((DispatchState *)state)->f2A0)[0x43]!=4) {
            func_PAL_L23_003C3868((char *)object,4,0,8,2,1.0f);
            F(((DispatchState *)state)->f2A0,0x48)=D_L23_001B3708;
        }
        if (!((DispatchState *)state)->f324 || ((DispatchState *)state)->f27C>D_L23_001AFA80) {
            moby_set_state(object,5,0); ((DispatchState *)state)->f250=0;
        } else if (((DispatchState *)state)->f27C>D_L23_001AFA88 ||
                   ((unsigned int)(object[0x43]-5)<2 && ((DispatchState *)state)->f27C>D_L23_001AFA88-2.0f)) {
            ((DispatchState *)state)->f320=(char *)g_hero_state.position; func_PAL_L23_003C3B70(object);
        } else {
            func_PAL_L23_003C3868((char *)object,3,0,8,1,1.0f); func_PAL_L11_00342558((char *)object);
        }
        if (func_PAL_002AF6C0(((DispatchState *)state)->f2A0,28.0f)) func_PAL_L23_003C3738((char *)object,D_L23_001B36F4+D_L23_001B36F4,(int)D_00189F00,0);
        else if (func_PAL_002AF6C0(((DispatchState *)state)->f2A0,14.0f)) func_PAL_L23_003C3738((char *)object,D_L23_001B36F4+D_L23_001B36F4,(int)D_00189F00,1);
        break;
    case 9:
        if (flag_set_first_pending(object)) {
            func_PAL_L23_003C3868((char *)object,6,0,10,1,D_L23_001AFA14);
            func_PAL_L23_003C3868((char *)object,8,0,10,2,4.0f);
            moby_stop_effects((char *)object);
            ((DispatchState *)state)->f328=ribbon_trail_create((u8 *)state+0x330,object,(u8 *)state+0x340,50,70,0.7f,0.85f,0.5f,1.2f,30,5,0x7F7F7F,0x7F7F7F,0,-1,0);
            ((DispatchState *)state)->f32C=ribbon_trail_create((u8 *)state+0x330,object,(u8 *)state+0x340,50,70,1.9f,2.05f,0.5f,1.2f,10,2,0x3F00000,0x3F0000,0,-1,0);
            ((DispatchState *)state)->f2A8=D_L23_001AFA5C;
            ((DispatchState *)state)->f3B4=snd_play_from_class_bank(4,4,(char *)object,0x7E5);
        }
        if (!((DispatchState *)state)->f324 || ((DispatchState *)state)->f27C>D_L23_001AFA80) {
            moby_set_state(object,5,0); ((DispatchState *)state)->f250=0; break;
        }
        moby_transform_joint_to_world(((DispatchState *)state)->f2A0,1,state+0x330);
        moby_transform_joint_to_world(((DispatchState *)state)->f2A0,0,state+0x340);
        if ((int)U(object,0x96)>D_L23_001AFA94) {
            ((DispatchState *)state)->f320=(char *)g_hero_state.position;
            if (((DispatchState *)state)->f27C<D_L23_001AFA8C) moby_set_state(object,10,2);
            func_PAL_L23_003C3B70(object);
        }
        break;
    case 10:
        if (!((DispatchState *)state)->f324 || ((DispatchState *)state)->f27C>D_L23_001AFA90) { moby_set_state(object,5,0); break; }
        moby_transform_joint_to_world(((DispatchState *)state)->f2A0,1,state+0x330);
        moby_transform_joint_to_world(((DispatchState *)state)->f2A0,0,state+0x340);
        if (flag_set_first_pending(object)) {
            moby_stop_effects((char *)object);
            ((DispatchState *)state)->f328=ribbon_trail_create((u8 *)state+0x330,object,(u8 *)D_L23_001B36D0,95,80,4.0f,4.25f,0.7f,1.3f,35,5,0x5F0000,0x5F2020,0,-1,0);
            ((DispatchState *)state)->f32C=ribbon_trail_create((u8 *)state+0x340,object,(u8 *)D_L23_001B36D0,95,80,4.0f,4.25f,0.7f,1.3f,35,5,0x5F0000,0x5F2020,0,-1,0);
            break;
        }
        if ((int)U(object,0x96)<=D_L23_001AFA98) break;
        FastVecAdd(difference,state+0x330,state+0x340);
        FastVecScale(difference,difference,0.5f);
        if (fast_vec_dist(difference,D_L23_001B36D0)<D_L23_001AFA4C) {
            vec_scale_to_length(point,((DispatchState *)state)->f2A0+0xE0,0.25f);
            FastVecAdd(point,point,((DispatchState *)state)->f2A0+0xC0);
            FastVecScale(point,point,15.0f); point[3]=5627.9248f;
            part_queue_impact_effect((int)g_hero_moby,(int)object,0x10007,(int)(object+0x10),(int)point,D_L23_001B36F8);
            queue_copy_record_by_index(43);
            func_PAL_L00_003FB330(D_L23_001B36D0,1,10,10,10,10,45,0,1.2f,20.0f,0,1,0,0);
            ((DispatchState *)state)->f3BE=1;
        }
        moby_set_state(object,11,2);
        break;
    case 11:
        if (flag_set_first_pending(object)) {
            if (((DispatchState *)state)->f3B4!=-1) { snd_stop_voice(((DispatchState *)state)->f3B4); ((DispatchState *)state)->f3B4=-1; }
        } else if ((int)U(object,0x96)>(((int)(D_L23_001AFA9C) * 5 + 2) / 6)) { moby_clear_selected((char *)object); moby_set_state(object,5,0); } else {
            if ((int)U(object,0x96)>=(((int)(D_L23_001AFA9C-5) * 5 + 2) / 6) && ((DispatchState *)state)->f3BE) {
                snd_start_in_slot(29,0,0); ((DispatchState *)state)->f3BE=0; queue_copy_record_by_index(43);
            }
        }
        break;
    case 12:
    case 13:
        break;
    }
    moby_tick_timers((char *)object);
    if (object[0x20]!=13) { func_PAL_L23_003C4FC0((char *)object); func_PAL_L23_003C5410((char *)object); }
}
