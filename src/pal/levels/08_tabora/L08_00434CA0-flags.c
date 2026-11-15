#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern void moby_set_state(void *,int,int);
extern float FastAddRotations(float,float);
extern char *part_find_owned_effect_slot(void *,int,int);
extern float func_PAL_002AA108(void *,void *);
extern void func_PAL_002AC290(void *,void *);
extern void func_PAL_002AC3C0(void *,void *);
extern int PlayMobySound(int,int,void *);
extern void set_moby_color(void *,int,int,int);
extern int moby_count_group_not_in_state(int,int);
extern int math_random_int_range(int,int);
extern void func_PAL_L00_00323918(void *,int,int,int,int,int,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void func_PAL_002B15D8(void *,int,void *,float,float,float,float,int);
extern void moby_mark_spawned(void *);
extern int g_active_emitter_count __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern int D_L08_002B35C0[];

void func_PAL_L08_00435540(char *a) {
    char *q=*(char **)(a+0x68);
    float hit;
    float v[4] __attribute__((aligned(16)));
    int id;
    switch(*(u8 *)(a+0x20)) {
    case 0:
        *(s16 *)(q+0x24)=5;
        *(float *)(q+0x20)=5.0f;
        moby_set_state(a,1,-1);
        break;
    case 1:
        *(float *)(a+0xF8)=FastAddRotations(*(float *)(a+0xF8),*(float *)(q+0x64)*0.0003490659f);
        hit=func_PAL_002AA108(a,part_find_owned_effect_slot(a,0x230000,0));
        if(hit>0.0f) {
            *(u8 *)(q+0x57)=255;
            *(u8 *)(q+0x58)=128;
            *(u8 *)(q+0x59)=128;
            func_PAL_002AC290(a,q+0x50);
            if(g_active_emitter_count<4) *(float *)(q+0x20)-=hit;
        }
        if(*(float *)(q+0x20)<0.0f) {
            PlayMobySound(0,0,a);
            moby_set_state(a,2,-1);
        }
        func_PAL_002AC3C0(a,q+0x50);
        *(u8 *)(a+0xA8)=255;
        break;
    case 2:
        set_moby_color(a,*(u8 *)(q+0x54),*(u8 *)(q+0x55),*(u8 *)(q+0x56));
        if(moby_count_group_not_in_state(*(u8 *)(a+0x21),-1)==1) {
            id=*(int *)((g_current_map_index << 2)+(char *)D_L08_002B35C0)*35-1;
            func_PAL_L00_00323918(a,id,id,3,-1,math_random_int_range(1,3),0.0f);
        }
        *(u128 *)v=0;
        v[0]=0.14000002f; v[1]=0.080000006f;
        matrix_mul_vec3(v,v,a+0xC0);
        if(*(u8 *)(a+0x31)) func_PAL_002B15D8(a,255,v,3.0f,6.0f,3.0f,6.0f,255);
        else func_PAL_002B15D8(a,170,v,3.0f,6.0f,3.0f,6.0f,255);
        moby_mark_spawned(a);
        break;
    }
}
