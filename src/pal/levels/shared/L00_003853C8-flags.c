#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern float FastVecDot(void *,void *);
extern float FastVecLength(void *);
extern float math_fabs(float);
extern float FastDiffRots(float,float);
typedef struct { unsigned char prefix[0x158];float heading;unsigned char gap15C[0x34];char *target; } CameraTargetView;
typedef struct {
    unsigned char prefix[0x80];Vector4 position;unsigned char gap90[8];float heading;
    unsigned char gap9C[0xD8];float speed;unsigned char gap178[0x2118];char *object;
} PlayerTargetView;
extern CameraTargetView g_camera_target_view;
extern PlayerTargetView g_hero_state;

/* Updates a marker object that follows the camera's target, and pushes it far away when the player is moving past it (PAL). */
void camera_marker_update_pal(char *object)
{
    Vector4 difference, projected;
    float amount;
    if (g_camera_target_view.target) {
        FIELD(Quadword,object,0x10)=FIELD(Quadword,g_camera_target_view.target,0x30);
        FastVecSub(&difference,object+0x10,&g_hero_state.position);
        amount=FastVecDot(&difference,g_hero_state.object+0xE0);
        FastVecScale(&projected,g_hero_state.object+0xE0,amount);
        FastVecSub(&difference,&difference,&projected);
        if (math_fabs(amount)<2.5f) {
            if (FastVecLength(&difference)<0.1f ||
                FastDiffRots(g_hero_state.heading,g_camera_target_view.heading)<2.3561947f ||
                g_hero_state.speed<0.002f) {
                FIELD(float,object,0x10)=FIELD(float,object,0x14)=FIELD(float,object,0x18)=15;
            }
            else {
                amount=FastVecDot(object+0x10,g_hero_state.object+0xE0);
                FastVecScale(&projected,g_hero_state.object+0xE0,amount);
                FastVecSub(&difference,object+0x10,&projected);
                amount=FastVecDot(&g_hero_state.position,g_hero_state.object+0xE0);
                FastVecScale(&projected,g_hero_state.object+0xE0,amount);
                FastVecAdd(object+0x10,&difference,&projected);
            }
        }
    } else {
        FIELD(float,object,0x10)=FIELD(float,object,0x14)=FIELD(float,object,0x18)=5;
    }
}
