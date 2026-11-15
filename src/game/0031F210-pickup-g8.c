#include "common.h"

/* Weapon-definition fields used by the ammo pickup (0xE0 bytes per entry). */
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

/* Per-pickup data: velocity vector, target weapon and collection state. */
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

/* The pickup's definition: only the rate used to fade its lifetime. */
typedef struct {
    char pad00[0x24];
    float fadeRate;
} PickupDef;

/* Moby fields used by the pickup. */
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

/* Hero state fields used while collecting and flying the pickup into the hero. */
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

extern unsigned char D_00139568[];
extern char D_00239BA0[];
extern int D_00139688[];
extern int D_001B1688;
extern int D_001B275C;
extern int D_001A8CA0;
extern char D_00189E20[];
extern PickupObject *D_0018C0B0 NOT_SDA;

/* The weapon definition of pickup-table slot i, and the hero state. */
#define WEAPON(i) ((PickupWeapon *)(D_00239BA0 + D_00139568[i] * sizeof(PickupWeapon)))
#define HERO ((PickupHero *)D_00189E20)

extern void func_00282C90(void *);
extern void func_00282C88(void *);
extern int func_00273B70(void *);
extern float func_00282E48(void *, void *);
extern int func_00282948(void *);
extern float func_00282C48(float);
extern float func_00282E80(void *, void *);
extern float func_002B0360(void *);
extern unsigned int func_0026F740(int, int);
extern void func_002B0A48(int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_00282C30(int);
extern int func_002E5CF8(int, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AA2E8(void *, float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_0029F338(void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_002ACE78(void *, void *, float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern int func_00282ED8(void *, void *);

typedef int PickupVectorBits __attribute__((mode(TI)));

/* Award ammo on collection, then move and rotate the pickup into the hero. */
void func_0031FC28(PickupObject *object)
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
        if (data->f5C == 3 && (gGameTime & 15) == (((int)object >> 8) & 15)) {
            qzero(data);
            StoreVectorHelper(data->f10);
            data->f5C = 0;
        }

        qcopy(old, data);
        UpdateCameraMoby(object);
        changed = 0;
        if (fast_vec_dist(old, data) > data->speedLimit * 2.0f)
            changed = 1;
        allow = 1;
        if (data->f5C || changed) {
            if (FastFloatHelperD(&data->f7C)) {
                if (FloatAbs(object->pos[2] - HERO->pos[2]) > HERO->pickupHeight ||
                    vec_distance_xy(object->pos, HERO->pos) > HERO->pickupRadius)
                    allow = 0;
            }
        } else {
            allow = 0;
            if (FloatAbs(object->pos[2] - HERO->pos[2]) < HERO->pickupHeight &&
                vec_distance_xy(object->pos, HERO->pos) < HERO->pickupRadius)
                data->f7C = 3;
        }
        if (gItemAmmoCounts[data->weapon] >= WEAPON(data->weapon)->capacity)
            allow = 0;
        if (D_001A8CA0) {
            if (GetDistanceFromGravityCenter(object->pos) < data->groundZ - 2.0f)
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
            previous = gItemAmmoCounts[item];
            EmptyStubF740(item, data->amount);
            if (gItemAmmoCounts[item] > previous) {
                count = gItemAmmoCounts[item] - previous;
                ForwardThreeArgumentCall(count == 1 ?
                    WEAPON(item)->messageOne :
                    WEAPON(item)->messageMany,
                    count, -1);
            }
            SetMobyState(object, 2, -1);
            data->pull = 1.0f / 7.5f;
            ClearVector128(data);
            if (subtract_integer_with_clamp(gGameTime - D_001B275C) >= 11) {
                PlayMobySound(0, 0, object);
                D_001B275C = gGameTime;
            }
        }
        break;
    case 2:
        /* The hero's basis vectors lie at fixed offsets around its position. */
        heroPos = gHeroState + 0x80;
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
            MarkMobySpawned(object);
            return;
        }
        vec_scale_to_length(data, delta, speed);
        FastVecAdd(object->pos, object->pos, data);
        FastVecCross(angle, heroPos - 0x60, data);
        SetDirectionWithComplement(angle, angle, 0.087266475f);
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

    if (object->state == 1 && FastVectorHelperD(object, gHeroMoby_0018C0B0)) {
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
