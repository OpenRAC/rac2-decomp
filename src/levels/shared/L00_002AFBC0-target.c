#include "common.h"

typedef struct {
    float pos[4];
    u8 pad10[0x80 - 0x10];
    float origin[4];
    u8 pad90[0x98 - 0x90];
    float yaw;
    u8 pad9C[0x190 - 0x9C];
    float altPos[4];
    float altYaw;
    u8 pad1A4[0xBC0 - 0x1A4];
    float aim[4];
    u8 padBD0[0xBE4 - 0xBD0];
    char *target;
    int active;
    float aimAngle;
    u8 padBF0[0x1248 - 0xBF0];
    int state;
    u8 pad124C[0x24B8 - 0x124C];
    float f24B8;
} HeroTargetState;

extern HeroTargetState D_00189E20_target;
extern void func_L00_002B39F0(int, float);
extern char *func_L00_002AE888(float, float, float, float, float *, int, int);
extern float func_00283248(float, float);
extern void func_00282CF0(float *, char *, float *);
extern void func_L00_002D3B58(float *, float *, float);

/* Unless the hero state is 0x20 or a target is already active, selects the best eligible target from the
 * hero position and yaw (or, when the value at 0x24B8 exceeds 0.5, from the alternate position and yaw after
 * clearing the target and marking it active), then aims: the angle and offset to the chosen target, else the
 * saved yaw and vector. Finally passes the aim vector to a helper. */
void func_L00_002B75A0(float a, float b, float c)
{
    HeroTargetState *p = &D_00189E20_target;
    char *result;
    float yaw;
    float vector[4];

    if (p->state == 0x20 || p->active != 0)
        return;
    yaw = p->yaw;
    qcopy(vector, p->pos);
    if (0.5f < p->f24B8) {
        func_L00_002B39F0(0, 1.0f);
        yaw = p->altYaw;
        qcopy(vector, p->altPos);
        p->target = 0;
        p->active = 1;
    }
    result = func_L00_002AE888(a, yaw, b, c, vector, -1, 0);
    if (result != 0 && (p->target == 0 || p->active != 0)) {
        p->aimAngle = func_00283248(*(float *)(result + 0x10) - p->origin[0],
                                    *(float *)(result + 0x14) - p->origin[1]);
        func_00282CF0(p->aim, result + 0x10, p->origin);
        p->target = result;
    } else {
        D_00189E20_target.aimAngle = yaw;
        qcopy(D_00189E20_target.aim, vector);
    }
    func_L00_002D3B58(D_00189E20_target.aim, D_00189E20_target.aim, 0.0f);
}
