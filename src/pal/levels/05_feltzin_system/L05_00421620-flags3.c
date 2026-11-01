#include "include_asm.h"

#include "common.h"
typedef struct { char pad[0x160]; float strength; int unused; int timer, mode; } Camera05;
extern Camera05 D_L05_001B9580;
extern struct { char pad[0x18]; char *hit; } D_L05_001BFB00;
extern char *func_002ED688(char *object);
extern void func_0029FCC0(char *object, int a1, char *out);
extern void func_00282CC0(void *dst, void *src, char *src2);
extern void func_00282CF0(void *dst, void *src, char *src2);
extern int func_002761F8(void *a0, void *a1, int a2, char *a3, int a4);
extern void func_PAL_L05_0037D3D0(float value);
extern char D_L05_001B1308[8];
extern void func_00282F20(void *, void *, float);
extern int func_002A7820(int, int);
extern char *func_PAL_002BE9A8(char *, float, float, float, float, int, char *, int, int);
extern float func_002A7878(float a, float b);
extern int func_001163B0(void);
extern int func_00283CF0(float);
extern float func_00283CE0(int);

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
    char *v = func_002ED688(object);
    int i;
    char *position;
    if (!v || !*(char **)(v + 0x120) || *(int *)(state + 0x268)) return;
    position = object + 0x10;
    func_00282CF0(delta, *(char **)(v + 0x120) + 0x10, position);
    {
        float speed = 0.70000005f;
        qcopy_nc(pos, position);
        func_00282F20(velocity, delta, speed);
    }

    func_00282F20(end, delta, 5.0f);
    func_00282CC0(end, end, position);
    if (func_002761F8(position, end, 0, object, 0)) {
        char *hit = D_L05_001BFB00.hit;
        if (hit && *(short *)(hit + 0xAA) == 0xFBF) {
            D_L05_001B9580.strength = 0.05f;
            D_L05_001B9580.timer = 25;
            D_L05_001B9580.mode = 0;
            func_PAL_L05_0037D3D0(1.0f);
        }
    }
    func_0029FCC0(object, 0, origin);
    {
        float scale = 1.0f, size = 210000.0f;
        for (i = 0; i < 3; i++) {
            int kind = func_002A7820(1, 5);
            char *particle = func_PAL_002BE9A8(origin, 0.0f, scale, 1.01f, func_002A7878(0.25f, scale) * size,
                                           kind, velocity, 0x5A182, 1);
            __builtin_memcpy(colors, D_L05_001B1308, 8);
            if (particle) {
                char *data = particle + 0x20;
                {
                    int index = func_001163B0() % 2;
                    particle[3] = colors[index * 4];
                }
                *(short *)(particle + 0xA) = 0x1D;
                particle[9] = func_00283CF0(4.0f) + 0x40;
                {
                    float value = func_00283CE0(4);
                    *(int *)(data + 4) = 3;
                    *(float *)(data + 0x1C) = value;
                }
                data[0xA] = func_002A7820(0x40, 0x80);
                data[0xB] = particle[0xA];
            }
        }
    }
    *(int *)(state + 0x268) = 3;
}
