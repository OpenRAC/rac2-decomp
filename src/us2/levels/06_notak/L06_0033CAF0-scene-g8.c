/*
 * func_US2_L06_0033CAF0, the USA v2.00 copy of func_L06_0033BDC0: the same C, where the
 * 0xFA0 arm also tests D_001A79F0 != 0x33. Indexing from the base, not through the member,
 * keeps the offset out of a hoisted add, so loop.c still moves 0xFA0 in its first pass.
 */
#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));

typedef struct {
    unsigned char pad00[0x34];
    unsigned short flags;
    unsigned char pad36[0x32];
    char *state;
    unsigned char pad6C[0x3E];
    short class_id;
    unsigned char padAC[0x14];
    Vector velocity;
    Vector offset;
} Moby;

typedef struct {
    unsigned char pad00[4];
    int mode;
    unsigned char pad08[2];
    unsigned char tint;
    unsigned char frame;
} ParticleTail;

/* Particle returned by func_002BDCE8. */
typedef struct {
    unsigned char pad00[8];
    unsigned char f08;
    unsigned char life;
    union {
        short word;
        unsigned char byte;
    } f0A;
    unsigned char pad0C[0x14];
    ParticleTail tail;
} Particle;

typedef struct {
    unsigned char before_active[0x30]; int active;
    unsigned char before_count[0x10]; short count;
    unsigned char before_objects[0x146];
    Moby *objects[0];
} ScenePrefix;

extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(Moby *);
extern void math_store_angle_update_result(void *, void *, int, int, float);
extern ScenePrefix D_L06_001BD540;
extern int g_current_map_index MACRO_ADDR;
extern void moby_transform_joint_to_world(void *, int, void *);
extern int math_random_int_below(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern Particle *SpawnSpinningSparkParticle(void *, float, float, float, int, void *, float, int, int);
extern int FloatToInt(float);

/* Update special scene objects, then emit the ship's paired exhaust particles. */
void func_US2_L06_0033CAF0(void)
{
    Vector left, right, velocity, position, shift;
    Moby *ship;
    Particle *first, *second, *spark;
    int i, rotation;

    anim_start_startup_animations();

    for (i = 0; i < D_L06_001BD540.count; i++) {
        Moby *obj = ((ScenePrefix *)((int *)&D_L06_001BD540 + i))->objects[0];

        if (obj && obj->class_id == 0xE29)
            obj->flags |= 0x800;
        if (obj->class_id == 0xD54)
            UpdateEquipmentPieces(obj);
        if (obj && obj->class_id == 0xFA0 && g_current_map_index != 0x33) {
            char *state = obj->state;

            if (state)
                math_store_angle_update_result(obj, state + 0xC, 0x80AAAAD2, 0x80396464, 0.06108653545f);
        }
    }

    if (g_current_map_index != 6 || D_L06_001BD540.active)
        return;

    ship = D_L06_001BD540.objects[2];
    if (ship->class_id != 0xE29)
        return;

    moby_transform_joint_to_world(ship, 0, left);
    moby_transform_joint_to_world(ship, 1, right);
    rotation = math_random_int_below(16);
    vec_scale_to_length(velocity, ship->velocity, 0.7333333492f);
    if (math_random_int_below(2))
        rotation = -rotation;
    qcopy(position, left);

    first = SpawnSpinningSparkParticle(position, 0.1f, 1.0f, 0.9f, rotation, velocity, 315000.0f, 0xDF204080, 0);
    if (first) {
        ParticleTail *tail = &first->tail;
        first->f0A.word = 7;
        first->life = FloatToInt(4.0f) + 0x70;
        tail->mode = 2;
        tail->tint = 0xDF;
        tail->frame = first->f0A.byte;
    }

    second = SpawnSpinningSparkParticle(position, 0.1f, 1.0f, 0.9f, rotation, velocity, 315000.0f, 0xDF204080, 0);
    if (second) {
        ParticleTail *tail = &second->tail;
        first->f0A.word = 7;
        first->life = FloatToInt(4.0f) + 0x70;
        tail->mode = 2;
        tail->tint = 0xDF;
        tail->frame = first->f0A.byte;
    }

    spark = SpawnSpinningSparkParticle(position, 0.05f, 1.0f, 0.97f, 16, velocity, 210000.0f, 0xDFFFFFFF, 0);
    if (spark) {
        ParticleTail *tail = &spark->tail;
        spark->life = FloatToInt(4.0f) + 0x70;
        spark->f0A.word = 7;
        spark->f08 = math_random_int_below(255);
        tail->mode = 2;
        tail->tint = 0xDF;
        tail->frame = first->f0A.byte;
    }

    *(VectorBits *)shift = *(VectorBits *)ship->offset;
    vec_scale_to_length(shift, shift, 0.3f);
    FastVecAdd(position, position, shift);

    first = SpawnSpinningSparkParticle(position, 0.1f, 1.0f, 0.9f, 16, velocity, 315000.0f, 0xDF204080, 0);
    if (first) {
        ParticleTail *tail = &first->tail;
        first->f0A.word = 7;
        first->life = FloatToInt(4.0f) + 0x70;
        tail->mode = 2;
        tail->tint = 0xDF;
        tail->frame = first->f0A.byte;
    }

    second = SpawnSpinningSparkParticle(position, 0.1f, 1.0f, 0.9f, 16, velocity, 315000.0f, 0xDF204080, 0);
    if (second) {
        ParticleTail *tail = &second->tail;
        first->f0A.word = 7;
        first->life = FloatToInt(4.0f) + 0x70;
        tail->mode = 2;
        tail->tint = 0xDF;
        tail->frame = first->f0A.byte;
    }

    spark = SpawnSpinningSparkParticle(position, 0.05f, 1.0f, 0.97f, 16, velocity, 210000.0f, 0xDFFFFFFF, 0);
    if (spark) {
        ParticleTail *tail = &spark->tail;
        spark->life = FloatToInt(4.0f) + 0x70;
        spark->f0A.word = 7;
        spark->f08 = math_random_int_below(255);
        tail->mode = 2;
        tail->tint = 0xDF;
        tail->frame = first->f0A.byte;
    }
}
