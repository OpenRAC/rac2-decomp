#include "common.h"

typedef int InputQuad __attribute__((mode(TI)));

typedef struct {
    unsigned char pad0[152];
    float x98;
    unsigned char pad9c[260];
    float x1a0;
    unsigned char pad1a4[12];
    float x1b0;
    unsigned char pad1b4[4768];
    short x1454;
    unsigned char x1456;
    unsigned char x1457;
    unsigned char pad1458[2904];
    float x1fb0;
    float x1fb4;
    unsigned char pad1fb8[728];
    char * x2290;
    unsigned char pad2294[47];
    unsigned char x22c3;
    unsigned char pad22c4[500];
    float x24b8;
} PlayerInputState;
extern PlayerInputState g_hero_state;
typedef struct {char pad[0x158];float angle;char gap[0x370-0x15c];char matrix[64];} InputCamera;
extern InputCamera g_scalar_transition_state;
extern unsigned char g_cheat_flags[] __attribute__((sda));
extern float math_fabs(float);
extern float vec_length_xy(void *);
extern void divide_vector_xyz(void *,void *,float);
extern float hero_compute_aim_angle(void);
extern void matrix_mul_vec3(void *,void *,void *);
extern float mat_fast_helper_a(float,float);
extern float FastDiffRots(float,float);
extern float FastAddRotations(float,float);

/* Resolve stick input into a camera-relative movement direction and target speed. */
void hero_resolve_stick_direction(int mode,float scale) {
    struct { float x,y,z,w; } stick __attribute__((aligned(16)));
    float z[4] __attribute__((aligned(16)));
    float angle,y;
    int dir;
    stick.y=g_hero_state.x1fb4;stick.x=g_hero_state.x1fb0;
    if(mode==1) {
        if(math_fabs(stick.y)>0.7f && math_fabs(stick.x)<0.12f) stick.x=0.0f;
        if(math_fabs(stick.x)>0.7f && math_fabs(stick.y)<0.12f) stick.y=0.0f;
    }
    {float length=vec_length_xy(&stick);if(length>1.0f) divide_vector_xyz(&stick,&stick,length);}
    y=stick.y;
    if(stick.x==0.0f && y==0.0f) {
        g_hero_state.x1b0=0.0f;
        if(g_hero_state.x22c3) g_hero_state.x1a0=hero_compute_aim_angle();else g_hero_state.x1a0=g_hero_state.x98;
        *(InputQuad *)z=0;z[0]=1.0f;
        matrix_mul_vec3((char *)&g_hero_state+0x190,z,g_hero_state.x2290+0xc0);
    } else {
        g_hero_state.x1a0=mat_fast_helper_a(-y,-stick.x);
        if(g_hero_state.x1454) {
            angle=mat_fast_helper_a(g_hero_state.x1fb0,g_hero_state.x1fb4);dir=2;
            if(FastDiffRots(angle,1.5707964897155762f)<0.7853982448577881f) dir=3;
            else if(FastDiffRots(angle,0.0f)<0.7853982448577881f) dir=1;
            else if(FastDiffRots(angle,3.1415929794311523f)<0.7853982448577881f) dir=0;
            g_hero_state.x1457=dir;
            if(dir==3 && g_hero_state.x24b8>0.15f) g_hero_state.x1456=1;else g_hero_state.x1456=0;
        }
        g_hero_state.x1a0=FastAddRotations(g_hero_state.x1a0,g_scalar_transition_state.angle);
        {float x=stick.x,y=stick.y;stick.y=-x;stick.x=-y;stick.z=stick.w=0.0f;if(g_cheat_flags[0]) stick.y=x;}
        matrix_mul_vec3((char *)&g_hero_state+0x190,&stick,g_scalar_transition_state.matrix);
        g_hero_state.x1b0=scale*vec_length_xy(&stick);
    }
}
