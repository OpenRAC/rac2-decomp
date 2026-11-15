/* func_PAL_L09_003C4454, the PAL copy of func_L06_00403710: the same C as func_PAL_L06_00407488. */
#include "common.h"

#define I(p, o) (*(s32 *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))
#define H(p, o) (*(u16 *)((char *)(p) + (o)))
extern char *g_path_list[];
typedef struct {
    char pad[0x1F0];
    u16 moveFlags;
    char pad1F2[0x13E];
    float height;
    char pad334[0x1F60];
    s32 mode;
    s32 pad2298;
    s32 action;
    char pad22A0[0x15];
    u8 flag;
} HeroState;
extern HeroState g_hero_state;
extern s32 g_current_map_index;
extern float D_L06_001B0090 __attribute__((sda));
extern float D_L06_001B9858 NOT_SDA;
extern s32 FloatToInt(float);
extern void moby_mark_spawned(void *);
extern s32 math_random_int_below(s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern float mat_fast_helper_a(float, float);
extern float math_approach_target_with_direction_mode(float *, float, float, float, float, float *, s32);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern s32 math_fast_float_d(s32 *);
extern float math_fabs(float);
extern s32 IsPointInCuboid(void *, s32);
extern float FastAddRotations(float,float);
extern void euler_rotation_basis(void *,void *);
extern s32 PlayMobySound(s32,s32,void *);
extern void func_PAL_L06_00407B38(void *,void *);
extern void func_PAL_L00_002B9CD8(void *,void *,s32,s32);
extern s32 point_in_path_xy(void *,void *,s32);
extern s32 flag_set_first_pending(void *);
extern void func_PAL_L00_002B3000(void);
typedef struct {
    char p0[0x48];
    u8 timerA;
    u8 p49;
    u8 timerB;
    char p4B[5];
    s32 path;
    s32 active;
    s32 point;
    s32 timeout;
    float turn;
    float homeZ;
    float speed;
    s32 wait;
    float pathZ;
    s32 p74;
    s32 range;
    s32 outsideWait;
    s32 insideWait;
} LaunchData;

void func_PAL_L09_003C4454(char *obj)
{
    float pos[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    LaunchData *data = *(LaunchData **)(obj + 0x68);
    s32 state = B(obj,0x20);
    switch (state) {
    case 0:
        if (data->active) {
            data->timerA = FloatToInt(15.0f);
            data->timerB = FloatToInt(12.0f);
            B(obj,0x20) = 2;
            {
                float height = F(obj,0x18);
                B(obj,0x30) = 255;
                H(obj,0x34) |= 1;
                data->homeZ = height;
                data->wait = 25;
            }
        } else {
            if (data->path == -1) {
                moby_mark_spawned(obj);
                return;
            }
            data->point = math_random_int_below(I(g_path_list[data->path],0));
            data->timeout = 500;
            if (B(obj,0x43) != 1) func_PAL_002A7E68(obj,1,0,8);
            F(obj,0x18) = F(g_path_list[data->path],0x18) - D_L06_001B0090;
            data->pathZ = F(obj,0x18);
            B(obj,0x20) = 1;
        }
        break;
    case 1:
        qcopy(pos,g_path_list[data->path] + 0x10 + data->point*16);
        math_approach_target_with_direction_mode((float *)(obj+0xF8),mat_fast_helper_a(pos[0]-F(obj,0x10),pos[1]-F(obj,0x14)),0.0012566373f,0.0012566373f,0.062831864f,&data->turn,0);
        vec_scale_to_length(step,obj+0xC0,0.060000002f);
        FastVecAdd(obj+0x10,obj+0x10,step);
        if (fast_vec_dist(obj+0x10,pos)<3.0f || math_fast_float_d(&data->timeout)) {
            data->point = (data->point+math_random_int_below(I(g_path_list[data->path],0))) % I(g_path_list[data->path],0);
            data->timeout = 500;
        }
        break;
    case 2:
        math_fast_float_d(&data->wait);
        if (math_fabs(g_hero_state.height-data->homeZ)<0.8f && g_hero_state.action==18 && !IsPointInCuboid((char *)&g_hero_state+0x80,data->range)) {
            if (data->wait == 0) {
                F(obj,0xF4) = -1.5533431768417358f;
                F(obj,0xF8) = FastAddRotations(D_L06_001B9858,1.5707964897155762f);
                euler_rotation_basis(obj+0xC0,obj+0xF0);
                qcopy(obj+0x10,(char *)&g_hero_state+0x80);
                vec_scale_to_length(pos,obj+0xE0,D_L06_001B0090);
                FastVecSub(obj+0x10,obj+0x10,pos);
                data->speed = 0.16000001f;
                H(obj,0x34) &= 0xFFFE;
                PlayMobySound(1,0,obj);
                if (B(obj,0x43) != 2) func_PAL_002A7E68(obj,2,10,4);
                B(obj,0x20) = 3;
                qcopy(step,(char *)&g_hero_state+0x80);
                step[2] = g_hero_state.height;
                func_PAL_L06_00407B38(obj,step);
                func_PAL_L00_002B9CD8((char *)&g_hero_state+0x80,(char *)&g_hero_state+0x90,111,0);
                g_hero_state.flag = 1;
            }
        } else if (g_hero_state.mode!=18) {
            if (point_in_path_xy((char *)&g_hero_state+0x80,g_path_list[data->path]+0x10,I(g_path_list[data->path],0))) data->wait=((s32)(data->insideWait) * 5 + 2) / 6;
            else data->wait=((s32)(data->outsideWait) * 5 + 2) / 6;
        }
        break;
    case 3:
        if (flag_set_first_pending(obj)) PlayMobySound(1,0,obj);
        qzero_nc((char *)&g_hero_state+0xF0);
        qzero_nc((char *)&g_hero_state+0x110);
        qzero_nc((char *)&g_hero_state+0x120);
        qzero_nc((char *)&g_hero_state+0x130);
        g_hero_state.moveFlags = 3;
        g_hero_state.flag = 1;
        {
            s32 level = g_current_map_index;
            F(obj,0x18) += data->speed;
            if (level != 9)
                data->speed -= 0.004f;
            else
                data->speed -= 0.008f;
        }
        if (data->speed<0.040000003f) {
            vec_scale_to_length(pos,obj+0xE0,D_L06_001B0090);
            math_approach_target_with_direction_mode((float *)(obj+0xF4),1.5533431768417358f,0.005026549f,0.005026549f,0.5026549f,&data->turn,0);
            euler_rotation_basis(obj+0xC0,obj+0xF0);
            vec_scale_to_length(step,obj+0xE0,D_L06_001B0090);
            FastVecSub(delta,step,pos);
            FastVecSub(obj+0x10,obj+0x10,delta);
        }
        if (data->speed<0.0f && F(obj,0x18)<g_hero_state.height) {
            qcopy_nc(pos,(char *)&g_hero_state+0x80);
            pos[2]=g_hero_state.height;
            func_PAL_L06_00407B38(obj,pos);
        }
        if (data->speed<0.0f && F(obj,0x18)<data->homeZ) func_PAL_L00_002B3000();
        if ((B(obj,0x60)&2) && B(obj,0x43)!=1) func_PAL_002A7E68(obj,1,0,8);
        break;
    }
}
