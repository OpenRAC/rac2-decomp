#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038E880(void *, void *, void *);
extern void func_L00_0038F3D8(void *);
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L24_001AC790 __attribute__((sda));
extern int D_L24_001B1F30 __attribute__((sda)), D_L24_001B1F38 __attribute__((sda));
extern Collision D_L24_001BEB00;
extern Material D_L24_00261E70[];
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




/* Moves a bouncing projectile one step, bursts it into sparks on a first floor hit, and bounces it off walls. */
void func_L24_00383818(unsigned char *moby) {
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
        ((Material *)((u32)D_L24_00261E70 + gItemSlotToRecord[12] * sizeof(Material)))->material;
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
            RippleDisturb(D_L24_001B1F30, D_L24_001B1F38, 1,
                *(float *)(moby + 0x10), *(float *)(moby + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            ClearVector128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(moby + 0x10);
            frame.position.f[1] = *(float *)(moby + 0x14);
            frame.position.f[2] = D_L24_001BEB00.point.f[2];
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
            Collision *collision = &D_L24_001BEB00;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = &D_L24_001BEB00;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L24_001AC790 && *(short *)(model + 0xAA) != 0x336)
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


/* Moves a projectile one step and bounces it off what it hits, using a stronger blast once it has bounced enough. */
void func_L24_00383C30(char *moby) {
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
    frame.packet.material = (D_00139574 + D_L24_00261E70)->material;
    qcopy(&frame.packet.vector, vars);
    FastVectorNormalizeHelper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(moby + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, moby, &frame.packet)) {
        collision = &D_L24_001BEB00;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = &D_L24_001BEB00;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L24_001AC790 && *(short *)(model + 0xAA) != 0x336)
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
            collision = &D_L24_001BEB00;
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



