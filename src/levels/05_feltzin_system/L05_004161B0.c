/* Updates the active interpolation records owned by this object. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { TI128 position, next, offset, origin; char *owner; int mode; float progress; int hit; } Entry05;
typedef struct { char pad[0x160]; float strength; int unused; int timer, mode; } Camera05;
extern Entry05 D_L05_002659E0[];
extern Camera05 D_L05_001B9580;
extern struct { char pad[0x18]; char *hit; } D_L05_001BFB00;
extern int D_L05_00221D10[];
extern char *moby_get_motion_data(char *object);
extern void moby_transform_joint_to_world(char *object, int a1, char *out);
extern void FastVecAdd(void *dst, void *src, char *src2);
extern void FastVecScale(void *dst, void *src, float value);
extern void FastVecSub(void *dst, void *src, char *src2);
extern void lerp_vector(char *, char *, char *, float);
extern float fast_vec_dist(char *, char *);
extern int CollLine(void *a0, void *a1, int a2, char *a3, int a4);
extern void hero_apply_damage(float value);
extern char D_L05_001B1308[8];
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_range(int, int);
/* The particle spawner (position, kind, velocity, color, count; four floats): the floats are
   declared first, each register bank keeps its order (a0-t0, f12-f15). */
extern char *SpawnSpinningSparkParticle(char *, float, float, float, float, int, char *, int, int);
extern float math_random_float_range(float a, float b);
extern int func_001163B0(void);
extern int FloatToInt(float);
extern float IntToFloat(int);

/* Moves every beam record this object owns toward the hero, releases finished ones, and shakes the camera the first time a beam hits the hero. */
void beam_update_records(char *obj)
{
    char aim_point[16] __attribute__((aligned(16)));
    char lift[16] __attribute__((aligned(16)));
    int i;
    char *position;
    for (i = 0; i < 128; i++) {
        Entry05 *record = &D_L05_002659E0[i];
        char *state;
        if (record->owner != obj) continue;
        position = (char *)&record->position;
        state = moby_get_motion_data(obj);
        if (D_L05_00221D10[11] == 1 || *(int *)(state + 0x110) == 0) {
            record->owner = 0;
            continue;
        }
        moby_transform_joint_to_world(obj, 0, (char *)&record->origin);
        qcopy(aim_point, *(char **)(state + 0x120) + 0x10);
        FastVecAdd(aim_point, (char *)&record->offset, aim_point);
        FastVecScale(lift, *(char **)(state + 0x120) + 0xC0, 0.5f);
        FastVecSub(aim_point, aim_point, lift);
        switch (record->mode) {
        case 0: {
            float distance;
            qcopy(position, (char *)&record->origin);
            lerp_vector((char *)&record->next, (char *)record, aim_point, record->progress);
            distance = fast_vec_dist((char *)&record->origin, aim_point);
            if (distance > 64.0f) distance = 64.0f;
            else if (distance < 1.0f) distance = 1.0f;
            record->progress += 2.0f / distance;
            if (record->progress >= 1.0f) {
                record->progress = 1.0f;
                record->mode = 1;
            }
            break;
        }
        case 1:
            qcopy((char *)&record->next, aim_point);
            lerp_vector((char *)record, aim_point, (char *)&record->origin, record->progress);
            record->progress -= 0.25f;
            if (record->progress <= 0.0f) record->owner = 0;
            break;
        }
        if (record->hit == 0 && CollLine(record, (char *)&record->next, 4, obj, 0)) {
            char *hit = D_L05_001BFB00.hit;
            if (hit && *(short *)(hit + 0xAA) == 0xFBF /* moby class 4031 */) {
                D_L05_001B9580.timer = 30;
                D_L05_001B9580.strength = 0.05f;
                D_L05_001B9580.mode = 0;
                hero_apply_damage(1.0f);
                record->hit = 1;
            }
        }
    }
}

/* Once the record has a target and the state+0x268 countdown is clear: casts a ray over five
   times the offset to the target (shaking the camera on a 0xFBF hit), emits three random particles from
   the object's origin and restarts the countdown at 4. */
void beam_fire_burst(char *object)
{
    char delta[16] __attribute__((aligned(16)));
    char pos[16] __attribute__((aligned(16)));
    char velocity[16] __attribute__((aligned(16)));
    char end[16] __attribute__((aligned(16)));
    char origin[16] __attribute__((aligned(16)));
    char colors[8];
    char *state = *(char **)(object + 0x68);
    char *target_info = moby_get_motion_data(object);
    int i;
    char *position;
    if (!target_info || !*(char **)(target_info + 0x120) || *(int *)(state + 0x268)) return;
    position = object + 0x10;
    FastVecSub(delta, *(char **)(target_info + 0x120) + 0x10, position);
    {
        float speed = 0.5833333730697632f;
        qcopy_nc(pos, position);
        vec_scale_to_length(velocity, delta, speed);
    }

    vec_scale_to_length(end, delta, 5.0f);
    FastVecAdd(end, end, position);
    if (CollLine(position, end, 0, object, 0)) {
        char *hit = D_L05_001BFB00.hit;
        if (hit && *(short *)(hit + 0xAA) == 0xFBF /* moby class 4031 */) {
            D_L05_001B9580.strength = 0.05f;
            D_L05_001B9580.timer = 30;
            D_L05_001B9580.mode = 0;
            hero_apply_damage(1.0f);
        }
    }
    moby_transform_joint_to_world(object, 0, origin);
    {
        float scale = 1.0f, size = 210000.0f;
        for (i = 0; i < 3; i++) {
            int kind = math_random_int_range(1, 5);
            char *particle = SpawnSpinningSparkParticle(origin, 0.0f, scale, 1.01f, math_random_float_range(0.25f, scale) * size,
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
                data[0xA] = math_random_int_range(0x40, 0x80);
                data[0xB] = particle[0xA];
            }
        }
    }
    *(int *)(state + 0x268) = 4;
}
