#include "include_asm.h"

#include "common.h"
extern void func_002E6EF8(void (*f)(char *), char *arg);
extern char *func_PAL_L00_0041D8A8(void *pos, int a, int b, int c, int d, int e, int f, int g, int h,
                              int k, float scale);
extern float math_random_float_range(float lo, float hi);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float a, float b);
extern int math_random_int_range(int lo, int hi);
extern void vec_build_spherical_offset(void *out, float x, float y, float z);
extern void FastVecSub(void *out, void *a, void *b);
extern void FastVecAdd(void *out, void *a, void *b);
extern void vec_scale_to_length(void *out, void *a, float scale);
extern void *func_PAL_L00_00340CA0(void *pos, void *velocity, float speed, float size,
                              unsigned int colour, unsigned int colour2, int life, int a, int b,
                              int c, int d);
extern char g_camera_l00_position[];

/* one func_PAL_L00_0041D8A8 effect at pos, then two func_PAL_L00_00340CA0 particles with random
   velocities; before each, pos moves 0.3 of the way towards D_L00_001B8DC0 (FastVecSub,
   scale, FastVecAdd) */
void func_PAL_L00_00408D50(float *pos, int unused, int mode)
{
    float velocity[4], offset[4], point[4];
    float pitch, heading, speed;
    int i;

    func_PAL_L00_0041D8A8(pos, 0, 15, 10, 0, 20, 0, 0, 1, 0, 0.1f);
    for (i = 0; i < 2; i++) {
        pitch = math_random_float_range(-0.9599312f, -1.3962636f);
        heading = math_random_angle();
        speed = math_random_float_range(0.0f, 0.5f);
        vec_build_spherical_offset(velocity, speed * 0.020000001f, heading, pitch);
        FastVecSub(offset, g_camera_l00_position, pos);
        vec_scale_to_length(offset, offset, 0.3f);
        FastVecAdd(pos, pos, offset);
        speed = math_random_float_range(25000.0f, 50000.0f);
        point[0] = pos[0] + math_random_signed_float_range(0.0f, 0.02f);
        point[1] = pos[1] + math_random_signed_float_range(0.0f, 0.02f);
        point[2] = pos[2] + math_random_signed_float_range(0.0f, 0.02f);
        if (mode)
            func_PAL_L00_00340CA0(point, velocity, speed, 0.1f, 0x78ffffff, 0x101e1e1e,
                              math_random_int_range(8, 17), 1, 1, -1, 1);
        else
            func_PAL_L00_00340CA0(point, velocity, speed, 0.1f, 0x78ffffff, 0x101e1e1e,
                              math_random_int_range(21, 50), 1, 1, -1, 1);
    }
}


typedef int TI128 __attribute__((mode(TI)));
extern void FastVecAdd(void *,void *,void *),vec_transform_or_copy(char *,char *);
extern void part_steer_effect_direction(int,int *,int),table_clear_entry_flag(int),moby_mark_spawned(char *);
extern void ref_L00_004045E8_00(void (*)(char *),char *);
extern void shop_trigger_current_state_effect(void *,void *),vec_add_object_direction_scaled(void *,void *,float);
extern void shot_handle_impact(void *,void *),func_PAL_L00_004098C0(void *,void *,void *),shot_draw_glow_sparks(char *);
extern char *func_PAL_L00_0041A788(void *,float,int,int,int,int,int,int,int,int,int);
extern int coll_process_hit(void *,int,void *,int,float);
extern char *g_area_hit_targets[];
extern char g_item_slot_to_record[],g_weapon_l00_table[],D_L00_001C6F40[];
extern void FastVecSub(void *,void *,void *),vec_scale_to_length(void *,void *,float);
extern void make_hit_descriptor(void *,void *,float,int,void *),QueueMobyImpact(void *,void *);
extern void gfx_free_point_light(int);
extern int func_PAL_0032F0B8(void *,int,int);
extern int part_l00_alloc_effect_slot_2(void *,float,float,float,float,float);

/* Moves a projectile, applies its explosion hit to nearby objects, and updates
 * its persistent trail record while active. */
void func_PAL_L00_00408FD0(char *arg)
{
    float old[4],delta[4];
    char hit[48] __attribute__((aligned(16)));
    char *ctx=*(char **)(arg+104);
    int n, count, boosted;
    char **objects;
    char *obj,*entry,*power;
    float force;
    switch (*(unsigned char *)(arg+32)) {
    case 0:
        *(int *)(ctx+24)=-1;
        *(unsigned char *)(arg+32)=1;
        *(float *)(ctx+28)=math_random_angle();
        break;
    case 1:
        qcopy(old,arg+16);
        FastVecAdd(arg+16,(int *)ctx,arg+16);
        vec_transform_or_copy(arg+16,arg+16);
        shop_trigger_current_state_effect(ctx,ctx);
        part_steer_effect_direction(*(int *)(ctx+48),(int *)ctx,0);
        vec_add_object_direction_scaled(arg+16,ctx,0.0012f);
        shot_handle_impact(arg,old);
        if (*(float *)(arg+16)<2.0f || *(float *)(arg+16)>1021.0f ||
            *(float *)(arg+20)<2.0f || *(float *)(arg+20)>1021.0f ||
            *(float *)(arg+24)<2.0f || *(float *)(arg+24)>1021.0f) {
            table_clear_entry_flag(*(int *)(ctx+48));
            moby_mark_spawned(arg);
            return;
        }
        break;
    case 2:
        func_PAL_L00_0041A788(arg+16,0.5f,1,50,40,40,40,90,1,1,1);
        n=coll_process_hit(arg+16,0,arg,0,3.0f);
        if(n>0) {
            objects=g_area_hit_targets;
            count=n;
            do {
                obj=*objects;
                if (*(short *)(*(char **)(obj+36)+70)==5 || (*(unsigned short *)(obj+52)&0x4000)) {
                    FastVecSub(delta,obj+16,arg+16);
                    vec_scale_to_length(delta,delta,1.0f);
                    vec_scale_to_length(hit,hit,1.0f);
                    force=10.0f;
                    power=g_weapon_l00_table+224*(unsigned char)g_item_slot_to_record[32];
                    boosted=*(int *)power && (unsigned char)power[4]==3;
                    if(boosted) force=20.0f;
                    make_hit_descriptor(hit,arg,force,0x810000,delta);
                    *(TI128 *)(hit)=*(TI128 *)(delta);
                    *(float *)(hit+12)=5627.9248046875f;
                    hit[25]=3; *(int *)(hit+32)=1; hit[24]=5;
                    *(unsigned short *)(hit+26)=*(unsigned short *)(obj+170);
                    QueueMobyImpact(obj,hit);
                    func_PAL_0032F0B8(obj,78,*(int *)(*(char **)(ctx+52)+184));
                }
                objects++;
            } while(--count);
        }
        if (*(int *)(ctx+24)!=-1) gfx_free_point_light(*(int *)(ctx+24));
        *(int *)(ctx+24)=-1;
        /* Fall through to the shared teardown. */
    case 3:
        table_clear_entry_flag(*(int *)(ctx+48));
        moby_mark_spawned(arg);
        return;
    }
    ref_L00_004045E8_00(shot_draw_glow_sparks,arg);
    *(TI128 *)(delta)=*(TI128 *)(arg+16);
    func_PAL_L00_004098C0(arg,delta,old);
    FastVecAdd((char *)delta,arg+16,ctx+32);
    FastVecAdd(hit,(char *)old,ctx+32);
    func_PAL_L00_004098C0(arg,delta,hit);
    if (*(int *)(ctx+24)==-1)
        *(int *)(ctx+24)=part_l00_alloc_effect_slot_2(arg+16,5.0f,0.0f,1.0f,0.8f,0.25f);
    else {
        entry=D_L00_001C6F40+32**(int *)(ctx+24);
        qcopy(entry+16,arg+16);
        *(float *)(entry+24)+=1.0f;
        *(float *)(entry+28)=5.0f;
        *(float *)entry=1.0f; *(float *)(entry+4)=0.8f;
        *(float *)(entry+8)=0.25f; *(int *)(entry+12)=0;
    }
}

