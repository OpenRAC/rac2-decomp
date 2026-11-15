#include "common.h"
typedef struct { float x,y,z,w; } Vec;
typedef struct ProjectileObject ProjectileObject;
typedef struct {
    Vec velocity, initial, previous, next;
    int timer40, field44, effect48;
    short field4c;
    signed char managerIndex, flightEffect;
    int field50;
    char pad54[8];
    int timer5c, field60, field64, field68, slot;
    ProjectileObject *attachment;
    float attachX, attachY, attachZ;
} ProjectileData;
struct ProjectileObject {
    char pad00[0x10]; Vec position;
    unsigned char state;
    char pad21[2]; unsigned char field23;
    char *classData;
    char pad28[0xc]; short flags;
    char pad36[0x12]; float playback;
    char pad4c[0x1c]; ProjectileData *data;
    char pad6c[0x2c]; int collision;
    char pad9c[0xe]; short classId;
    char padac[0x14]; float transform[12];
};
typedef struct { Vec from,to,velocity; ProjectileObject *object; int *filter; int mode; float radius,step,scale; int zero48,zero4c,flag; int surface; int flag58; float epsilon; } Sweep;
extern int D_001AEC0C;
extern float D_001AEC50 __attribute__((sda)), D_001AEC58 __attribute__((sda));
extern ProjectileObject *D_001AD7EC;
extern int D_0018C0B4 NOT_SDA;
extern int D_001B22D0 __attribute__((sda));
extern int D_001B22D8;
typedef struct { int owners[64]; int active[64]; int extra[8]; int count, flag, limit; } ProjectileManager;
extern ProjectileManager ref_00306A40_00;
extern ProjectileObject *ref_00306A40_01[];
typedef struct { float x, y, z; } Position3;
extern Position3 ref_00306A40_02[];
extern void func_002FE8D8(void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern float func_00282DB0(void *,void *);
extern float func_00283198(float),func_00283180(float);
extern void func_00282D30(void *,void *,float);
extern void func_00283958(void *,void *),func_00283738(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_002FEE70(int,void *,int);
extern void func_002FE880(void *,void *,float);
extern void func_00300190(void *,void *);
extern int func_002FE9D0(Sweep *);
extern int func_00300540(int);
extern void func_002FD1B8(int,int,int,float,float,float,float);
extern ProjectileObject *func_00312D58(void *,float);
extern int func_00300280(void *,void *);
extern void func_00307BD0(void);
extern int func_002E5DA0(int,int,void *,int);
extern void func_002A75E0(void *,int,int,int,int);
extern void func_002FEE50(int);
extern void func_00282CF0(void *,void *,void *),func_00283698(void *,void *),func_002830C0(void *,void *,void *);
extern float func_0029F530(void *);
extern void func_00307500(void *),func_003076F0(void *),func_00307808(void *);
extern int func_002FED90(void *,int,float,float,float),func_002FEC78(void *,int);
extern void func_00307298(void *),func_00307330(void *);
extern void func_002AC728(void *,void *,int,float,float);
extern void func_002FED28(int),func_00300300(void *,int),func_0029F338(void *);
extern void func_00283098(void *,void *,void *),func_003079E8(void *),func_002829D8(void *);
extern int func_00282948(void *);
extern void func_003073E0(void *),func_00307440(void *),func_00307BF0(void *);
extern void func_0027CFD0(void (*)(void *),void *);
/* The state machine of an object fired at a surface: flies and sweeps for a hit, sticks or
   bursts on what it hit, then follows what it stuck to until it is destroyed. */
void func_00306A40(ProjectileObject *self)
{
    Vec oldPos;
    int filter[2];
    Vec direction, velocity, quaternion, axis;
    float matrix[12];
    Sweep sweep;
    Vec relative;
    float inverse[16];
    ProjectileData *vars = self->data;
    ProjectileObject *hit;
    float angle;
    int hitResult, slotCounter;

    switch (self->state) {
    case 0:
        self->state = 1;
        slotCounter = D_001AEC0C;
        vars->slot = slotCounter;
        D_001AEC0C = (slotCounter + 1) % 100;
        self->collision = 0;
        /* fall through */
    case 1:
        GetObjectFacingDirection(&self->position, &direction);
        vec_scale_to_length(&velocity, &self->transform[8], 1.0f);
        FastVecCross(&axis, &velocity, &direction);
        angle = FastVecDot(&velocity, &direction) / 2.0f;
        FastVecScale(&quaternion, &axis, FastSinOrCosB(angle));
        quaternion.w = FastSinOrCosA(angle);
        quaternion_to_rotation_basis(&quaternion, matrix);
        multiply_matrix3x3(self->transform, matrix, self->transform);
        qcopy(&oldPos, &self->position);
        FastVecAdd(&self->position, &self->position, vars);
        SteerEffectDirection(vars->flightEffect, vars, 0);
        AddObjectDirectionScaled(&self->position, vars, D_001AEC50 * 0.00027777778f);
        TransformVectorOrCopy(&self->position, &self->position);
        filter[0] = 0;
        filter[1] = 0xc5a;
        qcopy(&sweep.from, &oldPos);
        qcopy(&sweep.to, &self->position);
        qcopy(&sweep.velocity, vars);
        sweep.object = self;
        sweep.filter = filter;
        sweep.mode = 2;
        sweep.radius = 0.13f;
        sweep.step = D_001AEC58;
        sweep.scale = 0.5555556f;
        sweep.zero48 = 0;
        sweep.zero4c = 0;
        sweep.flag = 1;
        sweep.flag58 = 1;
        sweep.epsilon = 0.0962f;
        hitResult = CollideSweptSphere(&sweep);
        qcopy(&self->position, &sweep.to);
        qcopy(vars, &sweep.velocity);
        if (hitResult != 2)
            break;
        hit = sweep.object;
        if (!hit || (hit->classId != 0xcb /* Decoy */ && hit->classId != 0x1366 /* Miniturret */ && hit->classId != 0x1367 /* Megaturret */)) {
            qzero_nc(vars);
            vars->attachment = hit;
            if (hit) {
                vars->attachX = hit->position.x;
                vars->attachY = hit->position.y;
                vars->attachZ = hit->position.z;
            }
            hitResult = GetWeaponGroup(sweep.surface);
            if (hitResult == 2) {
                vars->velocity.z = -0.025000002f;
                self->state = 7;
                if (!sweep.surface) {
                    RippleDisturb(gSurfaceHeightTiles, D_001B22D8, 1, self->position.x, self->position.y, 0.5f, -0.35f);
                    hit = SpawnScaledEffectMoby(&self->position, 2.0f);
                    if (hit)
                        hit->field23 = 0x70;
                }
            } else if (hitResult == 1) {
                self->state = 8;
            } else {
                vars->managerIndex = AddToSlotList(&ref_00306A40_00, self);
                CleanupProjectileTableAlt();
                if (ref_00306A40_00.active[vars->managerIndex]) {
                    self->state = 2;
                    PlaySoundFromClassBank(1, 0, self, 0x1367 /* Megaturret */);
                    StartAnimationBlendedWithFlags(self, 1, 0, 0, 0);
                } else {
                    self->state = 6;
                }
            }
            ClearEntryFlag(vars->flightEffect);
            ref_00306A40_01[vars->slot] = D_001AD7EC;
            if (D_001AD7EC) {
                FastVecSub(&relative, &self->position, &D_001AD7EC->position);
                matrix_from_basis_rows(inverse, ref_00306A40_01[vars->slot]->transform);
                transform_vector(&relative, &relative, inverse);
                {
                    /* Set twice, so alias analysis keeps the row's stores in order with the stack. */
                    int row = vars->slot * 12;

                    row += (int)ref_00306A40_02;
                    ((float *)row)[0] = relative.x;
                    ((float *)row)[1] = relative.y;
                    ((float *)row)[2] = relative.z;
                }
            }
            self->collision = *(int *)(self->classData + 0x10);
        } else {
            FastVecScale(vars, vars, 1.1f);
        }
        break;
    case 2:
        if (GetMobyAnimationValue(self) >= 6.5f) {
            StartAnimationBlendedWithFlags(self, 2, 0, 0, 0);
            self->state = 3;
        }
        break;
    case 3:
        FindMegaturretTarget(self);
        goto attachment;
    case 4:
        AimMegaturretAtTarget(self);
        FireMegaturretShot(self);
    attachment: {
        ProjectileObject *attached = vars->attachment;

        if (attached) {
            if (attached->state == 254)
                goto detached;
            if (attached->state != 253)
                break;
        detached:
            self->collision = 0;
            vars->flightEffect = AllocEffectSlot_002FED90(self, 0, 1.0f, 1.0f, 1.0f);
            self->state = 1;
            vars->attachment = 0;
        }
    }
        break;
    case 5:
        if (GetMobyAnimationValue(self) <= 1.0f) {
            StartAnimationBlendedWithFlags(self, 0, 0, 0, 0);
            self->playback = 1.0f;
            self->state = 6;
        }
        break;
    case 6:
        if (ref_00306A40_00.active[vars->managerIndex]) {
            self->state = 2;
            PlaySoundFromClassBank(1, 0, self, 0x1367 /* Megaturret */);
            StartAnimationBlendedWithFlags(self, 1, 0, 0, 0);
            vars->effect48 = AllocateSlotForObject(self, 0);
        }
        break;
    case 7:
        UpdateMegaturretFall(self);
        ApplyRandomPushToProjectileAlt(self);
        break;
    case 8:
        PlaySoundFromClassBank(3, 0, self, 0x1367 /* Megaturret */);
        SpawnExplosionWithSparks(self, &self->position, -1, 0.5f, 13.0f);
        self->state = 9;
        self->flags |= 0x41;
        break;
    case 9: {
        int invalid = -1;

        if (vars->effect48 != invalid)
            FreeSlot(vars->effect48);
        if (vars->managerIndex != invalid)
            RemoveFromSlotList(&ref_00306A40_00, vars->managerIndex);
        MarkMobySpawned(self);
        return;
    }
    }
    if (self->state >= 2 && ref_00306A40_01[vars->slot]) {
        /* Set twice, as above. */
        int row = vars->slot * 12;

        row += (int)ref_00306A40_02;
        direction.x = ((float *)row)[0];
        direction.y = ((float *)row)[1];
        direction.z = ((float *)row)[2];
        direction.w = 0;
        matrix_mul_vec3(&direction, &direction, ref_00306A40_01[vars->slot]->transform);
        FastVecAdd(&self->position, &ref_00306A40_01[vars->slot]->position, &direction);
    }
    if (self->state == 3 || self->state == 4)
        AdvanceGrowEffectAlt(self);
    FastVectorHelperB(&vars->timer5c);
    if (FastFloatHelperD(&vars->timer40) || D_0018C0B4 == 0x6f)
        if (self->state != 9)
            self->state = 8;
    if (self->state == 3 || self->state == 4) {
        CheckProjectileHitBreakAlt(self);
        if (!ref_00306A40_00.active[vars->managerIndex]) {
            StartAnimationBlendedWithFlags(self, 1, 11, 0, 0);
            self->state = 5;
            self->playback = -1.0f;
            FreeSlot(vars->effect48);
            vars->effect48 = -1;
            vars->field4c = 1;
            vars->field50 = 0;
            vars->field44 = 0;
            vars->field64 = 0;
            qcopy(&vars->next, &vars->initial);
            qcopy(&vars->previous, &vars->initial);
        }
    }
    if (self->state < 8 && vars->attachment)
        FollowAttachedMobyMotionAlt(self);
    RegisterOverlayDrawCallback(DrawProjectileEffectsAlt, self);
}
