#include "common.h"

extern char *CreateMoby(int);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern void part_l11_spawn_spark_ring(void *, int);
extern void snd_play_from_class_bank(int, int, char *, int);

extern float D_L11_001B22C4 __attribute__((sda));
extern int D_L11_001B22CC __attribute__((sda));

typedef struct {
    float velocity[4];
    char *owner;
    float parameterA;
    float parameterB;
    float heading;
    float turn;
    float parameterD;
} SpawnState;

typedef struct {
    char pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[2];
    u8 kind;
    char pad24[8];
    float scale;
    u8 opacity;
    u8 enabled;
    u16 alpha;
    u16 flags;
    u16 pad36;
    u64 ownerFlags;
    char pad40[0x28];
    SpawnState *data;
} SpawnObject;

/* Creates the object-type 0xE7B effect for an owner: copies the start velocity and position,
   picks a random heading and turn rate, and registers it. Returns the new object or NULL. */
char *joba_swirl_effect_create(char *owner, void *velocity, void *position, float paramA, float paramB,
                        float scale, float paramD)
{
    SpawnObject *obj = (SpawnObject *)CreateMoby(0xE7B /* moby class 3707 */);

    if (obj) {
        SpawnState *state;
        int arg;

        obj->opacity = 255;
        obj->alpha = 255;
        obj->enabled = 1;
        obj->state = 0;
        obj->ownerFlags = *(long long *)(owner + 0x38);
        qcopy(obj->position, position);

        state = obj->data;
        qcopy(state, velocity);
        state->owner = owner;
        state->parameterA = paramA;
        state->parameterB = paramB;
        state->heading = math_random_angle();
        state->turn = math_random_float_range(0.0523598865f, 0.104719773f);
        state->parameterD = paramD;

        obj->kind = 255;
        obj->flags = 8;
        arg = D_L11_001B22CC;
        obj->scale = D_L11_001B22C4 * scale;
        obj->flags = 0x1008;
        part_l11_spawn_spark_ring(obj->position, arg);
        snd_play_from_class_bank(0, 0, (char *)obj, 0xE7B);
    }
    return (char *)obj;
}
