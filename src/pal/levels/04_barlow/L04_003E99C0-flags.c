#include "include_asm.h"
#include "names.h"

extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float mat_fast_helper_a(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float moby_get_anim_value(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void vec_random_direction(void *, float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern int func_PAL_002B5E30(void *, float);
extern char *func_PAL_002BE9A8(void *, int, float, float, void *, float, int, int, float);
extern int func_PAL_L01_00323068(void *, void *);
extern float D_L04_002AF630[];

void func_PAL_L04_003E99C0(char *o, float *dest)
{
    float v[4], pos[4], vel[4], random[4], spawn[4];
    float frame, t, color;
    int index, i, kind;
    unsigned short lifetime;
    char *particle, *data;

    if ((unsigned char)o[0x42] != (unsigned char)o[0x43]) {
        func_PAL_L01_00323068(o, dest);
        return;
    }
    frame = moby_get_anim_value(o);
    index = FloatToInt(frame);
    {
        int nextIndex = index + 1;
        t = IntToFloat(index);
        frame -= t;
        FastVecScale(v, o + 0xc0,
                      D_L04_002AF630[index] + (D_L04_002AF630[nextIndex] - D_L04_002AF630[index]) * frame);
    }
    FastVecAdd(o + 0x10, v, o + 0x10);
    func_PAL_002B5E30(o, mat_fast_helper_a(dest[0] - *(float *)(o + 0x10), dest[1] - *(float *)(o + 0x14)));
    *(float *)(o + 0x18) = coll_probe_ground_height_below(o + 0x10, 0, 0.5f);
    if (index != 5 && index != 15) {
        return;
    }
    if (index == 5) {
        moby_transform_joint_to_world(o, 3, pos);
    } else {
        moby_transform_joint_to_world(o, 2, pos);
    }
    FastVecScale(vel, o + 0xc0, 0.5f);
    FastVecAdd(pos, pos, vel);
    pos[2] -= 0.2f;
    lifetime = 50;
    for (i = 9; i >= 0; i--) {
        vec_random_direction(random, 0.0060000005f, 0.060000002f);
        kind = FloatToInt(math_random_signed_float_range(1.0f, 3.0f));
        color = math_random_float_range(0.3f, 1.0f) * 210000.0f;
        spawn[0] = pos[0] + math_random_signed_float_range(0.0f, 0.3f);
        spawn[1] = pos[1] + math_random_signed_float_range(0.0f, 0.3f);
        spawn[2] = pos[2] + math_random_signed_float_range(0.0f, 0.3f);
        particle = func_PAL_002BE9A8(spawn, kind, 0.0f, 1.0f, random, 1.01f, 0x406080, 0, color);
        if (particle) {
            *(unsigned short *)(particle + 0xa) = lifetime;
            data = particle + 0x20;
            particle[3] = 0x44;
            particle[9] = FloatToInt(4.0f) + 0x40;
            *(float *)(data + 0x1c) = IntToFloat(4);
            *(int *)(data + 4) = 3;
            data[0xa] = 0x20;
            data[0xb] = particle[0xa];
        }
    }
}
