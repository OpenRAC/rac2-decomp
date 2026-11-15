#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038F3D8(void *);
extern void func_L00_0038E880(void *, void *, void *);
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L00_001AC850 __attribute__((sda));
extern int D_L00_001B2630 __attribute__((sda)), D_L00_001B2638 __attribute__((sda));
extern Collision D_L00_001BF200;
extern Material D_L00_00262570[];
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_L00_0038F178(void *);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern void func_002FD1B8(int, int, int, float, float, float, float);
extern void func_00282C88(void *);
extern char *func_00312D58(void *, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_002BFB38(void *, void *, int, int);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282948(char *);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);

extern char D_L07_001FDEC0[];
extern void func_338D68();

typedef int DriveVector __attribute__((mode(TI)));
typedef struct PlayerDriveView {
    unsigned char pad0[0x20]; float basis[16];
    unsigned char pad60[0x98 - 0x60]; float rotation;
    unsigned char pad9C[0xF0 - 0x9C]; DriveVector velocity;
    unsigned char pad100[0x160 - 0x100]; DriveVector pendingResult;
    float distance, planarDistance;
    unsigned char pad178[0x190 - 0x178]; DriveVector direction; float heading;
    float yawRate, yawError;
    unsigned char pad1AC[4]; float speed, targetSpeed; int frame;
    unsigned char pad1BC[0x348 - 0x1BC]; short request, contact;
    unsigned char pad34C[0x454 - 0x34C]; float recoverySpeed;
    unsigned char pad458[0x470 - 0x458]; DriveVector localDirection, targetDirection;
    float pad490, acceleration;
    unsigned char pad498[6]; unsigned char allowAction;
    unsigned char pad49F[0x4AE - 0x49F]; short actionFrame;
    unsigned char pad4B0[12]; float lateralSpeed, inputHeading, targetHeading;
    unsigned char pad4C8[12]; int transition; float inputSpeed, strafeSpeed;
    unsigned char pad4E0[16]; DriveVector jumpDirection;
    unsigned char pad500[0x20]; float recoveryRate; short special;
    unsigned char pad526[7]; unsigned char useCurrentSpeed;
    unsigned char pad52E[0xA60 - 0x52E]; DriveVector pending;
    unsigned char padA70[0x14]; float pendingDamping;
    unsigned char padA88[0xC38 - 0xA88]; float plane;
    unsigned char padC3C[0x1440 - 0xC3C]; DriveVector savedDirection;
    unsigned char pad1450[4]; short overrideDirection;
    unsigned char pad1456[2]; float savedHeading;
    unsigned char pad145C[0x2294 - 0x145C]; int state;
    unsigned char pad2298[4]; int mode;
    unsigned char pad22A0[0x22C3 - 0x22A0]; unsigned char axisMode;
    unsigned char pad22C4[0x24B8 - 0x22C4]; float animationSpeed;
} PlayerDriveView;
extern PlayerDriveView D_00189E20;
/* Resident subview at the velocity vector; targetSpeed is 0xC4 bytes later. */
typedef struct DriveVelocityView {
    DriveVector velocity;
    unsigned char pad10[0xC4 - 0x10]; float targetSpeed;
} DriveVelocityView;
extern DriveVelocityView D_00189F10;
extern int D_L07_001A8FF0 MACRO_ADDR;
extern float D_L07_001A7DC0 MACRO_ADDR;
/* The settings prefix ends at the observed direction vector. */
typedef struct DriveSettings {
    unsigned char pad0[0x158]; float heading;
    unsigned char pad15C[0x370 - 0x15C]; DriveVector direction;
} DriveSettings;
extern DriveSettings D_L07_001B90C0;
extern void func_L00_002B54F8(float, float);
extern void func_L00_002B41B8(float, float);
extern void func_L00_002B3EF8(int, float, float, float);
extern void func_L01_002B6948(float);
extern void func_L00_002D3798(DriveVector *, DriveVector *, float);
extern void func_L00_002D3B58(DriveVector *, DriveVector *, float);
extern void func_L00_002D3BD8(void *, const void *, float);
extern float func_L00_002D3A58(char *);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA898(float *, float *, int, float, float, float, float);
extern float func_00283BE0(float, float);
extern void func_L00_002AA0F0(float, float, float);
extern float func_00282DB0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283C80(float, float);
extern void func_00282CC0(void *, void *, void *);


/* Update directional movement, including the state-44 yaw spring.
 * Shares the resident views and locomotion arms with func_L01_002B7360. */
void func_L07_002B5738(void)
{
    union { DriveVector q; float f[4]; } local;
    float smoothed;
    float oldHeading;
    int state = gHeroState.state;

    if (state == 10) {
        BuildHeroMoveImpulse(0.7f, 0.0f);
        qcopy(&gHeroState.pendingResult, &gHeroState.pending);
        gHeroState.targetSpeed = gHeroState.planarDistance;
    } else if (state == 16) {
        float speed;
        PlayerDriveView *hero = &gHeroState;
        if (gHeroState.frame > 54) {
            ApproachValue((float *)(&gHeroState.recoveryRate), 0.0069444445f, 0.0019444445f);
        }
        if (gHeroState.frame <= 54) speed = gHeroState.recoverySpeed;
        else speed = 0.058333337f;
        hero->speed = speed;
        ApproachHeroSpeed(0.012222223f, 0.0125f);
        SetViewSpaceVectorLength(&D_00189F10.velocity, &D_00189F10.velocity, 0.0f);
        OffsetPointBySideDirection((DriveVector *)(&D_00189F10.velocity), (DriveVector *)(&D_00189F10.velocity), D_00189F10.targetSpeed);
    } else if (state == 27) {
        if (gHeroState.frame > 40) {
            SteerHeroHeading(0, 0.04f, 0.2f, 0.250163913f);
            ApproachHeroVelocity_L01(0.0055555557f);
        }
        if (13.0f <= gHeroState.plane && gHeroState.plane <= 30.0f) {
            if (27.0f < gHeroState.plane)
                ApproachValue((float *)(&gHeroState.lateralSpeed), 0.0f, 0.0022222223f);
            else ApproachValue((float *)(&gHeroState.lateralSpeed), 0.033333335f, 0.0022222223f);
        }
        local.f[0] = gHeroState.lateralSpeed;
        local.f[1] = 0.0f;
        local.f[2] = FastVecDot(&gHeroState.velocity, &gHeroState.basis);
        matrix_mul_vec3(&gHeroState.velocity, &local, &gHeroState);
    } else if (state == 11) {
        gHeroState.heading = gHeroState.targetHeading;
        qcopy(&gHeroState.direction, &gHeroState.targetDirection);
        SteerHeroHeading(0, 0.04f, 0.2f, 0.11635530f);
        if (gHeroState.transition != 3) gHeroState.targetSpeed = gHeroState.inputSpeed;
        else gHeroState.targetSpeed = 0.0f;
        if (gHeroState.useCurrentSpeed != 0) {
            float rate = gHeroState.animationSpeed * 0.083333336f;
            if (rate < 0.033333335f) rate = 0.033333335f;
            ApproachValue((float *)(&gHeroState.strafeSpeed), rate, 0.010277778f);
            gHeroState.targetSpeed = gHeroState.planarDistance;
        } else {
            if (gHeroState.allowAction != 0 && gHeroState.actionFrame <= 11)
                ApproachValue((float *)(&gHeroState.strafeSpeed), 0.0f, 0.0022222223f);
            else ApproachValue((float *)(&gHeroState.strafeSpeed), 0.07f, 0.0022222223f);
        }
        if (gHeroState.axisMode == 0) {
            ((float *)&gHeroState.velocity)[0] = FastSinOrCosA(gHeroState.inputHeading);
            ((float *)&gHeroState.velocity)[0] *= gHeroState.strafeSpeed;
            ((float *)&gHeroState.velocity)[1] = FastSinOrCosB(gHeroState.inputHeading);
            ((float *)&gHeroState.velocity)[1] *= gHeroState.strafeSpeed;
        } else {
            SetViewSpaceVectorLength(&local, &gHeroState.localDirection, gHeroState.strafeSpeed);
            SetViewSpaceHeight(&local.q, &local.q, 0.0f);
            SetViewSpaceVectorLength(&gHeroState.velocity, &gHeroState.velocity, 0.0f);
            FastVecAdd(&gHeroState.velocity, &gHeroState.velocity, &local);
        }
        if (gHeroState.axisMode == 0 && gHeroState.useCurrentSpeed == 0) {
            float angle = FastDiffRots(gHeroState.targetHeading, gHeroState.inputHeading);
            float cosine = FastSinOrCosB(angle);
            float amount = gHeroState.inputSpeed * cosine;
            float component = FastSinOrCosA(gHeroState.targetHeading);
            ((float *)&gHeroState.velocity)[0] += component * amount;
            component = FastSinOrCosB(gHeroState.targetHeading);
            ((float *)&gHeroState.velocity)[1] += component * amount;
        }
        BuildHeroMoveImpulse(0.7f, 0.0f);
        qcopy(&gHeroState.pendingResult, &gHeroState.pending);
    } else if (state == 17) {
        gHeroState.heading = ((float *)&gHeroState.jumpDirection)[3];
        qcopy(&gHeroState.direction, &gHeroState.jumpDirection);
        if (gHeroState.frame > 9) SteerHeroHeading(-1, 0.042f, 0.2f, 0.19780402f);
        if (gHeroState.frame > 8) {
            if (gHeroState.request == 0) {
                ((float *)&gHeroState.velocity)[0] = FastSinOrCosA(gHeroState.heading);
                ((float *)&gHeroState.velocity)[0] *= 0.08166667f;
                ((float *)&gHeroState.velocity)[1] = FastSinOrCosB(gHeroState.heading);
                ((float *)&gHeroState.velocity)[1] *= 0.08166667f;
            } else {
                SetViewSpaceVectorLength(&gHeroState.velocity, &gHeroState.velocity, 0.0f);
                vec_scale_to_length(&local, &gHeroState.direction, 0.08166667f);
                FastVecAdd(&gHeroState.velocity, &gHeroState.velocity, &local);
            }
        }
        gHeroState.targetSpeed = gHeroState.planarDistance;
    } else if (state == 129 && D_L07_001A8FF0 == 0) {
        SteerHeroHeading(0, 0.04f, 0.2f, gHeroState.acceleration);
        gHeroState.targetSpeed = 0.0f;
    } else {
        if (gHeroState.state == 44) {
            float angle = gHeroState.rotation;
            float delta;
            gHeroState.yawError = ApproachWithVelocity(&angle, &gHeroState.yawRate, 0,
                gHeroState.heading, 0.017999999225139618f, 0.2f, 0.12217307090759277f);
            delta = fast_subtract_rotations(angle, gHeroState.rotation);
            StartHeroPoseOffset(0.0f, 0.0f, delta);
        } else {
            oldHeading = gHeroState.heading;
            qcopy(&local, &gHeroState.direction);
            if (gHeroState.overrideDirection != 0) {
                gHeroState.heading = D_L07_001B90C0.heading;
                qcopy(&gHeroState.direction, &D_L07_001B90C0.direction);
            }
            SteerHeroHeading(0, 0.04f, 0.2f, gHeroState.acceleration);
            if (gHeroState.overrideDirection != 0) {
                gHeroState.savedHeading = oldHeading;
                qcopy(&gHeroState.savedDirection, &local);
                gHeroState.heading = oldHeading;
                qcopy(&gHeroState.direction, &gHeroState.savedDirection);
            }
        }
        BuildHeroMoveImpulse(0.7f, 0.0f);
        qcopy(&gHeroState.pendingResult, &gHeroState.pending);
        {
            float damping = 0.0055555557f;
            if (gHeroState.speed < D_L07_001A7DC0 * 0.00333333365f) {
                if (gHeroState.mode == 2) {
                    float rate = gHeroState.pendingDamping;
                    smoothed = GetViewSpaceVectorLength((char *)&gHeroState.velocity);
                    ApproachValue(&smoothed, 0.0f, rate);
                    SetViewSpaceVectorLength(&gHeroState.velocity, &gHeroState.velocity, smoothed);
                    return;
                }
                if (gHeroState.contact != 0) damping = 0.00305555575f;
                else if (gHeroState.special != 0) damping = 0.00055555557f;
                else damping = 0.0022222223f;
            }
            ApproachHeroVelocity_L01(damping);
        }
    }
}

/* func_L07_00321D68 is in its qualified quadword-copy unit. */


/* Looks up an entry by index and runs its handler. Returns -1 when the index is missing. */
int func_L07_00338D20(int index)
{
    char *entry;

    if (index == -1)
        return -1;
    entry = *(char **)(D_L07_001FDEC0 + index * 4);
    if (entry == 0)
        return -1;
    func_338D68(entry);
    return 0;
}



/* Moves a bouncing projectile one step. On a hit it splashes or bounces, and when it ends it sets off its explosion. */
void func_L07_003844C0(unsigned char *obj) {
    struct {
        Vec old, velocity, normal;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
        Vec position, spread;
    } frame;
    char *ctx = *(char **)(obj + 0x68), *position = (char *)obj + 0x10;
    int i, lifetime;
    float angle, speed;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, ctx, position);
    SteerEffectDirection(*(int *)(ctx + 0x1C), ctx, 0);
    TransformVectorOrCopy(position, position);
    TriggerCurrentStateEffect(ctx, ctx);
    AddObjectDirectionScaled(position, ctx, 0.0030555557f);
    EmitSparkleParticles(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)gWeaponTable_L00 + gItemSlotToRecord[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, ctx);
    FastVectorNormalizeHelper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        if (!GetCollHitMaterial() && *(float *)(ctx + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(D_L00_001B2630, D_L00_001B2638, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            ClearVector128(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = gCollisionResult.point.f[2];
            effect = SpawnScaledEffectMoby(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                angle = RandomAngle();
                speed = RandomFloatRange(0.0f, 0.050000004f);
                frame.spread.f[0] = FastSinOrCosA(angle) * speed;
                frame.spread.f[1] = FastSinOrCosB(angle) * speed;
                frame.spread.f[2] = RandomFloatRange(0.050000004f, 0.10833334f);
                lifetime = RandomIntRange(90, 120);
                SpawnSparkParticle_002BFB38(&frame.position, spread, RandomIntBelow(2), lifetime);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &gCollisionResult;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &gCollisionResult;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                FastVectorNormalize(&frame.velocity, ctx, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                FastVectorNormalize(&frame.velocity, ctx, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (FastFloatHelperD(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (obj[0xBC]) {
        ClearEntryFlag(*(int *)(ctx + 0x1C));
        SpawnBigExplosionEffect(obj, &frame.velocity, &frame.normal);
    }
}


/* Moves a bouncing projectile one step, like the other one, but counts steps and picks between two explosions. */
void func_L07_003848D8(char *obj) {
    struct {
        Vec velocity, normal, old, surface;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, position, ctx);
    ComputeViewDirection(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.0003055556f);
    SpawnSparkPuff(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + gWeaponTable_L00)->material;
    qcopy(&frame.packet.vector, ctx);
    FastVectorNormalizeHelper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &gCollisionResult;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &gCollisionResult;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            FastVectorNormalize(&frame.velocity, ctx, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &gCollisionResult;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            FastVectorNormalize(&frame.velocity, ctx, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (FastFloatHelperD(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        ClearEntryFlag(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 20)
            SpawnBigExplosionEffect(obj, &frame.velocity, &frame.normal);
        else
            SpawnImpactBurst(obj, &frame.velocity, &frame.normal);
    }
}



extern unsigned short *D_L07_001FAD60[];

extern unsigned char *D_L07_001B22DC[] __attribute__((sda));

extern int D_L07_001B22F8[] __attribute__((sda));

/* Returns the first entity of the group's id list whose state byte is 1, or 0. */
unsigned char *func_L07_003F6B88(int group) {
    unsigned short *p;
    unsigned char *e;

    for (p = gMobyGroupLists_L07[group];
         (unsigned char)group != 0xFF && group <= D_L07_001B22F8[0] && p != 0 &&
         ((short)p[-1] >= 0 || p == gMobyGroupLists_L07[group]);
         p++) {
        e = gMobyArray_L07[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] == 1)
            return e;
    }
    return 0;
}

/* func_L07_003F6F00 is defined in L07_002B3580-g8.c (it reads five tuning words through $gp). */



/* func_L07_00416510 is defined in L07_00416510-g8.c. */
