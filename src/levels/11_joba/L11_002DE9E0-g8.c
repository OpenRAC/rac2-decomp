#include "common.h"

extern void func_00282CC0(f32 *a0, f32 *a1, f32 *a2);

extern f32 func_00283B98(f32 a0, f32 a1);

extern f32 func_00282C48(f32 a0);

extern s32 func_00282948(void *a0);

extern s32 func_002829A8(void *a0);

extern void func_0029F338(void *a0);

/* The scale factor of the state's two velocity halves, reached through $gp. */
extern f32 D_L11_001AEC40 __attribute__((sda));

/* Scales the state's vector by the level's factor, clamps its timer to the state's
   limit, and runs the two animation angles through the engine's wrap function. */
/* Updates a falling, swinging piece of debris: it slows down, drops and spins. */
void func_L11_00397068(u8 *mobyArg) {
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 valueA, valueB, fallSpeed, minFall;

    FastVecAdd((f32 *)(moby + 0x10), (f32 *)(moby + 0x10), (f32 *)vars);
    fallSpeed = *(f32 *)(vars + 0x8) - 0.0041666667f;
    valueA = *(f32 *)(vars + 0x0) * D_L11_001AEC40;
    valueB = *(f32 *)(vars + 0x4) * D_L11_001AEC40;
    minFall = *(f32 *)(vars + 0x20);
    *(f32 *)(vars + 0x8) = fallSpeed;
    *(f32 *)(vars + 0x0) = valueA;
    *(f32 *)(vars + 0x4) = valueB;
    if (fallSpeed < minFall)
        *(f32 *)(vars + 0x8) = minFall;
    *(f32 *)(moby + 0xF8) = FastAddRotations(*(f32 *)(moby + 0xF8), *(f32 *)(vars + 0x28));
    *(f32 *)(moby + 0xF0) = FastAddRotations(*(f32 *)(moby + 0xF0), *(f32 *)(vars + 0x2C) * (f32)*(s32 *)(vars + 0x24));
    valueA = FloatAbs(*(f32 *)(moby + 0xF0));
    if (valueA > 0.78539824f)
        *(s32 *)(vars + 0x24) = -*(s32 *)(vars + 0x24);
    if (FastFloatHelperD(vars + 0x1C) != 0) {
        MarkMobySpawned(moby);
    } else if (moby[0x31] == 0) {
        MarkMobySpawned(moby);
    } else if (*(s32 *)(vars + 0x1C) < 0x1E) {
        if (FastVectorHelperA(moby + 0x23) != 0)
            MarkMobySpawned(moby);
    }
}

typedef int Quad_003982F0 __attribute__((mode(TI)));
extern void func_002ACB48(f32 *vector, f32 scale);
extern void func_002A7A00(f32 *out, f32 low, f32 high);
extern s32 func_002A7820(s32 low, s32 high);
extern f32 func_002A7878(f32 low, f32 high);
extern void func_L11_00397C08(void *points, s32 count, void *control, f32 noise);
extern void func_L11_00397E68(void *points, s32 count, s32 flags, u32 color0, u32 color1,
                              f32 width, f32 scale);
extern s32 D_L11_001AECD0 __attribute__((sda));
extern f32 D_L11_001AECD4 __attribute__((sda));
extern f32 D_L11_001AECD8 __attribute__((sda));
extern f32 D_L11_001AECDC __attribute__((sda));
extern f32 D_L11_001AECE0 __attribute__((sda));
extern f32 D_L11_001AECE4 __attribute__((sda));
extern f32 D_L11_001AECE8 __attribute__((sda));
extern f32 D_L11_001AECEC __attribute__((sda));
extern f32 D_L11_001AECF0 __attribute__((sda));
extern u32 D_L11_001AECF4 __attribute__((sda));
extern u32 D_L11_001AECF8 __attribute__((sda));

/* Builds a randomized strip from the object's position, as func_L18_003FD630 does from
   its state's point: two control points, two random tangents, then the ribbon. */
/* Draws a jagged, lightning-like ribbon starting at the object's position. */
void func_L11_003982F0(char *self) {
    f32 control[10][4];
    s32 count = D_L11_001AECD0;
    Quad_003982F0 points[count];
    char *vars = *(char **)(self + 0x68);
    s32 texture;
    f32 width, height;

    qcopy(control[0], (self + 0x10));
    qcopy(control[1], (self + 0x10));
    AddRandomOffsetToVector(control[1], D_L11_001AECF0 * *(f32 *)(vars + 0x2C));
    RandomDirectionVector(control[2], D_L11_001AECD8, D_L11_001AECDC);
    RandomDirectionVector(control[3], D_L11_001AECD8, D_L11_001AECDC);
    texture = RandomIntRange(16, 64);
    width = RandomFloatRange(D_L11_001AECE0, D_L11_001AECE4);
    height = RandomFloatRange(D_L11_001AECE8, D_L11_001AECEC);
    BuildJitteredCurvePoints_L11(points, D_L11_001AECD0, control, D_L11_001AECD4);
    DrawTwoLayerRibbon(points, D_L11_001AECD0, texture, D_L11_001AECF4, D_L11_001AECF8, width, height);
}

extern void *func_0029EFD0(s32 classId);
extern f32 func_002A78D8(f32 low, f32 high);
extern f32 func_002A7940(void);
extern s32 func_001163B0(void);
extern s32 func_00283CF0(f32 value);
extern void func_002A0F48(void *moby);
extern void func_002AB650(void *moby);
extern s32 D_L11_001AEC3C __attribute__((sda));
extern f32 D_L11_001AEC38 __attribute__((sda));
extern u8 D_00139578[];
/* One 0xE0-byte record of the level's selection table (as in L11_00443498-g8.c). */
typedef struct {
    u8 pad[4];
    u8 enabled;
    u8 rest[0xDB];
} JobaChoice_00396DC8;
extern u8 D_L11_00279BA0[];

/* The spawned piece's private block, as func_L11_00397068 updates it. */
typedef struct {
    f32 velocity[4];
    f32 random10;
    f32 random14;
    s32 pad18;
    s32 lifetime;
    f32 minFall;
    s32 swingDir;
    f32 spinRate;
    f32 swingRate;
} Piece_00396DC8;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 state;
    u8 pad21[0x2C - 0x21];
    f32 scale;
    u8 updateDist;
    u8 drawn;
    u16 drawDist;
    u16 modeBits;
    u8 pad36[0x68 - 0x36];
    Piece_00396DC8 *vars;
    u8 pad6C[0xBC - 0x6C];
    u8 byteBC;
    u8 padBD[0xF0 - 0xBD];
    f32 rot[3];
} PieceMoby_00396DC8;

/* Spawns a moby at POSITION pushed three frames along MOTION, with random swing and spin
   rates, a random lifetime around D_L11_001AEC3C frames and the level's scale (doubled
   when the current selection record is enabled). */
/* Creates one flying piece of debris at a position and gives it a random spin and
   lifetime. */
PieceMoby_00396DC8 *func_L11_00396DC8(void *unused, f32 *position, f32 *motion) {
    PieceMoby_00396DC8 *piece = CreateMoby(0x1AC /* moby class 428 */);

    if (piece != 0) {
        Piece_00396DC8 *vars;
        s32 low;

        piece->modeBits |= 0x1000;
        piece->updateDist = 0x40;
        piece->drawDist = 0x20;
        piece->drawn = 1;
        vars = piece->vars;
        piece->state = 0;
        piece->byteBC = 0;
        qcopy(piece->pos, position);
        piece->pos[2] += RandomFloatRange(0.2f, 0.7f);
        piece->pos[0] += motion[0] * 3.0f;
        piece->pos[1] += motion[1] * 3.0f;
        qcopy(vars, motion);
        piece->rot[1] = RandomSignedFloatRange(0.17453295f, 0.523598849773407f);
        piece->rot[0] = RandomFloatRange(0.17453295f, 0.7853982448577881f);
        vars->swingRate = RandomFloatRange(200.0f, 370.0f) * 0.00029088825f;
        vars->swingDir = -1;
        if (Rand() & 1) {
            vars->swingDir = 1;
            piece->rot[1] = -piece->rot[1];
        }
        piece->rot[2] = RandomAngle();
        vars->spinRate = -(RandomFloatRange(200.0f, 550.0f) * 0.00029088825f);
        vars->random10 = RandomAngle();
        vars->random14 = RandomAngle();
        low = FloatToInt((f32)D_L11_001AEC3C * 0.7f);
        vars->lifetime = RandomIntRange(low, FloatToInt((f32)D_L11_001AEC3C * 1.2f));
        piece->scale *= D_L11_001AEC38;
        if (((JobaChoice_00396DC8 *)(D_L11_00279BA0 + D_00139578[0] * 0xE0))->enabled)
            piece->scale += piece->scale;
        vars->minFall = RandomFloatRange(-1.2f, -0.4f) * 0.016666668f;
        func_002A0F48(piece);
        CopyHeroField38ToMoby(piece);
    }
    return piece;
}
