#include "common.h"

typedef struct {
    float direction[4];
    void *attacker;
    int flags;
    u8 kind, mode;
    u16 object_class;
    float damage;
    int enabled;
    /* QueueMobyImpact reads this word; this retail caller does not initialize it. */
    float field24;
} Impact;
typedef char ImpactExtentCheck[sizeof(Impact) == 0x28 ? 1 : -1];
extern unsigned char *D_L05_001FB5E0[];
extern float D_L05_001B1578 SDATA(D_L05_001B1578);
extern void func_00282F20(void *, void *, float);
extern void func_002A8E20(void *, Impact *);
extern void *func_L05_00427FC8(void *, void *, int, int, int, int, int, int,
                            int, int, int, int, int, float);
extern void func_00277F48(void *, int, int, void *, float);

void func_L05_00427E10(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    int i;
    unsigned char *target;
    Impact impact;
    impact.flags = 0x810000;
    impact.enabled = 1;
    impact.damage = 100.0f;
    impact.attacker = object;
    qcopy(impact.direction, state);
    vec_scale_to_length(impact.direction, impact.direction, 1.0f);
    impact.direction[3] = 5627.9248046875f;
    impact.kind = 3;
    impact.mode = 2;
    impact.object_class = *(u16 *)(object + 0xAA);
    for (i = 0; (target = D_L05_001FB5E0[i]) != 0; i++) {
        if (target[0x31] != 0 && target != 0 && target[0x20] != 0xFE &&
            target[0x20] != 0xFD && *(s16 *)(target + 0xAA) != 0xCBE &&
            *(s16 *)(target + 0xAA) != 0x110A)
            QueueMobyImpact(target, &impact);
    }
    func_L05_00427FC8(object + 0x10, object, 0, 50, 30, 30, 30, 40,
                      1, 1, 1, 1, 67, 4.0f);
    func_00277F48(object + 0x10, 1, *(int *)(state + 0x20), &impact, D_L05_001B1578);
}
