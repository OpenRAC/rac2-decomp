#include "common.h"
typedef struct { char pad[0x20]; float rate[4]; unsigned int start[4]; unsigned int end[4]; int timer[4]; float angle[4]; } PrisonVisualState;
extern void gfx_draw_rotated_billboard(void *, int, int, int, float, float, float);
extern float math_wrap_angle_full_turn(float);
extern void part_draw_spark_quads(void *);
extern int math_fast_float_d(void *);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern float FastAddRotations(float, float);

extern char g_tether_l14_origin_vec[];
extern char g_hero_state_block[];
extern void VU1_addGSregister(unsigned int, unsigned long);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
typedef struct {
    float pos[4][4];
    int color[4];
    float uv[4][2];
    long long mode;
    char pad[24];
} PrisonQuad;
extern float g_spark_quad_progress[32], g_spark_quad_angles[32];
extern float math_random_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);

/* Draws the pulse effect: a glowing center quad, two fading rotating quads and the sparks. */
void DrawAnimatedPrisonQuads(char *self)
{
    char *state = *(char **)(self + 0x68);
    int i;
    unsigned int color;
    float t, scale, angle;
    gfx_draw_rotated_billboard(self + 0x10, *(int *)(state+0xb8), *(int *)(state+0xc0), 1,
        *(float *)(state+0xbc) * *(float *)(state+0x80), *(float *)(state+0x80)*0.5f, 0.0f);
    for (i=0; i<2; i++) {
        if (math_fast_float_d(state+0x50+i*4))
            ((PrisonVisualState *)state)->timer[i] = (int)((float)*(int *)(state+0x10) / ((PrisonVisualState *)state)->rate[i]);
        t = 1.0f - (float)((PrisonVisualState *)state)->timer[i] /
            (float)(int)((float)*(int *)(state+0x10) / ((PrisonVisualState *)state)->rate[i]);
        if (*(float *)(state+0x14) < t) {
            color = ((PrisonVisualState *)state)->end[i];
            color = (color & 0xffffff) + (((int)((1.0f-t)/(1.0f-*(float *)(state+0x14))*80.0f)+48)<<24);
        } else {
            color = FastTweenColor(((PrisonVisualState *)state)->start[i], ((PrisonVisualState *)state)->end[i], t / *(float *)(state+0x14));
            color = (color & 0xffffff) + (((int)(t / *(float *)(state+0x14)*80.0f)+48)<<24);
        }
        scale = *(float *)(state+0x80) * *(float *)(state+0x18);
        angle = math_wrap_angle_full_turn(t * (((PrisonVisualState *)state)->angle[i] * 6.2831855f));
        gfx_draw_rotated_billboard(self+0x10, *(int *)(state+0x1c), color, 1, scale, *(float *)(state+0x80)*0.5f, angle + -3.1415927f);
    }
    *(float *)state = FastAddRotations(*(float *)state, 0.007f);
    gfx_draw_rotated_billboard(self+0x10, *(int *)(state+4), *(int *)(state+12), 1,
        *(float *)(state+8)* *(float *)(state+0x80), *(float *)(state+0x80)*0.5f, *(float *)state);
    part_draw_spark_quads(self);
}

/* Draws 32 small spark quads that drift away from the object and fade out. */
void part_draw_spark_quads(void *owner)
{
    char *object = owner;
    PrisonQuad q;
    float right[4], rotated[4], delta[4], axis[4];
    char *state = *(char **)(object + 0x68);
    int i, j, color, corners = 4, reg = 0x47, mode = 5, alpha = 128;
    unsigned long testOn = 0x53001, testOff = 0x5360B;
    float scale;
    for (i = 0; i < 32; i++) {
        g_spark_quad_progress[i]+=1.0f/ *(int *)(state+0xa8);
        if (g_spark_quad_progress[i]>1.0f) { g_spark_quad_progress[i]=0; g_spark_quad_angles[i]=math_random_float_range(-1.57079637f,1.57079637f); }
    }
    gfx_init_quad_packet_state(&q,*(int *)(state+0xb0),1,alpha);
    q.mode=mode;
    q.uv[0][0]=0; q.uv[0][1]=0; q.uv[1][0]=0; q.uv[1][1]=1;
    q.uv[2][0]=1; q.uv[2][1]=0; q.uv[3][0]=1; q.uv[3][1]=1;
    FastVecSub(right,g_tether_l14_origin_vec,object+16);
    vec_scale_to_length(right,right,*(float *)(state+0x80)*0.5f);
    vec_scale_to_length(axis,g_hero_state_block,-1.0f);
    for (i = 0; i < 32; i++) {
        if (*(float *)(state+0xac)<g_spark_quad_progress[i]) color=*(int *)(state+0x98);
        else color=FastTweenColor(*(int *)(state+0x94),*(int *)(state+0x98),g_spark_quad_progress[i]/ *(float *)(state+0xac));
        q.color[0]=q.color[1]=q.color[2]=q.color[3]=color;
        math_apply_axis_rotation_to_quat(rotated,axis,right,g_spark_quad_angles[i]);
        FastVecCross(delta,right,rotated);
        vec_scale_to_length(delta,delta,*(float *)(state+0xb4)*(1.0f-g_spark_quad_progress[i]));
        scale=*(float *)(state+0xa4)+g_spark_quad_progress[i]*(*(float *)(state+0xa0)-*(float *)(state+0xa4));
        if (scale>1.0f) scale=1.0f;
        VU1_addGSregister(reg,testOn);
        for (j = 0; j < corners; j++) {
            qcopy(q.pos[j],object+16);
            if (j>=2) FastVecAdd(q.pos[j],q.pos[j],delta);
            else FastVecSub(q.pos[j],q.pos[j],delta);
            if (!(j&1)) {
                vec_scale_to_length(rotated,rotated,*(float *)(state+0x80)*(1.0f-scale));
                FastVecAdd(q.pos[j],q.pos[j],rotated);
            } else {
                vec_scale_to_length(rotated,rotated,*(float *)(state+0x80));
                FastVecAdd(q.pos[j],q.pos[j],rotated);
                q.color[j]=*(int *)(state+0xc);
            }
            FastVecAdd(q.pos[j],q.pos[j],right);
        }
        draw_world_quad(&q,0,0);
    }
    VU1_addGSregister(reg,testOff);
}
