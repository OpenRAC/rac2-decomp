#include "common.h"

typedef int SpawnVector_F3FED60 __attribute__((mode(TI)));
typedef struct {
    SpawnVector_F3FED60 velocity;
    SpawnVector_F3FED60 spin;
    u8 unknown20[4];
    int age;
    int life;
    int bounced;
    int shadow;
} DebrisState_F3FED60;
/* Partial object view; the gaps are unmeasured. */
typedef struct {
    u8 unknown00[0x10];
    SpawnVector_F3FED60 position;
    u8 mode;
    u8 unknown21[0xB];
    float scale;
    u8 intensity;
    u8 unknown31;
    u16 colour;
    u16 flags;
    u8 unknown36[0x32];
    DebrisState_F3FED60 *state;
    u8 unknown6C[0x54];
    u8 rotation[0x10];
    u8 matrix[0x20];
    float angle[4];
} DebrisObject_F3FED60;

extern DebrisObject_F3FED60 *CreateMoby(int);
extern float math_random_angle(void);
extern void euler_rotation_basis(void *, void *);
extern float math_random_float_range(float, float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern int part_alloc_effect_slot(void *, void *, float, float, float);
extern void func_002A0F48(void *);
extern float D_L00_001B0C38 __attribute__((sda));
extern float D_L00_001B0C2C __attribute__((sda));

/* Spawns a piece of debris at the position with the given velocity, a random spin and a
   scale that depends on the flag. */
DebrisObject_F3FED60 *bouncer_spawn_debris_object(SpawnVector_F3FED60 *position, SpawnVector_F3FED60 *velocity, int flag)
{
    DebrisObject_F3FED60 *object = CreateMoby(0xE64 /* moby class 3684 */);
    if (object != 0) {
        DebrisState_F3FED60 *state;
        float spin;
        object->flags |= 0x100;
        object->mode = 0;
        state = object->state;
        object->colour = 255;
        object->intensity = 255;
        qcopy(&object->position, position);
        qcopy(&state->velocity, velocity);
        state->bounced = flag;
        state->age = 0;
        state->life = 15;
        object->angle[0] = math_random_angle();
        object->angle[1] = math_random_angle();
        object->angle[2] = math_random_angle();
        euler_rotation_basis(object->rotation, object->angle);
        spin = math_random_float_range(0.052359886f, 0.10471977f);
        math_build_axis_angle_quat(&state->spin, object->matrix, spin);
        if (flag) object->scale *= D_L00_001B0C38;
        else object->scale *= D_L00_001B0C2C;
        state->shadow = part_alloc_effect_slot(object, 0, 1.0f, 1.0f, 1.0f);
        func_002A0F48(object);
    }
    return object;
}
