#include "include_asm.h"
#include "common.h"

extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038E880(void *, void *, void *);
extern void func_L00_0038F3D8(void *);

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L26_001AC810 __attribute__((sda));
extern int D_L26_001B23B0 __attribute__((sda)), D_L26_001B23B8 __attribute__((sda));
extern Collision D_L26_001BEFC0;
extern Material D_L26_002622F0[];
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

extern void func_00282CC0(char *, char *, char *);



extern void func_002EE358(void *, void *, void *);
extern void func_00324530(void *, void *, void *, void *);
extern float func_002EE9C8(float, float);

extern void func_002EE5F0(void *, void *, float);
extern void func_002EE440(void *, void *, void *);



/* The hero record of L26_002FC8D8-g64.c; its part list at +0x18C holds `count` objects. */
typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap38[0x44 - 0x38];
    short count;
    char gap46[0x18C - 0x46];
    char *parts[0];
} Hero;
extern Hero D_L26_001BC880;
typedef struct { char pad[0x34]; unsigned short flags; char gap[0xAA - 0x36]; short id; } Object;
extern int D_001A79F0[] __attribute__((sda));
extern float D_L26_001A9450[][4] SDATA(D_L26_001A9450);
/* Min/max pairs: the first three lower bounds are read through $gp, every other bound absolute.
   The upper bounds are the second words of their pairs ([1]); the offset form keeps those absolute
   macro loads out of call delay slots, as in retail. */
extern float D_L26_001A9420[] __attribute__((sda));
extern float D_L26_001A9420_gp SDATA(D_L26_001A9420);
extern unsigned int D_L26_001A9428[] __attribute__((sda));
extern unsigned int D_L26_001A9428_gp SDATA(D_L26_001A9428);
extern int D_L26_001A9430[] __attribute__((sda));
extern int D_L26_001A9430_gp SDATA(D_L26_001A9430);
extern int D_L26_001A9438[] __attribute__((sda));
extern int D_L26_001A9440[] __attribute__((sda));
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(char *, float *, int, int, float);
extern void func_0029FC20(char *, int, char *);
extern void func_002830C0(void *, void *, void *);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern char *func_002BAA28(void *, void *, void *, unsigned int, unsigned int, int, int, int, int);
extern int func_00283CF0(float);

/* Walks the hero's part objects (sets flag 0x800 on id 0xE29, calls func_002E64A0 for id 0xD54,
   passes id 4000 objects with private data to func_L00_00326048) and, while D_001A79F0 is 26, the
   hero mode is 0 and its timer below 260, emits eight particles from part 3's transform with
   ranged colour, kind, duration and size. */
void func_L26_002FCCC0(void) {
    Vec transform[4];
    Vec position;
    Vec velocity;
    Vec acceleration;
    Hero *hero;
    char **slot;
    char *object;
    char *effect;
    unsigned int color;
    int kind;
    int duration;
    int size;
    int i;
    int j;
    int flags = -1;
    StartStartupAnimations();
    for (i = 0; i < D_L26_001BC880.count; i++) {
        hero = &D_L26_001BC880;
        slot = &hero->parts[i];
        object = *slot;
        if (object && ((Object *)object)->id == 0xE29 /* moby class 3625 */) {
            ((Object *)object)->flags |= 0x800;
        }
        if (((Object *)object)->id == 0xD54 /* moby class 3412 */) UpdateEquipmentPieces(object);
        if (object && *(short *)(object + 0xAA) == 4000 /* TV Screens */ && *(char **)(object + 0x68))
            StoreAngleUpdateResult(object, (float *)(*(char **)(object + 0x68) + 0xC),
                              (int)0x80AAAAD2, (int)0x80396464, 0.061086535f);
    }
    if (gCurrentMapIndex[0] == 26 && D_L26_001BC880.mode == 0 && D_L26_001BC880.timer < 260) {
        object = D_L26_001BC880.parts[3];
        TransformMobyJointPoint(object, 0, (char *)transform);
        object += 0x10;
        qcopy((transform + 3), object);
        for (j = 0; j < 8; j++) {
            transform_vector(&position, D_L26_001A9450[j & 1], transform);
            vec_scale_to_length(&velocity, transform, 0.06666667f);
            velocity.f[3] = D_L26_001A9420_gp;
            qzero_nc(&acceleration);
            acceleration.f[3] = D_L26_001A9420[1];
            color = FastTweenColor(D_L26_001A9428_gp, D_L26_001A9428[1], RandomFloatRange(0.0f, 1.0f));
            {
                unsigned int rgb = color & 0xFFFFFF;
                kind = RandomIntRange(D_L26_001A9430_gp, D_L26_001A9430[1]);
                duration = RandomIntRange(D_L26_001A9438[0], D_L26_001A9438[1]);
                size = RandomIntRange(D_L26_001A9440[0], D_L26_001A9440[1]);
                effect = SpawnTrailParticle_002BAA28(&position, &velocity, &acceleration, color, rgb,
                                       kind, duration, size, flags);
                if (effect) effect[9] = FloatToInt(2.0f) - 16;
            }
        }
    }
}

/* Samples the record's plane at its own position and returns the resident height. */
float func_L26_00324598(u8 *moby, void *planeIn, void *planeOut) {
    float sample[4];

    func_002EE358(sample, planeIn, moby + 0x10);
    func_00324530(moby, sample, sample, planeOut);
    return func_002EE9C8(sample[0], sample[1]);
}

/* Scales the three vertices of the record's triangle, ordering the middle pair
   by the caller's flag. */
void func_L26_00324DE8(u8 *tri, int swapOrder) {
    func_002EE5F0(tri, tri, 1.0f);
    if (swapOrder != 0)
        func_002EE440(tri + 0x10, tri + 0x20, tri);
    else
        func_002EE440(tri + 0x10, tri, tri + 0x20);
    func_002EE5F0(tri + 0x10, tri + 0x10, 1.0f);
    func_002EE440(tri + 0x20, tri + 0x10, tri);
}

/* func_L26_003547D8 is defined in L26_003547D8-g8.c (it reads its list through $gp). */

/* Per-frame update for a thrown projectile: it moves along its velocity with gravity, checks what
   it hits, and on impact bounces or bursts into a spray of sparks. */
void func_L26_0038BB28(unsigned char *moby) {
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
        ((Material *)((u32)D_L26_002622F0 + gItemSlotToRecord[12] * sizeof(Material)))->material;
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
            RippleDisturb(D_L26_001B23B0, D_L26_001B23B8, 1,
                *(float *)(moby + 0x10), *(float *)(moby + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            ClearVector128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(moby + 0x10);
            frame.position.f[1] = *(float *)(moby + 0x14);
            frame.position.f[2] = D_L26_001BEFC0.point.f[2];
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
            Collision *collision = &D_L26_001BEFC0;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = &D_L26_001BEFC0;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L26_001AC810 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
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

/* Per-frame update for a second kind of projectile: it moves, counts its age, and when it hits
   something it bounces, then takes the normal or the stronger impact response depending on age. */
void func_L26_0038BF40(char *moby) {
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
    frame.packet.material = (D_00139574 + D_L26_002622F0)->material;
    qcopy(&frame.packet.vector, vars);
    FastVectorNormalizeHelper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(moby + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, moby, &frame.packet)) {
        collision = &D_L26_001BEFC0;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = &D_L26_001BEFC0;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L26_001AC810 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
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
            collision = &D_L26_001BEFC0;
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




/* func_L26_003D4590 is defined in L26_003D4590-g8.c (it reaches data through $gp and needs -frac2-zero-ti-por). */

/* func_L26_003D4930 is matched in L26_003D4930-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L26_003D4AE8 is defined in L26_002EC840-g8.c (it reads the group count and a word through $gp). */

/* func_L26_003DB818 is defined in L26_003DB818-g8.c. */

/* func_L26_003DBE18 is defined in L26_002EC840-g8.c (it reads tuning words through $gp). */

extern int func_00282978(short *);
extern void func_00325DA0(void *, void *);
extern float func_00283B98(float, float);
extern void func_00325C50(float, void *, void *, int, void *);
extern char D_L26_001A8F20[];



/* func_L26_003DC128 lives in the -g8 sibling file (it reaches a global through $gp). */

/* func_L26_003DF7E8 is defined in L26_003DF7E8-g32.c (its tables are read through $gp). */


/* Implemented in L26_002EC840-0040C8A8.c. */

