#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad8010 __attribute__((mode(TI)));
typedef struct {
    char pad[0x18];
    float z;
    char pad1c[4];
    u8 state;
    char pad21[15];
    u8 alpha;
    char pad31;
    u16 flags;
    char pad34[0x14];
    float speed;
    char pad4c[0x49];
    s8 sound;
    u16 timer;
    char pad98[0x60];
    float angle;
} Object8010;
typedef struct {
    int ids[4];
    int direction;
    float initialHeight;
    float stopFrame;
    int timer;
    int duration;
    int selected;
    int sound;
    float turnSpeed;
    float targetAngle;
} Private8010;
extern char *g_moby_l04_pool __attribute__((sda));
extern char g_str_debug_stub_message[];
extern unsigned char g_sound_state[];
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float moby_get_anim_value(void *);
extern float math_fast_sin_or_cos_b(float);
extern float IntToFloat(int);
extern f32 math_approach_target_with_direction_mode(void *, float, void *, float, float, float, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern void euler_rotation_basis(void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);
extern void STUB_printf(void *);

void func_PAL_L04_003EBF44(char *o)
{
    Object8010 *obj = (Object8010 *)o;
    Private8010 *p = *(Private8010 **)(o + 0x68);
    unsigned char v[16] __attribute__((aligned(16))),
        old[16] __attribute__((aligned(16))),
        delta[16] __attribute__((aligned(16))),
        rot[16] __attribute__((aligned(16)));

    switch (obj->state) {
    case 0: {
        float initialZ = obj->z;

        obj->alpha = 128;
        obj->flags = 128;
        p->initialHeight = initialZ;
        p->stopFrame = 30;
        p->selected = 2;
        p->sound = -1;
        p->targetAngle = FastAddRotations(obj->angle, 1.5707964897155762f);
        if (p->direction)
            p->targetAngle = fast_subtract_rotations(obj->angle, 1.5707964897155762f);
        func_PAL_002A7E68(o, 1, 0, 0);
        moby_set_state(o, 1, -1);
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *m, *d;
                m = g_moby_l04_pool + (p->ids[i] << 8);
                d = *(char **)(m + 0x68);
                *(int *)(d + 0x5C) |= 1;
                ((Object8010 *)m)->alpha = 128;
                ((Object8010 *)m)->flags = 128;
            }
        }
        if (p->direction)
            func_PAL_002A7E68(o, 2, 0, 0);
        obj->speed = 1.0f / 3;
        break;
    }
    case 1: {
        char *m;
        float frame;

        frame = moby_get_anim_value(o);
        m = (char *)g_sound_state + p->sound * 0x70;
        if (*(char **)(m + 0x88) != o || !*(u8 *)(m + 0x74))
            p->sound = PlayMobySound(0, 4, o);
        if (!p->direction)
            math_approach_target_with_direction_mode(o + 0xF8, p->targetAngle, &p->turnSpeed,
                         0.00027925274f, 0.00027925274f, 0.08377582f, 0);
        else
            math_approach_target_with_direction_mode(o + 0xF8, p->targetAngle, &p->turnSpeed,
                         0.00027925274f, 0.00027925274f, 0.08377582f, 0);
        euler_rotation_basis(o + 0xC0, o + 0xF0);
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *m, *d;
                m = g_moby_l04_pool + (p->ids[i] << 8);
                d = *(char **)(m + 0x68);
                /* old is a separate stack vector; subsequent accesses use m. */
                qcopy_nc(old, m + 0x10);
                moby_transform_joint_to_world(o, i, v);
                *(Quad8010 *)(m + 0x10) = *(Quad8010 *)v;
                *(Quad8010 *)rot = *(Quad8010 *)(m + 0xF0);
                if (p->direction)
                    *(float *)(m + 0xF8) = FastAddRotations(obj->angle, 0.00872664712369442f);
                FastVecSub(delta, m + 0x10, old);
                if (p->selected == i && p->direction)
                    mat_combine_and_store(d + 0x20, delta, rot, m + 0xF0);
                else
                    mat_combine_and_store(d + 0x20, delta, rot, rot);
            }
        }
        if (frame == p->stopFrame) {
            p->timer = ((s32)(p->duration) * 5 + 2) / 6;
            obj->speed = 0;
            p->stopFrame += 30;
            if (p->stopFrame >= 120)
                p->stopFrame = 0;
            moby_set_state(o, 2, -1);
            p->turnSpeed = 0;
        }
        break;
    }
    case 2: {
        {
            int i = p->sound;
            char *m;

            if (i != -1) {
                m = (char *)g_sound_state + i * 0x70;
                if (*(char **)(m + 0x88) == o && *(u8 *)(m + 0x74))
                    snd_stop_voice(i);
            }
            p->sound = -1;
        }
        if (math_fast_float_d(&p->timer)) {
            if (++p->selected >= 4) {
                STUB_printf(g_str_debug_stub_message);
                p->selected = 0;
            }
            p->targetAngle = FastAddRotations(obj->angle, 1.5707964897155762f);
            if (p->direction)
                p->targetAngle = fast_subtract_rotations(obj->angle, 1.5707964897155762f);
            moby_set_state(o, 1, -1);
            obj->z = p->initialHeight;
            obj->speed = 1.0f / 3;
        } else if (p->timer < 21) {
            obj->z = p->initialHeight;
            obj->z += -math_fast_sin_or_cos_b(IntToFloat(p->timer) * 0.14842157f) * 0.25f;
        }
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *m, *d;
                m = g_moby_l04_pool + (p->ids[i] << 8);
                d = *(char **)(m + 0x68);
                qcopy_nc(old, m + 0x10);
                moby_transform_joint_to_world(o, i, v);
                *(Quad8010 *)(m + 0x10) = *(Quad8010 *)v;
                FastVecSub(delta, m + 0x10, old);
                mat_combine_and_store(d + 0x20, delta, m + 0xF0, m + 0xF0);
            }
        }
        break;
    }
    }
    if (obj->timer <= 0xFFFE)
        ++obj->timer;
}



