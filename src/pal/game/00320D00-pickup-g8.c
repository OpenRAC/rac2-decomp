#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad00[0x38];
    short message_many;
    short message_one;
    char pad3c[2];
    short moby_class;
    char pad40[0x4E];
    unsigned short capacity;
    char pad90[0x50];
} PickupWeapon;
typedef struct {
    float velocity[4];
    char f10[0x38];
    float speed_limit;
    char pad4c[0x10];
    unsigned char f5C;
    char pad5d[3];
    int amount;
    char pad64[4];
    int weapon;
    char pad6c[8];
    float pull;
    float ground_z;
    int f7C;
} PickupData;
typedef struct {
    char pad00[0x24];
    float fade_rate;
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
    short weapon_class;
    char padac[0x14];
    float basis[4];
} PickupObject;
typedef struct {
    char pad00[0x80];
    float pos[4];
    char pad90[0x2232];
    unsigned char flag22c2;
    char pad22c3[0x1E1];
    float pickup_radius;
    float pickup_height;
    char pad24ac[0x20];
    int active;
} PickupHero;
extern unsigned char g_item_slot_to_record[];
extern char g_weapon_table[];
extern int g_item_ammo_counts[];
extern int g_game_time;
extern int g_pickup_time;
extern int g_ground_check_inhibit;
extern char g_hero_state[];
extern PickupObject *g_hero_moby NOT_SDA;
#define WEAPON(i) ((PickupWeapon *)(D_00239BA0 + D_00139568[i] * sizeof(PickupWeapon)))
#define HERO ((PickupHero *)D_00189E20)
extern void vec_store_helper(void *);
extern void vec_clear_128(void *);
extern int cam_moby_update_pal(void *);
extern float fast_vec_dist(void *, void *);
extern int math_fast_float_d(void *);
extern float math_fabs(float);
extern float vec_distance_xy(void *, void *);
extern float gravity_get_center_distance(void *);
extern unsigned int stub_empty_7(int, int);
extern void value_forward_three_args_pal(int, int, int);
extern void moby_set_state(void *, int, int);
extern int subtract_integer_with_clamp(int);
extern int PlayMobySound(int, int, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern f32 ApproachValue(void *, float, float);
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
void UpdateWeaponAmmoPickup_pal(PickupObject *object)
{
    float old[4], move[4], delta[4], angle[4];
    float before[4], after[4], offset[4], pivot[4], rotation[12];
    float speed, time, target;
    PickupData *data = object->data;
    char *hero_pos;
    int i, changed, allow, item, previous, count;

    switch (object->state) {
    case 0:
        object->state = 1;
        for (i = 0; i < 56; i++) {
            PickupWeapon *entry = WEAPON(i);

            if (entry->moby_class == object->weapon_class)
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
        cam_moby_update_pal(object);
        changed = 0;
        if (fast_vec_dist(old, data) > data->speed_limit * 2.0f)
            changed = 1;
        allow = 1;
        if (data->f5C || changed) {
            if (math_fast_float_d(&data->f7C)) {
                if (math_fabs(object->pos[2] - HERO->pos[2]) > HERO->pickup_height ||
                    vec_distance_xy(object->pos, HERO->pos) > HERO->pickup_radius)
                    allow = 0;
            }
        } else {
            allow = 0;
            if (math_fabs(object->pos[2] - HERO->pos[2]) < HERO->pickup_height &&
                vec_distance_xy(object->pos, HERO->pos) < HERO->pickup_radius)
                data->f7C = 3;
        }
        if (g_item_ammo_counts[data->weapon] >= WEAPON(data->weapon)->capacity)
            allow = 0;
        if (g_ground_check_inhibit) {
            if (gravity_get_center_distance(object->pos) < data->ground_z - 2.0f)
                goto permit;
        } else if (object->pos[2] < data->ground_z - 2.0f) {
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
            stub_empty_7(item, data->amount);
            if (g_item_ammo_counts[item] > previous) {
                count = g_item_ammo_counts[item] - previous;
                value_forward_three_args_pal(count == 1 ?
                    WEAPON(item)->message_one :
                    WEAPON(item)->message_many,
                    count, -1);
            }
            moby_set_state(object, 2, -1);
            data->pull = 0.16000001f;
            vec_clear_128(data);
            if (subtract_integer_with_clamp(g_game_time - g_pickup_time) >= 9) {
                PlayMobySound(0, 0, object);
                g_pickup_time = g_game_time;
            }
        }
        break;
    case 2:
        /* The hero's basis vectors lie at fixed offsets around its position. */
        hero_pos = g_hero_state + 0x80;
        FastVecSub(old, object->pos, hero_pos);
        matrix_mul_vec3(old, old, hero_pos - 0x40);
        target = 8.0f;
        if (old[2] > 0.0f)
            target = 0.0f;
        ApproachValue(&data->pull, target, 0.0096f);
        vec_scale_to_length(move, hero_pos - 0x60, data->pull);
        FastVecAdd(object->pos, object->pos, move);
        FastVecAdd(object->pos, object->pos, hero_pos + 0xD0);
        speed = FastVecLength(data);
        ApproachValue(&speed, 1.2800001f, 0.0096f);
        FastVecSub(delta, hero_pos + 0x60, object->pos);
        time = FastVecLength(delta) / speed;
        if (time < 25.0f)
            ApproachValue(&object->lifetime, 0.0f, object->def->fade_rate * (0.04f));
        if (object->lifetime == 0.0f || time <= 1.0f) {
            moby_mark_spawned(object);
            return;
        }
        vec_scale_to_length(data, delta, speed);
        FastVecAdd(object->pos, object->pos, data);
        FastVecCross(angle, hero_pos - 0x60, data);
        vec_set_direction_with_complement(angle, angle, 0.10471977f);
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
