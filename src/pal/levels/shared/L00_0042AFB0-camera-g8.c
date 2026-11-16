#include "include_asm.h"
#include "names.h"

extern char g_camera_move_state[];
typedef struct { char pad[0x2290]; char *owner; int mode; char pad2[0x1c]; unsigned char flag; } CameraPlayer;
extern CameraPlayer g_camera_player;
extern float g_cam_ease_speed_a_min __attribute__((sda)), g_cam_ease_speed_b_min __attribute__((sda));
extern float g_cam_ease_speed_a_max __attribute__((sda)), g_cam_ease_speed_b_max __attribute__((sda));
extern float FastVecDot(void *, void *);
extern float math_fabs(float);
extern void follow_camera_set_distance(int, float, float);
#define F(p,n) (*(float *)((p)+(n)))
#define S(p,n) (*(short *)((p)+(n)))
#define P(p,n) (*(char **)((p)+(n)))

void cam_follow_get_ease_speeds_pal(char *obj, float *out1, float *out2)
{
    char *base = P(obj,112);
    char *state = base+576;
    char *movement = base+352;
    char *camera = g_camera_move_state;
    float t, target, value;
    if (!S(state,6) && ((S(state,4) && F(camera,164)==0.0f &&
         FastVecDot(g_camera_player.owner+192,obj)<=-0.3f) ||
        (math_fabs(F(camera,164))>0.0001f &&
         FastVecDot(camera+128,obj)<=-0.3f))) {
        S(state,4)=100;
        t=F(camera,164)*14.285699844360352f;
        if (t>1.0f) t=1.0f;
        target = g_camera_player.flag==1 ? 4.0f : F(state,12);
        value=F(movement,88)+(target-F(movement,88))*t;
        if (value>F(state,8)) F(state,8)=value;
        follow_camera_set_distance(0,F(state,8),0.003000000026077032f);
        *out1=g_cam_ease_speed_a_min+(g_cam_ease_speed_a_max-g_cam_ease_speed_a_min)*t;
        *out2=g_cam_ease_speed_b_min+(g_cam_ease_speed_b_max-g_cam_ease_speed_b_min)*t;
    } else {
        if (S(state,4)) {
            S(state,4)=0;
            F(state,8)=F(movement,88);
        }
        if (g_camera_player.mode==132) {
            *out1=0.04f;
            *out2=0.2f;
        } else {
            *out1=g_cam_ease_speed_a_min;
            *out2=g_cam_ease_speed_b_min;
        }
    }
}
