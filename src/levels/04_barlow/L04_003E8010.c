#include "common.h"

typedef unsigned int Quad8010 __attribute__((mode(TI)));

typedef struct {
    char pad[0x18];
    float z;
    char pad1c[4];
    u8 state;
    char pad21[15];
    u8 alpha;
    char pad31;
    u16 flags;
    char pad34[0x14];
    float speed;
    char pad4c[0x49];
    s8 sound;
    u16 timer;
    char pad98[0x60];
    float angle;
} Object8010;

typedef struct {
    int ids[4];
    int direction;
    float initialHeight;
    float stopFrame;
    int timer;
    int duration;
    int selected;
    int sound;
    float turnSpeed;
    float targetAngle;
} Private8010;

extern char *D_L04_001B24DC __attribute__((sda));
extern char D_L04_001AFFE0[];
extern unsigned char D_00188660[];
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_0029F530(void *);
extern float func_00283198(float);
extern float func_00283CE0(int);
/* Integer and FP parameters retain their order within each EE argument bank. */
extern void func_002AAA00(void *, float, void *, float, float, float, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002833F0(void *, void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern void func_0026FEB8(void *);

/* Turns a ring of four linked objects a quarter turn at a time, pausing between turns and playing a sound while they turn. */
void func_L04_003E8010(char *mobyPtr)
{
    Object8010 *obj = (Object8010 *)mobyPtr;
    Private8010 *vars = *(Private8010 **)(mobyPtr + 0x68);
    unsigned char partPos[16] __attribute__((aligned(16))),
        oldPos[16] __attribute__((aligned(16))),
        delta[16] __attribute__((aligned(16))),
        rot[16] __attribute__((aligned(16)));

    switch (obj->state) {
    case 0: {
        float initialZ = obj->z;

        obj->alpha = 128;
        obj->flags = 128;
        vars->initialHeight = initialZ;
        vars->stopFrame = 30;
        vars->selected = 2;
        vars->sound = -1;
        vars->targetAngle = FastAddRotations(obj->angle, 1.5707964897155762f);
        if (vars->direction)
            vars->targetAngle = fast_subtract_rotations(obj->angle, 1.5707964897155762f);
        StartAnimationBlended(mobyPtr, 1, 0, 0);
        SetMobyState(mobyPtr, 1, -1);
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *part, *partVars;
                part = gMobyPool_L04 + (vars->ids[i] << 8);
                partVars = *(char **)(part + 0x68);
                *(int *)(partVars + 0x5C) |= 1;
                ((Object8010 *)part)->alpha = 128;
                ((Object8010 *)part)->flags = 128;
            }
        }
        if (vars->direction)
            StartAnimationBlended(mobyPtr, 2, 0, 0);
        obj->speed = 1.0f / 3;
        break;
    }
    case 1: {
        char *part;
        float frame;

        frame = GetMobyAnimationValue(mobyPtr);
        part = (char *)gSoundState + vars->sound * 0x70;
        if (*(char **)(part + 0x88) != mobyPtr || !*(u8 *)(part + 0x74))
            vars->sound = PlayMobySound(0, 4, mobyPtr);
        if (!vars->direction)
            ApproachTargetWithDirectionMode(mobyPtr + 0xF8, vars->targetAngle, &vars->turnSpeed,
                         0.0001939255f, 0.0001939255f, 0.06981318444013596f, 0);
        else
            ApproachTargetWithDirectionMode(mobyPtr + 0xF8, vars->targetAngle, &vars->turnSpeed,
                         0.0001939255f, 0.0001939255f, 0.06981318444013596f, 0);
        euler_rotation_basis(mobyPtr + 0xC0, mobyPtr + 0xF0);
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *part, *partVars;
                part = gMobyPool_L04 + (vars->ids[i] << 8);
                partVars = *(char **)(part + 0x68);
                /* oldPos is a separate stack vector; subsequent accesses use part. */
                qcopy_nc(oldPos, part + 0x10);
                TransformMobyJointToWorld(mobyPtr, i, partPos);
                *(Quad8010 *)(part + 0x10) = *(Quad8010 *)partPos;
                *(Quad8010 *)rot = *(Quad8010 *)(part + 0xF0);
                if (vars->direction)
                    *(float *)(part + 0xF8) = FastAddRotations(obj->angle, 0.00872664712369442f);
                FastVecSub(delta, part + 0x10, oldPos);
                if (vars->selected == i && vars->direction)
                    CombineTransformsAndStore(partVars + 0x20, delta, rot, part + 0xF0);
                else
                    CombineTransformsAndStore(partVars + 0x20, delta, rot, rot);
            }
        }
        if (frame == vars->stopFrame) {
            vars->timer = vars->duration;
            obj->speed = 0;
            vars->stopFrame += 30;
            if (vars->stopFrame >= 120)
                vars->stopFrame = 0;
            SetMobyState(mobyPtr, 2, -1);
            vars->turnSpeed = 0;
        }
        break;
    }
    case 2: {
        {
            int i = vars->sound;
            char *part;

            if (i != -1) {
                part = (char *)gSoundState + i * 0x70;
                if (*(char **)(part + 0x88) == mobyPtr && *(u8 *)(part + 0x74))
                    StopSoundVoice(i);
            }
            vars->sound = -1;
        }
        if (FastFloatHelperD(&vars->timer)) {
            if (++vars->selected >= 4) {
                STUB_printf(D_L04_001AFFE0);
                vars->selected = 0;
            }
            vars->targetAngle = FastAddRotations(obj->angle, 1.5707964897155762f);
            if (vars->direction)
                vars->targetAngle = fast_subtract_rotations(obj->angle, 1.5707964897155762f);
            SetMobyState(mobyPtr, 1, -1);
            obj->z = vars->initialHeight;
            obj->speed = 1.0f / 3;
        } else if (vars->timer < 25) {
            obj->z = vars->initialHeight;
            obj->z += -FastSinOrCosB(IntToFloat(vars->timer) * 0.1256636083126068f) * 0.25f;
        }
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *part, *partVars;
                part = gMobyPool_L04 + (vars->ids[i] << 8);
                partVars = *(char **)(part + 0x68);
                qcopy_nc(oldPos, part + 0x10);
                TransformMobyJointToWorld(mobyPtr, i, partPos);
                *(Quad8010 *)(part + 0x10) = *(Quad8010 *)partPos;
                FastVecSub(delta, part + 0x10, oldPos);
                CombineTransformsAndStore(partVars + 0x20, delta, part + 0xF0, part + 0xF0);
            }
        }
        break;
    }
    }
    if (obj->timer <= 0xFFFE)
        ++obj->timer;
}
