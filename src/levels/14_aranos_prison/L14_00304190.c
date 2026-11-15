#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern unsigned char D_00139574;
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038F3D8(void *);
extern void func_L00_0038E880(void *, void *, void *);
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L14_001AC790 __attribute__((sda));
extern int D_L14_001B2D30 __attribute__((sda)), D_L14_001B2D38 __attribute__((sda));
extern Collision D_L14_001BF940;
extern Material D_L14_002686F0[];
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



extern void func_321F58();
extern char *func_328768();
extern void func_328DA8();
extern void func_3322F0();
extern void func_3DECE0();
extern void func_3DF6A0();
extern float func_3E22A8();
extern void func_2F5C38();
extern void func_2F5C68();
extern void func_2F6498();
extern void func_00282D30(void *dst, void *src, float scale);
extern void func_00282CC0(void *dst, void *a, void *b);
extern void func_31A618();
extern void func_4209A0();
extern int func_420C68();
extern float func_2F6C80(float a, float b);
extern float func_2F6240(float a);
extern void func_2F5F18(void *dst, void *src, float s);
extern void func_2F5D68(void *dst, void *src, void *mtx);
extern void func_3910E0(char *a0, char *a1, int a2, int a3, int t0, int t1, int t2,
                        float f12, float f13, float f14, float f15, float f16);

extern char D_0018A0E0[];
extern char D_L14_00237B00[];

/* func_L14_00304190 is defined in L14_00304190-zp.c (it clears a stack vector with por, which needs -frac2-zero-ti-por). */

/* func_L14_00304280 lives in the -g8 sibling file (it reaches a global through $gp). */

typedef struct {
    unsigned char pad00[0x34];
    unsigned short flags;
    unsigned char pad36[0x68 - 0x36];
    unsigned int p68;
    unsigned char pad6C[0xAA - 0x6C];
    short type;
} Mob_L14_00304588;

typedef struct {
    unsigned char pad00[0x30];
    int mode;
    unsigned char pad34[0x44 - 0x34];
    short count;
    unsigned char pad46[0x18C - 0x46];
    Mob_L14_00304588 *mobs[1];
} MobList_L14_00304588;

extern MobList_L14_00304588 ref_L14_00304588_00;
extern int D_001A79F0 __attribute__((sda));
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(void *, void *, int, int, float);
extern void func_L08_0037E6D8(void);
extern void func_L03_00326458(int);

/* Walks the level's list of mobs like func_L02_00300CE8; when the game state is 0xE and the
   list's word at +0x30 is zero it then runs two more calls, the second with the list's word at +0x194. */
void func_L14_00304588(void) {
    int i;

    StartStartupAnimations();
    for (i = 0; i < ref_L14_00304588_00.count; i++) {
        Mob_L14_00304588 *mob = ref_L14_00304588_00.mobs[i];

        if (mob != 0 && mob->type == 0xE29 /* moby class 3625 */)
            mob->flags |= 0x800;
        if (mob->type == 0xD54 /* moby class 3412 */)
            UpdateEquipmentPieces(mob);
        if (mob != 0 && mob->type == 0xFA0 /* TV Screens */ && mob->p68 != 0)
            StoreAngleUpdateResult(mob, (unsigned char *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.0610865355f);
    }
    if (gCurrentMapIndex == 0xE && ref_L14_00304588_00.mode == 0) {
        CopyGroupWordToMembers();
        EmitScaledObjectParticles(*(int *)((char *)&ref_L14_00304588_00 + 0x194));
    }
}

/* func_L14_00328E70 is matched in its own unit, src/levels/14_aranos_prison/L14_00328E70-qcopy.c (-frac2-qcopy). */

/* Looks up a helper for the object and, if one exists, hands it the object position (moved by an offset) and the rotation. */
void func_L14_00328E90(char *moby, char *offset, char *extra) {
    char buf[16];
    char *helper = func_328768(moby);

    if (helper != 0) {
        func_2F5C68(buf, moby + 0x10, offset);
        func_328DA8(helper, buf, extra, moby + 0xF0);
    }
}

/* func_L14_0035F510 is defined in L14_0035F510-g8.c (it reads its list through $gp). */

/* func_L14_00390DF8 is defined in L14_00390DF8-helpers.c. */

/* func_L14_00390EC0 is defined in L14_00304190-zp.c (it clears a stack vector with por, which needs -frac2-zero-ti-por). */

/* Sets up four pairs of entries from two tables, using the settings stored in the object. */
void func_L14_00390FE8(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *tableA = D_L14_00237B00;
    char *tableB = tableA + 0x400;
    int i;

    for (i = 0; i < 4; i++) {
        func_3910E0(moby, (char *)(((*(int *)(vars + 0xDC) + i) << 8) + (unsigned int)tableA),
                    *(int *)(vars + 0x38), *(int *)(vars + 0x40),
                    *(int *)(vars + 0x60), *(int *)(vars + 0x44), *(int *)(vars + 0x64),
                    *(float *)(vars + 0x50), *(float *)(vars + 0x70), *(float *)(vars + 0x54),
                    *(float *)(vars + 0x74), 0.9f);
        func_3910E0(moby, (char *)(((*(int *)(vars + 0xDC) + i) << 8) + (unsigned int)tableB),
                    *(int *)(vars + 0x38), *(int *)(vars + 0x48),
                    *(int *)(vars + 0x68), *(int *)(vars + 0x4C), *(int *)(vars + 0x6C),
                    *(float *)(vars + 0x58), *(float *)(vars + 0x78), *(float *)(vars + 0x5C),
                    *(float *)(vars + 0x7C), 0.1f);
    }
}

/* Scales a vector and adds the result onto the object offset at +0x30. */
void func_L14_00391B58(char *moby, float scale) {
    char buf[16];

    FastVecScale(buf, moby, scale);
    FastVecAdd(moby + 0x30, moby + 0x30, buf);
}

/* Moves a falling object one step, checks what it hits, and bounces or lands on the hit. On a floor hit it puffs out a burst of small particles. */
void func_L14_00399E28(unsigned char *moby) {
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
    char *vars = *(char **)(moby + 0x68), *position = (char *)moby + 0x10;
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
    EmitSparkleParticles(moby);
    frame.packet.moby = moby;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)D_L14_002686F0 + gItemSlotToRecord[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, vars);
    FastVectorNormalizeHelper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(moby + 0xAA);
    frame.packet.active = 1;
    if (CollLine(&frame.old, position, 0x10, moby, &frame.packet)) {
        if (!GetCollHitMaterial() && *(float *)(vars + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(D_L14_001B2D30, D_L14_001B2D38, 1,
                *(float *)(moby + 0x10), *(float *)(moby + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            ClearVector128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(moby + 0x10);
            frame.position.f[1] = *(float *)(moby + 0x14);
            frame.position.f[2] = D_L14_001BF940.point.f[2];
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
            Collision *collision = &D_L14_001BF940;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = &D_L14_001BF940;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L14_001AC790 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                    goto finish;
                moby[0xBC] = 1;
                qcopy(moby + 0x10, &reread->point);
                FastVectorNormalize(&frame.velocity, vars, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                moby[0xBC] = 1;
                qcopy(moby + 0x10, &collision->point);
                FastVectorNormalize(&frame.velocity, vars, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (FastFloatHelperD(vars + 0x18)) {
        moby[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (moby[0xBC]) {
        ClearEntryFlag(*(int *)(vars + 0x1C));
        SpawnBigExplosionEffect(moby, &frame.velocity, &frame.normal);
    }
}


/* Moves a flying object one step and checks what it hits. After enough steps a hit uses a different response. */
void func_L14_0039A240(char *moby) {
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
    char *vars = *(char **)(moby + 0x68);
    char *position = moby + 0x10;
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
    SpawnSparkPuff(moby);
    frame.packet.moby = moby;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L14_002686F0)->material;
    qcopy(&frame.packet.vector, vars);
    FastVectorNormalizeHelper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(moby + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, moby, &frame.packet)) {
        collision = &D_L14_001BF940;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = &D_L14_001BF940;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L14_001AC790 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            moby[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = moby + 0x10;
                qcopy(dest, source);
            }
            FastVectorNormalize(&frame.velocity, vars, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L14_001BF940;
            if (collision->count <= 0)
                goto finish;
            moby[0xBC] = 1;
            qcopy(position, &collision->point);
            FastVectorNormalize(&frame.velocity, vars, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (FastFloatHelperD(vars + 0x18)) {
        moby[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (*(unsigned char *)(moby + 0xBC)) {
        ClearEntryFlag(*(int *)(vars + 0x1C));
        if (*(int *)(vars + 0x14) < 20)
            SpawnBigExplosionEffect(moby, &frame.velocity, &frame.normal);
        else
            SpawnImpactBurst(moby, &frame.velocity, &frame.normal);
    }
}



/* Tells whether the entity has its flag byte at +0x95 set to exactly 1. */
int func_L14_003C9548(char *entity) {
    return (entity[0x95] ^ 1) == 0;
}

/* func_L14_003CB258 is defined in L14_003CB258-g8.c (it reads its tuning through $gp). */

/* func_L14_003CB4D8 is defined in L14_003CB4D8-g8.c. */

extern void func_00283698(void *dst, void *src);

extern void func_00282CF0(void *dst, void *a, void *b);

extern void func_002AFDD8(void *a, void *b, void *c, void *d);

extern float func_00282C48(float a);

extern void func_00283098(void *dst, void *a, void *mtx);

extern void func_00282CC0(void *dst, void *a, void *b);

extern void func_L14_003C9658(char *e, void *v);

extern unsigned short *D_L14_001FB060[];

extern unsigned char *D_L14_001B259C __attribute__((sda));

extern int D_L14_001B25B8 __attribute__((sda));

/* The twin of func_L14_003DF200 for the group word at +0x64: the same pass over the entities
   of the owner's group (not the states 0xFE and 0xFD, not the class 0xA59, accepted by
   func_L14_003C9548), with the box centred at -2.0 on the first axis: beyond 0.8 of it the
   offset is pulled back to -1.5 or -2.5, beyond 0.8 on the second axis to +-0.5, and the entity
   is handed the corrected world position (func_L14_003C9658). */
void func_L14_003CB608(char *self) {
    float mtx[16];
    float off[4];
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *entity;
    int clamped;

    matrix_from_basis_rows(mtx, self + 0xC0);
    for (p = gGroupEntityLists[*(int *)(state + 0x64)];
         (*(int *)(state + 0x64) & 0xFF) != 0xFF && *(int *)(state + 0x64) <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == gGroupEntityLists[*(int *)(state + 0x64)]);
         p++) {
        entity = gMobyPool_L14 + ((*p & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x20] != 0xFE) {
            if (entity[0x20] != 0xFD) {
                if (*(short *)(entity + 0xAA) != 0xA59 /* moby class 2649 */) {
                    if (IsEntityFlagSet((char *)entity) != 0) {
                        FastVecSub(off, entity + 0x10, self + 0x10);
                        clamped = 0;
                        TransformVectorByObjectOrGiven(self, off, off, mtx);
                        if (FloatAbs(off[0] + 2.0f) > 0.8f) {
                            clamped = 1;
                            if (off[0] > -1.5f)
                                off[0] = -1.5f;
                            else if (off[0] < -2.5f)
                                off[0] = -2.5f;
                        }
                        if (FloatAbs(off[1]) > 0.8f) {
                            clamped = 1;
                            if (off[1] > 0.5f)
                                off[1] = 0.5f;
                            else if (off[1] < -0.5f)
                                off[1] = -0.5f;
                        }
                        if (clamped) {
                            matrix_mul_vec3(off, off, self + 0xC0);
                            FastVecAdd(off, off, self + 0x10);
                            ApplyCorrectedPositionToEntity((char *)entity, off);
                        }
                    }
                }
            }
        }
    }
}

/* func_L14_003CB868 is defined in L14_003CB868.c. */

/* func_L14_003D18C8 is defined in L14_003D18C8.c. */


/* func_L14_003DDD38 is defined in L14_00304190-g8.c (it reaches D_L14_001B259C through $gp). */

/* Counts how many of the four child slots are in use. */
int func_L14_003DE2D8(char *moby) {
    int *slot = (int *)(*(int *)(moby + 0x68) + 0xE0);
    int count = 0;
    int i;

    for (i = 3; i >= 0; i--) {
        if (*slot != 0) {
            count++;
        }
        slot++;
    }
    return count;
}

extern void func_328340(void *dst, void *src, void *mtx, float f);
extern float func_324F78(float a, float b, float c);

/* The object is placed in the world: the group's two matrices are copied and turned by the
   angle, the object's own matrix is rebuilt from them, and the three floats it keeps are
   cleared. The first call takes the object's own matrix as its second argument, but the
   compiler overwrites it with the local buffer before the call, so the callee sees the
   buffer (as retail does). */
void func_L14_003DE360(char *self, float angleStep) {
    char buf[16];
    char *vars = *(char **)(self + 0x68);
    char *mB0 = vars + 0xB0;
    char *mC0 = vars + 0xC0;
    char *m10 = self + 0x10;
    char *mD0 = self + 0xD0;
    char *mE0 = self + 0xE0;
    float f0;
    float zero;

    func_2F5C68(buf, m10, mB0);
    func_328340(buf, buf, mC0, angleStep);
    f0 = *(float *)(vars + 0x80) + angleStep;
    *(float *)(vars + 0x80) = f0;
    func_2F5F18(buf, buf,
                func_324F78(*(float *)(vars + 0x84), *(float *)(vars + 0x88), f0 * 0.63661977f));
    func_2F5C38(m10, mB0, buf);
    func_2F5F18(mD0, mC0, 1.0f);
    func_2F5F18(mE0, buf, -1.0f);
    func_2F5D68(self + 0xC0, mE0, mD0);
    zero = 0.0f;
    *(float *)(self + 0xEC) = zero;
    *(float *)(self + 0xDC) = zero;
    *(float *)(self + 0xCC) = zero;
}

/* Wakes every child object that has a non-zero value in its state block. */
void func_L14_003DE488(char *moby) {
    char **slot = (char **)(*(int *)(moby + 0x68) + 0xE0);
    int i;

    for (i = 3; i >= 0; i--) {
        char *child = *slot;

        if (child != 0 && *(int *)(*(int *)(child + 0x68) + 0x2E0) != 0) {
            func_3322F0(child, 1);
        }
        slot++;
    }
}

typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } PrisonLiftVoice;
typedef struct {
    char pad0000[0x80];
    Vec position;               /* 0x80 */
    char pad0090[0x22B4 - 0x90];
    unsigned char mode;         /* 0x22B4 */
} PrisonLiftHero;
extern PrisonLiftHero D_00189E20;
extern char D_00188660[];
extern int func_002B3868(char *self);
extern int func_L00_00324120(char *);
extern int func_002ACBC8(void *, int);
extern int func_002E59B0(char *, int);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(int);
extern int func_L14_003DE908(char *);
extern void func_002A7750(void *, int, int);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_002AD6F0(void *, void *, void *, void *);

/* A lift that travels between its start height (0x68) and its target (0x64): state 0 sets it
   up, state 1 waits for the hero (or a trigger) and starts it with its travel sound, states 2
   and 3 ease it up and down and stop the sound on arrival. Riders follow its movement. */
void func_L14_003DE4E8(char *moby)
{
    Vec pos, rot, delta;
    char *state = *(char **)(moby + 0x68);
    int sound;

    qcopy(&pos, moby + 0x10);
    qcopy(&rot, moby + 0xF0);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(int *)(state + 0x5C) |= 1;
        {
            float target = *(float *)(state + 0x64);
            float start = *(float *)(moby + 0x18);
            *(int *)(state + 0x74) = -1;
            *(float *)(state + 0x7C) = 0.0011666667f;
            *(float *)(state + 0x68) = start;
            *(int *)(state + 0x70) = 0;
            *(float *)(state + 0x80) = (start + target) * 0.5f;
        }
        if (*(int *)(state + 0x60) == 0) *(int *)(state + 0x6C) = 0;
        else *(int *)(state + 0x6C) = 1;
        *(unsigned char *)(moby + 0x20) = 1;
        break;
    case 1:
        if (gHeroState.mode == 1 && *(int *)(state + 0x84)) {
            if (*(int *)(state + 0x6C) == 1) {
                SetMobyState(moby, 2, -1);
                *(int *)(state + 0x74) = PlayMobySound(0, 4, moby);
            }
        } else if (IsCurrentSelectedId(moby)
                   || ((*(float *)(moby + 0x18) - *(float *)(state + 0x80)) * (gHeroState.position.f[2] - *(float *)(state + 0x80)) < 0.0f
                       && *(int *)(state + 0x70))) {
            if (*(int *)(state + 0x6C) == 0) {
                SetMobyState(moby, 3, -1);
                if (!IsVoicePlayingForOwner(moby, *(int *)(state + 0x74)))
                    *(int *)(state + 0x74) = PlayMobySound(0, 4, moby);
            } else {
                SetMobyState(moby, 2, -1);
                if (!IsVoicePlayingForOwner(moby, *(int *)(state + 0x74)))
                    *(int *)(state + 0x74) = PlayMobySound(0, 4, moby);
            }
        }
        break;
    case 2:
        if (SetFirstPendingFlag(moby)) {
            *(float *)(state + 0x78) = 0.0f;
            (*(int *)(state + 0x70))++;
        }
        if (*(float *)(state + 0x64) - *(float *)(moby + 0x18) < 0.03f) {
            sound = *(int *)(state + 0x74);
            if (sound != -1) {
                PrisonLiftVoice *voice = (PrisonLiftVoice *)(gSoundState + sound * 0x70);
                if (voice->owner == moby && voice->active) StopSoundVoice(sound);
            }
            *(int *)(state + 0x74) = -1;
            if (!IsObjectHitByPlayerOrAimRay(moby)) {
                *(int *)(state + 0x6C) = 0;
                *(float *)(moby + 0x18) = *(float *)(state + 0x64);
                SetMobyState(moby, 1, -1);
            }
        } else StepValueTowardTarget(moby + 0x18, state + 0x78, *(float *)(state + 0x64), *(float *)(state + 0x7C), *(float *)(state + 0x7C), 0.10000001f);
        break;
    case 3:
        if (SetFirstPendingFlag(moby)) {
            *(float *)(state + 0x78) = 0.0f;
            (*(int *)(state + 0x70))++;
        }
        if (*(float *)(moby + 0x18) - *(float *)(state + 0x68) < 0.03f) {
            sound = *(int *)(state + 0x74);
            if (sound != -1) {
                PrisonLiftVoice *voice = (PrisonLiftVoice *)(gSoundState + sound * 0x70);
                if (voice->owner == moby && voice->active) StopSoundVoice(sound);
            }
            *(int *)(state + 0x74) = -1;
            if (!IsObjectHitByPlayerOrAimRay(moby)) {
                *(int *)(state + 0x6C) = 1;
                *(float *)(moby + 0x18) = *(float *)(state + 0x68);
                SetMobyState(moby, 1, -1);
            }
        } else {
            int ridden = IsCurrentSelectedId(moby) != 0;
            int away = IsPointInCuboid(&gHeroState.position, *(int *)(state + 0x88)) == 0;
            if (ridden || away)
                StepValueTowardTarget(moby + 0x18, state + 0x78, *(float *)(state + 0x68), *(float *)(state + 0x7C), *(float *)(state + 0x7C), 0.10000001f);
        }
        break;
    }
    FastVecSub(&delta, moby + 0x10, &pos);
    CombineTransformsAndStore(state + 0x20, &delta, &rot, moby + 0xF0);
}

/* Tells whether the object is in state 2 or state 3, which means it is moving. */
int func_L14_003DE8E8(unsigned char *moby) {
    return (unsigned int)(moby[0x20] - 2) < 2;
}

/* Marks the object so that it will start moving. */
void func_L14_003DE8F8(char *moby) {
    *(int *)(*(int *)(moby + 0x68) + 0x84) = 1;
}

/* Puts the object into state 2. */
void func_L14_003DE990(char *moby) {
    func_321F58(moby, 2, -1);
}

/* func_L14_003DE9B0 is in its -g8 unit. */

/* func_L14_003DECE0 is defined in L14_003DECE0.c. */

/* func_L14_003DF100 lives in the -g8 sibling file (its calls pass floats, so it needs real prototypes). */

extern float func_00282C48(float a);

extern void func_00283698(void *dst, void *src);

extern void func_00282CF0(void *dst, void *a, void *b);

extern void func_002AFDD8(void *a, void *b, void *c, void *d);

extern void func_00283098(void *dst, void *a, void *mtx);

extern void func_00282CC0(void *dst, void *a, void *b);

extern void func_L14_003C9658(char *e, void *v);

extern unsigned short *D_L14_001FB060[];

extern unsigned char *D_L14_001B259C __attribute__((sda));

extern int D_L14_001B25B8 __attribute__((sda));

/* For every entity of the owner's group (state word 0x68), other than the two states 0xFE and
   0xFD, that func_L14_003C9548 accepts: takes its offset from the owner in the owner's frame;
   when that is beyond 1.0 on the first axis or 1.5 on the second it is pulled back to +-0.5 or
   +-1.25, and the entity is handed the corrected world position (func_L14_003C9658). */
void func_L14_003DF200(char *self) {
    float mtx[16];
    float off[4];
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *entity;
    int clamped;

    matrix_from_basis_rows(mtx, self + 0xC0);
    for (p = gGroupEntityLists[*(int *)(state + 0x68)];
         (*(int *)(state + 0x68) & 0xFF) != 0xFF && *(int *)(state + 0x68) <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == gGroupEntityLists[*(int *)(state + 0x68)]);
         p++) {
        entity = gMobyPool_L14 + ((*p & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x20] != 0xFE) {
            if (entity[0x20] != 0xFD) {
                if (IsEntityFlagSet((char *)entity) != 0) {
                    FastVecSub(off, entity + 0x10, self + 0x10);
                    clamped = 0;
                    TransformVectorByObjectOrGiven(self, off, off, mtx);
                    if (FloatAbs(off[0]) > 1.0f) {
                        clamped = 1;
                        if (off[0] > 0.5f)
                            off[0] = 0.5f;
                        else if (off[0] < -0.5f)
                            off[0] = -0.5f;
                    }
                    if (FloatAbs(off[1]) > 1.5f) {
                        clamped = 1;
                        if (off[1] > 1.25f)
                            off[1] = 1.25f;
                        else if (off[1] < -1.25f)
                            off[1] = -1.25f;
                    }
                    if (clamped) {
                        matrix_mul_vec3(off, off, self + 0xC0);
                        FastVecAdd(off, off, self + 0x10);
                        ApplyCorrectedPositionToEntity((char *)entity, off);
                    }
                }
            }
        }
    }
}

/* func_L14_003DF440 lives in the -g8 sibling file (it reads a count through $gp). */

/* func_L14_003DF540 lives in the -g8 sibling file (it reads a count through $gp). */

/* Runs the setup call on the first frame and sets the object update callback. */
void func_L14_003DF650(unsigned char *moby) {
    if (moby[0x20] == 0) {
        func_3DECE0();
    }
    *(int *)(moby + 0x64) = (int)func_3DF6A0;
}

/* Stores a value into the object state block. */
void func_L14_003DF690(char *moby, int value) {
    *(int *)(*(int *)(moby + 0x68) + 0x7C) = value;
}

/* func_L14_003DF6A0 is defined in L14_003DF6A0-g8.c. */

/* func_L14_003DF7F8 is defined in L14_00304190-g8.c (this unit has no $gp access for it). */

/* Builds a position from the object and passes it, with a target, to another routine. */
void func_L14_003DFA10(char *moby, char *target) {
    char buf[16];
    char *vars = *(char **)(moby + 0x68);

    func_2F5C38(buf, moby + 0xC0, moby + 0x10);
    func_4209A0(*(int *)(vars + 0x0), buf, target);
}


/* Makes the object bob up and down smoothly around its start height. */
void func_L14_003E1DD0(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    unsigned char state = *(unsigned char *)(moby + 0x20);

    switch (state) {
    case 0:
        *(float *)(vars + 0x4) = *(float *)(moby + 0x18);
        *(int *)(vars + 0x8) = 0;
        func_321F58(moby, 1, -1);
        break;
    case 1:
        *(float *)(moby + 0xF8) = func_2F6C80(*(float *)(moby + 0xF8), *(float *)(vars + 0x0));
        *(float *)(vars + 0x8) = func_2F6C80(*(float *)(vars + 0x8), *(float *)(vars + 0xC));
        *(float *)(moby + 0x18) = *(float *)(vars + 0x4)
                                  + *(float *)(vars + 0x10) * func_2F6240(*(float *)(vars + 0x8));
        break;
    }
}


/* func_L14_003E1E78 is in its -g8 unit. */

/* Rebuilds the object matrix and scales it by an amount that depends on its state. */
void func_L14_003E2238(char *moby) {
    float scale = func_3E22A8(moby);

    func_2F6498(moby + 0xC0, moby + 0xF0);
    FastVecScale(moby + 0xC0, moby + 0xC0, scale);
    FastVecScale(moby + 0xD0, moby + 0xD0, scale);
    func_31A618(moby);
}

/* Gives a 0 to 1 fraction for how far the object is through its current state. */
float func_L14_003E22A8(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    unsigned int state = *(unsigned char *)(moby + 0x20);

    if (state == 4) {
        return (float)*(int *)(vars + 0x7C) / (float)*(int *)(vars + 0x78);
    }
    if (state == 2) {
        return 1.0f - (float)*(int *)(vars + 0x7C) / (float)*(int *)(vars + 0x70);
    }
    if (state == 1) {
        return 0.0f;
    }
    return 1.0f;
}

/* func_L14_003E2328 is defined in L14_003E2328-g8.c. */

/* func_L14_003E2688 is defined in L14_00304190-g8.c. */

/* Wraps an angle in radians into the range 0 to two pi. */
float func_L14_003E28E8(float angle) {
    float wrapped = angle;

    while (6.2831855f < wrapped) {
        wrapped = wrapped - 6.2831855f;
    }
    while (wrapped < 0.0f) {
        wrapped = wrapped + 6.2831855f;
    }
    return wrapped;
}

/* func_L14_003E2980 is defined in L14_00304190-g8.c (it reads its tuning through $gp). */

/* func_L14_003E4208 is defined in L14_003E4208-g.c (it needs -g for retail's line-note nops). */

extern char D_00188660[];
extern int func_332310(char *self);
extern int func_369AD0(int a0, int a1, char *a2);
extern int func_3697D0(int a0);
extern float func_2F6CC8(float a0, float a1);

/* The object steers a group of entities: by its state byte it either leaves the group
   (state 0), asks whether the group is free and hands itself over if it is (state 1) or
   turns (state 2).  In the turning state it takes an entry from the ring of the group's own
   entries (D_00188660, 0x70 bytes each) - a new one when the entry it holds is not its
   own or is free - and turns half a degree; at the end it releases the entry it holds
   when the entry is its own and in use, and forgets it either way. */
void func_L14_003E4A40(char *self) {
    char *state = *(char **)(self + 0x68);
    char *e1;
    char *e2;
    int idx;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        func_321F58(self, 1, -1);
        *(int *)state = -1;
        break;
    case 1:
        if (func_332310(self) != 0) {
            func_321F58(self, 2, -1);
        }
        break;
    case 2:
        if (*(float *)(self + 0xF0) > -1.5707964f) {
            e1 = gSoundState + *(int *)state * 0x70;
            if (*(int *)(e1 + 0x88) != (int)self || *(unsigned char *)(e1 + 0x74) == 0) {
                *(int *)state = func_369AD0(0, 4, self);
            }
            *(float *)(self + 0xF0) = func_2F6CC8(*(float *)(self + 0xF0), 0.0087266471f);
        }
        idx = *(int *)state;
        if (idx != -1) {
            e2 = gSoundState + idx * 0x70;
            if (*(int *)(e2 + 0x88) == (int)self && *(unsigned char *)(e2 + 0x74) != 0) {
                func_3697D0(idx);
            }
        }
        *(int *)state = -1;
        break;
    }
}

extern int func_002B3868(char *self);
extern int func_00282978(char *p);
extern void func_L14_003E4EA0(char *self);
extern void func_L14_003E5030(char *self);
extern void func_L14_003E50B8(char *self);
extern void func_L14_003E5190(char *self);
extern void func_L14_003E51B0(char *self);
extern void func_L14_003E5218(char *self);

/* The key state of an object that steers a group (+0x14 the current key, +0x16 the key index,
   +0x34 the key word). The last walk stores through this struct: cc1 then knows the store does
   not touch the two level globals (a store through a cast pointer might), so loop.c moves their
   loads and the constants out of the loop. That walk is spelled like the other two, with the
   second `p != 0`: its test is too long for the first jump pass to copy in front of the loop,
   and after loop.c has hoisted the invariants it is short enough for the second pass, which
   copies it (retail's entry test ahead of the loop, the hoisted values before it). A cast store
   instead leaves nothing to hoist and the walk stays in the `b test` form. */
typedef struct {
    unsigned char pad[0x14];
    unsigned short cur;
    unsigned short index;
} L14Key;

/* Steps the object by its state byte: 0 copies the six halfwords at +0x40 of its state into the
   state of every class-0xB19 entity of its group and calls func_L14_003E5030; 1 and 2 test
   func_002B3868 and call their handlers (the cases are in retail's block order, 0, 2, 1). Then,
   while the key word (+0x34) is set: when func_00282978 has run down the key counter (+0x14)
   the current key is reloaded from the key word and the key index of every class-0xB19 entity
   of the group is cleared; finally the current key is copied into each of them. Two pointers:
   the third walk has its own (one shared variable gives the other loops different registers). */
void func_L14_003E4BA0(unsigned char *self)
{
    unsigned char *state = *(unsigned char **)(self + 0x68);
    unsigned short *p;
    unsigned short *q;
    unsigned char *entity;

    switch (self[0x20]) {
    case 0:
        for (p = gGroupEntityLists[self[0x21]];
             self[0x21] != 0xFF && self[0x21] <= D_L14_001B25B8 && p != 0 &&
             ((p != 0 && (short)p[-1] >= 0) || p == gGroupEntityLists[self[0x21]]);
             p++) {
            entity = gMobyPool_L14 + ((*p & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (*(short *)(entity + 0xAA) == 0xB19 /* moby class 2841 */) {
                unsigned char *d = *(unsigned char **)(entity + 0x68);

                *(unsigned short *)(d + 0x40) = *(unsigned short *)(state + 0x40);
                *(unsigned short *)(d + 0x42) = *(unsigned short *)(state + 0x42);
                *(unsigned short *)(d + 0x44) = *(unsigned short *)(state + 0x44);
                *(unsigned short *)(d + 0x46) = *(unsigned short *)(state + 0x46);
                *(unsigned short *)(d + 0x48) = *(unsigned short *)(state + 0x48);
                *(unsigned short *)(d + 0x4A) = *(unsigned short *)(state + 0x4A);
            }
        }
        StoreObjectPositionAndLookupLinks((char *)self);
        break;
    case 2:
        if (SetFirstPendingFlag((char *)self) != 0) {
            SetChildFadeColors((char *)self);
            ClearLinkedMobyFlag((char *)self);
        }
        break;
    case 1:
        if (SetFirstPendingFlag((char *)self) != 0)
            SendColorsToLinkedMoby((char *)self);
        UpdateKeyframeSpanBlend((char *)self);
        break;
    }
    if (*(int *)(state + 0x34) != 0) {
        if (FastDecTimer((char *)(state + 0x14)) != 0) {
            *(unsigned short *)(state + 0x14) = *(unsigned short *)(state + 0x34);
            for (p = gGroupEntityLists[self[0x21]];
                 self[0x21] != 0xFF && self[0x21] <= D_L14_001B25B8 && p != 0 &&
                 ((p != 0 && (short)p[-1] >= 0) || p == gGroupEntityLists[self[0x21]]);
                 p++) {
                entity = gMobyPool_L14 + ((*p & 0x7FFF) << 8);
                if (entity == 0)
                    break;
                if (*(short *)(entity + 0xAA) == 0xB19 /* moby class 2841 */)
                    *(unsigned short *)(*(unsigned char **)(entity + 0x68) + 0x16) = 0;
            }
        }
        for (q = gGroupEntityLists[self[0x21]];
             self[0x21] != 0xFF && self[0x21] <= D_L14_001B25B8 && q != 0 &&
             ((q != 0 && (short)q[-1] >= 0) || q == gGroupEntityLists[self[0x21]]);
             q++) {
            entity = gMobyPool_L14 + ((*q & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (*(short *)(entity + 0xAA) == 0xB19 /* moby class 2841 */)
                ((L14Key *)*(unsigned char **)(entity + 0x68))->cur = ((L14Key *)state)->cur;
        }
    }
    AdvanceRingState((char *)self);
}

/* func_L14_003E4EA0 is matched in L14_003E4EA0-g8.c (built with -g). */

/* func_L14_003E5030 lives in the -g8 sibling file (it reaches a global through $gp). */

/* Keeps a ring of eight values up to date and picks state 1 or 2 depending on whether the current index is even or odd. */
void func_L14_003E50B8(char *moby)
{
    s16 *ring = *(s16 **)(moby + 0x68);
    while (ring[10] < ring[ring[11]]) {
        ring[11] = (ring[11] + 1) % 8;
    }
    if (((u16)ring[11] & 1) == 0) {
        if (*(u8 *)(moby + 0x20) != 1)
            func_321F58(moby, 1, -1);
    } else {
        if (*(u8 *)(moby + 0x20) != 2)
            func_321F58(moby, 2, -1);
    }
}

/* Clears the flag at +0x3C in the linked object. */
void func_L14_003E5190(char *moby) {
    char *link = *(char **)(moby + 0x68);
    link = *(char **)(link + 0x30);
    if (link != 0) {
        link = *(char **)(link + 0x68);
        *(int *)(link + 0x3C) = 0;
    }
}

/* Copies the two packed colour words and the key word into the linked object and turns its flag on. */
void func_L14_003E51B0(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *linked = *(char **)(vars + 0x30);

    if (linked != 0) {
        char *linkedVars = *(char **)(linked + 0x68);

        *(int *)(linkedVars + 0x48) = ((unsigned int)*(s16 *)(vars + 0x44) << 16)
                              | ((unsigned int)*(s16 *)(vars + 0x42) << 8)
                              | (unsigned int)*(s16 *)(vars + 0x40);
        *(int *)(linkedVars + 0x4C) = ((unsigned int)*(s16 *)(vars + 0x4A) << 16)
                              | ((unsigned int)*(s16 *)(vars + 0x48) << 8)
                              | (unsigned int)*(s16 *)(vars + 0x46);
        *(int *)(linkedVars + 0x3C) = 1;
        *(int *)(linkedVars + 0x34) = *(int *)(vars + 0x18);
    }
}

/* Sends fade values and colours to the two child objects when the current key index is odd. */
void func_L14_003E5218(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    short index = *(short *)(vars + 0x16);
    if ((short)(index % 2) == 1) {
        int startKey = ((short *)vars)[index];
        int endKey = ((short *)vars)[(index + 1) % 8];
        char *child;
        char *childVars;
        int greenBits;
        child = *(char **)(vars + 0x28);
        if (child) {
            childVars = *(char **)(child + 0x68);
            *(int *)(childVars + 0x14) = *(short *)(vars + 0x14) - startKey;
            *(int *)(childVars + 0x18) = startKey - endKey;
            greenBits = (*(short *)(vars + 0x42) << 8) | 0x80000000;
            *(int *)(childVars + 0x30) = *(int *)(childVars + 0x38) = (*(short *)(vars + 0x44) << 16) | greenBits | *(short *)(vars + 0x40);
            greenBits = (*(short *)(vars + 0x48) << 8) | 0x80000000;
            *(int *)(childVars + 0x34) = *(int *)(childVars + 0x3C) = (*(short *)(vars + 0x4A) << 16) | greenBits | *(short *)(vars + 0x46);
            *(float *)(childVars + 0xC) = 1.0f;
        }
        child = *(char **)(vars + 0x2C);
        if (child) {
            childVars = *(char **)(child + 0x68);
            *(int *)(childVars + 0x14) = *(short *)(vars + 0x14) - startKey;
            *(int *)(childVars + 0x18) = startKey - endKey;
            greenBits = (*(short *)(vars + 0x42) << 8) | 0x80000000;
            *(int *)(childVars + 0x30) = *(int *)(childVars + 0x38) = (*(short *)(vars + 0x44) << 16) | greenBits | *(short *)(vars + 0x40);
            greenBits = (*(short *)(vars + 0x48) << 8) | 0x80000000;
            *(int *)(childVars + 0x34) = *(int *)(childVars + 0x3C) = (*(short *)(vars + 0x4A) << 16) | greenBits | *(short *)(vars + 0x46);
            *(float *)(childVars + 0xC) = 1.0f;
        }
    }
}

extern void func_L00_002E54E0(float);
extern int func_002B38B8(char *);
extern void func_L00_002E6EF8(void (*f)(char *), char *arg);
extern float func_002A7878(float, float);
extern void func_L14_003F0E68(char *);

/* Scrolls two texture offsets that wrap at 8.0, and runs a draw call each frame while the effect is on. */
void func_L14_003F0D50(char *moby) {
    char *self = moby;
    char *vars = *(char **)(moby + 0x68);

    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(int *)(vars + 0x10) = 1;
        SetClampedViewDistance(2048.0f);
        *(unsigned char *)(moby + 0x20) = 1;
    }
    *(float *)(vars + 0x0) = *(float *)(vars + 0x0) + *(float *)(vars + 0x4);
    *(float *)(vars + 0x8) = *(float *)(vars + 0x8) + *(float *)(vars + 0xC);
    if (*(float *)(vars + 0x0) >= 8.0f) {
        *(float *)(vars + 0x0) = *(float *)(vars + 0x0) - 8.0f;
    }
    if (*(float *)(vars + 0x8) >= 8.0f) {
        *(float *)(vars + 0x8) = *(float *)(vars + 0x8) - 8.0f;
    }
    if (IsThirdPendingFlagSet(self) != 0) {
        *(int *)(vars + 0x10) = 0;
    }
    if (*(int *)(vars + 0x10) != 0) {
        AddDrawCallbackToList3(BindObjectToSmallDataWords, self);
    }
    *(float *)(vars + 0x4) = RandomFloatRange(0.003f, 0.005f);
    *(float *)(vars + 0xC) = RandomFloatRange(0.001f, 0.0025f);
}

/* Resets the record: the four axis pairs, the flags and the packed word. */
void func_L14_003F0E98(char *record)
{
    *(long long *)(record + 0x70) = 0LL;
    *(int *)(record + 0x50) = 0;
    *(int *)(record + 0x54) = 0;
    *(float *)(record + 0x58) = 1.0f;
    *(int *)(record + 0x5C) = 0;
    *(int *)(record + 0x60) = 0;
    *(float *)(record + 0x64) = 1.0f;
    *(float *)(record + 0x68) = 1.0f;
    *(float *)(record + 0x6C) = 1.0f;
    *(float *)(record + 0x8) = -4.0f;
    *(float *)(record + 0x18) = 4.0f;
    *(float *)(record + 0x4) = -2.0f;
    *(float *)(record + 0x24) = 2.0f;
    *(int *)(record + 0x0) = 0;
    *(int *)(record + 0x10) = 0;
    *(int *)(record + 0x20) = 0;
    *(int *)(record + 0x30) = 0;
    *(float *)(record + 0xC) = 1.0f;
    *(float *)(record + 0x1C) = 1.0f;
    *(float *)(record + 0x2C) = 1.0f;
    *(long long *)(record + 0x80) = 280993940374112LL;
    *(float *)(record + 0x28) = -4.0f;
    *(float *)(record + 0x38) = 4.0f;
    *(float *)(record + 0x14) = -2.0f;
    *(float *)(record + 0x34) = 2.0f;
    *(float *)(record + 0x3C) = 1.0f;
}

/* func_L14_003F0F38 lives in the -g8 sibling file (it reaches a global through $gp). */
