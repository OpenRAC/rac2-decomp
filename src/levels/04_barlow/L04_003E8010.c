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
/* Integer and FP parameters retain their order within each EE argument bank. */
extern f32 math_approach_target_with_direction_mode(void *, float, void *, float, float, float, int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern void euler_rotation_basis(void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);
extern void STUB_printf(void *);

/* Turns a ring of four linked objects a quarter turn at a time, pausing between turns and playing a sound while they turn. */
void UpdateRotatingObjectGroup(char *moby_ptr)
{
    Object8010 *obj = (Object8010 *)moby_ptr;
    Private8010 *vars = *(Private8010 **)(moby_ptr + 0x68);
    unsigned char part_pos[16] __attribute__((aligned(16))),
        old_pos[16] __attribute__((aligned(16))),
        delta[16] __attribute__((aligned(16))),
        rot[16] __attribute__((aligned(16)));

    switch (obj->state) {
    case 0: {
        float initialZ = obj->z;

        obj->alpha = 128;
        obj->flags = 128;
        vars->initialHeight = initialZ;
        vars->stopFrame = 30;
        vars->selected = 2;
        vars->sound = -1;
        vars->targetAngle = FastAddRotations(obj->angle, 1.5707964897155762f);
        if (vars->direction)
            vars->targetAngle = fast_subtract_rotations(obj->angle, 1.5707964897155762f);
        anim_start_blended(moby_ptr, 1, 0, 0);
        moby_set_state(moby_ptr, 1, -1);
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *part, *part_vars;
                part = g_moby_l04_pool + (vars->ids[i] << 8);
                part_vars = *(char **)(part + 0x68);
                *(int *)(part_vars + 0x5C) |= 1;
                ((Object8010 *)part)->alpha = 128;
                ((Object8010 *)part)->flags = 128;
            }
        }
        if (vars->direction)
            anim_start_blended(moby_ptr, 2, 0, 0);
        obj->speed = 1.0f / 3;
        break;
    }
    case 1: {
        char *part;
        float frame;

        frame = moby_get_anim_value(moby_ptr);
        part = (char *)g_sound_state + vars->sound * 0x70;
        if (*(char **)(part + 0x88) != moby_ptr || !*(u8 *)(part + 0x74))
            vars->sound = PlayMobySound(0, 4, moby_ptr);
        if (!vars->direction)
            math_approach_target_with_direction_mode(moby_ptr + 0xF8, vars->targetAngle, &vars->turnSpeed,
                         0.0001939255f, 0.0001939255f, 0.06981318444013596f, 0);
        else
            math_approach_target_with_direction_mode(moby_ptr + 0xF8, vars->targetAngle, &vars->turnSpeed,
                         0.0001939255f, 0.0001939255f, 0.06981318444013596f, 0);
        euler_rotation_basis(moby_ptr + 0xC0, moby_ptr + 0xF0);
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *part, *part_vars;
                part = g_moby_l04_pool + (vars->ids[i] << 8);
                part_vars = *(char **)(part + 0x68);
                /* oldPos is a separate stack vector; subsequent accesses use part. */
                qcopy_nc(old_pos, part + 0x10);
                moby_transform_joint_to_world(moby_ptr, i, part_pos);
                *(Quad8010 *)(part + 0x10) = *(Quad8010 *)part_pos;
                *(Quad8010 *)rot = *(Quad8010 *)(part + 0xF0);
                if (vars->direction)
                    *(float *)(part + 0xF8) = FastAddRotations(obj->angle, 0.00872664712369442f);
                FastVecSub(delta, part + 0x10, old_pos);
                if (vars->selected == i && vars->direction)
                    mat_combine_and_store(part_vars + 0x20, delta, rot, part + 0xF0);
                else
                    mat_combine_and_store(part_vars + 0x20, delta, rot, rot);
            }
        }
        if (frame == vars->stopFrame) {
            vars->timer = vars->duration;
            obj->speed = 0;
            vars->stopFrame += 30;
            if (vars->stopFrame >= 120)
                vars->stopFrame = 0;
            moby_set_state(moby_ptr, 2, -1);
            vars->turnSpeed = 0;
        }
        break;
    }
    case 2: {
        {
            int i = vars->sound;
            char *part;

            if (i != -1) {
                part = (char *)g_sound_state + i * 0x70;
                if (*(char **)(part + 0x88) == moby_ptr && *(u8 *)(part + 0x74))
                    snd_stop_voice(i);
            }
            vars->sound = -1;
        }
        if (math_fast_float_d(&vars->timer)) {
            if (++vars->selected >= 4) {
                STUB_printf(g_str_debug_stub_message);
                vars->selected = 0;
            }
            vars->targetAngle = FastAddRotations(obj->angle, 1.5707964897155762f);
            if (vars->direction)
                vars->targetAngle = fast_subtract_rotations(obj->angle, 1.5707964897155762f);
            moby_set_state(moby_ptr, 1, -1);
            obj->z = vars->initialHeight;
            obj->speed = 1.0f / 3;
        } else if (vars->timer < 25) {
            obj->z = vars->initialHeight;
            obj->z += -math_fast_sin_or_cos_b(IntToFloat(vars->timer) * 0.1256636083126068f) * 0.25f;
        }
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *part, *part_vars;
                part = g_moby_l04_pool + (vars->ids[i] << 8);
                part_vars = *(char **)(part + 0x68);
                qcopy_nc(old_pos, part + 0x10);
                moby_transform_joint_to_world(moby_ptr, i, part_pos);
                *(Quad8010 *)(part + 0x10) = *(Quad8010 *)part_pos;
                FastVecSub(delta, part + 0x10, old_pos);
                mat_combine_and_store(part_vars + 0x20, delta, part + 0xF0, part + 0xF0);
            }
        }
        break;
    }
    }
    if (obj->timer <= 0xFFFE)
        ++obj->timer;
}
