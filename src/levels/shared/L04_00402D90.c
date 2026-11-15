#include "common.h"

extern void func_002A7398(void *, int, int);
extern char D_00189EA0[];
extern unsigned char *D_L04_001B24E8 __attribute__((sda));

extern signed char *D_L04_001B24DC __attribute__((sda));
extern void func_L04_0040E248(int, unsigned char *);
extern float func_0033BBE0(void);
extern float func_0033BB78(float, float);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
/* Integer and float arguments keep their order within each EE register bank. */
extern void func_002C2210(void *, int, unsigned int, int, int, void *, float, float, float, int);

extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern unsigned char *D_L04_001FE340[];
extern float func_00282E48(void *, void *);
extern int D_L04_001B2008[] __attribute__((sda));
extern int D_00138320;
extern float D_L04_001BDC30;
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_002AA2E8(void *, float, float);
extern int func_00282948(void *);
extern int func_002829A8(void *);
extern void func_L00_00322BE0(void *, int);
extern void func_L00_00322A98(void *, void *);
extern void func_L00_00322AC0(void *, float, int, int);
extern void func_L00_00322EC8(void *);
extern int func_002E5DA0(int, int, void *, int);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern int func_L01_00355BA0(int, int);
extern void func_0027AB40(void);
extern int func_002A8600(void *, int, int, int);
extern int func_002A86E8(void *, void *, int, int);
extern void func_00283388(void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
typedef struct {
    unsigned char pad[0x1a8];
    int primary;
    int branches[4];
    int links[4];
    int parents[4];
} L04PathState;


/* Frozen Batch A A04-table-select-76; acknowledged claim 8c4d82cfbf43e138ed35e757fdaeee3e7c4651fa684549ba9d5e8ac22c56d111. */
typedef unsigned char BatchA_A04_u8;

typedef unsigned int BatchA_A04_u32;

extern BatchA_A04_u32 D_001A79F0[] __attribute__((sda));

extern BatchA_A04_u8 D_001395B8[];

extern void func_L00_002ECFE8(void *a0, void *a1, int a2, unsigned int a3,
                              float f12, float f13, float f14, int t0, int t1);

/* Steps the record's phase at +0x1FC down by 0.1 (wrapping up by 8 once it reaches -8) and
   draws the effect with it. */
void func_L04_00404068(void *moby) {
    char *vars = *(char **)((char *)moby + 0x68);

    *(float *)(vars + 0x1FC) -= 0.1f;
    if (*(float *)(vars + 0x1FC) <= -8.0f)
        *(float *)(vars + 0x1FC) += 8.0f;
    DrawOrientedQuadsAtPoints(moby, vars + 0x200, 3, 0x60005AFF, 0.08f, 0.45f, *(float *)(vars + 0x1FC), 0xFF,
                      0x17);
}

typedef unsigned int B781AimQuad __attribute__((mode(TI)));
extern float func_00282C48(float);
extern void func_002AA898(void *, void *, float, float, float, float, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A05A8(void *);
extern void func_002A0F48(void *);
extern void *func_L04_003E5E40(void *, int, float);
extern int func_L04_00343498(void *, float);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L04_00404068(void *);
extern void func_L00_0033E220(void *, void *, unsigned int, float, int, int, float, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern void func_L04_00416390(void *, void *, void *, float);
/* Animates the racer bike each frame: leans it into turns, keeps its child effect object in place and starts the spark effects when it is close to its target. */
void func_L04_00404100(unsigned char *moby, unsigned char *vars)
{
    float point[4];
    float end[4];
    float total = *(float *)(vars + 0x138) + *(float *)(vars + 0x13c);
    float a, b, c, angle, factor;
    if (total < 0.083333336f) total = 0.083333336f;
    a = *(float *)(vars + 0x130) * 13.750985f;
    b = total * 2.7088037f;
    c = *(float *)(vars + 0x130) * 28.647884f;
    a = a * FloatAbs(a);
    c = 1.0f - (1.0f - c) * (1.0f - c);
    if (b > 1.0f) b = 1.0f;
    if (*(float *)(vars + 0x1f4) != 0.0f) {
        if (FloatAbs(*(float *)(moby + 0xf0) - *(float *)(vars + 0x1f4)) < 0.003f) *(float *)(vars + 0x1f4) = 0.0f;
        factor = *(float *)(vars + 0x1f8);
        angle = *(float *)(vars + 0x1f4);
    } else {
        factor = 1.0f;
        angle = (factor - b) * a + b * c;
        if (angle > factor) angle = factor;
        if (angle < -1.0f) angle = -1.0f;
        angle *= -0.52359885f;
    }
    ApproachWithVelocity(moby + 0xf0, vars + 0x128, angle, factor * 0.035f, 0.45f, factor * 0.027634384f, 0);
    if (*(unsigned char **)(vars + 0x8c)) {
        unsigned char *child = *(unsigned char **)(vars + 0x8c);
        if ((child[0x60] & 2) && child[0x42]) StartAnimationBlended(child, 0, 0, 3);
        *(short *)(*(unsigned char **)(vars + 0x8c) + 0x32) = 30;
        (*(unsigned char **)(vars + 0x8c))[0x31] = 1;
        *(B781AimQuad *)(*(unsigned char **)(vars + 0x8c) + 0x10) = *(B781AimQuad *)(moby + 0x10);
        *(B781AimQuad *)(*(unsigned char **)(vars + 0x8c) + 0xf0) = *(B781AimQuad *)(moby + 0xf0);
        (*(unsigned char **)(vars + 0x8c))[0x30] = 0;
        func_002A05A8(*(void **)(vars + 0x8c));
        func_002A0F48(*(void **)(vars + 0x8c));
        *(unsigned short *)(*(unsigned char **)(vars + 0x8c) + 0x34) |= 6;
    } else *(void **)(vars + 0x8c) = SpawnMobyAtParentPose(moby, 0x8ef /* Enemy Hoverbike Racer */, 0.25f);
    if ((*(unsigned char **)(vars + 0x164))[0xbc] == 5) {
        if (ApplyScaledValueToVector(moby, 20.0f) != -1) {
            AddDrawCallbackToList3(AnimateBoostFlameStreak, moby);
            SpawnObjectFollowingEffect(vars + 0x200, moby, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
            SpawnObjectFollowingEffect(vars + 0x210, moby, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
            SpawnObjectFollowingEffect(vars + 0x220, moby, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
        }
    }
    if (*(int *)(vars + 0x244)) {
        FastVecSub(point, *(unsigned char **)(vars + 0x164) + 0x10, moby + 0x10);
        if (func_L00_002EE290(point) < 100.0f) {
            *(B781AimQuad *)(point) = *(B781AimQuad *)(moby + 0x10);
            point[2] -= 0.25f;
            *(B781AimQuad *)(end) = *(B781AimQuad *)(moby + 0x10);
            EmitTrailEffects(moby, end, vars + 0xd0, *(float *)(vars + 0x138) + *(float *)(vars + 0x13c));
        }
    }
}


/* func_L04_004045E0 is in L04_00402D90-follower.c. */

/* func_L04_00407078 is in L04_00402D90-debris.c. */

/* func_L04_004073E8 is in L04_00402D90-trail.c. */

extern int func_00282978(void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00283028(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern void func_002833F0(void *, void *);
extern void func_L00_003200F8(void *, void *, float, float, int);
extern void func_0032C700(void *, float, float, int, int, int, int, int, int, int, int, int, int, int);
extern void func_0029F338(void *);
extern int func_00277258(void *, int, float, void *);
extern void func_002AB668(void *, void *, float);
extern void func_002839D0(void *, void *);
extern void func_002AB6D8(void *, void *);
extern float D_L04_001BFB00[];
extern void func_L04_004073E8(void *);

/* Moves a flying debris piece, bounces it off the ground and removes it when its timer runs out. */
void func_L04_004077A0(unsigned char *moby)
{
    float oldpoint[4];
    float rot[12];
    float point[4];
    float delta[4];
    float probe[4];
    float matrix[16];
    float bounce[4];
    float axis[4];
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float speed, dot;
    float radius;
    *(unsigned short *)(vars + 0x32) += 1;
    switch (moby[0x20]) {
    case 1:
        if (FastDecTimer(vars + 0x30)) {
            moby[0x20] = (*(int *)(vars + 0x34) & 1) ? 3 : 2;
            *(short *)(vars + 0x30) = FloatToInt(10.0f);
            return;
        }
        if (*(int *)(vars + 0x34) & 4) AddDrawCallbackToList3(DrawRacerTrail, moby);
        break;
    case 2:
        matrix_mul_vec3(oldpoint, vars + 0x20, moby + 0xc0);
        FastVecAdd(oldpoint, oldpoint, moby + 0x10);
        if (*(int *)(vars + 0x34) & 2) SpawnExplosionBurst_L00(moby, oldpoint, 0.3f, 10.0f, -1);
        else SpawnExplosion(moby + 0x10, 0.5f, 0.0f, 0, 25, 20, 20, 20, 45, 0, 0, 0, 0, 0);
        goto destroy;
    case 3:
        if (FastDecTimer(vars + 0x30)) {
        case 0:
        destroy:
            MarkMobySpawned(moby);
            return;
        }
        moby[0x23] = FloatToInt((float)*(short *)(vars + 0x30) * 12.8f);
        break;
    }
    euler_rotation_basis(rot, vars + 0x10);
    matrix_mul_vec3(oldpoint, vars + 0x20, moby + 0xc0);
    multiply_matrix3x3(moby + 0xc0, rot, moby + 0xc0);
    matrix_mul_vec3(point, vars + 0x20, moby + 0xc0);
    FastVecSub(delta, point, oldpoint);
    FastVecSub(moby + 0x10, moby + 0x10, delta);
    FastVecAdd(moby + 0x10, moby + 0x10, vars);
    *(float *)(vars + 8) -= *(float *)(vars + 0x38);
    radius = *(float *)(vars + 0x2c);
    matrix_mul_vec3(probe, vars + 0x20, moby + 0xc0);
    FastVecAdd(probe, probe, moby + 0x10);
    if (TestPointAgainstCollision(probe, 0, radius, moby)) {
        vec_scale_to_length(D_L04_001BFB00, D_L04_001BFB00, 1.0f);
        speed = FastVecLength(vars);
        dot = FastVecDot(vars, D_L04_001BFB00);
        if (dot < 0.0f) {
            FastVectorNormalize(vars, vars, D_L04_001BFB00);
            vec_scale_to_length(bounce, D_L04_001BFB00, dot * 0.5f);
            FastVecAdd(vars, vars, bounce);
            vec_scale_to_length(vars, vars, speed);
            FastVecCross(axis, D_L04_001BFB00, vars);
            vec_scale_to_length(axis, axis, 1.0f);
            BuildAxisAngleQuaternion(axis, axis, FastVecLength(vars + 0x10));
            RotationToMatrix(axis, matrix);
            GetEulerAnglesFromMatrix(matrix, vars + 0x10);
            if (*(short *)(vars + 0x32) >= 16) *(short *)(vars + 0x30) = 0;
        }
    }
}




/* A04-table-select-76 freshly exact-verified under family reservation */
/* Gets how many times the player has won the current course (the table depends on the level). */
BatchA_A04_u32 func_L04_0040A1D0(BatchA_A04_u8 *courseIndex) {
    BatchA_A04_u32 level = gCurrentMapIndex[0];
    BatchA_A04_u32 count = 0;
    if (level == 4) count = D_001395B8[(BatchA_A04_u32)courseIndex + 0x4D];
    else if (level == 0xB) count = D_001395B8[(BatchA_A04_u32)courseIndex + 0x57];
    return count;
}

/* A04-table-select family, incrementing form: bumps the state-selected byte */
/* Adds one to the number of wins stored for this course. */
void func_L04_0040A220(BatchA_A04_u8 *courseIndex)
{
    BatchA_A04_u32 level = gCurrentMapIndex[0];

    if (level == 4) D_001395B8[(BatchA_A04_u32)courseIndex + 0x4D]++;
    else if (level == 0xB) D_001395B8[(BatchA_A04_u32)courseIndex + 0x57]++;
}

/* shared native body of family A04-table-select: reads the state-selected byte */
/* Gets how many times the player finished this course without winning. */
unsigned int func_L04_0040A268(unsigned char *courseIndex)
{
    unsigned int level = gCurrentMapIndex[0];
    unsigned int count = 0;

    if (level == 4) count = D_001395B8[(unsigned int)courseIndex + 0x52];
    else if (level == 0xB) count = D_001395B8[(unsigned int)courseIndex + 0x5C];
    return count;
}

/* A04-table-select family, incrementing form (second slot pair) */
/* Adds one to the number of non-winning finishes stored for this course. */
void func_L04_0040A2B8(BatchA_A04_u8 *courseIndex)
{
    BatchA_A04_u32 level = gCurrentMapIndex[0];

    if (level == 4) D_001395B8[(BatchA_A04_u32)courseIndex + 0x52]++;
    else if (level == 0xB) D_001395B8[(BatchA_A04_u32)courseIndex + 0x5C]++;
}

extern BatchA_A04_u8 *D_001B26F0 __attribute__((sda));

extern void func_002B9180(void *);

/* Sweeps the 0x800 packed 64-byte records, redrawing the four live kinds */
/* Goes through all the effect records and refreshes the ones of four active kinds. */
void func_L04_0040A310(void)
{
    int i;

    for (i = 0; i < 0x800; i++) {
        BatchA_A04_u8 kind = *(BatchA_A04_u8 *)((i << 6) + (BatchA_A04_u32)D_001B26F0);

        if (kind == 0x4A || kind == 8 || kind == 0xB || kind == 0xF) {
            KillParticle(D_001B26F0 + (i << 6));
        }
    }
}

/* Resets a racer to its starting state and removes leftover effect objects. When keep is set, the race progress is kept. */
void func_L04_0040A3B8(unsigned char *moby, int keep)
{
    unsigned char *vars = *(unsigned char **)(moby + 0x68), *otherMoby;
    unsigned char *linkedRacer;
    qzero(vars + 0x2b0);
    *(float *)(vars + 0x2b8) = 1.0f;
    qzero(vars + 0x290);
    qzero(vars + 0x2a0);
    qzero(vars + 0x2c0);
    qzero(vars + 0x6c0);
    *(B781AimQuad *)(moby + 0x10) = *(B781AimQuad *)gHeroPosition;
    *(int *)(vars + 0x76c) = 0;
    *(int *)(vars + 0x718) = 0;
    *(short *)(vars + 0x274) = 0;
    vars[0x349] = 0;
    *(int *)(vars + 0x34c) = 0;
    *(int *)(vars + 0x354) = 0;
    *(int *)(vars + 0x358) = 0;
    *(int *)(vars + 0x278) = 0;
    *(int *)(vars + 0x27c) = 0;
    *(int *)(vars + 0x300) = 0;
    *(int *)(vars + 0x304) = 0;
    *(int *)(vars + 0x308) = 0;
    *(int *)(vars + 0x30c) = 0;
    *(int *)(vars + 0x280) = 0;
    *(int *)(vars + 0x288) = 0;
    *(int *)(vars + 0x750) = 0;
    *(int *)(vars + 0x738) = 0;
    *(int *)(vars + 0x724) = 0;
    *(float *)(vars + 0x28c) = 90.0f;
    ReleaseRacerSoundHandles((int)moby, vars);
    linkedRacer = (unsigned char *)gMobyPool_L04 + (*(int *)(vars + 0x1dc) << 8);
    *(int *)(vars + 0x3a8) = 10;
    *(int *)(vars + 0x328) = -1;
    *(int *)(vars + 0x330) = -1;
    *(int *)(vars + 0x334) = -1;
    *(int *)(vars + 0x3bc) = -1;
    *(int *)(vars + 0x714) = -1;
    *(int *)(vars + 0x324) = 0;
    *(int *)(vars + 0x32c) = 0;
    *(int *)(vars + 0x33c) = 0;
    *(int *)(vars + 0x338) = 0;
    *(int *)(vars + 0x38c) = 0;
    *(int *)(vars + 0x390) = 0;
    *(int *)(vars + 0x4c4) = 0;
    *(int *)(vars + 0x3b0) = 0;
    *(int *)(vars + 0x3ac) = 0;
    *(int *)(vars + 0x3b4) = 0;
    *(int *)(vars + 0x360) = 0;
    *(int *)(vars + 0x364) = 0;
    *(int *)(vars + 0x368) = 0;
    *(int *)(vars + 0x4d8) = 0;
    *(int *)(vars + 0x4dc) = 0;
    if (linkedRacer) StartAnimationImmediate(linkedRacer, 0, 0);
    *(short *)(vars + 0x34a) = -1;
    *(int *)(vars + 0x36c) = 0;
    /* This cleared vector has no scalar consumers in the surrounding resets. */
    qzero_nc(vars + 0x2f0);
    *(int *)(vars + 0x64c) = 0;
    *(int *)(vars + 0x70c) = 0;
    if (!keep) {
        *(int *)(vars + 0x3a4) = 0;
        *(int *)(vars + 0x314) = -1;
        *(int *)(vars + 0x3b8) = 0;
        *(int *)(vars + 0x310) = 0;
        *(int *)(vars + 0x318) = 0;
    }
    for (otherMoby = D_L04_001B24E8; otherMoby; otherMoby = *(unsigned char **)(otherMoby + 0x28)) {
        unsigned short type = *(unsigned short *)(otherMoby + 0xaa);
        if ((unsigned int)(type - 0xb3d /* moby classes 2877-2880 */) < 4 || (short)type == 0x27f /* moby class 639 */ ||
            (short)type == 0x70 /* moby class 112 */ || (short)type == 0x7a /* moby class 122 */) {
            MarkMobySpawned(otherMoby);
        }
    }
    *(int *)(vars + 0x388) = 0;
}



/* func_L04_0040A628 is in L04_00402D90-racers-g8.c. */

/* func_L04_0040A958 is in L04_00402D90-reset-g8.c. */

extern signed char *D_L04_001B24DC __attribute__((sda));

extern void func_40E248(char *a0, char *a1);

/* Retail reaches its record base off $gp (a small-data symbol), and the three
   state words at 0x48 of the record and of the indexed record. */
/* Lets go of the racer sound handles and clears a state word on the racer and on the racer it is linked to. */
void func_L04_0040AC30(char *moby, char *vars)
{
    char *mobyCopy = moby;
    char *varsCopy = vars;

    func_40E248(mobyCopy, varsCopy);
    *(int *)(mobyCopy + 0x48) = 0;
    if (*(int *)(varsCopy + 0x1DC) != -1) {
        *(int *)((*(int *)(varsCopy + 0x1DC) << 8) + (int)gMobyPool_L04 + 0x48) = 0;
    }
}

/* func_L04_0040AC98 reaches its global off $gp, so its body lives in
   L04_00402D90-g8.c. */

/* func_L04_0040ACA8 reaches one of its globals absolutely and another off $gp,
   so its body lives in L04_00402D90-g8.c. */


/* func_L04_0040AD28 is defined in L04_00402D90-results-g8.c. */

/* func_L04_0040BA68 reaches its small globals off $gp, so its body lives in
   L04_00402D90-select-g8.c. */

typedef unsigned int L04Quad __attribute__((mode(TI)));
extern int func_0030FF98(float);
extern int func_0033BA80(int);
extern float func_0033BB18(float, float);
extern void func_L04_003C4AF8(void *, float);
/* The EE assigns the point, parameter and mode to a0-a2, and the two
 * float arguments to f12-f13, independently of their C interleaving. */
extern void func_0035BF30(void *, float, float, void *, int);
/* Spawns a puff of smoke and a few small sparks at a position. Stronger hits make more of them. */
void func_L04_0040BD50(L04Quad *position, int count, float value, float intensity)
{
    float origin[4];
    float point[4];
    float parameter;
    float *base = origin;
    *(L04Quad *)origin = *position;
    parameter = value;
    if (intensity >= 0.12f) {
        if (!func_0033BA80(func_0030FF98(1.0f / intensity) + 1))
            func_L04_003C4AF8(origin, func_0033BB18(0.5f, 1.25f) * intensity * 9.0f);
    }
    if (intensity >= 0.1f) {
        if (count > 0) do {
            point[0] = base[0] + func_0033BB18(-0.3f, 0.3f);
            count--;
            point[1] = base[1] + func_0033BB18(-0.3f, 0.3f);
            point[2] = base[2];
            func_0035BF30(point, func_0033BB18(0.3f, 0.6f), 5250.0f, &parameter, -1);
        } while (count != 0);
    }
}




/* Throws a burst of small coloured particles from a point, flying roughly along a direction. */
void func_L04_0040C0C0(L04Quad *position, L04Quad *direction, int count, int mode)
{
    float velocity[4], point[4], scaled[4], result[4];
    float size, angle, pitch;
    int sign, i;
    for (i = 0; i < count; i++) {
        size = func_0033BB18(0.025f, 0.5f);
        sign = func_0033BA80(2);
        if (!sign) sign--;
        angle = func_0033BBE0();
        pitch = func_0033BB18(0.6981318f, 1.5358899f);
        BuildSphericalOffset(velocity, func_0033BB18(0.012500001f, 0.025000002f), angle, pitch);
        *(L04Quad *)scaled = *direction;
        FastVecScale(scaled, direction, func_0033BB18(0.75f, 0.95f));
        if (mode) {
            velocity[0] *= 5.0f;
            velocity[1] *= 5.0f;
            size *= 3.0f;
        }
        add_vectors(result, velocity, scaled);
        qcopy(point, position);
        point[0] += func_0033BB78(0.0f, 0.0375f);
        point[1] += func_0033BB78(0.0f, 0.0375f);
        point[2] += func_0033BB78(0.0f, 0.0375f);
        SpawnGroundEffectParticle(point, 30, 0x7f207f7f, 0, sign, velocity, size * 0.1f, size, 0.003f, 0);
        SpawnGroundEffectParticle(point, 30, 0x7f7f7f7f, 1, -sign, velocity, size * 0.07f, size * 0.7f, 0.003f, 0);
    }
}

extern void func_L04_0040D148();

extern void func_L04_0040CE30();

/* Draws the glow around a racer: the pulsing sphere when it has a shield, otherwise the normal flame effect. */
void func_L04_0040CDD0(unsigned char *moby)
{
    unsigned char *vars = *(unsigned char **)(moby + 0x68);

    if (*(unsigned int *)(vars + 0x4D8) != 0) {
        DrawPulsingGlowSphere(moby, -1);
    } else if (*(unsigned int *)(vars + 0x768) != 0) {
        DrawPulsingGlowSphere(moby, *(unsigned int *)(vars + 0x764));
    } else if (*(unsigned char *)(moby + 0xBC) != 6) {
        EmitRacerExhaustParticles(moby);
    }
}

extern void func_0029FCC0(void *, int, void *);

extern void func_00282D30(void *, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern float func_00283CE0(int);

/* The five floats come first and the two ints last: the floats then go to
   f12-f16 and the ints to a1 and a2, and the int argument is set up after
   the float ones, as the retail code has it. */
extern void func_L00_003F8280(void *, float, float, float, float, float, int, int);

/* The emitter table the object points at: the slot id at 0x644, then the
   four rows of four heights from 0x660 on. */
typedef struct {
    char pad_000[0x644];
    int slot;
    char pad_648[0x18];
    float row660[4];
    float row670[4];
    float row680[4];
    float row690[4];
} L04_0040CE30_OBJ;

/* Walks the four rows of the emitter table: every row's height is lowered by
   the shared floor, the three threshold vectors are nudged by the row's share
   and handed to the particle scheduler, and a row that sinks too far is lifted
   back to the floor. */
void func_L04_0040CE30(char *moby)
{
    L04_0040CE30_OBJ *emitters = *(L04_0040CE30_OBJ **)(moby + 0x68);
    float vec3[4];
    float vec4[4];
    float vec2[4];
    float tmp[4];
    char *dir = moby + 0xC0;
    int i;

    for (i = 0; i < 4; i++) {
        float rowFraction;
        float rise;
        float size;

        TransformMobyJointToWorld(moby, 2, vec2);
        TransformMobyJointToWorld(moby, 3, vec3);
        TransformMobyJointToWorld(moby, 4, vec4);

        emitters->row670[i] = emitters->row670[i] - emitters->row660[i];
        FastVecScale(tmp, dir, emitters->row670[i]);
        FastVecAdd(vec3, vec3, tmp);

        rowFraction = IntToFloat(i) * 0.25f;
        rise = rowFraction * 0.1f;
        vec3[2] = vec3[2] + rise;
        size = rowFraction * -0.025f + 0.05f;
        DrawFlashQuad(vec3, size, 0.0f, 0.0f, 0.0f, 0.0025f, emitters->slot, 1);
        if (emitters->row670[i] < -0.2f) {
            emitters->row670[i] = -0.05f;
        }

        emitters->row680[i] = emitters->row680[i] - emitters->row660[i];
        FastVecScale(tmp, dir, emitters->row680[i]);
        FastVecAdd(vec2, vec2, tmp);
        vec2[2] = vec2[2] + rise;
        DrawFlashQuad(vec2, size, 0.0f, 0.0f, 0.0f, 0.0025f, emitters->slot, 1);
        if (emitters->row680[i] < -0.2f) {
            emitters->row680[i] = -0.05f;
        }

        emitters->row690[i] = emitters->row690[i] - emitters->row660[i];
        FastVecScale(tmp, dir, emitters->row690[i]);
        FastVecAdd(vec4, vec4, tmp);
        vec4[2] = vec4[2] + rise;
        DrawFlashQuad(vec4, rowFraction * -0.050000004f + 0.075f, 0.0f, 0.0f, 0.0f, 0.0025f, emitters->slot, 1);
        if (emitters->row690[i] < -0.19f) {
            emitters->row690[i] = -0.05f;
        }
    }
}

/* func_L04_0040DCA8 is defined in L04_0040DCA8-quad.c. */


extern BatchA_A04_u8 D_00188660[];

extern void func_002E59F8(int handle);

/* Releases the callback records this moby still holds: every handle slot that is set
   names a record of the callback table, and the one that belongs to this moby is
   handed to the release helper. Each slot is cleared afterwards. */
/* Stops the sounds this racer has started and clears the handles it kept for them. */
void func_L04_0040E248(int mobyAddress, BatchA_A04_u8 *varsArg)
{
    int id = mobyAddress;
    BatchA_A04_u8 *vars = varsArg;
    int handleIndex;
    BatchA_A04_u8 *record;

    handleIndex = *(int *)(vars + 0x748);
    if (handleIndex != -1) {
        record = gSoundState + handleIndex * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            StopSoundVoice(handleIndex);
        }
    }
    *(int *)(vars + 0x748) = -1;

    handleIndex = *(int *)(vars + 0x74C);
    if (handleIndex != -1) {
        record = gSoundState + handleIndex * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            StopSoundVoice(handleIndex);
        }
    }
    *(int *)(vars + 0x74C) = -1;

    handleIndex = *(int *)(vars + 0x714);
    if (handleIndex != -1) {
        record = gSoundState + handleIndex * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            StopSoundVoice(handleIndex);
        }
    }
    *(int *)(vars + 0x714) = -1;

    handleIndex = *(int *)(vars + 0x3BC);
    if (handleIndex != -1) {
        record = gSoundState + handleIndex * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            StopSoundVoice(handleIndex);
        }
    }
    *(int *)(vars + 0x3BC) = -1;

    handleIndex = *(int *)(vars + 0x328);
    if (handleIndex != -1) {
        record = gSoundState + handleIndex * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            StopSoundVoice(handleIndex);
        }
    }
    *(int *)(vars + 0x328) = -1;

    handleIndex = *(int *)(vars + 0x330);
    if (handleIndex != -1) {
        record = gSoundState + handleIndex * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            StopSoundVoice(handleIndex);
        }
    }
    *(int *)(vars + 0x330) = -1;

    handleIndex = *(int *)(vars + 0x334);
    if (handleIndex != -1) {
        record = gSoundState + handleIndex * 0x70;
        if (*(int *)(record + 0x88) == id && record[0x74] != 0) {
            StopSoundVoice(handleIndex);
        }
    }
    *(int *)(vars + 0x32C) = 0;
    *(int *)(vars + 0x334) = -1;
    *(int *)(vars + 0x324) = 0;
}

/* Inlining puts the literal rate straight into $f12, so each call loads it again. */
static inline void CallL00_00322AC0(void *state, float rate, int level, int slot)
{
    AppendRecordToFourEntryTable(state, rate, level, slot);
}

/* Updates the racer boost each frame: collects nearby boost pickups, charges the boost, and keeps the boost flame, sound and camera zoom going. */
void func_L04_0040E460(unsigned char *moby)
{
    float delta[4], rotation[16];
    unsigned char *pickupMoby, *boostMoby;
    int red, green, blue;
    int period = 50;
    int alpha = 128;
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    unsigned char *state;
    int *data;
    float wave, active, angle, sine, radius;
    unsigned int color;
    angle = IntToFloat(period);
    red = D_L04_001B2008[0] % period;
    {
        float phase = (float)red;
        wave = FastSinOrCosB(((phase / angle) * 2.0f) * 3.1415927f + -3.1415927f);
    }
    red = FloatToInt(wave * 48.0f) + 104;
    green = FloatToInt(wave * 64.0f) + 208;
    blue = FloatToInt(wave * 24.0f) + 60;
    if (green > 255) green = 255;
    if (*(int *)(vars + 0x278)) {
        ApproachValue(vars + 0x27c, 0.16666669f, 0.00555555569008f);
        ApproachValue(vars + 0x28c, 97.0f, 0.5666667f);
        if (*(int *)(vars + 0x278)) FastFloatHelperD(vars + 0x278);
        UpdateTransformHistoryFollowers(vars + 0x4e0, 1);
        state = vars + 0x4e0;
    } else {
        if ((moby[0x20] == 3 || (D_00138320 & 10)) && *(int *)(vars + 0x338) < 30 && *(int *)(vars + 0x33c) > 0) {
            *(int *)(vars + 0x338) = 240;
            --*(int *)(vars + 0x33c);
            if (moby[0x20] != 3) PlaySoundFromClassBank(0, 0, moby, 0x474);
            if (!IsVoicePlayingForOwner(moby, *(int *)(vars + 0x714))) {
                if (moby[0x20] != 3) *(int *)(vars + 0x714) = PlayMobySound(15, 4, moby);
                else {
                    *(int *)(vars + 0x714) = PlayMobySound(24, 5, moby);
                    SetSoundSlotField(*(int *)(vars + 0x714), 0x400);
                }
            }
            if (*(unsigned char **)(vars + 0x4c4)) {
                unsigned char *child = *(unsigned char **)(vars + 0x4c4);
                unsigned char *childState = *(unsigned char **)(child + 0x68);
                if (*(float *)(vars + 0x27c) <= 0.016666668f) *(int *)(childState + 0x1c0) = 0;
            }
            if (!*(int *)(vars + 0x640)) {
                InitPendingSlot(moby, vars + 0x4e0);
                CallL00_00322AC0(vars + 0x4e0, -0.7f, 64, 1);
                CallL00_00322AC0(vars + 0x4e0, -0.7f, 48, 2);
                CallL00_00322AC0(vars + 0x4e0, -0.7f, 32, 3);
                CallL00_00322AC0(vars + 0x4e0, -0.7f, 16, 4);
                *(int *)(vars + 0x640) = 1;
            }
        }
        state = vars + 0x4e0;
        if (FastFloatHelperD(vars + 0x338)) {
            active = 0.0f;
            ReleaseSlotList(state);
            *(int *)(vars + 0x640) = 0;
        } else {
            active = 1.0f;
            UpdateTransformHistoryFollowers(state, 1);
        }
        ApproachValue(vars + 0x27c, active * 0.10000001f, 0.00138888892252f);
        if (*(float *)(vars + 0x27c) < 0.0f) *(float *)(vars + 0x27c) = 0.0f;
        if (active > 0.5f) ApproachValue(vars + 0x28c, 97.0f, 0.5666667f);
        else ApproachValue(vars + 0x28c, 80.0f, 0.14166668f);
    }
    if (moby[0x20] != 3) {
        float viewAngle = *(float *)(vars + 0x28c);
        viewAngle *= 0.008726647f;
        sine = FastSinOrCosB(viewAngle);
        sine /= FastSinOrCosA(viewAngle);
        D_L04_001BDC30 = sine;
        UpdateViewContext();
    }
    if (*(int *)(vars + 0x25c) != -1) {
        GetFirstMobyInGroup(&pickupMoby, *(int *)(vars + 0x25c), 0, 0);
        if (pickupMoby) do {
            if (*(short *)(pickupMoby + 0xaa) == 0xa99 /* moby class 2713 */) {
                data = *(int **)(pickupMoby + 0x68);
                FastVecSub(delta, pickupMoby + 0x10, moby + 0x10);
                if (*data == 0 && *(int *)(vars + 0x33c) < 3 && func_L00_002EE290(delta) < 1.0f) {
                    ++*(int *)(vars + 0x33c);
                    if (moby[0x20] != 3) PlaySoundFromClassBank(0, 0, moby, 0xa99);
                    SpawnParticleBurst_L04((L04Quad *)(pickupMoby + 0x10), (L04Quad *)(vars + 0x290), 8, 0);
                    *data = 300;
                }
            }
            GetNextMobyInGroup(&pickupMoby, pickupMoby, 0, 0);
        } while (pickupMoby);
    }
    if (*(int *)(vars + 0x254) != -1) {
        GetFirstMobyInGroup(&boostMoby, *(int *)(vars + 0x254), 0, 0);
        if (boostMoby) {
            /* One four-term OR would be rebalanced by fold, so the terms join in steps. */
            unsigned int high = (alpha << 24) | (blue << 16);
            high |= green << 8;
            color = high | red;
            do {
                if (*(short *)(boostMoby + 0xaa) == 0x474 /* moby class 1140 */) radius = 1.25f;
                else if (*(short *)(boostMoby + 0xaa) == 0xcef /* moby class 3311 */) radius = 3.75f;
                else goto next;
                *(unsigned short *)(boostMoby + 0x34) |= 16;
                *(unsigned int *)(boostMoby + 0x78) = color;
                if (!FastVectorHelperA(boostMoby + 0xbc)) goto next;
                FastVecSub(delta, boostMoby + 0x10, gHeroPosition);
                if (FastVecDot(delta, delta) > 20.0f) goto next;
                set_identity_matrix(rotation);
                matrix_from_basis_rows(rotation, boostMoby + 0xc0);
                transform_vector(delta, delta, rotation);
                if (!(FloatAbs(delta[0]) < 2.8f) || !(FloatAbs(delta[1]) < radius) || !(FloatAbs(delta[2]) < 1.5f)) goto next;
                data = *(int **)(boostMoby + 0x68);
                *(int *)(vars + 0x278) += *data;
                if (!IsVoicePlayingForOwner(moby, *(int *)(vars + 0x714))) {
                    if (moby[0x20] != 3) *(int *)(vars + 0x714) = PlayMobySound(15, 4, moby);
                    else {
                        *(int *)(vars + 0x714) = PlayMobySound(24, 5, moby);
                        SetSoundSlotField(*(int *)(vars + 0x714), 0x400);
                    }
                }
                if (moby[0x20] != 3) PlayMobySound(12, 0, moby);
                *(int *)(vars + 0x650) = *data;
                boostMoby[0xbc] = 60;
                if (*(unsigned char **)(vars + 0x4c4)) {
                    unsigned char *child = *(unsigned char **)(vars + 0x4c4);
                    unsigned char *childState = *(unsigned char **)(child + 0x68);
                    if (*(float *)(vars + 0x27c) <= 0.016666668f) *(int *)(childState + 0x1c0) = 0;
                }
                if (!*(int *)(vars + 0x640)) {
                    InitPendingSlot(moby, vars + 0x4e0);
                    CallL00_00322AC0(vars + 0x4e0, -0.7f, 64, 1);
                    CallL00_00322AC0(vars + 0x4e0, -0.7f, 48, 2);
                    CallL00_00322AC0(vars + 0x4e0, -0.7f, 32, 3);
                    CallL00_00322AC0(vars + 0x4e0, -0.7f, 16, 4);
                    *(int *)(vars + 0x640) = 1;
                }
next:
                GetNextMobyInGroup(&boostMoby, boostMoby, 0, 0);
            } while (boostMoby);
        }
    }
}

/* func_L04_0040EC80 is in L04_00402D90-aim.c. */

/* func_L04_0040EF50 is in L04_00402D90-g8.c. */

/* Measures the main route and its branch routes and works out where each branch joins and leaves the others. */
void func_L04_0040F5D0(unsigned char *moby)
{
    float delta[4];
    L04PathState *vars = *(L04PathState **)(moby + 0x68);
    unsigned char *base, *path, *other;
    int i, j;
    float closest, index, distance;
    if (vars->primary == -1) return;
    base = gRoutePathTable[vars->primary];
    if (*(int *)base < 3) {
        vars->primary = -1;
        return;
    }
    *(float *)(base + 0x1c) = fast_vec_dist(base + 0x10, base + 0x20);
    for (i = 0; i < 4; i++) {
        if (vars->branches[i] == -1) continue;
        path = gRoutePathTable[vars->branches[i]];
        if (*(int *)path >= 4) {
            *(float *)(path + 0x1c) = fast_vec_dist(path + 0x10, path + 0x20);
            index = 0.0f;
            closest = 999999.0f;
            if (vars->parents[i] != -1) other = gRoutePathTable[vars->branches[vars->parents[i]]];
            else other = base;
            for (j = 0; j < *(int *)other - 1; j++) {
                FastVecSub(delta, other + 0x10 + j * 16, path + 0x10);
                distance = func_L00_002EE290(delta);
                if (distance < closest) {
                    index = IntToFloat(j);
                    closest = distance;
                }
            }
            *(float *)(path + 0x2c) = index;
            *(float *)(path + 0x4c) = fast_vec_dist(other + 0x10 + FloatToInt(index) * 16, path + 0x10) + *(float *)(path + 0x2c) * *(float *)(other + 0x1c);
            index = 0.0f;
            closest = 999999.0f;
            if (vars->links[i] != -1) other = gRoutePathTable[vars->branches[vars->links[i]]];
            else other = base;
            for (j = 0; j < *(int *)other - 1; j++) {
                FastVecSub(delta, other + 0x10 + j * 16, path + *(int *)path * 16);
                distance = func_L00_002EE290(delta);
                if (distance < closest) {
                    index = IntToFloat(j);
                    closest = distance;
                }
            }
            *(float *)(path + 0x3c) = index;
            *(float *)(path + 0x5c) = fast_vec_dist(other + 0x10 + FloatToInt(index) * 16, path + *(int *)path * 16) + *(float *)(path + 0x3c) * *(float *)(other + 0x1c);
        } else vars->branches[i] = -1;
    }
}
