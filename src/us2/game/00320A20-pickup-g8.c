#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad00[0x38];
    short messageMany;
    short messageOne;
    char pad3c[2];
    short mobyClass;
    char pad40[0x4E];
    unsigned short capacity;
    char pad90[0x50];
} PickupWeapon;
typedef struct {
    float velocity[4];
    char f10[0x38];
    float speedLimit;
    char pad4c[0x10];
    unsigned char f5C;
    char pad5d[3];
    int amount;
    char pad64[4];
    int weapon;
    char pad6c[8];
    float pull;
    float groundZ;
    int f7C;
} PickupData;
typedef struct {
    char pad00[0x24];
    float fadeRate;
} PickupDef;
typedef struct {
    char pad00[0x10];
    float pos[4];
    unsigned char state;
    char pad21[2];
    unsigned char alpha;
    PickupDef *def;
    char pad28[4];
    float lifetime;
    char pad30[4];
    unsigned short flags;
    char pad36[0x32];
    PickupData *data;
    char pad6c[0x3E];
    short weaponClass;
    char padac[0x14];
    float basis[4];
} PickupObject;
typedef struct {
    char pad00[0x80];
    float pos[4];
    char pad90[0x2232];
    unsigned char flag22c2;
    char pad22c3[0x1E1];
    float pickupRadius;
    float pickupHeight;
    char pad24ac[0x20];
    int active;
} PickupHero;
extern unsigned char g_item_slot_to_record[];
extern char g_weapon_table[];
extern int g_item_ammo_counts[];
extern int g_game_time;
extern int D_001B275C;
extern int D_001A8CA0;
extern char g_hero_state[];
extern PickupObject *g_hero_moby NOT_SDA;
#define WEAPON(i) ((PickupWeapon *)(D_00239BA0 + D_00139568[i] * sizeof(PickupWeapon)))
#define HERO ((PickupHero *)D_00189E20)
extern void vec_store_helper(void *);
extern void vec_clear_128(void *);
extern int cam_moby_update(void *);
extern float fast_vec_dist(void *, void *);
extern int math_fast_float_d(void *);
extern float math_fabs(float);
extern float vec_distance_xy(void *, void *);
extern float gravity_get_center_distance(void *);
extern unsigned int stub_empty_8(int, int);
extern void func_US2_002B18B0(int, int, int);
extern void moby_set_state(void *, int, int);
extern int subtract_integer_with_clamp(int);
extern int PlayMobySound(int, int, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void ApproachValue(void *, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern void moby_mark_spawned(void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_set_direction_with_complement(void *, void *, float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern int vec_fast_helper_d(void *, void *);
typedef int PickupVectorBits __attribute__((mode(TI)));

/* Award ammo on collection, then move and rotate the pickup into the hero. */
void func_US2_00320A20(PickupObject *object)
{
    float old[4], move[4], delta[4], angle[4];
    float before[4], after[4], offset[4], pivot[4], rotation[12];
    float speed, time, target;
    PickupData *data = object->data;
    char *heroPos;
    int i, changed, allow, item, previous, count;

    switch (object->state) {
    case 0:
        object->state = 1;
        for (i = 0; i < 56; i++) {
            PickupWeapon *entry = WEAPON(i);

            if (entry->mobyClass == object->weaponClass)
                data->weapon = i;
        }
        break;
    case 1:
        if (data->f5C == 3 && (g_game_time & 15) == (((int)object >> 8) & 15)) {
            qzero(data);
            vec_store_helper(data->f10);
            data->f5C = 0;
        }

        qcopy(old, data);
        cam_moby_update(object);
        changed = 0;
        if (fast_vec_dist(old, data) > data->speedLimit * 2.0f)
            changed = 1;
        allow = 1;
        if (data->f5C || changed) {
            if (math_fast_float_d(&data->f7C)) {
                if (math_fabs(object->pos[2] - HERO->pos[2]) > HERO->pickupHeight ||
                    vec_distance_xy(object->pos, HERO->pos) > HERO->pickupRadius)
                    allow = 0;
            }
        } else {
            allow = 0;
            if (math_fabs(object->pos[2] - HERO->pos[2]) < HERO->pickupHeight &&
                vec_distance_xy(object->pos, HERO->pos) < HERO->pickupRadius)
                data->f7C = 3;
        }
        if (g_item_ammo_counts[data->weapon] >= WEAPON(data->weapon)->capacity)
            allow = 0;
        if (D_001A8CA0) {
            if (gravity_get_center_distance(object->pos) < data->groundZ - 2.0f)
                goto permit;
        } else if (object->pos[2] < data->groundZ - 2.0f) {
            goto permit;
        }
        if (HERO->flag22c2) {
        permit:
            allow = 1;
        }
        if (!HERO->active)
            allow = 0;
        if (allow) {
            item = data->weapon;
            previous = g_item_ammo_counts[item];
            stub_empty_8(item, data->amount);
            if (g_item_ammo_counts[item] > previous) {
                count = g_item_ammo_counts[item] - previous;
                func_US2_002B18B0(count == 1 ?
                    WEAPON(item)->messageOne :
                    WEAPON(item)->messageMany,
                    count, -1);
            }
            moby_set_state(object, 2, -1);
            data->pull = 1.0f / 7.5f;
            vec_clear_128(data);
            if (subtract_integer_with_clamp(g_game_time - D_001B275C) >= 11) {
                PlayMobySound(0, 0, object);
                D_001B275C = g_game_time;
            }
        }
        break;
    case 2:
        /* The hero's basis vectors lie at fixed offsets around its position. */
        heroPos = g_hero_state + 0x80;
        FastVecSub(old, object->pos, heroPos);
        matrix_mul_vec3(old, old, heroPos - 0x40);
        target = 8.0f;
        if (old[2] > 0.0f)
            target = 0.0f;
        ApproachValue(&data->pull, target, 0.0066666668f);
        vec_scale_to_length(move, heroPos - 0x60, data->pull);
        FastVecAdd(object->pos, object->pos, move);
        FastVecAdd(object->pos, object->pos, heroPos + 0xD0);
        speed = FastVecLength(data);
        ApproachValue(&speed, 1.0666667f, 0.0066666668f);
        FastVecSub(delta, heroPos + 0x60, object->pos);
        time = FastVecLength(delta) / speed;
        if (time < 30.0f)
            ApproachValue(&object->lifetime, 0.0f, object->def->fadeRate * (1.0f / 30.0f));
        if (object->lifetime == 0.0f || time <= 1.0f) {
            moby_mark_spawned(object);
            return;
        }
        vec_scale_to_length(data, delta, speed);
        FastVecAdd(object->pos, object->pos, data);
        FastVecCross(angle, heroPos - 0x60, data);
        vec_set_direction_with_complement(angle, angle, 0.087266475f);
        *(PickupVectorBits *)pivot = 0;
        pivot[2] = 0.3f;
        matrix_mul_vec3(before, pivot, object->basis);
        quaternion_to_rotation_basis(angle, rotation);
        multiply_matrix3x3(object->basis, rotation, object->basis);
        matrix_mul_vec3(after, pivot, object->basis);
        FastVecSub(offset, after, before);
        FastVecSub(object->pos, object->pos, offset);
        break;
    }

    if (object->state == 1 && vec_fast_helper_d(object, g_hero_moby)) {
        if (object->alpha > 36)
            object->alpha -= 4;
        else
            object->alpha = 36;
    } else {
        if (object->alpha < 124)
            object->alpha += 4;
        else
            object->alpha = 128;
    }
    if ((signed char)object->alpha >= 0)
        object->flags |= 0x2000;
    else
        object->flags &= 0xDFFF;
}
