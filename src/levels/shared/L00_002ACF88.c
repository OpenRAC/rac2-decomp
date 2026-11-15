#include "common.h"
typedef int V4_Fbfdc087a __attribute__((mode(TI)));

typedef struct {
unsigned char pad0[464];
short cooldown;
unsigned char pad1d2[146];
float radius;
unsigned char pad268[180];
float groundHeight;
unsigned char pad320[382];
unsigned char pastApex;
unsigned char pad49f[1945];
float frame;
unsigned char padc3c[5716];
void * moby;
int state;
unsigned char pad2298[4];
int control;
unsigned char pad22a0[20];
unsigned char vehicle;
} LedgeProbeResident;
extern LedgeProbeResident g_hero_state;
/* Related ledge-probe flow: OpenRAC/rac1-decomp hero_idle_and_animation.c,
 * check_ledge_grab (GPL-3.0); this version uses oriented vector helpers. */
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float mat_fast_helper_a(float, float);
extern float cam_get_view_space_height(void *);
extern void cam_set_view_space_height(void *, void *, float);
extern float cam_get_view_space_angle(void *);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern char *moby_get_private_value_0(void *);
extern char *moby_get_private_value_2(void *);
extern int coll_test_point(void *, int, void *, float);
typedef struct {
    unsigned char pad0[0x18];
    void *moby;
    unsigned char pad1c[4];
    float position[4];
    unsigned char pad30[16];
    float normal[4];
} LedgeProbeHit;
extern LedgeProbeHit g_collision_result;
#define FL(p,o) (*(float *)((char *)(p)+(o)))
#define IN(p,o) (*(int *)((char *)(p)+(o)))
/* Checks whether the hero can grab a ledge in front of it. Returns 1 and fills in the grab position if it can. */
int hero_find_ledge_grab(void *position, void *unused, char *out)
{
    float probe_base[4], upper_point[4], lower_point[4], step_offset[4], scratch_offset[4], to_ledge[4], ledge_point[4], above_ledge[4], behind_ledge[4], probe_start[4], edge_step[4], probe_end[4], edge_normal[4], sweep_end_a[4], sweep_end_b[4], near_offset[4], far_offset[4], down_offset[4], sweep_point[4], back_offset[4];
    char *moby_data, *moby_info;
    void *object;
    int can_grab, found, i, kind, grabbable;
    int edge, j;
    float height;
    float step, max;
    float down, fwd, up, top, drop, rise, back, sweep_distance, length;
    if (out) IN(out,0x28)=0;
    if (g_hero_state.cooldown) return 0;
    can_grab=0;
    if (g_hero_state.vehicle==0) {
        if ((g_hero_state.control==4 && (g_hero_state.pastApex || cam_get_view_space_height((char *)&g_hero_state+0xf0)<0.05833333730697632f)) || g_hero_state.control==2 || g_hero_state.state==8 || g_hero_state.state==25 || g_hero_state.state==26) can_grab=1;
        if (g_hero_state.state==14 && g_hero_state.frame<37.0f) can_grab=0;
    }
    if (g_hero_state.vehicle==1) {
        if ((g_hero_state.control==4 && g_hero_state.pastApex) || g_hero_state.control==2 || g_hero_state.state==75 || g_hero_state.state==73 || g_hero_state.state==74) can_grab=1;
    }
    if (out != (char *)&g_hero_state+0x550) can_grab=1;
    if (!can_grab) return 0;
    down=-0.7f; fwd=0.3f; up=1.5f; top=1.15f; drop=-1.43f; rise=1.8f; back=0.5f;
    found=0;
    if (g_hero_state.vehicle==1) { down=-0.4f; fwd=0.25f; up=0.725f; top=0.7f; drop=-0.71f; rise=0.7f; back=0.32f; }
    qcopy(probe_base,position);
    vec_scale_to_length(scratch_offset,(char *)&g_hero_state,g_hero_state.radius);
    FastVecAdd(probe_base,probe_base,scratch_offset);
    vec_scale_to_length(scratch_offset,(char *)&g_hero_state+0x20,up+0.15f);
    FastVecAdd(upper_point,probe_base,scratch_offset);
    vec_scale_to_length(scratch_offset,(char *)&g_hero_state+0x20,-top);
    FastVecAdd(lower_point,probe_base,scratch_offset);
    vec_scale_to_length(step_offset,(char *)&g_hero_state,fwd*0.25f);
    for(i=0; i<4; i++) {
        FastVecAdd(upper_point,upper_point,step_offset);
        FastVecAdd(lower_point,lower_point,step_offset);
        if(CollLine(upper_point,lower_point,4,g_hero_state.moby,0)) {
            kind=GetCollHitMaterial();
            if(kind!=9 && kind!=12 && kind!=0 && cam_get_view_space_angle(g_collision_result.normal)<0.349065899848938f) found=1;
        }
        if(found) break;
    }
    object=0;
    if(!found) goto fail;
    if(g_collision_result.moby) {
        grabbable=0;
        moby_data=moby_get_private_value_0(g_collision_result.moby);
        moby_info=moby_get_private_value_2(g_collision_result.moby);
        if(moby_data && (*(unsigned short *)(moby_data+0x1e)&1)) grabbable=1;
        else if(moby_info) grabbable=IN(moby_info,0x3c)&1;
        if(!grabbable) return 0;
        object=g_collision_result.moby;
    }
    if(out) *(void **)(out+0x38)=g_collision_result.moby;
    qcopy(ledge_point,g_collision_result.position);
    FastVecSub(to_ledge,ledge_point,position);
    if(up<cam_get_view_space_height(to_ledge)) return 0;
    vec_scale_to_length(above_ledge,(char *)&g_hero_state+0x20,0.005f);
    FastVecAdd(above_ledge,above_ledge,ledge_point);
    vec_scale_to_length(behind_ledge,(char *)&g_hero_state,-1.0f);
    FastVecAdd(behind_ledge,behind_ledge,above_ledge);
    if(CollLine(behind_ledge,above_ledge,2,g_hero_state.moby,0)) {
        if(!g_collision_result.moby || g_collision_result.moby!=object) return 0;
    }
    if(out) {
        vec_scale_to_length(probe_start,(char *)&g_hero_state+0x20,0.6f);
        FastVecAdd(probe_start,probe_start,ledge_point);
        if(coll_test_point(probe_start,4,g_hero_state.moby,0.45f)) IN(out,0x34)|=1;
        else IN(out,0x34)&=~1;
    }
    height=cam_get_view_space_height(to_ledge);
    if(height+g_hero_state.groundHeight<rise || height<0.5f) return 0;
    *(V4_Fbfdc087a *)probe_end=0; FL(probe_end,0)=1.0f; FL(probe_end,8)=down;
    matrix_mul_vec3(probe_end,probe_end,(char *)&g_hero_state);
    edge=0;
    FastVecAdd(probe_end,probe_end,ledge_point);
    FastVecSub(probe_start,position,probe_end);
    cam_set_view_space_height(probe_start,probe_start,0.0f);
    FastVecAdd(probe_start,probe_start,probe_end);
    vec_scale_to_length(edge_step,(char *)&g_hero_state+0x20,-down*0.2f);
    for(j=0;j<5;j++) {
        if(CollLine(probe_start,probe_end,2,0,0)) {
            vec_scale_to_length(edge_normal,g_collision_result.normal,1.0f);
            edge=1;
            cam_set_view_space_height(edge_normal,edge_normal,0.0f);
            break;
        }
        FastVecAdd(probe_start,probe_start,edge_step);
        FastVecAdd(probe_end,probe_end,edge_step);
    }
    if(!edge) return 0;
    length=FastVecDot((char *)&g_hero_state,edge_normal);
    if(!(length<math_fast_sin_or_cos_a(1.134464144706726f))) return 0;
    step=0.03f;
    max=2.4f;
    qcopy(sweep_point,ledge_point);
    vec_scale_to_length(down_offset,(char *)&g_hero_state+0x2c0,-0.05f);
    vec_scale_to_length(far_offset,edge_normal,step);
    FastVecAdd(near_offset,far_offset,down_offset);
    FastVecSub(far_offset,far_offset,down_offset);
    FastVecAdd(sweep_end_a,sweep_point,far_offset);
    FastVecAdd(sweep_end_b,sweep_point,near_offset);
    for(sweep_distance=0.0f;sweep_distance<max;sweep_distance+=step) {
        if(!CollLine(sweep_end_b,sweep_end_a,4,g_hero_state.moby,0)) {
            if(out) {
                qcopy(out+0x10,sweep_point);
                vec_scale_to_length(back_offset,edge_normal,back);
                vec_scale_to_length(out,(char *)&g_hero_state+0x2c0,-drop);
                FastVecAdd(out,back_offset,out);
                FastVecAdd(out,out+0x10,out);
                FL(out,0x24)=mat_fast_helper_a(FL(edge_normal,0),FL(edge_normal,4));
                IN(out,0x28)=1;
            }
            return 1;
        }
        qcopy(sweep_point,g_collision_result.position);
        FastVecAdd(sweep_end_b,sweep_point,near_offset);
        FastVecAdd(sweep_end_a,sweep_point,far_offset);
    }
fail:
    return 0;
}
#undef FL
#undef IN
