#include "include_asm.h"

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
extern DebrisObject_F3FED60 *func_0029EFD0(int);
extern float func_002A7940(void);
extern void func_002833F0(void *, void *);
extern float func_002A7878(float, float);
extern void func_002AB668(void *, void *, float);
extern int func_002FED90(void *, void *, float, float, float);
extern void func_002A0F48(void *);
extern float D_L00_001B0C38 __attribute__((sda));
extern float D_L00_001B0C2C __attribute__((sda));

/* Spawns a piece of debris at the position with the given velocity, a random spin and a
   scale that depends on the flag. */
DebrisObject_F3FED60 *func_PAL_L00_00403640(SpawnVector_F3FED60 *position, SpawnVector_F3FED60 *velocity, int flag)
{
    DebrisObject_F3FED60 *object = func_0029EFD0(0xE64);
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
        state->life = 12;
        object->angle[0] = func_002A7940();
        object->angle[1] = func_002A7940();
        object->angle[2] = func_002A7940();
        func_002833F0(object->rotation, object->angle);
        spin = func_002A7878(0.062831864f, 0.12566373f);
        func_002AB668(&state->spin, object->matrix, spin);
        if (flag) object->scale *= D_L00_001B0C38;
        else object->scale *= D_L00_001B0C2C;
        state->shadow = func_002FED90(object, 0, 1.0f, 1.0f, 1.0f);
        func_002A0F48(object);
    }
    return object;
}
