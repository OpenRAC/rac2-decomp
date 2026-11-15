#include "include_asm.h"

#include "common.h"
typedef struct { char pad[0x160]; float strength; int unused; int timer, mode; } Camera05;
extern Camera05 D_L05_001B9580;
extern struct { char pad[0x18]; char *hit; } D_L05_001BFB00;
extern char *moby_get_motion_data(char *object);
extern void moby_transform_joint_to_world(char *object, int a1, char *out);
extern void FastVecAdd(void *dst, void *src, char *src2);
extern void FastVecSub(void *dst, void *src, char *src2);
extern int CollLine(void *a0, void *a1, int a2, char *a3, int a4);
extern void func_PAL_L05_0037D3D0(float value);
extern char D_L05_001B1308[8];
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_range(int, int);
extern char *func_PAL_002BE9A8(char *, float, float, float, float, int, char *, int, int);
extern float math_random_float_range(float a, float b);
extern int func_001163B0(void);
extern int FloatToInt(float);
extern float IntToFloat(int);

/* Once the record has a target and the state+0x268 countdown is clear: casts a ray over five
   times the offset to the target (shaking the camera on a 0xFBF hit), emits three random particles from
   the object's origin and restarts the countdown at 4. */
void func_PAL_L05_00421928(char *object)
{
    char delta[16] __attribute__((aligned(16)));
    char pos[16] __attribute__((aligned(16)));
    char velocity[16] __attribute__((aligned(16)));
    char end[16] __attribute__((aligned(16)));
    char origin[16] __attribute__((aligned(16)));
    char colors[8];
    char *state = *(char **)(object + 0x68);
    char *v = moby_get_motion_data(object);
    int i;
    char *position;
    if (!v || !*(char **)(v + 0x120) || *(int *)(state + 0x268)) return;
    position = object + 0x10;
    FastVecSub(delta, *(char **)(v + 0x120) + 0x10, position);
    {
        float speed = 0.70000005f;
        qcopy_nc(pos, position);
        vec_scale_to_length(velocity, delta, speed);
    }

    vec_scale_to_length(end, delta, 5.0f);
    FastVecAdd(end, end, position);
    if (CollLine(position, end, 0, object, 0)) {
        char *hit = D_L05_001BFB00.hit;
        if (hit && *(short *)(hit + 0xAA) == 0xFBF) {
            D_L05_001B9580.strength = 0.05f;
            D_L05_001B9580.timer = 25;
            D_L05_001B9580.mode = 0;
            func_PAL_L05_0037D3D0(1.0f);
        }
    }
    moby_transform_joint_to_world(object, 0, origin);
    {
        float scale = 1.0f, size = 210000.0f;
        for (i = 0; i < 3; i++) {
            int kind = math_random_int_range(1, 5);
            char *particle = func_PAL_002BE9A8(origin, 0.0f, scale, 1.01f, math_random_float_range(0.25f, scale) * size,
                                           kind, velocity, 0x5A182, 1);
            __builtin_memcpy(colors, D_L05_001B1308, 8);
            if (particle) {
                char *data = particle + 0x20;
                {
                    int index = func_001163B0() % 2;
                    particle[3] = colors[index * 4];
                }
                *(short *)(particle + 0xA) = 0x1D;
                particle[9] = FloatToInt(4.0f) + 0x40;
                {
                    float value = IntToFloat(4);
                    *(int *)(data + 4) = 3;
                    *(float *)(data + 0x1C) = value;
                }
                data[0xA] = math_random_int_range(0x40, 0x80);
                data[0xB] = particle[0xA];
            }
        }
    }
    *(int *)(state + 0x268) = 3;
}
