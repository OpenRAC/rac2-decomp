/* Updates the active interpolation records owned by this object. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { TI128 position, next, offset, origin; char *owner; int mode; float progress; int hit; } Entry05;
typedef struct { char pad[0x160]; float strength; int unused; int timer, mode; } Camera05;
extern Entry05 D_L05_002659E0[];
extern Camera05 D_L05_001B9580;
extern struct { char pad[0x18]; char *hit; } D_L05_001BFB00;
extern int D_L05_00221D10[];
extern char *func_002ED688(char *object);
extern void func_0029FCC0(char *object, int a1, char *out);
extern void func_00282CC0(void *dst, void *src, char *src2);
extern void func_00282D30(void *dst, void *src, float value);
extern void func_00282CF0(void *dst, void *src, char *src2);
extern void func_00282D08(char *, char *, char *, float);
extern float func_00282E48(char *, char *);
extern int func_002761F8(void *a0, void *a1, int a2, char *a3, int a4);
extern void func_L05_0037AC80(float value);
extern char D_L05_001B1308[8];
extern void func_00282F20(void *, void *, float);
extern int func_002A7820(int, int);
/* The particle spawner (position, kind, velocity, color, count; four floats): the floats are
   declared first, each register bank keeps its order (a0-t0, f12-f15). */
extern char *func_002BDCE8(char *, float, float, float, float, int, char *, int, int);
extern float func_002A7878(float a, float b);
extern int func_001163B0(void);
extern int func_00283CF0(float);
extern float func_00283CE0(int);

void func_L05_004161B0(char *obj)
{
    char a[16] __attribute__((aligned(16)));
    char b[16] __attribute__((aligned(16)));
    int i;
    char *position;
    for (i = 0; i < 128; i++) {
        Entry05 *p = &D_L05_002659E0[i];
        char *state;
        if (p->owner != obj) continue;
        position = (char *)&p->position;
        state = func_002ED688(obj);
        if (D_L05_00221D10[11] == 1 || *(int *)(state + 0x110) == 0) {
            p->owner = 0;
            continue;
        }
        func_0029FCC0(obj, 0, (char *)&p->origin);
        qcopy(a, *(char **)(state + 0x120) + 0x10);
        FastVecAdd(a, (char *)&p->offset, a);
        FastVecScale(b, *(char **)(state + 0x120) + 0xC0, 0.5f);
        FastVecSub(a, a, b);
        switch (p->mode) {
        case 0: {
            float d;
            qcopy(position, (char *)&p->origin);
            lerp_vector((char *)&p->next, (char *)p, a, p->progress);
            d = fast_vec_dist((char *)&p->origin, a);
            if (d > 64.0f) d = 64.0f;
            else if (d < 1.0f) d = 1.0f;
            p->progress += 2.0f / d;
            if (p->progress >= 1.0f) {
                p->progress = 1.0f;
                p->mode = 1;
            }
            break;
        }
        case 1:
            qcopy((char *)&p->next, a);
            lerp_vector((char *)p, a, (char *)&p->origin, p->progress);
            p->progress -= 0.25f;
            if (p->progress <= 0.0f) p->owner = 0;
            break;
        }
        if (p->hit == 0 && CollLine(p, (char *)&p->next, 4, obj, 0)) {
            char *hit = D_L05_001BFB00.hit;
            if (hit && *(short *)(hit + 0xAA) == 0xFBF) {
                D_L05_001B9580.timer = 30;
                D_L05_001B9580.strength = 0.05f;
                D_L05_001B9580.mode = 0;
                func_L05_0037AC80(1.0f);
                p->hit = 1;
            }
        }
    }
}

/* Once the record has a target and the state+0x268 countdown is clear: casts a ray over five
   times the offset to the target (shaking the camera on a 0xFBF hit), emits three random particles from
   the object's origin and restarts the countdown at 4. */
void func_L05_0041CB68(char *object)
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
    FastVecSub(delta, *(char **)(v + 0x120) + 0x10, position);
    {
        float speed = 0.5833333730697632f;
        qcopy_nc(pos, position);
        vec_scale_to_length(velocity, delta, speed);
    }

    vec_scale_to_length(end, delta, 5.0f);
    FastVecAdd(end, end, position);
    if (CollLine(position, end, 0, object, 0)) {
        char *hit = D_L05_001BFB00.hit;
        if (hit && *(short *)(hit + 0xAA) == 0xFBF) {
            D_L05_001B9580.strength = 0.05f;
            D_L05_001B9580.timer = 30;
            D_L05_001B9580.mode = 0;
            func_L05_0037AC80(1.0f);
        }
    }
    func_0029FCC0(object, 0, origin);
    {
        float scale = 1.0f, size = 210000.0f;
        for (i = 0; i < 3; i++) {
            int kind = func_002A7820(1, 5);
            char *particle = SpawnSpinningSparkParticle(origin, 0.0f, scale, 1.01f, func_002A7878(0.25f, scale) * size,
                                           kind, velocity, 0x5A182, 1);
            __builtin_memcpy(colors, D_L05_001B1308, 8);
            if (particle) {
                char *data = particle + 0x20;
                {
                    int index = func_001163B0() % 2;
                    particle[3] = colors[index * 4];
                }
                *(short *)(particle + 0xA) = 0x23;
                particle[9] = FloatToInt(4.0f) + 0x40;
                {
                    float value = IntToFloat(5);
                    *(int *)(data + 4) = 3;
                    *(float *)(data + 0x1C) = value;
                }
                data[0xA] = func_002A7820(0x40, 0x80);
                data[0xB] = particle[0xA];
            }
        }
    }
    *(int *)(state + 0x268) = 4;
}
