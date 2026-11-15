#include "include_asm.h"

#include "common.h"
extern void func_PAL_L01_003D1FD0(u8 *);
extern void swamp_monster_release_timers(u8 *);
extern void func_PAL_002A7E68(void *,int,int,int);
extern u8 *D_L01_001B255C_base[] __asm__("D_L01_001B255C") __attribute__((sda));
extern void swamp_monster_init_linked_body_part(u8 *);
extern void func_PAL_L01_003CFDB0(u8 *, int, int, int);
extern u8 *D_L01_001FE180[];
extern int math_random_int_below(int);
extern void script_queue_keyed_request(int,int);
extern void moby_set_state(u8 *,int,int);
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void vec_fast_divide_helper(void *,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern float mat_fast_helper_a(float,float);
extern float FastVecLength(void *);
extern float MobySpringTurn(void *,void *,float,float,float,float);
extern int point_in_path_xy(void *,void *,int);
extern s32 math_closest_point_on_polygon_edge(void *,void *,void *,int);
extern void moby_set_byte_on_group(int,int);
extern void func_PAL_002A7650(void *,int,int);
extern void moby_mark_spawned(void *);

/* Steps the owner state, moving along its path and releasing expired objects.
 * Separate unit for the jump table and small-data entity-base access. */
void func_PAL_L01_003D2350(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    float f;
    func_PAL_L01_003D1FD0(a0);
    switch (a0[0x95]) {
    case 0:
        swamp_monster_init_linked_body_part(a0);
        break;
    case 1:
        if (a0[0x60] & 2) {
            if (a0[0x42] != 2 && !math_random_int_below(15)) {
                if (a0[0x43] != 2) func_PAL_002A7E68(a0,2,0,10);
            } else if (a0[0x43] != 1) func_PAL_002A7E68(a0,1,0,10);
        }
        if (*(int *)(state+0xBC)) {
            script_queue_keyed_request(*(int *)(state+0xD0),*(int *)(state+0xD8));
            if (a0[0x43]!=1) func_PAL_002A7E68(a0,1,0,10);
            moby_set_state(a0,0,5);
        }
        break;
    case 2:
        if (!math_random_int_below(5)) func_PAL_L01_003CFDB0(a0,3,10,1);
        if (a0[0x60] & 2) {
            *(u16 *)(a0+0x34) &= 0xEFFF;
            if (a0[0x43]) func_PAL_002A7E68(a0,0,0,10);
            *(float *)(a0+0x48)=0.0f;
            moby_set_state(a0,0,4);
        }
        break;
    case 3:
        if (!math_random_int_below(5)) func_PAL_L01_003CFDB0(a0,3,10,1);
        if (a0[0x60] & 2) {
            *(u16 *)(a0+0x34) |= 0x1000;
            if (a0[0x43]!=1) func_PAL_002A7E68(a0,1,0,10);
            moby_set_state(a0,0,5);
        }
        break;
    case 4:
        if (*(int *)(state+0xBC)>0) {
            *(float *)(a0+0x48)=1.0f;
            if (a0[0x43]) func_PAL_002A7E68(a0,0,0,10);
            moby_set_state(a0,0,3);
        }
        break;
    case 5:
        if (a0[0x60] & 2) {
            if (a0[0x42] != 2 && !math_random_int_below(15)) {
                if (a0[0x43] != 2) func_PAL_002A7E68(a0,2,0,10);
            } else if (a0[0x43] != 1) func_PAL_002A7E68(a0,1,0,10);
        }
        {
            if (!*(int *)(state+0xBC)) qcopy(state+0x70,state+0x60);
            FastVecSub(v,state+0x70,a0+0x10);
            vec_fast_divide_helper(v,v,0.060000002f);
            FastVecAdd(a0+0x10,a0+0x10,v);
            f=mat_fast_helper_a(*(float *)(state+0x80)-*(float *)(a0+0x10),*(float *)(state+0x84)-*(float *)(a0+0x14));
            MobySpringTurn(a0,state+0xB8,f,0.0016755164f,0.1f,0.12566373f);
            if (!*(int *)(state+0xBC)) {
                script_queue_keyed_request(*(int *)(state+0xD4),*(int *)(state+0xDC));
                *(u16 *)(a0+0x34) &= 0xEFFF;
                if (a0[0x43] != 3) func_PAL_002A7E68(a0,3,0,20);
                moby_set_state(a0,0,2);
            }
        }
        break;
    case 6:
        FastVecAdd(v,a0+0x10,state+0x90);
        if (point_in_path_xy(v,D_L01_001FE180[*(int *)(state+0xA8)]+0x10,*(int *)D_L01_001FE180[*(int *)(state+0xA8)]))
            qcopy(a0+0x10,v);
        else {
            math_closest_point_on_polygon_edge(a0+0x10,v,D_L01_001FE180[*(int *)(state+0xA8)]+0x10,*(int *)D_L01_001FE180[*(int *)(state+0xA8)]);
            FastVecSub(w,state+0x60,a0+0x10);
            vec_scale_to_length(w,w,0.040000003f);
            FastVecAdd(a0+0x10,a0+0x10,w);
        }
        f=FastVecLength(state+0x90)-0.0044f;
        if (f<0.0f) f=0.0f;
        vec_scale_to_length(state+0x90,state+0x90,f);
        if (*(float *)(state+0x20)<=0.0f && !math_random_int_below(4)) func_PAL_L01_003CFDB0(a0,3,10,1);
        if (a0[0x60]&2) {
            if (*(float *)(state+0x20)<=0.0f) {
                *(u16 *)(a0+0x34) &= 0xEFFF;
                moby_set_state(a0,0,7);
            } else {
                *(u16 *)(a0+0x34) |= 0x1000;
                if (a0[0x43]!=1) func_PAL_002A7E68(a0,1,0,10);
                moby_set_state(a0,0,5);
            }
        }
        break;
    case 7:
        script_queue_keyed_request(*(int *)(state+0xD4),*(int *)(state+0xDC));
        if (*(int *)(state+0xB0)!=-1) moby_set_byte_on_group(*(int *)(state+0xB0),1);
        func_PAL_002A7650(a0,0x200,3);
        if (*(int *)(state+0xCC)!=-1) moby_mark_spawned(D_L01_001B255C_base[0]+(*(int *)(state+0xCC)<<8));
        *(int *)(state+0xCC)=-1;
        moby_mark_spawned(a0);
        return;
    }
    swamp_monster_release_timers(a0);
}
