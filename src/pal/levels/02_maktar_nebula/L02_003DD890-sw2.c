#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union {
    struct { float origin[4]; float difference[4]; } aim;
    struct { float angles[4]; float original[4]; } rotation;
} JointScratch;
typedef struct {
    char pad0[0x10];
    float position[4];
    unsigned char state;
    char pad21[0x21];
    unsigned char animation;
    unsigned char nextAnimation;
    char pad44[0x1C];
    unsigned char flags;
    char pad61[7];
    struct TurretState *vars;
    char pad6C[0x50];
    unsigned char emitted;
    char padBD[3];
    float matrix[12];
    float rotation[4];
} TurretObject;
typedef struct TurretState {
    char pad0[0x20];
    float elapsed;
    short duration;
    char pad26[0xE];
    unsigned char damage;
    char pad35[0x14B];
    float leftJoint[16];
    float rightJoint[16];
    char pad200[0x40];
    char *target;
    int proxyIndex;
    float yaw;
    float yawSpeed;
    unsigned int colour;
    unsigned int oldColour;
    unsigned int targetColour;
    float colourFraction;
    char pad260[0x26];
    short fireTimer;
} TurretState;
extern TurretObject *D_L02_001B359C __attribute__((sda));
extern int D_L02_001B30C8 __attribute__((sda));
extern float D_L02_001A8F20[4] __attribute__((sda));
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern void func_0029FC20(char *, int, char *);
extern void func_PAL_002A0F68(char *);
extern void func_002A0F48(char *);
extern void func_002A10E8(char *);
extern unsigned int func_L00_0031C998(unsigned int, unsigned int, float);
extern float func_00283198(float);
extern float func_002AAA00(float *, float *, int, float, float, float, float);
extern void func_002833F0(void *, void *);
extern void func_002AB6D8(float *, float *);
extern void func_0029FCC0(char *, int, char *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283BE0(float, float);
extern float func_00283C28(float);
extern void func_002A91F0(void *, float *);
extern float func_L02_00321C30(void *, void *, float);
extern int func_00282978(short *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern int func_00283CF0(float);
extern float func_0029F530(char *);
extern void func_00282F20(void *, void *, float);
extern unsigned char *func_PAL_L02_00426700(unsigned char *, int, unsigned char *, float);
#define OBJ (D_L02_001B359C[self->vars->proxyIndex])
#define PROXY ((unsigned char *)&OBJ)

/* Update the attached object's colour, aim joints and muzzle emissions. */
void func_PAL_L02_003DDFD0(TurretObject *self)
{
    float target[4];
    float ownerMatrix[16];
    JointScratch work;
    float angles[4];
    float orientation[4];
    float firstMuzzle[16];
    float secondMuzzle[16];
    TurretState *state = self->vars;
    TurretObject *object;
    float distance, yaw, difference, fraction, limit, phase;
    unsigned int colour;
    int mode;

    *(Quadword *)target = 0;
    {
        char *targetObject = state->target;
        if (targetObject) qcopy(target, targetObject + 0x10);
    }
    distance = func_00282E80(self->position, target);
    yaw = func_00283248(target[0] - self->position[0], target[1] - self->position[1]);
    difference = func_00283C80(*(float *)(PROXY + 0xF8), yaw);
    func_0029FC20((char *)self, 0, (char *)ownerMatrix);
    qcopy_nc(PROXY + 0x10, ownerMatrix + 12);
    func_PAL_002A0F68((char *)PROXY);
    func_002A0F48((char *)PROXY);
    func_002A10E8((char *)PROXY);
    if ((state->colour & 0xFFFFFF) != (state->targetColour & 0xFFFFFF)) {
        state->colour = func_L00_0031C998(state->oldColour,
                state->targetColour, state->colourFraction);
        state->colourFraction += 0.1f;
        if (state->colourFraction > 1.0f) state->colourFraction = 1.0f;
    } else {
        state->oldColour = state->targetColour;
        state->colourFraction = 0;
    }
    phase = func_00283198((float)(D_L02_001B30C8 % 120) * 0.052359883f - 3.1415927f);
    colour = (state->colour & 0xFFFFFF)
            | ((int)(phase * phase * (float)*((unsigned char *)&state->targetColour + 3)) << 24);
    state->colour = colour;
    *(unsigned int *)(PROXY + 0x78) = colour;
    if (self->state != 9 && self->state != 10 && self->state != 11 && self->state != 7) {
        fraction = state->elapsed / (float)state->duration;
        limit = (fraction * -330.0f + 360.0f) * 6.981318e-06f;
        func_002AAA00(&state->yaw, &state->yawSpeed, 0,
                yaw, limit, limit, (fraction * -225.0f + 240.0f) * 0.0003490659f);
        *(Quadword *)work.rotation.original = 0;
        work.rotation.original[2] = state->yaw;
        *(Quadword *)work.rotation.angles = *(Quadword *)work.rotation.original;
        func_002833F0(PROXY + 0xC0, &work);
        object = (TurretObject *)PROXY;
        func_002AB6D8(object->matrix, object->rotation);
    }
    mode = self->state;
    if (mode == 5 || (mode == 6 && state->elapsed < (float)state->duration * 0.2f)) {
        func_0029FCC0((char *)PROXY, 2, (char *)work.aim.origin);
        func_00282CF0(work.aim.difference, state->target + 0x10, work.aim.origin);
        limit = func_00282E80(state->target + 0x10, work.aim.origin);
        *(Quadword *)angles = 0;
        angles[1] = func_00283248(work.aim.difference[2], limit) + -1.5707964f;
        if (angles[1] > 1.5707965f) angles[1] = 1.5707965f;
        else if (angles[1] < -1.5707965f) angles[1] = -1.5707965f;
        if (difference < 0.17453295f) {
            angles[2] = func_00283248(work.aim.difference[0], work.aim.difference[1]);
            angles[2] = func_00283BE0(angles[2], *(float *)(PROXY + 0xF8));
            angles[2] = func_00283C28(angles[2]);
        }
        if (!(angles[2] > 0.9599312f)) {
            if (angles[2] < -0.13962635f) angles[2] = -0.13962635f;
        } else angles[2] = 0.9599312f;
        func_002A91F0(orientation, angles);
        func_L02_00321C30(state->leftJoint, orientation, 0.01f);
        func_0029FCC0((char *)PROXY, 3, (char *)work.aim.origin);
        func_00282CF0(work.aim.difference, state->target + 0x10, work.aim.origin);
        limit = func_00282E80(state->target + 0x10, work.aim.origin);
        angles[1] = func_00283248(work.aim.difference[2], limit) + -1.5707964f;
        if (angles[1] > 1.5707965f) angles[1] = 1.5707965f;
        else if (angles[1] < -1.5707965f) angles[1] = -1.5707965f;
        if (difference < 0.17453295f) {
            angles[2] = func_00283248(work.aim.difference[0], work.aim.difference[1]);
            angles[2] = func_00283BE0(angles[2], *(float *)(PROXY + 0xF8));
            angles[2] = func_00283C28(angles[2]);
        }
        if (!(angles[2] > 0.13962635f)) {
            if (angles[2] < -0.9599312f) angles[2] = -0.9599312f;
        } else angles[2] = 0.13962635f;
        func_002A91F0(orientation, angles);
        func_L02_00321C30(state->rightJoint, orientation, 0.01f);
        if (func_00282978(&state->fireTimer) && distance < 45.0f
                && distance > 0.0f && difference < 3.141593f) {
            if (OBJ.nextAnimation != 5) func_PAL_002A7E68((char *)&OBJ, 5, 0, 2);
            PROXY[0xBC] = 0;
            if (self->state == 5)
                state->fireTimer = ((s32)(func_00283CF0((state->elapsed / (float)state->duration) * 40.0f + 20.0f)) * 5 + 2) / 6;
            else state->fireTimer = 50;
        }
    } else {
        func_L02_00321C30(state->leftJoint, D_L02_001A8F20, 0.01f);
        func_L02_00321C30(state->rightJoint, D_L02_001A8F20, 0.01f);
    }
    switch (PROXY[0x42]) {
    case 0:
        state->targetColour = 0x40FF00EA;
        if (self->state != 5 || !(distance > 45.0f) || !(distance < 0.0f) || !(difference > 3.141593f)) return;
        if (OBJ.nextAnimation != 1) func_PAL_002A7E68((char *)&OBJ, 1, 0, 8);
        return;
    case 1: case 2: case 3: case 4:
        if (!(distance < 45.0f) || !(distance > 0.0f) || !(difference < 3.141593f)) return;
        if (OBJ.nextAnimation) func_PAL_002A7E68((char *)&OBJ, 0, 0, 8);
        return;
    case 5:
        state->targetColour = 0x80FF00EA;
        phase = func_0029F530((char *)PROXY);
        if (!OBJ.emitted && phase > 3.0f && phase < 6.0f) {
            func_0029FCC0((char *)&OBJ, 0, (char *)work.aim.origin);
            func_0029FC20((char *)PROXY, 0, (char *)firstMuzzle);
            func_00282CF0(angles, state->target + 0x10, work.aim.origin);
            func_00282F20(angles, angles, 1.0f);
            firstMuzzle[2] = angles[2];
            func_00282F20(firstMuzzle, firstMuzzle, 1.0f);
            func_PAL_L02_00426700((unsigned char *)work.aim.origin, (int)self, (unsigned char *)firstMuzzle,
                    (float)state->damage);
            func_0029FCC0((char *)PROXY, 1, (char *)work.aim.difference);
            func_0029FC20((char *)PROXY, 1, (char *)secondMuzzle);
            func_00282CF0(angles, state->target + 0x10, work.aim.difference);
            func_00282F20(angles, angles, 1.0f);
            secondMuzzle[2] = angles[2];
            func_00282F20(secondMuzzle, secondMuzzle, 1.0f);
            func_PAL_L02_00426700((unsigned char *)work.aim.difference, (int)self, (unsigned char *)secondMuzzle,
                    (float)state->damage);
            PROXY[0xBC] = 1;
        }
        if ((OBJ.flags & 2) && OBJ.nextAnimation) func_PAL_002A7E68((char *)&OBJ, 0, 0, 2);
        return;
    case 10:
        state->targetColour = 0x30FF00EA;
        return;
    case 12: case 13:
        state->targetColour = 0xFF000000;
        if (self->state != 11) {
            state->targetColour = 0x8000FFFF;
            state->yaw += state->yawSpeed;
            state->yawSpeed *= 0.97f;
            state->yaw = func_00283C28(state->yaw);
            *(Quadword *)work.rotation.original = 0;
            work.rotation.original[2] = state->yaw;
            *(Quadword *)work.rotation.angles = *(Quadword *)work.rotation.original;
            func_002833F0(PROXY + 0xC0, &work);
            object = (TurretObject *)PROXY;
            func_002AB6D8(object->matrix, object->rotation);
            return;
        }
        /* State 11 falls through and fails the state 7 guard. */
    case 7:
        if (self->state != 7) return;
        state->targetColour = 0x80806060;
        state->yaw += state->yawSpeed;
        state->yawSpeed *= 0.97f;
        state->yaw = func_00283C28(state->yaw);
        *(Quadword *)work.rotation.original = 0;
        work.rotation.original[2] = state->yaw;
        *(Quadword *)work.rotation.angles = *(Quadword *)work.rotation.original;
        func_002833F0(PROXY + 0xC0, &work);
        object = (TurretObject *)PROXY;
        func_002AB6D8(object->matrix, object->rotation);
        return;
    }
}
