#include "include_asm.h"
#include "common.h"

typedef struct { float rows[4][4]; } TodanoMatrix;
extern TodanoMatrix D_L12_001AEE40 __attribute__((sda));
/* The initialization uses GP addressing; updates use absolute field addresses. */
extern TodanoMatrix matrixGP SDATA(D_L12_001AEE40);
extern unsigned char D_00189EA0[];
extern int D_L12_001B363C __attribute__((sda));
extern int D_L12_001B29C8[] __attribute__((sda));
extern float D_L12_001B3640[4] __attribute__((aligned(16), sda));
extern float D_L12_001AEF4C SDATA(D_L12_001AEF4C);
extern float D_L12_001AEF50 SDATA(D_L12_001AEF50);
extern void func_L12_00389988(void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern float func_00282E80(void *, void *);

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
extern int D_L12_001AC810 __attribute__((sda));
extern int D_L12_001B3630 __attribute__((sda)), D_L12_001B3638 __attribute__((sda));
extern Collision D_L12_001C0240;
extern Material D_L12_002636F0[];
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


extern char *D_L12_001BDB00;

extern float D_L12_001AD230;

extern float D_L12_001AD234;

/* func_L12_002CF7B0 is in the sibling file L12_002CF7B0-decider.c (its own profile). */

/* func_L12_002FFF88 is in the sibling file L12_002CF7B0-g8.c: it reads a
   small-data global through $gp. */

/* func_L12_00300410 is in the sibling file L12_00300410-g8.c. */

/* func_L12_0035A838 is defined in L12_0035A838-g8.c (it reads its list through $gp). */

/* func_L12_00388038 is in the sibling file L12_002CF7B0-g8.c: its body
   reads a small-data global through $gp. */

/* func_L12_00388090 is defined in L12_00388090-flags-g8.c. */

/* func_L12_00389988 is defined in L12_00389988-g64.c. */

/* Moby class 4944 update. Slowly shifts four wave offsets back and forth so the water surface
   drawing ripples, and drops the drawing when the hero gets close. */
void func_L12_00389BC0(unsigned char *object)
{
    float *state = *(float **)(object + 0x68);
    float waveA, waveB, waveC, waveD;
    int rowsLeft, stateId = object[0x20];
    float *corner;
    switch (stateId) {
    case 0:
        state[0] = 0.0f;
        state[1] = 0.25f;
        state[2] = 0.5f;
        state[3] = 0.75f;
        state[8] = 1.0f;
        state[9] = 1.25f;
        state[10] = 1.5f;
        state[11] = 1.75f;
        object[0x20] = 1;
        object[0x30] = 255;
        if (matrixGP.rows[0][0] > 1000.0f) {
            corner = matrixGP.rows[0];
            rowsLeft = 3;
            do {
                float x = corner[0] * 0.01f;
                float y = corner[1] * 0.01f;
                float z = corner[2] * 0.01f;
                corner[0] = x;
                corner[1] = y;
                corner[2] = z;
                corner += 4;
            } while (--rowsLeft >= 0);
        }
        break;
    case 1:
        AddDrawCallbackToList1(DrawWaterWaveStrips, object);
        D_L12_001B363C = stateId;
        qcopy(D_L12_001B3640, gHeroPosition);
        *(short *)(gHeroPosition + 0x17E) = 5;
        D_L12_001B3640[3] = 48.0f;
        D_L12_001B3640[2] = FastSinOrCosB((float)(D_L12_001B29C8[0] % 360) * 0.01744444482028484344482421875f - 3.14f) * 0.25f + 59.5f;
        state[4] += state[5];
        if (state[4] >= 8.0f) state[4] -= 8.0f;
        waveA = FastSinOrCosB(state[0] * 3.141590118408203125f) * 0.01f;
        waveB = FastSinOrCosB(state[1] * 3.141590118408203125f) * 0.025f;
        waveC = FastSinOrCosB(state[2] * 3.141590118408203125f) * 0.01f;
        waveD = FastSinOrCosB(state[3] * 3.141590118408203125f) * 0.025f;
        D_L12_001AEE40.rows[0][2] += waveA;
        D_L12_001AEE40.rows[1][2] += waveB;
        D_L12_001AEE40.rows[2][2] += waveC;
        D_L12_001AEE40.rows[3][2] += waveD;
        state[0] += 0.01f;
        state[1] += 0.01f;
        state[2] += 0.01f;
        state[3] += 0.01f;
        if (state[0] > 2.0f) state[0] = 0.0f;
        if (state[1] > 2.0f) state[1] = 0.0f;
        if (state[2] > 2.0f) state[2] = 0.0f;
        if (state[3] > 2.0f) state[3] = 0.0f;
        state[5] = RandomFloatRange(D_L12_001AEF4C, D_L12_001AEF50);
        break;
    case 2:
        if (vec_distance_xy(object + 0x10, gHeroPosition) < 64.0f)
            AddDrawCallbackToList3(DrawWaterWaveStrips, object);
        break;
    }
}


/* func_L12_00389F80 uses small data in L12_002CF7B0-g8.c. */

/* Moves a falling spark one step, checks what it hits, and sprays small bits when it lands. */
void func_L12_00393458(unsigned char *obj) {
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
    int i, life;
    float dirAngle, dirSpeed;

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
        ((Material *)((u32)D_L12_002636F0 + gItemSlotToRecord[12] * sizeof(Material)))->material;
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
            RippleDisturb(D_L12_001B3630, D_L12_001B3638, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            ClearVector128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = D_L12_001C0240.point.f[2];
            effect = SpawnScaledEffectMoby(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                dirAngle = RandomAngle();
                dirSpeed = RandomFloatRange(0.0f, 0.050000004f);
                frame.spread.f[0] = FastSinOrCosA(dirAngle) * dirSpeed;
                frame.spread.f[1] = FastSinOrCosB(dirAngle) * dirSpeed;
                frame.spread.f[2] = RandomFloatRange(0.050000004f, 0.10833334f);
                life = RandomIntRange(90, 120);
                SpawnSparkParticle_002BFB38(&frame.position, spread, RandomIntBelow(2), life);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &D_L12_001C0240;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = &D_L12_001C0240;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L12_001AC810 && *(short *)(model + 0xAA) != 0x336)
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



/* Moves a thrown shard one step and blows it up or bounces it when it hits something. */
void func_L12_00393870(char *obj) {
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
    char *hitMoby;
    Collision *hitInfo;

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
    frame.packet.material = (D_00139574 + D_L12_002636F0)->material;
    qcopy(&frame.packet.vector, vars);
    FastVectorNormalizeHelper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        hitInfo = &D_L12_001C0240;
        hitMoby = hitInfo->hit;
        if (hitMoby) {
            Collision *reread;
            char *model;
            if ((hitMoby == gHeroMoby_0018C0B0 || *(short *)(hitMoby + 0xAA) == 0xC0) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = &D_L12_001C0240;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L12_001AC810 && *(short *)(model + 0xAA) != 0x336)
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
            hitInfo = &D_L12_001C0240;
            if (hitInfo->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &hitInfo->point);
            FastVectorNormalize(&frame.velocity, vars, &hitInfo->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &hitInfo->normal, 1.0f);
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
