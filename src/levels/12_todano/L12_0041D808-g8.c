#include "common.h"

#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))

typedef struct {
    u8 pad[0x60];
    s32 node;
    s32 destination;
    f32 angularSpeed;
    f32 speed;
    f32 origin[4];
    s32 sound;
    f32 targetHeight;
    f32 targetAngle;
    s32 timer;
} LiftVars;

extern u8 *D_L12_001B2F8C MACRO_ADDR;

typedef struct {
    u8 pad0[0x80];
    f32 position[4];
    u8 pad90[0x33C - 0x90];
    u8 *lift;
    s32 active;
} LiftHero;

extern LiftHero D_00189E20;

typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad75[0x13];
    u8 *owner;
} LiftSound;

extern u8 D_00188660[];
extern u8 *D_0018C0B0 NOT_SDA;
extern s32 D_00138324 NOT_SDA;

extern f32 func_00283B98(f32, f32);
extern f32 func_00282C48(f32);
extern f32 func_00282E80(void *, void *);
extern void func_002A7750(void *, s32, s32);
extern s32 func_002B0C28(s32, s32, s32);
extern s32 func_002B3868(void *);
extern s32 func_L00_002D40F0(void);
extern s32 func_002ACBC8(void *, s32);
extern void func_L00_002D40A0(void *, s32, f32);
extern void func_L01_002C98B8(void);
extern void func_002E59F8(s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern f32 func_002AA548(void *, void *, f32, f32, f32, f32);
/* The final integer argument still occupies $a2 in the EE ABI. */
extern f32 func_002AAA00(void *, void *, f32, f32, f32, f32, s32);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Moves a lift up and down while turning it, when the hero stands on it and asks, or walks up to it. */
void func_L12_0041D808(u8 *self)
{
    f32 oldpos[4] __attribute__((aligned(16)));
    f32 oldrot[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    LiftVars *vars = *(LiftVars **)(self + 0x68);
    f32 target, speed, y;

    qcopy(oldpos, self + 0x10);
    qcopy(oldrot, self + 0xF0);
    switch (self[0x20]) {
    case 0:
        F(self, 0xF8) = FastAddRotations(F(self, 0xF8), 1.5707964897155762f);
        qcopy_nc(vars->origin, self + 0x10);
        vars->origin[3] = F(self, 0xF8);
        SetMobyState(self, 2, -1);
        break;
    case 2:
        vars->targetHeight = vars->destination ?
            F((u8 *)(vars->node * 128 + (u32)D_L12_001B2F8C), 0x38) : vars->origin[2];
        vars->targetAngle = vars->destination ?
            FastAddRotations(F((u8 *)(vars->node * 128 + (u32)D_L12_001B2F8C), 0x78),
                          4.7123894691467285f) : vars->origin[3];
        y = F((u8 *)(vars->node * 128 + (u32)D_L12_001B2F8C), 0x38);
        if (gHeroState.lift == self && gHeroState.active) {
            TryClaimNotice(8, 0x279A, 1);
            if (D_00138324 & 16) {
                vars->destination = (vars->destination + 1) & 1;
                SetMobyState(self, 3, -1);
            }
        } else if (vars->destination) {
            if (FloatAbs(gHeroState.position[2] - vars->origin[2]) < 4.0f &&
                vec_distance_xy(gHeroState.position, self + 0x10) < 32.0f) {
                vars->destination = 0;
                SetMobyState(self, 1, -1);
            }
        } else if (FloatAbs(gHeroState.position[2] - y) < 4.0f &&
                   vec_distance_xy(gHeroState.position, self + 0x10) < 32.0f) {
            vars->destination = 1;
            SetMobyState(self, 1, -1);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(self)) {
            StartHeroTargetState(self + 0x10, 0, F(gHeroMoby_0018C0B0, 0xF8));
            vars->timer = 0;
        }
        if (++vars->timer >= 361) {
            SetHeroMoveStateBySpeed();
            SetMobyState(self, 2, -1);
        } else if (GetHeroTargetStateKind() != 1) {
            SetMobyState(self, 1, -1);
        }
        break;
    case 1:
        if (SetFirstPendingFlag(self)) {
            vars->angularSpeed = 0;
            vars->speed = 0;
        }
        vars->targetHeight = vars->destination ?
            F((u8 *)(vars->node * 128 + (u32)D_L12_001B2F8C), 0x38) : vars->origin[2];
        vars->targetAngle = vars->destination ?
            FastAddRotations(F((u8 *)(vars->node * 128 + (u32)D_L12_001B2F8C), 0x78),
                          4.7123894691467285f) : vars->origin[3];
        target = vars->targetHeight;
        speed = 0.003888889f;
        if (vars->destination) {
            if (gHeroState.position[2] < F(self, 0x18) - 1.0f &&
                IsPointInCuboid(gHeroState.position, vars->node)) {
                target += 3.0f;
                speed = 0.007777778f;
            } else {
                target += 0.5f;
            }
        }
        StepValueTowardTarget(self + 0x18, &vars->speed, target, 0.0019444445f, speed, 0.5f);
        if (FloatAbs(vars->targetHeight - F(self, 0x18)) < 0.6f &&
            FloatAbs(vars->speed) < 0.01f) {
            {
                s32 index = vars->sound;

                if (index != -1) {
                    LiftSound *entry = (LiftSound *)(index * 0x70 + (s32)gSoundState);

                    if (entry->owner == self && entry->active)
                        StopSoundVoice(index);
                }
            }
            vars->sound = -1;
            SetMobyState(self, 2, -1);
        } else {
            LiftSound *entry = (LiftSound *)(vars->sound * 0x70 + (s32)gSoundState);

            if (entry->owner != self || !entry->active)
                vars->sound = PlayMobySound(0, 4, self);
        }
        ApproachTargetWithDirectionMode(self + 0xF8, &vars->angularSpeed, vars->targetAngle,
                      0.00014544412260875106f, 0.00014544412260875106f, 0.10471977f, 0);
        break;
    }
    FastVecSub(delta, self + 0x10, oldpos);
    CombineTransformsAndStore((u8 *)vars + 0x20, delta, oldrot, self + 0xF0);
}
