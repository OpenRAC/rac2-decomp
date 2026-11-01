#include "include_asm.h"

#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { Quadword whole; float f[4] __attribute__((aligned(16))); } Vector;
typedef struct { unsigned char prefix[0x18]; char *object; int polygon; Vector point, offset, normal; } CollisionView;
extern unsigned char D_L06_001BFC80[];
#define COLLISION (*(CollisionView *)D_L06_001BFC80)
extern void func_002829A8(unsigned char *);
extern int func_00282978(unsigned char *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00283028(void *, void *, void *);
extern float func_00282E20(void *);
extern float func_00282DF0(void *);
extern float func_00283248(float, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern int func_00278E78(void);
extern float func_002A7878(float, float);
extern int func_002E5CF8(int, int, char *);
extern float func_002ABB18(float);
extern float func_002A89A8(void *, int, float);
extern void func_002A9288(char *, float);
extern char *func_L04_003EDD40(char *, Vector *);
extern void func_L06_0041CAB0(char *, char *);
typedef struct { Vector velocity; char *owner; char *successor; short timeout; unsigned char handoff, cooldown; } FlockStatePrefix;

/* Move a small flock member, separating it from walls and its live siblings. */
void func_PAL_L06_00420DC0(char *object)
{
    FlockStatePrefix *state = *(FlockStatePrefix **)(object + 0x68);
    struct { Vector old_position, probe, separation; } work;
    char *other;
    char **siblings;
    int i;
    float distance;
    *(unsigned int *)(object + 0x78) = 0x80808080;
    func_002829A8((unsigned char *)state + 0x1b);
    qcopy(&work.old_position, object + 0x10);
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(float *)(object + 0x2c) += (*(float *)(*(char **)(object + 0x24) + 0x24) - *(float *)(object + 0x2c)) * 0.060000002f;
        func_00282CC0(object + 0x10, object + 0x10, state);
        func_00282F20(&work.probe, state, 0.2f);
        func_00282CC0(&work.probe, &work.probe, object + 0x10);
        *(int *)(object + 0x98) = 0;
        *(int *)(state->owner + 0x98) = 0;
        if (func_002761F8(&work.old_position, &work.probe, 4, object, 0)) {
            func_00282CF0(&work.probe, &COLLISION.point, &work.probe);
            func_00282F20(&work.probe, &work.probe, 0.215f);
            func_00282CC0(object + 0x10, object + 0x10, &work.probe);
            if (COLLISION.polygon >= 0) {
                func_00283028(state, state, &COLLISION.normal);
                if (func_00283248(COLLISION.normal.f[2], func_00282E20(&COLLISION.normal)) < 0.69813179969787597656f && func_00278E78() == -1) {
                    func_00282D30(state, state, 0.5f);
                    if (func_00282DF0(state) < 0.025f)
                        *(unsigned char *)(object + 0x20) = 1;
                }
            } else {
                if (*(short *)(COLLISION.object + 0xaa) != 0xb66) {
                    func_00283028(state, state, &COLLISION.normal);
                    if (func_00283248(COLLISION.normal.f[2], func_00282E20(&COLLISION.normal)) < 0.69813179969787597656f && func_00278E78() == -1)
                        func_00282D30(state, state, 1.2f);
                } else {
                    state->velocity.f[2] *= func_002A7878(0.9f, 1.1f);
                }
            }
            if (state->cooldown == 0) {
                func_002E5CF8(0, 0, object);
                state->cooldown = 12;
            }
        }
        if (func_00277258((object + 0x10), 4, object, 0.2f)) {
            func_00282CF0(&work.probe, &COLLISION.point, &COLLISION.offset);
            func_00282F20(&work.probe, &work.probe, 0.015f);
            func_00282CC0((object + 0x10), &COLLISION.offset, &work.probe);
            if (COLLISION.object == 0) {
                func_00283028(state, state, &COLLISION.normal);
                if (func_00283248(COLLISION.normal.f[2], func_00282E20(&COLLISION.normal)) < 0.69813179969787597656f && func_00278E78() == -1) {
                    func_00282D30(state, state, 0.5f);
                    if (func_00282DF0(state) < 0.025f)
                        *(unsigned char *)(object + 0x20) = 1;
                }
            } else if (*(short *)(COLLISION.object + 0xaa) != 0xb66) {
                func_00283028(state, state, &COLLISION.normal);
                if (func_00283248(COLLISION.normal.f[2], func_00282E20(&COLLISION.normal)) < 0.69813179969787597656f && func_00278E78() == -1)
                    func_00282D30(state, state, 1.2f);
            } else {
                state->velocity.f[2] *= func_002A7878(0.9f, 1.1f);
            }
            if (state->cooldown == 0) {
                func_002E5CF8(0, 0, object);
                state->cooldown = 12;
            }
        }
        siblings = (char **)(*(char **)(state->owner + 0x68) + 0xa0);
        for (i = 0; i < 20; i++, siblings++) {
            other = *siblings;
            if (other != object && other != 0 && *(short *)(other + 0xaa) == 0xb66 && *(unsigned char *)(other + 0x20) != 0xfe && *(unsigned char *)(other + 0x20) != 0xfd) {
                func_00282CF0(&work.separation, (object + 0x10), other + 0x10);
                work.separation.f[2] = 0;
                distance = func_00282DF0(&work.separation);
                if (distance < 1.8f) {
                    func_00282D30(&work.separation, &work.separation, (1.8f - distance) * 0.39999998f);
                    func_00282CC0((object + 0x10), (object + 0x10), &work.separation);
                }
            }
        }
        if (func_00282978((unsigned char *)state + 0x18))
            *(unsigned char *)(object + 0x20) = 2;
        *(float *)(object + 0xf0) = func_002ABB18(state->velocity.f[0]);
        *(float *)(object + 0xf4) = func_002ABB18(state->velocity.f[1]);
        *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
        *(int *)(state->owner + 0x98) = *(int *)(*(char **)(state->owner + 0x24) + 0x10);
        state->velocity.f[2] -= 0.00392f;
        *(float *)(object + 0xf0) += 0.012f;
        *(float *)(object + 0xf4) += 0.024f;
        break;
    case 1:
        *(float *)(object + 0x18) = func_002A89A8(object + 0x10, 0, 0.5f) + 0.2f;
        *(int *)(object + 0x1c) = 0;
        work.probe.whole = ((Vector *)(object + 0x10))->whole;
        state->successor = func_L04_003EDD40(state->owner, &work.probe);
        *(unsigned char *)(object + 0x20) = 2;
        break;
    case 2: {
        char *successor;
        *(float *)(object + 0x2c) -= *(float *)(object + 0x2c) * 0.060000002f;
        successor = state->successor;
        if (successor != 0 && state->handoff != 0)
            *(float *)(successor + 0x2c) += (*(float *)(*(char **)(successor + 0x24) + 0x24) - *(float *)(successor + 0x2c)) * 0.060000002f;
        if (*(float *)(object + 0x2c) < *(float *)(*(char **)(object + 0x24) + 0x24) * 0.060000002f) {
            *(float *)(object + 0x2c) = 0.0001f;
            successor = state->successor;
            if (successor == 0 || *(unsigned char *)(successor + 0x20) == 0xfe || *(unsigned char *)(successor + 0x20) == 0xfd || state->handoff == 0 || *(float *)(successor + 0x2c) >= *(float *)(*(char **)(successor + 0x24) + 0x24) - 0.01f)
                func_L06_0041CAB0(object, (char *)state);
        }
        break;
    }
    }
    func_002A9288(object, (*(float *)(object + 0x2c) * 0.3f) / *(float *)(*(char **)(object + 0x24) + 0x24));
    if (*(float *)(object + 0x18) < 5.0f || *(float *)(object + 0x18) > 500.0f) {
        func_L06_0041CAB0(object, (char *)state);
    } else {
        if (*(float *)(object + 0x10) < 5.0f) *(float *)(object + 0x10) = 5.0f;
        if (*(float *)(object + 0x10) > 1018.0f) *(float *)(object + 0x10) = 1018.0f;
        if (*(float *)(object + 0x14) < 5.0f) *(float *)(object + 0x14) = 5.0f;
        if (*(float *)(object + 0x14) > 1018.0f) *(float *)(object + 0x14) = 1018.0f;
        if (*(float *)(object + 0x18) < 5.0f) *(float *)(object + 0x18) = 5.0f;
        if (*(float *)(object + 0x18) > 1018.0f) *(float *)(object + 0x18) = 1018.0f;
    }
}
