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
void func_L11_00397068(u8 *arg0) {
    u8 *s1 = arg0;
    u8 *s0 = *(u8 **)(s1 + 0x68);
    f32 f0, f1, f2, f4;

    FastVecAdd((f32 *)(s1 + 0x10), (f32 *)(s1 + 0x10), (f32 *)s0);
    f2 = *(f32 *)(s0 + 0x8) - 0.0041666667f;
    f0 = *(f32 *)(s0 + 0x0) * D_L11_001AEC40;
    f1 = *(f32 *)(s0 + 0x4) * D_L11_001AEC40;
    f4 = *(f32 *)(s0 + 0x20);
    *(f32 *)(s0 + 0x8) = f2;
    *(f32 *)(s0 + 0x0) = f0;
    *(f32 *)(s0 + 0x4) = f1;
    if (f2 < f4)
        *(f32 *)(s0 + 0x8) = f4;
    *(f32 *)(s1 + 0xF8) = FastAddRotations(*(f32 *)(s1 + 0xF8), *(f32 *)(s0 + 0x28));
    *(f32 *)(s1 + 0xF0) = FastAddRotations(*(f32 *)(s1 + 0xF0), *(f32 *)(s0 + 0x2C) * (f32)*(s32 *)(s0 + 0x24));
    f0 = func_00282C48(*(f32 *)(s1 + 0xF0));
    if (f0 > 0.78539824f)
        *(s32 *)(s0 + 0x24) = -*(s32 *)(s0 + 0x24);
    if (func_00282948(s0 + 0x1C) != 0) {
        func_0029F338(s1);
    } else if (s1[0x31] == 0) {
        func_0029F338(s1);
    } else if (*(s32 *)(s0 + 0x1C) < 0x1E) {
        if (func_002829A8(s1 + 0x23) != 0)
            func_0029F338(s1);
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
void func_L11_003982F0(char *self) {
    f32 control[10][4];
    s32 count = D_L11_001AECD0;
    Quad_003982F0 points[count];
    char *state = *(char **)(self + 0x68);
    s32 texture;
    f32 width, height;

    qcopy(control[0], (self + 0x10));
    qcopy(control[1], (self + 0x10));
    func_002ACB48(control[1], D_L11_001AECF0 * *(f32 *)(state + 0x2C));
    func_002A7A00(control[2], D_L11_001AECD8, D_L11_001AECDC);
    func_002A7A00(control[3], D_L11_001AECD8, D_L11_001AECDC);
    texture = func_002A7820(16, 64);
    width = func_002A7878(D_L11_001AECE0, D_L11_001AECE4);
    height = func_002A7878(D_L11_001AECE8, D_L11_001AECEC);
    func_L11_00397C08(points, D_L11_001AECD0, control, D_L11_001AECD4);
    func_L11_00397E68(points, D_L11_001AECD0, texture, D_L11_001AECF4, D_L11_001AECF8, width, height);
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
PieceMoby_00396DC8 *func_L11_00396DC8(void *unused, f32 *position, f32 *motion) {
    PieceMoby_00396DC8 *obj = CreateMoby(0x1AC);

    if (obj != 0) {
        Piece_00396DC8 *vars;
        s32 low;

        obj->modeBits |= 0x1000;
        obj->updateDist = 0x40;
        obj->drawDist = 0x20;
        obj->drawn = 1;
        vars = obj->vars;
        obj->state = 0;
        obj->byteBC = 0;
        qcopy(obj->pos, position);
        obj->pos[2] += func_002A7878(0.2f, 0.7f);
        obj->pos[0] += motion[0] * 3.0f;
        obj->pos[1] += motion[1] * 3.0f;
        qcopy(vars, motion);
        obj->rot[1] = func_002A78D8(0.17453295f, 0.523598849773407f);
        obj->rot[0] = func_002A7878(0.17453295f, 0.7853982448577881f);
        vars->swingRate = func_002A7878(200.0f, 370.0f) * 0.00029088825f;
        vars->swingDir = -1;
        if (func_001163B0() & 1) {
            vars->swingDir = 1;
            obj->rot[1] = -obj->rot[1];
        }
        obj->rot[2] = func_002A7940();
        vars->spinRate = -(func_002A7878(200.0f, 550.0f) * 0.00029088825f);
        vars->random10 = func_002A7940();
        vars->random14 = func_002A7940();
        low = FloatToInt((f32)D_L11_001AEC3C * 0.7f);
        vars->lifetime = func_002A7820(low, FloatToInt((f32)D_L11_001AEC3C * 1.2f));
        obj->scale *= D_L11_001AEC38;
        if (((JobaChoice_00396DC8 *)(D_L11_00279BA0 + D_00139578[0] * 0xE0))->enabled)
            obj->scale += obj->scale;
        vars->minFall = func_002A7878(-1.2f, -0.4f) * 0.016666668f;
        func_002A0F48(obj);
        func_002AB650(obj);
    }
    return obj;
}
