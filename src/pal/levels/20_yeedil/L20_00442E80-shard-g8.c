#include "include_asm.h"

#include "common.h"
typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { char pad[0x80]; Vec position; char pad90[0x40]; Vec top; } PlayerView;
typedef struct {
    Vec velocity;
    Vec trail[3];
    float radius, angle, targetRadius, targetZ, radiusSpeed, spin, zSpeed, baseZ, pad60;
    int timer;
    int reverse;
    int *clock;
    float scale;
} ShardState;
extern PlayerView D_00189E20;
typedef struct { char pad[0xF0]; float rot[3]; } Moby;
extern int D_L20_001A8F00, D_L20_001C0418[];
extern int D_L20_001B2AC8;
extern float D_L20_001B1F9C __attribute__((sda)), D_L20_001B1FA0 __attribute__((sda));
extern float D_L20_001B1FA4 __attribute__((sda)), D_L20_001B1FA8 __attribute__((sda));
extern float D_L20_001B1FAC __attribute__((sda)), D_L20_001B1FB0 __attribute__((sda));
extern float D_L20_001B1FB4 __attribute__((sda)), D_L20_001B1FB8 __attribute__((sda));
extern char D_L20_001B9FC0[];
extern void func_0029F338(void *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern float func_002AA2E8(float *, float, float);
extern float func_00283180(float), func_00283198(float), func_00282C48(float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float);
extern float func_00283B98(float, float), func_00283248(float, float), func_00283C80(float, float);
extern float func_002A7878(float, float), func_00282E20(void *), func_00282DF0(void *);
extern int func_00282948(void *), func_00282C30(int);
extern void func_002A7750(void *, int, int);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002A8C28(void *, void *, float, float, int, float, int, int, int);
extern void func_PAL_0032F3B8(void *, void *, void *, float);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_PAL_L20_00444E38(char *), func_L20_0043F510(void *);

void func_PAL_L20_00444688(unsigned char *obj)
{
    Vec old, delta, target;
    float speed;
    ShardState *s = *(ShardState **)(obj + 0x68);

    if (D_L20_001A8F00 == 2) {
        func_0029F338(obj);
        return;
    }
    qcopy(old, obj + 0x10);
    switch (obj[0x20]) {
    case 0:
        func_002AA548(&s->radius, &s->radiusSpeed, s->targetRadius, D_L20_001B1F9C * 0.00040000002f, D_L20_001B1F9C * 0.00040000002f, D_L20_001B1FA0 * 0.020000001f);
        ((float *)(obj + 0x10))[0] = func_00283180(s->angle) * s->radius;
        ((float *)(obj + 0x10))[1] = func_00283198(s->angle) * s->radius;
        ((float *)(obj + 0x10))[2] = 0.0f;
        func_00282CC0(obj + 0x10, obj + 0x10, *(char **)(obj + 0xB8) + 0x10);
        ((float *)(obj + 0x10))[2] = old[2];
        if (func_00282C48(s->radius - s->targetRadius) < 0.5f) {
            speed = D_L20_001B1FA4 * 0.0003490659f;
            if (s->reverse == 0)
                speed = -speed;
            func_002AA2E8(&s->spin, speed, D_L20_001B1FA8 * 6.981318e-06f);
            s->angle = func_00283B98(s->angle, s->spin);
            func_002AA548((float *)(obj + 0x18), &s->zSpeed, s->targetZ, D_L20_001B1FAC * 0.00040000002f, D_L20_001B1FAC * 0.00040000002f, D_L20_001B1FB0 * 0.020000001f);
            if (func_00282C48(((float *)(obj + 0x10))[2] - s->targetZ) < 0.1f)
                s->targetZ = s->baseZ + func_002A7878(3.0f, 8.0f);
        }
        if (func_00282948(&s->timer)
            && func_00283C80(((Moby *)obj)->rot[2], func_00283248(D_00189E20.position[0] - ((float *)(obj + 0x10))[0], D_00189E20.position[1] - ((float *)(obj + 0x10))[1])) < 0.62831855f) {
            func_00282CF0(s->velocity, obj + 0x10, old);
            s->velocity[2] = 0.0f;
            func_002A7750(obj, 1, -1);
        } else if (func_00282C30(*s->clock - D_L20_001B2AC8) >= 6) {
            func_00282CF0(s->velocity, obj + 0x10, old);
            s->velocity[2] = 0.0f;
            func_002A7750(obj, 2, -1);
        }
        break;
    case 1:
        {
            float rate;

            { float b = D_L20_001B1FB0 * 0.020000001f; func_002AA548((float *)(obj + 0x18), &s->zSpeed, s->baseZ + 1.0f, D_L20_001B1FAC * 0.00040000002f, D_L20_001B1FAC * 0.00040000002f, b); }
            rate = D_L20_001B1FB8 * 0.020000001f;
            func_00282CF0(target, D_00189E20.top, obj + 0x10);
            target[2] = 0.0f;
            func_00282F20(target, target, rate);
            func_00282CF0(delta, target, s->velocity);
            func_00282F20(delta, delta, D_L20_001B1FB4 * 0.00040000002f);
            func_00282CC0(s->velocity, s->velocity, delta);
            func_00282F20(s->velocity, s->velocity, rate);
            func_00282CC0(obj + 0x10, obj + 0x10, s->velocity);
            if (func_00283C80(((Moby *)obj)->rot[2], func_00283248(D_00189E20.position[0] - ((float *)(obj + 0x10))[0], D_00189E20.position[1] - ((float *)(obj + 0x10))[1])) > 1.5707964f)
                func_002A7750(obj, 2, -1);
        }
        break;
    case 2:
        {
            float length = func_00282DF0(s->velocity);

            func_002AA2E8(&length, D_L20_001B1FB8 * 0.020000001f, 0.004f);
            func_00282F20(s->velocity, s->velocity, length);
            func_00282CC0(obj + 0x10, obj + 0x10, s->velocity);
            if (obj[0x31] == 0) {
                func_0029F338(obj);
                return;
            }
        }
        break;
    }
    func_00282CF0(delta, obj + 0x10, old);
    ((Moby *)obj)->rot[2] = func_00283248(delta[0], delta[1]);
    ((Moby *)obj)->rot[1] = -func_00283248(func_00282E20(delta), delta[2]);
    ((Moby *)obj)->rot[0] = func_00283B98(((Moby *)obj)->rot[0], 0.062831864f);
    if ((D_L20_001B2AC8 & 3) == (((int)obj >> 8) & 3)) {
        int i;

        for (i = 2; i > 0; i--)
            qcopy(s->trail[i], s->trail[i - 1]);
        qcopy(s->trail[0], obj + 0x10);
    }
    if (func_002761F8(old, obj + 0x10, 0, *(void **)(obj + 0xB8), 0)) {
        if (D_L20_001C0418[0]) {
            func_00282CF0(target, D_L20_001B9FC0, obj + 0x10);
            func_00282F20(target, target, 1.0f);
            func_002A8C28(*(void **)(obj + 0xB8), obj + 0x10, 2.0f, s->scale, 0x10001, 1.0f, 0, 1, 0);
            func_PAL_0032F3B8(obj, obj + 0x10, target, 0.0f);
        } else {
            func_PAL_L00_003FB330(obj + 0x10, 0, 10, 20, 20, 20, 45, 0, 0.75f, 20.0f, 1, 0, 0, 0);
        }
        func_002E5CF8(0, 0, obj);
        func_0029F338(obj);
        return;
    }
    if (obj[0x31])
        func_PAL_L20_00444E38(obj);
    func_L00_002E6EF8(func_L20_0043F510, obj);
}
