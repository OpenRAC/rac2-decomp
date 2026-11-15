#include "common.h"

extern unsigned char D_00139574;
extern void func_002AFFD8(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern void func_L00_0038F3D8(void *);
extern void func_L00_0038E880(void *, void *, void *);

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L17_001AC790 __attribute__((sda));
extern int D_L17_001B33B0 __attribute__((sda)), D_L17_001B33B8 __attribute__((sda));
extern Collision D_L17_001C0000;
extern Material D_L17_00263470[];
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

/* Read once as a GP macro load in a delay slot and otherwise as lui/lw, as at -G0 in retail. */
extern int D_L17_001A8F00 __attribute__((sda));
typedef struct { char pad[0x30]; int phase, frame; char gap[0x15C]; char *actor; } CutsceneState;
extern CutsceneState D_L17_001BD8C0;
typedef struct EffectMoby {
    char pad0[0x28]; struct EffectMoby *next; char pad1[8]; unsigned short flags;
    char pad2[0x62]; int unknown; char pad3[0xE]; short classId;
} EffectMoby;
extern EffectMoby *D_L17_001B2C28 __attribute__((sda));
extern void func_0029FCC0(void *, int, void *);
typedef struct { char pad0[4]; int state; char pad1[2]; unsigned char opacity, age; } EffectTail;
typedef struct { char pad0[8]; unsigned char color, size; short life; char pad1[0x14]; EffectTail tail; } CutsceneParticle;
/* Each register bank keeps the callee's order (a0-t0: position, spin, axis, colour, count;
   f12-f15: jitter, lo, hi, size); the interleaving gives retail's argument setup order. */
extern CutsceneParticle *func_002BDCE8(void *, int, float, float, void *, float, unsigned int, float, int);
extern int func_00283CF0(float);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);

extern void func_00282CC0(char *, char *, char *);


extern char D_00189E20[];

extern char D_L17_001FE880[];

extern char D_L17_00296F80[];

extern char D_L17_00296FF0[];

extern void func_00283098(void *, void *, void *);

extern void func_2EEEB8(void *, void *, void *);

extern int func_2EEB28(char *);

extern int func_2F00C0(float);

extern float func_2EF4E0(float);

extern float func_00282C48(float);

extern float func_2F00B0(int);

extern void func_332E48(char *);

extern void func_002A7398();

extern void func_L17_003C71B0();

extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00282E80(void *, void *);
extern void func_L02_0032EF10(void *, void *, void *, void *, float);
/* Picks a random open spot to the side of a start point. It tries left and right first, then
   wider diagonal spots, and stops each try at walls. Returns 1 if the first tries worked. */
int func_L17_0032C070(float *origin, float *target, void *out, void *object, float radius, float height)
{
    Vec left, right, farLeft, farRight, start;
    float heading, angle, dleft, dright, finalDistance;
    heading = FastMatrixHelperA(target[0] - origin[0], target[1] - origin[1]);
    angle = FastAddRotations(heading, 1.5707965f);
    left.f[0] = FastSinOrCosA(angle) * radius;
    left.f[1] = FastSinOrCosB(angle) * radius;
    left.f[2] = 0;
    FastVecAdd((char *)&left, (char *)&left, (char *)origin);
    angle = fast_subtract_rotations(heading, 1.5707965f);
    right.f[0] = FastSinOrCosA(angle) * radius;
    right.f[1] = FastSinOrCosB(angle) * radius;
    right.f[2] = 0;
    FastVecAdd((char *)&right, (char *)&right, (char *)origin);
    start.q = *(Quad *)origin;
    ClampMoveToPathArea(&start, &left, &left, object, height);
    start.q = *(Quad *)origin;
    ClampMoveToPathArea(&start, &right, &right, object, height);
    dleft = vec_distance_xy(origin, &left);
    dright = vec_distance_xy(origin, &right);
    if (radius < dleft + dright) {
        if (RandomFloatRange(0, dleft + dright) < dleft) qcopy(out, &left);
        else qcopy(out, &right);
        return 1;
    }
    angle = FastAddRotations(heading, 0.78539824f);
    farLeft.f[0] = FastSinOrCosA(angle) * 12.0f;
    farLeft.f[1] = FastSinOrCosB(angle) * 12.0f;
    farLeft.f[2] = 0;
    FastVecAdd((char *)&farLeft, (char *)&farLeft, (char *)origin);
    angle = fast_subtract_rotations(heading, 0.78539824f);
    farRight.f[0] = FastSinOrCosA(angle) * 12.0f;
    farRight.f[1] = FastSinOrCosB(angle) * 12.0f;
    farRight.f[2] = 0;
    FastVecAdd((char *)&farRight, (char *)&farRight, (char *)origin);
    start.q = *(Quad *)origin;
    ClampMoveToPathArea(&start, &farLeft, &farLeft, object, height);
    start.q = *(Quad *)origin;
    ClampMoveToPathArea(&start, &farRight, &farRight, object, height);
    finalDistance = vec_distance_xy(origin, &farLeft);
    dright = vec_distance_xy(origin, &farRight);
    if (RandomFloatRange(0, finalDistance + dright) < finalDistance) qcopy(out, &farLeft);
    else qcopy(out, &farRight);
    return 0;
}




/* divides two sub-object measurements taken through the float accessor, scales the ratio by a fixed
   2*pi-scale constant, folds the result through two helpers and packs a colour byte into the object's
   high word */
/* Fades a particle's colour over its lifetime and removes the particle when its time is up. */
void func_L17_00340EA0(char *particle)
{
    float lifeRatio;
    float wave;
    char *extra;

    if (particle == 0)
        return;
    extra = particle + 0x20;
    if (func_2EEB28(particle + 0x24) != 0) {
        func_332E48(particle);
        return;
    }
    lifeRatio = func_2F00B0(*(short *)(extra + 4)) / func_2F00B0(*(short *)(extra + 6));
    wave = func_2EF4E0(lifeRatio * 6.283186f);
    *(int *)(particle + 4) = (*(int *)(particle + 4) & 0x00FFFFFF)
                       + (func_2F00C0(FloatAbs(func_2F00B0(*(int *)(extra + 0xC)) * wave)) << 24);
}



/* Activates the scene's effect mobys during phase 6 and emits paired sparks from the
   scene actor during two frame windows of phases 4 and 5. */
void func_L17_00385DE8(unsigned char *self) {
    Vec velocity, point;
    char *obj;
    CutsceneParticle *first, *second;
    EffectTail *detail;
    int amount, state;

    switch (self[0x20]) {
    case 0:
        self[0x30] = 255;
        self[0x20] = 1;
        break;
    case 1:
        if (D_L17_001A8F00 != 2)
            break;
        if (D_L17_001BD8C0.phase == 6) {
            EffectMoby *effectMoby;
            for (effectMoby = D_L17_001B2C28; effectMoby; effectMoby = effectMoby->next) {
                if (effectMoby->classId == 0xB88 /* Grulch */ || effectMoby->classId == 0x1249) {
                    effectMoby->unknown = 0;
                    effectMoby->flags = (effectMoby->flags | 0x43) & 0xEFFF;
                }
            }
        }
        state = D_L17_001A8F00;
        if (state != 2)
            break;
        if (D_L17_001BD8C0.phase == 4 && (unsigned)(D_L17_001BD8C0.frame - 301) < 59) {
            obj = D_L17_001BD8C0.actor;
            if (*(short *)(obj + 0xAA) == 0x125E) {
                TransformMobyJointToWorld(obj, 0, &point);
                vec_scale_to_length(&velocity, obj + 0xE0, -0.05f);
                amount = RandomIntBelow(16);
                if (RandomIntBelow(2))
                    amount = -amount;
                first = SpawnSpinningSparkParticle(&point, amount, 0.1f, 1.0f, &velocity, 0.9f, 0x7F204080, 100000.0f, 0);
                if (first) {
                    first->life = 16;
                    first->size = FloatToInt(4.0f) + 64;
                    detail = &first->tail;
                    detail->opacity = 127;
                    detail->state = state;
                    detail->age = (unsigned char)first->life;
                }
                amount = 16;
                second = SpawnSpinningSparkParticle(&point, amount, 0.05f, 1.0f, &velocity, 0.97f, 0x7FFFFFFF, 60000.0f, 0);
                /* Retail tests the first spark again before writing the second. */
                if (first) {
                    detail = &second->tail;
                    second->size = FloatToInt(4.0f) + 64;
                    second->life = amount;
                    second->color = RandomIntBelow(255);
                    detail->state = state;
                    detail->opacity = 127;
                    detail->age = (unsigned char)first->life;
                }
                state = D_L17_001A8F00;
            }
        }
        if (state != 2)
            break;
        if (D_L17_001BD8C0.phase == 5 && D_L17_001BD8C0.frame >= 531) {
            obj = D_L17_001BD8C0.actor;
            if (*(short *)(obj + 0xAA) == 0x125E) {
                TransformMobyJointToWorld(obj, 0, &point);
                vec_scale_to_length(&velocity, obj + 0xE0, -0.05f);
                amount = RandomIntBelow(16);
                if (RandomIntBelow(2))
                    amount = -amount;
                first = SpawnSpinningSparkParticle(&point, amount, 0.1f, 1.0f, &velocity, 0.9f, 0x7F204080, 100000.0f, 0);
                if (first) {
                    first->life = 16;
                    first->size = FloatToInt(4.0f) + 64;
                    detail = &first->tail;
                    detail->opacity = 127;
                    detail->state = state;
                    detail->age = (unsigned char)first->life;
                }
                amount = 16;
                second = SpawnSpinningSparkParticle(&point, amount, 0.05f, 1.0f, &velocity, 0.97f, 0x7FFFFFFF, 60000.0f, 0);
                if (first) {
                    detail = &second->tail;
                    second->size = FloatToInt(4.0f) + 64;
                    second->life = amount;
                    second->color = RandomIntBelow(255);
                    detail->state = state;
                    detail->opacity = 127;
                    detail->age = (unsigned char)first->life;
                }
            }
        }
        break;
    }
}

/* Moves a flying projectile one step. When it hits something it either makes a splash of small
   drops or marks itself finished and sets off its hit effect. */
void func_L17_00390CE0(unsigned char *obj) {
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
    char *vars = *(char **)(obj + 0x68), *position = (char *)obj + 0x10;
    int i, lifetime;
    float angle, speed;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, vars, position);
    SteerEffectDirection(*(int *)(vars + 0x1C), vars, 0);
    TransformVectorOrCopy(position, position);
    TriggerCurrentStateEffect(vars, vars);
    AddObjectDirectionScaled(position, vars, 0.0030555557f);
    EmitSparkleParticles(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)D_L17_00263470 + gItemSlotToRecord[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, vars);
    FastVectorNormalizeHelper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        if (!GetCollHitMaterial() && *(float *)(vars + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(D_L17_001B33B0, D_L17_001B33B8, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            ClearVector128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = D_L17_001C0000.point.f[2];
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
            Collision *collision = &D_L17_001C0000;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = &D_L17_001C0000;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L17_001AC790 && *(short *)(model + 0xAA) != 0x336)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                FastVectorNormalize(&frame.velocity, vars, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                FastVectorNormalize(&frame.velocity, vars, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (FastFloatHelperD(vars + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (obj[0xBC]) {
        ClearEntryFlag(*(int *)(vars + 0x1C));
        SpawnBigExplosionEffect(obj, &frame.velocity, &frame.normal);
    }
}



/* Moves a projectile one step and counts its age. When it hits something it sets off a small
   hit effect if it is young, or a bigger one if it is older. */
void func_L17_003910F8(char *obj) {
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
    char *vars = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, position, vars);
    ComputeViewDirection(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.0003055556f);
    SpawnSparkPuff(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L17_00263470)->material;
    qcopy(&frame.packet.vector, vars);
    FastVectorNormalizeHelper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L17_001C0000;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = &D_L17_001C0000;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L17_001AC790 && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            FastVectorNormalize(&frame.velocity, vars, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L17_001C0000;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            FastVectorNormalize(&frame.velocity, vars, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (FastFloatHelperD(vars + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        ClearEntryFlag(*(int *)(vars + 0x1C));
        if (*(int *)(vars + 0x14) < 20)
            SpawnBigExplosionEffect(obj, &frame.velocity, &frame.normal);
        else
            SpawnImpactBurst(obj, &frame.velocity, &frame.normal);
    }
}



/* func_L17_003A14A0 is defined in L17_0032C070-burst-g8.c. */

/* func_L17_003A4740 is defined in L17_0032C070-grid.c. */

/* func_L17_003BCBC8 is defined in L17_0032C070-g8.c: the -G8 profile of that
   unit is what makes its register allocation come out right. */

/* func_L17_003BCC30 is defined in L17_0032C070-path.c. */

/* func_L17_003BCEC0 is defined in L17_0032C070-path.c. */

/* func_L17_003BD310 is defined in L17_0032C070-hazard-g8.c. */

/* runs seven two-stage transforms over a record reached from an id in the sub-object; the id -1
   aborts, and the last id is echoed into the shared resident word */
/* Moves a seven-point path so it follows the platform (turned and shifted to match it) and
   remembers that path in the player data. */
void func_L17_003C3250(char *moby)
{
    char *vars;
    char *point;
    char *template;
    char *position;
    char *matrix;
    char *hero;
    int pathRef;
    int i;

    vars = *(char **)(moby + 0x68);
    pathRef = *(int *)(vars + 0xD0);
    if (pathRef == -1)
        return;
    pathRef = *(int *)(gPathTable_L17 + pathRef * 4);
    if (*(int *)pathRef != 7)
        return;
    matrix = moby + 0xC0;
    position = moby + 0x10;
    template = D_L17_00296F80;
    point = pathRef + 0x10;
    for (i = 6; i >= 0; i--) {
        matrix_mul_vec3(point, template, matrix);
        template += 0x10;
        func_2EEEB8(point, point, position);
        point += 0x10;
    }
    hero = gHeroState;
    *(unsigned short *)(hero + 0x24FE) = *(unsigned short *)(vars + 0xD0);
}

/* func_L17_003C3330 is defined in L17_0032C070-lift-g8.c. */






/* func_L17_003C4090 is defined in L17_0032C070-motion-g8.c. */

/* func_L17_003C45A0 is defined in L17_0032C070-carrier-g8.c. */



/* raises the state word to 0x920 and runs a three-argument setup, or, when it is already 0x929,
   re-runs the 0x71B0 activation if the object is still unmarked */
/* Starts a ride platform: a class 0x920 one in its first state moves on to state 1, and a class
   0x929 one in its first state runs its own set-up. */
void func_L17_003C5AF8(int moby)
{
    if (*(short *)(moby + 0xAA) == 0x920) {
        if (*(unsigned char *)(moby + 0x20) == 0) {
            *(unsigned char *)(moby + 0x20) = 1;
            StartAnimationImmediate(moby, 1, 0);
            return;
        }
    }
    if (*(short *)(moby + 0xAA) == 0x929) {
        if (*(unsigned char *)(moby + 0x20) == 0)
            WakeUpIdleMoby(moby);
    }
}



/* true for the sub-state 0x922 when the object's stage byte sits in the 2..6 window */
/* Returns 1 while a class 0x922 platform is in one of its states 2 to 6, which is while it is
   carrying the player along. */
int func_L17_003C5DF0(int moby)
{
    if (*(short *)(moby + 0xAA) != 0x922)
        return 0;
    return *(unsigned char *)(moby + 0x20) - 2U < 5;
}

/* true when the level's shared record names the given sub-state; the shared word at
   0x34E closes the answer when the record is not the level's own */
/* Returns 1 when the given object is the one the player is standing on or attached to. */
int func_L17_003C5E20(int moby)
{
    char *hero = gHeroState;

    if (*(int *)(hero + 0x229C) == 3 || *(int *)(hero + 0x2294) == 0x1B) {
        if (*(int *)(hero + 0x588) != moby)
            goto zero;
        return 1;
    }
    if (*(short *)(hero + 0x34E) != 0)
        goto zero;
    if (*(int *)(hero + 0x33C) == moby)
        return 1;
zero:
    return 0;
}

/* twin of func_L17_003C3250 on the 0x128 sub-object id and its own table */
/* Same as func_L17_003C3250, but for the second path of the platform. */
void func_L17_003C5E78(char *moby)
{
    char *vars;
    char *point;
    char *template;
    char *position;
    char *matrix;
    char *hero;
    int pathRef;
    int i;

    vars = *(char **)(moby + 0x68);
    pathRef = *(int *)(vars + 0x128);
    if (pathRef == -1)
        return;
    pathRef = *(int *)(gPathTable_L17 + pathRef * 4);
    if (*(int *)pathRef != 7)
        return;
    matrix = moby + 0xC0;
    position = moby + 0x10;
    template = D_L17_00296FF0;
    point = pathRef + 0x10;
    for (i = 6; i >= 0; i--) {
        matrix_mul_vec3(point, template, matrix);
        template += 0x10;
        func_2EEEB8(point, point, position);
        point += 0x10;
    }
    hero = gHeroState;
    *(unsigned short *)(hero + 0x24FE) = *(unsigned short *)(vars + 0x128);
}


/* func_L17_003C69A8 is defined in its dedicated-g8.c source. */

/* func_L17_003C6CE8 is defined in its dedicated-g8.c source. */

/* func_L17_003C7018 is defined in L17_0032C070-g8.c (this unit has no $gp access for it). */

/* func_L17_003C71B0 is matched in L17_003C71B0.c (built with -mno-split-addresses). */

/* Stores the second argument in the object's sub-record at 0xA4. */
void func_L17_003C7250(char *moby, int pathIndex)
{
    *(int *)(*(char **)(moby + 0x68) + 0xA4) = pathIndex;
}



/* func_L17_003C7680 is matched in L17_0032C070-platform-g8.c. */

/* true when the sub-object word at 0xBC holds the value two */
/* Returns 1 when the platform's second path is in its waiting stage (stage 2). */
int func_L17_003C7C58(int moby)
{
    return *(int *)(*(int *)(moby + 0x68) + 0xBC) == 2;
}
