#include "include_asm.h"

#include "common.h"
extern void func_00282CC0(f32 *a0, f32 *a1, f32 *a2);
extern f32 func_00283B98(f32 a0, f32 a1);
extern f32 func_00282C48(f32 a0);
extern s32 func_00282948(void *a0);
extern s32 func_002829A8(void *a0);
extern void func_0029F338(void *a0);
extern f32 D_L11_001AEC40 __attribute__((sda));
extern s32 func_002A7820(s32 low, s32 high);
extern f32 func_002A7878(f32 low, f32 high);
extern s32 D_L11_001AECD0 __attribute__((sda));
extern f32 D_L11_001AECD4 __attribute__((sda));
extern f32 D_L11_001AECD8 __attribute__((sda));
extern f32 D_L11_001AECDC __attribute__((sda));
extern f32 D_L11_001AECE0 __attribute__((sda));
extern f32 D_L11_001AECE4 __attribute__((sda));
extern f32 D_L11_001AECE8 __attribute__((sda));
extern f32 D_L11_001AECEC __attribute__((sda));
extern f32 D_L11_001AECF0 __attribute__((sda));
extern f32 func_002A78D8(f32 low, f32 high);
extern f32 func_002A7940(void);
extern s32 func_001163B0(void);
extern s32 func_00283CF0(f32 value);
extern s32 D_L11_001AEC3C __attribute__((sda));
extern f32 D_L11_001AEC38 __attribute__((sda));
extern u8 D_00139578[];
extern u8 D_L11_00279BA0[];

/* Scales the state's vector by the level's factor, clamps its timer to the state's
   limit, and runs the two animation angles through the engine's wrap function. */
void func_PAL_L11_00399E30(u8 *arg0) {
    u8 *s1 = arg0;
    u8 *s0 = *(u8 **)(s1 + 0x68);
    f32 f0, f1, f2, f4;

    func_00282CC0((f32 *)(s1 + 0x10), (f32 *)(s1 + 0x10), (f32 *)s0);
    f2 = *(f32 *)(s0 + 0x8) - 0.006f;
    f0 = *(f32 *)(s0 + 0x0) * D_L11_001AEC40;
    f1 = *(f32 *)(s0 + 0x4) * D_L11_001AEC40;
    f4 = *(f32 *)(s0 + 0x20);
    *(f32 *)(s0 + 0x8) = f2;
    *(f32 *)(s0 + 0x0) = f0;
    *(f32 *)(s0 + 0x4) = f1;
    if (f2 < f4)
        *(f32 *)(s0 + 0x8) = f4;
    *(f32 *)(s1 + 0xF8) = func_00283B98(*(f32 *)(s1 + 0xF8), *(f32 *)(s0 + 0x28));
    *(f32 *)(s1 + 0xF0) = func_00283B98(*(f32 *)(s1 + 0xF0), *(f32 *)(s0 + 0x2C) * (f32)*(s32 *)(s0 + 0x24));
    f0 = func_00282C48(*(f32 *)(s1 + 0xF0));
    if (f0 > 0.78539824f)
        *(s32 *)(s0 + 0x24) = -*(s32 *)(s0 + 0x24);
    if (func_00282948(s0 + 0x1C) != 0) {
        func_0029F338(s1);
    } else if (s1[0x31] == 0) {
        func_0029F338(s1);
    } else if (*(s32 *)(s0 + 0x1C) < 0x19) {
        if (func_002829A8(s1 + 0x23) != 0)
            func_0029F338(s1);
    }
}

extern void *func_0029EFD0(s32 classId);
extern void func_002A0F48(void *moby);
extern void func_002AB650(void *moby);
typedef struct {
    u8 pad[4];
    u8 enabled;
    u8 rest[0xDB];
} JobaChoice_00396DC8;
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
extern u8 D_PAL_001400E0[];

/* Spawns a moby at POSITION pushed three frames along MOTION, with random swing and spin
   rates, a random lifetime around D_L11_001AEC3C frames and the level's scale (doubled
   when the current selection record is enabled). */
PieceMoby_00396DC8 *func_PAL_L11_00399B70(void *unused, f32 *position, f32 *motion) {
    PieceMoby_00396DC8 *obj = func_0029EFD0(0x1AC);

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
        vars->swingRate = func_002A7878(200.0f, 370.0f) * 0.0003490659f;
        vars->swingDir = -1;
        if (func_001163B0() & 1) {
            vars->swingDir = 1;
            obj->rot[1] = -obj->rot[1];
        }
        obj->rot[2] = func_002A7940();
        vars->spinRate = -(func_002A7878(200.0f, 550.0f) * 0.0003490659f);
        vars->random10 = func_002A7940();
        vars->random14 = func_002A7940();
        low = func_00283CF0((f32)D_L11_001AEC3C * 0.7f);
        vars->lifetime = ((s32)(func_002A7820(low, func_00283CF0((f32)D_L11_001AEC3C * 1.2f))) * 5 + 2) / 6;
        obj->scale *= D_L11_001AEC38;
        if (((JobaChoice_00396DC8 *)(D_PAL_001400E0 + D_00139578[0] * 0xE0))->enabled)
            obj->scale += obj->scale;
        vars->minFall = func_002A7878(-1.2f, -0.4f) * 0.020000001f;
        func_002A0F48(obj);
        func_002AB650(obj);
    }
    return obj;
}
