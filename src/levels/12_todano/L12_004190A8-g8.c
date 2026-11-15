/* Path driver with child coordination, sound phases and pose oscillation. */
#include "common.h"

typedef struct {
    u8 pad[0x50];
    s32 path0, path1, path2, trigger, child;
    u8 pad64[12];
    f32 position[4], rotation[4];
    f32 length, phase0, phase1, phase2;
    f32 progress, velocity;
    s32 timer, sound, soundTimer;
} DriverState;
typedef struct DriverObject DriverObject;
struct DriverObject {
    u8 pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[0xF];
    u8 f30;
    u8 pad31;
    u16 f32;
    u8 pad34[0xE];
    u8 animation, nextAnimation;
    u8 pad44[0x24];
    DriverState *vars;
    u8 pad6C[0x84];
    float rotation[4];
};
/* Partial sound anchor: indices advance by 0x70, independently of this view. */
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad75[9];
    s16 kind;
    u8 pad80[8];
    DriverObject *owner;
} DriverSound;
extern u8 D_00188660[];
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern u8 *D_L12_001FEAC0[];
extern float D_L12_001B1C00[2] __attribute__((sda));
extern float D_L12_001B1C10[2] __attribute__((sda));
extern float D_L12_001B1C24 __attribute__((sda));
extern float D_L12_001B1C28 __attribute__((sda));
extern float D_L12_001B1C2C __attribute__((sda));
extern float D_L12_001B1C30 __attribute__((sda));
extern float D_L12_001B1C34 __attribute__((sda));
extern float D_L12_001B1C38 __attribute__((sda));
extern float D_L12_001B1C3C __attribute__((sda));
extern float D_L12_001B1C40 __attribute__((sda));
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,void *,int);
extern float func_002A7940(void);
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern int func_002E5CF8(int,int,void *);
extern float func_00282E48(void *,void *);
extern int func_00282948(int *);
extern float func_002AA548(float *,float *,float,float,float,float);
extern void func_002C9828(void *,int,void *,void *,int,float);
extern void func_L12_00418D20(void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A89A8(float,void *,int);
extern int func_L12_003E0858(int,void *,void *);
extern int func_L12_003E09C8(int);
extern void func_L12_0041A5F8(void *);
extern int func_L03_003CA138(void *);
extern int func_L12_0041A698(void *);
extern u8 *func_002A9640(void *,int,int);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_002A6C58(void *,int,int);
extern void func_0029F338(void *);
extern float func_00283B98(float,float);
extern float func_00283198(float);

#define SOUND_ENTRY(index) ((DriverSound *)((s32)D_00188660 + (index) * 0x70))
#define SOUND_LIVE(index) (SOUND_ENTRY(index)->owner == self && SOUND_ENTRY(index)->active)
static __inline__ void driver_clear_sound(DriverObject *self, DriverState *state)
{
    int slot = state->sound;
    if (slot != -1) {
        DriverSound *entry = SOUND_ENTRY(slot);
        if (entry->owner == self && entry->active) StopSoundVoice(slot);
    }
    state->sound = -1;
}
#define CLEAR_SOUND() driver_clear_sound(self, state)

void func_L12_004190A8(DriverObject *self)
{
    DriverState *state = self->vars;
    u8 *path;
    float sightStart[4] __attribute__((aligned(16)));
    float sightEnd[4] __attribute__((aligned(16)));
    u8 *hit;
    int accepted;
    switch (self->state) {
    case 0: {
        u8 *initialPath;
        state->sound = -1;
        if (state->path0 == -1 && state->path2 == -1 && state->path1 != 0 &&
            state->trigger == -1 && state->child == -1) {
            SetMobyState(self,7,-1);
            break;
        }
        initialPath = D_L12_001FEAC0[state->path0];
        state->length = fast_vec_dist(initialPath+0x10,initialPath+0x20);
        SetMobyState(self,3,-1);
        self->f30 = 0xff;
        self->f32 = 0xff;
        qcopy(state->position,self->position);
        qcopy(state->rotation,self->rotation);
        state->phase0 = RandomAngle();
        state->phase1 = RandomAngle();
        state->phase2 = RandomAngle();
        SetMobyState(self,1,-1);
        break;
    }
    case 1:
        if (SetFirstPendingFlag(self)) CLEAR_SOUND();
        if (IsMobyInState1_L03(D_L12_001B2E9C + (state->child << 8)))
            SetMobyState(self,2,-1);
        break;
    case 2:
        if (SetFirstPendingFlag(self)) CLEAR_SOUND();
        path = D_L12_001FEAC0[state->path0];
        StepValueTowardTarget(&state->progress,&state->velocity,(float)(*(int *)path-1),
                     0.013888889f,0.0013888889225199819f,0.33333334f);
        SamplePathPosition(path,0,state->position,state->rotation,0,state->progress);
        SpawnDriverSparkBursts(self);
        state->rotation[1] *= -0.333f;
        if (!SOUND_LIVE(state->sound))
            state->sound = PlayMobySound(0,4,self);
        if (state->progress >= (float)(*(int *)path-1)) {
            SetMobyState(self,3,-1);
            state->timer = 60;
            if (self->nextAnimation != 1) StartAnimationBlended(self,1,0,30);
            CLEAR_SOUND();
            state->sound = PlayMobySound(1,0,self);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(self)) CLEAR_SOUND();
        if (FastFloatHelperD(&state->timer)) {
            matrix_mul_vec3(sightStart,D_L12_001B1C00,(u8 *)self+0xC0);
            FastVecAdd(sightStart,sightStart,self->position);
            matrix_mul_vec3(sightEnd,D_L12_001B1C10,(u8 *)self+0xC0);
            FastVecAdd(sightEnd,sightEnd,self->position);
            sightEnd[2] += 2.0f;
            sightEnd[2] = ProbeGroundHeightBelow(0.5f,sightEnd,0);
            if (!LaunchSpaceTourist(state->trigger,sightStart,sightEnd)) {
                ResetObjectToSavedPosition(D_L12_001B2E9C + (state->child << 8));
                SetMobyState(self,4,-1);
                if (self->nextAnimation != 0) StartAnimationBlended(self,0,0,30);
                CLEAR_SOUND();
                state->sound = PlayMobySound(2,0,self);
                state->soundTimer = 15;
                state->progress = 0;
                state->velocity = 0;
            } else state->timer = 45;
        } else if (state->timer >= 46) {
            if (state->sound == -1 || !SOUND_LIVE(state->sound) ||
                SOUND_ENTRY(state->sound)->kind != 1)
                state->sound = PlayMobySound(1,0,self);
        }
        break;
    case 4:
        if (SetFirstPendingFlag(self)) CLEAR_SOUND();
        path = D_L12_001FEAC0[state->path1];
        StepValueTowardTarget(&state->progress,&state->velocity,(float)(*(int *)path-1),
                     0.0013888889225199819f,0.0013888889225199819f,0.33333334f);
        SamplePathPosition(path,0,state->position,state->rotation,0,state->progress);
        SpawnDriverSparkBursts(self);
        state->rotation[1] *= -0.333f;
        if (!FastFloatHelperD(&state->soundTimer)) {
            if (state->sound == -1 || !SOUND_LIVE(state->sound))
                state->sound = PlayMobySound(2,0,self);
        }
        if (state->progress >= (float)(*(int *)path-1)) {
            SetMobyState(self,5,-1);
            state->progress = 0;
        }
        break;
    case 5:
        if (SetFirstPendingFlag(self)) CLEAR_SOUND();
        if (self->nextAnimation == 0 &&
            IsAtLastPathPoint(D_L12_001B2E9C_gp + (state->child << 8))) {
            if (self->nextAnimation != 1) StartAnimationBlended(self,1,0,30);
            state->soundTimer = 15;
            CLEAR_SOUND();
            state->sound = PlayMobySound(1,0,self);
        } else if (AreAllSpaceTouristsIdle(state->trigger)) {
            SetMobyState(self,6,-1);
            if (self->nextAnimation != 0) StartAnimationBlended(self,0,0,30);
            CLEAR_SOUND();
            if (!SOUND_LIVE(state->sound))
                state->sound = PlayMobySound(2,4,self);
        } else if (self->animation == 1 && !FastFloatHelperD(&state->soundTimer)) {
            if (state->sound == -1 || !SOUND_LIVE(state->sound) ||
                SOUND_ENTRY(state->sound)->kind != 1)
                state->sound = PlayMobySound(1,0,self);
        }
        break;
    case 6:
        if (SetFirstPendingFlag(self)) CLEAR_SOUND();
        path = D_L12_001FEAC0[state->path2];
        StepValueTowardTarget(&state->progress,&state->velocity,(float)(*(int *)path-1),
                     D_L12_001B1C3C*0.00027777778f,
                     D_L12_001B1C3C*0.00027777778f,
                     D_L12_001B1C40*0.016666668f);
        SamplePathPosition(path,0,state->position,state->rotation,0,state->progress);
        SpawnDriverSparkBursts(self);
        state->rotation[1] *= -0.333f;
        if (!SOUND_LIVE(state->sound)) state->sound = PlayMobySound(0,4,self);
        if (state->progress >= (float)(*(int *)path-1)) {
            SetMobyState(self,1,-1);
            state->progress = 0;
        }
        break;
    case 7:
        if (SetFirstPendingFlag(self)) CLEAR_SOUND();
        hit = FindOwnedEffectSlot(self,0x10000,0);
        if (hit) {
            u8 *owner = *(u8 **)(hit+0x20);
            accepted = 0;
            if (owner && (*(s16 *)(owner+0xAA) == 0xB69 /* Protopet */ || *(s16 *)(owner+0xAA) == 0xF9E /* moby class 3998 */))
                accepted = 1;
            if (!accepted) {
                SpawnExplosionEffects(self,self->position,0,0,0,10,3,9,4,2,9,0,-1,15,1,1,-1,0,0x810001);
                SetDeathBits(self,0,3);
                MarkMobySpawned(self);
                return;
            }
        }
        break;
    }
    if (self->state != 7) {
        qcopy(self->position,state->position);
        qcopy(self->rotation,state->rotation);
        state->phase0 = FastAddRotations(state->phase0,D_L12_001B1C38*0.00029088825f);
        self->rotation[0] = FastAddRotations(D_L12_001B1C34*(FastSinOrCosB(state->phase0)*0.017453294f),state->rotation[0]);
        state->phase1 = FastAddRotations(state->phase1,D_L12_001B1C30*0.00029088825f);
        self->rotation[1] = FastAddRotations(D_L12_001B1C2C*(FastSinOrCosB(state->phase1)*0.017453294f),state->rotation[1]);
        state->phase2 = FastAddRotations(state->phase2,D_L12_001B1C28*0.00029088825f);
        self->position[2] += D_L12_001B1C24*FastSinOrCosB(state->phase2);
    }
}
