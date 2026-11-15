#include "include_asm.h"
#include "common.h"

typedef union {
    u32 words[4];
    u8 bytes[16];
} ParticleHeader;

typedef struct {
    char *object;
    int index;
    int class_id;
    float scale;
} ParticleContext;

/* A 64-byte particle slot: four quadwords. */
typedef struct {
    ParticleHeader header;
    float position[4];
    float previous_position[4];
    ParticleContext context;
} __attribute__((aligned(16))) ParticleSlot;

extern u8 *D_L09_001FF65C;
extern void *part_alloc(int);
extern int FloatToInt(float);
extern void moby_transform_joint_to_world(char *, int, char *);

/* Integer arguments stay object, index, value, parameter ($a0-$a3) and float arguments
   first_scale, second_scale ($f12-$f13); only the interleaving of the two banks is chosen. */
/* Creates one particle slot at the object (or at one of its points) with a size and fade, and returns it. */
char *part_spawn_sized(char *object, int index, float first_scale, u32 value,
                        float second_scale, int parameter)
{
    ParticleSlot *slot = part_alloc(0x37);
    float *position;

    if (slot != 0) {
        slot->header.words[1] = value;
        slot->header.words[3] = parameter;
        slot->header.bytes[9] = (u8)(FloatToInt(0.4f) + 0x20);
        slot->header.bytes[3] = 0x48;
        slot->header.bytes[1] = 3;
        slot->header.bytes[2] = D_L09_001FF65C[0];
        if (index > 0) {
            position = slot->position;
            moby_transform_joint_to_world(object, index, (char *)position);
        } else {
            qcopy(slot->position, object + 0x10);
        }
        qcopy(slot->previous_position, slot->position);
        slot->previous_position[3] = second_scale;
        slot->position[3] = first_scale;
        {
            ParticleContext *context = &slot->context;

            context->object = object;
            context->class_id = *(short *)(object + 0xAA);
            context->index = index;
            context->scale = first_scale;
        }
    }
    return (char *)slot;
}
