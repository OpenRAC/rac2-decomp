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
extern unsigned char D_00139568[];
extern char D_00239BA0[];
extern int D_00139688[];
extern int D_001B1688;
extern int D_001B275C;
extern int D_001A8CA0;
extern char D_00189E20[];
extern PickupObject *D_0018C0B0 NOT_SDA;
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
extern unsigned int func_0026F748(int, int);
extern void func_US2_002B18B0(int, int, int);
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
        if (data->f5C == 3 && (D_001B1688 & 15) == (((int)object >> 8) & 15)) {
            qzero(data);
            func_00282C90(data->f10);
            data->f5C = 0;
        }

        qcopy(old, data);
        func_00273B70(object);
        changed = 0;
        if (func_00282E48(old, data) > data->speedLimit * 2.0f)
            changed = 1;
        allow = 1;
        if (data->f5C || changed) {
            if (func_00282948(&data->f7C)) {
                if (func_00282C48(object->pos[2] - HERO->pos[2]) > HERO->pickupHeight ||
                    func_00282E80(object->pos, HERO->pos) > HERO->pickupRadius)
                    allow = 0;
            }
        } else {
            allow = 0;
            if (func_00282C48(object->pos[2] - HERO->pos[2]) < HERO->pickupHeight &&
                func_00282E80(object->pos, HERO->pos) < HERO->pickupRadius)
                data->f7C = 3;
        }
        if (D_00139688[data->weapon] >= WEAPON(data->weapon)->capacity)
            allow = 0;
        if (D_001A8CA0) {
            if (func_002B0360(object->pos) < data->groundZ - 2.0f)
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
            previous = D_00139688[item];
            func_0026F748(item, data->amount);
            if (D_00139688[item] > previous) {
                count = D_00139688[item] - previous;
                func_US2_002B18B0(count == 1 ?
                    WEAPON(item)->messageOne :
                    WEAPON(item)->messageMany,
                    count, -1);
            }
            func_002A7750(object, 2, -1);
            data->pull = 1.0f / 7.5f;
            func_00282C88(data);
            if (func_00282C30(D_001B1688 - D_001B275C) >= 11) {
                func_002E5CF8(0, 0, object);
                D_001B275C = D_001B1688;
            }
        }
        break;
    case 2:
        /* The hero's basis vectors lie at fixed offsets around its position. */
        heroPos = D_00189E20 + 0x80;
        func_00282CF0(old, object->pos, heroPos);
        func_00283098(old, old, heroPos - 0x40);
        target = 8.0f;
        if (old[2] > 0.0f)
            target = 0.0f;
        func_002AA2E8(&data->pull, target, 0.0066666668f);
        func_00282F20(move, heroPos - 0x60, data->pull);
        func_00282CC0(object->pos, object->pos, move);
        func_00282CC0(object->pos, object->pos, heroPos + 0xD0);
        speed = func_00282DF0(data);
        func_002AA2E8(&speed, 1.0666667f, 0.0066666668f);
        func_00282CF0(delta, heroPos + 0x60, object->pos);
        time = func_00282DF0(delta) / speed;
        if (time < 30.0f)
            func_002AA2E8(&object->lifetime, 0.0f, object->def->fadeRate * (1.0f / 30.0f));
        if (object->lifetime == 0.0f || time <= 1.0f) {
            func_0029F338(object);
            return;
        }
        func_00282F20(data, delta, speed);
        func_00282CC0(object->pos, object->pos, data);
        func_00282DD8(angle, heroPos - 0x60, data);
        func_002ACE78(angle, angle, 0.087266475f);
        *(PickupVectorBits *)pivot = 0;
        pivot[2] = 0.3f;
        func_00283098(before, pivot, object->basis);
        func_00283958(angle, rotation);
        func_00283738(object->basis, rotation, object->basis);
        func_00283098(after, pivot, object->basis);
        func_00282CF0(offset, after, before);
        func_00282CF0(object->pos, object->pos, offset);
        break;
    }

    if (object->state == 1 && func_00282ED8(object, D_0018C0B0)) {
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
